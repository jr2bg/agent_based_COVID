//#include<fstream>
/*
int data_w_row(std::vector<int> data, std::string filename){
  int n = data.size();
  std::ofstream file2w (filename);
  for (int j = 0; j < n; j++){
    file2w << data[j];
    if (j < n-1) file2w << ",";
  }
  file2w <<"\n";
  file2w.close();
  return 0;
}

int data_w_mat(std::vector<std::vector<int>> data, std::string filename){
  int n = data.size();
  std::ofstream file2w (filename);
  for (int j = 0; j < n; j++){
    file2w << data[j];
    if (j < n-1) file2w << ",";
  }
  file2w <<"\n";
  file2w.close();
  return 0;
}*/

// YA TIENEN QUE ESTAR EN FRACCION
int WRITE_frac_agents_infected_acumNact(std::vector<double> time, int sz,
                                    std::vector<double> acum, //FRACCION
                                    std::vector<double> act){ //FRACCION
  /*n_agents
  barrer sobre toda la lista para encontrar todos los infectados actuales
  barrer toda la lista para encontrar el acumulado
  tener el tiempo
  entregar un csv con las columnas tiempo, frac_acum, frac_act*/
  
  std::ofstream file2w("fraccion_infectados_acumuladosYactivos.csv");
  //int sz = time.size();
  
  // encabezado
  file2w << "tiempo,frac_inf_acum,frac_inf_act";
  
  for (int j = 0; j < sz; j++){
    file2w << "\n" << time[j] << "," << acum[j] << "," << act[j];
  }
  file2w.close();
  return 0;  
}

int WRITE_prop_sintom_acum(std::vector<double> time, int sz,
                std::vector<double> sintom){
  
  std::ofstream file2w("proporcion_sintomaticos.csv");
  file2w << "tiempo,prop_sintomaticos";
  
  for (int j = 0; j < sz; j++){
    file2w << "\n" << time[j] << "," << sintom[j];
  }
  file2w.close();
  return 0;
}

// fracción de agentes que actualmente están en sintomáticos
// + los que actualmente están cuarentena  
int WRITE_frac_act_sympNquar(std::vector<double> time, int sz,
                            std::vector<double> symp,
                            std::vector<double>quar){
  
  std::ofstream file2w ("fraccion_sintomaticos_cuarentena_activos.csv");
  
  file2w << "tiempo,frac_sint_act,frac_cuar_act";
  for (int j = 0; j < sz; j++){
    file2w << "\n" << time[j] << "," << symp[j] <<","<< quar[j];
  }
  file2w.close();
  return 0;
}


int WRITE_frac_inmunAct_deceAcum( std::vector<double>time, int sz,
                                std::vector<double> inmunAct,
                                std::vector<double>deceAcum ){
  
  std::ofstream file2w("fraccion_inmunesActivos_fallecidosAcumulados.csv");
  file2w << "tiempo,frac_inmun_act,frac_dece_acum";
  
  for (int j = 0; j < sz; j++){
    file2w << "\n" << time[j] << "," << inmunAct[j] <<","<< deceAcum[j];
  }
  file2w.close();
  return 0;
}


int WRITE_agent_dynamics(){
}
