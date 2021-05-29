## Wireless

Aim of this project is to host local files on a computer to the LAN(or to computers under a common a network).

## A little more about our aim

Suppose a file structure like
Docs/
	home.html
	g.txt

If program runs on Docs folder then, the link for accessing home.html from any computer on LAN will be
http://192.168.29.02:8000/home.html, where IP will be IP of computer where server is running.

> **NOTE** : The IP will change on every computer, to ease access once prorgam runs your own link with</br>
	with your IP will be printed to stdout.

## Benefit
Using this program anyone can host files in their home at local network using simple commands.

For a frontend-developer this will be more usefull as he/she can see real time updates in web design
on all the devices as the files are updates


## How this will be achieved

We are making this project from sratch using C language, only using system calls.
The basic idea we are following is socket programming.

We are going to program a server to host files requested by client(browser or our own client server)
 using TCP(Transmission Control Protocol).

## More technical ascpect
We are planning on building HTTP/0.9 then HTTP/1.0 then HTTP/1.1 adding features one by one.
What are these versions, let me explain
HTTP/0.9 : the first HTTP version also called one line protocol, it would only request in one line
> 	GET /mypage.html </br>

response to this is also just a file.

HTTP/1.0 : This improved the request header by appending http version  and user agent to the request
> 	GET /mypage.html HTTP/1.0</br>
> 	User-Agent: NCSA_Mosaic/2.0 (Windows 3.1)</br>

The response from server also improved adding a status code and content type the response

> 	200 OK</br>
>	 Date: Tue, 15 Nov 1994 08:12:31 GMT</br>
> 	Server: CERN/3.0 libwww/2.17</br>
> 	Content-Type: text/html</br>
> 	<HTML>
>	   A page with an image</br>
> 	</HTML>

HTTP/1.1 : The standardised protocol. This protocol added a lot of features like adding host name
		   for hosting more domains from on IP, caching, pipelining, encoding type and more.

At this point I cannot explain HTTP/1.1 all by myself so I have choosen this project so that
I can learn more about new advanced techniques used in the world.

## Installation
- > git clone "https://github.com/rapjack/Wireless.git"
- > make build
- > make run # runs at private network

If everything goes fine then, this will start server on your private
or local network.

## Progress
Server runs on private network and messages are printed on browser</br>
Log of server is maintained in /tmp/HTTPserver.log for bug checkup.

## TODO
 - Sending files over network.
 - Implementing HTTP/0.9
 - then we will implement HTTP/1.0
 - and then HTTP/1.1

## Limitations
> Server will only respond to GET method other request methods will be dumped.</br>
> Server may fail if number of requests exceed 50 at a time.</br>
> Server will not support windows however it will run on linux vm.</br>
> Server is not made for commercial purpose it is an educational project so issues with security</br>
> and reliability will not be touched.</br>