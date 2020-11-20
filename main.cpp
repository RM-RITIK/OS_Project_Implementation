#include <iostream>
#include <queue>
#define MAX 1000
using namespace std;

class request {
public:
    int size;
    request(){


    }
};

class app {
public:
    int budget;
    int max_budget;
    int S;
    int F;
    int weight;
    queue<request> request_queue;
    app(int budget){
        this->budget = budget;
    }
};

queue<app> set_of_enqueued_appl;

app applications[MAX];
app active_appl = NULL;
int remaining_budget = 0;
bool waiting_for_next_req = false;
bool all_appl_are_idle = false;
int BUDG_INC_STEP;
int T_wait;
int V = 0;
void set_timer(int t){

};
bool there_is_no_eligible_app(){

}
int set_of_enqueued_appl_minS(){

}
app eligible_appl_with_minF(){

}
void set_of_enqueued_appl_remove(app appl){

}
void unset_timer(){

}
void C_LOOK_next_req(int size){

}

void b_f2q_insert(app appl){
    if(appl != active_appl){
        appl.S = max(V, appl.F);
    }
    else{
        appl.S = appl.F;
    }
    appl.F = appl.S + appl.budget/appl.weight;

    set_of_enqueued_appl.push(appl);

}


void b_wf2q_update_vfintime(app appl, int recieved_service){
    appl.F = appl.S + recieved_service/appl.weight;

}

void b_wf2q_insert(app active){

}
app b_wf2q_get_next_application(){
    if(there_is_no_eligible_app()){
        V = set_of_enqueued_appl_minS();
    }
    app next_appl = eligible_appl_with_minF();
    set_of_enqueued_appl_remove(next_appl);
    return next_appl;

}
void b_wf2q_inc_tot_service(int service){
    V += service;

}

void add_request(int i, request R){
    app appl = applications[i];
    appl.request_queue.push(R);

    if(appl.request_queue.size() == 1){
        if(appl != active_appl){
            b_f2q_insert(appl);
        }
        else{
            if(waiting_for_next_req){
                unset_timer();
            }

        }
    }

}
request dequeue_next_request(app actove){
    request req;
    return req;
}

request request_dispactch(){
    if(waiting_for_next_req || all_appl_are_idle){
        return NULL;
    }
    if(active_appl != NULL && remaining_budget < C_LOOK_next_req(active_appl.request_queue.size())){
        b_wf2q_update_vfintime(active_appl, active_appl.budget - remaining_budget);
        if(active_appl.budget + BUDG_INC_STEP <= active_appl.max_budget){
            active_appl.budget += BUDG_INC_STEP;
        }
        else{
            active_appl.budget = active_appl.max_budget;
        }
        b_wf2q_insert(active_appl);
        active_appl = NULL;
    }

    if(active_appl == NULL ){
        active_appl = b_wf2q_get_next_application();
        remaining_budget = active_appl.budget;
    }

    request next_request = dequeue_next_request(active_appl);

    remaining_budget -= next_request.size;

    if(active_appl.request_queue.empty()){
        set_timer(T_wait);
    }

    b_wf2q_inc_tot_service(next_request.size);

    return next_request;


}
void timer_expiration(){
    active_appl.budget = active_appl.budget - remaining_budget ;
    b_wf2q_update_vfintime(active_appl , active_appl.budget) ;
    active_appl = NULL;
}

