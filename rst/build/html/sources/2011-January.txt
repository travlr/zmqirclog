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