# Communication-Network-Graph
It aims to help practice graph data structure and basic graph operations. My main task in this assignment is to develop a graph of emails using C programming language. I implemented the graph as an adjacency list in this project.

It is time to put the emails that I have worked on and processed in the previous projects in graph format. In other words, making a network of users and linking them together based on emails they 
exchange will be your task in this project.

To be more specific, I developed a program with the following functionalities:

• Read a list of emails from files without making assumptions about the length of the content 
of each email
• Make sure to take out each user and record how many emails they sent and received.
• Created a directed weighted graph where a vertex is created for each person who 
sent/received an email, and an edge is created between two vertices representing an email 
between users. For example, if A sent B an email, an edge should be drawn from A directed 
towards B. The weight of the edge should be equal to the number of words in the content of 
that email. If A sent multiple emails to B, then the weight of the edge should be the sum of 
the number of words in the emails.
• Display the graph by showing the vertices and edges by printing the adjacency list
• Display which people have the maximum number of emails sent and which people have the 
maximum number of words received.
• Check if there is a path between two given people

THIS IS A CONSOLE APPLICATION ON CODEBLOCKS!
