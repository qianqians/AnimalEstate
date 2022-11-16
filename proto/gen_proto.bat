cd ./rpc/
python genc2h.py ../proto/client_call_hub/ csharp ../gen/csharp/ ../proto/common
python genc2h.py ../proto/client_call_hub/ ts ../gen/ts/ ../proto/common
python genh2c.py ../proto/hub_call_client/ csharp ../gen/csharp/ ../proto/common
python genh2c.py ../proto/hub_call_client/ ts ../gen/ts/ ../proto/common
python genh2h.py ../proto/hub_call_hub/ csharp ../gen/csharp/ ../proto/common

cd ../
pause