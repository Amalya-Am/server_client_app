Welcome to  Server-Client application

Build: make 
Run Server: ./server1 1234
Run Client: ./client1 127.0.0.1 1234 


Server: 
		Receive shell commands and execute them.
		When receive message: disconnect, disconnects client.
		Can connects max 5 clients.
		
Client:	
		Send shell commands in this form "command", for example "pwd".
		For disconnect, send disconnect.
