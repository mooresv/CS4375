Remote Procedure Call (RPC) Example

Code modified from Remote Procedure Calls by Ed Petron at
https://www.linuxjournal.com/article/2204
See that article for an explanation of the code and how to build and use it. 

If you get the error below when you try to run ./avg_svc, see
https://www.looklinux.com/error-cannot-register-service-rpc-unable-to-receive-errno-connection-refused/ 
for how to fix it. You may need to install rpcbind, which you can do with
'sudo apt install rpcbind' on Ubuntu.  

  Cannot register service: RPC: Unable to receive; errno = Connection refused

