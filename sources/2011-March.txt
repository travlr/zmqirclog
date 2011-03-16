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
| [Monday 14 March 2011] [11:15:31] <jstrom>	hm i sent an email to zeromq-dev a few hours ago, haven't showed up in archives yet.. any problems with mail delivery/bad spam detection?
| [Monday 14 March 2011] [11:15:40] <jstrom>	or is there moderation?
| [Monday 14 March 2011] [11:24:39] <private_meta>	jstrom: The last time I sent an email it showed up immediately, so I doubt there is moderation
| [Monday 14 March 2011] [11:25:03] <jstrom>	okey, wierd
| [Monday 14 March 2011] [11:25:12] <private_meta>	jstrom: and,I see an email by you in my mailbox
| [Monday 14 March 2011] [11:25:16] <jstrom>	Just signed up but that usually doenst make any difference in mailman..
| [Monday 14 March 2011] [11:25:18] <jstrom>	oh, okey
| [Monday 14 March 2011] [11:25:40] <private_meta>	depending on your time zone, 1[1|2]:36
| [Monday 14 March 2011] [11:25:48] <jstrom>	Guess its just the archive beeing slow then :) I opted for digest mail, so I didnt get the mail myself directly
| [Monday 14 March 2011] [11:25:53] <jstrom>	yep
| [Monday 14 March 2011] [11:27:12] <private_meta>	By the way, it's in the archive as well
| [Monday 14 March 2011] [11:28:45] <private_meta>	jstrom: I have no idea why, but apparently your mail, if sorted by Topic, was considered as a reply to "[zeromq-dev] Poll about linger and termination behaviour!"
| [Monday 14 March 2011] [11:29:17] <jstrom>	hah.. yeah, there I see it.. thats very wierd indeed.. the gmane archive has it correct though: http://news.gmane.org/gmane.network.zeromq.devel
| [Monday 14 March 2011] [12:34:07] <troutwine>	Aside from tunneling, what are my options for secure transmission? SSL is not natively supported, right?
| [Monday 14 March 2011] [12:42:33] <cremes>	troutwine: there are no built-in options for security
| [Monday 14 March 2011] [12:42:41] <cremes>	tunneling is probably the easiest solution at this point
| [Monday 14 March 2011] [12:42:55] <troutwine>	cremes: Tunneling is out of the question, sadly.
| [Monday 14 March 2011] [12:42:57] <cremes>	you might want to search the mailing list archives for this question; it has come up a few times
| [Monday 14 March 2011] [12:43:08] <cremes>	and there might be a solution for you listed there
| [Monday 14 March 2011] [12:43:16] <troutwine>	cremes: I did, but didn't find anything terribly promising. 
| [Monday 14 March 2011] [12:43:34] <cremes>	too bad... perhaps you could try asking again and describe your use-case
| [Monday 14 March 2011] [12:43:56] <cremes>	maybe someone has come up with a clever solution and is waiting for someone to ask about it before sharing :)
| [Monday 14 March 2011] [12:44:29] <troutwine>	cremes: Maybe. Thanks.
| [Monday 14 March 2011] [12:44:33] <nadime>	it wouldn't be terribly hard to write your own ZMQ-SSL wrapper
| [Monday 14 March 2011] [12:44:47] <nadime>	someone may have done so, and just not released it
| [Monday 14 March 2011] [12:45:30] <nadime>	cremes -- question for you
| [Monday 14 March 2011] [12:45:39] <cremes>	nadime: shoot
| [Monday 14 March 2011] [12:46:02] <troutwine>	nadime: I think that's what I'm going to do, but I know squat about SSL implementations, or really about ZMQ internals. Any pointers?
| [Monday 14 March 2011] [12:47:08] <nadime>	i don't think you need to know anything about zmq internals
| [Monday 14 March 2011] [12:47:17] <nadime>	but you do need to look at a few SSL implementations probably
| [Monday 14 March 2011] [12:47:40] <nadime>	you basically want to create a message class where you're encrypting the dataload
| [Monday 14 March 2011] [12:47:51] <nadime>	you can do something much simpler than a full implementation
| [Monday 14 March 2011] [12:47:53] <cremes>	i recommend looking at this UML diagram for a "taste" of the 0mq internals
| [Monday 14 March 2011] [12:47:53] <cremes>	https://github.com/thijsterlouw/zeromq2-uml
| [Monday 14 March 2011] [12:48:31] <nadime>	cremes - for high I/O throughput scenarios, is it basically recommended to have 1 input and 1 output thread (or N input/output) to avoid using a poller?
| [Monday 14 March 2011] [12:48:54] <nadime>	the zmq implementation of poll seems incredibly slow, it was what was causing my i/o bottleneck yesterday
| [Monday 14 March 2011] [12:50:49] <nadime>	troutwine -- how scalable do you need your solution to be?
| [Monday 14 March 2011] [12:51:32] <nadime>	cremes - sorry, that was unclear.  i'm asking -- is it recommended to never use zmq_poll for high throughput
| [Monday 14 March 2011] [12:51:52] <troutwine>	nadime: A few thousand concurrent clients; not terribly.
| [Monday 14 March 2011] [12:52:13] <cremes>	nadime: it's hard to say; are you using zmq_poll with a timeout or do you use it to block?
| [Monday 14 March 2011] [12:52:36] <nadime>	either, both are slow
| [Monday 14 March 2011] [12:53:06] <cremes>	nadime: interesting; i don't think anyone has done any real benchmarks in this area
| [Monday 14 March 2011] [12:53:10] <nadime>	i was running about 500k msgs/s, avg. 50B msgs, so about 25MB
| [Monday 14 March 2011] [12:53:31] <nadime>	and i was falling behind because of a poll (with either block or timeout, tried both)
| [Monday 14 March 2011] [12:53:42] <nadime>	so i was pushing 500k until i hit the poll, then only getting about 100k/s
| [Monday 14 March 2011] [12:53:50] <cremes>	you only had a handful of sockets, right? like 4 or 5 of them?
| [Monday 14 March 2011] [12:53:51] <nadime>	and my app was blowing up because of the buffering
| [Monday 14 March 2011] [12:53:56] <nadime>	yep
| [Monday 14 March 2011] [12:54:02] <cremes>	wow, that's terrible
| [Monday 14 March 2011] [12:54:14] <nadime>	the memcpy was killing me
| [Monday 14 March 2011] [12:54:25] <cremes>	any chance you could open an issue illustrating this problem?
| [Monday 14 March 2011] [12:54:30] <nadime>	i'm on win7, so i think zmq_poll uses select()
| [Monday 14 March 2011] [12:54:48] <cremes>	ah... windows
| [Monday 14 March 2011] [12:54:48] <nadime>	sure in a day or two, i can probably make an example case pretty quickly
| [Monday 14 March 2011] [12:55:04] <cremes>	windows has probably gotten the least attention out of all of the platforms
| [Monday 14 March 2011] [12:55:05] <troutwine>	nadime: Limited by human latency, I'd guess each client is going to push one message a half-second. So a few thousand sockets, 4,000 msgs/s. 
| [Monday 14 March 2011] [12:55:11] <troutwine>	nadime: Why do you ask?
| [Monday 14 March 2011] [12:55:25] <cremes>	the 0mq project doesn't have a lot of windows-savvy devs working on it yet; there are a few but progress is slow
| [Monday 14 March 2011] [12:55:32] <nadime>	worried about key exchange, troutwine
| [Monday 14 March 2011] [12:55:37] <nadime>	not throughput
| [Monday 14 March 2011] [12:56:03] <nadime>	you should basically look up how SSL handles key exchange, once you have keys on both sides, it's really easy to use ZMQ to do secure xfer
| [Monday 14 March 2011] [12:56:18] <cremes>	nadime: you might want to ping Guthur and ask him about his work on using windows-native-api poll stuff
| [Monday 14 March 2011] [12:56:34] <troutwine>	nadime: I'm reading up on SSL now. Clearly I know nothing about it. 
| [Monday 14 March 2011] [12:57:17] <nadime>	thanks, i will do that
| [Monday 14 March 2011] [12:57:30] <nadime>	i was planning on taking a look at the implementation when i have a sec, gotta finish this project though
| [Monday 14 March 2011] [12:57:39] <nadime>	but if he's already working on it, maybe we can team up
| [Monday 14 March 2011] [12:57:51] <cremes>	nadime: good idea; i'm sure he would appreciate a hand
| [Monday 14 March 2011] [12:58:05] <cremes>	nadime: his focus is on getting ipc transport working on windows
| [Monday 14 March 2011] [12:58:21] <cremes>	but that stuff is all tied in with polling for events and handling i/o completion
| [Monday 14 March 2011] [12:58:27] <nadime>	ah, well i don't care about that, but happy to help re: poll implementation ;)
| [Monday 14 March 2011] [12:58:47] <cremes>	i think a solution for both pretty much go hand in hand
| [Monday 14 March 2011] [12:58:58] <nadime>	gotcha
| [Monday 14 March 2011] [12:59:01] <cremes>	based on what Guthur was posting here last week and the week before
| [Monday 14 March 2011] [12:59:09] <nadime>	he wants to do ipc using files?
| [Monday 14 March 2011] [12:59:21] <nadime>	and the windows poll implementationc an't handle sockets and files?
| [Monday 14 March 2011] [12:59:55] <cremes>	nadime: it's best just to ask him; he can explain it with the minimum amount of confusion (that i might add if i try)
| [Monday 14 March 2011] [13:00:11] <nadime>	k
| [Monday 14 March 2011] [13:00:40] <Guthur>	did I hear my name, hehe
| [Monday 14 March 2011] [13:00:49] <cremes>	Guthur: you did!
| [Monday 14 March 2011] [13:00:59] <nadime>	you did -- cremes was just asking me to ping you about your work on windows zmq_poll implementation
| [Monday 14 March 2011] [13:01:03] <cremes>	nadime has noticed that zmq_poll() sucks donkey on windows
| [Monday 14 March 2011] [13:01:31] <Guthur>	it's a 'feature'
| [Monday 14 March 2011] [13:01:40] <Guthur>	windows comes with extra donkeys for just such cases
| [Monday 14 March 2011] [13:01:45] <nadime>	haha
| [Monday 14 March 2011] [13:02:08] <Guthur>	but yeah, we really need to look at getting IOCP
| [Monday 14 March 2011] [13:02:29] <Guthur>	or possibly, at the very least, WSA_POLL (I think thats the name)
| [Monday 14 March 2011] [13:02:44] <nadime>	what is zmq_poll implemented using right now? select()?
| [Monday 14 March 2011] [13:02:53] <Guthur>	IOCP would be the bigger win because it would give IPC
| [Monday 14 March 2011] [13:03:02] <Guthur>	nadime: I believe so
| [Monday 14 March 2011] [13:03:23] <Guthur>	It only does TCP though
| [Monday 14 March 2011] [13:03:41] <Guthur>	Select doesn't support named pipes unfortunately
| [Monday 14 March 2011] [13:03:53] <cremes>	nadime, Guthur: i'll leave you two windows experts to hash things out :)
| [Monday 14 March 2011] [13:03:55] <nadime>	and i take it wsa_poll doesn't either
| [Monday 14 March 2011] [13:04:13] <Guthur>	nadime: As far as I am aware, nope
| [Monday 14 March 2011] [13:05:03] <nadime>	IOPC looks pretty nifty
| [Monday 14 March 2011] [13:05:41] <Guthur>	I think the only realistic option for named pipes is IOCP or WaitForMultipleObjects
| [Monday 14 March 2011] [13:05:43] <nadime>	would eliminate the need to memcpy the fd list for in, out, err every cycle which is i think what slows down the poller on high throughput
| [Monday 14 March 2011] [13:05:49] <Guthur>	IOCP is pretty sweet
| [Monday 14 March 2011] [13:06:26] <Guthur>	but it doesn't naturally fit into the 0MQ engine as is, afaik
| [Monday 14 March 2011] [13:07:01] <Guthur>	it will require an abstraction layer over named pipes and IOCP 
| [Monday 14 March 2011] [13:07:44] <Guthur>	I think it's due to the fact that 0MQ needs some state reflection which IOCP doesn't cover, sustrik is the man to talk to for 0MQs needs though
| [Monday 14 March 2011] [13:07:47] <nadime>	it looks like it will actually need to loop over all requested sockets/pipes instead of operating like select()
| [Monday 14 March 2011] [13:08:11] <nadime>	nm
| [Monday 14 March 2011] [13:08:56] <Guthur>	sorry I need to go, but i'll be back in an hour or so
| [Monday 14 March 2011] [13:18:17] <private_meta>	github is amazingly stupid
| [Monday 14 March 2011] [13:18:28] <private_meta>	my account doesn't work, I can't log in
| [Monday 14 March 2011] [13:18:35] <private_meta>	they're sending me to the support page
| [Monday 14 March 2011] [13:18:41] <private_meta>	which you can only access when you're logged in
| [Monday 14 March 2011] [13:20:27] <michelp>	morning/afternoon/evening everybody
| [Monday 14 March 2011] [13:21:30] <private_meta>	pieterh: If you don't mind adding that in a future release, add this to zmq.hpp: https://gist.github.com/94ced4a644021248f4d7 <- just for unifying the c++ binding and for not having to use C calls
| [Monday 14 March 2011] [13:22:16] <private_meta>	pieterh: I don't want to clone the entire thing just to get a patch for that if you don't mind
| [Monday 14 March 2011] [13:22:28] <guido_g>	you know how to submit patches
| [Monday 14 March 2011] [13:22:41] <guido_g>	there is *a lot* of information missing
| [Monday 14 March 2011] [13:23:04] <private_meta>	Ok, then leave it out
| [Monday 14 March 2011] [13:44:23] <pieterh>	re
| [Monday 14 March 2011] [13:44:27] <pieterh>	sorry, am in meetings all day
| [Monday 14 March 2011] [13:44:46] <pieterh>	private_meta: patches need to follow contribution policy
| [Monday 14 March 2011] [13:45:25] <private_meta>	So i need to go through all that (imho annoying) stuff to see a 1 line method in there?
| [Monday 14 March 2011] [13:45:35] <pieterh>	private_meta: wrt to github are you trying to login with an organization id? 
| [Monday 14 March 2011] [13:45:45] <pieterh>	private_meta: yes, even for a 1-line patch, sorry
| [Monday 14 March 2011] [13:45:57] <pieterh>	well, perhaps I can make the change, hang on...
| [Monday 14 March 2011] [13:47:23] <private_meta>	Working on zguid I'm doing multiple changes, and I understand that a patch is necessary
| [Monday 14 March 2011] [13:47:26] <pieterh>	private_meta: I'll make that change myself, and send a patch to martin, tomorrow
| [Monday 14 March 2011] [13:47:28] <private_meta>	a *patch
| [Monday 14 March 2011] [13:47:46] <pieterh>	i'll get all the credit for it, be warned
| [Monday 14 March 2011] [13:47:55] 	 * pieterh is going to tweet how he fixed the version method!
| [Monday 14 March 2011] [13:47:57] <pieterh>	:-)
| [Monday 14 March 2011] [13:47:59] <private_meta>	sure, I don't need the credit anyway
| [Monday 14 March 2011] [13:48:17] <pieterh>	it's kind of a joke, credit for a 1-line method
| [Monday 14 March 2011] [13:48:24] <private_meta>	ik
| [Monday 14 March 2011] [13:48:27] <private_meta>	I mean creadit there in general
| [Monday 14 March 2011] [13:48:30] <private_meta>	*credit
| [Monday 14 March 2011] [13:48:35] <pieterh>	it's more about blame than credit
| [Monday 14 March 2011] [13:48:43] <pieterh>	ok, have to flee, cyl
| [Monday 14 March 2011] [13:48:47] <private_meta>	thanks
| [Monday 14 March 2011] [14:10:04] <nadime>	anyone know: what's the behavior of the io threads f you set socket affinities to threads out of range, e.g. you have 1 io thread but you set a socket's affinity to 8
| [Monday 14 March 2011] [14:45:25] <loxs>	hi folks, jus saw Zed's talk on 0mq at PyCon and there I saw him saying it's not a good idea to put it on the internet...
| [Monday 14 March 2011] [14:45:44] <loxs>	uhm, it kind looks really promising for things like game networking
| [Monday 14 March 2011] [14:46:32] <loxs>	so, are there any plans to make suitable to work on the internet?
| [Monday 14 March 2011] [14:50:44] <loxs>	Zed said "they are working on it", but what does this mean?
| [Monday 14 March 2011] [14:53:39] <cremes>	loxs: you need to remember the context in which zed said that
| [Monday 14 March 2011] [14:53:51] <cremes>	he likes to 'fuzz' all of his projects (send random data to them)
| [Monday 14 March 2011] [14:54:05] <cremes>	he noted that 0mq still has assertions that will trigger when bad data is received on the port
| [Monday 14 March 2011] [14:54:24] <cremes>	so a perfect DOS attack would be to send random data to a 0mq socket and crash the lib
| [Monday 14 March 2011] [14:54:42] <cremes>	the 0mq guys are 'working on it' in the sense that they are slowly but surely removing those assertions
| [Monday 14 March 2011] [14:54:53] <cremes>	and fixing the library's behavior in the face of bad data
| [Monday 14 March 2011] [15:01:55] <michelp>	if you can handle the overhead of it openvpn might be a good solution to securing a 0mq network over the internet
| [Monday 14 March 2011] [15:02:11] <michelp>	i hear some game networks are using it successfully
| [Monday 14 March 2011] [15:02:38] <michelp>	it also lets you do things like revoke access to rogue clients
| [Monday 14 March 2011] [15:03:29] 	 * michelp is anxious to get some time to queue up zed's talk
| [Monday 14 March 2011] [15:04:16] <cremes>	zed's talk was only "okay"; due to time pressures he touched so lightly on 85% of the important stuff
| [Monday 14 March 2011] [15:04:34] <cremes>	that unless you were already a 0mq practitioner i doubt the audience got much out of it
| [Monday 14 March 2011] [15:06:32] <loxs>	well, I didn't, but the idea of "one messaging system to rull them all" started some bells in my head :)
| [Monday 14 March 2011] [15:07:29] <loxs>	michelp, well, it's not an option if you don't trust the client (if it's a game, people will try to do all kinds of hacks to cheat the game)
| [Monday 14 March 2011] [15:07:59] <loxs>	michelp, which game networks use zeromq?
| [Monday 14 March 2011] [15:09:43] <michelp>	loxs, i don't know, just something i read while i was cruising through google setting up my own private vpn
| [Monday 14 March 2011] [15:12:46] <mikko>	sustrik: tested and works
| [Monday 14 March 2011] [15:16:10] <michelp>	loxs, sorry i misread your question, i meant some game networks are using openvpn, not 0mq
| [Monday 14 March 2011] [15:16:13] <michelp>	based on what i read only, not on any direct knowledge
| [Monday 14 March 2011] [15:17:07] <michelp>	my suggestion was that if you were going to use 0mq over the internet, using it on a vpn might be a good approach to avoid fuzz hacks on an open port
| [Monday 14 March 2011] [15:18:13] <loxs>	I see. Yep, you are right
| [Monday 14 March 2011] [15:19:00] <loxs>	but it would be really cool if you could use zeromq directly for client server communication
| [Monday 14 March 2011] [15:19:57] <sustrik>	mikko: thx
| [Monday 14 March 2011] [15:30:08] <CIA-103>	zeromq2: 03Martin Sustrik 07master * rf987f4b 10/ src/pgm_receiver.cpp : 
| [Monday 14 March 2011] [15:30:08] <CIA-103>	zeromq2: FreeBSD complation error fixed
| [Monday 14 March 2011] [15:30:08] <CIA-103>	zeromq2: There was an error in pgm_receiver wrt strict aliasing.
| [Monday 14 March 2011] [15:30:08] <CIA-103>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/ecz5VG
| [Monday 14 March 2011] [15:34:57] <andrewvc>	cremes: around?
| [Monday 14 March 2011] [15:37:54] <cremes>	andrewvc: for about 20m
| [Monday 14 March 2011] [15:38:02] <andrewvc>	a couple things
| [Monday 14 March 2011] [15:38:11] <andrewvc>	1: you know the deal with all the finalizer errors on the specs
| [Monday 14 March 2011] [15:38:23] <andrewvc>	also, I added a zdevice branch to ffi-rzmq with a new ZMQ::Device class
| [Monday 14 March 2011] [15:39:17] <mikko>	sustrik: i'm confused
| [Monday 14 March 2011] [15:39:59] <mikko>	sustrik: do fixes go first to zeromq2 or zeromq2-1 repo?
| [Monday 14 March 2011] [15:46:34] <cremes>	andrewvc: i'll take a look at the zdevice branch tonight/tomorrow and give you feedback if anything pops
| [Monday 14 March 2011] [15:46:50] <andrewvc>	cool
| [Monday 14 March 2011] [15:46:53] <cremes>	however, i'm not sure what you mean about finalizer errors; i'm not getting any
| [Monday 14 March 2011] [15:47:09] <cremes>	can you pastie the errors you see? (i might have fixed 'em and forgot to push them)
| [Monday 14 March 2011] [15:47:12] <andrewvc>	sure
| [Monday 14 March 2011] [15:47:13] <andrewvc>	one sec
| [Monday 14 March 2011] [15:51:01] <andrewvc>	cremes: https://gist.github.com/869738
| [Monday 14 March 2011] [15:51:20] <andrewvc>	actually, there's a variety of errors
| [Monday 14 March 2011] [15:51:37] <andrewvc>	that's on rbx
| [Monday 14 March 2011] [15:52:16] <cremes>	huh
| [Monday 14 March 2011] [15:52:29] <cremes>	i don't get those under mri; i'll try under rbx and get them patched up
| [Monday 14 March 2011] [15:52:42] <cremes>	looks like we found another hole in rbx's ffi support
| [Monday 14 March 2011] [15:57:50] <andrewvc>	interesting
| [Monday 14 March 2011] [15:59:29] <sustrik>	mikko: i'm maintaining master (zeromq2)
| [Monday 14 March 2011] [16:00:39] <sustrik>	pieter volunteered to do stable releases
| [Monday 14 March 2011] [16:01:13] <sustrik>	so he should decide on the process for zeromq2-1
| [Monday 14 March 2011] [16:02:36] <mikko>	sustrik: so they should be treated as separate projects?
| [Monday 14 March 2011] [16:04:40] <sustrik>	you should ask pieter
| [Monday 14 March 2011] [16:05:03] <sustrik>	my understanding of stable is maintaining the backward compatibility while backporting patches
| [Monday 14 March 2011] [16:05:37] <mikko>	i shall ask him when we meet
| [Monday 14 March 2011] [16:05:43] <sustrik>	ok
| [Monday 14 March 2011] [16:07:09] <mikko>	sustrik: where is subscription forwarding going on?
| [Monday 14 March 2011] [16:07:15] <mikko>	is it stable?
| [Monday 14 March 2011] [16:07:26] <sustrik>	mikko: it's still on a branch
| [Monday 14 March 2011] [16:07:33] <sustrik>	not finished yet
| [Monday 14 March 2011] [16:07:37] <mikko>	ok
| [Monday 14 March 2011] [16:07:58] <sustrik>	then it'll go to master obviously
| [Monday 14 March 2011] [16:08:04] <sustrik>	not sure about stables
| [Monday 14 March 2011] [16:08:19] <mikko>	it crossed my mind yesterday
| [Monday 14 March 2011] [16:08:27] <mikko>	was writing a small utility that uses pub/sub sockets
| [Monday 14 March 2011] [16:08:40] <mikko>	so, next i need to get pieterh to merge the freebsd pgm build fix
| [Monday 14 March 2011] [16:08:54] <mikko>	and test steve's upstream changes 
| [Monday 14 March 2011] [16:08:55] <sustrik>	he'll do i so, i think
| [Monday 14 March 2011] [16:09:15] <sustrik>	ack
| [Monday 14 March 2011] [19:42:26] <Guthur>	any suggestions on why i might get a phantom POLLIN event
| [Monday 14 March 2011] [19:44:09] <Guthur>	oh wait nvm, something more fundamentally wrong with my code
| [Monday 14 March 2011] [19:47:03] <Guthur>	yep I was being a silly programmer
| [Monday 14 March 2011] [23:40:48] <michelp>	has anyone yet in the community explored distributed shared memory stores in python over 0mq?
| [Monday 14 March 2011] [23:41:15] <michelp>	thinking in terms of doing transactional changes to objects that get propagated to N nodes
| [Monday 14 March 2011] [23:43:58] <michelp>	it's something i've always taken an interest in, but the problem of distributing changes to threads, processes, and boxes uniformly has stumped me
| [Tuesday 15 March 2011] [04:46:06] <guido_g>	good morning
| [Tuesday 15 March 2011] [05:20:35] <sustrik>	morning
| [Tuesday 15 March 2011] [05:28:34] <Evet>	morning
| [Tuesday 15 March 2011] [05:29:10] <gambi>	morning :)
| [Tuesday 15 March 2011] [05:44:33] <pieter_hintjens>	g'morning
| [Tuesday 15 March 2011] [06:31:06] <private_meta>	sustrik: mind i talk to you about it outside the mailing lisT?
| [Tuesday 15 March 2011] [06:31:08] <private_meta>	*list
| [Tuesday 15 March 2011] [06:31:29] <private_meta>	sustrik: the zmq::version i mean
| [Tuesday 15 March 2011] [06:39:31] <sustrik>	sure
| [Tuesday 15 March 2011] [06:39:33] <sustrik>	what's up?
| [Tuesday 15 March 2011] [06:41:29] <private_meta>	about the pointer vs reference thing
| [Tuesday 15 March 2011] [06:42:07] <private_meta>	imho the only valid reason to use that would be to be coherent with the other function prototypes
| [Tuesday 15 March 2011] [06:44:03] <sustrik>	right
| [Tuesday 15 March 2011] [06:44:08] <sustrik>	it's a matter of style
| [Tuesday 15 March 2011] [06:44:20] <private_meta>	Bad style, according to a lot of people
| [Tuesday 15 March 2011] [06:44:32] <sustrik>	sure
| [Tuesday 15 March 2011] [06:44:46] <sustrik>	the point is that it's the style that C++ API uses now
| [Tuesday 15 March 2011] [06:44:52] <sustrik>	you can fork and restyle it
| [Tuesday 15 March 2011] [06:46:13] <private_meta>	Wouldn't really help anyway
| [Tuesday 15 March 2011] [06:46:56] <sustrik>	the thing with the style is you have to decide on it once and then keep it
| [Tuesday 15 March 2011] [06:47:04] <sustrik>	some may consider it ugly
| [Tuesday 15 March 2011] [06:47:13] <sustrik>	but that's how it goes
| [Tuesday 15 March 2011] [06:48:52] <private_meta>	hmm... it's just nowhere near defensive programming, maybe that's what bothers me, I was taught to do that over and over
| [Tuesday 15 March 2011] [06:49:30] <sustrik>	shrug
| [Tuesday 15 March 2011] [06:49:34] <sustrik>	you can fork it
| [Tuesday 15 March 2011] [06:50:03] <sustrik>	breaking backward comatibility because of styling issues is not worth it
| [Tuesday 15 March 2011] [06:50:33] <private_meta>	Yeah, but as I said, it wouldn't really help, and I would break my own compatibility
| [Tuesday 15 March 2011] [06:50:39] <private_meta>	It's not worth it
| [Tuesday 15 March 2011] [06:50:43] <sustrik>	ack
| [Tuesday 15 March 2011] [06:53:23] <private_meta>	well ok, even if I'm not quite agree with the reasoning, I can't change it anyway (and no, changing it by forking isn't what I call a helpful solution)
| [Tuesday 15 March 2011] [06:54:21] <sustrik>	would you prefer breaking everyone's applications instead?
| [Tuesday 15 March 2011] [06:54:33] <private_meta>	That's why I said I can't change it
| [Tuesday 15 March 2011] [06:54:37] <sustrik>	exactly
| [Tuesday 15 March 2011] [06:54:42] <sustrik>	nothing to do here
| [Tuesday 15 March 2011] [06:54:51] <private_meta>	"Go on, nothing to see"
| [Tuesday 15 March 2011] [06:54:56] <sustrik>	:)
| [Tuesday 15 March 2011] [06:55:27] <private_meta>	"Change what you can't accept, accept what you can't change" <-- accepting can be hard
| [Tuesday 15 March 2011] [07:38:38] <pieter_hintjens>	consistency is more important than accuracy in some cases
| [Tuesday 15 March 2011] [07:41:33] <pieter_hintjens>	private_meta: actually, it would be possible to change the C++ style for 3.0
| [Tuesday 15 March 2011] [07:58:51] <private_meta>	pieter_hintjens: ad consistency, I understand
| [Tuesday 15 March 2011] [07:59:04] <private_meta>	pieter_hintjens: ad 3.0, do you not plan backwards compatibility for 3.0?
| [Tuesday 15 March 2011] [08:11:41] <CIA-103>	zeromq2: 03Martin Sustrik 07master * r7045a4a 10/ (src/named_session.cpp src/named_session.hpp): 
| [Tuesday 15 March 2011] [08:11:41] <CIA-103>	zeromq2: Dead code removed from named_session.cpp
| [Tuesday 15 March 2011] [08:11:41] <CIA-103>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/fkOsT0
| [Tuesday 15 March 2011] [09:19:23] <Evet>	sustrik: have you benchmarked zeromq on debian-kfreebsd?
| [Tuesday 15 March 2011] [09:24:17] <sustrik>	Evet: no
| [Tuesday 15 March 2011] [09:24:18] <sustrik>	did you?
| [Tuesday 15 March 2011] [09:27:58] <Evet>	sustrik: downloading it now
| [Tuesday 15 March 2011] [09:28:57] <Evet>	it seems an interesting project
| [Tuesday 15 March 2011] [09:34:07] <sustrik>	yes
| [Tuesday 15 March 2011] [09:34:31] <sustrik>	have a look at http://www.zeromq.org/area:results
| [Tuesday 15 March 2011] [09:34:48] <sustrik>	if you get any numbers we can post the results on the website
| [Tuesday 15 March 2011] [10:06:57] <private_meta>	pieter_hintjens: What might be nice (and not too much work) for the guide, imho, would be a small example output of your code. 1) for those who go through the code to make sure they understood it right without running it 2) for those who want to translate to see a rough outline what the intended result is
| [Tuesday 15 March 2011] [10:32:04] <private_meta>	actually, overloading the C++ binding with by reference methods would be a good way to add the by reference functionality without breaking backwards compatibility
| [Tuesday 15 March 2011] [10:35:36] <pieter_hintjens>	private_meta: back, sorry, in meetings all day...
| [Tuesday 15 March 2011] [10:35:48] <pieter_hintjens>	actually you can make a new C++ binding at any time at all
| [Tuesday 15 March 2011] [10:35:50] <private_meta>	np, IRC is a patient protocol
| [Tuesday 15 March 2011] [10:36:06] <pieter_hintjens>	just as we have improvements to the other language bindings, orthogonally to 0MQ releases
| [Tuesday 15 March 2011] [10:37:12] <pieter_hintjens>	re the guide, yes, this is a good idea, I've done it in a few places but not systematically
| [Tuesday 15 March 2011] [10:38:28] <Evet>	do you think something like mongrel2 for xitami?
| [Tuesday 15 March 2011] [10:39:48] <pieter_hintjens>	Evet: xitami is dead, for several reasons
| [Tuesday 15 March 2011] [10:40:04] <pieter_hintjens>	i'm not sure what your question is... :-)
| [Tuesday 15 March 2011] [10:41:46] <Evet>	oh, xitami was my very first webserver
| [Tuesday 15 March 2011] [10:41:59] <Evet>	i have learnt perl on it :)
| [Tuesday 15 March 2011] [10:43:14] <private_meta>	pieter_hintjens: sorry for being slow and only arriving at the paranoid pirate pattern now, but I have a small question there. According to Figure 59 of the guide, the Lazy Pirate Client, the Paranoid Pirate Queue and the Paranoid Pirate Worker run at the same time, am I correct?
| [Tuesday 15 March 2011] [10:43:35] <pieter_hintjens>	yes, that's right
| [Tuesday 15 March 2011] [10:44:29] <pieter_hintjens>	I made them as three processes, rather than three threads in one process, so you can stop and start them independently
| [Tuesday 15 March 2011] [10:44:34] <private_meta>	So, I seem to be doing something wrong. I run ppqueue, then I run ppworker and I get an "Address already in use" error for the lpserver (which ought to run 2nd)
| [Tuesday 15 March 2011] [10:45:31] <private_meta>	ah wait
| [Tuesday 15 March 2011] [10:45:34] <pieter_hintjens>	you don't want to run lpserver
| [Tuesday 15 March 2011] [10:45:39] <private_meta>	i just realized that
| [Tuesday 15 March 2011] [10:45:40] <private_meta>	stupid me
| [Tuesday 15 March 2011] [10:45:48] <private_meta>	I wanted lpclient and ran lpserver
| [Tuesday 15 March 2011] [10:45:51] <pieter_hintjens>	it's not as simple as it could be...
| [Tuesday 15 March 2011] [10:45:51] <private_meta>	>_<
| [Tuesday 15 March 2011] [10:46:06] <private_meta>	argh
| [Tuesday 15 March 2011] [10:46:26] <private_meta>	I'm looking through it and thinking and thinking and I don't realize I use the wrong one
| [Tuesday 15 March 2011] [10:46:31] <private_meta>	lemme see
| [Tuesday 15 March 2011] [10:47:40] <private_meta>	Sorry for bothering you :/
| [Tuesday 15 March 2011] [10:48:18] <sustrik>	guys, an idea: what about factoring the C++ binding out of 0mq core in 3.0?
| [Tuesday 15 March 2011] [10:48:53] <yrashk>	sustrik: ....and merging erlzmq2 in :D haha, kidding, sorry
| [Tuesday 15 March 2011] [10:49:19] <sustrik>	well, i mean, all the other bindings are separate projects, why should c++ differ
| [Tuesday 15 March 2011] [10:50:58] <yrashk>	yeah, it makes some sense
| [Tuesday 15 March 2011] [10:51:17] <yrashk>	although I am ok with c++ binding living in there
| [Tuesday 15 March 2011] [10:51:21] <guido_g>	good idea
| [Tuesday 15 March 2011] [10:51:58] <sustrik>	the downside is that it ties the C++ binding to the core too much
| [Tuesday 15 March 2011] [10:52:23] <sustrik>	so there's little space for alternative implementations
| [Tuesday 15 March 2011] [10:52:40] <sustrik>	binding-only releases (without dragging the core along)
| [Tuesday 15 March 2011] [10:52:43] <sustrik>	etc.
| [Tuesday 15 March 2011] [10:54:01] <yrashk>	sustrik: I'd vote for keeping c++ binding
| [Tuesday 15 March 2011] [10:54:59] <pieter_hintjens>	sustrik: that was the idea, forking it out, but it needs to be folded back in for a real distribution
| [Tuesday 15 March 2011] [10:55:18] <sustrik>	sure, same as other bindings
| [Tuesday 15 March 2011] [10:55:24] <pieter_hintjens>	exactly the same
| [Tuesday 15 March 2011] [10:55:41] <pieter_hintjens>	makes it much easier to contribute to, improve, etc.
| [Tuesday 15 March 2011] [10:55:49] <sustrik>	ack
| [Tuesday 15 March 2011] [10:55:57] <sustrik>	i am +1 myself
| [Tuesday 15 March 2011] [10:56:08] <pieter_hintjens>	I'm +1 for making it consistent with other languages
| [Tuesday 15 March 2011] [10:56:08] <sustrik>	so far 3 +1's and a single -1
| [Tuesday 15 March 2011] [10:56:44] <pieter_hintjens>	in any case I want to explore how to make packages that include the popular bindings
| [Tuesday 15 March 2011] [10:57:06] <sustrik>	that's something i am wondering about for a long time
| [Tuesday 15 March 2011] [10:57:28] <sustrik>	core + java + ruby + python + .net
| [Tuesday 15 March 2011] [10:57:34] <pieter_hintjens>	the languages are: C++, C#, clisp, Java, Perl, PHP, Python, Ruby
| [Tuesday 15 March 2011] [10:57:47] <pieter_hintjens>	going by the % of translations of the guide examples
| [Tuesday 15 March 2011] [10:58:08] <sustrik>	ack
| [Tuesday 15 March 2011] [10:58:13] <mato>	pieter_hintjens: you'll want to keep in mind that $LANGUAGE generally has it's own way of distributing extensions...
| [Tuesday 15 March 2011] [10:58:23] <pieter_hintjens>	mato: indeed, this is the fun part
| [Tuesday 15 March 2011] [10:58:30] <mato>	pieter_hintjens: e.g. Perl -> CPAN, Ruby -> gem, etc.
| [Tuesday 15 March 2011] [10:58:43] <pieter_hintjens>	exactl
| [Tuesday 15 March 2011] [10:58:47] <pieter_hintjens>	y
| [Tuesday 15 March 2011] [10:58:58] <sustrik>	and on win32 people expect monolithic installer, i would say
| [Tuesday 15 March 2011] [10:59:02] <mato>	then you have the linux distribution people packaging stuff on top of that separately
| [Tuesday 15 March 2011] [10:59:26] <pieter_hintjens>	so Windows is the easiest case, in many ways
| [Tuesday 15 March 2011] [11:00:47] <pieterh>	the process can't replace existing $LANGUAGE distribution processes but it can automate them
| [Tuesday 15 March 2011] [11:01:58] <pieterh>	i'll spend some time studying this and make a few proposals
| [Tuesday 15 March 2011] [11:02:18] <pieterh>	it probably will need cooperation from binding authors / communities to make work well
| [Tuesday 15 March 2011] [11:02:27] <sustrik>	that will be useful
| [Tuesday 15 March 2011] [11:02:37] <pieterh>	ok
| [Tuesday 15 March 2011] [11:04:06] <pieterh>	sustrik: the poll for zmq_term is tied afaics, 4/4
| [Tuesday 15 March 2011] [11:04:51] <pieterh>	there was one vote for infinity here on irc afair
| [Tuesday 15 March 2011] [11:06:07] <Guthur>	+1 the extraction of C++ from core
| [Tuesday 15 March 2011] [11:06:21] <Guthur>	+1 for extraction of C++ from the world
| [Tuesday 15 March 2011] [11:06:29] <sustrik>	:)
| [Tuesday 15 March 2011] [11:06:50] <sustrik>	pieterh: let's wait couple of days more
| [Tuesday 15 March 2011] [11:07:08] <pieterh>	I do want to close the 2.1 release
| [Tuesday 15 March 2011] [11:07:22] <pieterh>	there is not sufficient mandate afaics to revert the behavior
| [Tuesday 15 March 2011] [11:07:40] <sustrik>	looks like
| [Tuesday 15 March 2011] [11:07:47] <sustrik>	let's go for current solution then
| [Tuesday 15 March 2011] [11:08:15] <pieterh>	well, this saves me a lot of work in the Guide, but I have this sinking feeling about it
| [Tuesday 15 March 2011] [11:08:30] <pieterh>	these semantics won't change again in 3.0, right?
| [Tuesday 15 March 2011] [11:08:46] <sustrik>	nope
| [Tuesday 15 March 2011] [11:09:30] <pieterh>	then it's defensible, and the poll shows we did discuss the issue ad nauseam
| [Tuesday 15 March 2011] [11:09:43] <pieterh>	if anyone still complains, they should have spoken up in time
| [Tuesday 15 March 2011] [11:09:43] <sustrik>	ok
| [Tuesday 15 March 2011] [11:09:49] <pieterh>	excellent
| [Tuesday 15 March 2011] [11:10:03] <private_meta>	aw not again
| [Tuesday 15 March 2011] [11:10:29] <pieterh>	private_meta: port in use?
| [Tuesday 15 March 2011] [11:10:33] <private_meta>	no
| [Tuesday 15 March 2011] [11:10:42] <private_meta>	Bad file descriptor
| [Tuesday 15 March 2011] [11:10:42] <private_meta>	nbytes != -1 (mailbox.cpp:241)
| [Tuesday 15 March 2011] [11:10:55] <private_meta>	don't remember right now what the error was when I had that one previously
| [Tuesday 15 March 2011] [11:11:07] <mato>	pieterh: so what is the decision on zmq_term? 
| [Tuesday 15 March 2011] [11:11:17] <mato>	pieterh: keep the current behaviour?
| [Tuesday 15 March 2011] [11:11:21] <pieterh>	mato: yes
| [Tuesday 15 March 2011] [11:11:27] <sustrik>	private_meta: is it a reproducible use case?
| [Tuesday 15 March 2011] [11:11:29] <mato>	ok, understood
| [Tuesday 15 March 2011] [11:11:45] <pieterh>	the problem, and the reason for the discussion, is that people migrating from 2.0 _will_ be systematically hit by this
| [Tuesday 15 March 2011] [11:11:47] <private_meta>	sustrik: it's my translation of ppworker (not yet submitted)
| [Tuesday 15 March 2011] [11:11:56] <cremes>	private_meta:  i have seen that assert when i ran out of sockets and/or ran out of file descriptors
| [Tuesday 15 March 2011] [11:12:01] <cremes>	should be easy to reproduce
| [Tuesday 15 March 2011] [11:12:11] <sustrik>	private_meta: iirc such a problem can happen if you close the fd you get fromZMQ_FD
| [Tuesday 15 March 2011] [11:12:34] <sustrik>	socket option i mean
| [Tuesday 15 March 2011] [11:12:34] <cremes>	yep, that causes it too
| [Tuesday 15 March 2011] [11:12:55] <sustrik>	cremes: if you can reproduce it, i would fix it
| [Tuesday 15 March 2011] [11:14:12] <bpl29>	Is there a reference page for ZMQ objects such as context and socket?
| [Tuesday 15 March 2011] [11:14:31] <pieterh>	bpl29: yes, at http://rfc.zeromq.org
| [Tuesday 15 March 2011] [11:14:34] <private_meta>	happens when calling zmq::poll
| [Tuesday 15 March 2011] [11:14:49] <pieterh>	bpl29: sorry! http://api.zeromq.org...
| [Tuesday 15 March 2011] [11:14:50] <private_meta>	wait, i think I know
| [Tuesday 15 March 2011] [11:15:04] <private_meta>	k, got it
| [Tuesday 15 March 2011] [11:15:30] <bpl29>	thanks pieterh.  Am I wrong or is this just a function reference though?
| [Tuesday 15 March 2011] [11:15:52] <pieterh>	bpl29: these objects are not accessed except via functions
| [Tuesday 15 March 2011] [11:15:56] <pieterh>	opaque structures
| [Tuesday 15 March 2011] [11:16:24] <bpl29>	Ah, I see!  Thank you!
| [Tuesday 15 March 2011] [11:17:34] <cremes>	sustrik: i'll submit a small C example that reproduces the EBADF
| [Tuesday 15 March 2011] [11:26:31] <Guthur>	Is 0MQ buildable on solaris 8
| [Tuesday 15 March 2011] [11:26:39] <Guthur>	and is Sun Studio the only option
| [Tuesday 15 March 2011] [11:26:41] <private_meta>	pieterh: again a (for you maybe opaque) question: In the ppqueue, ppworker, lpclient scenario, shouldn't lpclient connect at least ONCE? it only tells me it's trying to connect
| [Tuesday 15 March 2011] [11:33:18] <Guthur>	pieter: which pattern would you suggest for a  N client to N servers, where the servers are processing requests to retrieve data from files
| [Tuesday 15 March 2011] [11:49:51] <cremes>	Guthur: i'd use a REQ socket on the client, REP on the server and a QUEUE device in the middle to load balance
| [Tuesday 15 March 2011] [11:56:00] <Guthur>	cremes: Probably a wise choice, I have to resist the temptation to over engineer
| [Tuesday 15 March 2011] [11:57:18] <cremes>	Guthur: i suspect that over the next several months the "lazy pirate" patterns will become dominant
| [Tuesday 15 March 2011] [11:57:43] <Guthur>	I was being drawn to Ch4 patterns actually
| [Tuesday 15 March 2011] [11:57:50] <Guthur>	I've only started reading it though
| [Tuesday 15 March 2011] [11:58:10] <Guthur>	I got hung up debugging peering3 in C#
| [Tuesday 15 March 2011] [11:58:29] <Guthur>	massive 'doh' moment on my part there
| [Tuesday 15 March 2011] [12:04:08] <private_meta>	I'm still curious if the way the zguide C variant of the paranoid pirate is intended behavior. If i run the c example, the lazy pirate client never connects
| [Tuesday 15 March 2011] [12:04:14] <private_meta>	It shouldn't be intended
| [Tuesday 15 March 2011] [12:04:30] <private_meta>	But somehow I don't think it should be an error on my side, I didn't really change anything
| [Tuesday 15 March 2011] [12:47:19] <michelp>	morning
| [Tuesday 15 March 2011] [12:48:04] <michelp>	i asked this q last night but i think everyone was in bed.  has anyone in the community experimented with using 0mq to do shared memory objects across threads/procs/boxes in python?
| [Tuesday 15 March 2011] [12:48:35] <michelp>	it's something that's always interested me but i've never found a suitable transport for the underlying data transfer
| [Tuesday 15 March 2011] [12:49:24] <michelp>	seems like 0mq is ideal for things like distributing new versions of objects and doing two or three phase commit between a group of data managers
| [Tuesday 15 March 2011] [13:15:54] <Guthur>	michelp: sounds like an interesting project
| [Tuesday 15 March 2011] [13:16:31] <Guthur>	you could maybe utilize something like tokyo cabinet as well
| [Tuesday 15 March 2011] [13:17:28] <michelp>	for storage?  i was thinking of shipping around pickles so those would go well into a key value store where the key is the oid
| [Tuesday 15 March 2011] [13:18:29] <michelp>	it would be nice for there to be a way for a new node to easily bootstrap objects and for objects to survive cluster destruction
| [Tuesday 15 March 2011] [13:19:57] <michelp>	might even be possible for there to be more objects in the store than nodes have memory if there was a way to manage that.  thanks for the idea Guthur :)
| [Tuesday 15 March 2011] [13:20:34] <Guthur>	also check out some of the stuff from Ch4 of the guide
| [Tuesday 15 March 2011] [13:20:39] <Guthur>	for reliability
| [Tuesday 15 March 2011] [13:20:46] <michelp>	yeah i'm about halfway through ch 3 :)
| [Tuesday 15 March 2011] [13:21:00] <michelp>	almost there, it's a big guide, which is totally awesome
| [Tuesday 15 March 2011] [13:21:41] <michelp>	the best documentation i've found on rabbit is a blog post.  the guide alone has convinced me that 0mq is the future, i haven't even written any code yet :)
| [Tuesday 15 March 2011] [13:22:51] <michelp>	the guide would make an excellent 5 day course.  does anyone do 0mq training?
| [Tuesday 15 March 2011] [13:23:14] <Guthur>	not that I am aware
| [Tuesday 15 March 2011] [13:23:32] <Guthur>	I'm sure for corporate customers Imatix might be available for such
| [Tuesday 15 March 2011] [13:23:39] <Guthur>	but don't quote me on that
| [Tuesday 15 March 2011] [13:24:25] <michelp>	their services page does have various support level costs, but we're a US non-profit so it's a little out of our price range for a whole week
| [Tuesday 15 March 2011] [13:25:11] <michelp>	if i worked for a corporation i'd be spending their money on it in a minute :)
| [Tuesday 15 March 2011] [13:26:01] <michelp>	know if anyone in the 0mq community is going to OSCON this year?  It's here in my home town and we could get together for a BOF session
| [Tuesday 15 March 2011] [13:27:44] <Guthur>	I'm not sure
| [Tuesday 15 March 2011] [13:27:50] <Guthur>	there is sometimes meetups 
| [Tuesday 15 March 2011] [13:28:00] <Guthur>	there was one in San Fran recently
| [Tuesday 15 March 2011] [13:35:33] <Guthur>	anyone built jzmq on windows recently
| [Tuesday 15 March 2011] [13:38:15] <pieterh>	michelp: iMatix does 0MQ training, sure
| [Tuesday 15 March 2011] [13:39:35] <michelp>	pieterh, is it the usual services rate quoted here? http://www.imatix.com/services
| [Tuesday 15 March 2011] [13:39:54] <pieterh>	private_meta: (a) lpclient should connect, yes, I had '-v' to enable verbose tracing of messages in the C code, that helps. (b) let me retest the C code...
| [Tuesday 15 March 2011] [13:40:02] <pieterh>	michelp: yes, those are the usual rates
| [Tuesday 15 March 2011] [13:40:32] <pieterh>	however if you're a non-profit, and you need help, you will find that it's readily available here
| [Tuesday 15 March 2011] [13:41:13] <michelp>	yeah you guys have definitely be a great help so far!
| [Tuesday 15 March 2011] [13:41:14] <pieterh>	mostly, you will benefit most by also contributing somehow to the community
| [Tuesday 15 March 2011] [13:41:44] <Guthur>	I'm getting an error building the jzmq binding, error copying files
| [Tuesday 15 March 2011] [13:41:57] <Guthur>	and Java users around
| [Tuesday 15 March 2011] [13:41:59] <pieterh>	Guthur: I've not tried it in a long time... what's the error?
| [Tuesday 15 March 2011] [13:42:35] <Guthur>	Error	1	error MSB3073: The command "copy ..\config.hpp ..\..\..\src javac ..\..\..\src\org\zeromq\ZMQ.java ..\..\..\src\org\zeromq\ZMQException.java ..\..\..\src\org\zeromq\ZMQForwarder.java ..\..\..\src\org\zeromq\ZMQQueue.java ..\..\..\src\org\zeromq\ZMQStreamer.java  :VCEnd" exited with code 9009.	C:\Program Files\MSBuild\Microsoft.Cpp\v4.0\Microsoft.CppCommon.targets	103	6	jzmq 
| [Tuesday 15 March 2011] [13:42:49] <pieterh>	michelp: with respect to shared objects across threads/processes, it's a design I'm going to make for Ch5 of the Guide
| [Tuesday 15 March 2011] [13:42:58] <private_meta>	pieterh: thanks for retesting
| [Tuesday 15 March 2011] [13:44:24] <pieterh>	Guthur: I'm searching what exit code 9009 means...
| [Tuesday 15 March 2011] [13:44:40] <pieterh>	try running that command by hand in a shell, does it work?
| [Tuesday 15 March 2011] [13:45:47] <pieterh>	"9009	DNS server not authoritative for zone."???
| [Tuesday 15 March 2011] [13:45:49] <Guthur>	2 secs
| [Tuesday 15 March 2011] [13:46:06] <michelp>	pieterh, wow awesome.  i'm tinkering with the idea here in python, what language were you going to focus on?
| [Tuesday 15 March 2011] [13:46:37] <pieterh>	michelp: I always make the examples in C, but they can be translated into other languages quite simply
| [Tuesday 15 March 2011] [13:47:01] <pieterh>	the idea is to make a distributed key-value store using a mix of pubsub and req/rep
| [Tuesday 15 March 2011] [13:47:44] <Guthur>	umm syntax is incorrect
| [Tuesday 15 March 2011] [13:48:09] <pieterh>	Guthur: syntax looks correct, yes, and the command runs successfully?
| [Tuesday 15 March 2011] [13:48:19] <pieterh>	private_meta: indeed, it doesn't work... checking why...
| [Tuesday 15 March 2011] [13:53:15] <Guthur>	oh wait
| [Tuesday 15 March 2011] [13:53:30] <michelp>	pieterh, sound very interesting, i'll keep tinkering on my end for learning purposes until it comes out.  I'm also happy to proof read anything from a beginners point of view if you need that
| [Tuesday 15 March 2011] [13:53:51] <pieterh>	michelp: what really helps is running the examples from the guide, each one, and verifying that they work
| [Tuesday 15 March 2011] [13:54:14] <michelp>	yeah i've been doing that, which is why i'm only up to ch 3 at this point
| [Tuesday 15 March 2011] [13:54:32] <michelp>	i've been running them in python but I know C so i've been using both as a guide to understanding
| [Tuesday 15 March 2011] [13:54:44] <pieterh>	:-) you won't need any training
| [Tuesday 15 March 2011] [13:55:27] <michelp>	hopefully not, but we have 7 folks on our team and i was thinking it might be worth having a group training session in the future if we can swing it
| [Tuesday 15 March 2011] [13:55:34] <Guthur>	pieterh: the javac wasn't in the Path
| [Tuesday 15 March 2011] [13:55:41] <Guthur>	hopefully should work now
| [Tuesday 15 March 2011] [13:55:47] <michelp>	which is one reason why i was hoping maybe someone from imatix would be at OSCON :)
| [Tuesday 15 March 2011] [13:56:08] <pieterh>	Guthur: worth noting on the Java bindings page, perhaps (you can edit it)
| [Tuesday 15 March 2011] [13:56:17] <Guthur>	sure
| [Tuesday 15 March 2011] [13:56:33] <pieterh>	michelp: we didn't plan to go
| [Tuesday 15 March 2011] [13:56:43] <Guthur>	How does one generate a lib file again?
| [Tuesday 15 March 2011] [13:56:52] <Guthur>	oh wait I think that is documented
| [Tuesday 15 March 2011] [13:56:58] <michelp>	yeah it's expensive.  not to mention travel.  are you guys in the netherlands?
| [Tuesday 15 March 2011] [13:57:22] <pieterh>	Brussels
| [Tuesday 15 March 2011] [13:57:29] <pieterh>	Belgium
| [Tuesday 15 March 2011] [13:58:05] <pieterh>	It's more a question of time really, plus we've found that presentations from actual 0MQ users are more effective than our own, often
| [Tuesday 15 March 2011] [13:59:04] <michelp>	ah nice, i've never been.  been to just about every country around it except Luxembourg
| [Tuesday 15 March 2011] [13:59:41] <michelp>	one of these days hopefully
| [Tuesday 15 March 2011] [14:00:10] <Guthur>	ok binding page updated
| [Tuesday 15 March 2011] [14:02:13] <pieterh>	private_meta: there was a bug in ppqueue
| [Tuesday 15 March 2011] [14:02:24] <pieterh>	it was inserting an extra null frame at the front of the message
| [Tuesday 15 March 2011] [14:03:11] <pieterh>	line 165, in the C code:
| [Tuesday 15 March 2011] [14:03:13] <pieterh>	-            zmsg_wrap (msg, identity, "");
| [Tuesday 15 March 2011] [14:03:13] <pieterh>	+            zmsg_push (msg, identity);
| [Tuesday 15 March 2011] [14:03:21] <pieterh>	thanks for catching this!
| [Tuesday 15 March 2011] [14:06:14] <private_meta>	thanks for fixing it
| [Tuesday 15 March 2011] [14:06:25] <private_meta>	I'll test it a lil while later
| [Tuesday 15 March 2011] [14:06:53] <sustrik>	pieterh: an idea about version numbering
| [Tuesday 15 March 2011] [14:07:19] <Guthur>	is there something on the wiki about building libzmq as a static lib
| [Tuesday 15 March 2011] [14:07:24] <sustrik>	the guarantees for minor version number bump is not clear atm
| [Tuesday 15 March 2011] [14:07:36] <Guthur>	the java binding seems to want one
| [Tuesday 15 March 2011] [14:07:55] <sustrik>	what if it says: "minor version number is incremented when stable branch is forked from the master"
| [Tuesday 15 March 2011] [14:09:25] <sustrik>	Guthur: what OS?
| [Tuesday 15 March 2011] [14:09:56] <Guthur>	sustrik: Win32
| [Tuesday 15 March 2011] [14:10:00] <Guthur>	I think I have it though
| [Tuesday 15 March 2011] [14:10:02] <Guthur>	sorry
| [Tuesday 15 March 2011] [14:10:13] <Guthur>	sustrik: btw why is there an @ before your name
| [Tuesday 15 March 2011] [14:10:27] <Guthur>	are you ops
| [Tuesday 15 March 2011] [14:10:34] <sustrik>	Guthur: iirc building a static lib on win32 is a problem
| [Tuesday 15 March 2011] [14:10:47] <sustrik>	yup
| [Tuesday 15 March 2011] [14:11:04] <Guthur>	umm yeah it does seem to be an issue
| [Tuesday 15 March 2011] [14:11:10] <Guthur>	this is problematic
| [Tuesday 15 March 2011] [14:11:25] <Guthur>	jzmq wants a lib
| [Tuesday 15 March 2011] [14:11:33] <sustrik>	but jzmq used to work with dlls before
| [Tuesday 15 March 2011] [14:11:42] <sustrik>	have that changed?
| [Tuesday 15 March 2011] [14:12:01] <Guthur>	umm not sure, it's complaining at me about not finding a libzmq.lib
| [Tuesday 15 March 2011] [14:13:58] <sustrik>	ah
| [Tuesday 15 March 2011] [14:14:03] <sustrik>	win32 is strange
| [Tuesday 15 March 2011] [14:14:10] <Guthur>	yes, that it is
| [Tuesday 15 March 2011] [14:14:25] <Guthur>	not my first choice to be sure
| [Tuesday 15 March 2011] [14:14:31] <sustrik>	.lib is used even when doing dynamic linking
| [Tuesday 15 March 2011] [14:14:41] <sustrik>	it's basically a table of entry points
| [Tuesday 15 March 2011] [14:14:55] <sustrik>	it's located in lib subdir afterm msvc build
| [Tuesday 15 March 2011] [14:14:56] <sustrik>	iirc
| [Tuesday 15 March 2011] [14:17:08] <Guthur>	so it should be getting generated
| [Tuesday 15 March 2011] [14:22:32] <Guthur>	where is the platform tweaks
| [Tuesday 15 March 2011] [14:27:18] <Guthur>	i can generate a lib but then I get loads of unresolved external symbols
| [Tuesday 15 March 2011] [14:42:13] <sustrik>	like zmq_init() and such?
| [Tuesday 15 March 2011] [14:44:13] <Guthur>	__imp__zmq_init
| [Tuesday 15 March 2011] [14:44:15] <Guthur>	etc
| [Tuesday 15 March 2011] [14:48:23] <sustrik>	can you report that on the mailing list
| [Tuesday 15 March 2011] [14:48:57] <sustrik>	it looks like it is possibly connected to the recent changes regarding symbol visibility
| [Tuesday 15 March 2011] [14:49:32] <Guthur>	ah sure, I'll an old version to check
| [Tuesday 15 March 2011] [14:49:40] <Guthur>	I'd really like to have something for tomorrw
| [Tuesday 15 March 2011] [14:49:54] <Guthur>	I colleague wants to bridge from JMS to C#
| [Tuesday 15 March 2011] [14:50:16] <Guthur>	with possibility for client/server setup
| [Tuesday 15 March 2011] [14:50:28] <Guthur>	I'd like to show him a 0MQ solution
| [Tuesday 15 March 2011] [14:51:31] <Guthur>	sustrik: when was that update you mentioned
| [Tuesday 15 March 2011] [15:22:46] <mikko>	pieterh: there?
| [Tuesday 15 March 2011] [16:00:35] <sustrik>	Guthur: december, i think
| [Tuesday 15 March 2011] [16:04:47] <Guthur>	sustrik, ok, I'll try an earlier version
| [Tuesday 15 March 2011] [16:05:49] <Guthur>	I'm back home now though, on a much saner platform, hehe
| [Tuesday 15 March 2011] [17:11:26] <mikko>	pieterh: there now?
| [Tuesday 15 March 2011] [18:05:49] <mikko>	Guthur: are you michael?
| [Tuesday 15 March 2011] [18:07:07] <Guthur>	mikko, Indeed
| [Tuesday 15 March 2011] [18:07:52] <mikko>	http://www.mansysadmin.com/2011/03/using-zeromq-framework-with-visual-studio-2010-tutorial/
| [Tuesday 15 March 2011] [18:08:00] <mikko>	is this related to your problem?
| [Tuesday 15 March 2011] [18:08:10] <mikko>	i remember something related to VS2010 being funny
| [Tuesday 15 March 2011] [18:08:46] <Guthur>	I haven't been encountering any issues until I tried jzmq
| [Tuesday 15 March 2011] [18:09:22] <Guthur>	I'll double check that though
| [Tuesday 15 March 2011] [18:09:40] <Guthur>	but I am confident it was outputting to the correct directory
| [Tuesday 15 March 2011] [18:09:56] <Guthur>	I'm just freeing up some space on my wins VM here, then I will try again
| [Tuesday 15 March 2011] [18:10:25] 	 * Guthur made the mistake of thinking 20gb would be enough for windows and some tools
| [Tuesday 15 March 2011] [18:23:38] <sed>	Is anyone around to answer a couple of questions about ZMQ
| [Tuesday 15 March 2011] [18:23:40] <sed>	?
| [Tuesday 15 March 2011] [18:28:41] <Guthur>	ask and you shall receive...
| [Tuesday 15 March 2011] [18:28:44] <Guthur>	...maybe
| [Tuesday 15 March 2011] [18:31:37] <cremes>	sed: that means yes
| [Tuesday 15 March 2011] [18:31:57] <sed>	we have been testing out ZMQ for about a month and are very impressed with what it can do.  However we have noticed memory issues with the bindings in C C++ and perl.  
| [Tuesday 15 March 2011] [18:32:29] <sed>	over the course of several weeks we see memory usage rise uniformally across multiple servers
| [Tuesday 15 March 2011] [18:32:51] <sed>	also when running tests on single nodes top shows usage increasing
| [Tuesday 15 March 2011] [18:33:22] <mikko>	sed: are you closing the messages ?
| [Tuesday 15 March 2011] [18:33:24] <sed>	qwe are trying to identify the cause of this and what steps can be taken to avoid having to restart every 2 weeks
| [Tuesday 15 March 2011] [18:33:27] <sed>	yes
| [Tuesday 15 March 2011] [18:33:54] <cremes>	sed: are you closing and recreating sockets often?
| [Tuesday 15 March 2011] [18:34:21] <sed>	no  the sockets remain open
| [Tuesday 15 March 2011] [18:35:05] <cremes>	it's hard to say; an example that illustrates the problem in C or C++ would be great
| [Tuesday 15 March 2011] [18:35:28] <cremes>	i have seen some memory leaks but they are due to closing/reopening sockets very rapidly
| [Tuesday 15 March 2011] [18:35:43] <cremes>	i haven't heard about memory leakage with sockets that remain open indefinitely
| [Tuesday 15 March 2011] [18:36:06] <cremes>	are you running 2.1.x or 2.0.x?
| [Tuesday 15 March 2011] [18:36:56] <sed>	2.1.x
| [Tuesday 15 March 2011] [18:37:31] <cremes>	what kind of sockets? (btw, feel free to provide more details without requiring us to interrogate you)
| [Tuesday 15 March 2011] [18:38:11] <sed>	pulling up example code now   1 sec
| [Tuesday 15 March 2011] [18:39:29] <sed>	#include <stdio.h>
| [Tuesday 15 March 2011] [18:39:29] <sed>	#include <iostream>
| [Tuesday 15 March 2011] [18:39:29] <sed>	#include "zmq.hpp"
| [Tuesday 15 March 2011] [18:39:29] <sed>	int main(int argc, char *argv[]) {
| [Tuesday 15 March 2011] [18:39:29] <sed>	    int type, tm, uid, pid, city;
| [Tuesday 15 March 2011] [18:39:30] <sed>	    char msg[20000], ip[20],  host[100], cont[100], act[100], post[2000], get[2000];
| [Tuesday 15 March 2011] [18:39:32] <sed>	     // prepare our sockets and context with 1 I/O thread
| [Tuesday 15 March 2011] [18:39:34] <sed>	    zmq::context_t context(1);
| [Tuesday 15 March 2011] [18:39:36] <sed>	    // Connect to subscriber
| [Tuesday 15 March 2011] [18:39:38] <sed>	    zmq::socket_t subscriber(context, ZMQ_SUB);
| [Tuesday 15 March 2011] [18:39:40] <sed>	    subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);
| [Tuesday 15 March 2011] [18:39:42] <sed>	    subscriber.connect("tcp://s2hs-mw-cas1:5566");
| [Tuesday 15 March 2011] [18:39:44] <sed>	    while(1) {
| [Tuesday 15 March 2011] [18:39:46] <sed>	        zmq::message_t* message = new zmq::message_t;
| [Tuesday 15 March 2011] [18:39:48] <sed>	        subscriber.recv(message, ZMQ_NOBLOCK);
| [Tuesday 15 March 2011] [18:39:50] <sed>	        strncpy(msg, static_cast<char *>(message->data()), message->size());
| [Tuesday 15 March 2011] [18:39:54] <sed>	        delete message;
| [Tuesday 15 March 2011] [18:39:56] <sed>	        type = atoi(&msg[0]);
| [Tuesday 15 March 2011] [18:39:58] <sed>	        if (type == 3)
| [Tuesday 15 March 2011] [18:40:00] <sed>	        {
| [Tuesday 15 March 2011] [18:40:02] <sed>	            sscanf(msg,"%d %d %d %s %s %d %d %s %s %s %s", &type, &tm, &uid, &ip, &host, &pid, &city, &cont, &act, &post, &get);
| [Tuesday 15 March 2011] [18:40:05] <sed>	            std::cout << msg << "\n";
| [Tuesday 15 March 2011] [18:40:07] <sed>	        }
| [Tuesday 15 March 2011] [18:40:09] <sed>	        memset ( (void *) &msg, 0, sizeof(msg));
| [Tuesday 15 March 2011] [18:40:11] <sed>	    }
| [Tuesday 15 March 2011] [18:40:13] <sed>	    free (subscriber);
| [Tuesday 15 March 2011] [18:40:15] <sed>	    return 0;
| [Tuesday 15 March 2011] [18:40:17] <sed>	}
| [Tuesday 15 March 2011] [18:40:19] <sed>	that is a simple example script that we see the leak on
| [Tuesday 15 March 2011] [18:40:24] <Guthur>	sed: you really really, should use pastebin
| [Tuesday 15 March 2011] [18:40:52] <cremes>	sed: yeah, i can't read that; use gist.github.com or pastie.org to post code
| [Tuesday 15 March 2011] [18:41:25] <sed>	http://pastebin.com/mp9uJpCs
| [Tuesday 15 March 2011] [18:44:09] <cremes>	sed: how quickly does it leak? a few bytes for each message? is it a time based leak? e.g. it leaks even when messages aren't coming in
| [Tuesday 15 March 2011] [18:44:55] <sed>	we have 40000 messages/sec at all times.  Would have to run seperate tests to get that data
| [Tuesday 15 March 2011] [18:46:44] <Guthur>	i know it's not really relevant to the issue, but should that recv not be a blocking call
| [Tuesday 15 March 2011] [18:47:17] <cremes>	sed: does the publisher leak memory or just the subscriber?
| [Tuesday 15 March 2011] [18:47:19] <sed>	est 24k per minute
| [Tuesday 15 March 2011] [18:47:32] <cremes>	cool
| [Tuesday 15 March 2011] [18:47:55] <jond>	sed: I don't think recv should be non blocking, the message doesnt need to be on the heap and the free at end is just wrong
| [Tuesday 15 March 2011] [18:47:58] <cremes>	i see this is over tcp transport; any chance you could do a test where publisher & subscriber communicate via inproc transport?
| [Tuesday 15 March 2011] [18:50:11] <sed>	going to get a script running on the same box
| [Tuesday 15 March 2011] [18:50:47] <Guthur>	sed: Which platform, out of curiosity
| [Tuesday 15 March 2011] [18:52:07] <sed>	centos
| [Tuesday 15 March 2011] [18:54:34] <mikko>	sed: you shouldnt free subscriber
| [Tuesday 15 March 2011] [18:54:44] <mikko>	at the ed
| [Tuesday 15 March 2011] [18:55:07] <mikko>	end*
| [Tuesday 15 March 2011] [18:55:47] <mikko>	sed: also, you dont need to dynamically allocate 'message'
| [Tuesday 15 March 2011] [18:56:11] <sed>	yeah  that was just testing if it was related
| [Tuesday 15 March 2011] [18:56:46] <mikko>	that shouldnt leak
| [Tuesday 15 March 2011] [18:56:52] <mikko>	as far as i can see
| [Tuesday 15 March 2011] [18:57:20] <jond>	mikko: what time are you going to the pub tomorrow? hoping not to get my bag stolen this time.....
| [Tuesday 15 March 2011] [18:57:30] <mikko>	jond: dont take a bag with you!
| [Tuesday 15 March 2011] [18:57:43] <mikko>	jond: i probably get off from work around 17:30
| [Tuesday 15 March 2011] [18:57:53] <mikko>	heading to white horse after that so will be there around 18:00
| [Tuesday 15 March 2011] [18:58:03] <jond>	mikko: i have started doing that, learned the hard way
| [Tuesday 15 March 2011] [18:58:20] <mikko>	jond: hows life nowadays?
| [Tuesday 15 March 2011] [18:58:49] <mikko>	i guess we can chat tomorrow
| [Tuesday 15 March 2011] [18:59:08] <jond>	better than before xmas .....
| [Tuesday 15 March 2011] [18:59:09] <mikko>	sed: the only thing i can think of is if messages pile up
| [Tuesday 15 March 2011] [18:59:22] <jond>	i've found a bug in xrep today
| [Tuesday 15 March 2011] [18:59:48] <mikko>	jond: is it related to identities?
| [Tuesday 15 March 2011] [19:01:09] <jond>	when the pipe is full when processing identity message leaves socket in bad state
| [Tuesday 15 March 2011] [19:01:42] <jond>	i also don't think the HWM is honoured correctly but I'd need to show martin
| [Tuesday 15 March 2011] [19:02:05] <jond>	I'm just reading up on how to submit a patch cos I havent done one for months....
| [Tuesday 15 March 2011] [19:12:24] <mikko>	clone the repo, commit the change
| [Tuesday 15 March 2011] [19:12:31] <mikko>	and do git format-patch -s
| [Tuesday 15 March 2011] [19:19:59] <cremes>	this project has the most F'ed up submission policy; it's different from nearly every other github project
| [Tuesday 15 March 2011] [19:24:58] <jond>	mikko: I've sent patch to list. I think I got it right ...
| [Tuesday 15 March 2011] [19:26:09] <jond>	cremes: yep, it's like the version numbering. using master seems to be safest!!!
| [Tuesday 15 March 2011] [19:26:42] <cremes>	jond: don't get me started on that either :)
| [Tuesday 15 March 2011] [19:27:03] <cremes>	this is the only project i know that spawns a *new* repository for a branch
| [Tuesday 15 March 2011] [19:30:18] <Guthur>	a conscientious should be reached on this issue
| [Tuesday 15 March 2011] [19:30:30] <Guthur>	it seems to annoy a few people
| [Tuesday 15 March 2011] [19:30:32] <cremes>	concensus?
| [Tuesday 15 March 2011] [19:30:39] <Guthur>	cremes, yep
| [Tuesday 15 March 2011] [19:30:39] <cremes>	:)
| [Tuesday 15 March 2011] [19:30:50] <Guthur>	hehe trusted the spell checker too much
| [Tuesday 15 March 2011] [19:31:20] <cremes>	i don't feel like fighting this particular battle; i'm not much of a C guy so my patches (if any) will be rare
| [Tuesday 15 March 2011] [19:31:37] <mikko>	jond: didnt look at the contents but the format of the patch looks good
| [Tuesday 15 March 2011] [19:31:40] <cremes>	but it seems to me like it increases the learning curve quite a bit for people new to the project
| [Tuesday 15 March 2011] [19:32:10] <mikko>	im not fan of the dual repos either
| [Tuesday 15 March 2011] [19:32:19] <mikko>	but that seems to work for pieterh and sustrik so i guess its ok
| [Tuesday 15 March 2011] [19:32:35] <mikko>	the version numbering though is very odd for 2.1.x
| [Tuesday 15 March 2011] [19:33:14] <cremes>	yes
| [Tuesday 15 March 2011] [19:37:28] <jond>	mikko: just posted a note to the list about the operator void * on socket which allows that call to free to compile in example code above
| [Tuesday 15 March 2011] [20:00:37] <Guthur>	mikko, That Visual studio fix worked
| [Tuesday 15 March 2011] [20:00:45] <Guthur>	I successfully built the jzmq
| [Tuesday 15 March 2011] [20:00:47] <Guthur>	cheers
| [Tuesday 15 March 2011] [20:06:54] <sed>	set up an ipc connection and still see the memory increasing
| [Tuesday 15 March 2011] [20:18:56] <Guthur>	sed: I think that would be worth putting on the mail list
| [Tuesday 15 March 2011] [20:19:08] <Guthur>	to get wider exposure to the community
| [Tuesday 15 March 2011] [20:24:40] <cremes>	sed: try inproc; ipc still uses sockets
| [Tuesday 15 March 2011] [20:24:58] <sed>	k  will give that a shot
| [Tuesday 15 March 2011] [21:15:30] <sed>	thanks for answering questions guys.  Will be looking at this tomorow so will reach out further to the community.
| [Tuesday 15 March 2011] [22:43:47] <Honeyman>	Hello. I am using PyZMQ, and trying to do the REQ-REP communication, polling for the replies with the zmq.core.poll.select(), using timeout = 5.0 (seconds). But most of the times, this call returns immediately, without waiting for 5 seconds, returning empty lists, like if the socket is not available.
| [Tuesday 15 March 2011] [22:47:19] <Honeyman>	What could be the reason of this problem? A bug in the PyZMQ? If pyzmq's select() is using zmq_poll(), maybe it is zmq_poll who returns prematurely, not complying to the timeouts?
| [Tuesday 15 March 2011] [22:50:39] <Honeyman>	It is interesting that if I read from this socket no matter that it is absent from the rlist, the read always succeeds...
| [Tuesday 15 March 2011] [23:13:38] <Honeyman>	Uh, found myself, that's that known bug in ZMQ 2.0