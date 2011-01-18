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
| [Friday 07 January 2011] [09:17:14] <codebeaker>	hey everyone
| [Friday 07 January 2011] [09:26:06] <keffo>	hey ho
| [Friday 07 January 2011] [09:44:48] <codebeaker>	was wondering if anyone could lend me a hand, I'm trying to include mq in my project - I build it with CMake, and I would like a portable "FindMQ.cmake"  I found it in Patrick Chen's github repo, but ZMQ_DIR is always unset I wondered if I'm barking up the wrong tree - and should simply hard-code the paths?
| [Friday 07 January 2011] [09:45:55] <codebeaker>	right now, I have the maint branch from the @zeromq repository built and installed the defailt location, and a as a submodule in my project
| [Friday 07 January 2011] [09:49:08] <zchrish>	Hi.
| [Friday 07 January 2011] [09:49:18] <codebeaker>	 easy problem really, the linker isn't finding the library - not all together surprising, but I'd like a portable solution
| [Friday 07 January 2011] [09:51:26] <zchrish>	I have downloaded zeromq to my OpenSuse box and compiled the examples. I modified the mtserver and hwclient to suppress the printf and increased the message length to 80 bytes. When I run the program and pass 1000000 messages into it, it seems like the software works at around 7,500 messages per second. This seems low; any pointers?
| [Friday 07 January 2011] [09:55:00] <zchrish>	AAA
| [Friday 07 January 2011] [09:55:27] <keffo>	?
| [Friday 07 January 2011] [09:55:43] <zchrish>	I have downloaded zeromq to my OpenSuse box and compiled the examples. I modified the mtserver and hwclient to suppress the printf and increased the message length to 80 bytes. When I run the program and pass 1000000 messages into it, it seems like the software works at around 7,500 messages per second. This seems low; any pointers?
| [Friday 07 January 2011] [10:13:41] <sustrik>	zchrish: are you using local_thr & remote_thr to measure the throughput?
| [Friday 07 January 2011] [11:43:41] <zchrish>	I am just using the code out-of-the-box. Not sure how to answer the question; I am new to zeromq
| [Friday 07 January 2011] [11:47:29] <zchrish>	sustrik: I am measuring on the same machine.
| [Friday 07 January 2011] [12:04:37] <sustrik>	zchrish: how have you get the number?
| [Friday 07 January 2011] [12:04:39] <sustrik>	7500?
| [Friday 07 January 2011] [12:13:06] <zchrish>	sustrik: (1) started mtserver, (2) time hwclient
| [Friday 07 January 2011] [12:14:07] <zchrish>	sustrik: both mtserver and hwclient were stripped of printf statements and the sleep(1) was removed from mtserver and the number of iterations was increased to 1 million
| [Friday 07 January 2011] [12:14:50] <zchrish>	runtime / # iterations was about 7,500.
| [Friday 07 January 2011] [12:15:23] <zchrish>	sorry; other way around.
| [Friday 07 January 2011] [12:15:37] <sustrik>	that's something from the guide?
| [Friday 07 January 2011] [12:15:45] <sustrik>	anyway, try the offical perf tests:
| [Friday 07 January 2011] [12:15:46] <sustrik>	http://www.zeromq.org/results:perf-howto
| [Friday 07 January 2011] [12:16:06] <zchrish>	yes, in the c++ section. I will look at perf-howto; thank you.
| [Friday 07 January 2011] [13:27:09] <zchrish>	sustrik: OK, I ran these programs and the throughput is much higher. I will look more closely into how mtserver and hwclient are constructed to see how I can modify them to improve the throughput of these programs.
| [Friday 07 January 2011] [19:14:38] <codebeaker>	does anyone have a few mins, to help me get my project (CMake build) to work with Patrick Chen's CMake form of mq ?
| [Friday 07 January 2011] [19:17:10] <codebeaker>	Right now I can't get it to recognise ZMQ_DIR
| [Friday 07 January 2011] [20:11:28] <Seta00>	anyone experienced with pyzmq here?
| [Friday 07 January 2011] [20:11:32] <Seta00>	(on Windows)
| [Saturday 08 January 2011] [08:07:02] <s0undt3ch>	hello ppl
| [Saturday 08 January 2011] [08:07:45] <s0undt3ch>	while trying to send on a zmq.REQ socket, if the socket is not correctly connected, how can I catch the error?
| [Saturday 08 January 2011] [08:14:07] <sustrik>	you can't the messages are queued and will be send once to connecting succeeds
| [Saturday 08 January 2011] [08:40:50] <s0undt3ch>	sustrik: hmm, not the intended behaviour, what do you suggest?
| [Saturday 08 January 2011] [08:41:01] <s0undt3ch>	s/intended/desired
| [Saturday 08 January 2011] [08:43:16] <sustrik>	you mean when you misconfigure your component, right?
| [Saturday 08 January 2011] [08:43:50] <sustrik>	using an un-existent hostname or somesuch
| [Saturday 08 January 2011] [08:44:55] <s0undt3ch>	sustrik: yeah
| [Saturday 08 January 2011] [08:45:18] <s0undt3ch>	sustrik: right now I'm trying to build some king of ping/pong for my app's components
| [Saturday 08 January 2011] [08:45:54] <sustrik>	well, the requirement for 0mq is to withstand network failures
| [Saturday 08 January 2011] [08:45:55] <s0undt3ch>	but I'd like to know who's responding and calculate lag's 
| [Saturday 08 January 2011] [08:46:07] <sustrik>	so when it cannot connect
| [Saturday 08 January 2011] [08:46:16] <sustrik>	it tries a bit later on
| [Saturday 08 January 2011] [08:46:25] <s0undt3ch>	hmm
| [Saturday 08 January 2011] [08:47:05] <s0undt3ch>	sustrik: use pub/sub instead? those replying should then include their name etc...?
| [Saturday 08 January 2011] [08:47:34] <s0undt3ch>	instead of req/rep?
| [Saturday 08 January 2011] [08:52:19] <s0undt3ch>	hmm, I think I should look closely to the heartbeat example
| [Saturday 08 January 2011] [11:01:58] <mikko>	afternoon
| [Saturday 08 January 2011] [12:21:13] <andrewvc_>	cremes: Around?
| [Saturday 08 January 2011] [12:21:56] Notice	-ChanServ- [#gentoo] Welcome to #gentoo || Acceptable Usage Policy @ http://www.gentoo.org/main/en/irc.xml || Keep the language clean || Google is your friend || No bots or scripts that talk || Turn off public away messages || More than three lines to #flood or a pastebin service, no spam!
| [Saturday 08 January 2011] [12:26:37] <mikko>	sustrik: shutdown stress failing on freebsd 8.1
| [Saturday 08 January 2011] [12:27:13] Error	You are not on #gentoo.
| [Saturday 08 January 2011] [12:29:14] <sustrik>	let me see
| [Saturday 08 January 2011] [12:30:56] <sustrik>	that's the same problem with insufficient buffer space in socketpair as was seen several time before
| [Saturday 08 January 2011] [12:31:01] <sustrik>	there's no easy solution
| [Saturday 08 January 2011] [12:31:18] <sustrik>	presumably, we can make the stress test less stresfull :)
| [Saturday 08 January 2011] [19:27:56] <andrewvc>	cremes: ping
| [Sunday 09 January 2011] [02:05:27] <maxpn>	how can I handle timeouts in pyzmq ?
| [Sunday 09 January 2011] [02:05:48] <maxpn>	for PUSH socket
| [Sunday 09 January 2011] [02:24:55] <maxpn>	hmm... looks like I should use NOBLOCK in a loop
| [Sunday 09 January 2011] [05:26:56] <s0undt3ch>	hello ppl
| [Sunday 09 January 2011] [05:27:36] <s0undt3ch>	xreq_socket.recv(zmq.NOBLOCK) should never, ever block right? seems it's blocking for at least 1.5 secs for me :\
| [Sunday 09 January 2011] [05:32:32] <mikko>	maxpn: you can use poll
| [Sunday 09 January 2011] [05:32:43] <mikko>	s0undt3ch: it shouldn't block
| [Sunday 09 January 2011] [05:33:23] <s0undt3ch>	mikko: I'm using evenlet with zmq, it has block detector, I'm setting it to 1.5 secs, and it's triggering :|
| [Sunday 09 January 2011] [05:34:12] <mikko>	are you doing more than "xreq_socket.recv(zmq.NOBLOCK)" in that block of code?
| [Sunday 09 January 2011] [05:35:32] <s0undt3ch>	mikko: involved blocks of code -> http://paste.pocoo.org/show/317519/
| [Sunday 09 January 2011] [05:35:38] <maxpn>	is there an option like recv(NOBLOCK, timeout= ... )
| [Sunday 09 January 2011] [05:37:22] <maxpn>	would be very usable
| [Sunday 09 January 2011] [05:38:21] <mikko>	maxpn: noblock returns immediately
| [Sunday 09 January 2011] [05:39:01] <mikko>	maxpn: it's very simple to do with poll
| [Sunday 09 January 2011] [05:39:04] <maxpn>	mikko: yes, but in that case I have to sleep
| [Sunday 09 January 2011] [05:39:11] <maxpn>	for some amount of time
| [Sunday 09 January 2011] [05:40:54] <mikko>	maxpn: https://github.com/mkoppanen/httpush/blob/master/src/helpers.c#L110
| [Sunday 09 January 2011] [05:41:00] <mikko>	there is similar thing in C
| [Sunday 09 January 2011] [05:41:22] <mikko>	it uses poll to handle the timeout
| [Sunday 09 January 2011] [05:42:28] <mikko>	s0undt3ch: are you getting eagain?
| [Sunday 09 January 2011] [05:42:38] <s0undt3ch>	mikko: nope
| [Sunday 09 January 2011] [05:42:57] <mikko>	s0undt3ch: you are sure that it actually blocks inside recv call?
| [Sunday 09 January 2011] [05:43:01] <maxpn>	ok I see, is such an option for Python?
| [Sunday 09 January 2011] [05:43:23] <mikko>	maxpn: yes, poll
| [Sunday 09 January 2011] [05:43:27] <s0undt3ch>	mikko: aparently is, I'm trying to refactor it a bit to try and confirm it
| [Sunday 09 January 2011] [05:43:48] <mikko>	maxpn: https://github.com/zeromq/pyzmq/blob/master/examples/poll/pair.py
| [Sunday 09 January 2011] [05:48:31] <maxpn>	as I understand poller.poll() returns a list of paris (socket,state) , right?
| [Sunday 09 January 2011] [05:53:35] <mikko>	maxpn: i don't really know how it's implemented in python
| [Sunday 09 January 2011] [05:55:03] <maxpn>	poller.poll() will return data when complete ZMQ message received in POLLIN socket?
| [Sunday 09 January 2011] [05:55:47] <mikko>	it will retur when there is a state change in one or more of the sockets in the poll set
| [Sunday 09 January 2011] [05:57:22] <s0undt3ch>	mikko: how can I know if a message is complete?
| [Sunday 09 January 2011] [05:57:39] <mikko>	s0undt3ch: you mean with x(rep|req) sockets?
| [Sunday 09 January 2011] [05:57:45] <s0undt3ch>	mikko: yes
| [Sunday 09 January 2011] [05:58:20] <mikko>	the first parts will contain RCVMORE flag
| [Sunday 09 January 2011] [05:58:35] <mikko>	the part that doesn't contain it terminates the message
| [Sunday 09 January 2011] [05:59:31] <s0undt3ch>	mikko: so I can append to a buffer untill I get RCVMORE at wich time I can process the message right?
| [Sunday 09 January 2011] [06:00:10] <mikko>	the other way around
| [Sunday 09 January 2011] [06:00:26] <s0undt3ch>	ah yes
| [Sunday 09 January 2011] [06:01:04] <mikko>	RCVMORE indicates that there is at least one more part coming 
| [Sunday 09 January 2011] [06:01:37] <maxpn>	is recv_json() handles that situation correctly?
| [Sunday 09 January 2011] [06:01:42] <s0undt3ch>	mikko: xrep.getsockopt(zmq.RCVMORE) right?
| [Sunday 09 January 2011] [06:01:54] <mikko>	s0undt3ch: yes
| [Sunday 09 January 2011] [06:02:09] <mikko>	maxpn: i don't really know, that sounds like a python specific method
| [Sunday 09 January 2011] [06:02:36] <s0undt3ch>	mikko: RCVMORE is socket option right?
| [Sunday 09 January 2011] [06:02:53] <s0undt3ch>	ie, I test it in getsockopt
| [Sunday 09 January 2011] [06:03:28] <mikko>	yes
| [Sunday 09 January 2011] [06:03:47] <s0undt3ch>	mikko: Hurray! Thanks! Now working as suposed
| [Sunday 09 January 2011] [06:04:36] <s0undt3ch>	was implementing a heartbeater and each of the hearts, if more than one, would fail in turns, which let me to think that my could must have been wrong
| [Sunday 09 January 2011] [06:06:42] <s0undt3ch>	but now one of the processors is at 100% :)
| [Sunday 09 January 2011] [06:06:50] <s0undt3ch>	need to refactor again
| [Sunday 09 January 2011] [06:12:32] <mikko>	s0undt3ch: spinning on something?
| [Sunday 09 January 2011] [06:13:12] <s0undt3ch>	mikko: I think I'm checking socket state too often, unfotunately, eventlet does not allow listening to fd changes
| [Sunday 09 January 2011] [06:13:42] <s0undt3ch>	ok, now dropped to 8-10%
| [Sunday 09 January 2011] [06:13:46] <s0undt3ch>	:)
| [Sunday 09 January 2011] [06:23:55] <s0undt3ch>	handling 50 heartbeats at 7-9% ;)
| [Sunday 09 January 2011] [07:05:22] <s0undt3ch>	a REQ socket can be connected to multiple "endpoints" right? can it send a message to a specific endpoint?
| [Sunday 09 January 2011] [07:06:34] <s0undt3ch>	or sending will send to all and the receiving endpoint cannot know for who the message is?
| [Sunday 09 January 2011] [07:56:02] <zchrish>	That's my question. I am reading 3.0 roadmap and it appears that TCP and PUB/SUB are distributed across all receivers.
| [Sunday 09 January 2011] [07:57:05] <zchrish>	I think in this reference TCP=REQ.
| [Sunday 09 January 2011] [11:31:45] Notice	-NickServ- This nickname is registered. Please choose a different nickname, or identify via /msg NickServ identify <password>.
| [Sunday 09 January 2011] [11:31:45] Notice	-NickServ- You are now identified for travlr.
| [Sunday 09 January 2011] [12:01:55] <sustrik>	s0undt3ch: you send a request to a "cloud"
| [Sunday 09 January 2011] [12:02:06] <sustrik>	so it eventually gets to someone
| [Sunday 09 January 2011] [12:16:46] Notice	-NickServ- This nickname is registered. Please choose a different nickname, or identify via /msg NickServ identify <password>.
| [Sunday 09 January 2011] [12:16:46] Notice	-NickServ- You are now identified for travlr.
| [Sunday 09 January 2011] [13:02:48] <s0undt3ch>	sustrik: I'm trying to do some aync message handling. I have gobject listening for the socket's FD and when there's a change on it, a function is called. For REQ/REP, this is ok, I handle incoming message aync, and outgoing messages sync, however,  for XREP, I seem to be unable to  do async out messages
| [Sunday 09 January 2011] [13:03:07] <s0undt3ch>	especially since I'm calling socket.send_pyobj(data)
| [Sunday 09 January 2011] [13:03:26] <s0undt3ch>	I think that makes the socket go into zmq.POLLOUT
| [Sunday 09 January 2011] [13:03:38] <s0undt3ch>	but how do I handle zmq.POLLOUT?
| [Sunday 09 January 2011] [13:06:16] <s0undt3ch>	intead of directly calling send() should I put messages in a queue and then handle them in the queue?
| [Sunday 09 January 2011] [13:07:21] <s0undt3ch>	am I making any sense?
| [Sunday 09 January 2011] [13:15:07] <sustrik>	have a look at zmq_getsockopt(3), the ZMQ_FD and ZMQ_EVENTS section
| [Sunday 09 January 2011] [13:15:36] <sustrik>	ZMQ_FD signals that "something happened"
| [Sunday 09 January 2011] [13:15:48] <sustrik>	you have to get ZMQ_EVENTS to find out what actually happened
| [Sunday 09 January 2011] [13:17:53] <s0undt3ch>	sustrik: that part I know, that's how I'm handling incoming messges, I'm just failing to get own to handle outgoing messages with the same resources, ie, EVENTS and FD
| [Sunday 09 January 2011] [13:19:39] <s0undt3ch>	I already catched the (events & POOLOUT), just don't know what and from where to actualy send, since I've already done .send()
| [Sunday 09 January 2011] [13:23:31] <s0undt3ch>	s/own/how/
| [Sunday 09 January 2011] [13:24:48] <s0undt3ch>	is there a way to get the contents of the outgoing XREP buffer?
| [Sunday 09 January 2011] [13:25:37] <s0undt3ch>	perhaps better
| [Sunday 09 January 2011] [13:25:48] <s0undt3ch>	if I try to send NOBLOCK, how do I handle it?
| [Sunday 09 January 2011] [13:28:24] <sustrik>	send with a non-block
| [Sunday 09 January 2011] [13:28:40] <sustrik>	if it cannot be sent it returns EAGAIN
| [Sunday 09 January 2011] [13:28:48] <sustrik>	then you can poll on ZMQ_FD
| [Sunday 09 January 2011] [13:28:58] <sustrik>	once it signals POLLIN
| [Sunday 09 January 2011] [13:29:04] <sustrik>	you getsockopt(ZMQ_EVENTS)
| [Sunday 09 January 2011] [13:29:19] <sustrik>	if ZMQ_POLLOUT is set, you can send the message
| [Sunday 09 January 2011] [14:33:55] <zchrish>	Is using a vector a supported method to implement socket_t? I want to service 10,000 different subscription channels so that each channel has independent information. According to the roadmap, all data goes to all subscribers even if a subscriber is only interested in certain data. 
| [Sunday 09 January 2011] [14:42:06] <mikko>	zchrish: currently the filtering is done at subscriber side, correct
| [Sunday 09 January 2011] [14:42:52] <zchrish>	mikko: Yes, that is what I have learned. I don't want to do that; too much information flying across the publisher.
| [Sunday 09 January 2011] [14:54:22] <sustrik>	zchrish: why not use a single pub socket with subscriptions instead of handling 10,000 sockets
| [Sunday 09 January 2011] [14:55:49] <sustrik>	and rather focus on implementing subscription forwarding inside 0mq
| [Sunday 09 January 2011] [14:56:09] <zchrish>	sustrik: I'd like to but as far as I can tell, if my subscriber only wants data to travel across the wire for only 1 of the 10,000 channels, that isn't currently supported. The roadmap says that is a 3.0 feature possibly.
| [Sunday 09 January 2011] [14:57:05] <sustrik>	it can go even to 2.x if someone actually implements it
| [Sunday 09 January 2011] [14:57:17] <sustrik>	there are several people trying at the moment
| [Sunday 09 January 2011] [14:57:34] <zchrish>	So what to do now?
| [Sunday 09 January 2011] [14:58:02] <sustrik>	it's up to you
| [Sunday 09 January 2011] [14:58:22] <sustrik>	you can either write your code to use 10,000 sockets
| [Sunday 09 January 2011] [14:58:41] <sustrik>	or instead try to implement the subscription forwarding inside 0mq
| [Sunday 09 January 2011] [14:58:44] <zchrish>	So my idea was to create a vector of publishers and bind them to different ports. Sort of crude but was wondering if it was even supported.
| [Sunday 09 January 2011] [14:59:03] <sustrik>	yes, you can do that
| [Sunday 09 January 2011] [14:59:40] <zchrish>	can you estimate the work difference?
| [Sunday 09 January 2011] [14:59:52] <zchrish>	between the 2 methods?
| [Sunday 09 January 2011] [15:00:31] <sustrik>	well, the developer has to estimate the work
| [Sunday 09 January 2011] [15:00:40] <sustrik>	have a look at the mailing list
| [Sunday 09 January 2011] [15:00:53] <zchrish>	understood; thank you.
| [Sunday 09 January 2011] [15:00:58] <sustrik>	the subscription forwarding was discussed several times there
| [Sunday 09 January 2011] [15:01:03] <sustrik>	you'll get some idea
| [Sunday 09 January 2011] [15:02:07] <zchrish>	At this point, I'd like to remain a user of zeromq in my application and focus on that. Seems like great software but this feature seems really important as I guess people already know.
| [Sunday 09 January 2011] [15:03:03] <sustrik>	sure, it's up to you
| [Sunday 09 January 2011] [15:03:42] <zchrish>	But maybe I could be beta people's work if that'd help. I agree subscription forwarding is the way to go.
| [Sunday 09 January 2011] [15:11:02] <sustrik>	well, as i said, there are people trying, let's see what emerges
| [Sunday 09 January 2011] [20:17:53] <rbraley>	is there a good way to write to a file asynchronously in zeromq?
| [Monday 10 January 2011] [03:57:01] <mikko>	rbraley: can you elaborate a bit?
| [Monday 10 January 2011] [07:54:14] <CIA-21>	zeromq2: 03Martin Sustrik 07master * rbd0ba6e 10/ (6 files in 2 dirs): 
| [Monday 10 January 2011] [07:54:14] <CIA-21>	zeromq2: Size of inproc hwm and swap is sum of peers' hwms and swaps
| [Monday 10 January 2011] [07:54:14] <CIA-21>	zeromq2: The meat of the patch was contributed by Douglas Creager.
| [Monday 10 January 2011] [07:54:14] <CIA-21>	zeromq2: Martin Sustrik implemented storing peer options in inproc
| [Monday 10 January 2011] [07:54:14] <CIA-21>	zeromq2: endpoint repository.
| [Monday 10 January 2011] [07:54:14] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/fE9QLj
| [Monday 10 January 2011] [09:34:11] <zchrish>	Is there a way to control which IP addresses subscribe to a publisher?
| [Monday 10 January 2011] [09:50:43] <sustrik>	firewall?
| [Monday 10 January 2011] [10:11:29] <zchrish>	OK; I assumed that was the design of the package. Thank you.
| [Monday 10 January 2011] [12:25:54] <zchrish>	Is there a way to determine which IP addresses are subscribed to a publisher?
| [Monday 10 January 2011] [12:28:47] <cremes>	zchrish: not from within the framework
| [Monday 10 January 2011] [12:29:03] <zchrish>	ok; thank you.
| [Monday 10 January 2011] [12:48:25] <s0undt3ch>	hello ppl
| [Monday 10 January 2011] [12:48:27] <s0undt3ch>	using pyzmq
| [Monday 10 January 2011] [12:48:47] <s0undt3ch>	if we want to filter PUB/SUB messages, we need to send them multipart?
| [Monday 10 January 2011] [12:50:55] <Vince__>	hey
| [Monday 10 January 2011] [12:53:15] <Vince__>	I've making a wrapper and zmq_bind crashes. I am certain I am sending the right information at the API zmq_bind%(pSoc%,psAddr$):"zmq_bind"  and RetVal = zmq_bind(pSoc, "tcp://*:5555")
| [Monday 10 January 2011] [12:53:20] <sustrik>	s0undt3ch: no
| [Monday 10 January 2011] [12:53:34] <s0undt3ch>	sustrik: plain send right?
| [Monday 10 January 2011] [12:53:41] <sustrik>	yes
| [Monday 10 January 2011] [12:54:06] <sustrik>	Vince__: what's the crash?
| [Monday 10 January 2011] [12:54:15] <s0undt3ch>	send_pyobj won't allow this :\
| [Monday 10 January 2011] [12:54:50] <sustrik>	how come?
| [Monday 10 January 2011] [12:55:16] <Vince__>	Unfortunately I don't know because this is a user library for Blitz Basic and the debugger crashes with no output.
| [Monday 10 January 2011] [12:55:49] <sustrik>	hard to help then
| [Monday 10 January 2011] [12:56:19] <sustrik>	but i haven't seen any reports about zmq_bind crashing yet
| [Monday 10 January 2011] [12:56:33] <sustrik>	so maybe you should look at the layers above first
| [Monday 10 January 2011] [12:56:46] <s0undt3ch>	sustrik: send_pyobj pickles and unpicles the object we pass, filtering is done similar to msg.startswith() which won't work on a pickled string
| [Monday 10 January 2011] [12:57:08] <sustrik>	i see
| [Monday 10 January 2011] [12:57:19] <sustrik>	then maybe make a pyzmq patch
| [Monday 10 January 2011] [12:57:26] <sustrik>	to allow simple pub/sub messages
| [Monday 10 January 2011] [12:57:30] <Vince__>	Is it possible to make zeromq to a debug dump as API access occurs? Maybe to a text file or something?
| [Monday 10 January 2011] [12:58:00] <s0undt3ch>	sustrik: simple pub/sub messages, text messages, it supports them, I just wanted the pickling/unpickling to be automated ;)
| [Monday 10 January 2011] [12:58:15] <sustrik>	Vince__: you can create a core dump and inspect it in debugger afterwards
| [Monday 10 January 2011] [12:58:38] <s0undt3ch>	If I pickle/unpickle myself, I can do, 'filter <pickled_string>'
| [Monday 10 January 2011] [12:58:50] <s0undt3ch>	but then I have to be the one pickling and unpickling
| [Monday 10 January 2011] [13:00:41] <sustrik>	i see
| [Monday 10 January 2011] [13:04:35] <s0undt3ch>	anyway, since the filtering is done on the client side, I might skip it or work arround that issue
| [Monday 10 January 2011] [13:22:44] <guido_g>	why not put the topic (plus '\0') before the pickled data and on receive split on the first '\0'?
| [Monday 10 January 2011] [13:37:43] <s0undt3ch>	guido_g: that's an idea, but it needs to be done on the python bindings
| [Monday 10 January 2011] [13:37:57] <guido_g>	why?
| [Monday 10 January 2011] [13:38:41] <s0undt3ch>	guido_g: because using recv_pyobjc does the unplickling for us, so, \0 spliting should be done before unpickling
| [Monday 10 January 2011] [13:38:51] <s0undt3ch>	ecv_pyobj
| [Monday 10 January 2011] [13:38:54] <s0undt3ch>	errrr
| [Monday 10 January 2011] [13:38:57] <s0undt3ch>	*recv_pyobj
| [Monday 10 January 2011] [13:39:49] <guido_g>	recv_pyobj is a general method, not only for sub sockets
| [Monday 10 January 2011] [13:40:27] <guido_g>	just derive a class and implement your desired behaviour
| [Monday 10 January 2011] [13:40:47] <guido_g>	much much easier, for you and the pyzmq devs
| [Monday 10 January 2011] [13:41:09] <s0undt3ch>	that can be done to, sure, but then I'd have to also subclass Context in order for it to return my socket implementation
| [Monday 10 January 2011] [13:41:36] <guido_g>	just start to use a factory
| [Monday 10 January 2011] [13:41:36] <s0undt3ch>	guido_g: so right now, I might just use another socket for the filtering :)
| [Monday 10 January 2011] [14:08:18] <s0undt3ch>	guido_g: http://paste.pocoo.org/show/318466/
| [Monday 10 January 2011] [14:09:26] <guido_g>	this is for sub sockets only?
| [Monday 10 January 2011] [14:10:17] <s0undt3ch>	guido_g: when you mean sub, you mean those we get from context.socket?
| [Monday 10 January 2011] [14:10:40] <s0undt3ch>	well, anyway dunno, all of those that make use of socket.pyx
| [Monday 10 January 2011] [14:10:42] <guido_g>	no
| [Monday 10 January 2011] [14:10:56] <guido_g>	i mean sockets of type zmq.SUB
| [Monday 10 January 2011] [14:11:08] <s0undt3ch>	ah
| [Monday 10 January 2011] [14:11:15] <s0undt3ch>	didn't though of that
| [Monday 10 January 2011] [14:11:16] <s0undt3ch>	:)
| [Monday 10 January 2011] [14:11:17] <guido_g>	or zmq.PUB
| [Monday 10 January 2011] [14:11:26] <guido_g>	so you allow a topic for all sockets
| [Monday 10 January 2011] [14:11:33] <guido_g>	which is silly
| [Monday 10 January 2011] [14:11:36] <s0undt3ch>	yes
| [Monday 10 January 2011] [14:13:22] <guido_g>	as I said, implement a socket factory where you register your _special_ sockets
| [Monday 10 January 2011] [14:14:24] <guido_g>	so you don't need to patch a perfectly nice working module and would gain a higher degree of freedom
| [Monday 10 January 2011] [14:17:12] <s0undt3ch>	yeah
| [Monday 10 January 2011] [17:16:52] <vince____>	Finally managed to get an error out of Bind failing on my wrapper. First-chance exception at 0x762cb727 in test.exe: Microsoft C++ exception: zmq::error_t at memory location 0x0019f8f0..
| [Monday 10 January 2011] [17:30:37] <mikko>	vince____: is that an unhandled exception?
| [Monday 10 January 2011] [22:13:11] <potatodemon>	Howdy, how many queues can 0mq handle on a machine with a gig of ram?
| [Tuesday 11 January 2011] [07:20:02] <mikko>	hi steve
| [Tuesday 11 January 2011] [07:20:43] <mikko>	is it possible to have the scons to build to a specific subdirectory rather than platform specific one?
| [Tuesday 11 January 2011] [07:21:00] <mikko>	i played around during weekend with invoking scons build from zeromq build
| [Tuesday 11 January 2011] [07:26:11] <Steve-o>	just use autoconf & automake?
| [Tuesday 11 January 2011] [07:26:43] <Steve-o>	check the new trunk, committed support ~90 mins ago
| [Tuesday 11 January 2011] [07:27:15] <Steve-o>	please test on old platforms as I've hard coded the minimum versions to Ubuntu 10.10 :-)
| [Tuesday 11 January 2011] [07:27:37] <Steve-o>	"silent building" is limited to automake 1.11 I think
| [Tuesday 11 January 2011] [07:28:03] <Steve-o>	I'll have a look at CMake for Windows later
| [Tuesday 11 January 2011] [07:28:11] <mikko>	yes, automake would make things easier
| [Tuesday 11 January 2011] [07:28:39] <mikko>	the current way doesn't seem sustainable to me in the longer run
| [Tuesday 11 January 2011] [07:28:56] <mikko>	another question was about openpgm ABI/API
| [Tuesday 11 January 2011] [07:29:11] <mikko>	is there a guarantee in openpgm related to those?
| [Tuesday 11 January 2011] [07:29:33] <Steve-o>	The version numbers tie to the ABI
| [Tuesday 11 January 2011] [07:30:01] <Steve-o>	minor version on ABI changes, micro version on fixes
| [Tuesday 11 January 2011] [07:30:35] <Steve-o>	I've tried setting release/version-info with automake
| [Tuesday 11 January 2011] [07:30:42] <mikko>	because if we invoke openpgm build from 0mq we could support specifying arbitrary openpgm location as well
| [Tuesday 11 January 2011] [07:30:52] <mikko>	so that we wouldn't force certain version of openpgm
| [Tuesday 11 January 2011] [07:31:09] <Steve-o>	with autoconf distros are more likely to package it :D
| [Tuesday 11 January 2011] [07:31:17] <mikko>	brb, lunch
| [Tuesday 11 January 2011] [08:42:02] <sustrik>	mikko: have you seen the s360 patch?
| [Tuesday 11 January 2011] [08:42:33] <sustrik>	oh, it wasnt't sent to the mailing list
| [Tuesday 11 January 2011] [08:42:36] <sustrik>	wait a sec
| [Tuesday 11 January 2011] [08:45:01] <sustrik>	sent to the mailing list
| [Tuesday 11 January 2011] [10:18:03] <Skaag>	I want to subscribe to the mailing list
| [Tuesday 11 January 2011] [10:21:35] <mikko>	Skaag: http://lists.zeromq.org/mailman/listinfo/zeromq-dev
| [Tuesday 11 January 2011] [10:23:26] <Skaag>	thank you :)
| [Tuesday 11 January 2011] [10:23:34] <Skaag>	my internet is painfully slow :-(
| [Tuesday 11 January 2011] [10:23:45] <Skaag>	So even subscribing to this will take a while
| [Tuesday 11 January 2011] [10:24:45] <Skaag>	there, done, thankfully that page is very minimalistic and not loaded with images
| [Tuesday 11 January 2011] [11:18:58] <jugg>	sustrik, my implementation of erlzmq can be found here: https://github.com/csrl/erlzmq   If you want me to push to the zeromq/erlzmq repo, let me know.
| [Tuesday 11 January 2011] [12:54:08] <sustrik>	jugg: try to ask serge aleynikov first
| [Tuesday 11 January 2011] [12:54:20] <sustrik>	he've been maintaining the erlzmq
| [Tuesday 11 January 2011] [12:54:51] <sustrik>	serge@aleynikov.org
| [Tuesday 11 January 2011] [13:03:03] <s0undt3ch>	on a PUB socket, it can only be binded by a single instance? ie, can serveral unrelated parts of my code be bind to the same PUB socket?
| [Tuesday 11 January 2011] [13:03:47] <s0undt3ch>	from what I'm seeing from my code, it apears that it works like that :\
| [Tuesday 11 January 2011] [13:04:06] <s0undt3ch>	do I need to create a FORWARDER device of some kind?
| [Tuesday 11 January 2011] [13:06:09] <s0undt3ch>	sustrik: any idea?
| [Tuesday 11 January 2011] [13:07:20] <sustrik>	no. several sockets can't bind to the same endpoint
| [Tuesday 11 January 2011] [13:07:50] <sustrik>	if there are N pubs and M subs you need a forwarding device of some kind
| [Tuesday 11 January 2011] [13:08:03] <sustrik>	0MQ socket is always 1:N
| [Tuesday 11 January 2011] [13:08:23] <sustrik>	N:M topologies are created using devices in the middle
| [Tuesday 11 January 2011] [13:09:10] <s0undt3ch>	sustrik: hmm, any examples of that anywhere?
| [Tuesday 11 January 2011] [13:09:52] <guido_g>	http://paste.pocoo.org/show/318987/   <- minimal forwarder config
| [Tuesday 11 January 2011] [13:10:11] <guido_g>	the in address is where the pubs connect to
| [Tuesday 11 January 2011] [13:10:18] <guido_g>	the out where the subs connect to
| [Tuesday 11 January 2011] [13:10:48] <guido_g>	simply start zmq_forwarder <config-file>
| [Tuesday 11 January 2011] [13:10:48] <s0undt3ch>	hmm, ok
| [Tuesday 11 January 2011] [13:10:50] <s0undt3ch>	Thanks!
| [Tuesday 11 January 2011] [13:11:38] <guido_g>	you can have multiple bind addresses per section
| [Tuesday 11 January 2011] [13:12:10] <sustrik>	the config file looks something like this:
| [Tuesday 11 January 2011] [13:12:11] <sustrik>	<forwarder>
| [Tuesday 11 January 2011] [13:12:11] <sustrik>	    <in>
| [Tuesday 11 January 2011] [13:12:12] <sustrik>	        <bind addr = "tcp://eth0:5555&quot;/>
| [Tuesday 11 January 2011] [13:12:12] <sustrik>	    </in>
| [Tuesday 11 January 2011] [13:12:12] <sustrik>	    <out>
| [Tuesday 11 January 2011] [13:12:13] <sustrik>	        <bind addr = "tcp://eth0:5556&quot;/>
| [Tuesday 11 January 2011] [13:12:15] <sustrik>	    </out>
| [Tuesday 11 January 2011] [13:12:17] <sustrik>	</forwarder>
| [Tuesday 11 January 2011] [13:12:36] <s0undt3ch>	guido_g: the forwarder device will then allow multiple binds and connects
| [Tuesday 11 January 2011] [13:12:46] <s0undt3ch>	I thinks that's what I'm really after
| [Tuesday 11 January 2011] [13:12:51] <s0undt3ch>	*think
| [Tuesday 11 January 2011] [13:12:52] <sustrik>	oops, there should be double quoute instead of &quot;
| [Tuesday 11 January 2011] [13:12:57] <s0undt3ch>	yeah
| [Tuesday 11 January 2011] [13:13:05] <s0undt3ch>	I also saw guido_g's paste
| [Tuesday 11 January 2011] [13:13:07] <guido_g>	you PUB sockets all connect to the in addresses
| [Tuesday 11 January 2011] [13:13:19] <sustrik>	ah, i missed that
| [Tuesday 11 January 2011] [13:13:20] <s0undt3ch>	yeah, I think I got it
| [Tuesday 11 January 2011] [13:13:21] <guido_g>	you SUB sockets connect to the out addresses
| [Tuesday 11 January 2011] [13:45:49] <s0undt3ch>	do I need to set zmq.SUBSCRIBE on the device?
| [Tuesday 11 January 2011] [13:47:36] <guido_g>	no
| [Tuesday 11 January 2011] [13:47:44] <guido_g>	just what i pasted
| [Tuesday 11 January 2011] [13:51:42] <s0undt3ch>	guido_g: I'm not using zmq_formwarder, I'm using the python bindings :\
| [Tuesday 11 January 2011] [13:52:12] <guido_g>	writing you own device? why?
| [Tuesday 11 January 2011] [13:52:28] <guido_g>	btw, i'm also using python
| [Tuesday 11 January 2011] [13:52:59] <s0undt3ch>	guido_g: zmq_forwarder is python?
| [Tuesday 11 January 2011] [13:53:04] <guido_g>	no
| [Tuesday 11 January 2011] [13:53:24] <guido_g>	its a program that comes with mq
| [Tuesday 11 January 2011] [13:53:37] <s0undt3ch>	guido_g: http://paste.pocoo.org/show/319013/ my forwarding device
| [Tuesday 11 January 2011] [13:54:12] <guido_g>	seems you like it complicated
| [Tuesday 11 January 2011] [13:54:27] <s0undt3ch>	not realy, I'd love to make it simple
| [Tuesday 11 January 2011] [13:54:37] <s0undt3ch>	guido_g: what have I made complicate?
| [Tuesday 11 January 2011] [13:54:59] <guido_g>	by not using what's already there
| [Tuesday 11 January 2011] [13:55:37] <s0undt3ch>	I'm sorry... I don't know all of pyzmq's source code
| [Tuesday 11 January 2011] [13:55:45] <guido_g>	me neither
| [Tuesday 11 January 2011] [13:55:56] <s0undt3ch>	so what's there, where can I read it?
| [Tuesday 11 January 2011] [13:56:07] <guido_g>	but if you install nmq, zmq_forwarder is also installed
| [Tuesday 11 January 2011] [13:56:38] <s0undt3ch>	guido_g: I'm launching my own app, I'm not gonna use subprocess to lauch zmq_forwarder!?
| [Tuesday 11 January 2011] [13:56:56] <s0undt3ch>	espcially since pyzmq also provides irt
| [Tuesday 11 January 2011] [13:56:58] <s0undt3ch>	*it
| [Tuesday 11 January 2011] [13:56:59] <guido_g>	just start it in backround
| [Tuesday 11 January 2011] [13:57:21] <yawn>	regarding jzmq - is there any advice on error handling? i regularly experience the jvm dying due to zmq errors.
| [Tuesday 11 January 2011] [13:57:39] <s0undt3ch>	ok, as a last resort. Can you please, since you also code in python, walk me through setting up the threaddevice?
| [Tuesday 11 January 2011] [13:58:07] <guido_g>	what threaddevice?
| [Tuesday 11 January 2011] [13:58:36] <s0undt3ch>	guido_g: http://zeromq.github.com/pyzmq/api/generated/zmq.devices.basedevice.html#threaddevice
| [Tuesday 11 January 2011] [13:59:55] <guido_g>	where is the problem?
| [Tuesday 11 January 2011] [14:00:09] <s0undt3ch>	guido_g: my code is aparently not working
| [Tuesday 11 January 2011] [14:00:16] <guido_g>	its nearly the same as the config i pasted
| [Tuesday 11 January 2011] [14:00:44] <guido_g>	s0undt3ch: i can't see that from here, to many walls
| [Tuesday 11 January 2011] [14:01:12] <guido_g>	s0undt3ch: iow, could show the error message and the corresponding code?
| [Tuesday 11 January 2011] [14:01:21] <s0undt3ch>	it' s probably the subscriber
| [Tuesday 11 January 2011] [14:01:23] <s0undt3ch>	no error
| [Tuesday 11 January 2011] [14:01:33] <s0undt3ch>	I'm just not getting anything on the M subscribers
| [Tuesday 11 January 2011] [14:01:39] <guido_g>	show code
| [Tuesday 11 January 2011] [14:01:43] <s0undt3ch>	although the N publishers are publishing
| [Tuesday 11 January 2011] [14:03:46] <s0undt3ch>	guido_g: test subscriber
| [Tuesday 11 January 2011] [14:04:15] <guido_g>	s0undt3ch: huh? what does that mean?
| [Tuesday 11 January 2011] [14:04:29] <s0undt3ch>	guido_g: sorry
| [Tuesday 11 January 2011] [14:04:31] <s0undt3ch>	guido_g: test subscriber http://bpaste.net/show/12837/
| [Tuesday 11 January 2011] [14:04:36] <s0undt3ch>	forgot the paste
| [Tuesday 11 January 2011] [14:06:30] <guido_g>	does the device publish to the unix socket the subscriber expects?
| [Tuesday 11 January 2011] [14:06:32] <sustrik>	yawn: what errors are you getting?
| [Tuesday 11 January 2011] [14:06:41] <sustrik>	can you send them to the mailing list?
| [Tuesday 11 January 2011] [14:07:06] <s0undt3ch>	guido_g: http://bpaste.net/show/12838/ test publisher
| [Tuesday 11 January 2011] [14:07:13] <s0undt3ch>	sustrik: no errors at all
| [Tuesday 11 January 2011] [14:07:36] <sustrik>	it's question for yawn
| [Tuesday 11 January 2011] [14:07:46] <sustrik>	he's complaining about jzmq craching
| [Tuesday 11 January 2011] [14:07:55] <s0undt3ch>	sustrik: oh, sorry
| [Tuesday 11 January 2011] [14:08:00] <sustrik>	np
| [Tuesday 11 January 2011] [14:08:15] <s0undt3ch>	guido_g: the forwarder seems to not be forwarding nothing at all
| [Tuesday 11 January 2011] [14:09:07] <guido_g>	s0undt3ch: there is no forwarder involved as far as i can see
| [Tuesday 11 January 2011] [14:09:34] <s0undt3ch>	guido_g: the forwarder was the first paste, the one you said I was complicating
| [Tuesday 11 January 2011] [14:09:54] <guido_g>	*sigh*
| [Tuesday 11 January 2011] [14:10:09] <guido_g>	s0undt3ch: see which endpoints your code is using
| [Tuesday 11 January 2011] [14:10:35] <guido_g>	s0undt3ch: pub and sub are using the unix socket
| [Tuesday 11 January 2011] [14:10:44] <s0undt3ch>	yes
| [Tuesday 11 January 2011] [14:10:54] <s0undt3ch>	can't be unix sockets?
| [Tuesday 11 January 2011] [14:11:10] <s0undt3ch>	guido_g: diferent sockets though
| [Tuesday 11 January 2011] [14:11:19] <s0undt3ch>	xxx-in and xxx-out
| [Tuesday 11 January 2011] [14:15:19] <yawn>	sustrik: Bad file descriptorrc != -1 (kqueue.cpp:79)
| [Tuesday 11 January 2011] [14:15:47] <yawn>	sustrik: "somewhere", no stacktrace available when dealing with jni i suppose
| [Tuesday 11 January 2011] [14:16:12] <sustrik>	is it deterministic?
| [Tuesday 11 January 2011] [14:17:02] <s0undt3ch>	guido_g: test code -> http://bpaste.net/show/12840/
| [Tuesday 11 January 2011] [14:17:08] <s0undt3ch>	guido_g: what's wrong there?
| [Tuesday 11 January 2011] [14:18:45] <guido_g>	ipc endpoints are file names, http://api.zeromq.org/zmq_ipc.html
| [Tuesday 11 January 2011] [14:18:57] <s0undt3ch>	yes
| [Tuesday 11 January 2011] [14:19:15] <s0undt3ch>	that will create a file on the curent dir
| [Tuesday 11 January 2011] [14:19:36] <yawn>	sustrik: no really. only in the sense that it happens from time to time.
| [Tuesday 11 January 2011] [14:19:41] <s0undt3ch>	the diferences in paths on the previous code mean nothing, my app changes dir
| [Tuesday 11 January 2011] [14:21:35] <snidely>	If I have a high volume of stock/option quotes coming into a data center and I want clients connected over a low speed WAN link to subscribe to quotes from that dc.  Should I use 0MQ?  Or do I need some broker based solution so that the whole multicast doesnt have to go over the WAN for key based filtering on each client?
| [Tuesday 11 January 2011] [14:23:12] <sustrik>	snidely, are you looking for solution for both WAN and LAN?
| [Tuesday 11 January 2011] [14:24:06] <sustrik>	in that case the best way is to place forwarder device at the edge of your LAN
| [Tuesday 11 January 2011] [14:24:15] <sustrik>	then use TCP for WAN
| [Tuesday 11 January 2011] [14:24:21] <sustrik>	and multicast only on LAN part
| [Tuesday 11 January 2011] [14:24:33] <s0undt3ch>	guido_g: forwarders can't use unix sockets?
| [Tuesday 11 January 2011] [14:24:46] <guido_g>	don't know, ask sustric
| [Tuesday 11 January 2011] [14:24:59] <s0undt3ch>	sustrik:  forwarders can't use unix sockets?
| [Tuesday 11 January 2011] [14:25:00] <guido_g>	s/c$/k/
| [Tuesday 11 January 2011] [14:25:24] <yawn>	sustrik: but is there a sensible way to handle zmq errors when using it in a jvm?
| [Tuesday 11 January 2011] [14:25:28] <sustrik>	s0oundt3ch: they use the transport you specify
| [Tuesday 11 January 2011] [14:25:52] <sustrik>	it you are using ipc:// then they use unix domain sockets
| [Tuesday 11 January 2011] [14:25:57] <s0undt3ch>	sustrik:  what's wrong with http://bpaste.net/show/12840/?
| [Tuesday 11 January 2011] [14:26:07] <sustrik>	if you use tcp:// they'll use TCP socekts
| [Tuesday 11 January 2011] [14:26:08] <s0undt3ch>	http://bpaste.net/show/12840/
| [Tuesday 11 January 2011] [14:26:11] <s0undt3ch>	yeah
| [Tuesday 11 January 2011] [14:26:22] <s0undt3ch>	but my forwarder isn't forwarding
| [Tuesday 11 January 2011] [14:27:24] <snidely>	yeah I want to be able to have client apps at the datacenter subscribe to quotes (in large volume) and also have apps connected via WAN subscribe in small quantities.   
| [Tuesday 11 January 2011] [14:28:54] <snidely>	Where can I get more info about forwarders?  This is unfinished: http://api.zeromq.org/zmq_forwarder.html
| [Tuesday 11 January 2011] [14:29:17] <sustrik>	it's a simple executable, zmq_forwarder
| [Tuesday 11 January 2011] [14:29:29] <sustrik>	the argument is a config file
| [Tuesday 11 January 2011] [14:29:44] <sustrik>	http://paste.pocoo.org/show/318987/
| [Tuesday 11 January 2011] [14:30:08] <sustrik>	s0oundt3ch: hm, it's a pyzmq implementation of forwarder
| [Tuesday 11 January 2011] [14:30:09] <guido_g>	s0undt3ch: can't get your python forwarder to work even w/ tcp
| [Tuesday 11 January 2011] [14:30:16] <sustrik>	no idea how it works
| [Tuesday 11 January 2011] [14:30:27] <s0undt3ch>	hmmm
| [Tuesday 11 January 2011] [14:30:29] <s0undt3ch>	dam
| [Tuesday 11 January 2011] [14:30:43] <sustrik>	try asking on the mailing list
| [Tuesday 11 January 2011] [14:30:48] <s0undt3ch>	guido_g: something must be terrably wrong
| [Tuesday 11 January 2011] [14:30:53] <sustrik>	pyzmq devs should be able to reply
| [Tuesday 11 January 2011] [14:31:22] <guido_g>	with the original zmq forwarder it works ove rtcp
| [Tuesday 11 January 2011] [14:33:07] <s0undt3ch>	guido_g: the original zmq_forwarder?
| [Tuesday 11 January 2011] [14:33:12] <guido_g>	yes
| [Tuesday 11 January 2011] [14:33:17] <s0undt3ch>	hmm
| [Tuesday 11 January 2011] [14:33:31] <guido_g>	the one that comes with mq
| [Tuesday 11 January 2011] [14:33:45] <guido_g>	the one i pasted the config for
| [Tuesday 11 January 2011] [14:34:43] <s0undt3ch>	yeah
| [Tuesday 11 January 2011] [14:36:30] <guido_g>	just verified that that zmq_forwarder works w/ ipc
| [Tuesday 11 January 2011] [14:37:24] <guido_g>	did you try a zmq.SUBSCRIBE on the in socket of you device?
| [Tuesday 11 January 2011] [14:37:33] <guido_g>	*your
| [Tuesday 11 January 2011] [14:40:30] <s0undt3ch>	guido_g: just tried, it works
| [Tuesday 11 January 2011] [14:40:48] <guido_g>	what a crap
| [Tuesday 11 January 2011] [14:41:12] <s0undt3ch>	guido_g: http://paste.pocoo.org/show/319036/ <- this is what I tried, it works
| [Tuesday 11 January 2011] [14:41:24] <s0undt3ch>	bypasses the device
| [Tuesday 11 January 2011] [14:43:40] <guido_g>	that's what you had before the devices were mentioned, right?
| [Tuesday 11 January 2011] [14:44:05] <s0undt3ch>	guido_g: yes, but I need multiple publishers
| [Tuesday 11 January 2011] [14:44:16] <s0undt3ch>	for multiple subscribers
| [Tuesday 11 January 2011] [14:44:33] <s0undt3ch>	thats where devices came in
| [Tuesday 11 January 2011] [14:44:42] <guido_g>	i know
| [Tuesday 11 January 2011] [14:46:54] <guido_g>	forwarder.setsockopt_in(zmq.SUBSCRIBE, '') <- that's the trick
| [Tuesday 11 January 2011] [14:47:54] <guido_g>	at least it works w/ tcp
| [Tuesday 11 January 2011] [14:48:40] <s0undt3ch>	guido_g: can you paste your code?
| [Tuesday 11 January 2011] [14:48:58] <guido_g>	just add the line shown
| [Tuesday 11 January 2011] [14:49:33] <s0undt3ch>	guido_g: to which paste?
| [Tuesday 11 January 2011] [14:49:39] <guido_g>	omg
| [Tuesday 11 January 2011] [14:49:39] <s0undt3ch>	because I had tried that
| [Tuesday 11 January 2011] [14:50:18] <s0undt3ch>	guido_g: this one?
| [Tuesday 11 January 2011] [14:50:20] <s0undt3ch>	http://bpaste.net/show/12840/
| [Tuesday 11 January 2011] [14:50:35] <guido_g>	http://bpaste.net/show/12841/
| [Tuesday 11 January 2011] [14:53:26] <s0undt3ch>	great, bpast is throwing 500's
| [Tuesday 11 January 2011] [14:53:30] <s0undt3ch>	*bpaste
| [Tuesday 11 January 2011] [14:54:10] <guido_g>	works here
| [Tuesday 11 January 2011] [14:55:50] <s0undt3ch>	dunno then
| [Tuesday 11 January 2011] [14:57:06] <s0undt3ch>	heh, tpc, address already in use....
| [Tuesday 11 January 2011] [14:57:11] <s0undt3ch>	*tcp
| [Tuesday 11 January 2011] [14:57:58] <s0undt3ch>	guido_g: yeah, tried that too
| [Tuesday 11 January 2011] [14:58:06] <s0undt3ch>	guido_g: are you using 2.1.0?
| [Tuesday 11 January 2011] [14:58:14] <guido_g>	no
| [Tuesday 11 January 2011] [14:58:51] <s0undt3ch>	hmm, I am
| [Tuesday 11 January 2011] [14:58:51] <s0undt3ch>	hmm, I am
| [Tuesday 11 January 2011] [14:59:07] <s0undt3ch>	sorry for doubling
| [Tuesday 11 January 2011] [14:59:16] <s0undt3ch>	quassel wasn't responsive
| [Tuesday 11 January 2011] [15:01:39] <s0undt3ch>	ok
| [Tuesday 11 January 2011] [15:01:45] <s0undt3ch>	seems to be a 2.1.0 issue
| [Tuesday 11 January 2011] [15:02:05] <s0undt3ch>	on the subscribers endpoint
| [Tuesday 11 January 2011] [15:04:29] <s0undt3ch>	I think I found a bug
| [Tuesday 11 January 2011] [15:04:47] <s0undt3ch>	just recreating a minimal example to create a ticket
| [Tuesday 11 January 2011] [15:11:14] <s0undt3ch>	dam, with pyzmq's ioloop it works correctly
| [Tuesday 11 January 2011] [15:11:22] <s0undt3ch>	even on 2.1.0
| [Tuesday 11 January 2011] [15:13:13] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r725ebce 10/ include/zmq.h : 
| [Tuesday 11 January 2011] [15:13:13] <CIA-21>	zeromq2: Version bumped to 2.1.1
| [Tuesday 11 January 2011] [15:13:13] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/ihsCvD
| [Tuesday 11 January 2011] [15:41:10] <mikko>	sustrik: will look into the build patch now
| [Tuesday 11 January 2011] [15:43:21] <sustrik>	mikko: i've seen there are some additional functions being checked for
| [Tuesday 11 January 2011] [15:43:25] <sustrik>	for OpenPGM's sake
| [Tuesday 11 January 2011] [15:43:47] <sustrik>	they probably should not be checked for if pgm is disabled though
| [Tuesday 11 January 2011] [15:44:25] <mikko>	yes
| [Tuesday 11 January 2011] [15:44:38] <mikko>	steve has been working on openpgm autoconf as well
| [Tuesday 11 January 2011] [15:44:43] <mikko>	which is very good progress
| [Tuesday 11 January 2011] [15:44:59] <mikko>	we could invoke the openpgm build from zeromq build without additional deps
| [Tuesday 11 January 2011] [15:45:26] <sustrik>	that would be fantastic
| [Tuesday 11 January 2011] [15:45:44] <sustrik>	getting rid of the foreign build system...
| [Tuesday 11 January 2011] [15:46:04] <mikko>	and not maintain a copy of the openpgm build system
| [Tuesday 11 January 2011] [15:46:11] <sustrik>	exactly
| [Tuesday 11 January 2011] [15:46:34] <mikko>	i think those changes are in openpgm trunk now
| [Tuesday 11 January 2011] [15:46:46] <mikko>	i might take a poke on that side as well and test freebsd/solaris at some point
| [Tuesday 11 January 2011] [15:46:57] <sustrik>	ack
| [Tuesday 11 January 2011] [16:25:07] <mikko>	sustrik: getting build error on linux after the patch
| [Tuesday 11 January 2011] [16:25:12] <mikko>	will investigate a bit
| [Tuesday 11 January 2011] [16:26:36] <mikko>	hmm
| [Tuesday 11 January 2011] [17:29:24] <amacleod>	With the Python bindings for zmq, is it okay to just let the Context expire with the running script?  Or should I explicitly close it?
| [Tuesday 11 January 2011] [17:39:43] <sustrik>	amacleod: closing of the context ensures the all the pending messages are actually pushed to the network before the application extis
| [Tuesday 11 January 2011] [17:39:45] <sustrik>	exits
| [Tuesday 11 January 2011] [17:47:16] <codebeaker>	hi all - anyone know how to build Patrick Chen's fork properly, it says "See the INSTAL file", but that file is absent, and my typical cmake routine "$ mkdir build; $ cd build; $ cmake ../; ......" doesn't seem to want to work
| [Tuesday 11 January 2011] [17:58:48] <codebeaker>	I got as far as setting CMAKE_MODULE_PATH and ZMQ_DIR to the ./src/zmq directory, to which I cloned pchen's repository, now I get the error "include could not find load file: src/zmq/ZMQConfig.cmake" - which makes sense, because it only exists as ./src/zmq/ZMQConfig.cmake.in
| [Tuesday 11 January 2011] [17:59:30] <codebeaker>	how to make sure my top-level project configures the ./src/zmq correctly ? and preprocesses the .in files
| [Tuesday 11 January 2011] [18:12:33] <zchrish>	I made a test case whereby I created a publisher -> forwarder -> subscriber and feed it a 500MB file with 7500847 lines and the time it took to process the file was 102.39 seconds. This equates to about 72,350 messages per second. This was done on localhost. Do these results seem reasonable?
| [Tuesday 11 January 2011] [18:19:34] <zchrish>	Pleased to see that files pass "diff" !
| [Tuesday 11 January 2011] [18:20:06] <codebeaker>	zchrish: that does seem to tally with the numbers quoted in the various docs
| [Tuesday 11 January 2011] [18:20:27] <codebeaker>	 you can check the Introduction - into it a little way are some comparisons of throuput and message sizes
| [Tuesday 11 January 2011] [18:35:25] <snidely>	I'm told that 0MQ has missing libraries which prevent it from running on windows.  Anyone know about that?
| [Tuesday 11 January 2011] [19:44:12] <zchrish>	If I have a PUBSUB system with 3 subscribers that can handle data rates of 10,000 - 20,000 - 30,000 messages per second respectively, how many messages would arrive at the fastest subscriber after 10 seconds? I am asking theoretically of course. This is my next test.
| [Tuesday 11 January 2011] [20:10:19] <zchrish>	The result of the above test suggests that PUBSUB sets the transmisstion rate to the slowest subscriber; is that correct? If so, that could be a problem for my application if I encounter someone with a dialup or with a zombie subscriber. Is there anything that can be done in these cases?
| [Tuesday 11 January 2011] [20:11:34] <zchrish>	<test1> was all localhost and the aggregate PUB->FORWARDER->SUB was 72,350 messages per second.
| [Tuesday 11 January 2011] [20:12:32] <zchrish>	<test2> added an additional endpoint subscriber but across the internet and the aggregate reduced to 27,000 messages per second.
| [Tuesday 11 January 2011] [20:13:07] <zchrish>	<test2> showed both localhost and remote subscribers completed at the same time
| [Tuesday 11 January 2011] [20:14:58] <zchrish>	<test2> also had a couple of occurrances in which the transmission stalled for some seconds which I cannot account since other activities on my system appeared normal.
| [Tuesday 11 January 2011] [20:17:18] <zchrish>	<test2> both local and remote had correct diffs to the original !
| [Tuesday 11 January 2011] [20:22:07] <zchrish>	The result of <test2> seems to indicate that PUBSUB uses a global queue for its messaging system which is probably obvious but I haven't dug into the source code to find out. I wanted to be a user for awhile to see how it operates first.
| [Tuesday 11 January 2011] [20:23:29] <zchrish>	Seems like one item on the to-do list is to implement per-subscription queueing to improve transmission rates for faster channels. I am too naive to know what additional complexity that requires...
| [Tuesday 11 January 2011] [21:19:07] <potatodemon>	Howdy Y'all!  Can zeromq listen as a normal TCP socket? I have a lot of clients using normal sockets that I want to all connect to the zeromq server at once.  Is that something zeromq is good for ?
| [Tuesday 11 January 2011] [22:08:07] <potatodemon>	It looks like zeromq does not do normal sockets, http://lists.zeromq.org/pipermail/zeromq-dev/2010-September/006344.html  is that correct ?
| [Tuesday 11 January 2011] [22:08:33] <jugg>	http://www.zeromq.org/intro:read-the-manual
| [Tuesday 11 January 2011] [22:27:49] <potatodemon>	How many queues can I have with 0mq on a machine with a gig of ram?
| [Tuesday 11 January 2011] [23:06:55] <cremes>	potatodemon: you could probably figure this out on your own by writing a little app that spawns a bunch of sockets
| [Tuesday 11 January 2011] [23:07:29] <cremes>	make sure you bump up the number of file descriptors available to your process or it will run out pretty quickly
| [Tuesday 11 January 2011] [23:07:58] <cremes>	also, i think 0mq defaults to 512 max sockets; you need to change that in the source and recompile
| [Tuesday 11 January 2011] [23:29:44] <benoitc>	hi all
| [Tuesday 11 January 2011] [23:29:57] <benoitc>	how stable is erlzmq actually ?
| [Wednesday 12 January 2011] [02:23:49] <sustrik>	snidely: what libraries?
| [Wednesday 12 January 2011] [02:43:52] <potatodemon>	Hey Y'all anyone in here know a lot about the Python ZMQ lib ?
| [Wednesday 12 January 2011] [02:44:41] <guido_g>	dont't as meta-questions, just ask the question and wait
| [Wednesday 12 January 2011] [02:46:15] <potatodemon>	I just wanted to know if anyone has used the Python ZMQ lib with the Python gevents lib.
| [Wednesday 12 January 2011] [02:48:44] <potatodemon>	I am trying to write a simple normal bsd sockets to 0mq data proxy
| [Wednesday 12 January 2011] [02:49:11] <guido_g>	s0undt3ch had something like this yesterday
| [Wednesday 12 January 2011] [02:49:15] <potatodemon>	Or find a good, fast one
| [Wednesday 12 January 2011] [02:49:38] <guido_g>	you could do it w/ pyzmq.eventloop
| [Wednesday 12 January 2011] [02:51:40] <potatodemon>	Will that give me a async socket server ?
| [Wednesday 12 January 2011] [02:51:58] <potatodemon>	I think it does.  Do you know any examples -- this is new to me.
| [Wednesday 12 January 2011] [02:52:03] <guido_g>	http://zeromq.github.com/pyzmq/index.html#using-pyzmq
| [Wednesday 12 January 2011] [02:59:44] <potatodemon>	Cool, a good place to start. Thanks
| [Wednesday 12 January 2011] [03:22:38] <CIA-21>	zeromq2: 03Neale Ferguson 07master * r7051387 10/ (AUTHORS configure.in src/Makefile.am src/clock.cpp): 
| [Wednesday 12 January 2011] [03:22:38] <CIA-21>	zeromq2: Support dynamic generation of C preprocessor definitions for PGM rather than hardcoding them.
| [Wednesday 12 January 2011] [03:22:38] <CIA-21>	zeromq2: Signed-off-by: Neale Ferguson <neale@sinenomine.net> - http://bit.ly/fPnk1c
| [Wednesday 12 January 2011] [03:41:50] <codebeaker>	2
| [Wednesday 12 January 2011] [03:45:15] <codebeaker>	sorry, morning all - someone was kind enough to help me out last night, but had another quick query - with the code from github.com/PatrickCheng/zeromq2 - there are missing build instructions, specifically for using that in my own project which is built iwith cmake
| [Wednesday 12 January 2011] [03:47:11] <sustrik>	welll, with cmake you are probably on your own, it's not part of the official project and there's little knowledge of it; you can possibly to address patrick cheng directly...
| [Wednesday 12 January 2011] [03:57:22] <codebeaker>	ahh, thanks sustrik -
| [Wednesday 12 January 2011] [03:58:12] <codebeaker>	I *think* to be honest, this is something that would be easier if I knew about CMake - I want my build to automatically compile the ZMQ target, but I cna't work out how - and Patrick didn't write any docs :)
| [Wednesday 12 January 2011] [03:59:19] <benoitc>	erlzmq version using rebar : https://github.com/benoitc/erlzmq/tree/rebar
| [Wednesday 12 January 2011] [03:59:28] <benoitc>	if it helps someone
| [Wednesday 12 January 2011] [03:59:56] <benoitc>	how do you guys handle persistence with zmq ?
| [Wednesday 12 January 2011] [04:03:07] <codebeaker>	benoitc: as far as I understand, that's completely up to tiy
| [Wednesday 12 January 2011] [04:03:30] <codebeaker>	to you* since I believe you can guarantee that if the message is not sent, then it's not sent - and you should persist it
| [Wednesday 12 January 2011] [04:06:46] <benoitc>	mmm right
| [Wednesday 12 January 2011] [04:06:57] <codebeaker>	^^ :) HTH
| [Wednesday 12 January 2011] [04:07:42] <benoitc>	want ot use the possibility of zmq to load balance messages with push/pull instead of simply using redis and jhandle manually suscription
| [Wednesday 12 January 2011] [04:07:45] <benoitc>	+s
| [Wednesday 12 January 2011] [04:07:56] <benoitc>	maybe i will just use both
| [Wednesday 12 January 2011] [04:42:42] <si14>	hi all. Is anybody there?
| [Wednesday 12 January 2011] [04:49:14] <si14>	I'm trying to make a zeromq, but I've got a lot of errors like this
| [Wednesday 12 January 2011] [04:49:22] <si14>	 /usr/include/c++/4.4/bits/stl_vector.h:434: error: __gnu_cxx::__normal_iterator<typename std::_Vector_base<_Tp, _Alloc>::_Tp_alloc_type::const_pointer, std::vector<_Tp, _Alloc> > std::vector<_Tp, _Alloc>::begin() cannot be overloaded
| [Wednesday 12 January 2011] [04:50:08] <si14>	in fact it's something like this (it's not my log, but this one is very similar to mine): https://gist.github.com/700285
| [Wednesday 12 January 2011] [04:54:20] <si14>	ah, sorry, I've found the solution here: http://travlr.github.com/zmqirclog/2010-November.html
| [Wednesday 12 January 2011] [04:56:46] <sustrik>	sil4: if you find the website not addressing this problem, feel free to adjust it
| [Wednesday 12 January 2011] [04:56:47] <sustrik>	it's a wiki
| [Wednesday 12 January 2011] [07:37:09] <s0undt3ch>	guido_g: remeber my problem fom yesterday? here's a sucessfull attempt with zmq.eventloop using 2.1.0, 2.0.10 does not have zmq.devices, so I couldn't test it -> http://paste.pocoo.org/show/319395/
| [Wednesday 12 January 2011] [07:37:40] <s0undt3ch>	guido_g: now I have to narrow down what went wrong on my previous attemps using gobject and eventlet io loops
| [Wednesday 12 January 2011] [08:22:02] <s0undt3ch>	zchrish: you confirmed that the pub/sub io is as slow as the slowest client right?
| [Wednesday 12 January 2011] [08:28:00] <zchrish>	sOundt3ch: No, according to sustrik this is not the case. The cause of throughput drop is by the use of unicast and the throughput drops linearly with the number of subscribers.
| [Wednesday 12 January 2011] [08:28:25] <s0undt3ch>	zchrish: pub sub uses unicast?
| [Wednesday 12 January 2011] [08:30:03] <s0undt3ch>	zchrish: or you were using unicast on you pub/sub sockets?
| [Wednesday 12 January 2011] [08:30:47] <s0undt3ch>	ah, tcp is unicast
| [Wednesday 12 January 2011] [08:31:37] <zchrish>	sOundt3ch: My testing was using tcp. There exists pgm/epgm but I have no experience with it.
| [Wednesday 12 January 2011] [08:32:57] <s0undt3ch>	zchrish: for now I'm using local unix sockets, but I might need to use tcp at a latter stage...
| [Wednesday 12 January 2011] [08:33:11] <s0undt3ch>	zchrish: anyway, Thanks, was just wondering...
| [Wednesday 12 January 2011] [08:35:02] <zchrish>	sOundt3ch: My application is designed to be transported through the internet so I am concerned with latency and throughput issues. Still don't have enough experience with 0mq to know how robust it will be to this but I like what I see so far.
| [Wednesday 12 January 2011] [10:47:17] <yawn>	any advice on jzmq error handling?
| [Wednesday 12 January 2011] [10:47:49] <yawn>	it tends to die from assertions and being jni i have no obvious way to handle those
| [Wednesday 12 January 2011] [11:15:47] <efhache>	hi everybody... I need some help with a cross-compiled(arm) library under linux 2.4
| [Wednesday 12 January 2011] [11:16:34] <efhache>	I've previously compiled the library, codded and work fine under a linux 2.6 but now with a kernell 2.4, I obtain an error as Function not implemented epoll_fd != -1 (epoll.cpp:40) Aborted
| [Wednesday 12 January 2011] [11:16:58] <efhache>	May be is it possible to configure and recompile the library with an other sort of poolling?
| [Wednesday 12 January 2011] [11:19:09] <mikko>	yawn: what sort of assertions?
| [Wednesday 12 January 2011] [11:19:16] <mikko>	and which version of libzmq?
| [Wednesday 12 January 2011] [11:19:54] <efhache>	zmq 2.0.7
| [Wednesday 12 January 2011] [11:19:54] <yawn>	mikko: different assertions really. i have not yet collected all of them, last one was Assertion failed: (s), function get_socket, file Socket.cpp, line 467.
| [Wednesday 12 January 2011] [11:20:05] <mikko>	efhache: can you test with 2.1.0 ?
| [Wednesday 12 January 2011] [11:20:20] <yawn>	mikko: version is 2.0.10 from brew
| [Wednesday 12 January 2011] [11:20:23] <mikko>	i remember there is an issue with using epoll on linux even if it's not available
| [Wednesday 12 January 2011] [11:20:38] <yawn>	mikko: env is mac os x, snow leopard
| [Wednesday 12 January 2011] [11:20:38] <mikko>	yawn: can you test with 2.1.0 ?
| [Wednesday 12 January 2011] [11:20:52] <mikko>	2.1.0 is where active development happens currently
| [Wednesday 12 January 2011] [11:21:01] <mikko>	so it would be helpful to see if those have been sorted out already
| [Wednesday 12 January 2011] [11:21:03] <efhache>	miko : not really  All the code developped was based on an zmq 2.0.7 version
| [Wednesday 12 January 2011] [11:21:33] <yawn>	mikko: sure. but the large variety of errors makes me a bit nervous since there really seems to be no way of "catching" those errors. the jvm simply dies as soon as something crashes in the zmq api.
| [Wednesday 12 January 2011] [11:21:53] <yawn>	mikko: that's why i'm asking about error handling
| [Wednesday 12 January 2011] [11:22:04] <mikko>	yawn: yes, that's what assertion causes. large chunk of those have been sorted out and we are fixing them as we bump into new ones
| [Wednesday 12 January 2011] [11:22:31] <mikko>	efhache: i can check this evening as you should probably use poll rather than epoll with 2.4
| [Wednesday 12 January 2011] [11:23:03] <yawn>	mikko: ok. i have not much experience with jni at all but is there some kind of mechanism that would prevent the jvm from dying?
| [Wednesday 12 January 2011] [11:23:16] <efhache>	ok I'll back to you tomorow
| [Wednesday 12 January 2011] [11:23:23] <yawn>	mikko: or is there a flag that changes the assertion behaviour in zmq?
| [Wednesday 12 January 2011] [11:23:31] <yawn>	mikko: compile-time flag
| [Wednesday 12 January 2011] [11:23:38] <mikko>	efhache: sure
| [Wednesday 12 January 2011] [11:23:59] <mikko>	yawn: yes, but those are not properly handled in that case
| [Wednesday 12 January 2011] [11:24:12] <efhache>	mikko: I'll search again this evening, thw
| [Wednesday 12 January 2011] [11:24:22] <mikko>	yawn: you can specify -DNDEBUG iirc
| [Wednesday 12 January 2011] [11:24:51] <yawn>	ok
| [Wednesday 12 January 2011] [11:25:11] <mikko>	yawn: it would be helpful if you can give 2.1.0 a spin
| [Wednesday 12 January 2011] [11:25:23] <yawn>	mikko: i'll try to update zmq and compiling with DNDBUG (or whatever the flags name is).
| [Wednesday 12 January 2011] [11:25:36] <mikko>	yawn: try without the flag first
| [Wednesday 12 January 2011] [11:25:45] <mikko>	yawn: as i said 2.1.0 fixes a lot of the assertions
| [Wednesday 12 January 2011] [11:25:58] <mikko>	yawn: and if you run into assertions in normal usage we would like to sort those out as well
| [Wednesday 12 January 2011] [11:26:18] <yawn>	mikko: i think that most of the problems occur when inproc sockets with multipart messages terminate before the message is complete
| [Wednesday 12 January 2011] [11:26:41] <mikko>	yawn: do you code C ?
| [Wednesday 12 January 2011] [11:26:59] <mikko>	C test case would be a huge help (java should be ok as wlel but takes a bit longer to process)
| [Wednesday 12 January 2011] [11:27:11] <yawn>	mikko: no, it's a java project
| [Wednesday 12 January 2011] [11:27:36] <mikko>	if you can wait a couple of hours for me to get home i can test this on 2.1.0
| [Wednesday 12 January 2011] [11:27:46] <mikko>	i dont have java bindings running but shouldnt take long to get them
| [Wednesday 12 January 2011] [11:28:01] <mikko>	and as it's JNI java test case should be fairly valid as well
| [Wednesday 12 January 2011] [11:28:09] <yawn>	mikko: test data is a bit problematic since it's driven by real world data. plus the server that interfaces with zmq is evented - so i usually have no idea at all what exactly caused the assertion.
| [Wednesday 12 January 2011] [11:28:20] <mikko>	ok
| [Wednesday 12 January 2011] [11:28:23] <yawn>	real world data = totally volatile stuff
| [Wednesday 12 January 2011] [11:28:31] <mikko>	you can have the process to core dump on assertion
| [Wednesday 12 January 2011] [11:28:37] <mikko>	and run it in debugger
| [Wednesday 12 January 2011] [11:28:45] <mikko>	but i would recommend testing with 2.1.0 as the first step
| [Wednesday 12 January 2011] [11:28:52] <yawn>	i'll do that first
| [Wednesday 12 January 2011] [11:29:16] <yawn>	when it's still dying i'll try to send you a dump
| [Wednesday 12 January 2011] [11:34:03] <yawn>	mikko: damn, 2.1.0 is not yet on brew ... :-)
| [Wednesday 12 January 2011] [11:35:23] <mikko>	brew is something like macports?
| [Wednesday 12 January 2011] [11:36:45] <seb`>	yes
| [Wednesday 12 January 2011] [11:56:16] <zchrish>	In the PUBSUB pattern, is there a way for the publisher to know something about the subscriber set?
| [Wednesday 12 January 2011] [11:57:48] <zchrish>	like subscriber IPs.
| [Wednesday 12 January 2011] [11:59:01] <Vince__>	my wrapper has been throwing this message at me today "Operation cannot be accomplished in current state" anyone seen that before? This happens with zmq_recv()
| [Wednesday 12 January 2011] [11:59:20] <zchrish>	If not, I suppose it could be easy enough to broadcast a call-in message which causes the subscriber set to respond.
| [Wednesday 12 January 2011] [12:00:19] <Vince__>	Seems the actual point which throws this error is here:
| [Wednesday 12 January 2011] [12:00:19] <cremes>	zchrish: no, it's not possible because that kind of information doesn't fit into the pub/sub pattern
| [Wednesday 12 January 2011] [12:00:24] <Vince__>	   //  In blocking scenario, commands are processed over and over again until     //  we are able to fetch a message.     while (rc != 0) {         if (errno != EAGAIN)
| [Wednesday 12 January 2011] [12:00:29] <cremes>	zchrish: use a separate pair of sockets to share that information
| [Wednesday 12 January 2011] [12:00:50] <Vince__>	whats a blocking scenario? How do I over come it?
| [Wednesday 12 January 2011] [12:00:53] <cremes>	Vince__: that is happening with a req/rep pair, yes?
| [Wednesday 12 January 2011] [12:00:59] <zchrish>	OK; thanks.
| [Wednesday 12 January 2011] [12:01:00] <Vince__>	yes
| [Wednesday 12 January 2011] [12:01:34] <cremes>	Vince__: you need to call send/recv/send/recv in that pattern for each one; you must be trying to call send/send or recv/recv somewhere
| [Wednesday 12 January 2011] [12:01:45] <cremes>	which violates the request/reply state machine
| [Wednesday 12 January 2011] [12:02:17] <potatodemon>	Are pyzmq zmq socket sends non-bocking ?
| [Wednesday 12 January 2011] [12:02:18] <Vince__>	recv/recv on a server demo in a loop........ I guess that was wrong then
| [Wednesday 12 January 2011] [12:02:30] <cremes>	Vince__: yep, that's wrong
| [Wednesday 12 January 2011] [12:02:53] <cremes>	potatodemon: i doubt sends are nonblocking by default; there is likely a flag you can pass to make it so
| [Wednesday 12 January 2011] [12:02:57] <cremes>	otherwise it blocks by default
| [Wednesday 12 January 2011] [12:03:04] <Vince__>	Seems like I need to rethink the design then
| [Wednesday 12 January 2011] [12:03:31] <Vince__>	the server won't be sending anything usually though so now I'm confused...
| [Wednesday 12 January 2011] [12:03:33] <cremes>	Vince__: tell us what you are trying to do and we can probably make suggestions
| [Wednesday 12 January 2011] [12:05:15] <Vince__>	I wrote a wrapper for a basic language that not many people use (blitz) it needed safe types so I wrote an addition to the ZMQ API to use safe types as well. Everything seems to be fine except for this issue. I created a server in basic that right now has zmq_recv() running in a while loop. Obviously thats not right. 
| [Wednesday 12 January 2011] [12:05:50] <cremes>	Vince__: explain what the client is supposed to do and what the server is supposed to do
| [Wednesday 12 January 2011] [12:06:26] <Vince__>	server recieves messages from client and sends it to other clients
| [Wednesday 12 January 2011] [12:06:55] <Vince__>	pretty simple
| [Wednesday 12 January 2011] [12:06:55] <cremes>	and what does the client do?
| [Wednesday 12 January 2011] [12:07:08] <cremes>	send requests only?
| [Wednesday 12 January 2011] [12:07:39] <Vince__>	client sends messages to the server and recieves messages from the server
| [Wednesday 12 January 2011] [12:07:44] <yawn>	mikko: yes.
| [Wednesday 12 January 2011] [12:07:48] <cremes>	ok
| [Wednesday 12 January 2011] [12:08:17] <cremes>	so which one of these (client or server) is currently sitting in a while loop doing recv?
| [Wednesday 12 January 2011] [12:08:26] <Vince__>	server
| [Wednesday 12 January 2011] [12:09:01] <cremes>	does that server ever need to respond back to the client, e.g. return a result?
| [Wednesday 12 January 2011] [12:09:16] <Vince__>	I was hoping to just let the server sit there and wait for a connection/message from client
| [Wednesday 12 January 2011] [12:09:48] <cremes>	ok; so does the server ever need to respond back to its clients?
| [Wednesday 12 January 2011] [12:10:07] <cremes>	i'm trying to understand the message flow.... it's unclear
| [Wednesday 12 January 2011] [12:10:33] <Vince__>	the server needs to communicate messages from ClientA to B,C,D,E,F etc... the server doesn't need to talk back to the client that connected. All I need to know is if the client connected successfully.
| [Wednesday 12 January 2011] [12:10:52] <cremes>	ok
| [Wednesday 12 January 2011] [12:11:16] <cremes>	do clients B,C,D,etc need to respond to A or is the message flow uni-directional?
| [Wednesday 12 January 2011] [12:11:42] <cremes>	that is, A only ever sends and never receives, B,C,D,etc only recv and never send
| [Wednesday 12 January 2011] [12:11:48] <Vince__>	Easiest example I can think of is a game server where the client moves and the movement is sent to all the other clients
| [Wednesday 12 January 2011] [12:12:03] <cremes>	ok
| [Wednesday 12 January 2011] [12:12:22] <cremes>	you should look at the pub/sub sockets; req/rep is the *wrong* pattern
| [Wednesday 12 January 2011] [12:12:46] <Vince__>	hmmm
| [Wednesday 12 January 2011] [12:12:47] <cremes>	client A would have a PUB socket
| [Wednesday 12 January 2011] [12:12:57] <cremes>	the server would be a FORWARDER device
| [Wednesday 12 January 2011] [12:13:18] <cremes>	the clients of the server would all have SUB sockets and would subscribe to the topics they want
| [Wednesday 12 January 2011] [12:13:37] <cremes>	does that make sense?
| [Wednesday 12 January 2011] [12:13:53] <cremes>	if not, tell me where it's confusing or wrong
| [Wednesday 12 January 2011] [12:14:21] <Vince__>	I guess I need to make sure I understand what you are saying.
| [Wednesday 12 January 2011] [12:14:40] <cremes>	ok, i'll break it down a bit more
| [Wednesday 12 January 2011] [12:14:58] <cremes>	client A *only* sends data and never cares about a response to what it sent
| [Wednesday 12 January 2011] [12:15:02] <Vince__>	is there a simple example anywhere?
| [Wednesday 12 January 2011] [12:15:10] <cremes>	...
| [Wednesday 12 January 2011] [12:15:18] <cremes>	did you read the guide linked off of the website?
| [Wednesday 12 January 2011] [12:15:26] <cremes>	it covers all of these patterns in detail with code
| [Wednesday 12 January 2011] [12:15:28] <Vince__>	Yes I did actually
| [Wednesday 12 January 2011] [12:15:49] <cremes>	and the PUB section didn't seem appropriate for some reason?
| [Wednesday 12 January 2011] [12:16:10] <Vince__>	It is probably. I just did the tutorials a few weeks ago.
| [Wednesday 12 January 2011] [12:16:19] <Vince__>	Forwarder seems to be throwing me.
| [Wednesday 12 January 2011] [12:17:44] <Vince__>	I am looking at the guide now.
| [Wednesday 12 January 2011] [12:18:12] <cremes>	forwarder is a pretty simple device... let me see if i can help clarify its use
| [Wednesday 12 January 2011] [12:18:39] <cremes>	a forwarder device will have a SUB socket and a PUB socket
| [Wednesday 12 January 2011] [12:18:50] <Vince__>	k
| [Wednesday 12 January 2011] [12:18:54] <cremes>	both sockets will *bind* to some addresses
| [Wednesday 12 January 2011] [12:19:30] <cremes>	a publisher (client A) connects to the forwarder and sends its messages there
| [Wednesday 12 January 2011] [12:20:02] <cremes>	subscribers interested in what client A have to say subscribe to the forwarder without needing to know the address of client A
| [Wednesday 12 January 2011] [12:20:25] <Vince__>	aha! thats what I want indeed
| [Wednesday 12 January 2011] [12:20:28] <cremes>	now along comes client B who *also* wants to publish data to an unknown number of subscribers
| [Wednesday 12 January 2011] [12:20:41] <cremes>	it also connects to the forwarder and starts publishing
| [Wednesday 12 January 2011] [12:21:08] <cremes>	a forwarder is a device for linking up multiple subscribers with multiple publishers
| [Wednesday 12 January 2011] [12:21:34] <cremes>	does this help?
| [Wednesday 12 January 2011] [12:22:09] <cremes>	the forwarder can be thought of as a way to get "multicast"/spread delivery via tcp
| [Wednesday 12 January 2011] [12:23:06] <Vince__>	so what happens with the forwarder in terms of the application. Do I not need to actively tell it to recv messages?
| [Wednesday 12 January 2011] [12:23:24] <cremes>	nope
| [Wednesday 12 January 2011] [12:23:37] <cremes>	take a look at the code in the repository.... it's super simple
| [Wednesday 12 January 2011] [12:24:03] <cremes>	it essentially sits in a while loop; every time it receives something it immediately sends it out to all subscribers
| [Wednesday 12 January 2011] [12:24:14] <Vince__>	ah
| [Wednesday 12 January 2011] [12:24:44] <Vince__>	I'm starting to think something like
| [Wednesday 12 January 2011] [12:24:47] <Vince__>	zmq_init() //  Socket facing clients zmq_socket() //  Socket facing services zmq_bind() zmq_socket() //  Start built-in device zmq_device()
| [Wednesday 12 January 2011] [12:40:54] <Vince__>	cremes how can I determine if a subscriber connects to the published socket from the server application?
| [Wednesday 12 January 2011] [13:15:50] <cremes>	Vince__: that information is not exposed by the 0mq library; you would need a separate pair of sockets to transmit that info
| [Wednesday 12 January 2011] [13:15:54] <cremes>	at the application level
| [Wednesday 12 January 2011] [13:19:19] <Vince__>	thanks for all your help cremes!
| [Wednesday 12 January 2011] [13:19:34] <cremes>	Vince__: you're welcome
| [Wednesday 12 January 2011] [13:19:50] <Vince__>	pub/sub is certainly what I was looking for
| [Wednesday 12 January 2011] [14:24:06] <mikko>	good evening
| [Wednesday 12 January 2011] [15:26:47] <mikko>	sustrik: there?
| [Wednesday 12 January 2011] [15:37:19] <sustrik>	mikko: hi
| [Wednesday 12 January 2011] [15:39:39] <mikko>	sustrik: im adding some static analysis tools to builds
| [Wednesday 12 January 2011] [15:39:55] <mikko>	they might produce some false positives but i guess it's ok 
| [Wednesday 12 January 2011] [15:39:59] <mikko>	http://build.valokuva.org/job/ZeroMQ2-core-master_cppcheck/3/cppcheckResult/?
| [Wednesday 12 January 2011] [15:45:53] <sustrik>	mikko: nice
| [Wednesday 12 January 2011] [15:45:56] <sustrik>	let me check the report
| [Wednesday 12 January 2011] [15:47:45] <sustrik>	mikko: that's the current master?
| [Wednesday 12 January 2011] [15:48:56] <sustrik>	it looks like there's a bug in cppcheck :)
| [Wednesday 12 January 2011] [15:50:17] <sustrik>	struct x {}; results in "Redundant code: Found a statement that begins with numeric constant"
| [Wednesday 12 January 2011] [15:51:26] <mikko>	i could scale down the volume
| [Wednesday 12 January 2011] [15:51:31] <mikko>	to more critical errors
| [Wednesday 12 January 2011] [15:51:38] <sustrik>	no need
| [Wednesday 12 January 2011] [15:51:41] <mikko>	i was thinking about adding a check for trailing whitespace as well
| [Wednesday 12 January 2011] [15:51:50] <sustrik>	why not
| [Wednesday 12 January 2011] [15:52:01] <sustrik>	i should maybe report the problem to cppcheck devs...
| [Wednesday 12 January 2011] [15:53:51] <mikko>	yes, they are on github as well
| [Wednesday 12 January 2011] [15:56:19] <sustrik>	hm, github? brief search seems to point me to sourceforge
| [Wednesday 12 January 2011] [15:59:17] <mikko>	https://github.com/danmar/cppcheck
| [Wednesday 12 January 2011] [15:59:23] <mikko>	at least this is where i cloned it from
| [Wednesday 12 January 2011] [16:00:45] <sustrik>	probably a mirror
| [Wednesday 12 January 2011] [16:00:58] <sustrik>	the project itselft seems to live at sourceforge
| [Wednesday 12 January 2011] [16:10:46] <sustrik>	ok, i've posted a comment on their forum
| [Wednesday 12 January 2011] [16:32:27] <danyamins>	hi
| [Wednesday 12 January 2011] [16:32:51] <danyamins>	does anyone here have ideas about using pyzmq to make an asychronous driver for mongodb?
| [Wednesday 12 January 2011] [16:34:06] <guido_g>	mongodb doesn't speak mq
| [Wednesday 12 January 2011] [16:34:22] <guido_g>	so it would be more a proxy then a driver
| [Wednesday 12 January 2011] [16:34:40] <danyamins>	well
| [Wednesday 12 January 2011] [16:34:48] <danyamins>	when you say it doesnt speak 0zm, what do you mean?
| [Wednesday 12 January 2011] [16:35:01] <danyamins>	(sorry for the naive question)
| [Wednesday 12 January 2011] [16:35:54] <guido_g>	mongodb doesn't understand mq messages
| [Wednesday 12 January 2011] [16:36:23] <danyamins>	you mean, there's something about he packing of the bits ?
| [Wednesday 12 January 2011] [16:36:33] <danyamins>	you have to have it in aparticular form, the things you send over the sockets?
| [Wednesday 12 January 2011] [16:36:36] <guido_g>	*sigh* yes
| [Wednesday 12 January 2011] [16:37:12] <danyamins>	how so?
| [Wednesday 12 January 2011] [16:37:16] <danyamins>	where is that documented?
| [Wednesday 12 January 2011] [16:37:31] <danyamins>	I mean, undestand that the mongo stuff has to be in a particular form
| [Wednesday 12 January 2011] [16:37:41] <danyamins>	I've already written a mongodb asynchronous driver
| [Wednesday 12 January 2011] [16:37:58] <danyamins>	(I was hoping to replace the regular sockets in it with zmq sockets)
| [Wednesday 12 January 2011] [16:38:14] <danyamins>	(and replace the tornado ioloop i use with the zmq ioloop)
| [Wednesday 12 January 2011] [16:38:14] <mikko>	danyamins: zeromq frames the messages before sending them over wire
| [Wednesday 12 January 2011] [16:38:31] <danyamins>	ah
| [Wednesday 12 January 2011] [16:45:07] <danyamins>	so what is the proper solution?
| [Wednesday 12 January 2011] [16:45:11] <danyamins>	do I have any options?
| [Wednesday 12 January 2011] [16:45:13] <danyamins>	that are good?
| [Wednesday 12 January 2011] [16:47:42] <yrashk>	is there any common reason why this https://gist.github.com/92839a6ab653f9366bb2 might happen?
| [Wednesday 12 January 2011] [16:52:51] <benoitc>	https://github.com/benoitc/couch_zmq I started a zeromq endpoint for couchdb
| [Wednesday 12 January 2011] [16:54:56] <danyamins>	could that help with the mongodb project?
| [Wednesday 12 January 2011] [16:55:11] <benoitc>	no
| [Wednesday 12 January 2011] [16:55:18] <danyamins>	ok sorry
| [Wednesday 12 January 2011] [17:04:29] <mikko>	danyamins: you can't easily have zmq to communicate with mongo
| [Wednesday 12 January 2011] [17:04:50] <mikko>	danyamins: you would need to write a proxy that takes zeromq messages and converts them to something that mongo understands
| [Wednesday 12 January 2011] [17:04:58] <mikko>	so you are effectively back to square one
| [Wednesday 12 January 2011] [17:05:59] <mikko>	benoitc: i think i've seen this before
| [Wednesday 12 January 2011] [17:06:03] <mikko>	or something similar
| [Wednesday 12 January 2011] [17:27:02] <mikko>	sustrik: http://build.valokuva.org/job/ZeroMQ2-core-master_static-analysis/7/dryResult/?
| [Wednesday 12 January 2011] [17:27:07] <mikko>	duplicate code checker as well
| [Wednesday 12 January 2011] [17:27:11] <mikko>	now time to sleep
| [Wednesday 12 January 2011] [17:27:14] <mikko>	g'night
| [Wednesday 12 January 2011] [18:03:58] <Seta00>	how do I check if the other endpoint is running?
| [Wednesday 12 January 2011] [18:05:14] <Seta00>	(on a SUB socket)
| [Wednesday 12 January 2011] [18:05:18] <Seta00>	if that matters :P
| [Wednesday 12 January 2011] [18:06:00] <neopallium>	Seta00: you can't with just a SUB socket.
| [Wednesday 12 January 2011] [18:06:39] <Seta00>	neopallium, what are my options?
| [Wednesday 12 January 2011] [18:06:40] <neopallium>	you can create a REQ socket and send a request to the publisher to see if they are running, or just wait for a message on the SUB socket.
| [Wednesday 12 January 2011] [18:07:15] <Seta00>	the problem with just waiting is that I can't notify users that the server is not running
| [Wednesday 12 January 2011] [18:07:18] <neopallium>	the publisher can bind a REP socket, which the subscribers connect with a REQ socket to to ask if they are running.
| [Wednesday 12 January 2011] [18:07:58] <Seta00>	so the REQ socket won't wait for the endpoint to come online like a SUB socket?
| [Wednesday 12 January 2011] [18:08:39] <neopallium>	no, you would have to add some timeout when you send the request over the REQ socket.
| [Wednesday 12 January 2011] [18:08:58] <Seta00>	hmm, I wonder how I didn't notice that
| [Wednesday 12 January 2011] [18:09:01] <Seta00>	thank you neopallium 
| [Wednesday 12 January 2011] [18:09:06] <neopallium>	np
| [Wednesday 12 January 2011] [18:10:32] <neopallium>	I just wished 0mq provided a way to register to receive events from the sockets (i.e. like connect/disconnect notices).
| [Wednesday 12 January 2011] [18:11:01] <Seta00>	that would be nice :)
| [Wednesday 12 January 2011] [19:45:57] <zchrish>	Can one create a zmq::pollitem_t object dynamically? I am considering adding and subtracting PUSH patterns as subscribers come onboard.
| [Wednesday 12 January 2011] [19:49:09] <zchrish>	For example, in my publisher, I have a PULL pattern that syncs my subscribers. I want to add dedicated PUSH patterns that can connect to each of those subscribers. I would get the connection information from a message from the subscriber to the publisher.
| [Wednesday 12 January 2011] [19:51:04] <zchrish>	According to sustrik, using a vector for the pattern is supported (I think this is the result based on an earlier xChat post.
| [Wednesday 12 January 2011] [21:41:51] <jugg>	sustrik, if the offer for access to the zeromq/erlzmq repo is still on the table, please ping me.
| [Thursday 13 January 2011] [02:39:25] <benoitc>	mikko: i'm not awer of one, except something i launched in the past but aborted cause erlzmq wasn't working so well
| [Thursday 13 January 2011] [02:39:42] <benoitc>	sustrik: did you see my pull request for rebar ?
| [Thursday 13 January 2011] [02:41:11] <benoitc>	how would you validate suscriptions of a client ?
| [Thursday 13 January 2011] [02:58:56] <yrashk>	another bizzare random zeromq segfault: https://gist.github.com/b5495c3f5dd29e193e9b I must be definitely doing something wrong
| [Thursday 13 January 2011] [04:02:41] <sustrik>	benoitc: i am not maintaining the erlzmq binding
| [Thursday 13 January 2011] [04:02:54] <sustrik>	try contacting serge aleynikov
| [Thursday 13 January 2011] [04:03:15] <sustrik>	serge@aleynikov.org
| [Thursday 13 January 2011] [04:03:50] <sustrik>	yrashk: what's the error?
| [Thursday 13 January 2011] [04:08:24] <yrashk>	sustrik: the one in the gist i mentioned
| [Thursday 13 January 2011] [04:08:43] <sustrik>	there's no error there
| [Thursday 13 January 2011] [04:10:01] <jugg>	benoitc, you may want to look at http://github.com/csrl/erlzmq for what I believe is a usable erlang binding
| [Thursday 13 January 2011] [04:10:35] <sustrik>	jugg: any answer from serge?
| [Thursday 13 January 2011] [04:11:07] <yrashk>	sustrik: its a segfault point inspected in gdb
| [Thursday 13 January 2011] [04:11:41] <sustrik>	ah, segfault
| [Thursday 13 January 2011] [04:11:43] <jugg>	sustrik, ?  I think I may have missed something.
| [Thursday 13 January 2011] [04:12:00] <jugg>	I take it I should contact him. :)
| [Thursday 13 January 2011] [04:12:08] <sustrik>	doyrashk: can you provide a minimal test case?
| [Thursday 13 January 2011] [04:12:22] <sustrik>	jugg: well, try to ask him to pull the changes
| [Thursday 13 January 2011] [04:12:52] <jugg>	does he handle pull requests on zeromq/erlzmq?
| [Thursday 13 January 2011] [04:13:14] <yrashk>	sustrik: im trying but this segfault is only randomly reproducible :(
| [Thursday 13 January 2011] [04:13:17] <sustrik>	he did so a week ago
| [Thursday 13 January 2011] [04:13:24] <jugg>	k
| [Thursday 13 January 2011] [04:13:26] <sustrik>	so he's probably still maintaining the project
| [Thursday 13 January 2011] [04:13:35] <sustrik>	anyway, if he doesn't answer, ping me
| [Thursday 13 January 2011] [04:13:45] <sustrik>	i'll grant you commit access to the project
| [Thursday 13 January 2011] [04:13:50] <jugg>	ok
| [Thursday 13 January 2011] [04:14:16] <sustrik>	yrashk: maybe be using a loop in your test program?
| [Thursday 13 January 2011] [04:15:04] <yrashk>	sustrik: may be, i just have to narrow it down somehow
| [Thursday 13 January 2011] [04:15:15] <sustrik>	goodo
| [Thursday 13 January 2011] [04:15:20] <yrashk>	i have a pushing thread and a pulling thread
| [Thursday 13 January 2011] [04:15:30] <yrashk>	not sure how this can affect it
| [Thursday 13 January 2011] [04:15:53] <yrashk>	given i use ffn to deallocate stuff
| [Thursday 13 January 2011] [04:16:38] <benoitc>	sustrik: k
| [Thursday 13 January 2011] [04:19:43] <benoitc>	jugg: does it change the use of erlzmq ?
| [Thursday 13 January 2011] [04:20:32] <benoitc>	ah yes so you create one context / socket
| [Thursday 13 January 2011] [04:20:48] <jugg>	sustrik, to close the loop on an old discussion from a few weeks ago.  The problems I was seeing with bogus blank messages seems to have gone away with the updated erlang bindings, and I believe I have an explanation as to what was causing. As such I don't believe the issue exists but is masked, but that the issue was in the bindings.
| [Thursday 13 January 2011] [04:21:05] <jugg>	benoitc, no, there are multiple sockets per context.
| [Thursday 13 January 2011] [04:21:23] <jugg>	There is one erlang process per socket.
| [Thursday 13 January 2011] [04:21:42] <sustrik>	jugg: great
| [Thursday 13 January 2011] [04:21:56] <benoitc>	right parsing pursub server ex
| [Thursday 13 January 2011] [04:22:53] <jugg>	the main difference is that zmq:start_link no longer exists (which used to initialize a zmq context).  Now you must call zmq:init/1 instead to establish a context.  And you must pass the context to zmq:socket/2.  Also, the returned socket from zmq:socket/2 must be passed around.
| [Thursday 13 January 2011] [04:23:28] <benoitc>	mmm ok
| [Thursday 13 January 2011] [04:23:54] <benoitc>	would be good if the change happen soon, so i could test it on couch_zmq
| [Thursday 13 January 2011] [04:23:58] <jugg>	basically you can treat the erlang bindings very much like the C bindings.  See: http://csrl.github.com/erlzmq/  for documented differences.
| [Thursday 13 January 2011] [04:24:16] <jugg>	(under architecture)
| [Thursday 13 January 2011] [04:25:40] <benoitc>	jugg: i will provide a branch using rebar with that in coming hour
| [Thursday 13 January 2011] [04:25:47] <jugg>	however, if you want low level control, you can utilize the zmq_drv:xxx functions directly, however there are certain constraints to respect.  I don't have those documented yet.
| [Thursday 13 January 2011] [04:26:03] <benoitc>	cool
| [Thursday 13 January 2011] [04:26:22] <jugg>	benoitc, great, I saw your rebar update and was waiting to see if my fork would get merged before integrating.
| [Thursday 13 January 2011] [04:26:52] <benoitc>	i'm trying to only se rebar these days (hopefully it will be integrated in erlang)
| [Thursday 13 January 2011] [04:26:55] <benoitc>	so I need it
| [Thursday 13 January 2011] [04:31:32] <sustrik>	jugg: btw, i like the idea of erlzmq looking more alike to C API and other bindings
| [Thursday 13 January 2011] [04:32:41] <jugg>	things started coming together better once I took that approach.
| [Thursday 13 January 2011] [04:33:22] <sustrik>	nice
| [Thursday 13 January 2011] [04:36:30] <jugg>	ok, pull request sent.
| [Thursday 13 January 2011] [04:36:36] <yrashk>	jugg: how stable erlzmq now? I have another project in the pipeline and I am again trying to choose between zeromq and rabbitmq (I used both, although more of rabbitmq)
| [Thursday 13 January 2011] [04:36:40] <yrashk>	is now*
| [Thursday 13 January 2011] [04:37:32] <jugg>	fairly.  I haven't tested all of the get/setsockopt however, so I might have a bug in there - hopefully not.  And it'll be going into production use within two weeks here.
| [Thursday 13 January 2011] [04:37:43] <yrashk>	oh nice
| [Thursday 13 January 2011] [04:37:56] <mikko>	sustrik: im wondering that do we currently provide a way to remove subscription?
| [Thursday 13 January 2011] [04:38:24] <mikko>	sustrik: im thinking about internet like usage scenario where subscribers with identities might come and go
| [Thursday 13 January 2011] [04:50:39] <sustrik>	mikko: ZMQ_UNSUBSCRIBE
| [Thursday 13 January 2011] [05:08:16] <benoitc>	jugg: i've an error while building your version :
| [Thursday 13 January 2011] [05:08:17] <benoitc>	c_src/zmq_drv.cpp: In function void zmqdrv_ready_input(_erl_drv_data*, _erl_drv_event*):
| [Thursday 13 January 2011] [05:08:20] <benoitc>	c_src/zmq_drv.cpp:939: error: cast from _erl_drv_event* to int loses precision
| [Thursday 13 January 2011] [05:08:42] <benoitc>	mmm maybe I miss a flag
| [Thursday 13 January 2011] [05:11:52] <mikko>	sustrik: i meant from server side
| [Thursday 13 January 2011] [05:12:07] <mikko>	i've never used PUB/SUB with identities
| [Thursday 13 January 2011] [05:12:24] <mikko>	but i understand if subscriber with identity goes away the messages are buffered
| [Thursday 13 January 2011] [05:12:30] <mikko>	are they buffered up to HWM?
| [Thursday 13 January 2011] [05:12:40] <sustrik>	yes
| [Thursday 13 January 2011] [05:12:57] <sustrik>	basically, identity defines a "permanent connection"
| [Thursday 13 January 2011] [05:13:26] <sustrik>	one that remains even though reconnect happens, one application is shut down or alike
| [Thursday 13 January 2011] [05:13:46] <sustrik>	then there's orthogonal issue of how many massages can be buffered
| [Thursday 13 January 2011] [05:13:52] <sustrik>	that's HWM and SWAP
| [Thursday 13 January 2011] [05:13:55] <mikko>	but it's good that HWM limits it
| [Thursday 13 January 2011] [05:14:06] <sustrik>	yes, it's orthogonal
| [Thursday 13 January 2011] [05:14:17] <mikko>	i was thinking about untrusted subscribers creating a resource exchaustion 
| [Thursday 13 January 2011] [05:14:43] <sustrik>	it can still happen
| [Thursday 13 January 2011] [05:14:45] <seb`>	do sockets get a randomly assigned identity if it's not set?
| [Thursday 13 January 2011] [05:14:49] <sustrik>	it there's a lot of them
| [Thursday 13 January 2011] [05:14:56] <mikko>	yes, i guess so
| [Thursday 13 January 2011] [05:14:57] <sustrik>	is it wise to ude identities?
| [Thursday 13 January 2011] [05:15:00] <sustrik>	use
| [Thursday 13 January 2011] [05:15:12] <sustrik>	seb': kind of
| [Thursday 13 January 2011] [05:15:20] <mikko>	i guess a sockopt disabling permanent connections even if client requests might be good
| [Thursday 13 January 2011] [05:15:35] <mikko>	if clients are untrusted it might prove to be useful
| [Thursday 13 January 2011] [05:15:43] <sustrik>	seb': but the connection is not persistent in the sense the resources are deallocated once the connection breaks
| [Thursday 13 January 2011] [05:16:05] <seb`>	I see
| [Thursday 13 January 2011] [05:44:42] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r18f29de 10/ (52 files): 
| [Thursday 13 January 2011] [05:44:42] <CIA-21>	zeromq2: Make cppcheck not complain about "'operator=' should return something"
| [Thursday 13 January 2011] [05:44:42] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/hUiXv8
| [Thursday 13 January 2011] [05:45:18] <mikko>	heh, i wonder other static analysis tools are there
| [Thursday 13 January 2011] [05:45:34] <mikko>	currently it runs cppcheck, duplicate code check and soon sloccount
| [Thursday 13 January 2011] [05:50:45] <sustrik>	let me first fix these :)
| [Thursday 13 January 2011] [05:51:03] <sustrik>	mikko: btw, is it possible to switch off certain types of errors?
| [Thursday 13 January 2011] [05:51:17] <mikko>	sustrik: i can create a suppressions file
| [Thursday 13 January 2011] [05:51:21] <mikko>	which ones specifically?
| [Thursday 13 January 2011] [05:51:37] <sustrik>	Redundant condition. It is safe to deallocate a NULL pointer
| [Thursday 13 January 2011] [05:51:59] <sustrik>	The code is redundant but it improves readability
| [Thursday 13 January 2011] [05:52:07] <sustrik>	so I would prefer to leave it in
| [Thursday 13 January 2011] [05:52:25] <sustrik>	cppCheckId=	redundantIfDelete0
| [Thursday 13 January 2011] [05:53:24] <mikko>	ok, i'll try adding suppressions file
| [Thursday 13 January 2011] [05:53:25] <mikko>	just a sec
| [Thursday 13 January 2011] [06:19:03] <jugg>	benoitc, 32bit or 64bit?
| [Thursday 13 January 2011] [06:22:07] <jugg>	benoitc, looks like for some reason I changed the cast from a long to an int.  I'll take a look and see if I can figure out why.
| [Thursday 13 January 2011] [06:29:59] <mikko>	sustrik: http://build.valokuva.org/job/ZeroMQ2-core-master_static-analysis/12/cppcheckResult/?
| [Thursday 13 January 2011] [06:30:04] <mikko>	suppressed now
| [Thursday 13 January 2011] [06:31:10] <mikko>	still a couple of redundant ones but fixing later
| [Thursday 13 January 2011] [06:34:33] <sustrik>	mikko: strange that it is analysing the system header files
| [Thursday 13 January 2011] [06:34:43] <sustrik>	like /usr/include/stdlib.h
| [Thursday 13 January 2011] [06:36:22] <mikko>	yeah, i removed those 
| [Thursday 13 January 2011] [06:36:24] <mikko>	http://build.valokuva.org/job/ZeroMQ2-core-master_static-analysis/14/cppcheckResult/?
| [Thursday 13 January 2011] [06:46:18] <sustrik>	great
| [Thursday 13 January 2011] [06:46:28] <sustrik>	i have a look at remaining problems later on
| [Thursday 13 January 2011] [06:46:42] <mikko>	let me know if more suppressions are needed
| [Thursday 13 January 2011] [06:47:26] <jugg>	benoitc, It is because zeromq returns an 'int' for that value, so the conversion is harmless, but the warning should be suppressed.
| [Thursday 13 January 2011] [06:53:06] <benoitc>	jugg: sound like there are other error
| [Thursday 13 January 2011] [06:53:11] <benoitc>	yes 64 bits
| [Thursday 13 January 2011] [06:53:37] <benoitc>	jugg: there is also a problem l 446 and 820
| [Thursday 13 January 2011] [06:53:45] <benoitc>	int e = (uintptr_t)event;
| [Thursday 13 January 2011] [06:53:52] <benoitc>	solve the first one
| [Thursday 13 January 2011] [06:54:03] <benoitc>	on 446 i've to assert((sizeof(uint8_t)+ n+1) == size);
| [Thursday 13 January 2011] [06:54:12] <benoitc>	but my C is really rosten
| [Thursday 13 January 2011] [06:54:39] <benoitc>	rusty
| [Thursday 13 January 2011] [07:00:22] <jugg>	hmm, that 446 error is strange.  I don't yet understand why your change would be correct.
| [Thursday 13 January 2011] [07:01:16] <jugg>	size should be equal to n + 1
| [Thursday 13 January 2011] [07:01:25] <jugg>	sizeof(uint8_t) == 1
| [Thursday 13 January 2011] [07:01:37] <jugg>	so, sizeof(uint8_t) + n should be correct...
| [Thursday 13 January 2011] [07:04:04] <zchrish>	I have a use case and am wondering whether zeromq is the right implementation method :
| [Thursday 13 January 2011] [07:04:21] <jugg>	benoitc, what is the error on 820?
| [Thursday 13 January 2011] [07:04:58] <zchrish>	 Actually will send to the discussion group; sorry.
| [Thursday 13 January 2011] [07:07:01] <jugg>	benoitc, I believe I've understood the problem at 446.  Verifying...
| [Thursday 13 January 2011] [07:13:43] <jugg>	yes,  'n' is not byte size, it is the number of options.  So what is being asserted itself is bogus.  I'm making a fix and will push it shortly.
| [Thursday 13 January 2011] [07:38:22] <jugg>	benoitc, I have the fixes in place for the first two issues.  Is there anything to fix for line 820?
| [Thursday 13 January 2011] [07:57:53] <benoitc>	jugg: testing
| [Thursday 13 January 2011] [08:00:38] <benoitc>	jugg: new error c_src/zmq_drv.cpp: In function void wrap_zmq_setsockopt(zmq_drv_t*, const uint8_t*, size_t):
| [Thursday 13 January 2011] [08:00:41] <benoitc>	c_src/zmq_drv.cpp:492: error: optvalen was not declared in this scope
| [Thursday 13 January 2011] [08:00:47] <jugg>	eh
| [Thursday 13 January 2011] [08:01:24] <jugg>	wow, how is my compiler not giving me an error there?
| [Thursday 13 January 2011] [08:02:07] <benoitc>	-Wl isn't an option on osx
| [Thursday 13 January 2011] [08:02:35] <benoitc>	ah yes a typo
| [Thursday 13 January 2011] [08:03:37] <benoitc>	and now have a new warning c_src/zmq_drv.cpp:492: warning: comparison between signed and unsigned integer expressions
| [Thursday 13 January 2011] [08:04:07] <jugg>	ah NDEBUG is defined in my build environment... no wonder I'm not finding these problems.
| [Thursday 13 January 2011] [08:04:11] 	 * jugg slaps head
| [Thursday 13 January 2011] [08:04:21] <benoitc>	heh
| [Thursday 13 January 2011] [08:05:09] <jugg>	sorry... too many things going at once; missing these types of details.
| [Thursday 13 January 2011] [08:05:15] <benoitc>	np
| [Thursday 13 January 2011] [08:05:38] <benoitc>	that' where opensource helps :)
| [Thursday 13 January 2011] [08:05:52] <jugg>	quite so :)
| [Thursday 13 January 2011] [08:08:45] <jugg>	there we go... now I'm getting the errors.
| [Thursday 13 January 2011] [08:09:18] <benoitc>	i'm not sure it is, but cool :-)
| [Thursday 13 January 2011] [08:20:09] <jugg>	fix pushed
| [Thursday 13 January 2011] [08:22:45] <benoitc>	one last sorry :(
| [Thursday 13 January 2011] [08:22:46] <benoitc>	10> Assertion failed: (sizeof(uint32_t) == size), function wrap_zmq_poll, file c_src/zmq_drv.cpp, line 821. Abort trap
| [Thursday 13 January 2011] [08:22:51] <jugg>	I guess I should re-run my tests now that the asserts are actually 
| [Thursday 13 January 2011] [08:22:55] <benoitc>	the one I had with my fixes
| [Thursday 13 January 2011] [08:23:38] <benoitc>	jugg: btw rebared version https://github.com/benoitc/erlzmq/tree/rebar-socketprocess
| [Thursday 13 January 2011] [08:24:38] <benoitc>	the pubtest is ok here
| [Thursday 13 January 2011] [08:24:53] <benoitc>	only repserver hangs
| [Thursday 13 January 2011] [08:29:51] <jugg>	yes, I have another bug there. I'll have to rerun my tests now that asserts are actually being checked.
| [Thursday 13 January 2011] [08:30:26] <benoitc>	k i will concentrate on app level for now
| [Thursday 13 January 2011] [08:34:54] <efhache>	mikko: hi do you have seen how i can configure zmq 2.0.7  to work under linux 2.4 without epooll ?
| [Thursday 13 January 2011] [08:35:13] <mikko>	efhache: take a look at src/poller.h
| [Thursday 13 January 2011] [08:35:28] <mikko>	i reckon you could change ZMQ_HAVE_LINUX condition to use poll instead of epoll
| [Thursday 13 January 2011] [08:35:36] <mikko>	not sure if that's the only thing you need to do
| [Thursday 13 January 2011] [08:35:59] <mikko>	maybe we could add a configure flag in the future to choose poller implementation
| [Thursday 13 January 2011] [08:37:32] <efhache>	so the define become : elif defined ZMQ_HAVE_LINUX     typedef epoll_t poller_t; // fhn modification 20110113 epoll_t poller_t;
| [Thursday 13 January 2011] [08:37:38] <efhache>	are you ok with me?
| [Thursday 13 January 2011] [08:37:55] <mikko>	no
| [Thursday 13 January 2011] [08:38:04] <efhache>	sorry typedef : poll_t poller_t;
| [Thursday 13 January 2011] [08:38:08] <mikko>	yes
| [Thursday 13 January 2011] [08:38:10] <mikko>	try that 
| [Thursday 13 January 2011] [08:38:18] <efhache>	yes sorry wrong copy past   ;-)
| [Thursday 13 January 2011] [08:39:52] <sustrik>	efhache: you can use ZMQ_FORCE_POLL or somesuch
| [Thursday 13 January 2011] [08:40:29] <mikko>	did we have that in 2.0.7 ?
| [Thursday 13 January 2011] [08:40:58] <mikko>	oh
| [Thursday 13 January 2011] [08:41:00] <mikko>	it is there
| [Thursday 13 January 2011] [08:41:07] <mikko>	so no modification should be needed
| [Thursday 13 January 2011] [08:41:20] <mikko>	export CPPFLAGS="-DZMQ_FORCE_POLL" ./configure
| [Thursday 13 January 2011] [08:45:47] <efhache>	ah sorry I've modified source... it recompile it, I'll test and come back... if ok I'll retry with the flag
| [Thursday 13 January 2011] [08:45:56] <efhache>	thanks a lot and SYL ;-)
| [Thursday 13 January 2011] [08:46:29] <mikko>	you should really look into making the software work with 2.1.0 as well
| [Thursday 13 January 2011] [08:46:42] <mikko>	there aren't that many modifications needed usually
| [Thursday 13 January 2011] [08:52:08] <efhache>	mmhh  I''ve begun with 2.0.6  and then update to 2.0.7 thath normally "no many modification"  but in result I've rework all the code... So now I fix it  and later I'll update the library if need it
| [Thursday 13 January 2011] [09:02:03] <efhache>	mikko: it does not work more, i've test with poller.h modified and obtain another problem : "Assertion failed: !(it->revents & POLLNVAL) (poll.cpp:171)"
| [Thursday 13 January 2011] [09:02:30] <efhache>	with the export of the FORCE POLL FLAG  I reobtain the assetion with epoll.cpp as yesterday
| [Thursday 13 January 2011] [09:02:59] <mikko>	im not sure if anyone has really tested extensively with 2.4 kernel
| [Thursday 13 January 2011] [09:11:22] <jugg>	is there still plans for a zeromq conference in Budapest coming up?
| [Thursday 13 January 2011] [09:12:23] <sustrik>	pieter was organising it
| [Thursday 13 January 2011] [09:12:30] <sustrik>	but he got ill
| [Thursday 13 January 2011] [09:12:42] <sustrik>	he's out of hospital for only a few days now
| [Thursday 13 January 2011] [09:13:02] <sustrik>	so, hard to say
| [Thursday 13 January 2011] [09:13:45] <sustrik>	depends on when he gets ok
| [Thursday 13 January 2011] [09:14:30] <jugg>	He's recovering well?
| [Thursday 13 January 2011] [09:16:14] <benoitc>	jugg: i'm not sure why assertion is here line 821. on 64 bits it's always false.
| [Thursday 13 January 2011] [09:16:30] <benoitc>	removing it, pubrep works of course ..
| [Thursday 13 January 2011] [09:16:43] <sustrik>	i believe so
| [Thursday 13 January 2011] [09:17:30] <jugg>	I know why.  I'll have a fix soon. You can modify src/zmq_drv.erl line: 190 to be: <<(?ZMQ_POLL):8, (events_to_int(Events)):32>>
| [Thursday 13 January 2011] [09:20:33] <jugg>	actually, I might change poll/send/recv flags to all be a byte size instead.
| [Thursday 13 January 2011] [09:21:24] <jugg>	yes, that makes more sense
| [Thursday 13 January 2011] [09:21:32] <benoitc>	k
| [Thursday 13 January 2011] [09:21:41] 	 * benoitc just ordered k&r book
| [Thursday 13 January 2011] [09:21:47] <benoitc>	need to refresh my C
| [Thursday 13 January 2011] [09:22:27] <jugg>	so instead, change the assert in poll to: assert(sizeof(uint8_t) == size);
| [Thursday 13 January 2011] [09:23:20] <benoitc>	works 
| [Thursday 13 January 2011] [09:25:09] <efhache>	mikko: do you know if for zmq there is a use of "EPOLLET" (triggered mode) ??
| [Thursday 13 January 2011] [09:27:12] <yawn>	is there a way to determine the underlying zmq version in jzmq?
| [Thursday 13 January 2011] [09:42:28] <benoitc>	jugg: just did https://github.com/benoitc/erlzmq/commit/463d727dd90d7da94047e5cdb5b231672829d116 but anyway will wait your final fix
| [Thursday 13 January 2011] [09:42:54] <benoitc>	rebar is working well on erlzmq btw
| [Thursday 13 January 2011] [09:43:54] <jugg>	ok, almost ready.
| [Thursday 13 January 2011] [09:45:41] <benoitc>	cool :)
| [Thursday 13 January 2011] [09:48:02] <mikko>	efhache: i dont know what EPOLLET means
| [Thursday 13 January 2011] [09:48:39] <mikko>	yawn: not sure if it's exposed
| [Thursday 13 January 2011] [09:49:25] <mikko>	yawn: ZMQ::version_full() ?
| [Thursday 13 January 2011] [09:49:57] <yawn>	mikko: not in my version - maybe an old build ...
| [Thursday 13 January 2011] [09:50:15] <mikko>	https://github.com/zeromq/jzmq/blob/master/src/ZMQ.cpp#L30
| [Thursday 13 January 2011] [09:50:22] <mikko>	at least that's what the source says
| [Thursday 13 January 2011] [09:50:42] <sustrik>	mikko: it's edge-triggered
| [Thursday 13 January 2011] [09:51:10] <sustrik>	efhache: the underlying file descriptor (ZMQ_FD) is edge-triggered
| [Thursday 13 January 2011] [09:51:18] <mikko>	sustrik: EPOLLET stands for edge-triggered?
| [Thursday 13 January 2011] [09:51:25] <sustrik>	i think so
| [Thursday 13 January 2011] [09:51:30] <sustrik>	let me check
| [Thursday 13 January 2011] [09:52:17] <sustrik>	yes
| [Thursday 13 January 2011] [09:54:06] <mikko>	ok
| [Thursday 13 January 2011] [09:59:30] <efhache>	mikko:  I've resolved the problem, I've used the export CPPFLAGS="-DZMQ_FORCE_SELECT"
| [Thursday 13 January 2011] [10:03:44] <mikko>	efhache: cool
| [Thursday 13 January 2011] [10:04:14] <mikko>	sustrik: i guess that makes sense if it standa for EPOLL Egde-Triggered
| [Thursday 13 January 2011] [10:04:29] <yawn>	mikko: protected statics
| [Thursday 13 January 2011] [10:04:52] <yawn>	mikko: one needs to do the usual dance & sing to make java return the values
| [Thursday 13 January 2011] [10:25:12] <Hybelkanin>	Anyone with experience on zmq on osx 10.6 with the C# bindings?
| [Thursday 13 January 2011] [10:27:14] <mikko>	Hybelkanin: unusual combination
| [Thursday 13 January 2011] [10:27:21] <mikko>	can't say i've heard that combo before
| [Thursday 13 January 2011] [10:27:28] <Hybelkanin>	:P
| [Thursday 13 January 2011] [10:27:47] <mikko>	i have built and tested the c# bindings on linux
| [Thursday 13 January 2011] [10:28:54] <Hybelkanin>	I think my problem may be monodevelop
| [Thursday 13 January 2011] [10:29:10] <Hybelkanin>	So this might be the wrong channel
| [Thursday 13 January 2011] [10:43:10] <amacleod>	My Python 0MQ REP server doesn't stop when I interrupt it with ^C.  How do I make it respect ^C?
| [Thursday 13 January 2011] [10:49:35] <s0undt3ch>	ppl, pub/sub forward devices should connect_in and bind_out?
| [Thursday 13 January 2011] [10:49:43] <s0undt3ch>	or should they bind_in and bind_out?
| [Thursday 13 January 2011] [11:01:59] <mikko>	amacleod: i would i think it might be blocking on zmq_term
| [Thursday 13 January 2011] [11:02:34] <mikko>	amacleod: i dont really know how things are implemented in python so its just guessing
| [Thursday 13 January 2011] [11:02:35] <amacleod>	mikko, I wrote it like the examples with a "while True" loop.
| [Thursday 13 January 2011] [11:05:11] <amacleod>	I can stop it from within just fine--if I set up a conditional where my message handler calls self.context.term () when it receives "EXIT" or something, it's okay.
| [Thursday 13 January 2011] [11:05:18] <mikko>	amacleod: can you see where it's stuck?
| [Thursday 13 January 2011] [11:05:42] <amacleod>	As far as I know, it's not stuck.  It's just completely ignoring ^C or SIGTERM.
| [Thursday 13 January 2011] [11:06:11] <cremes>	amacleod: if it's blocked in zmq_term(), it won't let python's signal handler run to catch the signal
| [Thursday 13 January 2011] [11:06:22] <cremes>	this has been reported a few times; i think sustrik is planning a fix
| [Thursday 13 January 2011] [11:06:34] <cremes>	same thing happens with the ruby runtime
| [Thursday 13 January 2011] [11:07:07] <amacleod>	Oh, interesting.
| [Thursday 13 January 2011] [11:07:19] <amacleod>	If I hit ^C and then try sending something to it, it does get the KeyboardInterrupt exception.
| [Thursday 13 January 2011] [11:07:43] <amacleod>	So it's actually probably blocking in recv()
| [Thursday 13 January 2011] [11:07:52] <cremes>	huh, that might be a new problem
| [Thursday 13 January 2011] [11:07:57] <cremes>	if you can reduce it, file an issue
| [Thursday 13 January 2011] [11:08:33] <mikko>	recv should return on ctrl+c
| [Thursday 13 January 2011] [11:20:58] <s0undt3ch>	sustrik, guido_g: I found out the issue about my forwarder problem
| [Thursday 13 January 2011] [11:21:20] <s0undt3ch>	sustrik, guido_g: publishers were binding instead of connecting
| [Thursday 13 January 2011] [11:21:41] <s0undt3ch>	sustrik, guido_g: the forwarder device was the one binding so, no one else should bind
| [Thursday 13 January 2011] [11:29:08] <jugg>	benoitc, updates pushed.  All get/setsockopt options are tested now.  
| [Thursday 13 January 2011] [11:38:27] <benoitc>	jugg: works
| [Thursday 13 January 2011] [11:38:33] <benoitc>	thanks :)
| [Thursday 13 January 2011] [11:39:10] <benoitc>	smth weird though when you launch pubsub test
| [Thursday 13 January 2011] [11:39:24] <benoitc>	10 is sent but none of subclient get it
| [Thursday 13 January 2011] [11:40:47] <benoitc>	jugg: adding a timer after the bind fix that but ...
| [Thursday 13 January 2011] [11:42:09] <benoitc>	anyway https://github.com/benoitc/erlzmq/tree/rebar-socketprocess
| [Thursday 13 January 2011] [11:44:29] <jugg>	yes, that is normal - not a binding issue.
| [Thursday 13 January 2011] [11:44:50] <benoitc>	ok
| [Thursday 13 January 2011] [11:45:13] <benoitc>	didn't check but did you add PUSH and PULL
| [Thursday 13 January 2011] [11:45:25] <jugg>	yes
| [Thursday 13 January 2011] [11:45:26] <benoitc>	or DOWNSTREAM, UPSTREAM are current names ?
| [Thursday 13 January 2011] [11:45:29] <benoitc>	cool
| [Thursday 13 January 2011] [11:45:49] <jugg>	using your rebar, I always get errors: fatal: No tags can describe '6944b664b20b525e210f1eaebea00bbcd21ec217'
| [Thursday 13 January 2011] [11:45:55] <benoitc>	ok time to code this app then. more in the night
| [Thursday 13 January 2011] [11:45:58] <jugg>	when doing $ make
| [Thursday 13 January 2011] [11:46:00] <benoitc>	jugg: you have to tag
| [Thursday 13 January 2011] [11:46:08] <jugg>	just to build ??
| [Thursday 13 January 2011] [11:46:12] <benoitc>	i can remove it though
| [Thursday 13 January 2011] [11:46:25] <benoitc>	jugg: this is for archive creation
| [Thursday 13 January 2011] [11:46:26] <jugg>	yes, I build much more often than I tag
| [Thursday 13 January 2011] [11:46:35] <jugg>	no, that happens when doing $ make
| [Thursday 13 January 2011] [11:46:36] <benoitc>	let me edit this Makefile :)
| [Thursday 13 January 2011] [11:46:40] <jugg>	k :)
| [Thursday 13 January 2011] [11:46:55] <benoitc>	you could just do ./rebar compile anyway
| [Thursday 13 January 2011] [11:52:09] <amacleod>	Should I file my test case as an attachment to https://github.com/zeromq/zeromq2/issues/#issue/127 , or start a new issue?
| [Thursday 13 January 2011] [11:52:56] <mikko>	amacleod: is it python?
| [Thursday 13 January 2011] [11:53:03] <amacleod>	mikko, yes, Python, not Ruby.
| [Thursday 13 January 2011] [11:53:11] <mikko>	open it under https://github.com/zeromq/pyzmq
| [Thursday 13 January 2011] [11:58:19] <benoitc>	jugg: fixed and pushed
| [Thursday 13 January 2011] [12:07:32] <jugg>	benoitc, $git rebase -i can be your friend... :)
| [Thursday 13 January 2011] [12:14:56] <benoitc>	mmm ?
| [Thursday 13 January 2011] [12:15:05] <benoitc>	I've used rebase -i
| [Thursday 13 January 2011] [12:15:14] <benoitc>	just cherry-picking last update
| [Thursday 13 January 2011] [12:15:52] <jugg>	why not just rebase your commits ontop of the last update?
| [Thursday 13 January 2011] [12:16:14] <benoitc>	in rebar-socketprocess
| [Thursday 13 January 2011] [12:16:16] <benoitc>	dunno
| [Thursday 13 January 2011] [12:16:24] <benoitc>	rebasing now
| [Thursday 13 January 2011] [12:21:17] <benoitc>	jugg: done
| [Thursday 13 January 2011] [12:25:22] <benoitc>	win 6
| [Thursday 13 January 2011] [13:14:52] <amacleod>	Bleh.  Didn't realize pyzmq master won't build against zmq 2.1.0.
| [Thursday 13 January 2011] [13:19:16] <benoitc>	mmm it is 
| [Thursday 13 January 2011] [13:19:27] <benoitc>	at least it does
| [Thursday 13 January 2011] [13:20:21] <amacleod>	Do I need to delete my previous installation of pyzmq in order to make use of the development version?
| [Thursday 13 January 2011] [13:20:34] <benoitc>	i've installed it in my virtualenv
| [Thursday 13 January 2011] [13:22:35] <amacleod>	I must be doing something wrong.  I built and installed pyzmq master, and when I try to import zmq, it gets an error, 'cause it can't import initthreads from zmq.util
| [Thursday 13 January 2011] [13:23:27] <benoitc>	did you change paths in setup.cfg?
| [Thursday 13 January 2011] [13:26:01] <amacleod>	Ah, nope.  That must be it.
| [Thursday 13 January 2011] [13:26:38] <amacleod>	Does it not use /usr/local/lib and /usr/local/include by default?
| [Thursday 13 January 2011] [13:33:18] <benoitc>	not sure
| [Thursday 13 January 2011] [13:45:46] <amacleod>	The weird thing is that everything seems to get installed just fine.  It's only when I go to import zmq that the error occurs.
| [Thursday 13 January 2011] [14:50:27] <mikko>	sustrik: https://github.com/danmar/cppcheck/commit/36c18072280d71e49d4d2a38d011666f792d6283
| [Thursday 13 January 2011] [14:50:59] <mikko>	wrong one
| [Thursday 13 January 2011] [14:51:34] <mikko>	maybe not, not sure if that affects the one you reported
| [Thursday 13 January 2011] [14:52:42] <sustrik>	looks like
| [Thursday 13 January 2011] [14:53:27] <mikko>	testing now
| [Thursday 13 January 2011] [14:54:53] <mikko>	nope, still see those reported
| [Thursday 13 January 2011] [17:56:15] <yrashk>	can push socket be shared across threads?
| [Thursday 13 January 2011] [17:56:25] <yrashk>	or is it unsafe to do so?
| [Thursday 13 January 2011] [18:29:59] <yrashk>	if zmq_send with ZMQ_NOBLOCK returns EAGAIN, do I have to reinitialize the message?
| [Thursday 13 January 2011] [20:51:59] <jugg>	yrashk, in 2.1, you can migrate a socket between threads, but you can't share the socket simultaneously in multiple threads.
| [Thursday 13 January 2011] [20:52:14] <jugg>	and no need to reinitialize.
| [Friday 14 January 2011] [01:20:39] <potatodemon>	Hey Y'all.  I want to have a pub/sub queue.  Where these is no data persistance, if someone is not subscribed to the queue the data is not kept around.  Is this easy to do with 0mq?
| [Friday 14 January 2011] [01:22:26] <potatodemon>	Oh this looks like it is the default behavior. word up
| [Friday 14 January 2011] [03:28:11] <sustrik>	yes, it's default
| [Friday 14 January 2011] [03:28:52] <sustrik>	yeashk: no need to re-initialise
| [Friday 14 January 2011] [03:29:12] <sustrik>	ah, jugg answered already :)
| [Friday 14 January 2011] [04:30:22] <yrashk>	jugg: thanks! already moved to two push sockets approach :)
| [Friday 14 January 2011] [06:07:04] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r8eae7d8 10/ (5 files): 
| [Friday 14 January 2011] [06:07:04] <CIA-21>	zeromq2: 'message distribution mechanism' separated from XPUB socket
| [Friday 14 January 2011] [06:07:04] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/eC63Tc
| [Friday 14 January 2011] [06:15:46] <mikko>	good morning
| [Friday 14 January 2011] [06:17:09] <sustrik>	morning
| [Friday 14 January 2011] [06:26:28] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r58c9830 10/ (src/xsub.cpp src/xsub.hpp): 
| [Friday 14 January 2011] [06:26:28] <CIA-21>	zeromq2: XSUB socket has a subscription distributor
| [Friday 14 January 2011] [06:26:28] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/fifGK7
| [Friday 14 January 2011] [06:37:51] <CIA-21>	zeromq2: 03Martin Sustrik 07master * ra348d94 10/ (src/xpub.cpp src/xpub.hpp): 
| [Friday 14 January 2011] [06:37:51] <CIA-21>	zeromq2: Fair queueing of subscriptions added to XPUB socket
| [Friday 14 January 2011] [06:37:51] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/gZWsdO
| [Friday 14 January 2011] [06:40:58] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r59fa0c9 10/ AUTHORS : 
| [Friday 14 January 2011] [06:40:58] <CIA-21>	zeromq2: Gerard Toonstra added to the authors file
| [Friday 14 January 2011] [06:40:58] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/fNsKW7
| [Friday 14 January 2011] [06:50:16] <guido_g>	howdy
| [Friday 14 January 2011] [06:50:29] <guido_g>	any idea what is the cause of: Assertion failed: pending_bytes == 0 (pgm_receiver.cpp:141)
| [Friday 14 January 2011] [06:51:34] <guido_g>	killing my subscriber randomly
| [Friday 14 January 2011] [06:52:16] <guido_g>	looks like a heisen bug
| [Friday 14 January 2011] [07:02:30] <sustrik>	guido_g: the assert shouldn't be there
| [Friday 14 January 2011] [07:02:31] <sustrik>	imo
| [Friday 14 January 2011] [07:02:53] <sustrik>	please, do report the problem on the mailing list so that steven can get a look at it
| [Friday 14 January 2011] [07:17:26] <guido_g>	ok
| [Friday 14 January 2011] [07:30:18] <benoitc>	mmm how would you authenticate consumers in a PUB/SUB schema ?
| [Friday 14 January 2011] [07:31:50] <guido_g>	over a different connection
| [Friday 14 January 2011] [07:32:31] <benoitc>	i'm not sur eto follow, if i setup a pub server
| [Friday 14 January 2011] [07:32:46] <benoitc>	how can i make sure only authentciated consumer can have access to it ?
| [Friday 14 January 2011] [07:32:56] <benoitc>	something in the message ?
| [Friday 14 January 2011] [07:33:18] <guido_g>	mq does not provide authentication
| [Friday 14 January 2011] [07:33:27] <guido_g>	so you've to do it yourself
| [Friday 14 January 2011] [07:33:30] <benoitc>	i know
| [Friday 14 January 2011] [07:33:37] <benoitc>	i'm looking for ideas
| [Friday 14 January 2011] [07:33:47] <guido_g>	simple solution would be to use a req/rep
| [Friday 14 January 2011] [07:34:28] <benoitc>	right, it would mean a dedicaced connection in this case then
| [Friday 14 January 2011] [07:34:40] <guido_g>	for authentication
| [Friday 14 January 2011] [07:35:01] <benoitc>	mmm ? 
| [Friday 14 January 2011] [07:35:06] <benoitc>	i don't follow
| [Friday 14 January 2011] [07:35:58] <jugg>	it'd be interesting if pub sockets could accept connections based on connecting sub socket identity.
| [Friday 14 January 2011] [07:36:27] <guido_g>	i doubt that
| [Friday 14 January 2011] [07:36:31] <jugg>	or reject them...
| [Friday 14 January 2011] [07:36:47] <guido_g>	see where amqp went with all these "nice features"
| [Friday 14 January 2011] [07:37:34] <jugg>	socket identity itself isn't a nice feature?
| [Friday 14 January 2011] [07:37:54] <guido_g>	<jugg> it'd be interesting if pub sockets could accept connections based on connecting sub socket identity.
| [Friday 14 January 2011] [07:38:10] <guido_g>	socket-ids are cheap
| [Friday 14 January 2011] [07:38:21] <guido_g>	authentication is not
| [Friday 14 January 2011] [07:38:29] <jugg>	thanks, I didn't realize I wrote that... :)
| [Friday 14 January 2011] [07:38:55] <guido_g>	just to give the context for my point
| [Friday 14 January 2011] [07:39:13] <benoitc>	well it could be just a filter on socket-id
| [Friday 14 January 2011] [07:39:21] <benoitc>	whatever you do with that
| [Friday 14 January 2011] [07:39:51] <jugg>	so, you'd reject subscription forwarding then?  It isn't much different.
| [Friday 14 January 2011] [07:40:09] <guido_g>	yes
| [Friday 14 January 2011] [07:40:28] <jugg>	yes you'd reject it, or yes it is different?
| [Friday 14 January 2011] [07:40:33] <guido_g>	a)
| [Friday 14 January 2011] [07:41:33] <jugg>	anyway...  the idea is still interesting, likable or not. :)
| [Friday 14 January 2011] [07:43:21] <jugg>	probably could just add 'subscribe' socket option to a pub socket, and only identities that match the pub subscriptions can connect.  Too greatly overload the concept. :)
| [Friday 14 January 2011] [07:44:06] <guido_g>	how would this work w/ pgm?
| [Friday 14 January 2011] [07:44:58] <jugg>	I'll let someone else solve that :)
| [Friday 14 January 2011] [07:45:08] <guido_g>	i knew that...
| [Friday 14 January 2011] [07:45:39] <benoitc>	i guess i could encrypt messages in the pubserver
| [Friday 14 January 2011] [07:45:56] <guido_g>	sure
| [Friday 14 January 2011] [07:45:56] <benoitc>	so only authorized suscribers could read them
| [Friday 14 January 2011] [07:46:10] <guido_g>	decode
| [Friday 14 January 2011] [07:46:30] <benoitc>	yes
| [Friday 14 January 2011] [07:46:32] <guido_g>	the message itself would still be readable by not autorized clients
| [Friday 14 January 2011] [07:46:46] <benoitc>	right
| [Friday 14 January 2011] [07:56:24] <jugg>	if it is an issue of sensitive data, then you need to encrypt the connection anyway.   I assumed you were solving an issue of limiting connections.  So, however you encrypt the connection could also encapsulate the authentication.
| [Friday 14 January 2011] [07:57:26] <benoitc>	well not in a pubsub, i can't say don't send to this suscriber
| [Friday 14 January 2011] [07:58:57] <benoitc>	what i can do on the other hand is to let trusted suscribers to decode
| [Friday 14 January 2011] [09:21:56] <Steve-o>	so is anyone trying to write new transports for zmq?
| [Friday 14 January 2011] [09:24:05] <mikko>	Steve-o: sustrik maybe?
| [Friday 14 January 2011] [09:24:05] <mikko>	:)
| [Friday 14 January 2011] [09:24:22] <sustrik>	Steve-o: why so?
| [Friday 14 January 2011] [09:25:15] <sustrik>	Steve-o: btw, the problem reported by guido_g
| [Friday 14 January 2011] [09:25:37] <Steve-o>	just wondering
| [Friday 14 January 2011] [09:25:45] <sustrik>	what the semantics pending_bytes?
| [Friday 14 January 2011] [09:25:48] <sustrik>	of
| [Friday 14 January 2011] [09:26:06] <Steve-o>	zmq batches zmq messages into PGM packets
| [Friday 14 January 2011] [09:26:22] <Steve-o>	the pending_bytes refers to data remaining in the batch not sent to the application
| [Friday 14 January 2011] [09:26:32] <Steve-o>	I believe
| [Friday 14 January 2011] [09:27:12] <sustrik>	as for the transport it would be nice to make adding new ones but atm the interface between the trasnport and the rest of 0mq is kind of fuzzy
| [Friday 14 January 2011] [09:27:32] <sustrik>	adding new ones easy
| [Friday 14 January 2011] [09:30:12] <sustrik>	guido_g: is the problem reproducible?
| [Friday 14 January 2011] [09:30:59] <Steve-o>	something like a HTTP transport is quite complicated as you need timers and odd twist of push/pull characteristics unless you throw threads at it
| [Friday 14 January 2011] [09:31:37] <Steve-o>	I haven't seen guido's problem otherwise I would have logged it
| [Friday 14 January 2011] [09:34:24] <sustrik>	it's on the mailing list
| [Friday 14 January 2011] [09:34:41] <sustrik>	you've already replied
| [Friday 14 January 2011] [09:35:56] <mikko>	Steve-o: websocket transport might be a lot easier
| [Friday 14 January 2011] [09:36:06] <sustrik>	afaiu the problem is that if data cannot be sent to the application due to HWM or somesuch (pending_bytes>0)
| [Friday 14 January 2011] [09:36:21] <sustrik>	then pgm_receiver should unregister itself from polling on incoming data (reset_pollin)
| [Friday 14 January 2011] [09:36:46] <sustrik>	if it does so, in_event() should not be invoked
| [Friday 14 January 2011] [09:36:52] <sustrik>	and thus the assert doesn't happen
| [Friday 14 January 2011] [09:37:15] <sustrik>	there's a bug somewhere...
| [Friday 14 January 2011] [09:38:52] <sustrik>	mikko, Steve-o: HTTP, XMPP, SOAP and such are pretty complex, however, protocols like SCTP or UDP seem to make much better fit
| [Friday 14 January 2011] [09:39:04] <sustrik>	UDT i meant
| [Friday 14 January 2011] [09:44:49] <Steve-o>	HTTP is interesting as its really only the connection process that is different, the rest follows the TCP transport
| [Friday 14 January 2011] [09:46:33] <guido_g>	re
| [Friday 14 January 2011] [09:46:53] <guido_g>	sustrik: as I said, sometimes it happens sometimes not
| [Friday 14 January 2011] [09:47:09] <guido_g>	so there is no way to trigger that on demand
| [Friday 14 January 2011] [09:50:02] <guido_g>	msut be something in the packet because three independent subscribers crashed simultaniously
| [Friday 14 January 2011] [09:50:05] <guido_g>	*must
| [Friday 14 January 2011] [09:52:51] <Steve-o>	I guess you can tell if you had a dummy client that subs on the same transport but does no processing
| [Friday 14 January 2011] [09:53:19] <guido_g>	is in the working atm
| [Friday 14 January 2011] [09:53:34] <Steve-o>	Martin's implication is that the leading messages cause high CPU usage to cause the HWM to be hit
| [Friday 14 January 2011] [09:57:00] <Steve-o>	I presume then it would be straight forward to reproduce with a sleeping client and reasonably expedient publisher
| [Friday 14 January 2011] [09:59:08] <guido_g>	spoc works fine so far
| [Friday 14 January 2011] [09:59:34] <guido_g>	spoc  := Simplest POssibile Client
| [Friday 14 January 2011] [10:01:55] <guido_g>	other client still dies
| [Friday 14 January 2011] [10:03:12] <guido_g>	what does this error mean?
| [Friday 14 January 2011] [10:03:38] <Steve-o>	as Martin says, it is due to HWM on receiving side to app'
| [Friday 14 January 2011] [10:04:02] <Steve-o>	i.e. slow consumer causes push from PGM to the app' the fail and leave unprocessed data
| [Friday 14 January 2011] [10:04:52] <guido_g>	pardon?
| [Friday 14 January 2011] [10:05:20] <Steve-o>	data is queuing up inside ZMQ for you app'
| [Friday 14 January 2011] [10:05:29] <guido_g>	ok
| [Friday 14 January 2011] [10:05:43] <Steve-o>	when it hits a certain level it pushes back to the transport
| [Friday 14 January 2011] [10:05:52] <guido_g>	also ok and understood
| [Friday 14 January 2011] [10:06:06] <Steve-o>	the transport, PGM, operates in batches of messages, one packet contains one batch
| [Friday 14 January 2011] [10:06:19] <guido_g>	ok
| [Friday 14 January 2011] [10:06:49] <Steve-o>	the queue limit is being reached before a packet batch of messages has completed
| [Friday 14 January 2011] [10:07:19] <Steve-o>	leaving unprocessed bytes (pending_bytes > 0)
| [Friday 14 January 2011] [10:07:54] <guido_g>	now it starts to make sense
| [Friday 14 January 2011] [10:07:54] <Steve-o>	a subsequent event indicating further new incoming data occurs
| [Friday 14 January 2011] [10:08:03] <Steve-o>	then the assertion is hit
| [Friday 14 January 2011] [10:08:37] <guido_g>	so one way to circumvent this problem would be a high HWM on the subscriber?
| [Friday 14 January 2011] [10:09:53] <Steve-o>	well the transport needs to unhook from future in_events until the queue hits the LWM I guess
| [Friday 14 January 2011] [10:10:20] <guido_g>	iow, no easy way work around that bug
| [Friday 14 January 2011] [10:11:08] <Steve-o>	higher watermark would be a workaround
| [Friday 14 January 2011] [10:11:27] <guido_g>	i'll give it a try
| [Friday 14 January 2011] [10:12:03] <guido_g>	does rate-limiting work on the receiver side?
| [Friday 14 January 2011] [10:12:59] <Steve-o>	send side
| [Friday 14 January 2011] [10:13:57] <Steve-o>	just looking at zmq receiver, it already does unhook some events
| [Friday 14 January 2011] [10:14:21] <Steve-o>	line 222-231,
| [Friday 14 January 2011] [10:15:58] <Steve-o>	maybe then its the timer event
| [Friday 14 January 2011] [10:16:11] <sustrik>	hm
| [Friday 14 January 2011] [10:16:15] <sustrik>	what is see is:
| [Friday 14 January 2011] [10:16:16] <sustrik>	pending_bytes = received - processed;
| [Friday 14 January 2011] [10:16:17] <sustrik>	...
| [Friday 14 January 2011] [10:16:23] <sustrik>	reset_pollin (pipe_handle);
| [Friday 14 January 2011] [10:16:23] <sustrik>	            reset_pollin (socket_handle);
| [Friday 14 January 2011] [10:16:24] <Steve-o>	slow consumer with waiting packets
| [Friday 14 January 2011] [10:16:43] <sustrik>	and the whole thing is under
| [Friday 14 January 2011] [10:16:48] <sustrik>	if (processed < received) {
| [Friday 14 January 2011] [10:17:16] <Steve-o>	but timer events call in_event()
| [Friday 14 January 2011] [10:17:27] <sustrik>	it looks like there's no guarantee that reset_pollin will be triggered iff pending_bytes>0
| [Friday 14 January 2011] [10:17:41] <sustrik>	the code is quite complex though...
| [Friday 14 January 2011] [10:18:01] <Steve-o>	therefore the timer must skip if the pollin is in reset state
| [Friday 14 January 2011] [10:18:20] <sustrik>	ah. maybe
| [Friday 14 January 2011] [10:18:43] <sustrik>	that should be easy to test
| [Friday 14 January 2011] [10:18:57] <Steve-o>	or simply add a cancel_timer with reset_pollin()
| [Friday 14 January 2011] [10:19:29] <sustrik>	or just add a bool variable 'pollin_active'
| [Friday 14 January 2011] [10:19:54] <sustrik>	and return immediately from in_event if it's false
| [Friday 14 January 2011] [10:20:45] <Steve-o>	canceling the timer would be cleaner 
| [Friday 14 January 2011] [10:20:51] <sustrik>	sure
| [Friday 14 January 2011] [10:21:10] <Steve-o>	just copy the section in unplug()
| [Friday 14 January 2011] [10:23:22] <Steve-o>	++229: if (has_rx_timer) { cancel_timer (rx_timer_id); has_rx_timer = false; }
| [Friday 14 January 2011] [10:24:19] <Steve-o>	although ideally the timer should live until the reset state clears
| [Friday 14 January 2011] [10:25:28] <Steve-o>	if there is no further incoming data but packets remain in the window they will not get flushed., depending the complex logic determing when in_event fires
| [Friday 14 January 2011] [10:27:07] <Steve-o>	as in, after the queue is cleared
| [Friday 14 January 2011] [10:38:26] <Steve-o>	but it's certainly a condition worthy of note, as without the assertion you have an incredibly high chance of data loss
| [Friday 14 January 2011] [10:47:54] <guido_g>	ok, a very high HWM on the subscriber side does the trick so far
| [Friday 14 January 2011] [10:54:46] <sustrik>	Steve-o: however, I assume the timer should be cancelled nontheless
| [Friday 14 January 2011] [10:54:47] <sustrik>	right?
| [Friday 14 January 2011] [12:36:33] <mikko>	sustrik: is PUSH socket supposed to block when HWM is reached even if ZMQ_NOBLOCK is used?
| [Friday 14 January 2011] [13:39:59] <sustrik>	mikko: no
| [Friday 14 January 2011] [13:40:09] <sustrik>	it should return EAGAIN
| [Friday 14 January 2011] [13:53:08] <mikko>	sustrik: ok, i wonder why i'm seeing this behavior
| [Friday 14 January 2011] [13:53:19] <mikko>	let me recheck the code
| [Friday 14 January 2011] [13:55:02] <mikko>	ah, found it
| [Friday 14 January 2011] [13:55:44] <sustrik>	what's going on?
| [Friday 14 January 2011] [13:57:02] <mikko>	launched on debugger and noticed that it's blocking on lingering messages rather than send ()
| [Friday 14 January 2011] [13:57:48] <mikko>	i'm adding a test case for hwm
| [Friday 14 January 2011] [13:58:31] <mikko>	hmm, looks like it depends differently depending on whether i bind or connect
| [Friday 14 January 2011] [14:04:26] <sustrik>	yes, they are different
| [Friday 14 January 2011] [14:04:35] <sustrik>	when you bind there's no pipe there
| [Friday 14 January 2011] [14:04:44] <sustrik>	so send blocks immediately
| [Friday 14 January 2011] [14:05:12] <sustrik>	with connect, the pipe is created straight away, so you can send messages immediately
| [Friday 14 January 2011] [14:05:32] <sustrik>	i mean, with bind the pipes are created as individual peers connect
| [Friday 14 January 2011] [14:08:01] <mikko>	sustrik: is that the same with inproc?
| [Friday 14 January 2011] [14:09:41] <sustrik>	yes, the same principle
| [Friday 14 January 2011] [14:10:53] <mikko>	is there any difference between HWM handling between transports / socket types (apart from inproc)
| [Friday 14 January 2011] [14:10:53] <sustrik>	it's an inherent issue, the HWM is per peer
| [Friday 14 January 2011] [14:11:25] <sustrik>	so it doesn't even make sense to talk about HWM until there is no peer connected
| [Friday 14 January 2011] [14:11:36] <sustrik>	it's the same for all transports
| [Friday 14 January 2011] [14:12:01] <sustrik>	although... pgm is kind of different
| [Friday 14 January 2011] [14:12:18] <sustrik>	on the pub side it treats all the subs as a single "connection"
| [Friday 14 January 2011] [14:12:39] <sustrik>	(it's multicast so that's the only way to do it)
| [Friday 14 January 2011] [14:28:47] <mikko>	sustrik: does the socket come out from exceptional state after all pending messages have been consumed?
| [Friday 14 January 2011] [17:29:17] <sustrik>	mikko: no, it comes out after LWM is reached
| [Friday 14 January 2011] [17:43:28] <mikko>	sustrik: noticed
| [Friday 14 January 2011] [17:54:10] <mikko>	sustrik: https://gist.github.com/cd0cd7d8407c30456c23
| [Friday 14 January 2011] [17:54:18] <mikko>	shouldn't the SUB recv the second message?
| [Friday 14 January 2011] [17:54:23] <mikko>	or am i being silly again?
| [Friday 14 January 2011] [19:34:39] <mvolkov>	I am the first day 0MQ user and after going through docs I understand that 0MQ has capability of doing multiplexing between a few sockets with zmq_poll() function
| [Friday 14 January 2011] [19:35:57] <mvolkov>	however, I can't seems to find how one define a list of resources/items in Python
| [Friday 14 January 2011] [19:37:18] <mvolkov>	Can anyone please give me a hint? Or white paper or doc link?
| [Friday 14 January 2011] [19:37:27] <mvolkov>	on this topic?
| [Saturday 15 January 2011] [06:16:19] <mikko>	mvolkov: there should be examples of poll under pyzmq github 
| [Saturday 15 January 2011] [06:40:19] <CIA-21>	zeromq2: 03Martin Sustrik 07sub-forward * rbe94000 10/ (5 files): 
| [Saturday 15 January 2011] [06:40:19] <CIA-21>	zeromq2: Forwarding subscriptions up the stream implemented
| [Saturday 15 January 2011] [06:40:19] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/eLjdU0
| [Saturday 15 January 2011] [06:40:20] <CIA-21>	zeromq2: 03Martin Sustrik 07sub-forward * r706296d 10/ (src/trie.cpp src/trie.hpp src/xsub.cpp src/xsub.hpp): 
| [Saturday 15 January 2011] [06:40:20] <CIA-21>	zeromq2: Subscriptions from XSUB socketare sent to each new peer.
| [Saturday 15 January 2011] [06:40:20] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/gAfivp
| [Saturday 15 January 2011] [06:40:22] <CIA-21>	zeromq2: 03Martin Sustrik 07sub-forward * r3d26c3d 10/ (5 files): 
| [Saturday 15 January 2011] [06:40:22] <CIA-21>	zeromq2: econnection should now trigger subscription re-sending
| [Saturday 15 January 2011] [06:40:22] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/gdt449
| [Saturday 15 January 2011] [06:47:19] <CIA-21>	zeromq2: 03Martin Sustrik 07sub-forward * rbb605e0 10/ src/pub.cpp : 
| [Saturday 15 January 2011] [06:47:19] <CIA-21>	zeromq2: Print out subscriptions in PUB socket (for testing purposes)
| [Saturday 15 January 2011] [06:47:20] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/eV0jas
| [Saturday 15 January 2011] [06:47:45] <mikko>	sustrik: busy morning!
| [Saturday 15 January 2011] [06:47:53] <sustrik>	mikko: morning
| [Saturday 15 January 2011] [06:48:23] <sustrik>	i finally found some time to spent on subscription forwarding
| [Saturday 15 January 2011] [06:50:03] <mikko>	sustrik: did you see my paste from yesterday?
| [Saturday 15 January 2011] [06:50:13] <sustrik>	no
| [Saturday 15 January 2011] [06:50:15] <sustrik>	let me see
| [Saturday 15 January 2011] [06:50:21] <mikko>	https://gist.github.com/cd0cd7d8407c30456c23
| [Saturday 15 January 2011] [06:51:14] <sustrik>	hm, hard to say
| [Saturday 15 January 2011] [06:51:20] <sustrik>	it depends much on the timing
| [Saturday 15 January 2011] [06:51:29] <sustrik>	zmq_close is async
| [Saturday 15 January 2011] [06:51:52] <sustrik>	so the socket may actually still exist at the time you are sending second message
| [Saturday 15 January 2011] [06:52:04] <sustrik>	so it gets the message and terminates
| [Saturday 15 January 2011] [06:52:05] <mikko>	i tried adding sleep(5); before the second message
| [Saturday 15 January 2011] [06:52:08] <mikko>	but that didn't work
| [Saturday 15 January 2011] [06:52:09] <sustrik>	same thing?
| [Saturday 15 January 2011] [06:52:22] <sustrik>	that it looks like a bug imo
| [Saturday 15 January 2011] [06:52:30] <sustrik>	can you fill in a ticket?
| [Saturday 15 January 2011] [06:52:56] <mikko>	this is actually one of the test cases i've been preparing
| [Saturday 15 January 2011] [06:53:17] <sustrik>	great
| [Saturday 15 January 2011] [06:53:31] <mikko>	HWM and identity
| [Saturday 15 January 2011] [06:53:40] <mikko>	testing with sleep 20 now
| [Saturday 15 January 2011] [06:53:50] <mikko>	just in case 
| [Saturday 15 January 2011] [06:54:17] <mikko>	hmm, i could also try running the subscriber in it's own thread
| [Saturday 15 January 2011] [06:59:28] <sustrik>	mikko: i assume it's a bug
| [Saturday 15 January 2011] [06:59:34] <sustrik>	the test looks ok
| [Saturday 15 January 2011] [07:01:14] <mikko>	i'll open issue
| [Saturday 15 January 2011] [07:09:59] <mikko>	issue #150
| [Saturday 15 January 2011] [07:10:41] <mikko>	the HWM test-case is in http://valokuva.org/~mikko/0002-Added-test-for-HWM.patch
| [Saturday 15 January 2011] [07:14:08] <sustrik>	thanks
| [Saturday 15 January 2011] [07:41:40] <jugg>	sustrik, such a minor single word change to warrant a patch... The pull request was just so it got noticed, not so I got credit...  but anyway.
| [Saturday 15 January 2011] [07:57:27] <sustrik>	jugg: as you wish
| [Saturday 15 January 2011] [07:57:47] <sustrik>	let me fix it
| [Saturday 15 January 2011] [07:58:57] <sustrik>	jugg: have you sent the patch or not?
| [Saturday 15 January 2011] [07:59:05] <jugg>	I did... 
| [Saturday 15 January 2011] [07:59:16] <sustrik>	haven't got it yet
| [Saturday 15 January 2011] [08:00:11] <jugg>	I use gmane, sometimes it moves slowly.
| [Saturday 15 January 2011] [08:00:19] <sustrik>	np
| [Saturday 15 January 2011] [08:00:51] <jugg>	anyway, if it doesn't show up, feel free to make the change on your own.
| [Saturday 15 January 2011] [08:00:57] <sustrik>	sure
| [Saturday 15 January 2011] [08:01:26] <sustrik>	it's kind of strange following the process for trivial changes like this one
| [Saturday 15 January 2011] [08:01:41] <sustrik>	but it's hard to set a boundary between trivial and non-trivial
| [Saturday 15 January 2011] [09:04:27] <gancient>	hi all, i am trying to implement a distributed matrix multiplication algorithm in python using zmq , what would be the best approach ? (I am new to zmq , so any suggestions / comments are useful )
| [Saturday 15 January 2011] [10:29:01] <mvolkov>	mikko: Thank you for the answer. The issue is the not all zguide tutorial examples are translated to Python, however, I found examples at http://nullege.com/ - hopefully they'll work.
| [Saturday 15 January 2011] [10:29:24] <mikko>	mvolkov: https://github.com/zeromq/pyzmq/tree/master/examples
| [Saturday 15 January 2011] [10:30:08] <mvolkov>	oh... then we are talking about the same thing. Thank you
| [Saturday 15 January 2011] [13:31:40] <mikko>	sustrik: seems like msvc build files are out of date (?) 
| [Saturday 15 January 2011] [14:07:50] <sustrik>	mikko: right
| [Saturday 15 January 2011] [14:07:53] <sustrik>	let me fix it
| [Saturday 15 January 2011] [14:15:30] <CIA-21>	zeromq2: 03Martin Sustrik 07master * ra249d15 10/ builds/msvc/libzmq/libzmq.vcproj : 
| [Saturday 15 January 2011] [14:15:30] <CIA-21>	zeromq2: Fix MSVC build
| [Saturday 15 January 2011] [14:15:30] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/i0HCXP
| [Saturday 15 January 2011] [14:17:58] <sustrik>	mikko: ok, done
| [Saturday 15 January 2011] [16:13:51] <mikko>	sustrik_: thanks
| [Saturday 15 January 2011] [18:13:56] <mvolkov>	Q: is there a way in 0MQ to know whether socked is busy doing something so message is not sent until it is ready?
| [Saturday 15 January 2011] [18:15:06] <mvolkov>	or in 0MQ terminology how this "check and wait" behavior would be called?
| [Saturday 15 January 2011] [18:15:22] <mvolkov>	appreciate any input
| [Saturday 15 January 2011] [18:22:04] <mikko>	mvolkov: there are different kind of behaviors with different socket types
| [Saturday 15 January 2011] [18:22:18] <mikko>	mvolkov: for example PUB socket drops the message if there are no subscribers
| [Saturday 15 January 2011] [18:23:08] <mikko>	mvolkov: im not sure whether this answers your question as i am not sure what "socket is busy doing something" means
| [Saturday 15 January 2011] [18:54:18] <Skaag>	mikko: is this channel logged somewhere?
| [Saturday 15 January 2011] [19:23:48] <mvolkov>	mikko: I am interested in load balancing work to the different tcp: sockets and so far I understand that this is achievable with zmd.poll() function
| [Saturday 15 January 2011] [19:24:19] <mvolkov>	the objective is basically send message to less busy device
| [Saturday 15 January 2011] [19:24:38] <mvolkov>	or device which is doing nothing
| [Saturday 15 January 2011] [19:31:03] <mikko>	Skaag: not as far as i know
| [Saturday 15 January 2011] [19:31:12] <Skaag>	that is too bad
| [Saturday 15 January 2011] [19:31:17] <mikko>	mvolkov: load-balancing based on least busy is really not achievable using poll
| [Saturday 15 January 2011] [19:31:21] <Skaag>	a lot of very good answers here, to very good questions...
| [Saturday 15 January 2011] [19:31:27] <mikko>	mvolkov: you would need additional logic on top of the polling
| [Saturday 15 January 2011] [19:31:40] <mikko>	mvolkov: as in the poll really doesn't know which one of the sockets is least busy
| [Saturday 15 January 2011] [19:31:59] <mikko>	mvolkov: the built-in algorithm uses round-robin for balancing
| [Saturday 15 January 2011] [19:32:14] <mikko>	Skaag: i think i got logs since around last Feb
| [Saturday 15 January 2011] [19:32:32] <Skaag>	that's awesome. upload them somewhere.
| [Saturday 15 January 2011] [19:33:22] <mvolkov>	mikko: oh, so zmd.poll() has by default round robin built in? do I understand this right?
| [Saturday 15 January 2011] [19:36:55] <mikko>	Skaag: sec
| [Saturday 15 January 2011] [19:36:57] <mikko>	mvolkov: nope
| [Saturday 15 January 2011] [19:37:21] <mikko>	mvolkov: zmq_poll just indicates which sockets are readable/writable depending on parameters passed
| [Saturday 15 January 2011] [19:37:38] <mikko>	mvolkov: what i meant is that PUSH/PULL has round-robin balancing built in
| [Saturday 15 January 2011] [19:38:03] <mikko>	mvolkov: so if you zmq_connect PUSH socket multiple times the messages sent to the socket are balanced between the underlying transport sockets (tcp, ipc etc)
| [Saturday 15 January 2011] [19:38:17] <mvolkov>	mikko: thank you I'll try that -- greatly appreciate your inp
| [Saturday 15 January 2011] [19:39:05] <mvolkov>	ut
| [Saturday 15 January 2011] [19:42:52] <mikko>	Skaag: http://valokuva.org/~mikko/zeromq.log
| [Saturday 15 January 2011] [19:42:54] <mikko>	since last march
| [Saturday 15 January 2011] [19:43:13] <Skaag>	awesome :)
| [Saturday 15 January 2011] [19:43:21] <Skaag>	thanks
| [Saturday 15 January 2011] [21:01:05] <xchen>	hi, guys.
| [Saturday 15 January 2011] [21:01:41] <mikko>	hi
| [Saturday 15 January 2011] [21:02:08] <xchen>	I have a question about zeromq, I want to use the zeromq in a cluster which is connected using infiniband
| [Saturday 15 January 2011] [21:02:27] <xchen>	hi, mikko, thank you for your reply
| [Saturday 15 January 2011] [21:03:00] <xchen>	How can I configure the zeromq to make sure it use the infiniband, not the ethenet
| [Saturday 15 January 2011] [21:03:43] <xchen>	since the cluster is connected using both eth and ib
| [Saturday 15 January 2011] [21:05:33] <mikko>	i haven't really got experience with infiniband
| [Saturday 15 January 2011] [21:05:34] <xchen>	I googled and find nothing about the configuration of zeromq over infiniband, and it is not explained in the manual, 
| [Saturday 15 January 2011] [21:05:41] <xchen>	thanks
| [Saturday 15 January 2011] [21:05:46] <mikko>	you might want to ask your question tomorrow morning CET
| [Saturday 15 January 2011] [21:05:54] <mikko>	sustrik_ would probably be able to answer it 
| [Saturday 15 January 2011] [21:06:19] <xchen>	ok, thanks very much. He will be online then?
| [Saturday 15 January 2011] [21:06:28] <mikko>	usually is 
| [Saturday 15 January 2011] [21:06:43] <mikko>	are you running tcp/ip over infiniband?
| [Saturday 15 January 2011] [21:07:42] <xchen>	I didn't get you question. Zeromq is over tcp/ip than infiniband?
| [Saturday 15 January 2011] [21:07:53] <xchen>	I didn't get you question. Zeromq is over tcp/ip then infiniband?
| [Saturday 15 January 2011] [21:08:52] <mikko>	http://www.zeromq.org/results:ib-tests-v031
| [Saturday 15 January 2011] [21:09:57] <mikko>	ah
| [Saturday 15 January 2011] [21:09:59] <xchen>	Yes, I saw this page. But I do not know how do they get this result.
| [Saturday 15 January 2011] [21:10:07] <mikko>	found an old mailing list entry about infiniband
| [Saturday 15 January 2011] [21:10:33] <mikko>	xchen: http://lists.zeromq.org/pipermail/zeromq-dev/2009-December/001472.html
| [Saturday 15 January 2011] [21:11:30] <xchen>	Thank you very much. I have found this. But it seems do not answer my question
| [Saturday 15 January 2011] [21:11:47] <mikko>	xchen: best wait for sustrik to be online in that case
| [Saturday 15 January 2011] [21:12:07] <mikko>	you could also try posting to the mailing-lists
| [Saturday 15 January 2011] [21:12:18] <xchen>	ok, thanks. 
| [Saturday 15 January 2011] [21:12:40] <xchen>	thank you for so much help.
| [Saturday 15 January 2011] [21:13:02] <mikko>	no problem, i can't really be much more help as i haven't really used infiniband to any extent
| [Saturday 15 January 2011] [21:13:56] <xchen>	A question about the basic concept of 0mq, is the source code I get built on tcpip?
| [Saturday 15 January 2011] [21:14:22] <mikko>	there are different transports 
| [Saturday 15 January 2011] [21:14:31] <xchen>	I get means download from the homepage
| [Saturday 15 January 2011] [21:14:31] <mikko>	ipc, inproc, tcp and pgm
| [Saturday 15 January 2011] [21:15:22] <xchen>	ok, so , tcp can build on infiniband, am I right?
| [Saturday 15 January 2011] [21:18:55] <mikko>	what does 'can build on' mean in this context?
| [Saturday 15 January 2011] [21:24:33] <xchen>	sorry, I sould say tcp can be built on infiniband
| [Saturday 15 January 2011] [21:24:46] <xchen>	sorry, I should say tcp can be built on infiniband
| [Saturday 15 January 2011] [21:25:32] <mikko>	it looks like you should be able to LD_PRELOAD the SDP library and use zeromq over infiniband
| [Saturday 15 January 2011] [21:25:54] <mikko>	i would assume that if the SDP library is loaded it would use infiniband and not the eth interface
| [Saturday 15 January 2011] [21:26:08] <mikko>	you should be able to see this from throughput of messages as well i assume 
| [Saturday 15 January 2011] [21:29:13] <mikko>	looking at the following material http://pkg-ofed.alioth.debian.org/howto/infiniband-howto-7.html it would look so
| [Saturday 15 January 2011] [21:35:10] <xchen>	Yeah, I think I get it. Thanks a lot.
| [Saturday 15 January 2011] [21:35:27] <mikko>	cool
| [Saturday 15 January 2011] [21:35:39] <mikko>	i need to sleep, it's 3am soon
| [Saturday 15 January 2011] [21:35:42] <mikko>	good night
| [Saturday 15 January 2011] [21:36:04] <xchen>	thank
| [Monday 17 January 2011] [00:18:11] <andrewvc>	cremes: around?
| [Monday 17 January 2011] [01:30:32] <yrashk>	hmm, after reinstalling osx I am getting absolutely reproducible Bad file descriptor nbytes != -1 (mailbox.cpp:241) 
| [Monday 17 January 2011] [01:30:34] <yrashk>	:-\
| [Monday 17 January 2011] [02:36:34] <sustrik_>	yrashk: please do report the bug
| [Monday 17 January 2011] [02:36:58] <yrashk>	I need to narrow the scope first
| [Monday 17 January 2011] [02:37:02] <yrashk>	but this is getting interesting
| [Monday 17 January 2011] [02:37:19] <sustrik_>	is that with shutdown_stress test?
| [Monday 17 January 2011] [02:37:26] <yrashk>	although I still hope it's my bug
| [Monday 17 January 2011] [02:37:28] <yrashk>	no
| [Monday 17 January 2011] [02:37:46] <sustrik_>	ok
| [Monday 17 January 2011] [05:33:17] <mikko>	howdy
| [Monday 17 January 2011] [05:46:31] <Evet>	fine
| [Monday 17 January 2011] [06:10:21] <ivan-korobkov>	Hello. I need to access a sub socket from another thread in Java. Is it enough to synchronize this method?
| [Monday 17 January 2011] [06:14:20] <mikko>	ivan-korobkov: not sure how java handles this
| [Monday 17 January 2011] [06:14:34] <mikko>	ivan-korobkov: i tend to use inproc pipe between the threads in such a scenario
| [Monday 17 January 2011] [06:16:07] <ivan-korobkov>	Ok, thanks.
| [Monday 17 January 2011] [06:55:30] <mikko>	mingw is being a pain
| [Monday 17 January 2011] [06:58:08] <mikko>	sustrik_: i pushed the new tests into a branch in github if you want to take a look
| [Monday 17 January 2011] [06:58:16] <mikko>	test_identity is failing atm
| [Monday 17 January 2011] [07:57:20] <lestrrat>	if you're specifying a char * buffer to zmq_msg_init_data(...), do you need to give it a zmq_free_fn ?
| [Monday 17 January 2011] [08:11:39] <Steve-o>	it takes a zero-copy reference, doesn't matter what the target is
| [Monday 17 January 2011] [08:15:56] <stimpie>	somebody knows an key value pair serialization library?
| [Monday 17 January 2011] [08:18:11] <Steve-o>	google protobufs
| [Monday 17 January 2011] [08:18:20] <Steve-o>	thrift
| [Monday 17 January 2011] [08:18:28] <Steve-o>	xdr
| [Monday 17 January 2011] [08:18:41] <Steve-o>	json, yaml, etc
| [Monday 17 January 2011] [08:22:23] <stimpie>	thanks for the pointers
| [Monday 17 January 2011] [08:23:07] <sustrik_>	lestrrat: free_fn is needed only when you pass your buffer to 0mq and you want it to deallocate it once it's sent
| [Monday 17 January 2011] [08:23:56] <lestrrat>	thanks steve, sustrik
| [Monday 17 January 2011] [08:26:04] <Evet>	oh, zeromq built by imatix?
| [Monday 17 January 2011] [08:28:41] <Steve-o>	Evet: they're trying to steer to full flossy project, like apache
| [Monday 17 January 2011] [08:29:32] <Evet>	i have learnt perl in xitami more than ten years ago
| [Monday 17 January 2011] [08:30:08] <Steve-o>	sustrik: guido_g:  any feedback on the pgm_receiver assert?
| [Monday 17 January 2011] [08:32:15] <sustrik_>	i haven't tried it myself
| [Monday 17 January 2011] [08:32:26] <sustrik_>	what about the patch you proposed?
| [Monday 17 January 2011] [08:32:31] <sustrik_>	(removing the timer)
| [Monday 17 January 2011] [08:32:45] <sustrik_>	it seems that it should be patched anyway, no?
| [Monday 17 January 2011] [08:34:48] <Steve-o>	looks like it
| [Monday 17 January 2011] [08:35:01] <sustrik_>	would you submit a patch?
| [Monday 17 January 2011] [08:35:10] <sustrik_>	or should I fix it?
| [Monday 17 January 2011] [08:35:19] <Steve-o>	there's one on the list replying to Guido
| [Monday 17 January 2011] [08:35:28] <sustrik_>	let me see
| [Monday 17 January 2011] [08:37:02] <sustrik_>	ok, got it
| [Monday 17 January 2011] [08:37:29] <sustrik_>	when sending a patch use [PATCH] in subject
| [Monday 17 January 2011] [08:37:43] <Steve-o>	I was waiting for Guido to catch it first
| [Monday 17 January 2011] [08:37:51] <sustrik_>	i see
| [Monday 17 January 2011] [08:38:11] <Steve-o>	I've only got my Sparc up in the office presently, I can't test too much
| [Monday 17 January 2011] [08:38:21] <sustrik_>	but this is something that should be done anyway, right?
| [Monday 17 January 2011] [08:38:32] <sustrik_>	irrespective whether it solves guido's problem or not
| [Monday 17 January 2011] [08:38:57] <Steve-o>	well it looks right
| [Monday 17 January 2011] [08:39:13] <Steve-o>	so go ahead
| [Monday 17 January 2011] [08:39:18] <sustrik_>	ok, let me apply it
| [Monday 17 January 2011] [08:39:42] <Steve-o>	for autoconf, waiting for any further feedback from mikko
| [Monday 17 January 2011] [08:40:15] <sustrik_>	ack
| [Monday 17 January 2011] [08:42:06] <Steve-o>	I'm sure the devs using OSX will shout soon enough as master should be broken for them currently
| [Monday 17 January 2011] [08:42:27] <mikko>	Steve-o: i will start testing today
| [Monday 17 January 2011] [08:42:48] <mikko>	had suprisingly busy weekend
| [Monday 17 January 2011] [08:43:34] <mikko>	what is the current view regarding openpgm and zeromq?
| [Monday 17 January 2011] [08:43:42] <Steve-o>	no worries, I'm mid buying a house
| [Monday 17 January 2011] [08:43:55] <mikko>	do we bundle a version with zeromq2 and allow people to specify directory as well?
| [Monday 17 January 2011] [08:44:10] <Steve-o>	sounds good
| [Monday 17 January 2011] [08:44:31] <Steve-o>	I actually have autoconf making a shared library, but not really recommended
| [Monday 17 January 2011] [08:44:42] <mikko>	so by default the value of --with-pgm is foreign/...
| [Monday 17 January 2011] [08:44:44] <Steve-o>	came free with libtool I think :D
| [Monday 17 January 2011] [08:44:54] <mikko>	but you can specify --with-pgm=/opt/xyz
| [Monday 17 January 2011] [08:45:03] <mikko>	does that sound like a sensible approach?
| [Monday 17 January 2011] [08:45:20] <Steve-o>	sounds good, then distros can choose their packaging preference
| [Monday 17 January 2011] [08:45:44] <mikko>	yeah, distros don't like static linking between two projects they package
| [Monday 17 January 2011] [08:46:15] <CIA-21>	zeromq2: 03Steven McCoy 07master * r667b247 10/ src/pgm_receiver.cpp : 
| [Monday 17 January 2011] [08:46:15] <CIA-21>	zeromq2: Cancel pending timers when decoder for PGM stalls
| [Monday 17 January 2011] [08:46:15] <CIA-21>	zeromq2: Otherwise the timer event can raise an input event
| [Monday 17 January 2011] [08:46:15] <CIA-21>	zeromq2: causing assertion on unprocessed data.
| [Monday 17 January 2011] [08:46:15] <CIA-21>	zeromq2: Signed-off-by: Steven McCoy <steven.mccoy@miru.hk> - http://bit.ly/eJNCcf
| [Monday 17 January 2011] [08:47:11] <Steve-o>	once I start to see packages created I can copy the build script and then zeromq can be split up
| [Monday 17 January 2011] [08:48:29] <Steve-o>	The only future work I see is on FEC unless some University project picks up congestion control
| [Monday 17 January 2011] [08:49:18] <Steve-o>	the congestion protocol is broken above 10,000 packets-per-second
| [Monday 17 January 2011] [08:49:28] <guido_g>	Steve-o: i used a very high HWM on the subscriber as proposed and it worked
| [Monday 17 January 2011] [08:50:55] <Steve-o>	great, otherwise you would get application induced dataloss
| [Monday 17 January 2011] [08:51:37] <CIA-21>	zeromq2: 03Martin Sustrik 07master * rb262f2f 10/ doc/zmq_send.txt : 
| [Monday 17 January 2011] [08:51:37] <CIA-21>	zeromq2: Typo fixed in zmq_send(3) man page.
| [Monday 17 January 2011] [08:51:37] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/g9l7cN
| [Monday 17 January 2011] [08:52:14] <Steve-o>	definitely need to work on some feedback for admins around that issue in the future
| [Monday 17 January 2011] [08:53:04] <Steve-o>	but then that's the logging system which is rather awkward 
| [Monday 17 January 2011] [09:11:57] <sustrik_>	funny video here btw
| [Monday 17 January 2011] [09:11:58] <sustrik_>	http://cfkarsten.blip.tv/file/4639616
| [Monday 17 January 2011] [09:12:15] <sustrik_>	using 0mq to create a cloud of 1978 vintage computers :)
| [Monday 17 January 2011] [09:17:33] <stimpie>	Iam doing some performanc benchmarks (with the provided perf code)  on 1000G ethernet I get 936 Mb/s on infiband (32 Gb/s) this only goes up to 2070 Mb/s
| [Monday 17 January 2011] [09:17:58] <stimpie>	is this an expected resulted or should this be higher?
| [Monday 17 January 2011] [09:25:27] <sustrik_>	stimpie: what's your message size?
| [Monday 17 January 2011] [09:27:23] <sustrik_>	there are some test results here: http://www.zeromq.org/results:ib-tests-v206
| [Monday 17 January 2011] [09:28:32] <stimpie>	message size used is 100 bytes
| [Monday 17 January 2011] [09:29:23] <stimpie>	my result is similar to those in your link
| [Monday 17 January 2011] [09:29:53] <sustrik_>	yes, looks like
| [Monday 17 January 2011] [11:55:51] <Guest10403>	Hi There,  I am just beginning to use ZeroMQ and am experimenting with some of the samples.  I am using the C# language bindings and have run into an issue with getting a DllNotFound Exception
| [Monday 17 January 2011] [11:56:05] <Guest10403>	Has anyone else run into this issue?
| [Monday 17 January 2011] [11:56:31] <mikko>	Guest10403: dll not found sounds like the libzmq.dll can not be found
| [Monday 17 January 2011] [11:56:41] <mikko>	is it in a path where the loader can find it?
| [Monday 17 January 2011] [11:57:09] <Guest10403>	I can Load on My development machine, but when I move things to other servers, I get the error despite copying the libzmq.dll into both the folder the samples are running from and into Windows/System32
| [Monday 17 January 2011] [11:57:20] <Guest10403>	Hi Mikko
| [Monday 17 January 2011] [11:57:25] <Guest10403>	Thanks for your response
| [Monday 17 January 2011] [11:57:36] <Guest10403>	Windows should be able to find it, but does not seem to be able to
| [Monday 17 January 2011] [11:58:40] <mikko>	hmm
| [Monday 17 January 2011] [11:58:46] <mikko>	not an ACL issue?
| [Monday 17 January 2011] [11:59:51] <Guest10403>	I have put clzmq.dll into the Folder the sample app is in and also libzmq.dll  Also, i put libzmq into c:\Windows/System32
| [Monday 17 January 2011] [12:00:06] <Guest10403>	I don't understand your question ACL?
| [Monday 17 January 2011] [12:00:19] <Guest10403>	What does ACL stand for?
| [Monday 17 January 2011] [12:00:25] <mikko>	i mean file permissions on either one of the dll diles
| [Monday 17 January 2011] [12:00:28] <mikko>	files*
| [Monday 17 January 2011] [12:00:33] <mikko>	acl = access control list
| [Monday 17 January 2011] [12:00:41] <Guest10403>	Good question
| [Monday 17 January 2011] [12:01:07] <Guest10403>	It should not be that sort of issue, the user I am running as on the server has administrative rights
| [Monday 17 January 2011] [12:01:16] <Guest10403>	I'll check again
| [Monday 17 January 2011] [12:02:45] <Guest10403>	I have admin rights and am Running on Windows Server 2003 Service pack2
| [Monday 17 January 2011] [12:03:25] <mikko>	maybe send an email to mailing-lists 
| [Monday 17 January 2011] [12:03:35] <mikko>	i dont really run windows anywhere so i cant help much
| [Monday 17 January 2011] [12:04:05] <Guest10403>	Thanks for the suggestion
| [Monday 17 January 2011] [18:05:13] <mikko>	lestrrat: looks like perl build is failing for some reason
| [Monday 17 January 2011] [18:06:53] <lestrrat>	whoa
| [Monday 17 January 2011] [18:08:24] <lestrrat>	it says build timed out
| [Monday 17 January 2011] [18:08:31] <lestrrat>	does hudson have a timeout for tests?
| [Monday 17 January 2011] [18:26:52] <mikko>	lestrrat: yes
| [Monday 17 January 2011] [18:26:56] <mikko>	lestrrat: it will eventually time out
| [Monday 17 January 2011] [18:26:58] <lestrrat>	what's the timeout?
| [Monday 17 January 2011] [18:27:01] <mikko>	let me check
| [Monday 17 January 2011] [18:27:14] <mikko>	five minutes
| [Monday 17 January 2011] [18:27:18] <mikko>	is that enough for the build?
| [Monday 17 January 2011] [18:27:18] <lestrrat>	hmmm
| [Monday 17 January 2011] [18:27:26] <lestrrat>	should be
| [Monday 17 January 2011] [18:27:41] <lestrrat>	I added new tests that take up some time, but I'm pretty sure it doesn't go over 5 minutes. odd
| [Monday 17 January 2011] [18:27:43] <mikko>	looking at the trends the time is normally around <2min
| [Monday 17 January 2011] [18:28:02] <lestrrat>	I'll make the tests shorter for now, and see what happens
| [Monday 17 January 2011] [18:28:18] <mikko>	i can increase the build timeout as well
| [Monday 17 January 2011] [18:28:25] <mikko>	just to see if it passes with more time
| [Monday 17 January 2011] [18:28:49] <lestrrat>	well, let me change this first, and if it still doesn't work, I might ask you to change the timeout
| [Monday 17 January 2011] [18:29:25] <mikko>	http://build.valokuva.org/job/ZeroMQPerl-master_ZeroMQ2-master_GCC/buildTimeTrend
| [Monday 17 January 2011] [18:29:31] <mikko>	you can see build time trend from there
| [Monday 17 January 2011] [18:29:58] <lestrrat>	oh man. didn't know about that in hudson. that's nice :)
| [Monday 17 January 2011] [18:30:18] <mikko>	all kind of cool toys in hudson
| [Monday 17 January 2011] [18:30:24] <mikko>	like the static analysis plugins: http://build.valokuva.org/job/ZeroMQ2-core-master_static-analysis/
| [Monday 17 January 2011] [18:34:02] <lestrrat>	well, as of my latest commit, the test should run in about 12 seconds :/
| [Monday 17 January 2011] [18:34:42] <lestrrat>	so if the hudson runs were taking on average 1 min+, presumably most of that time is spent checking out git
| [Monday 17 January 2011] [18:37:49] <lestrrat>	well let's see what the next run brings up
| [Monday 17 January 2011] [18:39:30] <mikko>	pass
| [Monday 17 January 2011] [18:39:43] <lestrrat>	so soon? lol
| [Monday 17 January 2011] [18:39:45] <lestrrat>	thanks!
| [Monday 17 January 2011] [18:39:53] <mikko>	it will run quicker when there is no load
| [Monday 17 January 2011] [18:40:02] <mikko>	usually the build runs alongside with 4 other builds
| [Monday 17 January 2011] [18:40:05] <mikko>	so it takes longer
| [Monday 17 January 2011] [19:30:04] <traviscline>	i'm investigating getting the pyzmq polling integrated into gevent (cython wrapping of libevent) and wanted to ask if anyone had any 'to-reads' other than the eventlet implementation
| [Monday 17 January 2011] [19:31:59] <mikko>	i think there was someone here who was integrating with gevent
| [Monday 17 January 2011] [19:32:05] <mikko>	the process is very simple
| [Monday 17 January 2011] [19:32:18] <mikko>	i can walk you through it if you like?
| [Monday 17 January 2011] [19:34:42] <traviscline>	mikko: yeah if you have any input that'd be great
| [Monday 17 January 2011] [19:35:08] <mikko>	so, first you need zeromq 2.1.x
| [Monday 17 January 2011] [19:35:12] <traviscline>	rgr
| [Monday 17 January 2011] [19:35:22] <mikko>	what you need to do roughly is:
| [Monday 17 January 2011] [19:35:35] <mikko>	you create a zmq socket and connect/bind it 
| [Monday 17 January 2011] [19:35:51] <mikko>	you call getsockopt ZMQ_FD on the socket to get a filehandle 
| [Monday 17 January 2011] [19:36:03] <mikko>	then you add gevent io watcher on that filehandle 
| [Monday 17 January 2011] [19:36:18] <mikko>	and your callback should be signaled when the socket is readable/writable 
| [Monday 17 January 2011] [19:36:50] <traviscline>	http://www.mail-archive.com/zeromq-dev@lists.zeromq.org/msg00030.html that list posting discouraged me from taking that path
| [Monday 17 January 2011] [19:36:55] <traviscline>	but thanks, I'll give that a go
| [Monday 17 January 2011] [19:37:36] <mikko>	zeromq doesnt support io completion ports
| [Monday 17 January 2011] [19:37:38] <mikko>	that is true
| [Monday 17 January 2011] [19:38:38] <traviscline>	mikko: shit sorry, meant this http://www.mail-archive.com/zeromq-dev@lists.zeromq.org/msg06253.html
| [Monday 17 January 2011] [19:39:29] <mikko>	he is probably missing a fact that zeromq is edge-triggered
| [Monday 17 January 2011] [19:39:48] <mikko>	so when gevent signals that socket is readable you need to read until you get EAGAIN
| [Monday 17 January 2011] [19:40:11] <mikko>	so do nonblocking recv in a loop (in the callback) and break out from loop when you get EAGAIN from recv
| [Monday 17 January 2011] [19:40:55] <mikko>	edge-triggered means that the callback gets called on state changes, not necessarily on every new message
| [Monday 17 January 2011] [19:43:22] <traviscline>	*nods*
| [Monday 17 January 2011] [19:45:01] <traviscline>	mikko: !! thanks
| [Monday 17 January 2011] [19:45:03] <traviscline>	works
| [Monday 17 January 2011] [19:48:41] <mikko>	cool
| [Monday 17 January 2011] [19:51:39] <traviscline>	mikko: straight port as of now https://gist.github.com/783810 of eventlet's stuff
| [Monday 17 January 2011] [19:51:42] <traviscline>	but works
| [Monday 17 January 2011] [19:51:47] <traviscline>	on initial testing