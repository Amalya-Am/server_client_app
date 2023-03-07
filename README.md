Welcome to my Server-Client application

Run Server: make from /server/ directory.  
Run Client: make from /client/ directory.  

Introduction:

Server: 
		Receive shell commands and execute them.
		When receive message: disconnect, disconnects client.
		Can connects max 5 clients.
		
Client:	
		Send shell commands in this form "command", for example "pwd".
		For disconnect, send disconnect.
