
///////////// Global variables
std::unordered_map <std::string, double> risk_factor_dp ({
                                        {"cardio_dis", 13.2},
                                        {"diabetes", 9.2},
                                        {"hb_press", 8.4},
                                        {"ch_resp_dis", 8},
                                        {"cancer", 7.6}});
                
std::unordered_map <int, double> age_dp ({{29,0.2},
                                    {39,0.2},
                                    {49,0.4},
                                    {59, 1.3},
                                    {69,3.6},
                                    {79,8},
                                    {89,14.8}});
// social force model parameters
std::unordered_map <std::string, double> sfm_param ({
                                    // "radio" del agente, lo gordito
                                    {"r_i",0.23},
                                    // masa del agente
                                    {"m_i", 83},
                                    // tiempo de relajación
                                    {"tau_i", 0.5},
                                    // socio-psycological force magnitude
                                    {"alpha", 2000},
                                    // socio-psycological force fallof length
                                    {"beta", 0.08}});
// transmission parameters
std::unordered_map <std::string, double> transm_param ({
                                    // secretion rate of SARS by infective agents
                                    {"W", 0.001 *60*60},
                                    // decay rate of SARS-CoV-2
                                    {"sigma", 0.1732 *60 *60},
                                    // probability of direct transmission
                                    {"p_d", 0.04},
                                    //parameter of indirect transmission per day
                                    {"lambda", 0.015}});

std::unordered_map<int,std::string> state = {{0, "susceptible"},
                                     {1, "infected"},
                                     {2, "symptomatic"},
                                     {3, "quarantined"},
                                     {4, "immunized"},
                                     {5, "deceased"}};

