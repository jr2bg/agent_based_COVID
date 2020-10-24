unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  
std::default_random_engine generator (seed);


// distribuciones de probabilidad
// speed
std::normal_distribution<double> speed_nd(1.34,0.26);
// general porpuse uniform distribution
std::uniform_real_distribution<double> uniform_f(0.0,100.0);

// uniform distribution day
std::uniform_real_distribution<double> time_ind_trans_day(1.0,24000.0);


// incubation
std::lognormal_distribution<double> incub_per_distribution(5.1 *24 *60*60, 3.1 *24*60*60);
// period from symptoms to quarentine (sec)
std::normal_distribution<double> symp2quar_distribution(3.9 *24*60*60, 0.5 *24*60*60);
// period from quarantine to return to the population (sec)
std::normal_distribution<double> quar2ret_distribution(20.2 *24*60*60, 2 *24*60*60);
// period from quarantine to decease (sec)
std::normal_distribution<double> quar2dec_distribution(13 *24*60*60,1 *24*60*60);

/*
// FAKE!!!!!!!!!!!!!!!
// DISPLAY PURPOSES
// incubation
std::lognormal_distribution<double> incub_per_distribution(0.5, 0.07);
// period from symptoms to quarentine (sec)
std::normal_distribution<double> symp2quar_distribution(0.39 , 0.5 );
// period from quarantine to return to the population (sec)
std::normal_distribution<double> quar2ret_distribution(0.41, 0.05);
// period from quarantine to decease (sec)
std::normal_distribution<double> quar2dec_distribution(0.58, 0.09);
*/

int Fisher_Yates_shuffle(std::vector<int> &numeros){
  int n  = numeros.size();
  for (int j = n -1; j > 0; j--){
    std::swap(numeros[j], numeros[std::experimental::randint(0, j)]);
  }
  return 0;
}
