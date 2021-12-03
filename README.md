# Remote command execution using TCP
Allows the client to execute command on server's system over LAN. 

<b>Installation </b>

For creating server - 
<ul>
<li>Change the host IP address to server's IP address</li>
<li>Store passfile.txt in same directory as server.c file, it stores the LoginID and Passwords</li>
<li>Run the server.c script using gcc compiler.</li>
</ul>

For running server-
<ul>
<li>Change the host IP address to server's IP address</li>
<li>Run the client.c script using gcc compiler.</li>
</ul>

<b>Usage</b>
<ul>
<li>The Client have to enter correct pair of LoginID and password</li>
<li>Then he can enter command client want to execute on server's system.</li>
<li>Then enter exit to close the connection</li>
</ul>
