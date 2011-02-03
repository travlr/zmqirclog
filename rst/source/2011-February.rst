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