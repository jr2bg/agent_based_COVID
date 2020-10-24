#ifndef SIGNO
#define SIGNO(numb) (numb >= 0 ? 1:-1)
#endif
//////////////////////////////// toroid relative position
std::pair<double,double> relative_pos_toroid(double x_sz, double y_sz, 
                        std::pair<double,double> pos1, 
                        std::pair<double,double> pos2){

  std::pair<double,double> rel_pos;
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
  
  return std::make_pair(x_comp, y_comp);
}



// dot product:  v1°v2 = v1.x * v2.x + v1.y * v2.y
double dot_product(std::pair<double,double> v1, 
                    std::pair<double,double> v2){
  return v1.first*v2.first + v1.second * v2.second;
}


// vec_ij -> vector que va de i a j
std::pair<double,double> calc_vec_ij(std::pair<double,double> pi, 
                                    std::pair<double,double> pj){
  std::pair<double,double> result;
  result = std::make_pair(pj.first - pi.first, pj.second - pi.second);
  return result;
}


// e_ij -> vector normalizado que va de i a j
std::pair<double,double> calc_e_ij(std::pair<double,double> pi, 
                                    std::pair<double,double> pj){
  std::pair<double,double> result = calc_vec_ij(pi,pj);
  
  double norm2 = dot_product(result,result);
  double norm = sqrt(norm2);
  
  result.first = result.first/norm;
  result.second = result.second/norm;
  
  return result;
}

// suma de pares
std::pair<double,double> sum_pairs(std::pair<double,double> p1, 
                                    std::pair<double,double> p2){
  return std::make_pair (p1.first + p2.first, p2.second + p1.second);
}


// multiplicación de un par por una constante
std::pair<double,double> doub_mult_pair(double d, 
                                            std::pair<double,double> p){
    return std::make_pair (p.first * d, p.second * d);
}

std::unordered_map<std::string, int> vertex_surround_agent (std::pair<double,double> ai_pos){
  std::unordered_map<std::string, int> result;
  
  // x asociado a la primera entrada
  // y a la segunda
  int  x_1,x_2, y_1, y_2;
  
  x_1 = floor(ai_pos.first);
  y_1 = floor(ai_pos.second);
  
  x_2 = ceil(ai_pos.first);
  y_2 = ceil(ai_pos.second);
  
  // por distribución inicial, ceil(z) != 250 \forall z en este trabajo
  if (x_2 == 250) x_2 = 0;
  if (y_2 == 250) y_2 = 0;
  
  if (x_1 != x_2 && y_1 != y_2) {
    result["x_1"] = x_1;
    result["y_1"] = y_1;
    result["x_2"] = x_2;
    result["y_2"] = y_2;
  }
  else if (x_1 != x_2 && y_1 == y_2){
    result["y"] = y_1;
    result["x_1"] = x_1;
    result["x_2"] = x_2;
  }
  
  else if (x_1 == x_2 && y_1 != y_2){
    result["x"] = x_1;
    result["y_1"] = y_1;
    result["y_2"] = y_2;
  }
  
  else {
    result["x"] = x_1;
    result["y"] = y_1;
  }
  return result;
}


double linear_interp(double absc1, double absc2, double conc1, double conc2, double absc){
  return conc1 + (absc -absc1) * (conc2 - conc1)/(absc2 - absc1);
}

double bilinear_interp(double x1,double x2, 
                       double y1, double y2, 
                       double x, double y,
                       double conc_x1y1, double conc_x1y2, 
                       double conc_x2y1, double conc_x2y2){
                           
  double x_inter_y1 = (x2 - x) / (x2 - x1) * conc_x1y1 + (x - x1) / (x2 - x1) * conc_x2y1;
  double x_inter_y2 = (x2 - x) / (x2 - x1) * conc_x1y2 + (x - x1) / (x2 - x1) * conc_x2y2;
  
  return (y2 - y) / (y2 - y1) * x_inter_y1 + (y - y1) / (y2 - y1) * x_inter_y2;
}
