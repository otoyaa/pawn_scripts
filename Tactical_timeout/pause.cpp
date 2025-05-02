// file in sma

#include <amxmodx>
#include <cstrike>

new scoreboard[33];
new tr=0,ct=0,MAXPAUSE=2;
new flag=0;

public plugin_init(){
    register_plugin("tactical pause plugin","first","otoya");
    register_event("DeathMsg","cnt_kills","a");
    register_clcmd("say /pause","pedir_pause");
    // register_clcmd("say /p",pedir_pause);
}

public cnt_kills(){
    new who_kill=read_data(1);
    if(is_user_connected(who_kill)){
        ++scoreboard[who_kill];
    }
}

// o jogador só pode pedir pause se ele for o top-fragger
public is_captain(id,team){
    new mx=0,slot=-1;"
    for(new i=1;i<=32;++i){
        if(is_user_connected(i)){
            new user_team=get_user_team(i);
            if(user_team!=team)continue;
            if(scoreboard[i]>mx){
                mx=scoreboard[i];
                slot=i;
            }
        }
    }
    if(id==slot&&scoreboard[slot]==mx){
        return 1;
    }
    return 0;
}

public in_game_functions(id){
    // quando começar um round mp_freezetime vai ser 30, e logo dps voltar pra 12
    new name[33];
    get_user_name(id,name,charsmax(name));
    client_print(0,print_chat,"[PAUSE] - o jogador %s pediu um pause!",name);
    server_cmd("mp_freezetime 30");
}

// se o player que pedir o pause for top rank, posso mudar esse sistema dps
public pedir_pause(id){
    new id_team=get_user_team(id);
    new f=is_captain(id,id_team);
    if(f){
        in_game_functions(id);
    }else{
        client_print(id,print_chat,"[PAUSE] - Você não é o capitão e não pode pedir pause.");
    }
}
