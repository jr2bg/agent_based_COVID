#include <iostream>
#include <string>
#include <unordered_map>
#include <random>
#include <chrono>
#include <vector>
#include <utility>
#include <fstream>

#include <cmath> // ceil, floor

#include <experimental/random> // random int
#include <algorithm>    // std::swap

#include <assert.h> // <----------- TO DEBUG!!!!!

#define PI 3.14159265
#define SIGNO(numb) (numb >= 0 ? 1:-1)

#include "math_operations.h"
#include "randomness.h"
#include "global_variables.h"
#include "data_writer.h"
//#include "population_init.h" 


using std::cout;
using std::cin;
using std::unordered_map;
using std::string;
using std::vector;
using std::pair;
using std::make_pair;



///////////////////////// CLASE AGENTE
class agent{
public:
//  double v_i;
  int age;
  vector<string> risk_factors;
  // x = pos.first ; y = pos.second
  pair<double,double> pos;
  pair<double,double> vel = make_pair(0,0);
  pair<double,double> vel_d;
  int status {0};
  bool infected { false};
  double time2complete_status {0};
  double radius = 0.23;
  double mass = 83;
  pair<double,double> forces;
  double prob_decease {0};
  int immun_or_dec {0};
  bool is_infectious {false};
  long t_indTrans {0};

  bool acum_infected {false};
  bool acum_sym {false};
  bool acum_quar {false};
  bool acum_inmun {false};
  bool acum_dece {false};
  
  // function to calculate forces
  void calculate_velocity(double);
  pair<double,double> calculate_position(double);
  void actualize_status();
  void actualize_position(pair<double,double>);
  void actualize_time2complete_status(double);
  void set_prob_decease();
  bool becomes_infectious();
  void actualize_infectious(bool);
};



int set_age(double f){
  if (f <= 19.24 * 4 )
    return 18 + (59-18)* f /(19.24*4);
    
  if (f <= 91.53)
    return 60 + (69-60)* (f - 19.24 * 4) /(91.53 - 19.24 *4);
    
  if (f <= 97.61)
    return 70 + (79-70)* (f- 91.53) /(97.61 - 91.53);

  return 80 + (90-80)* (f - 97.61) /(100 - 97.61);
}

/*
//////////////////////////////// toroid relative position
pair<double,double> relative_pos_toroid(double x_sz, double y_sz, 
                        pair<double,double> pos1, pair<double,double> pos2){

  pair<double,double> rel_pos;
  double x_comp = pos2.first -pos1.first;
  double y_comp = pos2.second - pos1.second;
//  bool changed = false;
  
  if ( abs(x_comp) > x_sz /2){ 
    x_comp = pos2.first - x_sz * SIGNO(x_comp);
//    changed = true;
  }
  else x_comp = pos2.first;
  
  if (abs(y_comp) > y_sz /2) {
    y_comp = pos2.second -  y_sz * SIGNO(y_comp);
//    changed = true;
  }
  else y_comp = pos2.second;
  
//  if (not changed) return pos2;
  
  return make_pair(x_comp, y_comp);
}



// dot product:  v1°v2 = v1.x * v2.x + v1.y * v2.y
double dot_product(pair<double,double> v1, pair<double,double> v2){
  return v1.first*v2.first + v1.second * v2.second;
}


// vec_ij -> vector que va de i a j
pair<double,double> calc_vec_ij(pair<double,double> pi, pair<double,double> pj){
  pair<double,double> result;
  result = make_pair(pj.first - pi.first, pj.second - pi.second);
  return result;
}


// e_ij -> vector normalizado que va de i a j
pair<double,double> calc_e_ij(pair<double,double> pi, pair<double,double> pj){
  pair<double,double> result = calc_vec_ij(pi,pj);
  
  double norm2 = dot_product(result,result);
  double norm = sqrt(norm2);
  
  result.first = result.first/norm;
  result.second = result.second/norm;
  
  return result;
}

// suma de pares
pair<double,double> sum_pairs(pair<double,double> p1, pair<double,double> p2){
  return make_pair (p1.first + p2.first, p2.second + p1.second);
}


// multiplicación de un par por una constante
pair<double,double> doub_mult_pair(double d, pair<double,double> p){
    return make_pair (p.first * d, p.second * d);
}
*/


//////////////////////////////////////////////////////////// AGENT METHODS

//  Decease probability 
void agent::set_prob_decease(){
  if (age > 89) prob_decease = age_dp[89];
  else if (age <= 19) prob_decease = age_dp[29];
  else if (age % 10 == 9) prob_decease = age_dp[age];
  else{
    int age_inc = 9 - age %10;
    prob_decease = age_dp[age + age_inc];
  }

  for (auto factor : risk_factors){
    prob_decease += risk_factor_dp[factor];
  }
  
}


pair<double,double> agent::calculate_position(double dt){
  pair<double,double> n_pos = sum_pairs(pos, doub_mult_pair(dt, vel));

  // posiciones no salgan del toroide
  if (n_pos.first < 0 || n_pos.first >250) n_pos.first -= SIGNO(n_pos.first) *250;
  if (n_pos.second < 0 || n_pos.second > 250) n_pos.second -= SIGNO(n_pos.second) *250;

  return n_pos;
}

void agent::actualize_position(pair<double,double> n_pos){
  pos.first = n_pos.first;
  pos.second = n_pos.second;


}
void agent::calculate_velocity(double dt){
  // velocidad = t*acc = t/mass * force
  vel = sum_pairs(vel, doub_mult_pair(dt/mass, forces));
  //printf("vel_x:\t%4.4f\tvel_y:\t%4.4f\n",
  //                      vel.first, vel.second);
}


// ESTA FUNCIÓN CONTIENE LA EVOLUCIÓN DEL STATUS
// actualizaremos el tiempo para los agentes que estén enfermos
// o que se hayan contagiado
void agent::actualize_time2complete_status(double dt){
  if (infected && time2complete_status <= 0 && status < 3){
    // aumentamos en uno
    status += 1;
    
    // si es 3, debemos elegir entre 4 y 5
    // para ello usamos la probabilidad de deceso 
    if (status == 3)  {
      // fallecido  
      if (uniform_f(generator) <= prob_decease){
          
        time2complete_status = quar2dec_distribution(generator);  
        immun_or_dec = 5;
      }
      // inmunizado
      else {
        time2complete_status = quar2ret_distribution(generator);
        immun_or_dec = 4;
      }
    }
    
    // CUIDADO CON ESTE SWITCH
    switch (status){
      // infectado 
      case 1:
        time2complete_status = incub_per_distribution(generator);
      // sintomático a cuarentena  
      case 2:
        time2complete_status = symp2quar_distribution(generator);       
    }
  }
  
  else if (infected && time2complete_status <= 0 && status == 3){ 
    time2complete_status = 0;
    status = immun_or_dec;
  }  
  else if (infected) time2complete_status  -= dt;
  
  //cout << time2complete_status << "\n";
}

bool agent::becomes_infectious(){
  // infectado con menos de un día para sintomático, o;
  // sintomático
  // ==> puede infectar
  if ((status == 1 && time2complete_status <= 24 *60*60) || 
       status == 2){
    return true;
  }
  
  else return false;
}

void agent::actualize_infectious(bool infec){
  is_infectious = infec;
}

// ------------------------------------------------------------ COMMITMENT FORCE
// calculamos el vector e_ij con las posiciones de los agentes i y j,  
// así como el vector velocidad
pair<double,double> f_ij__soc(agent a_i, agent a_j, 
				vector<vector<double>> &mat_dist,
				int i, int j,
                double gamma,double alpha = 2000, 
				double beta = 0.08, double d_0 = 2){
  double d_ij;
  // a_j position "in the toroid"
  pair<double,double> a_j_tpos = relative_pos_toroid(250, 250, 
                        a_i.pos, a_j.pos);
  
  d_ij = pow(a_j_tpos.first - a_i.pos.first, 2) +  
         pow(a_j_tpos.second - a_i.pos.second, 2);
         
  d_ij = sqrt(d_ij) - (a_i.radius + a_j.radius );
  mat_dist[i][j] = d_ij;
  mat_dist[j][i] = d_ij;
  
  if (d_ij < d_0){
    
    // cálculo del vector e_ij
    pair<double,double> e_ij = calc_e_ij(a_i.pos, a_j_tpos);
    // ángulo entre la velocidad deseada y el vector que une a ambos agentes
    double cos_phi_ij = dot_product(a_j.vel_d, e_ij);  
    
    
    double fijs = alpha * exp((d_ij - d_0)/beta)*
          (gamma + (1-gamma) * (1+ cos_phi_ij ) /2);
          
    return make_pair(fijs* e_ij.first, fijs * e_ij.second);
  }
  
  else
    return  make_pair(0,0);
  
}


//------------------------------------------------------------------------ F_soc
int funct_F__soc(vector<vector<pair<double,double>>> &F__soc,vector<agent> population,
                vector<vector<double>> &mat_dist ,double gamma ){
  int n_agents = population.size();
  
  for (int i = 0; i < n_agents; i++){
    for (int j = i; j < n_agents; j++){
    
      // índices son iguales ==> no hay fuerza social (mismo individuo)
      if (i == j) F__soc[i][j] = make_pair(0,0);
      
      // cómputo de la fuerza social 
      // relative_pos_toroid pide el tamaño del espacio: consideramos (250,250)
      else {
        F__soc[i][j] = f_ij__soc(population[i], population[j], 
								mat_dist, i,j, gamma);
        
        // matriz antisimétrica
        F__soc[j][i] = doub_mult_pair(-1, F__soc[i][j]);
      }
    }
  }
  return 0;
}


//----------------------------------------------------------- SELF DRIVING FORCE
pair<double,double> f_i__self(agent a_i, double tau_i = 0.5){

  return make_pair(a_i.mass/tau_i * (a_i.vel_d.first - a_i.vel.first ), 
                   a_i.mass/tau_i * (a_i.vel_d.second - a_i.vel.second) );
}

//-------------------------------------------------- DIRECT TRANSMISSION
// para el agente en i, devuelve si está infectado o no (direct trans)
bool direct_infected(int i, vector<agent> population, 
                      vector<vector<double>> mat_dist){
  
  for (int j = 0; j < mat_dist.size(); j++){
    ////cout << "agentes dist: " << mat_dist[i][j] << " infec?: "<<population[j].infected << "\n";
    // agente no es él mismo &&
    // distancia menor o igual que un metro &&
    // el agente j puede infectar  
    if (j != i && mat_dist[i][j] <= 1 && population[j].is_infectious){
        ////cout << "entered\n";
        // se infecta si  un ri generado con  distribución unif entre 0-100
        // es menor o igual que la probabilidad de transmisión directa
        if (uniform_f(generator) <= transm_param["p_d"] * 100){
        //if (uniform_f(generator) <= 100){
          /////cout << "hola\n";
          return true;
        }
      }
    }
  return false;    
}

//------------------------------------------------ INDIRECT TRANSMISSION
// para el agente en i, devuelve si está infectado o no (indirect trans)
bool indirect_infected(int i, vector<vector<double>> mat_concentration){
    
}

// --------------------------------------------------- POPULATION INITIALIZATION
int initialize_agents(vector<agent> &population, int n_agents){

  
  // initialization loop
  for (int i = 0; i < n_agents; i++){
  
    // velocity -> follows a normal distribution
    double v_i = speed_nd(generator);
    
    // proyections: vel_d.first, vel_d.second
    // elegimos aleatoriamente un número entre [0,360] que corresponderá al ángulo
    double angle_st = uniform_f(generator)*3.6;
    // sin, cos need RADIANS
    population[i].vel_d = make_pair(v_i * sin(angle_st*2*PI/360), 
                                    v_i * cos(angle_st*2*PI/360));
    
    // age
    population[i].age = set_age(uniform_f(generator));
    // risk factors
    if (uniform_f(generator) <= 25)
      population[i].risk_factors.push_back("cardio_dis");
    if (uniform_f(generator) <= 8)
      population[i].risk_factors.push_back("diabetes");
    if (uniform_f(generator) <= 25)
      population[i].risk_factors.push_back("hb_press");
    if (uniform_f(generator) <= 5)
      population[i].risk_factors.push_back("ch_resp_dis");
    if (uniform_f(generator) <= 0.57)
      population[i].risk_factors.push_back("cancer");
    
    // initial place; 2.5 para tomar valores en en intervalo [0,250)
    population[i].pos.first = 2.5 * uniform_f(generator);
    population[i].pos.second = 2.5 * uniform_f(generator);
    
    // estado inicial
    //population[i].status = 0;
    
    // death probability
    population[i].set_prob_decease();

    // time when the indirect transmission is possible
    population[i].t_indTrans = time_ind_trans_day(generator);
  }
  return 0;
}


// ----------------------------------------------------------------- TOTAL FORCE
// estamos cambiando la fuerza del agente a_i, por eso el  &a_i
pair<double,double> total_force(agent &a_i, int i, int n_agents,
                                vector<vector<pair<double,double>>> F__soc ){
  // self driving force
  pair<double,double> t_force = f_i__self(a_i);
  //printf("self_df_x:\t%4.4f\tself_df_y:\t%4.4f\n",t_force.first, t_force.second);
  
  
  // commitment force: suma de todos los elementos en la i-ésima fila de F__soc
  for (int j = 0; j < n_agents; j++){
    //printf("f_x:\t%4.4f\tf_y:\t%4.4f\n",t_force.first, t_force.second);
    t_force = sum_pairs(t_force, F__soc[i][j]);
  }
  
  // actualización de forces en el i-ésimo agente 
  a_i.forces = t_force;
//  printf("f_x:\t%4.4f\tf_y:\t%4.4f\n",a_i.forces.first, a_i.forces.second);
  
  return t_force;
}


// ----------------------------------------------------------------- DRIVER LOOP
vector<agent> driver_pop(){

  // número de agentes
  int n_agents = 100;//250;
  int n_binf = 1;  // number of agentes infected at the beginning
  int nx_nodes = 250;
  int ny_nodes = 250;
  int n_nodes = nx_nodes * ny_nodes;
  // inicialización del tiempo transcurrido
  long tiempo_transc = 0;

  // INITIALIZATION OF VECTORS TO WRITE
  vector<double> w_time;
  vector<double> frac_infected_acum;
  double infected_acum = 0;
  vector<double> frac_infected_active;
  double infected_active;
  
  vector<double> frac_sintom_acum;
  double sintom_acum = 0;
  
  vector<double> frac_sym_active;
  double sym_active;
  vector<double> frac_quar_active;
  double quar_active;
  
  vector<double> frac_inmunAct;
  double inmunAct;
  vector<double> frac_deceAcum;
  double deceAcum = 0;
  
  
  
  
  // vector con n_agents elementos, cada uno es un agente
  vector<agent> population (n_agents, agent());
  
  // vector para el orden de los agentes
  vector<int> order_agents (n_agents);
  for (int j = 0; j < n_agents; j++) order_agents[j] = j;
  

  // función para inicializar a los agentes
  initialize_agents(population, n_agents);//, generator);
  
  // función para inicializar el estatus de la concentración en el espacio
  vector<vector<double>> mat_concentracion (ny_nodes, vector<double> (nx_nodes, 0));

  
  // F__soc tendrá todos los valores de f_ij__soc
  // f_ji_soc = -f_ij__soc
  vector<vector<pair<double,double>>> F__soc (n_agents, vector<pair<double,double>> (n_agents));

  // matriz de distancias relativas entre los agentes
  vector<vector<double>> mat_dist (n_agents, vector<double> (n_agents));
  
  // vector con las nuevas posiciones de los agentes
  vector<pair<double,double>> nw_pos (n_agents);
  
  // vector que indica si es infeccioso o no el agente
  vector<bool> infect_vect (n_agents, false);
  
  // función para calcular las fuerzas por interacción con otros agentes
  // contiene las variables alpha, beta, d_0 DENTRO de ella (calculo de f_ij__soc)
  double gamma = 0.5;
  //funct_F__soc(F__soc, population,mat_dist, gamma );
  
  // time step (10^-4 h) en segundos
  double dt = 0.0001 * 60 *60;
  
  
  /*///////////////TEST--
  // agente_0: infectado
  //population[0].status = 1;
  population[0].infected = true;
  population[0].pos.first = 1;
  population[0].pos.second = 1;
  population[1].pos.first = 1.1;
  population[1].pos.second = 1.2;
  //population[0].actualize_time2complete_status( generator, dt);
  //population[0].time2complete_status = 0.5;
  //cout << "tiempo: "<<population[0].time2complete_status << "\n";
  ////cout << "probabilidad de deceso: " << population[0].prob_decease << "\n"; 
  //////////// END TEST*/
  
  
  // Random shuffle of population
  Fisher_Yates_shuffle(order_agents);
  //elegimos agentes que sean infecciosos al principio
  for (int j = 0; j < n_binf; j++) population[order_agents[j]].infected = true;
  
  
  //-------- LOOP DE ACTUALIZACIÓN DE LA POSICIÓN Y VELOCIDAD DE CADA AGENTE
  // T -> número de veces que se repite el ciclo
  for (long T = 1 ; T < 10000001; T++){
    printf("\n------  ciclo #%ld ----\n", T);
	
	// actualización de la matriz de fuerza social
    funct_F__soc(F__soc, population,mat_dist, gamma );
    
    infected_active = 0;
    sym_active = 0;
    quar_active = 0;
    inmunAct = 0;
    
    // ciclo de actualización de información independiente
    for (int i = 0; i < population.size(); i++){
      //printf("---  agente #%d ------\n",i);
      
      // cómputo de la fuerza total en cada agente
      total_force(population[i], i, n_agents, F__soc );
      
      // dinámica de cada agente
      nw_pos[i] = population[i].calculate_position(dt);
      population[i].calculate_velocity(dt);
      
      
      // se infecta (solo si es suceptible)
      if (population[i].status == 0 && ! population[i].infected){
        // cambiar population[i].infected
        //infectado: transmisión directa
        bool infec = direct_infected(i, population,mat_dist);
      
      
        //infectado: transmisión indirecta
        //infec = infec || indirect_infected();
        
        population[i].infected = infec;
      
      }
      // cambia el tiempo solo si está enfermo
      population[i].actualize_time2complete_status( dt);
      
      
      // infeccioso o no
      infect_vect[i] = population[i].becomes_infectious();
      
      
           
      //cout << "status: " << state[population[i].status] << "\ttime: "<<
      //     population[i].time2complete_status << "\n";
      
      //for (auto rel_d: mat_dist[i]) printf("distancia: %4.2f\t",rel_d);
      
      
      //printf("pos_x:\t%4.2f\tpos_y:\t%4.2f\n",
      //                      population[i].pos.first, population[i].pos.second);
      /*printf("vel_x:\t%4.4f\tvel_y:\t%4.4f\n",
                            population[i].vel.first, population[i].vel.second);
      printf("f_x:\t%4.4f\tf_y:\t%4.4f\n\n",
                            population[i].forces.first, population[i].forces.second);*/
    
      if (population[i].status == 1){
        infected_active += 1;
        if (!population[i].acum_infected){
          infected_acum += 1;
          population[i].acum_infected = true;
        }
      }
      else if (population[i].status == 2){
        sym_active += 1;
        if (!population[i].acum_sym){
          sintom_acum += 1;
          population[i].acum_sym = true;
        }
      }
      else if (population[i].status == 3){
        quar_active += 1;  
      }
      else if (population[i].status == 4){
        inmunAct += 1;
      }
      else if (population[i].status == 5){
        if (!population[i].acum_dece){
          deceAcum += 1;
          population[i].acum_dece = true;
        }
      }
    }
    
    
    // ciclo de la actualización de información dependiente 
    for (int i = 0; i < population.size(); i++){
      // posición en el toroide
      population[i].actualize_position(nw_pos[i]);
      // infeccioso o no
      population[i].actualize_infectious(infect_vect[i]);
      // actualización del nivel de concentración en el espacio
	}
  
  
  
  /*
  // escritura
    if (T% 100 == 0){
      for (int  i= 0; i < n_agents; i++){
        population[i].t_indTrans = T + time_ind_trans_day(generator);
      }
    }*/
    
  // guardado en vectores
    if (T % 100 == 0){
      w_time.push_back(T* dt);
      frac_infected_acum.push_back(infected_acum / n_agents);
      frac_infected_active.push_back(infected_active / n_agents);
  
      frac_sintom_acum.push_back(sintom_acum /n_agents);
  
      frac_sym_active.push_back(sym_active / n_agents);
      frac_quar_active.push_back(quar_active/n_agents);
  
      frac_inmunAct.push_back(inmunAct / n_agents);
      frac_deceAcum.push_back(deceAcum/ n_agents);
      
    }
  }
  
  // guardado en archivos
  int sz = w_time.size();
  WRITE_frac_agents_infected_acumNact(w_time, sz,
                                    frac_infected_acum,
                                    frac_infected_active);
  
  WRITE_prop_sintom_acum(w_time, sz,
                    frac_sintom_acum);
  
  WRITE_frac_act_sympNquar(w_time, sz,
                        frac_sym_active,
                        frac_quar_active);
  
  WRITE_frac_inmunAct_deceAcum(w_time, sz,
                            frac_inmunAct,
                            frac_deceAcum);
  


  return population;
}




// ------------------------------------  MAIN  ---------------------------------
// ------------------------------------  LOOP  ---------------------------------
int main(){
  driver_pop();
  return 0;
}
