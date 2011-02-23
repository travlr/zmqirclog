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
| [Wednesday 02 February 2011] [08:03:22] <noj>	hello. I'm seeing a crash in ZeroMQ 2.0.10 compiled under Win32 with zmq::poll(). it crashes on  notify_fd = app_thread->get_signaler ()->get_fd ();  the signaler seems corrupt. what am I doing wrong?
| [Wednesday 02 February 2011] [08:05:45] <noj>	nevermind. I supplied the address of the socket in my pollitem_t structure
| [Wednesday 02 February 2011] [11:54:10] <mikko>	howdy
| [Wednesday 02 February 2011] [12:31:50] <stockMQ>	Hi .. anyone any experience with R6010 - abort() has been called on VC++
| [Wednesday 02 February 2011] [12:32:04] <stockMQ>	It is a multi threaded app
| [Wednesday 02 February 2011] [12:32:39] <stockMQ>	There are two threads say A and B receiving from two sockets 
| [Wednesday 02 February 2011] [12:33:13] <stockMQ>	then A and B both has a publisher bound to a TCP end point and a PGM end point
| [Wednesday 02 February 2011] [12:33:46] <stockMQ>	I get this only if the combination is a TCP and PGM
| [Wednesday 02 February 2011] [12:33:52] <stockMQ>	no problem with two TCPs
| [Wednesday 02 February 2011] [12:34:01] <mikko>	sounds like hitting an assertion
| [Wednesday 02 February 2011] [12:34:15] <mikko>	i would assume abort() gets invoked after assertion failure
| [Wednesday 02 February 2011] [12:34:57] <mikko>	never used PGM with windows
| [Wednesday 02 February 2011] [12:35:17] <stockMQ>	yeahh.. seems like something involving openPGM
| [Wednesday 02 February 2011] [12:36:13] <stockMQ>	checking now with combination of PGM and PGM
| [Wednesday 02 February 2011] [12:36:20] <stockMQ>	i mean epgm and epgm
| [Wednesday 02 February 2011] [12:37:02] <stockMQ>	ohk..got the error
| [Wednesday 02 February 2011] [12:37:51] <mikko>	->
| [Wednesday 02 February 2011] [12:41:24] <stockMQ>	I meant i got the same abort
| [Wednesday 02 February 2011] [12:43:39] <stockMQ>	After much testing the pattern i see is that i get this error if there are more than one epgm within the same process but each in a distinct thread
| [Wednesday 02 February 2011] [12:43:55] <stockMQ>	or more than one epgm in the same thread
| [Wednesday 02 February 2011] [12:48:42] <stockMQ>	Will it be better if on receiving data in thread A and B ,i send it through a common PUB instead of one PUB for each thread
| [Wednesday 02 February 2011] [12:49:16] <cremes>	stockMQ: no, don't share the same pub socket between 1+ threads
| [Wednesday 02 February 2011] [12:49:26] <cremes>	the rule is 1 socket per thread
| [Wednesday 02 February 2011] [12:50:25] <stockMQ>	ok
| [Wednesday 02 February 2011] [12:52:45] <stockMQ>	right now the two threads are sharing the same context
| [Wednesday 02 February 2011] [12:55:25] <cremes>	that should be okay; 99% of programs will only ever need a single context
| [Wednesday 02 February 2011] [18:37:38] <mikko>	Steve-o: hi
| [Wednesday 02 February 2011] [18:37:42] <mikko>	got my email?
| [Wednesday 02 February 2011] [18:39:19] <mikko>	i see you did
| [Wednesday 02 February 2011] [18:39:27] <Steve-o>	:P
| [Wednesday 02 February 2011] [18:41:14] <Steve-o>	I think I noticed it was debug build before
| [Wednesday 02 February 2011] [18:41:30] <mikko>	i replied to your email 
| [Wednesday 02 February 2011] [18:41:37] <mikko>	not sure how to check that with .libs
| [Wednesday 02 February 2011] [18:41:46] <mikko>	but dependency walker shows it on dlls
| [Wednesday 02 February 2011] [18:42:35] <Steve-o>	I guess I should look at DLL again sometime
| [Wednesday 02 February 2011] [18:43:11] <Steve-o>	CMake is broken on executables and dlls for some reason
| [Wednesday 02 February 2011] [18:43:55] <Steve-o>	as I wanted to include purinrecv.exe and purinsend.exe in the package
| [Wednesday 02 February 2011] [18:45:32] <Steve-o>	still working on ticket spinlocks which will help Windows a bit
| [Wednesday 02 February 2011] [18:46:06] <Steve-o>	idea being to avoid API calls that include context switches to the kernel
| [Wednesday 02 February 2011] [18:46:30] <Steve-o>	critical sections don't, but regular Windows mutexes do
| [Wednesday 02 February 2011] [18:46:42] <Steve-o>	rw locks are vista+ only
| [Wednesday 02 February 2011] [18:47:25] <mikko>	http://build.valokuva.org/job/ZeroMQ2-core-master_MSVC-win7/148/console
| [Wednesday 02 February 2011] [18:47:28] <mikko>	building now
| [Wednesday 02 February 2011] [18:48:30] <mikko>	there is now the WithOpenPGM target in the MSVC build which you can easily use to create "With OpenPGM release builds". It expects to find OpenPGM in ..\OpenPGM (one dir up from zeromq dir)
| [Wednesday 02 February 2011] [18:49:26] <mikko>	i think i had another question for you as well regarding the openpgm autoconf builds. what was the reason for LT_PREREQ([2.2]) in configure.ac?
| [Wednesday 02 February 2011] [18:50:39] <Steve-o>	just to match the versions on ubuntu 10.10
| [Wednesday 02 February 2011] [18:50:57] <Steve-o>	then I ran os OSX 10.6.5/6 and lowered the numbers for it working there
| [Wednesday 02 February 2011] [18:51:08] <Steve-o>	I had to fix the autoconf 11 parts for silent building
| [Wednesday 02 February 2011] [18:51:48] <Steve-o>	are there platforms it fails on?
| [Wednesday 02 February 2011] [18:51:53] <mikko>	debian stable
| [Wednesday 02 February 2011] [18:51:59] <mikko>	libtool 1.5
| [Wednesday 02 February 2011] [18:52:14] <mikko>	probably rhel as well
| [Wednesday 02 February 2011] [18:52:33] <Steve-o>	ok
| [Wednesday 02 February 2011] [18:52:58] <Steve-o>	if you change the version to 1.5 or remove the line does it build correctly?
| [Wednesday 02 February 2011] [18:53:19] <mikko>	i remved the line and added AC_PROG_LIBTOOL invocation
| [Wednesday 02 February 2011] [18:53:29] <mikko>	not sure if that is mandatory
| [Wednesday 02 February 2011] [18:53:33] <mikko>	but yes, builds properly
| [Wednesday 02 February 2011] [18:53:44] <Steve-o>	I need to update CMakeLists.txt and Makefile.am to remove the hard coded version numbers
| [Wednesday 02 February 2011] [18:53:45] <mikko>	just reading about how to statically link libtool archive 
| [Wednesday 02 February 2011] [18:54:02] <mikko>	http://snapshot.valokuva.org/msvc2008/2011-02-02_23-46-20/
| [Wednesday 02 February 2011] [18:54:06] <Steve-o>	I cannot use a version.sh on stock Windows without Cygwin
| [Wednesday 02 February 2011] [18:54:12] <mikko>	there we go, seems to be fully functional release dll 
| [Wednesday 02 February 2011] [18:54:33] <Steve-o>	nice, good job
| [Wednesday 02 February 2011] [18:54:35] <mikko>	version.bat ?
| [Wednesday 02 February 2011] [18:54:37] <mikko>	:)
| [Wednesday 02 February 2011] [18:54:59] <Steve-o>	well I was thinking of using perl or python
| [Wednesday 02 February 2011] [18:55:06] <mikko>	ill remove the earlier snapshots as they are varying quality and build configurations
| [Wednesday 02 February 2011] [18:55:07] <Steve-o>	after I have detected they exist
| [Wednesday 02 February 2011] [18:57:02] <Steve-o>	the libtool/autoconf/automake documentation changes a lot on its recommendations
| [Wednesday 02 February 2011] [18:57:34] <Steve-o>	I tried to go with the latest spec
| [Wednesday 02 February 2011] [18:57:50] <Steve-o>	I think 0mq is a bit behind
| [Wednesday 02 February 2011] [18:58:35] <mikko>	it's possible because we target for as wide as possible audience
| [Wednesday 02 February 2011] [18:59:17] <mikko>	or at least try to
| [Wednesday 02 February 2011] [18:59:45] <Steve-o>	its perverse because you can go with the latest version in repo as long as you ship all the configure scripts in release
| [Wednesday 02 February 2011] [19:00:20] <mikko>	yeah, i guess it's partially convenience
| [Wednesday 02 February 2011] [19:00:39] <mikko>	being able to build with distro-provided tools without having to first update the autoconf toolchain
| [Wednesday 02 February 2011] [19:00:58] <Steve-o>	the new silent build is nice though, brings it upto building Linux and how CMake runs
| [Wednesday 02 February 2011] [19:01:26] <Steve-o>	s/upto/upto date/
| [Wednesday 02 February 2011] [19:01:44] <mikko>	and i would think that at least the parts of the autoconf stuff i've written follow documentation or tutorials found online
| [Wednesday 02 February 2011] [19:01:50] <mikko>	not always necessarily up to date
| [Wednesday 02 February 2011] [19:01:58] <Steve-o>	that's the biggest problem,
| [Wednesday 02 February 2011] [19:02:11] <Steve-o>	every blog and walkthough refers to an older upstream version
| [Wednesday 02 February 2011] [19:03:10] <mikko>	yeah, i learned to appreciate the autoconf documentation at later stages
| [Wednesday 02 February 2011] [19:03:33] <Steve-o>	doesn't stop autoheader from being broken
| [Wednesday 02 February 2011] [19:03:44] <Steve-o>	gettext doesn't work out of the box
| [Wednesday 02 February 2011] [19:03:58] <Steve-o>	I didn't spend too long looking at it though
| [Wednesday 02 February 2011] [19:06:11] <Steve-o>	similarly detecting files is a bit odd
| [Wednesday 02 February 2011] [19:06:36] <Steve-o>	AC_CHECK_FILE seems to check for being able to read with the users permissions
| [Wednesday 02 February 2011] [19:07:06] <Steve-o>	so /dev/hpet always fails for example
| [Wednesday 02 February 2011] [19:08:20] <Steve-o>	oh and it looks like I didn't check for Sun Pro's hidden attribute
| [Wednesday 02 February 2011] [19:08:44] <mikko>	test -r ? 
| [Wednesday 02 February 2011] [19:08:59] <mikko>	or -x ?
| [Wednesday 02 February 2011] [19:09:20] <Steve-o>	not too important, only /dev/rtc and /dev/hpet which have major problems anyway
| [Wednesday 02 February 2011] [19:11:27] <Steve-o>	overall not too bad, I'm certainly not interested in copying the autoconf to SCons or CMake, they look a lot more verbose
| [Wednesday 02 February 2011] [19:12:42] <Steve-o>	I should get around to checking cygwin/mingw though, I guess autoconf doesn't work with msvc?
| [Wednesday 02 February 2011] [19:13:21] <mikko>	no, you would need MSBuild or visual studio templates
| [Wednesday 02 February 2011] [19:13:38] <mikko>	autoconf works on cygwin / mingw
| [Wednesday 02 February 2011] [19:13:54] <Steve-o>	that's why I have CMake :D
| [Wednesday 02 February 2011] [19:16:06] <Steve-o>	a bit limiting that you need a ssl certificate to get your name in the publisher field of Windows installers
| [Wednesday 02 February 2011] [19:16:59] <mikko>	i guess they have a reason for that
| [Wednesday 02 February 2011] [19:17:38] <Steve-o>	still need to look at getting an installer for 0mq though
| [Wednesday 02 February 2011] [19:18:21] <mikko>	is it much more than copying the dll in place?
| [Wednesday 02 February 2011] [19:19:22] <Steve-o>	I call NSIS through CPack as part of CMake
| [Wednesday 02 February 2011] [19:19:57] <Steve-o>	you setup the target directory structure and simply fill in a few fields unless you need something special
| [Wednesday 02 February 2011] [19:21:47] <mikko>	hmm
| [Wednesday 02 February 2011] [19:21:50] <Steve-o>	the main job of the installer is to prepare the uninstaller
| [Wednesday 02 February 2011] [19:22:07] <mikko>	for zeromq it might be possible to add an installer project into the solution
| [Wednesday 02 February 2011] [19:22:15] <mikko>	msvc
| [Wednesday 02 February 2011] [19:22:22] <Steve-o>	I'm guessing thats how it was done before
| [Wednesday 02 February 2011] [19:24:24] <Steve-o>	possibly pertinent to bundle the msvc 2010 redistributable too
| [Wednesday 02 February 2011] [19:24:59] <Steve-o>	Microsoft released an opensource installer thing a while back no, WiX?
| [Wednesday 02 February 2011] [19:25:44] <Steve-o>	http://wix.sourceforge.net/
| [Wednesday 02 February 2011] [19:26:27] <mikko>	cool
| [Wednesday 02 February 2011] [19:29:08] <Steve-o>	I don't have any templates in visual studio for an installer, maybe I missed something
| [Wednesday 02 February 2011] [19:32:08] <mikko>	are you using express edition?
| [Wednesday 02 February 2011] [19:32:36] <Steve-o>	yup
| [Wednesday 02 February 2011] [19:33:21] <mikko>	i dont think express includes the installer technology
| [Wednesday 02 February 2011] [19:33:31] <mikko>	so wix might be a better solution
| [Wednesday 02 February 2011] [19:45:11] <mikko>	openpgm autoconf was actually pretty easy to fit into zeromq build
| [Wednesday 02 February 2011] [19:45:36] <mikko>	also it's using libtool to link so it should continue working if libpgm provides shared libraries later on
| [Wednesday 02 February 2011] [19:47:34] <mikko>	hmm
| [Wednesday 02 February 2011] [19:47:48] <mikko>	hitting an assertion with epgm transport
| [Wednesday 02 February 2011] [19:47:54] <mikko>	i was getting this before as well
| [Wednesday 02 February 2011] [19:49:02] <mikko>	Assertion failed: rc == 0 (connect_session.cpp:82)
| [Wednesday 02 February 2011] [19:50:09] <Steve-o>	common on connect()
| [Wednesday 02 February 2011] [19:50:26] <Steve-o>	usually means resolving the network parameter failed
| [Wednesday 02 February 2011] [19:51:14] <Steve-o>	fyi: libpm in autoconf is already set to make static & shared libraries
| [Wednesday 02 February 2011] [19:52:03] <Steve-o>	ideally the pgm error object should be routed through the zeromq logging service
| [Wednesday 02 February 2011] [19:53:19] <Steve-o>	the zeromq error detail is incredibly brief
| [Wednesday 02 February 2011] [19:54:18] <Steve-o>	I'm currently pondering over chasing the libc defect with /etc/hosts resolution on multiple entries
| [Wednesday 02 February 2011] [19:54:34] <Steve-o>	I can't help think it's just NetworkManager being shit
| [Wednesday 02 February 2011] [19:54:40] <mikko>	what is the issue?
| [Wednesday 02 February 2011] [19:54:47] <mikko>	order of resolution?
| [Wednesday 02 February 2011] [19:54:55] <Steve-o>	two issues
| [Wednesday 02 February 2011] [19:55:06] <Steve-o>	one it seems to pickup ::1 as 127.0.0.1
| [Wednesday 02 February 2011] [19:55:19] <mikko>	my connection string is epgm://eth0;239.192.0.1:6868
| [Wednesday 02 February 2011] [19:55:20] <Steve-o>	and secondly it seems to read bottom to top
| [Wednesday 02 February 2011] [19:55:49] <Steve-o>	I'd try using the IP address but that looks fine
| [Wednesday 02 February 2011] [19:56:08] <mikko>	still asserts with ip
| [Wednesday 02 February 2011] [19:56:34] <mikko>	hmm
| [Wednesday 02 February 2011] [19:56:40] <Steve-o>	anything if you run with PGM_MIN_LOG_LEVEL=TRACE ?
| [Wednesday 02 February 2011] [19:57:16] <mikko>	https://gist.github.com/3f99af511f9059ce4a7c
| [Wednesday 02 February 2011] [19:57:23] <mikko>	it outputs that
| [Wednesday 02 February 2011] [19:59:58] <Steve-o>	odd, I'm guessing setsockopt on IP_PKTINFO is failing
| [Wednesday 02 February 2011] [20:01:48] <Steve-o>	this is with my autoconf?
| [Wednesday 02 February 2011] [20:02:11] <Steve-o>	or the stuff in master? 
| [Wednesday 02 February 2011] [20:02:30] <mikko>	it seems to happen with stuff on master and autoconf
| [Wednesday 02 February 2011] [20:03:25] <Steve-o>	but not with openpgm tools?
| [Wednesday 02 February 2011] [20:04:15] <mikko>	havent tested
| [Wednesday 02 February 2011] [20:04:16] <Steve-o>	have to prod Sustrik when he is online about PGM logging
| [Wednesday 02 February 2011] [20:04:52] <mikko>	trying to find the tools among the openpgm source
| [Wednesday 02 February 2011] [20:05:40] <mikko>	hmmm.. the autoconf doenst seem to build them
| [Wednesday 02 February 2011] [20:05:51] <Steve-o>	nope :P
| [Wednesday 02 February 2011] [20:06:02] <mikko>	sconssing now
| [Wednesday 02 February 2011] [20:06:57] <Steve-o>	autoconf & cmake only build libraries, easiest method for distribution
| [Wednesday 02 February 2011] [20:07:53] <mikko>	what is good test program?
| [Wednesday 02 February 2011] [20:08:08] <Steve-o>	purinrecv or purinsend are the easiest to use
| [Wednesday 02 February 2011] [20:08:40] <mikko>	hmm
| [Wednesday 02 February 2011] [20:08:43] <mikko>	nothing happens
| [Wednesday 02 February 2011] [20:08:46] <mikko>	but no errors
| [Wednesday 02 February 2011] [20:09:20] <Steve-o>	you can always build them with something like gcc -o purinrecv examples/purinrecv.c `PKG_CONFIG_PATH=. pkg-config --cflags --libs`
| [Wednesday 02 February 2011] [20:09:44] <mikko>	i got purinrecv running
| [Wednesday 02 February 2011] [20:09:50] <mikko>	and executing purinsend
| [Wednesday 02 February 2011] [20:09:59] <mikko>	should i see something in the receiver?
| [Wednesday 02 February 2011] [20:10:10] <Steve-o>	usually if you don't see anything it means it's picking up the loopback device
| [Wednesday 02 February 2011] [20:10:49] <mikko>	Trace: Multicast send interface set to 127.0.1.1 index 0
| [Wednesday 02 February 2011] [20:10:51] <mikko>	correct
| [Wednesday 02 February 2011] [20:11:14] <Steve-o>	that's the /etc/hosts problem correct
| [Wednesday 02 February 2011] [20:11:31] <Steve-o>	127.0.1.1 is the default ip for dhcp linux boxes
| [Wednesday 02 February 2011] [20:11:45] <Steve-o>	you should have a second entry with the dhcp address
| [Wednesday 02 February 2011] [20:12:12] <Steve-o>	but getaddrinfo('hostname') is returning a different order to what NetworkManager thinks it should
| [Wednesday 02 February 2011] [20:12:27] <Steve-o>	so annoying
| [Wednesday 02 February 2011] [20:12:38] <mikko>	ok, changed to the eth0 ip but still not seeing anything
| [Wednesday 02 February 2011] [20:12:39] <mikko>	odd
| [Wednesday 02 February 2011] [20:12:49] <mikko>	Trace: Multicast send interface set to 192.168.192.139 index 0
| [Wednesday 02 February 2011] [20:13:30] <Steve-o>	oh, add '-l' for loopback
| [Wednesday 02 February 2011] [20:13:54] <Steve-o>	it's disabled by default
| [Wednesday 02 February 2011] [20:14:00] <Steve-o>	doh
| [Wednesday 02 February 2011] [20:14:02] <mikko>	ok now seeing something: Trace: Recv again on not-full
| [Wednesday 02 February 2011] [20:14:20] <mikko>	in any case, it gets further than with zeromq
| [Wednesday 02 February 2011] [20:14:32] <Steve-o>	yup
| [Wednesday 02 February 2011] [20:15:55] <mikko>	comparing the results, inside zeromq i dont see this: Trace: Assuming IP header size of 20 bytes
| [Wednesday 02 February 2011] [20:16:05] <mikko>	Trace: Request IP headers. is the last line
| [Wednesday 02 February 2011] [20:16:10] <Steve-o>	i can try debian in a vm
| [Wednesday 02 February 2011] [20:18:50] <mikko>	https://gist.github.com/dc1855834b6445ef224f
| [Wednesday 02 February 2011] [20:18:57] <mikko>	that should be enough to reproduce
| [Wednesday 02 February 2011] [20:22:50] <Steve-o>	ok, I'll be a bit, I need to reboot into Ubuntu and download & install everything ...
| [Wednesday 02 February 2011] [20:22:58] <mikko>	hehe
| [Wednesday 02 February 2011] [20:23:03] <mikko>	i think im gonna hit the sack
| [Wednesday 02 February 2011] [20:23:07] <mikko>	getting a bit late here
| [Wednesday 02 February 2011] [20:23:12] <mikko>	good night
| [Wednesday 02 February 2011] [20:23:14] <Steve-o>	I'll shoot you a mail
| [Wednesday 02 February 2011] [20:23:18] <Steve-o>	night
| [Wednesday 02 February 2011] [20:23:19] <mikko>	thanks
| [Thursday 03 February 2011] [02:48:17] <CIA-21>	zeromq2: 03Martin Sustrik 07master * rca1acc3 10/ (src/poll.cpp src/poll.hpp): 
| [Thursday 03 February 2011] [02:48:17] <CIA-21>	zeromq2: RLIMIT_NOFILE not used in poll_t anymore
| [Thursday 03 February 2011] [02:48:17] <CIA-21>	zeromq2: The problem was that RLIMIT_NOFILE can be set to RLIM_INIFINITY
| [Thursday 03 February 2011] [02:48:17] <CIA-21>	zeromq2: (and that appears to be default on AIX) which caused 0MQ to fail.
| [Thursday 03 February 2011] [02:48:17] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/hHEbFN
| [Thursday 03 February 2011] [02:59:50] <mikko>	good morning
| [Thursday 03 February 2011] [03:06:17] <sustrik>	morning
| [Thursday 03 February 2011] [03:11:02] <sustrik>	mikko: i've realised you are running solaris builds
| [Thursday 03 February 2011] [03:11:17] <sustrik>	is there a chance to test a patch on solaris?
| [Thursday 03 February 2011] [03:11:55] <mikko>	sustrik: sure
| [Thursday 03 February 2011] [03:12:05] <sustrik>	great
| [Thursday 03 February 2011] [03:12:09] <mikko>	i can do it over lunch if its more involved
| [Thursday 03 February 2011] [03:12:13] <mikko>	have you got it in github?
| [Thursday 03 February 2011] [03:12:22] <sustrik>	nope
| [Thursday 03 February 2011] [03:12:32] <sustrik>	the problem is i have no access to solaris box
| [Thursday 03 February 2011] [03:12:46] <sustrik>	and i don't want to commit something i haven't even been able to compile
| [Thursday 03 February 2011] [03:13:08] <sustrik>	let me create the patch
| [Thursday 03 February 2011] [03:13:17] <sustrik>	we can check whether it builds on solaris
| [Thursday 03 February 2011] [03:13:22] <sustrik>	and if so, i'll commit it
| [Thursday 03 February 2011] [03:13:23] <mikko>	i noticed that default ZMQ_RATE seems to be too small for debian
| [Thursday 03 February 2011] [03:13:25] <mikko>	Assertion failed: rc == 0 (connect_session.cpp:82)
| [Thursday 03 February 2011] [03:13:51] <mikko>	i can add a separate build on hudson which builds from a specific github branch so you can build when you want 
| [Thursday 03 February 2011] [03:13:55] <mikko>	would that be useufl?
| [Thursday 03 February 2011] [03:14:14] <sustrik>	dunno
| [Thursday 03 February 2011] [03:14:23] <sustrik>	in most cases i can build at home
| [Thursday 03 February 2011] [03:14:36] <sustrik>	this time the problem is that the code is solaris-specific
| [Thursday 03 February 2011] [03:14:43] <mikko>	ok, i can give it a spin
| [Thursday 03 February 2011] [03:14:57] <sustrik>	ok, i'll send you the patch
| [Thursday 03 February 2011] [03:15:01] <sustrik>	no haste though
| [Thursday 03 February 2011] [03:17:05] <mikko>	steven suggested adding 1024 to both rxw_sqns and txw_sqns in pgm_socket.cpp
| [Thursday 03 February 2011] [03:17:10] <mikko>	but that still seems to be too low 
| [Thursday 03 February 2011] [03:17:23] <mikko>	sustrik: have you got ubuntu / debian at hand?
| [Thursday 03 February 2011] [03:18:05] <mikko>	https://gist.github.com/b99d73ce2e8759e126fa
| [Thursday 03 February 2011] [03:18:10] <mikko>	this code should hit assertion
| [Thursday 03 February 2011] [03:18:16] <mikko>	it does on debian 5.0
| [Thursday 03 February 2011] [03:18:25] <sustrik>	yup, i'm on ubuntu right now
| [Thursday 03 February 2011] [03:19:11] <mikko>	increasing ZMQ_RATE to 100000 solves it for me
| [Thursday 03 February 2011] [03:20:31] <sustrik>	let me check the problem
| [Thursday 03 February 2011] [03:36:05] <sustrik>	hm
| [Thursday 03 February 2011] [03:36:20] <sustrik>	for me it fails here:
| [Thursday 03 February 2011] [03:36:22] <sustrik>	153	        if (!pgm_setsockopt (sock, IPPROTO_PGM, PGM_UDP_ENCAP_UCAST_PORT,
| [Thursday 03 February 2011] [03:36:22] <sustrik>	154	                &encapsulation_port, sizeof (encapsulation_port)) ||
| [Thursday 03 February 2011] [03:36:22] <sustrik>	155	            !pgm_setsockopt (sock, IPPROTO_PGM, PGM_UDP_ENCAP_MCAST_PORT,
| [Thursday 03 February 2011] [03:36:22] <sustrik>	156	                &encapsulation_port, sizeof (encapsulation_port)))
| [Thursday 03 February 2011] [03:36:40] <sustrik>	which has nothing to do with the rate
| [Thursday 03 February 2011] [03:37:18] <mikko>	do you run as root?
| [Thursday 03 February 2011] [03:37:28] <sustrik>	i've changed the protocol to epgm
| [Thursday 03 February 2011] [03:37:40] <sustrik>	no need to be root in such case
| [Thursday 03 February 2011] [03:43:51] <sustrik>	mikko: patch sent
| [Thursday 03 February 2011] [03:44:05] <sustrik>	when you have few mins free, try it with solaris
| [Thursday 03 February 2011] [03:44:06] <sustrik>	thanks
| [Thursday 03 February 2011] [03:59:59] <mikko>	sustrik: All 8 tests passed
| [Thursday 03 February 2011] [04:00:05] <sustrik>	great
| [Thursday 03 February 2011] [04:00:05] <mikko>	solaris studio on solaris 
| [Thursday 03 February 2011] [04:00:18] <sustrik>	i'll apply the patch
| [Thursday 03 February 2011] [04:02:10] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r3f758ab 10/ (src/devpoll.cpp src/devpoll.hpp): 
| [Thursday 03 February 2011] [04:02:10] <CIA-21>	zeromq2: Don't use RLIMIT_NOFILES in devpoll_t.
| [Thursday 03 February 2011] [04:02:10] <CIA-21>	zeromq2: The patch allows for running 0MQ on Solaris and HP-UX
| [Thursday 03 February 2011] [04:02:10] <CIA-21>	zeromq2: even though ulimit for max number of file descriptors
| [Thursday 03 February 2011] [04:02:10] <CIA-21>	zeromq2: is set to unlimited.
| [Thursday 03 February 2011] [04:02:10] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/hLExdy
| [Thursday 03 February 2011] [05:23:15] <mikko>	hmm
| [Thursday 03 February 2011] [05:23:33] <mikko>	on platforms that dont support pic objects is it possible to link static library inside a shared library?
| [Thursday 03 February 2011] [05:37:12] <sustrik>	no idea, sorry
| [Thursday 03 February 2011] [05:43:19] <[equilibrium]>	ago: l'ideale  che tu nasconda (per tutti i chan aperti) la fuffa, tipo i parts, quit, nick changes e roba del genere, perch rallentano di brutto il sync
| [Thursday 03 February 2011] [05:43:34] <[equilibrium]>	sorry, wrong window, nevermind
| [Thursday 03 February 2011] [05:48:13] <mikko>	[equilibrium]: gelato con leche, dos bolas. uno fresa y uno cafe 
| [Thursday 03 February 2011] [05:48:27] <mikko>	thats what i learned last night
| [Thursday 03 February 2011] [05:48:44] <mikko>	hamburguesa con queso y patatas fritas
| [Thursday 03 February 2011] [05:50:51] <sustrik>	ha, the original post was in italian :)
| [Thursday 03 February 2011] [05:51:18] <sustrik>	how's barcelona btw?
| [Thursday 03 February 2011] [05:53:39] <sustrik>	or are you in san diego? /me is not quite sure
| [Thursday 03 February 2011] [07:08:09] <kabs>	Hello, in pub-sub model , if sub starts later and pub started earlier all messages by pub will be dropped. Is there a way to buffer those messages ( with some buffer limit)  so that they can sent to subscriber joining later. Can I get some link to go through it or if it is there in zeroMQ guide can someone point out which section it is ??
| [Thursday 03 February 2011] [07:14:05] <sustrik>	how could the PUB socket possibly know that there will be subscriber in the future?
| [Thursday 03 February 2011] [07:32:40] <mikko>	sustrik: barcelona at the moment
| [Thursday 03 February 2011] [07:32:52] <mikko>	going to san diego end of may
| [Thursday 03 February 2011] [09:33:07] Notice	-NickServ- travlr__ is not a registered nickname.
| [Thursday 03 February 2011] [10:02:45] <udoprog>	Hey, I'm currently developing a game which will require REQ-REP but also sporadic pushing of information to the client, I've got a picture of how to implement this in twisted, but with additional coding overhead (for framing), I would really like to give zeromq a shot.
| [Thursday 03 February 2011] [10:08:57] <mikko>	sure
| [Thursday 03 February 2011] [10:09:04] <mikko>	you can even use zeromq with twisted
| [Thursday 03 February 2011] [10:17:38] <udoprog>	okey, care to elaborate? do you know of any references I can use?
| [Thursday 03 February 2011] [10:42:38] <sustrik>	udoprog: no idea myself, try asking on the mailing list
| [Thursday 03 February 2011] [11:26:20] <sustrik>	mikko: what do you think about the system z proposal?
| [Thursday 03 February 2011] [13:11:47] <cyball>	hi ... does somebody have some samples of implementing ZMQ_XREP service with ZMQ_REQ clients i could not found any ?
| [Thursday 03 February 2011] [13:45:54] <starkdg>	cyball, what doyou mean ?  I think XREP and REQ work fine together.
| [Thursday 03 February 2011] [13:46:13] <starkdg>	i mean, ive done it just fine. 
| [Thursday 03 February 2011] [13:49:37] <cyball>	starkdg: i never said that it does not work i'm new to ZeroMQ and i'm a little bit confused because of the description :
| [Thursday 03 February 2011] [13:49:38] <cyball>	When a ZMQ_REQ socket is connected to a ZMQ_XREP socket, in addition to the identity of the originating peer each message received shall contain an empty delimiter message part. Hence, the entire structure of each received message as seen by the application becomes: one or more identity parts, delimiter part, one or more body parts. When sending replies to a ZMQ_REQ socket the application must include the delimiter part.
| [Thursday 03 February 2011] [13:50:09] <cyball>	what exactly does delimiter part or identity part means ?
| [Thursday 03 February 2011] [13:50:34] <starkdg>	i think that's just the protocol of the message buffer 
| [Thursday 03 February 2011] [13:50:39] <cyball>	how should that look like ?
| [Thursday 03 February 2011] [13:50:42] <starkdg>	it should work seemlessly for the user
| [Thursday 03 February 2011] [13:51:08] <cyball>	ok so i have only to define the constant ZMQ_XREQ in the zqm_socket function ?
| [Thursday 03 February 2011] [13:51:08] <starkdg>	i dont know how it actually looks,  maybe you can ask martin or pieter  
| [Thursday 03 February 2011] [13:51:30] <starkdg>	yeah,  when creating the socket,  just use ZMQ_REQ in the client app 
| [Thursday 03 February 2011] [13:51:35] <cyball>	ok i should mention that i'm using the c language
| [Thursday 03 February 2011] [13:51:41] <starkdg>	and ZMQ_XREP in the server part
| [Thursday 03 February 2011] [13:51:47] <cyball>	ok and that is enough ?
| [Thursday 03 February 2011] [13:51:50] <starkdg>	yeah, i use c 
| [Thursday 03 February 2011] [13:51:58] <starkdg>	yes, that's enough 
| [Thursday 03 February 2011] [13:52:07] <cyball>	starkdg: that's great
| [Thursday 03 February 2011] [13:52:15] <starkdg>	yeah, it works pretty well 
| [Thursday 03 February 2011] [13:53:39] <cyball>	ok i will give it a try :) thx a lot you saved my brain from burning :)
| [Thursday 03 February 2011] [13:55:25] <cyball>	one more question ... if i understood this stuff well ... the ZMQ_REQ waits until the response from the ZMQ_XREP returnes before sending a new request ? is that right ?
| [Thursday 03 February 2011] [14:12:08] <cyball>	starkdg: do you have an hello world sample for that ?
| [Thursday 03 February 2011] [14:12:21] <starkdg>	no i dont
| [Thursday 03 February 2011] [14:12:32] <starkdg>	let me see if i can find it 
| [Thursday 03 February 2011] [14:14:16] <starkdg>	wow, they've been busy , its all different now ! 
| [Thursday 03 February 2011] [14:14:55] <starkdg>	I can give you a link to my project which uses zeromq ,   that might takes some sorting through though 
| [Thursday 03 February 2011] [14:16:07] <cyball>	starkdg: that would be great ... i try to find out how to use it :)
| [Thursday 03 February 2011] [14:16:17] <starkdg>	cyball:  you can pick through the source here: http://code.google.com/p/audioscout/
| [Thursday 03 February 2011] [14:16:36] <starkdg>	that's my project i'm working on ,  the source you can browse through, or download the project
| [Thursday 03 February 2011] [14:18:03] <cyball>	ok thx a lot i've found already the client code with ZMQ_REQ :-)
| [Thursday 03 February 2011] [14:18:35] <starkdg>	yeah, the code with XREP you will see in auscout.c 
| [Thursday 03 February 2011] [14:18:53] <guido_g>	for examples and explanations always see http://zguide.zeromq.org/chapter:all
| [Thursday 03 February 2011] [14:19:37] <guido_g>	advanced routing stuff is in chapter three
| [Thursday 03 February 2011] [14:20:00] <starkdg>	guido_g: he was looking for an example of using REQ socket connecting to XREP ,  i couldnt find that specific example. 
| [Thursday 03 February 2011] [14:20:04] <guido_g>	it also explains the parts of req/rep messages and shows some tricks
| [Thursday 03 February 2011] [14:20:31] <starkdg>	ive noticed things have been busy on the site,  alot more additions. 
| [Thursday 03 February 2011] [14:24:37] <cyball>	guido_g: thx a lot i've found now the samples for ZMQ_REQ and ZMQ_XREP
| [Thursday 03 February 2011] [14:25:04] <cyball>	i think it should be enoug information for now -.... :-) thx for helping
| [Thursday 03 February 2011] [14:25:29] <cyball>	by the way ... ZeroMQ is really a great think :)
| [Thursday 03 February 2011] [14:31:22] <Slurpy>	hello
| [Thursday 03 February 2011] [14:38:02] <Slurpy>	I have a bit of a high-level question regarding the use of 0mq.  Ultimately I think I understand the examples in the documentation.  I have a business need where I can have logical queues that are serviced by more than 1 process (or server).  I'm wondering if there is a pattern that makes sense with 0mq.  I know a client can connect to multiple sockets, so I can have more than one server serving a logical connection.  Seems a bit mess
| [Thursday 03 February 2011] [14:45:35] <sustrik>	Slurpy: what you want afaiu is having a device in the middle
| [Thursday 03 February 2011] [14:47:10] <guido_g>	and, of course, reading the guide :)
| [Thursday 03 February 2011] [15:12:54] <cremes>	cyball: http://www.zeromq.org/tutorials:xreq-and-xrep
| [Thursday 03 February 2011] [15:13:10] <cremes>	for some reason that doc doesn't show up on any of the community pages
| [Thursday 03 February 2011] [15:13:15] <cremes>	you can only find it by searching for it
| [Thursday 03 February 2011] [15:21:36] <cyball>	cremes: thx
| [Thursday 03 February 2011] [15:22:07] <sustrik>	looks like there are some inaccessible pages on the website
| [Thursday 03 February 2011] [15:22:18] <sustrik>	presumably, some reorg is needed
| [Thursday 03 February 2011] [15:22:41] <cremes>	yep, all of the tutorials are orphaned
| [Thursday 03 February 2011] [15:24:07] <sustrik>	should we introduce a "tutorial" section?
| [Thursday 03 February 2011] [15:24:20] <sustrik>	or does it fit somewhere else?
| [Thursday 03 February 2011] [15:24:30] <sustrik>	whitepapers maybe?
| [Thursday 03 February 2011] [15:24:38] <sustrik>	rename whitepaper->articles
| [Thursday 03 February 2011] [15:24:43] <sustrik>	and place tutorials there?
| [Thursday 03 February 2011] [15:27:09] <cremes>	i think we should add back a tutorials page
| [Thursday 03 February 2011] [15:27:15] <guido_g>	imho articles section would be a good idea
| [Thursday 03 February 2011] [15:30:49] <cyball>	i have found this really nice multithreaded hello world server is it possible to get some subscriber do the work of the threads ?
| [Thursday 03 February 2011] [15:30:53] <guido_g>	anyhow, a cleanup would be nice, some links lead to non-existing pages
| [Thursday 03 February 2011] [15:31:26] <guido_g>	like http://www.zeromq.org/tutorials:traffic-monitoring 
| [Thursday 03 February 2011] [15:36:52] <sustrik>	where's the link?
| [Thursday 03 February 2011] [15:38:38] <guido_g>	http://www.zeromq.org/area:whitepapers  <- Traffic monitoring
| [Thursday 03 February 2011] [15:40:51] <cyball>	there is also no working link to the zqm_device function
| [Thursday 03 February 2011] [15:41:53] <cyball>	http://api.zeromq.org/zmq_device.html
| [Thursday 03 February 2011] [15:42:14] <sustrik>	guido_g: ok, removed
| [Thursday 03 February 2011] [15:42:25] <sustrik>	cyball: where's the link?
| [Thursday 03 February 2011] [15:43:02] <guido_g>	sustrik: great, thanks!
| [Thursday 03 February 2011] [15:43:22] <cyball>	http://zguide.zeromq.org/chapter:all #Built in Devices under Figure 20
| [Thursday 03 February 2011] [15:45:36] <sustrik>	actually, it turns out there's in no zmq_device man page
| [Thursday 03 February 2011] [15:45:48] <sustrik>	i wonder how that link have got into the guide
| [Thursday 03 February 2011] [15:47:08] <cyball>	sustrik: that is act of nature behind control :)
| [Thursday 03 February 2011] [15:47:20] <sustrik>	:)
| [Thursday 03 February 2011] [15:49:47] <cyball>	is it possible to replace the workers in the multithreaded hello world sample with subscribers ? that was the reason checking out zmq_device there seems to be a FORWARDER flag ... could that be a solution ? :)
| [Thursday 03 February 2011] [15:50:28] <sustrik>	you need a PUB/SUB device, right?
| [Thursday 03 February 2011] [15:50:39] <sustrik>	if so, yes, use forwarder device
| [Thursday 03 February 2011] [15:52:18] <cyball>	sustrik: but which parameter does it need .... for the clients workes it is fine rmq_device(FORWARDER, clients, ????) but i do not have subscribers or somethink similar ... 
| [Thursday 03 February 2011] [15:52:57] <sustrik>	?
| [Thursday 03 February 2011] [15:53:26] <cyball>	ohhh sorry i got it now
| [Thursday 03 February 2011] [15:53:42] <cyball>	it was a little bit misunderstood because of the words clients and workers
| [Thursday 03 February 2011] [15:53:47] <guido_g>	btw, it's all in the guide
| [Thursday 03 February 2011] [15:54:02] <cyball>	yes sorry i realized to late that this are sockets
| [Thursday 03 February 2011] [15:54:15] <cyball>	i guess i need a break
| [Thursday 03 February 2011] [15:54:16] <cyball>	:)
| [Thursday 03 February 2011] [15:58:05] <_jud>	hey sustrik: what is the current status of xpub/xsub w/ pub side filtering?
| [Thursday 03 February 2011] [16:05:56] <sustrik>	_jud: the ongoing work is on sub-forward branch
| [Thursday 03 February 2011] [16:06:33] <sustrik>	it propagates the subscriptions upstream
| [Thursday 03 February 2011] [16:06:48] <sustrik>	what's missing is actual filtering on pub side
| [Thursday 03 February 2011] [16:07:18] <_jud>	I have been trying to keep up on the mailing list
| [Thursday 03 February 2011] [16:08:54] <jhawk28>	silly question: what will it be called when the xpub gets extended?
| [Thursday 03 February 2011] [16:09:01] <jhawk28>	:)
| [Thursday 03 February 2011] [16:09:03] <_jud>	I've been wanting to use 0mq in a ticker plant
| [Thursday 03 February 2011] [16:10:46] <sustrik>	_jud: yeah, subscription forwarding is what's missing for 0mq to be a sane option for market data distribution
| [Thursday 03 February 2011] [16:11:01] <sustrik>	jhawk28: yes, the names are lame
| [Thursday 03 February 2011] [16:11:22] <sustrik>	it's actually two layers of the stack
| [Thursday 03 February 2011] [16:11:29] <sustrik>	X sockets are like IP
| [Thursday 03 February 2011] [16:11:35] <sustrik>	non-X sockets are like TCP
| [Thursday 03 February 2011] [16:11:49] <sustrik>	no idea how to formalise that decently
| [Thursday 03 February 2011] [16:12:59] <_jud>	sustrik: when you say sub forwarding - I assume that encompasses pub filtering also? 
| [Thursday 03 February 2011] [16:13:09] <sustrik>	yes
| [Thursday 03 February 2011] [16:13:34] <sustrik>	the whole thing consist from two parts
| [Thursday 03 February 2011] [16:13:43] <sustrik>	1. pass the subsription upstream
| [Thursday 03 February 2011] [16:13:52] <sustrik>	2. do the filtering on the most upstream node
| [Thursday 03 February 2011] [16:14:52] <_jud>	in regular pub/sub, all nodes just rebroadcast, correct?
| [Thursday 03 February 2011] [16:15:10] <sustrik>	right
| [Thursday 03 February 2011] [16:15:31] <sustrik>	that's the way it work now
| [Thursday 03 February 2011] [16:15:35] <_jud>	just trying to clear up my surface knowledge of the 0mq layout
| [Thursday 03 February 2011] [16:16:00] <_jud>	I will be monitoring the sub-forward branch
| [Thursday 03 February 2011] [16:16:03] <sustrik>	ah, you are asking about distinction beween X and non-X sockets, right?
| [Thursday 03 February 2011] [16:16:34] <_jud>	well, yes
| [Thursday 03 February 2011] [16:17:03] <sustrik>	X sockets are to be used by intermediate nodes
| [Thursday 03 February 2011] [16:17:19] <sustrik>	you can recv() a subsctiption on XPUB socket
| [Thursday 03 February 2011] [16:17:33] <sustrik>	and send() a subscription to XSUB socket
| [Thursday 03 February 2011] [16:17:44] <sustrik>	PUB and SUB are for endpoints
| [Thursday 03 February 2011] [16:18:08] <sustrik>	the subsctiption are mananged automatically for you
| [Thursday 03 February 2011] [16:18:21] <sustrik>	no need to explicitly send/recv them
| [Thursday 03 February 2011] [16:19:20] <_jud>	so when pub filtering is implimented
| [Thursday 03 February 2011] [16:19:39] <_jud>	it won't require the use of X sockets unless their are intermediaries?
| [Thursday 03 February 2011] [16:20:51] <sustrik>	yes
| [Thursday 03 February 2011] [16:20:59] <sustrik>	it will be opaque for you
| [Thursday 03 February 2011] [16:21:04] <_jud>	ahhh
| [Thursday 03 February 2011] [16:21:15] <sustrik>	X sockets are meant only for implemeting devices
| [Thursday 03 February 2011] [16:21:42] <sustrik>	it's similar to IP
| [Thursday 03 February 2011] [16:21:51] <sustrik>	normally, you don't use IP directly
| [Thursday 03 February 2011] [16:21:57] <_jud>	ah, thanks for clearing that up
| [Thursday 03 February 2011] [16:22:04] <sustrik>	unless you want to implement a router or somesuch
| [Thursday 03 February 2011] [16:22:37] <_jud>	thanks for that sustrik
| [Thursday 03 February 2011] [19:10:30] <cyball>	hi ... is there a way to read a message and after that to send it to a message queue ? 
| [Thursday 03 February 2011] [19:11:03] <cyball>	or to switch between message types ?
| [Thursday 03 February 2011] [19:58:04] <mikko>	cyball: what do you mean?
| [Thursday 03 February 2011] [20:00:23] <hero>	hi
| [Thursday 03 February 2011] [20:00:28] <mikko>	hello
| [Thursday 03 February 2011] [20:01:16] <nathanmarz>	i'm getting some strange errors from zeromq
| [Thursday 03 February 2011] [20:01:33] <stodge>	Is there a performance hit using the Java bindings for zeromq? I assume it uses jini?
| [Thursday 03 February 2011] [20:02:04] <mikko>	stodge: yes, it uses jni
| [Thursday 03 February 2011] [20:02:20] <stodge>	So I presume there's a performance hit?
| [Thursday 03 February 2011] [20:02:24] <mikko>	stodge: performance hit compared to what?
| [Thursday 03 February 2011] [20:02:44] <stodge>	If it were a native java app with no jini calls
| [Thursday 03 February 2011] [20:02:51] <stodge>	Significant
| [Thursday 03 February 2011] [20:03:09] <stodge>	Maybe that's not a reaonable question
| [Thursday 03 February 2011] [20:03:56] <mikko>	i dont really know the amount of overhead jni adds
| [Thursday 03 February 2011] [20:04:57] <stodge>	Me either
| [Thursday 03 February 2011] [20:04:58] <stodge>	:)
| [Thursday 03 February 2011] [20:05:51] <mikko>	but having native java app would mean replicating all zeromq logic in java
| [Thursday 03 February 2011] [20:05:56] <mikko>	so that doesnt seem appealing
| [Thursday 03 February 2011] [20:06:23] <stodge>	true
| [Thursday 03 February 2011] [20:06:57] <stodge>	I don't meant this in a negative sense, but I understand that rabbitmq has a native java library?
| [Thursday 03 February 2011] [20:07:58] <stodge>	I could be wrong
| [Thursday 03 February 2011] [20:08:34] <mikko>	probably almost any amqp client could communicate with it
| [Thursday 03 February 2011] [20:08:49] <stodge>	true
| [Thursday 03 February 2011] [20:09:04] <stodge>	zeromq has reliable multicast? Still reading through that long doc
| [Thursday 03 February 2011] [20:10:26] <stodge>	Ah pgm
| [Thursday 03 February 2011] [20:17:40] <stodge>	Hmm anyone know of a python/zeromq example of pgm
| [Thursday 03 February 2011] [20:26:04] <mikko>	stodge: its not really much different from using any other transport
| [Thursday 03 February 2011] [20:26:07] <mikko>	just different dsn
| [Thursday 03 February 2011] [20:26:37] <mikko>	anyways, off to bed
| [Thursday 03 February 2011] [20:26:37] <mikko>	nn
| [Thursday 03 February 2011] [20:38:52] <stodge>	thanks
| [Friday 04 February 2011] [00:31:28] <kabs>	As per my question above "Hello, in pub-sub model , if sub starts later and pub started earlier all messages by pub will be dropped. Is there a way to buffer those messages ( with some buffer limit) so that they can sent to subscriber joining later. Can I get some link to go through it or if it is there in zeroMQ guide can someone point out which section it is ??"
| [Friday 04 February 2011] [00:32:22] <kabs>	sustrik:Then how can be sync pub-sub there in one way in the zeroMQ guide , in chapter 2 in Node Coordination section, but it expect us pub to know the number of subscriber which is not a real world scenerio , how can be sync up pub-sub
| [Friday 04 February 2011] [01:36:44] <cyball>	mikko: i mean is there a way to have a look inside the message to define the type of the message an base o that to rout the request to a queue that can handle the message type ?
| [Friday 04 February 2011] [01:40:14] <guido_g>	cyball: see the guide, there is a lot about routing
| [Friday 04 February 2011] [01:40:14] <guido_g>	and: you're defining what's in the message, mq doesn't do anything w/ the your payload
| [Friday 04 February 2011] [01:40:14] <guido_g>	s/your//
| [Friday 04 February 2011] [01:40:22] <cyball>	guido_g: yes i know ... it is some times much easier to aks first if it is there or not :)
| [Friday 04 February 2011] [01:43:11] <guido_g>	cyball: sure, why invest your own time when you can waste the time of others
| [Friday 04 February 2011] [01:43:30] <guido_g>	cyball: it's a very fast and safe way to be ignored
| [Friday 04 February 2011] [01:45:19] <cyball>	guido_g: it was not my intention to waste the time of others ... and i do not think that the question was about that but by the way discussions like the one we have now is time wasting :)
| [Friday 04 February 2011] [01:46:28] <guido_g>	cyball: sure, from your point of view
| [Friday 04 February 2011] [01:48:03] <guido_g>	cyball: but given that you showed nearly no effort in understanding mq since you're here, it is not a waste of time -- from my point of view
| [Friday 04 February 2011] [01:50:08] <cyball>	guido_g: i would not say that ... it is sometimes hard to understand written words ... and in some cases it is more efficient to have an discussion about a think to proof also if the idea of the system you want to write is really good or only bullsh*t :)
| [Friday 04 February 2011] [01:51:31] <guido_g>	unfortunately does a "discussion" require both sides to something about the topic
| [Friday 04 February 2011] [01:51:38] <guido_g>	*to know
| [Friday 04 February 2011] [01:52:23] <cyball>	guido_g: i would say the conversation in alwas the key to success but you're right about the fact that i do not read all the documentation but if there are such great people like you it is much easier to get involved that is in my point of view the main fact of a community or not ?
| [Friday 04 February 2011] [01:53:14] <guido_g>	no
| [Friday 04 February 2011] [01:53:50] <guido_g>	experience shows that less than 10% of people like you ever come back and contribute
| [Friday 04 February 2011] [01:56:10] <cyball>	you're right but i guess that i belong to the 10% ... i'm not a scripting kiddy who makes a lot of fun trying something out and through it away after playing with it ... there is a lot more behind my intention than only have a look on zeromq :)
| [Friday 04 February 2011] [01:56:51] <cyball>	but also this information is something you can ask .... as i mentioned i will answer to it and i will contribute if i know enough about it ... this system as i mentioned yesterday is really really great
| [Friday 04 February 2011] [01:58:51] <cyball>	i was looking forward to write myself such a system for communication for my project i'm developing at the moment so that was the reason checking out some of them ... and 0mq is the only one fits to my needs :)
| [Friday 04 February 2011] [02:06:07] <guido_g>	guess how often i must have read things like these...
| [Friday 04 February 2011] [02:07:02] <guido_g>	in short agin: show your effort and you'll receive much more answers and insight
| [Friday 04 February 2011] [02:07:05] <cyball>	probably every time of the 90% from the of the people do not belong to the 10% you mentioned ? :)
| [Friday 04 February 2011] [02:07:22] <guido_g>	what?
| [Friday 04 February 2011] [02:07:48] <cyball>	i guess you read this very often 
| [Friday 04 February 2011] [02:07:55] <guido_g>	right
| [Friday 04 February 2011] [02:08:00] <guido_g>	for decades
| [Friday 04 February 2011] [02:13:40] <cyball>	ok i will have a look on the manual now ... you have a lot of experinces and you are still patient ... thx for your time i will ask if there is something not clear in the manual :)
| [Friday 04 February 2011] [02:13:52] <sustrik>	:)
| [Friday 04 February 2011] [03:57:34] <Guthur>	is there a limit of how many subscribers can simultaneously connect to tcp publisher?
| [Friday 04 February 2011] [03:59:36] <mikko>	Guthur: no, not really
| [Friday 04 February 2011] [03:59:46] <mikko>	apart from the obvious limits of hardware / operating system etc
| [Friday 04 February 2011] [04:01:23] <Guthur>	i seem to be getting an unhandled exception when I try to connect multiple times, if I put in a wait it is ok
| [Friday 04 February 2011] [04:01:30] <Guthur>	I am using the CLR binding
| [Friday 04 February 2011] [04:01:58] <mikko>	Guthur: which exception is it?
| [Friday 04 February 2011] [04:02:46] <Guthur>	that's the horrible thing, it passes through the .NET app unhandled, so it just says unhandle exception in win32 code
| [Friday 04 February 2011] [04:03:10] <mikko>	can you attach a debugger and check ?
| [Friday 04 February 2011] [04:03:25] <Guthur>	I probably have implement a global unhandled exception handler to catch it
| [Friday 04 February 2011] [04:03:35] <mikko>	have you tried to reproduce it on other machines?
| [Friday 04 February 2011] [04:03:46] <mikko>	if it's reproducable you could open an issue with reproduce code
| [Friday 04 February 2011] [04:04:09] <sustrik>	Guthur: are you saying that clrzmq throws a generic exception?
| [Friday 04 February 2011] [04:04:20] <sustrik>	then it's a bug in clrzmq
| [Friday 04 February 2011] [04:04:27] <mikko>	sustrik: i think it might be C++ exception from unmanaged code
| [Friday 04 February 2011] [04:04:35] <mikko>	which bubbles up and terminates the program
| [Friday 04 February 2011] [04:04:39] <mikko>	(i assume)
| [Friday 04 February 2011] [04:04:40] <sustrik>	what does that mean?
| [Friday 04 February 2011] [04:04:49] <sustrik>	ah
| [Friday 04 February 2011] [04:04:51] <sustrik>	got it
| [Friday 04 February 2011] [04:05:07] <sustrik>	a C++ exception that gets to C# code
| [Friday 04 February 2011] [04:05:19] <mikko>	thats how i understood it
| [Friday 04 February 2011] [04:05:19] <Guthur>	yeah, clr does provide a mechanism to catch these though, I'll try adding it
| [Friday 04 February 2011] [04:05:33] <sustrik>	wait a sec
| [Friday 04 February 2011] [04:05:39] <sustrik>	clrzmq is using C API
| [Friday 04 February 2011] [04:05:44] <sustrik>	not C++ API
| [Friday 04 February 2011] [04:05:46] <sustrik>	underneath
| [Friday 04 February 2011] [04:05:53] <sustrik>	so there should be no C++ exceptions
| [Friday 04 February 2011] [04:06:24] <sustrik>	C API returns errnos...
| [Friday 04 February 2011] [04:07:14] <Guthur>	I should be catching any exceptions in the clrzmq code
| [Friday 04 February 2011] [04:07:18] <Guthur>	it is very strange
| [Friday 04 February 2011] [04:07:40] <sustrik>	what i'm saying is that there are no exceptions from 0mq
| [Friday 04 February 2011] [04:07:59] <sustrik>	so if there's an exception is rather generated by clrzmq
| [Friday 04 February 2011] [04:08:41] <sustrik>	what's the win32 err code you are getting btw?
| [Friday 04 February 2011] [04:09:11] <Guthur>	1 min
| [Friday 04 February 2011] [04:09:58] <Guthur>	i get the JIT debugger saying unhandled win32 exception
| [Friday 04 February 2011] [04:10:23] <sustrik>	no further info?
| [Friday 04 February 2011] [04:11:03] <sustrik>	mikko: btw have you seen the email from neale?
| [Friday 04 February 2011] [04:11:28] <sustrik>	the one about system z
| [Friday 04 February 2011] [04:12:18] <Guthur>	sustrik: No, it just asks to connect the debugger, but the problem is a debugger is already attached, I am running the server app in visual studio in debug mode
| [Friday 04 February 2011] [04:12:50] <sustrik>	yuck :(
| [Friday 04 February 2011] [04:12:57] <Guthur>	yeah tell me about it
| [Friday 04 February 2011] [04:14:33] <Guthur>	I'll add the global handler and see if I get anything more meaninful
| [Friday 04 February 2011] [04:14:39] <sustrik>	ok
| [Friday 04 February 2011] [04:18:08] <mikko>	sustrik: i was just replying it
| [Friday 04 February 2011] [04:18:19] <mikko>	replying to it
| [Friday 04 February 2011] [04:18:42] <mikko>	oddly enough on windows the openpgm installation just disappears occasionally
| [Friday 04 February 2011] [04:18:48] <mikko>	havent really figured out yet what happens
| [Friday 04 February 2011] [04:19:02] <mikko>	but in any case we have a release build with ZeroMQ+OpenPGM for windows
| [Friday 04 February 2011] [04:19:26] <mikko>	http://snapshot.valokuva.org/msvc2008/2011-02-04_09-09-05/ is built from WithOpenPGM configuration
| [Friday 04 February 2011] [04:31:39] <Guthur>	the debugger seems to say libzmq is C++
| [Friday 04 February 2011] [04:32:04] <Guthur>	I got a debugger attached, all I have is the stack trace though
| [Friday 04 February 2011] [04:33:33] <Guthur>	http://paste.lisp.org/display/119368
| [Friday 04 February 2011] [04:37:00] <sustrik>	mikko: congrats!
| [Friday 04 February 2011] [04:37:36] <sustrik>	Guthur: it's in C++
| [Friday 04 February 2011] [04:37:41] <sustrik>	but the API is pure C
| [Friday 04 February 2011] [04:38:10] <sustrik>	so no exceptions should pass out of libzmq
| [Friday 04 February 2011] [04:38:13] <Guthur>	sustrik: does the stack trace give an clues?
| [Friday 04 February 2011] [04:38:20] <Guthur>	an,any
| [Friday 04 February 2011] [04:38:33] <sustrik>	sure, let's have a look
| [Friday 04 February 2011] [04:38:43] <mikko>	abort()
| [Friday 04 February 2011] [04:38:48] <mikko>	seems to be an assertion
| [Friday 04 February 2011] [04:41:43] <sustrik>	Guthur: what version of 0mq?
| [Friday 04 February 2011] [04:42:26] <Guthur>	2.0.10
| [Friday 04 February 2011] [04:43:02] <sustrik>	thx
| [Friday 04 February 2011] [04:44:39] <sustrik>	Guthur: i think this is the patch fixed by dhammika in 2.1 some time ago
| [Friday 04 February 2011] [04:44:47] <sustrik>	can you check with latest master?
| [Friday 04 February 2011] [04:45:05] <Guthur>	just trying that now, hehe
| [Friday 04 February 2011] [04:45:17] <Guthur>	sorry it never occurred to me to try before
| [Friday 04 February 2011] [05:07:18] <Guthur>	I am getting the same with 2.1
| [Friday 04 February 2011] [05:07:23] <Guthur>	same trace as well
| [Friday 04 February 2011] [05:11:35] <Guthur>	oh wait I think this is my fault
| [Friday 04 February 2011] [05:11:56] <Guthur>	what is suppose to happen if two sockets try to connect with the same identity
| [Friday 04 February 2011] [05:12:30] <sustrik>	you shouldn't do that
| [Friday 04 February 2011] [05:12:39] <sustrik>	but in 2.1 it shouldn't fail
| [Friday 04 February 2011] [05:13:07] <sustrik>	the bind side should silently drop the second connection iirc
| [Friday 04 February 2011] [05:13:14] <mikko>	it still asserts
| [Friday 04 February 2011] [05:13:21] <Guthur>	Yeah, I don't really want to be doing that, but this prototype code, and I haven't generated very unique uid
| [Friday 04 February 2011] [05:13:26] <sustrik>	ah, ok
| [Friday 04 February 2011] [05:13:39] <Guthur>	will when I remove the set Identity it works
| [Friday 04 February 2011] [05:13:43] <Guthur>	well*
| [Friday 04 February 2011] [05:14:24] <Guthur>	ok, so mystery solved then?
| [Friday 04 February 2011] [05:14:33] <sustrik>	i think so
| [Friday 04 February 2011] [05:15:01] <Guthur>	is there any plans to make this scenario a little less fatal
| [Friday 04 February 2011] [05:18:51] <sustrik>	that would be nice
| [Friday 04 February 2011] [05:18:59] <cyball>	is there a way to tell the XREP(router) depending on the MessageBody to which XREQ(dealer) to route the message .... i could not figure that out the only way to work on specific messages i found was to use the PubSub scenario but this is only unidirectional so no response will be routed back
| [Friday 04 February 2011] [05:19:02] <sustrik>	nbody volunteered yet though
| [Friday 04 February 2011] [05:20:15] <sustrik>	REP socket routes the reply back to original requester automagically
| [Friday 04 February 2011] [05:21:21] <Guthur>	unfortunately I seem to fighting a losing battle to allow the use of ZeroMQ in our app, the team lead is adamant I should use .Net threads with global state instead
| [Friday 04 February 2011] [05:21:30] <Guthur>	he is not listening to reason
| [Friday 04 February 2011] [05:22:37] <cyball>	yes i know but can i tell the REP(papa) to get only specific messages for example if i have some calculation and some data get from DB i want to make 2 different REP(papas) one for calcucation and one for data
| [Friday 04 February 2011] [05:22:54] <ianbarber>	sustrik - i filed a bug about the dual identity issue by the way. it certainly looks like it should drop, but doesn't
| [Friday 04 February 2011] [05:23:37] <ianbarber>	cyball:  the XREP is going to route based on the identity, and based on the first message segment
| [Friday 04 February 2011] [05:24:27] <ianbarber>	so if you had a 'calc' and a 'data' identity, you'd just need to prepend the message with that identity and a blank one before sending it to the xrep. 
| [Friday 04 February 2011] [05:25:02] <ianbarber>	that can be in the message body any way you want, just write a bit of code to pull it out and stick it in as a message segment before sending on to the xrep
| [Friday 04 February 2011] [05:27:59] <sustrik>	Guthur: that's pretty common occurence
| [Friday 04 February 2011] [05:28:54] <sustrik>	cyball: you have to use two different sockets
| [Friday 04 February 2011] [05:29:08] <sustrik>	so, say calculations are passed on port 5555
| [Friday 04 February 2011] [05:29:15] <sustrik>	and DB data on 5556
| [Friday 04 February 2011] [05:31:34] <cyball>	sustrik: is that the only way ?
| [Friday 04 February 2011] [05:31:50] <sustrik>	it's the only sensible way
| [Friday 04 February 2011] [05:32:07] <sustrik>	that way your network knows about your feeds
| [Friday 04 February 2011] [05:32:26] <sustrik>	and thus, for example, large DB dataset being passed
| [Friday 04 February 2011] [05:32:34] <sustrik>	doesn't block little calc operations
| [Friday 04 February 2011] [05:33:37] <cyball>	sustrik: thx
| [Friday 04 February 2011] [05:33:44] <sustrik>	np
| [Friday 04 February 2011] [08:54:30] <mikko>	sustrik: there?
| [Friday 04 February 2011] [08:54:47] <sustrik>	mikko: hi
| [Friday 04 February 2011] [08:54:48] <mikko>	i would like to discuss openpgm situation at some point
| [Friday 04 February 2011] [08:54:54] <sustrik>	sure
| [Friday 04 February 2011] [08:55:02] <mikko>	have you got a long-term vision for it?
| [Friday 04 February 2011] [08:55:02] <sustrik>	i have no idea what's going on
| [Friday 04 February 2011] [08:55:16] <mikko>	i am now looking into using the autoconf steven added to openpgm trunk
| [Friday 04 February 2011] [08:55:23] <mikko>	i can get it to build 
| [Friday 04 February 2011] [08:55:36] <sustrik>	well, from 30,000 feet
| [Friday 04 February 2011] [08:55:37] <mikko>	but i'm afraid the way i am doing it at the moment is not portable
| [Friday 04 February 2011] [08:56:00] <sustrik>	the pgm is needed for stock traders, banks etc.
| [Friday 04 February 2011] [08:56:00] <mikko>	so im wondering is the longer-term plan to bundle openpgm with zeromq
| [Friday 04 February 2011] [08:56:18] <mikko>	or is it feasible to ask users to install openpgm if they want to use it with zeromq
| [Friday 04 February 2011] [08:56:39] <mikko>	that would seem like the normal way "if you compile --with-pgm make sure you have installed openpgm"
| [Friday 04 February 2011] [08:56:42] <mikko>	brb
| [Friday 04 February 2011] [08:57:29] <Silly>	huh
| [Friday 04 February 2011] [08:58:17] <sustrik>	well, i am not sure openpgm is moving towards becoming a stand-alone package
| [Friday 04 February 2011] [08:58:34] <sustrik>	it would be ideal if it was so
| [Friday 04 February 2011] [08:58:58] <sustrik>	but we have to be pragmatic at the moment
| [Friday 04 February 2011] [09:03:44] <mikko>	sustrik: i'm beginning to doubt whether bundling is the pragmatic approach
| [Friday 04 February 2011] [09:04:07] <mikko>	as the problem with the autotools build is that some platforms dont support linking static libraries into shared libraries
| [Friday 04 February 2011] [09:05:06] <mikko>	at least thats my understand
| [Friday 04 February 2011] [09:05:07] <mikko>	ing
| [Friday 04 February 2011] [09:05:18] <sustrik>	i see
| [Friday 04 February 2011] [09:05:25] <mikko>	then again, i dont see why openpgm couldnt be installed as shared library 
| [Friday 04 February 2011] [09:05:31] <mikko>	and let libtool worry about the best way
| [Friday 04 February 2011] [09:05:40] <mikko>	but that might cause confusion as well
| [Friday 04 February 2011] [09:05:54] <mikko>	because some people might have openpgm already installed and 0mq would write over that
| [Friday 04 February 2011] [09:05:55] <sustrik>	i have no specific opinion on that
| [Friday 04 February 2011] [09:06:46] <sustrik>	the only goal imo is to make it as easy to build/use as possible
| [Friday 04 February 2011] [09:12:03] <sustrik>	mikko: what are your thoughts atm?
| [Friday 04 February 2011] [09:37:41] <mikko>	sustrik: my current thinking is that those two builds make more sense as separate ones
| [Friday 04 February 2011] [09:37:58] <sustrik>	how would people install it then?
| [Friday 04 February 2011] [09:38:31] <mikko>	execute their build
| [Friday 04 February 2011] [09:38:35] <mikko>	and install shared library
| [Friday 04 February 2011] [09:38:49] <sustrik>	which build?
| [Friday 04 February 2011] [09:39:02] <sustrik>	openpgm?
| [Friday 04 February 2011] [09:39:14] <mikko>	execute openpgm build, install it
| [Friday 04 February 2011] [09:39:21] <mikko>	execute zeromq build with --with-pgm
| [Friday 04 February 2011] [09:40:10] <sustrik>	well, it makes the whole process 2x as difficult
| [Friday 04 February 2011] [09:40:14] <sustrik>	1. install scons
| [Friday 04 February 2011] [09:40:28] <sustrik>	2. download openpgm (the right version!)
| [Friday 04 February 2011] [09:40:34] <sustrik>	4. build & install
| [Friday 04 February 2011] [09:40:44] <sustrik>	4. install autotools
| [Friday 04 February 2011] [09:40:50] <sustrik>	5. download 0mq
| [Friday 04 February 2011] [09:40:58] <sustrik>	6. build & install
| [Friday 04 February 2011] [09:41:52] <sustrik>	but as i say, i don't have a strong opinion
| [Friday 04 February 2011] [09:42:26] <sustrik>	pgm is used by stock traders, which have enough money to actually pay someone to that for them
| [Friday 04 February 2011] [09:42:43] <mikko>	thats not 100% correct now that openpgm has autotools build
| [Friday 04 February 2011] [09:42:45] <sustrik>	or even sponsor binary builds & installers
| [Friday 04 February 2011] [09:42:52] <mikko>	execute ./configure on openpgm, make install
| [Friday 04 February 2011] [09:43:00] <mikko>	execute ./configure --with-pgm on zeromq, make install
| [Friday 04 February 2011] [09:43:12] <sustrik>	yeah, that's better
| [Friday 04 February 2011] [09:43:14] <mikko>	if you use release packages. autotools are needed for trunk version
| [Friday 04 February 2011] [09:43:25] <mikko>	and even that is mitigated with snapshots which have configure script in them
| [Friday 04 February 2011] [09:43:40] <sustrik>	ack
| [Friday 04 February 2011] [09:44:11] <sustrik>	the hardest part, i assume, is getting right versions of 0mq and openpgm
| [Friday 04 February 2011] [09:44:55] <sustrik>	anyway, you are the build system maintainer, so it's up to you
| [Friday 04 February 2011] [09:45:50] <sustrik>	i would consult the mailing list first though
| [Friday 04 February 2011] [09:47:59] <drbobbeaty>	I know I'm only a user, and this is your choice, but as for me, ZeroMQ "contains" OpenPGM. There's no utility of OpenPGM for me outside of ZeroMQ, and a large part of ZeroMQ (for me) is the epgm transport. So if you unbundle these, it's going to make maintenance harder for me. I'll have to make sure that no machine in the organization has the "wrong" OpenPGM for ZeroMQ, etc.
| [Friday 04 February 2011] [09:48:52] <drbobbeaty>	I know it seems simple to unbundle them, and I can certainly see the advantages, but just one vote from your user base is that in an organization with many machines, this is something that I'd rather not have to deal with.
| [Friday 04 February 2011] [09:49:54] <sustrik>	that was the point i was trying to make but you are more eloquent than i am :)
| [Friday 04 February 2011] [10:18:57] <edw>	The clojure glue has a destory-socket call which calls the destroy method of a socket. There is no destroy method. There is a close method. Did this ever work (ie was destroy renamed to close) or has it been broken forever?
| [Friday 04 February 2011] [10:20:56] <sustrik>	there's no close method in C API
| [Friday 04 February 2011] [10:21:03] <sustrik>	there's zmq_close() though
| [Friday 04 February 2011] [10:21:13] <sustrik>	what are you referring to?
| [Friday 04 February 2011] [10:21:43] <edw>	I'm looking at he jzmq Java bindings. Those have a Socket::close method.
| [Friday 04 February 2011] [10:22:19] <sustrik>	that seems right
| [Friday 04 February 2011] [10:22:42] <sustrik>	i am not aware there was a destroy method originally, but maybe
| [Friday 04 February 2011] [10:22:51] <sustrik>	why not just use close instad of destroy?
| [Friday 04 February 2011] [10:24:39] <edw>	...which calls the finalizer which calls zmq_close. Mystery solved. I think that the Clojure glue is a piece of fairly shoddy workmanship. Time to fork or re-write it.
| [Friday 04 February 2011] [10:25:39] <edw>	It's not idiomatic Clojure e.g. constants look like +this+. And it calls methods that don't exist.
| [Friday 04 February 2011] [10:27:27] <sustrik>	sure, go on
| [Friday 04 February 2011] [10:27:32] <edw>	Oh, and it (inaccurately) redefines all the enums in the org.zeromq.ZMQ class. Ugh...
| [Friday 04 February 2011] [10:28:21] <sustrik>	well, it's up to you to fix it :)
| [Friday 04 February 2011] [10:30:16] <edw>	Actually, it should probably just be deprecated, as it's a molecule-thick layer of sewing machine oil over the JZMQ classes.
| [Friday 04 February 2011] [10:30:44] <edw>	E.g. "(defn make-context [io-threads] (ZMQ/context io-threads))
| [Friday 04 February 2011] [10:33:16] <sustrik>	maybe the intent was to make the API more clojure-like?
| [Friday 04 February 2011] [10:33:49] <edw>	For sure, but there's a better way to do it... I'm typing away right now...
| [Friday 04 February 2011] [10:45:22] <CIA-21>	zeromq2: 03Thijs Terlouw 07master * r042e34a 10/ include/zmq.hpp : 
| [Friday 04 February 2011] [10:45:22] <CIA-21>	zeromq2: operator void* () added to context_t.
| [Friday 04 February 2011] [10:45:22] <CIA-21>	zeromq2: Makes it possible to share the context from C++ to C.
| [Friday 04 February 2011] [10:45:22] <CIA-21>	zeromq2: Signed-off-by: Thijs Terlouw <thijsterlouw@gmail.com> - http://bit.ly/ew59JP
| [Friday 04 February 2011] [13:04:04] <Esmil>	Hmm.. suppose I have a select()/epoll()/what-have-you mainloop running, is there a way I can get events on a filedescripter whenever a socket has a new message?
| [Friday 04 February 2011] [13:05:25] <Esmil>	A zeromq socket that is 
| [Friday 04 February 2011] [13:12:47] <Steve-o>	try zmq_poll
| [Friday 04 February 2011] [13:14:51] <Esmil>	Yeah, but that means I'd have to rewrite the mainloop to use zmq_poll. I'm quite happy with libev
| [Friday 04 February 2011] [13:18:07] <Steve-o>	check the mailling list archive, it certainly has come up before
| [Friday 04 February 2011] [13:27:37] <Esmil>	Damn, once again I'm ahead of time :P http://article.gmane.org/gmane.network.zeromq.devel/1628
| [Friday 04 February 2011] [13:33:34] <mikko>	good evening
| [Friday 04 February 2011] [13:34:04] <mikko>	Esmil: yes there is 
| [Friday 04 February 2011] [13:34:23] <mikko>	Esmil: with 2.1.x you can use zmq_getsockopt( ZMQ_FD
| [Friday 04 February 2011] [13:35:19] <Esmil>	mikko: Cool! What version is the reference manual on zeromq.org refering to?
| [Friday 04 February 2011] [13:35:34] <mikko>	2.0.x i think
| [Friday 04 February 2011] [13:35:41] <Esmil>	Ahh, I see. Thanks
| [Friday 04 February 2011] [13:41:26] <Esmil>	2.0.x can speak with 2.1.x right? Or is there a reason my distribution hasn't updated to 2.1.x yet?
| [Friday 04 February 2011] [13:42:41] <Esmil>	Ohh, it's considered beta
| [Friday 04 February 2011] [13:42:50] 	 * Esmil should have read the NEWS file first >.<
| [Friday 04 February 2011] [13:43:38] <mikko>	can speak with yes
| [Friday 04 February 2011] [13:43:50] <Esmil>	Great
| [Friday 04 February 2011] [13:43:58] <mikko>	there are slight changes in the api so code written for 2.0.x might require modifications
| [Friday 04 February 2011] [13:44:21] <mikko>	the biggest changes are in zmq_term semantics and that zmq_context takes one param instead of many
| [Friday 04 February 2011] [13:45:38] <Esmil>	I see
| [Friday 04 February 2011] [13:47:13] <mikko>	drbobbeaty: i am not looking to necessarily uncouple
| [Friday 04 February 2011] [13:47:26] <mikko>	but what i am looking at is possible linking shared library rather than static
| [Friday 04 February 2011] [13:47:31] <mikko>	Steve-o: there?
| [Friday 04 February 2011] [13:48:11] <mikko>	so, i was building OpenPGM autoconf builds and ran into following thing which im not sure how to solve the cleanest way:
| [Friday 04 February 2011] [13:48:38] <mikko>	a) running the autoconf build generates static libraries that are non PIC by default
| [Friday 04 February 2011] [13:48:56] <mikko>	b) on 64bit linux you need to have pic static libraries to link them into shared libraries
| [Friday 04 February 2011] [13:49:01] <mikko>	c) this is probably not portable
| [Friday 04 February 2011] [13:49:14] <drbobbeaty>	mikko: I'm all for linking shared libs - even preferred. But it's the ability to have it built all at once, so that I can build RPMs and Ubuntu deb packages and have it be treated as a single, atomic, deliverable.
| [Friday 04 February 2011] [13:50:57] <Steve-o>	k
| [Friday 04 February 2011] [13:51:13] <Steve-o>	I normally make a -pic lib in scons
| [Friday 04 February 2011] [13:51:45] <Steve-o>	is there an easy way to do this with libtool & automake?
| [Friday 04 February 2011] [13:52:41] <Steve-o>	I thought the .la lib was supposed to be PIC
| [Friday 04 February 2011] [13:53:06] <Steve-o>	otherwise libtool couldn't build the shared library?
| [Friday 04 February 2011] [14:06:55] <mikko>	.la can contain shared and static
| [Friday 04 February 2011] [14:07:02] <mikko>	shared -pic and static non pic
| [Friday 04 February 2011] [14:07:15] <mikko>	at least on my system
| [Friday 04 February 2011] [14:07:36] <mikko>	i could link against the libtool archive in which case libtool can decide what to link against
| [Friday 04 February 2011] [14:24:01] <zchrish>	Question: What happens to the server, in a XREQ/XREP pattern, when a client dies after sending a request but before it receives the response from its query?
| [Friday 04 February 2011] [14:25:00] <cremes>	zchrish: when the server tries to send the reply, it should note that the peer is gone and drop the packet
| [Friday 04 February 2011] [14:26:21] <zchrish>	cremes: I assume this failure mechanism is modeled in zeromq and, therefore, handles the situation ok. Will a reconnect from the same client pose any issue I should be aware of?
| [Friday 04 February 2011] [14:27:46] <zchrish>	I.E. the client program dies and it is restarted from the OS. 
| [Friday 04 February 2011] [14:28:47] <zchrish>	In a different situation, suppose a server dies, what should the client do to restart w/o resorting to a complete program restart?
| [Friday 04 February 2011] [14:29:10] <zchrish>	Thank you.
| [Friday 04 February 2011] [14:52:56] <Leolo_3>	zchrish : depends on weither you gave the socket an identity
| [Friday 04 February 2011] [15:33:58] <zchrish>	Leolo_3: No, I didn't explicity give an identity.
| [Friday 04 February 2011] [15:35:21] <Leolo_3>	then the messages get dropped
| [Friday 04 February 2011] [15:35:48] <Leolo_3>	for your server dies senario : zeromq does automatic reconnect
| [Friday 04 February 2011] [15:37:34] <zchrish>	I am not worried about dropped messages. I just I am trying to learn the proper reconnection strategy. For example, do I need to shut down the zmq::context and start another or do I simply close and reopen?
| [Friday 04 February 2011] [15:38:50] <zchrish>	My current situation appears that clients hang during a server crash and must be shut down (ctrl+c) and restarted. 
| [Friday 04 February 2011] [15:39:46] <zchrish>	The docs don't discuss this area much. Clients don't have an issue if the server shuts down gracefully.
| [Friday 04 February 2011] [15:43:43] <Steve-o>	so the clients think the TCP socket is still open
| [Friday 04 February 2011] [15:44:05] <Steve-o>	I think this was discovered before as reasons for implementing heartbeats
| [Friday 04 February 2011] [15:44:15] <Steve-o>	in the list somewhere
| [Friday 04 February 2011] [15:50:01] <Steve-o>	>> http://lists.zeromq.org/pipermail/zeromq-dev/2010-October/007011.html
| [Friday 04 February 2011] [16:50:38] <sustrik>	zchris: to be resilient in case of server failure
| [Friday 04 February 2011] [16:50:47] <sustrik>	you have to timeout waiting for the reply
| [Friday 04 February 2011] [16:50:55] <sustrik>	and resend the request
| [Friday 04 February 2011] [16:51:12] <sustrik>	in theory, 0mq should do that for you, but it's not yet implemented :(
| [Friday 04 February 2011] [18:31:44] <zchrish>	Yes, using heartbeats is what I figured I needed to do. Thank you.
| [Friday 04 February 2011] [18:33:53] <zchrish>	How best to set a timeout for : string *string = s_recv (socket) ?
| [Friday 04 February 2011] [18:55:26] <Steve-o>	synchronous or asynchronous?
| [Friday 04 February 2011] [18:55:57] <zchrish>	In my case, I am using XREP/XREQ
| [Friday 04 February 2011] [19:13:55] <Steve-o>	but how do you want the timeout handled?
| [Friday 04 February 2011] [19:16:35] <zchrish>	Well, I will implement a handler of course. I am just trying to figure out how to configure 0mq to implement a timeout.
| [Friday 04 February 2011] [20:10:51] <Leolo_3>	zchrish : zmq_poll() with a timeout value
| [Friday 04 February 2011] [20:25:46] <zchrish>	I see; thank you.
| [Saturday 05 February 2011] [04:52:40] <jugg>	running ./autogen.sh using autoconf 2.67 (as installed from debian 6), produces this: configure.in:9: warning: AC_INIT: not a literal: m4_esyscmd([./version.sh | tr -d '\n'])  And this patch fixes it: http://paste2.org/p/1229684  - Will this cause issues on other systems? If not I'll go through the steps of submitting the patch.
| [Saturday 05 February 2011] [05:50:08] <Guthur>	Has the reason been identified why when two sockets connect with the same identity it crashes the destination?
| [Saturday 05 February 2011] [06:13:01] <sustrik>	jugg: you have to speak to mikko
| [Saturday 05 February 2011] [06:13:08] <sustrik>	he's in charge of the build system
| [Saturday 05 February 2011] [06:13:30] <sustrik>	Guthur: i assume there's an assertion there
| [Saturday 05 February 2011] [06:13:33] <sustrik>	not sure
| [Saturday 05 February 2011] [06:22:24] <Guthur>	right, assert(_engine)
| [Saturday 05 February 2011] [06:22:35] <Guthur>	or engine_ rather, let me find the line
| [Saturday 05 February 2011] [06:22:47] <Guthur>	it was on that stack trace I posted yesterday
| [Saturday 05 February 2011] [06:25:15] <Guthur>	I personally feel it should be reasonably high priority bug, having clients being able to crash the server so easily is not good
| [Saturday 05 February 2011] [06:26:05] <Guthur>	and from what I have experienced the server app will not even receive reasonable feedback on the error
| [Saturday 05 February 2011] [06:26:39] <sustrik>	yup, feel free to fix it
| [Saturday 05 February 2011] [06:29:56] <Guthur>	the assert in question is zmq_assert (engine_) in zmq::session_t::process_attach
| [Saturday 05 February 2011] [06:34:19] <Guthur>	peer_identity_ would be the identity, correct?
| [Saturday 05 February 2011] [06:37:43] <sustrik>	peer_identity_ is the identity of the peer socket
| [Saturday 05 February 2011] [06:51:35] <Guthur>	I'm going to slot this on to my todo list, but lack of inner zeromq knowledge will make it hard to find 
| [Saturday 05 February 2011] [06:52:00] <Guthur>	I want to add a couple of things to clrzmq2 today
| [Saturday 05 February 2011] [06:54:17] <Guthur>	I was actually thinking of adding a clrzmq-extensions project, with a special form of queue device, and generic send/recv with .Net serialization
| [Saturday 05 February 2011] [07:05:36] <Guthur>	Umm, pub/sub using inproc, seems to have stop working for me, very odd
| [Saturday 05 February 2011] [07:07:21] <Guthur>	actually scratch that, its inproc in general
| [Saturday 05 February 2011] [07:11:08] <sustrik>	inproc stopped working?
| [Saturday 05 February 2011] [07:13:21] <Guthur>	must be something to do with this computer
| [Saturday 05 February 2011] [07:13:25] <Guthur>	it was working fine in work
| [Saturday 05 February 2011] [07:13:55] <Guthur>	and it worked fine on this before
| [Saturday 05 February 2011] [07:14:11] <Guthur>	the peer has connection refused
| [Saturday 05 February 2011] [07:23:01] <Guthur>	ah got it
| [Saturday 05 February 2011] [07:23:15] <Guthur>	I did not realize inproc connection had to be the same context
| [Saturday 05 February 2011] [07:23:25] <Guthur>	learnt something new
| [Saturday 05 February 2011] [07:32:50] <sustrik>	:)
| [Saturday 05 February 2011] [07:52:47] <mikko>	good morning
| [Saturday 05 February 2011] [08:00:33] <jugg>	mikko, I just sent a patch to the mailing list, making a change to configure.in - I don't know if it'll have any side affects on other systems.
| [Saturday 05 February 2011] [08:07:35] <mikko>	let me check, sec
| [Saturday 05 February 2011] [08:43:44] <CIA-21>	zeromq2: 03Chris Rempel 07master * r4efead1 10/ (AUTHORS configure.in): 
| [Saturday 05 February 2011] [08:43:44] <CIA-21>	zeromq2: Fixed autogen.sh warnings on Debian 6 systems.
| [Saturday 05 February 2011] [08:43:44] <CIA-21>	zeromq2: Signed-off-by: Chris Rempel <csrl@gmx.com>
| [Saturday 05 February 2011] [08:43:44] <CIA-21>	zeromq2: Please enter the commit message for your changes. Lines starting - http://bit.ly/dHdxHE
| [Saturday 05 February 2011] [08:50:53] <jugg>	sustrik, is there any point in opening pull requests on github for zeromq?
| [Saturday 05 February 2011] [08:53:35] <sustrik>	jugg: no
| [Saturday 05 February 2011] [08:53:41] <jugg>	ok
| [Saturday 05 February 2011] [08:53:42] <sustrik>	the process works via the mailing list
| [Saturday 05 February 2011] [09:02:28] <jugg>	tests/test_hwm should be added to .gitignore
| [Saturday 05 February 2011] [09:04:01] <sustrik>	jugg: let me see
| [Saturday 05 February 2011] [09:05:21] <CIA-21>	zeromq2: 03Martin Sustrik 07master * rc8e5be8 10/ .gitignore : 
| [Saturday 05 February 2011] [09:05:21] <CIA-21>	zeromq2: test-hwm added to .gitignore
| [Saturday 05 February 2011] [09:05:21] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/hLOv45
| [Saturday 05 February 2011] [09:05:30] <sustrik>	done
| [Saturday 05 February 2011] [10:14:31] <mikko>	does anyone know if Neale is on IRC?
| [Saturday 05 February 2011] [10:17:02] <sustrik>	mikko: he was here few day ago
| [Saturday 05 February 2011] [10:17:09] <sustrik>	but i haven't seen him since
| [Saturday 05 February 2011] [10:24:41] <mikko>	mailed him
| [Saturday 05 February 2011] [10:24:47] <mikko>	it would be very nice to get system z
| [Saturday 05 February 2011] [10:24:57] <mikko>	and maybe solaris sparc at some point
| [Saturday 05 February 2011] [10:31:12] <sustrik>	i think mato has a solaris box in the cellar
| [Saturday 05 February 2011] [10:31:31] <sustrik>	you may ask him whether it's possible to put it online after's he back from NZ
| [Saturday 05 February 2011] [10:40:21] <Guthur>	ah the pain of maintaining backwards compatibility
| [Saturday 05 February 2011] [10:40:38] <Guthur>	though the problem is my own doing
| [Saturday 05 February 2011] [10:41:15] <Guthur>	I should have made the Poll method static in clrzmq2
| [Saturday 05 February 2011] [10:48:56] <sustrik>	you mean the original problem you've reported?
| [Saturday 05 February 2011] [11:08:34] <Guthur>	oh no sorry, unrelated
| [Saturday 05 February 2011] [11:08:39] <Guthur>	just lamenting
| [Saturday 05 February 2011] [12:34:35] <traviscline>	Any idea on the expected amount of overhead associated with using an external event loop ala ZMQ_FD?
| [Saturday 05 February 2011] [13:05:57] <Guthur>	Would it be ok to put code in the clrzmq2 repo that should be considered beta
| [Saturday 05 February 2011] [13:06:31] <Guthur>	It doesn't effect the binding, it's just extension/helper stuff
| [Saturday 05 February 2011] [13:10:39] <Leolo_3>	travis : I suspect very very little.  ZMQ does it's stuff in a background thread, and sends messages over the FD.  It does this "normally" when you call zmq_recv().  
| [Saturday 05 February 2011] [13:20:14] <traviscline>	Leolo_3: thanks
| [Sunday 06 February 2011] [05:00:30] <mikko>	good morning
| [Sunday 06 February 2011] [05:04:18] <sustrik>	morning
| [Sunday 06 February 2011] [05:10:54] <mikko>	neale is doing pretty good job
| [Sunday 06 February 2011] [05:11:05] <mikko>	we have s390x soon in build cluster
| [Sunday 06 February 2011] [05:16:58] <mikko>	im going to visit chinese new year and get back to hacking
| [Sunday 06 February 2011] [05:33:41] <sustrik>	great!
| [Sunday 06 February 2011] [06:51:20] <Guthur>	pieterh, Nice talk, the one you sent on the list
| [Sunday 06 February 2011] [06:51:34] <pieterh>	Hi Guthur :-)
| [Sunday 06 February 2011] [06:51:49] <pieterh>	It was very short, next time we'll try to get a longer slot
| [Sunday 06 February 2011] [06:51:57] <Guthur>	I'm going to try and get some of my colleagues to watch that, might help me convince them that OMQ fits our needs
| [Sunday 06 February 2011] [06:52:28] <Guthur>	a very good introduction though, even with the short time slot
| [Sunday 06 February 2011] [06:52:41] <Guthur>	I liked the E=mc2, hehe
| [Sunday 06 February 2011] [06:52:50] <pieterh>	It's a perspective I've used a few times in presentations, multithreading done wrong, and right
| [Sunday 06 February 2011] [06:53:31] <Guthur>	My team leader is pushing me to take that approach, the wrong way
| [Sunday 06 February 2011] [06:53:57] <pieterh>	It can be very hard to fight established ways of working...
| [Sunday 06 February 2011] [06:54:12] <Guthur>	I'm trying to convince him that multiple threads and global state without message passing is a problem waiting to happen
| [Sunday 06 February 2011] [06:54:27] <pieterh>	Well, it's a lot of pain and cost waiting to happen...
| [Sunday 06 February 2011] [06:54:39] <pieterh>	if the organization is large, it doesn't really care
| [Sunday 06 February 2011] [06:55:13] <pieterh>	But perhaps the argument that you can't stretch the results across multiple boxes may help
| [Sunday 06 February 2011] [06:55:42] <pieterh>	The best argument is usually running code
| [Sunday 06 February 2011] [06:56:20] <Guthur>	That's the thing I have it running with ZMQ, he's trying to argue against the dependency now
| [Sunday 06 February 2011] [06:56:50] <pieterh>	Hmm, what OS are you on?
| [Sunday 06 February 2011] [06:57:09] <Guthur>	windows, it's a .NET app
| [Sunday 06 February 2011] [06:57:23] <Guthur>	so he would rather it was nothing but .NET
| [Sunday 06 February 2011] [06:57:26] <pieterh>	Oh boy :-)
| [Sunday 06 February 2011] [06:57:39] <pieterh>	You can't argue logic with people who develop on Windows
| [Sunday 06 February 2011] [06:57:48] <Guthur>	hehe
| [Sunday 06 February 2011] [06:58:21] <pieterh>	I'm serious, they've swallowed the magic potion and believe in what they learn from MSDN
| [Sunday 06 February 2011] [06:58:35] <Guthur>	yeah it seems like that sometimes
| [Sunday 06 February 2011] [06:58:52] <pieterh>	And your organization has _no_ Linux?
| [Sunday 06 February 2011] [06:59:01] <Guthur>	oh yeah it has plenty
| [Sunday 06 February 2011] [06:59:10] <Guthur>	it's a very large American Bank
| [Sunday 06 February 2011] [06:59:17] <pieterh>	Oh boy
| [Sunday 06 February 2011] [06:59:53] <pieterh>	Well, performance maybe
| [Sunday 06 February 2011] [06:59:57] <Guthur>	Don't ask me the rationale for moving this app to windows, I still haven't got an answer to that
| [Sunday 06 February 2011] [07:00:08] <pieterh>	Banks don't use rationales
| [Sunday 06 February 2011] [07:00:39] <pieterh>	In my experience, anyhow, they often make IT choices based on egos and opinions
| [Sunday 06 February 2011] [07:00:55] <Guthur>	We are moving most client apps to windows (.NET), I can kind of see that as windows boxes are prevalent, but this app I am working on has windows through the whole stack
| [Sunday 06 February 2011] [07:01:01] <Guthur>	server included
| [Sunday 06 February 2011] [07:01:56] <pieterh>	So you can't use arguments like cost, portability, longeivity
| [Sunday 06 February 2011] [07:02:53] <Guthur>	no, but we do want scalability in our app, and there is many 'services' to talk to each other
| [Sunday 06 February 2011] [07:03:12] <pieterh>	So performance is one thing big egos are sensitive too
| [Sunday 06 February 2011] [07:03:28] <pieterh>	Especially if you can compare a pure .NET solution to other projects in the company
| [Sunday 06 February 2011] [07:03:36] <pieterh>	*sensitive to
| [Sunday 06 February 2011] [07:03:58] <pieterh>	If you can get a visible performance kick by using 0MQ, that's an argument that will fly IMO
| [Sunday 06 February 2011] [07:04:45] <Guthur>	I am hoping I can show that
| [Sunday 06 February 2011] [07:04:50] <Guthur>	and also with less code
| [Sunday 06 February 2011] [07:05:39] <pieterh>	Well, good luck and it'd be interesting to know how this plays out
| [Sunday 06 February 2011] [07:05:54] <Guthur>	cheers, yeah I hope I can win through
| [Sunday 06 February 2011] [07:06:08] <Guthur>	it's tiring fighting this mentality though
| [Sunday 06 February 2011] [07:06:46] <pieterh>	Personally, I'd look to change projects :-)
| [Sunday 06 February 2011] [07:06:57] <Guthur>	for the first time this week I started wanting to get a new job
| [Sunday 06 February 2011] [07:07:04] <Guthur>	hehe, yeah agree
| [Sunday 06 February 2011] [07:07:13] <Guthur>	this/last
| [Sunday 06 February 2011] [07:07:31] <pieterh>	It's not worth working with people who are mediocre, not worth working on projects that are mediocre
| [Sunday 06 February 2011] [07:07:44] <pieterh>	A terrible, tragic project... at least you learn a lot
| [Sunday 06 February 2011] [07:08:19] <Guthur>	maybe I will have more success next week
| [Sunday 06 February 2011] [07:08:33] <Guthur>	I have still to show the full working app
| [Sunday 06 February 2011] [07:08:41] <Guthur>	only got it ready on friday
| [Sunday 06 February 2011] [07:08:44] <pieterh>	I'd really focus purely on speed... nothing else
| [Sunday 06 February 2011] [07:09:22] <sustrik>	pieterh: the presentation should be definitely linked from zeromq.org
| [Sunday 06 February 2011] [07:09:35] <pieterh>	sustrik: the video or the slideshow?
| [Sunday 06 February 2011] [07:09:38] <sustrik>	video
| [Sunday 06 February 2011] [07:09:46] <Guthur>	I'd second that, its a good video
| [Sunday 06 February 2011] [07:10:06] <sustrik>	do they leave it on the site for a long time?
| [Sunday 06 February 2011] [07:10:11] <pieterh>	Guthur: especially if you can show an architecture that's hard to make with the pure .NET toolkit
| [Sunday 06 February 2011] [07:10:16] <pieterh>	sustrik: IMO it's there forever
| [Sunday 06 February 2011] [07:10:32] <sustrik>	then it should be easy to link...
| [Sunday 06 February 2011] [07:10:42] <pieterh>	I think it would be better to convert to youtube but I'm not sure how, will try on a Linux box
| [Sunday 06 February 2011] [07:11:10] <sustrik>	yes, it behaved kind of capricious
| [Sunday 06 February 2011] [07:11:19] <sustrik>	i was able to get it running after ~10 atemps
| [Sunday 06 February 2011] [07:11:24] <pieterh>	the HTML5/theora format is kind of strange
| [Sunday 06 February 2011] [07:12:02] <pieterh>	I'll give it a shot
| [Sunday 06 February 2011] [07:12:20] <pieterh>	I guess we already have a place on the wiki for this, i.e. the right hand side where we list the events
| [Sunday 06 February 2011] [07:12:30] <Guthur>	I had trouble accessing it with Chrome
| [Sunday 06 February 2011] [07:12:36] <Guthur>	worked on firefox though
| [Sunday 06 February 2011] [07:12:51] <sustrik>	i would say it will be valueable even after a year or so
| [Sunday 06 February 2011] [07:12:55] <pieterh>	Heh, from Slideshare, " "FOSDEM 2011 - 0MQ" is being tweeted more than anything else on SlideShare right now. So we've put it on the homepage of SlideShare.net (in the "Hot on Twitter" section)."
| [Sunday 06 February 2011] [07:13:04] <sustrik>	and the events list is going to rollover
| [Sunday 06 February 2011] [07:13:32] <sustrik>	something like "links" section, or "articles" or "media"
| [Sunday 06 February 2011] [07:13:54] <pieterh>	we can leave the events list to grow
| [Sunday 06 February 2011] [07:14:01] <pieterh>	eventually move it to its own page
| [Sunday 06 February 2011] [07:14:31] <pieterh>	makes sense that people use that list to find corresponding videos / slideshows
| [Sunday 06 February 2011] [07:15:04] <sustrik>	well, the problem is broader that that
| [Sunday 06 February 2011] [07:15:15] <sustrik>	for example, there are useful blogs out there
| [Sunday 06 February 2011] [07:15:17] <Guthur>	actually talking about performance of .NET vs ZMQ, I was testing a REQ/REP vs .NET remoting, both using TCP, and got some interesting results...
| [Sunday 06 February 2011] [07:15:23] <sustrik>	it's not clear where to link the from
| [Sunday 06 February 2011] [07:15:50] <pieterh>	sustrik:... Google kind of solves this problem, eventually
| [Sunday 06 February 2011] [07:16:01] <Guthur>	Up to about 100 requests ZMQ was faster or at least as performant, after that it started to fall behind remoting
| [Sunday 06 February 2011] [07:16:22] <pieterh>	I'm not sure collecting hundreds of links to articles and blogs makes sense
| [Sunday 06 February 2011] [07:16:29] <pieterh>	people want reusable material
| [Sunday 06 February 2011] [07:16:51] <Guthur>	I haven't investigated much further to identify the reasoning though, and my knowledge to inner works of remoting is limited
| [Sunday 06 February 2011] [07:16:57] <pieterh>	Guthur: interesting
| [Sunday 06 February 2011] [07:17:07] <pieterh>	0MQ on Windows is not optimized in any way
| [Sunday 06 February 2011] [07:17:22] <Guthur>	though I think remoting is now being replace by MS's new 'standard', WCF
| [Sunday 06 February 2011] [07:17:40] <pieterh>	aka WTF
| [Sunday 06 February 2011] [07:17:53] <Guthur>	are you familiar with it?
| [Sunday 06 February 2011] [07:17:58] <pieterh>	Nope... :-)
| [Sunday 06 February 2011] [07:18:01] <Guthur>	hehe
| [Sunday 06 February 2011] [07:18:19] <pieterh>	I maintain high levels of ignorance concerning anything coming from MSFT
| [Sunday 06 February 2011] [07:18:34] <Guthur>	nice for some, hehe
| [Sunday 06 February 2011] [07:19:27] <pieterh>	You know, what you might just do... is abandon the attempt to convert your team, which is most likely hopeless and will stress you
| [Sunday 06 February 2011] [07:19:57] <pieterh>	and instead take the opportunity to learn a lot about how WCF works, and then extend 0MQ to use that
| [Sunday 06 February 2011] [07:20:42] <sustrik>	pieterh: yes, i meant reusable links: your and oliver's video, nicolases' and ilya's articles etc.
| [Sunday 06 February 2011] [07:20:58] <Guthur>	unfortunately WCF only solves the interprocess connection
| [Sunday 06 February 2011] [07:21:14] <pieterh>	sustrik: we did collect the most valuable ones on the intro doc page, I think
| [Sunday 06 February 2011] [07:21:22] <Guthur>	there is nothing in .NET to solve inter thread, besides traditional thread mechanisms
| [Sunday 06 February 2011] [07:21:49] <pieterh>	well... i'm not against collecting resources but it does need upkeep
| [Sunday 06 February 2011] [07:22:11] <pieterh>	Guthur: right, and this is missing in 0MQ for Windows too
| [Sunday 06 February 2011] [07:23:09] <Guthur>	I wouldn't be surprised if WCF is .NET only, but I'm not 100% sure on that
| [Sunday 06 February 2011] [07:23:34] <Guthur>	Remoting was only intended for .NET endpoints
| [Sunday 06 February 2011] [07:27:27] <pieterh>	Let us know when you know :-)
| [Sunday 06 February 2011] [07:31:42] <sustrik>	why not link your talk from intro page then?
| [Sunday 06 February 2011] [07:40:10] <pieterh>	sustrik: could do... for now I've linked to it from the events list
| [Sunday 06 February 2011] [07:40:29] <pieterh>	let me try to convert that video first
| [Sunday 06 February 2011] [07:42:27] <sustrik>	sure
| [Sunday 06 February 2011] [07:42:56] <sustrik>	Guthur: getting slower after 100 messages -- isn't is just the queueing effect?
| [Sunday 06 February 2011] [07:43:18] <sustrik>	ie. publisher publishes faster than consumer consumes, thus making latencies gwo?
| [Sunday 06 February 2011] [07:43:20] <sustrik>	grow
| [Sunday 06 February 2011] [08:10:07] <Guthur>	sustrik, Possibly
| [Sunday 06 February 2011] [08:10:29] <Guthur>	if i remember right the majority of the time was in the Recv method
| [Sunday 06 February 2011] [08:11:01] <Guthur>	I have the code lying around somewhere, let me check
| [Sunday 06 February 2011] [08:38:13] <pieterh>	sustrik: I've uploaded to Youtube here: http://www.youtube.com/watch?v=CCBYzKfmQ4U
| [Sunday 06 February 2011] [08:38:17] <pieterh>	can you check if that works better?
| [Sunday 06 February 2011] [08:38:41] <sustrik>	yes
| [Sunday 06 February 2011] [08:38:48] <sustrik>	works with no problem
| [Sunday 06 February 2011] [08:40:24] <Guthur>	oh interesting, the tables turn drastically when I reuse the context/connection
| [Sunday 06 February 2011] [08:40:44] <Guthur>	OMQ starts to win hands down
| [Sunday 06 February 2011] [08:40:50] <Guthur>	0MQ
| [Sunday 06 February 2011] [08:42:22] <pieterh>	Guthur: you were opening a new connection each time?
| [Sunday 06 February 2011] [08:42:34] <Guthur>	I though it was fairer to remoting
| [Sunday 06 February 2011] [08:42:43] <pieterh>	huh
| [Sunday 06 February 2011] [08:42:58] <Guthur>	actually, there was another more important reason...
| [Sunday 06 February 2011] [08:43:23] <Guthur>	I was simulating a web application, which may not be able to reuse the connection
| [Sunday 06 February 2011] [08:43:31] <pieterh>	huh
| [Sunday 06 February 2011] [08:43:57] <pieterh>	you could add 'sleep(1)' into the main loop to properly simulate WCF
| [Sunday 06 February 2011] [08:44:38] <pieterh>	opening a socket each time is really slow
| [Sunday 06 February 2011] [08:45:07] <Guthur>	yep, I think remoting was probably keeping it's open in the background
| [Sunday 06 February 2011] [08:46:33] <Guthur>	but the target application was an IIS based web app, which would connect to a non IIS based process, and I was sure how well it would cope with persisting socket connections to external apps
| [Sunday 06 February 2011] [08:47:05] <pieterh>	is the target application performance critical?
| [Sunday 06 February 2011] [08:47:24] <Guthur>	we are hoping to ramp it up
| [Sunday 06 February 2011] [08:47:34] <Guthur>	its a FX Options trading app
| [Sunday 06 February 2011] [08:48:01] <Guthur>	so there could be lots of high frequency price movements
| [Sunday 06 February 2011] [08:48:04] <pieterh>	sure, so then you IMO want to make your 0MQ app as _fast_ as possible and use that as carrot
| [Sunday 06 February 2011] [08:48:24] <pieterh>	the stick would be to find a competing internal project and feed them juicy low latency technology
| [Sunday 06 February 2011] [08:48:44] <Guthur>	Well, reusing the context/connection, 0MQ is twice as fast
| [Sunday 06 February 2011] [08:49:11] <pieterh>	the code is in c#?
| [Sunday 06 February 2011] [08:49:16] <Guthur>	yeah
| [Sunday 06 February 2011] [08:49:46] <pieterh>	i'd probably make a C/Linux version just for sanity checking
| [Sunday 06 February 2011] [08:49:47] <Guthur>	though remoting does offer type safety
| [Sunday 06 February 2011] [08:50:24] <pieterh>	"safety" as in "ensure your types will never work on anything except our OS"
| [Sunday 06 February 2011] [08:50:33] <pieterh>	sustrik: OK, I've added the video to http://www.zeromq.org/intro:read-the-manual
| [Sunday 06 February 2011] [08:52:06] <Guthur>	getting them to accept 0MQ as the solution will be tough, getting them to dump .NET would be nigh on impossible
| [Sunday 06 February 2011] [08:52:38] <pieterh>	Guthur: oh, you'd just get blamed for the eventual failure
| [Sunday 06 February 2011] [08:52:54] <pieterh>	you have to leave technology evangelism to people outside the team
| [Sunday 06 February 2011] [08:54:13] <sustrik>	pieterh: thx
| [Sunday 06 February 2011] [08:54:39] <pieterh>	probably the best you can do is insert 0MQ as a "double the speed of this critical bus" solution
| [Sunday 06 February 2011] [08:54:57] <pieterh>	you would probably want to compare with another option too, to make it look fair
| [Sunday 06 February 2011] [08:55:09] <pieterh>	hmm, bank, hmm, for example RabbitMQ
| [Sunday 06 February 2011] [08:55:28] <pieterh>	and of course you need to make the architect think it was his idea all along
| [Sunday 06 February 2011] [08:55:59] <Guthur>	That's the thing the Team Lead is not really the architect, he is just too hands on
| [Sunday 06 February 2011] [08:56:06] <Guthur>	which is ok up to a point
| [Sunday 06 February 2011] [08:56:18] <pieterh>	well, s/architect/team lead/, it applies just the same
| [Sunday 06 February 2011] [08:56:21] <pieterh>	ego is ego
| [Sunday 06 February 2011] [09:49:28] <Guthur>	oops, i broke clrzmq2 build
| [Sunday 06 February 2011] [09:52:15] <Guthur>	I'll be pushing a fix promptly
| [Sunday 06 February 2011] [09:57:30] <Guthur>	is there no notification email when a build goes wrong?
| [Sunday 06 February 2011] [10:01:40] <sustrik>	Guthur: it's definitely possible
| [Sunday 06 February 2011] [10:02:00] <sustrik>	you have to ask mikko to add you to the list
| [Sunday 06 February 2011] [10:02:41] <Guthur>	I am one of the users registered, should I be receiving emails?
| [Sunday 06 February 2011] [10:02:41] <sustrik>	the auto builds are done once each 12hrs rather than immediately after commit btw
| [Sunday 06 February 2011] [10:02:57] <sustrik>	sorry, i am not a hudson expert
| [Sunday 06 February 2011] [10:03:01] <sustrik>	ask mikko
| [Sunday 06 February 2011] [10:03:08] <Guthur>	It is possible my over zealous email server is bouncing them
| [Sunday 06 February 2011] [10:03:43] <Guthur>	sustrik, do you receive mails?
| [Sunday 06 February 2011] [10:04:03] <sustrik>	nope, but i am not in the list afaik
| [Sunday 06 February 2011] [10:04:27] <Guthur>	ok
| [Sunday 06 February 2011] [10:04:36] <Guthur>	I can just monitor it after making a commit though
| [Sunday 06 February 2011] [10:04:55] <sustrik>	definitely
| [Sunday 06 February 2011] [10:05:09] <sustrik>	you have to wait till 5am or 5pm GMT though
| [Sunday 06 February 2011] [10:05:24] <sustrik>	that's when autoguilds are run
| [Sunday 06 February 2011] [10:05:34] <sustrik>	autobuilds*
| [Sunday 06 February 2011] [10:05:52] <Guthur>	ok, cheers
| [Sunday 06 February 2011] [10:57:32] <Guthur>	is Peter's video on the website yet?
| [Sunday 06 February 2011] [10:57:53] <Guthur>	oh sorry, found it
| [Sunday 06 February 2011] [10:58:03] <Guthur>	right in front of my eyes
| [Sunday 06 February 2011] [10:59:24] <Guthur>	would be really nice if it was on youtube or something though
| [Sunday 06 February 2011] [11:18:57] <Guthur>	I have multiple requests coming in, which will then make a further request to a service, this service will then reply back async on a separate thread, what is the appropriate 0MQ pattern to match the async response to the appropriate request thread?
| [Sunday 06 February 2011] [11:23:21] <sustrik>	req/rep
| [Sunday 06 February 2011] [11:24:31] <Guthur>	and match them using identity?
| [Sunday 06 February 2011] [11:25:11] <sustrik>	you don't have to care, rep socket does that for you
| [Sunday 06 February 2011] [11:28:18] <Guthur>	Either my understanding is wrong or it's bad problem description, because I can't see how that would work
| [Sunday 06 February 2011] [11:28:59] <sustrik>	rep sends the reply to the original requester
| [Sunday 06 February 2011] [11:29:13] <Guthur>	oh that part, yes
| [Sunday 06 February 2011] [11:29:31] <Guthur>	but its the async request from the service, it's not 0MQ
| [Sunday 06 February 2011] [11:29:44] <Guthur>	it's quickFIX to be precise
| [Sunday 06 February 2011] [11:29:55] <sustrik>	right
| [Sunday 06 February 2011] [11:30:29] <sustrik>	is there a reply-to field in the FIX message
| [Sunday 06 February 2011] [11:30:30] <sustrik>	?
| [Sunday 06 February 2011] [11:30:40] <Guthur>	and the reply will come back on a completely separate thread
| [Sunday 06 February 2011] [11:30:52] <Guthur>	there is reqID
| [Sunday 06 February 2011] [11:30:54] <Guthur>	that's it
| [Sunday 06 February 2011] [11:31:21] <sustrik>	who's behind the fix connection?
| [Sunday 06 February 2011] [11:31:24] <sustrik>	requester?
| [Sunday 06 February 2011] [11:31:26] <sustrik>	or replier?
| [Sunday 06 February 2011] [11:31:35] <Guthur>	replier
| [Sunday 06 February 2011] [11:31:45] <Guthur>	we are making Quote Requests
| [Sunday 06 February 2011] [11:31:53] <sustrik>	sure
| [Sunday 06 February 2011] [11:32:07] <sustrik>	reqID is an opaque correlation ID?
| [Sunday 06 February 2011] [11:32:54] <Guthur>	sorry,  opaque correlation?
| [Sunday 06 February 2011] [11:33:10] <sustrik>	i.e. is it an ID used to pair the request and the reply?
| [Sunday 06 February 2011] [11:33:28] <sustrik>	opaque = can you put anything into ReqID?
| [Sunday 06 February 2011] [11:33:41] <sustrik>	or is it restricted to UUIDs or somesuch
| [Sunday 06 February 2011] [11:33:55] <Guthur>	we can place anything
| [Sunday 06 February 2011] [11:34:07] <Guthur>	and yes it matches request and reply
| [Sunday 06 February 2011] [11:34:35] <sustrik>	then what you have to do at FIX/0MQ boundary
| [Sunday 06 February 2011] [11:34:54] <sustrik>	is to get all the address message parts from 0mq request
| [Sunday 06 February 2011] [11:35:01] <sustrik>	and put them into FIX ReqID
| [Sunday 06 February 2011] [11:35:08] <sustrik>	when the reply arrives
| [Sunday 06 February 2011] [11:35:31] <sustrik>	you get all the message parts from thr ReqID
| [Sunday 06 February 2011] [11:35:55] <sustrik>	that would guarantee that the reply gets to the original requester
| [Sunday 06 February 2011] [11:36:29] <Guthur>	yeah that sounds like a nice way
| [Sunday 06 February 2011] [11:38:00] <Guthur>	cheers, my initial vision had an intermediary hop
| [Sunday 06 February 2011] [11:38:13] <mikey_w>	As a newbee is there a document that explains zeromq?
| [Sunday 06 February 2011] [11:38:26] <Guthur>	I never thought about trying to reply directly to the Req Socket
| [Sunday 06 February 2011] [11:38:29] <Guthur>	cheers sustrik 
| [Sunday 06 February 2011] [11:38:45] <Guthur>	mikey_w, the guide, http://zguide.zeromq.org/chapter:all
| [Sunday 06 February 2011] [11:38:48] <sustrik>	what it is actually, is a 0mq-FIX bridge
| [Sunday 06 February 2011] [11:38:54] <mikey_w>	TU
| [Sunday 06 February 2011] [11:39:29] <sustrik>	so it's actually pretty generic and useful
| [Sunday 06 February 2011] [11:39:38] <sustrik>	think of making it an opensource
| [Sunday 06 February 2011] [11:40:52] <Guthur>	sustrik, Sure
| [Sunday 06 February 2011] [11:41:56] <Guthur>	that solution just might make all the complexity completely disappear, awesome
| [Sunday 06 February 2011] [12:17:56] <mikko>	good evening
| [Sunday 06 February 2011] [12:19:08] <mikko>	pieterh: how was fosdem?
| [Sunday 06 February 2011] [12:19:14] <pieterh>	hi mikko
| [Sunday 06 February 2011] [12:19:18] <pieterh>	short and sweet
| [Sunday 06 February 2011] [12:19:28] <pieterh>	there's a thread on hackernews: http://news.ycombinator.com/item?id=2185418
| [Sunday 06 February 2011] [12:20:22] <pieterh>	There's a video here: http://www.youtube.com/watch?v=CCBYzKfmQ4U
| [Sunday 06 February 2011] [12:20:45] <pieterh>	I think I successfully annoyed and intrigued various people :-)
| [Sunday 06 February 2011] [12:21:59] <pieterh>	anyone here interested in a command-line API for 0MQ?
| [Sunday 06 February 2011] [12:22:52] <mikko>	what do you mean by command line api?
| [Sunday 06 February 2011] [12:23:54] <pieterh>	export CONTEXT=`zmq context`
| [Sunday 06 February 2011] [12:24:09] <pieterh>	export SUBSOCK=`zmq socket $CONTEXT`
| [Sunday 06 February 2011] [12:24:21] <pieterh>	zmq connect $SUBSOCK randomaddress
| [Sunday 06 February 2011] [12:24:27] <pieterh>	etc.
| [Sunday 06 February 2011] [12:24:42] <pieterh>	I just had a rough idea of how to make it
| [Sunday 06 February 2011] [12:24:49] <pieterh>	could be fun for demos, especially
| [Sunday 06 February 2011] [12:25:00] <mikko>	i saw one guy making a small utility that reads from stdin and publishes that
| [Sunday 06 February 2011] [12:25:13] <mikko>	apart from that haven't seen much direct command line interaction
| [Sunday 06 February 2011] [12:25:23] <pieterh>	could it be useful?
| [Sunday 06 February 2011] [12:25:56] <mikko>	personally i dont see the immediate use-case but might be for some people
| [Sunday 06 February 2011] [12:26:27] <pieterh>	hmm, a resounding shrug, then :-)
| [Sunday 06 February 2011] [12:26:52] <Guthur>	hehe, of course Lisp would make such demos easy
| [Sunday 06 February 2011] [12:27:00] <Guthur>	the joys of having a REPL
| [Sunday 06 February 2011] [12:27:22] <pieterh>	problem with _any_ language is as soon as you go there you've lost 70% of your general audience
| [Sunday 06 February 2011] [12:28:00] <Guthur>	a REPL is such a cool feature I'm amazed more languages/environments don't offer it
| [Sunday 06 February 2011] [12:28:09] <Guthur>	i so miss having it
| [Sunday 06 February 2011] [12:29:07] <pieterh>	Read-Eval-Print loop, ok, right
| [Sunday 06 February 2011] [12:29:20] <pieterh>	Perl has it, and indeed it's useful
| [Sunday 06 February 2011] [12:29:43] <Guthur>	in Perl case the language completely negates any usefulness, hehe
| [Sunday 06 February 2011] [12:30:19] <pieterh>	Spoken like a true language bigot :-)
| [Sunday 06 February 2011] [12:30:28] <Guthur>	indeed, hehe
| [Sunday 06 February 2011] [12:33:01] <Guthur>	Interesting aside,
| [Sunday 06 February 2011] [12:33:03] <Guthur>	oops
| [Sunday 06 February 2011] [12:33:56] <Guthur>	what i meant to say was: an interesting side note is that Unix initially was suppose to come with a Lisp 
| [Sunday 06 February 2011] [12:34:46] <Guthur>	C for the Kernel, Lisp for some sort of shell, I believe 
| [Sunday 06 February 2011] [12:34:59] <pieterh>	hmm
| [Sunday 06 February 2011] [12:35:08] <Guthur>	Not Unix actually, GNU OS
| [Sunday 06 February 2011] [12:35:30] <pieterh>	ah, for sure, GNU OS had lots of weird and wonderful ideas :-)
| [Sunday 06 February 2011] [12:35:49] <Guthur>	Stallman like lisp obvious, look at Emacs
| [Sunday 06 February 2011] [12:37:25] <pieterh>	Lisp comes from MIT, where Stallman learned to hack
| [Sunday 06 February 2011] [17:42:52] <devon_hillard>	Is it correct to describe zeroMQ as a message-passing architecture?
| [Sunday 06 February 2011] [18:16:58] <Guthur>	I think i would go more with 'allows for a message passing architecture'
| [Sunday 06 February 2011] [19:00:43] <Guthur>	what happens if you are polling and then subsequently close the socket?
| [Sunday 06 February 2011] [20:27:27] <Guthur>	mikko, the build server is dead?
| [Sunday 06 February 2011] [23:39:19] <kabs>	Hello, if subscriber in pub-sub model goes down or restart we have the option to queue its data at publisher side by using HWM or SWAP but how can we make sure our system doesn't fail if publisher goes down?
| [Monday 07 February 2011] [00:03:52] <jhawk28>	kabs, you have to persist the data in your program
| [Monday 07 February 2011] [00:04:12] <jhawk28>	and determine what is acceptable for restarts
| [Monday 07 February 2011] [00:04:23] <jhawk28>	is it ok to send data to the subscriber again
| [Monday 07 February 2011] [00:06:02] <kabs>	Not sure as of now but I am looking for the options
| [Monday 07 February 2011] [00:07:24] <jhawk28>	if you need strong durability, and are not concerned so much with performance, AMQP may be a better fit
| [Monday 07 February 2011] [00:08:20] <jhawk28>	https://github.com/rabbitmq/rmq-0mq
| [Monday 07 February 2011] [00:09:03] <kabs>	jhawk28:Can you elaborate on data persistence here, since if pub is crashed all it's buffers( I/O, network buffers ) will be gone, how can we have persistence of those buffers ??
| [Monday 07 February 2011] [00:09:55] <jhawk28>	it would be external to the ZMQ library
| [Monday 07 February 2011] [00:10:08] <jhawk28>	in the application space
| [Monday 07 February 2011] [00:11:54] <jhawk28>	so you could just log data as it was published
| [Monday 07 February 2011] [00:12:20] <jhawk28>	then when the publisher was restarted, it would just replay the log
| [Monday 07 February 2011] [00:13:23] <jhawk28>	you could sequence it and use a periodic ack using a pull socket to know how far back, but then you need to keep track of acks for all subscribers (which slows performance)
| [Monday 07 February 2011] [00:14:23] <jhawk28>	it creates durability, but has a penalty for performance in addition to breaking the desired contract of sending a message once and only once
| [Monday 07 February 2011] [00:16:04] <kabs>	jhawk28: it seems there is no ideal system, some system has some penalty , etc ...
| [Monday 07 February 2011] [00:16:39] <jhawk28>	correct. durable pub is hard
| [Monday 07 February 2011] [00:16:53] <kabs>	jhawk28: so this pull and ack is to maintain identity
| [Monday 07 February 2011] [00:17:22] <jhawk28>	http://sna-projects.com/kafka/ is a full blown system just for it
| [Monday 07 February 2011] [00:17:35] <jhawk28>	you can get ideas from http://sna-projects.com/kafka/design.php
| [Monday 07 February 2011] [00:20:26] <kabs>	jhawk28: thank you for your input, will see it , just gave it a glance and found one beautiful line "Don't fear the filesystem!"   :)
| [Monday 07 February 2011] [04:37:01] <ianbarber>	hi all, anyone got any PGM ideas about this assertion: 
| [Monday 07 February 2011] [04:37:02] <ianbarber>	Assertion failed: rc == 0 (connect_session.cpp:82)
| [Monday 07 February 2011] [04:37:18] <ianbarber>	from a zmq_connect (pub, "epgm://;239.192.0.1:7601");
| [Monday 07 February 2011] [04:38:28] <ianbarber>	as far as I can see it's being thrown due to a failure in pgm_socket.cpp, possible if (!pgm_setsockopt (sock, IPPROTO_PGM, PGM_SEND_ONLY,
| [Monday 07 February 2011] [04:38:28] <ianbarber>	                &send_only, sizeof (send_only))
| [Monday 07 February 2011] [04:38:32] <ianbarber>	due to that
| [Monday 07 February 2011] [04:40:00] <guido_g>	you dont't specify an interface, check that the loopback is *not* used
| [Monday 07 February 2011] [04:40:22] <guido_g>	loopback is nit multicast capable
| [Monday 07 February 2011] [04:41:13] <guido_g>	s/nit/not/
| [Monday 07 February 2011] [04:43:32] <ianbarber>	ah, good point. just tried with eth0, same result
| [Monday 07 February 2011] [04:44:03] <ianbarber>	is there a way of telling whether the interface is capable, or enable/disabling it? i am on a VMWare VM, so it is entirely possible there is something odd about the network interface
| [Monday 07 February 2011] [04:44:17] <guido_g>	ifconfig should tell
| [Monday 07 February 2011] [04:44:56] <ianbarber>	yeah, MULTICAST is in there
| [Monday 07 February 2011] [04:44:57] <ianbarber>	hmm
| [Monday 07 February 2011] [04:46:54] <ianbarber>	i get the same thing with PGM as well as epgm (not massively suprisingly I'm sure)
| [Monday 07 February 2011] [04:56:31] <mikko>	ianbarber: increase ZMQ_RATE
| [Monday 07 February 2011] [04:56:36] <mikko>	seems to fix the symptoms
| [Monday 07 February 2011] [04:56:47] <mikko>	not sure what the actual issue is
| [Monday 07 February 2011] [04:58:52] <ianbarber>	ah, right, let me try that
| [Monday 07 February 2011] [04:58:57] <ianbarber>	what's rate default to then? 
| [Monday 07 February 2011] [04:59:45] <guido_g>	100kbit i think
| [Monday 07 February 2011] [05:01:53] <suzan_shakya>	Hi all, is there any method for listening on 2 sockets other than zmq.Poller()
| [Monday 07 February 2011] [05:02:08] <ianbarber>	awesome, that seemed to work (once I remember to define it as an int64_t rather than an int)
| [Monday 07 February 2011] [05:02:13] <ianbarber>	thanks mikko!
| [Monday 07 February 2011] [05:03:51] <ianbarber>	(and thanks guido for the help as well :))
| [Monday 07 February 2011] [05:15:57] <sustrik>	ianbarber: can you report the problem on the mailing list so that steve-o can have a look at it?
| [Monday 07 February 2011] [05:16:30] <sustrik>	suzan_shakya: you mean two 0mq sockets or two peers?
| [Monday 07 February 2011] [05:17:28] <ianbarber>	sustrik: sure thing
| [Monday 07 February 2011] [05:22:45] <mikko>	http://build.valokuva.org/job/ZeroMQ2-core-master-GCC-linux_s390x/11/console
| [Monday 07 February 2011] [05:22:50] <mikko>	s390x building
| [Monday 07 February 2011] [05:23:24] <mikko>	and fails
| [Monday 07 February 2011] [05:25:55] <ianbarber>	oh, cool that that's on the build system, even if it is failing :)
| [Monday 07 February 2011] [05:26:44] <sustrik>	the best thing is that's it proves that distributed build system is doable :)
| [Monday 07 February 2011] [05:27:07] <sustrik>	configure.in:9: error: possibly undefined macro: m4_esyscmd_s
| [Monday 07 February 2011] [05:27:23] <mikko>	yeah, just trying to figure out what system it is
| [Monday 07 February 2011] [05:27:28] <mikko>	might very well be a RHEL
| [Monday 07 February 2011] [05:27:31] <sustrik>	 that's the last patch that was made to the build system
| [Monday 07 February 2011] [05:27:37] <mikko>	yes
| [Monday 07 February 2011] [05:27:54] <mikko>	m4_esyscmd_s is present in autoconf 2.61
| [Monday 07 February 2011] [05:28:00] <mikko>	which is the minimum requirement
| [Monday 07 February 2011] [05:28:08] <mikko>	not sure what version that system runs
| [Monday 07 February 2011] [05:28:38] <sustrik>	aha
| [Monday 07 February 2011] [05:28:49] <mikko>	encouraging, no google results for "possibly undefined macro: m4_esyscmd_s"
| [Monday 07 February 2011] [05:30:23] <mikko>	works in 2.68 autoconf
| [Monday 07 February 2011] [05:30:31] <mikko>	that system runs 2.63
| [Monday 07 February 2011] [05:30:35] <mikko>	very strange
| [Monday 07 February 2011] [05:33:00] <mikko>	hmm, sustrik i think it's better to revert the patch
| [Monday 07 February 2011] [05:33:24] <jugg>	:(
| [Monday 07 February 2011] [05:33:42] <sustrik>	jugg: what was the problem it solved?
| [Monday 07 February 2011] [05:33:53] <mikko>	i think the behaviour of m4_esyscmd_s is a lot more inconsistent over different platofrms
| [Monday 07 February 2011] [05:34:05] <jugg>	debian 6 systems failing
| [Monday 07 February 2011] [05:34:14] <mikko>	jugg: does it fail or warn?
| [Monday 07 February 2011] [05:34:47] <mikko>	if it fails then we need to put more attention to this
| [Monday 07 February 2011] [05:35:05] <mikko>	(the daily build cluster master is debian 6.0)
| [Monday 07 February 2011] [05:35:15] <sustrik>	configure.in:9: warning: AC_INIT: not a literal: m4_esyscmd([./version.sh | tr -
| [Monday 07 February 2011] [05:35:15] <sustrik>	d '\n'])
| [Monday 07 February 2011] [05:35:35] <jugg>	looks like a warning, I'm not sure if ./configure works after, I did not try.
| [Monday 07 February 2011] [05:35:42] <jugg>	yes, what sustrik said
| [Monday 07 February 2011] [05:36:03] <sustrik>	jugg: can you check whether the package builds ok in spite of the warning?
| [Monday 07 February 2011] [05:36:21] <jugg>	one moment...
| [Monday 07 February 2011] [05:36:48] <mikko>	m4_esyscmd_s seems to present on all platforms which had daily builds but not on the new s390x
| [Monday 07 February 2011] [05:38:01] <mikko>	another option would be to use 'echo -n' instead of 'echo' in version.sh and revert to m4_esyscmd
| [Monday 07 February 2011] [05:38:28] 	 * sustrik has no idea what's going on there; it's up to you
| [Monday 07 February 2011] [05:42:33] <jugg>	everything seems to build fine without that fix
| [Monday 07 February 2011] [05:43:14] <jugg>	without the fix, ./autogen.sh produces that warning 6 times.
| [Monday 07 February 2011] [05:44:35] <mikko>	jugg: what about AC_INIT([zeromq],[m4_esyscmd([./version.sh])],[zeromq-dev@lists.zeromq.org])
| [Monday 07 February 2011] [05:44:45] <mikko>	and change version.sh to use 'echo -n ' at the end
| [Monday 07 February 2011] [05:46:06] <mikko>	echo -n is not portable
| [Monday 07 February 2011] [05:47:57] <jugg>	it worked however...
| [Monday 07 February 2011] [05:50:22] <mikko>	bash shell most probably
| [Monday 07 February 2011] [05:50:28] <mikko>	ksh:
| [Monday 07 February 2011] [05:50:29] <mikko>	$ echo -n hi
| [Monday 07 February 2011] [05:50:29] <mikko>	-n hi
| [Monday 07 February 2011] [05:53:59] <mikko>	hmm, what about if we moved the tr -d '\n' to the version.sh 
| [Monday 07 February 2011] [05:54:05] <mikko>	that should be as portable as the old way
| [Monday 07 February 2011] [05:56:57] <mikko>	jugg: https://gist.github.com/35b8a685a38c0e4a92c5
| [Monday 07 February 2011] [05:56:59] <mikko>	can you test that?
| [Monday 07 February 2011] [06:01:33] <jugg>	works
| [Monday 07 February 2011] [06:07:53] <mikko>	works on s390 as well
| [Monday 07 February 2011] [06:17:28] <mikko>	what on earth
| [Monday 07 February 2011] [06:17:29] <mikko>	"conftest.c:15: error: 'Syntax' does not name a type
| [Monday 07 February 2011] [07:14:22] <sustrik>	mikko: should i apply the patch or not?
| [Monday 07 February 2011] [08:01:02] <kristsk>	hello there.
| [Monday 07 February 2011] [08:01:46] <kristsk>	is it posssible to send FDs (file descriptors) around with zeromq - if processes reside in same box?
| [Monday 07 February 2011] [08:10:52] <sustrik>	FDs are process-specific
| [Monday 07 February 2011] [08:11:05] <sustrik>	no way of passing them between processes
| [Monday 07 February 2011] [08:33:40] <kristsk>	sustrik - there is a way.
| [Monday 07 February 2011] [08:34:15] <sustrik>	?
| [Monday 07 February 2011] [08:35:28] <kristsk>	https://github.com/pgte/fugue/wiki/How-Fugue-Works
| [Monday 07 February 2011] [08:35:47] <kristsk>	2. Master socket - ...
| [Monday 07 February 2011] [08:37:08] <sustrik>	right
| [Monday 07 February 2011] [08:37:13] <sustrik>	i almost forgot about that
| [Monday 07 February 2011] [08:37:34] <kristsk>	i am looking into zeromq as it has some nice features (queues, pairs), but im not sure i want to keep 2 separate subsystems for sharing data among processes
| [Monday 07 February 2011] [08:37:35] <sustrik>	anyway, it doesn't scale, so no such thing with 0mq
| [Monday 07 February 2011] [08:37:47] <kristsk>	even with local transport ?
| [Monday 07 February 2011] [08:38:18] <sustrik>	the point is that the code written for multiple threads can be scaled to multiple processes or boxes
| [Monday 07 February 2011] [08:38:31] <sustrik>	once you start passing FDs around, you break the scalability
| [Monday 07 February 2011] [08:39:25] <kristsk>	too bad :/
| [Monday 07 February 2011] [08:39:45] <stockMQ>	Hi .. where can i find documentation for Forwarder and Streamer.. I am working on VC++
| [Monday 07 February 2011] [08:49:38] <stockMQ>	All i found was this 
| [Monday 07 February 2011] [08:49:38] <stockMQ>	http://api.zeromq.org/zmq_forwarder.html
| [Monday 07 February 2011] [09:01:58] <mikko>	sustrik: yes, please
| [Monday 07 February 2011] [09:02:45] <mikko>	it should work on all of the daily build platforms after that
| [Monday 07 February 2011] [09:03:11] <mikko>	well, all platforms
| [Monday 07 February 2011] [09:07:47] <CIA-21>	zeromq2: 03Mikko Koppanen 07master * r908b39b 10/ (configure.in version.sh): 
| [Monday 07 February 2011] [09:07:47] <CIA-21>	zeromq2: m4_esyscmd_s doesnt seem to be portable across different systems
| [Monday 07 February 2011] [09:07:47] <CIA-21>	zeromq2: Signed-off-by: Mikko Koppanen <mikko.koppanen@gmail.com> - http://bit.ly/fCd8BW
| [Monday 07 February 2011] [09:08:00] <mikko>	thanks
| [Monday 07 February 2011] [09:08:24] <mikko>	hmm, so now we have proved that remote build slaves can work
| [Monday 07 February 2011] [09:08:43] <sustrik>	yes
| [Monday 07 February 2011] [09:09:05] <sustrik>	the question now is whether we can get more people to maintain slaves
| [Monday 07 February 2011] [09:09:22] <mikko>	yes, sparc would be nice. possibly hp-ux, aix etc
| [Monday 07 February 2011] [09:09:48] <sustrik>	you should maybe write an email about the new feature, so that people know there's such an option
| [Monday 07 February 2011] [09:14:04] <zchrish>	Has anyone tried to compile zeromq on mingw; I want to use zeromq with Qt.
| [Monday 07 February 2011] [09:15:09] <sustrik>	i recall there's a 0mq/qt project on labs page
| [Monday 07 February 2011] [09:16:15] <sustrik>	http://labs.wordtothewise.com/zeromqt/
| [Monday 07 February 2011] [09:17:02] <zchrish>	Oh, sorry. I meant compiling zeromq on Windows using mingw.
| [Monday 07 February 2011] [09:18:33] <mikko>	zchrish: yes
| [Monday 07 February 2011] [09:18:50] <mikko>	http://build.valokuva.org/job/ZeroMQ2-core-master_mingw32-win7/
| [Monday 07 February 2011] [09:18:58] <zchrish>	Oh, great. Thanks.
| [Monday 07 February 2011] [09:19:08] <mikko>	http://snapshot.valokuva.org/
| [Monday 07 February 2011] [09:19:15] <mikko>	you can also get a snapshot from there
| [Monday 07 February 2011] [09:20:43] <ianbarber>	mikko: are there any plans to do rpm and deb builds as part of your build empire at any point? 
| [Monday 07 February 2011] [09:21:25] <ianbarber>	it seems like you have to run the make dist (i guess?) to generate the spec files etc. properly, so it seems build-y 
| [Monday 07 February 2011] [09:21:44] <mikko>	yes, debian would be easy as the build master is debian
| [Monday 07 February 2011] [09:21:54] <mikko>	rpm would require setting up centos/rhel build slave
| [Monday 07 February 2011] [09:22:47] <ianbarber>	really? i mean, you could run rpmbuild on debian ok
| [Monday 07 February 2011] [09:24:07] <mikko>	the dependencies don't come out correctly
| [Monday 07 February 2011] [09:24:09] <ianbarber>	i guess the only difficulty would be rpmbuild complaining about build dependencies on compile, but you should be able to force ignore that, as the build reqs will be there
| [Monday 07 February 2011] [09:24:34] <mikko>	thats not a problem
| [Monday 07 February 2011] [09:24:39] <mikko>	the problem is run-time deps
| [Monday 07 February 2011] [09:25:32] <ianbarber>	verifying them, or an actual problem during the build?
| [Monday 07 February 2011] [09:26:56] <ianbarber>	probably easiest to have the actual centos env though i guess
| [Monday 07 February 2011] [09:28:09] <mikko>	if you build on debian you depend on the libraries present on the host system
| [Monday 07 February 2011] [09:28:19] <mikko>	which are more than likely not present in RHEL/Centos
| [Monday 07 February 2011] [09:28:40] <mikko>	also library versions you link against etc
| [Monday 07 February 2011] [09:29:04] <ianbarber>	oh, i get it. yeah, that's a pain. could build the SRPMS automatically, but yeah, would be easier to have a sep slave
| [Monday 07 February 2011] [09:31:42] <sustrik>	still, the idea of building packages on remote boxes is quite nice
| [Monday 07 February 2011] [09:32:23] <sustrik>	anyone who wants to have fresh packages available could volunteer to run the build on his box
| [Monday 07 February 2011] [09:32:52] <sustrik>	this way we could get quite a nice coverage of different CPUs/OSes
| [Monday 07 February 2011] [09:32:56] <kristsk>	how bout vms ?
| [Monday 07 February 2011] [09:33:09] <sustrik>	are you running vms?
| [Monday 07 February 2011] [09:33:26] <sustrik>	vms is a problem as it's not an unix
| [Monday 07 February 2011] [09:33:28] <kristsk>	uh huh, i ment, VM's not VMS
| [Monday 07 February 2011] [09:33:55] <sustrik>	can you simulate a different CPU in a VM?
| [Monday 07 February 2011] [09:34:13] <kristsk>	probably not :/
| [Monday 07 February 2011] [09:36:58] <Guthur>	talking about builds...I went and broke the clrzmq2 build again...
| [Monday 07 February 2011] [09:37:12] <Guthur>	Visual Studios Solutions are really beginning to bug me
| [Monday 07 February 2011] [09:39:42] <sustrik>	heh
| [Monday 07 February 2011] [09:40:40] <mikko>	Guthur: why dont you use msbuild?
| [Monday 07 February 2011] [09:40:55] <mikko>	kristsk: we are running different operating systems in VMs
| [Monday 07 February 2011] [09:41:13] <Guthur>	mikko: you know I asked myself the same question this morning, hehe
| [Monday 07 February 2011] [09:41:14] <mikko>	kristsk: linux, windows, solaris, freebsd but they are all x86
| [Monday 07 February 2011] [09:41:45] <kristsk>	yeah but sparcish things prolly wont run in vm on x86
| [Monday 07 February 2011] [09:41:47] <Guthur>	mikko: but I do want to make sure that clrzmq2 can be used easily from MSVS
| [Monday 07 February 2011] [09:42:17] <mikko>	not sure if qemu can emulate processors
| [Monday 07 February 2011] [09:42:33] <Guthur>	clrzmq2 will experience more resistance if it doesn't work well from visual studio
| [Monday 07 February 2011] [09:42:46] <Guthur>	IMO
| [Monday 07 February 2011] [09:46:48] <sustrik>	Guthur: +1
| [Monday 07 February 2011] [09:48:45] <mikko>	hi neale1 
| [Monday 07 February 2011] [09:49:01] <mikko>	everything seems to be up and running and the latest rounds of builds succeeded
| [Monday 07 February 2011] [09:50:29] <neale1>	Hi Mikko. Yes, we're building on bigger processor than my little emulator box. It's about 3 models older than the current generation. It's on a system with 700 virtual machines so it's being constrained so it "plays well with others". But 7 mins is pretty good turnaround. 
| [Monday 07 February 2011] [09:50:58] <mikko>	neale1: yeah, definitely. thanks for your hard work
| [Monday 07 February 2011] [09:51:08] <neale1>	No worries
| [Monday 07 February 2011] [09:51:15] <mikko>	i'll send an email out today that mentions the new system z build machine if you don't mind?
| [Monday 07 February 2011] [09:51:25] <neale1>	Sure
| [Monday 07 February 2011] [09:52:07] <neale1>	The machine it's running on is part of IBM's OSDL facility running at Marist College in mid-state new York.
| [Monday 07 February 2011] [09:52:35] <neale1>	I'm the s390x maintainer of mono so that's where I do my builds for it
| [Monday 07 February 2011] [10:05:12] <sustrik>	hm, the people/organizations who participate in build system should be mentioned somewhere so that they get the credit...
| [Monday 07 February 2011] [10:12:32] <ianbarber>	with pub/sub, you can have multiple subs connected to a pub, multiple pubs connected to a sub, but not multiple pubs connected to multiple subs right? does that include multicast transports?
| [Monday 07 February 2011] [10:13:53] <mikko>	stutter: i need to create a wiki page detailing the build system
| [Monday 07 February 2011] [10:14:01] <sustrik>	multicast treats the netowrk swtich (hardware) as a device
| [Monday 07 February 2011] [10:14:02] <mikko>	and organisations / people who participate in it
| [Monday 07 February 2011] [10:14:15] <stutter>	mikko: did you mean to tab-complete someone else/
| [Monday 07 February 2011] [10:14:23] <mikko>	yes
| [Monday 07 February 2011] [10:14:26] <stutter>	:P
| [Monday 07 February 2011] [10:14:28] <mikko>	i meant to tab complete sustrik 
| [Monday 07 February 2011] [10:14:32] <stutter>	i figured
| [Monday 07 February 2011] [10:14:33] <mikko>	sorry about that
| [Monday 07 February 2011] [10:14:45] <sustrik>	mikko: ok
| [Monday 07 February 2011] [10:14:57] <mikko>	ill try to have time today, ill put a reminder
| [Monday 07 February 2011] [10:15:13] <sustrik>	ianbarber: so both pubs and subs "connect" to the switch
| [Monday 07 February 2011] [10:15:25] <sustrik>	which then forwards any message from any pub to all subs
| [Monday 07 February 2011] [10:15:44] <ianbarber>	that makes sense, thanks
| [Monday 07 February 2011] [10:16:03] <mikko>	now when i look at ian's message about openpgm i think steven sent me an email about it
| [Monday 07 February 2011] [10:16:09] <mikko>	didnt have time to look further
| [Monday 07 February 2011] [10:16:21] <sustrik>	mikko: nice, i think if we made it reasonably visible we can get more participants
| [Monday 07 February 2011] [10:16:36] <mikko>	"Building ZeroMQ I finally get through to the same assertion, and wondering through the code I find the window size is being calculated with options.rate in bytes not kilobytes.  So add a  1024 for both rxw_sqns and txw_sqns."
| [Monday 07 February 2011] [10:16:45] <mikko>	was the relevant part from his email
| [Monday 07 February 2011] [10:17:15] <mikko>	but adding 1024 x didn't solve the issue for me and didn't really have time to look it further
| [Monday 07 February 2011] [10:17:51] <sustrik>	i tried to debug it, but here is seemed that setting the port have failed rather than rate...
| [Monday 07 February 2011] [10:17:52] <sustrik>	strange
| [Monday 07 February 2011] [10:22:42] <ianbarber>	mikko: there is a comment to that effects,     //  Data rate is in [B/s]. options.rate is in [kb/s].
| [Monday 07 February 2011] [10:23:01] <ianbarber>	and it is possible I was hitting the assert due to failing pgm_setsockopt (sock, IPPROTO_PGM, PGM_TXW_SQNS,
| [Monday 07 February 2011] [10:23:02] <ianbarber>	                &txw_sqns, sizeof (txw_sqns))
| [Monday 07 February 2011] [10:28:30] <ianbarber>	yep, that's it
| [Monday 07 February 2011] [10:28:46] <ianbarber>	if txw_sqns is 0, it asserts
| [Monday 07 February 2011] [10:30:33] <ianbarber>	pmg_max_tpdu is 1500
| [Monday 07 February 2011] [10:30:57] <ianbarber>	the sqns is options.recovery_ivl * options.rate /
| [Monday 07 February 2011] [10:30:57] <ianbarber>	                                      txw_max_tpdu
| [Monday 07 February 2011] [10:31:05] <ianbarber>	and recovery_ivl defaults to 10
| [Monday 07 February 2011] [10:31:22] <ianbarber>	so at 149 or below, it comes out as int 0
| [Monday 07 February 2011] [10:31:25] <ianbarber>	which blows up
| [Monday 07 February 2011] [10:31:44] <ianbarber>	so i think that for this calculation options.rate should be multiplied by 1024
| [Monday 07 February 2011] [10:32:03] <ianbarber>	or zmq:txw_max_tpdu appropriately reduced, but that seems more likely to have knock ons
| [Monday 07 February 2011] [10:33:15] <Guthur>	is there documentation of ZeroMQs underlying architecture, or is it just the source code?
| [Monday 07 February 2011] [10:38:04] <sustrik>	ianbarber: that's useful
| [Monday 07 February 2011] [10:38:14] <sustrik>	let me see whether it can be fixed
| [Monday 07 February 2011] [10:38:26] <ianbarber>	just tested a multiplying it by 1024 and it works fine
| [Monday 07 February 2011] [10:38:40] <ianbarber>	i can send a patch if useful (it's like 4 lines, so maybe not worth it)
| [Monday 07 February 2011] [10:39:04] <sustrik>	you mean patch that mutliples the value?
| [Monday 07 February 2011] [10:39:15] <ianbarber>	yeah
| [Monday 07 February 2011] [10:42:57] <sustrik>	hm, it seems it should be multiplied by 8 rather than 1024
| [Monday 07 February 2011] [10:43:17] <sustrik>	tpdu is in bytes
| [Monday 07 February 2011] [10:43:20] <sustrik>	rate is in bits
| [Monday 07 February 2011] [10:43:31] <ianbarber>	ah, you're right 
| [Monday 07 February 2011] [10:43:52] <ianbarber>	just fired the patch on mail as well, so you could see what i meant, but yeah, it should be 8
| [Monday 07 February 2011] [10:44:16] <ianbarber>	actually, should it? 
| [Monday 07 February 2011] [10:44:19] <sustrik>	the calculation is kind of strange
| [Monday 07 February 2011] [10:44:27] <ianbarber>	just looking, the comment does mention bytes to kb
| [Monday 07 February 2011] [10:44:34] <sustrik>	let us decypher what's going on there...
| [Monday 07 February 2011] [10:44:45] <ianbarber>	are you seeing bits to bytes somewhere?
| [Monday 07 February 2011] [10:44:56] <sustrik>	nope
| [Monday 07 February 2011] [10:45:12] <stimpie>	Guthur, all I could find is the source code.
| [Monday 07 February 2011] [10:45:17] <sustrik>	we are speaking about pgm_socket.cpp:201, right?
| [Monday 07 February 2011] [10:45:54] <ianbarber>	yeah, or the equivalent bit in sender
| [Monday 07 February 2011] [10:46:03] <sustrik>	options.recovery_ivl_msec >= 0 ?
| [Monday 07 February 2011] [10:46:03] <sustrik>	                                      options.recovery_ivl_msec * options.rate /
| [Monday 07 February 2011] [10:46:03] <sustrik>	                                      (1000 * rxw_max_tpdu) :
| [Monday 07 February 2011] [10:46:03] <sustrik>	                                      options.recovery_ivl * options.rate /
| [Monday 07 February 2011] [10:46:03] <sustrik>	                                      rxw_max_tpdu
| [Monday 07 February 2011] [10:46:16] <ianbarber>	pgm_max_tpdu is 1500, which looks like bytes 
| [Monday 07 February 2011] [10:46:23] <sustrik>	yes, it's bytes
| [Monday 07 February 2011] [10:46:47] <sustrik>	so, first of all, there are 2 options
| [Monday 07 February 2011] [10:46:59] <sustrik>	recovery_ivl and recovery_ivl_msec
| [Monday 07 February 2011] [10:47:11] <sustrik>	the former is in secs, the latter is in msecs
| [Monday 07 February 2011] [10:47:37] <sustrik>	if the latter is set to 0 (default), former value is used
| [Monday 07 February 2011] [10:47:53] <ianbarber>	zmq_rate says kilobits per second
| [Monday 07 February 2011] [10:48:09] <ianbarber>	the msec/sec is dealt with in the * 1000
| [Monday 07 February 2011] [10:48:12] <ianbarber>	so i think we need * 128
| [Monday 07 February 2011] [10:48:22] <ianbarber>	to go from kilobits to bytes
| [Monday 07 February 2011] [10:48:52] <sustrik>	i haven't got that far yet :)
| [Monday 07 February 2011] [10:49:26] 	 * sustrik has to write it down
| [Monday 07 February 2011] [10:50:24] <ianbarber>	:)
| [Monday 07 February 2011] [10:53:27] <sustrik>	recovery_ivl * rate * max_tpdu * 1000 / 8
| [Monday 07 February 2011] [10:54:12] <sustrik>	ianbarber: can you double check that?
| [Monday 07 February 2011] [10:54:54] <sustrik>	sorry
| [Monday 07 February 2011] [10:55:02] <sustrik>	recovery_ivl * rate / max_tpdu * 1000 / 8
| [Monday 07 February 2011] [10:56:40] <ianbarber>	was about to say :)
| [Monday 07 February 2011] [10:57:02] <sustrik>	ok, now the ordering of the terms
| [Monday 07 February 2011] [10:57:08] <sustrik>	the computation is done in ints
| [Monday 07 February 2011] [10:57:21] <sustrik>	so we have to beware rounding down to zero
| [Monday 07 February 2011] [10:57:31] <ianbarber>	not sure about that one still
| [Monday 07 February 2011] [10:57:39] <sustrik>	what's wrong?
| [Monday 07 February 2011] [10:57:41] <ianbarber>	10 * 100 / 1500 * 1000 / 8
| [Monday 07 February 2011] [10:57:49] <ianbarber>	that's with the default numbers plugged in
| [Monday 07 February 2011] [10:59:11] <sustrik>	that equals in ~83 packets
| [Monday 07 February 2011] [11:00:16] <ianbarber>	of course, this is for the ivl_msec case, so it would be 10000 or thereabouts on the left
| [Monday 07 February 2011] [11:00:20] <ianbarber>	yeah, that works then
| [Monday 07 February 2011] [11:01:07] <ianbarber>	though i don't get your 83 - that looks like about 5 packets to me. (i am likely missing something though)
| [Monday 07 February 2011] [11:02:28] <sustrik>	<ianbarber> 10 * 100 / 1500 * 1000 / 8
| [Monday 07 February 2011] [11:02:31] <sustrik>	= 83
| [Monday 07 February 2011] [11:03:24] <ianbarber>	yep, of course. i shoudn't try and do that in my head :)
| [Monday 07 February 2011] [11:03:29] <ianbarber>	yeah, that looks good
| [Monday 07 February 2011] [11:03:41] <sustrik>	ok, now the ordering...
| [Monday 07 February 2011] [11:04:40] <sustrik>	i think we can mutliply all multiplicants without overflowing the int
| [Monday 07 February 2011] [11:05:00] <sustrik>	hm
| [Monday 07 February 2011] [11:05:37] <sustrik>	with 1Gb rate we can overflow a 32-bit integer
| [Monday 07 February 2011] [11:05:57] <sustrik>	maybe the computation should be done in int64_t
| [Monday 07 February 2011] [11:06:04] <sustrik>	and then cast to int
| [Monday 07 February 2011] [11:07:51] <sustrik>	what unit is rxw_sqns meant to be in
| [Monday 07 February 2011] [11:08:01] <sustrik>	number of PGM packets?
| [Monday 07 February 2011] [11:08:06] <ianbarber>	sequence numbers
| [Monday 07 February 2011] [11:08:12] <ianbarber>	yeah, packets basically
| [Monday 07 February 2011] [11:08:26] <sustrik>	so the computation is completely wrong now
| [Monday 07 February 2011] [11:09:06] <ianbarber>	there is also a limit to how big it is
| [Monday 07 February 2011] [11:09:07] <sustrik>	it's 125x less than it should be :|
| [Monday 07 February 2011] [11:09:21] <ianbarber>	spec says no greater than half the sequence number space less one
| [Monday 07 February 2011] [11:09:28] <ianbarber>	though I suspect the space is pretty huge :)
| [Monday 07 February 2011] [11:09:53] <sustrik>	yeah, something like 2billion
| [Monday 07 February 2011] [11:09:56] <sustrik>	irrelevant here
| [Monday 07 February 2011] [11:09:58] <ianbarber>	yeah
| [Monday 07 February 2011] [11:10:19] <sustrik>	what i don't get it how it can work for anybody
| [Monday 07 February 2011] [11:10:41] <ianbarber>	well, it works if you have a high enough rate
| [Monday 07 February 2011] [11:10:46] <sustrik>	the buffers allocated now are 125x smaller than they should be
| [Monday 07 February 2011] [11:11:00] <ianbarber>	you just get a small sqns range, so it'll effectively get a lot less throughput than it should i think
| [Monday 07 February 2011] [11:11:08] <sustrik>	well, yes, but that means you recovery interval is 125x shorter
| [Monday 07 February 2011] [11:11:19] <ianbarber>	yeah, so less reliable
| [Monday 07 February 2011] [11:11:26] <sustrik>	strange
| [Monday 07 February 2011] [11:11:51] <ianbarber>	but reliability is pretty good on networks - most people are unlikely to hit it unless they're dropping packets
| [Monday 07 February 2011] [11:11:57] <sustrik>	maybe
| [Monday 07 February 2011] [11:12:03] <sustrik>	but if we fix it now
| [Monday 07 February 2011] [11:12:13] <sustrik>	prople's buffers will grow 126x
| [Monday 07 February 2011] [11:12:16] <sustrik>	125x
| [Monday 07 February 2011] [11:12:24] <sustrik>	and possibly get out of memory
| [Monday 07 February 2011] [11:12:25] <sustrik>	:(
| [Monday 07 February 2011] [11:12:27] <ianbarber>	hmm
| [Monday 07 February 2011] [11:12:32] <mikko>	at the moment it asserts (?) 
| [Monday 07 February 2011] [11:12:53] <sustrik>	mikko: it looks like the computation of pgm buffer size is wrong
| [Monday 07 February 2011] [11:12:53] <mikko>	just came back
| [Monday 07 February 2011] [11:13:04] <mikko>	i think that is something that should go to 2.1.x
| [Monday 07 February 2011] [11:13:06] <sustrik>	yielding buffers 125x smaller than they should be
| [Monday 07 February 2011] [11:13:17] <ianbarber>	not sure, txw_seqns does interact with txw_secs
| [Monday 07 February 2011] [11:13:28] <ianbarber>	so perhaps the effect isn't as large as it might be, of increasing the size
| [Monday 07 February 2011] [11:13:48] <sustrik>	i think we need to consult steven before changing it
| [Monday 07 February 2011] [11:14:02] <sustrik>	he doesn't seem to be online now
| [Monday 07 February 2011] [11:14:17] <ianbarber>	yeah, he's the best person to comment
| [Monday 07 February 2011] [11:14:19] <sustrik>	ianbarber: can you drop him a note on the mailing list?
| [Monday 07 February 2011] [11:14:31] <ianbarber>	sure thing
| [Monday 07 February 2011] [11:14:43] <sustrik>	thanks
| [Monday 07 February 2011] [11:28:36] <Guthur>	I was afraid it was only the source code as documentation
| [Monday 07 February 2011] [11:31:44] <sustrik>	Guthur: what exactly do you need?
| [Monday 07 February 2011] [11:39:22] <Guthur>	sustrik: understanding, hehe
| [Monday 07 February 2011] [11:39:48] <mikko>	neale1: on the build page should i list "Contributed by: IBM" or something else
| [Monday 07 February 2011] [11:40:10] <Guthur>	I was hoping to provide patches, but there is a lot to understand
| [Monday 07 February 2011] [11:40:21] <sustrik>	i've started writing somrthing:
| [Monday 07 February 2011] [11:40:22] <sustrik>	http://www.zeromq.org/whitepapers:architecture
| [Monday 07 February 2011] [11:40:23] <Guthur>	Specifically the duplicate identity issue
| [Monday 07 February 2011] [11:40:28] <sustrik>	but never got too far
| [Monday 07 February 2011] [11:40:51] <sustrik>	in any case, feel free to ask on irc
| [Monday 07 February 2011] [11:41:08] <Guthur>	in general I think it would make the learning curve for new contributors a little less steep
| [Monday 07 February 2011] [11:41:40] <sustrik>	definitely
| [Monday 07 February 2011] [11:41:59] <ianbarber>	that duplicate identity issue seems tricky
| [Monday 07 February 2011] [11:42:08] <sustrik>	the only problem is someone has to write it down and maintain it as the development goes on
| [Monday 07 February 2011] [11:44:22] <Guthur>	ianbarber: My main issue with it is the fact it crashes the server side
| [Monday 07 February 2011] [11:44:35] <Guthur>	clients crashing a server is not good
| [Monday 07 February 2011] [11:44:49] <ianbarber>	yep, i agree
| [Monday 07 February 2011] [11:44:54] <ianbarber>	i had the same reaction
| [Monday 07 February 2011] [11:52:11] <ianbarber>	hmm
| [Monday 07 February 2011] [11:52:13] <ianbarber>	sessions_sync.lock ();
| [Monday 07 February 2011] [11:52:13] <ianbarber>	    bool registered = sessions.insert (
| [Monday 07 February 2011] [11:52:13] <ianbarber>	        sessions_t::value_type (name_, session_)).second;
| [Monday 07 February 2011] [11:52:13] <ianbarber>	    sessions_sync.unlock ();
| [Monday 07 February 2011] [11:52:14] <ianbarber>	    return registered;
| [Monday 07 February 2011] [11:52:42] <ianbarber>	just google, the first ref I found for stl map said insert would return the inserted thing, or an operator
| [Monday 07 February 2011] [11:52:44] <ianbarber>	not a bool
| [Monday 07 February 2011] [11:53:04] <ianbarber>	so the insert wouldn't report a failure, even if it had encountered a collision?
| [Monday 07 February 2011] [11:53:16] <ianbarber>	sure sustrik will correct me in short order :)
| [Monday 07 February 2011] [12:01:47] <mikko>	http://www.zeromq.org/docs:builds
| [Monday 07 February 2011] [12:01:55] <mikko>	needs information about contributors as well
| [Monday 07 February 2011] [12:03:54] <ianbarber>	surely put yourself on there under contributors
| [Monday 07 February 2011] [12:04:06] <ianbarber>	others can add themselves I guess would be easiest, it is a wiki
| [Monday 07 February 2011] [12:25:30] <mikko>	crlzmq2 fails to build atm
| [Monday 07 February 2011] [12:30:39] <Guthur>	mikko: yeah sorry about that
| [Monday 07 February 2011] [12:30:55] <Guthur>	I know the issue, but can not fix at the moment, at work
| [Monday 07 February 2011] [12:31:00] <mikko>	thats fine
| [Monday 07 February 2011] [12:31:05] <mikko>	just making sure that it's known
| [Monday 07 February 2011] [12:31:19] <neale1>		mikko: There's a mono environment on the same s390x build server if you want to exploit that. What level of mono do you require? It's 2.7.1 atm, but can be brought up to current git head if required
| [Monday 07 February 2011] [12:31:46] <Guthur>	the solution file is the source of the problem
| [Monday 07 February 2011] [12:32:03] <mikko>	i got mono 2.6.7
| [Monday 07 February 2011] [12:32:11] <mikko>	is there a difference with mono across architectures?
| [Monday 07 February 2011] [12:32:16] <Guthur>	I should be able to push a fix in a couple of hours
| [Monday 07 February 2011] [12:33:11] <neale1>	mikko: Shouldn't be. I build from same base, just have s390x jit to do bytecode to s390x machine code xlate
| [Monday 07 February 2011] [12:33:33] <mikko>	neale1: should i mention that "Linux s390x build slave was contributed by IBM" ?
| [Monday 07 February 2011] [12:33:49] <neale1>	No, by Marist College would be better
| [Monday 07 February 2011] [12:33:57] <mikko>	neale1: i could add a mono build for clrzmq and clrzmq2
| [Monday 07 February 2011] [12:34:01] <mikko>	neale1: sure, will add that
| [Monday 07 February 2011] [12:34:04] <neale1>	Yes
| [Monday 07 February 2011] [12:34:15] <mikko>	do you want url to anywhere?
| [Monday 07 February 2011] [12:35:24] <neale1>	I'll ask the Marist folks
| [Monday 07 February 2011] [12:35:40] <mikko>	neale1: http://www.zeromq.org/docs:builds
| [Monday 07 February 2011] [12:35:47] <mikko>	you can edit the page to add the link
| [Monday 07 February 2011] [12:37:30] <neale1>	mikko: Tks
| [Monday 07 February 2011] [12:38:05] <ianbarber>	ah, there's a .second on that sessions code, so it's all good. Stepping through it looks like register session is only being called once, for some odd reason
| [Monday 07 February 2011] [12:41:20] <neale1>	mikko: Do I have a wikidot id to update that page?
| [Monday 07 February 2011] [12:42:48] <mikko>	neale1: i think you can create one
| [Monday 07 February 2011] [12:42:55] <mikko>	neale1: im not sure if you have one already :)
| [Monday 07 February 2011] [12:44:01] <neale1>	 mikko: Cld u just add this http://www.marist.edu/it/datacenter/systems.html
| [Monday 07 February 2011] [12:44:21] <mikko>	neale1: will do
| [Monday 07 February 2011] [12:45:19] <mikko>	neale1: done
| [Monday 07 February 2011] [12:54:27] <sustrik>	ianbarber: insert returns pair, the code selects the second part of the pair, which is bool
| [Monday 07 February 2011] [12:55:10] <ianbarber>	sustrik: spotted that, seems correct
| [Monday 07 February 2011] [12:55:22] <ianbarber>	weird thing I had when debugging the dual identities thing is that it only seems to be hit once
| [Monday 07 February 2011] [12:55:35] <ianbarber>	so I suspect the problem is further up the chain, in attach or something like that
| [Monday 07 February 2011] [12:55:57] <sustrik>	ianbarber: yes, possibly
| [Monday 07 February 2011] [12:57:09] <sustrik>	where exactly does it crash now?
| [Monday 07 February 2011] [12:57:59] <ianbarber>	Assertion failed: new_sndbuf > old_sndbuf (mailbox.cpp:182)
| [Monday 07 February 2011] [12:58:17] <ianbarber>	i think that's just because if it gets a send fail it just tries to increase buffer size (until it can't)
| [Monday 07 February 2011] [12:58:50] <sustrik>	ianbarber: that has nothing to do with duplicate identities imo
| [Monday 07 February 2011] [12:59:27] <sustrik>	well, unless duplicate identities cause an infinite or extremely fast generation of commands
| [Monday 07 February 2011] [12:59:40] <sustrik>	hm, the latter may be the case...
| [Monday 07 February 2011] [13:01:46] <ianbarber>	sustrik: i don't get the crash on connect, only when I attempt to send something to connected peers
| [Monday 07 February 2011] [13:01:58] <ianbarber>	so it may be something of that nature
| [Monday 07 February 2011] [13:02:16] <rook->	hello? I have a noob question if someone has a few minutes
| [Monday 07 February 2011] [13:02:41] <sustrik>	inabarder: interesting
| [Monday 07 February 2011] [13:02:48] <sustrik>	rook-: shoot
| [Monday 07 February 2011] [13:03:19] <sustrik>	ianbarber: it looks like large amount of commands is generated for some reason
| [Monday 07 February 2011] [13:03:22] <rook->	I'm looking for a messaging system to support a distributed "eventually consistent" cloud architecture...
| [Monday 07 February 2011] [13:03:30] <sustrik>	you need to find out why it is so
| [Monday 07 February 2011] [13:03:51] <sustrik>	check the send_command() function to hook into command passing mechanism
| [Monday 07 February 2011] [13:03:53] <rook->	all the mq's I've found seem to support 2 models: durable queues and pub/sub (fanout)
| [Monday 07 February 2011] [13:04:39] <rook->	but nothing seems to support publishing blindly to n-subscribers and guaranteeing that each subscriber receives 1 and only 1 copy of the message
| [Monday 07 February 2011] [13:04:51] <sustrik>	it's impossible
| [Monday 07 February 2011] [13:05:01] <sustrik>	slow consumers are the problem
| [Monday 07 February 2011] [13:05:08] <rook->	by blindly, I mean that the publisher just writes 1 message and all subs who've scribed (whether they're connected or not) eventually get it
| [Monday 07 February 2011] [13:05:49] <rook->	it looks to me like a pub-sub with a replay service or something similar would solve the problem, but haven't seen anything like it
| [Monday 07 February 2011] [13:06:08] <sustrik>	you would need infinite memory to hold the messages for slow/stuck consumers
| [Monday 07 February 2011] [13:06:27] <rook->	infinite/disk
| [Monday 07 February 2011] [13:06:27] <rook->	yea
| [Monday 07 February 2011] [13:07:20] <sustrik>	yes, so it can't be done
| [Monday 07 February 2011] [13:07:37] <rook->	um.. I have a hard time believing that...
| [Monday 07 February 2011] [13:08:13] <rook->	since so many services are using eventually consistent frameworks of their own devising
| [Monday 07 February 2011] [13:08:32] <sustrik>	shrug
| [Monday 07 February 2011] [13:09:21] <rook->	I mean, there may be the need for a high water mark/"beyond this point the stuck consumer needs help with rebuilding"
| [Monday 07 February 2011] [13:09:33] <rook->	but "can't be done" seems improbable
| [Monday 07 February 2011] [13:10:12] <sustrik>	there's an alternative, yes
| [Monday 07 February 2011] [13:10:20] <sustrik>	you can block the sender
| [Monday 07 February 2011] [13:10:39] <sustrik>	but that means that the slow/stuck consumer can stop all the data distribution
| [Monday 07 February 2011] [13:10:50] <sustrik>	even to the properly working consumers
| [Monday 07 February 2011] [13:11:10] <rook->	yea that'd suck :D
| [Monday 07 February 2011] [13:11:20] <sustrik>	so it's either-or
| [Monday 07 February 2011] [13:11:33] <sustrik>	either drop messages when there no space to store them
| [Monday 07 February 2011] [13:11:43] <sustrik>	or block the whole distribution
| [Monday 07 February 2011] [13:12:38] <rook->	hrm... 
| [Monday 07 February 2011] [13:13:26] <rook->	I think in our env. a rolling window would potentially be ok... i.e. if the consumer isn't around for a given period of time, then remediation is required for it to rejoin and resync
| [Monday 07 February 2011] [13:13:43] <sustrik>	ack
| [Monday 07 February 2011] [13:13:51] <rook->	true
| [Monday 07 February 2011] [13:13:51] <sustrik>	that's the standard model for pub-sub
| [Monday 07 February 2011] [13:14:03] <rook->	sorry?
| [Monday 07 February 2011] [13:14:32] <rook->	I thought that pub/sub was limited by immediately connectivity and deliverability
| [Monday 07 February 2011] [13:14:53] <rook->	i.e. if consumer isn't there to receive message, or isn't accepting the message, it may miss out
| [Monday 07 February 2011] [13:16:29] <rook->	is my impression of pub/sub overly simplified?
| [Monday 07 February 2011] [13:16:51] <rook->	 / have I missed something?
| [Monday 07 February 2011] [13:18:25] <ianbarber>	rook: that's how pubsub works in 0MQ, without identities. If you have identities set then it'll try and buffer up messages for them. 
| [Monday 07 February 2011] [13:19:13] <sustrik>	rook-: yes, you are right
| [Monday 07 February 2011] [13:19:19] <sustrik>	that's the general model
| [Monday 07 February 2011] [13:19:32] <sustrik>	however, different solution add some amount of reliability
| [Monday 07 February 2011] [13:20:02] <sustrik>	for example, PGM retransmits the missing packets if they are still in the reliability window
| [Monday 07 February 2011] [13:20:04] <sustrik>	etc.
| [Monday 07 February 2011] [13:21:22] <Guthur>	is the HWM per durable subscriber or does it effect all globally?
| [Monday 07 February 2011] [13:21:53] <sustrik>	it's per peer
| [Monday 07 February 2011] [13:22:33] <Guthur>	is there no way to clear it, besides the peer connecting?
| [Monday 07 February 2011] [13:23:31] <rook->	so I can, in 0mq, have a publisher, who just publishes events, and I can have n-consumers that each, with some reliability, receive every message and the publisher doesn't need to know or be configured with what the consumers are, how many of them there are, etc.
| [Monday 07 February 2011] [13:23:35] <rook->	?
| [Monday 07 February 2011] [13:27:52] <rook->	?
| [Monday 07 February 2011] [13:28:00] <rook->	sustrik?
| [Monday 07 February 2011] [13:31:33] <sustrik>	Guthur: no
| [Monday 07 February 2011] [13:31:52] <sustrik>	rook-: yes
| [Monday 07 February 2011] [13:32:09] <rook->	cool!
| [Monday 07 February 2011] [13:32:48] <rook->	is the size of the window configurable?  I clearly have more reading to do, url reference handy?  Pointers?
| [Monday 07 February 2011] [13:32:53] <rook->	(thanks for your help btw)
| [Monday 07 February 2011] [13:33:22] <Guthur>	rook-: http://zguide.zeromq.org/chapter:all
| [Monday 07 February 2011] [13:33:29] <Guthur>	you may have seen it already
| [Monday 07 February 2011] [13:33:32] <sustrik>	or check the man pages
| [Monday 07 February 2011] [13:34:14] <rook->	yea saw the docs - to be honest, I find them... difficult.. very friendly and jovial but not as... concise as typical docs ;)
| [Monday 07 February 2011] [13:34:29] <sustrik>	there's reference
| [Monday 07 February 2011] [13:34:36] <sustrik>	that's consice
| [Monday 07 February 2011] [13:35:04] <rook->	ok I'll poke about
| [Monday 07 February 2011] [13:35:10] <rook->	now that I know that 0mq handles it
| [Monday 07 February 2011] [13:35:23] <rook->	I feel more justified in digging harder for the info :)
| [Monday 07 February 2011] [13:35:57] <rook->	thanks for the help - off to read
| [Monday 07 February 2011] [13:35:59] <rook->	:)
| [Monday 07 February 2011] [14:45:08] <mikko>	good evening
| [Monday 07 February 2011] [14:58:36] <neale1>	mikko: I am getting an article on 0MQ printed in the April/May edition of z/Journal (a journal for IBM mainframers). It's an introduction to 0MQ for a group more familiar with things like MQSeries 
| [Monday 07 February 2011] [14:59:08] <mikko>	nice
| [Monday 07 February 2011] [14:59:16] <mikko>	i read about ibm system z
| [Monday 07 February 2011] [14:59:24] <mikko>	seems like pretty serious computing system
| [Monday 07 February 2011] [15:00:48] <neale1>	Yep, there's a major conference in Anaheim later this month which I'm going to. I wasn't able to schedule a 0MQ talk this time but I'll be trying to get one on the agenda for August in Orlando. As I'm on the program committee, it should get on
| [Monday 07 February 2011] [15:02:17] <mikko>	what is the conference in Orlando?
| [Monday 07 February 2011] [15:02:36] <neale1>	Same as the one in Anaheim - they hold 2 yearly. It's called "SHARE"
| [Monday 07 February 2011] [15:02:55] <mikko>	is it mainframy conference?
| [Monday 07 February 2011] [15:03:09] <neale1>	Yep
| [Monday 07 February 2011] [15:03:37] <neale1>	http://share.confex.com/share/116/webprogram/start.html
| [Monday 07 February 2011] [15:05:20] <mikko>	seems like a big conference
| [Monday 07 February 2011] [15:06:20] <mikko>	i've worked with some of the technologies mentioned in the talks
| [Monday 07 February 2011] [15:06:32] <mikko>	mainly on integrating them with web
| [Monday 07 February 2011] [15:07:53] <sustrik>	the introduction to 0mq for mq series users is something that's badly missing
| [Monday 07 February 2011] [15:08:11] <sustrik>	neale1: would your article be publicly available?
| [Monday 07 February 2011] [15:08:38] <neale1>	sustrik: Yes, z/Journal has it online as well as in a physical magazine.
| [Monday 07 February 2011] [15:08:56] <sustrik>	great!
| [Monday 07 February 2011] [15:09:04] <neale1>	sustrik: I'm not doing a if you're using WebSphere MQ and you do x, then on 0MQ you do y
| [Monday 07 February 2011] [15:09:15] <sustrik>	understood
| [Monday 07 February 2011] [15:09:22] <neale1>	It's a straight introduction trying to put it in context of where it would be useful.
| [Monday 07 February 2011] [15:09:40] <sustrik>	i mean, the problem is that if you have "corporate messaging" experience
| [Monday 07 February 2011] [15:09:49] <neale1>	A lot of folks want to avoid the complexity and cost of MQ
| [Monday 07 February 2011] [15:09:53] <sustrik>	you have quite lot of expectations...
| [Monday 07 February 2011] [15:09:56] <neale1>	yes
| [Monday 07 February 2011] [15:10:00] <sustrik>	that don't apply to 0mq
| [Monday 07 February 2011] [15:10:41] <sustrik>	so i think the point of the article is to explain the difference between mq series and 0mq
| [Monday 07 February 2011] [15:10:55] <sustrik>	like "what you should expect from 0mq"
| [Monday 07 February 2011] [15:10:58] <sustrik>	right?
| [Monday 07 February 2011] [15:12:40] <sustrik>	in any case, that kind of introduction is missing so far
| [Monday 07 February 2011] [15:14:19] <neale1>	At the moment it's even more basic than that. I want to aim at the sockets programmers who are dreading having to go to a full brokered option.
| [Monday 07 February 2011] [15:14:33] <sustrik>	ah, that's easier, yes
| [Monday 07 February 2011] [15:15:14] <neale1>	The linux on system z community is about 10 years old now, but most of its growth has been in the past 5. We're seeing a mix of traditional sysadmin/programmer types from the UNIX world combining with the old hands from the traditional mainframe set. 
| [Monday 07 February 2011] [15:16:00] <neale1>	I want to conclude the article with a set of questions people can ask when they want to select a technology. It might be useful to open the floor here to suggestions.
| [Monday 07 February 2011] [15:16:51] <sustrik>	definitely
| [Monday 07 February 2011] [15:17:15] <sustrik>	it's rather hard question to ask though
| [Monday 07 February 2011] [15:17:35] <sustrik>	as it's not only a technical question
| [Monday 07 February 2011] [15:18:07] <sustrik>	and depends on whether there are people skilled in the technology, whether company have licenses bought already etc.
| [Monday 07 February 2011] [15:18:36] <neale1>	In my own case I discovered 0MQ when I was tasked with a project that needed to have several "collector" clients receive raw data, package it, and send it to a sink which would process the collected data. In addition I wanted to add collectors at will, ensure delivery, receive configuration information from the server. And do this in a minimal footprint with little affect on overall CPU on the systems where those collectors are ru
| [Monday 07 February 2011] [15:18:54] <neale1>	Oh, and not require the customer install a full-fledged broker type system
| [Monday 07 February 2011] [15:19:14] <sustrik>	right, then using 0mq makes perfect sense
| [Monday 07 February 2011] [15:19:34] <sustrik>	when you spoke about mainframes i though of integrating legacy apps
| [Monday 07 February 2011] [15:19:42] <sustrik>	rather than writing new apps
| [Monday 07 February 2011] [15:20:37] <sustrik>	but linux subsystem is probably not that legacy-oriented
| [Monday 07 February 2011] [15:23:01] <neale1>	Actually, IBM has spent a lot of time/money putting hooks into its "legacy" systems to allow them to integrate with Linux. One thing we'd need to do on the legacy side though is to port the code (or provide a minimal set of things like the tcp: transport)
| [Monday 07 February 2011] [15:23:49] <sustrik>	right
| [Monday 07 February 2011] [15:24:06] <sustrik>	anyway, if you are going to have a lecture about 0mq
| [Monday 07 February 2011] [15:24:11] <neale1>	Within a mainframe you can talk between the legacy systems like z/OS and a z/Linux system at memory-to-memory speeds even though it appears to be a layer2/layer3 network
| [Monday 07 February 2011] [15:24:27] <sustrik>	announce it on www.zeromq.org/community (see top right)
| [Monday 07 February 2011] [15:24:32] <neale1>	Will do
| [Monday 07 February 2011] [15:24:58] <sustrik>	neale1: are you familiar with z/OS as well?
| [Monday 07 February 2011] [15:26:22] <neale1>	sustrik: Yes as well as z/VSE and z/VM. The latter two I've been using for *many* years now. I have only a few years experience with z/OS.
| [Monday 07 February 2011] [15:26:57] <neale1>	0MQ could easily be ported to what z/OS calls Unix System Services (USS). It has a full UNIX-branded set of APIs.
| [Monday 07 February 2011] [15:27:08] <sustrik>	wow
| [Monday 07 February 2011] [15:27:21] <sustrik>	thay have a posix-y interface, right?
| [Monday 07 February 2011] [15:27:30] <neale1>	Yes, fully posix-compliant
| [Monday 07 February 2011] [15:27:39] <sustrik>	that's need
| [Monday 07 February 2011] [15:27:43] <sustrik>	neat
| [Monday 07 February 2011] [15:28:04] <sustrik>	would be nice to have the port one day
| [Monday 07 February 2011] [15:28:19] <sustrik>	but i assume the build system would be the main problem
| [Monday 07 February 2011] [15:28:45] <neale1>	THey have most of the common tools too: autoconf/automake/libtool - at what level I'm not sure 
| [Monday 07 February 2011] [15:28:57] <sustrik>	even better
| [Monday 07 February 2011] [15:29:04] <sustrik>	there's a 0mq port to VMS
| [Monday 07 February 2011] [15:29:12] <sustrik>	there's a POSIX interface available
| [Monday 07 February 2011] [15:29:15] <neale1>	Yes, I saw that. 
| [Monday 07 February 2011] [15:29:25] <sustrik>	but the problem is that there's no unix shell
| [Monday 07 February 2011] [15:29:35] <sustrik>	so the autotools doesn't work
| [Monday 07 February 2011] [15:29:41] <neale1>	Ugh
| [Monday 07 February 2011] [15:30:01] <neale1>	On USS they have a korn shell but you can also run bash
| [Monday 07 February 2011] [15:30:12] <sustrik>	sounds good
| [Monday 07 February 2011] [15:30:15] <Guthur>	is there a zeromq irc log?
| [Monday 07 February 2011] [15:30:31] <sustrik>	travlr used to log the conversation
| [Monday 07 February 2011] [15:30:34] <neale1>	Same goes with z/VM
| [Monday 07 February 2011] [15:30:57] <sustrik>	i see
| [Monday 07 February 2011] [15:31:05] <Guthur>	ah ha, and he still does
| [Monday 07 February 2011] [15:31:05] <Guthur>	cheers sustrik 
| [Monday 07 February 2011] [15:31:33] <sustrik>	neale1: maybe give it a shot if you have some spare time
| [Monday 07 February 2011] [15:31:39] <Guthur>	oh it's a bit behind though
| [Monday 07 February 2011] [15:32:32] <neale1>	I'm going to be installing an upgrade of our z/OS system in the near future, so I'll make sure the USS environment and tools are there.
| [Monday 07 February 2011] [15:32:35] <sustrik>	the logger used to hang around called 'zmqircd'
| [Monday 07 February 2011] [15:32:46] <sustrik>	but it doesn't seem to be there for some time already
| [Monday 07 February 2011] [15:33:06] <sustrik>	neale1: nice
| [Monday 07 February 2011] [15:33:41] <mikko>	i got logs
| [Monday 07 February 2011] [15:33:50] <mikko>	since last Feb i think
| [Monday 07 February 2011] [15:34:37] <Guthur>	it only goes up until Feb 4 2011 or something
| [Monday 07 February 2011] [15:34:54] <Guthur>	I suppose it just needs the newest ones placed on it
| [Monday 07 February 2011] [15:36:25] <mikko>	it should be up to date
| [Monday 07 February 2011] [15:37:04] <Guthur>	here http://travlr.github.com/zmqirclog/
| [Monday 07 February 2011] [15:37:07] <Guthur>	correct?
| [Monday 07 February 2011] [15:37:13] <mikko>	http://valokuva.org/~mikko/zeromq.log
| [Monday 07 February 2011] [15:37:15] <mikko>	mine's here
| [Monday 07 February 2011] [15:37:46] <mikko>	it just links to my normal irc log from this channel
| [Monday 07 February 2011] [16:23:33] <Guthur>	ok, hopefully that's the clrzmq2 build fixed
| [Monday 07 February 2011] [17:28:54] <Guthur>	just whipped together this asyncReturn device http://paste.lisp.org/display/119452
| [Monday 07 February 2011] [17:29:30] <Guthur>	the return call could be made with a push socket supplying the appropriate address
| [Monday 07 February 2011] [17:30:31] <Guthur>	As an aside I have just moved the RunningLoop into the base class
| [Monday 07 February 2011] [17:31:15] <Guthur>	Just a simple thing, but thought I would share anyway
| [Monday 07 February 2011] [20:50:35] <Steve-o>	mikko: the x1024 patch on PGM 'works' but isn't correct, I'll have to look at Ian's suggestion tomorrow
| [Monday 07 February 2011] [20:51:49] <Steve-o>	all day at IKEA today, patience is a virtue as is said.
| [Monday 07 February 2011] [20:57:56] <d4de>	Hi, any idea on when aprox. v2.1.0 will go stable?
| [Monday 07 February 2011] [21:00:03] <Steve-o>	good question, probably dependent on the issue list on github getting cleaned up a bit
| [Monday 07 February 2011] [21:01:22] <d4de>	link?
| [Monday 07 February 2011] [21:02:05] <d4de>	meh nvm ... I think google can answer that one :-)
| [Monday 07 February 2011] [21:02:08] <Steve-o>	https://github.com/zeromq/zeromq2/issues
| [Monday 07 February 2011] [21:02:18] <d4de>	ooh well ... thanks :-D
| [Monday 07 February 2011] [21:03:01] <Steve-o>	there are a couple of weird platform dependent / compiler optimisation issues with the PGM socket
| [Monday 07 February 2011] [21:03:26] <Steve-o>	and there has been issues with zmq_term
| [Monday 07 February 2011] [21:03:36] <d4de>	so it is just PGM that is putting it back ... I saw that you guys has already fixed some annoying bugs in 2.1 beta, so I keep wondering what is left
| [Monday 07 February 2011] [21:03:41] <Steve-o>	you can always ask Martin again on the list
| [Monday 07 February 2011] [21:04:29] <d4de>	hmm still no IPv6 support huh?
| [Monday 07 February 2011] [21:04:58] <Steve-o>	well yes and no
| [Monday 07 February 2011] [21:05:44] <Steve-o>	there probably needs to be extra flags or specification for using IPv4 or IPv6, or both
| [Monday 07 February 2011] [21:05:58] <Steve-o>	similar to BSD's IPV6ONLY
| [Monday 07 February 2011] [21:06:12] <d4de>	aha
| [Monday 07 February 2011] [21:06:17] <Steve-o>	binding to eth0:* tends to be complicated in a multi-stack environment
| [Monday 07 February 2011] [21:07:39] <Steve-o>	surprisingly PGM has better support for IPv6 but it depends on reasonable OS support
| [Monday 07 February 2011] [21:08:11] <Steve-o>	there are some issues with the glibc in Ubuntu 10.10 there are definitely unexpected
| [Monday 07 February 2011] [21:08:24] <Steve-o>	for example ::1 resolves as 127.0.0.1
| [Monday 07 February 2011] [21:08:59] <Steve-o>	getaddrinfo (`hostname`) returns different address to ping `hostname` when using DHCP
| [Monday 07 February 2011] [21:09:38] <Steve-o>	one easy path is to assume IPv4 only and follow SMTP's requirement to use a IPv6: prefix 
| [Monday 07 February 2011] [21:11:12] <Steve-o>	I have to concede I only follow the PGM parts of ZeroMQ, not so much the other parts
| [Monday 07 February 2011] [21:12:54] <Steve-o>	There is certainly work on improving ZMQ_SWAP and XPUB/XSUB sockets
| [Tuesday 08 February 2011] [01:18:15] <stockMQ>	Hi.. I have a binary char* which i want to send from one Thread to Another.. i am trying inproc.. sending the char* as it is as a message does not work as at the receiving end while decoding i get erroneous data..I understand i have to use protobuf..but then can i serialize to string
| [Tuesday 08 February 2011] [01:42:58] <sustrik>	you have to copy the data to the message
| [Tuesday 08 February 2011] [02:38:39] <stockMQ>	I want to send a Byte* over a socket.. What would be the right way to do it
| [Tuesday 08 February 2011] [02:53:35] <Guthur>	stockMQ, do you mean send the pointer?
| [Tuesday 08 February 2011] [03:54:02] <Guthur>	I am sorry, I've busted the clrzmq2 build again, this MSVS solution stuff is utter crap
| [Tuesday 08 February 2011] [04:05:21] <mikko>	good morning
| [Tuesday 08 February 2011] [04:52:39] <sustrik>	morning
| [Tuesday 08 February 2011] [08:11:41] <Skaag>	BAHAHAHAHA.... IT'S ALIVE!!!
| [Tuesday 08 February 2011] [08:11:50] <Skaag>	The horror!
| [Tuesday 08 February 2011] [08:14:06] <sustrik>	run!
| [Tuesday 08 February 2011] [08:14:36] <sustrik>	:)
| [Tuesday 08 February 2011] [08:14:41] 	 * taotetek flees
| [Tuesday 08 February 2011] [08:19:43] <ianbarber>	another epgm question: if I, in one thread, do a PUB send, then a SUB recv, using PGM, that should work right? 
| [Tuesday 08 February 2011] [08:21:32] <sustrik>	ianbarber: that's using loopback multicast
| [Tuesday 08 February 2011] [08:21:40] <Guthur>	is the lack of IPC on windows more a lack of motivation issue as oppose to technical?
| [Tuesday 08 February 2011] [08:21:58] <sustrik>	in reality, multicast doesn't work in loopback manner
| [Tuesday 08 February 2011] [08:22:13] <sustrik>	so there's an emulation layer in the OS that simulates it
| [Tuesday 08 February 2011] [08:22:20] <ianbarber>	oh right
| [Tuesday 08 February 2011] [08:22:26] <sustrik>	however, as i am said, it's pretty crappy
| [Tuesday 08 February 2011] [08:22:38] <sustrik>	so rather use ipc/tcp for loopback
| [Tuesday 08 February 2011] [08:22:51] <sustrik>	Guthur: both in a way
| [Tuesday 08 February 2011] [08:22:56] <ianbarber>	that makes sense, i mean it's not something that is a good idea other than for testing stuff
| [Tuesday 08 February 2011] [08:23:20] <sustrik>	ack
| [Tuesday 08 February 2011] [08:23:41] <sustrik>	Guthur: to implement IPC on windows you need NamedPipes
| [Tuesday 08 February 2011] [08:23:53] <sustrik>	these are identified by handles rather than fds
| [Tuesday 08 February 2011] [08:24:02] <sustrik>	so you can't use select() for polling
| [Tuesday 08 February 2011] [08:24:13] <sustrik>	thus you have to implement IOCP polling mechanism
| [Tuesday 08 February 2011] [08:24:45] <Guthur>	oh, I should have none it was a simple issue, hehe
| [Tuesday 08 February 2011] [08:25:03] <sustrik>	well, it's doable
| [Tuesday 08 February 2011] [08:25:05] <Skaag>	what happens when one client out of 20, is down for an hour?
| [Tuesday 08 February 2011] [08:25:13] <Skaag>	it loses all data, right?
| [Tuesday 08 February 2011] [08:25:35] <sustrik>	Skaag: if no identity is set, then yes
| [Tuesday 08 February 2011] [08:25:48] <Skaag>	and if identity is set?
| [Tuesday 08 February 2011] [08:26:09] <sustrik>	then only the data that were "on the wire" during the failure are lost
| [Tuesday 08 February 2011] [08:26:19] <sustrik>	the subsequent messages are queued in the publisher
| [Tuesday 08 February 2011] [08:26:27] <Skaag>	and are saved in memory?
| [Tuesday 08 February 2011] [08:26:32] <sustrik>	yes
| [Tuesday 08 February 2011] [08:26:43] <Skaag>	and if the publisher died too, they are lost?
| [Tuesday 08 February 2011] [08:26:50] <sustrik>	sure thing
| [Tuesday 08 February 2011] [08:26:55] <Skaag>	ok :)
| [Tuesday 08 February 2011] [08:27:24] <Skaag>	i'm trying to figure out how to keep 20+ machines in sync with the same data
| [Tuesday 08 February 2011] [08:27:36] <Skaag>	they all get small incremental updates via zmq
| [Tuesday 08 February 2011] [08:27:42] <Skaag>	but it accumulates to quite a lot
| [Tuesday 08 February 2011] [08:28:05] <sustrik>	ask for a snapshot after starting the client using req/rep
| [Tuesday 08 February 2011] [08:28:16] <sustrik>	then subscribe to incremental upgrades using pub/sub
| [Tuesday 08 February 2011] [08:31:51] <Skaag>	sounds simple enough
| [Tuesday 08 February 2011] [08:32:02] <Skaag>	the remaining problem is knowing who to ask the snapshot from
| [Tuesday 08 February 2011] [08:32:08] <Skaag>	who is the leader with the best snapshot
| [Tuesday 08 February 2011] [08:32:29] <Skaag>	probably the one with the longest uptime
| [Tuesday 08 February 2011] [08:32:31] <mikko>	are you using zookeeper in the setup?
| [Tuesday 08 February 2011] [08:32:37] <Skaag>	not anymore
| [Tuesday 08 February 2011] [08:32:48] <Skaag>	I can't use zookeeper because it requires a fixed number of nodes
| [Tuesday 08 February 2011] [08:33:00] <mikko>	why is that?
| [Tuesday 08 February 2011] [08:33:00] <Skaag>	when when nodes are added, a configuration file needs to be edited, and the whole thing restarted
| [Tuesday 08 February 2011] [08:33:14] <mikko>	you mean to zookeeper itself?
| [Tuesday 08 February 2011] [08:33:17] <Skaag>	I followed a thread on their list, and found a person started working on fixing this
| [Tuesday 08 February 2011] [08:33:31] <Skaag>	yes to zookeeper itself
| [Tuesday 08 February 2011] [08:33:50] <Skaag>	anyway his work has stalled
| [Tuesday 08 February 2011] [08:34:12] <Skaag>	and he offered someone else to continue working on it, and the ETA is 3 ~ 5 month to implement
| [Tuesday 08 February 2011] [08:34:23] <Skaag>	why, no idea..
| [Tuesday 08 February 2011] [08:35:04] <Guthur>	sustrik: why not just use sockets for IPC
| [Tuesday 08 February 2011] [08:36:16] <Guthur>	sockets can be polled with select, or am I missing something big here
| [Tuesday 08 February 2011] [08:36:26] <sustrik>	Guthur: nope
| [Tuesday 08 February 2011] [08:36:33] <sustrik>	you can use sockets
| [Tuesday 08 February 2011] [08:36:46] <sustrik>	just use tcp://127.0.0.1:port
| [Tuesday 08 February 2011] [08:38:10] <sustrik>	Skaag: choosing a leader in a distributed env is a complex problem...
| [Tuesday 08 February 2011] [08:38:16] <Guthur>	are pipes more performant?
| [Tuesday 08 February 2011] [08:38:32] <sustrik>	you should peek into some disttibuted algorithm textbook
| [Tuesday 08 February 2011] [08:38:38] <zchrish>	mikko: You referred me to valokuva.org for a mingw dll for  Windows build. Is there a library option also available? 
| [Tuesday 08 February 2011] [08:38:43] <sustrik>	Guthur: never measured it
| [Tuesday 08 February 2011] [08:38:57] <sustrik>	but it would make sense if they were
| [Tuesday 08 February 2011] [08:39:44] <sustrik>	Skaag: especially beware of split-brain syndrome
| [Tuesday 08 February 2011] [08:40:03] <Skaag>	right, I heard about that
| [Tuesday 08 February 2011] [08:40:14] <Skaag>	a problem that exists in the glusterfs project
| [Tuesday 08 February 2011] [08:40:17] <Skaag>	(which I also use)
| [Tuesday 08 February 2011] [08:40:31] <sustrik>	it's when the network is broken into two parts
| [Tuesday 08 February 2011] [08:40:39] <sustrik>	each part selects its own leader
| [Tuesday 08 February 2011] [08:40:48] <sustrik>	resulting in inconsistent state
| [Tuesday 08 February 2011] [08:41:10] <Skaag>	can run a competition with set rules, and the winner gets its data replicated to everybody
| [Tuesday 08 February 2011] [08:41:52] <sustrik>	to prevent the split-brain the competition could be won only by a node that gets more than 50% of the vote
| [Tuesday 08 February 2011] [08:42:08] <sustrik>	to compute 50% you need to know the size of the cluster
| [Tuesday 08 February 2011] [08:42:11] <sustrik>	it's complex...
| [Tuesday 08 February 2011] [08:45:40] <mikko>	zchrish: what do you mean?
| [Tuesday 08 February 2011] [08:45:45] <mikko>	zchrish: static library?
| [Tuesday 08 February 2011] [08:46:01] <zchrish>	Yes, a static library.
| [Tuesday 08 February 2011] [08:46:12] <mikko>	zchrish: no, we don't support building static libraries under mingw32
| [Tuesday 08 February 2011] [08:46:33] <zchrish>	Oh, I see. Why not?
| [Tuesday 08 February 2011] [08:46:52] <mikko>	zchrish: it's a massive hassle with the dllexport/dllimport stuff
| [Tuesday 08 February 2011] [08:46:59] <mikko>	on windows
| [Tuesday 08 February 2011] [08:47:19] <zchrish>	Sure, ok. Thank you.
| [Tuesday 08 February 2011] [08:47:31] <mikko>	you can probably build libs by hacking the build scripts
| [Tuesday 08 February 2011] [08:47:56] <mikko>	but to keep things somewhat sane for mingw32/visual studio we only support dlls
| [Tuesday 08 February 2011] [08:48:10] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r5dcbc34 10/ src/zmq.cpp : 
| [Tuesday 08 February 2011] [08:48:11] <CIA-21>	zeromq2: zmq_poll with no fds behaves decently
| [Tuesday 08 February 2011] [08:48:11] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/g191uU
| [Tuesday 08 February 2011] [08:48:46] <zchrish>	But I see a .lib in the msvc2008 output.
| [Tuesday 08 February 2011] [08:49:00] <mikko>	thats the import library
| [Tuesday 08 February 2011] [08:49:07] <zchrish>	Oh, ok.
| [Tuesday 08 February 2011] [09:00:28] <zchrish>	mikko: Is WIN7 required to use the DLL?
| [Tuesday 08 February 2011] [09:02:54] <ianbarber>	sustrik/mikko: any thoughts on best way to debug if I see PGM packets from wireshark on my reciever host, but am not getting anything from 0MQ listening on that host
| [Tuesday 08 February 2011] [09:07:48] <sustrik>	check whether the multicast addresses and ports match on publisher and receiver
| [Tuesday 08 February 2011] [09:08:39] <ianbarber>	yep, definitely match
| [Tuesday 08 February 2011] [09:08:46] <ianbarber>	subscribe is ""
| [Tuesday 08 February 2011] [09:08:57] <ianbarber>	(as well)
| [Tuesday 08 February 2011] [09:09:13] <sustrik>	then you can place breakpoint to pgm_socket_t::recv()
| [Tuesday 08 February 2011] [09:09:28] <sustrik>	to see whether the data are getting from openPGM to 0MQ
| [Tuesday 08 February 2011] [09:16:20] <signalseeker>	 Is a pdf version of the zmq guide available?
| [Tuesday 08 February 2011] [09:17:34] <mikko>	zchrish: i wouldn't think so
| [Tuesday 08 February 2011] [09:17:52] <zchrish>	OK.
| [Tuesday 08 February 2011] [09:18:05] <mikko>	might need the visual studio 2008 redist libs
| [Tuesday 08 February 2011] [09:18:23] <ianbarber>	sustrik: it's not breaking in there, so it looks like 0MQ isn't seeing the packets
| [Tuesday 08 February 2011] [09:33:35] <sustrik>	ianbarber: ask steve-o then
| [Tuesday 08 February 2011] [09:33:41] <ianbarber>	steve-o: is there anything to check whether libpgm can see the packets on a host, for example? I've can see them in wireshark, but 0MQ doesn't seem to be getting them. 
| [Tuesday 08 February 2011] [09:33:58] <ianbarber>	was just about to, and did :)
| [Tuesday 08 February 2011] [09:34:30] <Steve-o>	mmm
| [Tuesday 08 February 2011] [09:34:56] <Steve-o>	You can try increasing the log level, i.e. PGM_MIN_LOG_LEVEL=TRACE
| [Tuesday 08 February 2011] [09:35:43] <ianbarber>	where would the logging go?
| [Tuesday 08 February 2011] [09:36:00] <Steve-o>	stdout
| [Tuesday 08 February 2011] [09:36:51] <Steve-o>	is it completely silent in zeromq or a little bit of data then silence?
| [Tuesday 08 February 2011] [09:36:56] <ianbarber>	ah
| [Tuesday 08 February 2011] [09:36:57] <ianbarber>	Trace: Discarded packet for muted receiver
| [Tuesday 08 February 2011] [09:37:07] <ianbarber>	awesome! 
| [Tuesday 08 February 2011] [09:37:13] <ianbarber>	now, why would it do that
| [Tuesday 08 February 2011] [09:37:15] <ianbarber>	:)
| [Tuesday 08 February 2011] [09:39:28] <Steve-o>	a sender would see that on data packets
| [Tuesday 08 February 2011] [09:39:46] <Steve-o>	possible cause is multiple active senders
| [Tuesday 08 February 2011] [09:40:43] <Steve-o>	it's not expected for a SUB socket
| [Tuesday 08 February 2011] [09:41:02] <Steve-o>	only PUBs
| [Tuesday 08 February 2011] [09:45:37] <ianbarber>	hmm, that was definitely on a sub 
| [Tuesday 08 February 2011] [09:45:45] <ianbarber>	but maybe there's something rogue running as well
| [Tuesday 08 February 2011] [09:47:34] <Steve-o>	it is only emitted if the socket is not permitted to receive data
| [Tuesday 08 February 2011] [09:48:05] <Steve-o>	so a SUB socket that cannot recv sounds a bit broken
| [Tuesday 08 February 2011] [09:48:37] <ianbarber>	hmm, that's strange
| [Tuesday 08 February 2011] [09:48:41] <ianbarber>	nothing else running
| [Tuesday 08 February 2011] [09:48:47] <ianbarber>	definitely only triggers when I'm sending on the other host
| [Tuesday 08 February 2011] [09:48:54] <ianbarber>	if i don't send, no output
| [Tuesday 08 February 2011] [09:49:38] <Guthur>	If i was wanting to learn what interface a windows IPC implementation should have where is the best places to look in the source code?
| [Tuesday 08 February 2011] [09:50:07] <ianbarber>	it does mention a send interface as well steve-o
| [Tuesday 08 February 2011] [09:50:09] <ianbarber>	Trace: Create transmit window.
| [Tuesday 08 February 2011] [09:50:09] <ianbarber>	Trace: Binding receive socket to INADDR_ANY
| [Tuesday 08 February 2011] [09:50:09] <ianbarber>	Trace: Binding send socket to interface index 2
| [Tuesday 08 February 2011] [09:50:10] <ianbarber>	Trace: Join multicast group 239.192.0.1 on interface index 2
| [Tuesday 08 February 2011] [09:50:10] <ianbarber>	Trace: Multicast send interface set to 192.168.192.132 index 2
| [Tuesday 08 February 2011] [09:50:11] <ianbarber>	is that normal?
| [Tuesday 08 February 2011] [09:50:28] <Steve-o>	ianbarber: PGM requires a back-channel from recv to sender for reliability
| [Tuesday 08 February 2011] [09:50:36] <ianbarber>	oh, of course
| [Tuesday 08 February 2011] [09:50:40] <ianbarber>	silly me
| [Tuesday 08 February 2011] [09:51:28] <ianbarber>	if you have a sec, could you look at https://gist.github.com/816533 and see if I'm doing something obviously dumb?
| [Tuesday 08 February 2011] [09:51:49] <Steve-o>	on Linux or Windows?
| [Tuesday 08 February 2011] [09:52:11] <Steve-o>	Linux flavour I'm guessing
| [Tuesday 08 February 2011] [09:52:55] <ianbarber>	linux
| [Tuesday 08 February 2011] [09:53:30] <Steve-o>	looks reasonable although you may hit this bug:  https://github.com/zeromq/zeromq2/issues#issue/139
| [Tuesday 08 February 2011] [09:53:50] <sustrik>	Guthur: you would have to start with implementing IOCP poller
| [Tuesday 08 February 2011] [09:54:11] <sustrik>	see select_t, poll_t, epoll_t, devpoll_t and kqueue_t
| [Tuesday 08 February 2011] [09:54:20] <sustrik>	you would have to make something similar
| [Tuesday 08 February 2011] [09:54:26] <sustrik>	presumably called iocp_t
| [Tuesday 08 February 2011] [09:54:34] <Steve-o>	ianbarber: sleeping before zmq_term can usually help diagnosis, basically keeping the socket open a bit longer.
| [Tuesday 08 February 2011] [09:54:54] <Steve-o>	ianbarber: or sending more data.
| [Tuesday 08 February 2011] [09:55:11] <Guthur>	sustrik: ok, thanks
| [Tuesday 08 February 2011] [09:55:27] <ianbarber>	steve-o: I've got the sender sending then sleeping for 1 second, in a loop, so it's c onstant stream of data. At the moment, I just wait on recv in the test code
| [Tuesday 08 February 2011] [09:56:04] <ianbarber>	each send triggers about 4-5 of those muted receiver  notices
| [Tuesday 08 February 2011] [09:56:20] <Guthur>	from MS docs local named pipes would be considerably faster than sockets
| [Tuesday 08 February 2011] [09:56:33] <Guthur>	so maybe worth the look
| [Tuesday 08 February 2011] [09:56:39] <Steve-o>	ianbarber: send me some code, steven.mccoy@miru.hk, I'm working on Windows this morning and I'll have a look later
| [Tuesday 08 February 2011] [09:57:14] <ianbarber>	will do, thanks steve
| [Tuesday 08 February 2011] [09:57:21] <sustrik>	Gurthur: yes, definitely
| [Tuesday 08 February 2011] [10:17:08] <neale1>	sustrik: Have you seen this whitepaper: http://mnb.ociweb.com/mnb/MiddlewareNewsBrief-201004.html
| [Tuesday 08 February 2011] [10:18:41] <drbobbeaty>	Question: Let's say I am using ZMQ/OpenPGM on the epgm: protocol... also let's assume that I have several multicast channels sending data. On the client, is it better to have a single zmq::context_t with 1 thread working for a series of zmq::socket_t connections, each ZMQ_SUB-ed to different multicast channels? Or would it be better to have a 1:1 mapping between the zmq::context_t and it's zmq::socket_t?
| [Tuesday 08 February 2011] [10:21:19] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r889424e 10/ src/ctx.cpp : 
| [Tuesday 08 February 2011] [10:21:19] <CIA-21>	zeromq2: max_sockets honoured precisely
| [Tuesday 08 February 2011] [10:21:19] <CIA-21>	zeromq2: The internal log socket was subtracted from the number of
| [Tuesday 08 February 2011] [10:21:19] <CIA-21>	zeromq2: available sockets. So, if max_sockets was set to 100,
| [Tuesday 08 February 2011] [10:21:19] <CIA-21>	zeromq2: you could create only 99 sockets. Fixed.
| [Tuesday 08 February 2011] [10:21:19] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/g08FfG
| [Tuesday 08 February 2011] [10:34:15] <Guthur>	what is the default max number of sockets per context?
| [Tuesday 08 February 2011] [10:34:34] <Guthur>	and what happens if you try to exceed that
| [Tuesday 08 February 2011] [10:35:20] <Guthur>	oh I've just answered my own question
| [Tuesday 08 February 2011] [10:38:12] <drbobbeaty>	I *believe* the context is a "one per process space" entity, so I *believe* you have one context for any number of sockets in the process, but I just wanted a verification from the designers.
| [Tuesday 08 February 2011] [11:02:38] <sustrik>	Guthur: 512
| [Tuesday 08 February 2011] [11:03:17] <Guthur>	sustrik: is it possible to set it higher?
| [Tuesday 08 February 2011] [11:03:28] <sustrik>	neale1: yep, it's an old one
| [Tuesday 08 February 2011] [11:04:00] <sustrik>	i think there is some discussion with opendds guys on the mailing list or somewhere
| [Tuesday 08 February 2011] [11:04:06] <sustrik>	Guthur: sure
| [Tuesday 08 February 2011] [11:05:03] <sustrik>	drbobbeaty: confirmed
| [Tuesday 08 February 2011] [11:06:40] <drbobbeaty>	sustrik: thank you very much for the confirmation. Appreciated.
| [Tuesday 08 February 2011] [11:07:10] <Guthur>	sustrik: I did a search for max_sockets in the src and couldn't find it
| [Tuesday 08 February 2011] [11:07:19] <Guthur>	is it a build variable
| [Tuesday 08 February 2011] [11:08:45] <sustrik>	src/confing.hpp
| [Tuesday 08 February 2011] [11:10:55] <Guthur>	all there is is max_app_threads = 512,
| [Tuesday 08 February 2011] [11:11:03] <Guthur>	is that equivalent?
| [Tuesday 08 February 2011] [11:12:48] <mikko>	Guthur: https://github.com/zeromq/zeromq2/blob/master/src/config.hpp#L31
| [Tuesday 08 February 2011] [11:13:26] <Guthur>	umm thats called max_app_threads = 512, in my source
| [Tuesday 08 February 2011] [11:13:38] <mikko>	2.0.x ?
| [Tuesday 08 February 2011] [11:14:04] <Guthur>	ah, yeah
| [Tuesday 08 February 2011] [11:28:59] <sustrik>	the theading has changed between 2.0 and 2.1
| [Tuesday 08 February 2011] [11:29:28] <sustrik>	with 2.0 the limit is on *threads* using 0mq sockets
| [Tuesday 08 February 2011] [11:29:47] <sustrik>	in 2.1 the limit is on the number of the sockets themselves
| [Tuesday 08 February 2011] [11:30:19] <Guthur>	I think this may explain a mysterious app crash I was having
| [Tuesday 08 February 2011] [11:30:56] <mikko>	Guthur: on windows?
| [Tuesday 08 February 2011] [11:31:56] <Guthur>	yep
| [Tuesday 08 February 2011] [11:32:31] <Guthur>	but it should have thrown an exception
| [Tuesday 08 February 2011] [11:32:39] <Guthur>	might have been another cause
| [Tuesday 08 February 2011] [11:34:51] <mikko>	running out of filehandles?
| [Tuesday 08 February 2011] [11:35:07] <mikko>	i think there was some shenanigans with filedescriptor count on windows
| [Tuesday 08 February 2011] [11:37:06] <kristsk>	like max 512 per process or so i've heard
| [Tuesday 08 February 2011] [11:37:28] <mikko>	i think it was way less by default
| [Tuesday 08 February 2011] [11:37:32] <mikko>	64 even
| [Tuesday 08 February 2011] [11:38:30] <kristsk>	thats not much.
| [Tuesday 08 February 2011] [11:38:33] <mikko>	https://github.com/zeromq/zeromq2/issues/issue/57
| [Tuesday 08 February 2011] [11:39:19] <sustrik>	64 is the default max descriptors you can poll on on win32
| [Tuesday 08 February 2011] [11:39:30] <mikko>	ah ok
| [Tuesday 08 February 2011] [11:39:30] <sustrik>	i've overloaded the value to 1024 recently
| [Tuesday 08 February 2011] [11:53:57] <Guthur>	I'm not sure what my issue was, the app just silently shutdown, not very helpful at all
| [Tuesday 08 February 2011] [11:55:15] <sustrik>	not even an assertion?
| [Tuesday 08 February 2011] [11:55:46] <Guthur>	nothing, it may not have been ZMQ
| [Tuesday 08 February 2011] [11:55:53] <Guthur>	there was quickfix as well
| [Tuesday 08 February 2011] [11:56:29] <sustrik>	i see
| [Tuesday 08 February 2011] [11:59:44] <Guthur>	well, home time now
| [Tuesday 08 February 2011] [12:09:51] <stockMQ>	Hi.. I am receiving protobuf messages from my zmq socket which i then want to serialize to a file as binary.. this file in turn should be readable by other processes simultaneously.. 
| [Tuesday 08 February 2011] [12:09:57] <stockMQ>	Any pointers?
| [Tuesday 08 February 2011] [12:10:46] <mikko>	one file per message or all messages in one file?
| [Tuesday 08 February 2011] [12:11:24] <stockMQ>	all messages in one file.. the messages are sequentially timestamped
| [Tuesday 08 February 2011] [12:12:22] <stockMQ>	basically the writer will just dump all incoming messages to the file
| [Tuesday 08 February 2011] [12:12:41] <stockMQ>	but the reader processes should be able to read and de serialize them
| [Tuesday 08 February 2011] [12:13:11] <mikko>	how does the reader know that message is not impartial?
| [Tuesday 08 February 2011] [12:14:37] <stockMQ>	by impartial what do you mean?can you elaborate please
| [Tuesday 08 February 2011] [12:15:19] <mikko>	if the writer is writing a message how do the readers know that the message has been fully written?
| [Tuesday 08 February 2011] [12:15:25] <mikko>	are you planning to use locking?
| [Tuesday 08 February 2011] [12:15:39] <stockMQ>	No..basically what i was doing till now is
| [Tuesday 08 February 2011] [12:15:46] <mikko>	and if yes how are you going to sync readers/writers?
| [Tuesday 08 February 2011] [12:15:46] <stockMQ>	intradayFile.Open(dataPath,CFile::modeWrite | CFile::modeNoTruncate | CFile::modeCreate | CFile::shareDenyWrite | CFile::osWriteThrough)
| [Tuesday 08 February 2011] [12:16:00] <mikko>	because you could easily "DoS" yourself by having high rate of messages coming in
| [Tuesday 08 February 2011] [12:16:08] <mikko>	in which case the lock wouldnt be released
| [Tuesday 08 February 2011] [12:16:40] <sustrik>	i would just use a DB
| [Tuesday 08 February 2011] [12:16:54] <stockMQ>	This basically is supposed to allow Shared read.. if the reader process opens the file with appropriate permission
| [Tuesday 08 February 2011] [12:17:14] <stockMQ>	The synchronization is supposed to be handled by the OS
| [Tuesday 08 February 2011] [12:17:44] <stockMQ>	I am working on VC++
| [Tuesday 08 February 2011] [12:18:02] <sustrik>	the OS won't handle the sync for you
| [Tuesday 08 February 2011] [12:18:09] <sustrik>	you have to implement it yourself
| [Tuesday 08 February 2011] [12:18:19] <sustrik>	that's why it's better to use a DB
| [Tuesday 08 February 2011] [12:18:36] <stockMQ>	ok
| [Tuesday 08 February 2011] [12:19:23] <mikko>	i think posix will guarantee that write within a process is atomic
| [Tuesday 08 February 2011] [12:19:25] <mikko>	but thats about it
| [Tuesday 08 February 2011] [12:19:42] <stockMQ>	ok
| [Tuesday 08 February 2011] [12:19:48] <mikko>	between processes
| [Tuesday 08 February 2011] [12:19:58] <mikko>	but that doesn't really help you with readers at all
| [Tuesday 08 February 2011] [12:20:15] <mikko>	and not sure how posix windows is 
| [Tuesday 08 February 2011] [12:20:36] <mikko>	this is what posix says:
| [Tuesday 08 February 2011] [12:20:39] <mikko>	"Atomic/non-atomic: A write is atomic if the whole amount written in one operation is not interleaved with data from any other process. This is useful when there are multiple writers sending data to a single reader. Applications need to know how large a write request can be expected to be performed atomically. "
| [Tuesday 08 February 2011] [12:21:19] <stockMQ>	My understanding was that CFile::ShareDenyWrite is a flag that tells the operating system not to permit any other process to write to your file while you have it open.
| [Tuesday 08 February 2011] [12:21:54] <mikko>	stockMQ: it will probably but what about if you have a constant stream of messages coming in?
| [Tuesday 08 February 2011] [12:22:12] <stockMQ>	and shareRead would allow it to be read simultaneously
| [Tuesday 08 February 2011] [12:22:30] <stockMQ>	yes u r right.. i had that in mind.. but wanted to check that heuristically
| [Tuesday 08 February 2011] [12:22:42] <mikko>	writer will block the readers
| [Tuesday 08 February 2011] [12:23:03] <mikko>	usually
| [Tuesday 08 February 2011] [12:23:19] <mikko>	if you have readers reading while the writer is writing you might end up with partial / incomplete data
| [Tuesday 08 February 2011] [12:23:39] <mikko>	then you need to track if the message is fully written or not
| [Tuesday 08 February 2011] [12:24:16] <neale1>	mikko: did you want to try enabling the clrzmq build for s390x to see how it goes?
| [Tuesday 08 February 2011] [12:24:39] <mikko>	neale1: i can at some point, still at work for about an hour
| [Tuesday 08 February 2011] [12:24:59] <neale1>	no worries
| [Tuesday 08 February 2011] [12:25:06] <stockMQ>	yes u r right.. Hence i planned to first write it to a file..see how the readers behave and then switch to a DB.. to learn along the process as well
| [Tuesday 08 February 2011] [12:26:45] <stockMQ>	I have received suggestions here like Kyoto cabinet,BDB etc.. More inputs/suggestions are welcome..Also it would be helpful if there is anyone who has written protobufs to a file can share his/her experience
| [Tuesday 08 February 2011] [12:29:04] <mikko>	do you need to keep this data?
| [Tuesday 08 February 2011] [12:29:12] <stockMQ>	yes
| [Tuesday 08 February 2011] [12:29:24] <stockMQ>	basically these are stock trade data..
| [Tuesday 08 February 2011] [12:29:32] <stockMQ>	they need to be kept for back analysis
| [Tuesday 08 February 2011] [12:29:52] <mikko>	and this is on windows?
| [Tuesday 08 February 2011] [12:30:04] <stockMQ>	and there could be more than one analysis tool accessing the data and hence the parallel readers
| [Tuesday 08 February 2011] [12:30:05] <stockMQ>	correct
| [Tuesday 08 February 2011] [12:31:01] <mikko>	do you want to keep the raw data or the results of the analysis?
| [Tuesday 08 February 2011] [12:31:08] <stockMQ>	The raw data
| [Tuesday 08 February 2011] [12:31:30] <stockMQ>	the analysis tools they basically read the data..do their stuff and display
| [Tuesday 08 February 2011] [12:31:32] <mikko>	so you want to be able to get historic data for time periods etc?
| [Tuesday 08 February 2011] [12:31:38] <stockMQ>	yess
| [Tuesday 08 February 2011] [12:31:44] <mikko>	do you want to be able to query the data?
| [Tuesday 08 February 2011] [12:31:57] <stockMQ>	till now i was copying the protobufs to struct and then writing the structs
| [Tuesday 08 February 2011] [12:32:09] <stockMQ>	now i want to bypass the structs and directly write the protobufs
| [Tuesday 08 February 2011] [12:33:12] <mikko>	the data you are receiveing, what kind of data is it?
| [Tuesday 08 February 2011] [12:33:13] <stockMQ>	yes.. query for the time window..nothing complex
| [Tuesday 08 February 2011] [12:33:15] <stockMQ>	as for nw
| [Tuesday 08 February 2011] [12:33:17] <mikko>	numbers, text?
| [Tuesday 08 February 2011] [12:33:52] <stockMQ>	both..mostly numbers.. text are just names of the Stock scrip
| [Tuesday 08 February 2011] [12:34:09] <mikko>	what sort of consistency requirements do you have for the data?
| [Tuesday 08 February 2011] [12:35:21] <mikko>	or maybe more accurate question would be resilience requirements
| [Tuesday 08 February 2011] [12:36:14] <mikko>	for example is it ok to fsync to disk every 10 seconds and if your system crashes you lose 10 seconds of data currently in buffers?
| [Tuesday 08 February 2011] [12:36:40] <stockMQ>	well.. if it is better not to lose any data :)
| [Tuesday 08 February 2011] [12:36:59] <stockMQ>	the analysis are going to be sensitive to loss of data
| [Tuesday 08 February 2011] [12:39:19] <mikko>	it's not an easy engineering task in that case
| [Tuesday 08 February 2011] [12:41:09] <mikko>	does the data need to be consistent on all consumers all the time?
| [Tuesday 08 February 2011] [12:41:49] <stockMQ>	I understand.. In fact to convince the management to go for DB.. i need to first implement a prototype writing it to a file and show them how the readers fair.
| [Tuesday 08 February 2011] [12:41:51] <kristsk>	CAP is a bitch.
| [Tuesday 08 February 2011] [12:42:05] <mikko>	yes, i was thinking this in terms of cap theorem
| [Tuesday 08 February 2011] [12:42:23] <stockMQ>	yes. basically more than one instance of a tool would be accessing it 
| [Tuesday 08 February 2011] [12:42:25] <stockMQ>	so yes
| [Tuesday 08 February 2011] [12:42:32] <stockMQ>	CAP? please enlighten
| [Tuesday 08 February 2011] [12:43:03] <mikko>	http://en.wikipedia.org/wiki/CAP_theorem
| [Tuesday 08 February 2011] [12:43:41] <kristsk>	consistency, availability, partitioning - choose any two.
| [Tuesday 08 February 2011] [12:44:35] <stockMQ>	C and A
| [Tuesday 08 February 2011] [12:44:38] <ianbarber>	stockMQ: you might have more success in writing straight out to a file, less disk seeks
| [Tuesday 08 February 2011] [12:44:56] <ianbarber>	the kafka guys talk about that a bit on their site
| [Tuesday 08 February 2011] [12:45:31] <mikko>	ianbarber: the problematic thing is that the processes reading the files are external
| [Tuesday 08 February 2011] [12:45:34] <mikko>	unlikely with kafka
| [Tuesday 08 February 2011] [12:45:47] <kristsk>	kafka ?
| [Tuesday 08 February 2011] [12:45:57] <mikko>	http://sna-projects.com/kafka/
| [Tuesday 08 February 2011] [12:46:02] <ianbarber>	mikko: oh, i see. I was thinking write file for backanalysis, 0MQ for distribution
| [Tuesday 08 February 2011] [12:46:03] <kristsk>	oh.
| [Tuesday 08 February 2011] [12:46:23] <mikko>	ianbarber: the process writing file is a subscriber as far as i understood
| [Tuesday 08 February 2011] [12:46:32] <mikko>	and the analysis tools read the file and create reports and such
| [Tuesday 08 February 2011] [12:47:00] <mikko>	so what you are effectively creating is a database 
| [Tuesday 08 February 2011] [12:47:02] <stockMQ>	that is right Mikko
| [Tuesday 08 February 2011] [12:47:27] <ianbarber>	yeah, sounds like a database and replication
| [Tuesday 08 February 2011] [12:48:08] <mikko>	so, without knowing the application / architecture very deeply somehow i would be inclined to say that it makes sense to investigate existing database technologies before going through all the hurdles
| [Tuesday 08 February 2011] [12:49:30] <mikko>	maybe you have volatile database for quick access to data and push to another queue which warehouses the data
| [Tuesday 08 February 2011] [12:49:50] <mikko>	very hard to say without knowing much about the application or the overall architecture
| [Tuesday 08 February 2011] [12:50:55] <stockMQ>	In a nutshell.. The exchange multicasts feed which contains the Intra day data.. I have intercepted this feed and then implemented a PUB
| [Tuesday 08 February 2011] [12:51:58] <kristsk>	uh, kafka is java-ish...
| [Tuesday 08 February 2011] [12:52:00] <stockMQ>	The SUBs need to dump this data somewhere.. which should be accessible to the Analysis tools during market hours for intra day analysis and after market hours for back analysis
| [Tuesday 08 February 2011] [12:52:47] <stockMQ>	After market hours, the write will not be happening..so it will be only reads.
| [Tuesday 08 February 2011] [12:52:56] <stockMQ>	The hurdle is during market hours
| [Tuesday 08 February 2011] [12:53:09] <kristsk>	umm, isnt pub/sub kinda "you weren't here, you missed, sorry" ?
| [Tuesday 08 February 2011] [12:53:38] <stockMQ>	yes that is right
| [Tuesday 08 February 2011] [12:53:52] <stockMQ>	hence the PUB also need to keep a copy of the data
| [Tuesday 08 February 2011] [12:53:54] <mikko>	pub/sub is like a radio broadcast (a metaphore sustrik tends to use)
| [Tuesday 08 February 2011] [12:54:05] <mikko>	when your receiver is on you will receive the broadcast
| [Tuesday 08 February 2011] [12:54:12] <stockMQ>	If any SUB failed to connect on time..it should be able to borrow the missed data from PUB
| [Tuesday 08 February 2011] [12:54:50] <mikko>	you can use identities for the subscribers 
| [Tuesday 08 February 2011] [12:55:34] <kristsk>	how many subscribers? maye you could make a queue per "subscriber"?
| [Tuesday 08 February 2011] [12:56:24] <stockMQ>	Well hard to say..to start with internally it will be around 10.. but it can scale quickly
| [Tuesday 08 February 2011] [12:57:45] <kristsk>	umyeah, ten-folding data probably is not a good idea.
| [Tuesday 08 February 2011] [12:57:46] <mikko>	so effetively you want separate req/rep socket on the publisher where subscribers can ask for a delta
| [Tuesday 08 February 2011] [12:58:25] <mikko>	is subscriber is offline for let's say 10 minutes it could ask the publisher through REQ for the last ten minutes
| [Tuesday 08 February 2011] [12:58:39] <mikko>	to get the missing pieces
| [Tuesday 08 February 2011] [12:59:02] <stockMQ>	yes .. that is going to be phase 2.. for now the market hours are known to all.. so the SUBs take up the responsiblity of listening before the market opens
| [Tuesday 08 February 2011] [12:59:34] <stockMQ>	yes somewhat like that
| [Tuesday 08 February 2011] [12:59:39] <mikko>	anyway, gotta commute home ->
| [Tuesday 08 February 2011] [13:00:01] <stockMQ>	ohkk..can i catchu later?
| [Tuesday 08 February 2011] [13:04:10] <sustrik>	stockMQ: you should also be concerned about HD performance
| [Tuesday 08 February 2011] [13:04:28] <sustrik>	if the feed is fast, as it tends to be with market data
| [Tuesday 08 February 2011] [13:04:42] <sustrik>	you may not be able to write the data to the HD fast enough
| [Tuesday 08 February 2011] [13:05:16] <stockMQ>	ok
| [Tuesday 08 February 2011] [13:06:20] <stockMQ>	So what would be the right approach in your opinion
| [Tuesday 08 February 2011] [13:07:22] <sustrik>	depends on details
| [Tuesday 08 February 2011] [13:07:35] <sustrik>	like, are you NASDAQ?
| [Tuesday 08 February 2011] [13:07:50] <sustrik>	if so, a single HD won't be enough
| [Tuesday 08 February 2011] [13:08:15] <sustrik>	if you are just a small trading firm getting modest amount of market data
| [Tuesday 08 February 2011] [13:08:19] <sustrik>	it may suffice though
| [Tuesday 08 February 2011] [13:08:34] <kristsk>	SSD then heh
| [Tuesday 08 February 2011] [13:08:53] <sustrik>	SSD is better in terms of latencies
| [Tuesday 08 February 2011] [13:09:12] <sustrik>	the throughput is similar to standard HD
| [Tuesday 08 February 2011] [13:09:25] <sustrik>	what you need is either software load balancer
| [Tuesday 08 February 2011] [13:09:30] <sustrik>	or a RAID
| [Tuesday 08 February 2011] [13:09:34] <sustrik>	SAN maybe...
| [Tuesday 08 February 2011] [13:09:44] <stockMQ>	ok
| [Tuesday 08 February 2011] [13:10:00] <sustrik>	in any case i would not try to implement a database myself
| [Tuesday 08 February 2011] [13:10:05] <kristsk>	netwrokish san would actually ensure no data gets lost
| [Tuesday 08 February 2011] [13:10:17] <sustrik>	it takes tens of manyears to do it properly
| [Tuesday 08 February 2011] [13:12:39] <stockMQ>	Actually the Interceptor aggregates the data and then Publishes it.. so the data received by the SUB will be lesser and slower than the actual feed received by the interceptor
| [Tuesday 08 February 2011] [13:13:09] <stockMQ>	Any suggestions for DBs.. open source
| [Tuesday 08 February 2011] [13:14:27] <kristsk>	pg ?
| [Tuesday 08 February 2011] [13:14:32] <sustrik>	given you need very little functionality, i would check those new nosql projects
| [Tuesday 08 February 2011] [13:14:33] <kristsk>	postgre
| [Tuesday 08 February 2011] [13:14:44] 	 * sustrik is not an expert though
| [Tuesday 08 February 2011] [13:15:01] <stockMQ>	like Kyoto cabinet?
| [Tuesday 08 February 2011] [13:15:32] <stockMQ>	or
| [Tuesday 08 February 2011] [13:15:33] <stockMQ>	http://en.wikipedia.org/wiki/Berkeley_DB
| [Tuesday 08 February 2011] [13:15:39] <stockMQ>	any users here already?
| [Tuesday 08 February 2011] [13:20:52] <stockMQ>	I think Mikko had used Kyoto
| [Tuesday 08 February 2011] [13:28:17] <stockMQ>	so to summarize.. DB seems to be the only sane solution.. Is that right
| [Tuesday 08 February 2011] [14:03:21] <stockMQ>	What would be the behaviour of the sockets if it is kept idle say overnight..
| [Tuesday 08 February 2011] [14:06:23] <Guthur>	One would hope it is still there in the morning
| [Tuesday 08 February 2011] [15:06:41] <cremes>	Guthur: max_sockets in src/config.hpp
| [Tuesday 08 February 2011] [15:06:55] <cremes>	it defaults to 512; i usually override it to 10k for my own use
| [Tuesday 08 February 2011] [15:33:58] <Guthur>	cremes, cheers, I was looking in the wrong src version, pre-2.1 it was just a thread count
| [Tuesday 08 February 2011] [15:34:22] <cremes>	Guthur: ah, ok
| [Tuesday 08 February 2011] [15:44:45] <andrewvc>	any idea what to make of nbytes != -1 (mailbox.cpp:241) errors in zmq?
| [Tuesday 08 February 2011] [16:32:25] <mikko>	neale1: there?
| [Tuesday 08 February 2011] [16:33:19] <neale1>	mikko: Yes
| [Tuesday 08 February 2011] [16:33:31] <neale1>	mikko: BTW, where r u located?
| [Tuesday 08 February 2011] [16:33:36] <mikko>	neale1: London
| [Tuesday 08 February 2011] [16:33:46] <mikko>	London United Kingdom, not London Canada
| [Tuesday 08 February 2011] [16:33:56] <neale1>	mikko: Better not mention the cricket - I'm an Australian living in the US
| [Tuesday 08 February 2011] [16:34:19] <mikko>	I'm a Finn living in London and know nothing about cricket
| [Tuesday 08 February 2011] [16:34:20] <mikko>	heh
| [Tuesday 08 February 2011] [16:34:23] <taotetek>	gah. anyone here have some pointers on how one could make a pull socket appear as a file (stringio object) using python with pyzmq?  I suppose that's more of a python question than a zeromq question.
| [Tuesday 08 February 2011] [16:34:24] <neale1>	:-)
| [Tuesday 08 February 2011] [16:34:29] <Guthur>	Australians, sure they are always winning the Ashes
| [Tuesday 08 February 2011] [16:34:33] <Guthur>	...oh wait
| [Tuesday 08 February 2011] [16:34:55] <mikko>	so anyway, i added a possibility for SSL tunneling the Hudson slave connection to add transport layer security to the connection
| [Tuesday 08 February 2011] [16:34:58] <Guthur>	hehe, only teasing, I don't much care for cricket
| [Tuesday 08 February 2011] [16:35:22] <mikko>	currently the master-slave connection goes over plain text which is not ideal as the master executes commands on the slave
| [Tuesday 08 February 2011] [16:35:23] <neale1>	It's okay, the poms have waited 20 years to get back at us
| [Tuesday 08 February 2011] [16:35:41] <neale1>	mikko: Do I need to do anything from my end?
| [Tuesday 08 February 2011] [16:35:57] <Guthur>	neale1, Yeah, sure you're just lending it to them for a while
| [Tuesday 08 February 2011] [16:36:14] <bitweiler>	hey what is this uuid-dev package & uuid/e2fsprogs?
| [Tuesday 08 February 2011] [16:36:20] <mikko>	neale1: yes, unfortunately Jenkins doesn't support SSL natively with JNLP connections so it would require setting up stunnel
| [Tuesday 08 February 2011] [16:36:43] <mikko>	i got a ready configuration for stunnel
| [Tuesday 08 February 2011] [16:36:49] <neale1>	mikko: I'm not as paranoid about SSL etc on the Marist system
| [Tuesday 08 February 2011] [16:37:01] <mikko>	neale1: ok
| [Tuesday 08 February 2011] [16:37:15] <mikko>	neale1: i just want to provide options to people as they are contributing the slaves
| [Tuesday 08 February 2011] [16:37:45] <mikko>	you don't need to add TLS but it's there if you want at some point
| [Tuesday 08 February 2011] [16:37:49] <bitweiler>	are those packages needed to run zeromq
| [Tuesday 08 February 2011] [16:38:09] <mikko>	bitweiler: libuuid from efs2progs is, yes
| [Tuesday 08 February 2011] [16:38:20] <bitweiler>	okay
| [Tuesday 08 February 2011] [16:38:40] <neale1>	mikko: Understood
| [Tuesday 08 February 2011] [16:38:42] <mikko>	hopefully rpm specs and debian packages have a dependency on that
| [Tuesday 08 February 2011] [16:39:17] <bitweiler>	slackware does have rpm specs or debian packages
| [Tuesday 08 February 2011] [16:40:19] <sustrik>	andrwvc: that's interesting, are you able to reproduce it?
| [Tuesday 08 February 2011] [16:40:57] <neale1>	bitweller: libuuid keeps changing packages. In Fedora 13 it's efs2progs but in 14 it's in its own libuuid-devel
| [Tuesday 08 February 2011] [16:43:11] <kristsk>	it likes to travel.
| [Tuesday 08 February 2011] [16:43:59] <neale1>	It's a pain the arse trying to keep a spec file that will work on all distributions
| [Tuesday 08 February 2011] [16:47:28] <mikko>	anyway, time to sleep
| [Tuesday 08 February 2011] [16:47:30] <mikko>	good night
| [Tuesday 08 February 2011] [16:48:02] <neale1>	'night
| [Tuesday 08 February 2011] [16:49:22] <bitweiler>	lucky me slackware has it pre-installed
| [Tuesday 08 February 2011] [16:50:20] <Guthur>	I'm making devices with a start and stop, and the way I was going to do it was have poll that would timeout every interval, what would be the opinion of the appropriate balance of performance and response?
| [Tuesday 08 February 2011] [16:50:39] <Guthur>	I am currently using a 750ms polling interval
| [Tuesday 08 February 2011] [16:50:55] <Guthur>	so at worse case it would take 750ms to stop
| [Tuesday 08 February 2011] [16:58:21] <sustrik>	what do you do on the timeout?
| [Tuesday 08 February 2011] [17:03:29] <Guthur>	just check if the stop flag has been set
| [Tuesday 08 February 2011] [17:03:41] <Guthur>	then go start polling again
| [Tuesday 08 February 2011] [17:05:10] <Guthur>	I have a feeling it may actually be necessary when implementing the device in a managed code environment
| [Tuesday 08 February 2011] [17:06:06] <sustrik>	who sets the stop flag?
| [Tuesday 08 February 2011] [17:06:28] <Guthur>	either the user by calling Stop(), or the Dispose method
| [Tuesday 08 February 2011] [17:06:50] <Guthur>	the device is nonblocking 
| [Tuesday 08 February 2011] [17:07:07] <sustrik>	who calls the Stop() methos?
| [Tuesday 08 February 2011] [17:07:10] <sustrik>	method*
| [Tuesday 08 February 2011] [17:07:14] <sustrik>	main thread?
| [Tuesday 08 February 2011] [17:07:26] <sustrik>	a thread different to the device thread?
| [Tuesday 08 February 2011] [17:07:34] <Guthur>	sustrik, you've just given me a bad threading feeling, hehe
| [Tuesday 08 February 2011] [17:07:46] <Guthur>	I have a feeling I am doing something bad
| [Tuesday 08 February 2011] [17:08:00] <sustrik>	well, if it's invoked from another thread
| [Tuesday 08 February 2011] [17:08:08] <sustrik>	you have to synchronise it using a mutex
| [Tuesday 08 February 2011] [17:08:11] <sustrik>	or something
| [Tuesday 08 February 2011] [17:08:19] <sustrik>	which will kill the performance
| [Tuesday 08 February 2011] [17:08:40] <sustrik>	so I would suggest simply calling zmq_term() from the main thread
| [Tuesday 08 February 2011] [17:08:46] <Guthur>	I have a a second flag that actually indicates when it has stopped
| [Tuesday 08 February 2011] [17:09:03] <sustrik>	which will cause next call to libzmq in the device to return ETERM error
| [Tuesday 08 February 2011] [17:09:20] <sustrik>	you can exit the device loop then
| [Tuesday 08 February 2011] [17:09:43] <Guthur>	I never considered that option
| [Tuesday 08 February 2011] [17:10:02] <sustrik>	ETERM was introduced specifically for this scenario
| [Tuesday 08 February 2011] [17:10:09] <sustrik>	shutting down multithreaded programs
| [Tuesday 08 February 2011] [17:10:38] <Guthur>	oh, this could make the code a bit nicer
| [Tuesday 08 February 2011] [17:10:49] <sustrik>	a much more performant
| [Tuesday 08 February 2011] [17:11:06] <sustrik>	as you can avoid mutex that way
| [Tuesday 08 February 2011] [17:37:33] <tiglionabbit>	I'm having a bit of trouble wading through the pretentious documentation.  Is there a simple multiple-chatrooms example for zeromq?
| [Tuesday 08 February 2011] [17:38:22] <tiglionabbit>	like, if I have a variety of incoming long-polling connections each listening for different criteria
| [Tuesday 08 February 2011] [17:43:20] <Steve-o>	if someone is bored I have plenty of x86 atomic ops instructions to convert from GCC format to SunPro format, already done MSVC :D
| [Tuesday 08 February 2011] [17:45:48] <Steve-o>	ending up almost two screen fulls of code to simply perform number++, lol
| [Tuesday 08 February 2011] [18:01:34] <Guthur>	tiglionabbit, do you mean the Guide?
| [Tuesday 08 February 2011] [18:01:45] <tiglionabbit>	yes
| [Tuesday 08 February 2011] [18:02:40] <Guthur>	I actually thought it was quite reasonable, you could just jump straight to code examples from the guide
| [Tuesday 08 February 2011] [18:02:56] <Guthur>	and then refer back to the guide if you get confused
| [Tuesday 08 February 2011] [18:03:51] <Guthur>	there is so many patterns possible with 0MQ that it would be impossible to convey properly with just one code example
| [Tuesday 08 February 2011] [18:03:53] <Guthur>	IMO
| [Tuesday 08 February 2011] [18:07:20] <Guthur>	is there a function that returns the ZMQ_HAUSNUMERO
| [Tuesday 08 February 2011] [18:11:10] <kristsk>	ZMQ_NOTAMUSED
| [Tuesday 08 February 2011] [18:11:14] <kristsk>	sorry.
| [Tuesday 08 February 2011] [18:14:27] <bitweiler>	does zeromq include the mongrel2 server?
| [Tuesday 08 February 2011] [18:15:54] <bitweiler>	just trying to see if I need to install that as well
| [Tuesday 08 February 2011] [18:21:21] <Steve-o>	bitweiler: no, the core zeromq package is just the sockets, not even the bindings any more
| [Tuesday 08 February 2011] [18:23:33] <bitweiler>	oh, okay
| [Tuesday 08 February 2011] [18:41:39] <bitweiler>	does zeromq have any other documentation besides the man pages?
| [Tuesday 08 February 2011] [18:42:03] <bitweiler>	I ask cause I trying to make a package for slackware
| [Tuesday 08 February 2011] [18:44:06] <Guthur>	bitweiler, I think the guide is the only other doc, http://zguide.zeromq.org/chapter:all
| [Tuesday 08 February 2011] [18:44:36] <Guthur>	When connecting a Push to a Pull using TCP, does one need a delay before sending?
| [Tuesday 08 February 2011] [18:45:37] <bitweiler>	Guthur: thanks
| [Tuesday 08 February 2011] [18:46:33] <bitweiler>	things look real promising for this project, i my eyes
| [Tuesday 08 February 2011] [18:47:43] <Guthur>	I think it's pretty cool, the guys have produced some cool tech
| [Tuesday 08 February 2011] [18:49:08] <bitweiler>	hmm, hopeful everything works smoothly with scheme's c-ffi
| [Tuesday 08 February 2011] [18:49:24] <Guthur>	I think there is a racket binding
| [Tuesday 08 February 2011] [18:49:41] <bitweiler>	there's one for chicken as well
| [Tuesday 08 February 2011] [18:49:44] <Guthur>	and someone was working on one for that chicken scheme i think
| [Tuesday 08 February 2011] [18:49:53] <Guthur>	there is also a Common Lisp one
| [Tuesday 08 February 2011] [18:49:53] 	 * bitweiler nods
| [Tuesday 08 February 2011] [18:50:10] <bitweiler>	I aim to test drive the chicken binding
| [Tuesday 08 February 2011] [18:51:29] <Guthur>	On my issue...I seem to be having an issue with REQ<->XREP<-PULL<-PUSH, using TCP
| [Tuesday 08 February 2011] [18:52:01] <Guthur>	it was working OK with inproc, now I have place a delay when connecting at the PUSH end
| [Tuesday 08 February 2011] [19:00:40] <Guthur>	nvm, something else is wrong actually
| [Tuesday 08 February 2011] [19:25:11] <Guthur>	ok I notice some weirdness, is there an upper limit to the timeout for Polling?
| [Tuesday 08 February 2011] [19:27:28] <Guthur>	around 500000 it stops working for me
| [Tuesday 08 February 2011] [19:33:25] <Guthur>	oh the problem disappears in 2.1
| [Tuesday 08 February 2011] [21:20:48] <bitweiler>	is the guide the best introduction to zeromq?
| [Tuesday 08 February 2011] [22:20:55] <bitweiler>	are context's numbers?
| [Tuesday 08 February 2011] [22:29:19] <bitweiler>	DerGuteMoritz: how you make contexts with zmq?
| [Wednesday 09 February 2011] [01:25:06] <gambi>	Can I connect multiple taskers to multiple workers with out a broker inbetween if I don't need a reply from a worker? Basically a FIFO that gets filled by the taskers and emptied by the workers.
| [Wednesday 09 February 2011] [01:25:40] <ianbarber>	not without them all knowing about each other
| [Wednesday 09 February 2011] [01:26:13] <ianbarber>	you could have each client connect to each worker with PUSH/PULL sockets
| [Wednesday 09 February 2011] [01:26:45] <gambi>	yeah, i've started with that ... but realized that PUSH blocks the socket
| [Wednesday 09 February 2011] [01:27:09] <ianbarber>	i would look at using a FORWARDER device, and have that be the stable point in the architecture
| [Wednesday 09 February 2011] [01:27:35] <gambi>	and the single point of failure :(
| [Wednesday 09 February 2011] [01:27:49] <ianbarber>	that's a pretty easy fix, have a couple of them (or more!) 
| [Wednesday 09 February 2011] [01:27:55] <gambi>	ok
| [Wednesday 09 February 2011] [01:28:39] <gambi>	so i do (many tasker) - device forwarder - (many worker) kinda thing?
| [Wednesday 09 February 2011] [01:29:29] <ianbarber>	yeah
| [Wednesday 09 February 2011] [01:30:38] <gambi>	if i don't need an reply from the worker and have to have the fastest possible way to talk to the device which pattern socket type should i use? tasker - (PUB/SUB) - dev forwarder (with stream + callback) - PUSH/PULL - worker?
| [Wednesday 09 February 2011] [01:31:35] <ianbarber>	i would say PUSH PULL in both parts. if you have pub/sub and two forwarders, they'll both get the message, and you'll likely end up with the work done twice
| [Wednesday 09 February 2011] [01:32:01] <ianbarber>	if you don't want to get stuck in a send() you could use ZMQ_NOBLOCk and catch when it can't send
| [Wednesday 09 February 2011] [01:33:50] <gambi>	how can I bind multiple PUSH sockets? I thought I can only PUSH from one tasker?
| [Wednesday 09 February 2011] [01:34:18] <ianbarber>	a single pull socket can have many pushes connected to it
| [Wednesday 09 February 2011] [01:34:25] <gambi>	ah
| [Wednesday 09 February 2011] [01:34:30] <ianbarber>	and vice versa
| [Wednesday 09 February 2011] [01:34:38] <gambi>	didn't know that
| [Wednesday 09 February 2011] [01:34:38] <ianbarber>	basically your forwarder would bind the pull
| [Wednesday 09 February 2011] [01:35:03] <ianbarber>	so lets say you had a forwarder on tcp://129.168.0.1:5566 and tcp://129.168.0.2:5566
| [Wednesday 09 February 2011] [01:35:17] <ianbarber>	you would then connect() both of those on each of your workers
| [Wednesday 09 February 2011] [01:35:23] <ianbarber>	sorry, taskers
| [Wednesday 09 February 2011] [01:35:52] <gambi>	ok
| [Wednesday 09 February 2011] [01:35:52] <ianbarber>	they would fire tasks at each alternatively, and on the other end the pull would fair queue between all the connected incoming
| [Wednesday 09 February 2011] [01:40:29] <ianbarber>	you should only need to bind() on the forwarder side
| [Wednesday 09 February 2011] [01:40:33] <ianbarber>	connect on all the other sides
| [Wednesday 09 February 2011] [01:40:42] <gambi>	ah
| [Wednesday 09 February 2011] [01:40:50] <gambi>	omg. lol ... sorry. yes of course
| [Wednesday 09 February 2011] [01:40:56] <gambi>	i'm new to zeromq
| [Wednesday 09 February 2011] [01:41:06] <ianbarber>	:)
| [Wednesday 09 February 2011] [01:42:12] <gambi>	ianbarber: thx for your help. let me try and write that out. :)
| [Wednesday 09 February 2011] [01:42:27] <ianbarber>	no worries
| [Wednesday 09 February 2011] [03:11:26] <andrewvc_>	I've been getting some weird zmq errs
| [Wednesday 09 February 2011] [03:11:29] <andrewvc_>	I see at some point
| [Wednesday 09 February 2011] [03:11:36] <andrewvc_>	[pid 24407] pipe([14, 15])              = 0
| [Wednesday 09 February 2011] [03:12:32] <andrewvc_>	actually nm
| [Wednesday 09 February 2011] [03:35:43] <skysbird2>	hi, buddies, lovely buddies
| [Wednesday 09 February 2011] [03:35:49] <skysbird2>	i want to know
| [Wednesday 09 February 2011] [03:36:02] <skysbird2>	why i cannot find the zmq_server file after i make install
| [Wednesday 09 February 2011] [03:36:16] <skysbird2>	i downloaded from www.zeromq.org
| [Wednesday 09 February 2011] [03:36:28] <skysbird2>	zeromq-2.0.10.tar.gz for POSIX systems
| [Wednesday 09 February 2011] [03:36:32] <skysbird2>	this one
| [Wednesday 09 February 2011] [03:38:39] <guido_g>	migt be because there is no such file
| [Wednesday 09 February 2011] [03:38:42] <guido_g>	*might
| [Wednesday 09 February 2011] [03:45:30] <skysbird2>	guido_g,but i think this file zmq_server is the kernel start up file of zeromq
| [Wednesday 09 February 2011] [03:48:09] <guido_g>	no it's not
| [Wednesday 09 February 2011] [03:48:20] <guido_g>	read the guide and the appropriate docs
| [Wednesday 09 February 2011] [04:00:39] <skysbird2>	guido_g, i just cannot find appropriate docs, can you recommend one for me?
| [Wednesday 09 February 2011] [04:08:56] <ianbarber>	skysbird2: try the guide http://zguide.zeromq.org/
| [Wednesday 09 February 2011] [04:09:14] <ianbarber>	zeromq doesn't have a daemon, it's a library
| [Wednesday 09 February 2011] [04:12:10] <skysbird2>	ianbarber,oh ,thank you
| [Wednesday 09 February 2011] [04:12:27] <skysbird2>	i 've seen some document said it has zmq_server....
| [Wednesday 09 February 2011] [04:12:43] <skysbird2>	http://www.zeromq.org/code:examples-exchange#toc3
| [Wednesday 09 February 2011] [04:12:45] <skysbird2>	like this
| [Wednesday 09 February 2011] [04:13:02] <guido_g>	outdated
| [Wednesday 09 February 2011] [04:13:25] <skysbird2>	oh
| [Wednesday 09 February 2011] [04:13:31] <ianbarber>	the hint is at the top "WARNING: This text is deprecated and refers to an old version of MQ. It remains here for historical interest. DO NOT USE THIS TO LEARN MQ."
| [Wednesday 09 February 2011] [04:15:40] <skysbird2>	oh
| [Wednesday 09 February 2011] [04:16:22] <skysbird2>	so is there some amq middleware like OpenAMQ build on zeroMQ?
| [Wednesday 09 February 2011] [04:18:11] <ianbarber>	i would really take a skim through the guide - 0MQ uses a different set of ideas
| [Wednesday 09 February 2011] [04:19:07] <ianbarber>	as an answer though - there are devices, which are similar, but intetionally simpler, and it's also a lot easier to write your own, so the idea is that you will have several small, specific devices in an architecture rather than one big broker
| [Wednesday 09 February 2011] [04:20:00] <skysbird2>	ok i know
| [Wednesday 09 February 2011] [04:20:04] <skysbird2>	just distribution
| [Wednesday 09 February 2011] [04:20:17] <skysbird2>	because i heard that opemamq will be unsupported
| [Wednesday 09 February 2011] [04:20:21] <skysbird2>	by 2011 
| [Wednesday 09 February 2011] [04:20:39] <skysbird2>	so i just want to find a middleware to replace OpenAMQ
| [Wednesday 09 February 2011] [04:21:47] <guido_g>	http://www.zeromq.org/whitepapers:brokerless  <- for starters
| [Wednesday 09 February 2011] [04:22:48] <ianbarber>	skysbird2: I would say that take a look at http://www.zeromq.org/docs:welcome-from-amqp to work out whether 0MQ is right for you - if not then take a look at other AMQP systems like Rabbit I guess. 
| [Wednesday 09 February 2011] [04:24:52] <mikko>	ianbarber: you got up early
| [Wednesday 09 February 2011] [04:34:30] <ianbarber>	mikko: had a deploy at 6 this morning
| [Wednesday 09 February 2011] [09:00:33] <Guthur>	Are shareable (between threads) sockets being worked on
| [Wednesday 09 February 2011] [09:00:38] <Guthur>	it would be a nice to have
| [Wednesday 09 February 2011] [09:01:14] <mikko>	no, i dont think they are
| [Wednesday 09 February 2011] [09:01:26] <mikko>	there should be no need for such a thing
| [Wednesday 09 February 2011] [09:01:36] <mikko>	if you share you need to lock
| [Wednesday 09 February 2011] [09:02:21] <Guthur>	yeah in general I suppose there isn't much need
| [Wednesday 09 February 2011] [09:05:32] <Guthur>	curious more than anything
| [Wednesday 09 February 2011] [10:06:52] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r80ac398 10/ (14 files in 2 dirs): 
| [Wednesday 09 February 2011] [10:06:52] <CIA-21>	zeromq2: Initial implementation of reaper thread.
| [Wednesday 09 February 2011] [10:06:52] <CIA-21>	zeromq2: Reaper thread destroys the socket asynchronously.
| [Wednesday 09 February 2011] [10:06:52] <CIA-21>	zeromq2: zmq_term() can be interrupted by a signal (EINTR).
| [Wednesday 09 February 2011] [10:06:52] <CIA-21>	zeromq2: zmq_socket() will return ETERM after zmq_term() was called.
| [Wednesday 09 February 2011] [10:06:53] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/gQddej
| [Wednesday 09 February 2011] [10:16:57] <cremes>	ooh, a reaper thread! just what we need to get rid of the zmq_term blocking behavior
| [Wednesday 09 February 2011] [10:17:04] <cremes>	glad to see some progress on that piece
| [Wednesday 09 February 2011] [10:20:45] <sustrik>	cremes: give it a try please
| [Wednesday 09 February 2011] [10:20:54] <sustrik>	does it solve the Ctrl+C problem?
| [Wednesday 09 February 2011] [10:21:35] <cremes>	sustrik: i'll try it out in a few hours; i'm in the middle of a refactoring and don't want to interrupt it just yet
| [Wednesday 09 February 2011] [10:21:45] <cremes>	i'll post my results here
| [Wednesday 09 February 2011] [10:22:17] <sustrik>	great, thanks
| [Wednesday 09 February 2011] [10:52:10] <andrewvc_>	cremes: around?
| [Wednesday 09 February 2011] [10:53:03] <cremes>	andrewvc_: yep, but a tad busy... got something quick?
| [Wednesday 09 February 2011] [10:53:21] <andrewvc_>	mmm, just wondering if you've seen nbytes = -1 errors in ffi-rzmq before
| [Wednesday 09 February 2011] [10:53:26] <andrewvc_>	err != -1  I mean
| [Wednesday 09 February 2011] [10:53:40] <andrewvc_>	followed by libzmq quitting
| [Wednesday 09 February 2011] [10:53:57] <cremes>	yes, i've seen that assertion before...
| [Wednesday 09 February 2011] [10:54:10] <cremes>	um... are you on latest master or are you using 2.1 release?
| [Wednesday 09 February 2011] [10:54:14] <andrewvc_>	master
| [Wednesday 09 February 2011] [10:54:28] <andrewvc_>	2.1 release doesn't seem to work with FDs for me
| [Wednesday 09 February 2011] [10:54:57] <cremes>	interesting... i used to see that assertion on 2.1 release but i upgraded to master about a month ago and forgot about it
| [Wednesday 09 February 2011] [10:55:14] <cremes>	is it reproducible or is it a heisenbug?
| [Wednesday 09 February 2011] [10:55:32] <cremes>	also, are you on osx or linux?
| [Wednesday 09 February 2011] [10:55:36] <andrewvc_>	linux
| [Wednesday 09 February 2011] [10:55:42] <andrewvc_>	totally reproduces
| [Wednesday 09 February 2011] [10:55:48] <andrewvc_>	can get it in this one exchange of messages
| [Wednesday 09 February 2011] [10:55:51] <andrewvc_>	always the same message
| [Wednesday 09 February 2011] [10:56:01] <andrewvc_>	I tried changing the message content, no diff
| [Wednesday 09 February 2011] [10:56:57] <cremes>	put up a gist and i'll try to look at it later; i need to get back to work
| [Wednesday 09 February 2011] [10:57:27] <andrewvc_>	cool, can do
| [Wednesday 09 February 2011] [11:09:38] <andrewvc_>	sustrik around?
| [Wednesday 09 February 2011] [11:20:50] <Guthur>	When the it says: Never initialize the same zmq_msg_t twice.
| [Wednesday 09 February 2011] [11:20:58] <Guthur>	does that mean reuse the msg
| [Wednesday 09 February 2011] [11:21:49] <Guthur>	or does it mean close and then init
| [Wednesday 09 February 2011] [11:24:05] <pieterh>	Guthur, close followed by init is ok afaics
| [Wednesday 09 February 2011] [11:24:16] <mikko>	it's ok
| [Wednesday 09 February 2011] [11:24:26] <mikko>	initing twice without close will leak
| [Wednesday 09 February 2011] [11:24:27] <pieterh>	Where does it say not to init twice?
| [Wednesday 09 February 2011] [11:24:49] <Guthur>	pieterh: http://api.zeromq.org/zmq_msg_init.html
| [Wednesday 09 February 2011] [11:24:53] <Guthur>	second caution
| [Wednesday 09 February 2011] [11:25:30] <pieterh>	Guthur, ah, it's wrong, afaik, you might want to signal that to Mato or send a patch
| [Wednesday 09 February 2011] [11:26:18] <Guthur>	pieterh: which part is wrong?
| [Wednesday 09 February 2011] [11:26:38] <Guthur>	assume it is fine to pass a msg directly from a recv to a send
| [Wednesday 09 February 2011] [11:26:52] <Guthur>	I assume*
| [Wednesday 09 February 2011] [11:27:26] <andrewvc>	pieterh, if you can spare a minute. Any idea what would cause a bad file descriptor error followed by nbytes != -1 error in ZMQ
| [Wednesday 09 February 2011] [11:27:34] <pieterh>	Guthur, it should probably say, "Never initialize the same zmq_msg_t twice without first doing zmq_msg_close."
| [Wednesday 09 February 2011] [11:27:55] <pieterh>	andrewvc, did you check strerror?
| [Wednesday 09 February 2011] [11:28:47] <pieterh>	andrewvc, uhm, I guess "bad file descriptor" is the error string?
| [Wednesday 09 February 2011] [11:28:52] <andrewvc>	yeah
| [Wednesday 09 February 2011] [11:28:57] <andrewvc>	I have that, followed by
| [Wednesday 09 February 2011] [11:28:58] <pieterh>	what's the context where you get the error?
| [Wednesday 09 February 2011] [11:29:07] <andrewvc>	sure, it's right after a send operation
| [Wednesday 09 February 2011] [11:29:15] <Guthur>	pieterh: ah ok, I'll mention it to mato, then
| [Wednesday 09 February 2011] [11:29:26] <andrewvc>	I get bad file descriptor, then it complains about mailbox.cpp:241 nbytes != -1
| [Wednesday 09 February 2011] [11:29:31] <andrewvc>	on the second line
| [Wednesday 09 February 2011] [11:29:31] <Guthur>	or maybe send a patch
| [Wednesday 09 February 2011] [11:29:37] <andrewvc>	I straced it as well
| [Wednesday 09 February 2011] [11:29:51] <pieterh>	andrewvc: possibly a bad bind or connect?
| [Wednesday 09 February 2011] [11:30:01] <pieterh>	don't really know these internals, sorry
| [Wednesday 09 February 2011] [11:30:05] <andrewvc>	well, the sockets are all local, on the loopback.
| [Wednesday 09 February 2011] [11:30:15] <andrewvc>	no worries, thanks though
| [Wednesday 09 February 2011] [11:30:18] <pieterh>	try replacing with ipc instead of tcp
| [Wednesday 09 February 2011] [11:30:28] <pieterh>	just to see what happens
| [Wednesday 09 February 2011] [11:30:38] <andrewvc>	yeah tried that
| [Wednesday 09 February 2011] [11:30:41] <pieterh>	same error?
| [Wednesday 09 February 2011] [11:30:47] <andrewvc>	yeah
| [Wednesday 09 February 2011] [11:31:06] <andrewvc>	actually, I should confirm that I have a mix of sockets, maybe I got the wrong one
| [Wednesday 09 February 2011] [11:31:34] <pieterh>	sounds something like that
| [Wednesday 09 February 2011] [11:32:25] <pieterh>	windows or Linux?
| [Wednesday 09 February 2011] [11:32:37] <andrewvc>	linux
| [Wednesday 09 February 2011] [11:33:07] <pieterh>	this is where we summon sustrik
| [Wednesday 09 February 2011] [11:33:46] <andrewvc>	hehe, that'd be awesome, I've been on the trail of this forever
| [Wednesday 09 February 2011] [11:33:52] <pieterh>	offhand I'd say you're using a socket that failed to bind/connect
| [Wednesday 09 February 2011] [11:34:05] <andrewvc>	well, the thing is, the app works in a stable manner for a while
| [Wednesday 09 February 2011] [11:34:08] <andrewvc>	then it just stops
| [Wednesday 09 February 2011] [11:34:15] <andrewvc>	but it's reproducible
| [Wednesday 09 February 2011] [11:34:25] <andrewvc>	consistently
| [Wednesday 09 February 2011] [11:34:29] <pieterh>	are you using assertions on all zmq_ calls?
| [Wednesday 09 February 2011] [11:35:30] <pieterh>	clearly the socket that zmq is trying to read from is invalid
| [Wednesday 09 February 2011] [11:35:45] <andrewvc>	hmmm, lemme see, I'm using the ruby zeromq library
| [Wednesday 09 February 2011] [11:35:51] <andrewvc>	I've got the source open...
| [Wednesday 09 February 2011] [11:35:55] <bitweiler>	anyone know of any docs that gives examples of how to use chicken's zeromq bindings?
| [Wednesday 09 February 2011] [11:37:59] <pieterh>	bitweiler, the only docs I know of are at http://wiki.call-cc.org/eggref/4/zmq?action=show
| [Wednesday 09 February 2011] [11:38:30] <bitweiler>	thanks I have those, which don't help much
| [Wednesday 09 February 2011] [11:39:06] <pieterh>	andrewvc, if you can reproduce it consistently, I'd suggest making a stripped-down test case
| [Wednesday 09 February 2011] [11:39:17] <pieterh>	quite often as you strip it down you'll see what you're doing wrong
| [Wednesday 09 February 2011] [11:39:19] <andrewvc>	that's the tough part, it's part of a complex app
| [Wednesday 09 February 2011] [11:39:25] <andrewvc>	and it was working fine
| [Wednesday 09 February 2011] [11:39:33] <pieterh>	'was not showing the error'
| [Wednesday 09 February 2011] [11:39:39] <andrewvc>	then all of a sudden it wasn't, I can fiddle with its inputs to get it to repro
| [Wednesday 09 February 2011] [11:39:42] <sustrik>	i am sorry, i have to leave now
| [Wednesday 09 February 2011] [11:39:46] <sustrik>	if there's a problem
| [Wednesday 09 February 2011] [11:39:52] <sustrik>	just send it to the ML
| [Wednesday 09 February 2011] [11:39:55] <andrewvc>	no worries, I'll see if I can figure out how to make a minimal case
| [Wednesday 09 February 2011] [11:40:03] <andrewvc>	maybe I'll record the message flow and make a fake app
| [Wednesday 09 February 2011] [11:40:07] <pieterh>	yeah
| [Wednesday 09 February 2011] [11:40:18] <pieterh>	at least follow what's happening on that specific zmq socket
| [Wednesday 09 February 2011] [11:40:52] <mikko>	can you attach a debugger and check errno on line 241?
| [Wednesday 09 February 2011] [11:41:19] <pieterh>	mikko: "bad file descriptor", said andrew
| [Wednesday 09 February 2011] [11:41:36] <mikko>	ah, i just hopped in. reading the buffer
| [Wednesday 09 February 2011] [11:41:39] <andrewvc>	yeah, it's an inproc socket btw
| [Wednesday 09 February 2011] [11:41:50] <andrewvc>	I switched it to inproc to help debug
| [Wednesday 09 February 2011] [11:42:23] <andrewvc>	tried ipc as well, same deal
| [Wednesday 09 February 2011] [11:42:34] <mikko>	sounds slightly odd
| [Wednesday 09 February 2011] [11:42:41] <andrewvc>	It's a pub/sub if that matters
| [Wednesday 09 February 2011] [11:42:47] <andrewvc>	it works for a little while
| [Wednesday 09 February 2011] [11:43:02] <andrewvc>	I'm not familiar with GDB, but if you don't mind walking me through it
| [Wednesday 09 February 2011] [11:43:10] <mikko>	can you run it inside valgrind just to see that there is nothing random going on with memory ?
| [Wednesday 09 February 2011] [11:43:11] <andrewvc>	I would be game. I have strace output already
| [Wednesday 09 February 2011] [11:43:25] <andrewvc>	mmm, it's a ruby app, not sure if valgrind supports that
| [Wednesday 09 February 2011] [11:43:40] <mikko>	it does
| [Wednesday 09 February 2011] [11:43:52] <mikko>	it doesn't understand about ruby
| [Wednesday 09 February 2011] [11:44:07] <mikko>	i remember seeing this before somewhere
| [Wednesday 09 February 2011] [11:44:21] <andrewvc>	well, so here's some history
| [Wednesday 09 February 2011] [11:44:28] <andrewvc>	I used to see it in odd places
| [Wednesday 09 February 2011] [11:44:33] <andrewvc>	so did cremes
| [Wednesday 09 February 2011] [11:44:50] <andrewvc>	he also uses ffi-rzmq as  a binding
| [Wednesday 09 February 2011] [11:44:52] <andrewvc>	but lately upgrading to master fixed it
| [Wednesday 09 February 2011] [11:45:06] <andrewvc>	until yesterday, now it's back with a vengeance on this one app of mine
| [Wednesday 09 February 2011] [11:45:26] <mikko>	no, i was thinking about the recent new_sndbuf > old_sndbuf (mailbox.cpp:182)
| [Wednesday 09 February 2011] [11:47:55] <pieterh>	andrewvc, if you're getting this no matter what the transport... then I'd say the zmq socket is in an invalid state
| [Wednesday 09 February 2011] [11:48:07] <pieterh>	try simply tracing all work you do with that socket
| [Wednesday 09 February 2011] [11:48:10] <andrewvc>	cool.
| [Wednesday 09 February 2011] [11:48:48] <andrewvc>	yeah, I've got crazy debugging going on right now :) hopefully I'll have something substantial to work off of
| [Wednesday 09 February 2011] [11:49:02] <andrewvc>	is there any call to just ask is this socket ok?
| [Wednesday 09 February 2011] [11:49:16] <andrewvc>	or does it sound like an uncaugh assertion?
| [Wednesday 09 February 2011] [11:53:14] <pieterh>	andrewvc, well, there is no such call but you could do a sanity test...
| [Wednesday 09 February 2011] [11:53:34] <pieterh>	e.g. try a non-blocking recv on the socket
| [Wednesday 09 February 2011] [11:53:48] <andrewvc>	ah, well, it's a PUB socket
| [Wednesday 09 February 2011] [11:53:53] <pieterh>	hang on
| [Wednesday 09 February 2011] [11:54:06] <pieterh>	it's a pub socket... so why are you ending up trying to recv from it?
| [Wednesday 09 February 2011] [11:55:07] 	 * pieterh could be confused here, not sure if mailbox:recv is reading from socket
| [Wednesday 09 February 2011] [11:55:51] <andrewvc>	hmmm, could it be a weird timing thing, maybe some socket is receiving in the background
| [Wednesday 09 February 2011] [11:56:00] <andrewvc>	and it just happens to be at the same time
| [Wednesday 09 February 2011] [11:56:26] <andrewvc>	so it's not actually the PUB socket at all. Or maybe it's the SUB receiving?
| [Wednesday 09 February 2011] [11:56:29] <pieterh>	weird timing things don't usually act reproducibly
| [Wednesday 09 February 2011] [11:56:53] <andrewvc>	yeah, maybe I should split it into two processes, so the sub is separated
| [Wednesday 09 February 2011] [11:57:20] <andrewvc>	oh, i'm not trying to receive
| [Wednesday 09 February 2011] [11:57:27] <andrewvc>	the error is right after a send
| [Wednesday 09 February 2011] [11:58:07] <pieterh>	well, as sustrik said, send the snippet and error message to zeromq-dev...
| [Wednesday 09 February 2011] [11:58:18] <pieterh>	he'll be back later
| [Wednesday 09 February 2011] [11:58:40] <andrewvc>	cool, thanks for your time pieter
| [Wednesday 09 February 2011] [11:58:54] <pieterh>	np
| [Wednesday 09 February 2011] [11:58:54] <andrewvc>	something fishy is going on here
| [Wednesday 09 February 2011] [11:58:56] <andrewvc>	lol
| [Wednesday 09 February 2011] [14:55:04] <mikko>	good evening
| [Wednesday 09 February 2011] [15:00:31] <Guthur>	'evening mikko 
| [Wednesday 09 February 2011] [16:27:30] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r5b82b1b 10/ (7 files): 
| [Wednesday 09 February 2011] [16:27:30] <CIA-21>	zeromq2: Reaper thread waits for commands rather them retrieving them periodically
| [Wednesday 09 February 2011] [16:27:30] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/eNn0wP
| [Wednesday 09 February 2011] [16:35:34] <CIA-21>	zeromq2: 03Martin Sustrik 07master * re947900 10/ builds/msvc/libzmq/libzmq.vcproj : 
| [Wednesday 09 February 2011] [16:35:34] <CIA-21>	zeromq2: reaper added to MSVC build
| [Wednesday 09 February 2011] [16:35:34] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/enwx8O
| [Wednesday 09 February 2011] [16:40:54] <sustrik>	mikko: https://github.com/zeromq/zeromq2/issues#issue/163
| [Wednesday 09 February 2011] [16:41:08] <sustrik>	i have no idea whether it's ok or not
| [Wednesday 09 February 2011] [16:41:35] <mikko>	will check
| [Wednesday 09 February 2011] [16:42:43] <mikko>	majority of the shared libraries and libtool archives i have installed on my machine have executable bit set
| [Wednesday 09 February 2011] [16:42:47] <mikko>	static libraries don't
| [Wednesday 09 February 2011] [16:43:23] 	 * sustrik hasn't a slightest idea
| [Wednesday 09 February 2011] [16:46:17] <mikko>	commented on the issue
| [Wednesday 09 February 2011] [16:47:14] <Guthur>	what would be the use case for zmq_msg_move(3)
| [Wednesday 09 February 2011] [16:47:35] <sustrik>	when you need to move a message payload without copying it?
| [Wednesday 09 February 2011] [16:47:48] <Guthur>	can you not just use the original msg?
| [Wednesday 09 February 2011] [16:48:05] <sustrik>	class X
| [Wednesday 09 February 2011] [16:48:06] <sustrik>	{
| [Wednesday 09 February 2011] [16:48:14] <sustrik>	   message_t msg;
| [Wednesday 09 February 2011] [16:48:28] <sustrik>	    void get_message (message_t *msg_)
| [Wednesday 09 February 2011] [16:48:30] <sustrik>	    {
| [Wednesday 09 February 2011] [16:48:43] <sustrik>	        zmq_msg_move (msg_, &msg);
| [Wednesday 09 February 2011] [16:48:45] <sustrik>	    }
| [Wednesday 09 February 2011] [16:48:46] <sustrik>	}
| [Wednesday 09 February 2011] [16:48:54] <Guthur>	oh ok, cheers
| [Wednesday 09 February 2011] [16:49:02] <sustrik>	:)
| [Wednesday 09 February 2011] [16:49:45] <Guthur>	I suppose I was wondering it there was any reason I should use it when moving a msg directly from one socket to another
| [Wednesday 09 February 2011] [16:50:38] <sustrik>	i don't think so
| [Wednesday 09 February 2011] [16:50:59] <sustrik>	you can pass the original message directly
| [Wednesday 09 February 2011] [16:51:33] <Guthur>	is there any lag when closing the msg for reuse in a multi part msg
| [Wednesday 09 February 2011] [16:51:44] <Guthur>	I'm sort of wildly guessing now though
| [Wednesday 09 February 2011] [16:52:07] <sustrik>	?
| [Wednesday 09 February 2011] [16:52:27] <mikko>	close should be fairly predictable operation
| [Wednesday 09 February 2011] [16:52:54] <Guthur>	Actual release of resources associated with the message object shall be postponed by MQ until all users of the message or underlying data buffer have indicated it is no longer required.
| [Wednesday 09 February 2011] [16:53:04] <sustrik>	yes
| [Wednesday 09 February 2011] [16:53:32] <sustrik>	the buffer is not deallocated until is it pushed to the network
| [Wednesday 09 February 2011] [16:53:55] <Guthur>	will that block close, or is it async
| [Wednesday 09 February 2011] [16:54:45] <sustrik>	it's asyncv
| [Wednesday 09 February 2011] [16:55:11] <sustrik>	zmq_msg_t is not a message itself
| [Wednesday 09 February 2011] [16:55:17] <sustrik>	it's just a pointer to message
| [Wednesday 09 February 2011] [16:55:26] <sustrik>	so what you close is the pointer
| [Wednesday 09 February 2011] [16:55:49] <sustrik>	the message itself may remain in the memory because it may be used from elsewhere
| [Wednesday 09 February 2011] [16:57:04] <Guthur>	ah yes, my thinking was getting a bit off there
| [Wednesday 09 February 2011] [17:04:47] <sustrik>	mikko: btw, any answer from ivan about the AIX build env?
| [Wednesday 09 February 2011] [17:05:22] <mikko>	sustrik: nope
| [Wednesday 09 February 2011] [17:05:30] <mikko>	sustrik: not sure how feasible it is behind a proxy
| [Wednesday 09 February 2011] [17:05:42] <sustrik>	understood
| [Wednesday 09 February 2011] [17:05:59] <sustrik>	i was just curious whether he replied
| [Wednesday 09 February 2011] [17:06:12] <mikko>	effectively they would need to hack around the proxy
| [Wednesday 09 February 2011] [17:06:39] <mikko>	it was very interesting offer as they have HP-UX and AIX 
| [Wednesday 09 February 2011] [17:06:57] <sustrik>	yeah
| [Wednesday 09 February 2011] [17:07:36] <sustrik>	HP has a free programme to allow you to boot and use HP-UX boxes
| [Wednesday 09 February 2011] [17:07:42] <sustrik>	DSPP it is called
| [Wednesday 09 February 2011] [17:07:57] <sustrik>	not sure whether there's a way to do it in regular intervals
| [Wednesday 09 February 2011] [17:09:15] <Rich_Morin>	I would love to try using ZeroMQ under SketchUp's Ruby.  However, I have no idea how to make it work.  Any Rubyists around?
| [Wednesday 09 February 2011] [17:09:45] <Rich_Morin>	The Ruby version (1.8.6, with limited library support) doesn't have sockets, but I've been able to construct a message-based protocol using EM, message files, and WebSockets.
| [Wednesday 09 February 2011] [17:10:13] <mikko>	Rich_Morin: cremes and andrewvc_ are ruby people
| [Wednesday 09 February 2011] [17:10:14] <mikko>	i think
| [Wednesday 09 February 2011] [17:10:24] <andrewvc_>	yeah
| [Wednesday 09 February 2011] [17:10:50] <andrewvc_>	1.8.7 doesn't work right
| [Wednesday 09 February 2011] [17:10:58] <andrewvc_>	the threading model is broken from what I've heard
| [Wednesday 09 February 2011] [17:11:10] <andrewvc_>	I've tried it, it seems to work, then a couple seconds later acts all weird and crashy
| [Wednesday 09 February 2011] [17:11:26] <Rich_Morin>	Threading isn't really an option, in any case. However, you can set up a periodic timer.
| [Wednesday 09 February 2011] [17:11:36] <andrewvc_>	well, even w/o threading 1.8.7 is weird
| [Wednesday 09 February 2011] [17:12:40] <mikko>	sustrik: The virtual systems offered span the HP portfolio. Available operating systems include HP-UX, OpenVMS, Microsoft Windows, Red Hat Enterprise Linux and Novell SuSE Linux. 
| [Wednesday 09 February 2011] [17:12:57] <andrewvc_>	there's a branch of rbzmq by method_missing, that's called 1.8.7 threads. I haven't tried it, not even sure if it's considered usable by anyone
| [Wednesday 09 February 2011] [17:13:17] <sustrik>	mikko: yep, but i think you have to book the time upfront
| [Wednesday 09 February 2011] [17:13:31] <sustrik>	not sure whether you can book periodic uptime
| [Wednesday 09 February 2011] [17:14:21] <mikko>	i guess it wouldn't hurt to ask if anyone has contacts there
| [Wednesday 09 February 2011] [17:14:30] <mikko>	mailing their customer support and asking might be a lost cause
| [Wednesday 09 February 2011] [17:14:45] <sustrik>	we have few friends at HP
| [Wednesday 09 February 2011] [17:15:00] <sustrik>	let me introduce you...
| [Wednesday 09 February 2011] [17:15:15] <mikko>	OpenVMS and HP-UX are both support iirc
| [Wednesday 09 February 2011] [17:15:21] <mikko>	by zeromq i mean
| [Wednesday 09 February 2011] [17:15:41] <sustrik>	yup, but getting hudson work on openvms may be tricky
| [Wednesday 09 February 2011] [17:15:41] <Rich_Morin>	andrewvc_: Does  ZeroMQ support a documented socket protocol?  IE, Can I use EM to proxy the messages via a socket?
| [Wednesday 09 February 2011] [17:15:58] <sustrik>	anyway, i introduce you to the guys doing openvms port
| [Wednesday 09 February 2011] [17:16:05] <sustrik>	they are both hp engineers
| [Wednesday 09 February 2011] [17:16:12] <sustrik>	wait a sec
| [Wednesday 09 February 2011] [17:19:42] <sustrik>	done
| [Wednesday 09 February 2011] [17:19:52] <sustrik>	Rich_Morin: check zmq_tcp(7)
| [Wednesday 09 February 2011] [17:20:27] <Rich_Morin>	tnx!
| [Wednesday 09 February 2011] [17:20:32] <chris_st>	Howdy -- any XCode folks here?  I'd like to build in XCode, and use the Objective-C bindings, and am curious how to do it... never built a library in XCode before!
| [Wednesday 09 February 2011] [17:21:16] <mikko>	sustrik: thanks
| [Wednesday 09 February 2011] [17:22:04] <Rich_Morin>	chris_st: The Cocoa (etc) bindings are also available in MacRuby.
| [Wednesday 09 February 2011] [17:22:31] <chris_st>	Rich_Morin: Thanks!  That's cool.  But I want to build an Obj-C program to use 0MQ.
| [Wednesday 09 February 2011] [17:22:53] <Rich_Morin>	np
| [Wednesday 09 February 2011] [17:23:39] <drbobbeaty>	chris_st: I think the best way is to look at the zmq.hpp file and see how they wrap the C calls into C++ objects. It's a simple conversion to Ocj-C methods from there.
| [Wednesday 09 February 2011] [17:24:03] <sustrik>	there's a objective C binding out there IIRC
| [Wednesday 09 February 2011] [17:24:12] <chris_st>	drbobbeaty: Thanks for the pointer -- appreciated.  I'm going to try JeremyW's code first, since I'm lazy :-)
| [Wednesday 09 February 2011] [17:34:21] <sustrik>	mikko: that was quick :)
| [Wednesday 09 February 2011] [17:41:50] <mikko>	sustrik: yeah
| [Wednesday 09 February 2011] [17:42:00] <mikko>	interesting to see what happens
| [Wednesday 09 February 2011] [17:42:07] <mikko>	now i gotta sleep, long day tomorrow
| [Wednesday 09 February 2011] [17:42:12] <sustrik>	cyl
| [Wednesday 09 February 2011] [17:42:13] <mikko>	good night
| [Wednesday 09 February 2011] [17:56:08] <Rich_Morin>	sustrik: https://github.com/chuckremes/zmqmachine looks like an interesting possibility. I already have an EM script that proxies between files ans WebSockets; it might be possible to mash my proxy up with zmqmachine.
| [Wednesday 09 February 2011] [18:01:52] <cremes>	Rich_Morin: you want to run your code on sketchup ruby, right? i'm not familiar with that... is it a "new" runtime from google?
| [Wednesday 09 February 2011] [18:02:47] <Rich_Morin>	No, it may actually predate Rails.  The Ruby version (1.8.6, with limited library support) doesn't have sockets, but I've been able to construct a message-based protocol using EM, message files, and WebSockets.
| [Wednesday 09 February 2011] [18:03:06] <Rich_Morin>	"want" perhaps overstates the case :-)
| [Wednesday 09 February 2011] [18:03:33] <cremes>	oh, i see
| [Wednesday 09 February 2011] [18:04:01] <cremes>	well, zmqmachine is just a thin wrapper around the ffi-rzmq gem which itself is a thin wrapper around libzmq
| [Wednesday 09 February 2011] [18:04:23] <cremes>	i assume the sketchup runtime can load C extensions if you are playing with EM
| [Wednesday 09 February 2011] [18:04:53] <cremes>	andrewvc_ has been working on a companion gem to ffi-rzmq so that 0mq sockets can be used from EM
| [Wednesday 09 February 2011] [18:04:57] <Rich_Morin>	ouch.  Even if it's possible, it would be nice to avoid.
| [Wednesday 09 February 2011] [18:05:11] <cremes>	what ouch?
| [Wednesday 09 February 2011] [18:06:17] <Rich_Morin>	SketchUp is used by modelers.  I'd like to keep things as lightweight as possible.
| [Wednesday 09 February 2011] [18:06:43] <Rich_Morin>	Thait said, I'm not ruling it out.
| [Wednesday 09 February 2011] [18:06:58] <cremes>	ok; then you'll need to reimplement 0mq in pure ruby because the existing solutions just wrap the 0mq C lib
| [Wednesday 09 February 2011] [18:07:06] <cremes>	that's a lot of work
| [Wednesday 09 February 2011] [18:07:44] <Rich_Morin>	Another possibility would be to hack my EM proxy to speak your socket-based protocol.  Any clues here?
| [Wednesday 09 February 2011] [18:08:10] <Rich_Morin>	The proxy runs under normal Ruby, BTW
| [Wednesday 09 February 2011] [18:10:51] <cremes>	sorry, no clues... the wire protocol in 0mq is documented but i have no particular insight on how to make it work in your situation
| [Wednesday 09 February 2011] [18:12:46] <Rich_Morin>	thanks, anyway
| [Wednesday 09 February 2011] [18:34:24] <msch>	hi, i've got a really strange bug. i've written a very simple zmq setup with PUSH/PULL, the PUSH code seems to work (it exists cleanly) while to PULL code just hangs in socket.recv. anyone care to take a look? https://gist.github.com/819576
| [Wednesday 09 February 2011] [18:35:33] <Seta00>	trying to link to zmq, gcc is giving me "/usr/lib/libzmq.so: could not read symbols: File in wrong format"
| [Wednesday 09 February 2011] [18:35:40] <Seta00>	and I've just built it
| [Wednesday 09 February 2011] [18:35:42] <Seta00>	everything goes fine
| [Wednesday 09 February 2011] [18:36:30] <Seta00>	oh
| [Wednesday 09 February 2011] [18:36:31] <Seta00>	-m 32
| [Wednesday 09 February 2011] [18:36:31] <Seta00>	damn
| [Wednesday 09 February 2011] [18:42:36] <Seta00>	er.. configure is asking me to use --target
| [Wednesday 09 February 2011] [18:42:40] <Seta00>	but --target i386 doesn't work
| [Wednesday 09 February 2011] [18:42:51] <Seta00>	--target=i386 **
| [Wednesday 09 February 2011] [19:07:43] <Seta00>	forgot to install g++-multilib
| [Wednesday 09 February 2011] [19:07:45] <Seta00>	:P
| [Thursday 10 February 2011] [02:37:56] <suzan_shakya>	hi all, can anybody explain me why a single context should be used in a process ?
| [Thursday 10 February 2011] [02:42:17] <Guthur>	suzan_shakya, you can use multiple contexts in a process
| [Thursday 10 February 2011] [02:42:44] <Guthur>	with you want to use inproc transport the sockets need to be created by the same context though
| [Thursday 10 February 2011] [02:43:03] <Guthur>	with/if
| [Thursday 10 February 2011] [02:46:13] <suzan_shakya>	Guthur: thanks
| [Thursday 10 February 2011] [02:46:58] <guido_g>	but is not the canonical way to have more then one context per process
| [Thursday 10 February 2011] [04:54:58] <mikko>	sustrik: http://build.valokuva.org/job/ZeroMQ2-core-master_mingw32-win7/79/console
| [Thursday 10 February 2011] [04:55:04] <mikko>	started failing after reaper changes
| [Thursday 10 February 2011] [05:20:55] <mikko>	man you are fast pieter_hintjens 
| [Thursday 10 February 2011] [05:21:08] <pieter_hintjens>	mikko: huh?
| [Thursday 10 February 2011] [05:21:23] <mikko>	pieter_hintjens: the "What happens when push socket is closed"
| [Thursday 10 February 2011] [05:21:32] <pieterh>	:-)
| [Thursday 10 February 2011] [05:21:36] <mikko>	i had barely read the message and already gmail indicated response from you
| [Thursday 10 February 2011] [05:22:02] <pieterh>	4 minutes is still pretty high latency
| [Thursday 10 February 2011] [05:22:19] <pieterh>	I need to find a way to get alerts on 0MQ list traffic...
| [Thursday 10 February 2011] [09:46:49] <mikko>	pieterh: https://build.valokuva.org/job/zfl-master_ZeroMQ2-master_mingw32/9/console
| [Thursday 10 February 2011] [09:46:54] <mikko>	zfl mingw32 running now
| [Thursday 10 February 2011] [09:47:13] <pieterh>	mikko, nice... there are still a few glitches but most of it builds
| [Thursday 10 February 2011] [09:48:07] <mikko>	fails
| [Thursday 10 February 2011] [10:02:34] <pieterh>	mikko: I've committed further fixes, send me a log of the errors and I'll check them out
| [Thursday 10 February 2011] [10:05:15] <mikko>	pieterh: you should be able to init build on hudson
| [Thursday 10 February 2011] [10:05:20] <mikko>	if you still have your username and pass
| [Thursday 10 February 2011] [10:05:32] <pieterh>	mikko: I have too many pots boiling :-)
| [Thursday 10 February 2011] [10:06:42] <mikko>	https://gist.github.com/73dae202027903631905
| [Thursday 10 February 2011] [10:06:51] <mikko>	looks like include issue
| [Thursday 10 February 2011] [10:07:01] <mikko>	path missing or something
| [Thursday 10 February 2011] [10:07:44] <mikko>	https://github.com/mkoppanen/zfl/commit/b54ea4c22956818f435ee085d01847bb5f6c9335
| [Thursday 10 February 2011] [10:07:50] <mikko>	this is some old fix i did
| [Thursday 10 February 2011] [10:07:56] <mikko>	not sure how relevant that still is
| [Thursday 10 February 2011] [10:10:20] <pieterh>	ah... the errors from zfl_prelude.h are because that file thinks it's building on a Unix box and is looking for Unix include files
| [Thursday 10 February 2011] [10:11:15] <pieterh>	I've not used ming32 for a really long time, so don't recall what's needed here
| [Thursday 10 February 2011] [10:11:16] <mikko>	not fully true
| [Thursday 10 February 2011] [10:11:26] <mikko>	you wouldn't include using '\' on unix ?
| [Thursday 10 February 2011] [10:11:38] <pieterh>	indeed
| [Thursday 10 February 2011] [10:11:41] <pieterh>	:-)
| [Thursday 10 February 2011] [10:11:50] <mikko>	zfl_prelude.h:255 is inside windows defs
| [Thursday 10 February 2011] [10:12:33] <pieterh>	it thinks it's both __MSDOS__ and __UNIX__
| [Thursday 10 February 2011] [10:13:11] <mikko>	regarding the build issue on freebsd someone mailed about
| [Thursday 10 February 2011] [10:13:28] <mikko>	i think a switch in configure would be nice "--with-libzmq=" or so
| [Thursday 10 February 2011] [10:13:44] <pieterh>	well, zfl is by definition dependent on zmq
| [Thursday 10 February 2011] [10:13:45] <mikko>	that could use pkg-config to check the prefix and required flags
| [Thursday 10 February 2011] [10:14:17] <mikko>	it also currently depending on user to specify CFLAGS and LDFLAGS for non-standard location
| [Thursday 10 February 2011] [10:14:35] <pieterh>	right
| [Thursday 10 February 2011] [10:14:41] 	 * pieterh needs to get some food
| [Thursday 10 February 2011] [10:14:51] <pieterh>	mikko, i'm going to leave this to settle for a while and come back to it later
| [Thursday 10 February 2011] [10:14:55] <mikko>	--with-libzmq=/opt/i/installed/libzmq/here style
| [Thursday 10 February 2011] [10:14:56] <mikko>	ok
| [Thursday 10 February 2011] [10:14:57] <pieterh>	may install mingw32 if needed
| [Thursday 10 February 2011] [10:15:11] <mikko>	i can look into patching this
| [Thursday 10 February 2011] [10:15:16] <pieterh>	have gotten the thing to compile on MSVC and almost link successfully... 
| [Thursday 10 February 2011] [10:15:19] <mikko>	i'll send you a mail if i got time to look into it today
| [Thursday 10 February 2011] [10:15:32] <pieterh>	that earns me lunch, in any timezone :-)
| [Thursday 10 February 2011] [10:15:39] <mikko>	true
| [Thursday 10 February 2011] [10:15:56] <pieterh>	cyl
| [Thursday 10 February 2011] [10:16:01] <mikko>	later
| [Thursday 10 February 2011] [11:07:30] <andrewvc>	sustrik: If you're around I have an strace that shows where that nbytes error is I believe
| [Thursday 10 February 2011] [11:07:36] <andrewvc>	https://gist.github.com/820779
| [Thursday 10 February 2011] [11:07:50] <andrewvc>	basically, it looks like close is called on FD 22
| [Thursday 10 February 2011] [11:11:42] <cremes>	andrewvc: fyi, i found (and fixed) a bug in ffi-rzmq
| [Thursday 10 February 2011] [11:11:48] <andrewvc>	oh?
| [Thursday 10 February 2011] [11:12:14] <cremes>	sometimes when a recv failed with rc = -1, eagain is *false* but it was still acting like it was a successful read
| [Thursday 10 February 2011] [11:12:21] <cremes>	i'll push the patch in a minute
| [Thursday 10 February 2011] [11:12:21] <andrewvc>	oh, good catch
| [Thursday 10 February 2011] [11:12:39] <andrewvc>	cool, I'll test it, I wonder if that was related, it sounds like it could have been
| [Thursday 10 February 2011] [11:12:45] <cremes>	i need to do a code clean up... some of my logic is too hard to follow
| [Thursday 10 February 2011] [11:12:48] <cremes>	simpler is better
| [Thursday 10 February 2011] [11:13:12] <andrewvc>	agreed, but don't bash your code, I've found it pretty clear ):
| [Thursday 10 February 2011] [11:13:15] <andrewvc>	:)
| [Thursday 10 February 2011] [11:14:53] <cremes>	andrewvc: you are too kind!
| [Thursday 10 February 2011] [11:14:55] <cremes>	ok, pushed
| [Thursday 10 February 2011] [11:15:04] <andrewvc>	cool, I've got my test suite all up already
| [Thursday 10 February 2011] [11:15:16] <cremes>	give it a try and see if it makes a difference
| [Thursday 10 February 2011] [11:15:33] <cremes>	btw, at the same time i found an error in zmqmachine related to the same thing
| [Thursday 10 February 2011] [11:15:35] <cremes>	i'll push that too
| [Thursday 10 February 2011] [11:16:43] <andrewvc>	sadly, not related
| [Thursday 10 February 2011] [11:17:12] <andrewvc>	i mean, that patch didn't fix this bug
| [Thursday 10 February 2011] [11:17:26] <cremes>	bummer
| [Thursday 10 February 2011] [11:17:39] <cremes>	it's likely a 0mq flaw
| [Thursday 10 February 2011] [11:17:47] <andrewvc>	yeah, I was just about to post to the list
| [Thursday 10 February 2011] [11:17:59] <cremes>	do you have a gist you can share? i have an hour or so today where i can poke at this
| [Thursday 10 February 2011] [11:18:02] <andrewvc>	yep
| [Thursday 10 February 2011] [11:18:16] <andrewvc>	well, so this is interesting in and of itself I guess
| [Thursday 10 February 2011] [11:18:18] <andrewvc>	https://gist.github.com/820779
| [Thursday 10 February 2011] [11:18:30] <andrewvc>	that's an strace to start with, I'll post the ruby code in a sec
| [Thursday 10 February 2011] [11:18:34] <andrewvc>	FD 22 is closed
| [Thursday 10 February 2011] [11:18:45] <andrewvc>	then recvfrom is called on it again later on
| [Thursday 10 February 2011] [11:19:17] <andrewvc>	I think that's the bug, unless I'm missing something, I'm a little shaky on low level syscall semantics
| [Thursday 10 February 2011] [11:20:04] <andrewvc>	FD22 being a unix domain socket, but one that was opened internally, as the ZMQ sockets are all tcp
| [Thursday 10 February 2011] [11:20:34] <andrewvc>	lemme upload the ruby code actually, right now it needs RBX or 1.9.2 to run. I'm working on jruby support (kicking Thin out)
| [Thursday 10 February 2011] [11:20:41] <cremes>	i wonder if FD 22 has some special meaning? i don't have a lot of knowledge about this lower level stuff
| [Thursday 10 February 2011] [11:20:53] <cremes>	cool, i use both
| [Thursday 10 February 2011] [11:21:06] <mikko>	no, it shouldn't have
| [Thursday 10 February 2011] [11:22:38] <andrewvc>	It's opened higher up with 116809 [pid 11284] socketpair(PF_FILE, SOCK_STREAM, 0, [21, 22]) = 0
| [Thursday 10 February 2011] [11:23:53] <andrewvc>	if you want to give the ruby code a shot cremes I can set you up pretty quick, lemme just push a couple things
| [Thursday 10 February 2011] [11:24:20] <cremes>	sure
| [Thursday 10 February 2011] [11:26:12] <andrewvc>	ok, so just a few things, you need either rbx or 1.9.2. then....
| [Thursday 10 February 2011] [11:26:22] <andrewvc>	gem install dripdrop
| [Thursday 10 February 2011] [11:26:49] <andrewvc>	then clone this somewhere git://github.com/andrewvc/socket-motor.git
| [Thursday 10 February 2011] [11:27:23] <andrewvc>	then, inside the socket-motor dir: ruby bin/socket-motor
| [Thursday 10 February 2011] [11:28:30] <andrewvc>	oh you also need: gem install sinatra haml
| [Thursday 10 February 2011] [11:28:59] <andrewvc>	inside socket-motor's example dir, run ./run.sh
| [Thursday 10 February 2011] [11:29:28] <andrewvc>	finally visit localhost:3000 and try putting a message in the chat entry box and hitting send. that'll cause the bin/socket-motor process to die
| [Thursday 10 February 2011] [11:29:33] <andrewvc>	phew
| [Thursday 10 February 2011] [11:29:51] <andrewvc>	yeah, I've been trying to communicate this via strace because the setup is a bit cumbersome
| [Thursday 10 February 2011] [11:34:25] <cremes>	needs hashie/mash too
| [Thursday 10 February 2011] [11:35:35] <andrewvc>	ah crap
| [Thursday 10 February 2011] [11:35:35] <cremes>	andrewvc: another require error, but this one doesn't look like a gem
| [Thursday 10 February 2011] [11:35:37] <cremes>	<internal:lib/rubygems/custom_require>:29:in `require': no such file to load -- socket-motor/messages/req_rep_message (LoadError)
| [Thursday 10 February 2011] [11:35:38] <andrewvc>	gem install hashie
| [Thursday 10 February 2011] [11:35:45] <andrewvc>	oh, forgot to check that in damnit
| [Thursday 10 February 2011] [11:36:36] <andrewvc>	wait, hmm it is there
| [Thursday 10 February 2011] [11:37:45] <cremes>	probably a path issue
| [Thursday 10 February 2011] [11:37:48] <andrewvc>	I've been running it with -I lib/ in the socket motor dir
| [Thursday 10 February 2011] [11:37:49] <andrewvc>	yeah
| [Thursday 10 February 2011] [11:38:28] <andrewvc>	 this is bin/socket-motor yeah
| [Thursday 10 February 2011] [11:39:01] <cremes>	so, what's the right command? ruby -l lib bin/socket-motor doesn't work
| [Thursday 10 February 2011] [11:39:49] <andrewvc>	I start it with ruby -I lib/ bin/socket-motor
| [Thursday 10 February 2011] [11:39:59] <cremes>	ruby -I lib bin/socket-motor works (where -I is an "eye")
| [Thursday 10 February 2011] [11:40:13] <andrewvc>	yep
| [Thursday 10 February 2011] [11:40:26] <cremes>	now i'm getting an in6_addr error (invalid address)
| [Thursday 10 February 2011] [11:40:33] <cremes>	do you have some addresses hard coded?
| [Thursday 10 February 2011] [11:40:40] <cremes>	or ipv6 stuff?
| [Thursday 10 February 2011] [11:40:53] <andrewvc>	nope
| [Thursday 10 February 2011] [11:41:06] <andrewvc>	I disabled it actually
| [Thursday 10 February 2011] [11:41:22] <cremes>	https://gist.github.com/820848
| [Thursday 10 February 2011] [11:41:52] <cremes>	i'm on osx... don't know if that should matter
| [Thursday 10 February 2011] [11:41:58] <andrewvc>	oh, it uses resolv to do a hostname lookup, weird lemme disable that whole block
| [Thursday 10 February 2011] [11:42:08] <andrewvc>	right now it doesn't do anything, it just looks for the first ipv4 addr
| [Thursday 10 February 2011] [11:42:31] <andrewvc>	for a given host
| [Thursday 10 February 2011] [11:43:18] <andrewvc>	prolly an OSX vs linux thing
| [Thursday 10 February 2011] [11:44:06] <cremes>	how can i disable it locally in your code?
| [Thursday 10 February 2011] [11:44:11] <andrewvc>	gem install dripdrop should fix it
| [Thursday 10 February 2011] [11:44:22] <andrewvc>	well hold on one sec
| [Thursday 10 February 2011] [11:44:26] <andrewvc>	pushing...
| [Thursday 10 February 2011] [11:44:31] <cremes>	heh
| [Thursday 10 February 2011] [11:44:39] <andrewvc>	ok pushed, dripdrop 0.9.6  should do it
| [Thursday 10 February 2011] [11:46:42] <cremes>	success
| [Thursday 10 February 2011] [11:46:45] <andrewvc>	nice!
| [Thursday 10 February 2011] [11:47:33] <andrewvc>	basically, this is a websocket <-> ZMQ <-> HTTP <-> Rack bridge
| [Thursday 10 February 2011] [11:47:34] <cremes>	andrewvc: new error:  https://gist.github.com/820863
| [Thursday 10 February 2011] [11:48:11] <andrewvc>	hmm, that's a new one
| [Thursday 10 February 2011] [11:48:48] <cremes>	i'm looking at config.ru... do i need some /swf and /js dirs somewhere?
| [Thursday 10 February 2011] [11:48:59] <andrewvc>	yeah, they're in public
| [Thursday 10 February 2011] [11:49:08] <cremes>	ah, so they are
| [Thursday 10 February 2011] [11:49:19] <andrewvc>	not sure about thin, hmmm
| [Thursday 10 February 2011] [11:49:34] <cremes>	is thin 1.2.7 the right one?
| [Thursday 10 February 2011] [11:50:02] <andrewvc>	oh, I just got it as well, it's a 1.9.2 vs rbx issue hold on lemme pin it down
| [Thursday 10 February 2011] [11:51:01] <andrewvc>	ah, here we go
| [Thursday 10 February 2011] [11:51:02] <andrewvc>	 thin -R config.ru start
| [Thursday 10 February 2011] [11:51:15] <andrewvc>	I was using old style syntax, apparently RBX doesn't mind weirdly
| [Thursday 10 February 2011] [11:52:22] <cremes>	okay, i get the crash
| [Thursday 10 February 2011] [11:52:42] <cremes>	there are a *lot* of moving parts here... this is going to be tough
| [Thursday 10 February 2011] [11:53:01] <andrewvc>	yeah, that's the thing
| [Thursday 10 February 2011] [11:53:10] <cremes>	do you also see the EM crash from run.sh?
| [Thursday 10 February 2011] [11:53:44] <andrewvc>	ohh yeah, now I do, this is the first time i've run it in 1.9.2 in a while, I guess rbx has been shielding me
| [Thursday 10 February 2011] [11:53:46] <andrewvc>	interesting
| [Thursday 10 February 2011] [11:54:01] <cremes>	i'm going to let you chase this a little bit more... :)
| [Thursday 10 February 2011] [11:54:05] <andrewvc>	yeah
| [Thursday 10 February 2011] [11:54:07] <andrewvc>	good find
| [Thursday 10 February 2011] [11:54:18] <cremes>	i find that i fix a *lot* of bugs by running my code across all 3 of the major runtimes
| [Thursday 10 February 2011] [11:54:20] <andrewvc>	i mean, if they're synchronized, that opens up a whole new world
| [Thursday 10 February 2011] [11:54:29] <cremes>	some are more forgiving than others
| [Thursday 10 February 2011] [11:55:33] <cremes>	you might also try MRI 1.8.7p-<whatever is latest> just for giggles
| [Thursday 10 February 2011] [11:55:36] <andrewvc>	hehe
| [Thursday 10 February 2011] [11:55:43] <andrewvc>	yeah, well here's the crazy thing, I've been  running socket-motor in rbx and 1.9.2
| [Thursday 10 February 2011] [11:55:50] <andrewvc>	just never thought to run the rack app in it
| [Thursday 10 February 2011] [11:55:51] <cremes>	i know the bindings don't really have support for it, but it might shed some light
| [Thursday 10 February 2011] [11:56:01] <cremes>	heh
| [Thursday 10 February 2011] [11:56:15] <andrewvc>	I'm looking forward to jruby support in dripdrop, that's around the corner, thin wasn't a great choice
| [Thursday 10 February 2011] [11:56:35] <andrewvc>	thanks for shedding light on this though
| [Thursday 10 February 2011] [11:57:03] <andrewvc>	I guess I should still submit the strace zmq dev, prolly is a zmq bug, shouldn't be possible anyway right?
| [Thursday 10 February 2011] [11:57:32] <cremes>	well, it depends
| [Thursday 10 February 2011] [11:57:59] <cremes>	is your rack app sending a 0mq packet in the right wire format?
| [Thursday 10 February 2011] [11:58:22] <cremes>	i.e. are you using a 0mq socket from rack or something else?
| [Thursday 10 February 2011] [11:58:39] <andrewvc>	nope, it doesn't speak 0mq, it speaks http. Dripdrop lets you drop HTTP in for a req/rep
| [Thursday 10 February 2011] [11:58:55] <andrewvc>	so, I'm guessing EM is going crazy, and terminating strangely
| [Thursday 10 February 2011] [11:59:01] <cremes>	ok, then i don't know
| [Thursday 10 February 2011] [11:59:44] <cremes>	don't you just love bug hunts?
| [Thursday 10 February 2011] [11:59:46] <andrewvc>	yeah, well, the HTTP message gets turned into ZMQ xreq/xrep, then comes back as HTTP
| [Thursday 10 February 2011] [11:59:47] <andrewvc>	hah
| [Thursday 10 February 2011] [12:00:04] <andrewvc>	Ummm, I woke up at 4am yesterday with an idea to fix it, went back to sleep at 4:30. grumpy
| [Thursday 10 February 2011] [12:00:56] <cremes>	so funny... i was just telling my partner that i went to bed at midnight, laid awake for 2 hours and started coding again at 2 until 3
| [Thursday 10 February 2011] [12:01:01] <cremes>	i'm a bit grumpy today myself :)
| [Thursday 10 February 2011] [12:01:16] <cremes>	sometimes it's impossible to turn off my brain
| [Thursday 10 February 2011] [12:01:23] <andrewvc>	lol
| [Thursday 10 February 2011] [12:01:26] <andrewvc>	same
| [Thursday 10 February 2011] [12:01:32] <andrewvc>	btw, apparently that error was unrelated
| [Thursday 10 February 2011] [12:02:13] <andrewvc>	I wasn't handling an HTTP response, so EM died, handled it, now it lives  but zmq still dies, I'm gonna send this off to the list
| [Thursday 10 February 2011] [12:03:01] <andrewvc>	my hunch is there's a bug in my app code, and EM is handling an exception strangely, and ZMQ is dying. I have no proof of this, but that's my feeling
| [Thursday 10 February 2011] [12:04:55] <cremes>	andrewvc: any idea what line of code in dripdrop that this dies on?
| [Thursday 10 February 2011] [12:05:06] <cremes>	have you narrowed that piece down yet?
| [Thursday 10 February 2011] [12:05:10] <andrewvc>	I think that's a red herring, I traced all the way through to ffi-rzmq
| [Thursday 10 February 2011] [12:05:24] <andrewvc>	to right before libzmq send
| [Thursday 10 February 2011] [12:05:38] <andrewvc>	but it's dying trying to recv from a socket
| [Thursday 10 February 2011] [12:05:43] <andrewvc>	according to strace
| [Thursday 10 February 2011] [12:05:56] <andrewvc>	a tried changing up the message being sent, allocating a new one
| [Thursday 10 February 2011] [12:06:16] <cremes>	is the socket that it is sending on the same as the one libzmq is recv on?
| [Thursday 10 February 2011] [12:06:19] <andrewvc>	I tried checking ZMQ::EVENTS in a debugger right before the call as well, making sure it was writable
| [Thursday 10 February 2011] [12:06:24] <andrewvc>	nah, it's a pub socket
| [Thursday 10 February 2011] [12:06:31] <cremes>	ok
| [Thursday 10 February 2011] [12:06:45] <andrewvc>	tcp vs inprocess vs ipc makes no diff either
| [Thursday 10 February 2011] [12:06:45] <cremes>	i bet this is some internal FD that the lib uses for talking amongst itself
| [Thursday 10 February 2011] [12:07:03] <andrewvc>	yeah, it uses a unix socket for that weird FD no matter which protocols I use
| [Thursday 10 February 2011] [12:07:32] <cremes>	you need to catch this in gdb
| [Thursday 10 February 2011] [12:08:06] <cremes>	run it like;  gdb --args ruby -I lib bin/socket-motor
| [Thursday 10 February 2011] [12:08:26] <cremes>	when it dies, you can print the zmq backtrace
| [Thursday 10 February 2011] [12:08:33] 	 * cremes goes to try this...
| [Thursday 10 February 2011] [12:08:51] <andrewvc>	awesome, I know nothing about GDB
| [Thursday 10 February 2011] [12:09:32] <cremes>	i know enough to be dangerous
| [Thursday 10 February 2011] [12:09:46] <andrewvc>	lol
| [Thursday 10 February 2011] [12:09:50] <cremes>	i have it in gdb... now i need sustrik or mato to tell me what they need to figure this out
| [Thursday 10 February 2011] [12:10:06] <andrewvc>	btw, I fixed the rack client
| [Thursday 10 February 2011] [12:10:28] <cremes>	https://gist.github.com/820902   the backtrace in gdb
| [Thursday 10 February 2011] [12:10:32] <andrewvc>	if you pull socket motor thin won't keep dying
| [Thursday 10 February 2011] [12:11:12] <cremes>	it didn't die when i caught the error in gdb
| [Thursday 10 February 2011] [12:11:28] <andrewvc>	that's good and bad
| [Thursday 10 February 2011] [12:11:35] <cremes>	it died when i exited gdb though
| [Thursday 10 February 2011] [12:11:44] <andrewvc>	interesting
| [Thursday 10 February 2011] [12:12:07] <andrewvc>	zmq acts weird in general when you ctrl-C
| [Thursday 10 February 2011] [12:12:08] <cremes>	andrewvc: which line in ffi-rzmq does it execute before choking?
| [Thursday 10 February 2011] [12:12:18] <andrewvc>	lemme dig it up
| [Thursday 10 February 2011] [12:12:20] <cremes>	yeah, the new reaper thread stuff is supposed to solve that
| [Thursday 10 February 2011] [12:13:10] <andrewvc>	socket.rb line 260
| [Thursday 10 February 2011] [12:13:16] <andrewvc>	yeah, I just pulled this morning
| [Thursday 10 February 2011] [12:13:25] <andrewvc>	no luck there, as far as the new reaper stuff
| [Thursday 10 February 2011] [12:13:58] <andrewvc>	well, it used to die there
| [Thursday 10 February 2011] [12:14:00] <andrewvc>	maybe not anymore
| [Thursday 10 February 2011] [12:14:17] <cremes>	any flags?
| [Thursday 10 February 2011] [12:14:27] <cremes>	NOBLOCK?
| [Thursday 10 February 2011] [12:14:35] <andrewvc>	yeah, I tried messing with those as well, it's a two part PUB messages, topic + body
| [Thursday 10 February 2011] [12:14:39] <andrewvc>	yeah, noblock
| [Thursday 10 February 2011] [12:14:46] <cremes>	ok, so NOBLOCK & SNDMORE
| [Thursday 10 February 2011] [12:14:50] <andrewvc>	i tried it with no flags as well
| [Thursday 10 February 2011] [12:14:56] <cremes>	ok
| [Thursday 10 February 2011] [12:15:20] <cremes>	how are you constructing the message? is message.address valid?
| [Thursday 10 February 2011] [12:15:54] <cremes>	i.e. maybe there is garbage in the message and 0mq is choking on that somehow
| [Thursday 10 February 2011] [12:16:16] <andrewvc>	https://github.com/andrewvc/dripdrop/blob/master/lib/dripdrop/handlers/zeromq.rb#L44
| [Thursday 10 February 2011] [12:16:18] <cremes>	is the message freshly allocated with Message.new? or is it sourced from elsewhere?
| [Thursday 10 February 2011] [12:16:20] <andrewvc>	is how it's constructed
| [Thursday 10 February 2011] [12:16:36] <andrewvc>	I tried firing up a debugger, allocating a new message, and sending that, right before it died
| [Thursday 10 February 2011] [12:16:50] <andrewvc>	so I used to be able to time it, like, it'd send 4 messages, and die on # 4
| [Thursday 10 February 2011] [12:17:05] <andrewvc>	so I stepped through the first 3, and inserted a new message right before zmq_send to test that out
| [Thursday 10 February 2011] [12:17:12] <andrewvc>	no luck there either
| [Thursday 10 February 2011] [12:17:15] <cremes>	are you sure this line is correct?
| [Thursday 10 February 2011] [12:17:16] <cremes>	https://github.com/andrewvc/dripdrop/blob/master/lib/dripdrop/handlers/zeromq.rb#L51
| [Thursday 10 February 2011] [12:17:32] <cremes>	generally you OR flags together, not add them
| [Thursday 10 February 2011] [12:18:02] <cremes>	e.g. flags = (i + 1 < num_parts ? ZMQ::SNDMORE : 0) | ZMQ::NOBLOCK
| [Thursday 10 February 2011] [12:18:25] <andrewvc>	oye, crap good catch
| [Thursday 10 February 2011] [12:18:28] <andrewvc>	*pacepalm
| [Thursday 10 February 2011] [12:18:32] <andrewvc>	*face palm
| [Thursday 10 February 2011] [12:18:40] <andrewvc>	lemme try that
| [Thursday 10 February 2011] [12:18:58] <cremes>	still crashes
| [Thursday 10 February 2011] [12:20:04] <andrewvc>	yep
| [Thursday 10 February 2011] [12:20:28] <andrewvc>	I think this is in libzmq, I mean, it shouldn't ever reach there anyway
| [Thursday 10 February 2011] [12:20:34] <andrewvc>	no matter how inept I am :)
| [Thursday 10 February 2011] [12:21:30] <andrewvc>	that socket is used for a remote logger, so it's not critical to the app. If I disable it, it runs fairly well
| [Thursday 10 February 2011] [12:21:49] <cremes>	still looking...
| [Thursday 10 February 2011] [12:21:54] <andrewvc>	well, aside from all the other bugs in it, that I haven't had time to deal with as I've tracked down this.
| [Thursday 10 February 2011] [12:22:04] <andrewvc>	brb
| [Thursday 10 February 2011] [12:26:56] <cremes>	andrewvc: found something
| [Thursday 10 February 2011] [12:30:45] <cremes>	andrewvc: nope, false alarm
| [Thursday 10 February 2011] [12:33:05] <andrewvc>	back
| [Thursday 10 February 2011] [12:33:31] <andrewvc>	the amount of time I've dumped into this is a bit ridiculous at this point, hopefully the mailing list will have an answer
| [Thursday 10 February 2011] [12:33:56] <Rich_Morin>	Zed Shaw gave a very nice talk last night at the Bay Area Python group, talking about how he used ZeroMQ on assorted projects.
| [Thursday 10 February 2011] [12:33:57] <andrewvc>	my last hope is finishing jruby dripdrop support
| [Thursday 10 February 2011] [12:34:08] <andrewvc>	and seeing if jruby gives a better error
| [Thursday 10 February 2011] [12:36:41] <andrewvc>	that, or running git bisect on libzmq on a lazy saturday
| [Thursday 10 February 2011] [12:37:29] <andrewvc>	course, I guess I need a known good rev for that
| [Thursday 10 February 2011] [12:40:27] <alexbOrsova>	im having an issue with zeromq on ubuntu 10.04.1. I downloaded the library for posix, did "./configure", "make", "sudo make install". Then I complied one of the examples and tried to run it and I got "error while loading shared libraries: libzmq.so.0"
| [Thursday 10 February 2011] [12:40:49] <alexbOrsova>	any suggestions?
| [Thursday 10 February 2011] [12:42:24] <alexbOrsova>	nevermind, it was a bug in the makefile, "/sbin/ldconfig" should probably be called as part of the "make install" process...
| [Thursday 10 February 2011] [13:03:23] <Rich_Morin>	Hi, guys.  Should we try for a SUSS session this Sunday?
| [Thursday 10 February 2011] [13:03:46] <mikko>	what is a SUSS session ?
| [Thursday 10 February 2011] [13:05:01] <Rich_Morin>	Sorry, wrong channel :-/
| [Thursday 10 February 2011] [13:05:19] <Rich_Morin>	SketchUp Sunday Social
| [Thursday 10 February 2011] [14:11:00] <bitweiler>	is ZMQ_REQ  and ZMQ_REP still use in library or should one use ZMQ_PULL & ZMQ_PUSH?
| [Thursday 10 February 2011] [14:17:16] <Seta00>	bitweiler, PUSH and PULL aren't replacements to REQ and REP
| [Thursday 10 February 2011] [14:19:51] <andrewvc>	cremes: I think I figured it out
| [Thursday 10 February 2011] [14:20:27] <andrewvc>	thanks for all the help, I mean it's still most likely a ZMQ bug I think, but it looks like ZMQ::EVENTS is the cause
| [Thursday 10 February 2011] [14:20:38] <cremes>	andrewvc: good deal
| [Thursday 10 February 2011] [14:20:53] <andrewvc>	so, thanks for GDB, that narrowed it down to getsockopt
| [Thursday 10 February 2011] [14:20:54] <cremes>	bitweiler: REQ/REP and PUSH/PULL are different kinds of sockets
| [Thursday 10 February 2011] [14:21:19] <cremes>	bitweiler: PUSH/PULL used to have different names that were deprecated; i forget what they were
| [Thursday 10 February 2011] [14:21:20] <andrewvc>	and ZMQ::EVENTS would get checked by my em-zeromq library, and it'd work for a while, then kaput
| [Thursday 10 February 2011] [14:21:39] <cremes>	andrewvc: race condition in getsockopt you think?
| [Thursday 10 February 2011] [14:21:52] <andrewvc>	I think what may be happening still is, ruby is generating some kind of exception but ZMQ is dying first.
| [Thursday 10 February 2011] [14:22:36] <andrewvc>	the ZMQ::EVENTS calls aren't necessary strictly, as far as I can tell, commenting them out in em-zeromq just results in recv or send being called, and those can fail and be handled
| [Thursday 10 February 2011] [14:23:05] <andrewvc>	so, I can't speak to it being a race condition, but that sounds right to me
| [Thursday 10 February 2011] [14:26:34] <cremes>	interesting
| [Thursday 10 February 2011] [14:26:41] <cremes>	you should post your observations to the ML
| [Thursday 10 February 2011] [14:26:54] <andrewvc>	I'm going to for sure
| [Thursday 10 February 2011] [14:29:08] <andrewvc>	if you have some time chuck: https://github.com/andrewvc/em-zeromq/blob/master/lib/em-zeromq/connection.rb
| [Thursday 10 February 2011] [14:29:27] <andrewvc>	I just removed the calls to ZMQ::EVENTS
| [Thursday 10 February 2011] [14:30:06] <andrewvc>	I mean, if I just attempt to send or recv and it fails, that works, I can see how it could be slower depending on the ZMQ internals, since those FDs are kind of blunt instruments
| [Thursday 10 February 2011] [14:30:19] <andrewvc>	could use a second pair of more experienced eyes
| [Thursday 10 February 2011] [14:31:37] <cremes>	looking...
| [Thursday 10 February 2011] [14:31:47] 	 * cremes finds it funny that my eyes are more experienced
| [Thursday 10 February 2011] [14:33:50] <andrewvc>	I think it may just be calling ZMQ::EVENTS on writable sockets
| [Thursday 10 February 2011] [14:34:13] <andrewvc>	it may even just be PUB sockets, since that's what it is in this case, leaving ZMQ::EVENTS enabled for readables doesn't trigger it
| [Thursday 10 February 2011] [14:34:45] <andrewvc>	though, this is obviously all new, and perhaps further testing will reveal problems there as well
| [Thursday 10 February 2011] [14:35:33] <cremes>	andrewvc: not sure about the purpose of #deregister_writable; it just sets a flag that isn't used anywhere
| [Thursday 10 February 2011] [14:36:42] <andrewvc>	oh, that's used by eventmachine
| [Thursday 10 February 2011] [14:36:54] <andrewvc>	so, it tells EM to regard or disregard activity on the FD
| [Thursday 10 February 2011] [14:37:06] <andrewvc>	yeah, it's a bit funky looking, could use a comment
| [Thursday 10 February 2011] [14:37:26] <andrewvc>	same thing in notify_readable
| [Thursday 10 February 2011] [14:37:41] <cremes>	ok
| [Thursday 10 February 2011] [14:37:52] <cremes>	nothing major jumps out at me; looks good
| [Thursday 10 February 2011] [14:38:28] <andrewvc>	cool. Well, I've got to get back to other stuff, but I'll be posting gdb traces and other goodness on the list tonight
| [Thursday 10 February 2011] [14:38:39] <cremes>	ok
| [Thursday 10 February 2011] [14:38:40] <andrewvc>	thanks a bunch, if you hadn't brought out GDB I think I'd still be stuck
| [Thursday 10 February 2011] [14:38:57] <sysgears>	hi guys, i'm trying to extend zmq termination, so that messages at the receiving pipe were all fetched before ZMQ terminates
| [Thursday 10 February 2011] [14:38:57] <cremes>	it's nice to have multiple tools in your toolbag
| [Thursday 10 February 2011] [14:39:13] <cremes>	sysgears: take a look at ZMQ_LINGER
| [Thursday 10 February 2011] [14:41:04] <sysgears>	cremes, what for? I'm trying to not loose any messages at receiver end, ZMQ_LINGER is to set TTL for messages, its a different thing I think
| [Thursday 10 February 2011] [14:43:08] <cremes>	ZMQ_LINGER prevents the socket from closing until it has flushed all messages OR until the timeout has expired
| [Thursday 10 February 2011] [14:43:12] <cremes>	there is no TTL in 0mq
| [Thursday 10 February 2011] [14:43:44] <cremes>	and it isn't possible to not lose messages at receiver end unless you do an explicit ACK/reply
| [Thursday 10 February 2011] [14:43:49] <cremes>	for each message
| [Thursday 10 February 2011] [14:43:51] <sysgears>	Cremes, this is true for sending end
| [Thursday 10 February 2011] [14:44:13] <sysgears>	I know it is not possible now, thats why I'm patching ZMQ
| [Thursday 10 February 2011] [14:44:43] <cremes>	ok
| [Thursday 10 February 2011] [14:44:52] <cremes>	are you creating a new socket type?
| [Thursday 10 February 2011] [14:45:58] <sysgears>	nope, I want that recv fetched all the messages it has before it will return ETERM
| [Thursday 10 February 2011] [14:46:36] <sysgears>	currently it returns ETERM right after it detects ctx_terminated is on
| [Thursday 10 February 2011] [14:46:56] <cremes>	do you plan to make that a socket option?
| [Thursday 10 February 2011] [14:47:17] <Seta00>	I'm having difficulties to track down the reason I'm hitting this assertion: nbytes == sizeof (command_t) (mailbox.cpp:244)
| [Thursday 10 February 2011] [14:47:49] <cremes>	Seta00: what os?
| [Thursday 10 February 2011] [14:47:52] <Seta00>	Linux
| [Thursday 10 February 2011] [14:47:56] <Seta00>	Ubuntu 10.10
| [Thursday 10 February 2011] [14:48:32] <cremes>	you might want to look at modifying some sysctls; the command_t's use some of those buffers for ipc/tcp/udp
| [Thursday 10 February 2011] [14:48:35] <sysgears>	I plan to extend zmq_term semantics - it will not only flush all messages to be sent before termination it will also recv all messages that are currently in its buffers before termination.
| [Thursday 10 February 2011] [14:48:47] <cremes>	search the ML for sysctl and see what comes up
| [Thursday 10 February 2011] [14:49:00] <Seta00>	the ML?
| [Thursday 10 February 2011] [14:49:05] <cremes>	mailing list
| [Thursday 10 February 2011] [14:49:07] <Seta00>	oh
| [Thursday 10 February 2011] [14:49:21] 	 * cremes likes acronyms that confuse people
| [Thursday 10 February 2011] [14:49:24] <Seta00>	lol
| [Thursday 10 February 2011] [14:49:33] <Seta00>	don't use ANU's
| [Thursday 10 February 2011] [14:49:42] <Seta00>	(Acronyms Nobody Understand)
| [Thursday 10 February 2011] [14:50:24] <cremes>	yessir
| [Thursday 10 February 2011] [14:51:01] <andrewvc>	ANU's are fine so long as they're TLA's
| [Thursday 10 February 2011] [14:51:22] <cremes>	andrewvc: hey, get back to work!
| [Thursday 10 February 2011] [14:51:38] <andrewvc>	lol
| [Thursday 10 February 2011] [15:00:15] <Guthur>	i have the scenario where requests come in on individual threads the reply to each comes back async on other threads, my solution is to use 0MQ, is it overkill and normal thread constructs more suited?
| [Thursday 10 February 2011] [15:00:22] <Seta00>	tried this: http://www.mail-archive.com/zeromq-dev@lists.zeromq.org/msg06901.html
| [Thursday 10 February 2011] [15:00:23] <Seta00>	didn't work
| [Thursday 10 February 2011] [15:03:15] <cremes>	Guthur: that's a great use-case for the inproc transport
| [Thursday 10 February 2011] [15:03:25] <kaib>	hi all. are there any other native implementation of zeromq than the reference c++ implementation?
| [Thursday 10 February 2011] [15:03:49] <cremes>	kaib: not that i know of
| [Thursday 10 February 2011] [15:04:30] <cremes>	Seta00: hmm... are there are sysctl's for ipc?
| [Thursday 10 February 2011] [15:04:55] <cremes>	i'm pretty sure the command mailboxes are using ipc or something similar internal to the library
| [Thursday 10 February 2011] [15:04:58] <kaib>	are they actively discouraged or just haven't happened yet? the protocol seems like a great little language interoperability system.
| [Thursday 10 February 2011] [15:05:00] <cremes>	(though i could definitely be wrong)
| [Thursday 10 February 2011] [15:05:16] <cremes>	kaib: no one has come along to take a whack at it yet; you could be the first
| [Thursday 10 February 2011] [15:05:35] <cremes>	i've never seen the imatix guys discourage anybody from hacking on the lib or attempting a port
| [Thursday 10 February 2011] [15:05:59] <Guthur>	cremes, that's my thought as well
| [Thursday 10 February 2011] [15:06:31] <Guthur>	trying to convince the team lead at work is proofing a challenge
| [Thursday 10 February 2011] [15:06:57] <Guthur>	he seems to think normal threading constructs and a global store are an 'easy' solution
| [Thursday 10 February 2011] [15:07:14] <Guthur>	it's funny though, this easy solution still does work right yet
| [Thursday 10 February 2011] [15:07:18] <cremes>	well, one way to discuss it is in terms of future scalability
| [Thursday 10 February 2011] [15:07:29] <Guthur>	does/doesn't
| [Thursday 10 February 2011] [15:07:34] <cremes>	what might be a thread today could easily be a separate process (or on a separate box) tomorrow
| [Thursday 10 February 2011] [15:07:49] <cremes>	and the only thing you need to change is the transport string:  inproc -> tcp
| [Thursday 10 February 2011] [15:08:35] <Guthur>	yeah, the flexibility is a real seller for me personally
| [Thursday 10 February 2011] [15:08:43] <Guthur>	that and the whole message passing concept
| [Thursday 10 February 2011] [15:09:05] <kaib>	cremes: so the transports add some framing, do the sockets add any framing of their own?
| [Thursday 10 February 2011] [15:09:17] <Guthur>	I just have to keep plugging a way at work to try and convince others
| [Thursday 10 February 2011] [15:09:19] <kaib>	cremes: i've been trying to figure out the exact wire format.
| [Thursday 10 February 2011] [15:09:39] <kaib>	Guthur: what is the problem you are trying to solve, i logged on just past your description..
| [Thursday 10 February 2011] [15:09:54] <Guthur>	kaib i have the scenario where requests come in on individual threads the reply to each comes back async on other threads, my solution is to use 0MQ, is it overkill and normal thread constructs more suited?
| [Thursday 10 February 2011] [15:11:16] <kaib>	ok, so are the original threads that received the request the ones that transmit out the response?
| [Thursday 10 February 2011] [15:12:17] <kaib>	Guthur: ie. Client -> Thread0 -> async backend -> Thread1 -> Thread0 -> Client
| [Thursday 10 February 2011] [15:13:35] <Seta00>	hmm, it has something to do with the way I'm killing the socket on disconnect
| [Thursday 10 February 2011] [15:17:08] <Guthur>	sorry i disco'd
| [Thursday 10 February 2011] [15:17:17] <Guthur>	kaib yeah that's the scenario
| [Thursday 10 February 2011] [15:17:26] <Guthur>	multiple client requests as well
| [Thursday 10 February 2011] [15:17:39] <Guthur>	concurrent requests
| [Thursday 10 February 2011] [15:17:47] <cremes>	kaib: wire format documented here:  http://api.zeromq.org/zmq_tcp.html
| [Thursday 10 February 2011] [15:18:27] <Guthur>	I actually have it solved with ZMQ
| [Thursday 10 February 2011] [15:18:58] <Guthur>	but just can't get the buy in from my team lead to include the dependency
| [Thursday 10 February 2011] [15:19:05] <Guthur>	very frustrating
| [Thursday 10 February 2011] [15:19:07] <cremes>	Guthur: show your team lead how you can now break it up into multiple processes without changing any of the message queueing code
| [Thursday 10 February 2011] [15:19:17] <cremes>	that's a pretty big win in my opinion
| [Thursday 10 February 2011] [15:19:59] <kaib>	cremes: that's the wire protocol for tcp, i'm reading the code and it seems like there is some other framing going on as well. there is talk about "data batches"
| [Thursday 10 February 2011] [15:20:34] <cremes>	kaib: not sure then; i haven't heard the term "data batches" come up before
| [Thursday 10 February 2011] [15:23:40] <kaib>	Guthur: when you fire off the request to the async backend do you have any chance of deciding which thread gets the response? or even which pool of threads?
| [Thursday 10 February 2011] [15:24:26] <Guthur>	kaib:nope its pretty opaque, the scenario is a request to a process running a quickFIX app
| [Thursday 10 February 2011] [15:24:58] <Guthur>	the requesting thread send off a, QuoteRequest FIX message, this will then return a Quote async on another thread
| [Thursday 10 February 2011] [15:27:24] <kaib>	Guthur: ok, your team lead might be trying to avoid extra dependencies on external projects... ie. if you guys can get it to work with a simpler approach you will be good for a while.
| [Thursday 10 February 2011] [15:27:57] <cremes>	s/simpler/more familiar/
| [Thursday 10 February 2011] [15:28:19] <kaib>	Guthur: i would benchmark your implementation. that gives you data to go on when the discussion resurfaces later..
| [Thursday 10 February 2011] [15:28:39] <kaib>	cremes: that's true. much can be said for believing in the familiar.. :-)
| [Thursday 10 February 2011] [15:28:55] <cremes>	kaib: don't i know it! :)
| [Thursday 10 February 2011] [15:29:08] <kaib>	cremes: in zmq_encoder.cpp, talking about batches.
| [Thursday 10 February 2011] [15:29:47] <cremes>	kaib: you need to chat with sustrik (primary dev) or drop a note to the mailing list
| [Thursday 10 February 2011] [15:30:06] <cremes>	i only dig into the internals when i have a showstopper bug
| [Thursday 10 February 2011] [15:30:12] <kaib>	cremes: thanks.
| [Thursday 10 February 2011] [15:30:16] <cremes>	so far, i have somehow avoided the encoder stuff
| [Thursday 10 February 2011] [15:30:19] <kaib>	sustrik: ping?
| [Thursday 10 February 2011] [15:30:22] <cremes>	you are welcome
| [Thursday 10 February 2011] [15:30:50] <cremes>	kaib: i think most of the devs are GMT+3
| [Thursday 10 February 2011] [15:30:59] <Guthur>	I think it is telling how no one has actually implemented the a solution using the 'easy' global data approach
| [Thursday 10 February 2011] [15:32:12] <kaib>	Guthur: heh.. well, you need to come well armed. working code and good political connections go a long way. :-)
| [Thursday 10 February 2011] [15:32:41] <kaib>	cremes: oh, well i'm gmt+2, they seem to drop off awfully early.. :-)
| [Thursday 10 February 2011] [15:32:45] <Guthur>	well I have the first, 
| [Thursday 10 February 2011] [15:33:15] <Guthur>	The half working solution they currently have takes the same time to do one quote as mine does to 60
| [Thursday 10 February 2011] [15:33:21] <Guthur>	to do 60*
| [Thursday 10 February 2011] [15:34:05] <Guthur>	That performance measurement has only became available to me this evening
| [Thursday 10 February 2011] [15:34:51] <Guthur>	though they are using HTTP for the remoting
| [Thursday 10 February 2011] [15:35:01] <Guthur>	so it will improve some when they can move a fast protocol
| [Thursday 10 February 2011] [15:35:04] <Guthur>	faster*
| [Thursday 10 February 2011] [15:36:20] <Guthur>	though it will need to be considerably faster than that, 5 secs per quote is just not going to cut it at all
| [Thursday 10 February 2011] [15:43:10] <cremes>	Guthur: i do *way* faster than that in *ruby*
| [Thursday 10 February 2011] [16:21:43] <chmod700>	so I just grabbed 0mq+python bindings for v2.0.10 and am trying to get https://github.com/imatix/zguide/blob/master/examples/Python/mtserver.py to work, can someone tell me what I should be sending to get the "World" response back?
| [Thursday 10 February 2011] [16:24:10] <chmod700>	all I see on my connection to port 5555 is '\x01\x00'
| [Thursday 10 February 2011] [16:25:58] <ianbarber>	are you connecting with 0mq?
| [Thursday 10 February 2011] [16:26:14] <ianbarber>	on both sides
| [Thursday 10 February 2011] [16:28:43] <chmod700>	ianbarber: no I was just using telnet to connect
| [Thursday 10 February 2011] [16:29:42] <chmod700>	I guess I missed something in the docs :), how does one go about layering their wire-format stuff on top of that XREP device?
| [Thursday 10 February 2011] [16:30:53] <ianbarber>	0mq pretty much does all the wire level stuff, you send your own format in the messages
| [Thursday 10 February 2011] [16:31:07] <ianbarber>	its very little overhead
| [Thursday 10 February 2011] [16:32:03] <chmod700>	ianbarber: so why doesn't telnet work (or wget, or a browser) when hitting the XREP port?
| [Thursday 10 February 2011] [17:11:05] <ianbarber>	there is still a wire protocol, so you need to be able to understand that
| [Thursday 10 February 2011] [17:11:17] <ianbarber>	in general zmq is designed for people using the library at both ends
| [Thursday 10 February 2011] [17:14:51] <chmod700>	ianbarber: thanks, so for HTTP for instance, do I need to stand up my own HTTP server and then forward requests through a zmq socket to workers?
| [Thursday 10 February 2011] [17:15:06] <chmod700>	or is there some magic http zmq device?
| [Thursday 10 February 2011] [17:15:57] <Skaag>	the first.
| [Thursday 10 February 2011] [17:16:11] <Skaag>	there is no direct relation between http and zmq
| [Thursday 10 February 2011] [17:16:48] <Skaag>	if with java, you can use something like jetty to expose some kind of rest/json/xml interface, then pass the messages to a thread that publishes messages
| [Thursday 10 February 2011] [17:18:49] <Guthur>	are select_t, poll_t, epoll_t, devpoll_t and kqueue_t all essentially doing the same thing except with different raw connections
| [Thursday 10 February 2011] [17:19:44] <ianbarber>	chmod700: mongrel2 is quite good for doing a webserver with 0MQ transport to the backend
| [Thursday 10 February 2011] [17:19:57] <ianbarber>	but in general, yeah, that's the kind of thing
| [Thursday 10 February 2011] [17:21:13] <Skaag>	ianbarber: any samples of such a setup with mongrel2?
| [Thursday 10 February 2011] [17:21:23] <Skaag>	would love to play around with it
| [Thursday 10 February 2011] [17:21:46] <ianbarber>	Skaag: look at the mongrel2 book, 0MQ is the only way you can do dynamic content with it
| [Thursday 10 February 2011] [17:22:08] <Skaag>	they have that as a sample? :)
| [Thursday 10 February 2011] [17:22:18] <ianbarber>	basically it binds a push socket, and sends the headers, path, and some other bits and pieces over it
| [Thursday 10 February 2011] [17:22:34] <ianbarber>	yeah, download mongrel2 and look in the examples dir
| [Thursday 10 February 2011] [17:23:28] <Skaag>	awesome
| [Thursday 10 February 2011] [17:23:31] <Skaag>	will do that now
| [Thursday 10 February 2011] [17:24:15] <ianbarber>	if you just need one way comms, take a look at mikko's httpush https://github.com/mkoppanen/httpush
| [Thursday 10 February 2011] [17:24:29] <ianbarber>	that's great if you want to do network logging over http or similar 
| [Thursday 10 February 2011] [17:41:27] <Skaag>	that's one way, towards the client side, I assume?
| [Thursday 10 February 2011] [17:42:16] <Skaag>	damn -17 outside... not daring to go out.
| [Thursday 10 February 2011] [17:42:24] <Skaag>	celcius.
| [Thursday 10 February 2011] [18:58:45] <eut>	hello
| [Thursday 10 February 2011] [18:59:46] <eut>	when using zmq_xrep sockets how are the three message pieces (identity, delimiter, and body) supposed to be separated?
| [Thursday 10 February 2011] [19:06:04] <cremes>	eut: http://www.zeromq.org/tutorials:xreq-and-xrep
| [Thursday 10 February 2011] [19:06:07] <cremes>	that might help
| [Thursday 10 February 2011] [19:08:16] <eut>	great :]
| [Thursday 10 February 2011] [23:47:00] <gui81>	anyone here
| [Thursday 10 February 2011] [23:47:38] <gui81>	this is my first time joining an irc chat, is this working
| [Thursday 10 February 2011] [23:57:49] <gui81>	has anyone solved the async client problem, or does anyone have an example using zmq_poll
| [Thursday 10 February 2011] [23:58:26] <gui81>	Matt talks about this issue in the comments section on http://www.zeromq.org/blog:multithreaded-server
| [Friday 11 February 2011] [00:01:03] <gui81>	another question I have is whether or not it is possible to publish and subscribe on the same port number, I have tried a simple example, that compiled just fine, but it locked up my computer and I had to reboot
| [Friday 11 February 2011] [00:04:18] <gui81>	the multithreaded server example in the link above requires that you send, receive, send, receive, etc..., but I want to be able to send a message and maybe send a few more messages before a response is actually received.  This is so that I don't have to wait on a request that could take a potentially long time
| [Friday 11 February 2011] [00:07:14] <gui81>	I could use pub/sub and rethink how I handle messages, but I was hoping I could do this over the same port
| [Friday 11 February 2011] [00:10:20] <guido_g>	publisher and subscriber should of course use the same port, otherwise they couldn't talk to each other
| [Friday 11 February 2011] [00:11:34] <gui81>	I'm saying that I want a single process to both publish and subscribe like the following:
| [Friday 11 February 2011] [00:12:03] <gui81>	zmq::socket_t publisher(context, ZMQ_PUB);
| [Friday 11 February 2011] [00:12:03] <guido_g>	doesn't matter
| [Friday 11 February 2011] [00:12:33] <guido_g>	publisher sends things out and subscriber needs to get the information
| [Friday 11 February 2011] [00:12:57] <guido_g>	so both need to share a communication path
| [Friday 11 February 2011] [00:13:02] <gui81>	publisher.bind("tcp://*:5563");
| [Friday 11 February 2011] [00:13:02] <gui81>	zmq::socket_t subscriber(context, ZMQ_SUB);subscriber.connect("tcp://localhost:5564");
| [Friday 11 February 2011] [00:13:22] <guido_g>	wouldn't work
| [Friday 11 February 2011] [00:13:26] <gui81>	sorry, let me try that again
| [Friday 11 February 2011] [00:13:45] <guido_g>	did you ever to network stuff befeore?
| [Friday 11 February 2011] [00:13:52] <guido_g>	s/to/do/
| [Friday 11 February 2011] [00:14:11] <gui81>	zmq::context_t context(1);
| [Friday 11 February 2011] [00:14:12] <gui81>	    zmq::socket_t publisher(context, ZMQ_PUB);
| [Friday 11 February 2011] [00:14:12] <gui81>	    publisher.bind("tcp://*:5563");
| [Friday 11 February 2011] [00:14:12] <gui81>		// don't do this on the same port as above, will have to reboot computer
| [Friday 11 February 2011] [00:14:12] <gui81>		zmq::socket_t subscriber(context, ZMQ_SUB);
| [Friday 11 February 2011] [00:14:13] <gui81>		subscriber.connect("tcp://localhost:5563");
| [Friday 11 February 2011] [00:14:13] <gui81>		subscriber.setsockopt( ZMQ_SUBSCRIBE, "C", 1);
| [Friday 11 February 2011] [00:15:03] <guido_g>	i don't know your computer and what you've done elsewhere, but the principle is right
| [Friday 11 February 2011] [00:15:59] <guido_g>	and for code please use a pastbin like https://gist.github.com/ or http://paste.pocoo.org/
| [Friday 11 February 2011] [00:17:22] <guido_g>	next thing: if you have trouble w/ something, write a minimal example that shows the problem and show the complete code and describe the expeceted vs. the observed behaviour
| [Friday 11 February 2011] [00:18:03] <gui81>	are you suggesting i post my code on a website?
| [Friday 11 February 2011] [00:18:20] <guido_g>	yes
| [Friday 11 February 2011] [00:28:16] <gui81>	guido_g, I think I figured out what I was doing wrong with my pub/sub stuff.  looks like I was trying to bind on both sides.  Turns out this compiled just fine, but after running it, it would lock up.  I even had to reboot, kill -9 wasn't working.  I am running on a Mac.  When I switched to only using one bind with multiple connects, things started working.
| [Friday 11 February 2011] [00:30:38] <gui81>	does anyone have any examples on an async client like what is suggested on http://www.zeromq.org/blog:multithreaded-server by Matt in the comments section
| [Friday 11 February 2011] [00:31:17] <guido_g>	did you read the guide?
| [Friday 11 February 2011] [00:31:39] <gui81>	yes
| [Friday 11 February 2011] [00:33:49] <gui81>	using req/rep it looks like you always have to send, receive, send, receive.  If I want to send, send, receive, send, receive, recieve   how would I do it, are there examples out there
| [Friday 11 February 2011] [00:34:35] <guido_g>	use xreq/xrep sockets
| [Friday 11 February 2011] [00:40:17] <gui81>	do you know of an example showing how to use xreq/xrep for something similar to the scenario i mentioned?  all of the examples in the guide look like they are used when kicking off worker threads
| [Friday 11 February 2011] [00:41:43] <guido_g>	frankly, i don't know what you intend
| [Friday 11 February 2011] [00:42:35] <guido_g>	if you have threads just let them talk via xreq/xrep
| [Friday 11 February 2011] [00:44:44] <gui81>	I would like to be able to do something similar to: s.send (request, callback);  where the sending thread won't be blocked and the application can send more requests.  then the callback is invoked whenever a reply is received for that request
| [Friday 11 February 2011] [00:45:45] <guido_g>	a) MQ doesn't do callbacks, you should have discovered that by now
| [Friday 11 February 2011] [00:46:42] <guido_g>	b) go read the XREQ/XREP docs again, there is no need for waiting or blocking
| [Friday 11 February 2011] [00:47:25] <gui81>	I understand they don't do callbacks, but if I can build a wrapper that would function similar to the callback, then that would work for me.  if this is possible with xreq/xrep then I will try to look further into this type of socket.  I admit that I don't know much about zeromq since I just started reading the guide today.  Thanks for the help.
| [Friday 11 February 2011] [00:48:39] <guido_g>	then finish reading the guide and the docs, will make a lot of things much clearer
| [Friday 11 February 2011] [00:49:13] <jugg>	I've had a system running for a couple of weeks, with zeromq built off of commit: 56bdba - and I just had the following assertion occur while running another round of stress tests: "Assertion failed: inpipes [current_in].active (xrep.cpp:229)"   Can that assert occur because of usage error, or why?
| [Friday 11 February 2011] [00:49:14] <guido_g>	ahh... and don't expect cookbook like examples suited for your use-cases
| [Friday 11 February 2011] [00:53:33] <jugg>	irc logs show another instance of this assertion at http://travlr.github.com/zmqirclog/2010-November.html
| [Friday 11 February 2011] [01:10:44] <bitweiler>	i notice in the zeromq-FAQ that it doesn't provide protocol buffering; what is the purpose of such said buffering?
| [Friday 11 February 2011] [01:14:34] <guido_g>	which faq item you're reffering to?
| [Friday 11 February 2011] [01:16:12] <guido_g>	s/reffering/referring/
| [Friday 11 February 2011] [01:16:19] <guido_g>	need more coffee
| [Friday 11 February 2011] [01:16:49] <bitweiler>	sorry, i meant serializing data to/from the wire representation
| [Friday 11 February 2011] [01:17:14] <bitweiler>	guido_g: this FAQ: http://www.zeromq.org/area:faq
| [Friday 11 February 2011] [01:18:29] <bitweiler>	Does MQ include APIs for serializing data to/from the wire representation? what is the purpose of such serializing?
| [Friday 11 February 2011] [01:19:26] <guido_g>	as stated, there is no such api in mq
| [Friday 11 February 2011] [01:20:07] <guido_g>	and serialization in the context of messaging means to convert a data strcuture into/from a byte stream for transfer
| [Friday 11 February 2011] [01:23:17] <guido_g>	bitweiler: hope that answers your question
| [Friday 11 February 2011] [01:24:23] <bitweiler>	yes, thanks
| [Friday 11 February 2011] [01:24:54] <guido_g>	great, i gotta run now... :)
| [Friday 11 February 2011] [01:25:05] 	 * bitweiler waves at guido_g
| [Friday 11 February 2011] [02:02:13] Notice	-NickServ- This nickname is registered. Please choose a different nickname, or identify via /msg NickServ identify <password>.
| [Friday 11 February 2011] [02:02:13] Notice	-NickServ- You are now identified for travlr.
| [Friday 11 February 2011] [02:30:55] <Guthur>	sustrik, ping
| [Friday 11 February 2011] [03:24:54] <bitweiler>	quick question, in the wuserver.c example from the guide what's the purpose of the within statement?
| [Friday 11 February 2011] [03:30:35] <sustrik>	morning
| [Friday 11 February 2011] [03:30:55] <bitweiler>	good day sustrik
| [Friday 11 February 2011] [04:31:17] <pieterh>	bitweiler: it produces a random number between 0 and N
| [Friday 11 February 2011] [04:31:45] <pieterh>	sorry that it's a bit cryptic, I'll change that
| [Friday 11 February 2011] [05:01:04] <sustrik>	pieterh: seems like there's something wrong with the mailing list
| [Friday 11 February 2011] [05:01:19] <sustrik>	i've sent a message there 5 mins ago
| [Friday 11 February 2011] [05:01:37] <sustrik>	and it's still not there
| [Friday 11 February 2011] [05:05:05] <mikko>	good morning
| [Friday 11 February 2011] [05:31:50] <sustrik>	kaib: pong
| [Friday 11 February 2011] [05:32:11] <sustrik>	Guthur: pong
| [Friday 11 February 2011] [05:36:21] <kaib>	sustrik: hi there
| [Friday 11 February 2011] [05:36:51] <kaib>	sustrik: i'm toying around with a freshly written 0mq protocol stack and was looking into how the wire protocol works.
| [Friday 11 February 2011] [05:37:38] <kaib>	sustrik: my aim is to write a prototype to see if a messaging based solution could be a good replacement for rpc in our system.
| [Friday 11 February 2011] [05:37:59] <sustrik>	kaib: speaking of 0mq over TCP?
| [Friday 11 February 2011] [05:38:01] <kaib>	sustrik: being wire compatible with 0mq seems like a good idea
| [Friday 11 February 2011] [05:38:14] <kaib>	sustrik: TCP initially, maybe UDP and other protocols later.
| [Friday 11 February 2011] [05:38:33] <sustrik>	there's no UDP transport for 0MQ so far...
| [Friday 11 February 2011] [05:38:40] <sustrik>	just PGM multicast
| [Friday 11 February 2011] [05:38:42] <sustrik>	anyway
| [Friday 11 February 2011] [05:38:48] <sustrik>	see zmq_tcp(7) man page
| [Friday 11 February 2011] [05:38:58] <sustrik>	there's 0mq framing described
| [Friday 11 February 2011] [05:39:02] <kaib>	sustrik: yep, i saw the line level framing
| [Friday 11 February 2011] [05:39:06] <sustrik>	ok
| [Friday 11 February 2011] [05:39:07] <mikko>	kaib: you could probably get prototype running pretty quickly by using zeromq and ZFL RPC
| [Friday 11 February 2011] [05:39:29] <sustrik>	as for the wire protocol on top of that
| [Friday 11 February 2011] [05:39:34] <kaib>	sustrik: i was wondering about the framing used by the different ports
| [Friday 11 February 2011] [05:39:43] <sustrik>	it's different for different messaging patterns
| [Friday 11 February 2011] [05:39:51] <sustrik>	REQ/REP
| [Friday 11 February 2011] [05:39:54] <sustrik>	PUB/SUB
| [Friday 11 February 2011] [05:39:57] <sustrik>	PUSH/PULL
| [Friday 11 February 2011] [05:40:04] <kaib>	mikko: what is ZFL RPC?
| [Friday 11 February 2011] [05:40:09] <mikko>	https://github.com/zeromq/zfl/blob/master/src/zfl_rpc.c
| [Friday 11 February 2011] [05:40:16] <mikko>	https://github.com/zeromq/zfl/blob/master/src/zfl_rpcd.c
| [Friday 11 February 2011] [05:40:21] <sustrik>	you can think of each pattern as a separate protocol on top of basic 0mq framing
| [Friday 11 February 2011] [05:40:27] <sustrik>	which one are you interested in?
| [Friday 11 February 2011] [05:40:48] <kaib>	sustrik: pub/sub push/pull req/rep, in that order.
| [Friday 11 February 2011] [05:41:06] <kaib>	sustrik: we have all those patterns in the system..
| [Friday 11 February 2011] [05:41:17] <sustrik>	pub/sub and push/pull are easy
| [Friday 11 February 2011] [05:41:39] <sustrik>	the only specific so far is that the first message sent be each peer is identity
| [Friday 11 February 2011] [05:41:48] <sustrik>	(see ZMQ_IDENTITY socket option)
| [Friday 11 February 2011] [05:42:00] <kaib>	sustrik: what does the peer do with the identity?
| [Friday 11 February 2011] [05:42:01] <sustrik>	if no identity is set, empty message is sent
| [Friday 11 February 2011] [05:42:23] <sustrik>	it can use when reconnection happens
| [Friday 11 February 2011] [05:42:24] <kaib>	sustrik: i understood it's used for persisting messages between crashes (presumably somewhere on disk?)
| [Friday 11 February 2011] [05:42:40] <sustrik>	if the new connection has same identity as one previously broken
| [Friday 11 February 2011] [05:42:53] <sustrik>	it can reuse the resources allocated for the old one
| [Friday 11 February 2011] [05:43:23] <sustrik>	so it can hold messages in the memory (or swap them to the disk) while the peer reconnects
| [Friday 11 February 2011] [05:44:03] <sustrik>	as for REQ/REP see here: http://www.zeromq.org/tutorials:xreq-and-xrep
| [Friday 11 February 2011] [05:44:17] <kaib>	sustrik: ok, so it's useful for making sure that no messages are dropped even if the client disconnects, right?
| [Friday 11 February 2011] [05:45:00] <sustrik>	messages can still be lost if they were processed or "on-the-wire" during the failure
| [Friday 11 February 2011] [05:45:11] <sustrik>	but it makes the whole thing more reliable, yes
| [Friday 11 February 2011] [05:45:37] <sustrik>	aside of that identities are used for routing replies to the original requesters in REQ/REP pattern
| [Friday 11 February 2011] [05:45:41] <sustrik>	see the link above
| [Friday 11 February 2011] [05:45:50] <sustrik>	there's a picture showing how it works
| [Friday 11 February 2011] [05:46:53] <sustrik>	kaib: btw, why write a new messaging solution?
| [Friday 11 February 2011] [05:47:11] <sustrik>	i'm not discouraging you, but it takes some manyears to get that done
| [Friday 11 February 2011] [05:47:58] <kaib>	sustrik: curiosity mostly, partially to see if a native implementation could be better integrated.
| [Friday 11 February 2011] [05:48:30] <kaib>	sustrik: we run a cluster consisting of ~50 nodes (we are still in pre launch) with the servers all written in Go.
| [Friday 11 February 2011] [05:48:48] <kaib>	sustrik: i was looking into hooking up mongrel2 as our http server and started reading more about 0mq.
| [Friday 11 February 2011] [05:48:56] <sustrik>	kaib: sure
| [Friday 11 February 2011] [05:49:08] <kaib>	sustrik: it seems like pattern used in 0mq is actually quite nice.
| [Friday 11 February 2011] [05:49:25] <kaib>	sustrik: i've used messaging systems back at Google but never really grokked them, the rpc system is so much more common.
| [Friday 11 February 2011] [05:49:51] <sustrik>	the patterns are the most interesting part of 0mq i think
| [Friday 11 February 2011] [05:50:04] <kaib>	sustrik: our main pain point is complexity we run 6 distinct server types with some very complex and latency sensitive interactions.
| [Friday 11 February 2011] [05:50:37] <kaib>	sustrik: i have a gut feeling that messages might be a good fit, but i need to write some code to make sure that's true.
| [Friday 11 February 2011] [05:51:06] <sustrik>	give it a try
| [Friday 11 February 2011] [05:51:17] <kaib>	sustrik: i'm not trying to do a generic library, just something that fits our specific purpose. i'll probably open source it when we have time, but it's definitely just to scratch our own itch.
| [Friday 11 February 2011] [05:51:39] <sustrik>	well, good luck
| [Friday 11 February 2011] [05:51:45] <kaib>	sustrik: given the core 0mq library is pretty good .. :-)
| [Friday 11 February 2011] [05:52:22] <sustrik>	you know, i've seen loads of ad hoc messaging library projects running into troubles
| [Friday 11 February 2011] [05:52:32] <sustrik>	it looks easy when you start
| [Friday 11 February 2011] [05:52:46] <kaib>	what type of issues do they usually encounter?
| [Friday 11 February 2011] [05:53:07] <sustrik>	all kind of asynchronicity issues
| [Friday 11 February 2011] [05:53:28] <sustrik>	also scaling issues
| [Friday 11 February 2011] [05:53:43] <sustrik>	everything works ok in test env
| [Friday 11 February 2011] [05:53:59] <sustrik>	then when you move to production you start to exprience bottlenecks
| [Friday 11 February 2011] [05:54:14] <kaib>	yep, that seems to be a common pattern for all distributed code.
| [Friday 11 February 2011] [05:54:30] <sustrik>	later on it turns out that the bottleneck can't be avoided without rewriting the whole code from scratch
| [Friday 11 February 2011] [05:54:31] <sustrik>	etc.
| [Friday 11 February 2011] [05:54:36] <kaib>	are the perf problems mostly in userspace or in interactions with the kernel?
| [Friday 11 February 2011] [05:54:42] <sustrik>	both
| [Friday 11 February 2011] [05:56:22] <kaib>	i'd love to know more specifics, obviously that's something i'd rather avoid .. are the difficulties related to messaging systems or just concurrent/parallel code in general?
| [Friday 11 February 2011] [05:56:36] <kaib>	ie. do the people running into trouble have experience with writing distributed systems?
| [Friday 11 February 2011] [05:56:44] <sustrik>	sure
| [Friday 11 February 2011] [06:01:56] <sustrik>	for example, there's some 12 manyears altogether spent on 0mq + many more years of messaging experience from beforehand
| [Friday 11 February 2011] [06:02:15] <sustrik>	but we still run into this kind of trouble occassionally
| [Friday 11 February 2011] [06:02:36] <sustrik>	say: what happens it 500 peers decide to disconnect at exactly the same moment?
| [Friday 11 February 2011] [06:02:55] <sustrik>	what's the latency impact for the remaining peers?
| [Friday 11 February 2011] [06:03:11] <sustrik>	how does the number of cores on the system affect the impact
| [Friday 11 February 2011] [06:03:13] <sustrik>	etc.
| [Friday 11 February 2011] [06:03:18] <sustrik>	complex stuff
| [Friday 11 February 2011] [06:04:20] <Guthur>	sustrik: Sorry I was not watching there
| [Friday 11 February 2011] [06:04:51] <Guthur>	I was hoping to pick your brains a little regarding the polling classes in 0MQ
| [Friday 11 February 2011] [06:04:57] <sustrik>	sure
| [Friday 11 February 2011] [06:04:59] <sustrik>	shoot
| [Friday 11 February 2011] [06:05:17] <Guthur>	I was investigating in relation to implementing windows named pipes
| [Friday 11 February 2011] [06:05:33] <Guthur>	is the polling used internally by 0MQ
| [Friday 11 February 2011] [06:05:44] <Guthur>	and are all the events required?
| [Friday 11 February 2011] [06:05:53] <sustrik>	what events?
| [Friday 11 February 2011] [06:05:56] <Guthur>	eg POLLIN, POLLOUT, and POLLERR
| [Friday 11 February 2011] [06:06:19] <sustrik>	that's used in POSIX poll()
| [Friday 11 February 2011] [06:06:33] <sustrik>	0mq virtualises the polling mechanism
| [Friday 11 February 2011] [06:06:51] <sustrik>	and from the user's perspective you have these events:
| [Friday 11 February 2011] [06:06:57] <sustrik>	in_event
| [Friday 11 February 2011] [06:06:59] <sustrik>	out_event
| [Friday 11 February 2011] [06:07:02] <sustrik>	timer_event
| [Friday 11 February 2011] [06:07:30] <kaib>	sustrik: thanks, i'll tinker around a bit and see what i get. we can always fall back on using the ref implementation if push comes to shove.
| [Friday 11 February 2011] [06:07:33] <sustrik>	(these are callbacks invoked by the poller class)
| [Friday 11 February 2011] [06:07:41] <sustrik>	kaib: sure
| [Friday 11 February 2011] [06:07:44] <Guthur>	ok, sorry I'll be right back
| [Friday 11 February 2011] [06:07:50] <Guthur>	need to go into a conf call
| [Friday 11 February 2011] [06:07:58] <Guthur>	sorry about this
| [Friday 11 February 2011] [06:09:36] <Guthur>	I was checking out select_t, poll_t, epoll_t, devpoll_t and kqueue_t, as you recommended
| [Friday 11 February 2011] [06:09:47] <Guthur>	is there anywhere else in particular I should look?
| [Friday 11 February 2011] [06:10:46] <sustrik>	nope, just implement the same interface with IOCP
| [Friday 11 February 2011] [06:10:59] <sustrik>	ah
| [Friday 11 February 2011] [06:11:10] <sustrik>	you should also redefine fd_t
| [Friday 11 February 2011] [06:11:18] <sustrik>	to resolve to HANDLE instead of SOCKET
| [Friday 11 February 2011] [06:11:21] <Guthur>	Named Pipes in MSWin obviously don't have a poll, all they have is call back functions on completion
| [Friday 11 February 2011] [06:11:42] <Guthur>	ok
| [Friday 11 February 2011] [06:12:24] <sustrik>	afaiu you can use ReadFile/WriteFile
| [Friday 11 February 2011] [06:12:46] <sustrik>	and IOCP for polling
| [Friday 11 February 2011] [06:12:56] <sustrik>	check that out first though
| [Friday 11 February 2011] [06:14:49] <Guthur>	yeah ReadFile/WriteFile sync, or ReadFileEx/WriteFileEx async
| [Friday 11 February 2011] [06:15:03] <Guthur>	each of those accept a completion callback function
| [Friday 11 February 2011] [06:15:46] <Guthur>	umm I haven't seen this IOCP 
| [Friday 11 February 2011] [06:15:50] <Guthur>	I'll check that out
| [Friday 11 February 2011] [08:28:13] <zchrish>	Question about exceptions and C++ : When a user gives a bogus hostname, the code asserts. Can I catch the error; what is the accepted alternative to dying in this case?
| [Friday 11 February 2011] [08:28:24] <zchrish>	This is on a connect.
| [Friday 11 February 2011] [08:29:40] <drbobbeaty>	You're going to need to check the data before you pass it to zmq. The assert() is not "catchable" like an exception is.
| [Friday 11 February 2011] [08:31:18] <zchrish>	I see; thank you.
| [Friday 11 February 2011] [09:46:08] <ianbarber>	pieterh: re DPC talk, will do, I was just waiting to see if i'll be doing it at confoo in canada as well (already speaking there about solr, they asked if I could do another). Not that it takes much longer to update twice
| [Friday 11 February 2011] [09:52:48] <ianbarber>	i do hope this talk doesn't suck! different sort of audience with PHP devs to your fosdem one, not so much multithreading being discussed :)
| [Friday 11 February 2011] [09:56:54] <sustrik>	that makes the talk more interesting imo
| [Friday 11 February 2011] [12:27:49] <mikko>	pieterh: there?
| [Friday 11 February 2011] [13:52:56] <Guthur>	do we have a way of executing unit tests on the build server?
| [Friday 11 February 2011] [13:53:09] <Guthur>	or is that outside the remit
| [Friday 11 February 2011] [14:13:42] <sustrik>	Guthur: make check is executed when zmq is built
| [Friday 11 February 2011] [14:14:58] <Guthur>	i wonder if I could get something similar set up for clrzmq1
| [Friday 11 February 2011] [14:15:05] <Guthur>	clrzmq2*
| [Friday 11 February 2011] [14:19:01] <Guthur>	mikko, you about?
| [Friday 11 February 2011] [16:29:09] <CIA-21>	jzmq: 03Nathan Marz 07master * r7983d5c 10/ src/Socket.cpp : fix type for args to linger from github issue #26 - http://bit.ly/dWrCkv
| [Friday 11 February 2011] [16:29:10] <CIA-21>	jzmq: 03Gonzalo Diethelm 07master * r306e3b8 10/ src/Socket.cpp : Arranged proposed changes a bit, and added a cast to avoid a warning. - http://bit.ly/eiciUG
| [Friday 11 February 2011] [21:25:17] <andrewvc>	chuck
| [Friday 11 February 2011] [21:25:19] <andrewvc>	err
| [Friday 11 February 2011] [21:25:21] <andrewvc>	cremes: around?
| [Friday 11 February 2011] [21:25:32] <andrewvc>	I think I found the bug, it's in ffi-rzmq I believe
| [Saturday 12 February 2011] [01:41:04] <yrashk>	under certain circumstances I am getting some weird segfault in zmq_recv (I use it in an Erlang NIF, and it works fine until I create a so called 'release' for my erlang app)
| [Saturday 12 February 2011] [01:41:07] <yrashk>	https://gist.github.com/2b197cc5718a9f6452e6
| [Saturday 12 February 2011] [01:41:10] <yrashk>	      peer_identity = 0x870e5bfa <Address 0x870e5bfa out of bounds>
| [Saturday 12 February 2011] [01:41:15] <yrashk>	looks suspicious
| [Saturday 12 February 2011] [01:41:31] <yrashk>	any ideas what to do to figure out the source of the problem
| [Saturday 12 February 2011] [01:41:42] <yrashk>	happens only in that beforementioned setting and only on osx
| [Saturday 12 February 2011] [01:41:45] <yrashk>	works fine on linux
| [Saturday 12 February 2011] [01:45:04] <yrashk>	sustrik: ^^^
| [Saturday 12 February 2011] [01:51:10] <yrashk>	and yes, this is 2.1.0 and master
| [Saturday 12 February 2011] [02:31:21] <sustrik>	yrashk: aren't you using same socket from multiple threads?
| [Saturday 12 February 2011] [02:32:31] <yrashk>	well, all sockets are created in thread #1
| [Saturday 12 February 2011] [02:32:46] <yrashk>	then I use push socket from a thread #1
| [Saturday 12 February 2011] [02:32:55] <yrashk>	and a pul socket from thread #2
| [Saturday 12 February 2011] [02:32:58] <yrashk>	pull*
| [Saturday 12 February 2011] [02:33:56] <yrashk>	will that result in an undefined behaviour?
| [Saturday 12 February 2011] [02:35:55] <sustrik>	if passing of the socket from #1 to #2 is well synchronised, then it should be ok
| [Saturday 12 February 2011] [02:36:52] <yrashk>	Each MQ socket belonging to a particular context may only be used by the thread that created it using zmq_socket().
| [Saturday 12 February 2011] [02:37:02] <yrashk>	I might have missed this
| [Saturday 12 February 2011] [02:37:21] <yrashk>	so the documentation says I have to use the socket form a thread that created it?
| [Saturday 12 February 2011] [02:37:24] <yrashk>	from*
| [Saturday 12 February 2011] [02:37:37] <sustrik>	with 2.1 the restriction is alleviated
| [Saturday 12 February 2011] [02:37:47] <yrashk>	k
| [Saturday 12 February 2011] [02:37:48] <sustrik>	you *can* pass sockets between threads
| [Saturday 12 February 2011] [02:38:03] <sustrik>	but you can't access a socket from 2 threads in parallel
| [Saturday 12 February 2011] [02:38:18] <yrashk>	I am never touching that pull socket from the 1st thread
| [Saturday 12 February 2011] [02:38:30] <yrashk>	except for its initialization
| [Saturday 12 February 2011] [02:39:36] <sustrik>	how do you pass the socket to the other thread?
| [Saturday 12 February 2011] [02:40:30] <yrashk>	it just lives in a class instance that 1st thread creates
| [Saturday 12 February 2011] [02:42:39] <yrashk>	after that 1s thread creates a 2nd thread and passes that object as an argument to a thread function
| [Saturday 12 February 2011] [02:42:50] <sustrik>	ok, i see
| [Saturday 12 February 2011] [02:42:53] <sustrik>	that should be ok
| [Saturday 12 February 2011] [02:43:30] <yrashk>	is there anything else that might result in that segfault? specifically on OSX
| [Saturday 12 February 2011] [02:43:39] <yrashk>	as Linux build seems to work just fine
| [Saturday 12 February 2011] [02:43:49] <yrashk>	at least I am yet to see a single crash in the same scenario
| [Saturday 12 February 2011] [02:43:58] <yrashk>	while OSX build crashes 80-90% times
| [Saturday 12 February 2011] [02:44:05] <sustrik>	well, what you have shown me looks like a socket have been closed while still being used
| [Saturday 12 February 2011] [02:44:22] <sustrik>	either from another thread
| [Saturday 12 February 2011] [02:44:51] <sustrik>	or from a single thread this way: zmq_close(x);zmq_recv(x,...);
| [Saturday 12 February 2011] [02:45:03] <sustrik>	do you have a minimal test case?
| [Saturday 12 February 2011] [02:45:31] <yrashk>	not yet
| [Saturday 12 February 2011] [02:45:38] <yrashk>	the setting is pretty complicated
| [Saturday 12 February 2011] [02:45:45] <sustrik>	ok
| [Saturday 12 February 2011] [02:45:57] <yrashk>	as it works just fine when not packaged as an erlang app release
| [Saturday 12 February 2011] [02:47:34] <yrashk>	I am just trying to think of any possible explanation of this segfault
| [Saturday 12 February 2011] [02:48:11] <sustrik>	library mismatch?
| [Saturday 12 February 2011] [02:48:31] <sustrik>	the recv that fails, is it the first recv called?
| [Saturday 12 February 2011] [02:50:07] <yrashk>	nope
| [Saturday 12 February 2011] [02:50:25] <yrashk>	normally anywhere from like 4 calls to about, say, 20
| [Saturday 12 February 2011] [02:52:38] <sustrik>	memory overwrite then?
| [Saturday 12 February 2011] [02:52:49] <sustrik>	it's just a guesswork
| [Saturday 12 February 2011] [02:53:57] <yrashk>	well may be
| [Saturday 12 February 2011] [02:54:06] <yrashk>	but I am not quite positive how can this happen
| [Saturday 12 February 2011] [02:54:17] <yrashk>	and only when the app is packaged
| [Saturday 12 February 2011] [02:54:56] <sustrik>	it'a a segfault, right?
| [Saturday 12 February 2011] [02:55:09] <sustrik>	does it print out the address it segfaults at?
| [Saturday 12 February 2011] [02:56:48] <yrashk>	it is
| [Saturday 12 February 2011] [02:57:17] <yrashk>	https://gist.github.com/63c48785c8f42c6c1f8b
| [Saturday 12 February 2011] [02:58:18] <sustrik>	i don't see the notification about the segfault there
| [Saturday 12 February 2011] [02:58:51] <sustrik>	i mean what address it tries to access that is out of bounds?
| [Saturday 12 February 2011] [02:59:07] <yrashk>	      peer_identity = 0x870e5bfa <Address 0x870e5bfa out of bounds>
| [Saturday 12 February 2011] [02:59:12] <yrashk>	I guess this is it
| [Saturday 12 February 2011] [03:00:35] <sustrik>	nope
| [Saturday 12 February 2011] [03:00:50] <sustrik>	it prints "segfault" somewhere
| [Saturday 12 February 2011] [03:00:58] <sustrik>	is there an address mentioned there?
| [Saturday 12 February 2011] [03:01:52] <yrashk>	it didn't print any address
| [Saturday 12 February 2011] [03:02:05] <yrashk>	anyway I think you led me into something
| [Saturday 12 February 2011] [03:04:40] <yrashk>	thanks a lot!
| [Saturday 12 February 2011] [03:07:07] <yrashk>	I really appreciate your help, sustrik -- I think I got it
| [Saturday 12 February 2011] [03:08:30] 	 * sustrik is curious
| [Saturday 12 February 2011] [03:08:36] <sustrik>	what's the problem?
| [Saturday 12 February 2011] [03:09:15] <yrashk>	apparently due to the hack I used to ensure a NIF module is loaded, I was calling initializion of that NIF twice
| [Saturday 12 February 2011] [03:09:21] <yrashk>	and it rewrote the context
| [Saturday 12 February 2011] [03:09:23] <yrashk>	facepalm
| [Saturday 12 February 2011] [03:09:49] <yrashk>	absolute facepalm
| [Saturday 12 February 2011] [03:10:08] <yrashk>	well I didn't check that it actually overwrote the context
| [Saturday 12 February 2011] [03:10:16] <yrashk>	but it is fairly trivial to guess that from the code
| [Saturday 12 February 2011] [03:10:19] <yrashk>	because it's my code
| [Saturday 12 February 2011] [03:10:21] <yrashk>	:]
| [Saturday 12 February 2011] [03:12:59] <sustrik>	:)
| [Saturday 12 February 2011] [05:00:06] <pieterh>	hi guys
| [Saturday 12 February 2011] [05:00:24] <pieterh>	seems our email server was out of action for a while
| [Saturday 12 February 2011] [05:00:41] <pieterh>	it looks like stuff was queued but not being sent out
| [Saturday 12 February 2011] [05:01:00] <pieterh>	this would have affected the zeromq-dev list presumably
| [Saturday 12 February 2011] [05:01:33] <pieterh>	anyhow, I rebooted the beast and emails are now slowly appearing 
| [Saturday 12 February 2011] [08:57:23] <pieterh>	Anyone hitting "Successful WSASTARTUP not yet performed (c:\work\src\zeromq2\src\mailbox.cpp:263)" on Windows
| [Saturday 12 February 2011] [08:57:27] <pieterh>	?
| [Saturday 12 February 2011] [09:18:25] <Guthur>	pieterh, never seen such an error myself
| [Saturday 12 February 2011] [09:18:58] <Guthur>	which windows version?
| [Saturday 12 February 2011] [09:21:17] <pieterh>	Guthur: I'm running WinXP, this hits at zmq_init()
| [Saturday 12 February 2011] [09:21:41] <pieterh>	Seems new to 2.1.0
| [Saturday 12 February 2011] [09:22:11] <Guthur>	I've be running 2.1.0 ok recently, WinXP as well
| [Saturday 12 February 2011] [09:22:58] <Guthur>	sorry, that's not really helpful for you though
| [Saturday 12 February 2011] [09:23:18] <pieterh>	I'll check if zmq is doing WSAStartup or not...
| [Saturday 12 February 2011] [09:24:39] <Guthur>	i'm looking at IOCP today for ICP on win
| [Saturday 12 February 2011] [09:24:56] <Guthur>	not sure if I will have it ready this weekend though, it's not very well documented
| [Saturday 12 February 2011] [09:25:30] <Guthur>	ICP/IPC
| [Saturday 12 February 2011] [09:27:46] <pieterh>	getting ipc: to work on win32 would be great
| [Saturday 12 February 2011] [09:28:24] <pieterh>	for some reason I'm getting zmq calling make_socketpair before doing WSAStartup... strange
| [Saturday 12 February 2011] [09:37:36] <sustrik>	pieterh: what version are you using?
| [Saturday 12 February 2011] [09:37:42] <pieterh>	latest from github
| [Saturday 12 February 2011] [09:37:59] <pieterh>	stepping though, it definitely tries to create a mailbox socket pair before doing WSAStartup
| [Saturday 12 February 2011] [09:38:15] <pieterh>	C++ is a joy to understand
| [Saturday 12 February 2011] [09:38:22] <sustrik>	how come?
| [Saturday 12 February 2011] [09:38:26] <sustrik>	see ctx.cpp
| [Saturday 12 February 2011] [09:38:36] <pieterh>	I am staring at it :-)
| [Saturday 12 February 2011] [09:38:41] <sustrik>	ctx_t constructor
| [Saturday 12 February 2011] [09:38:52] <sustrik>	line 36
| [Saturday 12 February 2011] [09:38:53] <pieterh>	any specific line no?
| [Saturday 12 February 2011] [09:39:08] <sustrik>	the very thing fitst done is WSAStartup
| [Saturday 12 February 2011] [09:39:23] <pieterh>	well, line 36 is a blank line here
| [Saturday 12 February 2011] [09:39:30] <pieterh>	yes, the very first thing it does is WSAStartup
| [Saturday 12 February 2011] [09:40:07] <sustrik>	that's zmq_init() implementation
| [Saturday 12 February 2011] [09:40:17] <pieterh>	ok, when I debug it step by step, I get...
| [Saturday 12 February 2011] [09:40:23] <pieterh>	(hang on, it'll take me a second...)
| [Saturday 12 February 2011] [09:41:36] <Guthur>	cool, just got feedback of some users of zmq2 and clrzmq2 being used as core tech, sweet
| [Saturday 12 February 2011] [09:42:07] <Guthur>	good to be getting feedback on some field tests 
| [Saturday 12 February 2011] [09:42:09] <pieterh>	sustrik: array, vector, mutex_t, vector, mailbox constructors before it does first line of ctx constructor
| [Saturday 12 February 2011] [09:42:38] <pieterh>	that is, after calling ctx constructor from zmq_init...
| [Saturday 12 February 2011] [09:42:38] <sustrik>	wait a sec, checking...
| [Saturday 12 February 2011] [09:42:57] <pieterh>	Guthur: saw that on twitter... nice
| [Saturday 12 February 2011] [09:43:06] <sustrik>	ok, got it
| [Saturday 12 February 2011] [09:43:10] <sustrik>	let me fix it
| [Saturday 12 February 2011] [09:43:26] <pieterh>	excellent, can you explain what it's doing?
| [Saturday 12 February 2011] [09:43:44] <Guthur>	pieterh, they already caught a couple of bugs, so paying dividends already
| [Saturday 12 February 2011] [09:43:54] <Guthur>	bugs in clrzmq2
| [Saturday 12 February 2011] [09:44:10] <pieterh>	It's nice to have users :-)
| [Saturday 12 February 2011] [09:44:12] <sustrik>	constructors of embedded object are called *before* the constructor of the main object
| [Saturday 12 February 2011] [09:44:26] <pieterh>	sustrik: ah, and mailbox is embedded I guess
| [Saturday 12 February 2011] [09:44:26] <sustrik>	ctx_t has a member called term_mailbox
| [Saturday 12 February 2011] [09:44:30] <pieterh>	right
| [Saturday 12 February 2011] [09:44:31] <sustrik>	right
| [Saturday 12 February 2011] [09:44:41] 	 * pieterh found a bug! :-)
| [Saturday 12 February 2011] [09:45:07] <pieterh>	you could move the WSAStartup code to zmq_init
| [Saturday 12 February 2011] [09:45:17] <sustrik>	yes, i should
| [Saturday 12 February 2011] [09:45:28] <pieterh>	well, let me try that, test it, submit a patch
| [Saturday 12 February 2011] [09:45:33] <sustrik>	goodo
| [Saturday 12 February 2011] [09:45:38] <pieterh>	it'll take me 3 minutes...
| [Saturday 12 February 2011] [09:46:21] <sustrik>	also, to retain symetricity, move WSACleanup to zmq_term()
| [Saturday 12 February 2011] [09:50:38] <zchrish>	In C++, should a context ever be introduced in a place other than in main()?
| [Saturday 12 February 2011] [09:52:10] <zchrish>	I am trying to design a thread management strategy to incorporate some sort of error management. Will a context ever become corrupted?
| [Saturday 12 February 2011] [09:59:48] <pieterh>	sustrik: ok, fixed and tested, sending patch now
| [Saturday 12 February 2011] [10:04:39] <pieterh>	zchrish: you can create a context anywhere you like but two threads that want to communicate via inproc: must share the same context
| [Saturday 12 February 2011] [10:04:51] <pieterh>	so the natural place is usually where you create child threads, which is usually main()
| [Saturday 12 February 2011] [10:05:15] <pieterh>	and no, a context will not become corrupted unless your application overwrites memory erroneously
| [Saturday 12 February 2011] [10:05:41] <zchrish>	OK; thanks.
| [Saturday 12 February 2011] [10:17:20] <sustrik>	pieterh: please, sign-off the patch
| [Saturday 12 February 2011] [10:17:28] <sustrik>	(commit -s)
| [Saturday 12 February 2011] [10:40:11] <Guthur>	sustrik, he has left
| [Saturday 12 February 2011] [10:54:54] <sustrik>	ah, missed that, thanks
| [Saturday 12 February 2011] [10:55:23] <Guthur>	sustrik, question about the IOCP integration...
| [Saturday 12 February 2011] [10:55:32] <sustrik>	sure
| [Saturday 12 February 2011] [10:55:33] <sustrik>	go on
| [Saturday 12 February 2011] [10:55:54] <Guthur>	will the zmq engine be able to call PostQueuedCompletionStatus on socket recvs and sends
| [Saturday 12 February 2011] [10:56:37] <sustrik>	?
| [Saturday 12 February 2011] [10:56:49] <Guthur>	i could be missing something but that seems to be how IOCP works, it's just a means of syncing stuff
| [Saturday 12 February 2011] [10:57:43] <Guthur>	so the polling object calls GetQueuedCompletionStatusEx to get any signalled events
| [Saturday 12 February 2011] [10:58:17] <Guthur>	but i'm having trouble seeing where these would get signalled form
| [Saturday 12 February 2011] [10:58:19] <Guthur>	from*
| [Saturday 12 February 2011] [10:58:34] <sustrik>	i would say the NamesPipe would signal it
| [Saturday 12 February 2011] [10:58:44] <sustrik>	you don't need to do that yourself
| [Saturday 12 February 2011] [10:58:57] <Guthur>	that's what i was initially thinking too
| [Saturday 12 February 2011] [10:59:08] <Guthur>	i'll dig a bit more
| [Saturday 12 February 2011] [10:59:09] 	 * sustrik never used IOCP though
| [Saturday 12 February 2011] [10:59:16] <Guthur>	the documentation is useless
| [Saturday 12 February 2011] [10:59:22] <Guthur>	MSDN is crap
| [Saturday 12 February 2011] [11:01:42] <sustrik>	any examples out there?
| [Saturday 12 February 2011] [11:02:16] <Guthur>	some stuff, I have more code here, but they do seem to be calling PostQueuedCompletionStatus explicitly
| [Saturday 12 February 2011] [11:02:33] <Guthur>	they are passing custom overlapped structs with event details
| [Saturday 12 February 2011] [11:03:38] <Guthur>	I have some server code here, i'll look through that
| [Saturday 12 February 2011] [11:04:12] <sustrik>	Have you seen this:
| [Saturday 12 February 2011] [11:04:13] <sustrik>	http://lists.zeromq.org/pipermail/zeromq-dev/2010-September/006240.html
| [Saturday 12 February 2011] [11:06:30] <Guthur>	I hadn't seen that 
| [Saturday 12 February 2011] [11:59:56] <Guthur>	I think I'm just going to have to throw some code together an experiment
| [Saturday 12 February 2011] [12:23:06] <sustrik>	maybe discussing it at some windows forum may give you some insight into different technologies
| [Saturday 12 February 2011] [12:23:16] <Guthur>	sustrik, way ahead. hehe
| [Saturday 12 February 2011] [12:23:26] <Guthur>	talking to someone on #winapi
| [Saturday 12 February 2011] [12:23:29] <sustrik>	:)
| [Saturday 12 February 2011] [12:23:50] <Guthur>	it is indeed possible to get events automatically from pipes via IOCP
| [Saturday 12 February 2011] [12:23:56] <Guthur>	it's just a little confusing
| [Saturday 12 February 2011] [12:32:10] <sustrik>	i see
| [Saturday 12 February 2011] [12:36:16] <CIA-21>	zeromq2: 03Pieter Hintjens 07master * r14a0e14 10/ (src/ctx.cpp src/zmq.cpp): 
| [Saturday 12 February 2011] [12:36:16] <CIA-21>	zeromq2: Fixed win32 issue with WSAStartup
| [Saturday 12 February 2011] [12:36:16] <CIA-21>	zeromq2:  - ctx constructor was calling mailbox_t constructor implicitly
| [Saturday 12 February 2011] [12:36:16] <CIA-21>	zeromq2:  - moved WSAStartup and WSACleanup to be outside constructor/destructor
| [Saturday 12 February 2011] [12:36:16] <CIA-21>	zeromq2: Signed-off-by: Pieter Hintjens <ph@imatix.com> - http://bit.ly/f693K5
| [Saturday 12 February 2011] [14:01:52] <eut>	does anyone use the lua zmq bindings? i'm having some trouble with the nonblocking recv
| [Saturday 12 February 2011] [14:02:03] <eut>	it seems as though i can never receive a message
| [Saturday 12 February 2011] [14:05:05] <cremes>	eut: what kind of sockets are you using in your test?
| [Saturday 12 February 2011] [14:05:15] <eut>	xrep/xreq
| [Saturday 12 February 2011] [14:09:02] <eut>	ah, never mind...
| [Saturday 12 February 2011] [14:09:14] <cremes>	ok
| [Saturday 12 February 2011] [14:09:26] <eut>	it looks like zmq buffers outgoing messages, sending several all at once
| [Saturday 12 February 2011] [14:10:09] <eut>	so sometimes i would quit listening before it finally sent
| [Saturday 12 February 2011] [14:10:10] <cremes>	i believe it has an internal timer on its I/O thread so that messages are coalesced and sent
| [Saturday 12 February 2011] [14:10:26] <cremes>	kind of like nagle's algorithm
| [Saturday 12 February 2011] [14:10:56] <eut>	ok i see
| [Saturday 12 February 2011] [14:11:47] <eut>	is there a way to influence that internal timer (or whatever)?
| [Saturday 12 February 2011] [14:18:16] <cremes>	eut: don't know... plus, i may be wrong on that
| [Saturday 12 February 2011] [14:18:57] <cremes>	ask the mailing list; be sure to include a pointer to your code just in case it's a different issue
| [Saturday 12 February 2011] [14:19:05] <eut>	ok
| [Saturday 12 February 2011] [14:35:46] <zedas>	hey can anyone point me at the docs on how 2.1.0 does graceful shutdown?  apparently there's a change where sockets will LINGER or not?
| [Saturday 12 February 2011] [14:37:53] <cremes>	zedas: https://github.com/zeromq/zeromq2/blob/master/doc/zmq_term.txt
| [Saturday 12 February 2011] [14:38:19] <cremes>	and
| [Saturday 12 February 2011] [14:38:20] <cremes>	https://github.com/zeromq/zeromq2/blob/master/doc/zmq_setsockopt.txt
| [Saturday 12 February 2011] [14:38:54] <cremes>	by default, it will "linger" forever until all packets are flushed
| [Saturday 12 February 2011] [14:47:10] <Guthur>	ah, i think i'm making progress
| [Saturday 12 February 2011] [14:47:57] <Guthur>	i'll not have the IOCP in ZMQ tonight, but I think i might be able to get it in soon enough
| [Saturday 12 February 2011] [14:48:21] <Guthur>	I have it working in a small test client server app
| [Saturday 12 February 2011] [15:03:03] <zedas>	cremes: ok thanks, i've gotta get 2.1.0 working with mongrel2 and this is the only thing that's broken right now.
| [Saturday 12 February 2011] [19:08:22] <rbitcon>	Howdy, I am kooking to be pointed in the right direction for help
| [Saturday 12 February 2011] [19:09:51] <rbitcon>	I am using zeromq with Python in a REQ/RESP model with one server and many "workers". I see that the zmq library take up hude amounts of RAM
| [Saturday 12 February 2011] [19:11:08] <rbitcon>	I read the docs about socket.setsockopt(zmq.HWM, 125), but it is not that clear
| [Saturday 12 February 2011] [19:11:24] <rbitcon>	any pointers?
| [Saturday 12 February 2011] [19:52:17] <rbitcon>	Solved my problem with memory usage.
| [Saturday 12 February 2011] [19:53:49] <rbitcon>	I downloaded pyzmq 2.0.10.1 and dis a plan python.exe setup.py install, previously i did a development build and install or 2.0.10. This is all under windows7 and using python2.6
| [Saturday 12 February 2011] [20:10:11] <tjgillies>	if im behind NAT can i use zeromq to do udp hole punching?
| [Saturday 12 February 2011] [22:35:24] <Seta00>	anyone from the pyzmq team here?
| [Saturday 12 February 2011] [22:35:43] <Seta00>	in fact, anyone with python 2.7 pyzmq builds for windows here?
| [Saturday 12 February 2011] [22:35:47] <Seta00>	it just won't install
| [Sunday 13 February 2011] [03:50:48] <sustrik>	zedas: just set ZMQ_LINGER option to zero for all the sockets and everything should work as with 2.0.x
| [Sunday 13 February 2011] [03:52:34] <sustrik>	Guthut: wow!
| [Sunday 13 February 2011] [04:06:39] <CIA-21>	zeromq2: 03Martin Sustrik 07master * rba26cc9 10/ src/zmq.cpp : 
| [Sunday 13 February 2011] [04:06:39] <CIA-21>	zeromq2: Build problem with OpenPGM and MSVC fixed
| [Sunday 13 February 2011] [04:06:39] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/guRl75
| [Sunday 13 February 2011] [06:30:27] <Guthur>	Sustrik: ping
| [Sunday 13 February 2011] [06:33:11] <DeadZen>	whats zeromq?
| [Sunday 13 February 2011] [06:38:52] <mikko>	DeadZen: http://www.zeromq.org/
| [Sunday 13 February 2011] [06:44:23] <Guthur>	in like the '0MQ in 100 words' in the guide as a description
| [Sunday 13 February 2011] [06:44:25] <Guthur>	http://zguide.zeromq.org/chapter:all#toc2
| [Sunday 13 February 2011] [06:49:59] <Guthur>	mikko, would be possible to have tests run as part of a bindings build, on the build server?
| [Sunday 13 February 2011] [06:51:57] <mikko>	sure
| [Sunday 13 February 2011] [06:53:20] <Guthur>	cool, I don't have the tests at the moment, but it is something I would like to add in the future for clrzmq2
| [Sunday 13 February 2011] [07:04:55] <mikko>	it should be a fairly painless process to add them to builds
| [Sunday 13 February 2011] [07:20:07] <mikko>	i to the b
| [Sunday 13 February 2011] [07:45:33] <Guthur>	I've been looking into IOCP for named pipes connection under windows, the main issue I have found is differentiating between the read and write operations. It is possible to pass in a handle to an event object to writefile function (as part of the overlapped struct), which will allow differentiation.
| [Sunday 13 February 2011] [07:46:04] <Guthur>	The only issue with that is that both the poller and and the writer need the handle to that event object.
| [Sunday 13 February 2011] [07:47:12] <Guthur>	or at least for the poller to know it is a write event object, it will be matched to the right pipe as part of the return from IOCP
| [Sunday 13 February 2011] [10:25:45] <sustrik>	Guthur: pong
| [Sunday 13 February 2011] [10:30:03] <Guthur>	sustrik, did that stuff i posted earlier make much sense?
| [Sunday 13 February 2011] [10:30:25] <sustrik>	i have no idea how IOCP works :|
| [Sunday 13 February 2011] [10:30:37] <sustrik>	anyway, what you need for integration with 0mq
| [Sunday 13 February 2011] [10:31:08] <sustrik>	is a polling mechanism that triggers an event when particular "socket" is readable and/or writeable
| [Sunday 13 February 2011] [10:31:26] <sustrik>	it has to be able to handle multiple "sockets" in parallel
| [Sunday 13 February 2011] [10:31:38] <Guthur>	oh yeah IOCP does multiple sockets very well
| [Sunday 13 February 2011] [10:31:57] <sustrik>	and all the event handlers have to be invoked within a single thread
| [Sunday 13 February 2011] [10:32:26] <Guthur>	that's no problem as well
| [Sunday 13 February 2011] [10:32:47] <sustrik>	then it should be easy, no?
| [Sunday 13 February 2011] [10:32:59] <Guthur>	the only complication as far as I can see is differentiating between what event is fired
| [Sunday 13 February 2011] [10:33:36] <sustrik>	can't you use 2 different events?
| [Sunday 13 February 2011] [10:33:47] <sustrik>	event objects i mean
| [Sunday 13 February 2011] [10:34:28] <Guthur>	if we can pass a different event object when writing to the pipe then yes
| [Sunday 13 February 2011] [10:35:01] <Guthur>	2 secs, just going to ask someone about it now
| [Sunday 13 February 2011] [10:36:55] <Guthur>	when one creates the name pipe one passes in an overlapped struct with an event object, this is set active by all events as far as I can see
| [Sunday 13 February 2011] [10:39:42] <sustrik>	aha
| [Sunday 13 February 2011] [10:40:08] <sustrik>	so how you are supposed to know whether the socket is readable or writeable?
| [Sunday 13 February 2011] [10:40:50] <Guthur>	you mean like a connected event?
| [Sunday 13 February 2011] [10:41:02] <sustrik>	hm
| [Sunday 13 February 2011] [10:41:17] <sustrik>	CreateNamedPipe doesn't seem to accept OVERLAPPED struct
| [Sunday 13 February 2011] [10:42:04] <Guthur>	writefile does
| [Sunday 13 February 2011] [10:43:47] <Guthur>	i'm talking to someone more knowledgeable now
| [Sunday 13 February 2011] [10:43:48] <Guthur>	2 secs
| [Sunday 13 February 2011] [10:44:30] 	 * sustrik is reading the docs
| [Sunday 13 February 2011] [10:48:19] <mikko>	Guthur: steve-o might be able to help you with IOCP
| [Sunday 13 February 2011] [10:48:25] <mikko>	he did some tests with it some time ago
| [Sunday 13 February 2011] [10:48:58] <Guthur>	mikko, did he rule it out for any technical reason?
| [Sunday 13 February 2011] [10:49:48] <mikko>	Guthur: i think it wasnt as fast as he expected
| [Sunday 13 February 2011] [10:50:03] <sustrik>	the problem with 0mq is a bit different
| [Sunday 13 February 2011] [10:50:12] <Guthur>	oh, interesting
| [Sunday 13 February 2011] [10:50:20] <sustrik>	namely, select() function that's currently used for polling
| [Sunday 13 February 2011] [10:50:44] <sustrik>	is limited to POSIX-like TCP sockets (winsock)
| [Sunday 13 February 2011] [10:50:54] <sustrik>	it doesn't work with anything else afaik
| [Sunday 13 February 2011] [10:51:04] <sustrik>	ie. named pipes etc.
| [Sunday 13 February 2011] [10:51:20] <mikko>	and kelly brock has done some work
| [Sunday 13 February 2011] [10:51:34] <mikko>	"For those interested, I highly
| [Sunday 13 February 2011] [10:51:34] <mikko>	suggest reading the change lists from V1 to V2rc of libevent, most changes
| [Sunday 13 February 2011] [10:51:34] <mikko>	were required because IOCP is nearly the opposite of all other async
| [Sunday 13 February 2011] [10:51:35] <mikko>	solutions."
| [Sunday 13 February 2011] [10:52:23] <sustrik>	the first question imo is whether IOCP is the only option to poll on TCP sockets and named pipes
| [Sunday 13 February 2011] [10:52:39] <sustrik>	maybe there's a different (and maybe less complex) way
| [Sunday 13 February 2011] [10:53:01] <mikko>	or whether named pipes could be emulated on windows using shared memory
| [Sunday 13 February 2011] [10:53:17] <mikko>	not sure if that makes sense as you would busy wait
| [Sunday 13 February 2011] [10:53:30] <sustrik>	you still to have poll in I/O thread
| [Sunday 13 February 2011] [10:53:37] <sustrik>	if you emulate the named pipes
| [Sunday 13 February 2011] [10:53:47] <sustrik>	you still have to event the I/O thread
| [Sunday 13 February 2011] [10:53:55] <sustrik>	which can be done via TCP socket (slow)
| [Sunday 13 February 2011] [10:54:12] <sustrik>	other option would be something like Event object
| [Sunday 13 February 2011] [10:54:42] <sustrik>	but once again, you can't poll on Event object using select()
| [Sunday 13 February 2011] [10:54:42] <mikko>	thinking out loud: optional dependency to libevent?
| [Sunday 13 February 2011] [10:55:02] <mikko>	new poller type which uses libevent or libev
| [Sunday 13 February 2011] [10:55:17] <mikko>	disabled by default but can be enabled during build
| [Sunday 13 February 2011] [10:55:42] <sustrik>	that would be more work than supporting IOCP natively IMO
| [Sunday 13 February 2011] [10:56:09] <mikko>	i really don't know whats involved in adding support for IOCP
| [Sunday 13 February 2011] [10:56:46] <Guthur>	does steve-o come on irc
| [Sunday 13 February 2011] [10:56:55] <mikko>	yes
| [Sunday 13 February 2011] [10:57:02] <mikko>	he is here usually during the week
| [Sunday 13 February 2011] [10:57:10] <mikko>	he's on NYC timezone
| [Sunday 13 February 2011] [10:57:17] <mikko>	EST?
| [Sunday 13 February 2011] [10:57:21] <sustrik>	still in NY?
| [Sunday 13 February 2011] [10:57:28] <mikko>	i thought so
| [Sunday 13 February 2011] [10:57:31] <sustrik>	he's from hong kong
| [Sunday 13 February 2011] [10:57:52] <mikko>	yeah, i thought he was going to be in NYC for a longer period
| [Sunday 13 February 2011] [10:57:57] <mikko>	maybe i misunderstood
| [Sunday 13 February 2011] [10:57:59] <sustrik>	ah, no idea
| [Sunday 13 February 2011] [10:58:20] <mikko>	he was in NYC and referred to "buying a house" during that time. i thought he might be there for a while
| [Sunday 13 February 2011] [10:58:38] <mikko>	anyway, he does come here occasionally during the week
| [Sunday 13 February 2011] [11:00:13] <Guthur>	there is a way to getting this IOCP working I'm sure
| [Sunday 13 February 2011] [11:01:11] <Guthur>	I'm missing something regarding the identification of the various ops, I can know that an something is happening on a pipe, just not what that something is
| [Sunday 13 February 2011] [11:01:19] <Guthur>	there has to be a way
| [Sunday 13 February 2011] [11:02:54] <sustrik>	Guthur: my impression so far is that event object is associated with particular I/O operation (Read/Write)
| [Sunday 13 February 2011] [11:03:03] <sustrik>	rather than Pipe as such
| [Sunday 13 February 2011] [11:03:18] <Guthur>	yeah, that's correct enough
| [Sunday 13 February 2011] [11:03:38] <Guthur>	sorry if I drew you to a different conclusion before
| [Sunday 13 February 2011] [11:04:05] <sustrik>	ok, maybe i misunderstood what the problem is then
| [Sunday 13 February 2011] [11:05:18] <Guthur>	`Orum on #winapi is posting some IOCP code, it might shed some light
| [Sunday 13 February 2011] [11:21:01] <zchrish>	I am performing a test to perform repeated zmq_init and zmq_term w/o performing any bind; is that permissible? I am noticing a memory leak after a continued run of this test.
| [Sunday 13 February 2011] [11:22:20] <sustrik>	zchrish: yes, it's permissible
| [Sunday 13 February 2011] [11:22:24] <sustrik>	what's the leak?
| [Sunday 13 February 2011] [11:23:58] <zchrish>	I am performing a "cout" of the context pointer and it is giving me a different value over time. I am watching "top" and the amount of memory required by my process is slowing growing. I am performing a zmq_init/zmq_term avery 1-2 seconds.
| [Sunday 13 February 2011] [11:24:37] <mikko>	zchrish: have you checked in valgrind?
| [Sunday 13 February 2011] [11:24:56] <zchrish>	Let me check; thanks.
| [Sunday 13 February 2011] [11:35:15] <zchrish>	Not sure whether the output of valgrind is related to the way I am using my program. I am creating threads which zmq_init and then zmq_term using a pthread_cleanup_push concept. After 20 iterations, I close the master thread which closes the main program. But I don't know whether this closing affects the slave threads which perform the zmq_init/zmq_term.
| [Sunday 13 February 2011] [11:36:02] <zchrish>	==22197== LEAK SUMMARY:
| [Sunday 13 February 2011] [11:36:02] <zchrish>	==22197==    definitely lost: 0 bytes in 0 blocks
| [Sunday 13 February 2011] [11:36:02] <zchrish>	==22197==    indirectly lost: 0 bytes in 0 blocks
| [Sunday 13 February 2011] [11:36:02] <zchrish>	==22197==      possibly lost: 12,584 bytes in 43 blocks
| [Sunday 13 February 2011] [11:36:02] <zchrish>	==22197==    still reachable: 4,552 bytes in 5 blocks
| [Sunday 13 February 2011] [11:36:02] <zchrish>	==22197==         suppressed: 0 bytes in 0 blocks
| [Sunday 13 February 2011] [11:37:31] <zchrish>	I have 3 threads: (A) master and (B),(C) slave threads. In (B), (C), I peform zmq_init and zmq_term based on a simulated incident which indicates a problem.
| [Sunday 13 February 2011] [11:38:48] <sustrik>	run the valgrind with --leak-check=full
| [Sunday 13 February 2011] [11:38:58] <sustrik>	to find out what's leaking
| [Sunday 13 February 2011] [11:39:07] <zchrish>	Anyway, it seems like the amount lost isn't that much, if it is from 0mq, so I won't worry about it at this point. I don't expect to perform a zmq_term and zmq_init very often.
| [Sunday 13 February 2011] [11:43:52] <zchrish>	Hmm. I did this but I am not proficient enough with valgrind to properly interpret the results. The program is simple enough but I am not sure whether someone is interested in re-creating the situation. If so, I will upload somewhere.
| [Sunday 13 February 2011] [11:47:43] <sustrik>	yes. do so. i'll have a look
| [Sunday 13 February 2011] [11:53:57] <zchrish>	I remember watching discussions about uploading to a website but I don't remember; would you please let me know. Thank you.
| [Sunday 13 February 2011] [11:54:09] <zchrish>	I will upload it.
| [Sunday 13 February 2011] [11:55:56] <sustrik>	gist.github.com
| [Sunday 13 February 2011] [11:56:01] <sustrik>	place it there
| [Sunday 13 February 2011] [11:56:07] <sustrik>	post the link here
| [Sunday 13 February 2011] [11:57:44] <Guthur>	sustrik, re: IOCP, what we can do is pass a custom overlapped struct to Connect, Read, Write etc, and this struct will be returned by IOCP
| [Sunday 13 February 2011] [11:58:15] <Guthur>	so the custom struct can have a member containing and enum of the op type, for example
| [Sunday 13 February 2011] [11:58:54] <sustrik>	how would you physically perform the polling?
| [Sunday 13 February 2011] [11:59:05] <sustrik>	WaitForMultiple objects or what?
| [Sunday 13 February 2011] [11:59:19] <Guthur>	GetQueuedCompletionStatus
| [Sunday 13 February 2011] [11:59:24] <Guthur>	GetQueuedCompletionStatusEx
| [Sunday 13 February 2011] [11:59:25] <zchrish>	Not sure if this is the output result; this is my first gist upload....       gist: 824833 
| [Sunday 13 February 2011] [11:59:50] <sustrik>	can you prpvide the link?
| [Sunday 13 February 2011] [12:00:20] <zchrish>	https://gist.github.com/824833
| [Sunday 13 February 2011] [12:00:29] <zchrish>	Is that right?
| [Sunday 13 February 2011] [12:00:36] <zchrish>	I think so.
| [Sunday 13 February 2011] [12:01:18] <sustrik>	ah
| [Sunday 13 February 2011] [12:01:30] <sustrik>	i meant, can you provide the valgrind output?
| [Sunday 13 February 2011] [12:01:44] <zchrish>	Oh, sorry. Let me do another.
| [Sunday 13 February 2011] [12:03:00] <sustrik>	Guthur: I see
| [Sunday 13 February 2011] [12:03:12] <sustrik>	so, a completion port
| [Sunday 13 February 2011] [12:03:29] <sustrik>	is actually a queue of pointers to OVERLAPPED structures
| [Sunday 13 February 2011] [12:05:38] <zchrish>	https://gist.github.com/824840
| [Sunday 13 February 2011] [12:05:43] <zchrish>	is the valgrind output
| [Sunday 13 February 2011] [12:07:13] <sustrik>	thanks
| [Sunday 13 February 2011] [12:08:22] <Guthur>	sustrik, essentially yes
| [Sunday 13 February 2011] [12:08:28] <Guthur>	there is also a completion key
| [Sunday 13 February 2011] [12:08:43] <Guthur>	it's quite common to place the handle of the socket in that
| [Sunday 13 February 2011] [12:08:58] <Guthur>	or some other context struct
| [Sunday 13 February 2011] [12:09:19] <sustrik>	ack
| [Sunday 13 February 2011] [12:09:27] <sustrik>	that seems reasonable
| [Sunday 13 February 2011] [12:09:33] <Guthur>	sustrik, does it sound like it will fullfil 0MQs needs?
| [Sunday 13 February 2011] [12:09:40] <sustrik>	definitely
| [Sunday 13 February 2011] [12:09:48] <Guthur>	sweet
| [Sunday 13 February 2011] [12:10:13] <sustrik>	you'll simply have a I/O thread loop with GetIOCompletionStatus
| [Sunday 13 February 2011] [12:10:39] <sustrik>	should be relativelty easy
| [Sunday 13 February 2011] [12:14:48] <Guthur>	so, do you want me put some code together for an implementation of epoll et al. using IOCP
| [Sunday 13 February 2011] [12:15:14] <sustrik>	definitely
| [Sunday 13 February 2011] [12:15:34] <sustrik>	try to hack something
| [Sunday 13 February 2011] [12:15:45] <sustrik>	feel free to ask about 0mq details in the process
| [Sunday 13 February 2011] [12:16:13] <Guthur>	will do, cheers to all for the help so far
| [Sunday 13 February 2011] [12:16:39] <Guthur>	I need to do something else tonight, for MSc thesis, but I'll continue with the IOCP this week
| [Sunday 13 February 2011] [12:18:22] <sustrik>	great
| [Sunday 13 February 2011] [12:18:59] <Guthur>	just as an aside: according to wiki  IOCP is also available on Solaris 10+
| [Sunday 13 February 2011] [12:19:11] <Guthur>	is ZMQ on solaris?
| [Sunday 13 February 2011] [12:19:55] <sustrik>	sure
| [Sunday 13 February 2011] [12:20:13] <sustrik>	but i think solaris I/O completion ports are a different beast
| [Sunday 13 February 2011] [12:20:23] <Guthur>	yeah probably
| [Sunday 13 February 2011] [12:20:41] <Guthur>	not like I have a solaris box hanging around anyway, hehe
| [Sunday 13 February 2011] [12:21:17] <sustrik>	i recall we've investigated polling mechanisms in solris quite a long time ago
| [Sunday 13 February 2011] [12:21:33] <sustrik>	and devided to go with /dev/poll rather than completion ports
| [Sunday 13 February 2011] [12:23:14] <Guthur>	if I can help bring IOCP on windows to 0MQ i'll be happy enough
| [Sunday 13 February 2011] [13:16:23] <sustrik>	zchrish: it looks like you are not terminating your threads cleanly
| [Sunday 13 February 2011] [13:44:18] <ianbarber>	m to the k (delayed response goodness)
| [Sunday 13 February 2011] [13:51:29] <zchrish>	I see; any pointer is appreciated. Thanks.
| [Sunday 13 February 2011] [14:28:05] <sustrik>	zchrish: pthread_cancel basically means you kill the thread
| [Sunday 13 February 2011] [14:28:30] <sustrik>	what you should do instead is to pthread_join it
| [Sunday 13 February 2011] [16:54:57] <eut>	cremes, i think that the delay or whatever in nonblocking packet delivery is manageable. if things on my end are designed properly then it shouldn't be a problem.
| [Sunday 13 February 2011] [16:55:11] <bitweiler>	hey using a publisher, socket should the publisher receive some request?
| [Sunday 13 February 2011] [16:55:39] <eut>	bitweiler, no
| [Sunday 13 February 2011] [16:55:58] <bitweiler>	eut: why is that?
| [Sunday 13 February 2011] [16:56:08] <eut>	http://api.zeromq.org/zmq_socket.html see summary of ZMQ_PUB characteristics. it is unidirectional and send only
| [Sunday 13 February 2011] [16:56:24] <bitweiler>	okay thanks
| [Sunday 13 February 2011] [17:01:03] <bitweiler>	what is meant by: The zmq_send() function is not implemented for this socket type. where socket type is ZMQ_SUB
| [Sunday 13 February 2011] [17:04:13] <eut>	did you bind or connect to this socket?
| [Sunday 13 February 2011] [17:04:45] <bitweiler>	yes, I bind in the server side and connect on the client side
| [Sunday 13 February 2011] [17:05:18] <eut>	whoops
| [Sunday 13 February 2011] [17:05:21] <bitweiler>	but I'm getting nothing on the client side in response
| [Sunday 13 February 2011] [17:05:31] <mikko>	bitweiler: are you subscribing
| [Sunday 13 February 2011] [17:05:38] <eut>	see that page i linked to earlier for description of ZMQ_SUB
| [Sunday 13 February 2011] [17:05:40] <mikko>	thats the most common thing causing messages not to be received
| [Sunday 13 February 2011] [17:06:09] <eut>	ZMQ_SUB is unidirectional receive only... you cannot send...
| [Sunday 13 February 2011] [17:07:57] <bitweiler>	mikko: yes I'm subscribing
| [Sunday 13 February 2011] [17:08:29] <eut>	i have a question about the xrep/xreq sockets. on the xreq side i have set the socket identity to some 4 byte long string ("111\0"). when i send a message, on the xrep side, i'm getting a 17 byte long response in the first received part.
| [Sunday 13 February 2011] [17:08:52] <mikko>	eut: you get three messages
| [Sunday 13 February 2011] [17:09:11] <mikko>	one with identity, empty message and the actual message
| [Sunday 13 February 2011] [17:09:40] <mikko>	you should send in xreq side in that fashion as well
| [Sunday 13 February 2011] [17:10:06] <mikko>	identity (ZMQ_SNDMORE set), empty message (ZMQ_SNDMORE set), message 
| [Sunday 13 February 2011] [17:10:54] <eut>	i thought that zmq takes care of prepending the socket identity and empty message when sending from a xreq socket
| [Sunday 13 February 2011] [17:11:53] <mikko>	let me check the code, it's been a while since i used xreq/xreq
| [Sunday 13 February 2011] [17:14:14] <eut>	i hope it doesnt matter... but the xrep side is in lua and the xreq side is c
| [Sunday 13 February 2011] [17:18:25] <mikko>	yes, client side prepends
| [Sunday 13 February 2011] [17:18:36] <mikko>	on xrep side you should receive multiple messages
| [Sunday 13 February 2011] [17:18:43] <mikko>	check for ZMQ_RCVMORE
| [Sunday 13 February 2011] [17:21:25] <eut>	yes
| [Sunday 13 February 2011] [17:21:49] <mikko>	does the lua binding expose that?
| [Sunday 13 February 2011] [17:21:58] <eut>	it exposes getsockopt
| [Sunday 13 February 2011] [17:22:11] <eut>	i'm able to see that more messages parts are there
| [Sunday 13 February 2011] [17:22:38] <mikko>	how are you replying with xreq?
| [Sunday 13 February 2011] [17:22:57] <eut>	i'm not replying at all yet, i'm just trying to interpret the received messages correctly.
| [Sunday 13 February 2011] [17:23:31] <mikko>	can i see the xrep code?
| [Sunday 13 February 2011] [17:23:50] <mikko>	trying to focus on too many things at once
| [Sunday 13 February 2011] [17:24:16] <eut>	sure
| [Sunday 13 February 2011] [17:26:05] <eut>	http://codepad.org/TqP35vOT
| [Sunday 13 February 2011] [17:27:20] <mikko>	what about xreq?
| [Sunday 13 February 2011] [17:27:50] <eut>	whoops, this is more correct xrep code: http://codepad.org/YfZepWdv
| [Sunday 13 February 2011] [17:27:57] <eut>	a moment for xreq
| [Sunday 13 February 2011] [17:35:40] <eut>	xreq code: http://codepad.org/3SFTxCwh
| [Sunday 13 February 2011] [17:37:36] <Guthur>	are you not suppose to set the identity before connecting
| [Sunday 13 February 2011] [17:38:32] <eut>	this is the output i'm getting and what i expect should happen: http://codepad.org/PSnx9yqX
| [Sunday 13 February 2011] [17:38:48] <eut>	the first part of the multipart message is 17 bytes for some reason...
| [Sunday 13 February 2011] [17:39:18] <eut>	the identity was set to "222" so i dont understand what is going on
| [Sunday 13 February 2011] [17:40:30] <Guthur>	from guide: If you want to set an identity you must do it before connecting or binding the socket.
| [Sunday 13 February 2011] [17:40:42] <Guthur>	you connect then set the identity in that code
| [Sunday 13 February 2011] [17:40:59] <Guthur>	the one for the xreq
| [Sunday 13 February 2011] [17:41:15] <eut>	:D
| [Sunday 13 February 2011] [17:41:24] <eut>	it works. thanks very much
| [Sunday 13 February 2011] [17:41:38] <Guthur>	you're welcome
| [Sunday 13 February 2011] [17:41:55] <Guthur>	it actually should mention that in the manual
| [Sunday 13 February 2011] [17:42:06] <Guthur>	i'm surprised it doesn't actually
| [Sunday 13 February 2011] [17:42:30] <eut>	it would make a nice addition to the zmq_socket api page
| [Sunday 13 February 2011] [17:42:45] <eut>	err, setsockopt
| [Sunday 13 February 2011] [17:42:51] <Guthur>	yeah I agree
| [Sunday 13 February 2011] [17:43:25] <eut>	do all options need to be set prior to connecting? or are some more flexible?
| [Sunday 13 February 2011] [17:43:42] <Guthur>	no identity is special
| [Sunday 13 February 2011] [17:44:01] <Guthur>	it makes sense that it needs to be before connecting, in a way
| [Sunday 13 February 2011] [17:44:13] <Guthur>	though it might be nice to be able to change an identity
| [Sunday 13 February 2011] [17:45:03] <Guthur>	after connecting, but things could get confusing then, and packet delivery might go terribly wrong
| [Sunday 13 February 2011] [17:45:12] <eut>	right
| [Sunday 13 February 2011] [17:45:46] <eut>	i think its fine the way it is, but it would help to have the api docs updated
| [Sunday 13 February 2011] [17:46:21] <Guthur>	yeah, I'll submit a patch
| [Sunday 13 February 2011] [17:46:33] <Guthur>	there was another thing I wanted to submit for the docs anyway
| [Sunday 13 February 2011] [17:46:49] <eut>	ok sure, thanks for the help
| [Sunday 13 February 2011] [17:47:10] <Guthur>	sure, anytime
| [Sunday 13 February 2011] [17:48:18] <eut>	is the development branch github.com/zeromq/zeromq2?
| [Sunday 13 February 2011] [17:49:29] <mikko>	eut: yes
| [Sunday 13 February 2011] [17:49:39] <mikko>	sorry, had to jet for a minute
| [Sunday 13 February 2011] [17:50:02] <mikko>	17 part response is UUID most likely, should've catched that
| [Sunday 13 February 2011] [17:50:12] <mikko>	17 char part*
| [Sunday 13 February 2011] [17:50:48] <eut>	ah, and of course its binary data so it wont display as normal text
| [Sunday 13 February 2011] [17:54:25] <Guthur>	mikko, do you think the api documentation for setsockopt identity should mention that it has to be set before bind/connect?
| [Sunday 13 February 2011] [17:54:35] <Guthur>	and if so should it be a caution note?
| [Sunday 13 February 2011] [17:54:40] <mikko>	Guthur: i think majority of them should mention it
| [Sunday 13 February 2011] [17:54:55] <mikko>	like HWM affects only subsequent binds/connects
| [Sunday 13 February 2011] [17:55:06] <sustrik>	all of them, actually
| [Sunday 13 February 2011] [17:55:08] <Guthur>	oh, I thought some didn't matter
| [Sunday 13 February 2011] [17:55:09] <eut>	is the delimiter message necessary if only going directly from xrep <-> xreq? it seems like it is only useful for chains longer than two nodes
| [Sunday 13 February 2011] [17:55:31] <Guthur>	good to know
| [Sunday 13 February 2011] [17:55:47] <sustrik>	it should be mentioned in the docs, you are right
| [Sunday 13 February 2011] [17:56:05] <mikko>	i ended up doing a patch for jenkins after running an issue with build slaves
| [Sunday 13 February 2011] [17:56:23] <mikko>	hopefully they'll accept it
| [Sunday 13 February 2011] [17:56:33] <sustrik>	congrats!
| [Sunday 13 February 2011] [17:56:37] <sustrik>	what was wrong there
| [Sunday 13 February 2011] [17:56:39] <sustrik>	?
| [Sunday 13 February 2011] [17:56:50] <mikko>	it adds ssl between slave and master
| [Sunday 13 February 2011] [17:56:54] <Guthur>	is there any opts it doesn't matter for?
| [Sunday 13 February 2011] [17:56:55] <mikko>	rather than having to use stunnel
| [Sunday 13 February 2011] [17:57:06] <mikko>	good for WAN connected slaves
| [Sunday 13 February 2011] [17:57:14] <sustrik>	ack
| [Sunday 13 February 2011] [17:57:27] <sustrik>	Guthur: the system applies to all the options
| [Sunday 13 February 2011] [17:57:33] <mikko>	what are the big todo items for 2.1.x stable ?
| [Sunday 13 February 2011] [17:57:49] <Guthur>	sustrik, ack
| [Sunday 13 February 2011] [17:58:28] <mikko>	i think it might be useful at some point to look into the todo items and sort them by value and effort
| [Sunday 13 February 2011] [17:58:39] <Guthur>	except for subscription string though, correct?
| [Sunday 13 February 2011] [17:58:50] <Guthur>	strings*
| [Sunday 13 February 2011] [17:59:02] <mikko>	that way people needing those features would have a place to check "rough estimation" and possibly chip in
| [Sunday 13 February 2011] [17:59:14] <mikko>	currently todo-list is github tickets mainly (?)
| [Sunday 13 February 2011] [18:01:17] <mikko>	http://sourceforge.net/projects/udt/forums/forum/393036/topic/4061830
| [Sunday 13 February 2011] [18:01:35] <mikko>	interesting, as this seems like the feature that would allow integrating udt with minimal pain
| [Sunday 13 February 2011] [18:09:03] <Guthur>	I updated the docs on a my fork, should I just submit a pull request?
| [Sunday 13 February 2011] [18:09:29] <mikko>	i think currently things go as signed patches over the mailing lists
| [Sunday 13 February 2011] [18:10:39] <Guthur>	ah ok
| [Sunday 13 February 2011] [18:36:36] <Guthur>	I have two minor doc updates, should they be separate patches?
| [Monday 14 February 2011] [02:19:17] <sustrik>	mikko: yes, clear roadmap to 2.1 would be nice
| [Monday 14 February 2011] [02:20:21] <sustrik>	however, i am not sure how to manage it within a distributed development model
| [Monday 14 February 2011] [02:20:37] <sustrik>	would it mean that patches out of scope of the roadmap are not accepted?
| [Monday 14 February 2011] [04:45:17] <mikko>	sustrik: sure they would
| [Monday 14 February 2011] [04:45:23] <mikko>	sustrik: im talking about feature roadmap
| [Monday 14 February 2011] [04:45:36] <mikko>	things that we know needs to be done
| [Monday 14 February 2011] [05:30:46] <mikko>	pieterh: there?
| [Monday 14 February 2011] [05:31:29] <pieterh>	mikko: hi
| [Monday 14 February 2011] [05:31:51] <mikko>	pieterh: is pkgconfig dependency acceptable in zfl?
| [Monday 14 February 2011] [05:32:43] <pieterh>	you mean autoconf tooling?
| [Monday 14 February 2011] [05:33:58] <mikko>	yes
| [Monday 14 February 2011] [05:34:01] <sustrik>	mikko: there's 3.0 roadmap
| [Monday 14 February 2011] [05:34:11] <mikko>	pieterh: let me show you a patch 
| [Monday 14 February 2011] [05:34:15] <mikko>	sec
| [Monday 14 February 2011] [05:34:19] <pieterh>	mikko: I used the same framework as for zmq
| [Monday 14 February 2011] [05:34:30] <pieterh>	but all suggestions welcome, of course
| [Monday 14 February 2011] [05:34:42] <mikko>	pieterh: https://github.com/mkoppanen/zfl/commit/25219e93d42e8fff6fac696c7ebcbe6e661fa2c3
| [Monday 14 February 2011] [05:34:52] <mikko>	pieterh: i sent one pull request for mingw32 fixes earlier
| [Monday 14 February 2011] [05:35:05] <mikko>	that can be rewritten without pkgconfig as well
| [Monday 14 February 2011] [05:35:09] <mikko>	to remove the dependency 
| [Monday 14 February 2011] [05:35:36] <pieterh>	sorry to be ignorant... I'm not even sure what pkgconfig is/does
| [Monday 14 February 2011] [05:36:07] <mikko>	NAME pkg-config - Return metainformation about installed libraries
| [Monday 14 February 2011] [05:36:15] <pieterh>	right
| [Monday 14 February 2011] [05:36:33] <mikko>	cflags, libs to link etc
| [Monday 14 February 2011] [05:36:45] <pieterh>	if you're happier removing the dependency, that's fine by me
| [Monday 14 February 2011] [05:37:00] <mikko>	ok, ill tinker with it this evening
| [Monday 14 February 2011] [05:37:07] <mikko>	the mingw32 fix is more straight-forward
| [Monday 14 February 2011] [05:37:08] <mikko>	https://github.com/mkoppanen/zfl/commit/ce88c706fc0c1bb023cc422e0c707a1a90a07fe8
| [Monday 14 February 2011] [05:37:18] <pieterh>	let me apply that mingw32 patch then...
| [Monday 14 February 2011] [05:37:21] <mikko>	the assumption before was that build happens on linux if gnu compiler is used
| [Monday 14 February 2011] [05:37:38] <mikko>	so -DLINUX got defined in mingw32 and bsd
| [Monday 14 February 2011] [05:37:40] <mikko>	etc
| [Monday 14 February 2011] [05:37:45] <pieterh>	right
| [Monday 14 February 2011] [05:38:03] <pieterh>	there is some plausible benefit in having zfl build the same way as zeromq2
| [Monday 14 February 2011] [05:38:41] <pieterh>	and i assume you made a similar patch for the zeromq2 configure.in?
| [Monday 14 February 2011] [05:38:57] <mikko>	pieterh: zeromq2 hasn't had that in ages
| [Monday 14 February 2011] [05:39:12] <pieterh>	the dependency, you mean?
| [Monday 14 February 2011] [05:39:14] <pieterh>	aight
| [Monday 14 February 2011] [05:39:23] <mikko>	the dependency to pkg-config can be removed
| [Monday 14 February 2011] [05:39:28] <mikko>	ill make a clean patch this evening
| [Monday 14 February 2011] [05:39:33] <pieterh>	nice
| [Monday 14 February 2011] [05:39:44] <mikko>	i think it's easier for users to do: ./configure --with-libzmq=/usr/local
| [Monday 14 February 2011] [05:39:56] <mikko>	rather than having to specify CFLAGS and LDFLAGS
| [Monday 14 February 2011] [05:40:47] <mikko>	this is really more zfl specific as it uses zeromq as a dependency
| [Monday 14 February 2011] [05:41:33] <mikko>	i'll add zfl build on solaris and freebsd at some point
| [Monday 14 February 2011] [05:48:53] <pieterh>	mikko: pull request merged
| [Monday 14 February 2011] [05:49:02] <mikko>	pieterh: will run mingw32 build now
| [Monday 14 February 2011] [05:49:03] <mikko>	sec
| [Monday 14 February 2011] [05:49:41] <mikko>	mingw32 and linux builds running now
| [Monday 14 February 2011] [05:49:46] <pieterh>	on linux it looks in /usr/local by default, right?
| [Monday 14 February 2011] [05:49:57] <mikko>	nope
| [Monday 14 February 2011] [05:50:20] <pieterh>	hmm, so how does this work on all my linux boxes without any special options...?
| [Monday 14 February 2011] [05:50:36] <mikko>	you've added /usr/local to runtime linkers conf
| [Monday 14 February 2011] [05:50:39] <mikko>	?
| [Monday 14 February 2011] [05:50:41] <mikko>	or your distro adds it
| [Monday 14 February 2011] [05:50:44] <pieterh>	let me check...
| [Monday 14 February 2011] [05:50:55] <mikko>	cd /etc/ld.so.conf.d/
| [Monday 14 February 2011] [05:51:02] <pieterh>	LD_LIBRARY_PATH...
| [Monday 14 February 2011] [05:51:28] <mikko>	https://build.valokuva.org/job/zfl-master_ZeroMQ2-master_mingw32/19/
| [Monday 14 February 2011] [05:51:30] <mikko>	mingw builds now
| [Monday 14 February 2011] [05:51:38] <mikko>	and linux builds as well
| [Monday 14 February 2011] [05:52:02] <mikko>	this is how i got it configured on build box:
| [Monday 14 February 2011] [05:52:03] <mikko>	CFLAGS="-I${ZEROMQ2_PREFIX_MASTER_MINGW32}/include" LDFLAGS="-L${ZEROMQ2_PREFIX_MASTER_MINGW32}/lib" ./configure --target=mingw32 --build=i686-linux --host=i586-mingw32msvc
| [Monday 14 February 2011] [05:52:19] <mikko>	for mingw32
| [Monday 14 February 2011] [05:52:34] <mikko>	linux is: CFLAGS="-I${ZEROMQ2_PREFIX_MASTER_GCC}/include" LDFLAGS="-L${ZEROMQ2_PREFIX_MASTER_GCC}/lib" ./configure
| [Monday 14 February 2011] [05:54:17] <pieterh>	hmm, I don't seem to need any of that... need to investigate
| [Monday 14 February 2011] [05:55:03] <mikko>	pieterh: the macro you use uses runtime linker
| [Monday 14 February 2011] [05:55:13] <mikko>	so if you got it configured then it should work (not sure about includes)
| [Monday 14 February 2011] [05:55:44] <stimpie>	I need to implement a push-pull with a custom loadbalancing strategy, what would be the recommend method? adjust the source and create a new socket type? implement it using PAIR's? 
| [Monday 14 February 2011] [05:55:52] <mikko>	do echo | gcc -v -x c -E -
| [Monday 14 February 2011] [05:55:59] <mikko>	and check for default includes
| [Monday 14 February 2011] [05:56:30] <pieterh>	mikko: yes, gcc goes looking in /usr/local/include
| [Monday 14 February 2011] [05:57:07] <pieterh>	stimpie, read the Guide and Ch3 on custom routing using XREP sockets
| [Monday 14 February 2011] [05:57:25] <pieterh>	to do custom routing you *always* use an XREP socket
| [Monday 14 February 2011] [06:01:06] <pieterh>	mikko: IMO it's Ubuntu doing smart stuff with gcc configuration
| [Monday 14 February 2011] [06:01:07] <stimpie>	pieterh, ok thanks I will do some more reading
| [Monday 14 February 2011] [06:01:27] <pieterh>	stimpie, if it's not clear in the Guide, let me know
| [Monday 14 February 2011] [06:02:04] <mikko>	pieterh: yes
| [Monday 14 February 2011] [06:02:17] <mikko>	pieterh: hence the build flag would be nice
| [Monday 14 February 2011] [06:02:24] <pieterh>	mikko: so basically any gcc system that is not set-up to look in /usr needs these build flags
| [Monday 14 February 2011] [06:02:25] <pieterh>	that's clear
| [Monday 14 February 2011] [06:02:51] <pieterh>	feel free to change the README.txt file for zfl (patch)
| [Monday 14 February 2011] [06:03:12] <mikko>	pieterh: i'll create a new patch to add the flag and update docs while im at it
| [Monday 14 February 2011] [06:03:38] <mikko>	probably won't have time until this evening
| [Monday 14 February 2011] [06:04:21] <pieterh>	mikko: :-) there is no hurry
| [Monday 14 February 2011] [06:40:32] <Guthur>	mikko: what was the link to your logs again?
| [Monday 14 February 2011] [06:40:48] <mikko>	http://valokuva.org/~mikko/zeromq.log
| [Monday 14 February 2011] [06:41:03] <Guthur>	cheers, you don't mind me using it?
| [Monday 14 February 2011] [06:41:42] <mikko>	don't like to it if possbly
| [Monday 14 February 2011] [06:41:46] <mikko>	possible*
| [Monday 14 February 2011] [06:42:36] <Guthur>	oh no certainly, it was just for my personal use
| [Monday 14 February 2011] [06:42:44] <Guthur>	to check anything I missed
| [Monday 14 February 2011] [06:42:49] <mikko>	thats fine
| [Monday 14 February 2011] [06:43:59] <Guthur>	i see the talk of 2.1 roadmap earlier, this for movement to a stable release I assume?
| [Monday 14 February 2011] [06:52:25] <sustrik>	yeah
| [Monday 14 February 2011] [06:52:36] <sustrik>	i am not sure how to fomalise it though
| [Monday 14 February 2011] [06:58:11] <Guthur>	sustrik: are there many outstanding issues?
| [Monday 14 February 2011] [06:58:20] <mikko>	gant chart!
| [Monday 14 February 2011] [06:59:02] <sustrik>	:)
| [Monday 14 February 2011] [06:59:12] <sustrik>	the problem is that everyone here is a volunteer
| [Monday 14 February 2011] [06:59:21] <sustrik>	so there's no way to estimate anything
| [Monday 14 February 2011] [07:01:18] <Guthur>	are the issues prioritized at all yet?
| [Monday 14 February 2011] [07:01:58] <sustrik>	what would that be good for?
| [Monday 14 February 2011] [07:02:43] <Guthur>	well maybe there are some that must be resolved and some that would be nice to have resolved
| [Monday 14 February 2011] [07:03:08] <Guthur>	I've not looked at the issues though, so I don't know what there is
| [Monday 14 February 2011] [07:03:19] <Guthur>	is it just the list on github?
| [Monday 14 February 2011] [07:03:29] <sustrik>	well, the point is that even an issue with highest priority won't be solved unless someone decides to solve it
| [Monday 14 February 2011] [07:03:42] <sustrik>	so having priorities is kind of mute
| [Monday 14 February 2011] [07:06:23] <Guthur>	 very true
| [Monday 14 February 2011] [07:08:10] <Guthur>	though from the github issue list it seems hard to know what is an issue stopping 2.1 becoming stable
| [Monday 14 February 2011] [07:08:24] <Guthur>	what/which
| [Monday 14 February 2011] [07:09:03] <sustrik>	there's no formal criterion
| [Monday 14 February 2011] [07:09:26] <sustrik>	if people are happy with stability of 2.1 it will become stable
| [Monday 14 February 2011] [07:10:10] <sustrik>	i think it has to do with migration to 2.1
| [Monday 14 February 2011] [07:10:19] <sustrik>	some people have switched already
| [Monday 14 February 2011] [07:10:22] <sustrik>	some have not
| [Monday 14 February 2011] [07:12:10] <sustrik>	if there's enough people using 2.1 in prodution, i believe we can make it "stable"
| [Monday 14 February 2011] [07:20:34] <Guthur>	is 0MQ then working towards a 2.2 after that
| [Monday 14 February 2011] [07:22:06] <sustrik>	either 2.2 or 3.0
| [Monday 14 February 2011] [07:22:18] <sustrik>	depends on overall sentiment of the community
| [Monday 14 February 2011] [07:27:44] <Guthur>	is the MQ/3.0 Roadmap up to date with current desires for 3.0?
| [Monday 14 February 2011] [07:28:37] <mikko>	i got a couple of desires that i would like to get in later releases
| [Monday 14 February 2011] [07:28:46] <mikko>	but it will take some time to produce patches
| [Monday 14 February 2011] [07:29:08] <mikko>	investigating UDT is one and another one is PUSH/PULL acks
| [Monday 14 February 2011] [07:29:50] <sustrik>	mikko: ack
| [Monday 14 February 2011] [07:30:19] <sustrik>	Guthur: the distinction is that 2.2 has to be backward compatible
| [Monday 14 February 2011] [07:30:37] <sustrik>	while 3.0 can break backward compatibility
| [Monday 14 February 2011] [07:30:52] <sustrik>	so 3.0 is a chance to fix API bugs and mis-designs
| [Monday 14 February 2011] [07:31:18] <sustrik>	however, introducing incompatible API is a painful process
| [Monday 14 February 2011] [07:31:42] <sustrik>	so people may choose to stick with existing API and work on 2.2 instead
| [Monday 14 February 2011] [07:32:08] <mikko>	do we have any outstanding ones?
| [Monday 14 February 2011] [07:32:18] <sustrik>	outstanding what?
| [Monday 14 February 2011] [07:32:27] <mikko>	"so 3.0 is a chance to fix API bugs and mis-designs"
| [Monday 14 February 2011] [07:32:34] <mikko>	api bugs and misdesign
| [Monday 14 February 2011] [07:32:38] <sustrik>	ah, many of them
| [Monday 14 February 2011] [07:32:47] <sustrik>	see socket option types
| [Monday 14 February 2011] [07:32:50] <sustrik>	they are a mess
| [Monday 14 February 2011] [07:34:00] <Guthur>	is that the: Review the types of socket options for getsockopt/setsockopt (it's kind of arbitrary now).
| [Monday 14 February 2011] [07:34:09] <sustrik>	another example: zero-copy should not be default
| [Monday 14 February 2011] [07:34:20] <sustrik>	zmq_send should look like POSIX send:
| [Monday 14 February 2011] [07:34:34] <sustrik>	zmq_send (void *buff, size_t size, int flags);
| [Monday 14 February 2011] [07:34:57] <sustrik>	Guthur: yes
| [Monday 14 February 2011] [07:38:48] <sustrik>	one intriguing option would be to provide both version of the API from the same library
| [Monday 14 February 2011] [07:39:02] <sustrik>	however, i am not sure whether that's technically possible
| [Monday 14 February 2011] [07:40:30] <Guthur>	like some compatibility layer on top the new API
| [Monday 14 February 2011] [07:40:49] <sustrik>	yep
| [Monday 14 February 2011] [07:40:56] <mikko>	LD_PRELOAD sumbols
| [Monday 14 February 2011] [07:40:59] <mikko>	symbols*
| [Monday 14 February 2011] [07:41:01] <mikko>	messy though
| [Monday 14 February 2011] [07:41:18] <sustrik>	not sure how portable that is
| [Monday 14 February 2011] [07:41:25] <mikko>	not very probably
| [Monday 14 February 2011] [07:41:41] <sustrik>	an alternative would be to export symbols such as:
| [Monday 14 February 2011] [07:41:44] <sustrik>	_zmq_init
| [Monday 14 February 2011] [07:41:47] <sustrik>	_zmq_socket
| [Monday 14 February 2011] [07:41:50] <sustrik>	etc.
| [Monday 14 February 2011] [07:41:59] <sustrik>	then have 2 header files
| [Monday 14 February 2011] [07:42:18] <sustrik>	containing simple inline functions
| [Monday 14 February 2011] [07:42:47] <sustrik>	that would call the appropriate _zmq routine
| [Monday 14 February 2011] [08:40:48] <pieterh>	sustrik: wrt 2.1 stable, IMO it's self-regulating...
| [Monday 14 February 2011] [08:41:05] <pieterh>	when there are no patches for a certain period you can assume it's stable
| [Monday 14 February 2011] [08:41:06] <sustrik>	yes, that's what i was saying
| [Monday 14 February 2011] [08:41:19] <pieterh>	difficulty is when you mix old and new code, it can remain unstable forever
| [Monday 14 February 2011] [08:41:36] <sustrik>	ack
| [Monday 14 February 2011] [08:41:44] <pieterh>	i'd not take master HEAD to stable, ever
| [Monday 14 February 2011] [08:41:58] <pieterh>	but rather the 2.1 unstable + patches -> stable
| [Monday 14 February 2011] [08:42:11] <sustrik>	i've missed that
| [Monday 14 February 2011] [08:42:32] <pieterh>	there is an unstable branch, no?
| [Monday 14 February 2011] [08:42:38] <sustrik>	master
| [Monday 14 February 2011] [08:42:51] <pieterh>	ah... well... this won't be optimal then
| [Monday 14 February 2011] [08:43:03] <pieterh>	not if you develop on master
| [Monday 14 February 2011] [08:43:17] <sustrik>	development should go on on topic branches
| [Monday 14 February 2011] [08:43:29] <pieterh>	yes but then it does not get tested...
| [Monday 14 February 2011] [08:43:49] <sustrik>	true
| [Monday 14 February 2011] [08:43:51] <pieterh>	i think the basic principle is that any specific code ages and becomes stable (or unused) automatically
| [Monday 14 February 2011] [08:44:00] <pieterh>	like fine wine
| [Monday 14 February 2011] [08:44:08] <sustrik>	that's the case with 2.1 i think
| [Monday 14 February 2011] [08:44:14] <sustrik>	people are already switching
| [Monday 14 February 2011] [08:44:24] <pieterh>	right but if you mix new wine with the old wine there is a problem
| [Monday 14 February 2011] [08:44:44] <pieterh>	you risk making a stable release that has relatively new, unproven code in it
| [Monday 14 February 2011] [08:45:21] <sustrik>	there's still a maint branch
| [Monday 14 February 2011] [08:45:33] <sustrik>	bugs are still patched in maint
| [Monday 14 February 2011] [08:45:36] <pieterh>	this is something to discuss with Mato when he's back from down-under
| [Monday 14 February 2011] [08:45:47] <sustrik>	yes
| [Monday 14 February 2011] [08:46:29] <pieterh>	if you can cleanly separate older code (6 months+) into its own branch you can push it to 'stable' safely
| [Monday 14 February 2011] [08:46:43] <pieterh>	e.g. stuff like the socket shutdown mechanics from 2.1
| [Monday 14 February 2011] [08:47:02] <mikko>	but in that case you need to separate well-tested from old
| [Monday 14 February 2011] [08:47:12] <pieterh>	but it would be a pity to have e.g. the bug I found on win32 yesterday to still be in a 'stable' release
| [Monday 14 February 2011] [08:47:22] <mikko>	older code that is implicitly used by everyone is more tested than some feature just used by some
| [Monday 14 February 2011] [08:47:28] <pieterh>	yeah
| [Monday 14 February 2011] [08:47:31] <mikko>	in the former you expect to see bugs quicker
| [Monday 14 February 2011] [08:47:39] <pieterh>	so you'd expect, IMO, to see
| [Monday 14 February 2011] [08:47:59] <pieterh>	- very stable (2.0.x), does not change except for major bugs
| [Monday 14 February 2011] [08:48:17] <pieterh>	- (almost) stable (2.1.x), maintained
| [Monday 14 February 2011] [08:48:26] <pieterh>	- raw (master HEAD)
| [Monday 14 February 2011] [08:48:38] <pieterh>	and all new work as rapidly as possible into HEAD
| [Monday 14 February 2011] [08:48:48] <pieterh>	e.g. xsub, xpub should be in HEAD now, so we actually test it
| [Monday 14 February 2011] [08:49:22] <pieterh>	but people have an 'official latest' release to work with
| [Monday 14 February 2011] [08:49:43] <pieterh>	to have to choose between 2.0.x and HEAD is kind of painful
| [Monday 14 February 2011] [08:49:44] <sustrik>	that's 2.1.0
| [Monday 14 February 2011] [08:49:50] <pieterh>	yeah, but it's not maintained :-)
| [Monday 14 February 2011] [08:50:18] <sustrik>	wait a sec
| [Monday 14 February 2011] [08:50:24] <sustrik>	there are 3 things there"
| [Monday 14 February 2011] [08:50:39] <sustrik>	1. latest stable (2.0.10)
| [Monday 14 February 2011] [08:50:52] <sustrik>	2. latest dev (2.0.1)
| [Monday 14 February 2011] [08:50:55] <sustrik>	3. head
| [Monday 14 February 2011] [08:51:03] <pieterh>	2. latest dev (2.1.0) ?
| [Monday 14 February 2011] [08:51:13] <sustrik>	2.1.0, sorry
| [Monday 14 February 2011] [08:51:15] <pieterh>	ack
| [Monday 14 February 2011] [08:51:29] <pieterh>	let me add two things I think would help
| [Monday 14 February 2011] [08:51:50] <pieterh>	a. new code goes into HEAD asap, not topic branches unless extremely unstable
| [Monday 14 February 2011] [08:52:07] <pieterh>	b. latest dev is a branch and gets bug fixes from head
| [Monday 14 February 2011] [08:52:47] <pieterh>	rationale for a = faster testing of new code is very valuable
| [Monday 14 February 2011] [08:52:50] <mikko>	latest dev is bug fixes only?
| [Monday 14 February 2011] [08:52:56] <pieterh>	hmm, yes
| [Monday 14 February 2011] [08:53:02] <pieterh>	at least
| [Monday 14 February 2011] [08:53:05] <sustrik>	then it's same as maint
| [Monday 14 February 2011] [08:53:09] <mikko>	so when do new features get in?
| [Monday 14 February 2011] [08:53:28] <pieterh>	well, this rolls around
| [Monday 14 February 2011] [08:53:31] <mikko>	and is new version branched of from HEAD?
| [Monday 14 February 2011] [08:53:36] <pieterh>	latest dev becomes stable at a certain point
| [Monday 14 February 2011] [08:53:41] <pieterh>	and then new dev is branched from head
| [Monday 14 February 2011] [08:53:49] <pieterh>	like I'd suggest 2.1.0 + patches is today ready for stable
| [Monday 14 February 2011] [08:53:56] <pieterh>	we want people to move off 2.0.10
| [Monday 14 February 2011] [08:54:11] <pieterh>	of course the packages can remain available
| [Monday 14 February 2011] [08:54:24] <pieterh>	but we don't want people asking about stuff that was fixed 6 months ago
| [Monday 14 February 2011] [08:54:56] <sustrik>	i still don't see why we need two maintenance branches instead of a single one
| [Monday 14 February 2011] [08:55:10] <pieterh>	because you have two generations of 'officially released' code
| [Monday 14 February 2011] [08:55:22] <pieterh>	that is standard operating procedure
| [Monday 14 February 2011] [08:55:38] <pieterh>	and you need to maintain both branches
| [Monday 14 February 2011] [08:55:50] <sustrik>	me?
| [Monday 14 February 2011] [08:55:51] <pieterh>	while also having space for new functionality that is raw and liable to break
| [Monday 14 February 2011] [08:55:54] <pieterh>	not you
| [Monday 14 February 2011] [08:55:55] <pieterh>	one
| [Monday 14 February 2011] [08:55:57] <pieterh>	 :-)
| [Monday 14 February 2011] [08:55:59] <sustrik>	:)
| [Monday 14 February 2011] [08:56:06] <pieterh>	i'm happy to do this
| [Monday 14 February 2011] [08:56:09] <pieterh>	i've said that often
| [Monday 14 February 2011] [08:56:33] <mikko>	if the process is being reviewed can we also look into using pull requests on github instead of signed patches?
| [Monday 14 February 2011] [08:56:42] <pieterh>	mikko: +1
| [Monday 14 February 2011] [08:57:29] <pieterh>	it allows the author of a patch to request explicitly that it be applied to a set of target branches
| [Monday 14 February 2011] [08:57:34] <pieterh>	and it creates an asynchronous workflow
| [Monday 14 February 2011] [08:57:36] <pieterh>	+100
| [Monday 14 February 2011] [08:58:56] <sustrik>	ok, we can have as many maintenance branches as we want
| [Monday 14 February 2011] [08:59:14] <sustrik>	have a look at linux, there are some 4-5 of them
| [Monday 14 February 2011] [08:59:25] <pieterh>	indeed
| [Monday 14 February 2011] [08:59:36] <sustrik>	as for new features, linux kernel uses concept of merge windows
| [Monday 14 February 2011] [08:59:50] <mikko>	do they still use the even and odd versions?
| [Monday 14 February 2011] [08:59:56] <sustrik>	nope
| [Monday 14 February 2011] [09:00:04] <sustrik>	basically, there's a week or two in each cycle
| [Monday 14 February 2011] [09:00:15] <sustrik>	when people can ask their new code to be merged
| [Monday 14 February 2011] [09:00:26] <pieterh>	linux kernel processes are *weird*, they don't always make good examples
| [Monday 14 February 2011] [09:00:32] <sustrik>	the rest of the cycle is used to stabilise the new codebase
| [Monday 14 February 2011] [09:01:33] <sustrik>	the merge windows eases the stabilisation process
| [Monday 14 February 2011] [09:02:10] <sustrik>	it makes the development of new features to happen in discrete steps
| [Monday 14 February 2011] [09:02:18] <pieterh>	i'd really avoid trying to imitate the Linux processes unless they solve real problems we face
| [Monday 14 February 2011] [09:02:44] <mikko>	i think one of the issues to solve is: clear and visible roadmap for new features
| [Monday 14 February 2011] [09:02:49] <sustrik>	well, this is the problem we face:
| [Monday 14 February 2011] [09:03:04] <sustrik>	the new fetures are merged in continuously
| [Monday 14 February 2011] [09:03:23] <sustrik>	so what you have is a shifting landscape
| [Monday 14 February 2011] [09:03:48] <pieterh>	i think the roadmap for 2.1 worked pretty well
| [Monday 14 February 2011] [09:04:00] <pieterh>	what sustrik says is right
| [Monday 14 February 2011] [09:04:07] <pieterh>	you cannot take a shifting landscape to stability
| [Monday 14 February 2011] [09:04:20] <pieterh>	today we have no way to produce a stable 2.1 release afaics
| [Monday 14 February 2011] [09:04:36] <pieterh>	except by putting all new work into topic branches and waiting for another 3 months
| [Monday 14 February 2011] [09:04:51] <pieterh>	and even then it would not be based on a real 'unstable'
| [Monday 14 February 2011] [09:05:59] <mikko>	we don't really classify incoming features much
| [Monday 14 February 2011] [09:06:29] <sustrik>	classify?
| [Monday 14 February 2011] [09:06:42] <pieterh>	mikko: you just need to ask Sustrik more often, "what are you going to make?" :-)
| [Monday 14 February 2011] [09:07:17] <mikko>	pieterh: im trying more and more be able to produce patches
| [Monday 14 February 2011] [09:07:30] <Guthur>	i'd like to +1 the pull request, more from a laziness point of view, hehe
| [Monday 14 February 2011] [09:07:36] <mikko>	sustrik: we get a fair amount of feature requests
| [Monday 14 February 2011] [09:07:56] <mikko>	sustrik: which i think could be classified based on two factors: value and effort
| [Monday 14 February 2011] [09:08:04] <mikko>	maybe more factors needed but as a baseline
| [Monday 14 February 2011] [09:08:06] <sustrik>	i see
| [Monday 14 February 2011] [09:08:27] <mikko>	small effort, large value -> you want to do those first
| [Monday 14 February 2011] [09:08:44] <sustrik>	in theory
| [Monday 14 February 2011] [09:08:46] <mikko>	large effort, large value -> maybe schedule somewhere future
| [Monday 14 February 2011] [09:08:47] <mikko>	etc
| [Monday 14 February 2011] [09:08:56] <sustrik>	the reality is that everyone scratches his own itch
| [Monday 14 February 2011] [09:09:28] <sustrik>	so people are going to do work on what they need rather than on effort/value estimates
| [Monday 14 February 2011] [09:09:30] <mikko>	i think this would also give 'tools' to people wanting to contribute
| [Monday 14 February 2011] [09:09:40] <mikko>	they could start from the small effort ones
| [Monday 14 February 2011] [09:09:53] <mikko>	sustrik: that is true as well
| [Monday 14 February 2011] [09:10:12] <sustrik>	sure, but do you really see people asking for something to do
| [Monday 14 February 2011] [09:10:14] <sustrik>	?
| [Monday 14 February 2011] [09:10:56] <sustrik>	it's rather like they choose what to do depending on what they want to use 0mq for
| [Monday 14 February 2011] [09:11:13] <sustrik>	GSoC may be a bit like what you have in mind
| [Monday 14 February 2011] [09:11:27] <mikko>	GSoC and also individuals 
| [Monday 14 February 2011] [09:11:27] <sustrik>	but even with GSoC you just sketch some ideas
| [Monday 14 February 2011] [09:11:33] <pieterh>	mikko, what could be nice is an area on the wiki where people *ask* for help on areas
| [Monday 14 February 2011] [09:11:34] <mikko>	there are people who contribute just for the sake of it
| [Monday 14 February 2011] [09:11:47] <pieterh>	i.e. acting as mentors
| [Monday 14 February 2011] [09:11:48] <sustrik>	and people are free to work on something completely different
| [Monday 14 February 2011] [09:12:09] <mikko>	is it too late for GSoC this year?
| [Monday 14 February 2011] [09:12:13] <sustrik>	nope
| [Monday 14 February 2011] [09:12:31] <sustrik>	the applications are to be posted shortly
| [Monday 14 February 2011] [09:12:34] <mikko>	we should apply. i think there are a couple of things that GSoC students could do
| [Monday 14 February 2011] [09:13:19] <pieterh>	mikko: there is a page on the wiki with about 50 ideas
| [Monday 14 February 2011] [09:13:26] <mikko>	pieterh: which one?
| [Monday 14 February 2011] [09:13:46] <pieterh>	it should be visible from the main community page
| [Monday 14 February 2011] [09:13:49] <pieterh>	hang on...
| [Monday 14 February 2011] [09:14:03] <pieterh>	yeah
| [Monday 14 February 2011] [09:14:12] <pieterh>	http://www.zeromq.org/topics:google-summer-of-code
| [Monday 14 February 2011] [09:14:20] <mikko>	hot topics
| [Monday 14 February 2011] [09:16:20] <pieterh>	:-)
| [Monday 14 February 2011] [09:21:50] <mikko>	udt and sctp are on the list
| [Monday 14 February 2011] [09:21:57] <mikko>	both very interesting transports
| [Monday 14 February 2011] [09:22:22] <mikko>	sustrik: https://github.com/zeromq/zeromq2/issues/issue/160 is this likely to be major change?
| [Monday 14 February 2011] [09:23:15] <Guthur>	From a prospective contributor point of view I think it would be nice to have a list of areas needing work
| [Monday 14 February 2011] [09:23:29] <Guthur>	i was looking at the GSoC and the 3.0 roadmap like that though
| [Monday 14 February 2011] [09:23:51] <Guthur>	i also have an interest in adding win32 IPC
| [Monday 14 February 2011] [09:24:20] <pieterh>	what do you think of the mentor idea?
| [Monday 14 February 2011] [09:24:32] <pieterh>	i.e. area of work means working with someone who helps you get into that code
| [Monday 14 February 2011] [09:25:06] <Guthur>	yeah that's a neat idea, though devs here tend to be very helpful as well
| [Monday 14 February 2011] [09:25:57] <Guthur>	i've been asking here regarding pointers in starting the win32 IPC
| [Monday 14 February 2011] [09:26:14] <Guthur>	got a lot the preliminary research done at the weekend there
| [Monday 14 February 2011] [09:26:53] <Guthur>	sustrik gave me a lot of pointers on where to start looking in ZMQ as well
| [Monday 14 February 2011] [09:27:15] <pieterh>	Grrr. we need ipc: working on windows... :-/
| [Monday 14 February 2011] [09:27:36] <pieterh>	just hitting problems due to that
| [Monday 14 February 2011] [09:28:49] <pieterh>	Guthur, can I help you make IPC work on win32?
| [Monday 14 February 2011] [09:30:24] <pieterh>	Oh... I'm using inproc: ... I take it back :-)
| [Monday 14 February 2011] [09:35:56] <mikko>	pieterh: zfl doesn't need to link against libuuid, right?
| [Monday 14 February 2011] [09:36:10] <Guthur>	pieterh: hehe, well hopefully someone will need it, I'm sure they will
| [Monday 14 February 2011] [09:36:48] <Guthur>	I just need to write some code now for it, my time is limited during the week though due to work, and I'll be in dublin on saturday
| [Monday 14 February 2011] [09:37:13] <Guthur>	hopefully slow but steady progress will be made
| [Monday 14 February 2011] [09:39:10] <sustrik>	btw guys, there's a need for backup mentor for GSoC
| [Monday 14 February 2011] [09:39:27] <sustrik>	i can be the mentor as i know the code best
| [Monday 14 February 2011] [09:39:45] <sustrik>	but the rules of GSoC require to have a backup mentor as well
| [Monday 14 February 2011] [09:40:09] <sustrik>	in case i got run over by car or something
| [Monday 14 February 2011] [09:40:29] <sustrik>	any volunteers?
| [Monday 14 February 2011] [09:44:23] <Guthur>	probably need to send that on ml
| [Monday 14 February 2011] [09:44:52] <sustrik>	i've already did :)
| [Monday 14 February 2011] [09:45:01] <sustrik>	no answer though
| [Monday 14 February 2011] [09:51:20] <pieterh>	mikko: well, zfl links with zeromq, which links with libuuid
| [Monday 14 February 2011] [09:51:39] <mikko>	pieterh: but zfl doesn't need to link libuuid
| [Monday 14 February 2011] [09:51:44] <mikko>	?
| [Monday 14 February 2011] [09:52:05] <pieterh>	mikko: it's like I said... there are zfl classes that link zmq functions
| [Monday 14 February 2011] [09:52:18] <pieterh>	like zfl_msg and zfl_rpc
| [Monday 14 February 2011] [09:52:33] <sustrik>	zfl->libzmq->libuuid
| [Monday 14 February 2011] [09:52:47] <pieterh>	sustrik: that email had too many questions in it, I doubt many read the part about backup mentor
| [Monday 14 February 2011] [09:52:48] <mikko>	yeah, but zfl links against libuuid as well which i think is unnecessary dependency
| [Monday 14 February 2011] [09:53:16] <pieterh>	zfl_selftest will need it
| [Monday 14 February 2011] [09:53:29] <pieterh>	remove the dependency, see if it still works :-)
| [Monday 14 February 2011] [09:54:05] <pieterh>	sustrik: do you know any place to get kefir seeds in bratislava?
| [Monday 14 February 2011] [09:54:50] <mikko>	pieterh: i think it should be fine as libzmq doesnt expose any libuuid stuff directly
| [Monday 14 February 2011] [09:55:05] <sustrik>	hm, some bio-food store, i would say
| [Monday 14 February 2011] [09:55:06] <mikko>	so there should be no need for dependent programs/libraries to link with libuuid
| [Monday 14 February 2011] [09:55:10] <mikko>	will test
| [Monday 14 February 2011] [09:55:17] <sustrik>	never tried to buy it myself
| [Monday 14 February 2011] [09:55:42] <pieterh>	ah, katka will know... :-)
| [Monday 14 February 2011] [09:56:06] 	 * pieterh needs a reliable supply of evil slavic fermented milk products
| [Monday 14 February 2011] [09:56:22] <sustrik>	you can buy kefir in any shop here
| [Monday 14 February 2011] [09:56:28] <sustrik>	but it's pasteurized
| [Monday 14 February 2011] [09:56:51] <sustrik>	so the culture is dead i suppose
| [Monday 14 February 2011] [09:56:57] <pieterh>	made from pasteurized milk but not itself pasteurized
| [Monday 14 February 2011] [09:57:02] <pieterh>	otherwise there'd be no point
| [Monday 14 February 2011] [09:57:28] <pieterh>	i've cultured kefir here, you can buy imported Polish kefir in some places
| [Monday 14 February 2011] [09:57:44] <pieterh>	but it's kind of hard to find
| [Monday 14 February 2011] [09:58:32] <pieterh>	mikko: regarding uuid, IMO it's better to leave the check in there
| [Monday 14 February 2011] [09:58:49] <pieterh>	since otherwise people will just get an error when they try to link their apps, if they don't have libuuid
| [Monday 14 February 2011] [10:00:16] <sustrik>	i have bottle of kefir in the fridge, it says nothing about pasteurisation, so it's probably alive
| [Monday 14 February 2011] [10:01:40] <sustrik>	my girlfriend suggests that the culture may be sold in pharmacy
| [Monday 14 February 2011] [10:01:41] <sustrik>	no guarantee though
| [Monday 14 February 2011] [10:02:25] <pieterh>	hmm, there are some online stores, will check them out
| [Monday 14 February 2011] [10:03:22] <pieterh>	heh, there are even kefir grain sharing communities :-)
| [Monday 14 February 2011] [10:06:00] <mikko>	pieterh: what do you mean?
| [Monday 14 February 2011] [10:06:09] <mikko>	pieterh: people shouldnt need to link libuuid
| [Monday 14 February 2011] [10:07:22] <pieterh>	mikko: we seem to have a misunderstanding...
| [Monday 14 February 2011] [10:07:39] <pieterh>	if you link with libzfl, you're going to need the uuid functions
| [Monday 14 February 2011] [10:07:58] <mikko>	pieterh: libzfl doesn't seem to use them directly (from what i can see)
| [Monday 14 February 2011] [10:08:09] <mikko>	pieterh: only through libzmq 
| [Monday 14 February 2011] [10:08:15] <mikko>	or am i missing something (?)
| [Monday 14 February 2011] [10:10:28] <pieterh>	link is link
| [Monday 14 February 2011] [10:10:42] <pieterh>	there will be a dependency on uuid functions
| [Monday 14 February 2011] [10:10:48] <sustrik>	i think it's different for staci and dynamic libraries
| [Monday 14 February 2011] [10:11:18] <sustrik>	static*
| [Monday 14 February 2011] [10:11:23] <pieterh>	i don't think so
| [Monday 14 February 2011] [10:12:08] <sustrik>	if zfl links static version of libzmq, it has to link with libuuid
| [Monday 14 February 2011] [10:12:20] <pieterh>	if you do a static link, linker will search for uuid functions at link time
| [Monday 14 February 2011] [10:12:26] <mikko>	unless libzmq links static version of uuid
| [Monday 14 February 2011] [10:12:30] <mikko>	in which case they would collide
| [Monday 14 February 2011] [10:12:37] <pieterh>	mikko: libraries do not link...
| [Monday 14 February 2011] [10:13:05] <pieterh>	if you use dynamic libraries, executable will look for uuid functions at run time
| [Monday 14 February 2011] [10:13:12] <pieterh>	it's the same result
| [Monday 14 February 2011] [10:13:21] <pieterh>	if you use zfl you will eventually have to have uuid on your box
| [Monday 14 February 2011] [10:13:58] <pieterh>	libzmq *never* includes other libraries
| [Monday 14 February 2011] [10:14:13] <pieterh>	on no system, ever, afaik
| [Monday 14 February 2011] [10:14:50] <mikko>	libuuid is shared library dependency for libzmq
| [Monday 14 February 2011] [10:15:54] <pieterh>	if you remove the dependency check in configure.in, in zmq, libzmq will build fine
| [Monday 14 February 2011] [10:17:42] <pieterh>	and if you don't have libuuid installed, your apps will run until a peer tries to generate an identity
| [Monday 14 February 2011] [10:18:01] <pieterh>	alternatively if you're doing static links, your apps won't link at all
| [Monday 14 February 2011] [10:18:37] <pieterh>	this is precisely the same situation for a zfl app
| [Monday 14 February 2011] [10:18:46] <pieterh>	and therefore the check has exactly the same purpose and value
| [Monday 14 February 2011] [10:21:24] <mikko>	what happens in a situation where i have libzmq statically linked with libuuid and i try to use that with libzfl?
| [Monday 14 February 2011] [10:23:15] <mikko>	i guess thats more rare scenario
| [Monday 14 February 2011] [10:24:59] <sustrik>	i have no idea of how it is to be done
| [Monday 14 February 2011] [10:25:15] <sustrik>	however, i would suggest following the best practices
| [Monday 14 February 2011] [10:25:17] <mikko>	i guess it doesn't harm to have the explicit dependency there
| [Monday 14 February 2011] [10:25:28] <sustrik>	rather than trying to figure it out yourselves
| [Monday 14 February 2011] [10:25:30] <pieterh>	mikko: there is no such thing afaik as a "statically linked library"
| [Monday 14 February 2011] [10:26:03] <pieterh>	you create statically linked executables that pull in all referenced object files from various lbraries
| [Monday 14 February 2011] [10:27:09] <pieterh>	I don't know if any linkers allow a mix of static and dynamic
| [Monday 14 February 2011] [10:27:11] <mikko>	pieterh: on linux you seem to be able to include static libraries inside shared libraries
| [Monday 14 February 2011] [10:27:31] <mikko>	did some investigation a while ago regarding pgm builds
| [Monday 14 February 2011] [10:27:36] <mikko>	but it's non-portable case anyway
| [Monday 14 February 2011] [10:28:09] <pieterh>	weird and wonderful and in that specific case, if libzmq was changed to do that, we could drop the uuid check in zfl for those platforms
| [Monday 14 February 2011] [10:28:52] <mikko>	the only reason i know this is because i was looking into openpgm autotools builds and how to include the results of those in zeromq
| [Monday 14 February 2011] [10:29:20] <sustrik>	mikko: btw have you seen the email wrt. openvms builds?
| [Monday 14 February 2011] [10:29:26] <mikko>	but my original thinking was related to libzmq making a dependency to libuuid already it wouldnt be necessary in libzfl
| [Monday 14 February 2011] [10:29:49] <mikko>	but i guess it's ok to be explicit about it especially when its almost identical to zeromq build check
| [Monday 14 February 2011] [10:30:35] <mikko>	sustrik: yeah, haven't formulated a response yet
| [Monday 14 February 2011] [10:30:58] <sustrik>	actually, i think there's java on openvms
| [Monday 14 February 2011] [10:31:14] <sustrik>	but i have no idea whether hudson will run on it
| [Monday 14 February 2011] [10:31:31] <sustrik>	s/hudson/jenkins
| [Monday 14 February 2011] [10:32:02] <mikko>	we should be able to execute a script over ssh as well
| [Monday 14 February 2011] [10:32:24] <sustrik>	ack
| [Monday 14 February 2011] [10:36:44] <mikko>	sustrik: responded
| [Monday 14 February 2011] [10:36:49] <sustrik>	thx
| [Monday 14 February 2011] [13:05:53] <Guthur>	would a socket pool make much sense from a 0MQ perspective?
| [Monday 14 February 2011] [13:06:31] <Guthur>	I'm thinking of implementing in C# and was curious if it would translate down into the 0MQ lib
| [Monday 14 February 2011] [13:34:53] <pieterh>	Guthur, what problem does that solve?
| [Monday 14 February 2011] [13:36:00] <Guthur>	pieterh, so that sockets can be reused
| [Monday 14 February 2011] [13:36:19] <Guthur>	not sure if it will really benefit much
| [Monday 14 February 2011] [13:36:44] <Guthur>	in a managed environment it may have more benefit
| [Monday 14 February 2011] [13:37:00] <bitweiler>	can zeromq send any kind of data or does it have to be string data?
| [Monday 14 February 2011] [13:38:03] <Guthur>	bitweiler, the messages can contain any byte data
| [Monday 14 February 2011] [13:38:18] <bitweiler>	okay thanks :)
| [Monday 14 February 2011] [13:42:58] <Guthur>	pieterh, I had the situation where there is many differing threads coming in and I was thinking of having a pool of already connected sockets for them to use and reuse
| [Monday 14 February 2011] [13:43:21] <Guthur>	probably too specialized to be relevant to 0MQ
| [Monday 14 February 2011] [13:57:26] <Guthur>	it's partly inspired by WCF which is quite fast once it is 'warmed up', in part due to reusing the connection
| [Monday 14 February 2011] [13:57:58] <Guthur>	i need to bench of course
| [Monday 14 February 2011] [14:03:08] <pieterh>	Guthur, sorry, was away...
| [Monday 14 February 2011] [14:03:32] <pieterh>	Reusing connections could be a fun optimization but you may hit the issue of flushing messages on sockets
| [Monday 14 February 2011] [14:03:57] <pieterh>	I've seen apps that did a lot of socket opening and closing
| [Monday 14 February 2011] [14:04:02] <pieterh>	but they were IMO badly designed
| [Monday 14 February 2011] [14:04:52] <pieterh>	TCP startup costs are significant compared to message transfer
| [Monday 14 February 2011] [14:13:17] <Guthur>	it's a interesting minor wee exercise
| [Monday 14 February 2011] [14:19:50] <Guthur>	pieterh, are other socket types (in ZMQ) reasonable cheap to create
| [Monday 14 February 2011] [14:57:21] <pieterh>	Guthur, I'd expect them to be very cheap, yes... it's something to measure if you want figures
| [Monday 14 February 2011] [15:02:25] <cremes>	on linux do i need to do anything special to compile the lib to use epoll?
| [Monday 14 February 2011] [15:02:31] <cremes>	or does it pick that up automatically?
| [Monday 14 February 2011] [15:06:10] <Guthur>	cremes, will epoll is #ifdef ZMQ_HAVE_LINUX if that makes any difference
| [Monday 14 February 2011] [15:06:15] <Guthur>	will/well
| [Monday 14 February 2011] [15:07:46] <cremes>	Guthur: ah, i see that now
| [Monday 14 February 2011] [15:08:00] <cremes>	my config.log shows it set to 1 so i assume it picked it up correctly
| [Monday 14 February 2011] [15:17:57] <neale1>	vargaz: I just pushed my s390x unwind changes. It hits a couple of common files in mini so you may want to inspect
| [Monday 14 February 2011] [15:20:14] <neale1>	Sorry wrong window!
| [Monday 14 February 2011] [15:28:43] <cremes>	i am seeing something quite odd on linux (2.6.35-ARCH)
| [Monday 14 February 2011] [15:29:22] <cremes>	processes that should be idle are showing 80% cpu; it looks like it's all in zmq_poll 
| [Monday 14 February 2011] [15:29:29] <cremes>	which is set for a 10ms timeout
| [Monday 14 February 2011] [15:29:37] <cremes>	that shouldn't tax the machine at all
| [Monday 14 February 2011] [15:29:46] <cremes>	suggestions on debugging this?
| [Monday 14 February 2011] [15:34:11] <pieterh>	cremes: perhaps you're doing other heavy work in that loop
| [Monday 14 February 2011] [15:34:18] <pieterh>	profiler should help
| [Monday 14 February 2011] [15:34:26] <cremes>	pieterh: nope, i'm not doing *any* work
| [Monday 14 February 2011] [15:34:42] <cremes>	running the exact same code on OSX shows around 3-5% cpu
| [Monday 14 February 2011] [15:34:54] <cremes>	do you have a suggested profiler?
| [Monday 14 February 2011] [15:35:21] <pieterh>	gprof springs to mind
| [Monday 14 February 2011] [15:35:30] <pieterh>	it sounds like a bug in zmq
| [Monday 14 February 2011] [15:35:45] <cremes>	okay, i'll poke at it with gprof
| [Monday 14 February 2011] [15:36:47] <Guthur>	cremes, you have remembered poll takes micro seconds, not sure if that would effect CPU load, but it's something I keep forgetting
| [Monday 14 February 2011] [15:37:13] <cremes>	Guthur: yes, i pass 10000 as the value for a 10ms timeout
| [Monday 14 February 2011] [15:37:41] <cremes>	it looks like a platform bug; osx is okay with it (for once) and linux is not
| [Monday 14 February 2011] [15:43:30] <mikko>	pieterh: pull req sent
| [Monday 14 February 2011] [15:43:37] <mikko>	pieterh: does that look sensible?
| [Monday 14 February 2011] [15:47:40] <pieterh>	mikko: hang on a sec
| [Monday 14 February 2011] [15:49:51] <pieterh>	mikko: yeah, but you removed the check for uuid :-)
| [Monday 14 February 2011] [15:50:03] <mikko>	i did?
| [Monday 14 February 2011] [15:50:18] <pieterh>	looks like it
| [Monday 14 February 2011] [15:50:32] <pieterh>	actually I don't mind, people building zfl will normally have built zmq already
| [Monday 14 February 2011] [15:50:37] <mikko>	oh, didnt save file before reverting that
| [Monday 14 February 2011] [15:50:56] <mikko>	i also noticed one thing
| [Monday 14 February 2011] [15:51:06] <mikko>	majority of the tests in configure.in for zfl are done in C++
| [Monday 14 February 2011] [15:51:30] <pieterh>	lol, yes, inherited from zmq
| [Monday 14 February 2011] [15:51:34] <pieterh>	feel free to rip em out
| [Monday 14 February 2011] [15:54:14] <mikko>	are you planning to use these things in the build in future?
| [Monday 14 February 2011] [15:54:21] <mikko>	as there is much inherited from zmq build
| [Monday 14 February 2011] [15:54:35] <mikko>	like checks for atomic operations 
| [Monday 14 February 2011] [15:54:38] <pieterh>	to some extent this was meant to be a template for other libraries
| [Monday 14 February 2011] [15:54:50] <pieterh>	but I doubt that will happen
| [Monday 14 February 2011] [15:55:01] <mikko>	on zeromq side i tried to isolate these things into functions
| [Monday 14 February 2011] [15:55:04] <pieterh>	take an axe to it, you have a blank check
| [Monday 14 February 2011] [15:55:16] <mikko>	https://github.com/zeromq/zeromq2/blob/master/acinclude.m4
| [Monday 14 February 2011] [15:55:26] <mikko>	these should be fairly reusable if needed
| [Monday 14 February 2011] [15:56:02] <pieterh>	it's a shame it's not reusable as-is
| [Monday 14 February 2011] [15:56:18] <pieterh>	nice work
| [Monday 14 February 2011] [15:56:58] <pieterh>	mikko: are you volunteering to give the zfl tooling a clean-up?
| [Monday 14 February 2011] [15:57:04] <pieterh>	:-)
| [Monday 14 February 2011] [15:57:14] <pieterh>	for me, it works, which is kind of sufficient
| [Monday 14 February 2011] [15:57:22] <pieterh>	since what I really like doing is writing beautiful C code
| [Monday 14 February 2011] [15:57:55] <mikko>	pieterh: yes, i think the build can be simplified a lot
| [Monday 14 February 2011] [15:57:59] <pieterh>	mato yells from the back of the room, "keep trying old man, one day you'll get it right!"
| [Monday 14 February 2011] [15:58:00] <mikko>	i'll take a poke at it
| [Monday 14 February 2011] [15:58:03] <pieterh>	yay!
| [Monday 14 February 2011] [15:59:13] <pieterh>	i doubt we'll have more C/C++ libraries but it's always possible
| [Monday 14 February 2011] [16:03:37] <Guthur>	pieterh, It's ok there is probably only a handful of people how can write beautiful C code, and even less than that for C++ (probably none)
| [Monday 14 February 2011] [16:03:45] <Guthur>	how/who
| [Monday 14 February 2011] [16:08:03] <pieterh>	Guthur, I wasn't being modest :-)
| [Monday 14 February 2011] [17:28:47] <Luke234>	Hey I'm trying to build and install the ZMQ java bindings for windows but can't locate the java class files the docs mention
| [Monday 14 February 2011] [17:29:12] <Luke234>	http://www.zeromq.org/bindings:java
| [Monday 14 February 2011] [17:29:46] <Luke234>	"Secondly, make sure that you have set the Java classpath to the directory where MQ classes reside." anyone know where I can get those classes?
| [Monday 14 February 2011] [17:40:04] <mikko>	Luke234: iirc you build them with ant
| [Monday 14 February 2011] [18:18:09] <Guthur>	sustrik: will it be possible for 0MQ to pass in an extended OVERLAPPED struct to pipe ops for use with  IOCP, where the OVERLAPPED struct basically has the standard content plus what would usually be in poll_entry_t
| [Monday 14 February 2011] [18:19:21] <Guthur>	there is other possibilities though
| [Monday 14 February 2011] [18:20:29] <Guthur>	we could just pass a generic extend OVERLAPPED struct with the OP set, and use the completion key to get the poll_entry_t
| [Monday 14 February 2011] [18:20:36] <Guthur>	which might be neater
| [Tuesday 15 February 2011] [03:26:51] <sustrik>	Guthur: what's pipe ops?
| [Tuesday 15 February 2011] [03:33:50] <CIA-21>	zeromq2: 03Michael Compton 07master * rfbe5d85 10/ (AUTHORS doc/zmq_setsockopt.txt): 
| [Tuesday 15 February 2011] [03:33:50] <CIA-21>	zeromq2: Added note regarding setting sockopt before bind/connect
| [Tuesday 15 February 2011] [03:33:50] <CIA-21>	zeromq2: Signed-off-by: Michael Compton <michael.compton@littleedge.co.uk> - http://bit.ly/fNGMan
| [Tuesday 15 February 2011] [06:22:09] <cyball>	hi can i do something like this :: REQ -> XREP->XREQ->SUB with zmq_device::ZMQ_FORWARDER ? i want to publish a message to morre than one subscribers :) thx
| [Tuesday 15 February 2011] [06:23:37] <cyball>	or is it also possible to work with ... REQ->PUB->SUB ?
| [Tuesday 15 February 2011] [06:31:01] <mikko>	cyball: do you need req sock on client?
| [Tuesday 15 February 2011] [06:32:09] <mikko>	cyball: you could have PUB on client and use forwarder device 
| [Tuesday 15 February 2011] [06:32:36] <mikko>	client PUB <---> SUB forwarder PUB <---> SUB subscribers
| [Tuesday 15 February 2011] [06:34:35] <cyball>	mikko, i work on a continous integration service and i got a post-commit from github so i can not run the PUB whole the time only on request from github :)
| [Tuesday 15 February 2011] [06:35:38] <mikko>	cyball: you can have the pub connect to forwarder on post-commit ?
| [Tuesday 15 February 2011] [06:35:52] <mikko>	connect, publish, go away
| [Tuesday 15 February 2011] [06:36:22] <cyball>	mikko, ohh ok .. i thought that i have to run the publisher whole the time 
| [Tuesday 15 February 2011] [06:36:30] <cyball>	because of the subscriibers
| [Tuesday 15 February 2011] [06:36:53] <mikko>	the subscribers would be connected to forwarder device
| [Tuesday 15 February 2011] [06:36:57] <mikko>	whcih can run all the time
| [Tuesday 15 February 2011] [06:37:02] <cyball>	ok
| [Tuesday 15 February 2011] [06:37:45] <mikko>	look at the diagram:
| [Tuesday 15 February 2011] [06:37:46] <mikko>	client PUB <---> SUB forwarder PUB <---> SUB subscribers
| [Tuesday 15 February 2011] [06:37:48] <mikko>	:)
| [Tuesday 15 February 2011] [06:38:00] <cyball>	mikko, thx
| [Tuesday 15 February 2011] [06:38:02] <mikko>	forwarder would run all the time and subscribers would only know that they are connected to it
| [Tuesday 15 February 2011] [06:38:09] <cyball>	ok
| [Tuesday 15 February 2011] [06:38:15] <cyball>	i will have a look on it
| [Tuesday 15 February 2011] [06:38:57] <cyball>	do you have a link to it ?
| [Tuesday 15 February 2011] [06:39:03] <mikko>	link to where?
| [Tuesday 15 February 2011] [06:39:12] <cyball>	diagrag :)
| [Tuesday 15 February 2011] [06:39:18] <cyball>	diagram :)
| [Tuesday 15 February 2011] [06:39:19] <mikko>	it's that ascii one
| [Tuesday 15 February 2011] [06:39:38] <mikko>	let me see if zguide has similar with prettier graphics
| [Tuesday 15 February 2011] [06:39:56] <cyball>	no sorry i thought there is one in the manual i did not seen
| [Tuesday 15 February 2011] [06:41:29] <mikko>	it's a very simple scenario
| [Tuesday 15 February 2011] [06:41:44] <mikko>	the publisher client connects to insocket on forwarder and publishes message
| [Tuesday 15 February 2011] [06:41:53] <mikko>	forwarder then publishes it on outsocket
| [Tuesday 15 February 2011] [06:42:02] <mikko>	and subscribers are connected to outsocket
| [Tuesday 15 February 2011] [06:42:27] <mikko>	forwarder runs on the background and subscribers only know about it's existence
| [Tuesday 15 February 2011] [06:42:38] <mikko>	publishers on insocket can come and go as they please
| [Tuesday 15 February 2011] [06:42:46] <cyball>	mikko, is that ok ? http://pastebin.com/1USs18EG
| [Tuesday 15 February 2011] [06:45:08] <mikko>	cyball: subscribe to "" on frontend
| [Tuesday 15 February 2011] [06:46:23] <mikko>	so before the frontend bind
| [Tuesday 15 February 2011] [06:47:02] <mikko>	zmq_setsockopt(frontend, "", 0);
| [Tuesday 15 February 2011] [06:47:49] <mikko>	otherwise your frontend will filter all messages
| [Tuesday 15 February 2011] [07:03:13] <cyball>	mikko, http://pastebin.com/yfHkwBv1 is that ok for the publisher on the client ? 
| [Tuesday 15 February 2011] [07:04:19] <cyball>	or should i also add some socket options too ?
| [Tuesday 15 February 2011] [07:04:45] <mikko>	should be fine
| [Tuesday 15 February 2011] [07:19:05] <cyball>	mikko,  ok i have put all pieces together :: http://pastebin.com/EGUTh9mY i do not see anything on the subscriber i guess there is something i do not see can u have pls a look on it ?
| [Tuesday 15 February 2011] [07:36:04] <mikko>	cyball: subscribe the sub
| [Tuesday 15 February 2011] [07:36:17] <mikko>	subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);
| [Tuesday 15 February 2011] [07:36:27] <mikko>	otherwise it will filter all messages
| [Tuesday 15 February 2011] [07:36:37] <mikko>	i gotta commute to the office
| [Tuesday 15 February 2011] [07:36:43] <mikko>	back in 30 mins or so
| [Tuesday 15 February 2011] [07:37:45] <cyball>	thx
| [Tuesday 15 February 2011] [07:42:19] <cyball>	it does not work :-(
| [Tuesday 15 February 2011] [07:47:17] <cyball>	sure that i can have a SUB bind on a port and it does not only support connect ?
| [Tuesday 15 February 2011] [07:51:51] <sustrik>	yes, bind/connect are orthogonal to the socket type
| [Tuesday 15 February 2011] [07:55:45] <cyball>	sustrik, thx 
| [Tuesday 15 February 2011] [07:57:05] <cyball>	sustrik, can you please have a look on the code ... ? http://pastebin.com/EGUTh9mY
| [Tuesday 15 February 2011] [07:57:47] <cyball>	probably there is something missing ... i have adde the  subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);
| [Tuesday 15 February 2011] [07:57:51] <cyball>	but it also does not work
| [Tuesday 15 February 2011] [07:58:36] <sustrik>	what version of 0mq are you using?
| [Tuesday 15 February 2011] [07:58:42] <Liam`>	I can safely assess that I do not understand a word of this conversation.
| [Tuesday 15 February 2011] [07:59:22] <cyball>	2.0.10
| [Tuesday 15 February 2011] [08:00:06] <sustrik>	with 2.0.10 there's no blocking zmq_close()
| [Tuesday 15 February 2011] [08:00:19] <cyball>	ohhh upps
| [Tuesday 15 February 2011] [08:00:26] <sustrik>	thus, if there are any queued outbound messages
| [Tuesday 15 February 2011] [08:00:33] <sustrik>	they are dropped on zmq_close()
| [Tuesday 15 February 2011] [08:00:53] <cyball>	ok that means i should compile the beta ?
| [Tuesday 15 February 2011] [08:00:54] <sustrik>	if you need to block till the messages are send, you'll have to use 2.1.0
| [Tuesday 15 February 2011] [08:01:00] <sustrik>	yup
| [Tuesday 15 February 2011] [08:01:10] <cyball>	ok i will do it now :)
| [Tuesday 15 February 2011] [08:06:27] <cyball>	sustrik, yeahhh it works now THX  
| [Tuesday 15 February 2011] [08:06:35] <sustrik>	np
| [Tuesday 15 February 2011] [08:10:38] <marcinkuzminski>	Hi, I'm planning a system to do concurrent database insert, that suppose to be fail safe when insert fails, it would retry/remember, can that all be achieved using zeromq ?
| [Tuesday 15 February 2011] [08:11:56] <sustrik>	what do you mean by fail-safe?
| [Tuesday 15 February 2011] [08:12:22] <marcinkuzminski>	sustrik, That i cannot allow a task to be lost.
| [Tuesday 15 February 2011] [08:12:33] <marcinkuzminski>	i run ~200-300 tasks/s
| [Tuesday 15 February 2011] [08:13:20] <marcinkuzminski>	let say one out of million fails due to any reason network/db. And i need to retry that task with delay few times, if it fails permanently i need to store and remember that.
| [Tuesday 15 February 2011] [08:14:14] <sustrik>	then you have to store the task into a database
| [Tuesday 15 February 2011] [08:14:37] <sustrik>	distributed transactions should be used to pair the task generation with the insertion
| [Tuesday 15 February 2011] [08:14:47] <sustrik>	so that either both fail or both succeed
| [Tuesday 15 February 2011] [08:14:57] <sustrik>	it has very little to do with 0mq
| [Tuesday 15 February 2011] [08:15:53] <marcinkuzminski>	right,
| [Tuesday 15 February 2011] [08:16:09] <marcinkuzminski>	so it's just about distrubution of task that zeromq does ?
| [Tuesday 15 February 2011] [08:16:51] <marcinkuzminski>	sustrik, ok, getting back to reading 0mq manual
| [Tuesday 15 February 2011] [08:16:59] <sustrik>	right
| [Tuesday 15 February 2011] [08:19:10] <Guthur>	sustrik: did you catch my  messages last night
| [Tuesday 15 February 2011] [08:19:30] <Guthur>	you can ignore the first suggestion though
| [Tuesday 15 February 2011] [08:19:41] <Guthur>	I now think the second would be better
| [Tuesday 15 February 2011] [08:22:13] <sustrik>	Guthur: i missed it
| [Tuesday 15 February 2011] [08:22:26] <sustrik>	can you explain once more?
| [Tuesday 15 February 2011] [08:30:16] <Guthur>	basically would it be ok for 0MQ to pass in a custom OVERLAPPED struct with an operation type flag when performing various pipe operations. iocp_t (epoll etc equivalent) would then use this along with poll_entry, which would be set as the completion key, to call to determine which event handlers to call
| [Tuesday 15 February 2011] [08:30:59] <Guthur>	I also have a question regarding the retired functionality, but I'm not near the code at the moment and can not remember the details
| [Tuesday 15 February 2011] [08:31:42] <Guthur>	does that make any sense?
| [Tuesday 15 February 2011] [08:34:59] <sustrik>	Guthur: pass what from where to where?
| [Tuesday 15 February 2011] [08:35:04] <sustrik>	sorry, i don't follow
| [Tuesday 15 February 2011] [08:36:14] <sustrik>	afaics, the OVERLAPPED should be part of poll_entry
| [Tuesday 15 February 2011] [08:36:20] <sustrik>	actyually 2 of them
| [Tuesday 15 February 2011] [08:36:27] <sustrik>	one for write another one for read
| [Tuesday 15 February 2011] [08:37:36] <Guthur>	when doing ReadFile or WriteFile or ConnectToPipe there is an argument for the OVERLAPPED, this will be returned through the IOCP when the op completes 
| [Tuesday 15 February 2011] [08:38:20] <sustrik>	the event in the OVERLAPPED will be signaled when the op completes, right?
| [Tuesday 15 February 2011] [08:39:01] <Guthur>	you can ignore the event field, not using it
| [Tuesday 15 February 2011] [08:39:20] <sustrik>	hm
| [Tuesday 15 February 2011] [08:39:23] <Guthur>	but the OVERLAPPED can be extended, so that it contains custom fields
| [Tuesday 15 February 2011] [08:39:42] <sustrik>	how are you notified about operation being exectured then?
| [Tuesday 15 February 2011] [08:39:59] <sustrik>	executed*
| [Tuesday 15 February 2011] [08:40:13] <Guthur>	the only way is by setting a field in the custom OVERLAPPED struct
| [Tuesday 15 February 2011] [08:40:28] <sustrik>	i mean, is it a callback or what?
| [Tuesday 15 February 2011] [08:41:34] <Guthur>	IOCP will return an array of OVERLAPPED_ENTRIES, these will contain that the OVERLAPPED passed in when starting the OP
| [Tuesday 15 February 2011] [08:41:53] <sustrik>	which function is that?
| [Tuesday 15 February 2011] [08:42:08] <sustrik>	the one that returns the ENTRIES
| [Tuesday 15 February 2011] [08:42:13] <Guthur>	it will also return the Completion Key which you specify when you add the handle to the IOCP
| [Tuesday 15 February 2011] [08:42:26] <Guthur>	GetQueueCompletionStatus
| [Tuesday 15 February 2011] [08:42:54] <Guthur>	GetQueueCompletionStatusEx actually (for the timeout)
| [Tuesday 15 February 2011] [08:45:27] <Guthur>	I'm going to grab a coffee, back in a mo
| [Tuesday 15 February 2011] [08:46:23] <sustrik>	checking the docs
| [Tuesday 15 February 2011] [08:46:48] <sustrik>	how do you associate a particular read/write request with a specific completion port?
| [Tuesday 15 February 2011] [08:48:24] <zchrish>	I am testing zmq::poll with a single entry pollitem_t list. After I send a packet, I check whether items[0].revents & ZMQ_POLLIN is "1" and then process the input from REP. But, in my case, it always seems to be set to "1" even though I purposely put a 5 second delay in my XEQ program. Am I doing something wrong?
| [Tuesday 15 February 2011] [08:50:47] <sustrik>	zchrish: so you get POLLIN even though there is no message available, right?
| [Tuesday 15 February 2011] [08:51:21] <zchrish>	I think so.
| [Tuesday 15 February 2011] [08:51:38] <sustrik>	write a minimal test case then and report it as a bug
| [Tuesday 15 February 2011] [08:51:56] <sustrik>	POLLIN should be signaled only if there's a message available for reading
| [Tuesday 15 February 2011] [08:52:05] <zchrish>	ok; let me test a minimal case.
| [Tuesday 15 February 2011] [08:52:46] <mikko>	pieterh_: i've been ripping the guts out from zfl builds
| [Tuesday 15 February 2011] [08:53:03] <pieterh_>	mikko: nice, I think... :-)
| [Tuesday 15 February 2011] [08:53:16] <mikko>	there was quite a lot of things that weren't seem to be needed
| [Tuesday 15 February 2011] [08:53:39] <mikko>	like checks for C++ compiler, atomic ops, linking against socket libs etc
| [Tuesday 15 February 2011] [08:53:54] <mikko>	tested linux, mingw32 and mac os x this far
| [Tuesday 15 February 2011] [08:54:05] <mikko>	solaris and freebsd to go from platforms i have access to
| [Tuesday 15 February 2011] [08:54:10] <pieterh_>	sounds great
| [Tuesday 15 February 2011] [08:54:25] <mikko>	also, make check now runs zfl_selftest
| [Tuesday 15 February 2011] [08:54:49] <pieterh_>	is that the normal action, there's no "make test"?
| [Tuesday 15 February 2011] [08:55:00] <mikko>	make check seems to be default action
| [Tuesday 15 February 2011] [08:55:29] <pieterh_>	how about I give you commit access to the git?
| [Tuesday 15 February 2011] [08:55:37] <pieterh_>	that seems simpler than pull requests
| [Tuesday 15 February 2011] [08:55:55] <pieterh_>	are you committer on zmq?
| [Tuesday 15 February 2011] [08:56:02] <mikko>	no, im not
| [Tuesday 15 February 2011] [08:56:21] <pieterh_>	how would you like to work? I'm happy giving you commit access
| [Tuesday 15 February 2011] [08:56:39] <mikko>	well, let's see whether you agree my thinking here:
| [Tuesday 15 February 2011] [08:57:08] 	 * pieterh_ listens
| [Tuesday 15 February 2011] [08:57:37] <mikko>	my thinking was to rip out as much as possible to make things maintainable and then fix per platform if there are bugs on let's say very old qnx
| [Tuesday 15 February 2011] [08:57:47] <mikko>	example:
| [Tuesday 15 February 2011] [08:58:05] <mikko>	mac os x was set to build without -pedantic even though ZFL builds fine with -pedantic on mac os x
| [Tuesday 15 February 2011] [08:59:01] <pieterh_>	well, you are far more expert in this than me
| [Tuesday 15 February 2011] [08:59:03] <mikko>	sparc cpu optimization:
| [Tuesday 15 February 2011] [08:59:04] <mikko>	-mcpu=v9
| [Tuesday 15 February 2011] [08:59:07] <mikko>	is that really needed?
| [Tuesday 15 February 2011] [08:59:30] <pieterh_>	:-)
| [Tuesday 15 February 2011] [08:59:43] <pieterh_>	I hope you're not asking me
| [Tuesday 15 February 2011] [08:59:47] <mikko>	i am
| [Tuesday 15 February 2011] [08:59:50] <mikko>	it's in the build :)
| [Tuesday 15 February 2011] [09:00:03] <pieterh_>	well, mikko, my process is kind of different
| [Tuesday 15 February 2011] [09:00:18] <pieterh_>	copy some code, hack it till it works, forget about it again asap, wait for patches
| [Tuesday 15 February 2011] [09:00:27] <mikko>	i can agree with that
| [Tuesday 15 February 2011] [09:00:35] <pieterh_>	specifically, for the tooling, which I don't want to be expert in
| [Tuesday 15 February 2011] [09:01:29] <pieterh_>	so most of what is there I copied, and left unchanged because it didn't break things
| [Tuesday 15 February 2011] [09:02:04] <pieterh_>	clearly someone who knows their stuff, like you, would rip most of it out
| [Tuesday 15 February 2011] [09:02:10] <pieterh_>	which is perfect
| [Tuesday 15 February 2011] [09:03:07] <pieterh_>	what's your github id?
| [Tuesday 15 February 2011] [09:03:50] <pieterh_>	plain mikko?
| [Tuesday 15 February 2011] [09:03:51] <mikko>	mkoppanen
| [Tuesday 15 February 2011] [09:04:03] <Guthur>	sustrik: the completion key will take care of that
| [Tuesday 15 February 2011] [09:04:17] <pieterh_>	ok, mikko, you are now committer on zfl
| [Tuesday 15 February 2011] [09:04:20] <Guthur>	it is returned as part of the OVERLAPPED_ENTRY struct
| [Tuesday 15 February 2011] [09:04:33] <mikko>	cool
| [Tuesday 15 February 2011] [09:04:47] <mikko>	i'll hopefully finish this during this week
| [Tuesday 15 February 2011] [09:04:52] <Guthur>	sustrik: oh wait I miss read
| [Tuesday 15 February 2011] [09:04:57] <pieterh_>	:-) I'm enormously grateful...
| [Tuesday 15 February 2011] [09:05:01] <mikko>	got company evening today so might be a bit out of game tomorrow
| [Tuesday 15 February 2011] [09:05:05] <Guthur>	I think if you had multiple IOCP it would be returned to all
| [Tuesday 15 February 2011] [09:05:20] <pieterh_>	suddenly zfl actually builds properly across more than Ubuntu :-)
| [Tuesday 15 February 2011] [09:05:29] <Guthur>	That's a guess though
| [Tuesday 15 February 2011] [09:05:50] <sustrik>	what would that be good for?
| [Tuesday 15 February 2011] [09:05:52] <sustrik>	strange
| [Tuesday 15 February 2011] [09:06:19] <Guthur>	sustrik: that comment for me?
| [Tuesday 15 February 2011] [09:06:26] <sustrik>	yep
| [Tuesday 15 February 2011] [09:06:40] <sustrik>	if every event is passed to all completion ports
| [Tuesday 15 February 2011] [09:06:44] <Guthur>	I have to admit I never really considered multiple IOCP
| [Tuesday 15 February 2011] [09:06:51] <sustrik>	what's the point of having many of them
| [Tuesday 15 February 2011] [09:07:02] <Guthur>	you associate the pipe handle with the IOCP 
| [Tuesday 15 February 2011] [09:07:10] <sustrik>	ah
| [Tuesday 15 February 2011] [09:07:14] <sustrik>	how do you do that?
| [Tuesday 15 February 2011] [09:07:17] <Guthur>	you can associate multiple pipes with the IOCP
| [Tuesday 15 February 2011] [09:07:30] <zchrish>	so I added code to C++ example from "the guide" to hwclient.cpp and hwserver.cpp to include a single pollitem_t entry. I included a 5 second delay in the hwserver.cpp. It appears the code always enters regardless.
| [Tuesday 15 February 2011] [09:07:43] <Guthur>	CreateIoCompletionPort
| [Tuesday 15 February 2011] [09:07:47] <Guthur>	sustrik: ^^
| [Tuesday 15 February 2011] [09:08:07] <Guthur>	http://msdn.microsoft.com/en-us/library/aa363862(v=VS.85).aspx
| [Tuesday 15 February 2011] [09:08:28] <pieterh_>	zchrish: could you post the code in a pastebin somewhere?
| [Tuesday 15 February 2011] [09:08:45] <zchrish>	Sure, that's next.
| [Tuesday 15 February 2011] [09:08:52] <sustrik>	Guthur: ok, i see
| [Tuesday 15 February 2011] [09:09:11] <Guthur>	sustrik: so, can we make it fit?
| [Tuesday 15 February 2011] [09:09:14] <sustrik>	i think i have a vague idea of how it works now :)
| [Tuesday 15 February 2011] [09:09:25] <mikko>	isnt ZMQ_SUBSCRIBE an exception to setsockopts before connect/bind?
| [Tuesday 15 February 2011] [09:09:37] <sustrik>	Guthur: there are few things to keep in mind
| [Tuesday 15 February 2011] [09:09:40] <sustrik>	mikko: no
| [Tuesday 15 February 2011] [09:09:56] <pieterh_>	sustrik: really?
| [Tuesday 15 February 2011] [09:10:04] <mikko>	then i found an error on zguide :)
| [Tuesday 15 February 2011] [09:10:18] <sustrik>	yes, ZMQ_SUBSCRIBE applies to the socket as a whole
| [Tuesday 15 February 2011] [09:10:22] <pieterh_>	you can't add/remove a filter after binding?
| [Tuesday 15 February 2011] [09:10:36] <Guthur>	i think you can
| [Tuesday 15 February 2011] [09:10:37] <sustrik>	as opposed to other sockopts that apply only to subsequent connects/binds
| [Tuesday 15 February 2011] [09:10:46] <sustrik>	pieterh_: yes
| [Tuesday 15 February 2011] [09:10:57] <pieterh_>	sorry, the 'no' part confused us, I think
| [Tuesday 15 February 2011] [09:11:28] <sustrik>	Guthur: namely, that the messages should be kept in 0mq as long as possible
| [Tuesday 15 February 2011] [09:11:56] <sustrik>	thus instead of starting asynch writes immediately for any data to send
| [Tuesday 15 February 2011] [09:12:10] <sustrik>	you should start async send
| [Tuesday 15 February 2011] [09:12:15] <sustrik>	wait while it compeltes
| [Tuesday 15 February 2011] [09:12:25] <sustrik>	then start next send
| [Tuesday 15 February 2011] [09:12:26] <sustrik>	etc.
| [Tuesday 15 February 2011] [09:12:48] <sustrik>	the rationale is that if you pushed all the data to the kernel immediately
| [Tuesday 15 February 2011] [09:13:03] <Guthur>	sustrik: and does 0MQ use the poll to do that subsequent send?
| [Tuesday 15 February 2011] [09:13:04] <sustrik>	0mq flow control (such as HWM) won't work
| [Tuesday 15 February 2011] [09:13:36] <sustrik>	Guthur: all existing polling mechanisms are using sync sends
| [Tuesday 15 February 2011] [09:13:43] <sustrik>	i.e. they poll for pollout
| [Tuesday 15 February 2011] [09:14:05] <sustrik>	pollout is signaled if there's a space free in the kernel buffer
| [Tuesday 15 February 2011] [09:14:24] <sustrik>	then it sends the data
| [Tuesday 15 February 2011] [09:14:43] <Guthur>	which should be the same as an IOCP completion status signaled for a write op, correct?
| [Tuesday 15 February 2011] [09:14:57] <sustrik>	yes
| [Tuesday 15 February 2011] [09:15:04] <sustrik>	it should be same
| [Tuesday 15 February 2011] [09:15:16] <sustrik>	except that IOCP itself is different from poll
| [Tuesday 15 February 2011] [09:15:23] <sustrik>	so it'll be a bit complex
| [Tuesday 15 February 2011] [09:15:30] <sustrik>	but the semantics should be the same, yes
| [Tuesday 15 February 2011] [09:15:52] <Guthur>	yep, we need to send some op identifying data  in the OVERLAPPED, 
| [Tuesday 15 February 2011] [09:16:27] <zchrish>	OK; here is the snipper - https://gist.github.com/827576
| [Tuesday 15 February 2011] [09:16:35] <Guthur>	it's the only way we will know what the completion status is being returned for
| [Tuesday 15 February 2011] [09:16:35] <sustrik>	even better: we can have a single IOCP per poller
| [Tuesday 15 February 2011] [09:17:00] <Guthur>	but IOCP will return for all ops
| [Tuesday 15 February 2011] [09:17:18] <sustrik>	yes, but we can place custom data to the result, right?
| [Tuesday 15 February 2011] [09:17:35] <Guthur>	via a custom OVERLAPPED sure
| [Tuesday 15 February 2011] [09:17:52] <pieterh>	zchrish: what does the client program print?
| [Tuesday 15 February 2011] [09:18:11] <sustrik>	then we can identify the socket there as well as operation being performed
| [Tuesday 15 February 2011] [09:18:19] <sustrik>	something like:
| [Tuesday 15 February 2011] [09:18:21] <sustrik>	{
| [Tuesday 15 February 2011] [09:18:28] <sustrik>	    HANDLE socket;
| [Tuesday 15 February 2011] [09:18:36] <sustrik>	    bool read_or_write;
| [Tuesday 15 February 2011] [09:18:36] <sustrik>	}
| [Tuesday 15 February 2011] [09:18:37] <zchrish>	Just the normal case : Received reply 0: [World]
| [Tuesday 15 February 2011] [09:18:50] <Guthur>	struct exactly that
| [Tuesday 15 February 2011] [09:19:00] <Guthur>	well roughly actually
| [Tuesday 15 February 2011] [09:19:16] <Guthur>	you don't need the Handle though, we can set the completion key to that
| [Tuesday 15 February 2011] [09:19:32] <Guthur>	it will be returned for all completion status' for that socket
| [Tuesday 15 February 2011] [09:19:36] <zchrish>	Never goes to "WAITING..."
| [Tuesday 15 February 2011] [09:19:39] <pieterh>	zchrish: you are doing an infinite timeout in zmq::poll, what else would you expect to see?
| [Tuesday 15 February 2011] [09:19:56] <sustrik>	Guthur: ok
| [Tuesday 15 February 2011] [09:20:02] <zchrish>	Sorry, yes. 
| [Tuesday 15 February 2011] [09:20:41] <pieterh>	zchrish: note that timeout is in usec (so use 1000000 for 1 second)
| [Tuesday 15 February 2011] [09:21:39] <Guthur>	sustrik: a bool wont cut it though, I actually intended to use an enum. There is at least 3 ops that take an overlapped ConnectNamedPipe, Read, write
| [Tuesday 15 February 2011] [09:22:51] <Guthur>	so the connect will also be returning to the IOCP
| [Tuesday 15 February 2011] [09:25:15] <zchrish>	So if I want to wrap my code like this, it seems like I should enter "0" and then perform the sleep myself. Is that permissible? Seems so.
| [Tuesday 15 February 2011] [09:27:13] <pieterh>	zchrish: did you get it working as expected?
| [Tuesday 15 February 2011] [09:27:42] <pieterh>	e.g. using a zmq_poll timeout of 1 second...
| [Tuesday 15 February 2011] [09:28:45] <pieterh>	doing the sleep outside zmq_poll is a bad design
| [Tuesday 15 February 2011] [09:29:01] <pieterh>	imagine your server replies after 1000 usec
| [Tuesday 15 February 2011] [09:29:23] <pieterh>	you client won't get the response until after 1 full second
| [Tuesday 15 February 2011] [09:30:08] <zchrish>	yes, it works. Thank you. I used "0". I agree with your assessment.
| [Tuesday 15 February 2011] [09:33:05] <sustrik>	Guthur: right
| [Tuesday 15 February 2011] [09:36:55] <Guthur>	cool, I think we are making progress with this. I have some rough code at home, hopefully we can go over it sometime soon
| [Tuesday 15 February 2011] [09:44:03] <zchrish>	pieterh: So I am playing around with different ways to detect errors in network traffic flow and the one that I seem to feel most comfortable with is the concept of a watchdog thread that monitors socket states. I put my 0mq socket into a thread and that thread doesn't reset the state, an alarm goes off. This is the best method I have learned thus far. If there are better ways that you are willing to share, please do so. Thank 
| [Tuesday 15 February 2011] [09:44:03] <zchrish>	you.
| [Tuesday 15 February 2011] [09:44:38] <pieterh>	zchrish: you cannot share a socket between threads, remember
| [Tuesday 15 February 2011] [09:45:05] <pieterh>	in general you need specific algorithms for different kinds of failure
| [Tuesday 15 February 2011] [09:45:31] <zchrish>	pieterh: No, I have a variable that represents the thread state and the thread is responsible for updating that state on a timely basis.
| [Tuesday 15 February 2011] [09:45:44] <mikko>	zchrish: what does that actually monitor?
| [Tuesday 15 February 2011] [09:45:45] <pieterh>	you cannot share state between threads either
| [Tuesday 15 February 2011] [09:45:51] <mikko>	that the thread is not stuck blocking?
| [Tuesday 15 February 2011] [09:47:49] <zchrish>	Well the idea is to try to verify that the routine is cycling through its while (true) state which I have defined to do so every "x" cycles of time. I want to ensure this is the case.
| [Tuesday 15 February 2011] [09:49:00] <zchrish>	pieterh: I am referring to "state" in a non-zeromq sense. 
| [Tuesday 15 February 2011] [09:49:14] <pieterh>	zchrish: you are IMO misusing threads quite fundamentally
| [Tuesday 15 February 2011] [09:49:42] <pieterh>	each thread should be entirely isolated in terms of state, meaning memory
| [Tuesday 15 February 2011] [09:49:50] <pieterh>	threads should communicate only by sending each other messages
| [Tuesday 15 February 2011] [09:50:18] <pieterh>	threads should process a set of sockets that they own fully
| [Tuesday 15 February 2011] [09:51:05] <pieterh>	the only object in ZMQ that's safe to share between threads is the context
| [Tuesday 15 February 2011] [09:51:26] <zchrish>	Thank you for your feedback; I will think...
| [Tuesday 15 February 2011] [09:53:31] <stimpie>	zchrish, you could have all your treads send a 'variable' to your watchdog thread using messages
| [Tuesday 15 February 2011] [10:44:27] <sustrik>	Guthur: still there?
| [Tuesday 15 February 2011] [10:44:40] <Guthur>	sure
| [Tuesday 15 February 2011] [10:44:56] <sustrik>	there's one problem with IOCP i haven't realised
| [Tuesday 15 February 2011] [10:45:11] <sustrik>	namely: how to implement zmq_poll()
| [Tuesday 15 February 2011] [10:45:12] <sustrik>	?
| [Tuesday 15 February 2011] [10:45:35] <sustrik>	given that fd_t will be HANDLE instead of SOCKET
| [Tuesday 15 February 2011] [10:45:51] <sustrik>	we can't use select() to simulate the polling
| [Tuesday 15 February 2011] [10:45:55] <Guthur>	yeah, that's something I meant to be asking you
| [Tuesday 15 February 2011] [10:46:41] 	 * sustrik is checking MSDN
| [Tuesday 15 February 2011] [10:48:18] <Guthur>	sustrik: though you can use SOCKETS with IOCP, but I assume that's not the issue
| [Tuesday 15 February 2011] [10:48:57] <sustrik>	the problem is that IPC descriptor *has* to be HANDLE
| [Tuesday 15 February 2011] [10:49:27] <sustrik>	hm, well
| [Tuesday 15 February 2011] [10:49:51] <sustrik>	the I/O thread has to poll on both TCP and IPC sockets
| [Tuesday 15 February 2011] [10:50:15] <sustrik>	zmq_poll has to poll only on the descriptors provided by mailbox_t
| [Tuesday 15 February 2011] [10:50:33] <sustrik>	currently SOCKET but presumably a HANDLE in the future
| [Tuesday 15 February 2011] [10:51:21] <sustrik>	could be doable...
| [Tuesday 15 February 2011] [10:51:54] 	 * sustrik still doesn't believe WinAPI has no equivalen of a simple poll() function
| [Tuesday 15 February 2011] [10:51:56] <Guthur>	yeah, a socket handle can be a file handle so it would make sense to get them all the same
| [Tuesday 15 February 2011] [10:52:32] <Guthur>	I think IOCP seems quite neat actually
| [Tuesday 15 February 2011] [10:52:45] <Guthur>	at bit murky at the beginning 
| [Tuesday 15 February 2011] [10:53:12] <Guthur>	one thing though...
| [Tuesday 15 February 2011] [10:53:27] <Guthur>	I don't think one can remove a handle from an IOCP
| [Tuesday 15 February 2011] [10:53:35] <sustrik>	the problem with IOCP is that it doesn't provide a sane pushback mechanism
| [Tuesday 15 February 2011] [10:53:36] <Guthur>	which begs believe
| [Tuesday 15 February 2011] [10:54:27] <Guthur>	sustrik: you mean the fact we have to use the overlapped struct to identify etc?
| [Tuesday 15 February 2011] [10:54:58] <sustrik>	i mean the fact that you can push any amount of data to the socket
| [Tuesday 15 February 2011] [10:55:07] <sustrik>	without being notified that the TCP buffer is full
| [Tuesday 15 February 2011] [10:57:00] <sustrik>	there seems to be no equivalent to HWM when using IOCP
| [Tuesday 15 February 2011] [10:57:21] <Guthur>	sustrik: there is data in the overlapped regarding the amount of data sent
| [Tuesday 15 February 2011] [10:57:40] <Guthur>	you would probably also have to pass you HWM it make the comparison
| [Tuesday 15 February 2011] [10:58:03] <Guthur>	that is off the top of my head, so there may be other nicer ways
| [Tuesday 15 February 2011] [10:58:36] <sustrik>	i don't follow
| [Tuesday 15 February 2011] [10:58:46] <sustrik>	what data in OVERLAPPED
| [Tuesday 15 February 2011] [10:58:48] <sustrik>	?
| [Tuesday 15 February 2011] [10:58:51] <Guthur>	http://msdn.microsoft.com/en-us/library/ms684342(v=vs.85).aspx 
| [Tuesday 15 February 2011] [10:58:55] <Guthur>	internalhigh
| [Tuesday 15 February 2011] [10:59:22] <sustrik>	"The InternalHigh member was originally reserved for system use and its behavior may change. "
| [Tuesday 15 February 2011] [10:59:23] <Guthur>	internal might have an error code for full buffer
| [Tuesday 15 February 2011] [10:59:35] <sustrik>	it's some internal IOCP stuff
| [Tuesday 15 February 2011] [10:59:40] <sustrik>	better not touch it
| [Tuesday 15 February 2011] [10:59:53] <Guthur>	no i meant the part that says: The number of bytes transferred for the I/O request. The system sets this member if the request is completed without errors.
| [Tuesday 15 February 2011] [11:00:24] <Guthur>	we can add are own stuff to the custom overlapped struct so that's not an issue
| [Tuesday 15 February 2011] [11:01:29] <Guthur>	a custom overlapped could look like follows...
| [Tuesday 15 February 2011] [11:01:31] <Guthur>	{                 OVERLAPPED olp;                 OP_TYPE op;                 int HWM;             }
| [Tuesday 15 February 2011] [11:01:34] <Guthur>	damn
| [Tuesday 15 February 2011] [11:01:38] <Guthur>	{
| [Tuesday 15 February 2011] [11:01:50] <Guthur>	     OVERLAPPED olp;
| [Tuesday 15 February 2011] [11:01:57] <Guthur>	    OP_TYPE op;
| [Tuesday 15 February 2011] [11:02:04] <Guthur>	    int HWM;
| [Tuesday 15 February 2011] [11:02:06] <Guthur>	}
| [Tuesday 15 February 2011] [11:02:18] <Guthur>	sorry for the spam
| [Tuesday 15 February 2011] [11:02:55] <Guthur>	that's just a very crude example
| [Tuesday 15 February 2011] [11:03:07] <sustrik>	hm, how would you limit the amount of pending outbound data?
| [Tuesday 15 February 2011] [11:15:27] <Guthur>	hmm, yeah that HWM probably wouldn't help, it was more to explicitly show the custom Overlapped
| [Tuesday 15 February 2011] [11:16:09] <Guthur>	but I think in terms of what is in epoll etc, we can get that easy enough with IOCP
| [Tuesday 15 February 2011] [11:16:15] <Guthur>	agree?
| [Tuesday 15 February 2011] [11:16:34] <Guthur>	I haven't looked much outside that
| [Tuesday 15 February 2011] [11:17:22] <sustrik>	Guthur: in terms of functionality you can get the same with IOCP
| [Tuesday 15 February 2011] [11:17:28] <sustrik>	although it requires a bit more work
| [Tuesday 15 February 2011] [11:18:00] <sustrik>	in terms of performance, there can be problems with IOCP
| [Tuesday 15 February 2011] [11:23:13] <Guthur>	i though IOCP was pretty performant
| [Tuesday 15 February 2011] [11:23:16] <Guthur>	thought*
| [Tuesday 15 February 2011] [11:24:16] <sustrik>	the problem i see is with under-filled outbound TCP buffer
| [Tuesday 15 February 2011] [11:24:38] <sustrik>	to honour the HWM on the send side
| [Tuesday 15 February 2011] [11:25:07] <Guthur>	how to the other method facilitate that?
| [Tuesday 15 February 2011] [11:25:20] <Guthur>	to/do
| [Tuesday 15 February 2011] [11:25:56] <sustrik>	hm, in theory we can count the number of bytes we've already sent to the socket and haven't seen acknowledgements for
| [Tuesday 15 February 2011] [11:26:13] <sustrik>	yuck
| [Tuesday 15 February 2011] [11:26:37] <Guthur>	ah yes I see, pretty yucky
| [Tuesday 15 February 2011] [11:26:50] <Guthur>	so you get this for free the other ways?
| [Tuesday 15 February 2011] [11:27:04] <sustrik>	yes, using select/poll/epoll etc.
| [Tuesday 15 February 2011] [11:27:12] <sustrik>	any sane OS has a mechanism like this
| [Tuesday 15 February 2011] [11:27:17] <sustrik>	Win32 has select
| [Tuesday 15 February 2011] [11:27:31] <sustrik>	but undfortunately, it can be used just for SOCKETs
| [Tuesday 15 February 2011] [11:27:36] <sustrik>	(i.e. not named pipes)
| [Tuesday 15 February 2011] [11:28:50] <sustrik>	There's WSAPoll btw
| [Tuesday 15 February 2011] [11:28:52] <sustrik>	but:
| [Tuesday 15 February 2011] [11:28:55] <sustrik>	"The WSAPoll function is defined on Windows Vista and later."
| [Tuesday 15 February 2011] [11:29:41] <sustrik>	so the alternative to IOCP would be to use WSAPoll on Vista and Win7
| [Tuesday 15 February 2011] [11:29:49] <Guthur>	umm, XP is a large chuck of windows to not support
| [Tuesday 15 February 2011] [11:29:56] <sustrik>	and fall back to select() on XP or somesuch
| [Tuesday 15 February 2011] [11:30:05] <sustrik>	shrug
| [Tuesday 15 February 2011] [11:30:07] <Guthur>	also may rule out a lot of windows server
| [Tuesday 15 February 2011] [11:30:28] <Guthur>	not sure on win server kernel families though
| [Tuesday 15 February 2011] [11:31:44] <sustrik>	Minimum supported server
| [Tuesday 15 February 2011] [11:31:44] <sustrik>		Windows Server 2008
| [Tuesday 15 February 2011] [11:32:03] <Guthur>	umm that's quite modern
| [Tuesday 15 February 2011] [11:32:06] <sustrik>	damn, it works for SOCKETs only
| [Tuesday 15 February 2011] [11:32:14] <Guthur>	hehe
| [Tuesday 15 February 2011] [11:32:17] <Guthur>	red herring then
| [Tuesday 15 February 2011] [11:40:19] <sustrik>	however, WSAPoll seems to have no limit on number of sockets it can poll on
| [Tuesday 15 February 2011] [11:40:30] <sustrik>	select is by default limited to 64
| [Tuesday 15 February 2011] [11:41:20] <sustrik>	so maybe, as a warm up, you could try to modify poll.hpp/poll.cpp to use WSAPoll on windows instead of poll
| [Tuesday 15 February 2011] [11:41:47] <sustrik>	you would need vista/win7 for that, obviously
| [Tuesday 15 February 2011] [11:43:01] <sustrik>	WSAPoll looks like pretty close copy of POSIX poll, so it should take some 1 hour to do that...
| [Tuesday 15 February 2011] [11:46:24] <Guthur>	sustrik: and keep the old version as a fall back?
| [Tuesday 15 February 2011] [11:46:41] <sustrik>	poll.cpp doesn't compile on windows
| [Tuesday 15 February 2011] [11:46:48] <sustrik>	there's no poll() function there
| [Tuesday 15 February 2011] [11:46:58] <sustrik>	so you won't break anything
| [Tuesday 15 February 2011] [11:47:06] <Guthur>	oh, it uses select instead though, right?
| [Tuesday 15 February 2011] [11:47:10] <sustrik>	right
| [Tuesday 15 February 2011] [11:47:51] <sustrik>	you could force 0MQ to compile with poll
| [Tuesday 15 February 2011] [11:48:00] <sustrik>	by defining ZMQ_FORCE_POLL macro
| [Tuesday 15 February 2011] [11:48:13] <sustrik>	that would make it use poll.cpp instead of select.cpp
| [Tuesday 15 February 2011] [11:48:21] <sustrik>	obviously, the build will fail now
| [Tuesday 15 February 2011] [11:48:39] <sustrik>	but it can be presumably fixed by doing something like this:
| [Tuesday 15 February 2011] [11:48:46] <sustrik>	#ifdef ZMQ_HAVE_WINDOWS
| [Tuesday 15 February 2011] [11:48:55] <sustrik>	    WSAPoll (...);
| [Tuesday 15 February 2011] [11:48:58] <sustrik>	#else
| [Tuesday 15 February 2011] [11:49:04] <sustrik>	    poll (...);
| [Tuesday 15 February 2011] [11:49:06] <sustrik>	#endif
| [Tuesday 15 February 2011] [11:50:41] <Guthur>	ok, seems a reasonable well contained updated
| [Tuesday 15 February 2011] [11:50:46] <Guthur>	update*
| [Tuesday 15 February 2011] [11:51:33] <Guthur>	so would there be performance gains for ZMQ, how does the 64 socket limit effect ZMQ at the moment?
| [Tuesday 15 February 2011] [11:53:02] <sustrik>	in MSVC build the limit is rasied to 1024
| [Tuesday 15 February 2011] [11:53:16] <sustrik>	still, if 0mq hits the limit it fails
| [Tuesday 15 February 2011] [11:54:12] <sustrik>	also, poll() should be more efficient with large pollsets than select
| [Tuesday 15 February 2011] [11:56:58] <sustrik>	Guthur: wait a sec, the current implementation of poll presumes that fd is an int
| [Tuesday 15 February 2011] [11:57:09] <Guthur>	sustrik: can you point me to the portion of polls which IOCP does supply
| [Tuesday 15 February 2011] [11:57:11] <sustrik>	which is not true on windows
| [Tuesday 15 February 2011] [11:57:29] <Guthur>	sorry I'm a little inexperienced with polls and sockets in general
| [Tuesday 15 February 2011] [11:57:40] <sustrik>	so rewriting the poll wouldn't be that easy
| [Tuesday 15 February 2011] [11:57:46] <sustrik>	anyway, what's your question?
| [Tuesday 15 February 2011] [11:58:04] <sustrik>	polling means that you can wait for multiple sockets at once
| [Tuesday 15 February 2011] [11:58:32] <sustrik>	you wait either for socket becoming readable or socket becoming writeavle (or both)
| [Tuesday 15 February 2011] [11:58:56] <sustrik>	POSIX defines 2 ways of polling : select and poll
| [Tuesday 15 February 2011] [11:59:14] <sustrik>	different unix flavours provide additional polling mechanisms:
| [Tuesday 15 February 2011] [11:59:21] <sustrik>	epoll, /dev/poll, kqueue
| [Tuesday 15 February 2011] [11:59:43] <sustrik>	winapi is, unfortunately, highly inconsistent
| [Tuesday 15 February 2011] [11:59:45] <Guthur>	and there is something more than the events?
| [Tuesday 15 February 2011] [12:00:15] <sustrik>	?
| [Tuesday 15 February 2011] [12:00:31] <sustrik>	poll() simply exists
| [Tuesday 15 February 2011] [12:00:37] <sustrik>	when one of the sockets is readable/writeable
| [Tuesday 15 February 2011] [12:00:49] <sustrik>	it works in the same way as zmq_poll() does
| [Tuesday 15 February 2011] [12:01:25] <sustrik>	exits*
| [Tuesday 15 February 2011] [12:01:36] <Guthur>	ok, so the problem is that IOCP only notifies when an operation has completed?
| [Tuesday 15 February 2011] [12:01:42] <sustrik>	exactly
| [Tuesday 15 February 2011] [12:01:46] <sustrik>	it's so called AIO
| [Tuesday 15 February 2011] [12:01:51] <sustrik>	(async I/O)
| [Tuesday 15 February 2011] [12:02:02] <sustrik>	which is supposed to be better than standard I/O
| [Tuesday 15 February 2011] [12:02:11] <sustrik>	howver, it's not used much
| [Tuesday 15 February 2011] [12:02:25] <private_meta>	Heya... Small question. Is there a way the server knows when a client disconnects?
| [Tuesday 15 February 2011] [12:02:27] <sustrik>	linux, for example, never implemented AIO for sockets
| [Tuesday 15 February 2011] [12:02:37] <sustrik>	private_meta: no
| [Tuesday 15 February 2011] [12:03:19] <private_meta>	so I'd have to implement some heartbeat and check if it's going through?
| [Tuesday 15 February 2011] [12:04:13] <sustrik>	it's up to you
| [Tuesday 15 February 2011] [12:04:22] <private_meta>	Would there be better options?
| [Tuesday 15 February 2011] [12:04:29] <sustrik>	i personally prefer timing out the request and resending afterwards
| [Tuesday 15 February 2011] [12:05:25] <private_meta>	Well, I would have needed to know when a connection terminates unexpectedly :/
| [Tuesday 15 February 2011] [12:05:46] <sustrik>	what does that mean?
| [Tuesday 15 February 2011] [12:06:24] <sustrik>	network stack has no idea about "connection termination"
| [Tuesday 15 February 2011] [12:07:04] <sustrik>	the only way to find out whether the other party is alive
| [Tuesday 15 February 2011] [12:07:11] <sustrik>	is to send it a ping
| [Tuesday 15 February 2011] [12:07:15] <sustrik>	and wait for a reply
| [Tuesday 15 February 2011] [12:07:16] <private_meta>	hmm k, thank you
| [Tuesday 15 February 2011] [12:07:33] <sustrik>	if the reply doesn't arrive in x secs, you say the "connection is broken"
| [Tuesday 15 February 2011] [12:07:35] <private_meta>	Apparently boost asio implemented something like that under the hood
| [Tuesday 15 February 2011] [12:07:52] <sustrik>	quite possibly
| [Tuesday 15 February 2011] [12:08:40] <private_meta>	Just to make sure, are timeout mechanims somehow implemented?
| [Tuesday 15 February 2011] [12:09:11] <sustrik>	there's timeout parameter in zmq_poll() finction
| [Tuesday 15 February 2011] [12:09:15] <sustrik>	function
| [Tuesday 15 February 2011] [12:09:37] <private_meta>	Thank you! I'll try to figure out the rest on my own.
| [Tuesday 15 February 2011] [12:20:02] <pieterh>	sustrik: I sent an email to the list about releases
| [Tuesday 15 February 2011] [12:22:51] <pieterh>	private_meta: it kind of depends on the type of work you're doing
| [Tuesday 15 February 2011] [12:23:16] <pieterh>	e.g. for pub-sub, servers don't even know clients exist
| [Tuesday 15 February 2011] [12:24:00] <pieterh>	and 0MQ's tcp:// transport is 'disconnected' meaning nodes can go and come back invisibly
| [Tuesday 15 February 2011] [12:24:03] <private_meta>	pieterh: I need two way communication between a server and multiple clients, and the server needs to be aware of the online status of clients
| [Tuesday 15 February 2011] [12:24:17] <pieterh>	so you have to define what this means, "online status"
| [Tuesday 15 February 2011] [12:24:28] <pieterh>	and then you have to explicitly send that to the server from clients
| [Tuesday 15 February 2011] [12:24:43] <pieterh>	typically it means "alive and kicking", i.e. not frozen, not crashed, not offline
| [Tuesday 15 February 2011] [12:24:55] <private_meta>	if the network connection between server and client is severed, the server needs to know, that's the basic thing
| [Tuesday 15 February 2011] [12:25:06] <private_meta>	hmm
| [Tuesday 15 February 2011] [12:25:07] <pieterh>	right
| [Tuesday 15 February 2011] [12:25:22] <pieterh>	the other typical problems are looping application threads, CPU overload on client box, etc.
| [Tuesday 15 February 2011] [12:25:30] <pieterh>	so a heartbeat sent by the main thread in your client is often the best thing
| [Tuesday 15 February 2011] [12:25:52] <private_meta>	ok
| [Tuesday 15 February 2011] [12:25:54] <pieterh>	this could be done by certain 0MQ sockets but it would not be fully reliable
| [Tuesday 15 February 2011] [12:26:06] <pieterh>	i.e. if your main thread looped, heartbeats would still be sent out
| [Tuesday 15 February 2011] [12:26:18] <pieterh>	also the reaction of your server to a dead client is specific to the use case
| [Tuesday 15 February 2011] [12:26:41] <pieterh>	if you read the Guide, you'll see an example of "least recently used" routing
| [Tuesday 15 February 2011] [12:26:48] <private_meta>	Of course. The reaction is already implemented. It's just that we need to switch the underlying server-client-infrastructure
| [Tuesday 15 February 2011] [12:26:59] <pieterh>	it's quite easy to modify to implement heartbeats
| [Tuesday 15 February 2011] [12:27:31] <pieterh>	I believe there are more advanced examples that actually do heartbeating
| [Tuesday 15 February 2011] [12:27:34] 	 * pieterh goes to check
| [Tuesday 15 February 2011] [12:28:43] <pieterh>	take a look at the peering1/3 examples
| [Tuesday 15 February 2011] [12:29:49] <pieterh>	well, it's more complex than heartbeating but shows how to handle multiple sockets using zmq_poll
| [Tuesday 15 February 2011] [12:29:52] <pieterh>	http://zguide.zeromq.org/chapter:all#toc50
| [Tuesday 15 February 2011] [12:30:55] <pieterh>	mikko: there are zfl build failures from Hud^hJenkins, I've fixed that issue
| [Tuesday 15 February 2011] [12:31:17] <private_meta>	Thanks, I'll look it up
| [Tuesday 15 February 2011] [12:31:57] <private_meta>	*sigh* it's a pain having switch to a new library if it's not all too compatible :/
| [Tuesday 15 February 2011] [12:36:03] <sustrik>	pieterh: thx
| [Tuesday 15 February 2011] [12:36:29] <pieterh>	private_meta: you can most likely make a decent emulation of your old library
| [Tuesday 15 February 2011] [12:36:57] <pieterh>	sustrik: let's see what discussion that creates...
| [Tuesday 15 February 2011] [12:37:06] <private_meta>	pieterh: In some way that is what I want to do. Or let's say need to do.
| [Tuesday 15 February 2011] [12:37:22] <pieterh>	what is the old library? Boost.asio?
| [Tuesday 15 February 2011] [12:39:19] <private_meta>	Yes
| [Tuesday 15 February 2011] [12:39:44] <pieterh>	I'd suggest making that a public project then
| [Tuesday 15 February 2011] [12:39:59] <pieterh>	shove it on github, announce it on zeromq-dev, get others to help you
| [Tuesday 15 February 2011] [12:40:10] <private_meta>	But apparently, when compiled with a linux MPI compiler and when using it with MPI commands, it loses messages
| [Tuesday 15 February 2011] [12:40:59] <pieterh>	private_meta: if your only problem is bugs, that's pretty good
| [Tuesday 15 February 2011] [12:41:10] <private_meta>	How so?
| [Tuesday 15 February 2011] [12:41:30] <pieterh>	should be easy to solve, if it's reproducible
| [Tuesday 15 February 2011] [12:41:43] <private_meta>	Ahahaa... yeah, that's what we thought
| [Tuesday 15 February 2011] [12:42:02] <private_meta>	before we spent months trying to fix it
| [Tuesday 15 February 2011] [12:42:10] <pieterh>	months? wow... ok
| [Tuesday 15 February 2011] [12:42:33] <private_meta>	The OpenMPI project doesn't care and not a single boost or asio developer can help
| [Tuesday 15 February 2011] [12:43:15] <pieterh>	Can you explain briefly the relationship between boost asio and MPI?
| [Tuesday 15 February 2011] [12:44:16] <pieterh>	Also, if you get stuck on any 0MQ issue for more than a few... days... come here or to the dev list for help
| [Tuesday 15 February 2011] [12:44:17] <private_meta>	Well, I don't know exactly what you want detailed. We use boost asio to communicate between a server and clients, while these clients are MPI programs that run parallel code.
| [Tuesday 15 February 2011] [12:44:47] <pieterh>	i've never used MPI and have only seen boost asio from a distance
| [Tuesday 15 February 2011] [12:44:54] <pieterh>	does the MPI API call boost asio?
| [Tuesday 15 February 2011] [12:45:30] <pieterh>	or is the MPI part separate from the boost asio stuff?
| [Tuesday 15 February 2011] [12:45:32] <private_meta>	Nonono, MPI and Boost asio are not connected in any way execpt for our code. We use MPI for parallelization.
| [Tuesday 15 February 2011] [12:45:44] <pieterh>	ok...
| [Tuesday 15 February 2011] [12:45:50] <private_meta>	But still we need communication from the parallel clients to the server(s)
| [Tuesday 15 February 2011] [12:45:59] <pieterh>	so your client apps are doing weird multithreading via MPI
| [Tuesday 15 February 2011] [12:46:12] <pieterh>	and at the same time trying to do sane multithreading via 0MQ at the other side
| [Tuesday 15 February 2011] [12:46:21] <pieterh>	all in a single process
| [Tuesday 15 February 2011] [12:46:25] <private_meta>	Somewhat. I'd rather call it multiprocessing
| [Tuesday 15 February 2011] [12:46:54] <pieterh>	:-) to be able to help, I need to map unfamiliar stuff onto words that make sense in this universe... 
| [Tuesday 15 February 2011] [12:47:00] <private_meta>	We have a cluster with several nodes/servers, and they all need to be communicated with while they do some multicore and multinode crunching
| [Tuesday 15 February 2011] [12:47:18] <private_meta>	hmm
| [Tuesday 15 February 2011] [12:47:22] <private_meta>	something familiar...
| [Tuesday 15 February 2011] [12:47:39] <pieterh>	so a client behaves correctly when it doesn't do any work, and starts to lose messages when it uses MPI...?
| [Tuesday 15 February 2011] [12:47:48] <private_meta>	well, imagine MPI to be some sort of threading library, where the threads can communicate with each other AND can be on different computers
| [Tuesday 15 February 2011] [12:47:58] <private_meta>	>_>
| [Tuesday 15 February 2011] [12:47:59] <pieterh>	sure, like a primitive 0MQ
| [Tuesday 15 February 2011] [12:48:05] <private_meta>	ok
| [Tuesday 15 February 2011] [12:48:35] <pieterh>	nah, I'm sure MPI is great, that's not the point
| [Tuesday 15 February 2011] [12:48:47] <pieterh>	your emulation over 0MQ works until you link clients with MPI, right?
| [Tuesday 15 February 2011] [12:48:49] <private_meta>	so, we use this setup to execute code on different platforms, like Graphics Cards (CUDA compiler), CPUs (MPI compiler) or IBM Cell Broadband Engine (IBM compiler)
| [Tuesday 15 February 2011] [12:49:01] <pieterh>	ack, a fairly classic setup IMO
| [Tuesday 15 February 2011] [12:49:05] <private_meta>	Whenever it's compiled with MPI and used with MPI, several messages are lost
| [Tuesday 15 February 2011] [12:49:09] <pieterh>	ok
| [Tuesday 15 February 2011] [12:49:19] <pieterh>	do you have a *minimal* test case that reproduces this?
| [Tuesday 15 February 2011] [12:50:01] <private_meta>	I'd have to ask my colleague, but he's not here right now
| [Tuesday 15 February 2011] [12:50:18] <pieterh>	faced with this, what I'd do is:
| [Tuesday 15 February 2011] [12:50:21] <private_meta>	As far as I know, he created some minimal test case for trying to find the bug
| [Tuesday 15 February 2011] [12:50:39] <pieterh>	... ok, more questions
| [Tuesday 15 February 2011] [12:50:45] <pieterh>	what 0MQ socket types are you using?
| [Tuesday 15 February 2011] [12:51:44] <private_meta>	slow down, slow down, I'm new to 0MQ, do you mean like "TCP and IPC" or do you mean that "ZMQ_REP" stuff?
| [Tuesday 15 February 2011] [12:51:50] <pieterh>	:-)
| [Tuesday 15 February 2011] [12:52:01] <pieterh>	both
| [Tuesday 15 February 2011] [12:52:16] <pieterh>	socket types means REP/REQ/PUB/SUB/etc.
| [Tuesday 15 February 2011] [12:52:36] <pieterh>	but I was also going to ask what transports you use (presumably tcp://)
| [Tuesday 15 February 2011] [12:52:43] <private_meta>	We want to use TCP and IPC
| [Tuesday 15 February 2011] [12:53:02] <pieterh>	the best way to proceed (and this is for any kind of 0MQ problem you face)
| [Tuesday 15 February 2011] [12:53:20] <pieterh>	is to make a minimal 0MQ server/client that reproduces the problem
| [Tuesday 15 February 2011] [12:53:26] <private_meta>	I guess I still need to find a list where the REP/REQ and other 0MQ vocabulary is detailed
| [Tuesday 15 February 2011] [12:53:35] <pieterh>	and post this somewhere we can look at it (e.g. a gist at github)
| [Tuesday 15 February 2011] [12:53:52] <private_meta>	uhm...
| [Tuesday 15 February 2011] [12:54:03] <private_meta>	My problem isn't with 0MQ right now I hope
| [Tuesday 15 February 2011] [12:54:08] <pieterh>	and you do need to read the Guide (http://zguide.zeromq.org/chapter:all) 
| [Tuesday 15 February 2011] [12:54:22] <private_meta>	It's getting to simulate what I HAVE (without the error of course)
| [Tuesday 15 February 2011] [12:54:39] <pieterh>	90% of the time its down to some error in how you use 0MQ
| [Tuesday 15 February 2011] [12:54:42] <private_meta>	yeah, I'm doing that, I was initially coming here to ask about the socket termination issue
| [Tuesday 15 February 2011] [12:55:07] <private_meta>	It's not like the docs are a 5 minute read :)
| [Tuesday 15 February 2011] [12:55:19] <pieterh>	3-4 days, IMO
| [Tuesday 15 February 2011] [12:55:31] <pieterh>	well, it took longer to write :-)
| [Tuesday 15 February 2011] [12:56:05] <pieterh>	anyhow, first thing to do is a sanity check of your 0MQ code
| [Tuesday 15 February 2011] [12:56:11] <private_meta>	I'm sure of that. I try to extract what's necessary, I doubt I need all the details for now (somewhat lazy approach, I know)
| [Tuesday 15 February 2011] [12:56:19] <pieterh>	we don't care about code that works
| [Tuesday 15 February 2011] [12:56:48] <pieterh>	so a minimal (totally stripped down) server/client that fails, that we can look at...
| [Tuesday 15 February 2011] [12:56:56] <pieterh>	if we don't find any errors in that, we can start to blame something else
| [Tuesday 15 February 2011] [12:57:00] <private_meta>	Well, the usual then :)
| [Tuesday 15 February 2011] [12:57:13] <pieterh>	right
| [Tuesday 15 February 2011] [12:57:32] <pieterh>	feel free to email me at ph@imatix.com if I'm not here when you're ready
| [Tuesday 15 February 2011] [12:57:40] <pieterh>	or else post to the zeromq-dev list
| [Tuesday 15 February 2011] [12:58:07] <pieterh>	I assume the problem can be reproduced without exotic hardware?
| [Tuesday 15 February 2011] [13:00:50] <private_meta>	Somehow it feels like I'm being misunderstood. Until now there's no problem with 0MQ yet, just with Boost Asio, that's why I want to replace Asio with 0MQ, but I just started, so there are no problems, except for the learning curve :)
| [Tuesday 15 February 2011] [13:04:12] <pieterh>	ah
| [Tuesday 15 February 2011] [13:04:28] <private_meta>	>_<
| [Tuesday 15 February 2011] [13:04:41] <pieterh>	see how fast we kill problems with 0MQ!
| [Tuesday 15 February 2011] [13:04:48] <pieterh>	that took negative 30 minutes
| [Tuesday 15 February 2011] [13:05:01] <pieterh>	of *course* boost asio is dropping messages
| [Tuesday 15 February 2011] [13:05:30] <private_meta>	o_O
| [Tuesday 15 February 2011] [13:05:35] <private_meta>	Well, it shouldn't
| [Tuesday 15 February 2011] [13:05:47] <pieterh>	sorry for misunderstanding
| [Tuesday 15 February 2011] [13:05:59] <pieterh>	presumably there is a queue overflow issue or something
| [Tuesday 15 February 2011] [13:08:55] <pieterh>	So if you want to make a boost asio emulation layer over 0MQ, I'd recommend doing it open source
| [Tuesday 15 February 2011] [13:11:37] <private_meta>	The amount of "emulation" we need contradicts a full open source emulation... it would be a heck of a lot of work, and I don't have time for that at work >_>
| [Tuesday 15 February 2011] [13:11:47] <private_meta>	not that it wouldn't be a neat idea
| [Tuesday 15 February 2011] [13:14:59] <pieterh>	The usual (sane) approach is to make strictly only what you need for your apps, release it, and allow others to expand it
| [Tuesday 15 February 2011] [13:15:15] <pieterh>	Assuming it's possible to map the subset of boost asio you use to 0MQ
| [Tuesday 15 February 2011] [13:15:52] <private_meta>	It would be difficult I assume
| [Tuesday 15 February 2011] [13:42:37] <Guthur>	sustrik, returning to are discussion earlier re: IOCP, would it not be beneficial in the long run, if possible, to have both named pipes and sockets on IOCP, with aim to remove the need for Select
| [Tuesday 15 February 2011] [13:53:06] <staylor>	I have a question about zmq sockets, are the underlying sockets maintained or opened/closed on demand?
| [Tuesday 15 February 2011] [13:53:42] <staylor>	reason I ask is I'd like to know from my application if the client application is currently connected to the server or not, but I don't see any socket status calls in the zmq_socket api
| [Tuesday 15 February 2011] [14:04:03] <cremes>	pieterh: does anyone with a wiki account have permission to modify the FAQ?
| [Tuesday 15 February 2011] [14:04:41] <cremes>	pieterh: nm; just answered my own question
| [Tuesday 15 February 2011] [14:13:40] <cremes>	just updated the FAQ to help people with the assertion in mailbox.cpp:182
| [Tuesday 15 February 2011] [15:06:33] Notice	-Martinp23- [Global Notice] Hi everyone. You will have possibly noticed some instability on the network earlier this evening. The network is under a sustained DDoS and so lag and possible further splits are to be expected. We apologise for the inconvenience - our fantastic sponsorship and infra teams are working to minimise the further impact. Have a nice evening!
| [Tuesday 15 February 2011] [15:40:03] <sejo>	hey all I'm looking at different solutions, and basicly just need an mq to be able to use from python,
| [Tuesday 15 February 2011] [15:40:27] <sejo>	so what would be my advantage using 0mq over rabbitmq or others?
| [Tuesday 15 February 2011] [15:47:14] <Guthur>	sejo, I really think it depends on use case scenario
| [Tuesday 15 February 2011] [15:48:04] <Guthur>	they are different beasts, rabbitmq is a broker base MQ, whereas ZeroMQ is brokerless, for a start
| [Tuesday 15 February 2011] [15:48:45] <Guthur>	I wont pretend to know much about rabbitmq though
| [Tuesday 15 February 2011] [15:49:10] <Guthur>	hehe, even my 0MQ knowledge would be on the lighter side compared to some around here
| [Tuesday 15 February 2011] [15:50:54] <sejo>	ok, well basicly in the beginning i probably have only like 10 clients popping items, and the same 10 pushing others onto it
| [Tuesday 15 February 2011] [15:51:57] <sejo>	as far as I understand now I should write my own protocol(s) and can use them over the clients and the servers. However is it easy to have multiple servers handling the same data?
| [Tuesday 15 February 2011] [15:52:27] <sejo>	it probably is
| [Tuesday 15 February 2011] [15:52:39] <sejo>	sorry stupid question
| [Tuesday 15 February 2011] [15:56:09] <sejo>	my biggest fear is that i'll spend too much time developing on it before I can use it...
| [Tuesday 15 February 2011] [15:56:40] <sejo>	that's why I ask around and not test them out all.. don't have the time for it
| [Tuesday 15 February 2011] [15:58:59] <Guthur>	sure, it's sensible to do research first
| [Tuesday 15 February 2011] [15:59:56] <Guthur>	scaling to multiple servers would something that 0MQ can do well
| [Tuesday 15 February 2011] [16:01:04] <Guthur>	but you don't really get much in the way of 'topic' or 'queue' management out of the box, though there are PUB/SUB sockets
| [Tuesday 15 February 2011] [16:01:39] <Guthur>	I'm reluctant to give any hard advice though, due to be lack of hardcore experience and knowledge
| [Tuesday 15 February 2011] [16:02:16] <sejo>	thanks anyway right now I have no knowledge on what to use so
| [Tuesday 15 February 2011] [16:02:35] <Guthur>	you could glance through the 0MQ guide
| [Tuesday 15 February 2011] [16:02:50] <sejo>	basicly i want multiple servers and n-clients pushing and popping independently
| [Tuesday 15 February 2011] [16:03:00] <Guthur>	http://zguide.zeromq.org/chapter:all
| [Tuesday 15 February 2011] [16:03:12] <sejo>	i'm reading through it while we talk :p
| [Tuesday 15 February 2011] [16:03:14] <Guthur>	ok
| [Tuesday 15 February 2011] [16:03:20] <Guthur>	hehe cool
| [Tuesday 15 February 2011] [16:03:50] <Guthur>	there is a few example in there that could give some inspiration for your particular problem
| [Tuesday 15 February 2011] [16:04:41] <sejo>	yeah, main thing is that I don't need a real pub/sub, client just chooses when to pop a message
| [Tuesday 15 February 2011] [16:06:15] <Guthur>	check out the Queue device, which would show a possible multi server pattern
| [Tuesday 15 February 2011] [16:06:24] <Guthur>	at a very simple level
| [Tuesday 15 February 2011] [16:06:59] <Guthur>	pieter or sustrik would be better at giving advice than me
| [Tuesday 15 February 2011] [16:07:25] <sejo>	thk i'll chekc it out
| [Tuesday 15 February 2011] [16:07:58] <sejo>	the thing that got me here was the nice looking python api :p
| [Tuesday 15 February 2011] [16:13:46] <Guthur>	I'm not familiar with the python binding, but yeah I'm sure its nice, hehe
| [Tuesday 15 February 2011] [16:14:19] <Guthur>	python has that sort of philosophy, nice simple interfaces
| [Tuesday 15 February 2011] [16:15:04] <sejo>	we'll i'll read up on it more, the ventilation example pretty much does what i want, only i have multiple ventilators and each of them multiple types of messages
| [Tuesday 15 February 2011] [16:16:12] <sejo>	well no probably i only need one type that works with json
| [Tuesday 15 February 2011] [16:16:49] <Guthur>	I like JSON, nice format
| [Tuesday 15 February 2011] [16:17:00] <sejo>	Guthur: thanks for the information, i'll read up on it a bit more and then i'll probably need to choose
| [Tuesday 15 February 2011] [16:17:07] <sejo>	ttyal
| [Tuesday 15 February 2011] [16:17:11] <sejo>	gtg
| [Tuesday 15 February 2011] [16:17:14] <Guthur>	later
| [Tuesday 15 February 2011] [16:17:38] <Guthur>	ok, drop by later and someone more experience can give better advice
| [Tuesday 15 February 2011] [16:43:59] <lt_schmidt_jr>	is gonzalo here perchance
| [Tuesday 15 February 2011] [16:46:59] <whack>	So, is there no way to bind to a random port? (like binding to port 0)
| [Tuesday 15 February 2011] [16:47:19] <whack>	I'm not seeing anything obvious in the docs, and attempts to bind to tcp://blah:0 result in an error
| [Tuesday 15 February 2011] [17:46:57] <sustrik>	lt_schmidt_jr: gonzalo doesn't come here often, you have to use email instead
| [Tuesday 15 February 2011] [17:47:23] <sustrik>	whack: no there's no way
| [Tuesday 15 February 2011] [17:53:51] <lt_schmidt_jr>	sustrik; we are having an impedance mismatch on our responses, thanks 
| [Tuesday 15 February 2011] [18:06:55] <kdj>	So what is the proper way to make sure that a message is sent to a polling server? Just a response?
| [Tuesday 15 February 2011] [18:07:33] <cremes>	kdj: i don't understand the question; can you rephrase?
| [Tuesday 15 February 2011] [18:09:48] <kdj>	Sorry. We have some clients that will occasionally send a short message to a server... but just sending won't error if the server isn't there. I understand why (I think)
| [Tuesday 15 February 2011] [18:10:09] <kdj>	But I want to make sure the server is there
| [Tuesday 15 February 2011] [18:10:40] <cremes>	kdj: that's correct; 0mq has no indicator that the server went away
| [Tuesday 15 February 2011] [18:11:02] <cremes>	you should establish an "ack" that the server should send back; if it times out, the server is dead
| [Tuesday 15 February 2011] [18:11:17] <cremes>	i recommend polling on req/rep sockets to accomplish this
| [Tuesday 15 February 2011] [18:11:43] <cremes>	e.g. each client has its own REQ socket; the server has a XREP socket (so that it can respond to multiple clients)
| [Tuesday 15 February 2011] [18:11:52] <kdj>	You can poll on REQ sockets?
| [Tuesday 15 February 2011] [18:12:04] <kdj>	Yeah, that is how it is setup now
| [Tuesday 15 February 2011] [18:12:06] <cremes>	absolutely; send/recv with ZM_NOBLOCK
| [Tuesday 15 February 2011] [18:12:15] <cremes>	and register them with zmq_poll
| [Tuesday 15 February 2011] [18:13:45] <kdj>	Sending with NOBLOCK isn't actually doing anything with just a normal REQ socket, but it does on receive... is that because I need polling?
| [Tuesday 15 February 2011] [18:14:34] <cremes>	kdj: well, you don't *need* to send with noblock 
| [Tuesday 15 February 2011] [18:14:50] <cremes>	the basic idea is when your client sends the data, start a timer
| [Tuesday 15 February 2011] [18:15:02] <cremes>	if the server responds back, cancel the timer
| [Tuesday 15 February 2011] [18:15:08] <cremes>	if the timer expires, close the req socket
| [Tuesday 15 February 2011] [18:15:26] <cremes>	none of that needs noblock 
| [Tuesday 15 February 2011] [18:15:42] <lt_schmidt_jr>	to jump in with kdj, when would you use in polling vs blocking
| [Tuesday 15 February 2011] [18:15:46] <cremes>	you will need to poll if your timer and req socket are in the same thread
| [Tuesday 15 February 2011] [18:16:04] <cremes>	lt_schmidt_jr: like so...
| [Tuesday 15 February 2011] [18:16:23] <cremes>	if you start your timer and then call recv in blocking mode, how do you handle timer expiration?
| [Tuesday 15 February 2011] [18:16:43] <cremes>	1. timer must live in a separate thread or process from the blocking recv
| [Tuesday 15 February 2011] [18:17:10] <lt_schmidt_jr>	right
| [Tuesday 15 February 2011] [18:17:12] <cremes>	2. recv is non-blocking and you use poll to handle the recv; timer is on the same thread
| [Tuesday 15 February 2011] [18:17:21] <cremes>	those are the 2 ways i would approach
| [Tuesday 15 February 2011] [18:17:25] <cremes>	i like #2 better
| [Tuesday 15 February 2011] [18:17:31] <kdj>	Ok. I wasn't sending an acknowledgement from the server originally... just receiving the message and moving on
| [Tuesday 15 February 2011] [18:17:33] <cremes>	threading gets so messy
| [Tuesday 15 February 2011] [18:18:09] <cremes>	kdj: if you were using REQ sockets on the client, the next time you tried to send you would get a EFSM error
| [Tuesday 15 February 2011] [18:18:37] <cremes>	REQ/REP sockets are strictly stateful; REQ *must* send/recv/send/recv while REP *must* recv/send/recv/send
| [Tuesday 15 February 2011] [18:19:44] <kdj>	Yeah, that makes sense.
| [Tuesday 15 February 2011] [18:21:39] <lt_schmidt_jr>	hmm, interesting, so I should be able to put multiple sockets with a poller
| [Tuesday 15 February 2011] [18:21:50] <lt_schmidt_jr>	same poller
| [Tuesday 15 February 2011] [18:23:04] <kdj>	Hmmm... does 0mq send an acknowledgement automatically?
| [Tuesday 15 February 2011] [18:23:27] <cremes>	lt_schmidt_jr: yes
| [Tuesday 15 February 2011] [18:23:30] <cremes>	kdj: no
| [Tuesday 15 February 2011] [18:24:17] <cremes>	kdj: the heartbeat is an application-level responsibility; your code must process and send the ack
| [Tuesday 15 February 2011] [18:24:46] <cremes>	you could actually abstract this out into your own private "heartbeat" socket and make it completely transparent
| [Tuesday 15 February 2011] [18:25:01] <kdj>	Yeah, that totally makes sense... I just threw some code together to test it though and it (sort of) works
| [Tuesday 15 February 2011] [18:26:03] <kdj>	having a poller on the server end, which just recieves messages (no sending), and a client which sends and then receives... somehow the receiving on the client end is still happening (and not blocking)
| [Tuesday 15 February 2011] [18:26:10] <lt_schmidt_jr>	kdj: for me I am planning to use ZooKeeper, which I have used successfully in a similar way to figure out server presence
| [Tuesday 15 February 2011] [18:27:01] <lt_schmidt_jr>	in my case to figure out other servers that will form a cluster
| [Tuesday 15 February 2011] [18:27:13] <cremes>	kdj: print out the data that your client is receiving
| [Tuesday 15 February 2011] [18:27:26] <cremes>	or run tcpdump and watch the packets fly
| [Tuesday 15 February 2011] [18:27:45] <cremes>	unless you are issuing a zmq_send() from the server, the client shouldn't be getting a response
| [Tuesday 15 February 2011] [18:27:59] <cremes>	there has to be code doing that somewhere in your example
| [Tuesday 15 February 2011] [18:28:05] <cremes>	is it small enough to pastie?
| [Tuesday 15 February 2011] [18:29:19] <lt_schmidt_jr>	kdj, cremes: you can use http://pastebin.com/
| [Tuesday 15 February 2011] [18:31:34] <kdj>	Sorry, I think it was just my threading code for testing it. It works as it is supposed to. :X
| [Tuesday 15 February 2011] [18:32:02] <cremes>	yeah, that's an easy mistake to make
| [Tuesday 15 February 2011] [18:32:18] <cremes>	take a look at using the "inproc" transport for communicating between threads
| [Tuesday 15 February 2011] [18:32:35] <cremes>	it obviates the need for mutexes and makes threading code simpler
| [Tuesday 15 February 2011] [18:32:56] <cremes>	btw, that's one of the great wins of using 0mq; it's a threading library too!
| [Tuesday 15 February 2011] [18:34:36] <lt_schmidt_jr>	cremes: not to ask a stupid question, but how does one use it for threading - is it in the guide?
| [Tuesday 15 February 2011] [18:36:00] <cremes>	lt_schmidt_jr: i don't know if it's in the guide; haven't looked lately
| [Tuesday 15 February 2011] [18:36:03] <cremes>	but here's the basic idea
| [Tuesday 15 February 2011] [18:36:26] <cremes>	imagine you have 10 threads trying to access a shared resource
| [Tuesday 15 February 2011] [18:36:35] <lt_schmidt_jr>	right
| [Tuesday 15 February 2011] [18:36:41] <cremes>	right now you use a mutex, spinlock or some locking structure
| [Tuesday 15 February 2011] [18:36:50] <lt_schmidt_jr>	ok
| [Tuesday 15 February 2011] [18:37:00] <cremes>	with 0mq, put the resource that everyone wants into its own thread and give it a XREP socket
| [Tuesday 15 February 2011] [18:37:22] <cremes>	now make every other thread a "client" of that "server" and give them REQ sockets
| [Tuesday 15 February 2011] [18:37:50] <cremes>	connect them all together using inproc (all platforms) or ipc (unix only) to communicate so you don't pay the TCP penalty
| [Tuesday 15 February 2011] [18:38:12] <cremes>	each client "asks" the resource for whatever via the 0mq socket
| [Tuesday 15 February 2011] [18:38:26] <cremes>	the 0mq socket serializes all access to the resource and prevents all race conditions
| [Tuesday 15 February 2011] [18:38:35] <cremes>	make sense?
| [Tuesday 15 February 2011] [18:38:35] <lt_schmidt_jr>	I see
| [Tuesday 15 February 2011] [18:38:42] <lt_schmidt_jr>	absolutely
| [Tuesday 15 February 2011] [18:38:51] <lt_schmidt_jr>	thank you
| [Tuesday 15 February 2011] [18:38:54] <cremes>	this is the basic idea behind Actors if you have played with those in any languages
| [Tuesday 15 February 2011] [18:39:05] <lt_schmidt_jr>	I have played with erl
| [Tuesday 15 February 2011] [18:39:28] <cremes>	lt_schmidt_jr: right; instead of using mutexes, you are using *messaging* for your concurrency
| [Tuesday 15 February 2011] [18:39:45] <cremes>	and here's another cool part of using 0mq
| [Tuesday 15 February 2011] [18:39:56] <lt_schmidt_jr>	cremes: very cool
| [Tuesday 15 February 2011] [18:40:04] <cremes>	let's say at some point this "server" resource needs to be on its own box
| [Tuesday 15 February 2011] [18:40:34] <cremes>	all you have to do to change communications is modify the transport string that you pass to zmq_connect/zmq_bind from inproc (or ipc) to tcp
| [Tuesday 15 February 2011] [18:40:39] <cremes>	instant scaling
| [Tuesday 15 February 2011] [18:40:52] <cremes>	i have used this technique many times already; works wonderfully
| [Tuesday 15 February 2011] [18:40:53] <lt_schmidt_jr>	yeah, you would just change the ..
| [Tuesday 15 February 2011] [18:41:36] <lt_schmidt_jr>	I have prototyped a pub/sub message bus and I have inproc/ipc/tcp going between different participants
| [Tuesday 15 February 2011] [18:42:03] <kdj>	Hmmm... now I'm not really sure how our original client/server stuff was working...
| [Tuesday 15 February 2011] [18:42:29] <lt_schmidt_jr>	but I think I am just not treating the threading correctly - too many threads
| [Tuesday 15 February 2011] [18:43:29] <cremes>	lt_schmidt_jr: you'll have to figure that one out; i'm not a threading expert
| [Tuesday 15 February 2011] [18:45:29] <lt_schmidt_jr>	cremes: the issue is I have a thread per connection and I still need to use polling to figure out if the thread needs to be shut down
| [Tuesday 15 February 2011] [18:45:36] <lt_schmidt_jr>	so its a little ugly
| [Tuesday 15 February 2011] [18:46:41] <cremes>	i don't understand, but ok
| [Tuesday 15 February 2011] [18:46:46] <lt_schmidt_jr>	If I block on recv, I am not sure how a subscriber can be inerrrupted
| [Tuesday 15 February 2011] [18:46:58] <cremes>	oh, i see
| [Tuesday 15 February 2011] [18:47:04] <cremes>	are you using 2.0.10 or 2.1.0?
| [Tuesday 15 February 2011] [18:47:13] <lt_schmidt_jr>	2.0.1 and Java
| [Tuesday 15 February 2011] [18:47:20] <lt_schmidt_jr>	2.0.10
| [Tuesday 15 February 2011] [18:47:23] <cremes>	um... ok
| [Tuesday 15 February 2011] [18:47:47] <lt_schmidt_jr>	is there something in 2.1.0 that  I should be using?
| [Tuesday 15 February 2011] [18:47:55] <cremes>	i think your only solution then is to close the entire context via zmq_term()
| [Tuesday 15 February 2011] [18:48:08] <cremes>	that will cause each socket to awaken and return ETERM
| [Tuesday 15 February 2011] [18:48:45] <cremes>	everybody should be on 2.1.0 now; the only 2.0.10 users should be legacy guys who *cannot* upgrade for whatever reason
| [Tuesday 15 February 2011] [18:48:52] <cremes>	so yeah, upgrade
| [Tuesday 15 February 2011] [18:48:52] <lt_schmidt_jr>	see, I have multiple subscibers within the same context, and only one would need to be terminated
| [Tuesday 15 February 2011] [18:49:17] <cremes>	yep, terminating the context terminates *all* sockets so that's your only choice there
| [Tuesday 15 February 2011] [18:49:33] <cremes>	in 2.1.0 i believe you can call zmq_close() on the socket from another thread and it will work as expected
| [Tuesday 15 February 2011] [18:49:35] <lt_schmidt_jr>	ok, I skipped 2.1.0, because it caused the java binding unit tests to fail
| [Tuesday 15 February 2011] [18:49:53] <cremes>	yeah, 2.1.0 is considered beta so not everyone has updated their bindings
| [Tuesday 15 February 2011] [18:50:02] <lt_schmidt_jr>	maybe I should do that myself
| [Tuesday 15 February 2011] [18:50:08] <cremes>	but it is *way* more stable than 2.0.10 so i would upgrade
| [Tuesday 15 February 2011] [18:50:16] <cremes>	maybe you could submit a patch to fix the java tests
| [Tuesday 15 February 2011] [18:50:41] <lt_schmidt_jr>	I submitted the maven fix, should do this as well
| [Tuesday 15 February 2011] [18:51:16] <lt_schmidt_jr>	so I could close the socket from a different thread, great
| [Tuesday 15 February 2011] [18:52:16] <lt_schmidt_jr>	I guess I could figure out how to use polling correctly and not have a bunch of threads in the first place
| [Tuesday 15 February 2011] [18:52:36] <lt_schmidt_jr>	that is have many sockets and a single polling thread
| [Tuesday 15 February 2011] [18:53:13] <lt_schmidt_jr>	and not have the computer turn into a space heater
| [Tuesday 15 February 2011] [18:53:51] <lt_schmidt_jr>	will go through the guide 
| [Tuesday 15 February 2011] [18:54:54] <kdj>	Thanks for your help cremes
| [Tuesday 15 February 2011] [19:00:54] <cremes>	kdj: you are welcome; remember to pay it forward at some point ;)
| [Tuesday 15 February 2011] [19:01:50] <kdj>	Hopefully that won't involve inadvertently leading someone astray. ;)
| [Tuesday 15 February 2011] [23:50:44] <zedas>	sustrik: hey so i still see this poll 100%CPU bug even with the latest 2.1.0 and *cannot* figure out how to fix it. http://dpaste.de/oxeU/
| [Tuesday 15 February 2011] [23:51:20] <zedas>	sustrik: it looks like i'll have to dig into the zeromq code and pull out the error handling that zmq_poll does.
| [Wednesday 16 February 2011] [02:07:37] <sustrik>	zedas: any chance to reproduce the problem here?
| [Wednesday 16 February 2011] [02:24:37] <zedas>	sustrik: it happens at random on my servers, so next time i can gdb to it and debug for you.
| [Wednesday 16 February 2011] [02:24:59] <sustrik>	thanks
| [Wednesday 16 February 2011] [02:25:12] <sustrik>	find out what's looping there
| [Wednesday 16 February 2011] [02:31:21] <zedas>	well i'm pretty sure it's zmq_poll not handling an EAGAIN on zeromq socket objects.
| [Wednesday 16 February 2011] [02:31:41] <zedas>	but i'll confirm it and work up a fix.  looking at the code the fix may be a flag that says to not stuff errors.
| [Wednesday 16 February 2011] [02:42:26] <sustrik>	let me have a look...
| [Wednesday 16 February 2011] [02:42:45] <sustrik>	zedas: is that linux?
| [Wednesday 16 February 2011] [02:44:30] <sustrik>	hm, the only operations on zeromq socket objects witihn zmq_poll is zmq_getsockopt()
| [Wednesday 16 February 2011] [02:45:02] <sustrik>	are you getting EAGAIN from zmq_getsockopt()? That should not happen as far as i am aware.
| [Wednesday 16 February 2011] [03:41:54] <enleth>	Hello
| [Wednesday 16 February 2011] [03:44:44] <sustrik>	hi
| [Wednesday 16 February 2011] [03:44:52] <enleth>	I've got a problem building OMQ - it's about the luuid dependency. OMQ reuires the OSSP UUID library, which, due to conflicts with (unmaintained and dropped a long time ago) e2fsprogrs libuuid was renamed to libossp-uuid in my Linux distribution and, FWIW, this was generally a very popular solution.
| [Wednesday 16 February 2011] [03:45:10] <enleth>	But OMQ looks for libuuid and the configure script does not accept an alternate name
| [Wednesday 16 February 2011] [03:45:56] <sustrik>	enleth: easy, patch the build system and submit the patch to the mailing list
| [Wednesday 16 February 2011] [03:47:49] <enleth>	Oh, and I just noticed that the proper libuuid provides an uuid-config program for the configure script to use
| [Wednesday 16 February 2011] [03:48:08] <enleth>	uuid-config --libs outputs -lossp-uuid, which should be used
| [Wednesday 16 February 2011] [03:48:41] <enleth>	I guess this is what the build system should do instead of using a hardcoded name
| [Wednesday 16 February 2011] [03:49:12] <sustrik>	great, post your suggestion to the mailing list
| [Wednesday 16 February 2011] [03:49:12] <enleth>	The problem is, my skills with autotools are crap
| [Wednesday 16 February 2011] [03:49:23] <sustrik>	so that build system maintainers can have a look at it
| [Wednesday 16 February 2011] [03:49:28] <enleth>	OK, will do
| [Wednesday 16 February 2011] [03:49:31] <sustrik>	thanks
| [Wednesday 16 February 2011] [04:16:56] <enleth>	No, wait. It does use the old e2fsprogrs-derived libuuid, my bad.
| [Wednesday 16 February 2011] [04:25:44] <enleth>	OK, there is no problem, the distro repository managed screwed up and I got a bad upgrade installed
| [Wednesday 16 February 2011] [04:34:18] <mikko>	pieterh: are you here sir?
| [Wednesday 16 February 2011] [04:34:28] <pieterh>	mikko: just arrived
| [Wednesday 16 February 2011] [04:36:22] <mikko>	is there a specific reason why test functions are compiled into zfl ?
| [Wednesday 16 February 2011] [04:36:33] <mikko>	are those symbols needed outside selftest?
| [Wednesday 16 February 2011] [04:38:49] <pieterh>	if you can find a way of compiling a single C source file into two objects, I'm hapopy
| [Wednesday 16 February 2011] [04:38:51] <pieterh>	*happy
| [Wednesday 16 February 2011] [04:39:02] <pieterh>	but the test code must, for me, be in the same source as the actual class
| [Wednesday 16 February 2011] [04:40:00] <mikko>	pieterh: ok
| [Wednesday 16 February 2011] [04:41:04] <pieterh>	mikko: if people are unhappy about extra code in their executables we could make these conditionally compiled
| [Wednesday 16 February 2011] [04:42:36] <mikko>	pieterh: currently i was prototyping something like: https://gist.github.com/3f2a43c19ab439b22884
| [Wednesday 16 February 2011] [04:42:41] <mikko>	separate tests/ directory
| [Wednesday 16 February 2011] [04:42:59] <mikko>	but i think it should be possible to create separate objects from same code as well
| [Wednesday 16 February 2011] [04:43:00] <pieterh>	aaaghhhh..... 
| [Wednesday 16 February 2011] [04:43:13] <pieterh>	it's the reason the man pages are a real pain to maintain
| [Wednesday 16 February 2011] [04:43:21] <pieterh>	separate directories look very clean organizationally
| [Wednesday 16 February 2011] [04:43:29] <pieterh>	but they ensure pieces don't get updated
| [Wednesday 16 February 2011] [04:44:02] <pieterh>	also the test cases are essential documentation, like the rest of the source file
| [Wednesday 16 February 2011] [04:44:29] <pieterh>	running the selftest in its own directory is a good idea, some tests need to mess with files
| [Wednesday 16 February 2011] [04:44:57] <pieterh>	but I really, really don't want to find ourselves in the zmq situation of having lots of code that lacks test cases
| [Wednesday 16 February 2011] [04:46:09] <mikko>	hmmm, this gives me additional idea
| [Wednesday 16 February 2011] [04:47:14] <mikko>	in zfls case code coverage reports would make sense
| [Wednesday 16 February 2011] [04:47:46] <pieterh>	yes, as an additional insurance
| [Wednesday 16 February 2011] [04:47:57] <pieterh>	that's meta testing, i.e. testing the test cases
| [Wednesday 16 February 2011] [04:48:11] <pieterh>	it's a neat idea
| [Wednesday 16 February 2011] [04:48:27] <mikko>	i'll put this on my todo
| [Wednesday 16 February 2011] [04:49:04] <pieterh>	there's still space? I'm impressed...
| [Wednesday 16 February 2011] [04:49:07] <pieterh>	:-)
| [Wednesday 16 February 2011] [04:49:33] <ianbarber>	speaking off: mikko, did you move the pear server?
| [Wednesday 16 February 2011] [04:49:44] <ianbarber>	s/off/of
| [Wednesday 16 February 2011] [04:50:51] <mikko>	ianbarber: in the works
| [Wednesday 16 February 2011] [04:51:12] <mikko>	hmm
| [Wednesday 16 February 2011] [04:51:23] <mikko>	i guess the easiest would be to put it where rest of the stuff is
| [Wednesday 16 February 2011] [04:51:30] <mikko>	you can point the dns to 193.211.31.222
| [Wednesday 16 February 2011] [04:51:46] <ianbarber>	i'll point both php. and pear. at it
| [Wednesday 16 February 2011] [04:56:05] <mikko>	looking at the apache rewrite rules this makes me want to use nginx
| [Wednesday 16 February 2011] [04:56:55] <kristsk>	nginx is about the same, imho
| [Wednesday 16 February 2011] [04:57:47] <mikko>	kristsk: dynamic virtualhosting seems a lot more fluent in nginx
| [Wednesday 16 February 2011] [05:03:15] <kristsk>	might be because of nginx's config syntax, it does not feel so archaic
| [Wednesday 16 February 2011] [05:05:06] <kristsk>	in regard of vhosts lighthttpd is sought to be more powerfull
| [Wednesday 16 February 2011] [05:48:11] <Guthur>	sustrik: do you think having wsapoll on supported win platforms would be good to have?
| [Wednesday 16 February 2011] [06:06:02] <ianbarber>	pieterh: about?
| [Wednesday 16 February 2011] [06:06:22] <pieterh>	ianbarber: about 12ish
| [Wednesday 16 February 2011] [06:06:46] <pieterh>	:-) how can I help you?
| [Wednesday 16 February 2011] [06:06:50] <ianbarber>	:)
| [Wednesday 16 February 2011] [06:08:09] <ianbarber>	i discovered the wonderful land of martinique has a fun domain extension, so the PHP extension is now available on php.zero.mq and pear.zero.mq (pear is the PHP package system). Was wondering - do you want to have zeromq.org listen on zero.mq and www.zero.mq as well, i can point in that direction (even if it's just doing a rewrite to zeromq.org)
| [Wednesday 16 February 2011] [06:08:56] <ianbarber>	we can redirect from hosting as well, just seems like if someone does go to just zero.mq, they should end up at the site. It's on mikko's geo redundant hosting at the mo :)
| [Wednesday 16 February 2011] [06:09:08] <pieterh>	oh... I like it
| [Wednesday 16 February 2011] [06:10:25] <ianbarber>	i can point them at 74.86.234.146 if thats sensible - don't know if there are any weird wikidot issues or similar 
| [Wednesday 16 February 2011] [06:10:27] <pieterh>	if you point www.zero.mq to www.wikidot.com, then I'll add it to the custom domains on the website
| [Wednesday 16 February 2011] [06:10:32] <ianbarber>	cool
| [Wednesday 16 February 2011] [06:10:33] <ianbarber>	will do
| [Wednesday 16 February 2011] [06:10:57] <pieterh>	wow, we have a sneaky short domain name, so 2011...
| [Wednesday 16 February 2011] [06:11:40] <pieterh>	afair you can't point zero.mq itself to a DNS name, you need to use the IP address there
| [Wednesday 16 February 2011] [06:11:52] <mikko>	you can
| [Wednesday 16 February 2011] [06:11:53] <mikko>	CNAME
| [Wednesday 16 February 2011] [06:11:57] <ianbarber>	should be able to cname it
| [Wednesday 16 February 2011] [06:11:58] <ianbarber>	yeah
| [Wednesday 16 February 2011] [06:12:27] <pieterh>	maybe I'm confusing with wildcards, I usually point *.zeromq.org etc. to wikidot
| [Wednesday 16 February 2011] [06:13:08] <pieterh>	cname the heck out of it, ianbarber, I'll add the custom domain entries in an hour or so
| [Wednesday 16 February 2011] [06:14:12] <ianbarber>	cool :) I've pointed zero.mq and www.zero.mq, so we'll see then :)
| [Wednesday 16 February 2011] [06:15:15] <pieterh>	would it be worth doing something sneaky like...
| [Wednesday 16 February 2011] [06:15:31] <pieterh>	zero.mq -> redirects to www.zeromq.org/community... ?
| [Wednesday 16 February 2011] [06:16:03] <pieterh>	I can make that work
| [Wednesday 16 February 2011] [06:16:54] <pieterh>	ianbarber: DNS seems to have propagated already, that was fast
| [Wednesday 16 February 2011] [06:17:07] <pieterh>	presumably not cached anywhere
| [Wednesday 16 February 2011] [06:17:33] <ianbarber>	yeah, www wasn't set up before
| [Wednesday 16 February 2011] [06:17:45] <ianbarber>	redirect to community sounds like an idea, if that's doable on wikidot
| [Wednesday 16 February 2011] [06:18:12] <pieterh>	np, give me 5 minutes...
| [Wednesday 16 February 2011] [06:20:03] <enleth>	mikko: hey, just wanted to say thanks for the PHP bindings for ZMQ, TC and TT - good job!
| [Wednesday 16 February 2011] [06:21:40] <enleth>	It was pretty amusing when I opened the github page for ZMQ bindings a moment ago, saw your username and though "well, I know this guy - what else I might be using that he did?"
| [Wednesday 16 February 2011] [06:21:55] <pieterh>	ianbarber: ok, done, give it a whirl... :-)
| [Wednesday 16 February 2011] [06:22:06] <mikko>	enleth: my pleasure
| [Wednesday 16 February 2011] [06:25:13] <ianbarber>	pieterh: i seem to be getting a password page. that's odd
| [Wednesday 16 February 2011] [06:25:32] <pieterh>	ianbarber: ah, my bad, it's still a private site, will fix immediately
| [Wednesday 16 February 2011] [06:25:47] <ianbarber>	ah, cool
| [Wednesday 16 February 2011] [06:26:03] <pieterh>	ianbarber: try again now?
| [Wednesday 16 February 2011] [06:26:12] <ianbarber>	yep, that's looking good
| [Wednesday 16 February 2011] [06:26:17] <ianbarber>	very nice! 
| [Wednesday 16 February 2011] [06:26:57] <pieterh>	it's very cool
| [Wednesday 16 February 2011] [09:30:33] <ianbarber>	pieterh: was thinking, I've noticed that there are a lot of questions on the mailing lists that are solved in broadly the same way, even from people who have read the guide (myself included). I was wondering whether there is any value in some sort of 0MQ pattern library. 
| [Wednesday 16 February 2011] [09:30:50] <ianbarber>	sort of like http://developer.yahoo.com/ypatterns/ but with messaging patterns at all kinds of scales
| [Wednesday 16 February 2011] [09:31:56] <ianbarber>	i like how the generic pattern is described and an example given in each one of those (http://developer.yahoo.com/ypatterns/navigation/accordion.html) 
| [Wednesday 16 February 2011] [09:32:37] <ianbarber>	but still pretty simple, 1 page
| [Wednesday 16 February 2011] [09:51:55] <mikko>	cremes: you can run make check
| [Wednesday 16 February 2011] [09:52:07] <mikko>	(dont wanna confuse the thread as it has moved on from there)
| [Wednesday 16 February 2011] [09:54:40] <cremes>	mikko: here are the results:  https://gist.github.com/829493
| [Wednesday 16 February 2011] [09:54:43] <cremes>	failure...
| [Wednesday 16 February 2011] [09:57:00] <mikko>	No space left on device
| [Wednesday 16 February 2011] [09:58:22] <cremes>	how did i not see that?.... bleary eyed after 30 hours of debugging...
| [Wednesday 16 February 2011] [09:58:39] <mikko>	also, the tests wont output anything but they should assert on failure
| [Wednesday 16 February 2011] [09:58:47] <mikko>	return code for success is 0
| [Wednesday 16 February 2011] [09:59:24] <cremes>	oh wait, that out of space condition happened overnight as i was testing something
| [Wednesday 16 February 2011] [09:59:29] <cremes>	hold on a sec
| [Wednesday 16 February 2011] [10:00:51] <cremes>	mikko: reload the gist; it now shows all as passing
| [Wednesday 16 February 2011] [10:01:10] <cremes>	my problem with running the tests was i didn't know the right make target
| [Wednesday 16 February 2011] [10:01:25] <mikko>	make check is autotools default test target
| [Wednesday 16 February 2011] [10:01:29] <cremes>	i tried 'make test' and 'make all' but the former didn't exist and the latter didn't seem to run them
| [Wednesday 16 February 2011] [10:01:35] <cremes>	didn't know that
| [Wednesday 16 February 2011] [10:02:03] <mikko>	make test seems to be widely used as well
| [Wednesday 16 February 2011] [10:02:04] <cremes>	looks like all is well; chalk this up to user error
| [Wednesday 16 February 2011] [10:02:25] <cremes>	yeah, maybe adding it as an additional target would be a nice convenience
| [Wednesday 16 February 2011] [10:02:43] <mikko>	i'll add that on todo
| [Wednesday 16 February 2011] [10:09:41] <pieterh_>	ianbarber, was eating lunch... back now
| [Wednesday 16 February 2011] [10:10:17] <pieterh_>	imo there would be value in a pattern library but I'll use Sustrik's Law here
| [Wednesday 16 February 2011] [10:10:57] <pieterh_>	find the person to collect and maintain the patterns, and the problem is solved :-)
| [Wednesday 16 February 2011] [10:12:42] <mikko>	http://build.valokuva.org/job/test-gcov/5/cobertura/?
| [Wednesday 16 February 2011] [10:12:48] <mikko>	zfl code coverage
| [Wednesday 16 February 2011] [10:13:22] <ianbarber>	pieterh_: fair point, i do appreciate sustrik's law :)
| [Wednesday 16 February 2011] [10:13:33] <mikko>	hmm source code missing
| [Wednesday 16 February 2011] [10:14:48] <pieterh_>	ianbarber, you can also apply Pieter's Response to Calls to Action
| [Wednesday 16 February 2011] [10:15:01] <pieterh_>	"Excellent idea, Ian, I'm curious to see how you do it"
| [Wednesday 16 February 2011] [10:15:31] <pieterh_>	Known in ruder groups as nypa :-)
| [Wednesday 16 February 2011] [10:16:46] <pieterh_>	Actually, I do have a more positive idea
| [Wednesday 16 February 2011] [10:17:33] <pieterh_>	When you see a question solved in a way you think is reusable, point me to it, and I'll cover it in the Guide at some stage
| [Wednesday 16 February 2011] [10:17:47] <pieterh_>	there are a lot of chapters waiting to be written
| [Wednesday 16 February 2011] [10:19:02] <ianbarber>	yeah, i think that's good. the guide really is the basis for shared understanding about it
| [Wednesday 16 February 2011] [10:19:13] <mikko>	ah
| [Wednesday 16 February 2011] [10:19:16] <mikko>	finally it works
| [Wednesday 16 February 2011] [10:19:17] <mikko>	https://build.valokuva.org/job/test-gcov/7/cobertura/_default_/zfl_rpcd_c/
| [Wednesday 16 February 2011] [10:19:35] <ianbarber>	i'm happy to do some patterns (at some point!) just wanted to check whether it fitted in with the direction you're taking the guide
| [Wednesday 16 February 2011] [10:25:38] <pieterh_>	mikko: sweet!
| [Wednesday 16 February 2011] [10:25:59] <pieterh_>	ianbarber, I guess the Guide aims to be the bible, eventually
| [Wednesday 16 February 2011] [10:26:02] <pieterh_>	modest aims
| [Wednesday 16 February 2011] [10:27:04] <pieterh_>	we can (and by 'we' I really mean 'you') start by collecting text on a wiki page
| [Wednesday 16 February 2011] [10:27:19] <pieterh_>	that is trivial, shareable, reusable
| [Wednesday 16 February 2011] [10:27:42] <pieterh_>	join the zero.mq (great name) wiki if you're not already on it, start a docs:patterns page...
| [Wednesday 16 February 2011] [10:27:47] <ianbarber>	yeah. i think the tricky thing with the guide is balancing it for new users, and for experienced ones
| [Wednesday 16 February 2011] [10:28:06] <ianbarber>	yep, i'm on it, will do
| [Wednesday 16 February 2011] [10:28:07] <pieterh_>	no problem, really... start with simple stuff, get more advanced as you go along
| [Wednesday 16 February 2011] [10:28:30] <pieterh_>	patterns would be like a cookbook, stand alone section, with some good indexing
| [Wednesday 16 February 2011] [10:28:33] <ianbarber>	yeah
| [Wednesday 16 February 2011] [10:28:55] <ianbarber>	that's pretty much the idea, just to have a concise example of different interaction models really
| [Wednesday 16 February 2011] [10:29:08] <pieterh_>	even copy/paste of solutions from the email list is a good start
| [Wednesday 16 February 2011] [10:29:22] <pieterh_>	don't worry about producing prose, that's my speciality
| [Wednesday 16 February 2011] [10:42:44] <mikko>	hi Steve-o 
| [Wednesday 16 February 2011] [10:42:55] <Steve-o>	hi mikko
| [Wednesday 16 February 2011] [10:43:59] <Steve-o>	working on new house this week, a foreclosure so many minor issues :/
| [Wednesday 16 February 2011] [10:44:16] <Steve-o>	back in HK next week and back to work
| [Wednesday 16 February 2011] [10:44:36] <mikko>	is your house in the states?
| [Wednesday 16 February 2011] [10:44:47] <Steve-o>	upstate NY
| [Wednesday 16 February 2011] [10:45:11] <mikko>	are you moving there?
| [Wednesday 16 February 2011] [10:45:24] <Steve-o>	near Martha Stewart is about the only notable point
| [Wednesday 16 February 2011] [10:46:18] <Steve-o>	eventually moving there, house prices very cheap so good time to buy
| [Wednesday 16 February 2011] [10:46:47] <Steve-o>	I have another year for my greencard it looks
| [Wednesday 16 February 2011] [10:48:40] <Steve-o>	so what is the status on autoconf in zeromq, anymore changes required?
| [Wednesday 16 February 2011] [10:49:52] <mikko>	i think we should get 2.1.0 out before refactoring the openpgm part
| [Wednesday 16 February 2011] [10:49:58] <mikko>	it seems to be working well with openpgm trunk
| [Wednesday 16 February 2011] [10:50:09] <mikko>	some open issues to solve but in general good
| [Wednesday 16 February 2011] [10:50:33] <mikko>	one of them is how to link openpgm if zeromq invokes openpgm built?
| [Wednesday 16 February 2011] [10:50:35] <mikko>	build*
| [Wednesday 16 February 2011] [10:50:51] <mikko>	install openpgm.so and use the shared lib?
| [Wednesday 16 February 2011] [10:51:04] <mikko>	use the object files directly?
| [Wednesday 16 February 2011] [10:51:05] <mikko>	etc
| [Wednesday 16 February 2011] [10:51:33] <Steve-o>	good question, distros would like shared libs, 
| [Wednesday 16 February 2011] [10:51:43] <mikko>	linking libpgm.a into libzmq.so works on linux (assuming libpgm.a is position independent code) but not portable
| [Wednesday 16 February 2011] [10:52:16] <mikko>	yes, my only fear is the following scenario:
| [Wednesday 16 February 2011] [10:52:17] <Steve-o>	which is why I don't have a dll on Windows
| [Wednesday 16 February 2011] [10:52:53] <mikko>	user has libpgm installed, now installs zeromq with openpgm support, zeromq invokes openpgm build and overwrites the existing installation
| [Wednesday 16 February 2011] [10:54:34] <Steve-o>	well a common solution I have seen to that is to install the dependent library in a sub-directory of the product build instead of the OS preferred location
| [Wednesday 16 February 2011] [10:55:31] <mikko>	but distros dont like rpath 
| [Wednesday 16 February 2011] [10:55:38] <Steve-o>	For convenience prefer static libraries but allow distributions to use shared libraries.
| [Wednesday 16 February 2011] [10:55:58] <Steve-o>	so out of the tarball build libpgm.a but allow configure options for libpgm.so
| [Wednesday 16 February 2011] [10:56:20] <mikko>	but how to use the libpgm.a ?
| [Wednesday 16 February 2011] [10:56:35] <mikko>	.a inside .so is not really portable
| [Wednesday 16 February 2011] [10:56:55] <Steve-o>	really?  where isn't it valid?
| [Wednesday 16 February 2011] [10:57:11] <mikko>	i can check, i did a lot of googling on this
| [Wednesday 16 February 2011] [11:01:24] <mikko>	hp-ux seems to be one
| [Wednesday 16 February 2011] [11:01:31] <mikko>	is that even supported by openpgm?
| [Wednesday 16 February 2011] [11:01:55] <Steve-o>	not yet
| [Wednesday 16 February 2011] [11:02:03] <mikko>	Libtool convenience library
| [Wednesday 16 February 2011] [11:02:07] <mikko>	sounds like a solution
| [Wednesday 16 February 2011] [11:02:09] <mikko>	http://sourceware.org/autobook/autobook/autobook_92.html
| [Wednesday 16 February 2011] [11:02:24] <mikko>	groups together a set of object files
| [Wednesday 16 February 2011] [11:02:30] <Steve-o>	that's what zeromq is using now
| [Wednesday 16 February 2011] [11:03:06] <mikko>	but on different side of the fence
| [Wednesday 16 February 2011] [11:04:09] <Steve-o>	let me read up on HPUX, v10 was fine as I remember they broke various things with 11
| [Wednesday 16 February 2011] [11:04:35] <mikko>	Steve-o: how does bundling convenience lib on openpgm side sound like?
| [Wednesday 16 February 2011] [11:04:42] <mikko>	and then zeromq links that
| [Wednesday 16 February 2011] [11:04:56] <mikko>	i could at least investigate this as it seems like a portable option
| [Wednesday 16 February 2011] [11:05:46] <Steve-o>	ok, if you can provide the code, I'm not sure how this is supposed to work with two different projects
| [Wednesday 16 February 2011] [11:06:10] <mikko>	the ultimate goal i guess is to have both as shared libraries provided by distros
| [Wednesday 16 February 2011] [11:06:19] <mikko>	but in the meanwhile convenience lib sounds ok
| [Wednesday 16 February 2011] [11:06:26] <mikko>	i'll put this on my ever growing todo list
| [Wednesday 16 February 2011] [11:07:04] <mikko>	at least i got ZFL code coverage working today
| [Wednesday 16 February 2011] [11:08:06] <Steve-o>	using gcov?
| [Wednesday 16 February 2011] [11:08:55] <mikko>	yes
| [Wednesday 16 February 2011] [11:09:25] <mikko>	http://build.valokuva.org/job/test-gcov/7/cobertura/_default_/
| [Wednesday 16 February 2011] [11:12:40] <Steve-o>	nice, it's tedious getting those percentages higher though
| [Wednesday 16 February 2011] [11:13:50] <mikko>	true. you would almost need to preload a malloc implementation that fails randomly
| [Wednesday 16 February 2011] [11:13:54] <mikko>	to test all asserts
| [Wednesday 16 February 2011] [11:14:04] <mikko>	and even then it would be very random
| [Wednesday 16 February 2011] [11:15:00] <mikko>	might add same thing for zeromq later as well
| [Wednesday 16 February 2011] [11:17:08] <cremes>	pieterh: ping... where is "zhelpers.h"? i can't compile your mailbugz.c test without it
| [Wednesday 16 February 2011] [11:18:04] <pieterh_>	cremes: sorry!
| [Wednesday 16 February 2011] [11:18:11] <pieterh_>	adding it now
| [Wednesday 16 February 2011] [11:18:12] <sustrik>	cremes, just replace it with zmq.h
| [Wednesday 16 February 2011] [11:18:21] <pieterh_>	sustrik: nope, that and other stuff
| [Wednesday 16 February 2011] [11:18:27] <sustrik>	there's nothing used from zhelpers.h in the code
| [Wednesday 16 February 2011] [11:18:39] <sustrik>	i've just compiled it
| [Wednesday 16 February 2011] [11:18:50] <sustrik>	aha
| [Wednesday 16 February 2011] [11:18:59] <sustrik>	replace the line with:
| [Wednesday 16 February 2011] [11:18:59] <sustrik>	#include <zmq.h>
| [Wednesday 16 February 2011] [11:19:00] <sustrik>	#include <stdio.h>
| [Wednesday 16 February 2011] [11:19:00] <sustrik>	#include <string.h>
| [Wednesday 16 February 2011] [11:19:03] <sustrik>	that works
| [Wednesday 16 February 2011] [11:19:16] <pieterh_>	yes, that works
| [Wednesday 16 February 2011] [11:21:30] <Steve-o>	mikko: ok so I already have the libtool convenience library libpgm.la, libtool is giving me the shared and static libraries for free
| [Wednesday 16 February 2011] [11:22:09] <mikko>	Steve-o: i know, but if you link against the .la from zeromq it gives a a warning "Warning: libpgm.la won't be deployed"
| [Wednesday 16 February 2011] [11:22:14] <mikko>	not sure if that can be ignored
| [Wednesday 16 February 2011] [11:22:29] <mikko>	maybe it can
| [Wednesday 16 February 2011] [11:22:35] <Steve-o>	is that because of a noinst_ line?
| [Wednesday 16 February 2011] [11:23:24] <mikko>	i got a local branch here
| [Wednesday 16 February 2011] [11:23:43] <pieterh_>	sustrik, in the pubsub pattern it is IMO a design flaw that zmq_connect is asynchronous
| [Wednesday 16 February 2011] [11:23:51] <mikko>	Steve-o: https://gist.github.com/3f14f1a3f816df3016c7
| [Wednesday 16 February 2011] [11:23:59] <mikko>	these are some of the changes related to zeromq
| [Wednesday 16 February 2011] [11:24:04] <pieterh_>	that is, on a sub socket
| [Wednesday 16 February 2011] [11:25:08] <mikko>	Steve-o: i tested that with ./configure --without-documentation --with-pgm=/tmp/to/pgm-trunk
| [Wednesday 16 February 2011] [11:28:23] <Steve-o>	mikko: I can't find anything on that error message in google
| [Wednesday 16 February 2011] [11:29:19] <sustrik>	pieterh_: why so?
| [Wednesday 16 February 2011] [11:32:59] <zedas>	sustrik: yep that's linux. why?
| [Wednesday 16 February 2011] [11:33:22] <sustrik>	there are 2 implementations of zmq_poll
| [Wednesday 16 February 2011] [11:33:38] <sustrik>	i was just checking which one to have a look at
| [Wednesday 16 February 2011] [11:34:25] <sustrik>	anyway, what's the problem you were referring to?
| [Wednesday 16 February 2011] [11:35:18] <sustrik>	ah, the EAGAINs in strace
| [Wednesday 16 February 2011] [11:35:37] <Steve-o>	mikko: maybe I need to explicitly add a noinst_LTLIBRARIES instead of lib_LTLIBRARIES
| [Wednesday 16 February 2011] [11:35:38] <sustrik>	i've missed the link, sorry
| [Wednesday 16 February 2011] [11:36:04] <cremes>	pieterh_: i don't compile a lot of C programs; what's the gcc line to get the example to compile & link?
| [Wednesday 16 February 2011] [11:37:29] <cremes>	nm, got it
| [Wednesday 16 February 2011] [11:38:09] <mikko>	Steve-o: gimme a sec
| [Wednesday 16 February 2011] [11:38:16] <mikko>	getting the exact error message out
| [Wednesday 16 February 2011] [11:40:53] <pieterh_>	cremes: sorry, my irc client's not alerting me for some reason
| [Wednesday 16 February 2011] [11:41:20] <cremes>	no worries; i compiled the program and ran it successfully
| [Wednesday 16 February 2011] [11:41:23] <cremes>	no failures
| [Wednesday 16 February 2011] [11:41:37] <cremes>	so my hypothesis must be wrong as to the cause of the mailbox assertion
| [Wednesday 16 February 2011] [11:41:49] <pieterh_>	at least it's not that simple
| [Wednesday 16 February 2011] [11:42:22] <cremes>	right
| [Wednesday 16 February 2011] [11:42:24] <pieterh_>	assuming I got the case right
| [Wednesday 16 February 2011] [11:42:32] <pieterh_>	5M writes, 5M reads...
| [Wednesday 16 February 2011] [11:42:39] <cremes>	you got it right as i explained it
| [Wednesday 16 February 2011] [11:42:46] <pieterh_>	sustrik: sorry also, I'm not getting beeps... 
| [Wednesday 16 February 2011] [11:42:56] <pieterh_>	pubsub fails, for every new user, in the same way
| [Wednesday 16 February 2011] [11:43:14] <pieterh_>	subscriber connects, then misses X milliseconds of messages 
| [Wednesday 16 February 2011] [11:43:25] <sustrik>	ack
| [Wednesday 16 February 2011] [11:43:36] <pieterh_>	i'm not sure doing a synchronous connect would make any difference
| [Wednesday 16 February 2011] [11:43:49] <sustrik>	it probably won't
| [Wednesday 16 February 2011] [11:43:49] <cremes>	pieterh_: is it possible to run this under gdb and have it drop into the debugger instead of asserting?
| [Wednesday 16 February 2011] [11:43:51] <pieterh_>	but there is definitely a problem when every user hits the same issue
| [Wednesday 16 February 2011] [11:44:02] <cremes>	if so, perhaps i could dump the contents of the mailbox?
| [Wednesday 16 February 2011] [11:44:24] <pieterh_>	cremes, afaik usual tactic is to get a core dump and then debug from there
| [Wednesday 16 February 2011] [11:44:31] <pieterh_>	i'm no gdb expert
| [Wednesday 16 February 2011] [11:44:37] 	 * pieterh_ likes printfs
| [Wednesday 16 February 2011] [11:44:39] <cremes>	ok, how can i force it to core?
| [Wednesday 16 February 2011] [11:44:47] <sustrik>	cremes: p
| [Wednesday 16 February 2011] [11:44:50] <pieterh_>	divide by zero?
| [Wednesday 16 February 2011] [11:45:14] <sustrik>	when you want to dump the content of variable x, type "p x"
| [Wednesday 16 February 2011] [11:45:17] <pieterh_>	assertion failure will produce a core I think
| [Wednesday 16 February 2011] [11:45:28] <pieterh_>	you need to enable core dumps for your process
| [Wednesday 16 February 2011] [11:45:49] <pieterh_>	ulimit unlimited
| [Wednesday 16 February 2011] [11:45:50] <cremes>	yeah, right now i'm set for a core size of 0; i can change that
| [Wednesday 16 February 2011] [11:46:05] <cremes>	are you sure the assertion causes a core?
| [Wednesday 16 February 2011] [11:46:11] <sustrik>	cremes: just start the executable under gdb
| [Wednesday 16 February 2011] [11:46:27] <sustrik>	it will stop and get you gdb prompt when assertion is hit
| [Wednesday 16 February 2011] [11:46:29] <pieterh_>	yeah, and make sure it's compiled and linked for debugging
| [Wednesday 16 February 2011] [11:47:20] <cremes>	i did run it under gdb several times; the assertion would cause the ruby runtime to throw an exception and exit cleanly
| [Wednesday 16 February 2011] [11:47:31] <cremes>	so gdb never caught the issue
| [Wednesday 16 February 2011] [11:47:43] <cremes>	outside of gdb, it would assert
| [Wednesday 16 February 2011] [11:47:49] <cremes>	very frustrating
| [Wednesday 16 February 2011] [11:47:54] <sustrik>	:|
| [Wednesday 16 February 2011] [11:48:40] <pieterh_>	my brute force approach would be to add code to 0MQ that dumps the mailbox just before it asserts, under the same conditions
| [Wednesday 16 February 2011] [11:48:52] <pieterh_>	don't waste time trying to get debuggers working unless you already know how
| [Wednesday 16 February 2011] [11:49:11] <cremes>	i like that suggestion; any suggestion on how to dump the mailbox?
| [Wednesday 16 February 2011] [11:49:29] <sustrik>	cremes: i would do a bit different thing
| [Wednesday 16 February 2011] [11:49:31] <cremes>	i.e. are there important components to capture or should i just dump it as a string?
| [Wednesday 16 February 2011] [11:49:40] <cremes>	sustrik: talk to me
| [Wednesday 16 February 2011] [11:49:47] <sustrik>	just print some text when mailbox_t::send() is invoked
| [Wednesday 16 February 2011] [11:50:07] <sustrik>	in you scenario the number of invocations should be pretty modest
| [Wednesday 16 February 2011] [11:50:33] <sustrik>	if it starts printing a lot of text, there's definitely some problem there
| [Wednesday 16 February 2011] [11:50:45] <cremes>	sustrik: just any text like "mailbox.send!"
| [Wednesday 16 February 2011] [11:50:53] <sustrik>	yes
| [Wednesday 16 February 2011] [11:50:55] <cremes>	ok
| [Wednesday 16 February 2011] [11:51:14] <cremes>	so you don't care about the contents of the mailbox
| [Wednesday 16 February 2011] [11:51:37] <sustrik>	not really
| [Wednesday 16 February 2011] [11:51:44] <cremes>	ok, i'll try that now
| [Wednesday 16 February 2011] [11:51:52] <sustrik>	if we find out that there's a lot of commands is written
| [Wednesday 16 February 2011] [11:52:04] <sustrik>	we'll have a look at what kind of commands is that
| [Wednesday 16 February 2011] [12:10:53] <pieterh_>	mikko: I'm improving some of the coverage but it's always going to miss on assertions, apparently
| [Wednesday 16 February 2011] [12:15:09] <mikko>	pieterh_: yes
| [Wednesday 16 February 2011] [12:15:13] <mikko>	i dont think it calculates those
| [Wednesday 16 February 2011] [12:15:21] <pieterh_>	hey, my beep works now! :-) 
| [Wednesday 16 February 2011] [12:15:34] <mikko>	and 100% is not really a realistic or even desirable aim
| [Wednesday 16 February 2011] [12:15:41] <mikko>	Steve-o: i think i solved it
| [Wednesday 16 February 2011] [12:15:43] <pieterh_>	ok, I'll improve some of the coverage but like Steve-o says, it gets messy
| [Wednesday 16 February 2011] [12:16:34] <mikko>	Steve-o: almost. now it compiles twice it seems
| [Wednesday 16 February 2011] [12:17:30] <ianbarber>	just to be doubly sure
| [Wednesday 16 February 2011] [12:18:16] <ianbarber>	compare the two, and if they're different fail on a non-deterministic build process
| [Wednesday 16 February 2011] [12:25:35] <cremes>	sustrik: yes, there are a *lot* of commands sent
| [Wednesday 16 February 2011] [12:25:53] <sustrik>	ok
| [Wednesday 16 February 2011] [12:25:53] <cremes>	what's the next step? dump the commands when the mailbox buffer is increased?
| [Wednesday 16 February 2011] [12:26:06] <sustrik>	can you print out cmd->type?
| [Wednesday 16 February 2011] [12:26:19] <sustrik>	that will show what kind of commands are being passed
| [Wednesday 16 February 2011] [12:26:30] <cremes>	sure; on every invocation or just when the buffer size is increased?
| [Wednesday 16 February 2011] [12:26:43] <sustrik>	on every invocation
| [Wednesday 16 February 2011] [12:26:46] <cremes>	ok
| [Wednesday 16 February 2011] [12:28:45] <cremes>	sustrik: i see it's defined as an enum so i can use printf("%d", cmd->type), yes?
| [Wednesday 16 February 2011] [12:29:28] <sustrik>	printf("%d", (int) cmd->type)
| [Wednesday 16 February 2011] [12:29:30] <sustrik>	just in case
| [Wednesday 16 February 2011] [12:29:38] <cremes>	k
| [Wednesday 16 February 2011] [12:31:52] <cremes>	sustrik: mailbox.cpp:158:34: error: base operand of '->' has non-pointer type 'const zmq::command_t'
| [Wednesday 16 February 2011] [12:32:02] <cremes>	??
| [Wednesday 16 February 2011] [12:32:16] <sustrik>	it should be cmd_.type
| [Wednesday 16 February 2011] [12:32:17] <sustrik>	sorry
| [Wednesday 16 February 2011] [12:34:37] <cremes>	clean compile; running now
| [Wednesday 16 February 2011] [12:37:07] <cremes>	sustrik: here's a sampling of what i see; the cmd is wrapped in TY(cmd) so i can pick it out of the log easily
| [Wednesday 16 February 2011] [12:37:08] <cremes>	https://gist.github.com/829782
| [Wednesday 16 February 2011] [12:39:51] <sustrik>	do you call connect or bind in that app?
| [Wednesday 16 February 2011] [12:40:40] <cremes>	i call both early on during setup, then i don't need to call it again
| [Wednesday 16 February 2011] [12:41:01] <sustrik>	ah, both are in the same process
| [Wednesday 16 February 2011] [12:41:02] <sustrik>	i see
| [Wednesday 16 February 2011] [12:41:12] <sustrik>	what transport do you use?
| [Wednesday 16 February 2011] [12:41:18] <sustrik>	tcp? inproc? ipc?
| [Wednesday 16 February 2011] [12:41:29] <cremes>	tcp
| [Wednesday 16 February 2011] [12:42:27] <sustrik>	cremes: can you printf something in connect_sessio_t::detached() function?
| [Wednesday 16 February 2011] [12:42:35] <cremes>	yes
| [Wednesday 16 February 2011] [12:42:59] <sustrik>	(that wey we'll see if there a lot of reconnecting happening)
| [Wednesday 16 February 2011] [12:47:35] <cremes>	sustrik: [cremes@box1 servers]$ grep ^REC t.out | wc -l
| [Wednesday 16 February 2011] [12:47:35] <cremes>	921674
| [Wednesday 16 February 2011] [12:47:43] <cremes>	so yes, lots of reconnects
| [Wednesday 16 February 2011] [12:51:37] <cremes>	this is a threaded app writing to the same logfile so sequence is a bit suspect
| [Wednesday 16 February 2011] [12:52:01] <cremes>	however, it appears each REC is always followed by command type 1 or 3 (plug or attach) which kind of makes sense
| [Wednesday 16 February 2011] [12:56:32] <sustrik>	yep
| [Wednesday 16 February 2011] [12:56:43] <sustrik>	the question is: why does it reconnect at all?
| [Wednesday 16 February 2011] [12:57:08] <sustrik>	moreover, the default reconnect interval is 0.1 sec
| [Wednesday 16 February 2011] [12:57:14] <cremes>	agreed; all transport strings are of the form 'tcp://127.0.0.1:<port>'
| [Wednesday 16 February 2011] [12:57:33] <sustrik>	so to get 921675 would require couple of days
| [Wednesday 16 February 2011] [12:58:00] <sustrik>	you mean: "both" rather than "all", right?
| [Wednesday 16 February 2011] [12:59:04] <cremes>	there is a PUB producer, a FORWARDER device, and multiple SUB consumers in this process
| [Wednesday 16 February 2011] [12:59:30] <cremes>	they all connect up in the beginning and should never close/reconnect for the life of the program
| [Wednesday 16 February 2011] [12:59:58] <cremes>	so each one has its own transport connection string; that's what i meant by 'all'
| [Wednesday 16 February 2011] [13:00:12] <sustrik>	i see
| [Wednesday 16 February 2011] [13:00:39] <sustrik>	how many SUBs?
| [Wednesday 16 February 2011] [13:01:59] <cremes>	let's see... 
| [Wednesday 16 February 2011] [13:02:18] <sustrik>	approximately...
| [Wednesday 16 February 2011] [13:02:35] <sustrik>	tens, hundreds, thousands?
| [Wednesday 16 February 2011] [13:02:35] <cremes>	5 in the clients and 1 in the FORWARDER, so about 6 (i might be forgetting one or two)
| [Wednesday 16 February 2011] [13:02:47] <sustrik>	ok
| [Wednesday 16 February 2011] [13:03:32] <sustrik>	do you close the FORWARDER before closing the SUBs?
| [Wednesday 16 February 2011] [13:04:47] <cremes>	they should all terminate at roughly the same time when i interrupt/kill the program
| [Wednesday 16 February 2011] [13:04:56] <sustrik>	ok
| [Wednesday 16 February 2011] [13:05:02] <cremes>	otherwise, the FORWARDER never exits
| [Wednesday 16 February 2011] [13:05:10] <sustrik>	does FORWARDER connect to SUBs or other way round?
| [Wednesday 16 February 2011] [13:05:32] <cremes>	FORWARDER binds while all clients connect
| [Wednesday 16 February 2011] [13:05:50] <sustrik>	what about PUB?
| [Wednesday 16 February 2011] [13:05:50] <cremes>	actually, the IN/OUT sockets on the FORWARDER always bind
| [Wednesday 16 February 2011] [13:06:00] <cremes>	the publisher connects too as a result
| [Wednesday 16 February 2011] [13:06:03] <sustrik>	ok
| [Wednesday 16 February 2011] [13:06:39] <sustrik>	hm, i see no reason then for reconnections to happen
| [Wednesday 16 February 2011] [13:06:57] <sustrik>	are you 100% that the connection strings match?
| [Wednesday 16 February 2011] [13:07:09] <cremes>	match in what way?
| [Wednesday 16 February 2011] [13:07:24] <cremes>	they are all tcp?
| [Wednesday 16 February 2011] [13:07:28] <sustrik>	are they the same on bind and connect side?
| [Wednesday 16 February 2011] [13:07:50] <cremes>	if they weren't, the data wouldn't flow through my app, yes?
| [Wednesday 16 February 2011] [13:08:00] 	 * cremes checks anyway...
| [Wednesday 16 February 2011] [13:08:11] <sustrik>	ah, the data flow through 
| [Wednesday 16 February 2011] [13:08:13] <sustrik>	i see
| [Wednesday 16 February 2011] [13:08:19] <sustrik>	to all 5 subs?
| [Wednesday 16 February 2011] [13:09:02] <cremes>	yes, the main PUB broadcasts and the 5 subs each sub to everything
| [Wednesday 16 February 2011] [13:09:32] <sustrik>	and all of them actually get the data
| [Wednesday 16 February 2011] [13:09:35] <cremes>	if they weren't getting the data, the app would lock (and produce something similar to EFSM in my code)
| [Wednesday 16 February 2011] [13:09:43] <sustrik>	ok, good
| [Wednesday 16 February 2011] [13:09:57] <cremes>	it's kind of like an election algo
| [Wednesday 16 February 2011] [13:10:04] <sustrik>	to be frank, i have no idea what's going on there
| [Wednesday 16 February 2011] [13:10:11] <sustrik>	if the reconnections happen
| [Wednesday 16 February 2011] [13:10:24] <sustrik>	one would expect that at least some messages would be lost
| [Wednesday 16 February 2011] [13:10:50] <cremes>	any idea how i can do 900k reconnects in a few minutes?
| [Wednesday 16 February 2011] [13:10:58] <sustrik>	no idea
| [Wednesday 16 February 2011] [13:11:07] <cremes>	<sigh>
| [Wednesday 16 February 2011] [13:11:12] <sustrik>	have you changed the default RECONNECT_IVL?
| [Wednesday 16 February 2011] [13:11:30] <cremes>	btw, i ran pieter's mailbugz code with these debug prints in them and it barely puts out anything at all
| [Wednesday 16 February 2011] [13:11:41] <sustrik>	exactly
| [Wednesday 16 February 2011] [13:11:41] <cremes>	nope, no changes to RECONNECT_IVL
| [Wednesday 16 February 2011] [13:12:21] <cremes>	all sockets are allocated in their default state; the one exception is calling setsockopt on the SUBs to set their subscription string
| [Wednesday 16 February 2011] [13:12:27] <cremes>	and i always set my own IDENTITY
| [Wednesday 16 February 2011] [13:12:52] <cremes>	someone on the ML suggested a potential IDENTITY collision; could that be related?
| [Wednesday 16 February 2011] [13:13:03] <sustrik>	maybe
| [Wednesday 16 February 2011] [13:13:13] <sustrik>	do you have identity collisions there?
| [Wednesday 16 February 2011] [13:13:23] <sustrik>	like all 5 subs having the same identity?
| [Wednesday 16 February 2011] [13:13:57] <cremes>	i shouldn't; the identity is always <random id>.<sock type>.<server type> where random id is 0 to 999_999_999
| [Wednesday 16 February 2011] [13:14:11] <cremes>	it's *possible* there is a collision but *improbable*
| [Wednesday 16 February 2011] [13:14:55] <sustrik>	try printing them out
| [Wednesday 16 February 2011] [13:15:40] <cremes>	i'm auditing that right now; give me 5m
| [Wednesday 16 February 2011] [13:22:47] <pieterh_>	cremes, are you sure you're initializing your random number generator?
| [Wednesday 16 February 2011] [13:22:57] <pieterh_>	if not, every client will produce an identical 'random' sequence
| [Wednesday 16 February 2011] [13:23:48] <pieterh_>	cremes: if you're getting reconnects, presumably you're also getting disconnects
| [Wednesday 16 February 2011] [13:23:57] <pieterh_>	and if you can find those, you can find what is causing them
| [Wednesday 16 February 2011] [13:24:13] <pieterh_>	sustrik: how many places does 0MQ forcefully disconnect a subscriber socket without assertion
| [Wednesday 16 February 2011] [13:24:23] <pieterh_>	do we have the sys: transport working?
| [Wednesday 16 February 2011] [13:24:57] 	 * pieterh_ bets 1c that this is a subscriber identity issue, and 0MQ is disconnecting subscribers massively but the error is never reported
| [Wednesday 16 February 2011] [13:26:14] <sustrik>	pieterh_: every time the other side does something unexpected
| [Wednesday 16 February 2011] [13:26:21] <sustrik>	such as sending malformed frame
| [Wednesday 16 February 2011] [13:26:28] <pieterh_>	yeah, but are there lots of places in the code?
| [Wednesday 16 February 2011] [13:26:44] <sustrik>	not much, 3-4 i think
| [Wednesday 16 February 2011] [13:26:56] <pieterh_>	right... so a few well-placed prints and we'll know what's happening
| [Wednesday 16 February 2011] [13:26:57] <sustrik>	sys: works
| [Wednesday 16 February 2011] [13:27:08] <sustrik>	and should be used exactly for this kind of thing
| [Wednesday 16 February 2011] [13:27:18] <pieterh_>	precisely
| [Wednesday 16 February 2011] [13:27:32] <sustrik>	the only problem is that some kind of throttling
| [Wednesday 16 February 2011] [13:27:38] <sustrik>	not to get the log overloaded
| [Wednesday 16 February 2011] [13:27:50] <pieterh_>	presumably all we care about are the first 10 messages
| [Wednesday 16 February 2011] [13:27:53] <sustrik>	i.e. if the same problem happens over and over again
| [Wednesday 16 February 2011] [13:27:57] <sustrik>	in 10us intevals
| [Wednesday 16 February 2011] [13:28:09] <sustrik>	only the fist one should be reported
| [Wednesday 16 February 2011] [13:28:19] <pieterh_>	add a numeric code and ignore duplicates, standard solution
| [Wednesday 16 February 2011] [13:28:37] <sustrik>	you need some kind of state machine
| [Wednesday 16 February 2011] [13:29:06] <sustrik>	if connecting fails happens log it a switch to "no log" state
| [Wednesday 16 February 2011] [13:29:10] <cremes>	alas, it looks to me like they are all unique:  https://gist.github.com/829865
| [Wednesday 16 February 2011] [13:29:21] <sustrik>	any subsequent connect failures are not logged
| [Wednesday 16 February 2011] [13:29:32] <cremes>	interestingly, out of all 4 components, only the one that crashes shows the hundreds of thousands of reconnects
| [Wednesday 16 February 2011] [13:29:34] <sustrik>	when connecting succeeds, switch back to "log" state
| [Wednesday 16 February 2011] [13:29:55] <sustrik>	thus making next disconnect being logged
| [Wednesday 16 February 2011] [13:30:12] <pieterh_>	you don't need anything that complex IMO
| [Wednesday 16 February 2011] [13:30:22] <pieterh_>	if you get more than 1000 alerts on sys: you can give up
| [Wednesday 16 February 2011] [13:30:34] <pieterh_>	(in a minute, hour, day_)
| [Wednesday 16 February 2011] [13:30:54] <pieterh_>	cremes, you may want to add prints in the places 0MQ *disconnects* subscribers
| [Wednesday 16 February 2011] [13:31:11] <sustrik>	cremes: no more ideas, i need a minimal test case
| [Wednesday 16 February 2011] [13:31:25] <sustrik>	to reproduce it here
| [Wednesday 16 February 2011] [13:31:30] <cremes>	ok, i'll keep poking at it
| [Wednesday 16 February 2011] [13:32:23] <pieterh_>	sustrik, can you tell cremes where those 3-4 places are?
| [Wednesday 16 February 2011] [13:32:45] <sustrik>	hm, i don't know precisely
| [Wednesday 16 February 2011] [13:32:55] <sustrik>	dhammika have supplied those patches
| [Wednesday 16 February 2011] [13:33:13] <pieterh_>	it used to be easy 'egrep assert *.cpp'
| [Wednesday 16 February 2011] [13:33:13] <sustrik>	maybe check the commit log
| [Wednesday 16 February 2011] [13:33:36] <sustrik>	?
| [Wednesday 16 February 2011] [13:33:54] <sustrik>	it's not asserting, it's closing the connections
| [Wednesday 16 February 2011] [13:36:08] <cremes>	this conversation gave me an idea... i think i am narrowing it down... give me 10m
| [Wednesday 16 February 2011] [13:36:59] <pieterh_>	sustrik, I meant, it *used* to assert and I remember several times chasing down framing errors by sticking printfs into those places
| [Wednesday 16 February 2011] [13:38:15] <sustrik>	these assert have been removed via your "0MQ competition" :)
| [Wednesday 16 February 2011] [13:46:09] <cremes>	sustrik, pieterh_: found it!
| [Wednesday 16 February 2011] [13:46:17] <pieterh_>	:-)
| [Wednesday 16 February 2011] [13:46:28] <cremes>	i had a duplicate identity on an unrelated XREQ socket!
| [Wednesday 16 February 2011] [13:46:33] <pieterh_>	yay!
| [Wednesday 16 February 2011] [13:47:06] <cremes>	to reproduce, it's probably just these steps...
| [Wednesday 16 February 2011] [13:47:14] <pieterh_>	sustrik, does zmq already send anything to sys:?
| [Wednesday 16 February 2011] [13:47:17] <cremes>	1. create a QUEUE device that binds to some port
| [Wednesday 16 February 2011] [13:47:23] <sustrik>	pieterh_: no
| [Wednesday 16 February 2011] [13:47:37] <cremes>	2. create two XREQ (REQ too?) sockets, set their identity the same and connect them to the QUEUE
| [Wednesday 16 February 2011] [13:47:48] <cremes>	3. check for reconnects
| [Wednesday 16 February 2011] [13:48:01] <cremes>	4. Maybe need to send some data through first...?
| [Wednesday 16 February 2011] [13:48:10] <pieterh_>	cremes: I'll make a test case later on
| [Wednesday 16 February 2011] [13:48:28] <cremes>	ok, thanks pieter! your c skills far exceed my own
| [Wednesday 16 February 2011] [13:48:51] <pieterh_>	what do you mean by 'check for reconnects'?
| [Wednesday 16 February 2011] [13:48:53] <cremes>	thank you both so much for working through this with me; this conversation solved it
| [Wednesday 16 February 2011] [13:49:08] <pieterh_>	i'd like to get a test case that results in a crash
| [Wednesday 16 February 2011] [13:49:33] <cremes>	i added a debug statement to connect_session.cpp:detach to print whenever it detached and attempted a reconnect
| [Wednesday 16 February 2011] [13:50:00] <cremes>	let me try to write one in ruby
| [Wednesday 16 February 2011] [13:50:09] <pieterh_>	this still does not explain why the mailbox exploded...
| [Wednesday 16 February 2011] [13:50:14] <cremes>	then i can tell you exactly what needs to be done in c
| [Wednesday 16 February 2011] [13:50:20] <pieterh_>	yes, make a ruby test case, that's perfect
| [Wednesday 16 February 2011] [13:50:34] <pieterh_>	exploding mailbox gets double score
| [Wednesday 16 February 2011] [13:50:53] <pieterh_>	sustrik: we should start to send stuff to sys: where we used to assert
| [Wednesday 16 February 2011] [13:51:16] <pieterh_>	if you can document how to use sys: from inside zmq I can try that
| [Wednesday 16 February 2011] [13:51:35] <pieterh_>	ideally, a 1-liner that sends a string... :-)
| [Wednesday 16 February 2011] [13:52:01] <pieterh_>	then we can apply that to cremes test case and check that we'd have caught this error 
| [Wednesday 16 February 2011] [13:52:22] <sustrik>	log ();
| [Wednesday 16 February 2011] [13:52:29] <sustrik>	it's ther
| [Wednesday 16 February 2011] [13:52:30] <sustrik>	e
| [Wednesday 16 February 2011] [13:53:13] <pieterh_>	ah, it requires all the work of creating a message first
| [Wednesday 16 February 2011] [13:53:19] <pieterh_>	that's tedious
| [Wednesday 16 February 2011] [13:54:03] <pieterh_>	do we have a standardized format for sys://log messages?
| [Wednesday 16 February 2011] [13:54:49] <pieterh_>	sorry to complain but if this was packaged somewhat, it'd be easier for people to use it internally
| [Wednesday 16 February 2011] [13:55:01] <sustrik>	no format
| [Wednesday 16 February 2011] [13:55:06] <sustrik>	just use string atm
| [Wednesday 16 February 2011] [13:55:23] <sustrik>	we can polish the format later on
| [Wednesday 16 February 2011] [13:55:46] <pieterh_>	every single object has a log method?
| [Wednesday 16 February 2011] [13:56:22] <pieterh_>	inherited from object_t?
| [Wednesday 16 February 2011] [13:56:27] <sustrik>	yes
| [Wednesday 16 February 2011] [13:56:38] <pieterh_>	so the log method there could be somewhat expanded to take a string and create/destroy the msg itself
| [Wednesday 16 February 2011] [13:57:00] <pieterh_>	afaics we don't use this anywhere yet
| [Wednesday 16 February 2011] [13:57:11] <sustrik>	sure
| [Wednesday 16 February 2011] [13:57:18] <pieterh_>	and then we need a documented parsable format for messages
| [Wednesday 16 February 2011] [13:57:23] <pieterh_>	minimal
| [Wednesday 16 February 2011] [13:57:32] <pieterh_>	easy to improve later
| [Wednesday 16 February 2011] [13:57:40] <sustrik>	ack
| [Wednesday 16 February 2011] [13:57:57] <pieterh_>	ok, I'll try my hand at this, apologies in advance...
| [Wednesday 16 February 2011] [14:11:34] <cremes>	yes! i have a reproducible crasher in ruby!
| [Wednesday 16 February 2011] [14:12:10] <cremes>	pieterh_: do you want the ruby code or an explanation for translation to c?
| [Wednesday 16 February 2011] [14:12:49] <pieterh_>	cremes, I think we need to log two issues here
| [Wednesday 16 February 2011] [14:13:11] <cremes>	ok, i can create the issues, but i only see one
| [Wednesday 16 February 2011] [14:13:14] <pieterh_>	(a) lack of any warning to the app developer
| [Wednesday 16 February 2011] [14:13:18] <pieterh_>	(b) mailbox crash
| [Wednesday 16 February 2011] [14:13:32] <pieterh_>	(b) is the critical one, and the ruby example will be valuable there
| [Wednesday 16 February 2011] [14:13:40] <cremes>	ok, so (a) is for tracking a new feature request to add the sys: stuff, yes?
| [Wednesday 16 February 2011] [14:13:44] <pieterh_>	yes
| [Wednesday 16 February 2011] [14:13:50] <cremes>	ok, i'll write them up
| [Wednesday 16 February 2011] [14:14:00] <pieterh_>	well, we don't track new feature requests, so perhaps skip (a)
| [Wednesday 16 February 2011] [14:14:36] <cremes>	i'll add it to the wiki 3.0/roadmap page
| [Wednesday 16 February 2011] [14:14:56] <pieterh_>	i'm working on it now... :-)
| [Wednesday 16 February 2011] [14:15:11] <cremes>	ok!
| [Wednesday 16 February 2011] [14:27:12] <cremes>	pieterh_: preview this issue and let me know if you need more details to reproduce in c:  https://github.com/zeromq/zeromq2/issues/165
| [Wednesday 16 February 2011] [14:27:22] <pieterh_>	cremes, thanks!
| [Wednesday 16 February 2011] [14:27:49] <cremes>	pieterh_: i've spent the last 96 hours banging on this! i'm happy to see it solved!
| [Wednesday 16 February 2011] [14:28:27] <pieterh_>	that's why i'm doing the sys://log stuff, it's insane to lose so much time to a missing warning
| [Wednesday 16 February 2011] [14:28:54] <cremes>	honestly, i'm taking the rest of the day off.... i feel deflated
| [Wednesday 16 February 2011] [14:29:59] <pieterh_>	sustrik, what's the correct way to work with a msg in the zmq core?
| [Wednesday 16 February 2011] [14:30:13] <pieterh_>	::zmq_msg_t or is there a message class I'm missing?
| [Wednesday 16 February 2011] [14:39:18] <enleth>	Hello
| [Wednesday 16 February 2011] [14:39:59] <enleth>	mikko: is the API documentation at http://valokuva.org/~mikko/php-zmq/ supposed to be inaccessible?
| [Wednesday 16 February 2011] [14:46:14] <ianbarber>	enleth: check php.zero.mq
| [Wednesday 16 February 2011] [14:46:40] <ianbarber>	references probably need updating
| [Wednesday 16 February 2011] [14:50:55] <mikko>	enleth: yes
| [Wednesday 16 February 2011] [14:55:46] <enleth>	ianbarber: thanks, that's it.
| [Wednesday 16 February 2011] [14:56:17] <enleth>	mikko: can I suggest a 302 redirect to the new address?
| [Wednesday 16 February 2011] [14:56:26] <pieterh_>	cremes: still there?
| [Wednesday 16 February 2011] [14:56:44] <enleth>	The old one is all over the latest git tree
| [Wednesday 16 February 2011] [15:01:16] <mikko>	done
| [Wednesday 16 February 2011] [15:01:29] <cremes>	pieterh_: for a bit more; what's up?
| [Wednesday 16 February 2011] [15:01:48] <pieterh_>	just wondered if you need to actually use the REQ/REP sockets to create the crash
| [Wednesday 16 February 2011] [15:01:55] <pieterh_>	or just bind them and BOOM
| [Wednesday 16 February 2011] [15:02:20] <pieterh_>	s/bind/connect
| [Wednesday 16 February 2011] [15:02:25] <cremes>	let me see... give me 1m
| [Wednesday 16 February 2011] [15:03:26] <cremes>	pieterh_: nope, crashes without using them; good catch... it's even *more* reduced now
| [Wednesday 16 February 2011] [15:03:33] <pieterh_>	excellent...
| [Wednesday 16 February 2011] [15:03:37] <pieterh_>	thanks a lot
| [Wednesday 16 February 2011] [15:03:37] <cremes>	i'm no longer thinking clearly otherwise i would have tried that :)
| [Wednesday 16 February 2011] [15:04:50] <pieterh_>	it's been a long day :-)
| [Wednesday 16 February 2011] [15:04:51] <cremes>	pieterh_: looks like you *do* need the REQ socket too
| [Wednesday 16 February 2011] [15:05:03] <cremes>	a pair of REP's with the same ID is insufficient
| [Wednesday 16 February 2011] [15:05:16] <cremes>	it's been a long *week*
| [Wednesday 16 February 2011] [15:05:27] <pieterh_>	ack, you need a pair of sockets with one disconnecting the other
| [Wednesday 16 February 2011] [15:05:44] <pieterh_>	presumably, I'll test that, it applies to all relevant socket types 
| [Wednesday 16 February 2011] [15:05:56] <pieterh_>	it's been a long *year*!
| [Wednesday 16 February 2011] [15:05:58] <cremes>	perhaps...
| [Wednesday 16 February 2011] [15:05:59] <pieterh_>	hang on...
| [Wednesday 16 February 2011] [15:06:05] <pieterh_>	:-)
| [Wednesday 16 February 2011] [15:06:07] <cremes>	heh
| [Wednesday 16 February 2011] [15:10:09] <pieterh_>	cremes: bingo, I reproduced it!
| [Wednesday 16 February 2011] [15:10:23] <cremes>	awesome!
| [Wednesday 16 February 2011] [15:11:03] <cremes>	once started it only takes a few seconds to exhaust that buffer even when it's 5MB!
| [Wednesday 16 February 2011] [15:11:11] <pieterh_>	just connect two req sockets with same ID, wait 1 second...
| [Wednesday 16 February 2011] [15:11:17] <pieterh_>	I'm going to try with other socket types now
| [Wednesday 16 February 2011] [15:16:42] <pieterh_>	cremes: it affects all socket types
| [Wednesday 16 February 2011] [15:16:52] <pieterh_>	any combination of bind/connect, even pub connecting to sub
| [Wednesday 16 February 2011] [15:17:21] <cremes>	wow
| [Wednesday 16 February 2011] [15:17:46] <cremes>	this *might* explain a lot of people's problems; there are several issues open about this assertion
| [Wednesday 16 February 2011] [15:18:28] <pieterh_>	ironically 0MQ used to assert before :-)
| [Wednesday 16 February 2011] [15:18:51] <cremes>	oh, the irony... :(
| [Wednesday 16 February 2011] [15:19:25] <cremes>	well, i'm just glad it's no longer a mystery
| [Wednesday 16 February 2011] [15:19:38] <pieterh_>	anyhow, this makes it much easier to solve properly
| [Wednesday 16 February 2011] [15:19:42] <cremes>	other than this, i haven't hit an assertion in a long time
| [Wednesday 16 February 2011] [15:22:15] <pieterh_>	indeed, we had a competition to kill them :-)
| [Wednesday 16 February 2011] [17:30:32] <jol>	pieterh: nice talk at fosdem, I just watch it.
| [Wednesday 16 February 2011] [17:40:48] <Steve-o>	thx mikko
| [Wednesday 16 February 2011] [18:53:12] <dan___>	hello
| [Wednesday 16 February 2011] [18:53:16] <mikko>	hi
| [Wednesday 16 February 2011] [18:53:47] <dan___>	i've got a question about zmq
| [Wednesday 16 February 2011] [18:54:43] <mikko>	go ahead
| [Wednesday 16 February 2011] [18:54:52] <dan___>	is there any reason I should not be able to implement a pubsub connection with one side in python and the other in cpp over ipc?
| [Wednesday 16 February 2011] [18:55:33] <mikko>	no reason
| [Wednesday 16 February 2011] [18:55:39] <mikko>	should be perfectly ok
| [Wednesday 16 February 2011] [18:55:41] <dan___>	hm
| [Wednesday 16 February 2011] [18:56:05] <mikko>	you are not seeing any messages?
| [Wednesday 16 February 2011] [18:56:31] <dan___>	i see them when I use tcp, but not when i use ipc
| [Wednesday 16 February 2011] [18:56:38] <mikko>	can i see the code?
| [Wednesday 16 February 2011] [18:56:48] <dan___>	whats the best way to share it?
| [Wednesday 16 February 2011] [18:56:52] <dan___>	copy paste in here?
| [Wednesday 16 February 2011] [18:56:52] <mikko>	gist.github.com
| [Wednesday 16 February 2011] [18:57:48] <dan___>	sure - let me copy the code
| [Wednesday 16 February 2011] [19:01:17] <mikko>	did it work?
| [Wednesday 16 February 2011] [19:02:31] <dan___>	yeah
| [Wednesday 16 February 2011] [19:02:38] <dan___>	im trying to figure out how to "share it" lol
| [Wednesday 16 February 2011] [19:02:43] <mikko>	just the url
| [Wednesday 16 February 2011] [19:02:53] <dan___>	git@gist.github.com:2f8a0d953fa7c1acc7d6.git
| [Wednesday 16 February 2011] [19:03:06] <dan___>	https://gist.github.com/2f8a0d953fa7c1acc7d6
| [Wednesday 16 February 2011] [19:03:09] <mikko>	thanks
| [Wednesday 16 February 2011] [19:03:13] <mikko>	let me take a look
| [Wednesday 16 February 2011] [19:03:39] <mikko>	thats not the ipc one?
| [Wednesday 16 February 2011] [19:03:45] <dan___>	The Connections.cpp and Connections.py files define "Publisher" and "Subscriber" classes
| [Wednesday 16 February 2011] [19:03:52] <mikko>	what did you use as URI for the ipc?
| [Wednesday 16 February 2011] [19:04:09] <dan___>	there is an intermediate service on tcp that tells teh publisher and subscribers where to connect
| [Wednesday 16 February 2011] [19:05:18] <dan___>	ah crap i forgot the file for the intermediate name look-up...
| [Wednesday 16 February 2011] [19:05:30] <dan___>	the ipc names are just ipc://something.ipc
| [Wednesday 16 February 2011] [19:05:50] <dan___>	the publisher gets told to bind to both tcp and ipc ports
| [Wednesday 16 February 2011] [19:06:10] <mikko>	hmm
| [Wednesday 16 February 2011] [19:06:16] <dan___>	the subscriber gets told to bind to an ipc (if it is on the same machine as the publisher) or tcp if it is remote
| [Wednesday 16 February 2011] [19:06:19] <mikko>	are you running them on same directory?
| [Wednesday 16 February 2011] [19:06:32] <dan___>	... no
| [Wednesday 16 February 2011] [19:06:46] <mikko>	ipc:///tmp/test.ipc
| [Wednesday 16 February 2011] [19:06:55] <mikko>	that would be an absolute path to /tmp/test.ipc
| [Wednesday 16 February 2011] [19:07:08] <mikko>	ipc://something.ipc would be relative to the current working directory
| [Wednesday 16 February 2011] [19:07:15] <mikko>	notice the amount of slashes
| [Wednesday 16 February 2011] [19:07:20] <dan___>	ah ok that would make sense
| [Wednesday 16 February 2011] [19:07:34] <dan___>	let me try that
| [Wednesday 16 February 2011] [19:09:38] <dan___>	awesome
| [Wednesday 16 February 2011] [19:09:40] <dan___>	that worked
| [Wednesday 16 February 2011] [19:09:42] <dan___>	thanks
| [Wednesday 16 February 2011] [19:10:27] <mikko>	no problem
| [Wednesday 16 February 2011] [19:11:27] <dan___>	one other question i just thought of - what is the correct way to get a python subscriber to exit cleanly if it is stuck waiting on a recv()?
| [Wednesday 16 February 2011] [19:11:40] <dan___>	(like in SubTest.py) ?
| [Wednesday 16 February 2011] [19:13:27] <mikko>	ctrl + c doesnt work?
| [Wednesday 16 February 2011] [19:13:55] <dan___>	no - it seems to take kill -9
| [Wednesday 16 February 2011] [19:14:44] <mikko>	i don't really know about python that much
| [Wednesday 16 February 2011] [19:14:55] <mikko>	i think python might be eating the signal
| [Wednesday 16 February 2011] [19:14:55] <dan___>	lol neither do i
| [Wednesday 16 February 2011] [19:15:08] <dan___>	well thats why i tried putting the signal handler in
| [Wednesday 16 February 2011] [19:15:25] <dan___>	but it doesn't seem to have any effect
| [Wednesday 16 February 2011] [19:15:58] <mikko>	one option would be to use zmq poll
| [Wednesday 16 February 2011] [19:16:11] <mikko>	use a timeout on socket and after timeout check a flag or something
| [Wednesday 16 February 2011] [19:16:19] <mikko>	which you set in signal handler
| [Wednesday 16 February 2011] [19:16:38] <dan___>	that sounds reasonable
| [Wednesday 16 February 2011] [19:16:48] <dan___>	i have not used the poll feature yet
| [Wednesday 16 February 2011] [19:17:55] <dan___>	at any rate - thanks for your time and help!
| [Wednesday 16 February 2011] [19:19:00] <mikko>	no probs
| [Wednesday 16 February 2011] [19:19:11] <mikko>	its usually more lively in here around day time  (eu time)
| [Wednesday 16 February 2011] [19:19:30] <dan___>	ah - are you a contributer?
| [Wednesday 16 February 2011] [19:32:29] <sam`>	hi
| [Wednesday 16 February 2011] [19:32:52] <sam`>	going through the mailing list archives I read that a reliable pub/sub (with EPGM) would be as slow as the slowest subscriber
| [Wednesday 16 February 2011] [19:33:12] <sam`>	anyone has some insight on this, and on how to avoid it?
| [Wednesday 16 February 2011] [19:33:47] <sam`>	i'm looking at using 0MQ with an EPGM transport to distribute blobs of data (~100MB) to several hundred machines effeciently
| [Wednesday 16 February 2011] [19:34:30] <sam`>	but I can't figure out if that's the worst idea ever, or if it's actually efficient both speed-wise and network usage -wise
| [Wednesday 16 February 2011] [23:35:39] <rhino>	Hi, has anyone loaded jzmq into eclipse before?
| [Thursday 17 February 2011] [03:29:22] <yrashk>	I am confused again.. which erlzmq is supposed to be better? I have currently packaged official one (zeromq/erlzmq) into erlagner.org index.
| [Thursday 17 February 2011] [03:32:21] <sustrik>	there are several of them?
| [Thursday 17 February 2011] [03:32:59] <jugg>	imo http://github.com/csrl/erlzmq is more feature complete and stable.  The "official" version is useful for high volume 'sub' sockets, and playground use.  But is pretty buggy otherwise.
| [Thursday 17 February 2011] [03:34:11] <jugg>	disclaimer, 'csrl' is me.
| [Thursday 17 February 2011] [03:34:12] <sustrik>	anything tah zeromq/erlzmq has and csrl/erlzmq hasn't?
| [Thursday 17 February 2011] [03:34:16] <sustrik>	i know
| [Thursday 17 February 2011] [03:34:55] <yrashk>	sustrik: I am trying to understand what's the difference between csrl and zeromq
| [Thursday 17 February 2011] [03:35:02] <sustrik>	no idea
| [Thursday 17 February 2011] [03:35:09] <sustrik>	jugg should be able to explain
| [Thursday 17 February 2011] [03:35:10] <yrashk>	jugg: then I just sent you a message on github :)
| [Thursday 17 February 2011] [03:35:24] <jugg>	zeromq/erlzmq will actively push incoming data to the erlang process.  csrl/erlzmq won't.
| [Thursday 17 February 2011] [03:35:26] <yrashk>	would you mind checking it out?
| [Thursday 17 February 2011] [03:36:28] <sustrik>	yrashk: what message? i haven't got anything yet.
| [Thursday 17 February 2011] [03:36:40] <yrashk>	sustrik: no, I have sent it to hugg
| [Thursday 17 February 2011] [03:36:42] <yrashk>	jugg*
| [Thursday 17 February 2011] [03:36:58] <yrashk>	I wrote " jugg: then I just sent you a message on github :)" 
| [Thursday 17 February 2011] [03:37:07] <sustrik>	oops
| [Thursday 17 February 2011] [03:37:08] <sustrik>	:)
| [Thursday 17 February 2011] [03:37:11] <yrashk>	:]
| [Thursday 17 February 2011] [03:37:36] <sustrik>	jugg: i think there used to be both options, no?
| [Thursday 17 February 2011] [03:37:44] <jugg>	yrashk, sure, I'll do that.
| [Thursday 17 February 2011] [03:37:55] <sustrik>	iirc, something like "passive" flag
| [Thursday 17 February 2011] [03:37:55] <yrashk>	sustrik: I think zeromq/erlzmq has active option
| [Thursday 17 February 2011] [03:37:56] <jugg>	sustrik, yes, my version doesn't provide that option.
| [Thursday 17 February 2011] [03:38:02] <jugg>	'active' flag actually... 
| [Thursday 17 February 2011] [03:38:09] <sustrik>	aha
| [Thursday 17 February 2011] [03:38:21] <sustrik>	ok, any chance to merge the two implementations?
| [Thursday 17 February 2011] [03:38:28] <yrashk>	jugg: please let me know when you'll merge that patch in, I'll package your fork right after that
| [Thursday 17 February 2011] [03:38:36] <yrashk>	sustrik: that would be nice.. I guess
| [Thursday 17 February 2011] [03:38:39] <jugg>	yrashk, ok
| [Thursday 17 February 2011] [03:38:43] <yrashk>	less to manage for me :]
| [Thursday 17 February 2011] [03:39:34] <sustrik>	yrashk: are you an erlzmq maintainer?
| [Thursday 17 February 2011] [03:39:40] <jugg>	sustrik, the 'active' flag is only useful for subscription sockets.  If used on other sockets it is the source of problems.
| [Thursday 17 February 2011] [03:39:53] <yrashk>	sustrik: erlzmq.agner maintainer, it's just a "spec" package
| [Thursday 17 February 2011] [03:40:05] <sustrik>	i see
| [Thursday 17 February 2011] [03:40:35] <yrashk>	I am the guy behing erlagner.org operations, we're finally doing proper packaging system for erlang
| [Thursday 17 February 2011] [03:41:00] <sustrik>	ah, i've heard about it
| [Thursday 17 February 2011] [03:41:21] <sustrik>	not or erlang user myself though
| [Thursday 17 February 2011] [03:41:58] <jugg>	saleyn will not merge my changes unless I implement 'active' option support and a couple of other minor things.  But I don't have the time to do it correctly at this point, and I'm not interested in merging the implementation as is, given the issues surrounding it.
| [Thursday 17 February 2011] [03:42:14] <sustrik>	jugg: iirc active was introduced to allow erlzmq to work in non-lock-step fashion
| [Thursday 17 February 2011] [03:42:32] <yrashk>	this is why I'd prefer to package both official and jugg's versions
| [Thursday 17 February 2011] [03:42:41] <jugg>	yes, my implementation supports polling, which negates the need for it in that regards.
| [Thursday 17 February 2011] [03:42:56] <sustrik>	well, no way out at the moment
| [Thursday 17 February 2011] [03:43:22] <sustrik>	you may also consider adding new binding page to zeromq.org
| [Thursday 17 February 2011] [03:43:28] <sustrik>	there's a precedent:
| [Thursday 17 February 2011] [03:43:34] <sustrik>	there are 2 ruby bindings
| [Thursday 17 February 2011] [03:43:35] <jugg>	saleyn sites possible performance implications, however no actual testing has been done afaik.
| [Thursday 17 February 2011] [03:44:14] <yrashk>	how much is the slowdown on raw 0mq vs erlzmq btw?
| [Thursday 17 February 2011] [03:44:18] <yrashk>	on either binding
| [Thursday 17 February 2011] [03:44:33] <yrashk>	or, let me rephrase, how severe*
| [Thursday 17 February 2011] [03:44:53] <sustrik>	nobody really tested it, afaik
| [Thursday 17 February 2011] [03:44:55] <yrashk>	and erlzmq vs raw 0mq, to be more correct :]
| [Thursday 17 February 2011] [03:45:05] <yrashk>	heh
| [Thursday 17 February 2011] [03:45:08] <yrashk>	too bad
| [Thursday 17 February 2011] [03:45:19] <yrashk>	I am actually actively considering using erlzmq in one of the oncoming projects
| [Thursday 17 February 2011] [03:45:37] <sustrik>	testing it should be easy
| [Thursday 17 February 2011] [03:45:49] <sustrik>	there are C testing in /perf subdirectory
| [Thursday 17 February 2011] [03:46:10] <sustrik>	as for erlzmq, i don't know, but most bindings have /perf subdir as well
| [Thursday 17 February 2011] [03:46:33] <jugg>	A different comparison: I have two interfaces to my application, one native erlang, and another using erlzmq.  zeromq doesn't significantly add any overhead.
| [Thursday 17 February 2011] [03:46:33] <sustrik>	containing exactly the same tests
| [Thursday 17 February 2011] [03:46:52] <yrashk>	jugg: so it's just comparable?
| [Thursday 17 February 2011] [03:47:29] <yrashk>	I hoped it will be faster, lol :)
| [Thursday 17 February 2011] [03:47:44] <jugg>	native erlang vs erlzmq, yes comparable.
| [Thursday 17 February 2011] [03:47:46] <yrashk>	although of course it is unlikely to be faster
| [Thursday 17 February 2011] [03:47:46] <sustrik>	it's native erlang vs. 0mq; what you asked about is raw 0MQ from C vs. erlzmq
| [Thursday 17 February 2011] [03:47:55] <yrashk>	yeah I understand
| [Thursday 17 February 2011] [03:48:15] <yrashk>	I suppose raw 0mq is much, much faster
| [Thursday 17 February 2011] [03:48:37] <sustrik>	jugg: are there perf tests in erlzmq?
| [Thursday 17 February 2011] [03:48:44] 	 * sustrik is checking
| [Thursday 17 February 2011] [03:48:48] <yrashk>	sustrik: nope
| [Thursday 17 February 2011] [03:49:14] <sustrik>	than you may consider writing them, it's few lines of code
| [Thursday 17 February 2011] [03:49:18] <jugg>	no
| [Thursday 17 February 2011] [03:50:09] <yrashk>	sustrik: like porting https://github.com/zeromq/pyzmq/tree/master/perf ?
| [Thursday 17 February 2011] [03:50:23] <mikko>	good morning
| [Thursday 17 February 2011] [03:50:46] <sustrik>	morning
| [Thursday 17 February 2011] [03:50:59] <sustrik>	yrashk: these seem unnecessary complex
| [Thursday 17 February 2011] [03:51:12] <yrashk>	sustrik: do you have any other examples?
| [Thursday 17 February 2011] [03:51:53] <sustrik>	what about this:
| [Thursday 17 February 2011] [03:51:54] <sustrik>	https://github.com/zeromq/rbzmq/tree/master/perf
| [Thursday 17 February 2011] [03:52:18] <yrashk>	yup, quite simple
| [Thursday 17 February 2011] [04:02:48] <yrashk>	porting local_lat
| [Thursday 17 February 2011] [04:03:57] <yrashk>	hmmm erlzmq has no support for contexts
| [Thursday 17 February 2011] [04:03:58] <yrashk>	:)
| [Thursday 17 February 2011] [04:10:13] <sustrik>	doesn't matter, there a global context in the lib, i assume
| [Thursday 17 February 2011] [04:11:09] <sustrik>	btw, setting HWM in local_lat is superfluous
| [Thursday 17 February 2011] [04:11:26] <sustrik>	no idea how it got into ruby perf suite
| [Thursday 17 February 2011] [04:14:36] <yrashk>	lol
| [Thursday 17 February 2011] [04:14:43] <yrashk>	anyway I actually switched to porting _thr tests
| [Thursday 17 February 2011] [04:14:48] <sustrik>	ack
| [Thursday 17 February 2011] [04:14:51] <yrashk>	local_thr is done
| [Thursday 17 February 2011] [04:14:54] <sustrik>	lol
| [Thursday 17 February 2011] [04:14:57] <yrashk>	:D
| [Thursday 17 February 2011] [04:15:01] <sustrik>	you are fast
| [Thursday 17 February 2011] [04:15:02] <yrashk>	realtime progress, eh?
| [Thursday 17 February 2011] [04:18:54] <yrashk>	what size & count should I test it on?
| [Thursday 17 February 2011] [04:21:15] <yrashk>	I think official erlzmq is somewhat broken
| [Thursday 17 February 2011] [04:22:38] <jugg>	yrashk, pushed.
| [Thursday 17 February 2011] [04:22:58] <yrashk>	jugg: cool!
| [Thursday 17 February 2011] [04:23:24] <yrashk>	zeromq/erlzmq setsockopt doesn't work with the type of sockets socket/* create :S
| [Thursday 17 February 2011] [04:26:57] <yrashk>	aaand {error,einval} :-\
| [Thursday 17 February 2011] [04:29:47] <yrashk>	ok, I'll try to package jugg's fork now
| [Thursday 17 February 2011] [04:32:34] <yrashk>	done
| [Thursday 17 February 2011] [04:32:41] <yrashk>	it looks much cleaner
| [Thursday 17 February 2011] [04:35:37] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r28f3e87 10/ (5 files): 
| [Thursday 17 February 2011] [04:35:37] <CIA-21>	zeromq2: Add delay before reconnecting
| [Thursday 17 February 2011] [04:35:37] <CIA-21>	zeromq2: So far ZMQ_RECONNECT_IVL delay was used only when TCP connect
| [Thursday 17 February 2011] [04:35:37] <CIA-21>	zeromq2: failed. Now it is used even if connect succeeds and the peer
| [Thursday 17 February 2011] [04:35:37] <CIA-21>	zeromq2: closes the connection afterwards.
| [Thursday 17 February 2011] [04:35:38] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/i9iO9x
| [Thursday 17 February 2011] [04:36:17] <sustrik>	yrashk: any perf results?
| [Thursday 17 February 2011] [04:36:35] <sustrik>	use something like 1M messages, each 1B long
| [Thursday 17 February 2011] [04:39:21] <yrashk>	sustrik: almost there
| [Thursday 17 February 2011] [04:39:28] <yrashk>	sustrik: fixing last bugs
| [Thursday 17 February 2011] [04:39:37] <jugg>	yrashk, for those perf tests, if you run local/remote on the same node under the same zmq context, you'll be sharing a single port which could cause a bottleneck.  Either run them on separate nodes, or create two contexts, one for local, one for remote.  (Using a port per socket is a TODO item).
| [Thursday 17 February 2011] [04:40:22] <yrashk>	it is late in the night so I am not sure if my math is right
| [Thursday 17 February 2011] [04:40:27] <yrashk>	jugg: testing on separate vms
| [Thursday 17 February 2011] [04:40:32] <jugg>	k
| [Thursday 17 February 2011] [04:40:48] <yrashk>	    Throughput = MessageCount / Elapsed
| [Thursday 17 February 2011] [04:40:53] <yrashk>	Elapsed is in microseconds
| [Thursday 17 February 2011] [04:41:16] <yrashk>	I guess I need to multiply by 1000
| [Thursday 17 February 2011] [04:42:13] <yrashk>	1M messages taking some time...
| [Thursday 17 February 2011] [04:42:17] <yrashk>	quite some time
| [Thursday 17 February 2011] [04:42:44] <yrashk>	sustrik: how long 1M of 1B is supposed to be with raw 0mq?
| [Thursday 17 February 2011] [04:42:53] <sustrik>	fraction of a second
| [Thursday 17 February 2011] [04:43:15] <yrashk>	ha
| [Thursday 17 February 2011] [04:43:25] <yrashk>	well erlzmq is doomed then
| [Thursday 17 February 2011] [04:43:59] <jugg>	can you post the code?
| [Thursday 17 February 2011] [04:44:15] <sustrik>	0.3 sec on my box
| [Thursday 17 February 2011] [04:44:46] <yrashk>	https://gist.github.com/5c3005692b594c318897
| [Thursday 17 February 2011] [04:44:53] <yrashk>	sustrik: with raw 0mq right?
| [Thursday 17 February 2011] [04:45:04] <sustrik>	yes
| [Thursday 17 February 2011] [04:46:17] <yrashk>	well it took about half a minute here
| [Thursday 17 February 2011] [04:46:18] <yrashk>	hehe
| [Thursday 17 February 2011] [04:46:31] <yrashk>	for tcp transport
| [Thursday 17 February 2011] [04:46:56] <yrashk>	mean throughput: 30524.908462667627 [msg/s]
| [Thursday 17 February 2011] [04:47:10] <yrashk>	(if my math is correct)
| [Thursday 17 February 2011] [04:47:20] <yrashk>	(this is csrl's fork)
| [Thursday 17 February 2011] [04:52:18] <yrashk>	official one, I can't even test yet
| [Thursday 17 February 2011] [04:52:23] <yrashk>	getting einval on recv
| [Thursday 17 February 2011] [04:53:20] <yrashk>	sustrik: jugg ^^^
| [Thursday 17 February 2011] [04:54:25] <sustrik>	strange
| [Thursday 17 February 2011] [04:54:58] <yrashk>	this performance isn't impressive at all :-(
| [Thursday 17 February 2011] [04:55:09] <sustrik>	maybe because of "active"?
| [Thursday 17 February 2011] [04:56:06] <sustrik>	in any case, don't throw the tests away
| [Thursday 17 February 2011] [04:56:23] <sustrik>	let's merge them to erlzmq
| [Thursday 17 February 2011] [04:56:36] <yrashk>	I am trying to set active to false explicitly
| [Thursday 17 February 2011] [04:57:20] <yrashk>	ok it worked
| [Thursday 17 February 2011] [04:57:25] <yrashk>	I think it was enabled by default
| [Thursday 17 February 2011] [04:58:24] <yrashk>	I suspect that official w/o active is even slower
| [Thursday 17 February 2011] [04:58:30] <yrashk>	no
| [Thursday 17 February 2011] [04:58:32] <yrashk>	about the same
| [Thursday 17 February 2011] [04:58:38] <yrashk>	mean throughput: 32142.1195960057 [msg/s]
| [Thursday 17 February 2011] [04:58:49] <sustrik>	hm
| [Thursday 17 February 2011] [04:59:17] <yrashk>	creating another version to test with active on
| [Thursday 17 February 2011] [05:01:02] <yrashk>	active was even worse
| [Thursday 17 February 2011] [05:01:02] <yrashk>	mean throughput: 28188.449027560524 [msg/s]
| [Thursday 17 February 2011] [05:01:35] <mikko>	sustrik: whats the process in updating openpgm?
| [Thursday 17 February 2011] [05:01:36] <yrashk>	and
| [Thursday 17 February 2011] [05:01:37] <yrashk>	mean throughput: 26443.701834780386 [msg/s]
| [Thursday 17 February 2011] [05:01:52] <sustrik>	mikko: i don't know, mato did it
| [Thursday 17 February 2011] [05:02:03] <sustrik>	i suppose it's just replacing the archive
| [Thursday 17 February 2011] [05:02:30] <mikko>	sustrik: i think we are soon in a point where we can invoke openpgm autotools build
| [Thursday 17 February 2011] [05:02:38] <mikko>	and remove large amount of duplicated work
| [Thursday 17 February 2011] [05:02:46] <sustrik>	wow
| [Thursday 17 February 2011] [05:02:53] <mikko>	everything still works as they did before (bundled openpgm)
| [Thursday 17 February 2011] [05:02:53] <sustrik>	congrats
| [Thursday 17 February 2011] [05:03:08] <mikko>	but it just runs openpgm 'configure' from zeromq 'configure'
| [Thursday 17 February 2011] [05:03:13] <sustrik>	yrashk: time to profile erlzmq :)
| [Thursday 17 February 2011] [05:03:45] <mikko>	also, all compiler choices etc flow down to openpgm build
| [Thursday 17 February 2011] [05:04:01] <pieterh_>	sustrik, fix to mailbox did not work, I've sent details to the list
| [Thursday 17 February 2011] [05:04:02] <sustrik>	nice
| [Thursday 17 February 2011] [05:04:20] <sustrik>	pieterh_: yes, it's a complex problem
| [Thursday 17 February 2011] [05:04:23] <mikko>	should i add gcov to zeromq as well?
| [Thursday 17 February 2011] [05:04:27] <sustrik>	see the original email in the thread
| [Thursday 17 February 2011] [05:04:33] <mikko>	so that we can visually see what's tested and what's not?
| [Thursday 17 February 2011] [05:04:50] <yrashk>	sustrik, jugg: ok so I have patches with perf teststo merge in now, interested?
| [Thursday 17 February 2011] [05:04:55] <pieterh_>	sustrik: IMO there is a bug in the mailbox handling of reconnect commands
| [Thursday 17 February 2011] [05:05:10] <pieterh_>	the mailbox grows consistently for each reconnect
| [Thursday 17 February 2011] [05:05:15] <jugg>	yrashk, sure
| [Thursday 17 February 2011] [05:05:18] <pieterh_>	doesn't matter how fast or slow you do them
| [Thursday 17 February 2011] [05:05:24] <sustrik>	mikko: why not
| [Thursday 17 February 2011] [05:05:48] <yrashk>	jugg: sent performance tests pull req
| [Thursday 17 February 2011] [05:05:49] <sustrik>	pieterh_: it's because the application thread does not process the commands (it's sleeping)
| [Thursday 17 February 2011] [05:06:20] <pieterh_>	sustrik: ack, any way to discard duplicates?
| [Thursday 17 February 2011] [05:06:34] <yrashk>	I am a very sad panda now
| [Thursday 17 February 2011] [05:06:40] <sustrik>	not really, they are in the middle of the socketpair buffer
| [Thursday 17 February 2011] [05:06:53] <pieterh_>	then kill the parent socket if it doesn't behave
| [Thursday 17 February 2011] [05:06:54] <sustrik>	rather the reconnection logic should be rethought
| [Thursday 17 February 2011] [05:07:12] <sustrik>	that's an option
| [Thursday 17 February 2011] [05:07:19] <sustrik>	EBROKEN
| [Thursday 17 February 2011] [05:07:22] <yrashk>	sustrik: https://github.com/zeromq/erlzmq/pull/16
| [Thursday 17 February 2011] [05:07:23] <pieterh_>	yes, exactly
| [Thursday 17 February 2011] [05:07:56] <sustrik>	yrashk: thx
| [Thursday 17 February 2011] [05:08:07] <pieterh_>	it's not a 0MQ error, it's a caller error, so it should kill whatever's misbehaving and return an error
| [Thursday 17 February 2011] [05:08:07] <yrashk>	still, 30K 1-byte messages per second...
| [Thursday 17 February 2011] [05:08:10] <pieterh_>	not assert, of course
| [Thursday 17 February 2011] [05:08:13] <yrashk>	:S
| [Thursday 17 February 2011] [05:08:26] <pieterh_>	yrashk, you running AMQP?
| [Thursday 17 February 2011] [05:08:58] <pieterh_>	just kidding, there was a 30K figure from someone impressed with AMQP, on Twitter...
| [Thursday 17 February 2011] [05:10:45] <yrashk>	pieterh_: no, erlzmq actually
| [Thursday 17 February 2011] [05:10:47] <yrashk>	i am not impressed
| [Thursday 17 February 2011] [05:10:51] <yrashk>	rather opposite
| [Thursday 17 February 2011] [05:11:08] <pieterh_>	erlang does some heavy locking, I've been told
| [Thursday 17 February 2011] [05:11:31] <yrashk>	this is a very vague statement
| [Thursday 17 February 2011] [05:11:58] <pieterh_>	indeed
| [Thursday 17 February 2011] [05:12:02] <yrashk>	I can't even reply to it
| [Thursday 17 February 2011] [05:12:50] <pieterh_>	i mean, it's spending its time somewhere and that is not 0MQ and probably not erlzmq as such either
| [Thursday 17 February 2011] [05:13:50] <mikko>	http://www.erlang-factory.com/upload/presentations/303/rickard-green-euc2010.pdf
| [Thursday 17 February 2011] [05:13:54] <mikko>	erlang locking explained
| [Thursday 17 February 2011] [05:14:28] <yrashk>	I assume everyone knows what erlang rwlocks are
| [Thursday 17 February 2011] [05:14:41] <mikko>	i didn't before i read that
| [Thursday 17 February 2011] [05:15:21] <pieterh_>	yrashk, few people here have every used erlang
| [Thursday 17 February 2011] [05:15:25] <pieterh_>	*ever used
| [Thursday 17 February 2011] [05:16:00] <pieterh_>	mikko, interesting stuff but does anyone have figures for the actual overhead of erlang rwlocks?
| [Thursday 17 February 2011] [05:18:49] <pieterh_>	sustrik: any best practice on turning an identity blob_t into a printable string for error reporting?
| [Thursday 17 February 2011] [05:18:59] <yrashk>	what really upsets me is that erlzmq is maintained by saleyn
| [Thursday 17 February 2011] [05:19:08] <yrashk>	if he can't make it fast, then who can? :-\
| [Thursday 17 February 2011] [05:19:20] <pieterh_>	maybe 30k/sec is fast, it's always relative...
| [Thursday 17 February 2011] [05:19:30] <yrashk>	I don't think it's fast
| [Thursday 17 February 2011] [05:19:38] <yrashk>	if raw 0mq can do it like 100 times faster
| [Thursday 17 February 2011] [05:19:48] <pieterh_>	Have you measured the raw speed of two erlang tasks talking to each other?
| [Thursday 17 February 2011] [05:19:58] <yrashk>	nope
| [Thursday 17 February 2011] [05:20:05] <yrashk>	I think jugg had
| [Thursday 17 February 2011] [05:20:07] <yrashk>	did you?
| [Thursday 17 February 2011] [05:20:26] <pieterh_>	So Erlang is afaik not meant to be a high performance language but a language for reliable distributed systems
| [Thursday 17 February 2011] [05:21:13] <pieterh_>	I suspect (with only third-hand information) that you'll find it to be around 30K/second
| [Thursday 17 February 2011] [05:21:34] <pieterh_>	Which is actually fine for many apps
| [Thursday 17 February 2011] [05:21:50] <pieterh_>	Especially if they process only one stream of data
| [Thursday 17 February 2011] [05:22:14] <yrashk>	"I see therefore that on two different Erlang nodes, this benchmark gives a result of an average of 700 thousands ping/pong messages per minute"
| [Thursday 17 February 2011] [05:22:18] <yrashk>	just googled this
| [Thursday 17 February 2011] [05:22:32] <yrashk>	well it looks like we're doing more
| [Thursday 17 February 2011] [05:22:32] <pieterh_>	hmm, 20x faster...
| [Thursday 17 February 2011] [05:22:41] <yrashk>	we have million per 30 seconds
| [Thursday 17 February 2011] [05:22:49] <pieterh_>	per *minute*...
| [Thursday 17 February 2011] [05:23:08] <yrashk>	it's ping/pong tho
| [Thursday 17 February 2011] [05:23:09] <pieterh_>	that's ping pongs
| [Thursday 17 February 2011] [05:23:11] <pieterh_>	so double it
| [Thursday 17 February 2011] [05:23:15] <yrashk>	1,4mln
| [Thursday 17 February 2011] [05:23:19] <pieterh_>	1,400,000/minute
| [Thursday 17 February 2011] [05:23:38] <pieterh_>	23k/second
| [Thursday 17 February 2011] [05:23:38] <yrashk>	sustrik: in your tests, I assume you run over tcp?
| [Thursday 17 February 2011] [05:24:06] <yrashk>	"I see therefore that within the same Erlang node, this benchmark gives a result of an average of 5.3 million ping/pong messages per minute, the same that we had without the queuing mechanism."
| [Thursday 17 February 2011] [05:24:08] <pieterh_>	which is pretty much equal to 30k/sec allowing for system differences
| [Thursday 17 February 2011] [05:24:45] <yrashk>	sustrik: also, different processes?
| [Thursday 17 February 2011] [05:25:43] <pieterh_>	so 160k/sec within same node
| [Thursday 17 February 2011] [05:26:46] <yrashk>	I just want to verify raw 0mq can do million messages betwen two diff processes over tcp on macosx in 0.3 secs
| [Thursday 17 February 2011] [05:26:56] <yrashk>	whether raw 0mq*
| [Thursday 17 February 2011] [05:27:08] <yrashk>	does this sound about right?
| [Thursday 17 February 2011] [05:27:32] <yrashk>	obviously there's an overhead in any higher level language esp with VM likes beam
| [Thursday 17 February 2011] [05:27:32] <pieterh_>	yrashk, not ping pong, just send?
| [Thursday 17 February 2011] [05:27:40] <yrashk>	just sends
| [Thursday 17 February 2011] [05:27:42] <yrashk>	and recvs
| [Thursday 17 February 2011] [05:27:47] <pieterh_>	well, it will batch messages
| [Thursday 17 February 2011] [05:27:55] <yrashk>	but I want to make sure it is 100 times faster
| [Thursday 17 February 2011] [05:28:14] <pieterh_>	so if you use 1 byte messages you will get a throughput of several million per second at least
| [Thursday 17 February 2011] [05:28:43] <pieterh_>	depends a lot on your material here
| [Thursday 17 February 2011] [05:28:43] <yrashk>	I guess this is what is causing a problem in erlzmq
| [Thursday 17 February 2011] [05:28:52] <pieterh_>	multicore = multifaster
| [Thursday 17 February 2011] [05:30:47] <yrashk>	does anybody have any other binding available with perf tests available?
| [Thursday 17 February 2011] [05:30:51] <yrashk>	like rbzmq?
| [Thursday 17 February 2011] [05:31:08] <yrashk>	I just don't want to go throguh system-wide installation of zeromq and such
| [Thursday 17 February 2011] [05:31:25] <yrashk>	I copied my test from ruby's remote/local_thr.rb
| [Thursday 17 February 2011] [05:33:49] <mikko>	do you want bindings tested or is local_thr/remote_thr from zeromq ok?
| [Thursday 17 February 2011] [05:34:33] <yrashk>	ideally I want both :D
| [Thursday 17 February 2011] [05:34:39] <yrashk>	I can do the zeromq thing myself I guess
| [Thursday 17 February 2011] [05:38:21] <yrashk>	mean throughput: 2315163 [msg/s]
| [Thursday 17 February 2011] [05:38:52] <pieterh_>	yrashk, that's rbzmq?
| [Thursday 17 February 2011] [05:39:03] <mikko>	mean throughput: 4997086 [msg/s]
| [Thursday 17 February 2011] [05:39:16] <mikko>	over lo using tcp socket on OS X
| [Thursday 17 February 2011] [05:39:26] <yrashk>	pieterh_: that's raw 0mq
| [Thursday 17 February 2011] [05:39:36] <yrashk>	win 10
| [Thursday 17 February 2011] [05:39:38] <yrashk>	oops
| [Thursday 17 February 2011] [05:39:48] <mikko>	mean throughput: 5345358 [msg/s]
| [Thursday 17 February 2011] [05:39:51] <mikko>	over en0
| [Thursday 17 February 2011] [05:41:50] <yrashk>	this is all raw 0mq right?
| [Thursday 17 February 2011] [05:41:57] <mikko>	yes
| [Thursday 17 February 2011] [05:41:58] <yrashk>	anybody with rbzmq or pyzmq handy?
| [Thursday 17 February 2011] [05:42:06] <mikko>	i do
| [Thursday 17 February 2011] [05:42:09] <mikko>	i build them all :)
| [Thursday 17 February 2011] [05:42:16] <mikko>	sec
| [Thursday 17 February 2011] [05:42:22] <yrashk>	can you please run the same test? 1b msgs 1mln times
| [Thursday 17 February 2011] [05:44:58] <mikko>	yrashk: let me figure out how
| [Thursday 17 February 2011] [05:45:13] <yrashk>	mikko: in rbzmq those are exactly the same tests
| [Thursday 17 February 2011] [05:45:26] <yrashk>	perf/local_thr.rb perf/remote_thr.rb
| [Thursday 17 February 2011] [05:46:19] <mikko>	ok
| [Thursday 17 February 2011] [05:47:48] <mikko>	i think im running it now
| [Thursday 17 February 2011] [05:50:02] <mikko>	takes very long time with ruby
| [Thursday 17 February 2011] [05:50:33] <yrashk>	mikko: lets wait until it's done
| [Thursday 17 February 2011] [05:50:43] <yrashk>	did you use tcp://127.0.0.1:port 1 1000000
| [Thursday 17 February 2011] [05:50:45] <yrashk>	or something?
| [Thursday 17 February 2011] [05:51:01] <mikko>	i started with 100000000 or so
| [Thursday 17 February 2011] [05:51:09] <mikko>	now testing quickly with 10 that it actually works
| [Thursday 17 February 2011] [05:51:27] <yrashk>	well I want the same test
| [Thursday 17 February 2011] [05:51:32] <yrashk>	1 byte msgs, 1mln messages
| [Thursday 17 February 2011] [05:51:37] <mikko>	https://gist.github.com/62772ec66fc1a46a3372
| [Thursday 17 February 2011] [05:51:55] <mikko>	this is on linux
| [Thursday 17 February 2011] [05:51:58] <yrashk>	that's 10mlns but thanks anyway
| [Thursday 17 February 2011] [05:52:17] <mikko>	and ruby
| [Thursday 17 February 2011] [05:52:20] <mikko>	http://build.valokuva.org/
| [Thursday 17 February 2011] [05:52:23] <mikko>	i got those available
| [Thursday 17 February 2011] [05:57:52] <jugg>	porting yrashk's tests to do raw erlang message passing between two nodes yields 59645.1127719094 [msg/s].
| [Thursday 17 February 2011] [05:58:09] <jugg>	to clarify that is without zeromq
| [Thursday 17 February 2011] [05:59:19] <mikko>	ok
| [Thursday 17 February 2011] [06:00:00] <yrashk>	jugg: so twice as fast
| [Thursday 17 February 2011] [06:00:55] <jugg>	using zmq (tcp lo) those tests yield 21378.701789023213 [msg/s]  on my system.
| [Thursday 17 February 2011] [06:01:18] <jugg>	erlzmq that is...
| [Thursday 17 February 2011] [06:01:43] <jugg>	anyway, I'm off. yrashk, I'll look at your pull request later.
| [Thursday 17 February 2011] [06:01:52] <yrashk>	well my pull req == git
| [Thursday 17 February 2011] [06:01:53] <yrashk>	gist
| [Thursday 17 February 2011] [06:01:54] <mikko>	yrashk: not many things on your blog
| [Thursday 17 February 2011] [06:02:03] <mikko>	in*
| [Thursday 17 February 2011] [06:02:05] <yrashk>	mikko: it's empty, I know
| [Thursday 17 February 2011] [06:02:08] <yrashk>	I keep myself busy
| [Thursday 17 February 2011] [06:02:34] <mikko>	is there more locking involved accessing zeromq sockets from erlang?
| [Thursday 17 February 2011] [06:02:38] <mikko>	like explicit locking?
| [Thursday 17 February 2011] [06:22:36] <sustrik>	re
| [Thursday 17 February 2011] [06:24:42] <sustrik>	pieterh_: no standard way to convert blob into string
| [Thursday 17 February 2011] [06:25:39] <sustrik>	yrashk: i've used TCP
| [Thursday 17 February 2011] [06:25:48] <sustrik>	yrashk: you can investigate further
| [Thursday 17 February 2011] [06:26:03] <sustrik>	by running C local_thr vs. Erlang remote_thr
| [Thursday 17 February 2011] [06:26:09] <sustrik>	and vice versa
| [Thursday 17 February 2011] [06:26:35] <sustrik>	that way you'll find out whether the bottleneck on the sender or receiver side
| [Thursday 17 February 2011] [06:32:30] <yrashk>	sustrik: I think I have a vague idea on how to make erlzmq faster
| [Thursday 17 February 2011] [06:32:44] <yrashk>	will require a lot of rewriting, though
| [Thursday 17 February 2011] [06:33:03] <sustrik>	do you have any idea where the bottleneck is?
| [Thursday 17 February 2011] [06:33:14] <yrashk>	port driver communication
| [Thursday 17 February 2011] [06:33:23] <yrashk>	not confirmed, just an idea
| [Thursday 17 February 2011] [06:33:35] <sustrik>	it's good to measure it first
| [Thursday 17 February 2011] [06:33:45] <sustrik>	otherwise you may end with no perf improvement
| [Thursday 17 February 2011] [06:33:46] <yrashk>	hard to measure this, though
| [Thursday 17 February 2011] [06:33:57] <yrashk>	but possible
| [Thursday 17 February 2011] [06:34:22] <sustrik>	anyway, try the c/erlang perf tests
| [Thursday 17 February 2011] [06:34:36] <yrashk>	c/erlang?
| [Thursday 17 February 2011] [06:34:40] <sustrik>	it may turn out that the bottleneck is only on one side
| [Thursday 17 February 2011] [06:34:48] <sustrik>	<sustrik> yrashk: you can investigate further
| [Thursday 17 February 2011] [06:34:49] <sustrik>	<sustrik> by running C local_thr vs. Erlang remote_thr
| [Thursday 17 February 2011] [06:34:49] <sustrik>	<sustrik> and vice versa
| [Thursday 17 February 2011] [06:34:54] <yrashk>	oh
| [Thursday 17 February 2011] [06:34:55] <yrashk>	right
| [Thursday 17 February 2011] [06:34:57] <yrashk>	missed that
| [Thursday 17 February 2011] [06:35:01] <yrashk>	good idea actually
| [Thursday 17 February 2011] [06:36:09] <yrashk>	mean throughput: 30606 [msg/s]
| [Thursday 17 February 2011] [06:36:16] <yrashk>	this is C local_thr
| [Thursday 17 February 2011] [06:36:55] <yrashk>	mean throughput: 67086.58395785352 [msg/s]
| [Thursday 17 February 2011] [06:37:01] <yrashk>	this is Erlang local_thr
| [Thursday 17 February 2011] [06:37:39] <yrashk>	so partially it is the way erlzmq's send works
| [Thursday 17 February 2011] [06:37:50] <yrashk>	sustrik: ^^
| [Thursday 17 February 2011] [06:38:13] <sustrik>	both are low
| [Thursday 17 February 2011] [06:38:16] <yrashk>	I guess no batching happening with erlzmq
| [Thursday 17 February 2011] [06:38:21] <sustrik>	so there's some common problem
| [Thursday 17 February 2011] [06:38:23] <yrashk>	yes they are
| [Thursday 17 February 2011] [06:38:25] <sustrik>	both on send and recv side
| [Thursday 17 February 2011] [06:38:37] <yrashk>	but receiving got twice as fast
| [Thursday 17 February 2011] [06:38:42] <sustrik>	yup
| [Thursday 17 February 2011] [06:39:28] <sustrik>	however, don't focus on that, the primary goal is to speed the whole beast ~50x
| [Thursday 17 February 2011] [06:39:47] <yrashk>	yeah 50x will be enough
| [Thursday 17 February 2011] [06:39:53] <yrashk>	that will be like about 1/2 of raw perf
| [Thursday 17 February 2011] [06:40:03] <yrashk>	which is acceptable
| [Thursday 17 February 2011] [06:40:04] <sustrik>	afterwards, you can check why recv is 2x faster
| [Thursday 17 February 2011] [06:40:12] <sustrik>	ack
| [Thursday 17 February 2011] [06:40:28] <yrashk>	well I am blaming erlzmq's model (driver) now
| [Thursday 17 February 2011] [06:40:35] <sustrik>	quite possible
| [Thursday 17 February 2011] [06:40:38] <yrashk>	driver communication isn't very fast as far as I understand
| [Thursday 17 February 2011] [06:40:45] <yrashk>	I can try converting this into a NIF
| [Thursday 17 February 2011] [06:40:51] <sustrik>	NIF?
| [Thursday 17 February 2011] [06:40:52] <yrashk>	which may or may not speed it up
| [Thursday 17 February 2011] [06:40:59] <yrashk>	Native Implemented Function
| [Thursday 17 February 2011] [06:41:03] <yrashk>	much less overhead
| [Thursday 17 February 2011] [06:41:23] <yrashk>	port communication sends data and parses it
| [Thursday 17 February 2011] [06:41:27] <yrashk>	which isn't fast
| [Thursday 17 February 2011] [06:42:05] <yrashk>	the only problem is that until some time in future, NIFs are blocking their scheduler. There is a way around that, though -- I wrote erlv8 so I know how to deal with tis
| [Thursday 17 February 2011] [06:42:08] <yrashk>	this*
| [Thursday 17 February 2011] [06:44:32] <sustrik>	i see
| [Thursday 17 February 2011] [06:44:56] <yrashk>	if only I had an unlimited supply of time
| [Thursday 17 February 2011] [06:45:12] <yrashk>	although I still may try to rewrite erlzmq
| [Thursday 17 February 2011] [06:45:22] <yrashk>	but that will be almost a complete rewrite
| [Thursday 17 February 2011] [06:45:23] <yrashk>	:-(
| [Thursday 17 February 2011] [06:46:55] <yrashk>	writing NIFs is not much fun, really
| [Thursday 17 February 2011] [06:47:06] <yrashk>	so are the drivers, though :)
| [Thursday 17 February 2011] [06:48:45] <yrashk>	sustrik: how does the batching work? is it time-based? like batch X messages within T?
| [Thursday 17 February 2011] [06:53:12] <sustrik>	it's triggered by the network stack
| [Thursday 17 February 2011] [06:53:37] <sustrik>	so, when the network stack notifies the user space that there's free space in tx buffer
| [Thursday 17 February 2011] [06:53:52] <sustrik>	0mq takes as much data as is available atm
| [Thursday 17 February 2011] [06:54:04] <sustrik>	and tries to push it into the kernel in a single go
| [Thursday 17 February 2011] [06:54:38] <yrashk>	I ee
| [Thursday 17 February 2011] [06:54:40] <yrashk>	I see
| [Thursday 17 February 2011] [06:54:49] <yrashk>	well at this point I'd really blame the port communication
| [Thursday 17 February 2011] [06:54:55] <sustrik>	well, maybe
| [Thursday 17 February 2011] [06:55:04] <sustrik>	if you haven't time to play with it
| [Thursday 17 February 2011] [06:55:06] <yrashk>	it is an encode -> pass -> decode -> work -> encode -> decode routine
| [Thursday 17 February 2011] [06:55:11] <sustrik>	at least write an email to the ML
| [Thursday 17 February 2011] [06:55:30] <yrashk>	it is an encode -> pass -> decode -> work -> encode -> pass -> decode routine *
| [Thursday 17 February 2011] [06:55:42] <sustrik>	doesn't seem very efficient
| [Thursday 17 February 2011] [06:56:01] <yrashk>	those encodings/decodings aren't super slow by themselves, probably, but still, everything adds up
| [Thursday 17 February 2011] [06:56:12] <yrashk>	NIFs work nearly directly with the data
| [Thursday 17 February 2011] [06:56:13] <sustrik>	ack
| [Thursday 17 February 2011] [06:56:25] <sustrik>	yes, that's how other bindings are done
| [Thursday 17 February 2011] [06:56:37] <sustrik>	the problem with erlang is its threading model
| [Thursday 17 February 2011] [06:56:54] <sustrik>	afaiu blocking in NIF could get the whole VM to a standstill
| [Thursday 17 February 2011] [06:56:59] <yrashk>	yes
| [Thursday 17 February 2011] [06:57:05] <yrashk>	but there are two points:
| [Thursday 17 February 2011] [06:57:46] <yrashk>	1) this is going to change http://erlang-factory.com/conference/SFBay2011/speakers/RickardGreen
| [Thursday 17 February 2011] [06:58:18] <yrashk>	2) there are some workarounds (basically, two-thread model). I used it in erlv8. Incidentially, I ended up using 0mq inside erlv8's NIF
| [Thursday 17 February 2011] [06:58:33] <sustrik>	:)
| [Thursday 17 February 2011] [06:59:19] <yrashk>	I will be at that conference (I am a speaker there, too) so I will have a chance to attend that talk
| [Thursday 17 February 2011] [06:59:25] <yrashk>	(in pt. 1)
| [Thursday 17 February 2011] [06:59:35] <sustrik>	i see
| [Thursday 17 February 2011] [07:00:32] <sustrik>	are you from SF?
| [Thursday 17 February 2011] [07:00:38] <yrashk>	nope
| [Thursday 17 February 2011] [07:00:53] <yrashk>	http://erlang-factory.com/conference/SFBay2011/speakers/YuriiRashkovskii
| [Thursday 17 February 2011] [07:00:55] <yrashk>	Vancouver, BC
| [Thursday 17 February 2011] [07:01:56] <sustrik>	aha, just that i'm visiting SF shortly
| [Thursday 17 February 2011] [07:02:20] <yrashk>	oh
| [Thursday 17 February 2011] [07:02:26] <sustrik>	but before the conference
| [Thursday 17 February 2011] [07:02:29] <sustrik>	no overlap there
| [Thursday 17 February 2011] [07:02:29] <yrashk>	too bad
| [Thursday 17 February 2011] [07:02:39] <yrashk>	I'd love to share a beer or something 
| [Thursday 17 February 2011] [07:02:58] <yrashk>	open source developers don't get much face-to-face time
| [Thursday 17 February 2011] [07:03:00] <yrashk>	and it's bad
| [Thursday 17 February 2011] [07:03:27] <pieterh_>	yeah, 5,000 open source developers at FOSDEM earlier in Feb, here in Brussels
| [Thursday 17 February 2011] [07:03:45] <yrashk>	well I didn't say they don't get it at all
| [Thursday 17 February 2011] [07:03:48] <yrashk>	just not much
| [Thursday 17 February 2011] [07:03:49] <yrashk>	:D
| [Thursday 17 February 2011] [07:03:56] <pieterh_>	I mean, it's only once a year
| [Thursday 17 February 2011] [07:04:04] <yrashk>	I see
| [Thursday 17 February 2011] [07:04:21] <yrashk>	it would be cool to have a rolling set of unconferences happening in every "hub" city
| [Thursday 17 February 2011] [07:04:28] <yrashk>	well, they do happen
| [Thursday 17 February 2011] [07:04:37] <yrashk>	but they are fairly limited
| [Thursday 17 February 2011] [07:05:05] <pieterh_>	sustrik: why not do a 0MQ meetup while you're there...
| [Thursday 17 February 2011] [07:06:08] <sustrik>	yes, i'll do that
| [Thursday 17 February 2011] [07:06:16] <yrashk>	record some video! :)
| [Thursday 17 February 2011] [07:06:30] <yrashk>	if there are going to be any presentations
| [Thursday 17 February 2011] [07:06:40] <sustrik>	nope, just people drinking beer :)
| [Thursday 17 February 2011] [07:06:45] <yrashk>	sigh 
| [Thursday 17 February 2011] [07:06:46] <yrashk>	:]
| [Thursday 17 February 2011] [07:07:00] <pieterh_>	yrashk, there's a video of me (I think) praising Erlang at FOSDEM
| [Thursday 17 February 2011] [07:07:25] <pieterh_>	that's "praising Erlang, I think" not "a video of me, I think"...
| [Thursday 17 February 2011] [07:07:26] <yrashk>	pieterh_: "of me (I think)"
| [Thursday 17 February 2011] [07:07:29] <yrashk>	were you drunk? :)
| [Thursday 17 February 2011] [07:07:34] <pieterh_>	one is never totally sure
| [Thursday 17 February 2011] [07:07:51] <pieterh_>	FOSDEM is fairly beer intensive
| [Thursday 17 February 2011] [07:08:02] <yrashk>	that comes withour saying
| [Thursday 17 February 2011] [07:08:24] <yrashk>	although I've never been to one
| [Thursday 17 February 2011] [07:08:31] <yrashk>	but just about any dev meetup implies beer
| [Thursday 17 February 2011] [07:08:52] <pieterh_>	yeah, but in Belgium that implies "how strong can we get the beer, and how cheaply can we sell it"
| [Thursday 17 February 2011] [07:08:54] <yrashk>	too bad I am a little sensitive to alcohol since like 2005 so I don't drink much
| [Thursday 17 February 2011] [07:09:01] <pieterh_>	me too, sadly
| [Thursday 17 February 2011] [07:09:28] <yrashk>	esp beer :-(
| [Thursday 17 February 2011] [07:09:35] <yrashk>	weak stomach
| [Thursday 17 February 2011] [07:09:38] <pieterh_>	anyhow fwiw the video is here:     //  If the session already has an engine attached, destroy new one.
| [Thursday 17 February 2011] [07:09:38] <pieterh_>	    //  Note new engine is not plugged in yet, we don't have to unplug it.
| [Thursday 17 February 2011] [07:09:38] <pieterh_>	    if (engine) {
| [Thursday 17 February 2011] [07:09:38] <pieterh_>	        delete engine_;
| [Thursday 17 February 2011] [07:09:39] <pieterh_>	        puts ("HEY!");
| [Thursday 17 February 2011] [07:09:41] <pieterh_>	        return;
| [Thursday 17 February 2011] [07:09:43] <pieterh_>	    }
| [Thursday 17 February 2011] [07:09:45] <yrashk>	that's not the video
| [Thursday 17 February 2011] [07:09:45] <yrashk>	:D
| [Thursday 17 February 2011] [07:09:48] <pieterh_>	aw, wrong paste
| [Thursday 17 February 2011] [07:10:15] <pieterh_>	http://www.youtube.com/watch?v=CCBYzKfmQ4U
| [Thursday 17 February 2011] [07:11:23] <yrashk>	nice accent
| [Thursday 17 February 2011] [07:15:41] <pieterh_>	What's erlv8? I couldn't find that on google
| [Thursday 17 February 2011] [07:15:51] <yrashk>	part of http://beamjs.org/
| [Thursday 17 February 2011] [07:16:01] <yrashk>	tightly integrated V8 for Erlang
| [Thursday 17 February 2011] [07:16:28] <yrashk>	heeey 
| [Thursday 17 February 2011] [07:16:33] <yrashk>	Erlang is not a "weird language"
| [Thursday 17 February 2011] [07:16:34] <yrashk>	;)
| [Thursday 17 February 2011] [07:17:45] <pieterh_>	Well, it's sooo relative ... :-)
| [Thursday 17 February 2011] [07:17:53] <yrashk>	it's not weird for me
| [Thursday 17 February 2011] [07:17:54] <yrashk>	:D
| [Thursday 17 February 2011] [07:18:08] <yrashk>	sayign language is weird is not exactly "praising" :-P
| [Thursday 17 February 2011] [07:18:09] <yrashk>	;)
| [Thursday 17 February 2011] [07:18:18] <pieterh_>	that's what my crazy uncle says when he eats raw spinach
| [Thursday 17 February 2011] [07:19:35] <kristsk>	why is he eating it raw?
| [Thursday 17 February 2011] [07:20:01] <pieterh_>	no-one knows, that's why we say he's weird, but he says "it's not weird for me"
| [Thursday 17 February 2011] [07:20:14] <pieterh_>	I think 'weird' is high praise compared to 'boring', 'irrelevant', or 'ok'
| [Thursday 17 February 2011] [07:20:23] <pieterh_>	people do speak highly of Erlang once they learn it
| [Thursday 17 February 2011] [07:20:33] <pieterh_>	I'm too lazy and happily ignorant to make that effort
| [Thursday 17 February 2011] [07:20:39] <pieterh_>	calling it 'weird' is much easier
| [Thursday 17 February 2011] [07:20:40] <kristsk>	same goes for lisp
| [Thursday 17 February 2011] [07:20:43] <yrashk>	;)
| [Thursday 17 February 2011] [07:20:52] <yrashk>	Erlang is actually a fantastic platform
| [Thursday 17 February 2011] [07:20:58] <yrashk>	I've used it stating in 2001 
| [Thursday 17 February 2011] [07:21:04] <yrashk>	and I am always returning to it
| [Thursday 17 February 2011] [07:21:08] <yrashk>	from other platforms
| [Thursday 17 February 2011] [07:21:18] <kristsk>	addiction eh
| [Thursday 17 February 2011] [07:21:28] <pieterh_>	it does seem to produce pretty good applications
| [Thursday 17 February 2011] [07:21:40] <pieterh_>	lots of return on your development investment
| [Thursday 17 February 2011] [07:21:59] <pieterh_>	but still...
| [Thursday 17 February 2011] [07:22:04] <yrashk>	it might be not very fast, but you know, only 20% of code impacts for 80% of slowdown
| [Thursday 17 February 2011] [07:22:07] <pieterh_>	... weird :)
| [Thursday 17 February 2011] [07:22:14] <yrashk>	so you can rewrite bottlenecks even in C
| [Thursday 17 February 2011] [07:22:23] <pieterh_>	just trolling, yrashk :)
| [Thursday 17 February 2011] [07:22:27] <yrashk>	and it's really to write some complicated stuff with it
| [Thursday 17 February 2011] [07:22:36] <yrashk>	ikr
| [Thursday 17 February 2011] [07:22:48] <pieterh_>	I don't trust any language that's not been properly dead for 10 years
| [Thursday 17 February 2011] [07:22:54] <kristsk>	im kinda looking for some pet project to try erlang 
| [Thursday 17 February 2011] [07:23:00] <yrashk>	see, I've been with erlang for 10 years and i still have hair ;)
| [Thursday 17 February 2011] [07:23:09] <pieterh_>	true
| [Thursday 17 February 2011] [07:23:24] <pieterh_>	did it grow faster after you learned Erlang, that's my question
| [Thursday 17 February 2011] [07:23:26] <yrashk>	kristsk: help porting socket.io server to erlang
| [Thursday 17 February 2011] [07:23:31] <yrashk>	pieterh_: of coure it did!
| [Thursday 17 February 2011] [07:23:34] <yrashk>	course*
| [Thursday 17 February 2011] [07:23:46] <yrashk>	kristsk: https://github.com/yrashk/socket.io-erlang
| [Thursday 17 February 2011] [07:23:57] <kristsk>	huh
| [Thursday 17 February 2011] [07:24:02] <yrashk>	I've barely started it but then again I don't have much time and my attention span is limited
| [Thursday 17 February 2011] [07:24:21] <yrashk>	erlang is like the best platform for socket.io
| [Thursday 17 February 2011] [07:24:24] <kristsk>	about same here 
| [Thursday 17 February 2011] [07:24:32] <kristsk>	regarding attention span
| [Thursday 17 February 2011] [07:24:36] <yrashk>	:D
| [Thursday 17 February 2011] [07:24:41] <yrashk>	yet i manage to create something
| [Thursday 17 February 2011] [07:24:51] <yrashk>	this winter accounts for erlv8/beamjs and agner
| [Thursday 17 February 2011] [07:24:57] <yrashk>	not too much but at least something
| [Thursday 17 February 2011] [07:25:20] <kristsk>	"dear lord, what the heck is this? did i write this?"
| [Thursday 17 February 2011] [07:25:29] <yrashk>	hahaha
| [Thursday 17 February 2011] [07:25:37] <yrashk>	I experience this like almost every day
| [Thursday 17 February 2011] [07:27:40] <yrashk>	or at least every other day
| [Thursday 17 February 2011] [08:17:57] <xet>	hi
| [Thursday 17 February 2011] [08:22:14] <sustrik>	hi
| [Thursday 17 February 2011] [08:22:19] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r1f536b2 10/ src/zmq_listener.cpp : 
| [Thursday 17 February 2011] [08:22:19] <CIA-21>	zeromq2: Init object is child of listener
| [Thursday 17 February 2011] [08:22:19] <CIA-21>	zeromq2: This means that all the handshaking while accepting incoming
| [Thursday 17 February 2011] [08:22:19] <CIA-21>	zeromq2: connection is done exclusively in I/O threads, thus it won't
| [Thursday 17 February 2011] [08:22:19] <CIA-21>	zeromq2: overload the application thread's mailbox.
| [Thursday 17 February 2011] [08:22:19] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/i0AFxk
| [Thursday 17 February 2011] [08:23:35] <xet>	any1 knows of a good realtime plotting lib to use with a zmq tcp socket?
| [Thursday 17 February 2011] [08:23:59] <xet>	realtime data stream i mean
| [Thursday 17 February 2011] [08:26:21] <sustrik>	no idea
| [Thursday 17 February 2011] [08:33:03] <yrashk>	so ok it looks like I am writing a new erlang binding
| [Thursday 17 February 2011] [08:33:04] <yrashk>	:-O
| [Thursday 17 February 2011] [08:33:18] <yrashk>	*facepalm*
| [Thursday 17 February 2011] [08:35:17] <pieterh_>	yrashk, that'll make 3... :-)
| [Thursday 17 February 2011] [08:35:46] <yrashk>	:D
| [Thursday 17 February 2011] [08:35:50] <pieterh_>	cremes: you around?
| [Thursday 17 February 2011] [08:43:21] <yrashk>	sustrik, pieterh_ I am trying to recall, is it safe to call zmq_msg_close after sending a message?
| [Thursday 17 February 2011] [08:43:43] <yrashk>	or should I better setup an ffn?
| [Thursday 17 February 2011] [08:44:14] <yrashk>	umm
| [Thursday 17 February 2011] [08:44:28] <yrashk>	I think I can do without this at all, I'll let erlang deal with deallocation
| [Thursday 17 February 2011] [08:44:36] <yrashk>	it's probably error prone tho
| [Thursday 17 February 2011] [08:45:05] <sustrik>	yrashk: it's safe
| [Thursday 17 February 2011] [08:45:14] <pieterh_>	yrashk, yes
| [Thursday 17 February 2011] [08:45:19] <sustrik>	unless you use zmq_init_data()
| [Thursday 17 February 2011] [08:45:50] <sustrik>	in which case 0mq will take ownerwhip and deallocate the buffer you pass to it
| [Thursday 17 February 2011] [08:45:55] <pieterh_>	which I'd propose to rename to zmq_init_data_are_you_really_sure ()
| [Thursday 17 February 2011] [08:46:16] <sustrik>	is should be zmq_sendmsg
| [Thursday 17 February 2011] [08:46:33] <sustrik>	and zmq_send should be zmq_send(void *data, size_t size, int flags);
| [Thursday 17 February 2011] [08:46:35] <pieterh_>	there should be zmq_send (blob) (implied copy)
| [Thursday 17 February 2011] [08:46:46] <pieterh_>	and zmq_sendz (message)
| [Thursday 17 February 2011] [08:46:48] <yrashk>	so should I do zmq_msg_init_size and then refer to a structure that is handled by erlang gc?
| [Thursday 17 February 2011] [08:46:57] <yrashk>	or init_size, then copy that binary
| [Thursday 17 February 2011] [08:47:09] <yrashk>	well, then I a need an ffn
| [Thursday 17 February 2011] [08:47:09] <pieterh_>	yrashk, you need to copy, IMO
| [Thursday 17 February 2011] [08:47:19] <yrashk>	then init_data
| [Thursday 17 February 2011] [08:47:30] <sustrik>	yrashk: forget about zero copy for now
| [Thursday 17 February 2011] [08:47:36] <pieterh_>	unless you can guarantee that Erlang won't free the data before zmq sends it
| [Thursday 17 February 2011] [08:47:39] <sustrik>	you can add it later if possible
| [Thursday 17 February 2011] [08:47:44] <yrashk>	I can't guarantee that
| [Thursday 17 February 2011] [08:47:51] <yrashk>	so when should I close that message?
| [Thursday 17 February 2011] [08:47:51] <pieterh_>	then just copy
| [Thursday 17 February 2011] [08:47:56] <pieterh_>	after sending
| [Thursday 17 February 2011] [08:48:01] <yrashk>	in case if I use init_data, too?
| [Thursday 17 February 2011] [08:48:14] <pieterh_>	zmq_msg_init_size, memcpy, zmq_send, zmq_msg_close
| [Thursday 17 February 2011] [08:48:19] <pieterh_>	do not use init_data
| [Thursday 17 February 2011] [08:48:41] <pieterh_>	sustrik: this has to be explained more forcefully IMO
| [Thursday 17 February 2011] [08:49:01] <yrashk>	ok
| [Thursday 17 February 2011] [08:49:07] <sustrik>	yes, but API change is even more importatnt
| [Thursday 17 February 2011] [08:49:15] <sustrik>	unfortunately it can't be done till 3.0
| [Thursday 17 February 2011] [08:49:18] <pieterh_>	idea: can we make the init method name match the send method?
| [Thursday 17 February 2011] [08:49:27] <sustrik>	?
| [Thursday 17 February 2011] [08:49:28] <pieterh_>	so zmq_msg_init_zcopy and zmq_send_zcopy?
| [Thursday 17 February 2011] [08:49:38] <sustrik>	why so?
| [Thursday 17 February 2011] [08:49:52] <pieterh_>	they are always used together, no?
| [Thursday 17 February 2011] [08:50:03] <sustrik>	there's only one send method
| [Thursday 17 February 2011] [08:50:09] <pieterh_>	today, yes
| [Thursday 17 February 2011] [08:50:19] <pieterh_>	oh... sorry... forget it
| [Thursday 17 February 2011] [08:50:27] <sustrik>	i would copy POSIX as close as possible
| [Thursday 17 February 2011] [08:50:30] <pieterh_>	brainfart
| [Thursday 17 February 2011] [08:50:51] <pieterh_>	anyhow, init_data is deceptively named IMO
| [Thursday 17 February 2011] [08:51:01] <yrashk>	will no zero copy seriously degrage perf?
| [Thursday 17 February 2011] [08:51:16] <sustrik>	only for very large messages
| [Thursday 17 February 2011] [08:51:16] <pieterh_>	it looks like a normal sibling of init_size when in fact it's a weird spinach eating cousin
| [Thursday 17 February 2011] [08:51:22] <sustrik>	like 256MB or so
| [Thursday 17 February 2011] [08:51:32] <yrashk>	ok
| [Thursday 17 February 2011] [08:51:43] <sustrik>	pieterh_: yes, agreed, but we can't change it till 3.0
| [Thursday 17 February 2011] [08:51:43] <yrashk>	likely, seriously degrade?
| [Thursday 17 February 2011] [08:51:45] <sustrik>	shrug
| [Thursday 17 February 2011] [08:51:45] <yrashk>	like*
| [Thursday 17 February 2011] [08:51:55] <pieterh_>	sustrik, np, can I add that to the roadmap page?
| [Thursday 17 February 2011] [08:52:08] <sustrik>	it's there
| [Thursday 17 February 2011] [08:52:10] <pieterh_>	yrashk, for large messages, you will see a visible difference...
| [Thursday 17 February 2011] [08:52:52] <sustrik>	yrashk: http://www.zeromq.org/results:copying
| [Thursday 17 February 2011] [08:56:27] <pieterh_>	sustrik, it wasn't there but I've added it and made a few other updates
| [Thursday 17 February 2011] [08:57:09] <pieterh_>	3.0 is going to be fun... :-)
| [Thursday 17 February 2011] [08:57:21] <pieterh_>	We're like MSFT, we get it right by version 3...
| [Thursday 17 February 2011] [08:58:41] <sustrik>	thanks
| [Thursday 17 February 2011] [08:58:58] <sustrik>	it's not obvious how to do the switch though
| [Thursday 17 February 2011] [08:59:04] <sustrik>	it's going to be painful
| [Thursday 17 February 2011] [09:00:08] <pieterh_>	90% of people work via bindings
| [Thursday 17 February 2011] [09:00:27] <pieterh_>	and bindings can handle both APIs, quite simply IMO
| [Thursday 17 February 2011] [09:01:27] <pieterh_>	that made more sense before I wrote it :-(
| [Thursday 17 February 2011] [09:04:03] <sustrik>	:)
| [Thursday 17 February 2011] [09:08:01] <yrashk>	debugging FFIs i fun
| [Thursday 17 February 2011] [09:08:03] <yrashk>	is*
| [Thursday 17 February 2011] [09:08:03] <yrashk>	Socket operation on non-socket
| [Thursday 17 February 2011] [09:08:04] <yrashk>	:D
| [Thursday 17 February 2011] [09:08:34] <sustrik>	what's needed imo is transitory period
| [Thursday 17 February 2011] [09:08:45] <sustrik>	when both APIs would be available
| [Thursday 17 February 2011] [09:09:32] <sustrik>	presumably, with 2.0 API being a lightweight wrapper over 3.0 like internals
| [Thursday 17 February 2011] [09:10:59] <yrashk>	hmm errno 156384765
| [Thursday 17 February 2011] [09:11:00] <yrashk>	:d
| [Thursday 17 February 2011] [09:11:08] <sustrik>	see zmq.h
| [Thursday 17 February 2011] [09:11:18] <yrashk>	trying
| [Thursday 17 February 2011] [09:11:37] <sustrik>	ETERM
| [Thursday 17 February 2011] [09:11:55] <sustrik>	that means the context was already closed
| [Thursday 17 February 2011] [09:12:03] <yrashk>	ETERM
| [Thursday 17 February 2011] [09:12:04] <yrashk>	ya
| [Thursday 17 February 2011] [09:15:31] <sustrik>	mikko: are you here by chance
| [Thursday 17 February 2011] [09:15:36] <sustrik>	?
| [Thursday 17 February 2011] [09:15:38] <mikko>	yes
| [Thursday 17 February 2011] [09:16:07] <sustrik>	are there any changes needed to the build system in case the names of exported symbols change?
| [Thursday 17 February 2011] [09:16:24] <mikko>	shouldn't be
| [Thursday 17 February 2011] [09:16:37] <sustrik>	the visibility thing?
| [Thursday 17 February 2011] [09:16:43] <mikko>	thats per symbol
| [Thursday 17 February 2011] [09:16:48] <mikko>	take a look at zmq.h
| [Thursday 17 February 2011] [09:17:00] <sustrik>	ZMQ_EXPORT, right?
| [Thursday 17 February 2011] [09:17:07] <mikko>	yes
| [Thursday 17 February 2011] [09:17:17] <sustrik>	mikko: thanks
| [Thursday 17 February 2011] [09:17:23] <mikko>	are you looking to support two apis in one lib?
| [Thursday 17 February 2011] [09:17:32] <sustrik>	yep
| [Thursday 17 February 2011] [09:17:43] <mikko>	hmm
| [Thursday 17 February 2011] [09:17:52] <sustrik>	still the option of exporting _zmq_init etc. seems most viable
| [Thursday 17 February 2011] [09:18:08] <mikko>	why do you need to support two versions in one library?
| [Thursday 17 February 2011] [09:18:09] <sustrik>	and supplying simple zmq_init etc. wrappers in the header file
| [Thursday 17 February 2011] [09:18:34] <sustrik>	otherwise the migration to 3.0 API would have to be done in one go
| [Thursday 17 February 2011] [09:18:55] <sustrik>	which is almost impossible, given all the bindings etc.
| [Thursday 17 February 2011] [09:19:50] <yrashk>	heh
| [Thursday 17 February 2011] [09:19:52] <yrashk>	almost there!
| [Thursday 17 February 2011] [09:20:29] <mikko>	i dont know why but i have some doubts about the approach
| [Thursday 17 February 2011] [09:20:47] <mikko>	it sounds complex
| [Thursday 17 February 2011] [09:21:09] <sustrik>	any better idea?
| [Thursday 17 February 2011] [09:21:23] <yrashk>	ok
| [Thursday 17 February 2011] [09:21:24] <yrashk>	works
| [Thursday 17 February 2011] [09:21:27] <yrashk>	:]
| [Thursday 17 February 2011] [09:21:29] <yrashk>	that was fast
| [Thursday 17 February 2011] [09:21:31] <sustrik>	new binding?
| [Thursday 17 February 2011] [09:21:34] <yrashk>	yep
| [Thursday 17 February 2011] [09:21:42] <pieterh_>	sustrik, transitional API sounds a good idea, it can be an optional header you include
| [Thursday 17 February 2011] [09:21:50] <sustrik>	your keyboard must have caught fire in the process :)
| [Thursday 17 February 2011] [09:21:53] <yrashk>	currently with block receive but I am going to solve this by using 2nd thread and 0mq inproc
| [Thursday 17 February 2011] [09:21:59] <yrashk>	sustrik: no, my kbd is cool
| [Thursday 17 February 2011] [09:22:05] <pieterh_>	i think that's the a world record for a new binding
| [Thursday 17 February 2011] [09:22:31] <yrashk>	it's an incomplete binding
| [Thursday 17 February 2011] [09:22:35] <yrashk>	sockopts are not there yet
| [Thursday 17 February 2011] [09:22:45] <yrashk>	and non-blocking receive is not there yet, too
| [Thursday 17 February 2011] [09:22:47] <yrashk>	https://gist.github.com/6e203bc2aeb410b36532
| [Thursday 17 February 2011] [09:23:08] <sustrik>	still:
| [Thursday 17 February 2011] [09:23:09] <sustrik>	<yrashk> so ok it looks like I am writing a new erlang binding
| [Thursday 17 February 2011] [09:23:35] <sustrik>	at 14:33
| [Thursday 17 February 2011] [09:23:43] <sustrik>	15:21: works
| [Thursday 17 February 2011] [09:23:44] <pieterh_>	under 1 hour...
| [Thursday 17 February 2011] [09:24:08] <sustrik>	:)
| [Thursday 17 February 2011] [09:24:35] <sustrik>	pieterh_: the API shift is doable even now
| [Thursday 17 February 2011] [09:24:39] <pieterh_>	yup
| [Thursday 17 February 2011] [09:24:45] <pieterh_>	it can be done with macros in zmq.h
| [Thursday 17 February 2011] [09:24:51] <sustrik>	but maybe forking the stable should be done first
| [Thursday 17 February 2011] [09:24:57] <mikko>	sustrik: i guess not 
| [Thursday 17 February 2011] [09:25:10] <pieterh_>	yes, no new features before we fork...
| [Thursday 17 February 2011] [09:25:16] <sustrik>	ack
| [Thursday 17 February 2011] [09:25:44] <mikko>	when is master going to be open for radical changes?
| [Thursday 17 February 2011] [09:25:54] <yrashk>	sustrik: https://github.com/yrashk/ezmq
| [Thursday 17 February 2011] [09:25:58] <pieterh_>	mikko: are you in a hurry?
| [Thursday 17 February 2011] [09:26:15] <mikko>	pieterh_: no
| [Thursday 17 February 2011] [09:26:22] <sustrik>	yrashk: nice
| [Thursday 17 February 2011] [09:26:25] <sustrik>	any perf results?
| [Thursday 17 February 2011] [09:26:44] <pieterh_>	easymq, hehe
| [Thursday 17 February 2011] [09:26:48] <mikko>	this is the openpgm autotools build change
| [Thursday 17 February 2011] [09:27:01] <mikko>	which also includes update from openpgm 5.0.x to 5.1.x
| [Thursday 17 February 2011] [09:27:16] <pieterh_>	mikko: that does not risk introducing bugs IMO
| [Thursday 17 February 2011] [09:27:25] <pieterh_>	i'd get that into the master asap
| [Thursday 17 February 2011] [09:27:48] <mikko>	well, openpgm update is potentially risky (?)
| [Thursday 17 February 2011] [09:28:35] <pieterh_>	hmm, we didn't see any real issues with switch from openpgm2.x to 5.0.x...
| [Thursday 17 February 2011] [09:28:37] <pieterh_>	afair
| [Thursday 17 February 2011] [09:29:08] <pieterh_>	if you don't get that into master before we clone it, it'll be for 2.2 only
| [Thursday 17 February 2011] [09:29:12] <pieterh_>	as you like
| [Thursday 17 February 2011] [09:29:31] <mikko>	ok
| [Thursday 17 February 2011] [09:29:36] <sustrik>	pieterh_: btw, are you not going to fork from a historic version?
| [Thursday 17 February 2011] [09:29:38] <mikko>	i'll have to check with steve-p
| [Thursday 17 February 2011] [09:29:41] <mikko>	steve-o
| [Thursday 17 February 2011] [09:29:53] <sustrik>	my feeling was that you want to fork pre-XPUB/XSUB version
| [Thursday 17 February 2011] [09:30:00] <pieterh_>	sustrik, nope, my plan is to fork head and then make releases as we collect fixes to it
| [Thursday 17 February 2011] [09:30:07] <sustrik>	ok
| [Thursday 17 February 2011] [09:30:23] <pieterh_>	we can disable XPUB/XSUB if needed (just the definitions, not the internals)
| [Thursday 17 February 2011] [09:30:48] <pieterh_>	that's a 2.2 feature, I guess
| [Thursday 17 February 2011] [09:31:00] <sustrik>	it's just a placeholder atm
| [Thursday 17 February 2011] [09:31:30] <pieterh_>	I've seen that
| [Thursday 17 February 2011] [09:31:43] <pieterh_>	so how do I get stuff off sys://log
| [Thursday 17 February 2011] [09:31:52] <pieterh_>	connect a SUB socket to it?
| [Thursday 17 February 2011] [09:31:55] <sustrik>	yes
| [Thursday 17 February 2011] [09:32:01] <pieterh_>	ok, trying that now...
| [Thursday 17 February 2011] [09:36:07] <cremes>	pieterh_: what's up?
| [Thursday 17 February 2011] [09:36:20] <pieterh_>	cremes: we found & nailed the real issue with mailboxes
| [Thursday 17 February 2011] [09:36:33] <pieterh_>	of course it's a 1-line fix :-)
| [Thursday 17 February 2011] [09:36:42] <cremes>	oh, of course!
| [Thursday 17 February 2011] [09:37:14] <pieterh_>	well, it's one line of magic from Martin... 
| [Thursday 17 February 2011] [09:37:19] <cremes>	has it been committed already?
| [Thursday 17 February 2011] [09:37:22] <pieterh_>	yup
| [Thursday 17 February 2011] [09:37:35] <cremes>	i'm going to look...
| [Thursday 17 February 2011] [09:39:00] <cremes>	launch_sibling became launch_child? that truly is magic
| [Thursday 17 February 2011] [09:39:34] <yrashk>	sustrik: no perfs yet, I haven't done 2nd thread non-block recv yet anyway
| [Thursday 17 February 2011] [09:39:40] <yrashk>	working on sockopts
| [Thursday 17 February 2011] [09:39:56] <pieterh_>	sustrik, ok, it works like a charm
| [Thursday 17 February 2011] [09:40:19] <pieterh_>	Compiling mailbugz...
| [Thursday 17 February 2011] [09:40:19] <pieterh_>	Linking mailbugz...
| [Thursday 17 February 2011] [09:40:19] <pieterh_>	E: (syslog) DUID: peer using non-unique identity - disconnected
| [Thursday 17 February 2011] [09:40:19] <pieterh_>	E: (syslog) DUID: 0x444945
| [Thursday 17 February 2011] [09:40:19] <pieterh_>	E: (syslog) DUID: "DIE"
| [Thursday 17 February 2011] [09:40:26] <sustrik>	yrashk: ack
| [Thursday 17 February 2011] [09:40:38] <pieterh_>	that message comes from session.cpp, and object.cpp formats and prints the identity
| [Thursday 17 February 2011] [09:40:49] <pieterh_>	and a thread in mailbugz catches and reports the error
| [Thursday 17 February 2011] [09:41:22] <sustrik>	pieterh_: it should be one log recoed imo
| [Thursday 17 February 2011] [09:41:26] <sustrik>	record
| [Thursday 17 February 2011] [09:41:42] <pieterh_>	sustrik, sure, this is a proof of concept
| [Thursday 17 February 2011] [09:42:02] <sustrik>	in the future it would be nice to add IP address of the offending peer
| [Thursday 17 February 2011] [09:42:07] <pieterh_>	and etc...
| [Thursday 17 February 2011] [09:42:09] <pieterh_>	yes
| [Thursday 17 February 2011] [09:42:52] <pieterh_>	my C++ skills are too poor to do this properly
| [Thursday 17 February 2011] [09:43:02] <sustrik>	use raw C
| [Thursday 17 February 2011] [09:43:09] <pieterh_>	done that, np
| [Thursday 17 February 2011] [09:43:35] <pieterh_>	ok, will add IP address and make a single string
| [Thursday 17 February 2011] [09:43:51] <sustrik>	the IP addr stuff may be tricky imo
| [Thursday 17 February 2011] [09:44:18] <pieterh_>	does the engine not have a socket it can look at?
| [Thursday 17 February 2011] [09:44:26] <sustrik>	it does
| [Thursday 17 February 2011] [09:44:34] <sustrik>	but there no code to do that
| [Thursday 17 February 2011] [09:44:41] <pieterh_>	ok, well, one step at a time
| [Thursday 17 February 2011] [09:44:45] <sustrik>	exactly
| [Thursday 17 February 2011] [09:44:50] <pieterh_>	the first thing is to get end-to-end reporting in place
| [Thursday 17 February 2011] [09:44:54] <pieterh_>	then we can extend and improve it...
| [Thursday 17 February 2011] [09:45:48] <pieterh_>	not sure if bindings should read sys://log themselves or leave this to apps...
| [Thursday 17 February 2011] [09:46:12] <pieterh_>	in latter case, people just won't use it and will still have the same 'what is happening?' issue
| [Thursday 17 February 2011] [09:46:53] <sustrik>	it's up to binding developers imo
| [Thursday 17 February 2011] [09:47:19] <pieterh_>	some thought and consistent policy would help IMO
| [Thursday 17 February 2011] [09:49:03] <sustrik>	i would leave binding as thin as possible personally
| [Thursday 17 February 2011] [09:49:22] <sustrik>	=> no need to change anything
| [Thursday 17 February 2011] [09:55:48] <pieterh_>	there is one very small issue with the syslog design
| [Thursday 17 February 2011] [09:55:58] <pieterh_>	if you get an error right at startup, you won't see it
| [Thursday 17 February 2011] [09:56:11] <pieterh_>	due to the async connect issue with pubsub
| [Thursday 17 February 2011] [09:57:12] <sustrik>	rightr
| [Thursday 17 February 2011] [09:57:20] <pieterh_>	since I'm conflating errors (sending only the first of a series), this means sometimes nothing shows
| [Thursday 17 February 2011] [09:57:35] <pieterh_>	I
| [Thursday 17 February 2011] [09:57:49] <pieterh_>	I've no solution in mind but it's an interesting use case
| [Thursday 17 February 2011] [09:58:26] <sustrik>	are you subscribing for logs immediately after zmq_init()
| [Thursday 17 February 2011] [09:58:27] <sustrik>	?
| [Thursday 17 February 2011] [09:58:45] <pieterh_>	yes
| [Thursday 17 February 2011] [09:59:01] <sustrik>	that should not happen imo
| [Thursday 17 February 2011] [09:59:05] <sustrik>	likely a bug...
| [Thursday 17 February 2011] [09:59:06] <pieterh_>	hang on, there should be no delay over inproc...
| [Thursday 17 February 2011] [09:59:18] <pieterh_>	i'm mistaken, it's because I'm using two threads
| [Thursday 17 February 2011] [09:59:39] <pieterh_>	ok, easily solved, connect subscriber in main thread and then pass to background thread
| [Thursday 17 February 2011] [09:59:48] <sustrik>	ack
| [Thursday 17 February 2011] [10:00:58] <pieterh_>	ack, that fixes it
| [Thursday 17 February 2011] [10:01:36] <yrashk>	when I am doing getsockopts on ZMQ_IDENTITY, should I allocate option value? 
| [Thursday 17 February 2011] [10:02:10] <yrashk>	sorry for dumb questions, was working through the whole night
| [Thursday 17 February 2011] [10:02:50] <sustrik>	yrashk: you supply a buffer
| [Thursday 17 February 2011] [10:02:59] <sustrik>	0mq will fill the identity into the buffer
| [Thursday 17 February 2011] [10:03:20] <yrashk>	gothca, will do 255 buff
| [Thursday 17 February 2011] [10:05:56] <yrashk>	I am not sure I really understand this IDENTITY thing yet, though
| [Thursday 17 February 2011] [10:08:37] <yrashk>	I am getting garbage from there :S
| [Thursday 17 February 2011] [10:08:45] <yrashk>	even though I set it to a binary value beforehand
| [Thursday 17 February 2011] [10:08:53] <yrashk>	lol, debugging stuff at 7am is fun
| [Thursday 17 February 2011] [10:12:13] <pieterh_>	yrashk, then tomorrow you're like 'wha...?'
| [Thursday 17 February 2011] [10:12:25] <yrashk>	well
| [Thursday 17 February 2011] [10:12:27] <yrashk>	that's a given
| [Thursday 17 February 2011] [10:12:32] <yrashk>	but anyway I fixed something
| [Thursday 17 February 2011] [10:12:33] <yrashk>	and it works
| [Thursday 17 February 2011] [10:13:03] <yrashk>	so what's left?
| [Thursday 17 February 2011] [10:13:07] <yrashk>	I guess non-blocking receive
| [Thursday 17 February 2011] [10:13:09] <yrashk>	and nicer API
| [Thursday 17 February 2011] [10:28:43] <pieterh_>	sustrik, ok, patch sent for the syslog interface
| [Thursday 17 February 2011] [10:28:58] <pieterh_>	it's pretty brutal, will benefit from some C++ review 
| [Thursday 17 February 2011] [10:34:34] <yrashk>	horaay
| [Thursday 17 February 2011] [10:34:43] <yrashk>	even pub/sub aleady works
| [Thursday 17 February 2011] [10:35:05] <sustrik>	:)
| [Thursday 17 February 2011] [10:35:24] <yrashk>	https://gist.github.com/36cde07be28d3dad39a7
| [Thursday 17 February 2011] [10:35:30] <yrashk>	and I added nicer higher level API
| [Thursday 17 February 2011] [10:36:06] 	 * sustrik is looking forward for the perf results
| [Thursday 17 February 2011] [10:37:46] <yrashk>	I am actually porting those right now
| [Thursday 17 February 2011] [10:38:24] <sustrik>	!
| [Thursday 17 February 2011] [10:39:19] <yrashk>	it probably is much worse
| [Thursday 17 February 2011] [10:39:32] <yrashk>	since it's currenly blocking
| [Thursday 17 February 2011] [10:39:38] <yrashk>	haha
| [Thursday 17 February 2011] [10:39:39] <yrashk>	the same
| [Thursday 17 February 2011] [10:39:40] <yrashk>	mean throughput: 30938.745584228862 [msg/s]
| [Thursday 17 February 2011] [10:39:54] <yrashk>	still my API is nice :-P
| [Thursday 17 February 2011] [10:41:48] <yrashk>	I increased message size to 100 bytes
| [Thursday 17 February 2011] [10:41:53] <yrashk>	and now it's faster:
| [Thursday 17 February 2011] [10:41:53] <yrashk>	mean throughput: 40136.63795933773 [msg/s]
| [Thursday 17 February 2011] [10:42:45] <sustrik>	what's going on there?
| [Thursday 17 February 2011] [10:42:49] <yrashk>	1000 bytes gives 38K
| [Thursday 17 February 2011] [10:43:25] <yrashk>	so I wrote this nice NIF API for nothing? :-(
| [Thursday 17 February 2011] [10:43:33] <sustrik>	is it possible that erlang itself is so slow as not to be able to execute the loop faster than that?
| [Thursday 17 February 2011] [10:43:35] <yrashk>	actually 40K for 1000 bytes
| [Thursday 17 February 2011] [10:43:47] <sustrik>	still, it should b 400k
| [Thursday 17 February 2011] [10:43:57] <sustrik>	at least
| [Thursday 17 February 2011] [10:44:00] <yrashk>	true
| [Thursday 17 February 2011] [10:44:05] <yrashk>	I am thinking why this is happening
| [Thursday 17 February 2011] [10:44:14] <yrashk>	I cutted driver communications out
| [Thursday 17 February 2011] [10:44:24] <yrashk>	so now it's NIF
| [Thursday 17 February 2011] [10:44:53] <sustrik>	can you benchmark average duration spent in the NIF
| [Thursday 17 February 2011] [10:44:56] <sustrik>	?
| [Thursday 17 February 2011] [10:45:02] <sustrik>	say in send?
| [Thursday 17 February 2011] [10:45:15] <yrashk>	or may be even better in recv?
| [Thursday 17 February 2011] [10:45:23] <yrashk>	send should be faster anyway, no?
| [Thursday 17 February 2011] [10:45:33] <yrashk>	getting 44K on 1 bytes
| [Thursday 17 February 2011] [10:45:53] <sustrik>	recv is more problematic, because it can be slow either because it itself is slow or because sender is slow
| [Thursday 17 February 2011] [10:46:12] <yrashk>	added noblock to sender
| [Thursday 17 February 2011] [10:46:31] <sustrik>	so, if you are able to find out how much time is spent in send
| [Thursday 17 February 2011] [10:46:40] <sustrik>	it may turn out that it's 10%
| [Thursday 17 February 2011] [10:46:49] <sustrik>	that would mean that erlang itself is slow
| [Thursday 17 February 2011] [10:46:51] <yrashk>	well I can do that
| [Thursday 17 February 2011] [10:47:05] <yrashk>	still I will probably not delete my binding
| [Thursday 17 February 2011] [10:47:10] <sustrik>	or 95% which would mean erlzmq is slow
| [Thursday 17 February 2011] [10:47:12] <yrashk>	as it's quite nice actually
| [Thursday 17 February 2011] [10:47:17] <sustrik>	no, don't do that
| [Thursday 17 February 2011] [10:47:26] <sustrik>	it may come handy one day
| [Thursday 17 February 2011] [10:48:38] <cremes>	erlang isn't known for execution performance; it's known for massive concurrency
| [Thursday 17 February 2011] [10:49:00] <cremes>	if the problem isn't parallelizable, perf isn't usually too impressive
| [Thursday 17 February 2011] [10:49:20] <yrashk>	it spends 2-3 microseconds in that call
| [Thursday 17 February 2011] [10:49:22] <yrashk>	(recv)
| [Thursday 17 February 2011] [10:50:42] <sustrik>	that should mean 330,000-500,000 msgs/sec
| [Thursday 17 February 2011] [10:51:08] <yrashk>	may be my math is wrong?
| [Thursday 17 February 2011] [10:51:09] <yrashk>	;)
| [Thursday 17 February 2011] [10:51:28] <sustrik>	yes, the math there is tricky
| [Thursday 17 February 2011] [10:51:38] <yrashk>	but it does spend up to 20-30 seconds or so
| [Thursday 17 February 2011] [10:51:41] <sustrik>	due to rounding errors
| [Thursday 17 February 2011] [10:51:45] <yrashk>	for a million messages
| [Thursday 17 February 2011] [10:51:53] <sustrik>	than the result looks right
| [Thursday 17 February 2011] [10:52:09] <yrashk>	real	0m31.754s
| [Thursday 17 February 2011] [10:52:10] <yrashk>	user	0m14.646s
| [Thursday 17 February 2011] [10:52:10] <yrashk>	sys	0m18.121s
| [Thursday 17 February 2011] [10:52:11] <sustrik>	the problem is that most of the time is spent *out* of erlzmq
| [Thursday 17 February 2011] [10:52:17] <yrashk>	well it is ezmq now
| [Thursday 17 February 2011] [10:52:23] <yrashk>	I rewrote it from scratch
| [Thursday 17 February 2011] [10:52:27] <yrashk>	;)
| [Thursday 17 February 2011] [10:52:33] <sustrik>	:)
| [Thursday 17 February 2011] [10:52:54] <sustrik>	those 2-3 microseconds are spent in NIF
| [Thursday 17 February 2011] [10:52:57] <sustrik>	or 0MQ itself?
| [Thursday 17 February 2011] [10:53:08] <yrashk>	NIF call
| [Thursday 17 February 2011] [10:53:24] <sustrik>	can you check the same on the send() call?
| [Thursday 17 February 2011] [10:53:35] <yrashk>	sure
| [Thursday 17 February 2011] [10:54:18] <yrashk>	10-15 microseconds
| [Thursday 17 February 2011] [10:54:31] <yrashk>	well even 8-15
| [Thursday 17 February 2011] [10:55:05] <sustrik>	with 40k msgs/sec
| [Thursday 17 February 2011] [10:55:22] <sustrik>	the time for single message is 25 usec
| [Thursday 17 February 2011] [10:55:32] <yrashk>	a little less without noblock
| [Thursday 17 February 2011] [10:55:41] <sustrik>	8-15 can be attributed to ezmq
| [Thursday 17 February 2011] [10:55:57] <sustrik>	remaining 10 are either erlang itself or the time measurement
| [Thursday 17 February 2011] [10:56:13] <yrashk>	still 8-15 is pretty fast, right?
| [Thursday 17 February 2011] [10:56:53] <sustrik>	it equals to 125k-666k msgs/sec
| [Thursday 17 February 2011] [10:57:48] <yrashk>	the almost empty cycle takes about 890645 microsecond
| [Thursday 17 February 2011] [10:58:03] <sustrik>	1M iterations?
| [Thursday 17 February 2011] [10:58:06] <yrashk>	yep
| [Thursday 17 February 2011] [10:58:15] <yrashk>	well, it's not empty
| [Thursday 17 February 2011] [10:58:18] <yrashk>	but almost
| [Thursday 17 February 2011] [10:58:23] <sustrik>	0.8 usec per iteration
| [Thursday 17 February 2011] [10:58:28] <sustrik>	that's reasonable
| [Thursday 17 February 2011] [10:58:41] <sustrik>	so what's the rest of the time spent on?
| [Thursday 17 February 2011] [10:58:45] <yrashk>	a little bit slower with integer value in it
| [Thursday 17 February 2011] [10:58:49] <yrashk>	I have no idea yet
| [Thursday 17 February 2011] [10:59:03] <sustrik>	cycle is 25 used long
| [Thursday 17 February 2011] [10:59:10] <sustrik>	8-15usec in NIF
| [Thursday 17 February 2011] [10:59:18] <sustrik>	0.8 the iteration itself
| [Thursday 17 February 2011] [10:59:25] <sustrik>	still some 10 usecs are missing
| [Thursday 17 February 2011] [10:59:31] <yrashk>	yup
| [Thursday 17 February 2011] [10:59:35] <yrashk>	you mean on send, right?
| [Thursday 17 February 2011] [10:59:43] <sustrik>	yes
| [Thursday 17 February 2011] [11:00:06] <yrashk>	right
| [Thursday 17 February 2011] [11:00:10] <yrashk>	I have no idea :)
| [Thursday 17 February 2011] [11:00:10] <sustrik>	maybe send is fast
| [Thursday 17 February 2011] [11:00:29] <sustrik>	how long does sending 1000000 msgs take?
| [Thursday 17 February 2011] [11:00:41] <sustrik>	measured before calling zmq_term()
| [Thursday 17 February 2011] [11:01:25] <sustrik>	(zmq_term waits for messages to be actually pushed to the wire)
| [Thursday 17 February 2011] [11:01:45] <yrashk>	lets see
| [Thursday 17 February 2011] [11:01:46] <sustrik>	(what we are interested in is how fast is erlang/ezmq able to push messages to 0mq)
| [Thursday 17 February 2011] [11:01:55] <yrashk>	I am measure the whole script timing
| [Thursday 17 February 2011] [11:02:04] <yrashk>	measuring*
| [Thursday 17 February 2011] [11:02:21] <yrashk>	25 secds
| [Thursday 17 February 2011] [11:02:22] <yrashk>	secs
| [Thursday 17 February 2011] [11:02:36] <yrashk>	real	0m25.188s
| [Thursday 17 February 2011] [11:02:36] <yrashk>	user	0m26.410s
| [Thursday 17 February 2011] [11:02:36] <yrashk>	sys	0m22.533s
| [Thursday 17 February 2011] [11:03:45] <sustrik>	that's before zmq_term is called, right?
| [Thursday 17 February 2011] [11:04:30] <sustrik>	that's 40k msgs/sec  i.e. 25 usec per message
| [Thursday 17 February 2011] [11:04:46] <yrashk>	no, not before
| [Thursday 17 February 2011] [11:05:05] <mikko>	are you setting linger to 0
| [Thursday 17 February 2011] [11:05:07] <mikko>	?
| [Thursday 17 February 2011] [11:06:07] <yrashk>	def not explicitly
| [Thursday 17 February 2011] [11:06:17] <sustrik>	right, setting linger to 0 would cause measuring only pushing the messages to 0mq
| [Thursday 17 February 2011] [11:06:21] <yrashk>	just got 52K messages per sec
| [Thursday 17 February 2011] [11:06:38] <yrashk>	also, 14249556 microseconds to send
| [Thursday 17 February 2011] [11:06:44] <yrashk>	before term
| [Thursday 17 February 2011] [11:07:11] <yrashk>	that is 14 seconds
| [Thursday 17 February 2011] [11:07:15] <yrashk>	now even 13
| [Thursday 17 February 2011] [11:07:21] <sustrik>	ie. 14 usec per message
| [Thursday 17 February 2011] [11:07:22] <yrashk>	and 67K messages
| [Thursday 17 February 2011] [11:07:27] <yrashk>	and I am not changing anything
| [Thursday 17 February 2011] [11:07:35] <sustrik>	with 8-15 in NIF
| [Thursday 17 February 2011] [11:07:47] <sustrik>	that sounds more or less reasonable
| [Thursday 17 February 2011] [11:08:06] <sustrik>	assuming that 8 is an outlayer
| [Thursday 17 February 2011] [11:08:16] <yrashk>	well I cant measure exactly NIF timing, but it's very close to that
| [Thursday 17 February 2011] [11:08:19] <sustrik>	and average values are around 14-15
| [Thursday 17 February 2011] [11:08:34] <yrashk>	avg seemed to be around 11-13
| [Thursday 17 February 2011] [11:08:48] <yrashk>	anyway I am getting even 67K messages
| [Thursday 17 February 2011] [11:08:48] <sustrik>	that seems ok
| [Thursday 17 February 2011] [11:08:58] <yrashk>	I was not able to see that with erlzmq
| [Thursday 17 February 2011] [11:09:18] <sustrik>	14.9 usec/msg
| [Thursday 17 February 2011] [11:09:54] <sustrik>	can you do ezmq/c perf test as before?
| [Thursday 17 February 2011] [11:10:12] <sustrik>	ezmq local + c remote
| [Thursday 17 February 2011] [11:10:15] <sustrik>	and vice versa?
| [Thursday 17 February 2011] [11:10:27] <yrashk>	sure just let me finish 10mln messages test
| [Thursday 17 February 2011] [11:10:35] <sustrik>	sure
| [Thursday 17 February 2011] [11:10:40] <yrashk>	still running...
| [Thursday 17 February 2011] [11:11:11] <yrashk>	that's likely to be like 3 mins
| [Thursday 17 February 2011] [11:11:12] <yrashk>	:D
| [Thursday 17 February 2011] [11:11:31] <yrashk>	whoa
| [Thursday 17 February 2011] [11:11:31] <yrashk>	mean throughput: 71015.7477562681 [msg/s]
| [Thursday 17 February 2011] [11:11:34] <yrashk>	71K
| [Thursday 17 February 2011] [11:12:48] <yrashk>	with C remote:
| [Thursday 17 February 2011] [11:12:48] <yrashk>	mean throughput: 119761.54040167542 [msg/s]
| [Thursday 17 February 2011] [11:13:07] <yrashk>	twice as good as it was with erlzmq btw
| [Thursday 17 February 2011] [11:13:08] <yrashk>	:-P
| [Thursday 17 February 2011] [11:13:49] <yrashk>	mean throughput: 126762.65050054133 [msg/s]
| [Thursday 17 February 2011] [11:14:03] <yrashk>	it looks like it warms up more every time I run it again
| [Thursday 17 February 2011] [11:14:28] <yrashk>	=_
| [Thursday 17 February 2011] [11:15:44] <sustrik>	heh
| [Thursday 17 February 2011] [11:16:20] <yrashk>	one thing I know for sure
| [Thursday 17 February 2011] [11:16:24] <yrashk>	it's faster than erlzmq
| [Thursday 17 February 2011] [11:16:34] <yrashk>	I just retested C/erlzmq: it tops at 80K/msgs
| [Thursday 17 February 2011] [11:16:45] <yrashk>	while C/ezmq tops at about 120K msgs
| [Thursday 17 February 2011] [11:17:26] <sustrik>	nice
| [Thursday 17 February 2011] [11:18:00] <yrashk>	and I ony spent... like 2 hours with it?
| [Thursday 17 February 2011] [11:18:05] <sustrik>	so maybe just write an email about your experiments to the ML
| [Thursday 17 February 2011] [11:18:08] <sustrik>	and have some sleep
| [Thursday 17 February 2011] [11:18:19] <yrashk>	I am too lazy to write emails right now
| [Thursday 17 February 2011] [11:18:25] <sustrik>	sure
| [Thursday 17 February 2011] [11:18:40] <yrashk>	well hopefully ezmq will be of use for somebody
| [Thursday 17 February 2011] [11:18:45] <yrashk>	since it's faster
| [Thursday 17 February 2011] [11:19:01] <sustrik>	we can even have a look at why the call to NIF takes 15 usec later on
| [Thursday 17 February 2011] [11:19:14] <yrashk>	yeah it's quite long
| [Thursday 17 February 2011] [11:19:34] <yrashk>	C version takes no time at all
| [Thursday 17 February 2011] [11:19:48] <sustrik>	something like 0.3 usec
| [Thursday 17 February 2011] [11:20:02] <sustrik>	so there's quite a lot of overhead that can be possibly eliminated
| [Thursday 17 February 2011] [11:20:04] <yrashk>	for all messages
| [Thursday 17 February 2011] [11:20:23] <sustrik>	for 1-byte messages
| [Thursday 17 February 2011] [11:20:30] <yrashk>	right
| [Thursday 17 February 2011] [11:20:45] <yrashk>	also may be it is not batching for some reason in this scenario?
| [Thursday 17 February 2011] [11:20:49] <yrashk>	could that happen?
| [Thursday 17 February 2011] [11:21:34] <sustrik>	batching does not occur only if messages are passed slower than the underlying network stack can send them
| [Thursday 17 February 2011] [11:21:51] <sustrik>	which can be the case here
| [Thursday 17 February 2011] [11:22:01] <sustrik>	however, if we speed up the erlzmq part
| [Thursday 17 February 2011] [11:22:09] <sustrik>	the batching will kick in
| [Thursday 17 February 2011] [11:22:39] <yrashk>	I think this is the case
| [Thursday 17 February 2011] [11:22:51] <yrashk>	we send whole packets for every byte
| [Thursday 17 February 2011] [11:23:11] <sustrik>	possible
| [Thursday 17 February 2011] [11:23:38] <sustrik>	but only way to make it not happen is to speed up the sender
| [Thursday 17 February 2011] [11:23:45] <sustrik>	i.e. erlang+ezmq
| [Thursday 17 February 2011] [11:24:37] <yrashk>	yup
| [Thursday 17 February 2011] [11:25:22] <yrashk>	yet I have no idea why this is so slow
| [Thursday 17 February 2011] [11:25:29] <yrashk>	well,erlang is indeed not very fast
| [Thursday 17 February 2011] [11:25:31] <yrashk>	but still
| [Thursday 17 February 2011] [11:27:23] <yrashk>	this code https://github.com/yrashk/ezmq/blob/master/c_src/ezmq_nif.c#L250 looks clean enough by me
| [Thursday 17 February 2011] [11:27:32] <yrashk>	to not cause *too* much trouble
| [Thursday 17 February 2011] [11:30:05] <sustrik>	yes, this is how most bindings look like
| [Thursday 17 February 2011] [11:30:20] <sustrik>	erlzmq is exceptional in its complexity
| [Thursday 17 February 2011] [11:30:29] <yrashk>	mine is much simpler, eh?
| [Thursday 17 February 2011] [11:30:34] <sustrik>	yup
| [Thursday 17 February 2011] [11:30:44] <yrashk>	and faster [grin]
| [Thursday 17 February 2011] [11:30:56] <sustrik>	hi5!
| [Thursday 17 February 2011] [11:44:24] <yrashk>	hm may be binary allocation isn't that fast
| [Thursday 17 February 2011] [11:44:51] <yrashk>	there is a way to tell erlang to use existing memory region as a binary without allocating it
| [Thursday 17 February 2011] [11:45:05] <yrashk>	but it means it will get into erlang gc
| [Thursday 17 February 2011] [11:45:16] <yrashk>	and should not be altered until erlang collects it
| [Thursday 17 February 2011] [11:45:26] <yrashk>	sustrik: is there a way to do that with 0mq?
| [Thursday 17 February 2011] [11:46:03] <yrashk>	should I not close message on recv and only close in a finalizer called by erlang gc?
| [Thursday 17 February 2011] [11:47:10] <sustrik>	yrashk: i don't follow
| [Thursday 17 February 2011] [11:47:17] <sustrik>	inside the NIF you get a message
| [Thursday 17 February 2011] [11:47:23] <yrashk>	yes
| [Thursday 17 February 2011] [11:47:27] <yrashk>	then I copy and close it
| [Thursday 17 February 2011] [11:47:36] <sustrik>	sounds ok
| [Thursday 17 February 2011] [11:47:43] <yrashk>	instead there is a possibility that I can use another API (that I haven't used before)
| [Thursday 17 February 2011] [11:47:54] <yrashk>	that allows me to reuse existing memory region as a binary
| [Thursday 17 February 2011] [11:48:03] <yrashk>	instead of copying it and allocating binary
| [Thursday 17 February 2011] [11:48:19] <yrashk>	and I can attach a destructor to such a binary
| [Thursday 17 February 2011] [11:48:26] <yrashk>	which can call msg_close
| [Thursday 17 February 2011] [11:48:37] <yrashk>	I am just thinking how good or bad this approach is
| [Thursday 17 February 2011] [11:49:18] <sustrik>	it's not bad, but it'll get pretty complex soon
| [Thursday 17 February 2011] [11:49:36] <sustrik>	i would just stick with the existing copy semantics at the moment
| [Thursday 17 February 2011] [11:49:56] <yrashk>	I am just trying to understand where's the bottleneck
| [Thursday 17 February 2011] [11:50:11] <yrashk>	btw it looks like ezmq got more or less consistently 2x faster than erlzmq
| [Thursday 17 February 2011] [11:50:16] <yrashk>	with some minor changes
| [Thursday 17 February 2011] [11:50:29] <yrashk>	at least I am constantly getting 60-70K
| [Thursday 17 February 2011] [11:50:32] <sustrik>	nice
| [Thursday 17 February 2011] [11:51:07] <sustrik>	handling native memory from VM tends to be pretty messy
| [Thursday 17 February 2011] [11:51:24] <yrashk>	I know
| [Thursday 17 February 2011] [11:51:31] <sustrik>	anyway, 15 usec for an allocation seems too much
| [Thursday 17 February 2011] [11:51:39] <yrashk>	well
| [Thursday 17 February 2011] [11:51:45] <yrashk>	I don't know what exactly takes 15 usec
| [Thursday 17 February 2011] [11:51:58] <sustrik>	i would rather guess scheduling is kicking in or something like that
| [Thursday 17 February 2011] [11:52:03] <yrashk>	I am just reading the code and fantasizing
| [Thursday 17 February 2011] [11:52:13] <yrashk>	well when it enters C part
| [Thursday 17 February 2011] [11:52:20] <yrashk>	there is no scheduling happening whatsoevr
| [Thursday 17 February 2011] [11:52:52] <sustrik>	doesn't the erlang thread get into wait state
| [Thursday 17 February 2011] [11:53:07] <sustrik>	while dedicated NIF thread does the work?
| [Thursday 17 February 2011] [11:53:09] <yrashk>	well current scheduler waits until C function ends
| [Thursday 17 February 2011] [11:53:18] <yrashk>	there's no dedicated NIF thread
| [Thursday 17 February 2011] [11:53:22] <yrashk>	it's in the scheduler's thread
| [Thursday 17 February 2011] [11:53:41] <sustrik>	ok
| [Thursday 17 February 2011] [11:53:52] <sustrik>	that should not take 15 usec either
| [Thursday 17 February 2011] [11:54:02] <yrashk>	no
| [Thursday 17 February 2011] [11:54:10] <yrashk>	I am really at loss here
| [Thursday 17 February 2011] [11:54:12] <sustrik>	maybe just locking and unlocking a mutex or somesuch
| [Thursday 17 February 2011] [11:54:15] <yrashk>	I don't quite get it
| [Thursday 17 February 2011] [11:54:16] <sustrik>	~1 usec
| [Thursday 17 February 2011] [11:54:53] <yrashk>	NIFs are pretty much like BIFs, implemented directly in the VMs opcode interpreter
| [Thursday 17 February 2011] [11:55:38] <sustrik>	can we do measurements in both erlang and ezmq?
| [Thursday 17 February 2011] [11:55:51] <sustrik>	1. before NIF is called
| [Thursday 17 February 2011] [11:55:57] <sustrik>	2. when C code is invoked
| [Thursday 17 February 2011] [11:56:06] <sustrik>	3. when C code is ready
| [Thursday 17 February 2011] [11:56:10] <yrashk>	btw time meas. takes time too
| [Thursday 17 February 2011] [11:56:19] <sustrik>	4. when erlang resumes execution
| [Thursday 17 February 2011] [11:56:30] <sustrik>	yes
| [Thursday 17 February 2011] [11:56:43] <sustrik>	something like readeing TSC is preferable
| [Thursday 17 February 2011] [11:56:54] <sustrik>	however, i am not sure it's available from erlang
| [Thursday 17 February 2011] [11:56:59] <yrashk>	TSC?
| [Thursday 17 February 2011] [11:57:15] <sustrik>	processor tick count
| [Thursday 17 February 2011] [11:58:15] <sustrik>	but we don't to do that now
| [Thursday 17 February 2011] [11:58:22] <sustrik>	let's use just standard time measurement
| [Thursday 17 February 2011] [11:58:44] <sustrik>	even if single measurement takes 1 usec
| [Thursday 17 February 2011] [11:59:05] <sustrik>	the original 15 usecs should still be visible
| [Thursday 17 February 2011] [12:01:26] <yrashk>	ya
| [Thursday 17 February 2011] [12:02:00] <yrashk>	I usually prefer to think about potential cause of a problem, sometimes logic beats brutal force
| [Thursday 17 February 2011] [12:02:03] <yrashk>	:D
| [Thursday 17 February 2011] [12:04:33] <sustrik>	my experience with tuning is that in most cases you are very surprised when you find out where the bottleneck is
| [Thursday 17 February 2011] [12:05:00] <yrashk>	true
| [Thursday 17 February 2011] [12:07:06] <yrashk>	damn my macbook air is much slower
| [Thursday 17 February 2011] [12:08:10] <yrashk>	...than my dual quad core mac pro :D
| [Thursday 17 February 2011] [12:09:00] <guido_g>	how comes?
| [Thursday 17 February 2011] [12:09:04] <yrashk>	very weird
| [Thursday 17 February 2011] [12:09:09] <guido_g>	in deed
| [Thursday 17 February 2011] [12:09:15] <yrashk>	in bed
| [Thursday 17 February 2011] [12:09:53] <guido_g>	sustrik: any pgm changes between 2.1.0 und the current git?
| [Thursday 17 February 2011] [12:10:16] <guido_g>	updated zmq to git master and pgm stopped working
| [Thursday 17 February 2011] [12:10:26] <guido_g>	pgm receive
| [Thursday 17 February 2011] [12:10:30] <sustrik>	what's the problem?
| [Thursday 17 February 2011] [12:10:59] <guido_g>	epgm messages are not received anymore
| [Thursday 17 February 2011] [12:11:33] <guido_g>	restored the 2.1.0 from the tar and everything was back
| [Thursday 17 February 2011] [12:12:23] <guido_g>	plain amd64 linux (2.6.37) box
| [Thursday 17 February 2011] [12:15:19] <sustrik>	can you report the problem?
| [Thursday 17 February 2011] [12:15:25] <guido_g>	sure
| [Thursday 17 February 2011] [12:15:30] <sustrik>	thanks
| [Thursday 17 February 2011] [12:15:34] <guido_g>	going to write small tests
| [Thursday 17 February 2011] [12:16:02] <sustrik>	post a note to the ML so that steve-o is aware of the problem
| [Thursday 17 February 2011] [12:16:11] <guido_g>	maybe it's the python binding...
| [Thursday 17 February 2011] [12:16:23] <guido_g>	yepp
| [Thursday 17 February 2011] [12:16:24] <sustrik>	not likely imo
| [Thursday 17 February 2011] [12:16:37] <guido_g>	no, because i just switched libzmq
| [Thursday 17 February 2011] [12:17:20] <yrashk>	anyway I am off for a nap
| [Thursday 17 February 2011] [12:17:28] <yrashk>	sustrik: thanks a lot for your help!
| [Thursday 17 February 2011] [12:17:33] <guido_g>	good night!
| [Thursday 17 February 2011] [12:17:48] <yrashk>	more like morning here already
| [Thursday 17 February 2011] [12:17:49] <yrashk>	:D
| [Thursday 17 February 2011] [12:17:51] <yrashk>	thanks anyway
| [Thursday 17 February 2011] [12:32:09] <sustrik>	good night
| [Thursday 17 February 2011] [12:40:23] <eyeris>	Am I doing something incorrectly here, or is that "Resource temporarily unavailable" message related to some actual resource being in use? I've checked that port 5563 is not in use. What other resource could it be referring to? http://pastebin.com/SdxBiFAk
| [Thursday 17 February 2011] [12:40:42] <guido_g>	ouch
| [Thursday 17 February 2011] [12:41:05] <guido_g>	the test sender runs into an assert 
| [Thursday 17 February 2011] [12:41:27] <guido_g>	Assertion failed: rc == 0 (connect_session.cpp:82)
| [Thursday 17 February 2011] [12:43:05] <eyeris>	guido_g: in my code? I don't see that
| [Thursday 17 February 2011] [12:43:13] <guido_g>	no
| [Thursday 17 February 2011] [12:51:56] <guido_g>	mail sent
| [Thursday 17 February 2011] [12:58:02] <guido_g>	eyeris: it's a timing problem
| [Thursday 17 February 2011] [12:58:26] <guido_g>	the io thread simply does not have enough time to connect 
| [Thursday 17 February 2011] [12:59:17] <guido_g>	eyeris: https://gist.github.com/832259  <- works
| [Thursday 17 February 2011] [13:02:55] <eyeris>	I understand the idea behind what you're saying. In fact, I tried the sleep(1) before the loop before and it didn't work. Using your gist I get an error: Assertion failed: *tmpbuf > 0 (src/zmq_decoder.cpp:60)
| [Thursday 17 February 2011] [13:03:38] <guido_g>	ouch
| [Thursday 17 February 2011] [13:04:14] <guido_g>	i'm on zeromq 2.1.0 from the tarball and the latest pyzmq (git master)
| [Thursday 17 February 2011] [13:05:00] <eyeris>	I am on 2.0.10 from pypi
| [Thursday 17 February 2011] [13:05:28] <guido_g>	and zeromq version?
| [Thursday 17 February 2011] [13:05:54] <eyeris>	Same
| [Thursday 17 February 2011] [13:06:09] <guido_g>	explains the assertion
| [Thursday 17 February 2011] [13:06:31] <guido_g>	try to update zeromq to 2.1.0 (from the tarball)
| [Thursday 17 February 2011] [13:15:41] <eyeris>	Alright, I've built and installed 2.1.0 into /opt/zeromq
| [Thursday 17 February 2011] [13:15:53] <eyeris>	I can't figure out how to make pyzmq find it though
| [Thursday 17 February 2011] [13:16:13] <eyeris>	There doesn't seem to be a --with-zeromq (or similar) build switch
| [Thursday 17 February 2011] [13:16:48] <guido_g>	from where did you get zeromq before?
| [Thursday 17 February 2011] [13:16:53] <eyeris>	pypi
| [Thursday 17 February 2011] [13:17:03] <guido_g>	not pyzmq
| [Thursday 17 February 2011] [13:17:50] <eyeris>	http://pypi.python.org/pypi/pyzmq-static/2.0.10
| [Thursday 17 February 2011] [13:18:00] <guido_g>	ouch
| [Thursday 17 February 2011] [13:18:01] <eyeris>	That includes the lib
| [Thursday 17 February 2011] [13:19:24] <guido_g>	get rid of it and use the non-static version
| [Thursday 17 February 2011] [13:20:04] <guido_g>	install zeromq using the default settings (using /usr/local/lib)
| [Thursday 17 February 2011] [13:20:18] <guido_g>	then install the non-static pyzmq
| [Thursday 17 February 2011] [13:34:04] <eyeris>	Works now
| [Thursday 17 February 2011] [13:34:05] <eyeris>	Thanks
| [Thursday 17 February 2011] [13:55:48] <fbarriga>	hello everyone
| [Thursday 17 February 2011] [13:57:24] <fbarriga>	there is any trade off on using zmq for non critical latency ? (use it only because is comfortable)
| [Thursday 17 February 2011] [14:03:48] <pieterh>	hi fbarriga
| [Thursday 17 February 2011] [14:03:53] <fbarriga>	hi
| [Thursday 17 February 2011] [14:04:02] <pieterh>	0MQ makes great soup no matter how you slice it
| [Thursday 17 February 2011] [14:04:26] <pieterh>	its speed is just a bonus when you need it
| [Thursday 17 February 2011] [14:04:49] <pieterh>	what's your use case?
| [Thursday 17 February 2011] [14:06:06] <fbarriga>	because here I have a program (A) that receive data and send it to another (B) to process it. So I want to monitor B in a gui (C) and I don't need a fancy way to send data. But as I'm already using zmq for comunicate A and B, it can be a good idea to use it to comunicate with the gui
| [Thursday 17 February 2011] [14:06:58] <pieterh>	sure
| [Thursday 17 February 2011] [14:09:41] <fbarriga>	has anyone tested the latency of using an point-to-point channel v/s publisher/subscriber ?
| [Thursday 17 February 2011] [14:10:00] <pieterh>	it's the same, unless you ping-pong back
| [Thursday 17 February 2011] [14:14:49] <fbarriga>	but any difference ? not even 1 uS ?
| [Thursday 17 February 2011] [14:15:13] <pieterh>	over the same transport? depends how many messages you are sending, how large they are
| [Thursday 17 February 2011] [14:15:23] <pieterh>	it does not depend on the socket type
| [Thursday 17 February 2011] [14:16:00] <fbarriga>	using unix socket, thousands of msg with a size of 32 bytes
| [Thursday 17 February 2011] [14:16:31] <pieterh>	fbarriga: have you read the documentation yet? the Guide?
| [Thursday 17 February 2011] [14:17:11] <fbarriga>	umm a kind RTFM ?
| [Thursday 17 February 2011] [14:17:34] <pieterh>	no, I want to know how much you know about 0MQ
| [Thursday 17 February 2011] [14:17:45] <fbarriga>	I read it but not completely
| [Thursday 17 February 2011] [14:18:04] <pieterh>	'point to point channel' is not a 0MQ term
| [Thursday 17 February 2011] [14:18:14] <fbarriga>	Not too much, I have 2 publishers, one on C++ and other on python feeding a C++ program
| [Thursday 17 February 2011] [14:19:17] <pieterh>	i think your questions are beside the point
| [Thursday 17 February 2011] [14:19:26] <pieterh>	(latency)
| [Thursday 17 February 2011] [14:19:41] <pieterh>	if you are not actually worried about usecs, it's irrelevant what I say
| [Thursday 17 February 2011] [14:20:23] <staylor>	something I'm not very clear on, if I have a server bound to an XREQ with multiple clients bound to REP how exactly could I send a message to a specific client from the server side?  I'm not very clear on how the addressing works here.
| [Thursday 17 February 2011] [14:20:28] <pieterh>	the usual rule is measure it, don't trust others' opinions
| [Thursday 17 February 2011] [14:20:43] <pieterh>	staylor: read Ch3 of the Guide
| [Thursday 17 February 2011] [14:20:56] <pieterh>	you need an XREP socket to do routing, and we're going to rename that a ROUTER socket
| [Thursday 17 February 2011] [14:21:03] <fbarriga>	I'm worried about uS. The python publisher uses bulk historic data (no latency problem). The C++ publisher receives marketdata in realtime
| [Thursday 17 February 2011] [14:21:32] <pieterh>	fbarriga: ok, that's good
| [Thursday 17 February 2011] [14:21:43] <pieterh>	you can try this yourself, it's trivial, two test programs in C++
| [Thursday 17 February 2011] [14:21:56] <pieterh>	try pubsub and push-pull
| [Thursday 17 February 2011] [14:21:59] <pieterh>	measure the latency
| [Thursday 17 February 2011] [14:22:20] <fbarriga>	yes, I was working in that way, but trying to avoid work asking here =)
| [Thursday 17 February 2011] [14:22:21] <staylor>	I'll look at it again, but out of quick curiosity would messages go to all REP sockets and be filtered or only to the specific client?
| [Thursday 17 February 2011] [14:22:42] <pieterh>	fbarriga: go do your own homework :-)
| [Thursday 17 February 2011] [14:22:48] <pieterh>	come back when you have results for us
| [Thursday 17 February 2011] [14:22:59] <fbarriga>	but is not too easy, event getting the time add some delay
| [Thursday 17 February 2011] [14:23:06] <fbarriga>	ok, thanks for the help
| [Thursday 17 February 2011] [14:23:27] <pieterh>	fbarriga: see how the latency test programs do it
| [Thursday 17 February 2011] [14:24:24] <pieterh>	staylor: clients are usually REQ, not REP
| [Thursday 17 February 2011] [14:24:41] <pieterh>	a REP socket is really for workers
| [Thursday 17 February 2011] [14:25:12] <pieterh>	are the names confusing?
| [Thursday 17 February 2011] [14:25:19] <staylor>	I might be going at this all wrong, but what I'm looking for is clients that connect to a server and wait for work requests (clients perform a task for the server)
| [Thursday 17 February 2011] [14:25:31] <pieterh>	call them 'workers', for sanity's sake :-)
| [Thursday 17 February 2011] [14:26:05] <staylor>	alright, so workers connect to the server which then sends them requests
| [Thursday 17 February 2011] [14:26:11] <pieterh>	it round-robins them
| [Thursday 17 February 2011] [14:26:20] <pieterh>	that's what an XREQ/DEALER socket does
| [Thursday 17 February 2011] [14:26:27] <pieterh>	deals the cards out
| [Thursday 17 February 2011] [14:26:44] <staylor>	in my scenario I need to send work to specific workers, that's where I'm unclear about how to identify them
| [Thursday 17 February 2011] [14:27:11] <fbarriga>	(any chance to use inproc for two different process ? like shared memory between processes?)
| [Thursday 17 February 2011] [14:27:27] <pieterh>	staylor: so, read Ch3, it is explained in exhaustive detail
| [Thursday 17 February 2011] [14:27:43] <pieterh>	you need REQ sockets for the workers, and XREQ to route to specific workers
| [Thursday 17 February 2011] [14:28:11] <pieterh>	fbarriga: nope, not unless you're able to hack together a shmem transport for 0MQ
| [Thursday 17 February 2011] [14:28:14] <staylor>	I think I see where I misunderstood the docs, I'll go over chap3 again
| [Thursday 17 February 2011] [14:28:28] <staylor>	thank you
| [Thursday 17 February 2011] [14:28:32] <pieterh>	np
| [Thursday 17 February 2011] [14:29:21] <fbarriga>	anyone has tried ?
| [Thursday 17 February 2011] [14:29:36] <pieterh>	don't think so
| [Thursday 17 February 2011] [14:29:48] <pieterh>	it would be fun to do but not portable
| [Thursday 17 February 2011] [15:16:55] <mikko>	evenin'
| [Thursday 17 February 2011] [15:26:26] <staylor>	is there a way to know if a worker is connected or not, or should that be let to the application to send acknowledgement requests?
| [Thursday 17 February 2011] [15:26:55] <staylor>	for example knowing when the underlying socket is broken?
| [Thursday 17 February 2011] [15:28:13] <Guthur>	staylor, the application will have to take care of the reliability
| [Thursday 17 February 2011] [15:29:34] <staylor>	alright, thank you
| [Thursday 17 February 2011] [15:55:13] <sam`>	hi
| [Thursday 17 February 2011] [15:55:34] <sam`>	i haven't heard back anything from my question yesterday about epgm and data distribution
| [Thursday 17 February 2011] [15:55:45] <sam`>	anyone around with some knowledge on this?
| [Thursday 17 February 2011] [15:57:00] <drbobbeaty>	sam: I'm not one of the main guys, but I'm using epgm and if I can answer your question, I'll give it a try. Can you repeat it (or cut-n-paste it) again?
| [Thursday 17 February 2011] [15:57:33] <Guthur>	sam`, you might try the Mailing list as well
| [Thursday 17 February 2011] [15:58:19] <sam`>	drbobbeaty: sure
| [Thursday 17 February 2011] [15:58:39] <sam`>	i need to distribute as efficiently as possible 100MB of data to several hundred machines in several datacenters around the world
| [Thursday 17 February 2011] [15:59:08] <sam`>	I was looking at multicast, and since my application uses 0MQ, epgm sounds like a good fit
| [Thursday 17 February 2011] [15:59:22] <sam`>	but I'm not sure multicast is even the appopriate solution
| [Thursday 17 February 2011] [16:00:38] <sam`>	also, I would like to do source-specific multicast, but I'm not sure how to do this with 0MQ. in SSM, you need to somehow specify both the source IP and the multicast channel, but I don't know how to do this in the epgm://<iface>;<multicast endpoint> syntax
| [Thursday 17 February 2011] [16:01:00] <drbobbeaty>	Wow... 100MB... Honestly, 0MQ is not what I'd be using - not that it's bad, but there are system-level tools to do this far more efficiently. For example, rdist on unix... you set up a "tree" of your datacenters where the 'source' sends to 4 boxes, each of those 4 send to 4 more, etc. Pretty soon it's all done.
| [Thursday 17 February 2011] [16:01:48] <drbobbeaty>	As for the source-specific multicast, that's not really possible in the 0MQ world because the sender is masked by the OpenPGM/URL scheme.
| [Thursday 17 February 2011] [16:01:49] <lt_schmidt_jr>	Upon advice from the experts I have grabbed the 2.1.0 tarball  instead of the 2.0.10 I have been using with homebrew on OSX
| [Thursday 17 February 2011] [16:01:57] <lt_schmidt_jr>	I am seeing the following error:
| [Thursday 17 February 2011] [16:02:00] <lt_schmidt_jr>	Making check in tests
| [Thursday 17 February 2011] [16:02:01] <lt_schmidt_jr>	make  check-TESTS
| [Thursday 17 February 2011] [16:02:01] <lt_schmidt_jr>	PASS: test_pair_inproc
| [Thursday 17 February 2011] [16:02:01] <lt_schmidt_jr>	PASS: test_pair_ipc
| [Thursday 17 February 2011] [16:02:02] <lt_schmidt_jr>	PASS: test_pair_tcp
| [Thursday 17 February 2011] [16:02:02] <lt_schmidt_jr>	PASS: test_reqrep_inproc
| [Thursday 17 February 2011] [16:02:02] <lt_schmidt_jr>	PASS: test_reqrep_ipc
| [Thursday 17 February 2011] [16:02:03] <lt_schmidt_jr>	PASS: test_reqrep_tcp
| [Thursday 17 February 2011] [16:02:03] <lt_schmidt_jr>	Invalid argument
| [Thursday 17 February 2011] [16:02:03] <lt_schmidt_jr>	nbytes != -1 (tcp_socket.cpp:197)
| [Thursday 17 February 2011] [16:02:04] <lt_schmidt_jr>	FAIL: test_shutdown_stress
| [Thursday 17 February 2011] [16:02:17] <lt_schmidt_jr>	sorry for the paste fail
| [Thursday 17 February 2011] [16:02:47] <lt_schmidt_jr>	so test_shutdown_stress fails when I run make check
| [Thursday 17 February 2011] [16:02:51] <lt_schmidt_jr>	should I worry?
| [Thursday 17 February 2011] [16:03:50] <drbobbeaty>	sam`: If you want to double-check me on the source specific multicast, send something to the mailing list. As for the 100MB file, I think there are better ways - especially since multicast is not routable so you'd have to make "tunnels" and that's a lot of work. There are tools/utilities geared for this for unix.
| [Thursday 17 February 2011] [16:04:12] <sam`>	drbobbeaty: what do you mean make tunnels?
| [Thursday 17 February 2011] [16:04:44] <drbobbeaty>	lt_schmidt_jr: this is a known issue with 2.1.0 but I *believe* it's fixed in the master (HEAD) on the git repo.
| [Thursday 17 February 2011] [16:04:59] <sam`>	drbobbeaty: afaik multicast is routable
| [Thursday 17 February 2011] [16:05:40] <sam`>	in my situation, all network equipment is layer3 capable and supports igmpv3, igmp snooping, pgm and ssm
| [Thursday 17 February 2011] [16:05:55] <lt_schmidt_jr>	drbobbeaty: thanks I think I will hold off, given the issues with the HEAD revision I see on the list
| [Thursday 17 February 2011] [16:06:17] <drbobbeaty>	sam`: I can almost certainly guarantee that it's not going to route through the internet. If you have a private WAN, then yes, it can be set up to have one switch send the data to another, but if you're betting on the plain old net, I think you're going to find it isn't.
| [Thursday 17 February 2011] [16:06:38] <sam`>	drbobbeaty: yes, you're absolutely right
| [Thursday 17 February 2011] [16:07:05] <sam`>	but we have dedicated links between our colos and a private network
| [Thursday 17 February 2011] [16:08:34] <drbobbeaty>	sam`: OK.. if you have private WANs then you can route it. However, my point on the best tool for the job stands. You can build something with 0MQ and use epgm, but I think there are better tools like rdist already written that make this so much easier.
| [Thursday 17 February 2011] [16:08:54] <sam`>	drbobbeaty: rdist looks cool, but it's basically a dump copy, it doesn't really help for the distribution problem
| [Thursday 17 February 2011] [16:09:58] <drbobbeaty>	sam`: OK... I'm missing something. If you have 100MB to move from A to B, then you can put that 100MB in a file, use rdist, load it at the other end. Right? If not, what am I missing about your requirements?
| [Thursday 17 February 2011] [16:10:26] <sam`>	it's not so much the copy from A to B that is the problem
| [Thursday 17 February 2011] [16:10:38] <sam`>	it's the distribution from A to B001 to B999
| [Thursday 17 February 2011] [16:11:32] <sam`>	right now, we're using scp, one machine after the other, which is what has been done for the past few years, and was probably fine with ~20 machines
| [Thursday 17 February 2011] [16:11:49] <sam`>	now we have ... "more"
| [Thursday 17 February 2011] [16:12:27] <sam`>	so I'm looking for a scalable solution, which obviously makes multicast come to mind
| [Thursday 17 February 2011] [16:12:41] <drbobbeaty>	sam`: If it were put in as a file, then the 1000 machines at B can all read it at the same time. Maybe what you need is an NFS mount for all machines at B to share?
| [Thursday 17 February 2011] [16:13:13] <sam`>	drbobbeaty: copying 1 file to 1000 serially, and having 1000 machines pull that 1 file from 1 machine at the same time
| [Thursday 17 February 2011] [16:13:16] <sam`>	doesn't help at all
| [Thursday 17 February 2011] [16:13:24] <sam`>	since you'll be sharing the bandwidth of that one machine
| [Thursday 17 February 2011] [16:13:31] <sam`>	so no time reduction at all
| [Thursday 17 February 2011] [16:14:52] <sam`>	and that's even worse when you only want the distribution of that file to take no more than X% of the network capacity
| [Thursday 17 February 2011] [16:15:20] <sam`>	(we're in a network-latency-critical environment, as is latency between our services as a direct impact on our revenue)
| [Thursday 17 February 2011] [16:15:22] <drbobbeaty>	sam`: if you have a primary box with a 10GbE NIC (or two), then it'll be a load, but not a lot.
| [Thursday 17 February 2011] [16:16:05] <drbobbeaty>	sam`: you know your set-up best, and maybe this isn't a workable solution. If that's the case, then sure, use 0MQ.
| [Thursday 17 February 2011] [16:16:31] <drbobbeaty>	sam`: You can write a "sender" and a "receiver" PUB/SUB and then make sure it's routed, and off you go.
| [Thursday 17 February 2011] [16:16:48] <drbobbeaty>	The examples in The Guide are really about all you need.
| [Thursday 17 February 2011] [16:17:04] <sam`>	it sure is a complex problem, and I'm not a network expert by any means
| [Thursday 17 February 2011] [16:17:26] <sam`>	but so far all existing solutions like puppet file serving, rdist, etc, all pull from one single machine, in unicast
| [Thursday 17 February 2011] [16:17:45] <sam`>	which puts a lot of load on that one machine, and the network, because you have N concurrent data streams
| [Thursday 17 February 2011] [16:18:25] <sam`>	that's why multicast looked interesting to me because I feel like it's (theoratically) the most "efficient" in the number of network packets transmitted
| [Thursday 17 February 2011] [16:19:26] <drbobbeaty>	sam`: But it's not "free"... if you have a failure, and a NACK is sent, you'll have to send that packet again - and with a WAN, the possibility goes up for that to happen.
| [Thursday 17 February 2011] [16:19:46] <drbobbeaty>	sam`: you are going to need a networking expert for this to be really efficient and workable.
| [Thursday 17 February 2011] [16:20:43] <sam`>	i'm afraid so
| [Thursday 17 February 2011] [16:21:04] <sam`>	and our network guy is in another continent building our next colo :\
| [Thursday 17 February 2011] [16:22:25] <sam`>	drbobbeaty: about my second question about SSM, any idea how to specify the source to 0MQ ?
| [Thursday 17 February 2011] [16:29:30] <drbobbeaty>	sam`: As for the source-specific multicast, that's not really possible in the 0MQ world because the sender is masked by the OpenPGM/URL scheme.
| [Thursday 17 February 2011] [16:30:00] <drbobbeaty>	sam`: but ask the mailing list to double-check me on this. I just don't see how with the APIs I've been using.
| [Thursday 17 February 2011] [16:30:44] <sam`>	kthx
| [Thursday 17 February 2011] [16:35:05] <sam`>	yep, I believe this could/should be added to pgm_socket.cpp to handle the source address somehow and do a pgm_setsockopt(sock, IPPROTO_PGM, PGM_MSFILTER, ...);
| [Thursday 17 February 2011] [16:35:54] <sam`>	if I settle on using 0MQ for the file distribution, I'll make a patch
| [Thursday 17 February 2011] [16:55:28] <sustrik>	lt_schmidt_jr: can you possibly find out what's the errno when the test fails?
| [Thursday 17 February 2011] [16:57:12] <lt_schmidt_jr>	let me see
| [Thursday 17 February 2011] [16:58:20] <mikko>	sustrik: steve-o suspects that openpgm with the changes needed for zeromq integration will be released next week around thu-fri
| [Thursday 17 February 2011] [16:59:46] <lt_schmidt_jr>	sustrik: this is what I am seeing: Invalid argument\n Nbytes != -1 (tcp_socket.cpp:197)
| [Thursday 17 February 2011] [17:01:43] <lt_schmidt_jr>	sustrik: I see what you are asking for, let me try to instrument the source
| [Thursday 17 February 2011] [17:02:31] <sustrik>	ah, invalid argument
| [Thursday 17 February 2011] [17:02:36] <sustrik>	i've missed that
| [Thursday 17 February 2011] [17:02:38] <sustrik>	sorry
| [Thursday 17 February 2011] [17:02:43] <sustrik>	mikko: great
| [Thursday 17 February 2011] [17:04:58] <sustrik>	hm, POSIX doesn't allow for send() returning EINVAL
| [Thursday 17 February 2011] [17:05:36] <sustrik>	Linux docs are not very helpful either:
| [Thursday 17 February 2011] [17:05:38] <sustrik>	"EINVAL Invalid argument passed."
| [Thursday 17 February 2011] [17:06:25] <sustrik>	lt_schmidt_jr: is that linux?
| [Thursday 17 February 2011] [17:06:50] <lt_schmidt_jr>	sustrik: mac osx 
| [Thursday 17 February 2011] [17:07:04] <sustrik>	can you check "man send"
| [Thursday 17 February 2011] [17:07:10] <sustrik>	and look for EINVAL?
| [Thursday 17 February 2011] [17:07:14] <lt_schmidt_jr>	checking
| [Thursday 17 February 2011] [17:08:34] <lt_schmidt_jr>	sustik:  [EINVAL]           The sum of the iov_len values overflows an ssize_t.
| [Thursday 17 February 2011] [17:09:53] <sustrik>	funny
| [Thursday 17 February 2011] [17:10:01] <sustrik>	that applies to sendmsg
| [Thursday 17 February 2011] [17:10:05] <lt_schmidt_jr>	yes
| [Thursday 17 February 2011] [17:10:18] <sustrik>	in this case its simple send that returns EINVAL
| [Thursday 17 February 2011] [17:10:56] <lt_schmidt_jr>	send() does not mention EINVAL in man
| [Thursday 17 February 2011] [17:11:30] <lt_schmidt_jr>	sustrik: where did you see EINVAL?
| [Thursday 17 February 2011] [17:13:17] <sustrik>	"Invalid argument"
| [Thursday 17 February 2011] [17:13:34] <sustrik>	= EINVAL
| [Thursday 17 February 2011] [17:14:43] <matott>	I'm starting with zmq. As an overlay network zmq it uses messages and doesn't provide a streaming api. Are there any fragmentation libraries to emulate streaming?
| [Thursday 17 February 2011] [17:16:48] <lt_schmidt_jr>	sustrik: this is odd, I have added a printf just before the failing assert to see the error number, and the failure changed to mailbox.cpp
| [Thursday 17 February 2011] [17:16:56] <matott>	I had a look at mongrel, but it seemed to me from the demos that the applications had to handle it itself.
| [Thursday 17 February 2011] [17:17:42] <sustrik>	what assert?
| [Thursday 17 February 2011] [17:18:25] <lt_schmidt_jr>	Nbytes != -1 (tcp_socket.cpp:197)
| [Thursday 17 February 2011] [17:18:33] <sustrik>	in mailbox.cpp?
| [Thursday 17 February 2011] [17:20:16] <lt_schmidt_jr>	I may be very confused, but the tcp_scoket.cpp:197 contains:  errno_assert (nbytes != -1);
| [Thursday 17 February 2011] [17:21:04] <sustrik>	"this is odd, I have added a printf just before the failing assert to see the error number, and the failure changed to mailbox.cpp"
| [Thursday 17 February 2011] [17:22:28] <lt_schmidt_jr>	but once I try to print the the errno in tcp_socket.cpp just before errno_assert in tcp_socket.cpp, the failure becomes: Assertion failed: nbytes == sizeof (command_t) (mailbox.cpp:193)
| [Thursday 17 February 2011] [17:22:39] <sustrik>	aha
| [Thursday 17 February 2011] [17:22:46] <sustrik>	that's a known problem with OSX
| [Thursday 17 February 2011] [17:23:06] <sustrik>	OSX has small default socket buffers
| [Thursday 17 February 2011] [17:23:15] <sustrik>	and resizing them seems to be broken
| [Thursday 17 February 2011] [17:23:38] <cremes>	sustrik: right... i have my little local "patch" that solves that for me on osx
| [Thursday 17 February 2011] [17:23:57] <cremes>	maybe lt_schmidt_jr can use the same thing until it gets fixed in master
| [Thursday 17 February 2011] [17:23:59] <sustrik>	yup, it would be nice to solve it in systemic way
| [Thursday 17 February 2011] [17:24:06] <sustrik>	however, i have no OSX box...
| [Thursday 17 February 2011] [17:24:29] <sustrik>	as for the tcp_socket/EINVAL error that's plain strange
| [Thursday 17 February 2011] [17:24:46] <sustrik>	it looks like the OS is returning undocumented error :(
| [Thursday 17 February 2011] [17:25:04] <lt_schmidt_jr>	hey, its like being back on Windows
| [Thursday 17 February 2011] [17:25:08] <lt_schmidt_jr>	:)
| [Thursday 17 February 2011] [17:25:43] <sustrik>	shrug
| [Thursday 17 February 2011] [17:26:15] <lt_schmidt_jr>	well, its ok, if I can get a patch, that would be great  - we would be deploying on CentOS
| [Thursday 17 February 2011] [17:26:26] <lt_schmidt_jr>	if I can get by for develpment
| [Thursday 17 February 2011] [17:28:02] <lt_schmidt_jr>	cremes: what version does you patch ... patch?
| [Thursday 17 February 2011] [17:29:09] <cremes>	lt_schmidt_jr: it's against master
| [Thursday 17 February 2011] [17:29:10] <cremes>	http://article.gmane.org/gmane.network.zeromq.devel/7146/match=old%5fsndbuf
| [Thursday 17 February 2011] [17:30:17] <lt_schmidt_jr>	cremes: thanks
| [Thursday 17 February 2011] [17:31:02] <lt_schmidt_jr>	Should I be using master? I just went from 2.0.10 which homebrew installed to 2.1.0 tarball
| [Thursday 17 February 2011] [17:31:19] <lt_schmidt_jr>	based on your suggestion
| [Thursday 17 February 2011] [17:31:35] <cremes>	lt_schmidt_jr: you should be; however, that little patch i just gave you should also work on 2.0.10 if you are happy with that release
| [Thursday 17 February 2011] [17:33:20] <lt_schmidt_jr>	Thanks. I will stay with the 2.1.0 tarball - I have already fixed the java tests - they were not exiting since sockets were not closed before context.term()
| [Thursday 17 February 2011] [17:33:50] <lt_schmidt_jr>	My question is more 2.1.0 tar on the zmq page vs latest git
| [Thursday 17 February 2011] [17:34:17] <lt_schmidt_jr>	a little nervous about HEAD revision
| [Thursday 17 February 2011] [17:37:54] <cremes>	lt_schmidt_jr: HEAD is likely more stable than 2.1.0 tarball; *lots* of fixes including another mailbox assert on osx
| [Thursday 17 February 2011] [17:38:05] <cremes>	given a choice between the tarball and master, use master
| [Thursday 17 February 2011] [17:38:30] <lt_schmidt_jr>	cremes: thank you
| [Thursday 17 February 2011] [17:38:36] <cremes>	you are welcome
| [Thursday 17 February 2011] [17:38:51] <cremes>	if you have fixes for the java tests, please contribute them back
| [Thursday 17 February 2011] [17:46:26] <lt_schmidt_jr>	I have not been getting responses from gonzalo on the mvn issues, so not sure how to contribute (its just 4 lines of socket.close())
| [Thursday 17 February 2011] [17:46:57] <lt_schmidt_jr>	to be fair to gonzalo, first he was gone, then he responded, I was gone, now he is gone ...
| [Thursday 17 February 2011] [19:14:24] <gui81>	anyone there
| [Thursday 17 February 2011] [19:15:44] <gui81>	is it possible to do this: http://pastebin.com/8KHzgu3a
| [Thursday 17 February 2011] [19:16:42] <gui81>	I am trying to publish to tcp://*:5555 and subscribe to tcp://localhost:5555, but it doesn't seem to work
| [Thursday 17 February 2011] [19:17:53] <gui81>	I can get the Hello World from pub_thread and Hello World from sub_thread messages to print out, but it doesn't seem to publish from pub_main or subscribe from sub_main
| [Thursday 17 February 2011] [19:27:18] <lt_schmidt_jr>	Regarding the named sockets - if I have a publisher with named subscribers that are connected to it. When a subscriber goes away and reconnects, is there any way to know if the subscriber has missed messages?
| [Thursday 17 February 2011] [19:27:35] <gui81>	nevermind, after reading through the Problem Solver, I realized that I didn't have setsockopt properly set the ZMQ_SUBSCRIBE option
| [Thursday 17 February 2011] [19:34:12] <lt_schmidt_jr>	sustrik: this may be a question for you
| [Thursday 17 February 2011] [19:34:42] <lt_schmidt_jr>	sustrik: how do i know (when using a named socket) if I have missed messages
| [Thursday 17 February 2011] [19:37:23] <lt_schmidt_jr>	named socket = DURABLE socket
| [Thursday 17 February 2011] [19:39:33] <cremes>	lt_schmidt_jr: a PUB socket is like a radio broadcast
| [Thursday 17 February 2011] [19:39:49] <cremes>	if you aren't connected when some messages go out, you miss them and never know it
| [Thursday 17 February 2011] [19:40:11] <lt_schmidt_jr>	even if I connect with a durable socket
| [Thursday 17 February 2011] [19:40:13] <lt_schmidt_jr>	?
| [Thursday 17 February 2011] [19:40:16] <lt_schmidt_jr>	then disconnect
| [Thursday 17 February 2011] [19:40:21] <lt_schmidt_jr>	and come back?
| [Thursday 17 February 2011] [19:40:30] <cremes>	if you disconnect, your queue is flushed
| [Thursday 17 February 2011] [19:40:51] <lt_schmidt_jr>	so durable sockets don't work with pub/sub
| [Thursday 17 February 2011] [19:40:52] <cremes>	you'll have to detect this via a sequence number gap (or similar) in the broadcast messages
| [Thursday 17 February 2011] [19:41:04] <cremes>	perhaps i don't understand what you mean by durable socket
| [Thursday 17 February 2011] [19:41:13] <cremes>	never heard of one
| [Thursday 17 February 2011] [19:41:29] <lt_schmidt_jr>	its in the guide
| [Thursday 17 February 2011] [19:42:18] <cremes>	i'll look in a minute...
| [Thursday 17 February 2011] [19:42:26] <cremes>	if you can provide a link, that would be best
| [Thursday 17 February 2011] [19:44:20] <lt_schmidt_jr>	http://zguide.zeromq.org/chapter:all#toc37
| [Thursday 17 February 2011] [19:56:57] <lt_schmidt_jr>	I guess I should just try it out
| [Thursday 17 February 2011] [20:01:02] <cremes>	lt_schmidt_jr: ok, i hadn't heard this term before
| [Thursday 17 February 2011] [20:01:19] <cremes>	but note that it *only* keeps the send buffer around
| [Thursday 17 February 2011] [20:01:32] <cremes>	anything in transit or in the receiver's OS buffers or queue will be lost
| [Thursday 17 February 2011] [20:01:49] <cremes>	so you probably still need to be able to identity gaps and recover from them
| [Thursday 17 February 2011] [20:02:10] <lt_schmidt_jr>	how does that interact with INPROC
| [Thursday 17 February 2011] [20:02:17] <lt_schmidt_jr>	loss is still possible?
| [Thursday 17 February 2011] [20:07:18] <cremes>	lt_schmidt_jr: i don't know
| [Thursday 17 February 2011] [20:07:25] <cremes>	that's a good question for the mailing list
| [Thursday 17 February 2011] [20:07:33] <lt_schmidt_jr>	thanks
| [Thursday 17 February 2011] [20:08:40] <lt_schmidt_jr>	I have subscriber sockets on the server on behalf of the websockets that may get disconnected
| [Thursday 17 February 2011] [20:08:59] <lt_schmidt_jr>	I actually have them run for a bit to see if client websocket reconects
| [Thursday 17 February 2011] [20:10:33] <lt_schmidt_jr>	but I wonder if I can terminate them instead
| [Thursday 17 February 2011] [20:10:49] <lt_schmidt_jr>	if they DURABLE
| [Thursday 17 February 2011] [20:21:20] <stodge>	Is there a pyzmq example of using PGM?
| [Thursday 17 February 2011] [20:36:49] <jugg>	yrashk, fyi, 'ezmq' is already used for an Eiffel 0mq binding.
| [Thursday 17 February 2011] [20:37:47] <yrashk>	jugg: oh well
| [Thursday 17 February 2011] [20:37:53] <yrashk>	who uses eiffel anyway?
| [Thursday 17 February 2011] [20:38:16] <jugg>	how about enifzmq ?
| [Thursday 17 February 2011] [20:38:28] <yrashk>	horrible :D
| [Thursday 17 February 2011] [20:38:30] <jugg>	:)
| [Thursday 17 February 2011] [20:38:58] <yrashk>	btw apparently ezmq is faster than erlzmq
| [Thursday 17 February 2011] [20:39:00] <yrashk>	up to 2x
| [Thursday 17 February 2011] [20:39:28] <jugg>	what changed?  I read some of the backlog... your original tests showed similar performance... how'd you up it?
| [Thursday 17 February 2011] [20:41:22] <yrashk>	jugg: well I don't quite know yet
| [Thursday 17 February 2011] [20:41:24] <yrashk>	it warmed up :D
| [Thursday 17 February 2011] [20:41:38] <yrashk>	I rewrote it form scratch as a NIF as you can see
| [Thursday 17 February 2011] [20:41:55] <yrashk>	from*
| [Thursday 17 February 2011] [20:42:54] <jugg>	yes, I'm stuck on R13B04 unfortunately.
| [Thursday 17 February 2011] [20:43:10] <yrashk>	and it can reach about 60-80K on my mac pro as opposed to 30K with erlzmq
| [Thursday 17 February 2011] [20:43:38] <yrashk>	I would assume this is because there is not so much communication overhead now
| [Thursday 17 February 2011] [20:44:00] <jugg>	that is ezmq/ezmq or erlang/ezmq ?
| [Thursday 17 February 2011] [20:44:05] <jugg>	eh
| [Thursday 17 February 2011] [20:44:08] <jugg>	zmq/ezmq
| [Thursday 17 February 2011] [20:45:43] <jugg>	I mean I saw something about testing C zmq to erlang zmq.
| [Thursday 17 February 2011] [20:46:29] <jugg>	those 60-80k is ezmq to ezmq?
| [Thursday 17 February 2011] [20:47:38] <yrashk>	yes
| [Thursday 17 February 2011] [21:02:44] <jugg>	yrashk, do you plan on making these bindings usable for receiving messages without having to call recv(noblock) on an interval? If so, how?
| [Thursday 17 February 2011] [21:03:46] <yrashk>	jugg: you mean nb recv?
| [Thursday 17 February 2011] [21:05:11] <jugg>	I mean you can't call zmq_poll, and there is no out of band recv support.  So, you either have to call recv on an interval, or call it and block the vm.
| [Thursday 17 February 2011] [21:05:35] <yrashk>	yes right now what you can see there is brecv()
| [Thursday 17 February 2011] [21:05:40] <yrashk>	a blocking recv
| [Thursday 17 February 2011] [21:05:52] <yrashk>	and here I have a non blocking recv() in my WIP
| [Thursday 17 February 2011] [21:06:04] <yrashk>	right now I am solving this with having a thread per socket
| [Thursday 17 February 2011] [21:06:57] <yrashk>	it works but only for some time, I have a bug somewhere
| [Thursday 17 February 2011] [21:07:00] <yrashk>	that causes a crash
| [Thursday 17 February 2011] [21:07:08] <yrashk>	that's why I am not committing it yet
| [Thursday 17 February 2011] [21:18:51] <jugg>	Why is 'send' not called 'bsend'?
| [Thursday 17 February 2011] [21:18:57] <jugg>	yrashk
| [Thursday 17 February 2011] [21:20:41] <yrashk>	jugg: because it's not inherently a waiting operation
| [Thursday 17 February 2011] [21:20:56] <yrashk>	you can use noblock flag for it
| [Thursday 17 February 2011] [21:21:32] <jugg>	and you can't in brecv? 
| [Thursday 17 February 2011] [21:22:14] <yrashk>	you can, but the nature of recv is different
| [Thursday 17 February 2011] [21:22:56] <yrashk>	it is inherently a waiting operation
| [Thursday 17 February 2011] [21:30:25] <yrashk>	nb recv() is about 10 times slower than blocking
| [Thursday 17 February 2011] [21:45:42] <jugg>	yrashk, is it possible to call an escript function using apply()?  I tried using ?MODULE for the module name, but that didn't work...  I'm trying to get those perf tests to run under R13B04.
| [Thursday 17 February 2011] [21:49:33] <yrashk>	jugg -mode(compile) will help with the ?MODULE thing afair
| [Thursday 17 February 2011] [21:51:28] <yrashk>	*if I am not mistaken*
| [Thursday 17 February 2011] [21:52:43] <jugg>	that worked, thanks.
| [Thursday 17 February 2011] [21:54:52] <yrashk>	yw
| [Thursday 17 February 2011] [22:58:13] <jugg>	yrashk, https://gist.github.com/833227 is what I'll commit on csrl/erlzmq.  Do you oppose being labeled the author?
| [Thursday 17 February 2011] [23:36:48] <jugg>	yrashk, if the ezmq:recv concept was also used for ezmq:send and for a ezmq:poll implementation, those bindings would become quite usable.  Nice (and fast) work.
| [Friday 18 February 2011] [00:22:58] <yrashk>	jugg: I don't oppose
| [Friday 18 February 2011] [00:23:26] <yrashk>	jugg: you think so? I might try doing recv trick with send, too
| [Friday 18 February 2011] [00:23:34] <yrashk>	but recv is quite slow
| [Friday 18 February 2011] [00:23:45] <yrashk>	brecv is much faster
| [Friday 18 February 2011] [00:27:56] <jugg>	how many cpu/cores do you have?
| [Friday 18 February 2011] [00:32:40] <yrashk>	8 (16 virtual)
| [Friday 18 February 2011] [00:33:08] <yrashk>	dual quadcore
| [Friday 18 February 2011] [00:35:18] <jugg>	it'd be interesting to know what the scheduler is doing then... playing with thread affinity could be interesting.  10x slow down seems odd.
| [Friday 18 February 2011] [00:37:04] <yrashk>	ya I am not sure what's happening
| [Friday 18 February 2011] [00:37:10] <yrashk>	but recv is about 10 times slower than brecv
| [Friday 18 February 2011] [00:37:21] <yrashk>	there's certainly *some* overhead
| [Friday 18 February 2011] [00:37:29] <yrashk>	but I doubt there is that much of an overhead
| [Friday 18 February 2011] [00:38:52] <yrashk>	although who knows
| [Friday 18 February 2011] [00:38:56] <yrashk>	recv is pretty tricky
| [Friday 18 February 2011] [00:39:10] <yrashk>	push, pull, recv, end
| [Friday 18 February 2011] [00:39:12] <yrashk>	*send
| [Friday 18 February 2011] [00:39:13] <jugg>	wild guess, but receiver_thread's enif_send() is the likely candidate since it is out of band, but brecv, the erlang scheduler is already blocking for the result.
| [Friday 18 February 2011] [00:39:49] <yrashk>	it is the candidate
| [Friday 18 February 2011] [00:39:58] <yrashk>	but I have no idea how else can you communicate result back
| [Friday 18 February 2011] [00:39:59] <yrashk>	;)
| [Friday 18 February 2011] [00:40:42] <yrashk>	also I suspect that ezmq is leaking memory
| [Friday 18 February 2011] [00:40:50] <yrashk>	but that should be fixable since its pretty small
| [Friday 18 February 2011] [00:40:55] <yrashk>	shouldn't be that hard to trace the leak
| [Friday 18 February 2011] [00:41:01] <yrashk>	I have no proof of leaking yet tho
| [Friday 18 February 2011] [00:41:51] <jugg>	maybe figure out a batch recv implementation... it'll loop until zmq_recv(noblock) returns eagain (or a max number is hit), then return the batch result.  Certainly useful for when SNDMORE exists.
| [Friday 18 February 2011] [00:42:22] <yrashk>	yeah I haven't even begin to deal with sndmore 
| [Friday 18 February 2011] [00:42:25] <yrashk>	was out of scope
| [Friday 18 February 2011] [00:42:49] <yrashk>	if you only you can tell erlang to designate a scheduler to only one process
| [Friday 18 February 2011] [00:43:04] <yrashk>	that is the one that talks to the NIF
| [Friday 18 February 2011] [00:43:12] <yrashk>	this way blocking would be irrelevant
| [Friday 18 February 2011] [00:43:12] <yrashk>	:D
| [Friday 18 February 2011] [00:44:28] <yrashk>	but I don't see any way to do so
| [Friday 18 February 2011] [00:46:37] <yrashk>	sigh
| [Friday 18 February 2011] [00:49:12] <jugg>	I think you'll need to refine your get/setsockopt implementation... zmq is rather exact about value lengths.  Also, not all socket options are valid for 'get'.
| [Friday 18 February 2011] [00:49:31] <yrashk>	I am ready to merge pull reqs
| [Friday 18 February 2011] [00:49:39] <jugg>	:)
| [Friday 18 February 2011] [00:49:39] <yrashk>	I'd rather focus on performance issues right now
| [Friday 18 February 2011] [00:49:44] <yrashk>	that was the original intention
| [Friday 18 February 2011] [00:49:51] <yrashk>	even though it is faster than erlzmq
| [Friday 18 February 2011] [00:49:56] <yrashk>	there's still a lot of work
| [Friday 18 February 2011] [00:50:12] <yrashk>	so if you can actually help me with sockopt thing, I will greatly appreciate that
| [Friday 18 February 2011] [00:50:17] <yrashk>	although you're on R13 :-(
| [Friday 18 February 2011] [00:51:09] <jugg>	yah, I can't even compile it... The best I can do is refer you to csrl/erlzmq implementation.
| [Friday 18 February 2011] [00:51:18] <yrashk>	re sockopt and stuff: after all ezmq is very new, I spent like 3 hours with it or so
| [Friday 18 February 2011] [00:51:47] <yrashk>	well you can also install R14 somewhere... hehehe :)
| [Friday 18 February 2011] [00:51:50] <jugg>	:)
| [Friday 18 February 2011] [00:53:29] <yrashk>	I am really trying to understand how to get recv almost as fast as brecv
| [Friday 18 February 2011] [00:56:25] <yrashk>	I have a rought idea of msend
| [Friday 18 February 2011] [00:56:31] <yrashk>	but it's too vague
| [Friday 18 February 2011] [00:57:42] <jugg>	ezmq_nif_recv should directly call zmq_recv(noblock|flags) and only if it returns EAGAIN do you hand it off to the receive_thread.
| [Friday 18 February 2011] [00:58:10] <yrashk>	or even asend.. hey this is an idea!
| [Friday 18 February 2011] [00:58:28] <jugg>	well, hand it off if (flags & noblock) == 0.
| [Friday 18 February 2011] [00:58:31] <yrashk>	jugg: hey, not a bad idea
| [Friday 18 February 2011] [00:58:39] <jugg>	it is what I do in erlzmq...
| [Friday 18 February 2011] [00:59:38] <yrashk>	just tested brecv again on this mac pro just in case
| [Friday 18 February 2011] [00:59:41] <yrashk>	66K
| [Friday 18 February 2011] [00:59:46] <yrashk>	twice as good as erlzmq
| [Friday 18 February 2011] [00:59:48] <yrashk>	still there, good
| [Friday 18 February 2011] [01:00:48] <yrashk>	now, recv
| [Friday 18 February 2011] [01:01:17] <yrashk>	27K
| [Friday 18 February 2011] [01:01:38] <yrashk>	hm not 10 times, roughly 2 times
| [Friday 18 February 2011] [01:01:53] <yrashk>	well I didn't recv on mac pro before yet
| [Friday 18 February 2011] [01:01:56] <yrashk>	only on macbook air
| [Friday 18 February 2011] [01:02:02] <yrashk>	which is much slower and fewer cores
| [Friday 18 February 2011] [01:12:17] <yrashk>	jugg: horaay
| [Friday 18 February 2011] [01:12:55] <jugg>	the suspense...
| [Friday 18 February 2011] [01:13:01] <yrashk>	now recv is more or less on par with brecv
| [Friday 18 February 2011] [01:13:06] <yrashk>	deviation is minimal
| [Friday 18 February 2011] [01:13:15] <jugg>	good deal
| [Friday 18 February 2011] [01:13:30] <yrashk>	thanks a lot!
| [Friday 18 February 2011] [01:15:16] <yrashk>	committed
| [Friday 18 February 2011] [01:16:02] <yrashk>	jugg: https://github.com/yrashk/ezmq/commit/77060d1b74d37c91ac7b403c90ea84095d30e5b9
| [Friday 18 February 2011] [01:20:07] <yrashk>	now... how can we make it even faster?
| [Friday 18 February 2011] [01:20:18] <jugg>	nice.  so, your old recv performed similarly to erlzmq?
| [Friday 18 February 2011] [01:20:32] <yrashk>	I haven't read erlzmq, honestly
| [Friday 18 February 2011] [01:20:47] <yrashk>	my recv was just unconditionally handing commands to the thread
| [Friday 18 February 2011] [01:20:50] <yrashk>	now it checks first
| [Friday 18 February 2011] [01:21:02] <jugg>	you said it was doing 27K msg/s?  erlzmq was about the same, yes?
| [Friday 18 February 2011] [01:21:03] <yrashk>	commands off*
| [Friday 18 February 2011] [01:21:19] <yrashk>	no, current codebase is within 60-80K msg/s
| [Friday 18 February 2011] [01:21:31] <yrashk>	that was for brecv prior to that commit
| [Friday 18 February 2011] [01:21:32] <jugg>	yah, sorry, I mean the old version.
| [Friday 18 February 2011] [01:21:38] <yrashk>	and recv was roughly 30K
| [Friday 18 February 2011] [01:21:46] <yrashk>	and now recv is on par with brecv
| [Friday 18 February 2011] [01:21:51] <jugg>	ok
| [Friday 18 February 2011] [01:22:04] <yrashk>	because if there's a lot of messages it does pretty much what brecv oes
| [Friday 18 February 2011] [01:22:05] <yrashk>	does
| [Friday 18 February 2011] [01:22:11] <yrashk>	thanks to your suggestion
| [Friday 18 February 2011] [01:22:23] <jugg>	that makes me think that the message passing out of the driver (nif/port) is the difference... a port driver always has to do message passing.
| [Friday 18 February 2011] [01:22:32] <yrashk>	yes
| [Friday 18 February 2011] [01:22:38] <yrashk>	and this is why I wrote NIF in the first place
| [Friday 18 February 2011] [01:22:46] <yrashk>	I blamed port comm for delays
| [Friday 18 February 2011] [01:23:06] <yrashk>	and apparently it can attribute to about 2x diff in timming
| [Friday 18 February 2011] [01:23:11] <yrashk>	timing*
| [Friday 18 February 2011] [01:23:41] <jugg>	well, I guess that is a bit of the reason NIFs exist anyway...
| [Friday 18 February 2011] [01:23:54] <yrashk>	ya
| [Friday 18 February 2011] [01:24:02] <yrashk>	and they are going to get even better
| [Friday 18 February 2011] [01:24:05] <yrashk>	in regards of async stuff
| [Friday 18 February 2011] [01:24:16] <yrashk>	but since it's only in the future I am dealing with what he have now
| [Friday 18 February 2011] [01:24:22] <jugg>	sure
| [Friday 18 February 2011] [01:24:42] <yrashk>	and I am not yet happy with 60-80K msg/sec
| [Friday 18 February 2011] [01:24:46] <yrashk>	and also sending is superslow
| [Friday 18 February 2011] [01:24:53] <yrashk>	looks like batching doesn't kick in
| [Friday 18 February 2011] [01:25:43] <yrashk>	it takes roughly 13 seconds to send those msgs
| [Friday 18 February 2011] [01:25:44] <yrashk>	insane
| [Friday 18 February 2011] [01:25:55] <yrashk>	C version takes less than a half of a second
| [Friday 18 February 2011] [01:26:16] <yrashk>	if I send messages with C version, ezmq reads at about 120K msg/sec
| [Friday 18 February 2011] [01:26:39] <yrashk>	so yet another 2x gain can be achieved if sending was somehow optimized
| [Friday 18 February 2011] [01:28:51] 	 * yrashk is scratching head
| [Friday 18 February 2011] [01:31:03] <yrashk>	hmm send seem to crash sometimes on my laptop
| [Friday 18 February 2011] [01:31:06] <yrashk>	not on the pro
| [Friday 18 February 2011] [01:31:20] <yrashk>	I guess ezmq needs a little bit more of maturing
| [Friday 18 February 2011] [01:52:34] <jugg>	yrashk, any progress, looks like I got disconnected for a while.
| [Friday 18 February 2011] [01:53:02] <cremes>	pieterh, sustrik: that mailbox fix has eliminated a ton of weird shit; so glad we solved it!
| [Friday 18 February 2011] [01:53:41] <sustrik>	cremes: i hope it haven't introduced other weird shit
| [Friday 18 February 2011] [01:54:12] <cremes>	sustrik: not at all; it's probably the most important fix i have seen yet
| [Friday 18 February 2011] [01:54:19] <sustrik>	:)
| [Friday 18 February 2011] [01:54:28] <cremes>	minor in code changes, huge in effect
| [Friday 18 February 2011] [01:54:31] <sustrik>	btw, do you have an osx box?
| [Friday 18 February 2011] [01:54:32] <cremes>	double :)
| [Friday 18 February 2011] [01:54:36] <cremes>	yes, i do
| [Friday 18 February 2011] [01:55:03] <sustrik>	i would like to fix the buffer resizing algorithm so that it works on osx
| [Friday 18 February 2011] [01:55:15] <cremes>	sustrik: i can give you an account on it
| [Friday 18 February 2011] [01:55:16] <sustrik>	if i do the patch, can you possibly test it?
| [Friday 18 February 2011] [01:55:25] <cremes>	sure, either way
| [Friday 18 February 2011] [01:55:28] <sustrik>	that would be great
| [Friday 18 February 2011] [01:55:30] <sustrik>	ssh?
| [Friday 18 February 2011] [01:55:35] <cremes>	of course
| [Friday 18 February 2011] [01:55:56] <cremes>	i'm going to bed now (1am) so i'll take care of it tomorrow
| [Friday 18 February 2011] [01:56:02] <sustrik>	great. let me know by email then
| [Friday 18 February 2011] [01:56:08] <cremes>	will do
| [Friday 18 February 2011] [01:56:11] <sustrik>	thanks
| [Friday 18 February 2011] [01:56:22] <cremes>	good night
| [Friday 18 February 2011] [01:56:37] <sustrik>	good night
| [Friday 18 February 2011] [01:56:49] <yrashk>	jugg: no
| [Friday 18 February 2011] [01:57:03] <yrashk>	jugg: just thinking how to improve performance further
| [Friday 18 February 2011] [01:57:18] <yrashk>	jugg: also I think I need to use rwlocks to guard sockets
| [Friday 18 February 2011] [01:58:42] <jugg>	or you could only allow the owner pid to use the socket?
| [Friday 18 February 2011] [01:59:04] <jugg>	not sure if that calling pid is availble in NIFs?
| [Friday 18 February 2011] [01:59:04] <yrashk>	or that
| [Friday 18 February 2011] [01:59:10] <yrashk>	it is
| [Friday 18 February 2011] [01:59:19] <yrashk>	but I think rwlock is a better method
| [Friday 18 February 2011] [01:59:20] <yrashk>	probably
| [Friday 18 February 2011] [01:59:32] <yrashk>	also
| [Friday 18 February 2011] [01:59:59] <yrashk>	I am not sure but afair there is no guarantee that call will always be made within the same scheduler
| [Friday 18 February 2011] [02:00:02] <yrashk>	hence it will be another thread
| [Friday 18 February 2011] [02:00:07] <yrashk>	and hence it will crash 0mq
| [Friday 18 February 2011] [02:00:13] <yrashk>	that's why I am thinking rwlocks
| [Friday 18 February 2011] [02:00:17] <jugg>	I don't... a socket should only be used by a single process.  Else you have troubles with multi-part messages, and socket states (eg REQ toggling of send/recv).
| [Friday 18 February 2011] [02:00:33] <yrashk>	and I think these occasional crashes might be attributed to this
| [Friday 18 February 2011] [02:01:01] <yrashk>	true
| [Friday 18 February 2011] [02:01:01] <jugg>	it is fine for sockets to be used in different threads (I assume you are using zmq 2.1.x)
| [Friday 18 February 2011] [02:01:14] <yrashk>	but not simultaneously
| [Friday 18 February 2011] [02:01:18] <yrashk>	I guess
| [Friday 18 February 2011] [02:01:21] <jugg>	correct
| [Friday 18 February 2011] [02:01:27] <yrashk>	hence rwlocks
| [Friday 18 February 2011] [02:01:41] <jugg>	or a single erlang process...
| [Friday 18 February 2011] [02:01:58] <yrashk>	again it doesn't guarantee the same scheduler (thread)
| [Friday 18 February 2011] [02:02:03] <jugg>	doesn't need to
| [Friday 18 February 2011] [02:02:12] <jugg>	a single process can't call into multiple nifs at once.
| [Friday 18 February 2011] [02:02:18] <yrashk>	true
| [Friday 18 February 2011] [02:02:31] <yrashk>	then we need to record pid on socket creation
| [Friday 18 February 2011] [02:02:32] <yrashk>	easy to do
| [Friday 18 February 2011] [02:02:37] <jugg>	yes
| [Friday 18 February 2011] [02:03:06] <yrashk>	and return badarg or something more appropriate if it is not from the same process
| [Friday 18 February 2011] [02:04:47] <yrashk>	this all doesn't explain rare segfaults
| [Friday 18 February 2011] [02:05:06] <yrashk>	basically *sometimes* 0mq fails on reading receiver_thread's pull socket
| [Friday 18 February 2011] [02:05:18] <yrashk>	which is something I can't yet explain
| [Friday 18 February 2011] [02:06:24] <yrashk>	A MQ context is thread safe and may be shared among as many application threads as necessary, without any additional locking required on the part of the caller. Each MQ socket belonging to a particular context may only be used by the thread that created it using zmq_socket().
| [Friday 18 February 2011] [02:06:37] <yrashk>	so not anymore?
| [Friday 18 February 2011] [02:07:14] <jugg>	not on 2.1.x
| [Friday 18 February 2011] [02:07:27] <yrashk>	too bad api doc is outdated
| [Friday 18 February 2011] [02:07:28] <yrashk>	:-(
| [Friday 18 February 2011] [02:07:37] <jugg>	in source, or on the web?
| [Friday 18 February 2011] [02:07:44] <yrashk>	web
| [Friday 18 February 2011] [02:07:45] <jugg>	the web is for 2.0.x still.
| [Friday 18 February 2011] [02:07:52] <yrashk>	any reason why?
| [Friday 18 February 2011] [02:07:58] <jugg>	it is the 'stable' version.
| [Friday 18 February 2011] [02:08:05] <yrashk>	ah
| [Friday 18 February 2011] [02:08:11] <yrashk>	so will be updated for 2.2?
| [Friday 18 February 2011] [02:08:21] <jugg>	I'm not sure how they're handling that...
| [Friday 18 February 2011] [02:09:03] <jugg>	I do wish they'd provide namespacing at api.zeromq.org tho for the different versions...
| [Friday 18 February 2011] [02:09:17] <jugg>	but I believe that's been discussed and rejected.
| [Friday 18 February 2011] [02:09:21] <yrashk>	that would be awesome
| [Friday 18 February 2011] [04:03:00] <mikko>	pieterh_: there?
| [Friday 18 February 2011] [04:03:13] <pieterh>	mikko: yup
| [Friday 18 February 2011] [04:03:46] <mikko>	pieterh: cJSON
| [Friday 18 February 2011] [04:04:00] <pieterh>	it's giving build errors?
| [Friday 18 February 2011] [04:04:00] <mikko>	is there a reason why the .c file is included in zfl_config_json?
| [Friday 18 February 2011] [04:04:09] <pieterh>	ah, that's just to simplify things
| [Friday 18 February 2011] [04:04:09] <mikko>	well, it's not included in make dist atm
| [Friday 18 February 2011] [04:04:11] <mikko>	fixing that
| [Friday 18 February 2011] [04:04:26] <mikko>	make dist, take the tar.gz and try to build
| [Friday 18 February 2011] [04:04:34] <pieterh>	it's used only by that one zfl class
| [Friday 18 February 2011] [04:04:38] <mikko>	yeah
| [Friday 18 February 2011] [04:04:43] <pieterh>	true, we never tested a tarball yet
| [Friday 18 February 2011] [04:17:43] <mikko>	pieterh: larger config refactoring on zfl, want it on separate branch first?
| [Friday 18 February 2011] [04:17:59] <mikko>	i went through most of it last night and all aspects of build work for me
| [Friday 18 February 2011] [04:18:07] <pieterh>	I don't think so mikko, let's do everything on master
| [Friday 18 February 2011] [04:18:24] <mikko>	ok, i can always revert if it breaks things in a bad way
| [Friday 18 February 2011] [04:18:27] <pieterh>	the sooner it breaks the more time we have to fix it :-)
| [Friday 18 February 2011] [04:18:40] <pieterh>	oh, we never revert :-)
| [Friday 18 February 2011] [04:19:20] <pieterh>	i'm serious, the only process I know is to publish & improve
| [Friday 18 February 2011] [04:19:56] <mikko>	 3 files changed, 67 insertions(+), 149 deletions(-)
| [Friday 18 February 2011] [04:19:58] <mikko>	heh
| [Friday 18 February 2011] [04:20:11] <pieterh>	commit it, I'll quickly test on this box I'm on
| [Friday 18 February 2011] [04:20:19] <pieterh>	I have 6 minutes then need to leave :-)
| [Friday 18 February 2011] [04:20:32] <pieterh>	I mean, push the commit...
| [Friday 18 February 2011] [04:20:38] <mikko>	pushed
| [Friday 18 February 2011] [04:21:05] <mikko>	let me know if something breaks. i'll test solaris today as well
| [Friday 18 February 2011] [04:22:03] <pieterh>	Tests passed OK
| [Friday 18 February 2011] [04:22:03] <pieterh>	PASS: zfl_selftest
| [Friday 18 February 2011] [04:22:03] <pieterh>	=============
| [Friday 18 February 2011] [04:22:03] <pieterh>	1 test passed
| [Friday 18 February 2011] [04:22:03] <pieterh>	=============
| [Friday 18 February 2011] [04:22:07] <pieterh>	that's on Ubuntu
| [Friday 18 February 2011] [04:22:12] <pieterh>	nice stuff!
| [Friday 18 February 2011] [04:22:27] <mikko>	good stuff
| [Friday 18 February 2011] [04:22:39] <mikko>	now i can add the gcov script and make the daily builds do this properly
| [Friday 18 February 2011] [04:36:13] <sustrik>	mikko: morning
| [Friday 18 February 2011] [04:36:28] <sustrik>	win7/msvc build seems to be failing
| [Friday 18 February 2011] [04:36:45] <sustrik>	when in build on my XP/msvc there's no problem
| [Friday 18 February 2011] [04:37:00] <sustrik>	is the source up to date there?
| [Friday 18 February 2011] [04:37:57] <sustrik>	maybe it has something to do with pgm?
| [Friday 18 February 2011] [04:37:58] <sustrik>	hm
| [Friday 18 February 2011] [04:39:29] <sustrik>	aha, that's probably it
| [Friday 18 February 2011] [04:44:35] <sustrik>	here it is: types.h:44: #	define bool		BOOL
| [Friday 18 February 2011] [04:57:00] <mikko>	yes
| [Friday 18 February 2011] [04:57:08] <mikko>	the pgm folder keeps disappearing for some reason
| [Friday 18 February 2011] [04:57:17] <mikko>	i think jenkins cleans the workspace at some point
| [Friday 18 February 2011] [04:58:38] <sustrik>	it's a different problem
| [Friday 18 February 2011] [04:58:59] <sustrik>	i've already sent an email about it to openpgm mailing list
| [Friday 18 February 2011] [05:00:25] <mikko>	ah good
| [Friday 18 February 2011] [05:00:32] <mikko>	so maybe the file permissions are working after all
| [Friday 18 February 2011] [05:00:52] <mikko>	if you got time at some point can you test this branch https://github.com/mkoppanen/zeromq2/tree/openpgm-autoconf
| [Friday 18 February 2011] [05:00:58] <mikko>	./configure --with-pgm
| [Friday 18 February 2011] [05:01:09] <mikko>	you should see during configure that it invokes openpgm configure
| [Friday 18 February 2011] [05:01:15] <mikko>	and everything works like magic
| [Friday 18 February 2011] [05:02:02] <sustrik>	i have ubuntu here
| [Friday 18 February 2011] [05:02:09] <sustrik>	would testing on that help you?
| [Friday 18 February 2011] [05:05:43] <mikko>	yeah, if you can
| [Friday 18 February 2011] [05:05:51] <mikko>	i've been only running it on my local vm
| [Friday 18 February 2011] [05:05:56] <mikko>	where everything seems to work ok
| [Friday 18 February 2011] [05:06:03] <sustrik>	ok, wait a sec
| [Friday 18 February 2011] [05:06:45] <mikko>	sun studio complains about same thing as msvc
| [Friday 18 February 2011] [05:07:58] <sustrik>	yes, same problem
| [Friday 18 February 2011] [05:13:57] <sustrik>	mikko: tested
| [Friday 18 February 2011] [05:13:59] <sustrik>	builds ok
| [Friday 18 February 2011] [05:14:02] <mikko>	good 
| [Friday 18 February 2011] [05:14:10] <mikko>	so it's ready(ish)
| [Friday 18 February 2011] [05:14:16] <sustrik>	nice
| [Friday 18 February 2011] [05:14:23] <mikko>	todo list emptying faster than i hoped
| [Friday 18 February 2011] [05:33:37] <yrashk>	I am confused now
| [Friday 18 February 2011] [05:33:48] <yrashk>	in PUB/SUBs who should connect and who should bind?
| [Friday 18 February 2011] [05:33:54] <mikko>	yrashk: doesnt matter
| [Friday 18 February 2011] [05:34:23] <yrashk>	looks like it works either way
| [Friday 18 February 2011] [05:34:25] <mikko>	yes
| [Friday 18 February 2011] [05:34:30] <yrashk>	mikko: that's what I thought, thanks
| [Friday 18 February 2011] [05:34:37] <yrashk>	I just received a patch "fixing" this in my tests
| [Friday 18 February 2011] [05:35:22] <yrashk>	and it got me puzzled because I never even thought about it
| [Friday 18 February 2011] [06:31:20] 	 * yrashk is trying to figure out how to make ezmq:send faster now
| [Friday 18 February 2011] [06:53:42] <mikko>	heyo
| [Friday 18 February 2011] [06:53:50] <pieterh_>	heyo, mikko
| [Friday 18 February 2011] [06:54:01] <mikko>	q: would it be useful to have sockopt to prevent durable subscribers on server side?
| [Friday 18 February 2011] [06:54:14] <pieterh_>	IMO yes
| [Friday 18 February 2011] [06:54:15] <mikko>	currently the server side is pretty vulnerable to DoS 
| [Friday 18 February 2011] [06:54:35] <mikko>	connect tons of clients with identities, disconnect them and it should run out of memory
| [Friday 18 February 2011] [06:54:40] <pieterh_>	Even more so, have sockopt that *allows* this
| [Friday 18 February 2011] [06:54:53] <mikko>	and another thing is removing subscriptions
| [Friday 18 February 2011] [06:54:53] <pieterh_>	Or else limit nbr of durable peers
| [Friday 18 February 2011] [06:55:06] <mikko>	or controlling their lifetime
| [Friday 18 February 2011] [06:55:14] <pieterh_>	indeed
| [Friday 18 February 2011] [06:55:16] <mikko>	as in "if peer has missed N messages consider it dead"
| [Friday 18 February 2011] [06:55:27] <pieterh_>	well, that's the whole point of durable sockets
| [Friday 18 February 2011] [06:55:29] <mikko>	or "if peer hasn't been back in 2 hours consider it dead"
| [Friday 18 February 2011] [06:55:32] <pieterh_>	peer can go away for a long time
| [Friday 18 February 2011] [06:55:41] <mikko>	i mean controllable time for durability
| [Friday 18 February 2011] [06:56:08] <pieterh_>	from a paranoid POV, I'd like
| [Friday 18 February 2011] [06:56:16] <pieterh_>	- default HWM for durable sockets
| [Friday 18 February 2011] [06:56:17] <mikko>	that way you don't have to worry about restarting server if you remove a durable subscriber
| [Friday 18 February 2011] [06:56:24] <pieterh_>	- default limit on number of those sockets
| [Friday 18 February 2011] [06:56:35] <pieterh_>	- default limit on total memory used by durable socket queues
| [Friday 18 February 2011] [06:57:15] <pieterh_>	good topic for discussion on list IMO
| [Friday 18 February 2011] [06:57:21] <mikko>	- ability to remove durable subscription explicitly
| [Friday 18 February 2011] [06:57:36] <mikko>	like remove subscription of "company ABC" while keeping others
| [Friday 18 February 2011] [06:57:42] <pieterh_>	- timeout on durable sockets
| [Friday 18 February 2011] [06:57:47] <mikko>	yes
| [Friday 18 February 2011] [06:58:16] <mikko>	one of the important features for 2.1.0 i could see is not failing on invalid connection uri
| [Friday 18 February 2011] [06:59:39] <pieterh_>	we should list the outstanding 'bugs' in 2.1.0
| [Friday 18 February 2011] [07:00:07] <mikko>	is atlassian stack overkill for us?
| [Friday 18 February 2011] [07:00:14] <mikko>	they give licenses to open source as far as i know
| [Friday 18 February 2011] [07:00:19] <mikko>	jira/confluence/etc
| [Friday 18 February 2011] [07:00:35] <pieterh_>	oh, I'd rather not
| [Friday 18 February 2011] [07:00:41] <pieterh_>	we used to use Jira for all issue tracking
| [Friday 18 February 2011] [07:00:46] <pieterh_>	it is a great, fantastic product
| [Friday 18 February 2011] [07:01:03] <pieterh_>	you just have to pay someone to reboot the *@%@$E# server once a week
| [Friday 18 February 2011] [07:01:33] <pieterh_>	i would 10x rather use github's simple but maintenance free issue tracking
| [Friday 18 February 2011] [07:02:05] <pieterh_>	anyhow, I was thinking of a wiki page, like the 2.0 roadmap
| [Friday 18 February 2011] [07:02:09] <pieterh_>	*3.0
| [Friday 18 February 2011] [07:02:30] <mikko>	what i would like is somehow automatically assign issues to roadmap milestones
| [Friday 18 February 2011] [07:02:54] <mikko>	i wonder if zfl tests should be broken into separate files
| [Friday 18 February 2011] [07:03:03] <mikko>	currently it shows "1 test succeeded"
| [Friday 18 February 2011] [07:03:38] <pieterh_>	regarding issue tracking, discuss on list, it's too contentious
| [Friday 18 February 2011] [07:04:06] <pieterh_>	remember our process is not driven by issues but by patches
| [Friday 18 February 2011] [07:04:31] <pieterh_>	for zfl tests, multiple executables would work for me, sure...
| [Friday 18 February 2011] [07:04:36] <pieterh_>	it's more work to maintain though
| [Friday 18 February 2011] [07:05:34] <pieterh_>	when we have four files for each class I start to get tempted by code generation
| [Friday 18 February 2011] [07:05:46] <pieterh_>	and that gets ugly, you don't want to see that :-)
| [Friday 18 February 2011] [07:06:47] <yrashk>	hey pieterh_ 
| [Friday 18 February 2011] [07:06:54] <pieterh_>	hi yrashk 
| [Friday 18 February 2011] [07:07:37] <yrashk>	mikko: I use open source license for bamboo, nice stuff
| [Friday 18 February 2011] [07:11:19] <mikko>	i find jenkins a lot better than bamboo
| [Friday 18 February 2011] [07:11:25] <mikko>	especially for distributed builds
| [Friday 18 February 2011] [07:17:49] <yrashk>	hmm may be I should add select() based active mode for ezmq.. not sure if this help with the performance issue, though
| [Friday 18 February 2011] [07:17:59] <yrashk>	this will*
| [Friday 18 February 2011] [07:22:58] <yrashk>	or, rather poll() one
| [Friday 18 February 2011] [07:44:17] <sustrik>	mikko, pieterh_: re durable subscribers: +1
| [Friday 18 February 2011] [07:44:30] <sustrik>	i would even remove the identity option altogether
| [Friday 18 February 2011] [08:02:15] <tormaroe>	Just found 0MQ, and I really exited. Built from source on Windows without problems. Now want to install Ruby gem, but having problems.
| [Friday 18 February 2011] [08:02:23] <tormaroe>	Trying gem install zmq -- --with-zmq-dir=c:\zeromq
| [Friday 18 February 2011] [08:02:31] <tormaroe>	but still getting ERROR: Failed to build gem native extension. extconf.rb:25: Couldn't find zmq library. try setting --with-zmq-dir=<path> to tell me where it is. (RuntimeError)
| [Friday 18 February 2011] [08:02:54] <tormaroe>	please help :)
| [Friday 18 February 2011] [08:03:47] <tormaroe>	I just copied the build output to my c:\zeromq. No other "installation" required, right?
| [Friday 18 February 2011] [08:05:50] <sustrik>	no
| [Friday 18 February 2011] [08:06:03] <sustrik>	you need just the library an the header file
| [Friday 18 February 2011] [08:07:13] <tormaroe>	I have no clue about c++, so what's the header file?
| [Friday 18 February 2011] [08:07:29] <tormaroe>	got dll, exp, ilk, lib and pdb
| [Friday 18 February 2011] [08:09:59] <yrashk>	it looks like I forgot a lot about poll()-related matters
| [Friday 18 February 2011] [08:10:12] <yrashk>	my recv blocks after receving a ZMQ_POLLIN revent
| [Friday 18 February 2011] [08:10:14] <yrashk>	eh
| [Friday 18 February 2011] [08:12:16] <yrashk>	don't quite understand how this could happen, but likely my 5am bug :D
| [Friday 18 February 2011] [08:16:07] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r17e2ca7 10/ (5 files): 
| [Friday 18 February 2011] [08:16:07] <CIA-21>	zeromq2: Logging of duplicit identities added
| [Friday 18 February 2011] [08:16:07] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/dXqok7
| [Friday 18 February 2011] [08:16:26] <sustrik>	tormaroe: zmq.h
| [Friday 18 February 2011] [08:17:00] <sustrik>	yrashk: that should not happen
| [Friday 18 February 2011] [08:21:07] <tormaroe>	Added zmq.h from the include folder and re-ran gem command, but getting same error :(
| [Friday 18 February 2011] [08:21:44] <sustrik>	try asking on the mailing list, i am not a ruby expert
| [Friday 18 February 2011] [08:21:54] <tormaroe>	ok, thanks anyway
| [Friday 18 February 2011] [08:24:24] <yrashk>	sustrik: yeah I figured that out already and fixed the bug
| [Friday 18 February 2011] [08:34:37] <yrashk>	doing poll & recv at the same time is probably an insanely bad idea, after all :D
| [Friday 18 February 2011] [10:05:54] <yrashk>	sustrik: pieterh is that ok that send() with ZMQ_NOBLOCK takes roughly 10 usec?
| [Friday 18 February 2011] [10:06:07] <yrashk>	I am profiling my C code
| [Friday 18 February 2011] [10:06:27] <sustrik>	raw zmq_send()?
| [Friday 18 February 2011] [10:06:30] <yrashk>	ya
| [Friday 18 February 2011] [10:06:48] <sustrik>	that's too much
| [Friday 18 February 2011] [10:06:58] <sustrik>	should be below 1 us
| [Friday 18 February 2011] [10:07:06] <yrashk>	https://gist.github.com/af07bbd989ec1f7e659c
| [Friday 18 February 2011] [10:08:03] <yrashk>	appended that gist with some typical tv.tv_usec-tv1.tv_usec printout
| [Friday 18 February 2011] [10:08:21] <yrashk>	it looks more like 7 us
| [Friday 18 February 2011] [10:08:41] <yrashk>	but still
| [Friday 18 February 2011] [10:08:44] <sustrik>	have you tried to measure zmq_send() itself?
| [Friday 18 February 2011] [10:08:54] <sustrik>	there's some other work being done there
| [Friday 18 February 2011] [10:08:57] <yrashk>	well that if condition is false
| [Friday 18 February 2011] [10:09:07] <sustrik>	ah
| [Friday 18 February 2011] [10:09:09] <sustrik>	ok
| [Friday 18 February 2011] [10:09:13] <yrashk>	but I can try
| [Friday 18 February 2011] [10:09:17] <sustrik>	what OS are you on?
| [Friday 18 February 2011] [10:09:20] <yrashk>	osx
| [Friday 18 February 2011] [10:09:34] <sustrik>	how long does gettimeofday take on osx?
| [Friday 18 February 2011] [10:09:46] <yrashk>	still 5+ us at least
| [Friday 18 February 2011] [10:09:50] <yrashk>	with no if
| [Friday 18 February 2011] [10:09:56] <yrashk>	no idea
| [Friday 18 February 2011] [10:10:03] <sustrik>	it tends to be slow
| [Friday 18 February 2011] [10:10:15] <sustrik>	it's kind of better with linux nowadays
| [Friday 18 February 2011] [10:10:24] <sustrik>	they've got it to something like 1us
| [Friday 18 February 2011] [10:10:37] <sustrik>	but before it was much worse
| [Friday 18 February 2011] [10:10:45] <sustrik>	no idea about osx though
| [Friday 18 February 2011] [10:11:24] <sustrik>	easiest way to measure is to make 1M zmq_send()s
| [Friday 18 February 2011] [10:11:31] <sustrik>	measure the whole thing
| [Friday 18 February 2011] [10:11:37] <sustrik>	and divide it by 1000000
| [Friday 18 February 2011] [10:12:16] <yrashk>	apparently _lat tests are good on ezmq
| [Friday 18 February 2011] [10:12:48] <yrashk>	well that's what I do
| [Friday 18 February 2011] [10:13:04] <yrashk>	(07:12) <evaxsoftware> _lat results:
| [Friday 18 February 2011] [10:13:04] <yrashk>	(07:12) <evaxsoftware> local_lat       remote_lat      mean latency        real/usr/sys
| [Friday 18 February 2011] [10:13:07] <yrashk>	(07:12) <evaxsoftware> C               C               41                  8.2/0.8/3.7
| [Friday 18 February 2011] [10:13:10] <yrashk>	(07:12) <evaxsoftware> ezmq            ezmq            47                  9.5/2.6/2.3
| [Friday 18 February 2011] [10:13:14] <yrashk>	(07:13) <evaxsoftware> pyzmq           pyzmq           48                  12.7/1.8/3.7
| [Friday 18 February 2011] [10:13:17] <yrashk>	.win 26
| [Friday 18 February 2011] [10:13:19] <yrashk>	oops
| [Friday 18 February 2011] [10:13:22] <yrashk>	(07:14) <evaxsoftware> it's efficient (completes nearly as fast as the C version)
| [Friday 18 February 2011] [10:13:46] <yrashk>	apparently better than pyzmq
| [Friday 18 February 2011] [10:15:19] <DarkGod>	hello, I'm sorry but I am afradi I have a few, probably stupid questions. I read the manual and wanted to try the auto reconnect stuff, I took the simple REQ/REP C examples and copiled them, if I run the client and then the server it's all dandy, yet if I kill the server while the client is running and then restart the server it does not seem to reconnect
| [Friday 18 February 2011] [10:15:32] <DarkGod>	it should no? or did I misunderstand ?
| [Friday 18 February 2011] [10:16:37] <sustrik>	yrashk: nice
| [Friday 18 February 2011] [10:17:10] <yrashk>	so I am not sure why thr is so bad
| [Friday 18 February 2011] [10:17:41] <sustrik>	throughput is a silly metric
| [Friday 18 February 2011] [10:17:59] <sustrik>	it exhibits large oscillation due to minor causes
| [Friday 18 February 2011] [10:18:04] <sustrik>	shrug
| [Friday 18 February 2011] [10:19:02] <sustrik>	DarkGod: it probably reconnects, but current request is lost
| [Friday 18 February 2011] [10:19:26] <sustrik>	if you need reliability you should implement it on top of 0mq
| [Friday 18 February 2011] [10:19:37] <sustrik>	iirc, the guide explains that
| [Friday 18 February 2011] [10:20:26] <DarkGod>	ah, so I should put a timeout on the send on the REQ side so that it can fail
| [Friday 18 February 2011] [10:20:39] <sustrik>	yes
| [Friday 18 February 2011] [10:20:47] <sustrik>	then you can resend the request if needed
| [Friday 18 February 2011] [10:20:59] <DarkGod>	I see
| [Friday 18 February 2011] [10:21:04] <DarkGod>	thanks :)
| [Friday 18 February 2011] [10:21:08] <sustrik>	np
| [Friday 18 February 2011] [10:22:53] <DarkGod>	next silly question: the pub/sub sockets look neat, but in some cases I want to adress a specific client, I could use filtering but a ngrep of the ethernet interface shows me that all data is pushed to clients and that they then do the filtering, as I might have large data going through I really do notwant it transmited to all
| [Friday 18 February 2011] [10:23:05] <DarkGod>	clietns when it is actaully only meant for one
| [Friday 18 February 2011] [10:23:30] <DarkGod>	I must use pairs in this case? (setting up a pair per client ?)
| [Friday 18 February 2011] [10:27:53] <sustrik>	there's a work in progress wrt filtering on the PUBside
| [Friday 18 February 2011] [10:28:04] <sustrik>	(sub-forward branch)
| [Friday 18 February 2011] [10:28:16] <sustrik>	you can help to finish that work
| [Friday 18 February 2011] [10:29:00] <DarkGod>	I'm afraid I dont know zmq code quite well enough, but yeah that's what I'd need I imagine
| [Friday 18 February 2011] [10:31:27] <DarkGod>	how advanced is this branch/what needs to be done ?
| [Friday 18 February 2011] [10:32:20] <sustrik>	check the mailing list archives
| [Friday 18 February 2011] [10:32:30] <sustrik>	there lot of related discussion there
| [Friday 18 February 2011] [10:32:45] <DarkGod>	ok :)
| [Friday 18 February 2011] [10:32:50] <sustrik>	so far the subscriptions are propagated up the distribution tree
| [Friday 18 February 2011] [10:32:59] <sustrik>	what's missing is acutal filtering
| [Friday 18 February 2011] [10:56:16] <yrashk>	https://gist.github.com/a3fd747d0bd7b3d61aba
| [Friday 18 February 2011] [10:56:44] <yrashk>	sustrik: ^^ another bizzare crash :) now I don't even see any out of bound pointers :-D
| [Friday 18 February 2011] [10:57:05] <yrashk>	does this tracce tell you anything worth checking out?
| [Friday 18 February 2011] [11:12:58] <sustrik>	yrashk: what's the error?
| [Friday 18 February 2011] [11:13:02] <sustrik>	SEGFAULT?
| [Friday 18 February 2011] [11:13:08] <yrashk>	yes
| [Friday 18 February 2011] [11:13:26] <sustrik>	segfault in glibc
| [Friday 18 February 2011] [11:13:28] <sustrik>	nasty
| [Friday 18 February 2011] [11:13:33] <yrashk>	I can show the whole socket printout
| [Friday 18 February 2011] [11:13:35] <yrashk>	if you want
| [Friday 18 February 2011] [11:13:50] <sustrik>	no need
| [Friday 18 February 2011] [11:13:54] <sustrik>	is it reproducible?
| [Friday 18 February 2011] [11:14:11] <yrashk>	not every time
| [Friday 18 February 2011] [11:14:18] <yrashk>	and not on every computer
| [Friday 18 February 2011] [11:14:19] <yrashk>	but it is
| [Friday 18 February 2011] [11:14:22] <sustrik>	hm
| [Friday 18 February 2011] [11:14:26] <yrashk>	just in case https://gist.github.com/dfc2e7eea5c89673ea74
| [Friday 18 February 2011] [11:14:27] <yrashk>	:)
| [Friday 18 February 2011] [11:14:42] <sustrik>	erlang, hm
| [Friday 18 February 2011] [11:14:45] <sustrik>	:|
| [Friday 18 February 2011] [11:14:48] <yrashk>	crash happens both on osx and linux
| [Friday 18 February 2011] [11:15:04] <yrashk>	I don't think it has *anything* to do with erlang per se
| [Friday 18 February 2011] [11:15:59] <yrashk>	this code is in a separate thread that Erlang has even a litle to no idea about
| [Friday 18 February 2011] [11:16:11] <yrashk>	s/a little/little/
| [Friday 18 February 2011] [11:19:24] <sustrik>	yrashk: any chance to reproduce the problem in C?
| [Friday 18 February 2011] [11:20:38] <yrashk>	may be
| [Friday 18 February 2011] [11:20:43] <yrashk>	but I have no idea how
| [Friday 18 February 2011] [11:22:24] <yrashk>	(yet)
| [Friday 18 February 2011] [11:22:33] <sustrik>	what's the OS btw?
| [Friday 18 February 2011] [11:25:32] <yrashk>	both osx and linux
| [Friday 18 February 2011] [11:25:35] <yrashk>	very similar crash
| [Friday 18 February 2011] [11:38:05] <yrashk>	are there any circumstances under which context gets terminated implicitly, sustrik?
| [Friday 18 February 2011] [11:38:27] <sustrik>	yrashk: no
| [Friday 18 February 2011] [11:38:37] <sustrik>	you have to terminate by calling zmq_term()
| [Friday 18 February 2011] [11:38:59] <sustrik>	it looks like a bug in 0mq anyway
| [Friday 18 February 2011] [11:39:17] <sustrik>	so the goal now is to make a reproducible test case
| [Friday 18 February 2011] [11:39:25] <sustrik>	and to fix it
| [Friday 18 February 2011] [11:39:39] <yrashk>	do you think it is a 0mq bug?
| [Friday 18 February 2011] [11:39:46] <yrashk>	huh
| [Friday 18 February 2011] [11:39:59] <yrashk>	I was getting segfaults in recvfrom() before
| [Friday 18 February 2011] [11:40:21] <yrashk>	last time it was due to an accidental rewrite over context
| [Friday 18 February 2011] [11:40:25] <sustrik>	it's kind of strange
| [Friday 18 February 2011] [11:40:43] <sustrik>	yes, it looks like memory overwrite
| [Friday 18 February 2011] [11:40:56] <sustrik>	wither by 0mq or ezmq or erlang itself
| [Friday 18 February 2011] [11:41:07] <sustrik>	that's why C use case would help
| [Friday 18 February 2011] [11:41:28] <sustrik>	that would make it clear that the problem is in 0mq
| [Friday 18 February 2011] [11:42:05] <yrashk>	yeah I know
| [Friday 18 February 2011] [11:42:14] <yrashk>	it's barely reproducable here on my laptop
| [Friday 18 February 2011] [11:42:27] <sustrik>	what's the use case?
| [Friday 18 February 2011] [11:42:28] <yrashk>	much more frequent on aother guy's linux box
| [Friday 18 February 2011] [11:42:54] <yrashk>	second thread recving on pull socket waiting for a command to recv another socket
| [Friday 18 February 2011] [11:44:30] <yrashk>	sustrik: does context change over time or is it immutable?
| [Friday 18 February 2011] [11:46:06] <sustrik>	you mean the internals of the context?
| [Friday 18 February 2011] [11:46:12] <yrashk>	ya
| [Friday 18 February 2011] [11:46:18] <sustrik>	yes, there's a lis of inproc endpoints for example
| [Friday 18 February 2011] [11:46:23] <sustrik>	a table of open sockets
| [Friday 18 February 2011] [11:46:27] <sustrik>	and similar
| [Friday 18 February 2011] [11:46:29] <yrashk>	that might be the case
| [Friday 18 February 2011] [11:46:39] <yrashk>	does any zmq operation might change the context?
| [Friday 18 February 2011] [11:47:09] <sustrik>	creating a socket
| [Friday 18 February 2011] [11:47:13] <sustrik>	closing a socket
| [Friday 18 February 2011] [11:47:18] <sustrik>	binding to inproc endpoint
| [Friday 18 February 2011] [11:48:02] <yrashk>	that's it?
| [Friday 18 February 2011] [11:48:46] <yrashk>	we do all three
| [Friday 18 February 2011] [11:48:50] <yrashk>	;)
| [Friday 18 February 2011] [11:48:55] <yrashk>	and definitely bind to inproc
| [Friday 18 February 2011] [11:49:00] <yrashk>	in that context
| [Friday 18 February 2011] [11:49:07] <yrashk>	in fact it is only used for inproc
| [Friday 18 February 2011] [11:50:03] <sustrik>	yes, but what's the deal?
| [Friday 18 February 2011] [11:50:15] <sustrik>	why should changing the context be a problem?
| [Friday 18 February 2011] [11:50:55] <yrashk>	"As soon as you write towards a shared state either through static variables or enif_priv_data you need to supply your own explicit synchronization. "
| [Friday 18 February 2011] [11:51:01] <yrashk>	this is from NIF documentation
| [Friday 18 February 2011] [11:51:16] <yrashk>	that context that we use there is a static variable
| [Friday 18 February 2011] [11:52:33] <sustrik>	but it's only a pointer to context, right?
| [Friday 18 February 2011] [11:52:36] <sustrik>	which never changes
| [Friday 18 February 2011] [11:52:39] <yrashk>	yup
| [Friday 18 February 2011] [11:52:46] <sustrik>	the context itself is threadsafe
| [Friday 18 February 2011] [11:52:59] <sustrik>	so it should be ok imo
| [Friday 18 February 2011] [11:53:01] <yrashk>	we're just trying to find any possible explanation for the crash :)
| [Friday 18 February 2011] [11:55:13] <yrashk>	ok, bed time
| [Friday 18 February 2011] [11:55:22] <yrashk>	I am exhausted and need to get up in 3 hours :]
| [Friday 18 February 2011] [11:57:00] <sustrik>	good god
| [Friday 18 February 2011] [11:57:28] <sustrik>	see you later then
| [Friday 18 February 2011] [11:58:38] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r12486fe 10/ (src/pgm_socket.hpp src/zmq.cpp): 
| [Friday 18 February 2011] [11:58:38] <CIA-21>	zeromq2: Fix MSVC and SunStudio builds with OpenPGM
| [Friday 18 February 2011] [11:58:38] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/hxuwyD
| [Friday 18 February 2011] [12:36:45] <lt_schmidt_jr>	sustrik: for inproc sub, are durable sockets trully durable? 
| [Friday 18 February 2011] [12:37:03] <sustrik>	what's durable?
| [Friday 18 February 2011] [12:38:00] <lt_schmidt_jr>	http://zguide.zeromq.org/chapter:all#toc37
| [Friday 18 February 2011] [12:38:18] <lt_schmidt_jr>	sockets with explicit identity
| [Friday 18 February 2011] [12:48:28] <sustrik>	and what's "trully durable"? :)
| [Friday 18 February 2011] [12:50:06] <lt_schmidt_jr>	sustrik: I mean if the connection is closed I would not loose messages given that there are no network buffers
| [Friday 18 February 2011] [12:51:55] <lt_schmidt_jr>	sustrik: I wonder if with inproc the client sub buffer gets filled 
| [Friday 18 February 2011] [12:52:40] <sustrik>	when you close the SUB side
| [Friday 18 February 2011] [12:52:47] <sustrik>	the buffer on PUB side is filled
| [Friday 18 February 2011] [12:53:11] <sustrik>	(SUB buffer doesn't exist at the moment)
| [Friday 18 February 2011] [12:53:37] <lt_schmidt_jr>	ah, so this may actually work for me
| [Friday 18 February 2011] [12:54:11] <sustrik>	i don't know how well inproc works with identities
| [Friday 18 February 2011] [12:54:21] <sustrik>	you have to test it yourself, i would say
| [Friday 18 February 2011] [12:54:24] <lt_schmidt_jr>	ah
| [Friday 18 February 2011] [12:54:46] <sustrik>	the problem with inproc is that there are still pieces missing
| [Friday 18 February 2011] [12:54:59] <sustrik>	like reconnect, for example
| [Friday 18 February 2011] [12:55:03] <sustrik>	not sure about identitie
| [Friday 18 February 2011] [12:55:04] <lt_schmidt_jr>	did not realize that
| [Friday 18 February 2011] [12:56:42] <lt_schmidt_jr>	the reason I am asking - is that I have an inproc forwarder connected to other servers symmetrically
| [Friday 18 February 2011] [12:57:33] <lt_schmidt_jr>	and I have sub sockets that I keep on behalf of web clients , and if the web clietnts disconnect, I keep the sub socket for a bit in case they reconnect
| [Friday 18 February 2011] [12:58:08] <lt_schmidt_jr>	I am thinking to use identity to have zmq do that for me
| [Friday 18 February 2011] [12:58:59] <lt_schmidt_jr>	but sounds like that may not be the best approach currently
| [Friday 18 February 2011] [13:55:37] <bhuga_>	i'm getting an assertion failure while using zeromq from the ruby FFI: Assertion failed: inpipes [current_in].active (xrep.cpp:229). Is that indicative of something I'm doing wrong, or a bug?
| [Friday 18 February 2011] [15:05:13] <cremes>	bhuga_: can you pastie your code that's causing that? it may be a bug in 0mq
| [Friday 18 February 2011] [15:29:19] <bhuga_>	it is kind of convoluted :/, pretty far from a minimal test case. it is also not deterministic, happening for sure, but not always after the same number of messages have passed. i have an strace running up to it, if that helps?
| [Friday 18 February 2011] [16:02:41] <cremes>	bhuga_: is your code similar to the setup described in this ticket?
| [Friday 18 February 2011] [16:02:42] <cremes>	https://github.com/zeromq/zeromq2/issuesearch?state=open&q=xrep#issue/164
| [Friday 18 February 2011] [16:02:57] <cremes>	that raises the same assertion as your code
| [Friday 18 February 2011] [16:03:10] <cremes>	i am wondering if the configuration of sockets & threads is similar in your case
| [Friday 18 February 2011] [16:03:27] <bhuga_>	mine is simpler
| [Friday 18 February 2011] [16:03:44] <bhuga_>	but still difficult to hand over for reproduction
| [Friday 18 February 2011] [16:04:05] <cremes>	how many sockets are you using?
| [Friday 18 February 2011] [16:04:19] <cremes>	i.e. how many xrep, how many xreq?
| [Friday 18 February 2011] [16:04:19] <bhuga_>	the ruby end is sitting on an xrep socket, one thread (ruby, after all) and the other end is common lisp via ffi on a req-rep
| [Friday 18 February 2011] [16:04:33] <cremes>	ok
| [Friday 18 February 2011] [16:04:42] <cremes>	are they both using the same build of libzmq?
| [Friday 18 February 2011] [16:04:47] <bhuga_>	yes, 2.1.0
| [Friday 18 February 2011] [16:05:02] <cremes>	2.1.0 from the tarball or 2.1.0 from github master?
| [Friday 18 February 2011] [16:05:23] <bhuga_>	yowza, good question, i didnt write that down when i put it into puppet last month.  probably the tarball.
| [Friday 18 February 2011] [16:05:34] <cremes>	ok
| [Friday 18 February 2011] [16:05:49] <cremes>	i would recommend trying master and seeing if the problem persists
| [Friday 18 February 2011] [16:06:04] <bhuga_>	okay, i can do that. will be back in 15 or 20
| [Friday 18 February 2011] [16:06:06] <cremes>	there have been many bug fixes since the 2.1.0 tarball was cut 2 or 3 months ago
| [Friday 18 February 2011] [16:06:10] <cremes>	k
| [Friday 18 February 2011] [16:07:37] <bhuga_>	(about to try it, but my buddy on the lisp end, debugging something else, just realized that putting 1 second between calls fixes it)
| [Friday 18 February 2011] [16:10:21] <cremes>	bhuga_: yuck, that's a sucky fix :)
| [Friday 18 February 2011] [16:10:36] <bhuga_>	yeah, it kinda defeats the point of a sweet high-performance message queue :)
| [Friday 18 February 2011] [16:10:48] <cremes>	definitely
| [Friday 18 February 2011] [16:11:33] <cremes>	i have dozens of xrep/xreq sockets doing very high volume communications (from ruby) and i haven't hit that particular assertin
| [Friday 18 February 2011] [16:11:51] <cremes>	(though i was tearing my hair out about another one that just got fixed a few days back)
| [Friday 18 February 2011] [16:12:09] <bhuga_>	this one has our hair pulled, i have to admit
| [Friday 18 February 2011] [16:12:13] <cremes>	heh
| [Friday 18 February 2011] [16:12:15] <bhuga_>	its pretty much brought us to a standstill
| [Friday 18 February 2011] [16:12:25] <cremes>	let me know how it goes after the update
| [Friday 18 February 2011] [16:12:42] <bhuga_>	figuring out how to make autoconf work on head still :)
| [Friday 18 February 2011] [16:13:17] <cremes>	what os are you on?
| [Friday 18 February 2011] [16:13:23] <bhuga_>	ubuntu 10.10
| [Friday 18 February 2011] [16:13:26] <cremes>	ko
| [Friday 18 February 2011] [16:13:29] <cremes>	er, ok
| [Friday 18 February 2011] [16:15:05] <bhuga_>	autoreconf --install and autoconf are neither doing the trick :/
| [Friday 18 February 2011] [16:16:09] <bhuga_>	(then i found autogen.sh, not mentioned in the INSTALL :) )
| [Friday 18 February 2011] [16:25:28] <bhuga_>	(initial results with the new version are quite promising. thanks!)
| [Friday 18 February 2011] [16:33:14] <cremes>	bhuga_: good to hear
| [Friday 18 February 2011] [16:33:48] <bhuga_>	we are still getting it but its more deterministic now
| [Friday 18 February 2011] [16:34:13] <bhuga_>	makes me think we're using it wrong now as opposed to weird bugs
| [Friday 18 February 2011] [16:34:38] <cremes>	interesting
| [Friday 18 February 2011] [16:34:55] <cremes>	a reproducible case would be a great addition to that ticket i referenced earlier
| [Friday 18 February 2011] [16:35:58] <bhuga_>	well you know how testing these things are
| [Friday 18 February 2011] [16:36:05] <bhuga_>	by definition they're made to work with different languages, daemons, etc
| [Friday 18 February 2011] [16:36:20] <bhuga_>	if we can make a minimal case we will
| [Friday 18 February 2011] [16:36:25] <cremes>	cool
| [Friday 18 February 2011] [16:36:26] <bhuga_>	(though i suspect if i could i could just fix it)
| [Friday 18 February 2011] [16:36:34] <cremes>	:)
| [Friday 18 February 2011] [16:44:18] <bhuga_>	more testing reveals some more non-deterministic failures :( but i guess if nobody's heard of it before we'll have to figure it out
| [Friday 18 February 2011] [16:45:18] <cremes>	bhuga_: do you have any QUEUE devices in between your clients & servers?
| [Friday 18 February 2011] [16:45:40] <cremes>	if i understand your setup a bit, perhaps i can suggest a place to start looking
| [Friday 18 February 2011] [16:46:22] <bhuga_>	its really simple
| [Friday 18 February 2011] [16:46:36] <bhuga_>	the two are on the same machine, talking over an IPC (it might actually be ITC, i'd need to check) socket
| [Friday 18 February 2011] [16:46:50] <bhuga_>	REQ-REP from lisp talking to XREP on ruby
| [Friday 18 February 2011] [16:47:01] <bhuga_>	no other devices, no shenanigans
| [Friday 18 February 2011] [16:47:06] <cremes>	ok
| [Friday 18 February 2011] [16:47:26] <bhuga_>	the general feel of the upgrade is that it happens less, but it still happens
| [Friday 18 February 2011] [16:47:40] <cremes>	what do you mean by REQ-REP from lisp? is a req socket talking to *both* the rep lisp and xrep ruby sockets?
| [Friday 18 February 2011] [16:47:59] <bhuga_>	it's doing a request-reply pattern, sending a request, blocking waiting for a reply
| [Friday 18 February 2011] [16:48:25] <bhuga_>	the ruby bit is data-driven, receiving that message and sending a response
| [Friday 18 February 2011] [16:48:39] <cremes>	ok, so you have single req socket in the lisp program talking to a single xrep socket in ruby
| [Friday 18 February 2011] [16:49:10] <cremes>	and only the ruby side crashes?
| [Friday 18 February 2011] [16:49:45] <bhuga_>	only the ruby side crashes, correct
| [Friday 18 February 2011] [16:51:02] <cremes>	does it crash on recv or on send? and are these recv/sends blocking or non-blocking?
| [Friday 18 February 2011] [16:52:00] <bhuga_>	i dont actually know. it's hard to debug the assert. i have an strace of it
| [Friday 18 February 2011] [16:52:07] <bhuga_>	and ruby's not doing any syscalls on its own, i can say
| [Friday 18 February 2011] [16:52:13] <cremes>	ok
| [Friday 18 February 2011] [16:52:41] <bhuga_>	(apologies for spam:)
| [Friday 18 February 2011] [16:52:42] <bhuga_>	send(5, "\220#.\r\n\0\0\0\377\377\377\377\1\0\0\0\fQ\200\r\0302\236\f", 24, 0) = 24
| [Friday 18 February 2011] [16:52:42] <bhuga_>	recv(15, "\230P\200\r\2\0\0\0h\201E\r\24\0\0\0t\201E\r\364\357\f\267", 24, MSG_DONTWAIT) = 24
| [Friday 18 February 2011] [16:52:42] <bhuga_>	recv(15, "\230P\200\r\2\0\0\0\30#\6\r\330\264\251\10t\201E\r\364\357\f\267", 24, MSG_DONTWAIT) = 24
| [Friday 18 February 2011] [16:52:43] <bhuga_>	recv(15, "\230P\200\r\t\0\0\0h\201E\r\364\277\20\267\30#\6\r\3\0\0\0", 24, MSG_DONTWAIT) = 24
| [Friday 18 February 2011] [16:52:43] <bhuga_>	send(5, "h\201E\r\n\0\0\0\377\377\377\377\0\0\0\0\fQ\200\r\0302\236\f", 24, 0) = 24
| [Friday 18 February 2011] [16:52:43] <bhuga_>	recv(15, "\230P\200\r\4\0\0\0p\323o\r\210\34-\r\21\0\0\0\10O\266\v", 24, MSG_DONTWAIT) = 24
| [Friday 18 February 2011] [16:52:44] <bhuga_>	recv(15, "\250\335S\r\7\0\0\0\300\223M\267\364\177M\267\300\223M\267\30#\6\r", 24, MSG_DONTWAIT) = 24
| [Friday 18 February 2011] [16:52:44] <bhuga_>	send(5, "X\1_\r\10\0\0\0\300\223M\267\364\177M\267\300\223M\267\230P\200\r", 24, 0) = 24
| [Friday 18 February 2011] [16:52:44] <bhuga_>	recv(15, "\240\345<\r\5\0\0\0\300\223M\267\364\177M\267\300\223M\267\30#\6\r", 24, MSG_DONTWAIT) = 24
| [Friday 18 February 2011] [16:52:44] <bhuga_>	recv(15, "\230P\200\r\v\0\0\0\324\201E\r\0\0\0\0\n\0\0\0\364\277\20\267", 24, MSG_DONTWAIT) = 24
| [Friday 18 February 2011] [16:52:45] <bhuga_>	recv(15, 0xbfe7b514, 24, MSG_DONTWAIT)  = -1 EAGAIN (Resource temporarily unavailable)
| [Friday 18 February 2011] [16:52:45] <cremes>	can you puts a debug statement around the ruby send/recv calls to see which one is active during the crash?
| [Friday 18 February 2011] [16:52:45] <bhuga_>	send(5, "p<\350\f\7\0\0\0\300\223M\267\364\177M\267\300\223M\267\364\277\20\267", 24, 0) = 24
| [Friday 18 February 2011] [16:52:45] <bhuga_>	recv(15, "\240\345<\r\10\0\0\0h\201E\r\0\0\0\0\n\0\0\0\364\277\20\267", 24, MSG_DONTWAIT) = 24
| [Friday 18 February 2011] [16:53:13] <cremes>	bhuga_: use pastie.org or gist.github.com for anything over 2 lines, pls; that's really hard to read in the channel
| [Friday 18 February 2011] [16:53:17] <bhuga_>	yeah http://pastie.org/1580392
| [Friday 18 February 2011] [16:53:23] <bhuga_>	i got throttled anyway
| [Friday 18 February 2011] [16:53:53] <cremes>	can you puts a debug statement around the ruby send/recv calls to see which one is active during the crash?
| [Friday 18 February 2011] [16:54:25] <bhuga_>	based on the assertion, it seems to be receiving
| [Friday 18 February 2011] [16:54:30] <bhuga_>	it's asserting that it shouldn't be doing what it's about to do unless the message has more parts
| [Friday 18 February 2011] [16:54:55] <cremes>	ok
| [Friday 18 February 2011] [16:55:14] <cremes>	how are you forming the messages on the lisp end for transmission? are they simple strings?
| [Friday 18 February 2011] [16:55:27] <cremes>	encoded as json? protobufs, etc?
| [Friday 18 February 2011] [16:55:33] <bhuga_>	that i know less about :/
| [Friday 18 February 2011] [16:55:36] <cremes>	hell, s-expressions?
| [Friday 18 February 2011] [16:55:46] <cremes>	ok
| [Friday 18 February 2011] [16:55:59] <bhuga_>	im finding out
| [Friday 18 February 2011] [16:56:29] <bhuga_>	utf-8 encoded, null-terminated strings
| [Friday 18 February 2011] [16:56:41] <cremes>	ok
| [Friday 18 February 2011] [16:56:42] <bhuga_>	the content of them does not appear to matter
| [Friday 18 February 2011] [16:57:18] <bhuga_>	in that a given message (which we send from the lisp end, and reproduce) can be sent any number of times
| [Friday 18 February 2011] [16:57:46] <bhuga_>	until the random crash
| [Friday 18 February 2011] [16:58:08] <bhuga_>	(after playing with it, it seems a 50-100ms delay is sufficient to prevent the issue from appearing in simple tests)
| [Friday 18 February 2011] [16:58:08] <cremes>	can you try a req socket on the ruby end instead of xrep? it doesn't sound like you need the flexibility of an xrep anyway
| [Friday 18 February 2011] [16:58:48] <bhuga_>	hrm. i can try it, i think.
| [Friday 18 February 2011] [16:58:54] <bhuga_>	it will take me a minute
| [Friday 18 February 2011] [16:58:58] <cremes>	ok
| [Friday 18 February 2011] [16:59:19] <cremes>	with a rep socket you don't have to worry about creating the null message delimiter and such
| [Friday 18 February 2011] [16:59:28] <bhuga_>	(though the xrep is kind of what you need on ruby--we're currently only doing one task at a time but that's not the goal, and blocking is the devil)
| [Friday 18 February 2011] [16:59:52] <cremes>	yeah, but how does xrep help in that case? it's blocking too
| [Friday 18 February 2011] [17:00:16] <cremes>	you can use both rep and xrep with ZMQ::NOBLOCK; it isn't limited to just xrep
| [Friday 18 February 2011] [17:00:35] <bhuga_>	i guess i need to keep reading (i have taken this bug over from someone else)
| [Friday 18 February 2011] [17:00:58] <cremes>	can you pastie the ruby method that does the recv and the one that does the send?
| [Friday 18 February 2011] [17:01:41] <cremes>	i can probably help with the socket switch out... i wrote the ffi-rzmq gem so i'm pretty familiar with this stuff
| [Friday 18 February 2011] [17:02:53] <bhuga_>	okay, i can do that
| [Friday 18 February 2011] [17:03:51] <bhuga_>	http://pastie.org/1580429
| [Friday 18 February 2011] [17:04:16] <bhuga_>	there is a lot of silly metaprogramming going on
| [Friday 18 February 2011] [17:04:28] <bhuga_>	but the log_req in that method never happens
| [Friday 18 February 2011] [17:04:56] <bhuga_>	i can toss in a debug to make sure that it's getting to that socket.recv_string, which i suspect is the line
| [Friday 18 February 2011] [17:05:10] <cremes>	right
| [Friday 18 February 2011] [17:05:19] <cremes>	do you set any options on this socket?
| [Friday 18 February 2011] [17:05:31] <cremes>	e.g. socket.setsockopt(option, value)
| [Friday 18 February 2011] [17:05:56] <bhuga_>	the metaprogramming thing again. i'll try and output the current options in my forthcoming debug addition
| [Friday 18 February 2011] [17:06:38] <cremes>	ok
| [Friday 18 February 2011] [17:06:51] <cremes>	btw, nothing you are doing there requires an xrep socket
| [Friday 18 February 2011] [17:06:59] <bhuga_>	i believe you :)
| [Friday 18 February 2011] [17:07:04] <cremes>	but you do make things more complicated for yourself when you have to send the reply
| [Friday 18 February 2011] [17:07:05] <bhuga_>	and i will change it if need be
| [Friday 18 February 2011] [17:07:33] <bhuga_>	im afraid to change it just now since if we are doing the null-terminator thing that would perhaps no longer be correct?
| [Friday 18 February 2011] [17:07:41] <cremes>	right
| [Friday 18 February 2011] [17:07:58] <cremes>	you need to save the "return envelope" for the reply
| [Friday 18 February 2011] [17:08:17] <cremes>	and it is separated from the body of your messages by an empty/null message
| [Friday 18 February 2011] [17:08:30] <bhuga_>	is there a nice way to get all of the socket options?
| [Friday 18 February 2011] [17:08:40] <cremes>	search the code for setsockopt
| [Friday 18 February 2011] [17:09:01] <cremes>	if you don't find it, then you haven't set any beyond the defaults
| [Friday 18 February 2011] [17:09:34] <bhuga_>	 sockets[shard_id].setsockopt(ZMQ::LINGER, -1)
| [Friday 18 February 2011] [17:09:47] <bhuga_>	which i thing fixed a bug we had on exiting
| [Friday 18 February 2011] [17:10:08] <cremes>	yeah, it prevents the socket from closing until all packets are flushed
| [Friday 18 February 2011] [17:10:27] <bhuga_>	sounds about right, i think it was giving all kinds of errors when we tried to exit
| [Friday 18 February 2011] [17:10:30] <cremes>	just for kicks, can you comment that out and run your test? it crashes before it's done anyway, right?
| [Friday 18 February 2011] [17:10:36] <bhuga_>	yeah, i can do that
| [Friday 18 February 2011] [17:13:37] <bhuga_>	i dont think the linger is on the server
| [Friday 18 February 2011] [17:13:47] <bhuga_>	i think this is from a (being replaced by lisp) ruby client
| [Friday 18 February 2011] [17:13:57] <bhuga_>	could a server expecting a lingering client cause this behavior?
| [Friday 18 February 2011] [17:14:03] <cremes>	no
| [Friday 18 February 2011] [17:14:56] <cremes>	so, i think it is worthwhile for you to figure out how to swap the xrep for a rep socket
| [Friday 18 February 2011] [17:15:10] <cremes>	xrep is a lower-level 0mq socket so it is trickier to work with
| [Friday 18 February 2011] [17:15:38] <cremes>	from what i have seen, you don't need it; a rep socket and an xrep socket both 'block' the same way when sending/recving
| [Friday 18 February 2011] [17:16:08] <cremes>	you only use xrep when you want to break the strict send/recv/send/recv REQ-REP pattern
| [Friday 18 February 2011] [17:17:36] <bhuga_>	well, it will need to, of sorts. eventually the 'client' in this case will send out one request and get results of initially-unknown length back from n different workers
| [Friday 18 February 2011] [17:17:47] <bhuga_>	but not *yet*, necessarily :)
| [Friday 18 February 2011] [17:18:12] <cremes>	ok
| [Friday 18 February 2011] [17:18:28] <bhuga_>	but i'll investigate taht further and plug in some debug to make sure i know exactly what line of ruby is causing it
| [Friday 18 February 2011] [17:18:29] <cremes>	but remember the YAGNI principle :)
| [Friday 18 February 2011] [17:18:31] <bhuga_>	then update the issue
| [Friday 18 February 2011] [17:18:39] <cremes>	cool
| [Friday 18 February 2011] [17:18:50] <bhuga_>	if i pin it down
| [Friday 18 February 2011] [17:18:54] <bhuga_>	thanks for your time anyway
| [Friday 18 February 2011] [17:18:59] <cremes>	sure
| [Friday 18 February 2011] [17:19:05] <bhuga_>	best gem author ever
| [Friday 18 February 2011] [19:20:26] <Kinbote>	would it be possible to use zermomq as a kind of "router" for udp traffic, specfically SIP+RTP?
| [Friday 18 February 2011] [19:24:45] <sam`>	Kinbote: 0MQ uses its own wire protocol, so it's not "directly" compatible with software not using 0MQ
| [Friday 18 February 2011] [19:25:04] <sam`>	but you could listen on one side with a "normal" socket for UDP traffic
| [Friday 18 February 2011] [19:25:12] <sam`>	route that through your series of hops using ZMQ
| [Friday 18 February 2011] [19:25:25] <sam`>	and de-encapsulate at the end onto a normal socket
| [Friday 18 February 2011] [20:04:59] <stodge>	Anyone know if there are ubuntu packages for openpgm/zeromq/pyzmq?
| [Friday 18 February 2011] [20:05:40] <stodge>	Oops - accidentally left the channel. Did my question make it?
| [Friday 18 February 2011] [20:06:06] <stodge>	Are there Ubuntu packages for openpgm/zeromq/pyzmq?
| [Friday 18 February 2011] [20:31:10] <stodge>	How do I build pyzmq with openpgm support? I built openpgm, built zeromq --with-pgm and then built pyzmq. But zmq.EPGM isn't available
| [Saturday 19 February 2011] [11:09:23] <Steve-o>	sustrik: have a new alternative to types.h, following MSVC's CRT definitions
| [Saturday 19 February 2011] [12:36:48] <sustrik>	Steve-o: would that fix the 0mq build?
| [Saturday 19 February 2011] [12:37:02] <sustrik>	i've undefined bool
| [Saturday 19 February 2011] [12:37:10] <sustrik>	which fixed sunstudio build
| [Saturday 19 February 2011] [12:37:19] <sustrik>	however, the msvc build is still broken
| [Saturday 19 February 2011] [12:37:28] <sustrik>	no idea of what's going to
| [Saturday 19 February 2011] [12:37:32] <sustrik>	on*
| [Saturday 19 February 2011] [12:37:44] <Steve-o>	msvc has never complained here
| [Saturday 19 February 2011] [12:38:29] <Steve-o>	haven't tested 0mq & sunpro for a long while
| [Saturday 19 February 2011] [12:38:43] <Steve-o>	got an output log?
| [Saturday 19 February 2011] [12:44:10] <sustrik>	wait a sec
| [Saturday 19 February 2011] [12:45:02] <sustrik>	Steve-o: http://build.zero.mq/job/ZeroMQ2-core-master_MSVC-win7/184/console
| [Saturday 19 February 2011] [12:45:24] <sustrik>	that's 0mq master
| [Saturday 19 February 2011] [12:45:32] <sustrik>	it looks like there's still problem with bool
| [Saturday 19 February 2011] [12:45:52] <sustrik>	note that the "missing" function has bool argument
| [Saturday 19 February 2011] [12:46:22] <Steve-o>	I see
| [Saturday 19 February 2011] [12:46:40] <sustrik>	it's pgm_sender and pgm_receiver
| [Saturday 19 February 2011] [12:46:45] <sustrik>	which include pgm_socket
| [Saturday 19 February 2011] [12:46:52] <sustrik>	which in turn include pgm.h
| [Saturday 19 February 2011] [12:47:35] <Steve-o>	so what changed, how come 2.1.0 builds fine?
| [Saturday 19 February 2011] [12:48:41] <sustrik>	so what happened is that i've added a new argument to one internal 0mq function
| [Saturday 19 February 2011] [12:48:56] <sustrik>	it was a bool argument
| [Saturday 19 February 2011] [12:49:17] <Steve-o>	and conflicts trickled through, ok
| [Saturday 19 February 2011] [12:49:22] <sustrik>	right
| [Saturday 19 February 2011] [12:49:32] <sustrik>	then i've added something like this:
| [Saturday 19 February 2011] [12:49:35] <sustrik>	#include <pgm.h>
| [Saturday 19 February 2011] [12:49:42] <sustrik>	#ifdef bool
| [Saturday 19 February 2011] [12:49:48] <sustrik>	#undef bool
| [Saturday 19 February 2011] [12:49:50] <sustrik>	#endif
| [Saturday 19 February 2011] [12:49:50] <Steve-o>	as per your mail
| [Saturday 19 February 2011] [12:49:57] <sustrik>	yes
| [Saturday 19 February 2011] [12:50:05] <sustrik>	that fixed the sunstudio build
| [Saturday 19 February 2011] [12:50:18] <sustrik>	but caused different errors in msvc build
| [Saturday 19 February 2011] [12:50:28] <sustrik>	the ones you see now
| [Saturday 19 February 2011] [12:51:02] <Steve-o>	so the header and the code are using different definitions of bool still
| [Saturday 19 February 2011] [12:52:05] <sustrik>	yes, looks like that
| [Saturday 19 February 2011] [12:52:17] <guido_g>	howdy
| [Saturday 19 February 2011] [12:52:17] <sustrik>	no idea what exactly is wrong
| [Saturday 19 February 2011] [12:52:20] <sustrik>	hi
| [Saturday 19 February 2011] [12:52:22] <Steve-o>	well pgm.h is only included twice
| [Saturday 19 February 2011] [12:52:26] <sustrik>	yes
| [Saturday 19 February 2011] [12:52:33] <sustrik>	i've undefed bool at both places
| [Saturday 19 February 2011] [12:52:35] <guido_g>	any ideas why (e)pgm stopped working on the master?
| [Saturday 19 February 2011] [12:53:13] <sustrik>	no, but it looks like 0mq problem
| [Saturday 19 February 2011] [12:53:21] <guido_g>	ahh ok
| [Saturday 19 February 2011] [12:53:27] <sustrik>	presumably one of the recent patches have broken it
| [Saturday 19 February 2011] [12:53:50] <guido_g>	just asking because there was no feedback to the mail
| [Saturday 19 February 2011] [12:54:07] <sustrik>	are you experiencing the problem?
| [Saturday 19 February 2011] [12:54:14] <sustrik>	my problem is i have no test env
| [Saturday 19 February 2011] [12:54:24] <sustrik>	so it's hard for me to find out what's the problem
| [Saturday 19 February 2011] [12:54:35] <guido_g>	yes, i experienced the problem and reported it
| [Saturday 19 February 2011] [12:54:42] <sustrik>	i may try pgm over loopback though...
| [Saturday 19 February 2011] [12:54:57] <guido_g>	huh?
| [Saturday 19 February 2011] [12:55:08] <sustrik>	i have just a single box :)
| [Saturday 19 February 2011] [12:55:13] <guido_g>	lo doesn't do multicast
| [Saturday 19 February 2011] [12:55:24] <guido_g>	too bad
| [Saturday 19 February 2011] [12:55:26] <Steve-o>	my blade chassis is switched off and 50,000 miles away, I only have a windows laptop currently
| [Saturday 19 February 2011] [12:55:47] <Steve-o>	:D
| [Saturday 19 February 2011] [12:55:48] <sustrik>	still in NY?
| [Saturday 19 February 2011] [12:56:02] <Steve-o>	back in HK next week
| [Saturday 19 February 2011] [12:56:24] <Steve-o>	just working through a lot of contractor jobs
| [Saturday 19 February 2011] [12:56:29] <sustrik>	right
| [Saturday 19 February 2011] [12:56:50] <sustrik>	guido_g: there's simulated multicast over lo
| [Saturday 19 February 2011] [12:56:56] <sustrik>	i may try that
| [Saturday 19 February 2011] [12:57:26] <guido_g>	you simply use the external ip, mc isn't routed anyway
| [Saturday 19 February 2011] [12:57:51] <guido_g>	btw, this was the setup where i first discovered that something went wrong
| [Saturday 19 February 2011] [12:58:16] <guido_g>	normaly mc traffic is also routed back to the originating host
| [Saturday 19 February 2011] [12:58:28] <sustrik>	if i do that i won't see whether the message goes through or not
| [Saturday 19 February 2011] [12:58:48] <guido_g>	huh?
| [Saturday 19 February 2011] [12:58:58] <guido_g>	sorry, can't follow you
| [Saturday 19 February 2011] [12:59:12] <sustrik>	when i use a multicast group that nobody listens to
| [Saturday 19 February 2011] [12:59:21] <sustrik>	"you simply use the external ip, mc isn't routed anyway"
| [Saturday 19 February 2011] [13:00:22] <guido_g>	ment to mean that the mc traffic is not gouing to leave your local network when using the external ip of you box
| [Saturday 19 February 2011] [13:00:56] <guido_g>	and you don't have to play tricks w/ the network stack to make lo mc aware
| [Saturday 19 February 2011] [13:01:29] <guido_g>	or did you mean multicast loopback?
| [Saturday 19 February 2011] [13:01:29] <sustrik>	ok
| [Saturday 19 February 2011] [13:01:34] <sustrik>	yep
| [Saturday 19 February 2011] [13:01:38] <guido_g>	ahhh...
| [Saturday 19 February 2011] [13:01:39] <guido_g>	sorry
| [Saturday 19 February 2011] [13:01:43] <guido_g>	my fault then
| [Saturday 19 February 2011] [13:01:48] <sustrik>	never mind
| [Saturday 19 February 2011] [13:01:55] <guido_g>	i assumed loopback device
| [Saturday 19 February 2011] [13:02:14] <sustrik>	i'll try that am i'll see whether i can discover the bug that way
| [Saturday 19 February 2011] [13:02:29] <guido_g>	ok
| [Saturday 19 February 2011] [13:02:39] <guido_g>	thanks
| [Saturday 19 February 2011] [13:02:58] <guido_g>	if you think you have it, i can try it w/ two machines
| [Saturday 19 February 2011] [13:13:56] <Steve-o>	sustrik:  ugggggh, so I really have to use a pgm_bool_t?  Is MSVC picking up BOOL from inside pgm.h and breaking some C++ templates expecting bool?
| [Saturday 19 February 2011] [13:23:29] <Steve-o>	the xtree template warning with bool/BOOL conflict no longer occurs with OpenPGM trunk
| [Saturday 19 February 2011] [13:24:18] <Steve-o>	i.e. the new types.h:  http://code.google.com/p/openpgm/source/browse/trunk/openpgm/pgm/include/pgm/types.h
| [Saturday 19 February 2011] [13:33:19] <pieterh_>	sustrik, do we have a place in the git for tools like web api generation?
| [Saturday 19 February 2011] [13:33:19] <sustrik>	Steve-o: well, i'm not sure what's exactly going on
| [Saturday 19 February 2011] [13:33:34] <sustrik>	pieterh_: hm, not yet
| [Saturday 19 February 2011] [13:33:53] <pieterh_>	I guess this applies also to mikko's tools
| [Saturday 19 February 2011] [13:34:12] <sustrik>	the build system is scattered across the directiories
| [Saturday 19 February 2011] [13:34:20] <sustrik>	which is how autotools work
| [Saturday 19 February 2011] [13:34:31] <sustrik>	what about putting the scripts to doc subdir?
| [Saturday 19 February 2011] [13:34:42] <pieterh_>	hmm, ok what I'll do is make a separate tool that does this work
| [Saturday 19 February 2011] [13:34:47] <pieterh_>	in its own git
| [Saturday 19 February 2011] [13:34:58] <pieterh_>	since we have other projects with the same needs, e.g. zfl
| [Saturday 19 February 2011] [13:35:06] <sustrik>	as you wish
| [Saturday 19 February 2011] [13:35:22] <sustrik>	however, there are documentation generation scripts in doc subdir
| [Saturday 19 February 2011] [13:35:33] 	 * pieterh_ goes to check...
| [Saturday 19 February 2011] [13:35:48] <sustrik>	so placing one more there won't be completely ridiculous
| [Saturday 19 February 2011] [13:36:04] <sustrik>	Steve-o: i though that undefining bool should solve the issue...
| [Saturday 19 February 2011] [13:36:25] <pieterh_>	sustrik, what's there now is the straight man->txt/xml stuff
| [Saturday 19 February 2011] [13:36:28] <Steve-o>	not defining in the first place is better :D
| [Saturday 19 February 2011] [13:36:52] <pieterh_>	let me think this over for a couple of hours
| [Saturday 19 February 2011] [13:37:01] <sustrik>	pieterh_: txt->man/http
| [Saturday 19 February 2011] [13:37:08] <sustrik>	html*
| [Saturday 19 February 2011] [13:37:11] <sustrik>	Steve-o: yes
| [Saturday 19 February 2011] [13:37:19] <pieterh_>	yes, txt to man/html/xml
| [Saturday 19 February 2011] [13:37:28] <pieterh_>	I'm using the xml as input for this process
| [Saturday 19 February 2011] [13:37:34] <sustrik>	but as far as I understand you use your "bool" in PGM API, right?
| [Saturday 19 February 2011] [13:38:08] <sustrik>	pieterh: what xml?
| [Saturday 19 February 2011] [13:38:19] <pieterh_>	try 'make zmq.xml' in the doc directory
| [Saturday 19 February 2011] [13:38:24] <sustrik>	it's some intermediate asciidoc step?
| [Saturday 19 February 2011] [13:38:26] <sustrik>	a-ha
| [Saturday 19 February 2011] [13:38:28] <pieterh_>	sure
| [Saturday 19 February 2011] [13:38:31] <sustrik>	i see
| [Saturday 19 February 2011] [13:38:32] <pieterh_>	docbook xml format
| [Saturday 19 February 2011] [13:39:21] <sustrik>	Steve-o: maybe the bool in the API should be simply changed to int
| [Saturday 19 February 2011] [13:40:22] <sustrik>	pieterh_: i would say generating the wikidot source could be part of the build process
| [Saturday 19 February 2011] [13:40:31] <sustrik>	it introduces dependency on perl though
| [Saturday 19 February 2011] [13:40:46] <pieterh_>	sustrik, indeed
| [Saturday 19 February 2011] [13:41:16] <Steve-o>	try the update first, although it might indeed be that BOOL is too strongly typed
| [Saturday 19 February 2011] [13:41:29] <pieterh_>	let's aim for stand-alone tool which mikko can then integrate into his build processes
| [Saturday 19 February 2011] [13:41:41] <sustrik>	pieterh_: ok
| [Saturday 19 February 2011] [13:41:52] <sustrik>	Steve-o: ok
| [Saturday 19 February 2011] [13:41:57] <pieterh_>	:-)
| [Saturday 19 February 2011] [13:42:17] <pieterh_>	if there are other things we can profitably mechanically upload to the wiki, let me know
| [Saturday 19 February 2011] [13:43:07] <sustrik>	ultimately, the docs for stable version
| [Saturday 19 February 2011] [13:43:38] <sustrik>	on the other hand, raw html is much faster than wikidot
| [Saturday 19 February 2011] [13:43:55] <sustrik>	it's a trade-off, speed vs. nice design
| [Saturday 19 February 2011] [13:47:10] <pieterh_>	up to you, really
| [Saturday 19 February 2011] [13:47:58] <pieterh_>	it's faster with pure HTML but we can do more interesting things with Wikidot, e.g. Table of Contents, navigation, etc.
| [Saturday 19 February 2011] [13:48:13] <pieterh_>	our limiting factor is URLs, really
| [Saturday 19 February 2011] [13:48:42] <pieterh_>	api.zeromq.org/2.1.0/zmq_bind would work
| [Saturday 19 February 2011] [13:48:55] <pieterh_>	for each stable version released
| [Saturday 19 February 2011] [13:49:05] <pieterh_>	there are still people using 2.0.8 in production...
| [Saturday 19 February 2011] [13:49:46] <pieterh_>	sorry, my bad, wikidot doesn't allow subdirectories...
| [Saturday 19 February 2011] [13:50:21] <pieterh_>	api.zeromq.org/2-1-0:zmq_bind
| [Saturday 19 February 2011] [13:52:06] <sustrik>	no preference
| [Saturday 19 February 2011] [13:52:18] <sustrik>	should we ask on the ml?
| [Saturday 19 February 2011] [14:08:52] <pieterh_>	sustrik: ack
| [Saturday 19 February 2011] [16:28:14] <mikko>	g'evening
| [Saturday 19 February 2011] [17:03:33] <pieterh_>	mikko, top of the evening to you!
| [Saturday 19 February 2011] [17:43:05] <sustrik>	pieterh_: still there?
| [Saturday 19 February 2011] [17:57:33] <Steve-o>	wow, it's surprisingly tedious to detect single core machines with hyper-threading
| [Saturday 19 February 2011] [17:58:34] <mikko>	Steve-o: runtime?
| [Saturday 19 February 2011] [17:58:40] <Steve-o>	yup
| [Saturday 19 February 2011] [17:59:01] <Steve-o>	Windows XP SP3 has a backported API to walk the CPU topology to count packages, cores, logical processors
| [Saturday 19 February 2011] [17:59:27] <Steve-o>	CPUID seems to be a bit broken on new i3, i5, i7 processors
| [Saturday 19 February 2011] [17:59:47] <Steve-o>	every Unix has it's own custom API or /proc system
| [Saturday 19 February 2011] [18:00:48] <Steve-o>	I'm trying to see if I can at runtime catch the case of 1 core with HT enabled to stop spinlocks spinning
| [Saturday 19 February 2011] [18:01:54] <Steve-o>	it's probably futile as on Linux at least the system clock is pretty much only low resolution in such configurations as HT causes it to jump all over the place
| [Saturday 19 February 2011] [18:02:06] <mikko>	i got a vague memory about reading about this or something related
| [Saturday 19 February 2011] [18:03:02] <Steve-o>	I have something working in Windows but it's probably not worth committing
| [Saturday 19 February 2011] [18:04:34] <Steve-o>	I already use hyper-threading CPU pauses in spinlocks so that multi-core HT systems run fine
| [Saturday 19 February 2011] [18:06:42] <mikko>	btw, i don't know whether you saw this:
| [Saturday 19 February 2011] [18:06:51] <mikko>	https://github.com/mkoppanen/zeromq2/tree/openpgm-autoconf
| [Saturday 19 February 2011] [18:07:02] <mikko>	seems to be functional now
| [Saturday 19 February 2011] [18:10:20] <Steve-o>	ok great
| [Saturday 19 February 2011] [18:10:43] <mikko>	intel seems to have articles on detecting HT
| [Saturday 19 February 2011] [18:10:56] <mikko>	but when i try to follow the link to the article it 404s
| [Saturday 19 February 2011] [18:11:00] <Steve-o>	just have the recent fixes from sustrik for C++ and should be good to release soon
| [Saturday 19 February 2011] [18:11:18] <Steve-o>	detecting HT is easy with CPUID, counting the physical cores is a bit difficult
| [Saturday 19 February 2011] [18:11:35] <Steve-o>	or rather the number of logical processors CPUID returns no longer appears valid
| [Saturday 19 February 2011] [18:12:35] <Steve-o>	there's a question on stackoverflow with i7 cores
| [Saturday 19 February 2011] [18:12:46] <Steve-o>	anyway, must dash, ciao
| [Saturday 19 February 2011] [18:13:10] <mikko>	see you
| [Saturday 19 February 2011] [21:16:16] <Jay7_>	Hey I'm new to ZMQ and tried installing in on a Mac OSX 10.6.3; but it appears --with-pgm is not supported currently on darwin.  Is this expected in the near future by chance?
| [Saturday 19 February 2011] [21:28:57] <cremes>	Jay7_: i'm not a pgm expert, but apparently the openpgm package (a separate project from 0mq) doesn't have good/any osx support
| [Saturday 19 February 2011] [21:29:09] <cremes>	Jay7_: check the mailing list archives for more discussion on this
| [Saturday 19 February 2011] [21:29:52] <Jay7_>	@cremes_: ah, okay. Thank you. I'll look through those.
| [Sunday 20 February 2011] [02:51:40] <pieterh_>	sustrik: hi
| [Sunday 20 February 2011] [02:53:15] <rem7>	Hi, I was going over the zmq guide, I noticed the examples use strings as messages. If I want to send something like floats is it ok to just memcpy the float, or should I use something like protobuffers?
| [Sunday 20 February 2011] [02:53:59] <pieterh_>	rem7, depends on your needs
| [Sunday 20 February 2011] [02:54:40] <pieterh_>	sending data as-such is easy and cheap but doesn't give you any kind of leverage
| [Sunday 20 February 2011] [02:54:43] <rem7>	I just need to pass float arrays... using a PUSH/PULL system.
| [Sunday 20 February 2011] [02:55:01] <pieterh_>	if it's a throw-away app, go for it
| [Sunday 20 February 2011] [02:55:16] <pieterh_>	if it's something you are more serious about, make formal 'contracts' 
| [Sunday 20 February 2011] [02:55:28] <pieterh_>	i.e. serialize your data properly (portably), document the message formats, etc.
| [Sunday 20 February 2011] [02:55:46] <pieterh_>	it's a lot more work up front but lets you work more cheaply long term
| [Sunday 20 February 2011] [02:56:07] <pieterh_>	e.g. plug in a worker in a different language
| [Sunday 20 February 2011] [02:56:43] <rem7>	would using google proto buffers take care of that? 
| [Sunday 20 February 2011] [02:57:00] <rem7>	I don't have much experience with this kinda of stuff...
| [Sunday 20 February 2011] [03:15:21] <pieterh_>	rem7, yes, it would
| [Sunday 20 February 2011] [03:18:17] <rem7>	pieterh_:  I guess I'll start looking into that. Thanks.
| [Sunday 20 February 2011] [03:18:27] <pieterh_>	let us know how it goes
| [Sunday 20 February 2011] [03:20:15] <guido_g>	smaller alternative might be http://msgpack.org/
| [Sunday 20 February 2011] [03:22:23] <rem7>	guido_g: thanks, I'll look into it
| [Sunday 20 February 2011] [03:42:39] <sustrik>	pieterh_: morning
| [Sunday 20 February 2011] [03:56:53] <pieterh_>	sustrik, hi
| [Sunday 20 February 2011] [03:58:31] <pieterh_>	do you think the red theme is readable enough for the man pages?
| [Sunday 20 February 2011] [05:28:25] <pieter_hintjens>	anyone looked at distributed hash tables on top of 0MQ, e.g. Chord?
| [Sunday 20 February 2011] [05:52:46] <travlr>	hi all. i've got a question about interfacing zmq in Qt having read up a lot on what's going on I'm still a little confused about zmq's edge-trigger....
| [Sunday 20 February 2011] [05:53:21] <travlr>	Qt has a QSocketNotifier class that provides a signal when there is activity on a profided FD
| [Sunday 20 February 2011] [05:53:47] <travlr>	like from zmq_getsockopt(... ZMQ_FD...)
| [Sunday 20 February 2011] [05:54:15] <travlr>	I'm assuming that the Qt sig is level triggered.
| [Sunday 20 February 2011] [05:56:19] <travlr>	so when I get a signal from QSocketNotifier, I check the ZMQ_EVENTS for ZMQ_POLLIN (in this case) and ....
| [Sunday 20 February 2011] [05:56:33] <travlr>	what do I do exactly when I get EAGAIN?
| [Sunday 20 February 2011] [06:02:30] <travlr>	I'm guessing that I need to keep calling zmq_recv() until I do get the EAGAIN condition.
| [Sunday 20 February 2011] [06:06:37] <pieter_hintjens>	travlr: sorry, can't really help, not sure what the edge trigger vs. level trigger is about
| [Sunday 20 February 2011] [06:06:45] <pieter_hintjens>	try invoking sustrik... :-)
| [Sunday 20 February 2011] [06:07:00] <travlr>	hi pieter.. ok, thanks just the same 
| [Sunday 20 February 2011] [06:42:05] <private_meta>	Is it possible to download a certain language bound example-set (or all of them if necessary) without having to install the entire git suite?
| [Sunday 20 February 2011] [06:42:58] <travlr>	private_meta: each binding has its own git repo.. i think
| [Sunday 20 February 2011] [06:43:20] <private_meta>	I meant that one https://github.com/imatix/zguide/tree/master/examples
| [Sunday 20 February 2011] [06:43:30] <private_meta>	and/or the dedicated subdirectories/trees
| [Sunday 20 February 2011] [06:43:43] <private_meta>	brb
| [Sunday 20 February 2011] [06:44:42] <travlr>	no. but the that download isn't that big anyway
| [Sunday 20 February 2011] [07:05:42] <sustrik>	travlr: yes
| [Sunday 20 February 2011] [07:05:57] <sustrik>	you have to call recv() till you get EAGAIN
| [Sunday 20 February 2011] [07:06:17] <private_meta>	travlr: I don't want to download 40 files per language, it's a hassle
| [Sunday 20 February 2011] [07:15:26] <mikko>	good morning all
| [Sunday 20 February 2011] [07:16:52] <sustrik>	morning
| [Sunday 20 February 2011] [07:24:11] <mikko>	build failure on s390x
| [Sunday 20 February 2011] [07:24:18] <mikko>	but that is due to shutdown_stress
| [Sunday 20 February 2011] [07:35:53] <pieter_hintjens>	mikko: quick question
| [Sunday 20 February 2011] [07:39:47] <pieter_hintjens>	private_meta: it takes about 30 seconds to clone the git
| [Sunday 20 February 2011] [07:40:47] <pieter_hintjens>	and it's nice that people get the git because they can then translate the examples into other languages
| [Sunday 20 February 2011] [07:42:36] <pieter_hintjens>	private_meta: ah, you can click on 'Downloads' on the github page and get a .zip or .tar.gz. file
| [Sunday 20 February 2011] [07:45:04] <mikko>	pieter_hintjens: sure
| [Sunday 20 February 2011] [07:45:12] <mikko>	what is the question?
| [Sunday 20 February 2011] [07:45:56] <pieter_hintjens>	mikko: I have scripts that will rebuild api.zero.mq from the git repo
| [Sunday 20 February 2011] [07:46:04] <pieter_hintjens>	bash/perl/python
| [Sunday 20 February 2011] [07:46:22] <mikko>	do you want to run it automatically on daily builds?
| [Sunday 20 February 2011] [07:46:30] <pieter_hintjens>	at least for master, I think, yes
| [Sunday 20 February 2011] [07:46:46] <mikko>	of course
| [Sunday 20 February 2011] [07:46:49] <pieter_hintjens>	also for any branch that is being maintained...
| [Sunday 20 February 2011] [07:46:51] <mikko>	is the script available somewhere?
| [Sunday 20 February 2011] [07:47:16] <mikko>	thats perfectly fine, the box is idle apart from the 5am/pm builds
| [Sunday 20 February 2011] [07:47:21] <pieter_hintjens>	I guess the question is whether the scripts should be in their own git, the zeromq2 git, or just floating around somewhere
| [Sunday 20 February 2011] [07:47:43] <pieter_hintjens>	eventually we could do the same for the zfl man pages
| [Sunday 20 February 2011] [07:47:45] <mikko>	well, i think we could have git for random infra stuff
| [Sunday 20 February 2011] [07:47:55] <pieter_hintjens>	ztools?
| [Sunday 20 February 2011] [07:47:55] <mikko>	i got some scripts on the build server that could be there as well
| [Sunday 20 February 2011] [07:48:07] <mikko>	which are not available anywhere now etc
| [Sunday 20 February 2011] [07:48:10] <pieter_hintjens>	indeed
| [Sunday 20 February 2011] [07:49:06] <pieter_hintjens>	so a new git that collects all the random tools we make?
| [Sunday 20 February 2011] [07:49:23] <mikko>	it wouldn't probably something usable for people out of the box
| [Sunday 20 February 2011] [07:49:31] <mikko>	but just to make sure that everything is available
| [Sunday 20 February 2011] [07:49:48] <pieter_hintjens>	right
| [Sunday 20 February 2011] [07:49:58] <pieter_hintjens>	in the zeromq organization would be best
| [Sunday 20 February 2011] [07:50:05] <mikko>	yeah, probably
| [Sunday 20 February 2011] [07:50:54] <pieter_hintjens>	git@github.com:zeromq/ztools.git
| [Sunday 20 February 2011] [07:51:21] <mikko>	cool, i'll add things there later
| [Sunday 20 February 2011] [07:51:26] <pieter_hintjens>	I'll whip up a README, I suggest one directory per tool
| [Sunday 20 February 2011] [07:51:40] <mikko>	yeah
| [Sunday 20 February 2011] [07:51:43] <mikko>	makes sense
| [Sunday 20 February 2011] [07:51:57] <mikko>	lunch, brb
| [Sunday 20 February 2011] [07:53:20] <pieter_hintjens>	ok, you should have rw access
| [Sunday 20 February 2011] [07:53:22] <pieter_hintjens>	cyl
| [Sunday 20 February 2011] [07:53:47] <private_meta>	pieter_hintjens: the download page was empty for me
| [Sunday 20 February 2011] [07:54:10] <pieter_hintjens>	private_meta: ? it should pop up a window asking if you want a .zip or .tar.gz...
| [Sunday 20 February 2011] [07:54:28] <pieter_hintjens>	what URL did you get?
| [Sunday 20 February 2011] [07:54:42] <pieter_hintjens>	You want to be here: https://github.com/zeromq/zfl
| [Sunday 20 February 2011] [07:54:51] <pieter_hintjens>	then click on Downloads
| [Sunday 20 February 2011] [07:55:17] <pieter_hintjens>	sorry!
| [Sunday 20 February 2011] [07:55:23] <pieter_hintjens>	https://github.com/imatix/zguide
| [Sunday 20 February 2011] [07:56:23] <private_meta>	pieter_hintjens: "should" is such a nice word, covers all kinds of possibilities, mostly the "not" possibility for me
| [Sunday 20 February 2011] [07:56:43] <Guthur>	it works fine here
| [Sunday 20 February 2011] [07:57:03] <pieter_hintjens>	private_meta: please explain in more detail what you do, and what happens
| [Sunday 20 February 2011] [07:57:19] <pieter_hintjens>	"it doesn't work" is not useful...
| [Sunday 20 February 2011] [08:01:34] <pieter_hintjens>	ok, lunch, bbl
| [Sunday 20 February 2011] [08:04:57] <private_meta>	yay... demonstrative effect... had "no downloads" or something like that for half a week, now I ASK about it nd it shows downloads
| [Sunday 20 February 2011] [08:05:07] <private_meta>	I hate that
| [Sunday 20 February 2011] [08:07:16] <Guthur>	well, at least it's working, hehe
| [Sunday 20 February 2011] [08:13:05] <private_meta>	I'm not sure anymore, someone might have told me already, but where in the guide can I find some info about how to implement heartbeating. according to the guide it has to do something with zmq_poll, but I don't find anything helpful on zmq_poll. I want to do something like heartbeat pings, but I'm not sure how to do it exactly
| [Sunday 20 February 2011] [08:19:46] <mikko>	pieter_hintjens: http://snapshot.zero.mq/zfl/
| [Sunday 20 February 2011] [08:23:45] <mikko>	private_meta: normally you would send a heartbeat request to client
| [Sunday 20 February 2011] [08:23:52] <mikko>	zmq_poll for incoming messages
| [Sunday 20 February 2011] [08:24:02] <mikko>	no message in given timeout -> consider dead
| [Sunday 20 February 2011] [08:25:48] <private_meta>	I don't quite understand zmq_poll and how to use it yet. I'm reading the man page, but i need to see how to be able to use the zmq_poll system.
| [Sunday 20 February 2011] [08:26:24] <private_meta>	So the heartbeat request would be a normal message that's recognizable as a heartbeat for the other side I assume?
| [Sunday 20 February 2011] [08:26:43] <mikko>	see "Handling Multiple Sockets
| [Sunday 20 February 2011] [08:26:47] <mikko>	in the zguide
| [Sunday 20 February 2011] [08:27:03] <mikko>	yes, or even a separate heartbeat socket
| [Sunday 20 February 2011] [08:27:10] <mikko>	depends on the application
| [Sunday 20 February 2011] [08:28:53] <private_meta>	A separate socket might be an interesting idea, thanks. I'll read up the multiple sockets first
| [Sunday 20 February 2011] [08:29:56] <mikko>	for example if you got PUSH/PULL as main socket you can't really heartbeat over it
| [Sunday 20 February 2011] [08:31:23] <private_meta>	So do push/pull stand for dedicated one-way-communication endpoints?
| [Sunday 20 February 2011] [08:32:15] <mikko>	http://api.zero.mq/2-1-0:zmq-socket
| [Sunday 20 February 2011] [08:32:26] <mikko>	you can see the characteristics of each socket type from here
| [Sunday 20 February 2011] [08:32:40] <private_meta>	i hate surfing on gprs
| [Sunday 20 February 2011] [08:32:48] <private_meta>	thanks
| [Sunday 20 February 2011] [08:32:48] <mikko>	whether they force a pattern, uni-directional/bi-directional
| [Sunday 20 February 2011] [08:32:58] <mikko>	if you got zeromq installed the man pages should work as well
| [Sunday 20 February 2011] [08:33:13] <private_meta>	thought as much
| [Sunday 20 February 2011] [08:35:57] <mikko>	XREP/XREQ is probably the most suitable socket for heartbeating
| [Sunday 20 February 2011] [08:37:31] <private_meta>	Well, I have 1 server, multiple clients, and I need to address these clients separately and each of these clients need to check heartbeats, or at least know if a connection terminates
| [Sunday 20 February 2011] [08:37:47] <private_meta>	while these connections are bidirectional
| [Sunday 20 February 2011] [08:39:08] <mikko>	yep, definitely XREQ/XREP
| [Sunday 20 February 2011] [08:39:16] <mikko>	i think zguide has an example of custom routing
| [Sunday 20 February 2011] [08:39:20] <mikko>	which is needed here
| [Sunday 20 February 2011] [08:39:41] <private_meta>	so the normal req/rep is balanced automatically all the time?
| [Sunday 20 February 2011] [08:40:06] <private_meta>	or is xreq and xrep as well, normally?
| [Sunday 20 February 2011] [08:41:23] <private_meta>	I have a slight difficulty understanding the terminology for the custom routing I find in the guide. dealer, mama, papa, router. Assuming I need one of those, I don't know what these terms actually mean
| [Sunday 20 February 2011] [08:42:48] <private_meta>	ah...think i found the explanation
| [Sunday 20 February 2011] [08:44:17] <private_meta>	so i'd need router-to-router,
| [Sunday 20 February 2011] [08:45:04] <mikko>	private_meta: xrep/xrep doesnt force request-reply pattern as strictly as req/rep
| [Sunday 20 February 2011] [08:45:26] <mikko>	in your case you might want "req client 1, req client 2, req client 3", "wait responses from all"
| [Sunday 20 February 2011] [08:45:29] <mikko>	i guess
| [Sunday 20 February 2011] [08:45:46] <private_meta>	uhm... train station coming up, brb
| [Sunday 20 February 2011] [08:45:48] <mikko>	not necessarily req client 1, wait for rep client 1, req client 2 
| [Sunday 20 February 2011] [08:45:49] <mikko>	etc
| [Sunday 20 February 2011] [08:46:39] <mikko>	pieterh_: snapshots for zfl are now generated during builds
| [Sunday 20 February 2011] [08:57:09] <private_meta>	mikko: According to some of the terminology: Server-to-N-Clients connection, no forced request-to-reply pattern and standard-async-but-sync-by-choice (by higher level wrapper)
| [Sunday 20 February 2011] [08:57:17] <private_meta>	Is what I need
| [Sunday 20 February 2011] [08:58:31] <private_meta>	and non-balanced directly addressed messaging
| [Sunday 20 February 2011] [09:04:04] <private_meta>	mikko: concerning multiple sockets, Actually I want the connections incoming at the SAME socket, like all connection incoming at tcp port (e.g.) 5555. Still I want to address all connected clients separately
| [Sunday 20 February 2011] [09:10:22] <pieterh_>	private_meta, see LRU routing in Ch3 of the Guide
| [Sunday 20 February 2011] [09:10:54] <pieterh_>	mikko: nice, snapshots
| [Sunday 20 February 2011] [09:12:09] <private_meta>	pieterh_: you mean as in "lru uses several clients/workers connecting to the same socket"?
| [Sunday 20 February 2011] [09:12:22] <pieterh_>	private_meta, yes, it gives you the basic framework
| [Sunday 20 February 2011] [09:12:41] <pieterh_>	you will want to do your own routing, not LRU
| [Sunday 20 February 2011] [09:13:01] <private_meta>	Yes
| [Sunday 20 February 2011] [09:13:58] <private_meta>	pieterh_: do you know why the c++ version uses void* instead of char* for messages??
| [Sunday 20 February 2011] [09:14:18] <pieterh_>	private_meta, no idea...
| [Sunday 20 February 2011] [09:14:27] <private_meta>	kk
| [Sunday 20 February 2011] [09:18:08] <private_meta>	hmm... 3g networks are way too spotty here outside of towns... it's a hassle working in trains :/
| [Sunday 20 February 2011] [09:21:43] <private_meta>	pieterh_: not quite sure I understand correctly, for demonstrative purposes, in the lru example the client and server code is in one file and only executed in threads so you don't have separate server/client files?
| [Sunday 20 February 2011] [09:22:00] <pieterh_>	private_meta, yes, it's just to simplify the exercise
| [Sunday 20 February 2011] [09:22:08] <private_meta>	ok
| [Sunday 20 February 2011] [09:22:13] <pieterh_>	the code in each thread is the same as it would be in a separate process
| [Sunday 20 February 2011] [09:22:19] <pieterh_>	with a little less wrapping
| [Sunday 20 February 2011] [09:22:27] <private_meta>	Thanks!
| [Sunday 20 February 2011] [09:30:31] <private_meta>	hmm... the lru example on git seems pretty different from the guide example
| [Sunday 20 February 2011] [09:32:39] <pieterh_>	private_meta,  what URL?
| [Sunday 20 February 2011] [09:32:59] <pieterh_>	are you looking at the same two languages?
| [Sunday 20 February 2011] [09:33:24] <private_meta>	Ah, let me look a second
| [Sunday 20 February 2011] [09:34:02] <private_meta>	Ah, i thought i was looking at the lruqueue example in the guide, it was rtmama
| [Sunday 20 February 2011] [09:34:27] <private_meta>	Sorry
| [Sunday 20 February 2011] [09:35:48] <private_meta>	mama is not ideal for me i guess, everyone should be able to initiate a message
| [Sunday 20 February 2011] [11:12:32] <mikko>	private_meta: it's void* because it's not really an array of characters
| [Sunday 20 February 2011] [11:12:40] <mikko>	rather a blob of data of size X
| [Sunday 20 February 2011] [11:42:32] <private_meta>	mikko: "just because you are sending strings over a line most of the time doesn't mean everyone does"
| [Sunday 20 February 2011] [11:42:37] <private_meta>	mikko: something like that?
| [Sunday 20 February 2011] [11:43:30] <private_meta>	I guess representing something other than a string AS a string might be a severe waste of space...
| [Sunday 20 February 2011] [11:48:03] <mikko>	private_meta: it's also conceptual thing
| [Sunday 20 February 2011] [11:48:15] <mikko>	private_meta: using the inproc transport you might send a pointer to a struct
| [Sunday 20 February 2011] [11:48:21] <mikko>	or just about anything
| [Sunday 20 February 2011] [11:48:25] <mikko>	rather than char*
| [Sunday 20 February 2011] [11:50:36] <mikko>	private_meta: but yes, you are right
| [Sunday 20 February 2011] [11:51:21] <private_meta>	I didn't think of using a message queue from an external library for in-process messaging
| [Sunday 20 February 2011] [11:51:37] <private_meta>	ah, between threads it might be handy i guess
| [Sunday 20 February 2011] [11:53:23] <mikko>	private_meta: http://www.zeromq.org/blog:multithreading-magic
| [Sunday 20 February 2011] [11:53:29] <mikko>	related post
| [Sunday 20 February 2011] [12:24:10] <Guthur>	imho inproc messaging is a big win
| [Sunday 20 February 2011] [12:24:43] <Guthur>	the multithreading magic article explains it best though
| [Sunday 20 February 2011] [12:47:41] <andrewvc>	anyone know if zmq_queue supports xreq/xrep or just rep/req
| [Sunday 20 February 2011] [12:56:33] <sustrik>	andrewvc: just xreq/xrep :)
| [Sunday 20 February 2011] [12:56:45] <andrewvc>	oh, awesome :)
| [Sunday 20 February 2011] [13:00:52] <travlr>	sustrik: thanks for the help earlier
| [Sunday 20 February 2011] [13:02:10] <sustrik>	you are welcome
| [Sunday 20 February 2011] [13:02:44] <sustrik>	travlr: if you feel the reference is unclear, feel free to suggest a patch
| [Sunday 20 February 2011] [13:05:23] <travlr>	i will. i'm just coming back to my work with zmq after having to totally focus on other stuff for a while.
| [Sunday 20 February 2011] [13:05:37] <travlr>	 I also have to get the internal api bot working again at http://travlr.github.com/zeromq2
| [Sunday 20 February 2011] [13:06:14] <travlr>	as its broken atm
| [Sunday 20 February 2011] [13:07:20] <Guthur>	is the new API doc only beta at the moment
| [Sunday 20 February 2011] [13:07:36] <Guthur>	I'm just wondering why it's not linked from the main site
| [Sunday 20 February 2011] [13:08:03] <sustrik>	well, pieter have written the generator yesterday
| [Sunday 20 February 2011] [13:08:05] <sustrik>	that's why
| [Sunday 20 February 2011] [13:08:43] <Guthur>	ah, ok
| [Sunday 20 February 2011] [13:09:12] <Guthur>	it does seem very good though
| [Sunday 20 February 2011] [13:10:26] <travlr>	nice! l like the the new reference links from a simple index.
| [Sunday 20 February 2011] [13:10:41] <sustrik>	what's particularly nice is that all the released versions are covered
| [Sunday 20 February 2011] [13:10:47] <travlr>	yup
| [Sunday 20 February 2011] [13:20:55] <andrewvc>	Are there any examples of the XML for zmq_queue?
| [Sunday 20 February 2011] [13:21:10] <andrewvc>	the manpage is empty of course, and my google-fu is failing me
| [Sunday 20 February 2011] [13:26:20] <andrewvc>	nm, figured it out
| [Sunday 20 February 2011] [13:53:40] <pieterh_>	sustrik, mikko and I will arrange to rebuild the docs once a day or so
| [Sunday 20 February 2011] [13:55:50] <sustrik>	pieterh_: great
| [Sunday 20 February 2011] [13:56:10] <sustrik>	if you do it twice a day, the docs will be in sync with latest snapshots
| [Sunday 20 February 2011] [13:56:13] <pieterh_>	we've made a ztools git for random tools, incl the rebuild shells scripts
| [Sunday 20 February 2011] [13:56:31] <sustrik>	ack
| [Sunday 20 February 2011] [13:56:50] <pieterh_>	let's see if people have more comments on the look & feel
| [Sunday 20 February 2011] [13:57:01] <pieterh_>	i already toned it down, darker red, no logo on man pages, etc.
| [Sunday 20 February 2011] [13:57:17] <sustrik>	let me see
| [Sunday 20 February 2011] [13:57:47] <sustrik>	nice
| [Sunday 20 February 2011] [13:57:54] <sustrik>	btw, what about the stable branch, do you have any schedule for doing the fork?
| [Sunday 20 February 2011] [13:58:29] <pieterh_>	next week sometime, I was thinking
| [Sunday 20 February 2011] [13:58:33] <sustrik>	great
| [Sunday 20 February 2011] [13:59:00] <pieterh_>	ok, good!
| [Sunday 20 February 2011] [13:59:12] <pieterh_>	people will be happy to see a new stable 2.1.x version
| [Sunday 20 February 2011] [13:59:26] <pieterh_>	so many new goodies :-)
| [Sunday 20 February 2011] [13:59:26] <sustrik>	i think so
| [Sunday 20 February 2011] [13:59:34] <sustrik>	so will I
| [Sunday 20 February 2011] [13:59:49] <pieterh_>	I'll keep the 2.0.x version of the Guide online as well
| [Sunday 20 February 2011] [14:00:07] <sustrik>	i like that all the versions are available
| [Sunday 20 February 2011] [14:00:20] <sustrik>	ah, the guide
| [Sunday 20 February 2011] [14:00:21] <pieterh_>	yes, people have asked for that... 
| [Sunday 20 February 2011] [14:00:39] <pieterh_>	so I will update that for 2.1, and keep the 2.0 version for reference
| [Sunday 20 February 2011] [14:00:43] <sustrik>	i've checked it lately and it seemed to cover both 2.0 and 2.1
| [Sunday 20 February 2011] [14:01:17] <pieterh_>	in several places it covers things that were changed
| [Sunday 20 February 2011] [14:01:24] <pieterh_>	e.g. socket migration, socket shutdown
| [Sunday 20 February 2011] [14:01:30] <pieterh_>	needs fixing for 2.1
| [Sunday 20 February 2011] [14:01:35] <sustrik>	right
| [Sunday 20 February 2011] [14:01:45] <pieterh_>	hmm, perhaps better is a section with explicit differences
| [Sunday 20 February 2011] [14:01:57] <sustrik>	it's up to you
| [Sunday 20 February 2011] [14:02:19] <pieterh_>	i think as a programmer, what I want is "what changed in 2.1 and what does this mean for my code?"
| [Sunday 20 February 2011] [14:02:28] <pieterh_>	expanded release notes with some jokes
| [Sunday 20 February 2011] [14:02:37] <sustrik>	sounds good
| [Sunday 20 February 2011] [14:02:42] <pieterh_>	ok!
| [Sunday 20 February 2011] [14:03:27] <mikko>	good stuff
| [Sunday 20 February 2011] [14:03:40] <mikko>	do you have the build script online already?
| [Sunday 20 February 2011] [14:03:43] <mikko>	the documentation one
| [Sunday 20 February 2011] [14:04:32] <mikko>	my todo-list is almost empty now
| [Sunday 20 February 2011] [14:04:39] <mikko>	apart from testing openpgm on solaris
| [Sunday 20 February 2011] [14:06:14] <pieterh_>	mikko: I'm documenting / cleaning it up, will publish it asap
| [Sunday 20 February 2011] [14:07:20] <mikko>	pieterh_: cool
| [Sunday 20 February 2011] [14:07:30] <mikko>	any other periodic things that should be automated?
| [Sunday 20 February 2011] [14:08:18] <pieterh_>	mikko the machine
| [Sunday 20 February 2011] [14:08:26] <pieterh_>	no todo list can survive
| [Sunday 20 February 2011] [14:08:28] <Guthur>	pieterh_, my first impression of the new api doc is that it is very good
| [Sunday 20 February 2011] [14:08:33] <Guthur>	well done
| [Sunday 20 February 2011] [14:08:51] <pieterh_>	Guthur, I'm glad you like it...
| [Sunday 20 February 2011] [14:09:16] <Guthur>	I'd imagine most will have similar impressions
| [Sunday 20 February 2011] [14:09:21] <pieterh_>	not too painful to read? it's the usual cortex red scheme but toned down a little
| [Sunday 20 February 2011] [14:09:48] <Guthur>	nope the styling is very good, for my tastes
| [Sunday 20 February 2011] [14:10:12] <mikko>	lestrrat: are you there?
| [Sunday 20 February 2011] [14:10:15] <Guthur>	must dash though
| [Sunday 20 February 2011] [14:13:11] <pieterh_>	mikko: you'll need to get an API key from Wikidot
| [Sunday 20 February 2011] [14:13:27] <pieterh_>	it's tied to your account
| [Sunday 20 February 2011] [14:13:51] <pieterh_>	if you don't already have a Wikidot.com account, register and tell me your account name
| [Sunday 20 February 2011] [14:14:00] <pieterh_>	then I'll get them to give you API access and a key
| [Sunday 20 February 2011] [14:14:15] <mikko>	mkoppanen
| [Sunday 20 February 2011] [14:17:50] <pieterh_>	ok
| [Sunday 20 February 2011] [14:49:38] <pieterh_>	mikko: ok, the tool is documented and packaged for reuse 
| [Sunday 20 February 2011] [15:42:20] <jobytaffey>	Hi, I was wondering if anyone can help out. I'm new to 0MQ. I'm trying to write a TCP server which accepts many incoming connections, reads fixed sized packets from TCP and generates 0MQ messages for handling somewhere else. I'm using libev and the receive side seems fine. But, for sending (receive 0MQ message then put it onto a TCP socket), it looks like I need to zmq_poll() when libev gives me EV_WRITE, is there a better way of doing this? A zmq ca
| [Sunday 20 February 2011] [15:43:31] <mikko>	jobytaffey: yes
| [Sunday 20 February 2011] [15:43:47] <mikko>	jobytaffey: you should schedule libev EV_WRITE only if you got message coming from zeromq
| [Sunday 20 February 2011] [15:44:00] <mikko>	so roughly the following (assuming zeromq 2.1.x)
| [Sunday 20 February 2011] [15:44:24] <mikko>	you schedule constant read event for incoming tcp messages and incoming zeromq messages
| [Sunday 20 February 2011] [15:44:48] <mikko>	if you get tcp message in you schedule a EV_WRITE for zeromq out socket
| [Sunday 20 February 2011] [15:45:01] <mikko>	and if you get zeromq message in you schedule EV_WRITE for tcp socket
| [Sunday 20 February 2011] [15:45:57] <jobytaffey>	Ok, that makes sense. I didn't see anything in the API for getting at zeromq's underlying sockets though?
| [Sunday 20 February 2011] [15:46:07] <mikko>	jobytaffey: it's a feature in 2.1.x
| [Sunday 20 February 2011] [15:46:10] <mikko>	give me a sec
| [Sunday 20 February 2011] [15:46:38] <mikko>	jobytaffey: http://api.zero.mq/master:zmq-getsockopt see ZMQ_FD and ZMQ_EVENTS there
| [Sunday 20 February 2011] [15:48:50] <jobytaffey>	That looks like what I need. Thanks.
| [Sunday 20 February 2011] [15:49:12] <mikko>	it doesn't make sense to schedule EV_WRITE event unless you know that you have something to write
| [Sunday 20 February 2011] [17:52:41] <lestrrat>	wassup?
| [Sunday 20 February 2011] [17:54:03] <sam`>	not much
| [Sunday 20 February 2011] [18:05:24] <lestrrat>	oh I get it, there's a build failure. http://build.zero.mq/job/ZeroMQPerl-master_ZeroMQ2-master_GCC/313/
| [Sunday 20 February 2011] [18:05:39] <lestrrat>	mikko: I didn't change anything in the last few days
| [Sunday 20 February 2011] [18:48:31] <mikko>	lestrrat: ok, will rerun to see
| [Sunday 20 February 2011] [18:49:18] <mikko>	succeeds
| [Sunday 20 February 2011] [18:49:27] <mikko>	probably an intermittent failure
| [Sunday 20 February 2011] [21:54:48] <JStoker>	Hi. Is there any debian packages for zeromq? :)
| [Sunday 20 February 2011] [21:55:04] <sam`>	JStoker: yes, i think there's a 2.0.10 package
| [Sunday 20 February 2011] [21:55:07] <sam`>	(at least in sid)
| [Sunday 20 February 2011] [21:56:03] <JStoker>	Aah. Thanks, I'll try to work out a way of coaxing that into my squeeze install. :)
| [Sunday 20 February 2011] [21:56:31] <sam`>	JStoker: http://packages.debian.org/libzmq
| [Sunday 20 February 2011] [21:56:57] <sam`>	keep in mind though that 2.1.x is probably a better choice, it fixes a lot of things
| [Sunday 20 February 2011] [21:57:51] <JStoker>	Ah. Hm.
| [Sunday 20 February 2011] [21:58:39] <JStoker>	The debian machine works fine with compiling, I guess. The ubuntu one on the other hand seems to have a bit of a dependency failure, so isn't able to actually compile it itself.
| [Sunday 20 February 2011] [21:58:48] <sam`>	ah?
| [Sunday 20 February 2011] [21:59:11] <sam`>	libzmq is rather easy on the dependencies AFAIR
| [Sunday 20 February 2011] [21:59:17] <sam`>	what problem are you facing?
| [Sunday 20 February 2011] [21:59:20] <JStoker>	Requires uuid-dev, but "libuuid1 (= 2.17.2-0ubuntu1) but 2.17.2-0ubuntu1.10.04.2 is to be installed"
| [Sunday 20 February 2011] [21:59:53] <sam`>	install the uuid-dev version you can, and build zeromq yourself
| [Sunday 20 February 2011] [21:59:58] <sam`>	you should be fine
| [Sunday 20 February 2011] [22:00:15] <JStoker>	I just tried `apt-get install uuid-dev`, didn't specify a version :/
| [Sunday 20 February 2011] [22:01:44] <sam`>	try with aptitude
| [Sunday 20 February 2011] [22:01:53] <sam`>	it's usually smarter when resolving dependencies
| [Sunday 20 February 2011] [22:02:15] <JStoker>	I've just forced it to a different version, which has seemed to help... (it's installing, at least)
| [Sunday 20 February 2011] [22:13:29] <seb`>	JStoker: it should be fine
| [Sunday 20 February 2011] [22:14:58] <seb`>	JStoker: for ubuntu you should use this ppa: https://launchpad.net/~chris-lea/+archive/zeromq
| [Sunday 20 February 2011] [22:15:08] <seb`>	but it's only 2.0.10:-(
| [Sunday 20 February 2011] [22:17:14] <JStoker>	That's the ub... oh. I just went and built my own package out of git://github.com/zeromq/zeromq2.git. Whoops.
| [Sunday 20 February 2011] [22:17:40] <JStoker>	seb`, Question. Are 2.0.10 and 2.1.x compatable?
| [Sunday 20 February 2011] [22:18:37] <JStoker>	That does report itself as 2.1.1 though, so no issues. :)
| [Sunday 20 February 2011] [22:19:34] <seb`>	JStoker: It's compatible yes
| [Sunday 20 February 2011] [22:19:42] <seb`>	at least my code works on both
| [Sunday 20 February 2011] [22:20:03] <seb`>	but 2.1 is the way to go IMHO
| [Sunday 20 February 2011] [22:20:20] <seb`>	I'm still using 2.0.10 in production right now
| [Sunday 20 February 2011] [22:20:30] <JStoker>	oh well. Got the difficult system running with 2.1 anyway, so might as well continue with it on the debian one.
| [Monday 21 February 2011] [05:23:28] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r5c09311 10/ (src/pgm_socket.cpp src/pgm_socket.hpp): 
| [Monday 21 February 2011] [05:23:28] <CIA-21>	zeromq2: Computation of buffer size for PGM fixed.
| [Monday 21 February 2011] [05:23:28] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/i9Ptxs
| [Monday 21 February 2011] [05:23:54] <pieter_hintjens>	sustrik, I'm seeing zmq_term just exit the process
| [Monday 21 February 2011] [05:24:00] <pieter_hintjens>	does that sound normal?
| [Monday 21 February 2011] [05:24:21] <sustrik>	no
| [Monday 21 February 2011] [05:24:35] <sustrik>	do you have a test case
| [Monday 21 February 2011] [05:24:36] <sustrik>	?
| [Monday 21 February 2011] [05:24:38] <pieter_hintjens>	trying to make some of the Guide examples work with 2.1...
| [Monday 21 February 2011] [05:24:46] <pieter_hintjens>	yes, I have a test case... I'll email it to you
| [Monday 21 February 2011] [05:24:49] <sustrik>	thanks
| [Monday 21 February 2011] [05:25:55] <pieter_hintjens>	https://gist.github.com/836902
| [Monday 21 February 2011] [05:26:10] <pieter_hintjens>	also some problems transferring messages but I'll break that down
| [Monday 21 February 2011] [05:27:28] <sustrik>	ok
| [Monday 21 February 2011] [05:28:13] <mikko>	good morning
| [Monday 21 February 2011] [05:28:30] <sustrik>	morning
| [Monday 21 February 2011] [05:29:33] <pieter_hintjens>	hi mikko :-)
| [Monday 21 February 2011] [05:34:58] <pieter_hintjens>	sustrik: you didn't add my log on unroutable messages...
| [Monday 21 February 2011] [05:35:10] <sustrik>	nope
| [Monday 21 February 2011] [05:35:23] <pieter_hintjens>	any particular reason?
| [Monday 21 February 2011] [05:35:31] <sustrik>	it's a standard behaviour
| [Monday 21 February 2011] [05:35:38] <sustrik>	nothing special to log
| [Monday 21 February 2011] [05:35:47] <sustrik>	it's like dropping an IP packet
| [Monday 21 February 2011] [05:35:58] <pieter_hintjens>	i violently disagree
| [Monday 21 February 2011] [05:36:09] <pieter_hintjens>	debugging dropped messages is one of the major pains
| [Monday 21 February 2011] [05:36:54] <pieter_hintjens>	xrep dropping a malformed envelope is not like dropping an IP packet
| [Monday 21 February 2011] [05:37:14] <pieter_hintjens>	it's a sign of application error, and that information is particularly valuable to the developer
| [Monday 21 February 2011] [05:37:15] <sustrik>	yes, we should log malformed envelope
| [Monday 21 February 2011] [05:37:25] <pieter_hintjens>	that is what I had done...
| [Monday 21 February 2011] [05:37:35] <sustrik>	not dropping a well-formed envelope though
| [Monday 21 February 2011] [05:37:43] <pieter_hintjens>	malformed = no such address, sorry
| [Monday 21 February 2011] [05:37:44] <sustrik>	well-formed message i mean
| [Monday 21 February 2011] [05:37:52] <sustrik>	it's on critical path
| [Monday 21 February 2011] [05:38:03] <pieter_hintjens>	errors are exceptional;
| [Monday 21 February 2011] [05:38:04] <sustrik>	if you need it for debugging
| [Monday 21 February 2011] [05:38:17] <sustrik>	we can add some special debug functionality
| [Monday 21 February 2011] [05:38:17] <pieter_hintjens>	when you start to use xrep this is a major pain
| [Monday 21 February 2011] [05:38:29] <pieter_hintjens>	errors -> silence
| [Monday 21 February 2011] [05:38:38] <sustrik>	yes
| [Monday 21 February 2011] [05:38:40] <pieter_hintjens>	the only way I know to debug is to hack 0MQ to print something
| [Monday 21 February 2011] [05:38:46] <pieter_hintjens>	it's a *major* annoyance
| [Monday 21 February 2011] [05:38:49] <sustrik>	it means that the original requester is no longer available
| [Monday 21 February 2011] [05:38:52] <pieter_hintjens>	no
| [Monday 21 February 2011] [05:38:53] <sustrik>	so the reply is dropped
| [Monday 21 February 2011] [05:38:57] <pieter_hintjens>	it means there's a bug in my app code
| [Monday 21 February 2011] [05:39:01] <sustrik>	?
| [Monday 21 February 2011] [05:39:11] <pieter_hintjens>	i assume you've never written code that uses xrep then
| [Monday 21 February 2011] [05:39:26] <sustrik>	i did
| [Monday 21 February 2011] [05:39:29] <sustrik>	queue device :)
| [Monday 21 February 2011] [05:39:40] <pieter_hintjens>	well, I've done a lot of work using xrep
| [Monday 21 February 2011] [05:39:43] <pieter_hintjens>	and it's tricky
| [Monday 21 February 2011] [05:40:01] <pieter_hintjens>	and the classic 80% error is a bad envelope (valid for 0MQ but where the routing information is wrongly placed)
| [Monday 21 February 2011] [05:40:10] <pieter_hintjens>	0MQ absolutely must report this
| [Monday 21 February 2011] [05:40:15] <pieter_hintjens>	ask on the list if you're not sure
| [Monday 21 February 2011] [05:40:25] <pieter_hintjens>	it's not a critical path
| [Monday 21 February 2011] [05:40:33] <pieter_hintjens>	there are not millions of malformed addresses per second
| [Monday 21 February 2011] [05:40:36] <pieter_hintjens>	no way
| [Monday 21 February 2011] [05:40:44] <sustrik>	how would you distinguish it from simply dropping the packet because the destination is simply dead atm
| [Monday 21 February 2011] [05:40:47] <mikko>	pieter_hintjens: this is pretty classic as well http://bit.ly/g6RXaS?r=td
| [Monday 21 February 2011] [05:40:51] <pieter_hintjens>	same thing, sustrik
| [Monday 21 February 2011] [05:40:52] <mikko>	might want to feature in the guide
| [Monday 21 February 2011] [05:40:57] <pieter_hintjens>	not critical path, that's the first thing
| [Monday 21 February 2011] [05:41:06] <pieter_hintjens>	this is an exception and can be logged
| [Monday 21 February 2011] [05:41:28] <pieter_hintjens>	mikko: yes, ipc has some gotchas
| [Monday 21 February 2011] [05:41:41] <pieter_hintjens>	i'm trying to debug a case now and the 'silence when dropping messages' just cost me an hour
| [Monday 21 February 2011] [05:41:45] <pieter_hintjens>	bleh
| [Monday 21 February 2011] [05:42:08] <sustrik>	let's add some debugging code then
| [Monday 21 February 2011] [05:42:16] <pieter_hintjens>	sustrik: why? you have a mechanism that's ideal
| [Monday 21 February 2011] [05:42:29] <pieter_hintjens>	as a user I'm asking formally that syslog be used to report bad addresses
| [Monday 21 February 2011] [05:42:37] <sustrik>	the problem is that a node being offline is a pretty common occurence
| [Monday 21 February 2011] [05:42:40] <pieter_hintjens>	it will also help debug topology errors
| [Monday 21 February 2011] [05:42:42] <sustrik>	at least on wan
| [Monday 21 February 2011] [05:42:48] <pieter_hintjens>	'pretty common' is not a critical path
| [Monday 21 February 2011] [05:42:53] <pieter_hintjens>	wan is not our environment today
| [Monday 21 February 2011] [05:43:00] <pieter_hintjens>	these are bogus arguments afaics, sorry
| [Monday 21 February 2011] [05:43:03] <sustrik>	i'm planning for the future
| [Monday 21 February 2011] [05:43:15] <pieter_hintjens>	you're making it unnecessarily difficult for the present
| [Monday 21 February 2011] [05:43:30] <pieter_hintjens>	at which point the future becomes less certain at all
| [Monday 21 February 2011] [05:43:46] <pieter_hintjens>	if people cannot easily debug routing issues and topology issues they will lose confidence in 0MQ
| [Monday 21 February 2011] [05:44:11] <pieter_hintjens>	if you actually hit this *theoretical* issue of millions of WAN disconnections
| [Monday 21 February 2011] [05:44:22] <pieter_hintjens>	*then* you can solve that problem in the correct fashion
| [Monday 21 February 2011] [05:44:36] <pieter_hintjens>	refusing to log this information today is not a solution
| [Monday 21 February 2011] [05:44:48] <pieter_hintjens>	you would probably want to reduce the logging level on specific sockets
| [Monday 21 February 2011] [05:44:55] <pieter_hintjens>	in 3 years' time
| [Monday 21 February 2011] [05:44:56] <sustrik>	ok, the real problem is that once i add that kind of thing, people start using it to drive their business logic
| [Monday 21 February 2011] [05:45:02] <pieter_hintjens>	it's syslog
| [Monday 21 February 2011] [05:45:11] <pieter_hintjens>	syslog cannot be used for presence
| [Monday 21 February 2011] [05:45:16] <pieter_hintjens>	we know this, it's not a risk
| [Monday 21 February 2011] [05:45:22] <sustrik>	which means the applications would become not scalable outside of a lan
| [Monday 21 February 2011] [05:45:30] <pieter_hintjens>	?
| [Monday 21 February 2011] [05:45:39] <pieter_hintjens>	sorry, let's kill inproc then
| [Monday 21 February 2011] [05:45:44] <pieter_hintjens>	and multicast
| [Monday 21 February 2011] [05:45:44] <sustrik>	?
| [Monday 21 February 2011] [05:45:50] <pieter_hintjens>	cause people might depend on that
| [Monday 21 February 2011] [05:45:57] <pieter_hintjens>	and not be scalable outside the lan
| [Monday 21 February 2011] [05:46:00] <pieter_hintjens>	seriously?
| [Monday 21 February 2011] [05:46:08] <sustrik>	nope, you can scale inproc and multicast by replacing them with tcp
| [Monday 21 February 2011] [05:46:16] <pieter_hintjens>	sigh
| [Monday 21 February 2011] [05:46:26] <sustrik>	when you start using logs in your business logic
| [Monday 21 February 2011] [05:46:29] <pieter_hintjens>	how?
| [Monday 21 February 2011] [05:46:30] <sustrik>	you are screwed
| [Monday 21 February 2011] [05:46:38] <pieter_hintjens>	how do you use logs in your business logic?
| [Monday 21 February 2011] [05:46:38] <sustrik>	as the logs are local
| [Monday 21 February 2011] [05:46:57] <pieter_hintjens>	syslog is async
| [Monday 21 February 2011] [05:46:58] <sustrik>	1. send x to y
| [Monday 21 February 2011] [05:47:08] <pieter_hintjens>	you cannot rely on it for business logic
| [Monday 21 February 2011] [05:47:14] <pieter_hintjens>	we already discussed this on the list
| [Monday 21 February 2011] [05:47:16] <sustrik>	2. if i get "non routable" error
| [Monday 21 February 2011] [05:47:23] <sustrik>	3. send it somewhere else
| [Monday 21 February 2011] [05:47:35] <sustrik>	yes, i've discussed it many times
| [Monday 21 February 2011] [05:47:38] <pieter_hintjens>	so people can abuse a tool
| [Monday 21 February 2011] [05:47:45] <pieter_hintjens>	that does not mean you throw away the tool
| [Monday 21 February 2011] [05:47:47] <sustrik>	and each time people asked for this kind of thing
| [Monday 21 February 2011] [05:47:49] <pieter_hintjens>	you educate them
| [Monday 21 February 2011] [05:47:57] <sustrik>	i discussed it with them
| [Monday 21 February 2011] [05:48:13] <pieter_hintjens>	education, not censorship martin
| [Monday 21 February 2011] [05:48:17] <sustrik>	and after some conversation it become obvious thay want to drive their business logic
| [Monday 21 February 2011] [05:48:21] <pieter_hintjens>	you do not actually know what people need
| [Monday 21 February 2011] [05:48:26] <sustrik>	none a single person wanting just logging
| [Monday 21 February 2011] [05:48:31] <pieter_hintjens>	i want just logging
| [Monday 21 February 2011] [05:48:38] <sustrik>	it's 100% misuse rate
| [Monday 21 February 2011] [05:48:44] <sustrik>	99% then
| [Monday 21 February 2011] [05:49:24] <sustrik>	ok, an idea
| [Monday 21 February 2011] [05:49:47] <sustrik>	what about having a "debug" build which would log this kind of errors
| [Monday 21 February 2011] [05:49:51] <pieter_hintjens>	and if people want to use routing failures in their app, why not?
| [Monday 21 February 2011] [05:49:54] <sustrik>	and release build that won't
| [Monday 21 February 2011] [05:49:55] <sustrik>	?
| [Monday 21 February 2011] [05:49:57] <pieter_hintjens>	hang on
| [Monday 21 February 2011] [05:50:03] <sustrik>	it doesn't scale
| [Monday 21 February 2011] [05:50:07] <pieter_hintjens>	I'm challenging your assertion that using this information won't scale
| [Monday 21 February 2011] [05:50:19] <pieter_hintjens>	if I make a broker that uses this
| [Monday 21 February 2011] [05:50:22] <pieter_hintjens>	the broker will scale fine
| [Monday 21 February 2011] [05:50:58] <pieter_hintjens>	it's like getting disconnection alerts
| [Monday 21 February 2011] [05:51:04] <sustrik>	wait a sec
| [Monday 21 February 2011] [05:51:08] <sustrik>	let me explain
| [Monday 21 February 2011] [05:51:22] <sustrik>	say you have a server (XREP)
| [Monday 21 February 2011] [05:51:27] <sustrik>	and clients (XREQ)
| [Monday 21 February 2011] [05:52:07] <sustrik>	the server uses sys://log to find out whether clients are disconnected
| [Monday 21 February 2011] [05:52:20] <pieter_hintjens>	yes?
| [Monday 21 February 2011] [05:52:37] <sustrik>	when it finds out, it will do something relevant, like allert the operator or somesuch
| [Monday 21 February 2011] [05:52:51] <pieter_hintjens>	you mean ... log a message somewhere else?
| [Monday 21 February 2011] [05:53:05] <pieter_hintjens>	on the operator console, for example...
| [Monday 21 February 2011] [05:53:07] <sustrik>	i mean, initiate some other business process
| [Monday 21 February 2011] [05:53:12] <sustrik>	like sending the message by DHL
| [Monday 21 February 2011] [05:53:23] <pieter_hintjens>	? this is your example?
| [Monday 21 February 2011] [05:53:38] <pieter_hintjens>	business logic would be
| [Monday 21 February 2011] [05:53:43] <sustrik>	or placing a message on dlq
| [Monday 21 February 2011] [05:53:47] <pieter_hintjens>	- discover principal connection is dead
| [Monday 21 February 2011] [05:53:52] <pieter_hintjens>	- switch over to backup connection
| [Monday 21 February 2011] [05:53:53] <sustrik>	or running a special repair script
| [Monday 21 February 2011] [05:54:12] <sustrik>	any business logic will do
| [Monday 21 February 2011] [05:54:12] <sustrik>	now
| [Monday 21 February 2011] [05:54:20] <sustrik>	the company grows
| [Monday 21 February 2011] [05:54:29] <sustrik>	and have several offices all over the world
| [Monday 21 February 2011] [05:54:36] <sustrik>	it wants to federate
| [Monday 21 February 2011] [05:54:46] <sustrik>	so they place a queue device at each location
| [Monday 21 February 2011] [05:55:06] <pieter_hintjens>	sustrik, you have device obsession
| [Monday 21 February 2011] [05:55:12] <sustrik>	now imagine an client at point A invoking a service at point B
| [Monday 21 February 2011] [05:55:27] <pieter_hintjens>	people do not, ime, use the standard devices except as a stepping stone while they're learning 0MQ
| [Monday 21 February 2011] [05:55:36] <sustrik>	the connection to A may be perfectly ok, but the client may be dead
| [Monday 21 February 2011] [05:55:36] <pieter_hintjens>	they build their own devices, = brokers
| [Monday 21 February 2011] [05:55:47] <sustrik>	the same thing
| [Monday 21 February 2011] [05:56:10] <sustrik>	the problem is that the "cannot route" error works in hop-by-hop fashion
| [Monday 21 February 2011] [05:56:13] <pieter_hintjens>	i really can't swallow your chain of logic
| [Monday 21 February 2011] [05:56:28] <pieter_hintjens>	it is based on the assumption that all 0MQ applications today will one day scale to the WAN
| [Monday 21 February 2011] [05:56:34] <sustrik>	so the error you get is 'cannot route to next hop'
| [Monday 21 February 2011] [05:56:40] <sustrik>	instead of 'message is unroutable'
| [Monday 21 February 2011] [05:56:42] <pieter_hintjens>	which is true for about 0.001% of cases, maybe
| [Monday 21 February 2011] [05:57:04] <pieter_hintjens>	99.999% of today's apps (and those written for the next two years) will do what they do, and basta
| [Monday 21 February 2011] [05:57:10] <pieter_hintjens>	that is our constituency
| [Monday 21 February 2011] [05:57:32] <sustrik>	if IP folks would think that way Internet would interconnect the original 3 machines still :)
| [Monday 21 February 2011] [05:57:36] <pieter_hintjens>	trying to stop people writing those apps any way they can is counter-productive
| [Monday 21 February 2011] [05:57:43] <pieter_hintjens>	i'm not a luddite, please
| [Monday 21 February 2011] [05:58:01] <pieter_hintjens>	and you are NOT reinventing the Internet, don't imagine that
| [Monday 21 February 2011] [05:58:18] <pieter_hintjens>	I'm asking for basic tools to make today's problem slightly easier to solve
| [Monday 21 February 2011] [05:58:21] <sustrik>	nope, i'm building a new layer for it
| [Monday 21 February 2011] [05:58:29] <sustrik>	ack
| [Monday 21 February 2011] [05:58:35] <pieter_hintjens>	you ignore the requests of your users at your direct peril
| [Monday 21 February 2011] [05:58:54] <sustrik>	i know
| [Monday 21 February 2011] [05:58:56] <pieter_hintjens>	people will not give much patience to a nerd who tells them "I know your problems better than you do"
| [Monday 21 February 2011] [05:59:04] <sustrik>	there are several options how to solve the problem
| [Monday 21 February 2011] [05:59:10] <pieter_hintjens>	you need people to bring their problems and expertise
| [Monday 21 February 2011] [05:59:16] <pieter_hintjens>	to experiment, even if it means blowing things up
| [Monday 21 February 2011] [05:59:28] <pieter_hintjens>	without that, what you make will be dead and unused
| [Monday 21 February 2011] [05:59:38] <pieter_hintjens>	just a collection of weird names and bizarre theories
| [Monday 21 February 2011] [05:59:48] <pieter_hintjens>	that's 90% of the software universe
| [Monday 21 February 2011] [05:59:59] <sustrik>	i would suggest you fork the stable
| [Monday 21 February 2011] [06:00:02] <pieter_hintjens>	not yet
| [Monday 21 February 2011] [06:00:06] <sustrik>	and apply the patch there
| [Monday 21 February 2011] [06:00:08] <pieter_hintjens>	i cannot run my basic examples on 2.1
| [Monday 21 February 2011] [06:00:17] <pieter_hintjens>	and I'm not going to fork 0MQ... nope
| [Monday 21 February 2011] [06:00:22] <sustrik>	a regrestion?
| [Monday 21 February 2011] [06:00:27] <sustrik>	what happened?
| [Monday 21 February 2011] [06:00:35] <pieter_hintjens>	stabilization = current version + patches from you
| [Monday 21 February 2011] [06:00:37] <pieter_hintjens>	no more or less
| [Monday 21 February 2011] [06:01:24] <pieter_hintjens>	I'd like to request some debugging framework (syslog is frankly quite heavy) that tells me when I make the stupid and repeated error of misconstructing a routing envelope
| [Monday 21 February 2011] [06:01:25] <sustrik>	well, the problem is we have different goals
| [Monday 21 February 2011] [06:01:40] <pieter_hintjens>	we have different timeframes, is all
| [Monday 21 February 2011] [06:01:51] <pieter_hintjens>	i'm actually using 0MQ and finding difficulties with it
| [Monday 21 February 2011] [06:01:53] <sustrik>	how can we possibly synchronise?
| [Monday 21 February 2011] [06:02:09] <pieter_hintjens>	accept the problems your users present you as real
| [Monday 21 February 2011] [06:02:19] <sustrik>	sure they are
| [Monday 21 February 2011] [06:02:24] <pieter_hintjens>	if they take the effort to express them, that means there is real pain involved
| [Monday 21 February 2011] [06:02:30] <sustrik>	i proposed a solution: let's make a debug version of 0mq
| [Monday 21 February 2011] [06:02:37] <pieter_hintjens>	yes, that might work but
| [Monday 21 February 2011] [06:02:44] <pieter_hintjens>	we know why it won't, in practice
| [Monday 21 February 2011] [06:02:46] <sustrik>	#ifdef ZMQ_DEBUG
| [Monday 21 February 2011] [06:02:50] <sustrik>	   log (...)'
| [Monday 21 February 2011] [06:02:51] <sustrik>	#endif
| [Monday 21 February 2011] [06:02:53] <sustrik>	easy
| [Monday 21 February 2011] [06:03:13] <pieter_hintjens>	Except that many people provide 0MQ to their own customers
| [Monday 21 February 2011] [06:03:32] <pieter_hintjens>	Now they face the lovely choice of (a) debug version or (b) silent on failure version
| [Monday 21 February 2011] [06:03:41] 	 * pieter_hintjens needs coffee
| [Monday 21 February 2011] [06:05:30] <pieter_hintjens>	ok, I have a proposal
| [Monday 21 February 2011] [06:05:59] <pieter_hintjens>	i don't actually like the syslog solution at all, for developers
| [Monday 21 February 2011] [06:06:14] <pieter_hintjens>	it's a pain to use and all it really does is collect output you can print to a log file
| [Monday 21 February 2011] [06:06:36] <pieter_hintjens>	if you try to *use* that information in any way you hit Sustrik's Barrier of "it will not scale to the WAN"
| [Monday 21 February 2011] [06:06:38] <pieter_hintjens>	ack?
| [Monday 21 February 2011] [06:07:07] <pieter_hintjens>	it can work internally as a log collector
| [Monday 21 February 2011] [06:07:43] <pieter_hintjens>	so leave it undocumented, and add a method zmq_verbose() that enables printing of syslog messages
| [Monday 21 February 2011] [06:07:56] <pieter_hintjens>	or zmq_debug() or whatever
| [Monday 21 February 2011] [06:08:08] <sustrik>	not bad
| [Monday 21 February 2011] [06:08:24] <sustrik>	same as ZMQ_DEBUG but configurable at runtime
| [Monday 21 February 2011] [06:08:26] <pieter_hintjens>	then when things go weird we can tell users, "run again with the --verbose switch and send me the screen dump"
| [Monday 21 February 2011] [06:08:33] <pieter_hintjens>	yes, has to be runtime configurable
| [Monday 21 February 2011] [06:08:34] <sustrik>	ack
| [Monday 21 February 2011] [06:08:42] <sustrik>	that's a good solution
| [Monday 21 February 2011] [06:08:44] <pieter_hintjens>	IMO there is no performance hit in doing this for all exceptional conditions
| [Monday 21 February 2011] [06:08:54] <pieter_hintjens>	if we do see such a performance issue, we can solve it
| [Monday 21 February 2011] [06:09:33] <pieter_hintjens>	if the syslog collector is embedded in zmq, it can't be abused and it requires no extra work except that one call
| [Monday 21 February 2011] [06:14:06] <Guthur>	is there an optimum zmq_size size?
| [Monday 21 February 2011] [06:14:42] <pieter_hintjens>	Guthur: to achieve what?
| [Monday 21 February 2011] [06:14:55] <pieter_hintjens>	high throughput or low latency?
| [Monday 21 February 2011] [06:15:18] <Guthur>	I was thinking of adding a stream interface to clrzmq2
| [Monday 21 February 2011] [06:15:37] <pieter_hintjens>	what is a stream interface?
| [Monday 21 February 2011] [06:15:37] <Guthur>	and so i was think it would send that as a series of msgs
| [Monday 21 February 2011] [06:16:03] <Guthur>	just passing in a stream to send
| [Monday 21 February 2011] [06:16:07] <pieter_hintjens>	no frames?
| [Monday 21 February 2011] [06:16:09] <Guthur>	and then it would split it up into chunks and send
| [Monday 21 February 2011] [06:16:51] <pieter_hintjens>	if it was video, for example
| [Monday 21 February 2011] [06:17:12] <pieter_hintjens>	you'd want to send one frame per message to get best latency
| [Monday 21 February 2011] [06:17:12] <Guthur>	I haven't thoroughly thought it through it yet, do you recommend framing 
| [Monday 21 February 2011] [06:17:40] <pieter_hintjens>	if it was file transfer, for example, you'd use large messages to maximize throughput
| [Monday 21 February 2011] [06:17:42] <Guthur>	early idea genesis stage at the moment, hehe
| [Monday 21 February 2011] [06:18:02] <pieter_hintjens>	then just choose a random value and optimize later when you actually know what the target is :-)
| [Monday 21 February 2011] [06:18:22] <pieter_hintjens>	4096 bytes per message, there, I've decided for you
| [Monday 21 February 2011] [06:18:25] <Guthur>	oh, ok
| [Monday 21 February 2011] [06:18:42] <Guthur>	hehe, thanks
| [Monday 21 February 2011] [06:19:28] <mikko>	Guthur: do you have tests you want to have run at some point?
| [Monday 21 February 2011] [06:19:46] <Guthur>	mikko: not yet, I hope to sometime
| [Monday 21 February 2011] [06:19:54] <Guthur>	a lot on my plate at the moment
| [Monday 21 February 2011] [06:20:08] <Guthur>	really behind on my MSc thesis, unfortunately
| [Monday 21 February 2011] [06:20:18] <pieter_hintjens>	"life is a buffet of interesting problems"
| [Monday 21 February 2011] [06:24:12] <mikko>	"nothing is more expensive than hiring an amateur"
| [Monday 21 February 2011] [06:24:23] <mikko>	saw that on twitter today
| [Monday 21 February 2011] [06:24:46] <pieter_hintjens>	"If you think a professional is expensive, wait till you see the cost of hiring an amateur" was the version I saw
| [Monday 21 February 2011] [06:24:52] <pieter_hintjens>	I think this would make a good motto for iMatix
| [Monday 21 February 2011] [06:25:08] <pieter_hintjens>	I prefer your short version...
| [Monday 21 February 2011] [06:26:19] <mikko>	http://twitter.com/cgbystrom/statuses/39607943171284992
| [Monday 21 February 2011] [06:26:24] <mikko>	there it is
| [Monday 21 February 2011] [06:26:59] <pieter_hintjens>	I need a Latin version
| [Monday 21 February 2011] [06:27:57] <Guthur>	'If you think training a Graduate is expensive, try an Old Dog'
| [Monday 21 February 2011] [06:28:02] <Guthur>	there's mine, hehe
| [Monday 21 February 2011] [06:29:15] <mikko>	"If you think training a graduate is expensive, you are probably right but it might pay off later. Maybe"
| [Monday 21 February 2011] [06:31:25] <pieter_hintjens>	I'd like to change the text "Explore the Community" on the main welcome page
| [Monday 21 February 2011] [06:31:28] <pieter_hintjens>	it is too bland
| [Monday 21 February 2011] [06:31:59] <pieter_hintjens>	It should be verb article noun
| [Monday 21 February 2011] [06:33:51] <pieter_hintjens>	Escape the Box
| [Monday 21 February 2011] [06:34:34] <pieter_hintjens>	that'll do...
| [Monday 21 February 2011] [06:34:44] <mikko>	reminds too much of thinking out of the box
| [Monday 21 February 2011] [06:34:56] <pieter_hintjens>	that was the intention
| [Monday 21 February 2011] [06:35:04] <mikko>	oh..
| [Monday 21 February 2011] [07:17:42] <pieter_hintjens>	sustrik: how can I tell if a specific commit got into the 2.0.10 release?
| [Monday 21 February 2011] [07:17:49] <pieter_hintjens>	e2167cecaefec6557c7a5712fb75e51487ff69a6 is the one I'm interested in
| [Monday 21 February 2011] [07:18:01] 	 * pieter_hintjens needs to learn more git...
| [Monday 21 February 2011] [07:19:34] <pieter_hintjens>	ok, it's not there... np
| [Monday 21 February 2011] [07:46:38] <pieter_hintjens>	sustrik: I've found another bug in master
| [Monday 21 February 2011] [07:46:54] <pieter_hintjens>	am porting all the Guide examples to 2.1, some of them do quite strange stuff
| [Monday 21 February 2011] [07:47:14] <pieter_hintjens>	Have logged this https://github.com/zeromq/zeromq2/issues/167 (and #168 was the one I found earlier)
| [Monday 21 February 2011] [07:50:15] <pieter_hintjens>	lunch, brb
| [Monday 21 February 2011] [07:55:05] <sustrik>	pieter_hintjens: ok
| [Monday 21 February 2011] [07:55:16] <sustrik>	btw "fathom the basics" is not good
| [Monday 21 February 2011] [07:55:23] <sustrik>	it's a rarely used word
| [Monday 21 February 2011] [07:55:34] <sustrik>	and most non-native speakers won't understand it
| [Monday 21 February 2011] [07:56:35] <sustrik>	same with "grab"
| [Monday 21 February 2011] [07:57:55] <sustrik>	also, nobody will understand "escape the box" leads to the community page
| [Monday 21 February 2011] [09:32:32] <pieter_hintjens>	sustrik: sure, but what does "the community" mean either?
| [Monday 21 February 2011] [09:32:44] <sustrik>	dunno :)
| [Monday 21 February 2011] [09:32:59] <pieter_hintjens>	exactly, it only makes sense when you already know what it is...
| [Monday 21 February 2011] [09:33:05] <sustrik>	development?
| [Monday 21 February 2011] [09:33:17] <pieter_hintjens>	... something that says, "Get a lot more stuff here..."
| [Monday 21 February 2011] [09:33:22] <sustrik>	yes
| [Monday 21 February 2011] [09:33:24] <pieter_hintjens>	Get the Addons
| [Monday 21 February 2011] [09:33:38] <pieter_hintjens>	ugh
| [Monday 21 February 2011] [09:33:40] <mikko>	addon sounds proprietary
| [Monday 21 February 2011] [09:33:42] <sustrik>	or simple "more"
| [Monday 21 February 2011] [09:34:18] <pieter_hintjens>	from a design basis it's Verb article Noun
| [Monday 21 February 2011] [09:34:54] <pieter_hintjens>	minimalism is quite difficult... :)
| [Monday 21 February 2011] [09:34:59] <sustrik>	true
| [Monday 21 February 2011] [09:35:14] <sustrik>	proceed to more
| [Monday 21 February 2011] [09:35:23] <sustrik>	check more stuff
| [Monday 21 February 2011] [09:35:39] <pieter_hintjens>	Enter the Deep End
| [Monday 21 February 2011] [09:35:56] <pieter_hintjens>	Dive into the Boiling Tarpits of Git
| [Monday 21 February 2011] [09:36:24] <sustrik>	something like that
| [Monday 21 February 2011] [09:36:29] <pieter_hintjens>	anyhow it doesn't really matter if people understand what each option means...
| [Monday 21 February 2011] [09:36:35] <pieter_hintjens>	there are 5 options, clickety-click...
| [Monday 21 February 2011] [09:36:46] <pieter_hintjens>	all we want is their curiosity
| [Monday 21 February 2011] [09:37:03] <sustrik>	we can try to leave it as it
| [Monday 21 February 2011] [09:37:08] <pieter_hintjens>	no-one's going to hesitate thinking, "Oh, I don't fully understand that, therefore I can't click"
| [Monday 21 February 2011] [09:37:14] <sustrik>	what i find really wrong is "fathom"
| [Monday 21 February 2011] [09:37:17] <pieter_hintjens>	sure
| [Monday 21 February 2011] [09:37:36] <pieter_hintjens>	I wanted a little more spice
| [Monday 21 February 2011] [09:37:48] <pieter_hintjens>	Learn the Basics
| [Monday 21 February 2011] [09:37:54] <pieter_hintjens>	but Learn sounds like school
| [Monday 21 February 2011] [09:38:05] <pieter_hintjens>	and "Read the Manual" just sounds like work
| [Monday 21 February 2011] [09:38:35] <sustrik>	read the manual is neutral imo
| [Monday 21 February 2011] [09:38:52] <pieter_hintjens>	hmm, basics vs. advancedics
| [Monday 21 February 2011] [09:38:57] <sustrik>	what about community -> "dive into details"
| [Monday 21 February 2011] [09:39:03] <pieter_hintjens>	I like it
| [Monday 21 February 2011] [09:39:09] <pieter_hintjens>	that contrasts with Basics nicely
| [Monday 21 February 2011] [09:40:16] <pieter_hintjens>	aight, we have a winner, thanks Martin :-)
| [Monday 21 February 2011] [09:44:46] <jobytaffey>	I'm working on a server which multiplexes many TCP sockets into 0MQ. I want a worker app to be able to talk bi-directionally to any TCP socket. What's an efficient way to approach this? One 0MQ socket per TCP socket? or perhaps a single 0MQ socket per direction, aggregating all TCP messages (filtered with ZMQ_SUBSCRIBE)?
| [Monday 21 February 2011] [09:45:24] <pieter_hintjens>	jobytaffey: have you read the Guide?
| [Monday 21 February 2011] [09:46:06] <jobytaffey>	Bits of. I guess I'll go and read some more then...
| [Monday 21 February 2011] [09:46:42] <pieter_hintjens>	this is not actually covered but it will help you understand how to make the 0MQ part
| [Monday 21 February 2011] [09:47:02] <pieter_hintjens>	the answer depends a lot on what kind of work you are doing with the TCP sockets
| [Monday 21 February 2011] [09:47:32] <pieter_hintjens>	i.e. how you map the TCP side to one or more 0MQ patterns (pubsub, req-rep, pipeline)
| [Monday 21 February 2011] [09:49:12] <jobytaffey>	I've got fixed sized packets going in both directions over TCP. I have an online wireless sensor network where I want to be able to register for telemetry feeds from the devices. But, given millions of devices, I don't think I can afford a 0MQ socket per device.
| [Monday 21 February 2011] [09:50:25] <pieter_hintjens>	jobytaffey: please read the Guide, at least Ch1 in detail, and come back when you can map your problem to 0MQ patterns
| [Monday 21 February 2011] [09:50:34] <pieter_hintjens>	otherwise you lack the tools to design this properly
| [Monday 21 February 2011] [09:51:12] <pieter_hintjens>	it sounds like pubsub except you say it's bidirectional
| [Monday 21 February 2011] [09:51:41] <jobytaffey>	I agree I'm trying to run before walking, thanks.
| [Monday 21 February 2011] [10:00:12] <fbarriga>	I don't speak english very good but after a while I could decipher the expresion "Dive into the Boiling Tarpits of Git" but "fathom" is quite weird
| [Monday 21 February 2011] [10:01:15] <fbarriga>	reading the guide is quite amusing but all the decoration make it a bit longer to finish.
| [Monday 21 February 2011] [10:02:20] <neale1>	fathom == a unit of depth (6 feet ~ 2m). The expression is used to indicate that you getting "deeper" into the subject matter.
| [Monday 21 February 2011] [10:03:01] <pieter_hintjens>	fbarriga: ah, but you did finish it ... :-)
| [Monday 21 February 2011] [10:03:30] <pieter_hintjens>	we had some arguments at the start, about whether or not to decorate the text
| [Monday 21 February 2011] [10:03:44] <pieter_hintjens>	some people complained about it, but most people enjoyed it, so that's the style I used
| [Monday 21 February 2011] [10:04:04] <fbarriga>	pieter_hintjens, nop, I was working on other stuff :(
| [Monday 21 February 2011] [10:04:32] <pieter_hintjens>	for those who prefer their text dry we have the man pages, I guess
| [Monday 21 February 2011] [10:06:43] <fbarriga>	is more 'artistic' the way you write the guide. I think that it sound more intellectual rather than technical.
| [Monday 21 February 2011] [10:13:19] <pieter_hintjens>	fbarriga: well, to be honest, this is how I write when no-one is telling me to conform
| [Monday 21 February 2011] [10:13:30] <pieter_hintjens>	s/telling/paying/
| [Monday 21 February 2011] [10:24:22] <fbarriga>	that's good
| [Monday 21 February 2011] [10:49:20] <cremes>	is this callstack from 0mq sending or receiving a message?  https://gist.github.com/837241
| [Monday 21 February 2011] [10:50:22] <neale1>	anyone had any experience using 0MQ with Spring?
| [Monday 21 February 2011] [10:54:30] <pieter_hintjens>	cremes: it looks like it's in the zmq_msg_init_size method
| [Monday 21 February 2011] [10:55:38] <pieter_hintjens>	neale1: not as far as I know of, there are some people talking about it but nothing concrete yet
| [Monday 21 February 2011] [10:56:39] <neale1>	Tks. I have a client trying to use it and having problems. (That's as about as detailed as they have described it unfortunately)
| [Monday 21 February 2011] [10:57:21] <cremes>	pieter_hintjens: right; but i'm wondering if this is 0mq in the act of sending or receiving a message because this isn't code i am calling directly
| [Monday 21 February 2011] [10:57:37] <cremes>	and i'm showing that i have a small memory leak here on occasion
| [Monday 21 February 2011] [10:58:30] <pieter_hintjens>	cremes: hmm, sustrik would know for sure but it looks like an input event, so receiving a message
| [Monday 21 February 2011] [10:58:48] <pieter_hintjens>	neale1: you obviously need more detail on what the problems are...
| [Monday 21 February 2011] [10:59:17] <cremes>	yeah, i'm thinking this is 0mq allocating its own msg_t for receiving the message envelope/header/routing information for an req/rep pair
| [Monday 21 February 2011] [11:03:20] <sustrik>	cremes: receiving
| [Monday 21 February 2011] [11:04:09] <cremes>	sustrik: any chance the lib is not calling close on the message envelope (which isn't passed to the user)?
| [Monday 21 February 2011] [11:04:09] <sustrik>	cremes: how do you know there's a memory leak?
| [Monday 21 February 2011] [11:04:31] <sustrik>	sure, there can be a bug
| [Monday 21 February 2011] [11:04:40] <sustrik>	can you be more specific about the leak?
| [Monday 21 February 2011] [11:04:44] <cremes>	on osx there is a program called 'leaks' that can read the heap and use a malloc flag to find leaks
| [Monday 21 February 2011] [11:04:51] <cremes>	yes
| [Monday 21 February 2011] [11:05:17] <sustrik>	ok, so it maps malloc to frees
| [Monday 21 February 2011] [11:05:22] <sustrik>	and once the program exits
| [Monday 21 February 2011] [11:05:26] <sustrik>	it'll print out the leaks
| [Monday 21 February 2011] [11:05:27] <cremes>	'leaks' is outputting that i am leaking 112 bytes periodically
| [Monday 21 February 2011] [11:05:28] <sustrik>	right?
| [Monday 21 February 2011] [11:05:47] <cremes>	nope, it analyses a live heap
| [Monday 21 February 2011] [11:06:08] <sustrik>	how can it possibly know the chunk is not referenced anymore?
| [Monday 21 February 2011] [11:07:26] <pieter_hintjens>	it's osx... apple... magic... :)
| [Monday 21 February 2011] [11:08:10] <cremes>	sustrik: login to my box with your account and run 'man leaks'; read the first paragraph
| [Monday 21 February 2011] [11:08:21] <sustrik>	let me see...
| [Monday 21 February 2011] [11:08:46] <cremes>	also, reload this gist to see the output from leaks for my program:  https://gist.github.com/837241
| [Monday 21 February 2011] [11:10:46] <cremes>	the receiving socket in this case is an xreq
| [Monday 21 February 2011] [11:11:37] <sustrik>	ok, it scans whole memory for the pointers
| [Monday 21 February 2011] [11:12:19] <cremes>	yes; if you keep reading, you'll see the note about MallocStackLogging for getting the stack where the leaked memory was allocated
| [Monday 21 February 2011] [11:12:33] <cremes>	s/stack/callstack/
| [Monday 21 February 2011] [11:13:01] <sustrik>	the stack i see in the output it
| [Monday 21 February 2011] [11:13:03] <sustrik>	is
| [Monday 21 February 2011] [11:13:10] <sustrik>	thread_start | _pthread_start | thread_routine | zmq::kqueue_t::loop() | zmq::zmq_engine_t::in_event()
| [Monday 21 February 2011] [11:13:26] <sustrik>	that's different from the one you've posted before
| [Monday 21 February 2011] [11:13:33] <sustrik>	is it truncated or what?
| [Monday 21 February 2011] [11:14:12] <cremes>	you need to scroll the gist to the right; for some reason it doesn't wrap this output
| [Monday 21 February 2011] [11:14:33] <sustrik>	ah
| [Monday 21 February 2011] [11:16:15] <sustrik>	well, there are 3 possibilities:
| [Monday 21 February 2011] [11:16:23] <sustrik>	1. bug in 0mq
| [Monday 21 February 2011] [11:16:31] <sustrik>	2. client program not closing the message
| [Monday 21 February 2011] [11:16:51] <sustrik>	3. the pointer is actually stored outside of process memory
| [Monday 21 February 2011] [11:17:46] <cremes>	i don't think it's 2 because i loop over all messages and call zmq_close() on each part when i'm done
| [Monday 21 February 2011] [11:17:57] <cremes>	there's no way for my logic to skip that step
| [Monday 21 February 2011] [11:18:12] <cremes>	though it's certainly possible my code is the cause
| [Monday 21 February 2011] [11:18:22] <sustrik>	ok
| [Monday 21 February 2011] [11:18:28] <sustrik>	then it's either 1 or 3
| [Monday 21 February 2011] [11:18:49] <sustrik>	3 happens when pointer to memory is actually held inside of socketpair buffer
| [Monday 21 February 2011] [11:18:57] <sustrik>	which resides in kernel space
| [Monday 21 February 2011] [11:19:13] <sustrik>	at least i would assume it does, even on osx
| [Monday 21 February 2011] [11:19:53] <cremes>	i am *only* seeing this on the one client program i have using an xreq socket
| [Monday 21 February 2011] [11:20:14] <cremes>	everything else is using req,rep,pub,sub and i don't see the leak
| [Monday 21 February 2011] [11:20:23] <cremes>	so i am wondering if this is specific to xreq
| [Monday 21 February 2011] [11:20:57] <sustrik>	ack
| [Monday 21 February 2011] [11:20:57] <cremes>	you can see from the 'context' hex that it contains my custom identity so i assume this is routing info
| [Monday 21 February 2011] [11:21:09] <cremes>	which xreq is supposed to cut off before passing the messages to me
| [Monday 21 February 2011] [11:21:39] <sustrik>	is it a head version?
| [Monday 21 February 2011] [11:21:56] <sustrik>	or 2.1.0 or 2.0.x?
| [Monday 21 February 2011] [11:22:07] <cremes>	hang on, let me get the git commit hash (oh, 2.1.0)
| [Monday 21 February 2011] [11:22:14] <sustrik>	ok
| [Monday 21 February 2011] [11:22:38] <cremes>	e94790006ea6f4c64c commit from feb 9
| [Monday 21 February 2011] [11:22:52] <cremes>	i'll update to latest & greatest
| [Monday 21 February 2011] [11:23:11] 	 * sustrik is checking the code
| [Monday 21 February 2011] [11:25:14] <neale1>	pieter_hintjens: Yeah I was just going to see if anyone had done it so (a) I know it could be done and (b) they might have a "recipe" for doing it and I could pass that wisdom on
| [Monday 21 February 2011] [11:25:48] <sustrik>	cremes: the application in questio; is it using req or xreq socket?
| [Monday 21 February 2011] [11:25:55] <cremes>	xreq
| [Monday 21 February 2011] [11:26:20] <sustrik>	ok, so you handle individual message parts by hand
| [Monday 21 February 2011] [11:26:29] <sustrik>	are you closing all of them?
| [Monday 21 February 2011] [11:26:47] <sustrik>	identity/delimiter/body?
| [Monday 21 February 2011] [11:27:32] <cremes>	yes
| [Monday 21 February 2011] [11:27:43] <cremes>	btw, i see this with the latest master too
| [Monday 21 February 2011] [11:28:31] <cremes>	all message parts are passed to my read callback
| [Monday 21 February 2011] [11:28:35] <cremes>	and i call:  messages.each { |message| message.close }
| [Monday 21 February 2011] [11:29:14] <cremes>	it's iterating over the array of message parts calling close on each (zmq_close is called inside of the close() instance method)
| [Monday 21 February 2011] [11:29:39] <sustrik>	what language is that?
| [Monday 21 February 2011] [11:29:42] <cremes>	does xreq pass the identity and delimiter messages up the stack?
| [Monday 21 February 2011] [11:29:44] <cremes>	ruby
| [Monday 21 February 2011] [11:29:53] <sustrik>	cremes: yes
| [Monday 21 February 2011] [11:29:59] <cremes>	i thought only xrep saw all that detail
| [Monday 21 February 2011] [11:30:22] <sustrik>	same with xreq 
| [Monday 21 February 2011] [11:31:37] <sustrik>	are there connections being created and torn down during the test?
| [Monday 21 February 2011] [11:33:31] <cremes>	yes, these connections can and do go away (socket is closed via zmq_close())
| [Monday 21 February 2011] [11:33:48] <cremes>	btw, i am printing everything this callback is receiving to my log
| [Monday 21 February 2011] [11:34:05] <cremes>	it does get the nul delimiter message but it does not get the identity message before it
| [Monday 21 February 2011] [11:34:41] <sustrik>	right the identity is used and stripped off by the xrep socket on the other side of the connection
| [Monday 21 February 2011] [11:34:44] <cremes>	that confirms what i originally thought; xreq strips that off
| [Monday 21 February 2011] [11:34:50] <sustrik>	xrep
| [Monday 21 February 2011] [11:35:22] <sustrik>	so the identity is passed to the xreq only on a single occassion:
| [Monday 21 February 2011] [11:35:27] <sustrik>	on connection initiation
| [Monday 21 February 2011] [11:35:43] <sustrik>	let me check the corresponding code...
| [Monday 21 February 2011] [11:36:07] <cremes>	i thought it worked opposite; xrep gets identity from xreq during connection
| [Monday 21 February 2011] [11:36:22] <cremes>	xreq doesn't actually send its identity after that; xrep prepends it locally
| [Monday 21 February 2011] [11:37:04] <cremes>	so when sending from xreq, it goes nul delimiter + message parts
| [Monday 21 February 2011] [11:37:46] <cremes>	xrep recvs routing info (if any intervening hops) and pushes its peers identity on the top of that stack + delimiter + message parts
| [Monday 21 February 2011] [11:38:03] <cremes>	then when it replies, it just sends that routing info stack + nul + parts
| [Monday 21 February 2011] [11:38:43] <cremes>	and ultimately xreq (at original source) recvs just nul delimiter + parts because each intervening xreq stripped off one level of routing info
| [Monday 21 February 2011] [11:38:52] <sustrik>	except of the first part of the route stack
| [Monday 21 February 2011] [11:39:06] <sustrik>	which it have already used to route the message back
| [Monday 21 February 2011] [11:39:09] <sustrik>	to the xreq
| [Monday 21 February 2011] [11:40:07] <cremes>	why would the last hop need to send that routing info to the originator? that socket already "knows" their own identity!
| [Monday 21 February 2011] [11:40:29] <sustrik>	that's why it stips it off
| [Monday 21 February 2011] [11:40:33] <sustrik>	i short
| [Monday 21 February 2011] [11:40:44] <sustrik>	xreq doesn't mess with routing info at all
| [Monday 21 February 2011] [11:41:03] <sustrik>	xrep adds one peers identity to the stack on message receival
| [Monday 21 February 2011] [11:41:17] <sustrik>	and strips one identity from the stack on send
| [Monday 21 February 2011] [11:41:19] <pieter_hintjens>	s/xreq/dealer/g, s/xrep/router/g, it'll be much easier
| [Monday 21 February 2011] [11:41:31] <sustrik>	i think i see the leak
| [Monday 21 February 2011] [11:41:56] <pieter_hintjens>	dealers are just like push + pull
| [Monday 21 February 2011] [11:42:04] <cremes>	right, then i think we agree; the *last* xrep to reply to the original xreq will *strip* off its identity, so it only sends the delimiter + parts
| [Monday 21 February 2011] [11:44:50] <sustrik>	cremes: i've pasted the patch via irc to you directly
| [Monday 21 February 2011] [11:45:05] <sustrik>	let me know whether it helps
| [Monday 21 February 2011] [11:45:22] <pieter_hintjens>	sustrik: thanks for your help with those two issues btw
| [Monday 21 February 2011] [11:45:34] <sustrik>	np
| [Monday 21 February 2011] [11:45:54] <pieter_hintjens>	i have a third one which I *think* actually might be a 0MQ issue ... :-)
| [Monday 21 February 2011] [11:45:57] <pieter_hintjens>	#169
| [Monday 21 February 2011] [11:46:10] <sustrik>	:)
| [Monday 21 February 2011] [11:46:44] <pieter_hintjens>	not sure what the semantics are for zmq_term and pubsub
| [Monday 21 February 2011] [11:46:57] <pieter_hintjens>	if there are 10 connected subscribers, should they all get the last message?
| [Monday 21 February 2011] [11:47:13] <pieter_hintjens>	assuming publisher sends and then terminates
| [Monday 21 February 2011] [11:47:39] <sustrik>	aren't you just running into async connect issue?
| [Monday 21 February 2011] [11:47:55] <cremes>	sustrik: success!
| [Monday 21 February 2011] [11:47:56] <pieter_hintjens>	it's a synchronized pubsub example
| [Monday 21 February 2011] [11:48:12] <sustrik>	cremes: great
| [Monday 21 February 2011] [11:48:18] <sustrik>	let me apply the patch
| [Monday 21 February 2011] [11:48:26] <pieter_hintjens>	subscribers explicitly tell publisher when they are present
| [Monday 21 February 2011] [11:48:38] <cremes>	sustrik: if you want to do an occasional 'leaks' check on osx, feel free
| [Monday 21 February 2011] [11:48:48] <sustrik>	ack
| [Monday 21 February 2011] [11:49:00] <cremes>	it's really easy... # MallocStackLogging=1 ./my_program
| [Monday 21 February 2011] [11:49:09] <cremes>	leaks <pid of my_program>
| [Monday 21 February 2011] [11:49:17] <pieter_hintjens>	sustrik: I'll test if it's due to async connects... hang on...
| [Monday 21 February 2011] [11:50:31] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r0eea935 10/ src/zmq_init.cpp : 
| [Monday 21 February 2011] [11:50:32] <CIA-21>	zeromq2: Fix for memory leak caused by long identities
| [Monday 21 February 2011] [11:50:32] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/hrfcjQ
| [Monday 21 February 2011] [11:50:40] <sustrik>	cremes: done
| [Monday 21 February 2011] [11:50:45] <sustrik>	and thanks for the offer
| [Monday 21 February 2011] [11:51:22] <sustrik>	cremes: btw, it was you who said that SO_SNDBUF/SO_RCVBUF on OSX is measured in kB rather than bytes, right?
| [Monday 21 February 2011] [11:51:57] <cremes>	sustrik: yeah, that's the way it looks to me but i can't find that documented anywhere
| [Monday 21 February 2011] [11:51:59] <cremes>	it's screwy
| [Monday 21 February 2011] [11:52:47] <sustrik>	the interesting part is that you've mentioned that getsockopt(SNDBUF) returns 0
| [Monday 21 February 2011] [11:52:58] <sustrik>	so it's not obvious how to even find out
| [Monday 21 February 2011] [11:53:09] <cremes>	ack
| [Monday 21 February 2011] [11:53:26] <cremes>	if you want to write a small c program that exercises that stuff, that's probably the best way to know "for sure"
| [Monday 21 February 2011] [11:53:41] <sustrik>	what kind of kernel is that btw
| [Monday 21 February 2011] [11:53:44] <sustrik>	proprietaty?
| [Monday 21 February 2011] [11:53:44] <cremes>	i could also ask about it on apple's dev lists
| [Monday 21 February 2011] [11:53:53] <cremes>	nope, it's open source
| [Monday 21 February 2011] [11:54:05] <cremes>	it's called darwin... it's a mach + freebsd hybrid
| [Monday 21 February 2011] [11:54:05] <sustrik>	then try asking on the list
| [Monday 21 February 2011] [11:54:22] <cremes>	ok
| [Monday 21 February 2011] [11:54:22] <sustrik>	the functionality is obviously misbehaving
| [Monday 21 February 2011] [11:54:34] <sustrik>	so it would be nice to know what the devs have to say about it
| [Monday 21 February 2011] [11:54:35] <cremes>	any chance you could provide a small c program that illustrates the issue?
| [Monday 21 February 2011] [11:54:41] <cremes>	code always talks louder
| [Monday 21 February 2011] [11:54:43] <sustrik>	i can try
| [Monday 21 February 2011] [11:54:46] <sustrik>	wait a sec
| [Monday 21 February 2011] [11:54:48] <cremes>	especially when they can repro it :)
| [Monday 21 February 2011] [11:55:22] <cremes>	maybe get/setsockopt only screw up on socketpairs
| [Monday 21 February 2011] [11:55:57] <sustrik>	yes, that's my thinking as well
| [Monday 21 February 2011] [11:56:06] <sustrik>	btw, POSIX doesn't specify the unit :_
| [Monday 21 February 2011] [11:56:07] <sustrik>	:)
| [Monday 21 February 2011] [11:56:17] <sustrik>	it just says "buffer size"
| [Monday 21 February 2011] [11:56:22] <cremes>	heh
| [Monday 21 February 2011] [11:56:47] <cremes>	yeah, i can't imagine get/setsockopt are broken for all sockets... that would be *very* obvious
| [Monday 21 February 2011] [11:56:56] <sustrik>	Same with Stevens' book
| [Monday 21 February 2011] [11:57:09] <sustrik>	anyway, let me write an example
| [Monday 21 February 2011] [11:57:58] <cremes>	k
| [Monday 21 February 2011] [12:02:22] <pieter_hintjens>	sustrik: you were right...!
| [Monday 21 February 2011] [12:02:55] <pieter_hintjens>	0MQ is just too fast, all the 1M messages get broadcast even before the clients connect...
| [Monday 21 February 2011] [12:03:23] <sustrik>	heh
| [Monday 21 February 2011] [12:03:52] <pieter_hintjens>	it makes it quite a challenge to synchronize subscribers and publishers then...
| [Monday 21 February 2011] [12:03:58] <pieter_hintjens>	not sure the worked example is even valid
| [Monday 21 February 2011] [12:06:27] <sustrik>	i am not sure that's it even possible
| [Monday 21 February 2011] [12:06:35] <sustrik>	it's like synchronising a radio show
| [Monday 21 February 2011] [12:06:38] <sustrik>	with all listeners
| [Monday 21 February 2011] [12:07:29] <sustrik>	there still me a letter from a listener in amazonia asking for postponing the show
| [Monday 21 February 2011] [12:07:39] <sustrik>	stuck somewhere in post office at manaos
| [Monday 21 February 2011] [12:08:38] <sustrik>	if you know the number of listeners in advance, it can be solvable
| [Monday 21 February 2011] [12:13:02] <sustrik>	cremes: i've created a socket pair on OSX
| [Monday 21 February 2011] [12:13:14] <cremes>	ok
| [Monday 21 February 2011] [12:13:22] <sustrik>	tried to getsockopt the SNDBUF and RCVBUF
| [Monday 21 February 2011] [12:13:28] <sustrik>	both result in 3,000,000
| [Monday 21 February 2011] [12:13:43] <sustrik>	where have you seen it returning a zero?
| [Monday 21 February 2011] [12:14:26] <cremes>	in mailbox.cpp ::send, that buffer expansion code will return 0 or 32 depending
| [Monday 21 February 2011] [12:14:59] <cremes>	zmq::mailbox_t::send around line 160
| [Monday 21 February 2011] [12:15:26] <sustrik>	strange
| [Monday 21 February 2011] [12:15:27] <cremes>	line 170 usually fails to return a sane number
| [Monday 21 February 2011] [12:15:43] <sustrik>	meybe setsockopt uses different units than getsockopt?
| [Monday 21 February 2011] [12:15:48] <sustrik>	let me try
| [Monday 21 February 2011] [12:16:08] <cremes>	btw, that 3 million number is bytes and i set it in my /etc/sysctl.conf if you want to look at that
| [Monday 21 February 2011] [12:16:26] <sustrik>	that seems to be ok
| [Monday 21 February 2011] [12:16:27] <cremes>	that's the sysctl for local communications which is what i guess socketpair uses
| [Monday 21 February 2011] [12:16:30] <sustrik>	no need checking
| [Monday 21 February 2011] [12:16:39] <sustrik>	the problem is somewhere further down the way
| [Monday 21 February 2011] [12:21:22] <sustrik>	resizing on osx works better on osx than on linux :)
| [Monday 21 February 2011] [12:21:29] <sustrik>	i resize to 100,000
| [Monday 21 February 2011] [12:21:32] <sustrik>	i check the size
| [Monday 21 February 2011] [12:21:35] <sustrik>	i get 100000
| [Monday 21 February 2011] [12:21:45] <sustrik>	when i do same with linux i get
| [Monday 21 February 2011] [12:21:47] <sustrik>	200000
| [Monday 21 February 2011] [12:22:00] <cremes>	heh
| [Monday 21 February 2011] [12:22:23] <cremes>	try running that stress test... that usually blows it up
| [Monday 21 February 2011] [12:27:21] <pieter_hintjens>	sustrik: something to think about for the future, if we can make synchronous connects
| [Monday 21 February 2011] [12:27:34] <pieter_hintjens>	it'd add real value IMO
| [Monday 21 February 2011] [12:27:46] <pieter_hintjens>	for certain use cases at least
| [Monday 21 February 2011] [12:28:19] <cremes>	pieter_hintjens: that could be provided by an add-on/wrapper library
| [Monday 21 February 2011] [12:28:26] <pieter_hintjens>	nope, not afaics
| [Monday 21 February 2011] [12:28:35] <pieter_hintjens>	i'm hitting this problem in one of the examples
| [Monday 21 February 2011] [12:28:47] <cremes>	why, because connection status isn't exposed?
| [Monday 21 February 2011] [12:28:53] <pieter_hintjens>	i use a req/rep dialog to synchronize the two peers, then a pubsub dialog for the data
| [Monday 21 February 2011] [12:29:04] <cremes>	sounds like ftp
| [Monday 21 February 2011] [12:29:11] <pieter_hintjens>	but I can't get the two synchronized
| [Monday 21 February 2011] [12:29:20] <pieter_hintjens>	because the pubsub connect can take any arbitrary time
| [Monday 21 February 2011] [12:29:37] <cremes>	hmmm
| [Monday 21 February 2011] [12:29:38] <pieter_hintjens>	so even if the req/rep dialog says 'ready', that doesn't mean the subscriber will get data
| [Monday 21 February 2011] [12:29:43] <cremes>	right
| [Monday 21 February 2011] [12:29:56] <pieter_hintjens>	the only sure way is that the pubsub dialog explicitly confirms the connection, if over a connected transport
| [Monday 21 February 2011] [12:30:11] <cremes>	so, you bind the SUB socket, the req/rep says ready, you connect the PUB and it fails?
| [Monday 21 February 2011] [12:30:15] <pieter_hintjens>	yup
| [Monday 21 February 2011] [12:30:26] <cremes>	sounds like a bug
| [Monday 21 February 2011] [12:30:27] <pieter_hintjens>	doesn't fail, just doesn't connect in time to get any data
| [Monday 21 February 2011] [12:30:40] <cremes>	wait, which one doesn't connect in time to get data?
| [Monday 21 February 2011] [12:30:57] <pieter_hintjens>	It's this one: https://github.com/zeromq/zeromq2/issues/169
| [Monday 21 February 2011] [12:31:46] <pieter_hintjens>	i'd like a handshake between publisher & subscriber at connect time, which is exposed to the app
| [Monday 21 February 2011] [12:32:04] <pieter_hintjens>	so subscriber sends identity, and publisher acknowledges, and app code can wait for that to complete
| [Monday 21 February 2011] [12:32:10] <pieter_hintjens>	optionally
| [Monday 21 February 2011] [12:32:14] <cremes>	pieter_hintjens: this is why i use devices so much
| [Monday 21 February 2011] [12:32:33] <cremes>	put a forwarder in the middle and it will probably work
| [Monday 21 February 2011] [12:32:45] <cremes>	the pub connects to the forwarder as do the subs
| [Monday 21 February 2011] [12:32:56] <pieter_hintjens>	i'll have the same issue from forwarder to subscribers
| [Monday 21 February 2011] [12:32:59] <cremes>	when your req/rep gives the all-clear, let 'er rip
| [Monday 21 February 2011] [12:33:36] <cremes>	well, if zmq_connect() takes an arbitrary amount of time, that seems like a 'broken' contract to me
| [Monday 21 February 2011] [12:33:36] <pieter_hintjens>	it's all asynchronous, adding more steps may introduce enough delay, but it's not certain
| [Monday 21 February 2011] [12:33:43] <cremes>	right, i see
| [Monday 21 February 2011] [12:34:22] <pieter_hintjens>	sustrik: would you consider a handshake for new connections?
| [Monday 21 February 2011] [12:34:38] <pieter_hintjens>	i.e. C: identity frame, S: identity ack
| [Monday 21 February 2011] [14:16:13] <sustrik>	cremes: still there?
| [Monday 21 February 2011] [14:16:24] <cremes>	sustrik: yes
| [Monday 21 February 2011] [14:16:27] <sustrik>	git doesn't seem to be installed on your box
| [Monday 21 February 2011] [14:16:54] <sustrik>	how do you get the sources?
| [Monday 21 February 2011] [14:16:57] <cremes>	add /opt/local/bin to your $PATH
| [Monday 21 February 2011] [14:17:02] <sustrik>	ok
| [Monday 21 February 2011] [14:17:27] <sustrik>	works!
| [Monday 21 February 2011] [14:17:28] <sustrik>	thanks
| [Monday 21 February 2011] [14:17:34] <cremes>	you're welcome
| [Monday 21 February 2011] [14:19:58] <sustrik>	btw, have you seen the shutdown stress to fail with head?
| [Monday 21 February 2011] [14:20:18] <sustrik>	doesn't fail for me
| [Monday 21 February 2011] [14:20:35] 	 * sustrik guesses that the problem was alleviated by introduction of the reaper thread
| [Monday 21 February 2011] [14:26:17] <cremes>	sustrik: i haven't seen it fail since i boosted my buffers to 3MB (that 3 million number you saw earlier)
| [Monday 21 February 2011] [14:26:28] <cremes>	if i move back to the defaults, i'm fairly certain it will fail
| [Monday 21 February 2011] [14:26:29] <sustrik>	aha
| [Monday 21 February 2011] [14:26:36] <sustrik>	can you do that?
| [Monday 21 February 2011] [14:26:54] <cremes>	not at the moment... i'm wrapping up some work
| [Monday 21 February 2011] [14:26:59] <cremes>	i can do that tomorrow 
| [Monday 21 February 2011] [14:27:00] <sustrik>	ok, np
| [Monday 21 February 2011] [14:27:09] <sustrik>	just ping me then
| [Monday 21 February 2011] [14:28:05] <ljackson>	did I read the documentation correctly that in a multithreaded app the zmq context is common to all sockets bind and connect ?
| [Monday 21 February 2011] [14:28:40] <sustrik>	yes
| [Monday 21 February 2011] [14:29:45] <ljackson>	k, if you have a embeded queue device with workers in threads connecting to inproc
| [Monday 21 February 2011] [14:29:57] <pieter_hintjens>	ljackson: only necessarily if you're using inproc
| [Monday 21 February 2011] [14:30:08] <ljackson>	can you with the same context in another thread add stuff to the queue via another inproc ?
| [Monday 21 February 2011] [14:30:16] <ljackson>	pieter_hintjens, good to know. 
| [Monday 21 February 2011] [14:30:33] <pieter_hintjens>	ljackson: the semantic for communicating between threads is 'send a message'
| [Monday 21 February 2011] [14:30:44] <pieter_hintjens>	you can send a message to the queue device from any thread, obviously
| [Monday 21 February 2011] [14:30:46] <ljackson>	what I am seeing is zmq hanging trying to connect/bind must be something i messed up then
| [Monday 21 February 2011] [14:31:22] <ljackson>	basically as a test tring to take mtserver.cpp and put the client internal all on inproc using same context is this even valid ?
| [Monday 21 February 2011] [14:31:31] <ljackson>	obviously
| [Monday 21 February 2011] [14:31:37] <ljackson>	diffrent inproc:// addresses
| [Monday 21 February 2011] [14:31:53] <ljackson>	workers for threads as example has and then using queue for clients
| [Monday 21 February 2011] [14:31:58] <pieter_hintjens>	it should work
| [Monday 21 February 2011] [14:32:02] <ljackson>	humm
| [Monday 21 February 2011] [14:32:24] <ljackson>	ok will keep digging or write example test code if I can get it to work and ask again here
| [Monday 21 February 2011] [14:32:27] <ljackson>	thx 
| [Monday 21 February 2011] [14:32:30] <pieter_hintjens>	if your code's short, post it to a gist so we can look at it
| [Monday 21 February 2011] [14:33:06] <ljackson>	yeah might have to write an example code for my own sanity anyway if I can reproduce my issue I will post and ask again here
| [Monday 21 February 2011] [14:34:44] <ljackson>	i also believe I read that the order of connection bind vs connect doesn't matter? Or is that in only certain socket types ?
| [Monday 21 February 2011] [14:35:00] <ljackson>	worried that the device thread is not binding before the workers connect
| [Monday 21 February 2011] [14:35:06] <ljackson>	...etc.
| [Monday 21 February 2011] [14:35:32] <pieter_hintjens>	for inproc it matters
| [Monday 21 February 2011] [14:35:38] <pieter_hintjens>	you must absolutely bind, then connect
| [Monday 21 February 2011] [14:35:50] <pieter_hintjens>	let me send you a new version of mtrelay that shows how I do this in 2.1
| [Monday 21 February 2011] [14:35:54] <pieter_hintjens>	it's somewhat changed
| [Monday 21 February 2011] [14:36:04] <ljackson>	nice thx, I am using 2.1.1 from git
| [Monday 21 February 2011] [14:36:25] <pieter_hintjens>	https://gist.github.com/837575
| [Monday 21 February 2011] [14:36:43] <pieter_hintjens>	the trick is to bind and connect a socket pair in the parent thread, then pass the context & socket to the child thread
| [Monday 21 February 2011] [14:37:06] <pieter_hintjens>	i will try to make a simple abstraction for this, it's a very common pattern
| [Monday 21 February 2011] [14:37:28] <pieter_hintjens>	specifically for inproc multithreading that is never intended to be scaled out
| [Monday 21 February 2011] [14:39:23] <ljackson>	humm
| [Monday 21 February 2011] [14:39:38] <ljackson>	i thought you were never to share/send the socket ?
| [Monday 21 February 2011] [14:42:23] <pieter_hintjens>	in 2.1 this is legal, and extremely useful for inproc/multithreading
| [Monday 21 February 2011] [14:42:31] <pieter_hintjens>	not shared, just sent
| [Monday 21 February 2011] [14:49:52] <ljackson>	ahh i get it so you know for sure that it was done in the correct order
| [Monday 21 February 2011] [14:50:04] <ljackson>	then you send on the pointer and forget you knew about it
| [Monday 21 February 2011] [14:50:07] <ljackson>	k
| [Monday 21 February 2011] [14:51:40] <ljackson>	pieter_hintjens, so you need to bind a new socket for each worker thread then 
| [Monday 21 February 2011] [14:51:54] <ljackson>	in REQ/RES...etc.
| [Monday 21 February 2011] [14:52:25] <pieter_hintjens>	yes
| [Monday 21 February 2011] [14:55:06] <amacleod>	What 0MQ pattern is best for an asynchronous dialogue, where 2 participants can send messages but there doesn't need to be a 1:1 request/response correspondence?
| [Monday 21 February 2011] [14:55:20] <amacleod>	Can XREQ/XREP do that?
| [Monday 21 February 2011] [14:56:42] <ljackson>	pieter_hintjens, thread_args_t *child; child->socket = new zmq::socket_t(*context, ZMQ_ZXREP); ?
| [Monday 21 February 2011] [14:57:08] <cremes>	amacleod: yes, those sockets are the perfect choice
| [Monday 21 February 2011] [14:57:15] <pieter_hintjens>	ljackson: what's the question?
| [Monday 21 February 2011] [14:57:34] <amacleod>	Okay, cool.  My next step is to understand how to use identity addressing, then.
| [Monday 21 February 2011] [14:57:43] <pieter_hintjens>	amacleod: have you read the Guide yet?
| [Monday 21 February 2011] [14:57:45] <ljackson>	c++ vs your example
| [Monday 21 February 2011] [14:57:55] <amacleod>	pieter_hintjens, parts of it.
| [Monday 21 February 2011] [14:58:04] <pieter_hintjens>	ljackson: you're asking whether the C++ is correct?
| [Monday 21 February 2011] [14:58:46] <ljackson>	as in the new pointer .. yeah nevermind answered my own Q
| [Monday 21 February 2011] [15:05:28] <amacleod>	So, I noticed when using the Java bindings, I cannot seem to interrupt a recv operation that's trying to read from a socket whose other endpoint doesn't exist.
| [Monday 21 February 2011] [15:05:51] <amacleod>	If I want to preserve Java interruptability, should I be using NOBLOCK and a poller?
| [Monday 21 February 2011] [15:16:28] <fbarriga>	I have a little problem with python
| [Monday 21 February 2011] [15:16:41] <fbarriga>	I can't receive an structure from C++
| [Monday 21 February 2011] [15:16:56] <amacleod>	fbarriga, what format are you using to serialize structures?
| [Monday 21 February 2011] [15:17:00] <fbarriga>	I don't know why It tries to receive it like a string
| [Monday 21 February 2011] [15:17:06] <fbarriga>	in C++ raw structure
| [Monday 21 February 2011] [15:17:11] <fbarriga>	in python struct.unpack
| [Monday 21 February 2011] [15:17:16] <fbarriga>	in the reverse way it works
| [Monday 21 February 2011] [15:17:59] <fbarriga>	msg = self.socket.recv()
| [Monday 21 February 2011] [15:18:13] <fbarriga>	len (msg) it prints 29
| [Monday 21 February 2011] [15:18:59] <fbarriga>	and I'm sending only a double
| [Monday 21 February 2011] [15:19:09] <fbarriga>	double nav = 1; memcpy(zmq_msg_data(&msg), &nav, sizeof(double));
| [Monday 21 February 2011] [15:19:39] <amacleod>	Can you do a byte-by-byte comparison of what you're getting on the wire and the result of struct.pack with the value you expect?
| [Monday 21 February 2011] [15:21:36] <amacleod>	On the C++ side you are telling zmq that your packet should be (sizeof double) bytes long?
| [Monday 21 February 2011] [15:22:48] <ljackson>	pieterh, acording to what I read in the docs/guide am i correct in that the PUSH/PULL socket can have multiple pushers and a single puller in the same context e.g. workers and sinks ?
| [Monday 21 February 2011] [15:23:06] <pieterh>	sure
| [Monday 21 February 2011] [15:23:12] <fbarriga>	sorry guys I found it
| [Monday 21 February 2011] [15:23:23] <ljackson>	pieterh, just wanted to make sure I read it right thx :)
| [Monday 21 February 2011] [15:23:34] <pieterh>	ljackson: all socket types except PAIR can be connected 1-N or N-1
| [Monday 21 February 2011] [15:23:42] <ljackson>	or N-N ?
| [Monday 21 February 2011] [15:23:54] <fbarriga>	quite stupid my error, I've 2 streams and I was connecting to the wrong one :(
| [Monday 21 February 2011] [15:24:00] <pieterh>	that's just 1-N and N-1 from two sides
| [Monday 21 February 2011] [15:24:06] <ljackson>	ya
| [Monday 21 February 2011] [15:25:36] <ljackson>	inproc, pull push need the same treatment as req/res ..etc ?
| [Monday 21 February 2011] [15:28:08] <pieterh>	ljackson: rtfm here http://zguide.zeromq.org/chapter:all#toc21
| [Monday 21 February 2011] [15:28:38] <pieterh>	i'm adding more detail on the 2.1 mtrelay example but the point is that inproc is not a disconnected transport
| [Monday 21 February 2011] [15:34:07] <ljackson>	k thx
| [Monday 21 February 2011] [15:52:53] <amacleod>	In Java bindings, how do I determine what error happened when recv returns null?
| [Monday 21 February 2011] [15:58:58] <CIA-21>	jzmq: 03Gonzalo Diethelm 07master * r91da678 10/ (5 files in 2 dirs): 
| [Monday 21 February 2011] [15:58:59] <CIA-21>	jzmq: Use zmq_errno() everywhere instead of errno.
| [Monday 21 February 2011] [15:58:59] <CIA-21>	jzmq: Set all projects to compile with a Release configuration. - http://bit.ly/h8ZIKL
| [Monday 21 February 2011] [16:05:49] <gdan>	trying to build in ubuntu 10.10:  installed: g++,g++ 4.5,gcc-opt, libstdc++6, libstdc++645-dev,   *** I am getting what appers to me stl errors, does anyone have a list of reuired libaries?
| [Monday 21 February 2011] [16:06:04] <gdan>	building the libzmq
| [Monday 21 February 2011] [16:09:08] <pieterh>	gdan: I'm searching for the answer...
| [Monday 21 February 2011] [16:09:15] <gdan>	thanks
| [Monday 21 February 2011] [16:10:56] <pieterh>	gdan: do you have build-essential?
| [Monday 21 February 2011] [16:11:11] <gdan>	let me check
| [Monday 21 February 2011] [16:12:51] <gdan>	do not see it, nor do i see it avail in software centr
| [Monday 21 February 2011] [16:13:11] <pieterh>	apt-get install build-essential
| [Monday 21 February 2011] [16:13:25] <pieterh>	sudo apt-get install build-essential, to be accurate
| [Monday 21 February 2011] [16:13:56] <pieterh>	also uuid-dev
| [Monday 21 February 2011] [16:14:05] <gdan>	installing...
| [Monday 21 February 2011] [16:14:35] <soren>	Or: sudo apt-get build-dep libzmq0
| [Monday 21 February 2011] [16:14:49] <soren>	That installs all the build-dependencies of the libzmq0 ubuntu package.
| [Monday 21 February 2011] [16:14:54] <soren>	Handy shortcut.
| [Monday 21 February 2011] [16:15:14] <gdan>	will do...
| [Monday 21 February 2011] [16:19:33] <gdan>	i re-ran  configure, now make is running.   so far, looks good.  thank you
| [Monday 21 February 2011] [16:24:39] <pieterh>	gdan: np
| [Monday 21 February 2011] [16:28:29] <ljackson>	pieterh, odd appears i am close, getting context terminated exception...
| [Monday 21 February 2011] [16:29:09] <pieterh>	main thread terminates the context before other threads are finished
| [Monday 21 February 2011] [16:31:23] <ljackson>	humm
| [Monday 21 February 2011] [16:32:40] <ljackson>	this happens starting up the ZMQ_QUEUE device. even before I get to starting worker threads
| [Monday 21 February 2011] [16:32:59] <ljackson>	QUEUE bridging inproc not tested ?
| [Monday 21 February 2011] [16:38:43] <pieterh>	ljackson: hard to say without code to look at
| [Monday 21 February 2011] [16:39:07] <pieterh>	the queue device is just normal code
| [Monday 21 February 2011] [16:39:47] <pieterh>	find where you're doing zmq_term, print "HELLO" and then check whether that shows before the error...
| [Monday 21 February 2011] [16:40:02] <pieterh>	if you terminate the context, that kills all inproc sockets
| [Monday 21 February 2011] [16:42:50] <ljackson>	yeah not doing any terminate, but a few other things with this existing code... prob need to make test code to try to reproduce
| [Monday 21 February 2011] [16:49:12] <ljackson>	doh I think i see it
| [Monday 21 February 2011] [16:51:18] <amacleod>	Where are the URIs for 0MQ documented?  I assumed I should be using tcp://host:port even for my XREQ/XREP dialogue, but the "mamas/papas" examples in the guide use things like "ipc://routing.ipc".
| [Monday 21 February 2011] [16:53:46] <amacleod>	Found it.  zmq_ipc(7) man page.
| [Monday 21 February 2011] [16:58:03] <pieterh>	amacleod: zmq_bind / zmq_connect man pages list the transports, each has its own man page
| [Monday 21 February 2011] [16:59:05] <amacleod>	Ok, thanks.  So I still want tcp since I want all my sockets to be remote.
| [Monday 21 February 2011] [17:00:44] <amacleod>	I'm still having trouble wrapping my head around the addressing requirements for XREQ/XREP.
| [Monday 21 February 2011] [17:01:26] <amacleod>	So far I have an XREP "server" that listens for connections.  I'm able to create an XREQ "client" that establishes a connection and sends a request.
| [Monday 21 February 2011] [17:01:56] <amacleod>	The server sees the request and where it came from (2 message parts: address, payload), and is able to reply.
| [Monday 21 February 2011] [17:02:27] <amacleod>	When I send the reply as (address, null, payload), I can see in wireshark that some data gets sent in the opposite direction on the socket, but my recv call in the client never returns.
| [Monday 21 February 2011] [17:02:35] <pieterh>	amacleod: ... some generalities about the request-reply pattern
| [Monday 21 February 2011] [17:02:51] <pieterh>	in most cases, client is REQ and server is REP
| [Monday 21 February 2011] [17:03:06] <pieterh>	and anything in the middle (e.g. queue device) is XREP--XREQ
| [Monday 21 February 2011] [17:03:20] <pieterh>	that's the basic layout
| [Monday 21 February 2011] [17:03:29] <pieterh>	after that there is the weird stuff
| [Monday 21 February 2011] [17:03:42] <pieterh>	which chapter 3 explains
| [Monday 21 February 2011] [17:03:47] <amacleod>	So to do this "asynchronous dialogue" thing, do I need to have more than 2 participants?
| [Monday 21 February 2011] [17:04:06] <pieterh>	asynchronous means what exactly?
| [Monday 21 February 2011] [17:04:16] <pieterh>	in your use case, I mean
| [Monday 21 February 2011] [17:04:21] <amacleod>	Not lockstep on requests and replies.
| [Monday 21 February 2011] [17:04:30] <pieterh>	so how do the messages flow?
| [Monday 21 February 2011] [17:04:37] <pieterh>	do you have N clients, 1 server?
| [Monday 21 February 2011] [17:04:43] <pieterh>	N clients, N servers?
| [Monday 21 February 2011] [17:04:45] <amacleod>	Yes.. N clients, 1 server.
| [Monday 21 February 2011] [17:04:51] <amacleod>	Bi-directional messages.
| [Monday 21 February 2011] [17:05:08] <pieterh>	can servers send messages to clients who have not sent a message to the server?
| [Monday 21 February 2011] [17:05:17] <pieterh>	or is it 1 request / 0-N responses?
| [Monday 21 February 2011] [17:05:21] <amacleod>	No.  There has to be at least an initial handshake.
| [Monday 21 February 2011] [17:05:29] <amacleod>	It's 1-N requests, 0-N responses.
| [Monday 21 February 2011] [17:05:44] <amacleod>	So, the client can still send messages to the server even while the server is sending responses.
| [Monday 21 February 2011] [17:05:47] <pieterh>	can clients pipeline requests?
| [Monday 21 February 2011] [17:05:50] <pieterh>	ah, ok
| [Monday 21 February 2011] [17:06:26] <pieterh>	so your server definitely has to be XREP (which we will rename to ROUTER at some stage)
| [Monday 21 February 2011] [17:06:39] <amacleod>	Okay.  That's the way I have it.
| [Monday 21 February 2011] [17:06:57] <pieterh>	your clients always initiate the dialog, and they talk to a single server only
| [Monday 21 February 2011] [17:07:04] <amacleod>	When I get messages in on the server, I add the identity to a routing table in the server object.
| [Monday 21 February 2011] [17:07:05] <gdan>	does anyone know in mono, how in mono (on ubuntu) i reference the libzmq runtime libraries i just built in the project?  ( do see that they are in usr/local/lib)
| [Monday 21 February 2011] [17:07:10] <pieterh>	so they do indeed use XREQ
| [Monday 21 February 2011] [17:07:13] <amacleod>	pieterh, that is correct.
| [Monday 21 February 2011] [17:07:27] <pieterh>	if your clients talked to N servers, you'd want to use XREP for them as well
| [Monday 21 February 2011] [17:07:28] <amacleod>	gdan, does mono respect LD_LIBRARY_PATH?
| [Monday 21 February 2011] [17:08:11] <gdan>	don't know.   perhaps when i run i specify the path?
| [Monday 21 February 2011] [17:08:24] <amacleod>	pieterh, indeed.  One thing I didn't realize at first was that, with XREQ, I did not need to explicitly send the client's identity.
| [Monday 21 February 2011] [17:08:55] <amacleod>	gdan, I know in Java, I have to do something like -Djava.library.path=path/to/jzmq_native.  Probably mono has something similar.
| [Monday 21 February 2011] [17:08:57] <pieterh>	amacleod: if you use either XREP or XREQ in your code, you absolutely have to study and learn how these sockets create and use envelopes
| [Monday 21 February 2011] [17:09:13] <pieterh>	it's logical once you know it but it is really not obvious
| [Monday 21 February 2011] [17:09:26] <amacleod>	pieterh, I have been trying to understand a bit by looking at wireshark.
| [Monday 21 February 2011] [17:09:30] <gdan>	i'll look
| [Monday 21 February 2011] [17:09:46] <pieterh>	it's explained in Ch3, look for Request-Reply envelopes
| [Monday 21 February 2011] [17:10:26] <amacleod>	One thing I was confused about in chapter 3 was how XREP and XREQ expect their envelopes.  Is it true that XREQ expects envelopes the same way REQ does and that XREP expects envelopes the same way REP does?
| [Monday 21 February 2011] [17:10:35] <pieterh>	no
| [Monday 21 February 2011] [17:10:39] <pieterh>	the name XREQ is highly misleading
| [Monday 21 February 2011] [17:10:46] <pieterh>	it should and will be called "DEALER"
| [Monday 21 February 2011] [17:10:56] <pieterh>	it is exactly equivalent to a PUSH+PULL combination
| [Monday 21 February 2011] [17:11:11] <pieterh>	it deals messages out, and in, without changing them
| [Monday 21 February 2011] [17:11:37] <pieterh>	whereas REP is a terminator that rips open the envelope, hides it, gives you the contents, and sneakily recreates the envelope when you send a reply
| [Monday 21 February 2011] [17:11:51] <pieterh>	they are fundamentally different tools
| [Monday 21 February 2011] [17:12:35] <pieterh>	take a look at the rtdealer example
| [Monday 21 February 2011] [17:12:38] <amacleod>	Ok.  What I was thinking a while ago is that I could achieve what I wanted with a pair of REQ/REP sockets, one for each direction.  The replies would always be dinky little "yep I got it" acknowledgements.
| [Monday 21 February 2011] [17:13:01] <pieterh>	it will work really easily using XREQ/XREP, don't panic
| [Monday 21 February 2011] [17:13:18] <amacleod>	But I couldn't think of a good way to create both at once.  (trying not to panic :-D)
| [Monday 21 February 2011] [17:13:50] <pieterh>	- your clients using XREQ just connect, and send simple messages
| [Monday 21 February 2011] [17:14:19] <pieterh>	- the server, when it receives a message, gives the app the client identity, followed by the simple message, in two parts
| [Monday 21 February 2011] [17:14:21] <amacleod>	So they are similar to the "worker" in rtdealer?  (I say this because worker uses XREQ).
| [Monday 21 February 2011] [17:14:42] <pieterh>	- the server, when it wants to talk to client A, sends two parts: identity A, and then simple message
| [Monday 21 February 2011] [17:14:59] <pieterh>	in rtdealer, client is the worker (uses XREQ as you see), server is the main thread
| [Monday 21 February 2011] [17:15:20] <pieterh>	would it help to have a real example of a server and clients working like this?
| [Monday 21 February 2011] [17:15:34] <pieterh>	i'll make one tomorrow, it's late here now
| [Monday 21 February 2011] [17:15:55] <amacleod>	Possibly.  I might try translating rtdealer into Java after I get home.
| [Monday 21 February 2011] [17:16:10] <pieterh>	it's not literally what you want, but it shows how to use that socket pair
| [Monday 21 February 2011] [17:17:15] <amacleod>	I thought that I had things pretty much okay as far as you have said.  When you say "the server sends two parts: identity A, and then simple message", do you mean that XREP(router) does that for me when I call send, or that my code should do that using sendmore followed by send?
| [Monday 21 February 2011] [17:17:56] <pieterh>	sendmore followed by send
| [Monday 21 February 2011] [17:18:09] <pieterh>	you need to explicitly tell the router socket who to send the message to
| [Monday 21 February 2011] [17:18:17] <pieterh>	it does not actually send the identity
| [Monday 21 February 2011] [17:18:32] <pieterh>	it uses that to decide what client to talk to, then sends the remaining message part(s)
| [Monday 21 February 2011] [17:18:42] <amacleod>	Ok.  It's possible there is a bug in my client receiving code.  I did see the reply come back on the socket in wireshark.
| [Monday 21 February 2011] [17:19:43] <pieterh>	I think your use case is much better than the one I used for XREP-XREQ 
| [Monday 21 February 2011] [17:20:00] <pieterh>	so I'll change the Guide for that...
| [Monday 21 February 2011] [17:20:20] <amacleod>	It's for instant-message style chat.  (wrapping XMPP).
| [Monday 21 February 2011] [17:20:40] <pieterh>	indeed
| [Monday 21 February 2011] [17:20:53] <pieterh>	tomorrow sometime I'll have a working example
| [Monday 21 February 2011] [17:21:38] <amacleod>	Ok.  I'll stop pestering you so you can sleep :-)  If I am able to translate the current example into Java, I'll let you know here tomorrow.
| [Monday 21 February 2011] [17:23:20] <pieterh>	np :-)
| [Monday 21 February 2011] [17:41:39] <CIA-21>	zeromq2: 03Mikko Koppanen 07master * r98ccff1 10/ builds/redhat/zeromq.spec : 
| [Monday 21 February 2011] [17:41:40] <CIA-21>	zeromq2: Fixes build on at least CentOS 5
| [Monday 21 February 2011] [17:41:40] <CIA-21>	zeromq2: Signed-off-by: Mikko Koppanen <mikko.koppanen@gmail.com> - http://bit.ly/hHoTEo
| [Monday 21 February 2011] [18:39:57] <rem7>	what is the best way to ensure the delivery of a msg in a PUSH/PULL (something very similar to the ventilator tutorial) ... I sent out about 16Million msgs and my sink recvd 10million.
| [Monday 21 February 2011] [18:41:07] <rem7>	I was reading that multicast only works on PUB/SUB...?
| [Monday 21 February 2011] [18:50:24] <mikko>	sustrik: thanks!
| [Monday 21 February 2011] [19:20:28] <cremes>	on a multi-part send, if any part fails (rc != 0 and errno is set) then 0mq gives my user code owernship of the messages again, yes?
| [Monday 21 February 2011] [19:20:50] <cremes>	in normal circumstances, once you pass a message to zmq_send() it's 0mq's responsibility to call zmq_msg_close()
| [Monday 21 February 2011] [19:20:56] <cremes>	except in the case above, right?
| [Monday 21 February 2011] [19:33:57] <mikko>	cremes: nope
| [Monday 21 February 2011] [19:34:07] <mikko>	cremes: even if you zmq_send message you need to close it
| [Monday 21 February 2011] [19:35:59] <cremes>	mikko: sheesh, i've been doing this wrong for *months* then
| [Monday 21 February 2011] [19:36:34] <cremes>	so, does zmq_send() increment the "copy counter" on the zmq_msg_t and then decrement it (and release) when it's sent?
| [Monday 21 February 2011] [19:37:00] <cremes>	it must otherwise when i call close it would release the message before 0mq has a chance to transmit it
| [Monday 21 February 2011] [19:37:10] <cremes>	pls confirm if you can
| [Monday 21 February 2011] [20:37:20] <mikko>	cremes: sorry, was a away building stuff
| [Monday 21 February 2011] [20:37:55] <mikko>	cremes: you can close right after send
| [Monday 21 February 2011] [20:38:03] <mikko>	take a look at zguide for samples
| [Monday 21 February 2011] [20:38:47] <mikko>	https://github.com/zeromq/zeromq2/blob/master/src/zmq.cpp#L129
| [Monday 21 February 2011] [20:38:52] <mikko>	also, that might clear it up a bit
| [Monday 21 February 2011] [20:40:14] <mikko>	also, see the page: http://api.zero.mq/master:zmq-msg-close for zmq_msg_close
| [Monday 21 February 2011] [21:09:39] <jugg>	whoa!  Since when did we get versioned api on the web?  Nice! :)
| [Monday 21 February 2011] [21:10:24] <jugg>	oh, different domain.  interesting.
| [Monday 21 February 2011] [21:11:43] <mikko>	jugg: been there a few days
| [Monday 21 February 2011] [21:12:09] <mikko>	and finally!
| [Monday 21 February 2011] [21:12:12] <mikko>	http://snapshot.zero.mq/rpm/2011-02-22_02-09-11/centos5/i386/
| [Monday 21 February 2011] [21:12:16] <mikko>	centos rpms available
| [Monday 21 February 2011] [21:12:20] <mikko>	time to sleep
| [Tuesday 22 February 2011] [05:40:56] <pieterh>	good morning
| [Tuesday 22 February 2011] [05:42:43] <ianbarber>	morning
| [Tuesday 22 February 2011] [05:48:01] <pieterh>	ianbarber: what part of the world are you in?
| [Tuesday 22 February 2011] [05:48:34] <pieterh>	London? you seem to get around a lot for your "0MQ is the answer" talks :-)
| [Tuesday 22 February 2011] [05:56:34] <ianbarber>	yep, london
| [Tuesday 22 February 2011] [05:56:54] <ianbarber>	i was hoping to get to give it at confoo as well, but they went with a different talk in the end :)
| [Tuesday 22 February 2011] [05:59:45] <pieterh>	I was thinking of doing a small 0MQ event in Brussels later in spring
| [Tuesday 22 February 2011] [06:00:01] <pieterh>	April or May, when it's nicer weather
| [Tuesday 22 February 2011] [06:03:42] <ianbarber>	awesome, i think that would be fun
| [Tuesday 22 February 2011] [06:05:05] <ianbarber>	are you based in brussels then, or near by?
| [Tuesday 22 February 2011] [06:07:37] <pieterh>	I'm in Brussels, yes, so it's easy for us to organize something here
| [Tuesday 22 February 2011] [06:08:03] <pieterh>	There's a nice place in the center of town I used to hold conferences in
| [Tuesday 22 February 2011] [06:09:02] <pieterh>	Brussels is reasonably central IMO, and of course there's the beer...
| [Tuesday 22 February 2011] [06:09:44] <ianbarber>	surely there are some unused government buildings available? :)
| [Tuesday 22 February 2011] [06:10:28] <ianbarber>	yeah, brussels is a really nice place, and easy to get to on the train from everywhere as well for people that aren't keen on flying. 
| [Tuesday 22 February 2011] [06:10:33] <pieterh>	you mean because one of our 7 governments is currently on extended holiday?
| [Tuesday 22 February 2011] [06:10:38] <pieterh>	lol
| [Tuesday 22 February 2011] [06:10:51] <pieterh>	ok, I'll set it up... excellent...
| [Tuesday 22 February 2011] [06:11:45] <pieterh>	I'm thinking, mix of workshops and project presentations
| [Tuesday 22 February 2011] [06:12:13] <pieterh>	people can go home in the evening, or stay overnight and socialise
| [Tuesday 22 February 2011] [06:13:53] <ianbarber>	i think that's sensible, though I would probably aim for a panel or discussion slot or two, just to to give it a less structured feel - I would imagine that the crowd will all be pretty good with the library so the chat will be as good as the talks
| [Tuesday 22 February 2011] [06:17:46] <pieterh>	So the idea is a lot of tables, chairs, refreshments, in a large room
| [Tuesday 22 February 2011] [06:18:07] <pieterh>	wifi
| [Tuesday 22 February 2011] [06:19:58] <ianbarber>	sounds good
| [Tuesday 22 February 2011] [06:29:01] <ianbarber>	btw, the clone example in the new guide chapter is excellent. 
| [Tuesday 22 February 2011] [06:31:35] <pieterh>	ah, glad you like it
| [Tuesday 22 February 2011] [06:32:04] <pieterh>	do you think it makes sense to do all the design discussion first, and then the code later?
| [Tuesday 22 February 2011] [06:32:26] <pieterh>	these examples are going to be a lot larger than the earlier ones
| [Tuesday 22 February 2011] [06:34:46] <ianbarber>	yeah, i think that's tricky whenever you get to a more real world example - i mean if the reader had been paying attention then should pretty much get how to build it by that point as all of the blocks have been covered. I think it is going to be a big block of code to cover the whole client and server case, but I'm not sure there's that much that should split it up
| [Tuesday 22 February 2011] [06:36:11] <pieterh>	I mean, after you read the Clone discussion, do you want to see it worked out in code, or do you want to continue to the Harmony discussion?
| [Tuesday 22 February 2011] [06:36:26] <pieterh>	assuming that code is 20 pages long...
| [Tuesday 22 February 2011] [06:36:54] <pieterh>	(not one code block, but developed piece by piece)
| [Tuesday 22 February 2011] [06:37:17] <pieterh>	for me the only way to prove the design is running code
| [Tuesday 22 February 2011] [06:37:50] <ianbarber>	yeah, i would definitely prefer to see some code
| [Tuesday 22 February 2011] [06:38:16] <pieterh>	ok, then I'll switch back to the earlier structure... it'll be like the last Worked example in Ch3
| [Tuesday 22 February 2011] [06:38:41] <ianbarber>	yeah, i think that was a reasonable model
| [Tuesday 22 February 2011] [06:39:01] <ianbarber>	would it be worth maybe having these examples be in python or another scripting language, just to trim the size on-page some?
| [Tuesday 22 February 2011] [06:41:17] <pieterh>	that could be good, yes
| [Tuesday 22 February 2011] [06:41:33] <pieterh>	it solves one problem I have with C, the lack of containers
| [Tuesday 22 February 2011] [06:41:44] <pieterh>	I was thinking of using ZFL for these advanced cases
| [Tuesday 22 February 2011] [06:41:49] <pieterh>	but Python would be neater
| [Tuesday 22 February 2011] [06:42:10] <pieterh>	However... I still need to write them in C :-)
| [Tuesday 22 February 2011] [06:42:20] <pieterh>	For completeness' sake
| [Tuesday 22 February 2011] [06:43:03] 	 * pieterh thinks a little...
| [Tuesday 22 February 2011] [06:43:15] <pieterh>	let's continue in C, which is the language of the API
| [Tuesday 22 February 2011] [06:43:35] <pieterh>	but we can produce versions of the Guide for every single language
| [Tuesday 22 February 2011] [06:43:44] <pieterh>	you want the Guide in Python? Not a problem!
| [Tuesday 22 February 2011] [06:44:03] <pieterh>	(any examples not translated will default to C then)
| [Tuesday 22 February 2011] [06:45:00] <pieterh>	since the source for examples is merged into the text at build time anyhow
| [Tuesday 22 February 2011] [06:46:46] <ianbarber>	that would be quite cool
| [Tuesday 22 February 2011] [06:47:22] <pieterh>	ok, it's a deal
| [Tuesday 22 February 2011] [06:47:57] <ianbarber>	on that note - is there a process for saying when new examples are ready for translation?
| [Tuesday 22 February 2011] [06:48:09] <ianbarber>	maybe just a mailing list ping that the code is there before the guide goes live
| [Tuesday 22 February 2011] [06:48:13] <pieterh>	hmm, I guess it involves tracking the git
| [Tuesday 22 February 2011] [06:48:34] <pieterh>	I'd rather not get into a release process for the guide
| [Tuesday 22 February 2011] [06:49:08] <pieterh>	there are only a couple of languages that people have translated systematically
| [Tuesday 22 February 2011] [06:49:12] <pieterh>	like PHP :-)
| [Tuesday 22 February 2011] [06:49:17] <stimpie>	I understood the goal of zeromq is becoming a kernel module, I have just read the interesting new part of the manual 'clone pattern' but I wander how this adds to a kernel level system? 
| [Tuesday 22 February 2011] [06:49:29] <pieterh>	stimpie: it's a layer on top
| [Tuesday 22 February 2011] [06:50:13] <ianbarber>	pieterh: fair point :) 
| [Tuesday 22 February 2011] [06:50:49] <pieterh>	ianbarber: yesterday I updated the C examples and text for 2.1...
| [Tuesday 22 February 2011] [06:51:06] <pieterh>	I'm not sure the PHP binding handles 2.1 even...
| [Tuesday 22 February 2011] [06:51:07] <ianbarber>	yeah, i was just making a note I should check the PHP ones
| [Tuesday 22 February 2011] [06:51:36] <ianbarber>	it's up to date as far as I know, I've been mostly using it against 2.1.0
| [Tuesday 22 February 2011] [06:51:43] <stimpie>	pieterh, ok clear enough.
| [Tuesday 22 February 2011] [06:51:45] <pieterh>	nice!
| [Tuesday 22 February 2011] [06:51:47] <pieterh>	hopefully these shifts will become rarer and rarer
| [Tuesday 22 February 2011] [06:52:15] <pieterh>	stimpie: there are lots of reusable patterns we can make on top of 0MQ, Ch4 is covering some of the reliability ones
| [Tuesday 22 February 2011] [06:52:28] <pieterh>	I think giving them names makes them easier to understand and reuse
| [Tuesday 22 February 2011] [06:54:27] <stimpie>	They are interesting patterns but it confuses me with what the scope of the zeromq project is
| [Tuesday 22 February 2011] [06:55:22] <private_meta>	hmm... I've been told that the c++ version of zmq uses void pointers because you can send something OTHER than char pointers as well, yet for the python version you can pretty much send a standard string in the send function. Doesn't that mean that this gives c++ functionality you can't capture with a similar python implementation?
| [Tuesday 22 February 2011] [06:57:30] <stimpie>	private_meta, the message content is up to the client. You could also serialize java objects which are pretty useless in a c++ client.
| [Tuesday 22 February 2011] [06:58:32] <private_meta>	Yeah, but it looks to me that for the python interface, in case I don't misunderstand it, the message content is narrowed down to strings
| [Tuesday 22 February 2011] [06:59:28] <ianbarber>	private_meta: underneath it's just a chunk of bytes - I would imagine that there is a pack function or similar that can pack anything into a string for python?
| [Tuesday 22 February 2011] [07:00:42] <private_meta>	I don't know, it's just that the send interface for python looks so convenient while with c++ you have to bitch around with zmq::message_t where you have to use memcpy or message_t.rebuild to get a simple string into a message
| [Tuesday 22 February 2011] [07:02:39] <ianbarber>	hmm, for C there's the little zhelpers script pieterh uses that provides some handy helper functions to hide some of that stuff, i don't know if there's a C++ equivalent
| [Tuesday 22 February 2011] [07:03:05] <pieterh>	stimpie: I'll make this clear in the text, thanks for pointing that out
| [Tuesday 22 February 2011] [07:04:00] <pieterh>	ianbarber: yes, some kind person made zhelpers.hpp
| [Tuesday 22 February 2011] [07:05:02] <pieterh>	private_meta: feel free to translate the zmsg code from C to C++, it'll give you what you want
| [Tuesday 22 February 2011] [07:06:01] <private_meta>	pieterh: uhm... it doesn't exist yte?
| [Tuesday 22 February 2011] [07:06:02] <private_meta>	*yet?
| [Tuesday 22 February 2011] [07:06:37] <pieterh>	private_meta: the feeling of pride and accomplishment you'll feel as you make it... will be better than steak salad and fries
| [Tuesday 22 February 2011] [07:06:58] <private_meta>	Well, not that hard, I don't quite like steak
| [Tuesday 22 February 2011] [07:07:10] <pieterh>	even better then... :-)
| [Tuesday 22 February 2011] [07:07:30] <pieterh>	general rule with 0MQ is, if there's something you think could work better, make it happen
| [Tuesday 22 February 2011] [07:07:53] <pieterh>	you can take the C code and wrap it as C++ very easily IMO
| [Tuesday 22 February 2011] [07:07:55] <private_meta>	I wouldn't know how
| [Tuesday 22 February 2011] [07:08:09] <pieterh>	you are working in what language?
| [Tuesday 22 February 2011] [07:08:18] <private_meta>	C++
| [Tuesday 22 February 2011] [07:08:58] <pieterh>	did you read the zmsg.c code yet?
| [Tuesday 22 February 2011] [07:10:34] <private_meta>	nope
| [Tuesday 22 February 2011] [07:10:58] <private_meta>	Well, isn't there a zmsg.cpp already?
| [Tuesday 22 February 2011] [07:12:07] <pieterh>	private_meta: please read both those files, then come back...
| [Tuesday 22 February 2011] [07:13:44] <pieterh>	you have three choices, when it comes to getting functionality in 0MQ (or any software)
| [Tuesday 22 February 2011] [07:13:48] <pieterh>	1. pay for it and get it soon
| [Tuesday 22 February 2011] [07:14:00] <private_meta>	2. don't pay and wait
| [Tuesday 22 February 2011] [07:14:02] <pieterh>	2. wait until someone else makes it and shares it, then get it for free
| [Tuesday 22 February 2011] [07:14:02] <private_meta>	3. do it yourself
| [Tuesday 22 February 2011] [07:14:08] <pieterh>	exactly
| [Tuesday 22 February 2011] [07:14:14] <pieterh>	:-)
| [Tuesday 22 February 2011] [07:14:31] <pieterh>	in this case I've made it really, really easy for you...
| [Tuesday 22 February 2011] [07:14:43] <private_meta>	seen an interesting venn diagram for that
| [Tuesday 22 February 2011] [07:14:49] <pieterh>	since you can literally take the C code (already designed as a class), wrap it with (I'd guess 20 lines of C++ code)
| [Tuesday 22 February 2011] [07:14:55] <pieterh>	and get what you need
| [Tuesday 22 February 2011] [07:14:56] <stimpie>	the file: examples/Java/psenvsub.java contains some garbage at the end 
| [Tuesday 22 February 2011] [07:15:22] <pieterh>	stimpie: indeed, it seems chopped off...
| [Tuesday 22 February 2011] [07:16:53] <pieterh>	stimpie: ah, I see what you mean
| [Tuesday 22 February 2011] [07:17:02] <pieterh>	ok, fixing that, I found the original contribution
| [Tuesday 22 February 2011] [07:17:40] <pieterh>	stimpie: fixed, thanks!
| [Tuesday 22 February 2011] [07:17:43] <stimpie>	np
| [Tuesday 22 February 2011] [07:26:24] <private_meta>	just out of curiosity, don't have time at the moment, let's say i want to improve zmq by adding convenience methods for send/recv for c++, let's say for strings, would that be worth considering it?
| [Tuesday 22 February 2011] [07:28:07] <stimpie>	private_meta, what is wrong with send(msg.toBytes())?
| [Tuesday 22 February 2011] [07:28:08] <pieterh>	private_meta: it would not go into the core
| [Tuesday 22 February 2011] [07:28:44] <pieterh>	private_meta: if all you want is send/recv string, it's already in zhelpers.hpp
| [Tuesday 22 February 2011] [07:29:43] <pieterh>	//  Convert string to 0MQ string and send to socket
| [Tuesday 22 February 2011] [07:29:43] <pieterh>	static bool
| [Tuesday 22 February 2011] [07:29:43] <pieterh>	s_send (zmq::socket_t & socket, const std::string & string) {
| [Tuesday 22 February 2011] [07:29:43] <pieterh>	    zmq::message_t message(string.size());
| [Tuesday 22 February 2011] [07:29:43] <pieterh>	    memcpy(message.data(), string.data(), string.size());
| [Tuesday 22 February 2011] [07:29:44] <pieterh>	    bool rc = socket.send(message);
| [Tuesday 22 February 2011] [07:29:44] <pieterh>	    return (rc);
| [Tuesday 22 February 2011] [07:29:45] <pieterh>	}
| [Tuesday 22 February 2011] [07:30:18] <private_meta>	oh, I've already seen that. By the way, why do you use memcpy there and not rebuild?
| [Tuesday 22 February 2011] [07:38:34] <private_meta>	argh... the disabled copy constructor is annoying, I can't even return a message_t object from a function
| [Tuesday 22 February 2011] [08:08:45] <pieterh>	private_meta: that code was written by Olivier Chamoux afair
| [Tuesday 22 February 2011] [08:09:46] <private_meta>	The example code carries that name as well
| [Tuesday 22 February 2011] [08:10:35] <private_meta>	According to a comment in the source it's to avoid "shared messages", which seems to be a somewhat valid argument if you tried to use it for that, but it's annoying if you want to return a message by a function
| [Tuesday 22 February 2011] [08:11:11] <pieterh>	sure
| [Tuesday 22 February 2011] [10:24:33] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r43e8868 10/ (24 files): 
| [Tuesday 22 February 2011] [10:24:33] <CIA-21>	zeromq2: Added explicit error message in case of memory exhaustion
| [Tuesday 22 February 2011] [10:24:33] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/eVM1AS
| [Tuesday 22 February 2011] [11:00:38] <amacleod>	Are there any plans to have language-native ZMQ libraries, rather than wrapping C++ libs?
| [Tuesday 22 February 2011] [11:01:25] <amacleod>	I guess maintaining parallel language-native libs would be a much bigger maintenance load.
| [Tuesday 22 February 2011] [11:08:57] <pieterh>	amacleod: it's a lot of work unless there's a real payoff, e.g. languages that can't link to C++
| [Tuesday 22 February 2011] [11:09:16] <pieterh>	you would not reach a similar level of performance and functionality
| [Tuesday 22 February 2011] [11:09:36] <pieterh>	it's been discussed, we would need to document the wire level protocols properly first
| [Tuesday 22 February 2011] [11:10:07] <amacleod>	pieterh, hm, yeah, good point.  And I guess the hassle of linking, for example, JNI libraries in Java, is pretty much a one-time configuration thing.
| [Tuesday 22 February 2011] [11:10:23] <pieterh>	plus you always get the latest/greatest 0MQ, etc.
| [Tuesday 22 February 2011] [11:10:24] <amacleod>	pieterh, well, documenting the wire level protocols sounds like a good idea anyway. :-D
| [Tuesday 22 February 2011] [11:10:38] <pieterh>	yes, when someone actually wants it... :-)
| [Tuesday 22 February 2011] [11:11:01] <amacleod>	pieterh, by the way, where can I look at the new router/dealer example you made?
| [Tuesday 22 February 2011] [11:11:29] <pieterh>	amacleod: hang on, I'll rebuild the Guide...
| [Tuesday 22 February 2011] [11:11:36] <amacleod>	Thanks.
| [Tuesday 22 February 2011] [11:16:05] <pieterh>	hmm, Wikidot seems to cache the old text for a while...
| [Tuesday 22 February 2011] [11:17:06] <pieterh>	oops, error in my upload robot, it's sending the content to the wrong place...
| [Tuesday 22 February 2011] [11:17:32] <amacleod>	Silly robot.
| [Tuesday 22 February 2011] [11:18:21] <pieterh>	ok, here: http://zguide.zeromq.org/chapter:all#toc51
| [Tuesday 22 February 2011] [11:19:04] <ljackson>	pieterh, got that code working last night, thx for your help
| [Tuesday 22 February 2011] [11:19:18] <pieterh>	ljackson: np
| [Tuesday 22 February 2011] [11:19:30] <ljackson>	pieterh, silly mistake of not de-ref on the work/clients sockets before sending to the queue device
| [Tuesday 22 February 2011] [11:19:39] <ljackson>	odd that the api took that tho
| [Tuesday 22 February 2011] [11:20:02] <pieterh>	ljackson: what language binding?
| [Tuesday 22 February 2011] [11:20:06] <ljackson>	who maintains the c++ api for zeromq ? Maybe I could extend to accept socket pointers and ask for a pull request ?
| [Tuesday 22 February 2011] [11:20:21] <pieterh>	ah, yes, I'm sure the maintainers will welcome contributions
| [Tuesday 22 February 2011] [11:20:30] <amacleod>	"Worked Example: Inter-Broker Routing", right?
| [Tuesday 22 February 2011] [11:20:42] <pieterh>	amacleod: "Asynchronous Client-Server"...
| [Tuesday 22 February 2011] [11:20:52] <pieterh>	reload that page
| [Tuesday 22 February 2011] [11:21:19] <amacleod>	Ah, ok.
| [Tuesday 22 February 2011] [11:21:41] <amacleod>	Looks like it renders as #toc50 for me.
| [Tuesday 22 February 2011] [11:22:17] <pieterh>	caching issue perhaps
| [Tuesday 22 February 2011] [11:22:25] <amacleod>	Yeah.. I think I'm still getting the old version.
| [Tuesday 22 February 2011] [11:22:41] <pieterh>	do you see figure 46 "Asynchronous Client Server" ?
| [Tuesday 22 February 2011] [11:22:48] <amacleod>	Yeah.. I see the diagram.
| [Tuesday 22 February 2011] [11:22:54] <pieterh>	ok, then that's all good
| [Tuesday 22 February 2011] [11:23:34] <amacleod>	The next code sample is router-to-router, though...
| [Tuesday 22 February 2011] [11:24:08] <pieterh>	does it not show the asyncsrv example?
| [Tuesday 22 February 2011] [11:24:29] <pieterh>	ah, diagrams are accurate but text is out of date...
| [Tuesday 22 February 2011] [11:24:34] <pieterh>	reload, reload, reload!
| [Tuesday 22 February 2011] [11:24:41] <amacleod>	Nope.  It's a little incongruous, actually... :)
| [Tuesday 22 February 2011] [11:24:49] <amacleod>	aha.. there it is!
| [Tuesday 22 February 2011] [11:25:28] <pieterh>	enjoy, amacleod, and let me know if it's helpful
| [Tuesday 22 February 2011] [11:25:39] <pieterh>	it was quite fun making this pattern
| [Tuesday 22 February 2011] [11:25:43] <amacleod>	Sure thing.  :)
| [Tuesday 22 February 2011] [11:27:44] <amacleod>	Could the client_task use blocking recv rather than polling, or is the polling crucial?
| [Tuesday 22 February 2011] [11:28:29] <pieterh>	amacleod: if you want to send a mix of requests and replies, it can't block on recv
| [Tuesday 22 February 2011] [11:28:48] <pieterh>	you can't have a separate thread doing the receiving
| [Tuesday 22 February 2011] [11:29:08] <pieterh>	it can use a simpler poll than the one I made, that's to ensure requests are sent on time
| [Tuesday 22 February 2011] [11:30:14] <pieterh>	brb, lunch...
| [Tuesday 22 February 2011] [11:34:55] <CIA-21>	zeromq2: 03Martin Sustrik 07sub-forward * r977f5b7 10/ (5 files): 
| [Tuesday 22 February 2011] [11:34:55] <CIA-21>	zeromq2: Trie-based matcher (ptrie_t) implemented.
| [Tuesday 22 February 2011] [11:34:55] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/gSZiWK
| [Tuesday 22 February 2011] [12:31:46] <cremes>	is there any technique for detecting a slow subscriber? e.g. check queue sizes on netstat or something?
| [Tuesday 22 February 2011] [12:32:12] <cremes>	i have a pub socket that has a dozen or so subscribers; my memory usage slowly climbs even though i don't have any leaks
| [Tuesday 22 February 2011] [12:32:40] <cremes>	i now suspect a slow subscriber isn't pulling stuff off the queue quickly enough and it's backing up at the publisher (HWM is default)
| [Tuesday 22 February 2011] [12:44:55] <pieterh>	cremes: there's zmq_getsockopt (..ZMQ_BACKLOG)
| [Tuesday 22 February 2011] [12:46:15] <cremes>	is that really appropriate? that just controls the queue of initial connects/binds
| [Tuesday 22 February 2011] [12:46:31] <cremes>	it doesn't have anything to do with message queue length, right?
| [Tuesday 22 February 2011] [12:46:37] <pieterh>	oops
| [Tuesday 22 February 2011] [12:46:50] <cremes>	:)
| [Tuesday 22 February 2011] [12:47:22] <pieterh>	so there's no way to know what's happening at the level of individual subscribers...
| [Tuesday 22 February 2011] [12:47:39] <pieterh>	do you number your messages?
| [Tuesday 22 February 2011] [12:47:52] <cremes>	no but they do get a timestamp
| [Tuesday 22 February 2011] [12:47:58] <nooob>	you might want to setup a connection from the subscriber back to the sender
| [Tuesday 22 February 2011] [12:48:00] <cremes>	so they are sequential
| [Tuesday 22 February 2011] [12:48:01] <pieterh>	ok, even better
| [Tuesday 22 February 2011] [12:48:15] <pieterh>	in the subscriber, check how old incoming messages are
| [Tuesday 22 February 2011] [12:48:28] <pieterh>	if you exceed X seconds, send an alert to your system console
| [Tuesday 22 February 2011] [12:48:29] <nooob>	there was a pattern like that in the guide
| [Tuesday 22 February 2011] [12:48:39] <cremes>	hmmm, that doesn't seem like it would help unless i misunderstand how the pub socket queueing works
| [Tuesday 22 February 2011] [12:48:59] <cremes>	there is a separate outgoing queue for each subscriber on a pub socket, yes?
| [Tuesday 22 February 2011] [12:49:12] <pieterh>	cremes: if your pubsub system is stable, subscribers will get messages with predictably low delays
| [Tuesday 22 February 2011] [12:49:13] <cremes>	so fast subscribers would have a small or empty queue while my slow guy would have a large queue
| [Tuesday 22 February 2011] [12:49:30] <pieterh>	it's running over TCP?
| [Tuesday 22 February 2011] [12:49:33] <cremes>	yes
| [Tuesday 22 February 2011] [12:49:43] <pieterh>	even over PGM...
| [Tuesday 22 February 2011] [12:49:53] <pieterh>	slow subscribers will by definition :-) get messages 'too slowly'
| [Tuesday 22 February 2011] [12:50:05] <pieterh>	timestamp checking should do it
| [Tuesday 22 February 2011] [12:50:19] <cremes>	i will check that out
| [Tuesday 22 February 2011] [12:50:35] <pieterh>	i like the pattern, will try a quick implementation
| [Tuesday 22 February 2011] [13:12:09] <cremes>	pieterh: question...
| [Tuesday 22 February 2011] [13:12:16] <pieterh>	cremes: shoot...
| [Tuesday 22 February 2011] [13:12:28] <cremes>	i wrote an example where i have a single publisher that connects to a forwarder device
| [Tuesday 22 February 2011] [13:12:32] <cremes>	it publishes as fast as it can
| [Tuesday 22 February 2011] [13:12:41] <cremes>	there are no subscribers connected to the device
| [Tuesday 22 February 2011] [13:12:51] <cremes>	i see memory growing rapidly; is that expected?
| [Tuesday 22 February 2011] [13:12:58] <pieterh>	depends...
| [Tuesday 22 February 2011] [13:13:04] <pieterh>	running on the same box?
| [Tuesday 22 February 2011] [13:13:09] <cremes>	yeah
| [Tuesday 22 February 2011] [13:13:13] <pieterh>	one core?
| [Tuesday 22 February 2011] [13:13:25] <cremes>	dual quad, 16gb memory... beefy box
| [Tuesday 22 February 2011] [13:13:34] <pieterh>	no, then it's not expected
| [Tuesday 22 February 2011] [13:13:43] <cremes>	ok
| [Tuesday 22 February 2011] [13:13:49] <pieterh>	is the memory growing in the publisher or in the forwarder?
| [Tuesday 22 February 2011] [13:13:52] <cremes>	i'm going to try and replicate this with the C forwarder
| [Tuesday 22 February 2011] [13:13:57] <cremes>	it grows in the forwarder
| [Tuesday 22 February 2011] [13:14:10] <pieterh>	how about CPU usage?
| [Tuesday 22 February 2011] [13:14:21] <cremes>	high
| [Tuesday 22 February 2011] [13:14:25] <pieterh>	ok, try this
| [Tuesday 22 February 2011] [13:14:34] <pieterh>	- publish 20M messages, then pause for 10 seconds
| [Tuesday 22 February 2011] [13:14:36] <pieterh>	- repeat
| [Tuesday 22 February 2011] [13:14:46] <cremes>	ok
| [Tuesday 22 February 2011] [13:14:48] <pieterh>	see if memory usage remains high during that pause
| [Tuesday 22 February 2011] [13:14:56] <pieterh>	if so, forwarder is broken somehow
| [Tuesday 22 February 2011] [13:15:10] <pieterh>	if it comes down, it's just queuing bizarreness
| [Tuesday 22 February 2011] [13:28:07] <sustrik>	with a single incoming streams and many outgoing streams you would expect the latter to be bandwidth-bound and thus slower than the former
| [Tuesday 22 February 2011] [13:28:38] <sustrik>	consequently, in congestion situations you should expect messages queueing in the forwarder
| [Tuesday 22 February 2011] [13:38:42] <pieterh>	sustrik: yes, but here there are no subscribers on the forwarder...
| [Tuesday 22 February 2011] [13:39:14] <sustrik_>	ah
| [Tuesday 22 February 2011] [13:40:28] <sustrik_>	i've missed that
| [Tuesday 22 February 2011] [13:41:26] <sustrik_>	then the queue's main loop must be slower then message receiving in its SUB socket
| [Tuesday 22 February 2011] [13:41:38] <sustrik_>	in any case, when doing congestion tests
| [Tuesday 22 February 2011] [13:41:40] <sustrik_>	use hwm
| [Tuesday 22 February 2011] [13:41:55] <sustrik_>	otherwise you are inevitable going to run out of memory
| [Tuesday 22 February 2011] [13:52:00] <pieterh>	hmm, forwarder should run at least as fast as publisher in this case...
| [Tuesday 22 February 2011] [13:52:34] <pieterh>	let's see if cremes comes back with more data
| [Tuesday 22 February 2011] [13:52:45] <cremes>	when there are no subscribers attached to the forwarder, calls to zmq_send() should just close the msg and drop it, right?
| [Tuesday 22 February 2011] [13:53:38] <pieterh>	cremes: ack
| [Tuesday 22 February 2011] [13:53:56] <pieterh>	did you try that run/pause/run/pause ?
| [Tuesday 22 February 2011] [13:55:39] <cremes>	yes, the memory did not shrink
| [Tuesday 22 February 2011] [13:56:25] <pieterh>	did _not_ shrink?
| [Tuesday 22 February 2011] [13:56:28] <pieterh>	then it's a real leak
| [Tuesday 22 February 2011] [13:56:55] <cremes>	i need to try this with the C forwarder device that comes with the lib
| [Tuesday 22 February 2011] [13:57:01] <cremes>	and see if it behaves the same
| [Tuesday 22 February 2011] [13:57:05] <pieterh>	yes
| [Tuesday 22 February 2011] [13:57:19] <cremes>	i'll open a ticket if i see it replicated
| [Tuesday 22 February 2011] [13:57:22] <pieterh>	i just reviewed the code for that, there is zero chance it leaks memory
| [Tuesday 22 February 2011] [13:57:32] <cremes>	right, it's so simple there is *no* way
| [Tuesday 22 February 2011] [13:57:36] <cremes>	<sigh>
| [Tuesday 22 February 2011] [13:57:57] <pieterh>	if there's a leak it's either in the pub socket (unlikely), or the binding (possible), or it's a heap artifact (plausible)
| [Tuesday 22 February 2011] [13:58:10] <pieterh>	sometimes the heap does not shrink immediately when memory is freed
| [Tuesday 22 February 2011] [13:58:45] <pieterh>	try setting a HWM of, say, 100K on the publisher and see what effect that has
| [Tuesday 22 February 2011] [13:58:53] <pieterh>	s/publisher/forwarder/ sorry
| [Tuesday 22 February 2011] [13:59:06] <pieterh>	on the frontend socket, initially
| [Tuesday 22 February 2011] [13:59:11] <cremes>	yes, i'll keep at it
| [Tuesday 22 February 2011] [14:05:59] <amacleod>	pieterh, my problem from yesterday does seem to be a threading issue.  When I changed my test harness (which simulates a client) to use a separate context from the server, the messages got through correctly in both directions.
| [Tuesday 22 February 2011] [14:06:26] <amacleod>	However, now I'm seeing "Assertion failed: pending_term_acks" when closing the socket.
| [Tuesday 22 February 2011] [14:06:27] <pieterh>	amacleod: ah, good... I've also been using separate contexts for each 'task' when it simulates a separate process
| [Tuesday 22 February 2011] [14:06:48] <pieterh>	that's not a 0MQ assertion...
| [Tuesday 22 February 2011] [14:07:04] <amacleod>	It lists it as socket_base.cpp:690
| [Tuesday 22 February 2011] [14:07:18] <amacleod>	It's hard for me to debug, because it doesn't generate a Java exception, it just kills the process.
| [Tuesday 22 February 2011] [14:07:54] <pieterh>	what version of 0MQ are you on?
| [Tuesday 22 February 2011] [14:07:56] <amacleod>	Might be jzmq, hmm..
| [Tuesday 22 February 2011] [14:07:58] <amacleod>	2.0.10
| [Tuesday 22 February 2011] [14:08:08] <pieterh>	any problem upgrading to master?
| [Tuesday 22 February 2011] [14:08:19] <pieterh>	there are a lot of fixes since 2.0.10
| [Tuesday 22 February 2011] [14:09:28] <pieterh>	sustrik: do you keep any log of major changes made apart from the git commit history?
| [Tuesday 22 February 2011] [14:09:37] <amacleod>	Depends--how stable is 2.1?  I think we chose 2.0.10 because we wanted not to use the "development" branch.
| [Tuesday 22 February 2011] [14:10:21] <pieterh>	amacleod: for various reasons, the git master is significantly more stable than the 'stable'
| [Tuesday 22 February 2011] [14:10:31] <pieterh>	... than the 'stable' 2.0.10 release
| [Tuesday 22 February 2011] [14:10:58] <amacleod>	Hmm. :)  Might be worth the switch, then.
| [Tuesday 22 February 2011] [14:11:00] <sustrik_>	btw, the assertion is in code that was complately rewritten in 2.1
| [Tuesday 22 February 2011] [14:11:09] <amacleod>	sustrik, good to know.
| [Tuesday 22 February 2011] [14:11:10] <pieterh>	we're in the slow process of making a formal release for 2.1.11
| [Tuesday 22 February 2011] [14:11:28] <pieterh>	sustrik: the one thing that will be problematic is making release notes
| [Tuesday 22 February 2011] [14:11:30] <sustrik_>	pieterh: what log?
| [Tuesday 22 February 2011] [14:11:41] <sustrik_>	why so?
| [Tuesday 22 February 2011] [14:11:41] <pieterh>	i was afraid of that...
| [Tuesday 22 February 2011] [14:11:44] <sustrik_>	it's automatic
| [Tuesday 22 February 2011] [14:12:02] <pieterh>	what's automatic is a dump of every commit message
| [Tuesday 22 February 2011] [14:12:07] <sustrik_>	yup
| [Tuesday 22 February 2011] [14:12:09] <amacleod>	https://github.com/zeromq/zeromq2/raw/master/NEWS
| [Tuesday 22 February 2011] [14:12:11] <pieterh>	that is not release notes
| [Tuesday 22 February 2011] [14:12:27] <pieterh>	nope, NEWS is painfully made by hand
| [Tuesday 22 February 2011] [14:12:29] <sustrik_>	ah, i'll go through the commit messages and write the release notes
| [Tuesday 22 February 2011] [14:12:31] <sustrik_>	not a problem
| [Tuesday 22 February 2011] [14:12:36] <pieterh>	excellent...!
| [Tuesday 22 February 2011] [14:12:50] <pieterh>	then IMO we're ready to break off the branch...
| [Tuesday 22 February 2011] [14:13:02] <pieterh>	there were zero issues porting the Guide examples to 2.1.11
| [Tuesday 22 February 2011] [14:13:07] <sustrik_>	there are some pgm problems being experienced with head currently
| [Tuesday 22 February 2011] [14:13:32] <pieterh>	that's ok, we'll have at least a couple of weeks to stabilize
| [Tuesday 22 February 2011] [14:13:48] <amacleod>	In the mean time, if we assume I cannot presently upgrade from 2.0.10, any suggestion on where I should look to prevent this assertion from failing?
| [Tuesday 22 February 2011] [14:13:56] <pieterh>	the key now IMO is to get a formal package out so folks like amacleod use the current master, not old code
| [Tuesday 22 February 2011] [14:14:57] <pieterh>	sustrik_, so I'm going to create a separate git but this is somewhat experimental
| [Tuesday 22 February 2011] [14:14:58] <amacleod>	As far as I know, jzmq is set up to handle both 2.0.10 and 2.1.x, so upgrading shouldn't be too painful.
| [Tuesday 22 February 2011] [14:15:10] <sustrik_>	the only thing preventing branching off right now is the pgm problem
| [Tuesday 22 February 2011] [14:15:16] <pieterh>	amacleod: at least, try on the 2.1.x master so you know whether it works better or not
| [Tuesday 22 February 2011] [14:15:32] <sustrik_>	i can't help with that :|
| [Tuesday 22 February 2011] [14:15:49] <sustrik_>	so we'll have to wait while someone fixes it
| [Tuesday 22 February 2011] [14:15:54] <pieterh>	sustrik_ steve's traveling right now
| [Tuesday 22 February 2011] [14:16:01] <pieterh>	we'll pipeline it all
| [Tuesday 22 February 2011] [14:16:10] <sustrik_>	or, alternatively, you can branch from a historic version
| [Tuesday 22 February 2011] [14:16:11] <pieterh>	pgm fixes can come in after we branch
| [Tuesday 22 February 2011] [14:16:24] <pieterh>	it's good to have known issues so we can prove that the process works
| [Tuesday 22 February 2011] [14:16:29] <sustrik_>	right, you can branch a backport the ix
| [Tuesday 22 February 2011] [14:16:31] <sustrik_>	fix
| [Tuesday 22 February 2011] [14:16:31] <pieterh>	yes
| [Tuesday 22 February 2011] [14:17:04] <pieterh>	do you want to push any code before I clone the repo?
| [Tuesday 22 February 2011] [14:17:11] <sustrik_>	no
| [Tuesday 22 February 2011] [14:17:14] <sustrik_>	do it now
| [Tuesday 22 February 2011] [14:17:18] <pieterh>	okay... going for it :-)
| [Tuesday 22 February 2011] [14:17:29] <sustrik_>	amacleod: upgrading should not be painful
| [Tuesday 22 February 2011] [14:17:50] <sustrik_>	trying to fix the problem in 2.0.10 is going to be painful
| [Tuesday 22 February 2011] [14:18:00] <amacleod>	Hm, I think you are right.
| [Tuesday 22 February 2011] [14:18:09] <sustrik_>	it's a problem with shutdown subsystem
| [Tuesday 22 February 2011] [14:18:18] <sustrik_>	which was pretty creaky in 2.0.x
| [Tuesday 22 February 2011] [14:18:39] <sustrik_>	it was one of the major reasons for making 2.1
| [Tuesday 22 February 2011] [14:18:50] <amacleod>	So, which version should I get?  The 2.1.0 package from the front page?
| [Tuesday 22 February 2011] [14:19:03] <sustrik_>	yes
| [Tuesday 22 February 2011] [14:24:11] <pieterh>	hmm, anyone know how to clone a github repository and _keep_ it in the same organization?
| [Tuesday 22 February 2011] [14:24:28] <pieterh>	I'm sure I'm missing something obvious...
| [Tuesday 22 February 2011] [14:33:21] <pieterh>	hmm, git push -u, obviously... duh
| [Tuesday 22 February 2011] [14:40:19] <pieterh>	sustrik_: okaaay, I think that's done... we now have http://github.com/zeromq/zeromq2-1
| [Tuesday 22 February 2011] [14:40:42] <pieterh>	just the master branch and no tracking between the two gits, I hope
| [Tuesday 22 February 2011] [14:43:26] <pieterh>	sustrik_: next step is to make release notes (you) and then packages (me)
| [Tuesday 22 February 2011] [14:49:05] <sustrik_>	ok
| [Tuesday 22 February 2011] [14:49:14] <sustrik_>	let me see
| [Tuesday 22 February 2011] [14:53:46] <pieterh>	I suggest we edit the NEWS together at http://piratepad.net/, then commit to (the real) master
| [Tuesday 22 February 2011] [14:54:03] <sustrik>	yes
| [Tuesday 22 February 2011] [14:54:07] <sustrik>	wait a sec
| [Tuesday 22 February 2011] [14:56:16] <pieterh>	I'd like to make 2-3 release candidates over 2-3 weeks
| [Tuesday 22 February 2011] [14:56:32] <pieterh>	http://piratepad.net/dkenb33ThF
| [Tuesday 22 February 2011] [14:57:54] <pieterh>	I think we have enough momentum to get rapid feedback on releases
| [Tuesday 22 February 2011] [14:58:43] <pieterh>	the one problem I see with this approach is we don't get a branch for the stable release, automatically, in the real git
| [Tuesday 22 February 2011] [14:59:11] <pieterh>	s/branch/tag/
| [Tuesday 22 February 2011] [14:59:30] <pieterh>	mato's going to cut my throat...
| [Tuesday 22 February 2011] [15:05:07] <sustrik>	what's the problem?
| [Tuesday 22 February 2011] [15:05:12] <sustrik>	it's DCVS
| [Tuesday 22 February 2011] [15:05:29] <sustrik>	so it shouldn't matter whether it's a branch or a separate repo
| [Tuesday 22 February 2011] [15:05:39] <sustrik>	DVCS*
| [Tuesday 22 February 2011] [15:05:50] <sustrik>	pieterh: still there
| [Tuesday 22 February 2011] [15:05:51] <pieterh>	ok, allow for the fact that any gross git manipulations leave me nervous
| [Tuesday 22 February 2011] [15:05:52] <sustrik>	?
| [Tuesday 22 February 2011] [15:06:03] <pieterh>	I find the tool 10x too complex and dangerous, so...
| [Tuesday 22 February 2011] [15:06:25] <pieterh>	I'd much prefer to work with a copy of the repository (not a clone or a fork)
| [Tuesday 22 February 2011] [15:06:40] <pieterh>	advantages: anyone can imitate this, make releases, safely
| [Tuesday 22 February 2011] [15:06:56] <sustrik>	you mean you've created a new repo?
| [Tuesday 22 February 2011] [15:06:59] <pieterh>	yes
| [Tuesday 22 February 2011] [15:07:05] <sustrik>	i.e. deleted the entire history?
| [Tuesday 22 February 2011] [15:07:14] <pieterh>	 http://github.com/zeromq/zeromq2-1
| [Tuesday 22 February 2011] [15:07:22] <pieterh>	I was able to copy the master branch
| [Tuesday 22 February 2011] [15:07:34] <pieterh>	which is fine for my purposes (stabilization)
| [Tuesday 22 February 2011] [15:07:43] <sustrik>	github seems to be dead
| [Tuesday 22 February 2011] [15:07:48] <pieterh>	it wasn't me!!!!!
| [Tuesday 22 February 2011] [15:07:52] <sustrik>	:)))
| [Tuesday 22 February 2011] [15:08:12] <pieterh>	i'd *much* prefer to work with readonly access to the real repository
| [Tuesday 22 February 2011] [15:08:42] <sustrik>	let's move to piratepad now
| [Tuesday 22 February 2011] [15:08:47] <pieterh>	but problem is, separate repository breaks the neat history of version tags in the real repo
| [Tuesday 22 February 2011] [15:09:02] <pieterh>	piratepad seems unreliable right now...
| [Tuesday 22 February 2011] [15:09:17] <sustrik>	yuck
| [Tuesday 22 February 2011] [15:09:19] <cremes>	ok, i can reproduce the memory "leak"; it is somewhat complicated and it's not a real leak... it's more like a DDOS
| [Tuesday 22 February 2011] [15:09:27] <sustrik>	anyway, there are just 2 items
| [Tuesday 22 February 2011] [15:09:35] <sustrik>	ZMQ_RECONNECT_IVL_MAX
| [Tuesday 22 February 2011] [15:09:41] <sustrik>	and
| [Tuesday 22 February 2011] [15:09:42] <sustrik>	ZMQ_RECOVERY_IVL_MSEC
| [Tuesday 22 February 2011] [15:09:50] <sustrik>	+ the bug fixes
| [Tuesday 22 February 2011] [15:10:45] <sustrik>	you can get description for both from zmq_setsockopt(3)
| [Tuesday 22 February 2011] [15:10:52] <pieterh>	indeed
| [Tuesday 22 February 2011] [15:11:04] <pieterh>	I'll do that, np
| [Tuesday 22 February 2011] [15:11:12] <sustrik>	it's easy this time
| [Tuesday 22 February 2011] [15:11:19] <pieterh>	"An automatic restart of Piratepad will occur in-31945seconds."
| [Tuesday 22 February 2011] [15:11:21] <pieterh>	good god
| [Tuesday 22 February 2011] [15:11:34] <sustrik>	they are pirates, you know
| [Tuesday 22 February 2011] [15:11:37] <pieterh>	We killed Piratepad...
| [Tuesday 22 February 2011] [15:11:38] <sustrik>	not exactly precise
| [Tuesday 22 February 2011] [15:11:45] <pieterh>	Well, Google bought etherpad and then shut it down...
| [Tuesday 22 February 2011] [15:12:15] <sustrik>	anyway
| [Tuesday 22 February 2011] [15:12:28] <sustrik>	anything else missing for making the stable branch?
| [Tuesday 22 February 2011] [15:13:30] <pieterh>	not for me
| [Tuesday 22 February 2011] [15:13:35] <sustrik>	good
| [Tuesday 22 February 2011] [15:13:36] <pieterh>	but did you understand my concern?
| [Tuesday 22 February 2011] [15:13:41] <sustrik>	which one?
| [Tuesday 22 February 2011] [15:13:52] <pieterh>	we're breaking the master/maint process
| [Tuesday 22 February 2011] [15:14:12] <pieterh>	smashing it into little pieces
| [Tuesday 22 February 2011] [15:14:22] <sustrik>	yes
| [Tuesday 22 February 2011] [15:14:37] <sustrik>	the problem is the maint was not really well maintained anyway
| [Tuesday 22 February 2011] [15:14:43] <pieterh>	since I personally dislike that process and find it complex and bizarre, I'm happy with that
| [Tuesday 22 February 2011] [15:15:02] <pieterh>	I'd like a process that takes 30 seconds to fully understand
| [Tuesday 22 February 2011] [15:15:11] <pieterh>	on a cold monday morning before coffee
| [Tuesday 22 February 2011] [15:15:18] <sustrik>	i think it's the same now
| [Tuesday 22 February 2011] [15:16:02] <sustrik>	patches being passed between branches
| [Tuesday 22 February 2011] [15:16:16] <sustrik>	ah, one point
| [Tuesday 22 February 2011] [15:16:26] <sustrik>	have a look how version numbers are to be maintained
| [Tuesday 22 February 2011] [15:16:55] <sustrik>	it's important not to mess that up
| [Tuesday 22 February 2011] [15:17:32] <pieterh>	I still don't remember how changes flow from maint to master and vice-versa
| [Tuesday 22 February 2011] [15:17:47] <pieterh>	so if this works, what we'll get are a series of stand-alone gits, zeromq2-1, zeromq2-2, zeromq3-0, each with their own maintainer(s)
| [Tuesday 22 February 2011] [15:17:48] <pieterh>	and pull requests with patches between them
| [Tuesday 22 February 2011] [15:17:48] <pieterh>	each being copied off the real repo as that heads towards stability
| [Tuesday 22 February 2011] [15:18:30] <sustrik>	it works both ways
| [Tuesday 22 February 2011] [15:18:31] <pieterh>	the version numbering works properly IMO
| [Tuesday 22 February 2011] [15:18:35] <amacleod>	:-( Now jzmq tests are hung forever in Context.finalize
| [Tuesday 22 February 2011] [15:18:37] <pieterh>	next releases will be 2.1.1, 2.1.2, 2.1.3...
| [Tuesday 22 February 2011] [15:18:46] <sustrik>	1. backporting patches from master to maint(s)
| [Tuesday 22 February 2011] [15:18:56] <sustrik>	2. upstreaming patches from maint(s) to master
| [Tuesday 22 February 2011] [15:19:12] <pieterh>	I'd assume 2.1.3 will be the stable one if people find bugs
| [Tuesday 22 February 2011] [15:19:42] <pieterh>	yes
| [Tuesday 22 February 2011] [15:19:43] <pieterh>	I'd veto that
| [Tuesday 22 February 2011] [15:19:43] <pieterh>	upstreaming patches from temporary clones of maint(s) to master
| [Tuesday 22 February 2011] [15:19:43] <pieterh>	at least in my view... for now...
| [Tuesday 22 February 2011] [15:19:47] <pieterh>	anyhow, yes, if it makes sense
| [Tuesday 22 February 2011] [15:19:50] <pieterh>	DCVS as you said
| [Tuesday 22 February 2011] [15:20:15] <pieterh>	each repo is largely independent and we work by protocol
| [Tuesday 22 February 2011] [15:20:29] <sustrik>	well, if you bugfix a patch for maint, you want to upstream it
| [Tuesday 22 February 2011] [15:20:42] <sustrik>	only thing it means is sending it to the ML
| [Tuesday 22 February 2011] [15:20:45] <sustrik>	no big deal
| [Tuesday 22 February 2011] [15:21:02] <pieterh>	if the bug is in the current master, I'd first want to get it fixed there
| [Tuesday 22 February 2011] [15:21:15] <pieterh>	because until it's gone past that filter, there's no guarantee it's sane
| [Tuesday 22 February 2011] [15:21:31] <pieterh>	if the bug is in old code, then there's no upstreaming anyhow
| [Tuesday 22 February 2011] [15:21:47] <sustrik>	it's up to you
| [Tuesday 22 February 2011] [15:22:02] <sustrik>	so you're going to reject patches to maint
| [Tuesday 22 February 2011] [15:22:04] <sustrik>	right?
| [Tuesday 22 February 2011] [15:22:15] <pieterh>	presumably, yes
| [Tuesday 22 February 2011] [15:22:19] <sustrik>	ok
| [Tuesday 22 February 2011] [15:22:22] <pieterh>	or at least treat them with scepticism
| [Tuesday 22 February 2011] [15:22:32] <pieterh>	the only person I trust for my patches is you
| [Tuesday 22 February 2011] [15:22:48] <sustrik>	ok, now for the versioning
| [Tuesday 22 February 2011] [15:22:48] <pieterh>	especially, especially on a stable release people rely on for production
| [Tuesday 22 February 2011] [15:22:55] <pieterh>	versioning... ok
| [Tuesday 22 February 2011] [15:23:09] <sustrik>	the process looks like this:
| [Tuesday 22 February 2011] [15:23:12] <pieterh>	s/you/the owner of the code in question/
| [Tuesday 22 February 2011] [15:23:26] <sustrik>	when about to make a release:
| [Tuesday 22 February 2011] [15:23:37] <sustrik>	1. update the version numbers in zmq.h
| [Tuesday 22 February 2011] [15:23:45] <sustrik>	2. make a release
| [Tuesday 22 February 2011] [15:23:52] <sustrik>	3. bump the version number
| [Tuesday 22 February 2011] [15:24:02] <pieterh>	right, http://www.zeromq.org/docs:procedures
| [Tuesday 22 February 2011] [15:24:08] <sustrik>	yes
| [Tuesday 22 February 2011] [15:24:15] <sustrik>	exactly the same process
| [Tuesday 22 February 2011] [15:24:17] <pieterh>	this would happen on the release git only
| [Tuesday 22 February 2011] [15:24:59] <sustrik>	are you saying you are not going to version the maint  branch?
| [Tuesday 22 February 2011] [15:25:09] <sustrik>	that's nonsense
| [Tuesday 22 February 2011] [15:25:14] <pieterh>	as far as I'm concerned, there is no maint branch
| [Tuesday 22 February 2011] [15:25:21] <sustrik>	maint repo
| [Tuesday 22 February 2011] [15:25:27] <sustrik>	no versions?
| [Tuesday 22 February 2011] [15:25:28] <pieterh>	ok, the terms are vital here
| [Tuesday 22 February 2011] [15:25:36] <pieterh>	let's call it the release git
| [Tuesday 22 February 2011] [15:25:42] <pieterh>	as compared to the master git 
| [Tuesday 22 February 2011] [15:25:47] <sustrik>	whatever
| [Tuesday 22 February 2011] [15:25:52] <sustrik>	what about versions?
| [Tuesday 22 February 2011] [15:25:59] <pieterh>	I'm going to tag the release git properly
| [Tuesday 22 February 2011] [15:26:22] <pieterh>	and version it properly, exactly as now
| [Tuesday 22 February 2011] [15:26:24] <sustrik>	change zmq.h as well
| [Tuesday 22 February 2011] [15:26:36] <pieterh>	exactly the same, but it all happens on my master branch
| [Tuesday 22 February 2011] [15:26:40] <sustrik>	otherwise users won't be able to find out what the version is
| [Tuesday 22 February 2011] [15:26:48] <sustrik>	(zmq_version(), version macros
| [Tuesday 22 February 2011] [15:26:59] <pieterh>	yes, all that is unambiguous
| [Tuesday 22 February 2011] [15:27:09] <pieterh>	the versioning is sane, obvious, necessary
| [Tuesday 22 February 2011] [15:27:19] <sustrik>	right, 3 steps
| [Tuesday 22 February 2011] [15:27:26] <sustrik>	tag
| [Tuesday 22 February 2011] [15:27:43] <sustrik>	release
| [Tuesday 22 February 2011] [15:27:45] <sustrik>	change version
| [Tuesday 22 February 2011] [15:27:48] <pieterh>	yes
| [Tuesday 22 February 2011] [15:27:49] <sustrik>	that's it
| [Tuesday 22 February 2011] [15:27:52] <sustrik>	ok
| [Tuesday 22 February 2011] [15:28:10] <pieterh>	and the final step is update the version in the development master
| [Tuesday 22 February 2011] [15:28:17] <sustrik>	so, i'm going to bump master to 2.2
| [Tuesday 22 February 2011] [15:28:18] <pieterh>	so it goes from 2.1.1 to 2.2.0
| [Tuesday 22 February 2011] [15:28:26] <sustrik>	yes, i'll do that now
| [Tuesday 22 February 2011] [15:28:36] <pieterh>	very excellent...!
| [Tuesday 22 February 2011] [15:28:43] <pieterh>	ok, I'm going to make a release now
| [Tuesday 22 February 2011] [15:28:47] <pieterh>	no time like the present
| [Tuesday 22 February 2011] [15:29:16] <sustrik>	cremes: sorry for the delay
| [Tuesday 22 February 2011] [15:29:26] <sustrik>	have you found out what's the problem?
| [Tuesday 22 February 2011] [15:29:34] <pieterh>	amacleod: sounds like there's a socket left open
| [Tuesday 22 February 2011] [15:29:51] <pieterh>	amacleod: sorry also for the delay
| [Tuesday 22 February 2011] [15:30:15] <amacleod>	Terminating a context will not finish if a socket is left open?
| [Tuesday 22 February 2011] [15:31:13] <pieterh>	amacleod: not in every case, but in some cases
| [Tuesday 22 February 2011] [15:31:19] <pieterh>	this is new behavior in 2.1
| [Tuesday 22 February 2011] [15:31:34] <pieterh>	a side-effect of zmq_term's determination to flush sockets safely
| [Tuesday 22 February 2011] [15:32:02] <pieterh>	if the socket is held by the same thread as calls zmq_term, it deadlocks (or something)
| [Tuesday 22 February 2011] [15:32:54] <amacleod>	Hmm, yeah.  It did look as though the Java finalizer was waiting on some things.
| [Tuesday 22 February 2011] [15:36:04] <pieterh>	sustrik: s/until/untill/ in zmq_setsockopt.txt...
| [Tuesday 22 February 2011] [15:37:06] <sustrik>	would you fix it in maint and upstram it to master or should i fix it in master and you'll backport it to the maint :)
| [Tuesday 22 February 2011] [15:38:19] <pieterh>	For a one-word fix... let me clone the git and send you a pull request with regression test case
| [Tuesday 22 February 2011] [15:38:27] <pieterh>	yeah :-) process!
| [Tuesday 22 February 2011] [15:40:15] <sustrik>	i love it :)
| [Tuesday 22 February 2011] [15:41:08] <pieterh>	what do you call sys://log? do we want to document that briefly?
| [Tuesday 22 February 2011] [15:41:16] <pieterh>	is it an internal transport?
| [Tuesday 22 February 2011] [15:41:17] <cremes>	sustrik: yes, i've discovered a problem; i am just finishing a second test of my hypothesis.... i'll share it in about 10m
| [Tuesday 22 February 2011] [15:41:47] <sustrik>	good god, everything is shutting down
| [Tuesday 22 February 2011] [15:41:58] <pieterh>	someone dropped the Internet!
| [Tuesday 22 February 2011] [15:42:11] <sustrik>	i suspect i'm in lybia
| [Tuesday 22 February 2011] [15:42:27] <pieterh>	I knew they should have left it safe with the Elders of the Internet at the top of Big Ben
| [Tuesday 22 February 2011] [15:43:04] <pieterh>	sustrik: funny, a friend of mine was supposed to be doing a rally in Libya just about now...
| [Tuesday 22 February 2011] [15:43:27] <sustrik>	let's hope he's not there really
| [Tuesday 22 February 2011] [15:43:54] <pieterh>	indeed, I asked him like two weeks ago, "you going before or after the revolution?", he lol'd
| [Tuesday 22 February 2011] [15:44:39] <fbarriga>	hi everyone
| [Tuesday 22 February 2011] [15:44:44] <fbarriga>	I've a little doubt
| [Tuesday 22 February 2011] [15:45:04] <sustrik>	yuck, github is totally braindead
| [Tuesday 22 February 2011] [15:45:14] <sustrik>	repos as well as the site
| [Tuesday 22 February 2011] [15:45:27] <pieterh>	fbarriga: hi, what's up?
| [Tuesday 22 February 2011] [15:45:53] <fbarriga>	hi pieterh , playing with the socket
| [Tuesday 22 February 2011] [15:46:15] <fbarriga>	probably this deserve a RTFM reply..
| [Tuesday 22 February 2011] [15:46:23] <fbarriga>	if I do this: zmq_msg_init(&msg); zmq_recv(sock, &msg, 0); zmq_recv(sock, &msg, 0); zmq_msg_close(&msg);
| [Tuesday 22 February 2011] [15:46:29] <fbarriga>	i'm leaking memory ?
| [Tuesday 22 February 2011] [15:46:44] <cremes>	sustrik: apparently i can reproduce a memory ddos with 0mq sockets; here's how (there may be a simpler way but this is how i did it)
| [Tuesday 22 February 2011] [15:46:55] <fbarriga>	every time zmq_recv allocate new memory ?
| [Tuesday 22 February 2011] [15:47:02] <cremes>	setup a standard forwarder
| [Tuesday 22 February 2011] [15:47:12] <pieterh>	fbarriga: yes, that works fine
| [Tuesday 22 February 2011] [15:47:15] <fbarriga>	and is mandatory to init the msg before receive the data ?
| [Tuesday 22 February 2011] [15:47:18] <pieterh>	yes
| [Tuesday 22 February 2011] [15:47:26] <cremes>	connect a publisher to it and let it go crazy broadcasting (bigger messages are better, e.g. 20k+)
| [Tuesday 22 February 2011] [15:47:32] <cremes>	so far, no leak
| [Tuesday 22 February 2011] [15:47:44] <cremes>	now start adding subscribers
| [Tuesday 22 February 2011] [15:47:49] <fbarriga>	umm, but if I have a while(true) I can't put the init outside to avoid overhead ?
| [Tuesday 22 February 2011] [15:48:03] <cremes>	again, no real leak except for a little queueing if the subscribers are slower than the pub
| [Tuesday 22 February 2011] [15:48:12] <pieterh>	fbarriga: close and init are a pair
| [Tuesday 22 February 2011] [15:48:16] <cremes>	i adjusted my publisher so that it would not overrun the subscribers
| [Tuesday 22 February 2011] [15:48:24] <cremes>	now here's where the leak comes in....
| [Tuesday 22 February 2011] [15:48:49] 	 * sustrik_ is listening
| [Tuesday 22 February 2011] [15:49:04] <cremes>	modify the subscribers so that they only stay connected for a few seconds; they close their sockets, and then immediately reconnect to the forwarder
| [Tuesday 22 February 2011] [15:49:11] <fbarriga>	so I can do this:  zmq_msg_init(&msg); while (true) { zmq_recv(sock, &msg, 0); }  zmq_msg_close(&msg); ?
| [Tuesday 22 February 2011] [15:49:14] <cremes>	they continue to do this for at least 15 minutes
| [Tuesday 22 February 2011] [15:49:26] <cremes>	what i see happening is a lot of sockets go into TIME_WAIT
| [Tuesday 22 February 2011] [15:49:57] <cremes>	i suspected that the socket ZMQ_LINGER option (defaults to indefinite) was holding onto the messages
| [Tuesday 22 February 2011] [15:50:06] <cremes>	but i just ran a test where i set it to 0 and it still occurred
| [Tuesday 22 February 2011] [15:50:37] <cremes>	so i'm thinking that as a socket sits in TIME_WAIT, its queue is still active; as new messages arrive from the publisher they are added to the queue
| [Tuesday 22 February 2011] [15:50:38] <sustrik_>	do the subscribers have identities?
| [Tuesday 22 February 2011] [15:50:53] <cremes>	when the TIME_WAIT expires, the queued data doesn't go away
| [Tuesday 22 February 2011] [15:51:15] <cremes>	they are using the default random id's; i am not overriding with my own
| [Tuesday 22 February 2011] [15:51:20] <pieterh>	fbarriga: nope, it'll leak memory
| [Tuesday 22 February 2011] [15:51:37] <pieterh>	if you have positive proof that init/close are slow, send it along
| [Tuesday 22 February 2011] [15:51:45] <cremes>	when i stop the publisher, the forwarder's memory stops growing
| [Tuesday 22 February 2011] [15:51:49] <pieterh>	if you don't then please don't optimize unnecessarily, it's pointless
| [Tuesday 22 February 2011] [15:52:05] <cremes>	when i disconnect the publisher and *all* subscribers, the forwarder's memory footprint remains the same (big)
| [Tuesday 22 February 2011] [15:52:26] <cremes>	so if i left it running (like for an overnight test) it would exhaust all memory resources by morning
| [Tuesday 22 February 2011] [15:52:37] <sustrik_>	cremes: afaik processes don't return allocated memory to the OS
| [Tuesday 22 February 2011] [15:52:43] <cremes>	and this is exactly what has been plaguing me the last week or so (since i found that last bug!)
| [Tuesday 22 February 2011] [15:53:12] <pieterh>	cremes: does the forwarder memory grow again from that high point ?
| [Tuesday 22 February 2011] [15:53:24] <pieterh>	i.e. leak vs. cached heap in process...?
| [Tuesday 22 February 2011] [15:53:27] <cremes>	pieterh: it only grows again if i turn the publisher back on
| [Tuesday 22 February 2011] [15:53:38] <pieterh>	but does it start growing again immediately?
| [Tuesday 22 February 2011] [15:54:23] <cremes>	let's see....
| [Tuesday 22 February 2011] [15:54:25] <pieterh>	if it's cached heap memory then after a few cycles it will stop growing
| [Tuesday 22 February 2011] [15:55:11] <fbarriga>	pieterh, but hypothetically calling those function will slow down the function
| [Tuesday 22 February 2011] [15:55:44] <pieterh>	fbarriga: doing hypothetical optimization is a waste of time, please don't
| [Tuesday 22 February 2011] [15:55:47] <cremes>	pieterh: no, it doesn't start growing again right away
| [Tuesday 22 February 2011] [15:56:00] <pieterh>	cremes: then it's cached heap memory, not a leak
| [Tuesday 22 February 2011] [15:56:31] <pieterh>	fbarriga: if you wish to actually know, try calling zmq_msg_init() and zmq_msg_close() in a loop, 1 billion times
| [Tuesday 22 February 2011] [15:56:37] <pieterh>	measure how many seconds it takes
| [Tuesday 22 February 2011] [15:56:59] <cremes>	so this is just due to the heap growing really large and it never gives the buffer space back to the OS even if the buffer is empty
| [Tuesday 22 February 2011] [15:57:00] <cremes>	?
| [Tuesday 22 February 2011] [15:57:04] <pieterh>	cremes: yup
| [Tuesday 22 February 2011] [15:57:14] <CIA-21>	jzmq: 03Gonzalo Diethelm 07master * ra791958 10/ (.gitignore configure.in): Changes by jrideout to allow the build to succeed with autoconf 2.59. - http://bit.ly/fypsls
| [Tuesday 22 February 2011] [15:57:27] <pieterh>	if you have a normally peaky stream, it'll hit some max and stop growing
| [Tuesday 22 February 2011] [15:57:39] <pieterh>	there may be a system call to return memory to the OS
| [Tuesday 22 February 2011] [15:57:57] <pieterh>	but it's always virtualized anyhow, not real RAM, afaik
| [Tuesday 22 February 2011] [15:58:53] <pieterh>	sustrik: is the inproc hwm+swap change worth mentioning in the release notes?
| [Tuesday 22 February 2011] [15:59:20] <sustrik_>	dunno
| [Tuesday 22 February 2011] [15:59:30] <sustrik_>	it's more of a fix
| [Tuesday 22 February 2011] [15:59:37] <sustrik_>	than a new feature
| [Tuesday 22 February 2011] [16:01:34] <pieterh>	basically the hwm is shared between peers, right?
| [Tuesday 22 February 2011] [16:03:13] <sustrik_>	it's sum of the two hwms
| [Tuesday 22 February 2011] [16:05:15] <pieterh>	the peers share a single buffer...
| [Tuesday 22 February 2011] [16:08:01] <pieterh>	sustrik: http://edupad.ch/2tZLebJbTg is the NEWS for 2.1.1... 
| [Tuesday 22 February 2011] [16:08:13] <pieterh>	I've gone through the git log
| [Tuesday 22 February 2011] [16:10:37] <sustrik_>	you've killed the edupad as well!
| [Tuesday 22 February 2011] [16:11:20] <sustrik_>	isn't it a ipv6 day today?
| [Tuesday 22 February 2011] [16:15:23] <pieterh>	sustrik: let's do that tomorrow... update your NEWS, send me a pull request
| [Tuesday 22 February 2011] [16:15:48] <pieterh>	when we get that working, I'll make the release
| [Tuesday 22 February 2011] [16:16:06] <sustrik_>	ok
| [Tuesday 22 February 2011] [16:19:26] <cremes>	i'm pretty convinced there is still a leak here... new information
| [Tuesday 22 February 2011] [16:19:49] <cremes>	slowing the publisher to every 10ms and setting HWM for all sockets to 1 and LINGER to 0
| [Tuesday 22 February 2011] [16:19:58] <cremes>	it still slowly grows in size
| [Tuesday 22 February 2011] [16:20:13] <cremes>	there shouldn't be *anything* getting queued or buffered here
| [Tuesday 22 February 2011] [16:20:34] <sustrik_>	ack
| [Tuesday 22 February 2011] [16:20:52] <sustrik_>	can you provide the test program?
| [Tuesday 22 February 2011] [16:20:55] <cremes>	the "cause" appears to be the subscribers connecting/disconnecting 
| [Tuesday 22 February 2011] [16:21:10] <sustrik_>	yes, looks like
| [Tuesday 22 February 2011] [16:21:18] <cremes>	sustrik: i can but it will be in ruby; i'll describe the steps so it could be replicated in another lang
| [Tuesday 22 February 2011] [16:21:44] <pieterh>	hmm, sustrik, maybe you really are in Libya...
| [Tuesday 22 February 2011] [16:23:28] <pieterh>	sustrik: does the HWM on a PUB socket affect each subscriber queue (over TCP)? so potentially N x HWM?
| [Tuesday 22 February 2011] [16:23:39] <sustrik_>	cremes: ok
| [Tuesday 22 February 2011] [16:23:49] <sustrik_>	yes
| [Tuesday 22 February 2011] [16:23:54] <sustrik_>	pieterh: yes
| [Tuesday 22 February 2011] [16:24:04] <pieterh>	thx
| [Tuesday 22 February 2011] [16:39:19] <sustrik_>	pieterh: still there
| [Tuesday 22 February 2011] [16:39:22] <sustrik_>	?
| [Tuesday 22 February 2011] [16:39:47] <sustrik_>	one more important thing...
| [Tuesday 22 February 2011] [16:40:25] <pieterh>	yeah, still here
| [Tuesday 22 February 2011] [16:41:06] <pieterh>	hmm?
| [Tuesday 22 February 2011] [16:41:49] <sustrik_>	given that there are two separately maintained repos now
| [Tuesday 22 February 2011] [16:42:02] <sustrik_>	we should keep the patches completely clean
| [Tuesday 22 February 2011] [16:42:14] <sustrik_>	i.e. no whitespace patching
| [Tuesday 22 February 2011] [16:42:20] <sustrik_>	no mixed patches
| [Tuesday 22 February 2011] [16:42:43] <sustrik_>	like fixing a bug and correcting an unrelated typo in a single patch
| [Tuesday 22 February 2011] [16:42:44] <sustrik_>	etc.
| [Tuesday 22 February 2011] [16:42:55] <pieterh>	you mean so we can re-port the history anywhere?
| [Tuesday 22 February 2011] [16:42:56] <sustrik_>	otherwise we'll end in dependency hell
| [Tuesday 22 February 2011] [16:43:07] <sustrik_>	yes
| [Tuesday 22 February 2011] [16:43:11] <pieterh>	right
| [Tuesday 22 February 2011] [16:43:16] <sustrik_>	keeping patches mobile
| [Tuesday 22 February 2011] [16:43:31] <pieterh>	so the way a pull request works is you specify a commit (or multiple commits)
| [Tuesday 22 February 2011] [16:43:38] <pieterh>	this may not work all the time
| [Tuesday 22 February 2011] [16:44:56] <sustrik_>	?
| [Tuesday 22 February 2011] [16:50:40] <pieterh>	clearly if we can keep patches fully mobile on the development master, that's ideal
| [Tuesday 22 February 2011] [16:50:40] <pieterh>	makes it fairly easy to send them anywhere
| [Tuesday 22 February 2011] [16:50:40] <pieterh>	we may want to add more process support, e.g. something greppable in the log
| [Tuesday 22 February 2011] [16:50:40] <pieterh>	in the worst case we can apply patches by hand
| [Tuesday 22 February 2011] [16:51:42] <pieterh>	well, some situations I can see happening
| [Tuesday 22 February 2011] [16:51:42] <pieterh>	- bug hits in 2.1 but that code has changed in 2.2
| [Tuesday 22 February 2011] [16:51:42] <pieterh>	- patch in 2.2 doesn't apply cleanly in 2.1
| [Tuesday 22 February 2011] [16:52:19] <pieterh>	- 2.1 needs only part of a patch made to 2.2
| [Tuesday 22 February 2011] [16:52:22] <pieterh>	etc.
| [Tuesday 22 February 2011] [16:55:11] <sustrik_>	git has support for that
| [Tuesday 22 February 2011] [16:55:11] <amacleod>	I am getting a different assertion error from jzmq tests now: Unknown error 156384765, rc == 0 (src/socket_base.cpp:243)
| [Tuesday 22 February 2011] [16:55:17] <sustrik_>	it's called merging
| [Tuesday 22 February 2011] [16:55:32] <sustrik_>	so you apply the patch
| [Tuesday 22 February 2011] [16:55:38] <sustrik_>	you get merge conflicts
| [Tuesday 22 February 2011] [16:55:41] <sustrik_>	you solve them
| [Tuesday 22 February 2011] [16:55:46] <sustrik_>	you commit the patch
| [Tuesday 22 February 2011] [16:55:58] <sustrik_>	it's still the same patch, but it have been backported
| [Tuesday 22 February 2011] [16:56:27] <sustrik_>	the backport iirc is visible as a separate commit
| [Tuesday 22 February 2011] [16:57:08] <sustrik_>	amacleod: what version?
| [Tuesday 22 February 2011] [16:57:59] <pieterh>	sustrik: ok, we'll play it through
| [Tuesday 22 February 2011] [16:58:16] <amacleod>	sustrik, v2.1.0, from tarball on http://www.zeromq.org/intro:get-the-software
| [Tuesday 22 February 2011] [17:00:27] <amacleod>	Looks like that line reference is in zmq::socket_base_t::getsockopt
| [Tuesday 22 February 2011] [17:01:25] <sustrik_>	amacleod: yes, it's a bug
| [Tuesday 22 February 2011] [17:01:32] <sustrik_>	it's solved in head
| [Tuesday 22 February 2011] [17:01:46] <amacleod>	Ok.  Guess I should get head, then, eh?
| [Tuesday 22 February 2011] [17:01:55] <sustrik_>	pieterh: when are you going to release 2.1.1?
| [Tuesday 22 February 2011] [17:02:36] <sustrik_>	amacleod: either get the head or wait for 2.1.1
| [Tuesday 22 February 2011] [17:02:45] <amacleod>	I will try with head.
| [Tuesday 22 February 2011] [17:10:06] <pieterh>	sustrik: please review http://edupad.ch/2tZLebJbTg and add to your master if you're happy with it
| [Tuesday 22 February 2011] [17:10:06] <pieterh>	date is set for tomorrow
| [Tuesday 22 February 2011] [17:10:07] <pieterh>	send me a pull request for that change, and I'll process it, and then make the release
| [Tuesday 22 February 2011] [17:10:08] <pieterh>	tomorrow morning after coffee
| [Tuesday 22 February 2011] [17:10:08] <pieterh>	does that work?
| [Tuesday 22 February 2011] [17:10:29] <pieterh>	I'd like to split off "Making a Release" from the "Source Code" page, it's two separate topics
| [Tuesday 22 February 2011] [17:10:29] <pieterh>	and this lets me document how to make a release, as a naive and not very expert person
| [Tuesday 22 February 2011] [17:10:29] <pieterh>	which is ideal
| [Tuesday 22 February 2011] [17:11:55] <pieterh>	ok, away
| [Tuesday 22 February 2011] [17:12:06] <pieterh>	g'nite everyone
| [Tuesday 22 February 2011] [17:12:23] <amacleod>	Nite Pieter.
| [Tuesday 22 February 2011] [17:15:35] <sustrik_>	what change?
| [Tuesday 22 February 2011] [17:16:12] <sustrik_>	edpad times out here btw
| [Tuesday 22 February 2011] [17:16:20] <sustrik_>	good night anyway
| [Tuesday 22 February 2011] [17:21:28] <amacleod>	Do pollers need to be closed or finalized in some way before terminating the context?
| [Tuesday 22 February 2011] [17:28:03] <rphillips>	is there a way to set a zeromq socket up to timeout on a zmq_send?
| [Tuesday 22 February 2011] [17:28:41] <ianbarber>	you could poll for a socket being writeable, with a timeout
| [Tuesday 22 February 2011] [17:32:10] <rphillips>	Do I need to check for writability after the connect or after the send?
| [Tuesday 22 February 2011] [17:32:18] <rphillips>	the send is blocked already
| [Tuesday 22 February 2011] [17:44:41] <sustrik_>	before the send
| [Tuesday 22 February 2011] [19:06:41] <leiger>	Hey, is Pieter here?
| [Tuesday 22 February 2011] [19:22:25] <cremes>	sustrik: got a repro for you here:  https://github.com/zeromq/zeromq2/issues/171
| [Tuesday 22 February 2011] [19:22:37] <cremes>	it affects tcp and ipc transports
| [Tuesday 22 February 2011] [19:23:06] <cremes>	sustrik: if you'd like, i can set this up under your account on my box so you can see it since i assume you don't plan
| [Tuesday 22 February 2011] [19:23:18] <cremes>	to install ruby and the dependent libraries
| [Tuesday 22 February 2011] [19:23:27] <cremes>	let me know
| [Tuesday 22 February 2011] [19:34:32] <lt_schmidt_jr>	Hi guys, is anyone compiling zmq for multiple platforms?
| [Tuesday 22 February 2011] [19:35:09] <lt_schmidt_jr>	anyone do jar packaging for binaries for java?
| [Tuesday 22 February 2011] [19:56:30] <kdj>	I am having a problem uninstalling an older version of pyzmq...
| [Tuesday 22 February 2011] [19:56:39] <kdj>	I mean a newer version, actually
| [Tuesday 22 February 2011] [19:56:57] <kdj>	I have pyzmq 2.1.0 installed, I want to revert to pyzmq2.0.10
| [Tuesday 22 February 2011] [19:57:16] <kdj>	I remove the directory and .egg from site-packages, and the module seems removed...
| [Tuesday 22 February 2011] [19:57:45] <kdj>	But when I re-install it, the zmq_version() is still 2.1.0, *except* for in the shell I installed from O_o
| [Tuesday 22 February 2011] [19:57:50] <kdj>	This is in Windows
| [Tuesday 22 February 2011] [19:59:17] <kdj>	Oh, it is because I am in the directory in which zmq is located. I still don't get how they're not the same...
| [Tuesday 22 February 2011] [20:37:21] <erickt>	hello #zeromq. I noticed that the HEAD of zeromq2 doesn't seem to be building and installing the documentation.
| [Tuesday 22 February 2011] [20:42:52] <jugg>	erickt, check the output of ./configure, you're probably missing a dependency.
| [Tuesday 22 February 2011] [20:44:27] <Steve-o>	which should be asciidoc
| [Tuesday 22 February 2011] [20:45:23] <erickt>	I got both asciidoc and xmlto installed. "make dist" properly builds all the docs
| [Tuesday 22 February 2011] [20:45:55] 	 * erickt checks 2.0.10
| [Tuesday 22 February 2011] [20:47:08] <Steve-o>	didn't someone catch this on the list recently
| [Tuesday 22 February 2011] [20:48:49] <erickt>	ah yeah the documentation does build correctly with v2.1.0
| [Tuesday 22 February 2011] [20:49:04] <Steve-o>	or maybe a new side effect with the new api.zero.mq support
| [Tuesday 22 February 2011] [20:55:22] 	 * erickt git bisects...
| [Tuesday 22 February 2011] [21:00:56] <erickt>	oh, haha, it's all my fault
| [Tuesday 22 February 2011] [21:01:35] <erickt>	I'm trying to get zeromq to build outside of the checkout directory and I messed up getting the doc builds to work :)
| [Tuesday 22 February 2011] [23:54:39] <cremes>	andrewvc: ping
| [Tuesday 22 February 2011] [23:54:52] <andrewvc>	yo
| [Tuesday 22 February 2011] [23:54:58] <andrewvc>	sitting next to evanphx right now
| [Tuesday 22 February 2011] [23:55:09] <cremes>	get it up on flickr
| [Tuesday 22 February 2011] [23:55:12] <cremes>	:)
| [Tuesday 22 February 2011] [23:55:16] <andrewvc>	lol
| [Tuesday 22 February 2011] [23:55:32] <andrewvc>	we're looking at that zmq bug actually, going through mailbox.cpp
| [Tuesday 22 February 2011] [23:55:35] <cremes>	so which bug are you and evan chatting about?
| [Tuesday 22 February 2011] [23:55:49] <andrewvc>	I think yours was a separate one, something about kernel buffers?
| [Tuesday 22 February 2011] [23:55:57] <andrewvc>	this is the one I hit a while ago that jruby doesn't have
| [Tuesday 22 February 2011] [23:56:44] <cremes>	the new_sndbuf > old_sndbuf assertion?
| [Tuesday 22 February 2011] [23:56:57] <andrewvc>	mmm this is nbytes != -1 EBADF
| [Tuesday 22 February 2011] [23:57:01] <andrewvc>	mailbox.cpp 241
| [Tuesday 22 February 2011] [23:57:03] <andrewvc>	that one
| [Tuesday 22 February 2011] [23:57:09] <cremes>	ah, your file descriptor one
| [Tuesday 22 February 2011] [23:57:11] <andrewvc>	yep
| [Wednesday 23 February 2011] [00:00:12] <cremes>	btw, i think 0mq is a pretty good exercise of rbx's ffi impl
| [Wednesday 23 February 2011] [00:44:03] <andrewvc>	cremes: still around?
| [Wednesday 23 February 2011] [00:45:13] <cremes>	barely; what's up?
| [Wednesday 23 February 2011] [00:46:55] <andrewvc>	yo, not much, but have a bit of a lead on the issue
| [Wednesday 23 February 2011] [00:47:07] <andrewvc>	basically, zmq is shutting down, but a call to zmqgetsockopt gets through
| [Wednesday 23 February 2011] [00:47:14] <andrewvc>	though the socket has been closed zmq doesn't see it
| [Wednesday 23 February 2011] [00:47:29] <andrewvc>	btw, evan was saying we should probably not use finalizers, as they can be dangerous
| [Wednesday 23 February 2011] [00:47:38] <cremes>	so it's shutting down when you do the getsockopt call?
| [Wednesday 23 February 2011] [00:47:39] <andrewvc>	basically, it's easy to have to FFI pointers to the same data
| [Wednesday 23 February 2011] [00:47:46] <andrewvc>	it shuts down  before
| [Wednesday 23 February 2011] [00:47:53] <andrewvc>	but the getsockopt gets through later
| [Wednesday 23 February 2011] [00:48:01] <cremes>	hrm...
| [Wednesday 23 February 2011] [00:48:11] <andrewvc>	and zmq blows up, because an internal FD it uses for that socket, an FD for a socketpair, has been closed
| [Wednesday 23 February 2011] [00:48:16] <cremes>	so what's this about finalizers? don't use 'em for auto-gc?
| [Wednesday 23 February 2011] [00:48:43] <andrewvc>	the cpp mailbox object seems to have been deleted, but not overwritten, but the ffi socket still points to it
| [Wednesday 23 February 2011] [00:48:50] <andrewvc>	that's from evan btw
| [Wednesday 23 February 2011] [00:49:00] <cremes>	the ffi socket...?
| [Wednesday 23 February 2011] [00:49:06] <andrewvc>	ZMQ::Socket
| [Wednesday 23 February 2011] [00:49:16] <andrewvc>	the actual pointer to the socket
| [Wednesday 23 February 2011] [00:49:19] <cremes>	the socketpairs are used for internal signaling, so they aren't exposed to us via ffi at all
| [Wednesday 23 February 2011] [00:49:33] <cremes>	ok, zmq.socket
| [Wednesday 23 February 2011] [00:49:37] <andrewvc>	yeah, but I think they're still tied to the socket
| [Wednesday 23 February 2011] [00:50:07] <evan>	hi cremes
| [Wednesday 23 February 2011] [00:50:07] <andrewvc>	evan's going to pop in
| [Wednesday 23 February 2011] [00:50:08] <evan>	:D
| [Wednesday 23 February 2011] [00:50:13] <cremes>	howdeee
| [Wednesday 23 February 2011] [00:50:18] <evan>	so, real fast
| [Wednesday 23 February 2011] [00:50:20] <evan>	here's how I see it.
| [Wednesday 23 February 2011] [00:50:39] 	 * cremes had a dram or two... :)
| [Wednesday 23 February 2011] [00:50:43] <andrewvc>	lol
| [Wednesday 23 February 2011] [00:50:51] <evan>	FFI -> zmq::getsockopt -> zmq::process_commands -> zmq::mailbox::recv
| [Wednesday 23 February 2011] [00:51:01] <evan>	those last 3 are in C++, in zmq's code base
| [Wednesday 23 February 2011] [00:51:06] <cremes>	hey, when you work 22 hours a day, a dram is all the vacation you need :)
| [Wednesday 23 February 2011] [00:51:08] <evan>	the FFI is called from the getsockopt method
| [Wednesday 23 February 2011] [00:51:13] <cremes>	right
| [Wednesday 23 February 2011] [00:51:29] <evan>	ZMQ_EVENTS is the option requested
| [Wednesday 23 February 2011] [00:51:45] <cremes>	k
| [Wednesday 23 February 2011] [00:51:51] <evan>	it appears that zmq has deleted the mailbox in question
| [Wednesday 23 February 2011] [00:52:08] <evan>	we're still able to access it because the FFI side has a hanging pointer to where it used to be
| [Wednesday 23 February 2011] [00:52:12] <evan>	and it hasn't been overriden
| [Wednesday 23 February 2011] [00:52:32] <evan>	I believe it has been deleted because I can see that the destructor for the mailbox is what closes the socketpari
| [Wednesday 23 February 2011] [00:52:43] <evan>	and I know that we're getting the EBADF on the socketpair in a mailbox
| [Wednesday 23 February 2011] [00:52:59] <cremes>	ok, then that's a bug
| [Wednesday 23 February 2011] [00:53:09] <evan>	all of that leads me to believe that zmq has decided to shutdown
| [Wednesday 23 February 2011] [00:53:15] <evan>	either because of an internal condition
| [Wednesday 23 February 2011] [00:53:18] <evan>	or because it was requested to
| [Wednesday 23 February 2011] [00:53:28] <evan>	but FFI was not told zmq was shutting down
| [Wednesday 23 February 2011] [00:53:40] <evan>	and thus still holds pointers to the C++ objects that have been deleted
| [Wednesday 23 February 2011] [00:53:50] <cremes>	the socketpair is used for signaling between the virtual socket and the i/o thread that handles all send/recv on the back-end
| [Wednesday 23 February 2011] [00:53:55] <cremes>	so if what you are saying is true
| [Wednesday 23 February 2011] [00:54:07] <cremes>	then we need to show a repro and get them to fix that up
| [Wednesday 23 February 2011] [00:54:17] <cremes>	the socket should only shut down under 2 conditions
| [Wednesday 23 February 2011] [00:54:24] <andrewvc>	well, I think that's all in the strace and backtrace I showed previously
| [Wednesday 23 February 2011] [00:54:26] <cremes>	1. zmq_close() is called on the socket
| [Wednesday 23 February 2011] [00:54:29] <andrewvc>	but I didn't frame it right
| [Wednesday 23 February 2011] [00:54:36] <andrewvc>	well, I never called zmq_close on the socket
| [Wednesday 23 February 2011] [00:54:39] <cremes>	2. zmq_term() is called on the context to shut *everything* down
| [Wednesday 23 February 2011] [00:54:48] <andrewvc>	we're not sure why it's being shut down
| [Wednesday 23 February 2011] [00:54:55] <cremes>	ok, then 3. bug
| [Wednesday 23 February 2011] [00:55:12] <andrewvc>	in my app I never call those things, it could be related to a ruby exception, or perhaps an exception in eventmachine's cext
| [Wednesday 23 February 2011] [00:55:20] <andrewvc>	since moving to jruby fixed the issue
| [Wednesday 23 February 2011] [00:55:22] <evan>	#1 and #2 need to be verified that they're not happening
| [Wednesday 23 February 2011] [00:55:31] <evan>	because of the extra indirection of the FFI binding
| [Wednesday 23 February 2011] [00:55:34] <andrewvc>	yep
| [Wednesday 23 February 2011] [00:55:50] <cremes>	yeah, breakpoints on those c++ functions
| [Wednesday 23 February 2011] [00:55:52] <evan>	it seems possible that zmq_term was called (perhaps by a finalizer?)
| [Wednesday 23 February 2011] [00:56:05] <cremes>	only if a context is garbage collected
| [Wednesday 23 February 2011] [00:56:20] <evan>	sure
| [Wednesday 23 February 2011] [00:56:27] <cremes>	and *only* under 2.1.0... it activates that code based on the version of the 0mq lib that is loaded
| [Wednesday 23 February 2011] [00:56:29] <evan>	basically, you need to verify if those are happening.
| [Wednesday 23 February 2011] [00:56:38] <evan>	or not happening
| [Wednesday 23 February 2011] [00:56:43] <evan>	when the bug occurs
| [Wednesday 23 February 2011] [00:56:44] <andrewvc>	oh, well this was off zmq HEAD
| [Wednesday 23 February 2011] [00:56:47] <evan>	only then can you proceed to #3
| [Wednesday 23 February 2011] [00:56:58] <cremes>	agreed (evan)
| [Wednesday 23 February 2011] [00:57:03] <evan>	additionally, you can certainly repro this all in C++
| [Wednesday 23 February 2011] [00:57:23] <cremes>	maybe andrewvc  can ... ;)
| [Wednesday 23 February 2011] [00:57:27] <evan>	you can see if calling zmq_term, then zmq_getsockopt causes an EBADF
| [Wednesday 23 February 2011] [00:57:30] <evan>	it seems likely it would :)
| [Wednesday 23 February 2011] [00:57:35] <andrewvc>	lol, I'd actually really like to, I'll put some more time into this this weekend
| [Wednesday 23 February 2011] [00:57:39] <cremes>	that's easy enough to try
| [Wednesday 23 February 2011] [00:58:14] <cremes>	there are certainly bugs in 0mq; i found another today that i've been chasing for the last 4 days
| [Wednesday 23 February 2011] [00:58:26] <cremes>	i sent them a repro (in ruby)
| [Wednesday 23 February 2011] [00:58:31] <evan>	cremes: yeah, I told andrewvc about that one.
| [Wednesday 23 February 2011] [00:58:35] <evan>	the buffer bug.
| [Wednesday 23 February 2011] [00:58:50] <cremes>	yeah, the same code also crashes rbx... right
| [Wednesday 23 February 2011] [00:58:51] <andrewvc>	yeah
| [Wednesday 23 February 2011] [00:59:15] <cremes>	well, this is all pretty exciting
| [Wednesday 23 February 2011] [00:59:33] <cremes>	thanks for taking some time to dive into this... are you guys as a BoF or something?
| [Wednesday 23 February 2011] [00:59:38] <cremes>	s/as/at/
| [Wednesday 23 February 2011] [00:59:51] <andrewvc>	we're both usually at LA Ruby hack nights on tues
| [Wednesday 23 February 2011] [00:59:57] <cremes>	ah...
| [Wednesday 23 February 2011] [01:00:03] <andrewvc>	actually evan's a cofounder, him and shane becker run it
| [Wednesday 23 February 2011] [01:00:28] <cremes>	cool.... well, you certainly brought in a knotty problem tonight
| [Wednesday 23 February 2011] [01:00:29] <andrewvc>	what's a BoF
| [Wednesday 23 February 2011] [01:00:40] <cremes>	birds of a feather
| [Wednesday 23 February 2011] [01:00:52] <cremes>	it's a wwdc term 
| [Wednesday 23 February 2011] [01:00:53] <andrewvc>	yeah, I'm glad evan took a look at it, really interesting stuff going through zeromq internals tracking it down
| [Wednesday 23 February 2011] [01:01:13] <cremes>	heh, i bet evan had some comments on that codebase
| [Wednesday 23 February 2011] [01:01:17] <andrewvc>	lol
| [Wednesday 23 February 2011] [01:01:21] <andrewvc>	how did you know
| [Wednesday 23 February 2011] [01:01:37] <cremes>	i've seen rbx c++ and it's nothing like 0mq c++
| [Wednesday 23 February 2011] [01:01:40] <cremes>	:)
| [Wednesday 23 February 2011] [01:01:53] <andrewvc>	hehe
| [Wednesday 23 February 2011] [01:01:59] <cremes>	d'oh! this is all in-channel!  heh heh
| [Wednesday 23 February 2011] [01:02:01] <evan>	cremes: yeah, I did
| [Wednesday 23 February 2011] [01:02:05] <evan>	*eyeroll*
| [Wednesday 23 February 2011] [01:02:08] <evan>	:D
| [Wednesday 23 February 2011] [01:02:27] <cremes>	that's why i'm a ruby guy; i have a hard enough time making that look good let alone attempt c++ anymore
| [Wednesday 23 February 2011] [01:02:35] <cremes>	!!
| [Wednesday 23 February 2011] [01:02:44] <cremes>	well, thanks for digging into this
| [Wednesday 23 February 2011] [01:02:44] <cremes>	i 
| [Wednesday 23 February 2011] [01:03:02] <cremes>	think between andrewvc and i we can probably produce a repro for these guys
| [Wednesday 23 February 2011] [01:03:10] <cremes>	that ZMQ_EVENTS code is still pretty new
| [Wednesday 23 February 2011] [01:03:17] <cremes>	and likely needs more shake-down
| [Wednesday 23 February 2011] [01:04:04] <cremes>	andrewvc: are you doing your dripdrop testing under rbx full-time yet?
| [Wednesday 23 February 2011] [01:04:25] <andrewvc>	hah, switched to jruby because of this bug
| [Wednesday 23 February 2011] [01:04:32] <andrewvc>	but if I get this back under control, I'm back on rbx
| [Wednesday 23 February 2011] [01:04:33] <cremes>	pussy
| [Wednesday 23 February 2011] [01:04:40] <cremes>	;)
| [Wednesday 23 February 2011] [01:04:47] <evan>	cremes: cool.
| [Wednesday 23 February 2011] [01:04:48] <andrewvc>	lol, well, I like my stack traces with my errors
| [Wednesday 23 February 2011] [01:05:10] <cremes>	it doesn't make a lot of sense that this would work under jruby but break under rbx, yes?
| [Wednesday 23 February 2011] [01:05:22] <andrewvc>	well, eventmachine has a different java core
| [Wednesday 23 February 2011] [01:05:22] <cremes>	zmq should behave the same in both scenarios
| [Wednesday 23 February 2011] [01:05:30] <andrewvc>	so maybe there's an interaction with the cext
| [Wednesday 23 February 2011] [01:05:36] <evan>	also
| [Wednesday 23 February 2011] [01:05:37] <andrewvc>	or maybe I'm crazy
| [Wednesday 23 February 2011] [01:05:40] <cremes>	crazy
| [Wednesday 23 February 2011] [01:05:41] <evan>	if it is something with finalizers
| [Wednesday 23 February 2011] [01:05:53] <evan>	jruby could have very different finalizer run patterns than rbx
| [Wednesday 23 February 2011] [01:05:56] <evan>	jsut throwing that out there.
| [Wednesday 23 February 2011] [01:06:02] <andrewvc>	yep, I'll try removing finalizers as well
| [Wednesday 23 February 2011] [01:06:05] <cremes>	finalizers are easy to disable; andrewvc : give that a try
| [Wednesday 23 February 2011] [01:06:21] <andrewvc>	I definitely will
| [Wednesday 23 February 2011] [01:06:30] <cremes>	yeah, the finalizers could be the culprit
| [Wednesday 23 February 2011] [01:06:46] <cremes>	most of these commands run async on the i/o thread so timing can play a part
| [Wednesday 23 February 2011] [01:07:01] <evan>	cremes: i'm packing up my laptop
| [Wednesday 23 February 2011] [01:07:02] <andrewvc>	it was always reproducible in sequence though
| [Wednesday 23 February 2011] [01:07:07] <andrewvc>	I as well, they're closing down
| [Wednesday 23 February 2011] [01:07:09] <evan>	talk to ya tomorrow, back on the battlefield!
| [Wednesday 23 February 2011] [01:07:09] <andrewvc>	I'll ttyl chuck
| [Wednesday 23 February 2011] [01:07:11] <cremes>	evan: g'night
| [Wednesday 23 February 2011] [01:07:17] <cremes>	goodnight to all!
| [Wednesday 23 February 2011] [01:07:20] <cremes>	happy hacking