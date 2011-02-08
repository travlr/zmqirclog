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