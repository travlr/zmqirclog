===============
2011-March
===============

| [Saturday 12 March 2011] [09:10:25] <pieterh>	it was written for 2.0 to be precise
| [Saturday 12 March 2011] [09:10:43] <pieterh>	I flatly disagree that it did not apply, does not *now* apply to 2.1
| [Saturday 12 March 2011] [09:10:48] <pieterh>	that is completely wrong
| [Saturday 12 March 2011] [09:11:00] <sustrik>	i recall explicitly addressing 2.1 compatibility issues when writing it
| [Saturday 12 March 2011] [09:11:12] <pieterh>	We wrote it in August
| [Saturday 12 March 2011] [09:11:29] <pieterh>	your memory is ... curious
| [Saturday 12 March 2011] [09:11:36] <sustrik>	ah, yes, i think thr 2.1 work started back then
| [Saturday 12 March 2011] [09:11:36] <pieterh>	Check the history
| [Saturday 12 March 2011] [09:11:51] <sustrik>	remember the great heats in BTS?
| [Saturday 12 March 2011] [09:12:12] <pieterh>	please, sustrik, check the dates when you introduced the zmq_term blocking
| [Saturday 12 March 2011] [09:12:24] <pieterh>	anyhow, this is irrelevant
| [Saturday 12 March 2011] [09:12:34] <sustrik>	yes, it was at the same time
| [Saturday 12 March 2011] [09:12:35] <pieterh>	you have a release policy and we are about to release a stable 2.1
| [Saturday 12 March 2011] [09:12:41] <pieterh>	which breaks the release policy
| [Saturday 12 March 2011] [09:12:51] <pieterh>	I'm formally against that
| [Saturday 12 March 2011] [09:12:58] <pieterh>	and formally asking you to respect the documented policy
| [Saturday 12 March 2011] [09:13:05] <sustrik>	i am against repeated breaking of API
| [Saturday 12 March 2011] [09:13:13] <sustrik>	2.1.1->2.1.2
| [Saturday 12 March 2011] [09:13:13] <pieterh>	the API includes the semantics of zmq_term
| [Saturday 12 March 2011] [09:13:39] <sustrik>	well, let's do a poll then
| [Saturday 12 March 2011] [09:13:46] <pieterh>	blocking or non-blocking?
| [Saturday 12 March 2011] [09:13:59] <pieterh>	yes, let's do a poll
| [Saturday 12 March 2011] [09:14:05] <sustrik>	default linger of 0 vs. infinite
| [Saturday 12 March 2011] [09:14:08] <pieterh>	indeed
| [Saturday 12 March 2011] [09:14:44] <pieterh>	note, you can add zmq_term_blocking () which does infinite blocking with a timeout
| [Saturday 12 March 2011] [09:15:02] <sustrik>	sure, but that's not the point
| [Saturday 12 March 2011] [09:15:06] <pieterh>	yes it is
| [Saturday 12 March 2011] [09:15:13] <pieterh>	if people absolutely need the semantics, they are present
| [Saturday 12 March 2011] [09:15:23] <sustrik>	we are discussing backward comaptibility not new apis
| [Saturday 12 March 2011] [09:15:27] <pieterh>	ok, setting LINGER gives the same results
| [Saturday 12 March 2011] [09:15:29] <sustrik>	anyway, let's ask people
| [Saturday 12 March 2011] [09:15:37] <yrashk>	I vote for keeping it as is
| [Saturday 12 March 2011] [09:15:39] <yrashk>	:)
| [Saturday 12 March 2011] [09:15:44] <yrashk>	if anybody's interested :)
| [Saturday 12 March 2011] [09:15:50] <sustrik>	i am against :)
| [Saturday 12 March 2011] [09:15:52] <pieterh>	yrashk: 'as is' depends where you are today
| [Saturday 12 March 2011] [09:15:56] <yrashk>	master
| [Saturday 12 March 2011] [09:15:57] <sustrik>	let me ask on ml
| [Saturday 12 March 2011] [09:16:07] <pieterh>	could you please be specific: infinite blocking, or not
| [Saturday 12 March 2011] [09:16:11] <yrashk>	infinite
| [Saturday 12 March 2011] [09:16:11] <sustrik>	yes
| [Saturday 12 March 2011] [09:16:33] <sustrik>	there are two sides to the problem
| [Saturday 12 March 2011] [09:16:42] <sustrik>	i'll try to explain on the ml
| [Saturday 12 March 2011] [09:17:06] <pieterh>	sustrik: please, do point out this is for the stable 2.1 to be released shortly
| [Saturday 12 March 2011] [09:17:19] <pieterh>	and do explain that infinite blocking means all existing apps are likely to break
| [Saturday 12 March 2011] [09:17:25] <pieterh>	when they migrate from 2.0 to 2.1
| [Saturday 12 March 2011] [09:17:27] <sustrik>	2.0 apps
| [Saturday 12 March 2011] [09:17:35] <sustrik>	in the opposite case
| [Saturday 12 March 2011] [09:17:42] <sustrik>	the 2.1 apps are going to break
| [Saturday 12 March 2011] [09:17:48] <sustrik>	i'll explain that
| [Saturday 12 March 2011] [09:17:56] <pieterh>	all the ones that don't explicitly set LINGER to zero, which is loads and loads
| [Saturday 12 March 2011] [09:18:09] <pieterh>	(loads and loads take the effort to set LINGER to zero)
| [Saturday 12 March 2011] [09:18:54] <pieterh>	yes, a poll will be interesting...
| [Saturday 12 March 2011] [09:19:26] <pieterh>	BTW there's a line in the Release Policies page I am going to remove
| [Saturday 12 March 2011] [09:19:32] <pieterh>	"In general we have a stable and an unstable releases of the product, e.g. 2.0.x and 2.1.x"
| [Saturday 12 March 2011] [09:19:36] <pieterh>	that is just wrong
| [Saturday 12 March 2011] [09:21:22] <pieterh>	bleh, the contract is vague for minor releases
| [Saturday 12 March 2011] [09:21:29] <pieterh>	"It may even run"
| [Saturday 12 March 2011] [09:21:38] <pieterh>	some lawyer has been editing that page...
| [Saturday 12 March 2011] [09:30:06] <Guthur>	is the reactor pattern still ear marked for 3.0
| [Saturday 12 March 2011] [09:30:48] <Guthur>	just thinking that if it was to replace Poll it might be a good opportunity to work IOCP into the windows version
| [Saturday 12 March 2011] [09:31:39] <Guthur>	which would obviously immediately open up IPC
| [Saturday 12 March 2011] [09:32:06] <pieterh>	Guthur: I don't think that's on the 3.0 roadmap
| [Saturday 12 March 2011] [09:32:38] <Guthur>	it is according to the website
| [Saturday 12 March 2011] [09:32:52] <Guthur>	http://www.zeromq.org/docs:3-0#toc3
| [Saturday 12 March 2011] [09:33:19] <Guthur>	it does say replacing OR supplementing though
| [Saturday 12 March 2011] [09:33:23] <pieterh>	indeed, but I don't think it's on the roadmap
| [Saturday 12 March 2011] [09:33:44] <Guthur>	ok, is there a more up to date doc
| [Saturday 12 March 2011] [09:34:34] <pieterh>	sorry to be unhelpful but the only accurate doc is the NEWS when a feature's been released
| [Saturday 12 March 2011] [09:34:43] <pieterh>	and then the man page...
| [Saturday 12 March 2011] [10:29:07] <zedas>	pieterh: or write a book :-)
| [Saturday 12 March 2011] [10:29:26] <pieterh>	:-) yeah, that's always a good option
| [Saturday 12 March 2011] [10:31:14] <sustrik>	3.0 road map is out of date
| [Saturday 12 March 2011] [10:31:24] <sustrik>	:(
| [Saturday 12 March 2011] [10:32:11] <sustrik>	i would rather use the page to collect the API changes
| [Saturday 12 March 2011] [10:32:25] <pieterh>	sustrik: ctrl-e (stuff) ctrl-s
| [Saturday 12 March 2011] [10:32:34] <sustrik>	new features, otoh, will anyway be only those that people contribute
| [Saturday 12 March 2011] [10:32:55] <sustrik>	right
| [Saturday 12 March 2011] [10:36:32] <Skaag>	sustrik: you heard about Sector and UDT?
| [Saturday 12 March 2011] [10:36:48] <sustrik>	i know UDT
| [Saturday 12 March 2011] [10:36:56] <sustrik>	don't know about Sector
| [Saturday 12 March 2011] [10:37:04] <Skaag>	that's the funny thing
| [Saturday 12 March 2011] [10:37:12] <Skaag>	I thought about implementing a filesystem based on ZMQ
| [Saturday 12 March 2011] [10:37:22] <Skaag>	and while looking for prior work, I found Sector...
| [Saturday 12 March 2011] [10:37:24] <Skaag>	http://sector.sourceforge.net/
| [Saturday 12 March 2011] [10:37:34] <Skaag>	I'm currently installing it and about to try it out
| [Saturday 12 March 2011] [10:37:42] <Skaag>	on paper, it looks very interesting
| [Saturday 12 March 2011] [10:38:16] <sustrik>	there are several distributed databases out there
| [Saturday 12 March 2011] [10:38:25] <sustrik>	i am not an expert in the topic though
| [Saturday 12 March 2011] [10:38:30] <Skaag>	this one offers a fuse client which makes it interesting
| [Saturday 12 March 2011] [10:38:43] <Skaag>	the reason I mentioned it is UDT actually
| [Saturday 12 March 2011] [10:39:31] <sustrik>	like in "uses UDT" fro communication between nodes, right?
| [Saturday 12 March 2011] [10:39:36] <Skaag>	yes
| [Saturday 12 March 2011] [10:39:46] <sustrik>	nice
| [Saturday 12 March 2011] [10:40:03] <sustrik>	could work well for large-scale synchronisations over a WAN
| [Saturday 12 March 2011] [10:40:12] <Skaag>	that's what I need to establish now
| [Saturday 12 March 2011] [10:40:50] <Skaag>	I have at the moment machines in 7 ~ 8 different data centers
| [Saturday 12 March 2011] [10:41:02] <Skaag>	by the way, zmq is working wonders for us
| [Saturday 12 March 2011] [10:41:17] <Skaag>	we are graphing in real-time the data from 20+ nodes
| [Saturday 12 March 2011] [10:41:46] <Skaag>	without the illnesses we were experiencing while using rabbitmq
| [Saturday 12 March 2011] [10:43:43] <pieterh>	Skaag: we'd welcome a short story that we could publish on the wiki...
| [Saturday 12 March 2011] [10:43:54] <pieterh>	about your experiences in moving to 0MQ
| [Saturday 12 March 2011] [10:43:54] <Skaag>	ok
| [Saturday 12 March 2011] [10:44:30] <sustrik>	Skaag: what's the project?
| [Saturday 12 March 2011] [10:45:00] <Skaag>	it's a control panel for a CDN
| [Saturday 12 March 2011] [10:45:08] <sustrik>	is there a link?
| [Saturday 12 March 2011] [10:45:26] <Skaag>	I'm still making the site for it :-\
| [Saturday 12 March 2011] [10:45:32] <sustrik>	i see
| [Saturday 12 March 2011] [10:45:52] <sustrik>	when you have it, share the link
| [Saturday 12 March 2011] [10:45:58] <Skaag>	 will do
| [Saturday 12 March 2011] [10:45:59] <sustrik>	it would be interesting to have a look
| [Saturday 12 March 2011] [11:17:22] <CIA-103>	zeromq2: 03Guido Goldstein 07master * rd0c8edd 10/ include/zmq.hpp : 
| [Saturday 12 March 2011] [11:17:22] <CIA-103>	zeromq2: Added missing close method w/ check if socket is already closed.
| [Saturday 12 March 2011] [11:17:22] <CIA-103>	zeromq2: Signed-off-by: Guido Goldstein <github@a-nugget.de> - http://bit.ly/ggZZI6
| [Saturday 12 March 2011] [11:37:29] <dermoth|home>	I just fixed the cia auto-voice in chanserv...
| [Saturday 12 March 2011] [12:04:00] <guido_g>	sustrik: thx for mentioning the sign-off thingie
| [Saturday 12 March 2011] [12:04:41] <guido_g>	didn't move the .gitconfig to the new machine
| [Saturday 12 March 2011] [17:48:28] <nadime>	any zmq gurus around to help me figure out a performance bottleneck issue?
| [Saturday 12 March 2011] [17:49:07] <nadime>	i think it's kind of interesting!
| [Saturday 12 March 2011] [17:53:56] <mikko>	nadime: what's the issue?
| [Saturday 12 March 2011] [17:54:06] <nadime>	i have the following setup
| [Saturday 12 March 2011] [17:54:52] <nadime>	push socket fans out from a thread into N (defaults to 4) IO threads using push/pull to distribute the work to the io threads
| [Saturday 12 March 2011] [17:55:04] <nadime>	the io threads then talk 1 to 1 with N io threads on a client
| [Saturday 12 March 2011] [17:55:18] <nadime>	the io threads use pub/sub since it's 1 to 1
| [Saturday 12 March 2011] [17:55:36] <nadime>	each io thread has 1 zmq io thread
| [Saturday 12 March 2011] [17:55:40] <nadime>	and i set affinities
| [Saturday 12 March 2011] [17:55:45] <nadime>	to make it as quick as possible
| [Saturday 12 March 2011] [17:55:50] <nadime>	the issue i'm having
| [Saturday 12 March 2011] [17:56:03] <nadime>	is that i see about 500k msgs/sec go into my push socket
| [Saturday 12 March 2011] [17:56:09] <nadime>	but i fall way behind on my 4 io sockets
| [Saturday 12 March 2011] [17:56:25] <nadime>	sorry the io sockets are tcp
| [Saturday 12 March 2011] [17:56:49] <nadime>	so i didn't expec tthem to keep up, but i figured with 4 and a pretty solid machine (12 cores, about 1 thread per core)
| [Saturday 12 March 2011] [17:56:59] <nadime>	they'd be ok
| [Saturday 12 March 2011] [17:57:06] <mikko>	are they tcp over local loopback?
| [Saturday 12 March 2011] [17:57:10] <mikko>	or over network?
| [Saturday 12 March 2011] [17:57:15] <nadime>	local 1 GB network
| [Saturday 12 March 2011] [17:57:29] <mikko>	what is your message size?
| [Saturday 12 March 2011] [17:57:37] <nadime>	avg prolly 50b
| [Saturday 12 March 2011] [17:57:47] <nadime>	sorry B
| [Saturday 12 March 2011] [17:57:48] <nadime>	bytes
| [Saturday 12 March 2011] [17:59:18] <mikko>	so, 50b messages x 500k would be roughly 238 megabytes per second
| [Saturday 12 March 2011] [17:59:38] <nadime>	yeah but i fall WAY behind
| [Saturday 12 March 2011] [17:59:49] <nadime>	like the io threads barely do 80kmsg/s
| [Saturday 12 March 2011] [17:59:53] <mikko>	one gigabit per second is 128 megabytes per second
| [Saturday 12 March 2011] [18:00:50] <nadime>	50b is probably wrong, i don't see anywhere near full bandwidth utilization
| [Saturday 12 March 2011] [18:01:30] <nadime>	the point though is that what the io threads do is nowhere near even 20% capacity
| [Saturday 12 March 2011] [18:02:32] <mikko>	are you seeing high utilisation anywhere?
| [Saturday 12 March 2011] [18:02:37] <mikko>	or just falling rates?
| [Saturday 12 March 2011] [18:03:21] <nadime>	no high network utilization usually around 15%
| [Saturday 12 March 2011] [18:03:44] <mikko>	what os is this?
| [Saturday 12 March 2011] [18:03:49] <nadime>	win7
| [Saturday 12 March 2011] [18:03:53] <nadime>	64b
| [Saturday 12 March 2011] [18:04:03] <mikko>	hmm, can't help you much there
| [Saturday 12 March 2011] [18:04:14] <mikko>	i have got very little experience with windows and performance
| [Saturday 12 March 2011] [18:04:20] <nadime>	i'm not missing anything though in terms of things you'd do with zmq?
| [Saturday 12 March 2011] [18:05:17] <mikko>	sounds ok
| [Saturday 12 March 2011] [18:05:25] <mikko>	i would maybe use zmq_pair socket for 1:1
| [Saturday 12 March 2011] [18:05:34] <nadime>	k, i can try that
| [Saturday 12 March 2011] [18:05:46] <nadime>	is the push/pull fair queuing slow?
| [Saturday 12 March 2011] [18:05:57] <mikko>	shouldn't be
| [Saturday 12 March 2011] [18:06:03] <nadime>	k
| [Saturday 12 March 2011] [18:06:03] <mikko>	it's very simple algorithm
| [Saturday 12 March 2011] [18:06:18] <nadime>	i would think
| [Saturday 12 March 2011] [18:06:29] <mikko>	if you have a profiler available that might help
| [Saturday 12 March 2011] [18:06:35] <mikko>	to see where time is spent
| [Saturday 12 March 2011] [18:06:35] <nadime>	yeah i do
| [Saturday 12 March 2011] [18:06:38] <nadime>	i will use it
| [Saturday 12 March 2011] [18:06:58] <nadime>	i just thught i might be missing something obvious that would help
| [Saturday 12 March 2011] [18:08:48] <mikko>	so, do i understand your architecture correctly:
| [Saturday 12 March 2011] [18:09:03] <mikko>	you have push/pull socket, which balances work to four threads
| [Saturday 12 March 2011] [18:09:24] <mikko>	each one of the threads has pub socket which publishes messages over tcp to workers
| [Saturday 12 March 2011] [18:09:27] <mikko>	?
| [Saturday 12 March 2011] [18:14:48] <mikko>	i gotta head to bed
| [Saturday 12 March 2011] [18:15:19] <mikko>	nadime: the channel is usually more lively during the day time in europe (large amount of devs from eu)
| [Saturday 12 March 2011] [18:39:20] <cremes>	nadime: i have a few suggestions for things to look at
| [Saturday 12 March 2011] [18:39:52] <cremes>	1. if your PUSH socket is in the same process as your "io thread PULL sockets" you should be using inproc transport instead of tcp
| [Saturday 12 March 2011] [18:40:16] <cremes>	2. take a look at your message serialization; sometimes deserialization is more costly than serialization
| [Saturday 12 March 2011] [18:40:38] <cremes>	however, i assume you are sending packed structures so you are probably just casting a pointer to get to your data
| [Saturday 12 March 2011] [18:41:21] <cremes>	3. instrument your messages so that you can measure how many nano/micro/milliseconds it takes for the PUSH to deliver to the PULL socket
| [Saturday 12 March 2011] [18:42:14] <cremes>	4. instrument the messages that go from the "server io threads" to the "client io threads" via PUB/SUB to measure latency
| [Saturday 12 March 2011] [19:04:32] <nadime>	i am using inproc for anything local, cremes
| [Saturday 12 March 2011] [19:04:42] <nadime>	the only thing i use tcp for is external
| [Saturday 12 March 2011] [19:05:41] <nadime>	thanks for the suggestions, re: instrumentation
| [Saturday 12 March 2011] [19:06:13] <nadime>	oh incidentally, mikko, we were doing the math wrong.  50B x 500k = 25MB/s
| [Saturday 12 March 2011] [19:06:19] <nadime>	which makes much more sense
| [Saturday 12 March 2011] [19:06:28] <nadime>	since i'm seeing 10% utilization
| [Saturday 12 March 2011] [19:06:30] <nadime>	10-15
| [Saturday 12 March 2011] [20:03:04] <Guest51726>	hello, anyone awake tonight ?
| [Saturday 12 March 2011] [20:04:56] <Evet_>	:)
| [Saturday 12 March 2011] [20:17:03] <Guest51726>	Hello Evet, how are you ?
| [Saturday 12 March 2011] [20:17:21] <Evet>	fine, Guest51726. you?
| [Saturday 12 March 2011] [20:18:48] <Guest51726>	not so bad !
| [Saturday 12 March 2011] [20:19:12] <Guest51726>	I was doing some experimenting with 0MQ, 2.1.2 the other day - tell me, is the load balancing stable ?
| [Saturday 12 March 2011] [20:26:33] <Guest51726>	Yep.
| [Saturday 12 March 2011] [20:41:06] <Evet>	Guest51726: i think so
| [Saturday 12 March 2011] [20:41:49] <Guest51726>	hmmm...that wasn't what I was seeing :(
| [Saturday 12 March 2011] [21:04:25] <emacsen>	I have a, hopefully basic question:   I'm learning zeromq. I only have my laptop and I'm trying to test push and pull requests. I heard that pull requests will be balanced across pullers. But I'm testing with ipc and all the requests go to one listener. Is that because of ipc?
| [Saturday 12 March 2011] [21:05:01] <Guest51726>	thats a good question:  I don't know.
| [Saturday 12 March 2011] [21:05:51] <Guest51726>	the requests really should be balanced across pullers, regardless of the transport.  However I have observed uneven load balancing myself.
| [Sunday 13 March 2011] [01:19:07] <guido_g>	hello world!
| [Sunday 13 March 2011] [01:34:28] <pieterh>	hey guido_g, hi!
| [Sunday 13 March 2011] [01:34:38] <guido_g>	morning pieterh 
| [Sunday 13 March 2011] [01:35:10] <pieterh>	another day, another little protocol spec :-)
| [Sunday 13 March 2011] [01:35:12] <guido_g>	just pulled the zeromq2-1 changes and compiled
| [Sunday 13 March 2011] [01:35:19] <guido_g>	ohh...
| [Sunday 13 March 2011] [01:35:50] <guido_g>	spec:10
| [Sunday 13 March 2011] [01:36:00] <pieterh>	yeah, brokerless reliability
| [Sunday 13 March 2011] [01:36:12] <pieterh>	final part of chapter 4... finally... :-)
| [Sunday 13 March 2011] [01:36:18] <guido_g>	yes!
| [Sunday 13 March 2011] [01:36:19] <guido_g>	:)
| [Sunday 13 March 2011] [01:37:03] <pieterh>	for 2.1 I defined ZMQ_DEALER and ZMQ_ROUTER as aliases
| [Sunday 13 March 2011] [01:37:19] <guido_g>	seen it
| [Sunday 13 March 2011] [01:37:30] <guido_g>	good move imho
| [Sunday 13 March 2011] [01:38:08] <pieterh>	I'm going to change the man pages, leave the old names as deprecated
| [Sunday 13 March 2011] [01:38:18] <pieterh>	this will make it easier for people to move to 3.0
| [Sunday 13 March 2011] [01:38:53] <guido_g>	ok
| [Sunday 13 March 2011] [01:39:06] <guido_g>	from spec10: "From the MQ Reference Manual[Bibliography item zmqsocket not found.]:"
| [Sunday 13 March 2011] [01:39:18] <guido_g>	seems that a link can't be resolved
| [Sunday 13 March 2011] [01:39:37] <pieterh>	just fixed that, thanks
| [Sunday 13 March 2011] [01:39:53] <guido_g>	ahh
| [Sunday 13 March 2011] [01:40:08] <guido_g>	reload did it
| [Sunday 13 March 2011] [01:40:35] <pieterh>	I figured out how to do router-to-router connections between clients and servers
| [Sunday 13 March 2011] [01:40:41] <guido_g>	great
| [Sunday 13 March 2011] [01:40:54] <guido_g>	will be fun to read
| [Sunday 13 March 2011] [01:40:56] <pieterh>	it's rather fun because neither side can talk to the other without knowing their identity first
| [Sunday 13 March 2011] [01:41:28] <guido_g>	using ahh... router sockets
| [Sunday 13 March 2011] [01:41:59] <guido_g>	need to get used to the new name
| [Sunday 13 March 2011] [01:42:10] <pieterh>	:-)
| [Sunday 13 March 2011] [01:43:39] <guido_g>	example program adjusted
| [Sunday 13 March 2011] [06:47:53] <Guthur>	pieterh, Ch4 is turning into a bit of a monster
| [Sunday 13 March 2011] [06:48:30] <Guthur>	good stuff though
| [Sunday 13 March 2011] [06:49:29] <Guthur>	After sorting out my POSIX issues, and fix a bug I found during the process, I'm now ready to finish ch3
| [Sunday 13 March 2011] [06:49:37] <Guthur>	looking forward to ch4
| [Sunday 13 March 2011] [12:02:24] <pieterh>	Guthur: CH4 is now finished
| [Sunday 13 March 2011] [12:03:19] <Guthur>	cool, i'm just debugging my peering3 and then i can start on ch4
| [Sunday 13 March 2011] [12:03:26] <pieterh>	:-)
| [Sunday 13 March 2011] [12:17:33] <mikko>	\\o
| [Sunday 13 March 2011] [12:17:34] <mikko>	o//
| [Sunday 13 March 2011] [12:18:06] <mikko>	pieterh: we got some more fixes going on in openpgm with steve
| [Sunday 13 March 2011] [12:18:19] <pieterh>	mikko: nice, what's the issue?
| [Sunday 13 March 2011] [12:18:31] <mikko>	sun linker visibility with sungcc compiler
| [Sunday 13 March 2011] [12:18:35] <pieterh>	ah, ok
| [Sunday 13 March 2011] [12:18:45] <mikko>	and i think i've found zeromq compile warning on freebsd 8.1
| [Sunday 13 March 2011] [12:19:02] <mikko>	pgm_receiver.cpp:154: warning: dereferencing type-punned pointer will break strict-aliasing rules
| [Sunday 13 March 2011] [12:19:17] <pieterh>	that definitely looks like a warning :-)
| [Sunday 13 March 2011] [12:19:25] <mikko>	it breaks the build nowadays
| [Sunday 13 March 2011] [12:19:39] <mikko>	previously zeromq was compiled without -Werror when openpgm was enabled
| [Sunday 13 March 2011] [12:19:59] <mikko>	now that openpgm is built separately i added -Werror back in
| [Sunday 13 March 2011] [12:23:03] <pieterh>	mikko: sanity check, do you see a man page for zmq_device() in your zeromq source tree?
| [Sunday 13 March 2011] [12:24:14] <mikko>	https://github.com/zeromq/zeromq2-1/tree/master/doc
| [Sunday 13 March 2011] [12:24:26] <mikko>	doesn't seem to be there
| [Sunday 13 March 2011] [12:24:54] <pieterh>	funny, the method isn't documented, but I recall writing a man page for it
| [Sunday 13 March 2011] [12:25:05] <pieterh>	which is installed on my box...
| [Sunday 13 March 2011] [12:25:10] <pieterh>	hmm
| [Sunday 13 March 2011] [12:25:22] <mikko>	maybe you haven't committed / pushed it?
| [Sunday 13 March 2011] [12:25:53] <pieterh>	nope, it was reverted by the maintainers...
| [Sunday 13 March 2011] [12:25:57] <pieterh>	sep 4
| [Sunday 13 March 2011] [12:26:02] <pieterh>	ok, I'm adding it back to 2.0 and 2.1
| [Sunday 13 March 2011] [12:26:53] <mikko>	when are you flying back?
| [Sunday 13 March 2011] [12:27:09] <pieterh>	as soon as these mushrooms wear off
| [Sunday 13 March 2011] [12:27:12] <pieterh>	what? what?
| [Sunday 13 March 2011] [12:27:19] <pieterh>	:-) I'm not away, Mikko, happily working at home
| [Sunday 13 March 2011] [12:27:26] <mikko>	i mean from london
| [Sunday 13 March 2011] [12:27:43] <pieterh>	ah, I take the train, easy ride from London to Brussels
| [Sunday 13 March 2011] [12:27:53] <mikko>	ah, ok
| [Sunday 13 March 2011] [12:27:57] <pieterh>	if you want to meet up I'm around Wednesday afternoon
| [Sunday 13 March 2011] [12:27:59] <mikko>	i noticed that cloudcamp (http://www.cloudcamp.org/london) is on 17th
| [Sunday 13 March 2011] [12:28:24] <mikko>	if that is of interest to you
| [Sunday 13 March 2011] [12:28:26] <pieterh>	sigh, yeah, won't make it
| [Sunday 13 March 2011] [12:28:44] <mikko>	i'm gonna be on client site all next week so probably earliest we meet is in the pub
| [Sunday 13 March 2011] [12:28:53] <mikko>	been hectic last week
| [Sunday 13 March 2011] [12:28:57] <mikko>	setting up my own company
| [Sunday 13 March 2011] [12:29:03] <pieterh>	nice!
| [Sunday 13 March 2011] [12:29:21] <mikko>	almost everything ready
| [Sunday 13 March 2011] [12:29:27] <mikko>	still need to sort out bank account
| [Sunday 13 March 2011] [12:29:36] <mikko>	(i think at some point it would be nice to get paid)
| [Sunday 13 March 2011] [12:31:13] <pieterh>	that's always a nice option
| [Sunday 13 March 2011] [13:44:58] <Guthur>	I'm getting an "Operation cannot be accomplished in current state" in the clientTask of peering3
| [Sunday 13 March 2011] [13:45:09] <Guthur>	it works for a while then that error on a recv
| [Sunday 13 March 2011] [13:45:19] <Guthur>	any suggestions on how to find the route of the error
| [Sunday 13 March 2011] [13:53:21] <mikko>	Guthur: req/rep sockets?
| [Sunday 13 March 2011] [13:53:23] <pieterh>	hmm, sounds like a REQ socket state error
| [Sunday 13 March 2011] [13:53:26] <pieterh>	let me check that
| [Sunday 13 March 2011] [13:53:29] <mikko>	yeah, was thinking the same
| [Sunday 13 March 2011] [13:53:52] <Guthur>	yeah re
| [Sunday 13 March 2011] [13:53:54] <mikko>	wrong order of recv/send causes that
| [Sunday 13 March 2011] [13:53:56] <Guthur>	req/rep
| [Sunday 13 March 2011] [13:53:58] <mikko>	usually
| [Sunday 13 March 2011] [13:54:27] <mikko>	so for example send/recv/recv on req socket would cause that
| [Sunday 13 March 2011] [13:54:27] <Guthur>	oh ok, it's possible there is an error with my code
| [Sunday 13 March 2011] [13:54:45] <pieterh>	Guthur: it could be a bug in the design, as well
| [Sunday 13 March 2011] [13:54:47] <mikko>	there possibly should be a way to recover the socket
| [Sunday 13 March 2011] [13:55:02] <pieterh>	well, what I do is close it and reopen, in later examples
| [Sunday 13 March 2011] [13:55:29] <pieterh>	kind of annoying but finally it works ok
| [Sunday 13 March 2011] [13:59:47] <Guthur>	dinner time, I'll check my code later
| [Sunday 13 March 2011] [15:10:05] <guido_g>	http://pycon.blip.tv/file/4878885/  <- zeds mq talk at pycon
| [Sunday 13 March 2011] [15:22:21] <mikko>	interesting observations
| [Sunday 13 March 2011] [15:25:29] <Skaag>	mikko: getting paid is very important, but can be dangerous if not done right
| [Sunday 13 March 2011] [15:25:44] <Skaag>	need to consider it strategically
| [Sunday 13 March 2011] [15:26:25] <Skaag>	but no doubt, it has to happen
| [Sunday 13 March 2011] [15:32:25] <mikko>	Skaag: i really haven't got much savings so there isnt that much room for strategy
| [Sunday 13 March 2011] [15:32:28] <mikko>	:)
| [Sunday 13 March 2011] [15:32:53] <Skaag>	well ok but here's what I mean:
| [Sunday 13 March 2011] [15:33:05] <Skaag>	Assuming you have a client who wishes to hire your services - what does he need exactly?
| [Sunday 13 March 2011] [15:33:16] <mikko>	services?
| [Sunday 13 March 2011] [15:33:17] <Skaag>	And the question is, of course, how many such offers you get
| [Sunday 13 March 2011] [15:33:34] <Skaag>	the danger i'm talking about is one of stifling innovation
| [Sunday 13 March 2011] [15:33:46] <Skaag>	basically the elimination of time for creativity
| [Sunday 13 March 2011] [15:34:23] <Skaag>	sometimes you need to delegate work to a team, make a cut from the top, but remain "CTO" and continue to research and develop the core technology
| [Sunday 13 March 2011] [15:34:38] <Skaag>	you don't have a day job?
| [Sunday 13 March 2011] [15:34:46] <Skaag>	I was certain you were hired for good pay at the very least :)
| [Sunday 13 March 2011] [15:34:48] <mikko>	i have but not soon
| [Sunday 13 March 2011] [15:34:59] <Skaag>	company closing?
| [Sunday 13 March 2011] [15:35:00] <mikko>	i resigned to start my own company
| [Sunday 13 March 2011] [15:35:12] <Skaag>	ah, good luck!!
| [Sunday 13 March 2011] [15:35:33] <mikko>	thanks
| [Sunday 13 March 2011] [15:35:40] <Skaag>	it's not easy, the path you have chosen
| [Sunday 13 March 2011] [15:35:44] <Skaag>	:)
| [Sunday 13 March 2011] [15:35:51] <Skaag>	but certainly, most fulfilling :)
| [Sunday 13 March 2011] [15:36:28] <Skaag>	some would say, easiest is to be the cow in the shed, slowly milked, given music and food...
| [Sunday 13 March 2011] [15:36:32] <Skaag>	:)
| [Sunday 13 March 2011] [15:36:52] <mikko>	probably
| [Sunday 13 March 2011] [15:36:59] <mikko>	i like the excitement of setting up a company
| [Sunday 13 March 2011] [15:37:03] <mikko>	even if it fails eventually
| [Sunday 13 March 2011] [15:37:19] <mikko>	knowing that there won't be food on the table unless you do something about it
| [Sunday 13 March 2011] [15:38:12] <guido_g>	hmmm i gained ~20kg in the 2 years since i went freelancing
| [Sunday 13 March 2011] [15:38:20] <mikko>	sustrik: there?
| [Sunday 13 March 2011] [15:43:37] <Skaag>	mikko: I so know what you're talking about, that I can't help but remember all the pain :)
| [Sunday 13 March 2011] [15:44:10] <Skaag>	If you need any help, I am here
| [Sunday 13 March 2011] [15:44:38] <mikko>	i'm not overly worried at the moment
| [Sunday 13 March 2011] [15:44:53] <mikko>	not yet at least :)
| [Sunday 13 March 2011] [15:52:02] <Skaag>	what's the goal of the company?
| [Sunday 13 March 2011] [15:53:50] <mikko>	i got a few SaaS ideas but i guess initially just bring the food to table
| [Sunday 13 March 2011] [15:53:58] <mikko>	initially providing services i would guess
| [Sunday 13 March 2011] [15:54:24] <Skaag>	ok so the classic "Tech Guy opens a Company" scenario, as I thought :)
| [Sunday 13 March 2011] [15:54:58] <mikko>	yeah
| [Sunday 13 March 2011] [15:55:05] <mikko>	initially it will just be me
| [Sunday 13 March 2011] [15:55:10] <Skaag>	(not saying it in any negative way!)
| [Sunday 13 March 2011] [15:55:12] <mikko>	i haven't really planned things very far
| [Sunday 13 March 2011] [15:55:27] <mikko>	i just kinda felt that i need new challenges
| [Sunday 13 March 2011] [15:55:40] <Skaag>	I did it for other reasons
| [Sunday 13 March 2011] [15:55:53] <Skaag>	I wanted a stable passive income to allow me to research things in my free time
| [Sunday 13 March 2011] [15:56:16] <mikko>	did it work out?
| [Sunday 13 March 2011] [15:56:18] <Skaag>	corporate took too much of my time, they were the hungry pig that never had enough
| [Sunday 13 March 2011] [15:56:22] <Skaag>	actually yes :)
| [Sunday 13 March 2011] [15:56:32] <Skaag>	thanks to my wife though
| [Sunday 13 March 2011] [15:56:43] <Skaag>	if she hadn't taken the financial parts from me, it would have failed miserably
| [Sunday 13 March 2011] [15:56:54] <Skaag>	not ashamed to admit it
| [Sunday 13 March 2011] [15:57:11] <Skaag>	she's a woman who is not afraid to bill customers for her husband's work/hours :)
| [Sunday 13 March 2011] [15:57:25] <Skaag>	and she will hunt them down, until hell freezes, or they pay!!
| [Sunday 13 March 2011] [15:57:46] <Skaag>	and better not tell her the payment is late, for she will unleash upon you her furious anger, and terrible might!! :)
| [Sunday 13 March 2011] [15:58:06] <Skaag>	ok I may be exaggerating it a bit, but more or less that's how it is! :)
| [Sunday 13 March 2011] [15:58:19] <mikko>	in UK it seems very common to delay 50+ or so days
| [Sunday 13 March 2011] [15:58:33] <Skaag>	never go down that route
| [Sunday 13 March 2011] [15:58:35] <Skaag>	never.
| [Sunday 13 March 2011] [15:58:45] <Skaag>	do not agree to that.
| [Sunday 13 March 2011] [15:59:07] <mikko>	no, i mean companies just not paying even when the terms say 30 days or so
| [Sunday 13 March 2011] [15:59:48] <Skaag>	don't even agree for 30 days
| [Sunday 13 March 2011] [16:00:11] <mikko>	30 days is common here
| [Sunday 13 March 2011] [16:00:16] <Skaag>	7 days from the presentation of the invoice.
| [Sunday 13 March 2011] [16:00:38] <mikko>	back in finland 7 days was reasonable
| [Sunday 13 March 2011] [16:00:43] <mikko>	here, i don't think so
| [Sunday 13 March 2011] [16:00:52] <Skaag>	and I don't know how tax authorities work in the UK, but VAT in Israel want their chunk of the money whether or not you received payment, for any invoices you produced.
| [Sunday 13 March 2011] [16:01:02] <Skaag>	mikko, seriously, who cares what is common
| [Sunday 13 March 2011] [16:01:10] <Skaag>	start with 7 days and let the customer squirm
| [Sunday 13 March 2011] [16:01:23] <Skaag>	and then if you do heed the 30 days, at least he will feel he won something
| [Sunday 13 March 2011] [16:01:25] <Skaag>	he earned them ;)
| [Sunday 13 March 2011] [16:01:55] <Skaag>	I hate seeing people get fucked, especially if I care about them and their future
| [Sunday 13 March 2011] [16:04:26] <mikko>	pieterh: have you done work on zns or still gathering ideas?
| [Sunday 13 March 2011] [16:06:34] <nadime>	if mikko or cremes are here -- solved my IO bottleneck problem
| [Sunday 13 March 2011] [16:06:53] <nadime>	profiler did the trick
| [Sunday 13 March 2011] [16:14:25] <michelp>	i have to agree with Skaag on this one, when the customer balks that 30 days is normal, tell them to go hire a normal person.  you're better than normal.
| [Sunday 13 March 2011] [16:18:27] <Skaag>	exactly my point - this is Mikko!!!! Not some random developer.
| [Sunday 13 March 2011] [16:18:37] <Skaag>	I mean c'mon, is nothing holy anymore?!
| [Sunday 13 March 2011] [16:18:40] <Skaag>	:)
| [Sunday 13 March 2011] [16:38:04] <mikko>	nadime: what was the issue?
| [Sunday 13 March 2011] [18:17:49] <nadime>	mikko - i was using a poller in a bottleneck thread for no good reason
| [Sunday 13 March 2011] [18:40:32] <Guthur>	should a SUB socket connect block until it's connected to an endpoint?
| [Sunday 13 March 2011] [18:43:48] <Guthur>	the example in peering3 seems to block
| [Sunday 13 March 2011] [18:44:00] <Guthur>	but mine does not which has me scratching my head
| [Sunday 13 March 2011] [18:44:20] <yo>	yo
| [Sunday 13 March 2011] [18:44:26] <yo>	what's up
| [Sunday 13 March 2011] [20:06:28] <travlr>	Zed's Presentation -- PyCon 2011: Advanced Network Architectures With ZeroMQ : http://blip.tv/file/4878885
| [Sunday 13 March 2011] [20:07:02] <Guthur>	decent presentation, a bit lightning fast though
| [Sunday 13 March 2011] [20:07:33] <travlr>	ahh, i now see guido_g beat me to the link.
| [Sunday 13 March 2011] [20:07:46] <travlr>	Guthur: yeah i'm watching it now
| [Sunday 13 March 2011] [20:08:02] <Guthur>	pieterh sent it on the mailing list
| [Sunday 13 March 2011] [20:08:22] <travlr>	credit to pieter then. ;)
| [Sunday 13 March 2011] [20:19:36] <Guthur>	ah it's not blocking, question from before, just printf was not showing
| [Sunday 13 March 2011] [21:16:50] <gholt>	I can't beleive he only got 30mins for 0mq. 0mq does run length encoding?
| [Monday 14 March 2011] [00:02:39] <cleifer>	kind of random question, but if i'm using a pub/sub style interaction and want to "flush" the queue of messages waiting to be published, is there a good way?
| [Monday 14 March 2011] [02:11:57] <CIA-103>	zeromq2: 03Martin Sustrik 07master * r2970d6c 10/ src/pgm_socket.cpp : 
| [Monday 14 March 2011] [02:11:57] <CIA-103>	zeromq2: Remove obsolete assert from pgm_socket.cpp
| [Monday 14 March 2011] [02:11:57] <CIA-103>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/eTHjYC
| [Monday 14 March 2011] [02:19:33] <sustrik>	mikko: hi, are you there by chance?
| [Monday 14 March 2011] [02:45:58] <dermoth|home>	hi sustrik 
| [Monday 14 March 2011] [02:46:04] <sustrik>	hi
| [Monday 14 March 2011] [02:46:38] <dermoth|home>	you may remember my issue with the devices deadlocking due to a blocking socket...
| [Monday 14 March 2011] [02:49:43] <dermoth|home>	src/signaler.cpp, making the send MSG_DONTWAIT in zmq::signaler_t::send...
| [Monday 14 March 2011] [02:50:11] <dermoth|home>	I believe i've seen talks abot who to make is non-blocking, was this solved yet?
| [Monday 14 March 2011] [02:50:48] <dermoth|home>	in 2.1 I think the code is in mailbox.cpp...
| [Monday 14 March 2011] [02:53:46] <dermoth|home>	well, sustrik if not I was just wondering if you have considered the use of a pipe... I've used them in the past, and one nice thing about them is that a non-blocking pipe write (up to a defined limit) is atomic, it either goes trough entirely or fail, whihc I feel is what the current problem was with making sockets non-blocking...
| [Monday 14 March 2011] [02:55:26] <dermoth|home>	POSIX.1-2001  says  that write(2)s of less than PIPE_BUF bytes must be atomic: the output data is written to the pipe as a contiguous sequence. [...] O_NONBLOCK enabled, n <= PIPE_BUF: If there is room to write n bytes to the pipe, then write(2) succeeds immediately, writing all n bytes; otherwise write(2) fails, with errno set to EAGAIN.
| [Monday 14 March 2011] [02:56:54] <sustrik>	dermoth: is pipe different from a socket pair in this respect?
| [Monday 14 March 2011] [02:58:53] <sustrik>	the nice thing at least is that pipe is unidirectional rather than bidrectional
| [Monday 14 March 2011] [02:59:07] <sustrik>	meaning it will consume less buffer memory
| [Monday 14 March 2011] [02:59:16] <dermoth|home>	sustrik, I have little experience with sockets, but afaik a non-blocking write can he partial and there's no threshold for atomicity. OTOH  POSIX.1-2001 says that anything less than or equal to PIPE_BUF must be written atomically. IIRC it also defines PIPE_BUF be at least 512 bytes, iirc in Linux it's 4096 though...
| [Monday 14 March 2011] [03:00:45] <dermoth|home>	as with above, from "man 7 pipe" on Ubuntu: POSIX.1-2001 requires PIPE_BUF to be at least 512 bytes.  (On Linux, PIPE_BUF  is  4096 bytes.)
| [Monday 14 March 2011] [03:01:44] <sustrik>	yep
| [Monday 14 March 2011] [03:01:53] <sustrik>	i recall reading the same about socketpair
| [Monday 14 March 2011] [03:01:58] <dermoth|home>	note that if you wish to poll on a pipe, it must be open with O_RDWR
| [Monday 14 March 2011] [03:02:00] <sustrik>	cannot find that now though
| [Monday 14 March 2011] [03:02:42] <sustrik>	anyway, i can try using pipes
| [Monday 14 March 2011] [03:02:54] <sustrik>	however, it's likely to break on some OSes
| [Monday 14 March 2011] [03:03:13] <sustrik>	so i would postpone the experiment till stable 2.1 is out
| [Monday 14 March 2011] [03:03:53] <sustrik>	hm, can you set SNDBUF on a pipe?
| [Monday 14 March 2011] [03:04:56] <dermoth|home>	likely not...
| [Monday 14 March 2011] [03:08:28] <dermoth|home>	well I just thought i'd share this in case it can be of any help, although i'm far from understanding all the magic that happens behind the zmq api :) 
| [Monday 14 March 2011] [03:11:40] <dermoth|home>	btw the MSG_DONTWAIT fix worked like a charm, I can get occasional restarts but no more communication deadlock. BTW it seems the data is help on the devices, not the PUSH clients - and when I kill them (SIGTERM) all data is flushed to the PULL clients
| [Monday 14 March 2011] [03:11:47] <dermoth|home>	data is *held*
| [Monday 14 March 2011] [03:53:10] <pieterh>	g'morning
| [Monday 14 March 2011] [03:54:00] <guido_g>	morning
| [Monday 14 March 2011] [03:54:57] <pieterh>	random poll to 0MQ users here: does anyone use the devices packaged with the library?
| [Monday 14 March 2011] [03:59:25] <pieterh>	{poll timeout: ENORESPONSE}
| [Monday 14 March 2011] [04:01:49] <guido_g>	pieterh: saw the guide ch4 checkins yesterday, when will the online version of the be updated?
| [Monday 14 March 2011] [04:02:00] <pieterh>	guido_g: was going to do that now in fact
| [Monday 14 March 2011] [04:02:05] <pieterh>	am just reviewing the text once again
| [Monday 14 March 2011] [04:02:16] <guido_g>	ok, won't disturb you then ,)
| [Monday 14 March 2011] [04:02:41] <pieterh>	np, let me launch it then...
| [Monday 14 March 2011] [04:03:06] <guido_g>	no hurry, page set to auto-reload
| [Monday 14 March 2011] [04:06:41] <mikko>	sustrik: i am now
| [Monday 14 March 2011] [04:10:00] <sustrik>	mikko: the bsd bug
| [Monday 14 March 2011] [04:10:08] <sustrik>	if i send you a patch can you check it?
| [Monday 14 March 2011] [04:10:13] <mikko>	sustrik: sure
| [Monday 14 March 2011] [04:10:18] <sustrik>	ok
| [Monday 14 March 2011] [04:10:27] <mikko>	the pgm type punned pointer?
| [Monday 14 March 2011] [04:10:44] <mikko>	pgm_receiver.cpp:154: warning: dereferencing type-punned pointer will break strict-aliasing rules
| [Monday 14 March 2011] [04:10:47] <mikko>	this one?
| [Monday 14 March 2011] [04:12:18] <sustrik>	yes
| [Monday 14 March 2011] [04:13:31] <sustrik>	sent
| [Monday 14 March 2011] [04:17:48] <mikko>	will test later today!
| [Monday 14 March 2011] [04:25:07] <pieterh>	mikko: when the openpgm integration is stable, can you send a patch to the ML?
| [Monday 14 March 2011] [04:28:36] <sustrik>	pieterh: is there any particular reason why you want to drop devices in 2.1?
| [Monday 14 March 2011] [04:28:55] <pieterh>	sustrik: I'm not dropping devices, just those undocumented, unmaintained examples
| [Monday 14 March 2011] [04:29:06] <pieterh>	0MQ core should not have these, period
| [Monday 14 March 2011] [04:29:06] <pieterh>	I'
| [Monday 14 March 2011] [04:29:24] <pieterh>	I've been asking for this cleanup since September and each time it's been refused for... no good reason
| [Monday 14 March 2011] [04:29:25] <sustrik>	it's more work to do and you risk annoying users
| [Monday 14 March 2011] [04:29:28] <pieterh>	nope
| [Monday 14 March 2011] [04:29:40] <pieterh>	I've asked now several times if anyone uses these
| [Monday 14 March 2011] [04:29:46] <sustrik>	and it's going to be removed from master once 2.1 is out anyway
| [Monday 14 March 2011] [04:30:01] <sustrik>	so you would have to reconcile both patches afterwards
| [Monday 14 March 2011] [04:30:04] <pieterh>	I want 2.1 to be clean
| [Monday 14 March 2011] [04:30:13] <sustrik>	sure, i don't care
| [Monday 14 March 2011] [04:30:15] <pieterh>	currently it has junk in it
| [Monday 14 March 2011] [04:30:20] <pieterh>	undocumented, bleh :-/
| [Monday 14 March 2011] [04:30:34] <pieterh>	these should have gone ages ago
| [Monday 14 March 2011] [04:30:45] <pieterh>	also I've restored the zmq_device(3) man page which seems essential
| [Monday 14 March 2011] [04:30:58] <pieterh>	lastly, having these devices in there gives them special weight they do not deserve
| [Monday 14 March 2011] [04:31:10] <pieterh>	and which contradicts developing *real* apps elsewhere
| [Monday 14 March 2011] [04:31:19] <pieterh>	finally, they are unmaintained
| [Monday 14 March 2011] [04:31:26] <pieterh>	and have survived several attempts at improvement
| [Monday 14 March 2011] [04:31:31] <pieterh>	which is inexcusable
| [Monday 14 March 2011] [04:31:33] <sustrik>	well, i would say that 2.1 should be called something else than stable then
| [Monday 14 March 2011] [04:31:41] <pieterh>	when unused code resists improvement, it has to be killed
| [Monday 14 March 2011] [04:31:50] <sustrik>	what about "iMatix enterprise distribution"?
| [Monday 14 March 2011] [04:31:54] <pieterh>	"stable and clean" if you prefer
| [Monday 14 March 2011] [04:32:14] <pieterh>	you focus on making the core, I'll take responsibility for clean packages, ok?
| [Monday 14 March 2011] [04:32:20] <sustrik>	sure
| [Monday 14 March 2011] [04:32:23] <pieterh>	thanks
| [Monday 14 March 2011] [04:32:55] <pieterh>	I note that both Jon Dyte and myself contributed documented, cleaned up improvements to those devices
| [Monday 14 March 2011] [04:33:01] <pieterh>	both times, rejected for no good reason
| [Monday 14 March 2011] [04:33:10] <pieterh>	this annoys me to a point you perhaps can't appreciate
| [Monday 14 March 2011] [04:33:14] <sustrik>	they are scheduled for removeal
| [Monday 14 March 2011] [04:33:16] <sustrik>	freezed
| [Monday 14 March 2011] [04:33:26] <pieterh>	bogus argument
| [Monday 14 March 2011] [04:33:36] <pieterh>	for the last 6 months?
| [Monday 14 March 2011] [04:33:40] <sustrik>	yes
| [Monday 14 March 2011] [04:33:41] <sustrik>	till 3.0
| [Monday 14 March 2011] [04:33:43] <pieterh>	lol
| [Monday 14 March 2011] [04:33:59] <pieterh>	I'm not even going to argue this
| [Monday 14 March 2011] [04:34:08] <pieterh>	you want a distribution with rubbish in it, make it
| [Monday 14 March 2011] [04:34:10] <sustrik>	well, if you want a stable stable you have to maintain it for 5+ years
| [Monday 14 March 2011] [04:34:20] <sustrik>	backward compatible
| [Monday 14 March 2011] [04:34:21] <pieterh>	I'm not interested in releasing crap
| [Monday 14 March 2011] [04:34:25] <pieterh>	no excuses
| [Monday 14 March 2011] [04:34:44] <pieterh>	and everything in the distribution must be maintained or documented, or removed
| [Monday 14 March 2011] [04:34:46] <sustrik>	maintaining crap is what "stable" means
| [Monday 14 March 2011] [04:34:46] <pieterh>	no excuses
| [Monday 14 March 2011] [04:34:56] <sustrik>	otherwise you are doing dev branch
| [Monday 14 March 2011] [04:35:11] <sustrik>	anyway, it's up to you
| [Monday 14 March 2011] [04:35:22] <pieterh>	no Martin, and with all due respect, maintaining releases over years is something I'm expert in, whereas you are not
| [Monday 14 March 2011] [04:35:56] <sustrik>	i don't really care
| [Monday 14 March 2011] [04:36:08] <pieterh>	then don't argue with me
| [Monday 14 March 2011] [04:36:09] <sustrik>	do it as you believe it's best
| [Monday 14 March 2011] [04:36:13] <pieterh>	I always do
| [Monday 14 March 2011] [04:36:15] <sustrik>	just warning you
| [Monday 14 March 2011] [04:36:24] <pieterh>	and I'm intensely interested in the opinions of real users
| [Monday 14 March 2011] [04:36:43] <pieterh>	but not interested in discussing "policies" that are unhelpful and arbitrary in this case
| [Monday 14 March 2011] [04:40:59] <pieterh>	again, if *anyone* here is actually using these device apps, please speak up
| [Monday 14 March 2011] [04:41:07] <pieterh>	I'll ask again on the ML before taking a final decision
| [Monday 14 March 2011] [04:41:46] <pieterh>	mikko: there's been some changes to the Wikidot API, so it broke
| [Monday 14 March 2011] [04:42:02] <pieterh>	if you're generating the api.zeromq.org it'll have stopped working
| [Monday 14 March 2011] [04:54:21] <guido_g>	pieterh: fig62.png seems to be missing
| [Monday 14 March 2011] [04:54:37] <pieterh>	guido_g: thanks, let me fix that
| [Monday 14 March 2011] [04:55:37] <guido_g>	and a feature request: is it possible to fold the code listings like the toc?
| [Monday 14 March 2011] [04:56:21] <pieterh>	guido_g: yes, it's a good idea
| [Monday 14 March 2011] [04:56:37] <pieterh>	I'm redesigning the whole code listing UI, will do this as part of that
| [Monday 14 March 2011] [04:56:40] <guido_g>	they're simply too large for the main text now
| [Monday 14 March 2011] [04:56:52] <pieterh>	yup, monsterous :-)
| [Monday 14 March 2011] [04:56:53] <guido_g>	great! thanks in advance
| [Monday 14 March 2011] [04:58:13] <pieterh>	guido_g: ok, the images should all be working now, may need a reload
| [Monday 14 March 2011] [04:58:35] <guido_g>	works now
| [Monday 14 March 2011] [04:58:40] <Guthur>	+1 for code folding
| [Monday 14 March 2011] [04:58:58] <guido_g>	:)
| [Monday 14 March 2011] [05:00:07] 	 * guido_g is going to do the chores first
| [Monday 14 March 2011] [05:21:48] <Guthur>	pieterh: 5 specifications within 13 days, that's quite a feat
| [Monday 14 March 2011] [07:28:08] <pieterh>	Guthur: ... am in meetings all day...
| [Monday 14 March 2011] [07:28:16] <pieterh>	making specifications is kind of a hobby of mine
| [Monday 14 March 2011] [07:28:29] <pieterh>	I think it's time to properly document the 0MQ wire protocols, all of them
| [Monday 14 March 2011] [07:28:38] <dermoth|home>	pieterh, i do - I run a pool of streamer devices
| [Monday 14 March 2011] [07:28:56] <pieterh>	dermoth|home: do you use the code from the repository or have you made your own versions?
| [Monday 14 March 2011] [07:30:47] <Guthur>	+1 on 0MQ wire protocols
| [Monday 14 March 2011] [07:30:47] <dermoth|home>	pieterh, not sure if we're talking about the same repo... i'm running the devices from the code zmq library, not the separate (newer) project. The goal is to flush asap the httpd workers asap to avoid loss when they crash/restart, and also simplify the configuration (everything connect to the same pool of "servers"
| [Monday 14 March 2011] [07:30:59] <Guthur>	better to get it done sooner rather than later in imo
| [Monday 14 March 2011] [07:31:07] <dermoth|home>	from the *core* library
| [Monday 14 March 2011] [08:24:12] <Guthur>	is there a minimum language version requirement for the python or perl binding
| [Monday 14 March 2011] [08:24:46] <private_meta>	Is the lack of a dedicated zmq::version call intended?
| [Monday 14 March 2011] [08:25:27] <Guthur>	also, how is 0MQ on solaris?
| [Monday 14 March 2011] [08:57:51] <Guthur>	re My solaris question; I notice the daily build is on solaris 10, anyone know if 0MQ is working on solaris 8
| [Monday 14 March 2011] [09:00:36] <Steve-o>	I wouldn't expect much unless you try G++ 
| [Monday 14 March 2011] [09:03:48] <Steve-o>	Wasn't it EOL a while ago?
| [Monday 14 March 2011] [09:04:56] <Steve-o>	Forte might be too old, but I think at least one of the Sun ONE Studio's runs on 8?
| [Monday 14 March 2011] [09:05:22] <Guthur>	Steve-o: Yeah we need to move soon
| [Monday 14 March 2011] [09:05:36] <private_meta>	pieterh: I know it's just a wrapper, but for uniformity it would be nice to have the zmq::version call in the C++ version
| [Monday 14 March 2011] [09:05:46] <Guthur>	I wish we could easily migrate to RH
| [Monday 14 March 2011] [09:05:59] <Guthur>	that's an option, but probably a painful one
| [Monday 14 March 2011] [09:07:03] <Steve-o>	Guthur: you actually using Solaris on x86/x64?
| [Monday 14 March 2011] [09:09:32] <Steve-o>	it's bad enough that studio 12 is still out-of-date, Google Protobufs doesn't work well with Sun's STL stack