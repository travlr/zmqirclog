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