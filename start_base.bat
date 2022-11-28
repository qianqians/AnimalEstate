start ./bin/debug/center_svr.exe ./config/config_base.txt center
sleep 10
start ./bin/debug/dbproxy_svr.exe ./config/config_base.txt dbproxy
sleep 2
start ./bin/debug/gate_svr.exe ./config/config_base.txt gate
