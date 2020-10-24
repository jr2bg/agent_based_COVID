para cada elemento de la matriz del espacio
hay un valor de concentración

la concentración aumenta cuando hay un infeccioso cerca
---------------- disminuye conforme pasa el tiempo dt

la transmisión indirecta puede darse solamente una vez a lo largo del día
==> función random f_t_ind_trans entre [0, 24*60*60) para cada agente y tener un 
    contador t_day para el tiempo transcurrido. 
    Cuando t_day llegue a un múltiplo de 24*60*60 que se vuelva a correr 
    f_t_ind_trans para cada agente
    agent::time_ind_trans = t_day (en múltiplo de 1 día) + f_t_ind_trans


función que determina la concentración de virus en un nodo              |
f_concent: (vector<agent>, dt, sigma, concent, pos_nodo) -----> R       |
                                                                        |
    sumaXinfectious  = f_W(vector<agent>, pos_nodo, d_0)                |
    time_decrease = -sigma * concent                                    |
                                                                        |
    DEVUELVE concent + (sumaXinfectious - time_decrease) * dt           |
                                                                        |
                                                                        |--> O(n_agents * n_rows*n_cols) !!!
función que determina el incremento en la concentración por secreciones |
de agentes infecciosos en un nodo fijo                                  |
f_W : (vector<agent>, pos_nodo, d_0 = algo) --------> R                 |
    suma_concent = 0                                                    |
    \forall agente \suchThat agente.is_infectious:                      |
        d = dist(pos_nodo, agente.pos)                                  |
        SI d <= d_0:                                                    |
            suma_concent +=  1/4 * (1 + cos(PI*d / d_0) )               |
                                                                        |
    DEVUELVE suma_concent                                               |



función que determina el decremento de concentración por nodo
f_dec_conc:(vec<vec<int>> &nodos, pos, sigma, dt) -----------------> R
    SI nodo[pos] > 0
        nodos[pos] -= nodos[pos] * sigma * dt 
    
    SI nodo[pos] < 0
        nodo[pos] = 0 


función que determina el incremento de concentración por agente
f_inc_conc: (agente, vec<vec<int>> &nodos, dt) ----------->R
    
    
  
