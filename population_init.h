// --------------------------------------------------- POPULATION INITIALIZATION
int initialize_agents(vector<agent> &population, int n_agents){
  // RANDOM
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  
  std::default_random_engine generator (seed);
  
  // speed
  std::normal_distribution<double> speed_nd(1.34,0.26);
  // general porpuse uniform distribution
  std::uniform_real_distribution<double> uniform_f(0.0,100.0);
  
  // incubation period (parameters in days)
  std::lognormal_distribution<double> incub_per_distribution(5.1, 3.1);
  
  // period from symptoms to quarentine (days)
  std::normal_distribution<double> symp2quar_distribution(3.9, 0.5);
  
  // period from quarantine to return to the population (days)
  std::normal_distribution<double> quar2ret_distribution(20.2, 2);
  
  // period from quarantine to decease (days)
  std::normal_distribution<double> quar2dec_distribution(13,1);
  
  
  
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
    
    // initial place (2.5 por que vamos de 0-250)
    population[i].pos.first = 2.5 * uniform_f(generator);
    population[i].pos.second = 2.5 * uniform_f(generator);
    
    // estado inicial
    population[i].status = 0;
  }
  return 0;
}
