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