SCHOOL OF COMPUTER ENGINEERING, MANIPAL INSTITUTE OF TECHNOLOGY
MID TERM LAB EXAMINATIONS, 27-09-2025
TIME: 9:30 AM – 10:30 AM
MAX MARKS: 20M

CSE3143 COMPUTER NETWORKS LAB

## Question)

You are required to design and implement a TCP Client-Server application in C.

A concurrent TCP Server runs on a computer with IP address 172.16.57.125, listening on port 6666.

• The server waits for a client connection. Once a client connects and sends a message, the server must receive the message and send back a reply.

• A TCP Client connects to the server, sends its message, waits for the reply, and then displays the reply received from the server.

• Client Message Structure contains your name and register number as character array of 50 bytes and a long integer data respectively (both are enterd as keyboard input).

• Server Reply Structure contains a character array of 100 bytes, an integer and a character array of 50 bytes.

After successfully running your client program, capture packets using Wireshark. Analyze and report the following:

• TCP 3-Way Handshake Connection Establishment
• Data Transfer Phase
• TCP 3-Way Connection Termination

For each phase, you must clearly indicate observed sequence numbers, acknowledgement numbers, relevant TCP flag registers (SYN, ACK, FIN, etc.) Sender and receiver window sizes, source and destination IP addresses, source and destination port numbers.
(You may use neat Time-Sequence Diagrams)

## SCHEME OF EVALUATION:

| **Component**                              | **Marks** |
| ------------------------------------------ | --------- |
| **Write-up (Both Client and Server Code)** | **12**    |
| Concurrent Server code                     | 8         |
| Client code                                | 4         |
| **Execution (ONLY CLIENT)**                | **08**    |
| Client connection                          | 2         |
| Display of server reply                    | 4         | 
| Wireshark analysis                         | 2         | 

Note:

Professional writeup/coding practices are expected and rewarded. This includes:

• Use of appropriate error handling techniques while using any system calls/commands  
• Clear and consistent variable naming conventions  
• Modularization of code into functions  
• Appropriate use of comments  
• Neat formatting and readability  