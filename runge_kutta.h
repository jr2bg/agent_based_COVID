/******************************************************************************
----------------- MÉTODO DE RUNGE KUTTA PARA UN SISTEMA
------------------ DE DOS ODE DE PRIMER ORDEN

INPUT: funciones, número de pasos, longitud del paso, intervalo,
       condiciones iniciales
       
OUTPUT: array con la solución de las ODE        


Lo aplicaremos solo para un paso

f1 = m*dv/dt = f__self + f__sco +f__w + epsilon
f2 = dx/dt = v

i = 1 -> velocidad
i 0 2 -> posición

*******************************************************************************/


// sum of forces es una tupla, lista de dos elementos
pair<double,double> f_velocity(double mi, pair<double, double> sum_forces_i){
    return make_pair(sum_forces_i.first/mi, sum_forces_i.second / mi)
}

vector<pair<double,double>> f_k1(double h,
                                double t_j, 
                                pair<double,double> vi, 
                                pair<double,double> xi, 
                                pair<double,double> sum_forces_i, 
                                double mi){
  // velocity
  pair<double,double> vel_k1 = f_velocity(mi, sum_forces_i);
  vel_k1.first *= h;
  vel_k1.second *= h;
  
  // position
  pair<double,double> pos_k1;
  pos_k1.first = h * vi.first;
  pos_k1.second = h * vi.second;
  
  
  return { vel_k1, pos_k1 };
} 



vector<pair<double,double>> f_k2(double h,
                                double t_j, 
                                pair<double,double> vi, 
                                pair<double,double> xi, 
                                pair<double,double> sum_forces_i, 
                                vector<pair<double,double>> res_k1;
                                double mi){
  // velocity
  pair<double,double> vel_k2 = f_velocity(mi, sum_forces_i);
  vel_k2.first *= h/2;
  vel_k2.second *= h/2;
  
  // position
  pair<double,double> pos_k2;
  pos_k2.first = h * vi.first;
  pos_k2.second = h * vi.second;
  
  
  return { vel_k1, pos_k1 };
} 
