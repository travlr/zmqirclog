===============
2011-January
===============

| [Saturday 01 January 2011] [10:10:37] <dos000>	and happy new year
| [Saturday 01 January 2011] [10:10:51] <dos000>	is sustrik here ?
| [Saturday 01 January 2011] [10:12:02] <mikko>	he was in yesterday
| [Saturday 01 January 2011] [10:12:28] <mikko>	havent seen him talking today
| [Saturday 01 January 2011] [10:15:01] <dos000>	ah!
| [Saturday 01 January 2011] [12:34:22] <sustrik>	dos000: hi
| [Saturday 01 January 2011] [12:36:15] <sustrik>	happy new year everyone!
| [Saturday 01 January 2011] [13:16:07] <pythonirc1011>	how much work is it to get a installer ready for windows7 for zeromq+python bindings. Where can one get started on that? 
| [Saturday 01 January 2011] [13:33:07] <mikko>	pythonirc1011: probably it's just building the installer
| [Saturday 01 January 2011] [13:33:38] <mikko>	pythonirc1011: not sure how python extensions are installed on windows or any platform really
| [Saturday 01 January 2011] [13:41:38] <dos000>	sustrik, howdy !
| [Saturday 01 January 2011] [13:42:03] <dos000>	sustrik, happy new year to you too
| [Saturday 01 January 2011] [13:47:30] <sustrik>	pythonirc1011: building a win installer would be very helpful
| [Saturday 01 January 2011] [13:47:42] <sustrik>	i would start with the core part
| [Saturday 01 January 2011] [13:47:43] <pythonirc1011>	mikko: so i need a installation script language + compilation of a zeromq on my win box i guess...
| [Saturday 01 January 2011] [13:47:57] <sustrik>	it's just a lib and a header file so it should be easy
| [Saturday 01 January 2011] [13:48:20] <pythonirc1011>	i'm more after building the python bindings. I need to use it from python
| [Saturday 01 January 2011] [13:48:35] <sustrik>	sure, but those are dependent on the lib
| [Saturday 01 January 2011] [13:48:44] <pythonirc1011>	true
| [Saturday 01 January 2011] [13:48:53] <pythonirc1011>	perhaps ship the library pre-compiler on windows
| [Saturday 01 January 2011] [13:48:58] <pythonirc1011>	compiler
| [Saturday 01 January 2011] [13:49:01] <pythonirc1011>	compiled i meant
| [Saturday 01 January 2011] [13:49:04] <sustrik>	exactly
| [Saturday 01 January 2011] [13:49:10] <sustrik>	what you need is 2 libraties
| [Saturday 01 January 2011] [13:49:12] <sustrik>	libzmq
| [Saturday 01 January 2011] [13:49:18] <sustrik>	and libpyzmq
| [Saturday 01 January 2011] [13:49:24] <sustrik>	you need to compile them
| [Saturday 01 January 2011] [13:49:35] <sustrik>	and build an installer
| [Saturday 01 January 2011] [13:49:42] <pythonirc1011>	k, that should be doable...are they dlls?
| [Saturday 01 January 2011] [13:49:59] <sustrik>	i am not sure whether python needs anythig else aside of those libs
| [Saturday 01 January 2011] [13:50:15] <sustrik>	yes, i think so
| [Saturday 01 January 2011] [13:50:48] <pythonirc1011>	I'll look into it soon. Thanks. 
| [Saturday 01 January 2011] [13:55:38] <dos000>	sustrik, does zma uses lock free ring buffers  ? sometalk i listened mentioned it being musch faster than using queues becose of contention
| [Saturday 01 January 2011] [13:55:51] <dos000>	s/zma/0mq
| [Saturday 01 January 2011] [13:56:04] <sustrik>	yes, the queues are lock-free
| [Saturday 01 January 2011] [13:56:46] <dos000>	sustrik, is it ringbuffer based ?
| [Saturday 01 January 2011] [13:57:06] <sustrik>	messages are allocated in blocks
| [Saturday 01 January 2011] [13:57:10] <sustrik>	(256 per block)
| [Saturday 01 January 2011] [13:57:40] <dos000>	sustrik, here is the talk http://www.infoq.com/presentations/LMAX jump to 36:00 for the real meat. 
| [Saturday 01 January 2011] [13:57:54] <sustrik>	one block is recycled to eliminate excessive allocation/deallocation
| [Saturday 01 January 2011] [13:58:17] <dos000>	its kinda java oriented but i think the same issues apply in c++
| [Saturday 01 January 2011] [13:58:28] <sustrik>	however, if the number of messages in the queue drops, only 1 block is recycled, any subsequent blocvks are dealloc'd
| [Saturday 01 January 2011] [13:58:41] <dos000>	ah!
| [Saturday 01 January 2011] [13:59:02] <dos000>	thats seems smarter .. they allocate 2min off hand to counter java gc 
| [Saturday 01 January 2011] [13:59:09] <dos000>	2 millions
| [Saturday 01 January 2011] [13:59:31] <sustrik>	well, depends on the use case
| [Saturday 01 January 2011] [13:59:50] <sustrik>	it's something that's not good to do on a sensor or an embedded system
| [Saturday 01 January 2011] [14:00:11] <sustrik>	0mq tries to be generic
| [Saturday 01 January 2011] [14:00:12] <dos000>	indeed .. for a server its much different
| [Saturday 01 January 2011] [14:00:26] <sustrik>	you can of course tune it by hand if you want to
| [Saturday 01 January 2011] [14:00:48] <sustrik>	see src/config.hpp
| [Saturday 01 January 2011] [14:01:51] <dos000>	sustrik, so its configurable by source changes only then 
| [Saturday 01 January 2011] [14:02:16] <sustrik>	there are 2 mechanisms there
| [Saturday 01 January 2011] [14:02:26] <sustrik>	config.hpp are compile-time options
| [Saturday 01 January 2011] [14:02:28] <dos000>	sustrik, it will apply to all queues then
| [Saturday 01 January 2011] [14:02:40] <sustrik>	socket options can be used in run-time
| [Saturday 01 January 2011] [14:02:49] <dos000>	ah!
| [Saturday 01 January 2011] [14:03:08] <sustrik>	it's a matter to consider whether specific tuning parameter
| [Saturday 01 January 2011] [14:03:09] <dos000>	socket options allow to you bigger/smaller buffers ?
| [Saturday 01 January 2011] [14:03:18] <sustrik>	should be a socket option or a compile-time param
| [Saturday 01 January 2011] [14:03:36] <sustrik>	socket option allow to set the maximal buffer size
| [Saturday 01 January 2011] [14:03:49] <dos000>	i cant use compile time options 
| [Saturday 01 January 2011] [14:03:58] <sustrik>	what are you trying to do?
| [Saturday 01 January 2011] [14:05:13] <dos000>	i am writing queues with different bechmarking options
| [Saturday 01 January 2011] [14:05:24] <dos000>	so i want to see effect of the changes
| [Saturday 01 January 2011] [14:06:26] <sustrik>	writing queues?
| [Saturday 01 January 2011] [14:06:36] <sustrik>	you mean you are implementing the queues yourself?
| [Saturday 01 January 2011] [14:06:41] <dos000>	so far i have 0mq and fastflow ( http://calvados.di.unipi.it/dokuwiki/doku.php?id=ffnamespace:about ) on my list
| [Saturday 01 January 2011] [14:06:59] <sustrik>	ok, i see
| [Saturday 01 January 2011] [14:07:05] <sustrik>	and what exactly are you missing?
| [Saturday 01 January 2011] [14:08:39] <dos000>	sustrik, i only have one issue so far ... 
| [Saturday 01 January 2011] [14:09:17] <dos000>	i have to receive the events and process them in  java ... 
| [Saturday 01 January 2011] [14:10:07] <dos000>	i either reimplement the lockfree ring buffers in java .. or use jzmq 
| [Saturday 01 January 2011] [14:10:39] <dos000>	it looks deceptively easy to write it in java !
| [Saturday 01 January 2011] [14:11:27] <sustrik>	i still don't see what you are missing :)
| [Saturday 01 January 2011] [14:11:39] <sustrik>	0mq is lock-free
| [Saturday 01 January 2011] [14:11:43] <dos000>	yes ... i am not missing anything ... 
| [Saturday 01 January 2011] [14:11:48] <dos000>	i just have options !
| [Saturday 01 January 2011] [14:12:04] <sustrik>	implementing the lock-free queeu is not hard
| [Saturday 01 January 2011] [14:12:20] <sustrik>	it may become a problem as you want to add more features
| [Saturday 01 January 2011] [14:12:23] <dos000>	sustrik, there is locking when you call c++ functions from java
| [Saturday 01 January 2011] [14:12:28] <sustrik>	like limiting the number of messages in queue
| [Saturday 01 January 2011] [14:12:31] <sustrik>	or somesuch
| [Saturday 01 January 2011] [14:13:00] <sustrik>	is there, i am not familiar with how jzmq works atm
| [Saturday 01 January 2011] [14:13:09] <dos000>	its inherent in jni 
| [Saturday 01 January 2011] [14:13:15] <sustrik>	i see
| [Saturday 01 January 2011] [14:13:28] <sustrik>	then you have to reimplement it yourself
| [Saturday 01 January 2011] [14:13:35] <dos000>	another option would be to receive the events via sockets in java
| [Saturday 01 January 2011] [14:13:53] <sustrik>	what sockets?
| [Saturday 01 January 2011] [14:14:40] <dos000>	instead of passing the messages via jni pass it via a the (local) netwrk interface 
| [Saturday 01 January 2011] [14:15:00] <dos000>	of course that would be slower i imagine
| [Saturday 01 January 2011] [14:15:33] <dos000>	1) evtsource -> zmq --> jzmq --> java app
| [Saturday 01 January 2011] [14:16:08] <dos000>	eventsource -> zmq --> javanio --> javaapp 
| [Saturday 01 January 2011] [14:17:19] <dos000>	anyway ... 
| [Saturday 01 January 2011] [14:17:25] <dos000>	i will keep you updated !
| [Saturday 01 January 2011] [14:17:28] <dos000>	thanks a lot
| [Saturday 01 January 2011] [14:20:46] <sustrik>	you are welcome
| [Saturday 01 January 2011] [14:36:27] <mikko>	happy new year all
| [Saturday 01 January 2011] [15:12:01] <andrewvc>	cremes: If you're around I have a question about error_check_nonblock if you have a chance
| [Saturday 01 January 2011] [15:33:17] <andrewvc>	So, here's a nonblocking question
| [Saturday 01 January 2011] [15:36:31] <andrewvc>	so, if I get an errno 95 doing a recv NOBLOCK
| [Saturday 01 January 2011] [15:37:18] <andrewvc>	what is the usual cause for that
| [Saturday 01 January 2011] [15:37:28] <andrewvc>	I was expecting an EAGAIN
| [Saturday 01 January 2011] [15:37:36] <andrewvc>	and retrying later my recv did work
| [Saturday 01 January 2011] [16:27:29] <sustrik>	what's errno 95?
| [Saturday 01 January 2011] [16:59:13] <andrewvc>	sustrik,  #define EOPNOTSUPP  95  /* Operation not supported on transport endpoint */
| [Saturday 01 January 2011] [16:59:53] <andrewvc>	basically, I get a notification of activity via select for a FD
| [Saturday 01 January 2011] [17:00:06] <andrewvc>	so I'm calling a recv ZMQ::NOBLOCK on it to see if I can read off a message
| [Saturday 01 January 2011] [17:00:08] <andrewvc>	and I get that
| [Saturday 01 January 2011] [17:00:29] <andrewvc>	i mean if I just pretend that's an EAGAIN it works alright
| [Saturday 01 January 2011] [17:00:37] <andrewvc>	but just not what I expected
| [Saturday 01 January 2011] [18:23:03] <neopallium>	andrewvc: if you are calling recv() on a REQ/REP socket during the wrong state, you will get that error.
| [Saturday 01 January 2011] [18:24:36] <neopallium>	REQ/REP sockets switch back and forth from send-only to recv-only states.
| [Saturday 01 January 2011] [19:03:57] <andrewvc>	neopallium: it's actually a push socket
| [Saturday 01 January 2011] [19:04:03] <andrewvc>	errr a pull socket I mena
| [Saturday 01 January 2011] [19:04:20] <andrewvc>	maybe it didn't finish binding yet or something?
| [Saturday 01 January 2011] [19:04:28] <andrewvc>	though the FD did trigger
| [Saturday 01 January 2011] [19:19:37] <mikko>	andrewvc: are you sure it's a pull and not push socket?
| [Saturday 01 January 2011] [19:28:59] <andrewvc>	yeah I'm certain
| [Saturday 01 January 2011] [19:29:10] <andrewvc>	mikko: I'm certain because the messages eventually do start coming off
| [Saturday 01 January 2011] [19:29:19] <andrewvc>	I should double check though
| [Saturday 01 January 2011] [19:50:12] <andrewvc>	mikko: Oh how about that, I didn't realize that was being called on both send AND recv.... Thanks for the pointer
| [Saturday 01 January 2011] [19:50:35] <andrewvc>	it was a PUSH after all. Thanks for recognizing that!
| [Saturday 01 January 2011] [19:51:13] <mikko>	no prob, i think i've done that before as well
| [Saturday 01 January 2011] [19:51:21] <andrewvc>	but recv isn't being called on it
| [Saturday 01 January 2011] [19:51:23] <andrewvc>	send is
| [Saturday 01 January 2011] [19:51:40] <andrewvc>	so, does that mean the socket isn't in a state where it's ready for sending I suppose
| [Saturday 01 January 2011] [19:54:57] <andrewvc>	mikko: Well, re-checking it I'm getting all proper codes, and EAGAIN where I expect it. I guess cleaning up my testing code must have fixed whatever the err was
| [Saturday 01 January 2011] [19:55:11] <andrewvc>	thanks for the help though, still good to know for later
| [Sunday 02 January 2011] [05:08:53] <sustrik>	andrewvc: you've got ENOTSUPP from zmq_recv?
| [Sunday 02 January 2011] [05:11:38] <sustrik>	looking at the code...
| [Sunday 02 January 2011] [05:12:00] <sustrik>	hm, it can possibly happen when the socket is not yet fully initialised
| [Sunday 02 January 2011] [05:31:08] <sustrik>	do you have a test program to reproduce it?
| [Sunday 02 January 2011] [17:20:36] <shykes_>	Hello
| [Sunday 02 January 2011] [17:29:28] <mikko>	hi
| [Sunday 02 January 2011] [17:31:06] <shykes_>	I'm weighing my options for a "smarter" req/rep device. Are you aware of any projects going in that direction?
| [Sunday 02 January 2011] [17:31:25] <mikko>	what do you mean by smarter?
| [Sunday 02 January 2011] [17:31:27] <mikko>	brb
| [Sunday 02 January 2011] [17:32:19] <shykes_>	Currently we have a forwarder with bind on both sides
| [Sunday 02 January 2011] [17:32:26] <shykes_>	ie dynamic workers, dynamic clients
| [Sunday 02 January 2011] [17:32:57] <shykes_>	we use that to load-balance synchronous rpc. I'm guessing this is a classic use case
| [Sunday 02 January 2011] [17:34:02] <shykes_>	I'd like my device to stop forwarding requests to a worker which doesn't behave properly
| [Sunday 02 January 2011] [17:34:29] <shykes_>	eg. a pre-configured timeout
| [Sunday 02 January 2011] [17:37:18] <shykes_>	Maybe I could implement this as a 'proxy device' in front of each worker
| [Sunday 02 January 2011] [17:38:00] <shykes_>	each proxy has only one message to worry about at a time, which makes it simpler to write
| [Sunday 02 January 2011] [17:38:06] <shykes_>	Any insight would be much appreciated :)
| [Sunday 02 January 2011] [19:47:25] <Skaag>	shykes_: sounds like an important and also "classical" use case to me, sounds like you need a sort of a "broker"? :-)
| [Sunday 02 January 2011] [19:48:57] <shykes_>	Correct. Although I already use zmq_forwarder as a broker
| [Sunday 02 January 2011] [19:50:09] <shykes_>	But before I reinvent the wheel, I'm trying to find out how much of it already exists
| [Sunday 02 January 2011] [19:50:51] <shykes_>	I'm guessing a lot of people use zeromq for the same purpose as me. How did all these people implement this?
| [Sunday 02 January 2011] [19:55:14] <shykes_>	Hum, I just found rabbitmq's rmq-0mq plugin. Maybe that can help
| [Sunday 02 January 2011] [20:00:11] <Skaag>	we are porting our system from rabbitmq to 0mq
| [Sunday 02 January 2011] [20:00:26] <Skaag>	because of scaling issues
| [Sunday 02 January 2011] [20:00:43] <shykes_>	Yeah, we were using rabbitmq too
| [Sunday 02 January 2011] [20:00:46] <Skaag>	I think the case of a "dead" machine is handled well, but a misbehaving machine, that's another story
| [Sunday 02 January 2011] [20:01:23] <Skaag>	you'll simply need to implement this yourself, or on the machine itself, decouple the process that receives the messages from the processes that do the actual work
| [Sunday 02 January 2011] [20:01:31] <shykes_>	yeah
| [Sunday 02 January 2011] [20:01:39] <shykes_>	sounds like less work than putting rabbitmq back into the mix :)
| [Sunday 02 January 2011] [20:01:44] <Skaag>	why are you using 0mq instead of the wicked rabbit if I may ask?
| [Sunday 02 January 2011] [20:02:09] <Skaag>	yes, also in my opinion, it is less work.
| [Sunday 02 January 2011] [20:02:16] <shykes_>	A few reasons
| [Sunday 02 January 2011] [20:02:29] <shykes_>	1. We encountered problems with our Celery+RabbitMQ setup
| [Sunday 02 January 2011] [20:02:30] <Skaag>	I wish I knew about the shortcomings before I started implementing with rabbit...
| [Sunday 02 January 2011] [20:02:56] <shykes_>	2. We hit a major bug in the persister, which made it crash and not come back. Had to recover by hand...
| [Sunday 02 January 2011] [20:03:09] <Skaag>	crap
| [Sunday 02 January 2011] [20:03:15] <Skaag>	(and now i'm told that our 16 node cluster is considered "very large" in rabbitmq terms...)
| [Sunday 02 January 2011] [20:03:19] <shykes_>	3. I hate amqp. It's too complicated
| [Sunday 02 January 2011] [20:03:55] <Skaag>	well then we agree at least on 2 and 3, and about 1 is irrelevant to our own system
| [Sunday 02 January 2011] [20:03:58] <shykes_>	4. more freedom in the topology
| [Sunday 02 January 2011] [20:04:04] <Skaag>	right
| [Sunday 02 January 2011] [20:04:13] <shykes_>	for example, switch to multicast down the road 
| [Sunday 02 January 2011] [20:04:16] <Skaag>	ok this gives me validation in my own path
| [Sunday 02 January 2011] [20:04:20] <Skaag>	yep
| [Sunday 02 January 2011] [20:04:28] <Skaag>	at least within a single DC
| [Sunday 02 January 2011] [20:04:37] <Skaag>	I believe multicast over WAN is not feasible and may never be
| [Sunday 02 January 2011] [20:04:51] <shykes_>	yeah, we're primarily on EC2 for now, so not relevant for us either
| [Sunday 02 January 2011] [20:21:22] <Skaag>	I constantly fail to see how EC2 helps with anything other than temporarily huge computations
| [Sunday 02 January 2011] [20:21:38] <Skaag>	it's more expensive than standard hosting
| [Sunday 02 January 2011] [20:21:46] <Skaag>	by any calculation I made
| [Sunday 02 January 2011] [22:01:38] <viraptor>	hi all
| [Sunday 02 January 2011] [22:02:29] <viraptor>	could someone tell me where to look for information on zeromq + forking? the docs describe multithreading, but not how I should handle a fork (inherit the context or not)
| [Sunday 02 January 2011] [22:46:42] <viraptor>	ehh... found the answer after all... it's "don't share the context with fork"
| [Monday 03 January 2011] [00:46:14] <jugg>	with zmq 2.1.x, sockets can be shared between threads.  However, zmq_poll documentation still state that the sockets must belong to the same thread calling zmq_poll.   Is that still the case?
| [Monday 03 January 2011] [01:09:59] <neopallium>	jugg: with zmq 2.1 sockets can be moved between threads, but you still can't send/recv from different threads on the same socket.
| [Monday 03 January 2011] [01:57:01] <PeterTork>	Question regarding the Ruby bindings. I am creating a socket, and then trying to extend it with a module. This causes it to fail in ZM.select(arrayOfSockets, nil, nil, 30) with the error `select': uninitialized stream (IOError)
| [Monday 03 January 2011] [01:57:20] <PeterTork>	Removing the s.extend(EmptyModule) fixes this.
| [Monday 03 January 2011] [12:55:38] <Seta00>	I'm having lots of problems building pyzmq :(
| [Monday 03 January 2011] [12:55:57] <Seta00>	well, only one problem, but I can't fix it :P
| [Monday 03 January 2011] [12:58:15] <mikko>	what problem are you having?
| [Monday 03 January 2011] [13:02:15] <Seta00>	mikko, distutils couldn't find my vcvarsall, but I've just fixed it by manually returning the absolute path to it
| [Monday 03 January 2011] [13:02:42] <Seta00>	now I just need to put the include files on the right dirs
| [Monday 03 January 2011] [13:02:49] <Seta00>	and everything is good to go (I think)
| [Monday 03 January 2011] [13:06:27] <Seta00>	now I need a constants.pyd.manifest file
| [Monday 03 January 2011] [13:15:44] <Seta00>	lol I had to manually create a bunch of manifest files
| [Monday 03 January 2011] [13:18:10] <Seta00>	hehe finally working
| [Monday 03 January 2011] [13:25:58] <Seta00>	aaaand they don't work :)
| [Monday 03 January 2011] [13:26:13] <Seta00>	DLL load failed: The application has failed to start because its side-by-side configuration is incorrect.
| [Monday 03 January 2011] [13:50:22] <Seta00>	this thing is driving me nuts, I think I'll just use the C++ library
| [Monday 03 January 2011] [13:56:17] <sustrik>	Seta00: try asking on the mailing list, the pyzmq guys can possibly help you
| [Monday 03 January 2011] [14:29:29] <mikko>	sustrik: build currently fails on sunos using gcc3
| [Monday 03 January 2011] [14:29:33] <mikko>	not sure if that is big deal
| [Monday 03 January 2011] [14:38:11] <sustrik>	mikko: there's lot of failures there...
| [Monday 03 January 2011] [14:38:38] <mikko>	what do you mean? 
| [Monday 03 January 2011] [14:38:59] <mikko>	you mean sunos and gcc3 to begin with
| [Monday 03 January 2011] [14:39:00] <mikko>	:)
| [Monday 03 January 2011] [14:39:13] <sustrik>	i see 8 red point on valokuva.org
| [Monday 03 January 2011] [14:39:20] <sustrik>	points
| [Monday 03 January 2011] [14:39:45] <mikko>	have i broken something?
| [Monday 03 January 2011] [14:39:50] <mikko>	i'll check
| [Monday 03 January 2011] [14:40:09] <mikko>	github was unavailable it seems
| [Monday 03 January 2011] [14:40:17] <sustrik>	ah, yes
| [Monday 03 January 2011] [14:40:25] <sustrik>	i've noticed that myself
| [Monday 03 January 2011] [14:40:41] <sustrik>	so where should i look for console output?
| [Monday 03 January 2011] [14:41:23] <mikko>	http://build.valokuva.org/job/ZeroMQ2-core-master-SunGCC-solaris10/4/console
| [Monday 03 January 2011] [14:41:27] <mikko>	there at the end
| [Monday 03 January 2011] [14:42:02] <mikko>	i looked at it last night, looks like compiler error to me
| [Monday 03 January 2011] [14:44:05] <sustrik>	yep
| [Monday 03 January 2011] [14:44:08] <sustrik>	let me fix it
| [Monday 03 January 2011] [14:49:56] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r95eebbf 10/ src/sub.cpp : 
| [Monday 03 January 2011] [14:49:56] <CIA-21>	zeromq2: sunos/gcc3 compilation issue fixed
| [Monday 03 January 2011] [14:49:56] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/ezkv67
| [Monday 03 January 2011] [14:50:02] <sustrik>	mikko: try now
| [Monday 03 January 2011] [16:07:50] <mikko>	sustrik: i'll kick a build
| [Monday 03 January 2011] [16:08:16] <mikko>	building
| [Monday 03 January 2011] [16:16:11] <mikko>	passes
| [Monday 03 January 2011] [16:18:26] <sustrik>	great
| [Monday 03 January 2011] [16:26:09] <Thomas_aboutus>	I have what I'm sure is a super-noob question, but I've been over the docs a hundred times and can't figure out what I'm doing wrong. If someone can help me that would rock!
| [Monday 03 January 2011] [16:26:48] <Thomas_aboutus>	I am trying to make a simple pub/sub setup. I have the code here: https://gist.github.com/763990   For some reason, the subscriber never receives messages from the publisher. The code in the gist is as simple as I could make it for clarities sake.
| [Monday 03 January 2011] [16:36:08] <mikko>	Thomas_aboutus: both sockets connect
| [Monday 03 January 2011] [16:37:39] <mikko>	change the pub to bind and it should work
| [Monday 03 January 2011] [16:40:05] <Thomas_aboutus>	Wow... Thank you.
| [Monday 03 January 2011] [16:40:07] <Thomas_aboutus>	:)
| [Tuesday 04 January 2011] [00:42:35] <jugg>	I've done some work updating the zmq erlang bindings, for the most part things are working well now, but I'm running into issues with events on the socket FD (that was retrieved using ZMQ_FD getsockopt).  question: Can the FD be used in poll/select in one thread while the Socket is being used in other thread?  eg. the erlang vm sits on the FD in the poll/select call while waiting for an event and in the mean time other socket operations may be performe
| [Tuesday 04 January 2011] [01:45:35] <sustrik>	jugg: no
| [Tuesday 04 January 2011] [01:45:41] <sustrik>	sockets are not thread safe
| [Tuesday 04 January 2011] [01:46:02] <sustrik>	you can access a socket from at most one thread at a time
| [Tuesday 04 January 2011] [01:48:40] <jugg>	Is this zmq specific, or (I've not yet been able to find an answer) is it the case that a normal file descriptor would have problems if one thread used it in a poll() call, while another thread tried to read/write to it?
| [Tuesday 04 January 2011] [01:49:31] <sustrik>	normal FDs are thread safe
| [Tuesday 04 January 2011] [01:50:16] <sustrik>	0mq is special as it uses lock-free algorithms
| [Tuesday 04 January 2011] [01:50:32] <sustrik>	thus, it cannot synchronise the access using mutex or somesuch
| [Tuesday 04 January 2011] [01:51:32] <sustrik>	you can apply a mutex on top of it yourself, if that's what you need
| [Tuesday 04 January 2011] [01:51:40] <sustrik>	but be aware of the performance impact
| [Tuesday 04 January 2011] [01:51:42] <jugg>	What makes the socket FD different than a normal FD in this regards?
| [Tuesday 04 January 2011] [01:51:51] <jugg>	No, that isn't an option for the erlang bindings...
| [Tuesday 04 January 2011] [01:59:51] <neopallium>	jugg: the 0mq FD is just a socketpair to sent notices that there are messages/commands to read from the socket's queue.
| [Tuesday 04 January 2011] [02:00:47] <neopallium>	the message data you get from recv() is transferred in-memory from a lock-free queue, not over the socketpair.
| [Tuesday 04 January 2011] [02:02:58] <neopallium>	jugg: are you making a erlang port or a linked-in driver?
| [Tuesday 04 January 2011] [02:03:30] <jugg>	linked-in driver - its based off of the broken erlzmq bindings.
| [Tuesday 04 January 2011] [02:10:39] <jugg>	So if the socket FD is a socketpair, what makes it not usable in a poll call from one thread while another thread uses the socket?  Does zmq listen for events on the socket internally (outside of zmq_poll itself)?
| [Tuesday 04 January 2011] [02:11:45] <sustrik>	jugg: yes, it does so in zmq_send, zmq_recv and alike
| [Tuesday 04 January 2011] [02:12:50] <jugg>	ok... well, time to approach the erlang binding architecture differently then... :/
| [Tuesday 04 January 2011] [02:14:09] <neopallium>	sustrik: if the polling thread just calls poll() and not any zmq_* functions like zmq_poll(), would it still cause an issue?
| [Tuesday 04 January 2011] [02:14:33] <jugg>	if other parts of zmq consume the socketpair events, then yes...
| [Tuesday 04 January 2011] [02:14:35] <neopallium>	jugg: what is your polling thread doing with the events it gets back from the 0mq FD?
| [Tuesday 04 January 2011] [02:15:04] <jugg>	Notifies the socket owner thread and event occurred.
| [Tuesday 04 January 2011] [02:16:12] <jugg>	and => an
| [Tuesday 04 January 2011] [02:16:38] <neopallium>	ok, even if the owner thread gets a old POLLIN or POLLOUT event it can still try to call zmq_send/zmq_recv() with the NOBLOCK flag.
| [Tuesday 04 January 2011] [02:16:59] <neopallium>	it will just get an EAGAIN if it had already comsumed the event.
| [Tuesday 04 January 2011] [02:17:10] <jugg>	the problem is that it does not get a POLLIN/OUT event - as it appears the zmq internals are consuming those events...
| [Tuesday 04 January 2011] [02:17:23] <jugg>	which from sustrik's statement confirms this.
| [Tuesday 04 January 2011] [02:17:32] <neopallium>	do you use the NOBLOCK flag?
| [Tuesday 04 January 2011] [02:18:09] <jugg>	I don't see the relevance... the problem is the erlang poll is not being signaled an event occurred...
| [Tuesday 04 January 2011] [02:18:56] <neopallium>	your owner thread should be calling zmq_send()/zmq_recv() with the NOBLOCK flag, and only if it get EAGAIN, do it wait for an event notice from the polling thread.
| [Tuesday 04 January 2011] [02:18:57] <sustrik>	neopallium: getsockopt(ZMQ_EVENTS) consumes events from the socket pair
| [Tuesday 04 January 2011] [02:19:27] <neopallium>	sustrik: yes, and he should only call that from the owner thread not the poller thread.
| [Tuesday 04 January 2011] [02:20:39] <sustrik>	jugg: why do you need to combine recv and poll from different threads
| [Tuesday 04 January 2011] [02:20:52] <sustrik>	(i know, erlang is tricky)
| [Tuesday 04 January 2011] [02:21:46] <sustrik>	neopallium: i assume the problem is how erlang VM works
| [Tuesday 04 January 2011] [02:21:55] <sustrik>	it's kind of thread-agnostic
| [Tuesday 04 January 2011] [02:22:27] <neopallium>	jugg: have you tried an external C port?  it would make this must similar.
| [Tuesday 04 January 2011] [02:23:47] <neopallium>	sustrik: yeah, the book I have on erlang doesn't have much details about how the linked-in driver interface is effected by any internal threads that the erlang VM might have.
| [Tuesday 04 January 2011] [02:25:29] <sustrik>	the erlang binding is a troublesome one
| [Tuesday 04 January 2011] [02:25:39] <sustrik>	originally it was written by shammika pathirana
| [Tuesday 04 January 2011] [02:25:44] <jugg>	the only way to wait on an event in erlang is to provide the fd to the erlang vm.  The erlang vm, then calls the driver callback routine input/output_ready depending on the event type.  The callback is an arbitrary thread.   That callback checks the fd if an even actually occurred on the socket using getsockopt(ZMQ_EVENTS), and if so, then sends a notification back into the erlang world notifying an erlang process which owns the socket.  That erlang pr
| [Tuesday 04 January 2011] [02:25:51] <sustrik>	who had no erlang experience at the time afaik
| [Tuesday 04 January 2011] [02:26:06] <sustrik>	then it was fixed by serge aleynikov
| [Tuesday 04 January 2011] [02:26:26] <sustrik>	later on we've created some fixes when working on RabbitMQ/0MQ bridge with VMWare
| [Tuesday 04 January 2011] [02:26:29] <neopallium>	jugg: are you sure the vm is using a different polling thread from the callbacks?
| [Tuesday 04 January 2011] [02:26:32] <sustrik>	this are not yet in
| [Tuesday 04 January 2011] [02:26:34] <sustrik>	etc.
| [Tuesday 04 January 2011] [02:27:21] <jugg>	neopallium, the callback gets called from arbitrary threads... I don't know for sure if the poll is happening in the same thread or not.
| [Tuesday 04 January 2011] [02:28:54] <sustrik>	what about an alternative architecture: poll on FD, when signaled remove it from the pollset then read, when read is done, return it to the pollset
| [Tuesday 04 January 2011] [02:29:09] <neopallium>	jugg: why not do the zmq_recv() in the output_ready() callback instead of sending a notice to the erlang process (which is not a real thread/process).
| [Tuesday 04 January 2011] [02:30:17] <jugg>	sustrik, I'm already half way down that path...
| [Tuesday 04 January 2011] [02:30:58] <neopallium>	even if you are sending a notice back to the erlang process (saying hay you can read now), that erlang process will just send a port command which will be delivered to the port
| [Tuesday 04 January 2011] [02:30:59] <jugg>	neopallium, that has issues with multi-part messages... 
| [Tuesday 04 January 2011] [02:31:19] <neopallium>	the ports callbacks should be restricted to one thread.
| [Tuesday 04 January 2011] [02:31:36] <neopallium>	I don't see any warnings that linked-in drivers need to be thread-safe.
| [Tuesday 04 January 2011] [02:32:45] <neopallium>	jugg: do you deliver each part of the message in a different message back to the controlling process?
| [Tuesday 04 January 2011] [02:33:47] <jugg>	each erlzmq recv call acts just like zmq_recv.  It'll return each part separately.
| [Tuesday 04 January 2011] [02:34:58] <sustrik>	jugg: btw, there's a problem with erlzmq project now; as i've mentioned dhammika is not really an erlang guy and serge has unrelated problems now that prevent him from doing stuff
| [Tuesday 04 January 2011] [02:35:18] <sustrik>	in case you are interested i can give you commit access...
| [Tuesday 04 January 2011] [02:36:32] <jugg>	sustrik, let me get this working successfully, and I'll ping you then for access.
| [Tuesday 04 January 2011] [02:37:07] <sustrik>	jugg: ok, good
| [Tuesday 04 January 2011] [02:38:31] <sustrik>	there's also VMware patch that solves the sender-side backpressure IIRC
| [Tuesday 04 January 2011] [02:38:40] <jugg>	sustrik, just to clarify something.. you said getsockopt(ZMQ_EVENTS) consumes the socketpair events... do you mean payload or events that would trigger a waiting poll call?
| [Tuesday 04 January 2011] [02:38:40] 	 * sustrik makes a mental note that it has to be applied
| [Tuesday 04 January 2011] [02:39:30] <sustrik>	it consumes internal 0mq events from the socket pair
| [Tuesday 04 January 2011] [02:39:49] <neopallium>	jugg: it reads from the socketpair which will consume the POLLIN event from the FD
| [Tuesday 04 January 2011] [02:40:26] <sustrik>	let me give an overvirew of the achitecture
| [Tuesday 04 January 2011] [02:40:39] <sustrik>	the actual TCP sockets are handled by background threads
| [Tuesday 04 January 2011] [02:40:49] <sustrik>	making sending/receiving messages asynchronous
| [Tuesday 04 January 2011] [02:41:20] <sustrik>	the user's thread communicates with background (I/O) threads using so called 'commands'
| [Tuesday 04 January 2011] [02:41:41] <sustrik>	these are sent via a socketpair connecting the user thread and the I/O thread
| [Tuesday 04 January 2011] [02:42:14] <sustrik>	example of a command sent from I/O thread to user's thread would be "there are messages available for reading"
| [Tuesday 04 January 2011] [02:43:02] <sustrik>	when user's thread get that command it knows it can unblock (in case it's blocked in recv) and read new messages from the lock-free queue
| [Tuesday 04 January 2011] [02:43:16] <sustrik>	that's more or less it
| [Tuesday 04 January 2011] [02:45:48] <jugg>	are socketpairs ever shared with multiple zmq sockets?
| [Tuesday 04 January 2011] [02:46:18] <jugg>	or does every zmq socket have its own socketpair?
| [Tuesday 04 January 2011] [02:46:57] <sustrik>	every socket has it's own socketpair
| [Tuesday 04 January 2011] [02:47:11] <sustrik>	this is needed to be able to migrate sockets between threads
| [Tuesday 04 January 2011] [02:47:33] <sustrik>	so, to be precise, in 2.0.x multiple sockets share single socketpair
| [Tuesday 04 January 2011] [02:47:53] <sustrik>	in 2.1 there's one socketpair per 0mq socket
| [Tuesday 04 January 2011] [02:50:46] <jugg>	ok.  Thanks, this helps my mental picture.  I have a couple of approaches to test out now.
| [Tuesday 04 January 2011] [02:51:43] <sustrik>	good luck :)
| [Tuesday 04 January 2011] [02:52:30] <sustrik>	ah, btw, erlang binding works with 2.1 only anyway
| [Tuesday 04 January 2011] [02:52:53] <sustrik>	so you don't have to take the case where the socketpair is shared between sockets into account
| [Tuesday 04 January 2011] [02:54:24] <jugg>	yes
| [Tuesday 04 January 2011] [02:59:03] <neopallium>	jugg: I think you should only register events with driver_select() when the 0mq socket is blocked as reported by ZMQ_EVENTS.
| [Tuesday 04 January 2011] [02:59:47] <neopallium>	and when you are waiting for an event back from the vm don't call zmq_recv() or ZMQ_EVENTS until the event comes back.
| [Tuesday 04 January 2011] [03:00:15] <jugg>	that is interesting
| [Tuesday 04 January 2011] [03:00:20] <neopallium>	that way the owner thread can't consume events from the socketpair.
| [Tuesday 04 January 2011] [03:01:32] <neopallium>	I found the details about driver's and erlang threads.
| [Tuesday 04 January 2011] [03:01:54] <neopallium>	and by default the driver will only have one thread access it at a time.
| [Tuesday 04 January 2011] [03:02:19] <neopallium>	you can do locking at driver or port level, the default is locking at the driver level.
| [Tuesday 04 January 2011] [03:03:19] <neopallium>	if you don't share 0mq sockets between ports it should be possible to use port-level locking.
| [Tuesday 04 January 2011] [03:04:26] <neopallium>	also remember to remove the event notice from the socket after receiving the event and mark the socket as readable/writable.
| [Tuesday 04 January 2011] [03:05:38] <neopallium>	sustrik basically said the same thing earlier about removing the socket from the pollset (i.e. from driver_select()) when it is readable.
| [Tuesday 04 January 2011] [03:06:50] <jugg>	I'm not sure what you meant by "remove the event notice"... are you talking an implementation concept, or an erlang requirement?
| [Tuesday 04 January 2011] [03:07:44] <neopallium>	jugg: driver_select(port, event, mode, /* put 0 here. */)
| [Tuesday 04 January 2011] [03:08:14] <neopallium>	that last arg. is for clearing the event (i.e. removing it from the pollset)
| [Tuesday 04 January 2011] [03:09:27] <jugg>	yes.  But my understanding is (although it has been hard to find supporting evidence) that it isn't a requirement normally to do that in order for the erlang vm to report subsequent events on a fd.
| [Tuesday 04 January 2011] [03:10:17] <neopallium>	jugg: is your current problem that you are not receiving an event from the vm?
| [Tuesday 04 January 2011] [03:11:22] <jugg>	yes, but I think between sustrik's comment on getsockopt(ZMQ_EVENTS) consuming events, and his description on how things work, I can see why that is the case...
| [Tuesday 04 January 2011] [03:11:25] <neopallium>	0mq sockets are edge-triggered, that means you need to read from them until they will block (i.e. you get EAGAIN)
| [Tuesday 04 January 2011] [03:11:33] <jugg>	yes
| [Tuesday 04 January 2011] [03:12:57] <neopallium>	when your driver call getsockopt(ZMQ_EVENTS) and it says there is a message to read, then you need to mark the socket as readable, until you read a full message.
| [Tuesday 04 January 2011] [03:13:48] <neopallium>	once you read a full message call ZMQ_EVENTS again to check if there is another message to read, if it reports "no messages", then you wait for a read event from the vm.
| [Tuesday 04 January 2011] [03:14:32] <neopallium>	I think there was an example in the guide that use ZMQ_EVENTS like that.
| [Tuesday 04 January 2011] [03:14:54] <sustrik>	yes, more or less
| [Tuesday 04 January 2011] [03:15:06] <sustrik>	but you don't have to store the "readable" flag yourself
| [Tuesday 04 January 2011] [03:15:30] <sustrik>	you can retrieve it from 0mq by calling getsockop(ZMQ_EVENTS) actually
| [Tuesday 04 January 2011] [03:15:33] <jugg>	yes, I think the key is to implement a poll method which checks ZMQ_EVENTS prior to passing the fd to the erlang vm, and only do so if nothing is pending.
| [Tuesday 04 January 2011] [03:15:52] <sustrik>	yes
| [Tuesday 04 January 2011] [03:17:53] <neopallium>	jugg: is this driver pushing messages out to the controlling erlang process?  or does the erlang process block in a recv() type function for each message?
| [Tuesday 04 January 2011] [03:22:17] <jugg>	the driver returns messages only if the erlang process requests it via recv().   Of course, driver does not block in the recv() call, as that'd freeze the vm.  It later pushes the incoming message when it comes available - thus the driver must use the fd to be notified of such an event.  A gen_server is used to ensure further requests to the driver is not made, and the calling erlang process is blocked in the gen_server call until the driver eventually
| [Tuesday 04 January 2011] [03:22:56] <jugg>	of course the erlang process can call a non blocking recv as well.
| [Tuesday 04 January 2011] [03:23:25] <jugg>	(the old erlzmq did not support that last)
| [Tuesday 04 January 2011] [03:27:15] <jugg>	sustrik, does one only use the socketpair fd with POLLIN?  even if waiting for the zmq socket to become writeable?
| [Tuesday 04 January 2011] [03:28:10] <neopallium>	jugg: so the erlang sends the port a {call, recv} type message telling it to call zmq_recv() and send back a part of the message.
| [Tuesday 04 January 2011] [03:28:18] <sustrik>	jugg: yes
| [Tuesday 04 January 2011] [03:28:25] <sustrik>	POLLOUT makes no sense
| [Tuesday 04 January 2011] [03:28:31] <jugg>	sustrik, ok
| [Tuesday 04 January 2011] [03:29:55] <jugg>	neopallium, the driver will always call zmq_recv with NOBLOCK.  But if the erlang requests did not specify NOBLOCK, and zmq_recv returns EAGAIN, then the driver calls driver_select on the socket fd, and waits for an event, at which point it reads from the socket and returns the received message part to the erlang process.
| [Tuesday 04 January 2011] [03:29:56] <neopallium>	sustrik: so if the 0mq socket blocks on zmq_send(), do you have to wait for a POLLIN from the socketpair and the check with ZMQ_EVENTS if the socket is writable?
| [Tuesday 04 January 2011] [03:30:14] <sustrik>	yes
| [Tuesday 04 January 2011] [03:30:35] <sustrik>	the underlying socketpair is actually used for uni-directional transfer of commands
| [Tuesday 04 January 2011] [03:30:42] <neopallium>	ok, I need to fix my Lua async handler for 0mq sockets.
| [Tuesday 04 January 2011] [03:30:43] <sustrik>	so POLLOUT is always signaled
| [Tuesday 04 January 2011] [03:31:18] <sustrik>	i think it's mentioned in the reference
| [Tuesday 04 January 2011] [03:31:20] <sustrik>	let me check
| [Tuesday 04 January 2011] [03:31:24] <jugg>	sustrik, the docs could be clarified on that regards... It kind of says so, but it was unclear.
| [Tuesday 04 January 2011] [03:31:28] <neopallium>	yeah, I am basically doing a POLLOUT on the socketpair when zmq_send() returns EAGAIN.
| [Tuesday 04 January 2011] [03:32:07] <neopallium>	it is hard to test blocking on zmq_send()
| [Tuesday 04 January 2011] [03:32:17] <jugg>	indeed :/
| [Tuesday 04 January 2011] [03:32:42] <sustrik>	"0MQ library shall signal any pending events on the socket in an edge-triggered fashion by making the file descriptor become ready for reading"
| [Tuesday 04 January 2011] [03:33:00] <sustrik>	how would you reprharse that?
| [Tuesday 04 January 2011] [03:33:47] <neopallium>	.... signal any pending events from getsockopt(ZMQ_EVENTS...) when the FD is readable?
| [Tuesday 04 January 2011] [03:34:13] <sustrik>	i don't understand that :)
| [Tuesday 04 January 2011] [03:34:17] <sustrik>	maybe 2 sentences?
| [Tuesday 04 January 2011] [03:34:51] <neopallium>	it needs to say something about calling getsockopt(ZMQ_EVENTS...) for the ready events.
| [Tuesday 04 January 2011] [03:35:28] <sustrik>	"The ability to read from the returned file descriptor does not necessarily indicate that messages are available to be read from, or can be written to, the underlying socket; applications
| [Tuesday 04 January 2011] [03:35:29] <sustrik>	           must retrieve the actual event state with a subsequent retrieval of the ZMQ_EVENTS option."
| [Tuesday 04 January 2011] [03:35:43] <sustrik>	see zmq_getsockopt(3)
| [Tuesday 04 January 2011] [03:36:42] <neopallium>	how about something like: "0MQ library shall signal any pending events by making the FD readable, getsockopt(ZMQ_EVENTS...) returns which events are pending."
| [Tuesday 04 January 2011] [03:37:09] <sustrik>	that's better
| [Tuesday 04 January 2011] [03:37:26] <neopallium>	yeah, but not perfect
| [Tuesday 04 January 2011] [03:37:28] <sustrik>	but kind of duplicates what the note above says
| [Tuesday 04 January 2011] [03:38:42] <sustrik>	have a look at whole ZMQ_FD section and feel free to propose a better wording
| [Tuesday 04 January 2011] [03:40:28] <neopallium>	hmm, yeah I guess the original dues say that in the Note
| [Tuesday 04 January 2011] [03:41:49] <neopallium>	maybe just add a note that checking for POLLOUT on the FD is use-less for finding out if it is writable?
| [Tuesday 04 January 2011] [03:42:27] <jugg>	is it the case to mark the socketpair FD read, one must call getsockopt(ZMQ_EVENTS), else subsequent calls to poll will always return immediately?
| [Tuesday 04 January 2011] [03:44:51] <neopallium>	jugg: if you get a POLLIN event from poll() you will need to call getsockopt(ZMQ_EVENTS) to clear that event, or you will just keep getting the POLLIN.
| [Tuesday 04 January 2011] [03:46:38] <neopallium>	I think from a simple event loop it would be best to call getsockopt(ZMQ_EVENTS) on each POLLIN event and then dispatch the real POLLIN/POLLOUT events as returned from getsockopt(ZMQ_EVENTS).
| [Tuesday 04 January 2011] [03:47:10] <neopallium>	that is what I am going to try with my async. handlers.
| [Tuesday 04 January 2011] [03:49:50] <sustrik>	jugg: the event is cleared also when you call non-blocking recv() which returns with EAGAIN
| [Tuesday 04 January 2011] [04:26:50] <mikko>	good morning
| [Tuesday 04 January 2011] [04:53:03] <sustrik>	morning
| [Tuesday 04 January 2011] [04:57:17] <mikko>	hmm, [zeromq-dev] Segfault
| [Tuesday 04 January 2011] [04:57:26] <mikko>	looks like to be related to the HWM bug we discussed ages ago
| [Tuesday 04 January 2011] [04:58:05] <sustrik>	mikko: the one you've gave me the test case for?
| [Tuesday 04 January 2011] [04:58:24] <mikko>	sustrik: i think so
| [Tuesday 04 January 2011] [04:58:30] <sustrik>	i've looked into that but the problem was not obvious
| [Tuesday 04 January 2011] [04:58:47] <sustrik>	i'll have to look at it further
| [Tuesday 04 January 2011] [04:58:59] <mikko>	man, year after year it's harder to come back to work after holidays
| [Tuesday 04 January 2011] [04:59:27] <sustrik>	same here :)
| [Tuesday 04 January 2011] [05:15:22] <neopallium>	I hit this assertion in zeromq: Assertion failed: msg_->flags & ZMQ_MSG_MORE (rep.cpp:80)
| [Tuesday 04 January 2011] [05:15:53] <neopallium>	that is from a REP socket with a XREQ client.
| [Tuesday 04 January 2011] [05:16:27] <neopallium>	is it bad to connect a XREQ socket to a REP socket?
| [Tuesday 04 January 2011] [05:18:37] <neopallium>	hmm, looks like XREQ -> REP is a supported setup.
| [Tuesday 04 January 2011] [05:23:25] <jugg>	I believe REP socket expects at least two message parts, but three is needed.  <msg id> <empty msg> <msg body>.  Both <msg id> and <empty msg> should be sent with SNDMORE flag set.
| [Tuesday 04 January 2011] [05:26:55] <jugg>	basically, your application code on the xreq side passes in <msg body> (in one or more parts).  The xreq wrapper layer must then provide an identifier for that <msg body> and send that along to the rep socket, along with an empty message so that the rep socket and delineate between id parts and body parts.  When the rep socket responds, your xrep wrapper layer pulls off the msg id part and looks up who to route the body part to.
| [Tuesday 04 January 2011] [05:28:28] <jugg>	"...so that the rep socket can delineate.."
| [Tuesday 04 January 2011] [05:29:20] <neopallium>	jugg: yup, REQ/REP sockets hid the "address" part of the message, XREQ/XREP expose the "address" part.
| [Tuesday 04 January 2011] [05:30:00] <neopallium>	I am trying a manual example with the plain lua-zmq bindings to make sure it is not just my use of zmq that is cause it.
| [Tuesday 04 January 2011] [05:30:15] <jugg>	so, you were already sending along the message id and blank msg? 
| [Tuesday 04 January 2011] [05:30:37] <jugg>	with SNDMORE set?
| [Tuesday 04 January 2011] [05:31:39] <neopallium>	testing that right now, making a minimal example.
| [Tuesday 04 January 2011] [05:41:29] <neopallium>	jugg: https://gist.github.com/764629
| [Tuesday 04 January 2011] [05:42:33] <neopallium>	also sometime I got a crash on the XREQ side.
| [Tuesday 04 January 2011] [05:42:49] <neopallium>	but not an assertion, just a core dump.
| [Tuesday 04 January 2011] [05:43:23] <jugg>	I believe the delim needs to be empty, zero bytes.  You are sending a single byte.
| [Tuesday 04 January 2011] [05:43:46] <jugg>	try: s:send("", zmq.SNDMORE)
| [Tuesday 04 January 2011] [05:44:13] <neopallium>	ah, yeah, I just tried that and it worked
| [Tuesday 04 January 2011] [05:44:18] <jugg>	cool
| [Tuesday 04 January 2011] [05:44:41] <neopallium>	I don't know where I read to send "\0" as the delim. part
| [Tuesday 04 January 2011] [06:05:25] <orestis>	Hello, I'm wondering how 0mq fits in with a GUI event loop - is it safe to make 0mq requests from the GUI thread?
| [Tuesday 04 January 2011] [06:05:48] <mikko>	orestis: you mean whether it would block?
| [Tuesday 04 January 2011] [06:06:39] <mikko>	orestis: can you integrate external filehandle polling to your gui event loop?
| [Tuesday 04 January 2011] [06:06:59] <mikko>	you can get ZMQ_FD from the socket and use that event loop
| [Tuesday 04 January 2011] [06:07:08] <mikko>	then in the callback check for ZMQ_EVENTS 
| [Tuesday 04 January 2011] [06:29:35] <orestis>	Thanks. That looks a bit too cutting-edge for my taste. I guess my original question was, are the 0mq send/receive calls async? I'm a bit confused because there are mentions of background threads.
| [Tuesday 04 January 2011] [06:33:19] <mikko>	orestis: send/recv is async yes but there is a possiblity that the calls block
| [Tuesday 04 January 2011] [06:33:27] <mikko>	unless ZMQ_NOBLOCK is used
| [Tuesday 04 January 2011] [06:37:16] <orestis>	Thanks. In general, is 0mq a bit more low-level for doing async I/O from something like Twisted (that gives you Deferreds, Callbacks etc)?
| [Tuesday 04 January 2011] [06:38:16] <mikko>	orestis: i guess that is true. then again as far as i understand twisted is more general purpose ae framework where as 0mq is messaging stack
| [Tuesday 04 January 2011] [06:41:02] <orestis>	yes, apparently. I mainly wanted to use 0mq to split a monolithic gui app that does heavy I/O into separate processes. I definitely want to use Twisted for Deferreds and Callbacks (and Twisted plays well with GUIs) so I was wondering how to bring everything together.
| [Tuesday 04 January 2011] [06:42:25] <mikko>	orestis: you should be able to integrate 0mq into twisted
| [Tuesday 04 January 2011] [06:42:33] <mikko>	using the methods i mentioned earlier
| [Tuesday 04 January 2011] [06:44:05] <orestis>	mikko: they're not in the stable version though, are they?
| [Tuesday 04 January 2011] [06:45:05] <mikko>	orestis: if you mean 2.0.x then no
| [Tuesday 04 January 2011] [06:45:11] <mikko>	but 2.1.x seems fairly stable
| [Tuesday 04 January 2011] [06:45:19] <mikko>	i use github trunk in all my developments
| [Tuesday 04 January 2011] [07:14:53] <orestis>	mikko: thanks for your input. I'll see what I can come up with.
| [Tuesday 04 January 2011] [07:21:39] <jugg>	The documentation for ZMQ_IDENTITY is not clear to me.  I assume that the zmq context has to be maintained in order for a socket's identity to be re-usable?  But terminating the zmq context will lose the identity persistence?
| [Tuesday 04 January 2011] [10:55:17] <Seta00>	how do I build 0MQ with MinGW?
| [Tuesday 04 January 2011] [10:55:36] <mikko>	Seta00: configure && make && make install i guess
| [Tuesday 04 January 2011] [10:55:51] <mikko>	Seta00: i got mingw build running on linux machine
| [Tuesday 04 January 2011] [10:55:52] 	 * Seta00 installs MSYS
| [Tuesday 04 January 2011] [10:55:54] <Seta00>	:P
| [Tuesday 04 January 2011] [10:56:05] <mikko>	haven't tried on windows in a while
| [Tuesday 04 January 2011] [10:56:32] <mikko>	i got mingw32 on linux and VS2008 on windows in daily builds
| [Tuesday 04 January 2011] [10:56:43] <mikko>	maybe mingw32 on windows would be a good addition
| [Tuesday 04 January 2011] [10:57:26] <Seta00>	definitely :)
| [Tuesday 04 January 2011] [11:00:21] <Seta00>	working with various libraries can get messed up really fast
| [Tuesday 04 January 2011] [11:12:05] <Seta00>	msg_store.cpp:279: error: ISO C++ does not support `long long'
| [Tuesday 04 January 2011] [11:12:10] <Seta00>	why aren't things easier? hehe
| [Tuesday 04 January 2011] [11:13:17] <sustrik>	Set00: is that 2.0.10?
| [Tuesday 04 January 2011] [11:13:39] <Seta00>	sustrik, yes
| [Tuesday 04 January 2011] [11:13:52] <sustrik>	i recall the long long issue was being solved
| [Tuesday 04 January 2011] [11:13:59] <sustrik>	maybe it's fixed in 2.1
| [Tuesday 04 January 2011] [11:14:08] <sustrik>	mikko: don't you remember by chance?
| [Tuesday 04 January 2011] [11:14:46] <Seta00>	I'll try
| [Tuesday 04 January 2011] [11:26:16] <Seta00>	2.1.0 gives me ".../mingw/lib/dllcrt2.o: No such file or directory" when linking
| [Tuesday 04 January 2011] [11:27:32] <sustrik>	:|
| [Tuesday 04 January 2011] [11:28:53] <sustrik>	no idea what that is
| [Tuesday 04 January 2011] [11:28:57] <sustrik>	as for the long long problem
| [Tuesday 04 January 2011] [11:29:31] <sustrik>	iirc the problem is that long long is not part of C++ standard, yet it it used in Win32 signatures
| [Tuesday 04 January 2011] [11:29:37] <sustrik>	Win32 API
| [Tuesday 04 January 2011] [11:30:09] <Skaag>	I wonder if anyone else is using google protocol buffers to send messages over zmq
| [Tuesday 04 January 2011] [11:31:14] <Seta00>	I'm trying with uint64_t
| [Tuesday 04 January 2011] [11:33:42] <Seta00>	doesn't work
| [Tuesday 04 January 2011] [11:34:03] <Seta00>	how can I remove -Werror?
| [Tuesday 04 January 2011] [11:34:16] <Seta00>	other than manually editing the makefile?
| [Tuesday 04 January 2011] [11:35:32] <Seta00>	long works fine, but msys doesn`t find that DLL
| [Tuesday 04 January 2011] [11:40:26] <sustrik>	no idea, try checking configure.in
| [Tuesday 04 January 2011] [11:41:28] <Seta00>	forgot to configure fstab
| [Tuesday 04 January 2011] [11:42:39] <mikko>	sustrik: yes
| [Tuesday 04 January 2011] [11:42:48] <mikko>	ah, it was answered
| [Tuesday 04 January 2011] [11:42:58] <mikko>	long long problem is with 2.0.x
| [Tuesday 04 January 2011] [11:43:02] <mikko>	it's fixed in 2.1.0
| [Tuesday 04 January 2011] [11:43:48] <sustrik>	thx
| [Tuesday 04 January 2011] [11:46:20] <mikko>	Skaag: there has been a couple of mentions about that
| [Tuesday 04 January 2011] [11:46:31] <mikko>	Seta00: i can test mingw32 build when i get home
| [Tuesday 04 January 2011] [11:47:00] <Seta00>	mikko, it worked after I configured my fstab on MSYS
| [Tuesday 04 January 2011] [11:47:15] <Seta00>	thanks sustrik and mikko
| [Tuesday 04 January 2011] [11:47:37] <sustrik>	you are welcome
| [Tuesday 04 January 2011] [11:47:49] <Seta00>	now I need qmake to link to it :P
| [Tuesday 04 January 2011] [11:48:04] <Seta00>	which shall be solved in #qt
| [Tuesday 04 January 2011] [11:48:05] <Seta00>	:)
| [Tuesday 04 January 2011] [11:48:28] <mikko>	i remember someone doing this before
| [Tuesday 04 January 2011] [11:48:31] <mikko>	with qt toolchain
| [Tuesday 04 January 2011] [11:48:39] <mikko>	that sparked the whole fixing of mingw32 builds
| [Tuesday 04 January 2011] [12:28:58] <s0undt3ch>	with pyzmq, on a publisher subscriber model, I'm setting the publisher's identity, how can a subscriber retrieve that identity
| [Tuesday 04 January 2011] [12:28:59] <s0undt3ch>	?
| [Tuesday 04 January 2011] [12:31:53] <sustrik>	it can't
| [Tuesday 04 January 2011] [12:33:16] <s0undt3ch>	hmmm
| [Tuesday 04 January 2011] [12:33:25] <s0undt3ch>	I need to pass that on the message then
| [Tuesday 04 January 2011] [12:34:26] <sustrik>	yes, the identity is only internel per-hop mechanism
| [Tuesday 04 January 2011] [12:34:42] <sustrik>	it's not passed all the way down from publisher to subscriber
| [Tuesday 04 January 2011] [12:39:56] <s0undt3ch>	sustrik: same for req/rep right?
| [Tuesday 04 January 2011] [12:41:11] <Seta00>	s0undt3ch, are you on windows?
| [Tuesday 04 January 2011] [12:44:59] <sustrik>	same for all patterns
| [Tuesday 04 January 2011] [12:45:31] <sustrik>	req/rep is special in that identities are stuck to the request as it passes individual nodes
| [Tuesday 04 January 2011] [12:46:03] <sustrik>	but there's still no special mechanism to inspect peers' identities
| [Tuesday 04 January 2011] [12:48:35] <s0undt3ch>	Seta00: nope
| [Tuesday 04 January 2011] [12:49:01] <Seta00>	just checking if someone has a pyzmq build for Windows
| [Tuesday 04 January 2011] [13:54:20] <Joes_>	Hello. It is very tempting for me to use ZeroMQ, but I'm trying to figure out how architecture would look like. So, we have chat server (a-la IRC) with chat rooms.
| [Tuesday 04 January 2011] [13:54:40] <Joes_>	Users can join multiple rooms and I need to route messages between users in same room.
| [Tuesday 04 January 2011] [13:54:53] <Joes_>	As far as I understood tutorials, I need 2 connections
| [Tuesday 04 January 2011] [13:55:06] <Joes_>	one pubsub to send room events back to users
| [Tuesday 04 January 2011] [13:55:16] <Joes_>	and one pubsub to send events from users to rooms?
| [Tuesday 04 January 2011] [13:55:30] <Joes_>	can it be done with only one connection?
| [Tuesday 04 January 2011] [13:55:38] <Joes_>	(or socket)
| [Tuesday 04 January 2011] [14:16:49] <mikko>	Joes_: you would need two
| [Tuesday 04 January 2011] [14:17:34] <Joes_>	in terms of low level communication with tcp transport - two tcp ports on the server will be used
| [Tuesday 04 January 2011] [14:17:36] <Joes_>	correct?
| [Tuesday 04 January 2011] [14:17:44] <Joes_>	(firewall setup, etc)
| [Tuesday 04 January 2011] [14:18:04] <mikko>	Joes_: assuming you bind the two sockets then yet
| [Tuesday 04 January 2011] [14:18:07] <mikko>	yes*
| [Tuesday 04 January 2011] [14:18:10] <Joes_>	ok
| [Tuesday 04 January 2011] [14:18:19] <Joes_>	and second question - any bindings for Javascript?
| [Tuesday 04 January 2011] [14:18:31] <mikko>	i think someone was working for node.js bindings
| [Tuesday 04 January 2011] [14:18:34] <Joes_>	using WebSockets/socketjs/etc
| [Tuesday 04 January 2011] [14:18:42] <Joes_>	saw them
| [Tuesday 04 January 2011] [14:18:52] <Joes_>	includes native C code
| [Tuesday 04 January 2011] [14:19:02] <Joes_>	is wire protocol documented?
| [Tuesday 04 January 2011] [14:19:08] <mikko>	yes, i think it is
| [Tuesday 04 January 2011] [14:19:19] <mikko>	gimme a sec
| [Tuesday 04 January 2011] [14:20:39] <mikko>	here is the message format http://rfc.zeromq.org/spec:2
| [Tuesday 04 January 2011] [14:20:54] <Joes_>	thanks
| [Tuesday 04 January 2011] [14:20:57] <mikko>	let me see if the rest is documented
| [Tuesday 04 January 2011] [14:21:02] <Joes_>	going to see how long it will take to write dumb client in JS
| [Tuesday 04 January 2011] [14:21:25] <Joes_>	there's one for AMQP, but nothing for ZeroMQ
| [Tuesday 04 January 2011] [14:21:33] <Joes_>	and I don't need 95% of AMQP features...
| [Tuesday 04 January 2011] [14:22:38] <mikko>	are you going to do communications from browser straight to 0mq?
| [Tuesday 04 January 2011] [14:22:46] <Joes_>	well, that would be ideal
| [Tuesday 04 January 2011] [14:22:55] <mikko>	i don't think that's going to work
| [Tuesday 04 January 2011] [14:23:00] <mikko>	at least with websockets
| [Tuesday 04 January 2011] [14:23:12] <mikko>	as websockets have their own framing as well
| [Tuesday 04 January 2011] [14:23:25] <Joes_>	instead of making own wire protocol
| [Tuesday 04 January 2011] [14:23:40] <Joes_>	hm
| [Tuesday 04 January 2011] [14:23:43] <mikko>	have you looked into mongrel2?
| [Tuesday 04 January 2011] [14:24:04] <Joes_>	I did
| [Tuesday 04 January 2011] [14:24:14] <Joes_>	however, I can't find any benchmarks
| [Tuesday 04 January 2011] [14:24:20] <Joes_>	or who's using it in production
| [Tuesday 04 January 2011] [14:24:38] <mikko>	it's very new tech, i would be surprised if there are large installations yet
| [Tuesday 04 January 2011] [14:25:03] <mikko>	and i tend to find benchmarks mainly useless as there are a lot of people who don't know how to benchmark the software
| [Tuesday 04 January 2011] [14:25:08] <mikko>	or optimize it for benchmarking
| [Tuesday 04 January 2011] [14:25:27] <Joes_>	well, at least some rough numbers would help
| [Tuesday 04 January 2011] [14:25:34] <Joes_>	like faster than X Y times
| [Tuesday 04 January 2011] [14:27:12] <mikko>	but very often i find they are comparing apples to oranges
| [Tuesday 04 January 2011] [14:27:35] <mikko>	one tool with highly optimized config against incorrect config of other
| [Tuesday 04 January 2011] [14:27:49] <Joes_>	I see.
| [Tuesday 04 January 2011] [14:28:17] <mikko>	it's very hard to create good benchmarks
| [Tuesday 04 January 2011] [14:32:13] <mikko>	but communicating from browser you most likely need some sort of middle piece
| [Tuesday 04 January 2011] [14:32:36] <mikko>	probably doesn't need to be complicated but something that converts websocket messages to 0mq messages
| [Tuesday 04 January 2011] [14:32:40] <Joes_>	Let's assume I have middlepiece - some kind of broker between browser and 0MQ
| [Tuesday 04 January 2011] [14:32:45] <Joes_>	(thought about it)
| [Tuesday 04 January 2011] [14:32:49] <Joes_>	with some simple wire protocol
| [Tuesday 04 January 2011] [14:32:56] <sustrik>	i think that's mostly what mongrel2 does
| [Tuesday 04 January 2011] [14:33:01] <Joes_>	but I have following issues:
| [Tuesday 04 January 2011] [14:33:12] <Joes_>	1. Who will guarantee delivery, if client drops connection
| [Tuesday 04 January 2011] [14:33:26] <Joes_>	(I will need to queue up messages for this client till his next connection)
| [Tuesday 04 January 2011] [14:33:53] <Joes_>	well, there some other issues, but I don't remember them all :-)
| [Tuesday 04 January 2011] [14:33:57] <mikko>	if client drops connection do you want to queue messages?
| [Tuesday 04 January 2011] [14:34:08] <mikko>	for how long time after client leaves?
| [Tuesday 04 January 2011] [14:34:19] <Joes_>	I don't know if client dropped or temporary lost connection to the server and will reconnect shortly
| [Tuesday 04 January 2011] [14:34:30] <sustrik>	can be done using ZMQ_IDENTITY
| [Tuesday 04 January 2011] [14:34:39] <Joes_>	em
| [Tuesday 04 January 2011] [14:34:51] <Joes_>	let's say I'm am the server which handles requests from browsers.
| [Tuesday 04 January 2011] [14:34:59] <Joes_>	I accepted raw TCP connection (or websocket connection)
| [Tuesday 04 January 2011] [14:35:16] <Joes_>	so, for this connection, I will create 0MQ socket (or two, but it does not matter now)
| [Tuesday 04 January 2011] [14:35:24] <Joes_>	and will connect to the chat server
| [Tuesday 04 January 2011] [14:35:31] <sustrik>	right
| [Tuesday 04 January 2011] [14:35:41] <Joes_>	if incoming (browser) connection will drop
| [Tuesday 04 January 2011] [14:35:48] <Joes_>	I should close socket?
| [Tuesday 04 January 2011] [14:35:54] <Joes_>	(0MQ socket)
| [Tuesday 04 January 2011] [14:36:08] <sustrik>	no, 0MQ socket represents all the connections
| [Tuesday 04 January 2011] [14:36:17] <sustrik>	so closing it means closing all the connections
| [Tuesday 04 January 2011] [14:36:20] <Joes_>	hm
| [Tuesday 04 January 2011] [14:36:27] <Joes_>	1 socket for all incoming clients?
| [Tuesday 04 January 2011] [14:36:31] <sustrik>	yes
| [Tuesday 04 January 2011] [14:37:03] <Joes_>	who will be doing queuing of the messages for temporary disconnected clients?
| [Tuesday 04 January 2011] [14:37:14] <sustrik>	the server
| [Tuesday 04 January 2011] [14:37:39] <Joes_>	I see
| [Tuesday 04 January 2011] [14:37:41] <sustrik>	to be precise, the 0MQ socket in the server
| [Tuesday 04 January 2011] [14:37:45] <Joes_>	hm
| [Tuesday 04 January 2011] [14:38:03] <sustrik>	all you need to do is set the ZMQ_IDENTITY socket option on the client
| [Tuesday 04 January 2011] [14:38:37] <sustrik>	that way the server socket would know that is should not deallocate the connection when it accidentally breaks
| [Tuesday 04 January 2011] [14:38:46] <sustrik>	the messages will be stored
| [Tuesday 04 January 2011] [14:38:58] <sustrik>	and once the same client re-connects they will be sent
| [Tuesday 04 January 2011] [14:39:03] <Joes_>	that's the problem - I will have to write proxy between browser and 0MQ server
| [Tuesday 04 January 2011] [14:39:05] <mikko>	i think you are talking about separate issue
| [Tuesday 04 January 2011] [14:39:10] <mikko>	in this case:
| [Tuesday 04 January 2011] [14:39:33] <mikko>	chat server <-- 0mq --> broker <-- raw tcp --> client
| [Tuesday 04 January 2011] [14:39:38] <Joes_>	yep
| [Tuesday 04 January 2011] [14:40:33] <Joes_>	so, my question is - I'm adding extra logic on broker side to handle another wire protocol, message queuing (connection persistence logic like in 0MQ)
| [Tuesday 04 January 2011] [14:40:42] <Joes_>	is it worth of the trouble?
| [Tuesday 04 January 2011] [14:41:01] <Joes_>	broker can be "end point"
| [Tuesday 04 January 2011] [14:41:34] <Joes_>	not scalable solution, though
| [Tuesday 04 January 2011] [14:41:35] <mikko>	the only thing you have described about the application this far that it's a chat like irc
| [Tuesday 04 January 2011] [14:41:56] <Joes_>	yep, pretty much
| [Tuesday 04 January 2011] [14:42:03] <mikko>	is this from scratch or do you have something running already?
| [Tuesday 04 January 2011] [14:42:07] <Joes_>	scratch
| [Tuesday 04 January 2011] [14:42:12] <Joes_>	prototyping
| [Tuesday 04 January 2011] [14:43:04] <Joes_>	well, in terms of possible load - ~12k users average online
| [Tuesday 04 January 2011] [14:43:30] <Joes_>	each making ~1 message in 5 seconds (worst case)
| [Tuesday 04 January 2011] [14:43:49] <Joes_>	ajax with long polling does not suit very well
| [Tuesday 04 January 2011] [14:44:17] <mikko>	why do you need to queue the messages if the client drops?
| [Tuesday 04 January 2011] [14:44:20] <Joes_>	so, trying to find other possibilities apart of writing custom protocol on top of raw sockets
| [Tuesday 04 January 2011] [14:44:36] <Joes_>	to keep state of the room and its recent history
| [Tuesday 04 January 2011] [14:45:03] <Joes_>	it is doable by resending last N items on reconnect
| [Tuesday 04 January 2011] [14:45:19] <Joes_>	which solves the problem, but.. if 0MQ provides it for free..
| [Tuesday 04 January 2011] [14:49:14] <mikko>	let me think for a sec
| [Tuesday 04 January 2011] [14:49:28] <mikko>	the biggest problem is the last part to the browser
| [Tuesday 04 January 2011] [14:49:32] <Joes_>	yep
| [Tuesday 04 January 2011] [14:49:45] <Joes_>	I want to get rid of it by having simple, yet functional, 0mq client
| [Tuesday 04 January 2011] [14:50:01] <Joes_>	let's assume there's no WebSocket wrapping for now.
| [Tuesday 04 January 2011] [14:50:05] <Joes_>	plain tcp sockets
| [Tuesday 04 January 2011] [14:50:54] <mikko>	you are not in control of the client side i assume?
| [Tuesday 04 January 2011] [14:51:04] <mikko>	as in installing 0mq on client :)
| [Tuesday 04 January 2011] [14:51:16] <Joes_>	nope.
| [Tuesday 04 January 2011] [14:51:19] <Joes_>	plain HTML+JS
| [Tuesday 04 January 2011] [14:51:28] <Joes_>	and, maybe, some Flash.
| [Tuesday 04 January 2011] [14:51:50] <Joes_>	(I already checked almost all language integrations - all of them are dependent on the native C library)
| [Tuesday 04 January 2011] [14:54:36] <mikko>	yes, i think you would need to implement some logic in your broker
| [Tuesday 04 January 2011] [14:55:52] <Joes_>	in terms of code, for 1 incoming browser it will create 0mq socket or it will handle all incoming browser connections through 1 0mq socket?
| [Tuesday 04 January 2011] [14:55:55] <Joes_>	what is better approach?
| [Tuesday 04 January 2011] [14:56:37] <Joes_>	multiple sockets - free message queuing
| [Tuesday 04 January 2011] [14:56:57] <Joes_>	one socket - easier overall architecture (and speed?), but manual queuing on the broker
| [Tuesday 04 January 2011] [14:57:17] <Joes_>	plus, custom wire protocol from broker to browser
| [Tuesday 04 January 2011] [14:57:20] <Joes_>	etc.
| [Tuesday 04 January 2011] [14:57:31] <mikko>	one socket also requires custom filtering i guess
| [Tuesday 04 January 2011] [14:57:49] <mikko>	you got messages coming in 1 socket destined to ~12k clients
| [Tuesday 04 January 2011] [14:57:51] <Joes_>	well, I can read address from the message
| [Tuesday 04 January 2011] [14:58:00] <mikko>	so you need to write them to correct handles on other side
| [Tuesday 04 January 2011] [14:58:12] <Joes_>	and then pick proper browser socket and send it there
| [Tuesday 04 January 2011] [14:58:12] <Joes_>	yep
| [Tuesday 04 January 2011] [14:58:20] <Joes_>	it = message
| [Tuesday 04 January 2011] [14:59:02] <mikko>	one socket might be easier to handle for events as well
| [Tuesday 04 January 2011] [14:59:09] <mikko>	otherwise you got a pollset of 12k items
| [Tuesday 04 January 2011] [14:59:13] <mikko>	that you need to maintain
| [Tuesday 04 January 2011] [14:59:15] <Joes_>	yeah
| [Tuesday 04 January 2011] [14:59:19] <Joes_>	bad idea.
| [Tuesday 04 January 2011] [14:59:27] <Joes_>	ok, another idea.
| [Tuesday 04 January 2011] [14:59:39] <Joes_>	I write pure JS implementation of the wire protocol
| [Tuesday 04 January 2011] [14:59:43] <Joes_>	it's pretty simple
| [Tuesday 04 January 2011] [14:59:57] <Joes_>	and broker will be dump WebSocket negotiator and TCP proxy
| [Tuesday 04 January 2011] [15:00:07] <Joes_>	(forwards tcp connection to the real 0MQ server port)
| [Tuesday 04 January 2011] [15:00:14] <Joes_>	I assume it might work.
| [Tuesday 04 January 2011] [15:00:33] <Joes_>	each message sent will have address as a first chunk
| [Tuesday 04 January 2011] [15:00:46] <Joes_>	so chat server knows who sent it
| [Tuesday 04 January 2011] [15:00:54] <Joes_>	and, maybe, where
| [Tuesday 04 January 2011] [15:01:07] <Joes_>	dump = dumb
| [Tuesday 04 January 2011] [15:01:18] <mikko>	i think i wrote websocket daemon ages ago using libev
| [Tuesday 04 January 2011] [15:01:29] <mikko>	it wasn't complicated
| [Tuesday 04 January 2011] [15:03:57] <Joes_>	hm, someone already did it for Ruby
| [Tuesday 04 January 2011] [15:04:10] <Joes_>	https://github.com/andrewvc/dripdrop
| [Tuesday 04 January 2011] [15:04:28] <Joes_>	custom wire format from client
| [Tuesday 04 January 2011] [15:04:32] <andrewvc>	hey, that's me
| [Tuesday 04 January 2011] [15:04:35] <Joes_>	browser that is
| [Tuesday 04 January 2011] [15:04:36] <Joes_>	:-)
| [Tuesday 04 January 2011] [15:04:39] <Joes_>	wonderful
| [Tuesday 04 January 2011] [15:04:54] <Joes_>	there was pretty long discussion
| [Tuesday 04 January 2011] [15:05:04] <andrewvc>	oh?
| [Tuesday 04 January 2011] [15:05:16] <Joes_>	but, to sum it up - any plans for pure JS 0mq client instead of custom protocol?
| [Tuesday 04 January 2011] [15:05:18] <Joes_>	(or message format)
| [Tuesday 04 January 2011] [15:05:39] <Joes_>	so, you can get rid of Ruby server and just relay messages to 0mq
| [Tuesday 04 January 2011] [15:05:42] <Joes_>	straight
| [Tuesday 04 January 2011] [15:05:46] <andrewvc>	oh
| [Tuesday 04 January 2011] [15:05:54] <andrewvc>	well, there's a node JS project
| [Tuesday 04 January 2011] [15:06:05] <andrewvc>	and I was going to implement zmq_devices as part of ffi-rzmq as well
| [Tuesday 04 January 2011] [15:06:14] <andrewvc>	or do those options not cover it?
| [Tuesday 04 January 2011] [15:06:19] <Joes_>	node JS is using native C library
| [Tuesday 04 January 2011] [15:06:28] <Joes_>	I want something like DripDrop
| [Tuesday 04 January 2011] [15:06:31] <andrewvc>	oh
| [Tuesday 04 January 2011] [15:06:33] <andrewvc>	interesting
| [Tuesday 04 January 2011] [15:06:33] <Joes_>	browser <-> 0mq
| [Tuesday 04 January 2011] [15:06:40] <Joes_>	and simple TCP proxy
| [Tuesday 04 January 2011] [15:06:42] <Joes_>	in between
| [Tuesday 04 January 2011] [15:06:49] <andrewvc>	well, dripdrop doesn't really require zeromq
| [Tuesday 04 January 2011] [15:06:50] <Joes_>	which knows how to handle WebSocket handshake
| [Tuesday 04 January 2011] [15:06:53] <andrewvc>	it works well with websockets
| [Tuesday 04 January 2011] [15:06:56] <andrewvc>	and http
| [Tuesday 04 January 2011] [15:06:57] <andrewvc>	all evented
| [Tuesday 04 January 2011] [15:07:18] <andrewvc>	I'm a bit confused as to the actual question still I guess
| [Tuesday 04 January 2011] [15:07:21] <mikko>	andrewvc: but he wants to run this in browser
| [Tuesday 04 January 2011] [15:07:28] <mikko>	andrewvc: hence the pure js implementation i guess
| [Tuesday 04 January 2011] [15:07:34] <Joes_>	yes
| [Tuesday 04 January 2011] [15:07:43] <andrewvc>	ohhh, well who would the browser talk to. Itself?
| [Tuesday 04 January 2011] [15:07:51] <Joes_>	0mq server, preferably.
| [Tuesday 04 January 2011] [15:08:09] <Joes_>	here's another example: online real-time game.
| [Tuesday 04 January 2011] [15:08:11] <andrewvc>	oh, well, as far as I know you can't open a raw TCP conn from any browser still
| [Tuesday 04 January 2011] [15:08:17] <andrewvc>	so you're using websockets in the yes?
| [Tuesday 04 January 2011] [15:08:29] <Joes_>	socketjs also works
| [Tuesday 04 January 2011] [15:09:01] <Joes_>	(embeds small Flash object to proxy sockets)
| [Tuesday 04 January 2011] [15:09:09] <Joes_>	gives plain sockets in JS
| [Tuesday 04 January 2011] [15:09:41] <andrewvc>	yeah, so, that's an interesting idea
| [Tuesday 04 January 2011] [15:09:56] <Joes_>	I mean - sure, I can create custom protocol
| [Tuesday 04 January 2011] [15:10:00] <Joes_>	write custom server software
| [Tuesday 04 January 2011] [15:10:00] <andrewvc>	what kinds of implementation were you guys thinking?
| [Tuesday 04 January 2011] [15:10:06] <Joes_>	which will parse messages, etc
| [Tuesday 04 January 2011] [15:10:11] <Joes_>	but I dont see a point
| [Tuesday 04 January 2011] [15:10:52] <andrewvc>	what would the api look like, in JS?
| [Tuesday 04 January 2011] [15:11:04] <Joes_>	so, DripDrop already doing it - checked JS files, it is encapsulating messages into DD.Message
| [Tuesday 04 January 2011] [15:11:05] <andrewvc>	I think that's probably a good place to start, if you can throw up a gist for a simple case
| [Tuesday 04 January 2011] [15:11:09] <andrewvc>	yep
| [Tuesday 04 January 2011] [15:11:37] <andrewvc>	the JS prolly needs a little love at this point
| [Tuesday 04 January 2011] [15:12:15] <Joes_>	so, imagine that there's no need to have custom wire protocol (json serialized) and JS would just talk to 0mq server using 0mq wire protocol
| [Tuesday 04 January 2011] [15:12:48] <Joes_>	that's the simpliest case
| [Tuesday 04 January 2011] [15:13:18] <andrewvc>	hmmm, the 0mq wire protocol doesn't handle that much really
| [Tuesday 04 January 2011] [15:13:43] <andrewvc>	I mean, you could express multipart stuff, like socket identities for stuff like xreq/xrep
| [Tuesday 04 January 2011] [15:13:45] <Joes_>	browser won't be server either
| [Tuesday 04 January 2011] [15:13:49] <andrewvc>	but I'm not sure how useful that is
| [Tuesday 04 January 2011] [15:13:50] <Joes_>	sub or pub, mostly
| [Tuesday 04 January 2011] [15:13:59] <Joes_>	maybe req
| [Tuesday 04 January 2011] [15:14:13] <andrewvc>	I'm off to grab some lunch, but it's an interesting idea
| [Tuesday 04 January 2011] [15:14:20] <andrewvc>	I'd love to see a gist of a proposed API
| [Tuesday 04 January 2011] [15:14:26] <Joes_>	actually, from wire perspective it can be req
| [Tuesday 04 January 2011] [15:14:28] <Joes_>	always
| [Tuesday 04 January 2011] [15:14:37] <Joes_>	em, no.
| [Tuesday 04 January 2011] [15:14:40] <Joes_>	I need to get updates from server.
| [Tuesday 04 January 2011] [15:14:44] <Joes_>	anyway, I'll think about it.
| [Tuesday 04 January 2011] [15:14:53] <andrewvc>	yeah, I'd like to hear more
| [Tuesday 04 January 2011] [15:15:00] <Joes_>	it won't be full-scale 0mq implementation anyway
| [Tuesday 04 January 2011] [15:15:04] <andrewvc>	If you could ping me at @andrewvc on twitter when you have something I'd be interested
| [Tuesday 04 January 2011] [15:15:09] <andrewvc>	anyway, off to lunch
| [Tuesday 04 January 2011] [15:15:12] <Joes_>	k
| [Tuesday 04 January 2011] [15:15:24] <Joes_>	bon appetit
| [Tuesday 04 January 2011] [15:17:32] <Joes_>	Disconnected question - how do you handle security? If you don't want particular client to be connected, what you can do?
| [Tuesday 04 January 2011] [15:17:48] <Joes_>	so, I don't want malicious client to DOS my message queue
| [Tuesday 04 January 2011] [15:17:52] <Joes_>	can I forcibly disconnect him?
| [Tuesday 04 January 2011] [15:17:58] <Joes_>	(in my application)
| [Tuesday 04 January 2011] [15:20:29] <mikko>	hmm
| [Tuesday 04 January 2011] [15:20:47] <mikko>	was searching for 0mq on twitter and most of the results are people using "0mq" instead of "omg"
| [Tuesday 04 January 2011] [15:20:53] <Joes_>	:-)
| [Tuesday 04 January 2011] [15:24:09] <Joes_>	mikko: any hints on how to forcibly drop connections on server side?
| [Tuesday 04 January 2011] [15:25:44] <Joes_>	or 0mq not really suited for client-facing functionality?
| [Tuesday 04 January 2011] [15:26:51] <mikko>	there is really no way to forcibly drop a connection
| [Tuesday 04 January 2011] [15:27:02] <Joes_>	ouch.
| [Tuesday 04 January 2011] [15:27:12] <mikko>	apart from closing the socket
| [Tuesday 04 January 2011] [15:27:20] <Joes_>	on client side, I assume
| [Tuesday 04 January 2011] [15:27:21] <Joes_>	?
| [Tuesday 04 January 2011] [15:27:31] <mikko>	on the server-side but that closes all connections
| [Tuesday 04 January 2011] [15:27:39] <Joes_>	oops.
| [Tuesday 04 January 2011] [15:28:40] <Joes_>	means, 0mq not really suitable for client-facing stuff, as clients might misbehave
| [Tuesday 04 January 2011] [15:28:47] <Joes_>	plus, if there's some sort of authentication
| [Tuesday 04 January 2011] [15:28:56] <Joes_>	it's easier to disconnect client
| [Tuesday 04 January 2011] [15:29:01] <Joes_>	than to ignore all his sent messages
| [Tuesday 04 January 2011] [15:43:17] <sustrik>	what's the difference? a malevolent client can reconnect immediately and sent another malformed message
| [Tuesday 04 January 2011] [15:43:59] <sustrik>	the only consequence is that the server would use much more CPU to handle the reconnecting instead of simply dropping the messages
| [Tuesday 04 January 2011] [15:47:25] <Joes_>	yep
| [Tuesday 04 January 2011] [15:47:28] <Joes_>	but
| [Tuesday 04 January 2011] [15:47:35] <Joes_>	let's assume that it is pub/sub
| [Tuesday 04 January 2011] [15:47:41] <Joes_>	with, let's say 10 subscribers
| [Tuesday 04 January 2011] [15:48:15] <Joes_>	so, bad clients sends 1 message
| [Tuesday 04 January 2011] [15:48:47] <Joes_>	and 10 messages total are sent to subscribers
| [Tuesday 04 January 2011] [15:49:01] <Joes_>	effectively, network topology creates nice DOS environment
| [Tuesday 04 January 2011] [15:49:31] <Joes_>	bad client sends*
| [Tuesday 04 January 2011] [15:49:55] <Joes_>	I mean - there's no built-in security, so there's no way to filter these messages before they get into "internal" network
| [Tuesday 04 January 2011] [15:50:08] <Joes_>	where workers sit
| [Tuesday 04 January 2011] [15:56:16] <Joes_>	however, I think broker which will relay messages to internal network will work
| [Tuesday 04 January 2011] [15:56:26] <Joes_>	and he'll do the authentication stuff too
| [Tuesday 04 January 2011] [16:13:42] <mikko>	Joes_: it sounds like a sensible approach
| [Tuesday 04 January 2011] [20:47:48] <jugg>	sustrik, it would appear that 2.1.x C zmq_poll function needs to check ZMQ_EVENTS prior to polling the FD... yes?
| [Tuesday 04 January 2011] [20:49:53] <jugg>	btw, erlang bindings are functioning again... still some clean up work and consideration on how to expose certain aspects, but it is fairly usable now.
| [Tuesday 04 January 2011] [21:30:33] <jugg>	documentation bug: http://api.zeromq.org/zmq_send.html -> EFAULT incorrectly references 'context' rather than 'socket'.
| [Tuesday 04 January 2011] [23:56:48] <munin>	i have a python / zeromq question if anyone is active..? 
| [Tuesday 04 January 2011] [23:57:04] <munin>	i'm trying to get python 3.2 and zeromq to work and am having a problem importing zmq:
| [Tuesday 04 January 2011] [23:57:14] <munin>	ImportError: /home/munin/dbz-class/python/lib/python3.2/site-packages/zmq/core/poll.cpython-32m.so: undefined symbol: PyCObject_FromVoidPtr
| [Wednesday 05 January 2011] [01:31:27] <the_hulk>	hi, if i allocate a memory to zmq_msg_t pointer using malloc, then does zmq_msg_close frees the memory, or i would have to free it?
| [Wednesday 05 January 2011] [01:35:49] <jsimmons>	if you allocate it, you have to free it.
| [Wednesday 05 January 2011] [01:36:36] <the_hulk>	jsimmons, after zmq_msg_close, ok, thanks
| [Wednesday 05 January 2011] [04:03:53] <mikko>	the_hulk: you can use zmq_msg_init_data if you want the data to be freed when the message is freed
| [Wednesday 05 January 2011] [04:07:55] <the_hulk>	mikko, data, no, i was talking about zmq_msg_t struct
| [Wednesday 05 January 2011] [04:08:46] <mikko>	ah, ok
| [Wednesday 05 January 2011] [04:22:15] <mikko>	http://twitter.com/alexdong/statuses/22478134221733888
| [Wednesday 05 January 2011] [04:22:18] <mikko>	i don't get this
| [Wednesday 05 January 2011] [04:46:26] <the_hulk>	mikko, me too
| [Wednesday 05 January 2011] [05:35:25] <sustrik>	redis is a database, isn't it?
| [Wednesday 05 January 2011] [05:35:31] <sustrik>	some people have no clue
| [Wednesday 05 January 2011] [05:44:05] <mikko>	yes, it's a key-value store
| [Wednesday 05 January 2011] [05:51:31] <mikko>	https://github.com/mkoppanen/httpush
| [Wednesday 05 January 2011] [05:51:37] <mikko>	if anyone is interested in such a thing
| [Wednesday 05 January 2011] [05:54:55] <sustrik>	mikko: i am not a web developer so i cannot judge
| [Wednesday 05 January 2011] [05:55:20] <sustrik>	but i would definitely announce it on mailing list and add a link to zeromq.org labs page
| [Wednesday 05 January 2011] [05:55:26] <sustrik>	to make it more accessible
| [Wednesday 05 January 2011] [06:01:30] <neopallium>	mikko: that is similar to Mongrel2
| [Wednesday 05 January 2011] [06:01:36] <the_hulk>	mikko, mongrel?
| [Wednesday 05 January 2011] [06:02:22] <mikko>	neopallium: it doesn't really act as request reply web-server
| [Wednesday 05 January 2011] [06:02:35] <mikko>	i just needed a simple http->zeromq bridge for statistics collection
| [Wednesday 05 January 2011] [06:03:38] <neopallium>	so you can only push data to a 0mq socket? no responses back to the http client?
| [Wednesday 05 January 2011] [06:03:47] <mikko>	neopallium: yep
| [Wednesday 05 January 2011] [06:05:42] <the_hulk>	mikko, how does that help? i am quite new to this stuff..
| [Wednesday 05 January 2011] [06:06:02] <mikko>	the use-case for this was fairly simple
| [Wednesday 05 January 2011] [06:06:26] <mikko>	the initial use-case was just collecting web-statistics/analytics
| [Wednesday 05 January 2011] [06:07:27] <mikko>	so take a request from client, push to 0mq and analyse later in the background
| [Wednesday 05 January 2011] [06:08:09] <the_hulk>	and response?
| [Wednesday 05 January 2011] [06:08:16] <mikko>	static 200 OK
| [Wednesday 05 January 2011] [06:08:47] <mikko>	if you want to send proper responses to client you probably want something like mongrel2
| [Wednesday 05 January 2011] [06:19:49] <the_hulk>	yeah, i am trying mongrel2, but i am still not clear about httppush.. is it like backend for page tagging?
| [Wednesday 05 January 2011] [06:20:52] <mikko>	it just pushes http requests to 0mq
| [Wednesday 05 January 2011] [06:20:54] <mikko>	nothing more
| [Wednesday 05 January 2011] [06:21:06] <mikko>	not a bidirectional communication
| [Wednesday 05 January 2011] [06:21:54] <the_hulk>	hmm, looks good
| [Wednesday 05 January 2011] [06:22:42] <mikko>	it's for far simpler and specifc use-case than mongrel2
| [Wednesday 05 January 2011] [10:07:30] <jugg>	sustrik, in 2.1.x zmq_term is a blocking call, is there a way to check if it will block, or make it not block?   In the erlang bindings, this causes a problem, because it hard locks the erlang vm, not allowing the sockets to be cleaned up and closed (which would unblock the zmq_term call).  As such it turns into a dead lock.   Of course I can put smarts into the erlang driver to deal with this issue, but...
| [Wednesday 05 January 2011] [10:08:48] <mikko>	jugg: it blocks if there are sockets open
| [Wednesday 05 January 2011] [10:08:56] <mikko>	jugg: if you close all sockets first then it will not block
| [Wednesday 05 January 2011] [10:09:10] <jugg>	yes
| [Wednesday 05 January 2011] [10:09:12] <mikko>	jugg: currently there is no non-blocking version but there has been some discussion around it
| [Wednesday 05 January 2011] [10:10:36] <sustrik>	there are 2 distinct problems there
| [Wednesday 05 January 2011] [10:11:10] <sustrik>	1. the sockets have to be closed before zmq_term succeeds
| [Wednesday 05 January 2011] [10:11:39] <sustrik>	the reason is that otherwise you would destroy the sockets underneath running threads
| [Wednesday 05 January 2011] [10:11:52] <sustrik>	and end up with access violations etc.
| [Wednesday 05 January 2011] [10:12:20] <mikko>	there was the idea having a non-blocking call that just checks if sockets have been closed
| [Wednesday 05 January 2011] [10:12:30] <sustrik>	yes
| [Wednesday 05 January 2011] [10:12:46] <mikko>	does the following sound absurd:
| [Wednesday 05 January 2011] [10:12:55] <sustrik>	2. zmq_term() waits while the pending message are send to the wite
| [Wednesday 05 January 2011] [10:13:03] <mikko>	1. call zmq_term_nb(ctx);
| [Wednesday 05 January 2011] [10:13:11] <sustrik>	that one can be worked aeound by setting ZMQ_LINGER to 0
| [Wednesday 05 January 2011] [10:13:11] <jugg>	it'd be nice if it just returned with EAGAIN if there were open sockets, and have any blocking calls on the open sockets return with ETERM
| [Wednesday 05 January 2011] [10:13:20] <mikko>	2. context is marked "awaiting termination" and doesnt allow new sockets to be allocated
| [Wednesday 05 January 2011] [10:13:41] <mikko>	3. context automatically terminates after alst socket is done
| [Wednesday 05 January 2011] [10:13:45] <mikko>	is this even possible?
| [Wednesday 05 January 2011] [10:14:17] <mikko>	jugg: i guess that would be ideal
| [Wednesday 05 January 2011] [10:14:31] <sustrik>	1 and 2 is ok
| [Wednesday 05 January 2011] [10:14:32] <mikko>	but not sure if possible
| [Wednesday 05 January 2011] [10:14:37] <sustrik>	3 won't fly
| [Wednesday 05 January 2011] [10:15:01] <sustrik>	the problem is that what you noramally do is:
| [Wednesday 05 January 2011] [10:15:05] <sustrik>	zmq_term()
| [Wednesday 05 January 2011] [10:15:07] <sustrik>	exit()
| [Wednesday 05 January 2011] [10:15:17] <jugg>	zmq_term would have to be called again if it returned with eagain previously...
| [Wednesday 05 January 2011] [10:15:33] <sustrik>	thus the application exits even though there are pending messages there
| [Wednesday 05 January 2011] [10:15:48] <sustrik>	jugg: yes
| [Wednesday 05 January 2011] [10:16:33] <mikko>	sustrik: i see two problems here
| [Wednesday 05 January 2011] [10:16:40] <sustrik>	in short you need a point where the application can sleep waiting for 0mq to finish any work underway
| [Wednesday 05 January 2011] [10:16:43] <mikko>	well, one problem 
| [Wednesday 05 January 2011] [10:16:49] 	 * sustrik listens
| [Wednesday 05 January 2011] [10:16:57] <mikko>	the problem being that zmq_term doesn't indicate to sockets that they should exit
| [Wednesday 05 January 2011] [10:17:12] <sustrik>	?
| [Wednesday 05 January 2011] [10:17:17] <sustrik>	what about ETERM?
| [Wednesday 05 January 2011] [10:17:30] <mikko>	does it currently send eterm to sockets?
| [Wednesday 05 January 2011] [10:17:41] <mikko>	maybe im not handling that in my code properly
| [Wednesday 05 January 2011] [10:17:45] <sustrik>	after zmq_term() is called
| [Wednesday 05 January 2011] [10:17:54] <sustrik>	all the functions except amq_close() return ETERM
| [Wednesday 05 January 2011] [10:18:18] <mikko>	does that signal event in ZMQ_FD as well?
| [Wednesday 05 January 2011] [10:18:28] <sustrik>	good question
| [Wednesday 05 January 2011] [10:18:37] <sustrik>	probably yes
| [Wednesday 05 January 2011] [10:18:43] <sustrik>	not sure
| [Wednesday 05 January 2011] [10:18:43] <mikko>	maybe that was my problem as i am using libevent loop
| [Wednesday 05 January 2011] [10:19:14] <sustrik>	i would say
| [Wednesday 05 January 2011] [10:19:19] <sustrik>	fd should be signaled
| [Wednesday 05 January 2011] [10:19:35] <sustrik>	and getsockopt(zmq_events) should return ETERM
| [Wednesday 05 January 2011] [10:19:40] <mikko>	let me test
| [Wednesday 05 January 2011] [10:19:41] <sustrik>	but i never tried that
| [Wednesday 05 January 2011] [10:21:09] <jugg>	what happens of zmq_send is blocking, or if the last message was sent with SNDMORE?  Do only full message sets get sent?  Or does zmq_send not return with eterm?
| [Wednesday 05 January 2011] [10:22:10] <sustrik>	messages are atomic
| [Wednesday 05 January 2011] [10:22:15] <sustrik>	so, in this case
| [Wednesday 05 January 2011] [10:22:19] <jugg>	I assume, the linger option only deals with a fully atomic message set?
| [Wednesday 05 January 2011] [10:22:24] <sustrik>	zmq_send return ETERM
| [Wednesday 05 January 2011] [10:22:32] <sustrik>	but the message is not sent at all
| [Wednesday 05 January 2011] [10:22:40] <mikko>	https://gist.github.com/79d15fa01f0c7288f129
| [Wednesday 05 January 2011] [10:22:41] <mikko>	strange
| [Wednesday 05 January 2011] [10:22:56] <sustrik>	jugg: yes, half-sent messages are never delivered
| [Wednesday 05 January 2011] [10:24:28] <sustrik>	mikko: that's ETERM
| [Wednesday 05 January 2011] [10:24:42] <mikko>	yeah
| [Wednesday 05 January 2011] [10:24:50] <mikko>	so it does signal the ZMQ_FD
| [Wednesday 05 January 2011] [10:25:37] <sustrik>	ok, easy to fix
| [Wednesday 05 January 2011] [10:25:53] <sustrik>	just change line 270 to
| [Wednesday 05 January 2011] [10:26:03] <sustrik>	if (rc != 0 && (errno == EINTR || errno == ETERM))
| [Wednesday 05 January 2011] [10:27:21] <mikko>	sustrik: socket_base.cpp:272
| [Wednesday 05 January 2011] [10:27:24] <mikko>	yeah
| [Wednesday 05 January 2011] [10:57:35] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r472bdcd 10/ src/socket_base.cpp : 
| [Wednesday 05 January 2011] [10:57:35] <CIA-21>	zeromq2: Return ETERM from getsockopt(ZMQ_EVETS) if zmq_term() was called
| [Wednesday 05 January 2011] [10:57:35] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/hXhab5
| [Wednesday 05 January 2011] [12:29:53] <s0undt3ch>	hello ppl
| [Wednesday 05 January 2011] [12:30:42] <s0undt3ch>	I'm trying to use pyzmq withing a gobject mainloop, ie, I can't simple do while True: sock.recv()
| [Wednesday 05 January 2011] [12:30:47] <s0undt3ch>	so what are my options?
| [Wednesday 05 January 2011] [12:31:06] <s0undt3ch>	using the gobject mainlopp I can make a function run at a specific interval
| [Wednesday 05 January 2011] [12:31:25] <sustrik>	you can do non-blocking recv
| [Wednesday 05 January 2011] [12:31:34] <sustrik>	use ZMQ_NOBLOCK flag
| [Wednesday 05 January 2011] [12:32:50] <s0undt3ch>	sustrik: so, keep calling recv(zmq.NOBLOCK) untill I get an empty message meaning a message was completely sent?
| [Wednesday 05 January 2011] [12:33:26] <sustrik>	EAGAIN error ensues if there's nothing to receive
| [Wednesday 05 January 2011] [12:35:59] <s0undt3ch>	sustrik: k, Thanks
| [Wednesday 05 January 2011] [12:36:07] <sustrik>	np
| [Wednesday 05 January 2011] [12:36:10] <s0undt3ch>	sustrik: in which cases should we use poller?
| [Wednesday 05 January 2011] [12:36:26] <s0undt3ch>	might be unrelated
| [Wednesday 05 January 2011] [12:36:28] <sustrik>	if you need to use several sockets in parallel
| [Wednesday 05 January 2011] [12:36:55] <s0undt3ch>	sustrik: well, a daemonized process will need a req and a rep socket
| [Wednesday 05 January 2011] [12:37:00] <s0undt3ch>	is this such a case?
| [Wednesday 05 January 2011] [12:37:14] <sustrik>	if you need to use them from the same thread
| [Wednesday 05 January 2011] [12:37:20] <mikko>	s0undt3ch: ideal for you would be to use ZMQ_FD to get the filehandle
| [Wednesday 05 January 2011] [12:37:30] <mikko>	and gobject.add_watch to watch for activity on the handle
| [Wednesday 05 January 2011] [12:37:43] <mikko>	then in the callback check ZMQ_EVENTS and recv if there are events
| [Wednesday 05 January 2011] [12:37:50] <mikko>	i think
| [Wednesday 05 January 2011] [12:37:55] <mikko>	home ->
| [Wednesday 05 January 2011] [12:38:00] <s0undt3ch>	mikko: wow! Thanks! Have you done something like this?
| [Wednesday 05 January 2011] [12:38:06] <s0undt3ch>	mikko: any public code?
| [Wednesday 05 January 2011] [12:38:11] <mikko>	s0undt3ch: i've done something like this with libevent
| [Wednesday 05 January 2011] [12:38:17] <mikko>	i'll be back in an hour
| [Wednesday 05 January 2011] [12:38:19] <mikko>	->
| [Wednesday 05 January 2011] [12:38:28] <s0undt3ch>	mikko: please ping me when back
| [Wednesday 05 January 2011] [12:39:32] <s0undt3ch>	mikko: ah, zmq 2.1.0 right?
| [Wednesday 05 January 2011] [12:41:14] <sustrik>	yes, 2.1
| [Wednesday 05 January 2011] [12:43:05] <s0undt3ch>	hmm, guess I need to build both packages in order to support that
| [Wednesday 05 January 2011] [13:00:15] <s0undt3ch>	while trying to build pyzmq 2.1.0(git master) I'm getting http://paste.pocoo.org/show/315418/
| [Wednesday 05 January 2011] [13:04:03] <sustrik>	looks like mismatch btween 2.0 and 2.1
| [Wednesday 05 January 2011] [13:04:14] <sustrik>	aren't there old headers lingering somewhere?
| [Wednesday 05 January 2011] [13:05:31] <s0undt3ch>	sustrik: yes, the distro ones
| [Wednesday 05 January 2011] [13:05:35] <s0undt3ch>	ie, probably
| [Wednesday 05 January 2011] [13:07:00] <s0undt3ch>	sustrik: I need to remove all distro headers?
| [Wednesday 05 January 2011] [13:07:13] <s0undt3ch>	sustrik: I've specified the path to the new ones though
| [Wednesday 05 January 2011] [13:08:04] <sustrik>	there's some mismatch obviously
| [Wednesday 05 January 2011] [13:08:13] <s0undt3ch>	anyway I've downloaded the latest dev tar from the git downloads
| [Wednesday 05 January 2011] [13:08:14] <sustrik>	mikko should be able to help you with that
| [Wednesday 05 January 2011] [13:08:15] <s0undt3ch>	it now builds
| [Wednesday 05 January 2011] [13:08:17] <s0undt3ch>	though
| [Wednesday 05 January 2011] [13:08:43] <s0undt3ch>	http://paste.pocoo.org/show/315424/
| [Wednesday 05 January 2011] [13:15:37] <s0undt3ch>	it now does not finding the compiled lib
| [Wednesday 05 January 2011] [13:18:58] <s0undt3ch>	ok, tests work now
| [Wednesday 05 January 2011] [13:26:04] <s0undt3ch>	sustrik: there's no ZMQ_FD example in pyzmq's git is there?
| [Wednesday 05 January 2011] [13:26:28] <sustrik>	don't know
| [Wednesday 05 January 2011] [13:26:38] <sustrik>	you shoud ask brian or minrk
| [Wednesday 05 January 2011] [13:26:46] <sustrik>	those are pyzmq authors
| [Wednesday 05 January 2011] [13:26:56] <sustrik>	you can talk to them via mailing list
| [Wednesday 05 January 2011] [13:27:37] <sustrik>	ale uz si podpisla zmluvu na preklad :}
| [Wednesday 05 January 2011] [13:28:22] <sustrik>	oops, sorry
| [Wednesday 05 January 2011] [13:33:16] <mikko>	back
| [Wednesday 05 January 2011] [13:33:39] <s0undt3ch>	mikko: hello there again!
| [Wednesday 05 January 2011] [13:33:58] <s0undt3ch>	mikko: I've sucessfully built zmq and pyzmq 2.1.0 on my machine
| [Wednesday 05 January 2011] [13:34:16] <s0undt3ch>	mikko: your work with the ZMQ_FD is it public?
| [Wednesday 05 January 2011] [13:34:47] <s0undt3ch>	ie, just to get me some pointers on where to go next
| [Wednesday 05 January 2011] [13:34:58] <mikko>	yes
| [Wednesday 05 January 2011] [13:35:23] <mikko>	this is the callback https://github.com/mkoppanen/httpush/blob/master/src/httpd.c#L170
| [Wednesday 05 January 2011] [13:35:40] <s0undt3ch>	I can't seem to find any examples in pyzmq
| [Wednesday 05 January 2011] [13:35:43] <s0undt3ch>	ah, C ;)
| [Wednesday 05 January 2011] [13:35:55] <s0undt3ch>	I'll see if I can translate that to python....
| [Wednesday 05 January 2011] [13:35:59] 	 * s0undt3ch does not know C
| [Wednesday 05 January 2011] [13:36:25] <mikko>	initialized here https://github.com/mkoppanen/httpush/blob/master/src/server.c#L41
| [Wednesday 05 January 2011] [13:36:28] <mikko>	yes, C
| [Wednesday 05 January 2011] [13:36:47] <mikko>	is zmq_getsockopt ZMQ_FD available in python?
| [Wednesday 05 January 2011] [13:40:13] <s0undt3ch>	mikko: in 2.1.0 yes
| [Wednesday 05 January 2011] [13:40:17] <s0undt3ch>	I was able to get the FD
| [Wednesday 05 January 2011] [13:40:35] <mikko>	now you probably want to look into gobject.add_watch
| [Wednesday 05 January 2011] [13:41:58] <mikko>	i think
| [Wednesday 05 January 2011] [13:42:29] <mikko>	http://www.pygtk.org/pygtk2reference/gobject-functions.html#function-gobject--io-add-watch
| [Wednesday 05 January 2011] [13:42:32] <mikko>	this
| [Wednesday 05 January 2011] [13:43:01] <mikko>	pass the fd, gobject.IO_IN, and a callback
| [Wednesday 05 January 2011] [13:43:17] <mikko>	then in the callback you: zmq_getsockopt(ZMQ_EVENTS
| [Wednesday 05 January 2011] [13:43:24] <mikko>	and see if there are events available
| [Wednesday 05 January 2011] [13:43:28] <mikko>	and do a read
| [Wednesday 05 January 2011] [13:43:41] <mikko>	and remember that zeromq is edge-triggered rather than level-triggered
| [Wednesday 05 January 2011] [13:45:53] <s0undt3ch>	mikko: hmm, that means?
| [Wednesday 05 January 2011] [13:46:07] <mikko>	let's say you got 3 messages waiting in the socket
| [Wednesday 05 January 2011] [13:46:13] <mikko>	your callback gets triggered
| [Wednesday 05 January 2011] [13:46:23] <mikko>	you need to read all events in one go in the callback
| [Wednesday 05 January 2011] [13:46:51] <mikko>	the fd only triggers event when the state changes rather than "until there are messages"
| [Wednesday 05 January 2011] [13:48:06] <mikko>	if you look at this callback https://github.com/mkoppanen/httpush/blob/master/src/httpd.c#L170 you should understand the semantics even without understanding c
| [Wednesday 05 January 2011] [14:03:26] <s0undt3ch>	mikko: sorry, had to work a bit?
| [Wednesday 05 January 2011] [14:03:32] <s0undt3ch>	oops
| [Wednesday 05 January 2011] [14:03:43] <s0undt3ch>	forget the ?
| [Wednesday 05 January 2011] [14:03:51] <s0undt3ch>	mikko: I'll have a look a that code
| [Wednesday 05 January 2011] [14:03:54] <s0undt3ch>	mikko: Thanks!
| [Wednesday 05 January 2011] [14:04:12] <mikko>	no problem
| [Wednesday 05 January 2011] [14:28:13] <s0undt3ch>	mikko: working python example -> http://paste.pocoo.org/show/315462/
| [Wednesday 05 January 2011] [14:28:53] <s0undt3ch>	mikko: although I'm sending alot of messages, I aparently only handle one at a time, ie, events = subscriber.getsockopt(zmq.EVENTS) either returns 0 or 1
| [Wednesday 05 January 2011] [14:30:56] <s0undt3ch>	mikko: is there a way to test in order to get more than a single zmq message?
| [Wednesday 05 January 2011] [14:31:32] <s0undt3ch>	mikko: or socket.getsockopt(zmq.EVENTS) returns 0 or 1 in order to tell if there are events pending or not?
| [Wednesday 05 January 2011] [14:35:30] <s0undt3ch>	mikko: the same can be done for outgoing events?
| [Wednesday 05 January 2011] [14:35:30] <mikko>	if events == 0:
| [Wednesday 05 January 2011] [14:35:43] <mikko>	check if (events & ZMQ_POLLIN)
| [Wednesday 05 January 2011] [14:36:23] <mikko>	s0undt3ch: you could start your socket
| [Wednesday 05 January 2011] [14:36:31] <mikko>	sleep 5 seconds while sending messages at other end
| [Wednesday 05 January 2011] [14:36:37] <mikko>	and see how many you get in the callback
| [Wednesday 05 January 2011] [14:36:50] <mikko>	hmm that might not work well
| [Wednesday 05 January 2011] [14:36:55] <mikko>	or you could sleep in the callback
| [Wednesday 05 January 2011] [14:37:11] <mikko>	ah now i see
| [Wednesday 05 January 2011] [14:37:13] <mikko>	print 'GOT', events, 'EVENTS'
| [Wednesday 05 January 2011] [14:37:22] <s0undt3ch>	mikko: I tried sleeping in the callback, 1 message every time
| [Wednesday 05 January 2011] [14:37:25] <mikko>	events is a bitmask rather than number of events
| [Wednesday 05 January 2011] [14:37:29] <s0undt3ch>	ah
| [Wednesday 05 January 2011] [14:38:13] <s0undt3ch>	mikko: so "if events and zmq.POLLIN: break" right?
| [Wednesday 05 January 2011] [14:38:40] <mikko>	if (events & zmq.POLLIN) 
| [Wednesday 05 January 2011] [14:38:48] <mikko>	you can also check for if (events & zmq.POLLERR
| [Wednesday 05 January 2011] [14:39:36] <s0undt3ch>	thats in case of errors right?
| [Wednesday 05 January 2011] [14:40:15] <s0undt3ch>	recv() reads every message? or single message everytime?
| [Wednesday 05 January 2011] [14:41:11] <mikko>	single message at a time
| [Wednesday 05 January 2011] [14:41:14] <mikko>	thats why you loop
| [Wednesday 05 January 2011] [14:41:47] <s0undt3ch>	ok
| [Wednesday 05 January 2011] [14:42:08] <s0undt3ch>	so, it's working correctly, ie, with the changes you've said
| [Wednesday 05 January 2011] [14:45:12] <mikko>	it sounds like so
| [Wednesday 05 January 2011] [14:52:15] <s0undt3ch>	mikko: in case of (events & zmq.POLLERR) can we get the error?
| [Wednesday 05 January 2011] [14:53:16] <mikko>	im not sure
| [Wednesday 05 January 2011] [14:53:39] <mikko>	errno might or might not contain it
| [Wednesday 05 January 2011] [14:55:29] <s0undt3ch>	k
| [Wednesday 05 January 2011] [15:36:19] <s0undt3ch>	mikko: can it also be done for zmq.POLLOUT? or this does not make that much sense?
| [Wednesday 05 January 2011] [15:36:47] <s0undt3ch>	since in order to send a message we have to call .send()
| [Wednesday 05 January 2011] [15:36:57] <s0undt3ch>	which would send
| [Wednesday 05 January 2011] [15:37:03] <mikko>	yes, it ca be done with pollout as well
| [Wednesday 05 January 2011] [15:37:05] <s0undt3ch>	hmm, doesn't make that much sense
| [Wednesday 05 January 2011] [15:37:12] <mikko>	send could block
| [Wednesday 05 January 2011] [15:37:45] <mikko>	so you could either do a non-blocking send and check for the return code (EAGAIN) or poll
| [Wednesday 05 January 2011] [15:38:30] <mikko>	it might be easier just to send with ZMQ_NOBLOCK
| [Wednesday 05 January 2011] [15:38:34] <mikko>	and check for EINVAL
| [Wednesday 05 January 2011] [15:38:42] <mikko>	depending on socket type it might not even block
| [Wednesday 05 January 2011] [15:41:25] <s0undt3ch>	so, socket.send(msg, zmq.NOBLOCK) and have gobject listening on the fd for gobject.IO_OUT, then on the callback check for zmq.EINVAL meaning message was completely sent?
| [Wednesday 05 January 2011] [15:44:27] <s0undt3ch>	mikko: makes sense?
| [Wednesday 05 January 2011] [15:44:41] <mikko>	no
| [Wednesday 05 January 2011] [15:44:56] <mikko>	socket.send(msg, zmq.NOBLOCK)
| [Wednesday 05 January 2011] [15:45:00] <mikko>	then check errno
| [Wednesday 05 January 2011] [15:45:17] <mikko>	if errno == einval, schedule gobject io_out
| [Wednesday 05 January 2011] [15:45:26] <mikko>	and send message when it's signaled ready
| [Wednesday 05 January 2011] [15:45:27] <mikko>	maybe
| [Wednesday 05 January 2011] [15:57:56] <s0undt3ch>	mikko: my example -> http://paste.pocoo.org/show/315517/ <- though I don't think it makes that much sense
| [Wednesday 05 January 2011] [15:58:31] <s0undt3ch>	and I don't know how to schedule a gobject io_out
| [Wednesday 05 January 2011] [16:01:33] <s0undt3ch>	messages get through, but I don't think this is what you were saying
| [Wednesday 05 January 2011] [16:05:31] <mikko>	ZMQ_PUB socket wont block
| [Wednesday 05 January 2011] [16:05:43] <mikko>	so you dont need to worry about that really
| [Wednesday 05 January 2011] [16:06:46] <s0undt3ch>	mikko: REQ/REP will?
| [Wednesday 05 January 2011] [16:07:05] <s0undt3ch>	the purpose of this was actually for REQ/REP
| [Wednesday 05 January 2011] [16:07:18] <mikko>	some sockets block depending on situation
| [Wednesday 05 January 2011] [16:07:20] <s0undt3ch>	PUB/SUB was some existing code I had lying arround
| [Wednesday 05 January 2011] [16:07:59] <mikko>	let me see if i can write understandable python
| [Wednesday 05 January 2011] [16:08:43] <s0undt3ch>	ah
| [Wednesday 05 January 2011] [16:08:54] <s0undt3ch>	making those REQ/REP I'm getting Operation cannot be accomplished in current state
| [Wednesday 05 January 2011] [16:09:22] <s0undt3ch>	mikko: that would be wonderful!
| [Wednesday 05 January 2011] [16:09:25] <mikko>	where you have if e.errno == zmq.EINVAL:
| [Wednesday 05 January 2011] [16:09:44] <mikko>	if you check for zmq.EAGAIN
| [Wednesday 05 January 2011] [16:09:53] <mikko>	EAGAIN means that the operation would have blocked
| [Wednesday 05 January 2011] [16:10:01] <mikko>	so if e.errno == zmq.EAGAIN
| [Wednesday 05 January 2011] [16:10:10] <mikko>	schedule io watcher there for IO_OUT
| [Wednesday 05 January 2011] [16:10:21] <mikko>	it should be called when the socket becomes writable
| [Wednesday 05 January 2011] [16:10:33] <mikko>	and in the callback:
| [Wednesday 05 January 2011] [16:10:41] <mikko>	if you have sent everything, do not reschedule event
| [Wednesday 05 January 2011] [16:10:57] <mikko>	if you get EAGAIN in the callback before sending all messages, reschedule event
| [Wednesday 05 January 2011] [16:11:03] <mikko>	do you follow?
| [Wednesday 05 January 2011] [16:11:07] <s0undt3ch>	mikko: I think so
| [Wednesday 05 January 2011] [16:11:21] <mikko>	let's say you need to send out 100 messages
| [Wednesday 05 January 2011] [16:11:33] <mikko>	you are happily sending messages but on message 59 you get EAGAIN
| [Wednesday 05 January 2011] [16:11:57] <mikko>	which means that the operation would block. so you schedule io_watcher for the outgoing socket 
| [Wednesday 05 January 2011] [16:12:12] <mikko>	the callback gets called when the socket is ready to receive more message
| [Wednesday 05 January 2011] [16:12:13] <mikko>	s
| [Wednesday 05 January 2011] [16:12:24] <mikko>	so then you keep on sending where you left 
| [Wednesday 05 January 2011] [16:12:55] <mikko>	if you hit EAGAIN then return true (that seems to be the way gobject reschedules the event)
| [Wednesday 05 January 2011] [16:13:03] <mikko>	if you have sent everything return false
| [Wednesday 05 January 2011] [16:18:30] Notice	-NickServ- This nickname is registered. Please choose a different nickname, or identify via /msg NickServ identify <password>.
| [Wednesday 05 January 2011] [16:18:30] Notice	-NickServ- You are now identified for travlr.
| [Wednesday 05 January 2011] [16:24:41] <s0undt3ch>	mikko: as it is now -> http://paste.pocoo.org/show/315529/ <- I'm getting "Operation cannot be accomplished in current state", errno is 156384763
| [Wednesday 05 January 2011] [16:24:55] <s0undt3ch>	ie, no messages are beeing sent as it is
| [Wednesday 05 January 2011] [16:31:10] <mikko>	request-reply is strict on the pattern
| [Wednesday 05 January 2011] [16:31:26] <mikko>	recv -> send -> recv -> send etc
| [Wednesday 05 January 2011] [16:31:48] <s0undt3ch>	ah, the socket hasn't received anyting so it can't send
| [Wednesday 05 January 2011] [16:32:27] <s0undt3ch>	I think for now I won't worry about this, right now I'm worried about async handling on incoming messages
| [Wednesday 05 January 2011] [16:51:14] <mikko>	s0undt3ch: you might want to look into XREP/XREQ as well
| [Wednesday 05 January 2011] [16:51:31] <s0undt3ch>	mikko: big diferences?
| [Wednesday 05 January 2011] [16:51:53] <s0undt3ch>	mikko: I'm looking at REQ/REP to create a kind of rpc through zmq messaging
| [Wednesday 05 January 2011] [16:52:05] <s0undt3ch>	*rpc client/server
| [Wednesday 05 January 2011] [16:59:56] <mikko>	then maybe rep/req might be in place
| [Wednesday 05 January 2011] [17:00:03] <mikko>	are you going to have multiple worker processes?
| [Wednesday 05 January 2011] [17:01:20] <s0undt3ch>	mikko: yes, different ones, ie, each worker, the replier, will handle a specific job, the rpc is for them
| [Wednesday 05 January 2011] [17:01:32] <s0undt3ch>	mikko: my "problem" at hands is
| [Wednesday 05 January 2011] [17:02:52] <s0undt3ch>	I'll have several processes analysing diferent audio sources through gstreamer. when a problem on that audio source is found, a pub message is sent. However then need to be controllable, hence the rpc(REQ) need for them
| [Wednesday 05 January 2011] [17:03:08] <s0undt3ch>	s/then need/they need/
| [Wednesday 05 January 2011] [17:03:43] <s0undt3ch>	a client should be able to control a single or all of those gstreamer processes
| [Wednesday 05 January 2011] [17:24:47] <s0undt3ch>	mikko: does my needs apply for XREQ/XREP?
| [Wednesday 05 January 2011] [17:25:09] <mikko>	probably not 
| [Wednesday 05 January 2011] [17:25:17] <mikko>	xreq/xrep doesn't enforce the pattern
| [Wednesday 05 January 2011] [17:25:22] <mikko>	recv/send/recv/send
| [Wednesday 05 January 2011] [17:27:30] <s0undt3ch>	ah ok
| [Wednesday 05 January 2011] [17:27:54] <s0undt3ch>	mikko: those would be good for my testing needs, but not for the actual project
| [Wednesday 05 January 2011] [17:27:56] <s0undt3ch>	Thanks!
| [Wednesday 05 January 2011] [18:26:58] <s0undt3ch>	on a rep socket, can we know "who" is making the request?
| [Thursday 06 January 2011] [01:52:43] <Malinga>	hi all i have a question to be asked
| [Thursday 06 January 2011] [01:53:35] <Malinga>	about how to use OpenAMQ or ZeroMQ to deliver market data (quote server)
| [Thursday 06 January 2011] [01:53:44] <Malinga>	*effectively
| [Thursday 06 January 2011] [01:56:00] <Malinga>	hi any one there to help my technical question
| [Thursday 06 January 2011] [02:00:54] <sustrik>	what's the problem?
| [Thursday 06 January 2011] [02:02:48] <Malinga>	We are developing a Quote Server which will be handel the market data and deliver it to the end client
| [Thursday 06 January 2011] [02:02:59] <Malinga>	we are think of using a SOA architecture for this
| [Thursday 06 January 2011] [02:03:46] <Malinga>	So can u tell me some information how to use OpenAMQ to make this happen
| [Thursday 06 January 2011] [02:04:06] <guido_g>	hrhrhr
| [Thursday 06 January 2011] [02:04:10] <Malinga>	i used openamq 3 years back in my previous company as a middleware
| [Thursday 06 January 2011] [02:04:12] <guido_g>	sorry
| [Thursday 06 January 2011] [02:04:37] <sustrik>	openamq or 0mq?
| [Thursday 06 January 2011] [02:04:42] <Malinga>	but now i want to use it to deliver market data effectlvely and use this openAMQ as a quote server
| [Thursday 06 January 2011] [02:04:52] <Malinga>	any idas ?
| [Thursday 06 January 2011] [02:04:52] <guido_g>	you did realize that zeromq is not related to openamq?
| [Thursday 06 January 2011] [02:05:09] <Malinga>	if zeroMQ is better approach i can use ithat even
| [Thursday 06 January 2011] [02:06:03] <guido_g>	no its not better
| [Thursday 06 January 2011] [02:06:10] <guido_g>	its different
| [Thursday 06 January 2011] [02:06:20] <Malinga>	any architecture gudes that u can give sustrik ...
| [Thursday 06 January 2011] [02:08:21] <Malinga>	so can i use zero MQ for my senario
| [Thursday 06 January 2011] [02:08:26] <sustrik>	Malinga: on the quote publisher open a PUB socket
| [Thursday 06 January 2011] [02:08:32] <sustrik>	send the quotes to the socket
| [Thursday 06 January 2011] [02:08:42] <sustrik>	on clients, open a SUB socket
| [Thursday 06 January 2011] [02:08:54] <sustrik>	do your subscriptions
| [Thursday 06 January 2011] [02:09:00] <sustrik>	and recv() the messages
| [Thursday 06 January 2011] [02:09:02] <sustrik>	that's all
| [Thursday 06 January 2011] [02:09:04] <Malinga>	listning
| [Thursday 06 January 2011] [02:09:39] <Malinga>	this is via openAMQ right ?
| [Thursday 06 January 2011] [02:09:48] <sustrik>	no, it's 0mq
| [Thursday 06 January 2011] [02:09:53] <Malinga>	sorry
| [Thursday 06 January 2011] [02:09:54] <Malinga>	ok
| [Thursday 06 January 2011] [02:10:16] <Malinga>	so u think we can use the 0MQ to our market data quote server ?
| [Thursday 06 January 2011] [02:10:23] <sustrik>	yes
| [Thursday 06 January 2011] [02:10:27] <Malinga>	cool
| [Thursday 06 January 2011] [02:10:39] <sustrik>	have a look at 0mq guide
| [Thursday 06 January 2011] [02:10:45] <Malinga>	do u have some high level architecture on this is possible
| [Thursday 06 January 2011] [02:10:58] <sustrik>	there's an example of -- i think -- distributing weather forecase
| [Thursday 06 January 2011] [02:11:03] <sustrik>	forecast
| [Thursday 06 January 2011] [02:11:12] <Malinga>	hmmm
| [Thursday 06 January 2011] [02:11:21] <sustrik>	it's basically the same as you need for stock quotes
| [Thursday 06 January 2011] [02:11:52] <Malinga>	so like in openAMQ do we have to have per symbol queues sorry i dont have much ida about 0MQ
| [Thursday 06 January 2011] [02:12:39] <sustrik>	what do you need it for?
| [Thursday 06 January 2011] [02:12:55] <sustrik>	fair balancing between individual symbols?
| [Thursday 06 January 2011] [02:14:16] <Malinga>	u mean per symbol queues ?
| [Thursday 06 January 2011] [02:16:33] <Malinga>	what is the better open 0MQ or OpenAMQ for my quote server
| [Thursday 06 January 2011] [02:17:07] <sustrik>	openamq is a legacy technology
| [Thursday 06 January 2011] [02:17:15] <sustrik>	so i would recommend 0mq
| [Thursday 06 January 2011] [02:17:22] <sustrik>	it's also much easier to use
| [Thursday 06 January 2011] [02:17:31] <sustrik>	and you don't need the broker
| [Thursday 06 January 2011] [02:17:39] <sustrik>	which makes administration easier
| [Thursday 06 January 2011] [02:17:47] <Malinga>	cool
| [Thursday 06 January 2011] [02:18:14] <Malinga>	but our entire application (end clients) is in Java and hope to write back end also in java
| [Thursday 06 January 2011] [02:18:21] <sustrik>	sure
| [Thursday 06 January 2011] [02:18:29] <sustrik>	check java 0mq bindings
| [Thursday 06 January 2011] [02:18:35] <Malinga>	u have java wrappers right ?
| [Thursday 06 January 2011] [02:18:38] <sustrik>	yes
| [Thursday 06 January 2011] [02:19:06] <Malinga>	realiable as C++ ? i mean java wrappers ?
| [Thursday 06 January 2011] [02:19:19] <sustrik>	it's wrapper on top of C
| [Thursday 06 January 2011] [02:19:27] <sustrik>	so it's the same thing
| [Thursday 06 January 2011] [02:19:31] <Malinga>	JNI /
| [Thursday 06 January 2011] [02:19:34] <Malinga>	JNI ?
| [Thursday 06 January 2011] [02:19:34] <sustrik>	yes
| [Thursday 06 January 2011] [02:19:37] <Malinga>	hmmm
| [Thursday 06 January 2011] [02:19:39] <Malinga>	ok
| [Thursday 06 January 2011] [02:19:44] <Malinga>	let me read 0MQ
| [Thursday 06 January 2011] [02:19:53] <Malinga>	and come back to u in a few days
| [Thursday 06 January 2011] [02:20:12] <sustrik>	you are welcome
| [Thursday 06 January 2011] [02:20:52] <Malinga>	anyway thanks so much for all those informatin, i still can remember u helped me allot (u may not rememebr now) few years back also
| [Thursday 06 January 2011] [02:21:06] <Malinga>	when im doing another system with openAMQ
| [Thursday 06 January 2011] [02:21:11] <Malinga>	it was a gr8 sucess
| [Thursday 06 January 2011] [02:21:14] <Malinga>	thanks
| [Thursday 06 January 2011] [02:21:18] <Malinga>	and bye for now
| [Thursday 06 January 2011] [02:21:40] <sustrik>	i remember your nick :)
| [Thursday 06 January 2011] [02:21:42] <sustrik>	see you
| [Thursday 06 January 2011] [02:42:31] <CIA-21>	zeromq2: 03Min Ragan-Kelley 07master * r08cd2ce 10/ (AUTHORS include/zmq.h include/zmq_utils.h): 
| [Thursday 06 January 2011] [02:42:31] <CIA-21>	zeromq2: resolve "function declaration isn't a prototype"
| [Thursday 06 January 2011] [02:42:31] <CIA-21>	zeromq2: change two declarations in headers to form f(void); instead of f();
| [Thursday 06 January 2011] [02:42:31] <CIA-21>	zeromq2: which eliminates the warnings when compiling against zeromq
| [Thursday 06 January 2011] [02:42:31] <CIA-21>	zeromq2: Signed-off-by: MinRK <benjaminrk@gmail.com> - http://bit.ly/fIJTkE
| [Thursday 06 January 2011] [04:14:13] <mikko>	good morning
| [Thursday 06 January 2011] [04:29:44] <sustrik>	morning
| [Thursday 06 January 2011] [05:13:38] <jugg>	After calling zmq_send(..., ZMQ_SNDMORE), is there a way to abort the transfer without sending the final message part?  eg. If an application error occurs disallowing sending the final part(s), is closing the socket the only way to recover?
| [Thursday 06 January 2011] [05:16:03] <jugg>	A reset socket option would be nice...
| [Thursday 06 January 2011] [05:18:24] <mikko>	you mean reset as in send empty message part or a part flagged as "reset" ?
| [Thursday 06 January 2011] [05:32:55] <jugg>	I mean, abort the sending of the message parts (don't send them over the wire).  Which they aren't at this point.   However, currently either you have to send another message without sndmore set, thus the entire bad message is put on the wire, or you have to close the socket.
| [Thursday 06 January 2011] [05:35:38] <sustrik>	jugg: what are you trying to achieve?
| [Thursday 06 January 2011] [05:35:56] <sustrik>	how come the message is "bad"?
| [Thursday 06 January 2011] [05:36:26] <jugg>	the message is incomplete... the application code generating the message parts can not finish.
| [Thursday 06 January 2011] [05:37:23] <jugg>	Of course, the application code could wait until the entire message is built, but that isn't always interesting.
| [Thursday 06 January 2011] [05:38:12] <sustrik>	so what happens?
| [Thursday 06 January 2011] [05:38:17] <sustrik>	something like timeout?
| [Thursday 06 January 2011] [05:38:50] <jugg>	the application would like to go on to start building another message, but it can not send a new message until the old one completes.  So it either has to allow a bad message to be sent, or close the socket.
| [Thursday 06 January 2011] [05:39:20] <sustrik>	i mean, how come the message is bad?
| [Thursday 06 January 2011] [05:39:26] <jugg>	it is incomplete
| [Thursday 06 January 2011] [05:39:37] <sustrik>	why are you sending it then?
| [Thursday 06 January 2011] [05:40:02] <jugg>	because it is sent as it is built.
| [Thursday 06 January 2011] [05:40:09] <sustrik>	hm
| [Thursday 06 January 2011] [05:40:35] <sustrik>	that's not what multi-part messages are for
| [Thursday 06 January 2011] [05:40:36] <jugg>	obviously a solution is to wait to send until it is fully built, but...
| [Thursday 06 January 2011] [05:40:56] <sustrik>	the goal is not to hold the list of message parts on behalf of the user
| [Thursday 06 January 2011] [05:41:05] <sustrik>	it's more like gather/scatter array
| [Thursday 06 January 2011] [05:41:23] <sustrik>	allowing for zero-copy of data that is not placed in contiguous memory
| [Thursday 06 January 2011] [05:41:58] <sustrik>	i would suggest holding the message parts in your app
| [Thursday 06 January 2011] [05:41:59] <jugg>	yes, I'm aware of what it is designed for... But that doesn't mean I won't try to extend its use case...
| [Thursday 06 January 2011] [05:42:06] <sustrik>	and sending only when the message is complete
| [Thursday 06 January 2011] [05:42:17] <sustrik>	sure, go on :)
| [Thursday 06 January 2011] [05:43:16] <jugg>	a socket reset option would help.  - for other reasons as well, but I know I'll get more flac for those.. :)
| [Thursday 06 January 2011] [05:43:52] <jugg>	btw, I'll probably hit you up for erlzmq access tomorrow... it seems to be working well.
| [Thursday 06 January 2011] [05:44:08] <jugg>	Still a few more test cases to check.
| [Thursday 06 January 2011] [05:44:24] <sustrik>	well, my concert is that the option would bind the API to particular implementation
| [Thursday 06 January 2011] [05:44:28] <sustrik>	ie.
| [Thursday 06 January 2011] [05:45:03] <sustrik>	currently the code can be rewritten/optimised in such a way that message parts are sent over the wire
| [Thursday 06 January 2011] [05:45:11] <sustrik>	even if the message is not fully sent
| [Thursday 06 January 2011] [05:45:18] <sustrik>	and cached on the receiver side
| [Thursday 06 January 2011] [05:45:46] <sustrik>	if the connection breaks, the cached message parts would be discarded
| [Thursday 06 January 2011] [05:46:07] <jugg>	you'd have to send an abort message then, so the receiver could discard the incomplete parts.
| [Thursday 06 January 2011] [05:46:11] <sustrik>	the rollback option would then require to extent the wire protocol
| [Thursday 06 January 2011] [05:46:21] <sustrik>	exactly
| [Thursday 06 January 2011] [05:46:31] <jugg>	I see
| [Thursday 06 January 2011] [05:46:43] <sustrik>	the interactions are quite complex
| [Thursday 06 January 2011] [05:47:11] <sustrik>	now, doing that just to not force user to keep a simple list of message parts seems an overkill
| [Thursday 06 January 2011] [05:48:04] <sustrik>	in more generic terms, 0mq was designed to implement the minimal possible subset of features
| [Thursday 06 January 2011] [05:48:20] <sustrik>	everytihng that can be build on top was deliberately eliminated
| [Thursday 06 January 2011] [05:48:47] <sustrik>	so, if you want this kind of thing, just go on, implement a wrapper on top on 0mq
| [Thursday 06 January 2011] [05:49:22] <sustrik>	or maybe a whole stack layer that would provide all kind of additional functionality
| [Thursday 06 January 2011] [05:49:24] <jugg>	Well, that view point simplifies a problem I was having with the erlang bindings... :)
| [Thursday 06 January 2011] [05:53:38] <jugg>	I have to run.  Thanks for the explanation.  Combined with the discussion we had some time ago where I wanted zmq to send each part over the wire as it was received, I might be starting to 'get' it :)
| [Thursday 06 January 2011] [05:54:14] <sustrik>	it's simply avoinding the feature creep
| [Thursday 06 January 2011] [05:54:26] <sustrik>	see you later
| [Thursday 06 January 2011] [06:38:52] <parik>	Hi
| [Thursday 06 January 2011] [06:40:03] <sustrik>	hi
| [Thursday 06 January 2011] [06:40:37] <parik>	I was going through 0MQ src and found that it is based on PGM protocol.So i studied first PGM protocol and it was intersting need to know about multicasting 
| [Thursday 06 January 2011] [06:41:43] <parik>	Like how no acknowledgment for successful delievery and negative acks for data loss and duplication of packet by the router
| [Thursday 06 January 2011] [06:42:43] <parik>	and hence reduce Server Load  and Network Load
| [Thursday 06 January 2011] [06:43:17] <parik>	Do i need to download open PGM to make 0MQ work
| [Thursday 06 January 2011] [06:44:26] <parik>	I am not getting the defintion for pgm_init..I looked around in PGM also
| [Thursday 06 January 2011] [06:44:50] <parik>	Hi Sustrik are you there
| [Thursday 06 January 2011] [06:44:58] <sustrik>	parik: 0mq is multi-protocol
| [Thursday 06 January 2011] [06:45:17] <sustrik>	so you have tcp as well as pgm
| [Thursday 06 January 2011] [06:45:31] <sustrik>	if you don't need mutlicast you can just ignore pgm
| [Thursday 06 January 2011] [06:45:56] <sustrik>	if you need it, openpgm is packaged with 0mq (see foreign/openpgm subdir)
| [Thursday 06 January 2011] [06:46:21] <sustrik>	to build 0mq *with* pgm you need to add an option to confiuger:
| [Thursday 06 January 2011] [06:46:23] <parik>	Thanks Sustrik.
| [Thursday 06 January 2011] [06:46:26] <sustrik>	./configure --with-pgm
| [Thursday 06 January 2011] [06:46:44] <mikko>	does openpgm maintain ABI?
| [Thursday 06 January 2011] [06:46:49] <parik>	ok.Thanks alot.
| [Thursday 06 January 2011] [06:46:57] <parik>	What is ABI
| [Thursday 06 January 2011] [06:46:58] <mikko>	i'm wondering if packaging openpgm with 0mq makes sense in long-term
| [Thursday 06 January 2011] [06:47:14] <mikko>	application binary interface
| [Thursday 06 January 2011] [06:47:17] <sustrik>	it would be better to have an separate openpgm package
| [Thursday 06 January 2011] [06:47:30] <sustrik>	but so far it doesn't look like that
| [Thursday 06 January 2011] [06:47:45] <parik>	Thanks Mikko
| [Thursday 06 January 2011] [06:47:55] <mikko>	the main problem with current implementation being hard to upgrade and added maintenance for 0mq project
| [Thursday 06 January 2011] [06:48:00] <sustrik>	the actual fact, afaiu, is that most people are using openpg via 0mq
| [Thursday 06 January 2011] [06:48:29] <sustrik>	mikko: right
| [Thursday 06 January 2011] [06:48:37] <sustrik>	it's not obvious how to solve it though
| [Thursday 06 January 2011] [06:48:48] <mikko>	so there are situations where openpgm is supported on certain platform + compiler combination but cant be compiled with --with-pgm
| [Thursday 06 January 2011] [06:49:01] <parik>	You mean to say it's better to use open pgm pakage then that comes with OMQ
| [Thursday 06 January 2011] [06:49:39] <sustrik>	i am aware of that
| [Thursday 06 January 2011] [06:50:03] <sustrik>	but on the other hand requiring users to install scons and build openpgm by hand
| [Thursday 06 January 2011] [06:50:06] <mikko>	there are two ways to change it: a) decouple pgm completely from 0mq and have users install it separately b) build openpgm using their scons builds and just link against artifacts
| [Thursday 06 January 2011] [06:50:11] <sustrik>	manage the dependencies
| [Thursday 06 January 2011] [06:50:12] <sustrik>	etc.
| [Thursday 06 January 2011] [06:50:13] <mikko>	the latter adds dependency to scons
| [Thursday 06 January 2011] [06:50:21] <sustrik>	could be actually a barrier to adoption
| [Thursday 06 January 2011] [06:50:23] <mikko>	as does the former
| [Thursday 06 January 2011] [06:50:25] <parik>	So pgm that is bundled with 0MQ will be potable to all OS and architectures
| [Thursday 06 January 2011] [06:50:43] <mikko>	sustrik: in the long run 99% of the users will get 0mq via their distro
| [Thursday 06 January 2011] [06:50:52] <mikko>	well, maybe not that large amount but high percentage
| [Thursday 06 January 2011] [06:50:56] <sustrik>	yes
| [Thursday 06 January 2011] [06:51:13] <sustrik>	so the goal is to have openpgm packages for all distros and 0mq packages for all distros
| [Thursday 06 January 2011] [06:51:24] <sustrik>	we are quite far away from that afaics
| [Thursday 06 January 2011] [06:51:52] <sustrik>	the current system is the next best thing imo
| [Thursday 06 January 2011] [06:52:09] <mikko>	im not sure if dependency to scons is a large issue 
| [Thursday 06 January 2011] [06:52:17] <mikko>	i see python as larger issue but that is already a dependency
| [Thursday 06 January 2011] [06:52:28] <sustrik>	huh
| [Thursday 06 January 2011] [06:52:29] <sustrik>	is it?
| [Thursday 06 January 2011] [06:52:31] <mikko>	yes
| [Thursday 06 January 2011] [06:52:35] <sustrik>	where?
| [Thursday 06 January 2011] [06:52:49] <sustrik>	openpgm?
| [Thursday 06 January 2011] [06:52:53] <mikko>	yes
| [Thursday 06 January 2011] [06:52:59] <sustrik>	oh my
| [Thursday 06 January 2011] [06:53:04] <mikko>	https://github.com/zeromq/zeromq2/blob/master/configure.in#L318
| [Thursday 06 January 2011] [06:53:07] <sustrik>	any idea of what is it used for?
| [Thursday 06 January 2011] [06:53:32] <mikko>	i don't but i can easily check
| [Thursday 06 January 2011] [06:53:56] <mikko>	foreign/openpgm/@pgm_basename@/openpgm/pgm/version.c: ../foreign/openpgm/@pgm_basename@/openpgm/pgm/version_generator.py
| [Thursday 06 January 2011] [06:53:59] <mikko>	python ../foreign/openpgm/@pgm_basename@/openpgm/pgm/version_generator.py > $@
| [Thursday 06 January 2011] [06:54:10] <sustrik>	hm
| [Thursday 06 January 2011] [06:54:12] <sustrik>	let me see
| [Thursday 06 January 2011] [06:54:12] <mikko>	https://github.com/zeromq/zeromq2/blob/master/src/Makefile.am
| [Thursday 06 January 2011] [06:54:25] <mikko>	github doesn't show lines so i can't link you directly
| [Thursday 06 January 2011] [06:54:29] <mikko>	but should be easy to find
| [Thursday 06 January 2011] [06:56:10] <sustrik>	the script generates the version name
| [Thursday 06 January 2011] [06:56:47] <sustrik>	possibly we can replace it by a hardcoded one
| [Thursday 06 January 2011] [06:56:57] <sustrik>	and thus drop the python dependency
| [Thursday 06 January 2011] [06:57:59] <mikko>	but then again, there hasn't been complaints about python dependency
| [Thursday 06 January 2011] [06:58:37] <sustrik>	the problem imo is that the build comes very early on in adoption process
| [Thursday 06 January 2011] [06:59:06] <sustrik>	so, say if you find a bug in 0mq, you are already using it
| [Thursday 06 January 2011] [06:59:12] <sustrik>	so it make sense to report the bug
| [Thursday 06 January 2011] [06:59:15] <sustrik>	or even fix it
| [Thursday 06 January 2011] [06:59:31] <sustrik>	however, if you are building it
| [Thursday 06 January 2011] [06:59:45] <sustrik>	it means you are using 0mq for 5 mins at the moment
| [Thursday 06 January 2011] [07:00:11] <sustrik>	if there's a problem, the simple solution is to just let it be
| [Thursday 06 January 2011] [07:00:16] <sustrik>	and use something else
| [Thursday 06 January 2011] [07:00:48] <mikko>	hmm
| [Thursday 06 January 2011] [07:00:53] <mikko>	i agree and disagree
| [Thursday 06 January 2011] [07:00:59] 	 * sustrik listens
| [Thursday 06 January 2011] [07:01:09] <mikko>	i agree that build issues will throw off people
| [Thursday 06 January 2011] [07:01:30] <mikko>	i disagree that clear dependency will throw off people, especially when it's build-time only
| [Thursday 06 January 2011] [07:01:45] <mikko>	we require autoconf 2.61 as well which is not available everywhere
| [Thursday 06 January 2011] [07:02:09] <sustrik>	ack
| [Thursday 06 January 2011] [07:02:11] <mikko>	brb, fetching lunch
| [Thursday 06 January 2011] [07:02:21] <sustrik>	otoh, autoconf is a standard package
| [Thursday 06 January 2011] [07:02:40] <sustrik>	openpgm is not yet a package
| [Thursday 06 January 2011] [07:02:46] <sustrik>	you have to build it by hand
| [Thursday 06 January 2011] [07:02:47] <sustrik>	etc.
| [Thursday 06 January 2011] [07:02:58] <sustrik>	bon appettit
| [Thursday 06 January 2011] [07:13:47] <parik>	Sustrik.Thanks alot.Yes I got pgm package inside foreign subdir.I am going to do code walkthrough before i take up and understands 0MQ
| [Thursday 06 January 2011] [07:13:55] <parik>	Thanks alot Sustrik once again
| [Thursday 06 January 2011] [07:14:01] <parik>	Thanks mikko
| [Thursday 06 January 2011] [07:14:45] <sustrik>	:)
| [Thursday 06 January 2011] [07:15:48] <parik>	Do I am going in right direction.I always wnat to know as much as possible so as this learning will help me somewhere
| [Thursday 06 January 2011] [07:18:16] <sustrik>	parik: have you seen the 0mq guide?
| [Thursday 06 January 2011] [07:18:26] <sustrik>	it's worth of reading for the starters
| [Thursday 06 January 2011] [07:18:26] <parik>	Yes ..
| [Thursday 06 January 2011] [07:19:27] <parik>	Thanks Sustrik.Actually I have not yet gone through it completely
| [Thursday 06 January 2011] [07:20:12] <sustrik>	ch1 & ch2 are the most important
| [Thursday 06 January 2011] [07:20:17] <sustrik>	to grasp the concept
| [Thursday 06 January 2011] [07:20:29] <parik>	When I come across 0MQ is based on PGM My entire focus goes to understand PGM first as I was not aware fo it earlier
| [Thursday 06 January 2011] [07:21:04] <parik>	I will definitly go through ch1 and ch2
| [Thursday 06 January 2011] [07:21:37] <sustrik>	parik: be careful with pgm
| [Thursday 06 January 2011] [07:21:42] <parik>	Now i understands PGM to certain extent to start with
| [Thursday 06 January 2011] [07:22:03] <sustrik>	mutlicast is only useful in special circumstances
| [Thursday 06 January 2011] [07:22:05] <parik>	You mean to say shall i not concentrate much on this
| [Thursday 06 January 2011] [07:22:14] <parik>	ok...
| [Thursday 06 January 2011] [07:22:15] <sustrik>	in most cases tcp makes more sense
| [Thursday 06 January 2011] [07:22:35] <sustrik>	pgm =very high volume pub/sub on LANs
| [Thursday 06 January 2011] [07:22:49] <sustrik>	it needs quite a lot of administration
| [Thursday 06 January 2011] [07:22:50] <parik>	But does not three way shaking makes it more congested in TCP
| [Thursday 06 January 2011] [07:22:59] <parik>	ok..
| [Thursday 06 January 2011] [07:23:04] <sustrik>	it requires good hardware etc.
| [Thursday 06 January 2011] [07:23:18] <parik>	You mean to say pgm compatible routers
| [Thursday 06 January 2011] [07:23:40] <parik>	upgraded hardware for performance
| [Thursday 06 January 2011] [07:23:48] <sustrik>	in most cases you don't event want multicast traffic pass the router
| [Thursday 06 January 2011] [07:23:58] <parik>	ok
| [Thursday 06 January 2011] [07:23:58] <sustrik>	rather i meant switches with IGMP snooping
| [Thursday 06 January 2011] [07:24:11] <Steve-o>	pgm routers are v. expensive
| [Thursday 06 January 2011] [07:24:26] <Steve-o>	switches are pretty easy, standard procurves work well
| [Thursday 06 January 2011] [07:24:33] <parik>	ok..So that's an expensive one
| [Thursday 06 January 2011] [07:25:33] <Steve-o>	well, v.expensive for gigabit capacity, cisco support it on almost their entire product range, expensive = US$10,000
| [Thursday 06 January 2011] [07:26:01] <parik>	oh...That's really expensive...
| [Thursday 06 January 2011] [07:27:09] <parik>	So then i will start with TCP.But no ways going through PGM gives me some insight of what is it and how does it work
| [Thursday 06 January 2011] [07:27:29] <parik>	I will start with TCP 
| [Thursday 06 January 2011] [07:27:37] <Steve-o>	100mb is around $5,000 the closest I saw last check, slower speeds all the way down to $250 for DSL routers, etc.
| [Thursday 06 January 2011] [07:28:01] <Steve-o>	consider PGM an administrative option rather than anything particular technical for development
| [Thursday 06 January 2011] [07:28:46] <Steve-o>	that's how zeromq has been developed, choose a ZMQ_PUB socket and run it to the ground with TCP until you really need scaling
| [Thursday 06 January 2011] [07:28:51] <sustrik>	right, you can start with tcp and switch to pgm when needed
| [Thursday 06 January 2011] [07:29:22] <Steve-o>	consider TCP sockets are pretty much accelerated everywhere and PGM isn't anywhere
| [Thursday 06 January 2011] [07:29:29] <parik>	Thanks for guidance and making me to go in right direction 
| [Thursday 06 January 2011] [07:29:40] <parik>	Yes I do agree
| [Thursday 06 January 2011] [07:30:04] <Steve-o>	but when you need it, it's awesome :D
| [Thursday 06 January 2011] [07:30:25] <parik>	I am a novice but got some useful tips from Sustrik and Steve
| [Thursday 06 January 2011] [07:30:33] <parik>	:-)
| [Thursday 06 January 2011] [07:33:44] <parik>	Just one thing I always want to work and write some protcols, creating some utility but i always wonder how can I start with
| [Thursday 06 January 2011] [07:35:45] <Steve-o>	implementing your own network protcol or are we talking above zeromq?
| [Thursday 06 January 2011] [07:40:04] <parik>	I mean to say something I can contribute to and involved myself as one of the developer
| [Thursday 06 January 2011] [07:41:00] <Steve-o>	well there is plenty of scope with zeromq
| [Thursday 06 January 2011] [07:41:58] <Steve-o>	a lot can be made on top, e.g. last value cache, certified delivery, transactional delivery, virtual circuits, http tunneling, encryption, authentication, proxying, etc
| [Thursday 06 January 2011] [07:43:09] <parik>	Great..Since I am novice and don't know How I can also be felt great of doing/contributing something..Just I want to know How can I contribute...Need some guidance on this front
| [Thursday 06 January 2011] [07:44:53] <Steve-o>	well it's usually easiest if you have a target architecture to develop for, 
| [Thursday 06 January 2011] [07:45:22] <Steve-o>	for example a last value cache could be simply integrating memcached from TCP/UDP to zeromq sockets
| [Thursday 06 January 2011] [07:45:22] <keffo>	What's wrong with abstract logic? =)
| [Thursday 06 January 2011] [07:47:16] <parik>	Steve I am really sorry ..I didnot get it
| [Thursday 06 January 2011] [07:49:16] <Steve-o>	if you have a scenario to deploy something its easier than randomly creating something
| [Thursday 06 January 2011] [07:49:31] <Steve-o>	unless you are into computer science theory I guess
| [Thursday 06 January 2011] [07:49:39] <parik>	oh..
| [Thursday 06 January 2011] [07:50:13] <parik>	Yeah I am in Comuter Science
| [Thursday 06 January 2011] [07:50:59] <Steve-o>	there is one developer integrating zeromq with websockets for their app, that's pretty neat
| [Thursday 06 January 2011] [07:51:44] <parik>	ok..
| [Thursday 06 January 2011] [07:52:36] <Steve-o>	you can also pickup ideas from here:  http://www.zeromq.org/docs:labs
| [Thursday 06 January 2011] [07:53:56] <parik>	Thanks alot Steve..I think this will really help.
| [Thursday 06 January 2011] [07:55:12] <parik>	Thanks Steve You have given me a starting point to start with..I
| [Thursday 06 January 2011] [07:55:23] <parik>	am really grateful to you
| [Thursday 06 January 2011] [07:57:04] <parik>	Thanks alot once again to Steve to Sustrik for guiding me and answering my doubts and given your precious time.
| [Thursday 06 January 2011] [07:57:34] <Steve-o>	good luck, post something on a blog and let us read about it
| [Thursday 06 January 2011] [07:58:01] <sustrik>	feel free to discuss your ideas on the mailing list
| [Thursday 06 January 2011] [07:58:16] <parik>	Thanks alot Steve.I will make it sure...
| [Thursday 06 January 2011] [07:58:17] <sustrik>	there's much more people there to comment then on irc
| [Thursday 06 January 2011] [07:58:32] <parik>	oh...ok
| [Thursday 06 January 2011] [07:59:34] <sustrik>	Steve-o: btw, your Tibco migration docs are really useful
| [Thursday 06 January 2011] [07:59:40] <sustrik>	especially the code examples
| [Thursday 06 January 2011] [07:59:55] <parik>	Thanks once again to Steve and Sustrik...I donot want to leave the discussion but i have to as I have to go but i will cherish the discussion with you people.You people are alot supported
| [Thursday 06 January 2011] [07:59:56] <sustrik>	it would be great if these were widely accessible
| [Thursday 06 January 2011] [08:00:25] <sustrik>	even if they are not perfect, it at least allows rv users to start somewhere
| [Thursday 06 January 2011] [08:00:43] <Steve-o>	ideally dumping in github or somewhere
| [Thursday 06 January 2011] [08:00:58] <Steve-o>	as I mentioned I already have C++ & Java examples but didn't include them
| [Thursday 06 January 2011] [08:01:27] <Steve-o>	but honestly I have no idea how you want rv users to migrate no-single-point-of-failure architectures
| [Thursday 06 January 2011] [08:01:30] <sustrik>	i would say the text can be dumped on a wiki page, while code examples can reside on github
| [Thursday 06 January 2011] [08:02:12] <sustrik>	well, we can address that later on
| [Thursday 06 January 2011] [08:02:39] <sustrik>	the important thing is make the initial docs accessible
| [Thursday 06 January 2011] [08:02:51] <Steve-o>	that will make all the order routing developers happy
| [Thursday 06 January 2011] [08:03:50] <keffo>	routing developer, now that's a career! :)
| [Thursday 06 January 2011] [08:03:56] <sustrik>	it's matter of time imo, you can't do everything straight away
| [Thursday 06 January 2011] [08:04:12] <sustrik>	so let them try 0mq, experiment with it, complain about it
| [Thursday 06 January 2011] [08:04:28] <sustrik>	and hopefully solution would emerge
| [Thursday 06 January 2011] [08:04:33] <keffo>	sustrik: Do you know if anyone has tried to bridge zmq with wcf?
| [Thursday 06 January 2011] [08:04:59] <sustrik>	i think i dimly remember something like that
| [Thursday 06 January 2011] [08:05:03] <sustrik>	but i may be wrong
| [Thursday 06 January 2011] [08:05:36] <Steve-o>	keffo: order routing is rather dull, especially FX
| [Thursday 06 January 2011] [08:05:49] <keffo>	Steve-o: my point yeah :)
| [Thursday 06 January 2011] [08:06:17] <Steve-o>	1,000 trades a day max, woohoo
| [Thursday 06 January 2011] [08:06:35] <keffo>	sustrik: It's easy enough to just call a zmq api inside a wcf service, but a somewhat more native method would be very useful
| [Thursday 06 January 2011] [08:08:33] <sustrik>	hm, tried googling?
| [Thursday 06 January 2011] [08:08:43] <keffo>	yeah
| [Thursday 06 January 2011] [08:09:32] <sustrik>	doesn't look like anything is available
| [Thursday 06 January 2011] [08:10:02] <sustrik>	small project for someone to spend weekend hacking :)
| [Thursday 06 January 2011] [08:10:21] <keffo>	hmm, rabbitmq seems to support it, and also federation services, that's totally awesome if they support full saml & adfs
| [Thursday 06 January 2011] [08:10:45] <keffo>	not that it helps in any way I guess, exept perusal of their code maybe
| [Thursday 06 January 2011] [08:10:50] <Steve-o>	presumably wcf 4 looks most interesting?
| [Thursday 06 January 2011] [08:11:03] <keffo>	how do you mean?
| [Thursday 06 January 2011] [08:11:14] <keffo>	if I did decide to try I would target the latest version obviously?
| [Thursday 06 January 2011] [08:11:46] <Steve-o>	the original cl wrapper was designed around .net 2 for greater compatibility
| [Thursday 06 January 2011] [08:12:29] <keffo>	I already have my loadbalancer ui in wpf, but there's something oddly appealing about hosting the loadbalancer directly in IIS, with the ui as a silverlight app 
| [Thursday 06 January 2011] [08:13:03] <keffo>	Steve-o: this would be a lib, using the zmq api, and nothing more
| [Thursday 06 January 2011] [08:31:01] <keffo>	"The RabbitMQ .NET client is an implementation of an AMQP client library for C# (and, implicitly, other .NET languages), and a binding exposing AMQP services via Microsoft's Windows Communication Foundation (WCF)."
| [Thursday 06 January 2011] [08:31:08] <keffo>	So, doable
| [Thursday 06 January 2011] [08:35:45] <mikko>	http://msdn.microsoft.com/en-us/magazine/cc163394.aspx
| [Thursday 06 January 2011] [08:35:55] <mikko>	doesn't seem to be overly complicated to create custom bindings
| [Thursday 06 January 2011] [08:36:07] <mikko>	then again, i really dont know anything about windows
| [Thursday 06 January 2011] [10:14:10] <mikko>	sustrik: there?
| [Thursday 06 January 2011] [10:14:25] <sustrik>	mikko: yes
| [Thursday 06 January 2011] [10:14:54] <mikko>	where is api.zeromq.org hosted at?
| [Thursday 06 January 2011] [10:16:39] <sustrik>	here in bratislava
| [Thursday 06 January 2011] [10:17:19] <sustrik>	it's a box at the local ISP's datacenter afaik
| [Thursday 06 January 2011] [10:17:48] <mikko>	cool, i noticed that the 404 handler is not very user-friendly:
| [Thursday 06 January 2011] [10:17:53] <mikko>	http://api.zeromq.org/zmq_msg_close for example
| [Thursday 06 January 2011] [10:18:32] <mikko>	i can do a small page that shows "Did you mean: x" 
| [Thursday 06 January 2011] [10:18:41] <mikko>	not sure if that is a high priority though
| [Thursday 06 January 2011] [10:19:03] <sustrik>	you have to speak to mato
| [Thursday 06 January 2011] [10:19:08] <sustrik>	he's managing the box
| [Thursday 06 January 2011] [10:19:13] <mikko>	where is mato nowadays btw?
| [Thursday 06 January 2011] [10:19:18] <sustrik>	new zealand
| [Thursday 06 January 2011] [10:19:25] <mikko>	contract work?
| [Thursday 06 January 2011] [10:19:42] <sustrik>	he's half slovak, half new zealander
| [Thursday 06 January 2011] [10:19:48] <sustrik>	on his holiday atm
| [Thursday 06 January 2011] [10:20:10] <sustrik>	i think he should be available shortly
| [Thursday 06 January 2011] [16:46:39] <Namei>	Hello
| [Thursday 06 January 2011] [16:54:51] <sustrik>	hi
| [Thursday 06 January 2011] [17:01:20] <mikko>	hi
| [Thursday 06 January 2011] [17:01:30] <Namei>	how are u ?
| [Thursday 06 January 2011] [17:02:33] <mikko>	im fine thank you
| [Thursday 06 January 2011] [17:02:36] <mikko>	yourself?
| [Thursday 06 January 2011] [17:04:44] <Namei>	the same :)
| [Thursday 06 January 2011] [17:06:50] <Namei>	i came in a english server to perfect my english, but it's hard lol
| [Thursday 06 January 2011] [17:20:30] <Namei>	good night
| [Thursday 06 January 2011] [20:19:54] <codebeaker>	Good evening all, quick question for an inexperienced C-developer, I'm following the Introduction, and I'm getting an odd error - https://gist.github.com/4f82911f324c8fae8f9e - trying to compile one of the exampels. What have I missed, zmq installed (maint branch) from Git, built and make-installed to the standard places, and I'm compiling my sample project with a vanilla cmake project
| [Thursday 06 January 2011] [20:20:06] <codebeaker>	is there a CMake find_zmq I'm missing?
| [Thursday 06 January 2011] [20:32:01] <codebeaker>	I found this https://github.com/PatrickCheng/zeromq2/blob/master/FindZMQ.cmake - P.Chen - thanks if you're idling here somewhere!
| [Thursday 06 January 2011] [22:55:21] <jugg>	Can zmq ever error with EAGAIN if ZMQ_SNDMORE is set?
| [Thursday 06 January 2011] [22:57:33] <jugg>	(of course ZMQ_NOBLOCK is also set)
| [Thursday 06 January 2011] [23:26:24] <rqmedes>	anyone use zeromq with c#?
| [Friday 07 January 2011] [02:36:38] <sustrik>	jugg: yes it can
| [Friday 07 January 2011] [02:36:47] <sustrik>	for the first message part
| [Friday 07 January 2011] [03:01:04] <parik>	Hi Sustrik and Steve 
| [Friday 07 January 2011] [03:02:40] <parik>	I am trying to build zeromq src but running ./configure script before that to check the dependencies and I am getting error "configure: error: cannot link with -luuid, install uuid-dev."
| [Friday 07 January 2011] [03:03:12] <parik>	I tried looking on web-also for downloading uuid-dev but not of much success.I didn't get the package
| [Friday 07 January 2011] [03:04:20] <parik>	Does anybody help me out
| [Friday 07 January 2011] [03:04:27] <parik>	in this regard
| [Friday 07 January 2011] [04:00:56] <mikko>	rqmedes: there are a couple of people who do use it in C#
| [Friday 07 January 2011] [04:16:55] <jugg>	sustrik, So, after send(...,SNDMORE|NOBLOCK) the first message part successfully, I could subsequently tight loop send(..., SNDMORE|NOBLOCK) an arbitrarily large amount of messages and never get EAGAIN?  If so, could you explain what causes EAGAIN to be generated?
| [Friday 07 January 2011] [04:39:04] <sustrik>	jugg: EAGAIN means there are already HWM messages in 0mq's buffer
| [Friday 07 January 2011] [04:39:17] <sustrik>	so you get EAGAIN when you try to insert new message
| [Friday 07 January 2011] [04:39:25] <sustrik>	which happens with the first message parts
| [Friday 07 January 2011] [04:39:43] <sustrik>	subsequent message parts belong to the same message that was already validated
| [Friday 07 January 2011] [04:39:51] <sustrik>	so you never get EAGAIN there
| [Friday 07 January 2011] [04:41:31] <jugg>	so nothing to do whether data can be put on the wire?
| [Friday 07 January 2011] [04:44:43] <parik>	Hi
| [Friday 07 January 2011] [04:46:23] <jugg>	anyway, what seems to me a bug - zmq::xsub_t::xhas_out () is implemented returning true.  Thus getsockopt(events) shows the a sub socket can be written to.
| [Friday 07 January 2011] [04:46:33] <parik>	Where I can find the definiton for zmq_init() 
| [Friday 07 January 2011] [04:47:18] <jugg>	http://api.zeromq.org/
| [Friday 07 January 2011] [04:48:36] <parik>	That's the manual page.I have referred it but I want to know What inside zmq_init is happening.How its initalizing and returning context and creating a thread poool
| [Friday 07 January 2011] [04:48:47] <parik>	I am interesting in code
| [Friday 07 January 2011] [04:49:06] <jugg>	http://github.com/zeromq/zeromq2
| [Friday 07 January 2011] [04:52:35] <parik>	Thanks jugg But I want to have C source
| [Friday 07 January 2011] [04:55:50] <guido_g>	funny
| [Friday 07 January 2011] [04:56:03] <guido_g>	mq is written in c++
| [Friday 07 January 2011] [04:58:15] <parik>	But In 0MQ Guide its showing C example using zeroMQ facililites
| [Friday 07 January 2011] [04:58:36] <parik>	Also other Languages
| [Friday 07 January 2011] [04:58:49] <guido_g>	sure
| [Friday 07 January 2011] [04:59:09] <guido_g>	the mq core is still written in c++
| [Friday 07 January 2011] [04:59:49] <guido_g>	"<parik> That's the manual page.I have referred it but I want to know What inside zmq_init is happening.How its initalizing and returning context and creating a thread poool" <- this part is in the core
| [Friday 07 January 2011] [05:01:23] <parik>	ok.
| [Friday 07 January 2011] [05:02:03] <yrashk>	I am new to zeromq2, and have a simple question  for inproc, should endpoint be unique per process if each thread has its own pair of push/pull sockets?
| [Friday 07 January 2011] [05:02:23] <yrashk>	s/unique per process/unique process-wide/
| [Friday 07 January 2011] [05:03:23] <mikko>	yrashk: it should be unique to context
| [Friday 07 January 2011] [05:03:47] <yrashk>	mikko: alright, make sense, thanks :) is it okay to have a context per thread?
| [Friday 07 January 2011] [05:03:59] <mikko>	yrashk: no
| [Friday 07 January 2011] [05:04:12] <yrashk>	ok, I'll generate unique endpoints then :)
| [Friday 07 January 2011] [05:04:15] <mikko>	yrashk: you can only have inproc communications between sockets allocated from same context
| [Friday 07 January 2011] [05:04:42] <mikko>	yrashk: i usually use something like "inproc://thread-%d" where %d is thread id or similar
| [Friday 07 January 2011] [05:04:51] <yrashk>	yeah this is exactly what I am going to do
| [Friday 07 January 2011] [05:04:54] <yrashk>	sprintf thread id
| [Friday 07 January 2011] [05:05:53] <parik>	I guesss Context is represeneting application.I mean to say Context shall be think w.r.t. application
| [Friday 07 January 2011] [05:06:03] <parik>	In application context
| [Friday 07 January 2011] [05:09:09] <yrashk>	fine, done :) another question is when exactly msg's ffn will be called? I didn't really get this from the man (3)
| [Friday 07 January 2011] [05:09:16] <yrashk>	should I look deeper into the manual?
| [Friday 07 January 2011] [05:09:25] <mikko>	parik: not quite i would say
| [Friday 07 January 2011] [05:09:43] <mikko>	parik: context is more of a "operating context" for 0mq
| [Friday 07 January 2011] [05:10:07] <mikko>	let's say you have two libraries, libxy and libzz and both of them use 0mq internally
| [Friday 07 January 2011] [05:10:18] <mikko>	most likely each one of these libraries would have their own context
| [Friday 07 January 2011] [05:10:40] <mikko>	and you could happily use both libraries in a project without having to worry about collisions in inproc names etc
| [Friday 07 January 2011] [05:10:56] <mikko>	that's at least how i see it
| [Friday 07 January 2011] [05:11:14] <yrashk>	I suspect I have occasional test failures because I don't quite understand when msg data is deallocated :S
| [Friday 07 January 2011] [05:12:14] <mikko>	yrashk: does this lead to a specific question?
| [Friday 07 January 2011] [05:12:23] <yrashk>	yep, the one above :)
| [Friday 07 January 2011] [05:12:31] <yrashk>	"another question is when exactly msg's ffn will be called? I didn't really get this from the man (3)"
| [Friday 07 January 2011] [05:12:38] <yrashk>	"should I look deeper into the manual?"
| [Friday 07 January 2011] [05:14:55] <mikko>	yrashk: the ffn is called when the message refcount is 0 and the message is not shared
| [Friday 07 January 2011] [05:15:05] <mikko>	yrashk: https://github.com/zeromq/zeromq2/blob/master/src/zmq.cpp#L126
| [Friday 07 January 2011] [05:15:38] <yrashk>	thanks
| [Friday 07 January 2011] [05:15:47] <yrashk>	mm I think I know what causes those occasional failures
| [Friday 07 January 2011] [05:23:10] <yrashk>	yup, nothing to do with zeromq (almost, rather with its awesomeness :)
| [Friday 07 January 2011] [05:32:25] <yrashk>	although I am surprised it didn't gain me any extra performance comparing to pthread_cond message delivery method. Well, may be I am doing something wrong
| [Friday 07 January 2011] [05:32:39] <parik>	Hi Mikko, I agree with you.Thanks for expalining thorugh the scenarios.Sorry for replying late as I was off from the discussion for sometime
| [Friday 07 January 2011] [05:48:54] <yrashk>	mikko: if I am using ZMQ_NOBLOCK in zmq_send, should I initialize context with at least one thread? or I am misunderstanding how NOBLOCK works for inproc?
| [Friday 07 January 2011] [05:48:59] <yrashk>	*am *
| [Friday 07 January 2011] [05:49:04] <yrashk>	*am I
| [Friday 07 January 2011] [05:57:24] <jsimmons>	with inproc, it should be non-blocking anyway yrashk, as far as I can tell
| [Friday 07 January 2011] [05:57:55] <mikko>	yrashk: sorry, i dont understand the question
| [Friday 07 January 2011] [05:58:50] <mikko>	jsimmons: zero lock yes but not necessarily non-blocking
| [Friday 07 January 2011] [05:59:45] <jsimmons>	oh noblock returns failure when it's going to block I see
| [Friday 07 January 2011] [06:01:30] <rqmedes>	sorry miko was away from keyboard
| [Friday 07 January 2011] [06:03:04] <rqmedes>	have installed and am playing through c# examples, any pointers on how  you run your seperate programs, wcf, services?
| [Friday 07 January 2011] [06:18:16] <mikko>	rqmedes: i guess you could do a custom wcf binding
| [Friday 07 January 2011] [06:18:20] <mikko>	as far as i understand
| [Friday 07 January 2011] [06:18:29] <mikko>	rqmedes: i don't really know anything about windows world
| [Friday 07 January 2011] [06:19:36] <mikko>	rqmedes: i think you should mail to mailing-list. there are several windows people there
| [Friday 07 January 2011] [06:19:42] <mikko>	i gotta hop into a meeting ->
| [Friday 07 January 2011] [06:23:07] <parik>	Thanks alot mikko and guido_g
| [Friday 07 January 2011] [06:46:50] <sustrik>	jugg: good point
| [Friday 07 January 2011] [06:46:53] <sustrik>	let me fix it
| [Friday 07 January 2011] [06:50:18] <jugg>	sustrik, is the idea for subscriptions to be sent to the publisher eventually?  Or why is zmq::sub_t::xsetsockopt sending subscriptions as a payload?
| [Friday 07 January 2011] [06:51:21] <sustrik>	jugg: yes, it's the first step towards subscription forwarding
| [Friday 07 January 2011] [06:51:31] <jugg>	cool
| [Friday 07 January 2011] [06:59:55] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r8e0049e 10/ (src/sub.cpp src/sub.hpp): 
| [Friday 07 January 2011] [06:59:55] <CIA-21>	zeromq2: Disable sending messages on SUB socket
| [Friday 07 January 2011] [06:59:55] <CIA-21>	zeromq2: The ability was inherited from XSUB socket.
| [Friday 07 January 2011] [06:59:55] <CIA-21>	zeromq2: Now it's properly disabled.
| [Friday 07 January 2011] [06:59:55] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/ih6erI
| [Friday 07 January 2011] [06:59:58] <sustrik>	jugg: done
| [Friday 07 January 2011] [07:01:17] <rqmedes>	thanks mikko
| [Friday 07 January 2011] [07:01:20] <jugg>	thanks
| [Friday 07 January 2011] [07:10:19] <yrashk>	hmm, caught a rare segfault in recv, https://gist.github.com/c985ee3760af3aadaf96
| [Friday 07 January 2011] [07:10:38] <yrashk>	(2.1.0)
| [Friday 07 January 2011] [07:20:41] <sustrik>	yrashk: is it reproducible
| [Friday 07 January 2011] [07:20:44] <sustrik>	?
| [Friday 07 January 2011] [07:20:57] <yrashk>	sustrik: rarely  running some indirect stress tests
| [Friday 07 January 2011] [07:21:23] <sustrik>	can you possible compile 0mq with debug enabled?
| [Friday 07 January 2011] [07:21:32] <sustrik>	so that backtrace is more useful?
| [Friday 07 January 2011] [07:21:43] <sustrik>	./configure --enable-debug
| [Friday 07 January 2011] [07:21:44] <yrashk>	sure, may be not tonight, but will do
| [Friday 07 January 2011] [07:21:53] <sustrik>	sure, take your time
| [Friday 07 January 2011] [07:22:15] <yrashk>	hopefully its nothing serious
| [Friday 07 January 2011] [07:22:20] <yrashk>	or should I switch to master?
| [Friday 07 January 2011] [07:26:45] <sustrik>	wait a sec, i'm going to apply one pending patch
| [Friday 07 January 2011] [07:29:45] <CIA-21>	zeromq2: 03Dhammika Pathirana 07master * rbabdf48 10/ src/pipe.cpp : 
| [Friday 07 January 2011] [07:29:45] <CIA-21>	zeromq2: Fix pipe writer termination
| [Friday 07 January 2011] [07:29:45] <CIA-21>	zeromq2: Signed-off-by: Dhammika Pathirana <dhammika@gmail.com> - http://bit.ly/gNG05Z
| [Friday 07 January 2011] [07:29:58] <sustrik>	yrashk: ok, done
| [Friday 07 January 2011] [07:30:21] <sustrik>	you can use the trunk, there are couple of patches there
| [Friday 07 January 2011] [07:30:33] <sustrik>	that may (or may not) fix your problem
| [Friday 07 January 2011] [07:30:36] <yrashk>	hmmm this patchh is for PUSH/PULL sockets, am I right?
| [Friday 07 January 2011] [07:30:46] <sustrik>	it's generic
| [Friday 07 January 2011] [07:30:49] <sustrik>	all socket types
| [Friday 07 January 2011] [07:30:50] <yrashk>	oh ok
| [Friday 07 January 2011] [07:31:24] <yrashk>	I am new to actual zeromq usage (knew about it for quite some time, though) just trying to switch my event loop from pthread_cond kind of loop
| [Friday 07 January 2011] [07:31:50] <yrashk>	(although I naively expected to get some performance gains from this transition, but it didn't happen :)
| [Friday 07 January 2011] [07:32:26] <sustrik>	you should get the performance gain once the batching kicks in
| [Friday 07 January 2011] [07:32:38] <yrashk>	at least it simplified my code
| [Friday 07 January 2011] [07:32:43] <sustrik>	i.e. sending many messages using a single operation
| [Friday 07 January 2011] [07:32:53] <yrashk>	when it is going to kick in?
| [Friday 07 January 2011] [07:32:58] <yrashk>	to be kicked in*
| [Friday 07 January 2011] [07:33:13] <sustrik>	with high message load
| [Friday 07 January 2011] [07:33:42] <yrashk>	hmm I do have a high message load in my stress test
| [Friday 07 January 2011] [07:33:57] <yrashk>	I guess it depends on what we understand by high essage load
| [Friday 07 January 2011] [07:34:13] <sustrik>	dunno, million a second or somesuch
| [Friday 07 January 2011] [07:34:22] <yrashk>	mm I have less, I guess
| [Friday 07 January 2011] [07:35:02] <yrashk>	most likely my performance issues aren't in event loop algorithm (so either cond or zeromq get the same bottleneck down the road)
| [Friday 07 January 2011] [07:35:18] <sustrik>	that's quite likely
| [Friday 07 January 2011] [07:35:26] <sustrik>	as both of them are pretty much optimised
| [Friday 07 January 2011] [07:35:38] <yrashk>	I would assume so
| [Friday 07 January 2011] [07:35:48] <yrashk>	still with zeromq my code is much cleaner
| [Friday 07 January 2011] [07:36:27] <yrashk>	helped me to drop message queueing/pooling thing of my own
| [Friday 07 January 2011] [07:38:18] <yrashk>	and hopefully will help more down the road
| [Friday 07 January 2011] [07:38:20] <codebeaker>	what's the practical difference on Github between the @zeqomq user, and the repository of @PatrickCheng? They both seem pretty much the same, on the surface - but Cheng's includes useful snips for using MQ in a CMake project
| [Friday 07 January 2011] [07:40:03] <sustrik>	i think he just made the cmake build
| [Friday 07 January 2011] [07:40:08] <sustrik>	not 100% sure though
| [Friday 07 January 2011] [07:40:13] <sustrik>	check the project history
| [Friday 07 January 2011] [07:44:28] <codebeaker>	thanks sustrik - maynbe I'll fork both (running) and diff the whole trees, but his cmake work looks good
| [Friday 07 January 2011] [07:45:16] <codebeaker>	appreciate teh answer to a dumb question!
| [Friday 07 January 2011] [07:45:54] <sustrik>	:)