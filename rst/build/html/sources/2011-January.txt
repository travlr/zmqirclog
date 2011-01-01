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