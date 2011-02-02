===============
2011-February
===============

| [Tuesday 01 February 2011] [02:23:00] <stockMQ>	but the i need to copy the protobuf message to a struct and write the struct to a file.. 
| [Tuesday 01 February 2011] [02:23:31] <stockMQ>	I need to do this because there are other applications consuming the file and they expect a struct
| [Tuesday 01 February 2011] [02:24:02] <stockMQ>	right now i copy each field of the message to the corresponding field of the buffer
| [Tuesday 01 February 2011] [02:24:22] <stockMQ>	Is this the right way or is there any other optimized way to go about with it
| [Tuesday 01 February 2011] [03:20:33] <mikko>	stockMQ: are the other applications expecting a binary struct?
| [Tuesday 01 February 2011] [03:20:36] <mikko>	stockMQ: sounds odd
| [Tuesday 01 February 2011] [03:25:28] <stockMQ>	yes.. they too are custom applications built in house but to change them is to be avoided
| [Tuesday 01 February 2011] [04:24:31] <CIA-21>	zeromq2: 03Martin Sustrik 07sub-forward * raddcc85 10/ devices/zmq_forwarder/zmq_forwarder.cpp : 
| [Tuesday 01 February 2011] [04:24:32] <CIA-21>	zeromq2: Forwarder device uses XPUB and XSUB sockets.
| [Tuesday 01 February 2011] [04:24:32] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/eoHfSJ
| [Tuesday 01 February 2011] [04:28:50] <jugg>	having a publisher that connects to an endpoint, how would I prevent messages from being queued if the endpoint has not yet been bound?  Set the publisher HWM to zero, and call zmq_send(noblock)?
| [Tuesday 01 February 2011] [04:32:04] <sustrik>	yes, use hwm
| [Tuesday 01 February 2011] [04:33:39] <jugg>	hmm, I guess HWM = 1, as 0 is no limit...
| [Tuesday 01 February 2011] [04:34:27] <jugg>	but that'll queue a single message, no?
| [Tuesday 01 February 2011] [04:34:50] <jugg>	So a stale message will be delivered when the listener binds the endpoint.
| [Tuesday 01 February 2011] [04:57:40] <sustrik>	it that pub/sub?
| [Tuesday 01 February 2011] [05:06:18] <ianbarber>	potentially silly bug: if I destroy then recreate a sub socket with an identity too quickly I get an assert "Assertion failed: new_sndbuf > old_sndbuf (mailbox.cpp:182)" from the publisher
| [Tuesday 01 February 2011] [05:06:51] <ianbarber>	this may not be something that is sensible to do, but i encountered it in a semi-real world usage (some prototype code)
| [Tuesday 01 February 2011] [05:12:40] <CIA-21>	zeromq2: 03Martin Sustrik 07sub-forward * rca34d2a 10/ (5 files): 
| [Tuesday 01 February 2011] [05:12:40] <CIA-21>	zeromq2: Debug output for subscription forwarding.
| [Tuesday 01 February 2011] [05:12:40] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/fdwCNa
| [Tuesday 01 February 2011] [05:34:29] <ianbarber>	ah, it's because the publisher thinks it has two sockets with the same identity connected at the same time. It would be nice to have that cause a problem on the client side, rather than the server side, but I don't know if that's doable
| [Tuesday 01 February 2011] [05:37:20] <mikko>	i dont think two identities should assert
| [Tuesday 01 February 2011] [05:41:22] <ianbarber>	mikko: i haven't made a testcase in C yet, but in PHP
| [Tuesday 01 February 2011] [05:42:09] <ianbarber>	https://gist.github.com/805688
| [Tuesday 01 February 2011] [05:43:43] <ianbarber>	if anything was going to assert, i'd much rather it be the client
| [Tuesday 01 February 2011] [05:43:58] <ianbarber>	but i think the best behavior would be a failed connect()
| [Tuesday 01 February 2011] [05:44:26] <ianbarber>	not sure how easy it is to compare a new identity against connected identities on connect though, from the pub side
| [Tuesday 01 February 2011] [05:47:09] <ianbarber>	ooh, if this works in c, this is worth a point in the 0mq game :)
| [Tuesday 01 February 2011] [05:53:38] <ianbarber>	same thing in C: https://gist.github.com/805701
| [Tuesday 01 February 2011] [05:57:04] <ianbarber>	yep, and if I split that into client server, it still happens
| [Tuesday 01 February 2011] [06:02:58] <CIA-21>	zeromq2: 03Martin Sustrik 07sub-forward * rcc7bed5 10/ (src/trie.cpp src/trie.hpp src/xsub.cpp): 
| [Tuesday 01 February 2011] [06:02:58] <CIA-21>	zeromq2: Duplicate subscriptions are not forwarded by XSUB socket.
| [Tuesday 01 February 2011] [06:02:58] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/hGPp1V
| [Tuesday 01 February 2011] [06:24:54] <suzan_shakya>	Is it possible to have mulitple publisher with PUB/SUB ?
| [Tuesday 01 February 2011] [06:39:19] <stockMQ>	 Hi..what would be the equivalent of  zmq_close (sender);     zmq_term (context);
| [Tuesday 01 February 2011] [06:39:22] <stockMQ>	in C++
| [Tuesday 01 February 2011] [06:40:26] <mikko>	stockMQ: object going out of scope
| [Tuesday 01 February 2011] [06:40:34] <mikko>	its called during destruction
| [Tuesday 01 February 2011] [06:41:15] <stockMQ>	ok..So in order to say premptively stop the socket for some time can i just pause the thread for the duration
| [Tuesday 01 February 2011] [10:40:21] <stockMQ>	Is there a way we can exit out of the blocking zmq_recv
| [Tuesday 01 February 2011] [10:42:11] <sustrik>	send it a message
| [Tuesday 01 February 2011] [10:44:57] <stockMQ>	The issue is I have a thread with basic while(1){zmq_recv }..Now in the Main UI thread I have a Disconnect button,clicking on which an event message is sent to the socket thread asking it to quit gracefully.But due to the blocking message of the socket thread that message is never read
| [Tuesday 01 February 2011] [10:45:43] <sustrik>	you have to poll on both sockets
| [Tuesday 01 February 2011] [10:45:50] <sustrik>	instead of recv()ing on one of them
| [Tuesday 01 February 2011] [10:46:56] <stockMQ>	Ohk.. you mean i can have one tcp main socket and apart from that inprc sockets for communication between Main UI thread and child UI thread
| [Tuesday 01 February 2011] [10:48:56] <stockMQ>	is that right
| [Tuesday 01 February 2011] [10:50:26] <sustrik>	yes
| [Tuesday 01 February 2011] [10:51:59] <stockMQ>	ok thanx
| [Tuesday 01 February 2011] [11:52:33] Notice	-NickServ- This nickname is registered. Please choose a different nickname, or identify via /msg NickServ identify <password>.
| [Tuesday 01 February 2011] [11:52:33] Notice	-NickServ- You are now identified for travlr.
| [Tuesday 01 February 2011] [12:31:15] Notice	-NickServ- travlr_ is not a registered nickname.
| [Tuesday 01 February 2011] [12:46:36] <andrewvc>	any ideas what broken pipe, nbytes != 1 errors are caused by?
| [Tuesday 01 February 2011] [12:50:32] <sustrik>	what's the assertion?
| [Tuesday 01 February 2011] [13:28:17] <CIA-21>	jzmq: 03robin.palotai 07master * r04c2900 10/ src/Poller.cpp : testing patch for jni crashes - http://bit.ly/hlc8vI
| [Tuesday 01 February 2011] [14:05:18] <andrewvc>	cremes: around?
| [Tuesday 01 February 2011] [14:05:29] <andrewvc>	I was wondering if you noticed issues with pub/sub and ZMQ::NOBLOCK in the past
| [Tuesday 01 February 2011] [14:05:35] <cremes>	andrewvc: yep
| [Tuesday 01 February 2011] [14:06:06] <cremes>	nope, i have not noticed any specific issues with pub/sub
| [Tuesday 01 February 2011] [14:06:06] <andrewvc>	hmmmm
| [Tuesday 01 February 2011] [14:06:10] <andrewvc>	so in my work on em-zeromq, push/pull works well, pub/sub however
| [Tuesday 01 February 2011] [14:06:23] <cremes>	what's it doing?
| [Tuesday 01 February 2011] [14:06:23] <andrewvc>	zmq_recv just doesn't pick anything up
| [Tuesday 01 February 2011] [14:06:23] <cremes>	or not doing?
| [Tuesday 01 February 2011] [14:06:32] <andrewvc>	the FD gets triggered as readable
| [Tuesday 01 February 2011] [14:06:38] <andrewvc>	on the sub
| [Tuesday 01 February 2011] [14:06:38] <cremes>	so pub works but sub is busted?
| [Tuesday 01 February 2011] [14:06:38] <andrewvc>	yeah
| [Tuesday 01 February 2011] [14:06:38] <andrewvc>	i straced it
| [Tuesday 01 February 2011] [14:06:44] <andrewvc>	i see the data getting written and read
| [Tuesday 01 February 2011] [14:06:54] <andrewvc>	and ZMQ_EVENTS says POLLOUT is enabled
| [Tuesday 01 February 2011] [14:06:58] <andrewvc>	errr triggered
| [Tuesday 01 February 2011] [14:07:15] <andrewvc>	but recv doesn't work
| [Tuesday 01 February 2011] [14:07:21] <cremes>	which socket are you talking about here? sub sockets don't care about POLLOUT
| [Tuesday 01 February 2011] [14:07:31] <andrewvc>	errrm, I meant pollin
| [Tuesday 01 February 2011] [14:07:31] <cremes>	they need POLLIN
| [Tuesday 01 February 2011] [14:07:32] <andrewvc>	sorry
| [Tuesday 01 February 2011] [14:07:34] <cremes>	ok
| [Tuesday 01 February 2011] [14:07:41] <andrewvc>	wait, actually
| [Tuesday 01 February 2011] [14:07:44] <cremes>	damn, thought we had the fix right there...
| [Tuesday 01 February 2011] [14:08:04] <andrewvc>	i think they were triggering POLLOUT (according to ZMQ::EVENTS) on a ZMQSUB socket
| [Tuesday 01 February 2011] [14:08:10] <andrewvc>	lemme double check that
| [Tuesday 01 February 2011] [14:12:23] <andrewvc>	hmmm
| [Tuesday 01 February 2011] [14:12:32] <andrewvc>	now I see no events on the socket, which is good and bad
| [Tuesday 01 February 2011] [14:13:28] <andrewvc>	i mean, the same exact code works with pub/sub
| [Tuesday 01 February 2011] [14:13:34] <andrewvc>	errr push/pull
| [Tuesday 01 February 2011] [14:14:04] <andrewvc>	[pid 14619] sendto(22, "\10\0TMsg777", 9, 0, NULL, 0 <unfinished ...>
| [Tuesday 01 February 2011] [14:14:04] <andrewvc>	[pid 14619] <... recvfrom resumed> "\10\0TMsg777", 8192, 0, NULL, NULL) = 9
| [Tuesday 01 February 2011] [14:14:06] <andrewvc>	from the strace
| [Tuesday 01 February 2011] [14:14:12] <andrewvc>	so, internally, the message gets sent/received
| [Tuesday 01 February 2011] [14:14:17] <andrewvc>	by zeromq it looks
| [Tuesday 01 February 2011] [14:15:03] <andrewvc>	cremes: any ideas on that? I can dig into ffi-rzmq tonight I guess
| [Tuesday 01 February 2011] [14:15:43] <cremes>	andrewvc: can you gist your test code for me; i'd like to look at it
| [Tuesday 01 February 2011] [14:17:12] <andrewvc>	sure, i mean, I'm a bit short on time now, about to head into a meeting. I can write a minimal test later
| [Tuesday 01 February 2011] [14:17:12] <andrewvc>	however
| [Tuesday 01 February 2011] [14:17:12] <andrewvc>	if you want you can look at
| [Tuesday 01 February 2011] [14:17:12] <andrewvc>	however
| [Tuesday 01 February 2011] [14:17:12] <andrewvc>	https://github.com/andrewvc/em-zeromq
| [Tuesday 01 February 2011] [14:17:27] <andrewvc>	if you run this spec https://github.com/andrewvc/em-zeromq/blob/master/spec/em-zeromq_spec.rb
| [Tuesday 01 February 2011] [14:17:36] <cremes>	i just wonder if i'll see something that you don't... hopefully it's an easy fix
| [Tuesday 01 February 2011] [14:17:49] <andrewvc>	and s/ZMQ::PUSH/ZMQ::PUB
| [Tuesday 01 February 2011] [14:17:56] <andrewvc>	and s/ZMQ::PULL/ZMQ::PUB
| [Tuesday 01 February 2011] [14:17:58] <andrewvc>	you'll see it
| [Tuesday 01 February 2011] [14:18:09] <cremes>	ok
| [Tuesday 01 February 2011] [14:18:19] <andrewvc>	or I can send something later, I'll be expanding the test suite tonight
| [Tuesday 01 February 2011] [14:52:43] <CIA-21>	zeromq2: 03Martin Sustrik 07sub-forward * ra40436b 10/ (5 files): 
| [Tuesday 01 February 2011] [14:52:44] <CIA-21>	zeromq2: Couple of bug fixes to subscription forwarding mechanism.
| [Tuesday 01 February 2011] [14:52:44] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/eOAJxP
| [Tuesday 01 February 2011] [15:14:31] <mikko>	good evening
| [Tuesday 01 February 2011] [15:19:27] <sustrik>	evening
| [Wednesday 02 February 2011] [03:54:56] <efhache>	Hi everybody, just one question about zmq vs 2.0.7,   it's possible there is a sort of memory leak?  I use a simple "broker"  that received message from a zmq socket and redispatch by an other zmq socket the message to the appropriate receiver
| [Wednesday 02 February 2011] [03:56:14] <efhache>	there is nothing else in this piece of soft that the zmq library...   but memory consumption do not stop to increase...
| [Wednesday 02 February 2011] [03:56:56] <efhache>	I work under a linux with 2.4 kernel
| [Wednesday 02 February 2011] [03:59:38] <sustrik>	efhache: it's an outdated version, so yes, it's possible there's a memory leak there that have been fixed in the meantime
| [Wednesday 02 February 2011] [03:59:43] <sustrik>	check ChangeLog
| [Wednesday 02 February 2011] [04:00:25] <sustrik>	the other possibility is that publisher(s) are simply publishing faster then consumer(s) consume
| [Wednesday 02 February 2011] [04:01:17] <efhache>	sustrik :  I see in changelog that there was a memory leak problem with REQ socket, but I don't use REQ
| [Wednesday 02 February 2011] [04:01:50] <efhache>	sustrik : there is a possibility to "view" the total message in queue ?
| [Wednesday 02 February 2011] [04:02:15] <efhache>	sustrik :  to be sure that the publisher don't publish faster than consumer ?
| [Wednesday 02 February 2011] [04:02:26] <sustrik>	nope
| [Wednesday 02 February 2011] [04:02:33] <sustrik>	you can limit the queue size
| [Wednesday 02 February 2011] [04:02:38] <sustrik>	use ZMQ_HWM option
| [Wednesday 02 February 2011] [04:04:40] <efhache>	ok I will see the man page
| [Wednesday 02 February 2011] [04:04:44] <efhache>	thanks sustrik
| [Wednesday 02 February 2011] [04:08:35] <efhache>	sustrik : have you a example to use ZMQ_HWM with a REP/PUB  socket ?
| [Wednesday 02 February 2011] [04:08:59] <sustrik>	man setsockopt
| [Wednesday 02 February 2011] [04:28:57] <suzan_shakya>	socket(zmq.PUB) can bind to multiple ipc sockets. Is this a feature or a bug ?
| [Wednesday 02 February 2011] [04:30:35] <mikko>	suzan_shakya: feature
| [Wednesday 02 February 2011] [04:31:27] <suzan_shakya>	mikko: can multiple publisher and multiple subscriber can be implemented using this feature ?
| [Wednesday 02 February 2011] [04:32:13] <mikko>	suzan_shakya: what do you mean? a single publisher that publishes using multiple endpoints?
| [Wednesday 02 February 2011] [04:34:27] <suzan_shakya>	mikko: i need to implement multiple publisher and multiple subscriber. Multiple subscriber can simply be implemented. In addition to multi sub, i need multi pub, so that all subscriber gets the message of all the publishers
| [Wednesday 02 February 2011] [04:35:30] <sustrik>	you can either connect each sub to each pub, or more sanely, use a forwarder device in the middle
| [Wednesday 02 February 2011] [04:35:37] <mikko>	suzan_shakya: you can a) have subscriber connect to all publishers b) have a device that connects to ..
| [Wednesday 02 February 2011] [04:35:44] <mikko>	martin answered it already
| [Wednesday 02 February 2011] [04:35:58] <sustrik>	:)
| [Wednesday 02 February 2011] [04:36:05] <suzan_shakya>	mikko: I want to implement that without any device
| [Wednesday 02 February 2011] [04:36:47] <mikko>	suzan_shakya: a device in zeromq is just a lightweight process, not a hardware device
| [Wednesday 02 February 2011] [04:36:58] <suzan_shakya>	mikko: ya i know
| [Wednesday 02 February 2011] [04:37:24] <mikko>	in that case you can just connect all subscribers to all publishers
| [Wednesday 02 February 2011] [04:37:29] <suzan_shakya>	mikko: that device is a separate process, right ?
| [Wednesday 02 February 2011] [04:37:52] <mikko>	it can be
| [Wednesday 02 February 2011] [04:40:46] <suzan_shakya>	mikko: i got it, thanks :)
| [Wednesday 02 February 2011] [04:41:25] <efhache>	In the future, a pdf version or a book version of the 0MQ Guide   will be available  ??
| [Wednesday 02 February 2011] [04:42:36] <sustrik>	efhache: try asking on the mailing list
| [Wednesday 02 February 2011] [04:42:50] <sustrik>	pieter may know a way to convert it into a pdf
| [Wednesday 02 February 2011] [04:45:00] <efhache>	sustrik : ok...  I recome with another question about setsockopt() function...   It's possible to assing more than just one option?  may be with two, three or more line with setsockopt()   ???
| [Wednesday 02 February 2011] [04:45:24] <sustrik>	sure
| [Wednesday 02 February 2011] [04:45:37] <sustrik>	you can set all settable options
| [Wednesday 02 February 2011] [04:45:38] <sustrik>	no problem
| [Wednesday 02 February 2011] [04:46:22] <efhache>	ok thanks
| [Wednesday 02 February 2011] [05:56:20] <CIA-21>	zeromq2: 03Martin Sustrik 07sub-forward * re156f09 10/ src/trie.cpp : 
| [Wednesday 02 February 2011] [05:56:20] <CIA-21>	zeromq2: trie_t::rm returns true only if it actually removes the subscription
| [Wednesday 02 February 2011] [05:56:20] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/fI1gLN