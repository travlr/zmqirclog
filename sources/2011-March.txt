===============
2011-March
===============

| [Tuesday 01 March 2011] [00:29:05] <cremes>	andrewvc: for a little bit; what's up?
| [Tuesday 01 March 2011] [00:29:22] <andrewvc>	hey, some good news, wanted your thoughts on something
| [Tuesday 01 March 2011] [00:29:35] <andrewvc>	so, one issue with ffi-rzmq is depending on ffi
| [Tuesday 01 March 2011] [00:29:48] <andrewvc>	which is good in MRI, but bad in RBX and jRuby
| [Tuesday 01 March 2011] [00:30:02] <cremes>	right
| [Tuesday 01 March 2011] [00:30:16] <andrewvc>	https://github.com/andrewvc/em-zeromq/blob/master/em-zeromq.gemspec
| [Tuesday 01 March 2011] [00:30:21] <andrewvc>	did you know you can do that in a gemspec?
| [Tuesday 01 March 2011] [00:30:26] <cremes>	the jruby & rbx guys are working on a solution so the dependencies are tracked properly
| [Tuesday 01 March 2011] [00:30:26] <andrewvc>	I https://github.com/andrewvc/em-zeromq/blob/master/em-zeromq.gemspec#L20
| [Tuesday 01 March 2011] [00:30:29] <andrewvc>	err that line
| [Tuesday 01 March 2011] [00:30:33] <andrewvc>	I think that should work
| [Tuesday 01 March 2011] [00:30:51] <cremes>	true!
| [Tuesday 01 March 2011] [00:30:57] <cremes>	it's just ruby after all
| [Tuesday 01 March 2011] [00:31:01] <andrewvc>	yep
| [Tuesday 01 March 2011] [00:31:19] <andrewvc>	yeah, oruen contributed that bit
| [Tuesday 01 March 2011] [00:31:27] <cremes>	i'll commit something similar; thanks for the idea
| [Tuesday 01 March 2011] [00:31:31] <andrewvc>	but it should really be in ffi-rzmq not em-zeromq
| [Tuesday 01 March 2011] [00:31:36] <andrewvc>	cool, actually, one other thing
| [Tuesday 01 March 2011] [00:31:46] <andrewvc>	he switched me off bones and onto bundler for gem releases
| [Tuesday 01 March 2011] [00:32:01] <cremes>	yeah, i saw that; honeslty, bones has been pissing me off
| [Tuesday 01 March 2011] [00:32:09] <andrewvc>	yeah, it doesn't work well under rbx either
| [Tuesday 01 March 2011] [00:32:12] <cremes>	there is no compatibility between the 2.x and 3.x versions
| [Tuesday 01 March 2011] [00:32:29] <andrewvc>	oh? yeah it's a bit of overkill, the skeleton is nice, the rake tasks, not so much
| [Tuesday 01 March 2011] [00:32:51] <cremes>	it's kind of a big change for so little benefit... i'm open to suggestions and/or patches
| [Tuesday 01 March 2011] [00:33:07] <andrewvc>	yeah, I'll throw one together this week if you like the idea
| [Tuesday 01 March 2011] [00:33:19] <cremes>	sure
| [Tuesday 01 March 2011] [00:33:30] <andrewvc>	I'm excited with these changes it should finally be possible to just gem install and get everything you need
| [Tuesday 01 March 2011] [00:34:05] <cremes>	that is a nice little benefit; the 'ffi' gem situation has been poor for a while now
| [Tuesday 01 March 2011] [00:34:09] <andrewvc>	right now dripdrop needs a custom eventmachine and libzeromq2 and maybe ffi.
| [Tuesday 01 March 2011] [00:34:15] <andrewvc>	such a pain
| [Tuesday 01 March 2011] [00:34:18] <cremes>	true
| [Tuesday 01 March 2011] [00:34:28] <cremes>	every little bit to make it easier is worthwhile
| [Tuesday 01 March 2011] [00:35:22] <andrewvc>	yep, the only missing piece is probably an apt package for a current zeromq
| [Tuesday 01 March 2011] [00:35:47] <andrewvc>	but that's prolly about 2 years off :)
| [Tuesday 01 March 2011] [00:35:59] <cremes>	well, 0mq seems to be moving a little faster again... packages are always out of date
| [Tuesday 01 March 2011] [00:36:04] <cremes>	we live in a git world now
| [Tuesday 01 March 2011] [00:36:20] <andrewvc>	yeah, someone should right an apt adapter to github
| [Tuesday 01 March 2011] [00:36:38] <andrewvc>	or git in general I guess
| [Tuesday 01 March 2011] [00:37:30] <andrewvc>	hmmm, that's definitely going on my spare time ideas list
| [Tuesday 01 March 2011] [00:41:01] <cremes>	i think something like that exists already... but i can't remember where i saw it :(
| [Tuesday 01 March 2011] [00:41:02] <cremes>	time for bed... i've been burning the candle at both ends lately
| [Tuesday 01 March 2011] [02:50:32] <jstrom`>	Hi ppl! I'm playing a bit with async zmq (2.1.1rc) and perl on FreeBSD.. Building a POE socket wrapper (yes i know about the anyevent/moose thingy), works great! However, when I close sockets (pub/sub tcp in same app) it crashes :/ Seems to sometimes crash in mailbox_t::send right after close(), and sometimes it can close both but then crash in kqueue::kevent_add.. Is there any known bugs regarding kqueue/freebsd/perl? I've tried to reproduce in C but canno
| [Tuesday 01 March 2011] [02:52:05] <jstrom`>	if it doesnt crash in close, the kevent_add crash comes right after the close() calls (waiting a bit before calling ctx->terminate()).
| [Tuesday 01 March 2011] [02:58:42] <jstrom`>	the perl unittests seems to work at least.. hrm.. gotta dig deeper i guess :)
| [Tuesday 01 March 2011] [03:00:35] <jstrom`>	the crash in send is hitting errno_assert (nbytes != -1); in mailbox_t::send
| [Tuesday 01 March 2011] [03:15:49] <private_meta>	jstrom`: Your first message was cut off after "reproduce in C but canno"
| [Tuesday 01 March 2011] [03:21:54] <jstrom`>	doh, ah well nothing vital there: I've tried to reproduce in C but cannot 
| [Tuesday 01 March 2011] [03:21:55] <jstrom`>	                    really get it to fail there..
| [Tuesday 01 March 2011] [03:21:59] <jstrom`>	(evil newlines!)
| [Tuesday 01 March 2011] [03:22:31] <jstrom`>	errno=35 (EAGAIN) when i hit the assert btw
| [Tuesday 01 March 2011] [03:37:42] <sustrik>	jstrom`: afaics what's happening there is 0mq filling up the socketpair buffer, so it doubles it's size, checks whether size was doubled and tries to write to the socketpair once again -- it fails but it should not
| [Tuesday 01 March 2011] [03:37:57] <sustrik>	some strange freebsd quirk i assume
| [Tuesday 01 March 2011] [03:39:47] <jstrom`>	maybee, will try harder to reproduce in C (havent gotten around to do select stuff there, only open pub/sub, then send/recv and then close)
| [Tuesday 01 March 2011] [03:40:10] <sustrik>	you don't have to reproduce it
| [Tuesday 01 March 2011] [03:40:23] <sustrik>	the question is why freebsd behaves in such a way
| [Tuesday 01 March 2011] [03:40:31] <sustrik>	and whether it can be worked around
| [Tuesday 01 March 2011] [03:41:09] <jstrom`>	mkey
| [Tuesday 01 March 2011] [03:41:59] <jstrom`>	I'll try to strip it down to a simple test case at least :)
| [Tuesday 01 March 2011] [03:48:59] <private_meta>	The term "workaround" makes me shudder every time I read or hear it...
| [Tuesday 01 March 2011] [03:52:31] <sustrik>	that's often exaclty what you have to do in the case with OS bug :)
| [Tuesday 01 March 2011] [04:01:56] <jstrom`>	hm simple non-FD-based socket(),socket(),send(),recv(),close(),close(),term() works fine.. seems to be in more advanced cases the problem occurs (i can reproduce it fully there). Will continue until i get a working testcase, but will have to do it later today.
| [Tuesday 01 March 2011] [04:07:56] <private_meta>	Hmm... if heartbeats are asynchroneous in both directions and heartbeat sending and receiving are made via zmq_poll on the server side, how can you make independent sending on the client side if you don't have zmq_poll's timeouts?
| [Tuesday 01 March 2011] [04:38:02] <private_meta>	When using socket_t::getsockopt, the equivalent of C's zmq_getsockopt in C++, it works if I call getsockopt in the same function as I create the socket, but fails if I give the socket pointer to a different function and request it there. It gives me an invalid argument error in the function. 
| [Tuesday 01 March 2011] [04:38:20] <private_meta>	According to the man pages, that's "The requested option option_name is unknown, or the requested option_len or option_value is invalid, or the size of the buffer pointed to by option_value, as specified by option_len, is insufficient for storing the option value."
| [Tuesday 01 March 2011] [04:38:43] <private_meta>	But I call it exactly the same, I even call the same pointer, but in two different places, yet the same thread. Any idea what might be the problem there?
| [Tuesday 01 March 2011] [04:45:55] <private_meta>	hmm now it suddenly works... I hate demonstrative effects to the core
| [Tuesday 01 March 2011] [04:46:28] <private_meta>	Somewhat unreliable behavior
| [Tuesday 01 March 2011] [05:48:22] <Guthur>	sustrik: will there be minutes are a webcast of the meetup at san fran
| [Tuesday 01 March 2011] [06:35:32] <jstrom`>	sustrik: i think i found the problem.. I was using IO::Handle to wrap the ZMQ_FD to make it select'able in POE, and i accidentally called close() on the IO::handle, which means close() on the actual FD.. 
| [Tuesday 01 March 2011] [06:37:44] <jstrom`>	so, not a ZMQ/freebsd problem, just buggy code on my end :) 
| [Tuesday 01 March 2011] [06:41:53] <Guest19497>	can any one help me about 0mq
| [Tuesday 01 March 2011] [06:41:56] <skm>	0mq for sending files: stupid idea, yes?
| [Tuesday 01 March 2011] [06:42:15] <Guest19497>	what the 0mq architecture?
| [Tuesday 01 March 2011] [06:42:19] <drbobbeaty>	skim: It's not what I'd use, no.
| [Tuesday 01 March 2011] [06:42:41] <Guest19497>	hi
| [Tuesday 01 March 2011] [06:42:55] <skm>	sweet - ill stick to 0mq for messaging and regular sockets for file sending
| [Tuesday 01 March 2011] [06:43:17] <drbobbeaty>	Guest19497: There's a very nice into to ZeroMQ at http://zguide.zeromq.org/page:all
| [Tuesday 01 March 2011] [06:43:59] <Guest19497>	thanks
| [Tuesday 01 March 2011] [06:44:10] <drbobbeaty>	Guest19497: it contains lots of examples, explanations, even different language bindings.
| [Tuesday 01 March 2011] [06:44:35] <pieterh>	I've made a URL shortener at zero.mq
| [Tuesday 01 March 2011] [06:45:00] <pieterh>	e.g. http://zero.mq/ib->https://github.com/ianbarber/ZeroMQ-Talk
| [Tuesday 01 March 2011] [06:45:08] <pieterh>	if anyone wants access to this, let me know
| [Tuesday 01 March 2011] [06:53:40] <private_meta>	pieterh: hmm... when trying to translate the lazy pirate pattern to C++ I get assertions
| [Tuesday 01 March 2011] [06:54:05] <pieterh>	private_meta: such as...?
| [Tuesday 01 March 2011] [06:54:53] <private_meta>	I have the lazy pirate client, I try to start it, and I would have the setsockopt call for ZMQ_LINGER. When calling it, I get the error "Assertion failed: rc == 0 (zmq_connecter.cpp:47)"
| [Tuesday 01 March 2011] [06:55:00] <pieterh>	please post your code to a gist
| [Tuesday 01 March 2011] [06:55:05] <private_meta>	gist?
| [Tuesday 01 March 2011] [06:55:18] <pieterh>	gist.github.com or another pastebin
| [Tuesday 01 March 2011] [06:55:40] <pieterh>	presumably the connection failed because you have no server running?
| [Tuesday 01 March 2011] [06:55:56] <pieterh>	I don't know, can't tell without code to look at...
| [Tuesday 01 March 2011] [06:56:13] <pieterh>	you've run the C code, and it works?
| [Tuesday 01 March 2011] [06:56:32] <private_meta>	The server is running
| [Tuesday 01 March 2011] [06:56:39] <private_meta>	hmm... No, I didn't try the C version
| [Tuesday 01 March 2011] [06:56:55] <private_meta>	I don't really code in C, I try to avoid it
| [Tuesday 01 March 2011] [06:56:58] <private_meta>	(don't like it)
| [Tuesday 01 March 2011] [06:57:38] <pieterh>	at least run it, as a sanity check
| [Tuesday 01 March 2011] [06:57:55] <private_meta>	meh... I'll try
| [Tuesday 01 March 2011] [06:58:34] <pieterh>	it's a basic tool for problem solving, replace pieces and see when it starts/stops breaking
| [Tuesday 01 March 2011] [07:00:18] <private_meta>	pieterh: btw, you wrote in the docs that you use the lazy pirate client for the paranoid pirate server. You made heartbeats in the server, but apparently not on the client. am I misunderstanding something there?
| [Tuesday 01 March 2011] [07:00:28] <pieterh>	nope, that's how it works
| [Tuesday 01 March 2011] [07:01:02] <pieterh>	there are good reasons to do heartbeating from queue to worker, but not from client to queue, afaics
| [Tuesday 01 March 2011] [07:01:27] <pieterh>	queues don't hold any resources per client
| [Tuesday 01 March 2011] [07:01:39] <pieterh>	clients don't care if the queue is present/absent except when they are doing a request
| [Tuesday 01 March 2011] [07:01:51] <private_meta>	You send a heartbeat out, but the client doesn't even seem to receive one, I don't quite get how that works to assure that there actually IS a working connection
| [Tuesday 01 March 2011] [07:02:08] <pieterh>	the client-to-queue dialog has no heartbeating
| [Tuesday 01 March 2011] [07:02:48] <private_meta>	ok, you say, queue, do you mean the server?
| [Tuesday 01 March 2011] [07:03:10] <pieterh>	I'm avoiding the word 'server' because it's ambiguous
| [Tuesday 01 March 2011] [07:03:19] <pieterh>	we have client, queue, and worker
| [Tuesday 01 March 2011] [07:03:30] <pieterh>	when I say 'queue', I mean 'queue'... :-)
| [Tuesday 01 March 2011] [07:05:14] <private_meta>	ok, then can you define those three, what they do exactly, because I didn't seem to find any good definition in the docs
| [Tuesday 01 March 2011] [07:05:49] <pieterh>	it is always local to the pattern
| [Tuesday 01 March 2011] [07:06:02] <pieterh>	that's why I provide a schema for each pattern with the boxes clearly labelled
| [Tuesday 01 March 2011] [07:06:18] <pieterh>	client is easy
| [Tuesday 01 March 2011] [07:06:21] <pieterh>	queue is easy
| [Tuesday 01 March 2011] [07:06:28] <pieterh>	worker is also unambiguous
| [Tuesday 01 March 2011] [07:06:41] <pieterh>	but "server" is anything that accepts a connection, or does work, or ...
| [Tuesday 01 March 2011] [07:07:42] <private_meta>	So going after figure 21 in the docs, "Client" is what I and everyone I work with always understood as "Server", and "worker" is what I understand as "Client", and the "Server in the figure is something I didn't even name yet in that regard
| [Tuesday 01 March 2011] [07:08:19] <private_meta>	I have never met anyone who defined it the way it's defined here
| [Tuesday 01 March 2011] [07:10:48] <pieterh>	private_meta: figure 21 is really clear 
| [Tuesday 01 March 2011] [07:11:01] <pieterh>	the client is the application that makes a request
| [Tuesday 01 March 2011] [07:11:10] <pieterh>	the server is the host that does the work
| [Tuesday 01 March 2011] [07:11:21] <private_meta>	pieterh: Yeah, according to that, as I said, I never met ANYONE who defined it like that, not even remotely
| [Tuesday 01 March 2011] [07:11:21] <pieterh>	hmm, e.g. web browser and web server
| [Tuesday 01 March 2011] [07:11:30] <pieterh>	so your browser is a "server"?
| [Tuesday 01 March 2011] [07:11:44] <pieterh>	and google.com is the "client" of your browser?
| [Tuesday 01 March 2011] [07:11:59] <private_meta>	No, my browser is a client, google is a server
| [Tuesday 01 March 2011] [07:12:06] <pieterh>	and that's figure 21
| [Tuesday 01 March 2011] [07:12:22] <pieterh>	what's confusing about it?
| [Tuesday 01 March 2011] [07:12:33] <pieterh>	maybe you want the server at the top of the page, and the client below?
| [Tuesday 01 March 2011] [07:12:46] <pieterh>	all the diagrams show the logical flow of requests / tasks from top to bottom
| [Tuesday 01 March 2011] [07:13:23] <private_meta>	Wait, in Figure 21 Google would be the worker?
| [Tuesday 01 March 2011] [07:13:28] <pieterh>	figure 21 shows an application server, in fact
| [Tuesday 01 March 2011] [07:13:41] <pieterh>	workers are applications, if you like
| [Tuesday 01 March 2011] [07:13:55] <pieterh>	server plugins
| [Tuesday 01 March 2011] [07:14:16] <pieterh>	this is all classic stuff, can I please go back to my Majordomo coding now ? :-)
| [Tuesday 01 March 2011] [07:14:37] <private_meta>	Well, you didn't really help me understand it
| [Tuesday 01 March 2011] [07:14:41] <private_meta>	:/
| [Tuesday 01 March 2011] [07:14:51] <pieterh>	since you don't tell me what your confusion is...
| [Tuesday 01 March 2011] [07:15:00] <pieterh>	I'd suggest reading the text like 10 times until it clicks
| [Tuesday 01 March 2011] [07:15:17] <pieterh>	these concepts are slippery, I know
| [Tuesday 01 March 2011] [07:15:32] <pieterh>	but I can't explain them over IRC better than the text and pictures already do
| [Tuesday 01 March 2011] [07:15:54] <private_meta>	Well, just give me a real world example what CLIENT, SERVER and WORKER would be in an example I can understand
| [Tuesday 01 March 2011] [07:15:58] <private_meta>	you're giving me confusing information
| [Tuesday 01 March 2011] [07:16:09] <pieterh>	I've just done that, you're making me repeat myself
| [Tuesday 01 March 2011] [07:16:14] <pieterh>	web browser = client
| [Tuesday 01 March 2011] [07:16:18] <pieterh>	web server = server 
| [Tuesday 01 March 2011] [07:16:31] <pieterh>	PHP application producing web content = worker
| [Tuesday 01 March 2011] [07:16:37] <private_meta>	ok, that was clear
| [Tuesday 01 March 2011] [07:16:41] <pieterh>	there are hundreds of such examples
| [Tuesday 01 March 2011] [07:16:42] <guido_g>	rofl
| [Tuesday 01 March 2011] [07:16:42] <private_meta>	it wasn't clear before
| [Tuesday 01 March 2011] [07:17:15] <private_meta>	hmm... sanity check for lazy pirate pattern worked in C
| [Tuesday 01 March 2011] [07:17:16] <guido_g>	<private_meta> I have never met anyone who defined it the way it's defined here  <- hard to believe
| [Tuesday 01 March 2011] [07:17:23] <pieterh>	private_meta: like I said, re-read the text until it clicks
| [Tuesday 01 March 2011] [07:18:30] <private_meta>	int linger = 0; client->setsockopt(ZMQ_LINGER, &linger, sizeof(linger)); <-- that line fails in c++
| [Tuesday 01 March 2011] [07:19:03] <skm>	i have 3 servers that dish out work (in the form of mp3 files) and 5 clients that need to receive the files - i want to add servers and clients with little effort so im going to have a manager inbetween them all..
| [Tuesday 01 March 2011] [07:19:30] <jugg>	eh, api.zeromq.org is broken...
| [Tuesday 01 March 2011] [07:19:35] <skm>	im using push/pull for the servers - my problem is what if the manager fails then comes back up - what's the best way to resend the files
| [Tuesday 01 March 2011] [07:19:36] <pieterh>	jugg: where?
| [Tuesday 01 March 2011] [07:19:47] <jugg>	http://api.zeromq.org/zmq-setsockopt-html
| [Tuesday 01 March 2011] [07:19:54] <jugg>	but any of the links
| [Tuesday 01 March 2011] [07:20:04] <skm>	(the files exist on the server until a client downloads it from the server - the manager just has a list in a queue)
| [Tuesday 01 March 2011] [07:20:14] <pieterh>	skm: there's no documented patterns for reliable push/pull, I'm working on those
| [Tuesday 01 March 2011] [07:20:18] <pieterh>	jugg: bleh
| [Tuesday 01 March 2011] [07:20:25] <private_meta>	pieterh: yeah, all links from the guide to the api are broken
| [Tuesday 01 March 2011] [07:20:36] <private_meta>	or seem to be
| [Tuesday 01 March 2011] [07:20:37] <jugg>	hmm, looks like api.zeromq.org was cached, forced refresh pulls the new page.
| [Tuesday 01 March 2011] [07:20:44] <pieterh>	private_meta: nope, fixed those about 10 minutes ago, reload
| [Tuesday 01 March 2011] [07:20:44] <jugg>	which has different links
| [Tuesday 01 March 2011] [07:20:57] <pieterh>	jugg: I'll need to make forwards from all the old API pages... bleh
| [Tuesday 01 March 2011] [07:21:07] <jugg>	yah
| [Tuesday 01 March 2011] [07:21:15] <private_meta>	ah ok
| [Tuesday 01 March 2011] [07:21:25] <private_meta>	just reloaded 30 minutes ago XD
| [Tuesday 01 March 2011] [07:22:11] <private_meta>	pieterh: maybe I made a mistake, but I thought it should be a working translation https://gist.github.com/45ae7e2a36ad5c1ca50f https://gist.github.com/a4df2891f9c8edc1ac0c
| [Tuesday 01 March 2011] [07:23:30] <jugg>	v2.1.1 is not tagged in Git
| [Tuesday 01 March 2011] [07:23:51] <pieterh>	private_meta: yeah, it looks OK, I've no idea why the C++ setsockopt would be failing
| [Tuesday 01 March 2011] [07:24:06] <pieterh>	jugg: it's in http://github.com/zeromq/zeromq2-1
| [Tuesday 01 March 2011] [07:24:16] <pieterh>	we forked the repository to make life easier for everyone
| [Tuesday 01 March 2011] [07:24:38] <jugg>	ugh
| [Tuesday 01 March 2011] [07:25:19] <pieterh>	jugg: there are pros and cons but it's simplified our work a lot
| [Tuesday 01 March 2011] [07:25:29] <private_meta>	The setsockopt fails with the error stated 30 minutes ago, and if continued I get the error "Bad file descriptor, nbytes != -1 (mailbox.cpp:241)"
| [Tuesday 01 March 2011] [07:25:38] <jugg>	well, thankfully Git supports multiple remotes...
| [Tuesday 01 March 2011] [07:30:05] <private_meta>	pieterh: Now that I got the terminology described, my worker needs to know if the client is there, and my client needs to know if my worker is there, so i need heartbeats from client to server and vice versa, that's why I was asking before about the heartbeats
| [Tuesday 01 March 2011] [07:31:31] <Guthur>	umm this talk of linger has just made be notice a minor type bug in clrzmq2
| [Tuesday 01 March 2011] [07:31:39] <Guthur>	at least it was good for something, hehe
| [Tuesday 01 March 2011] [07:32:54] <Guthur>	be/me
| [Tuesday 01 March 2011] [07:34:46] <pieterh>	private_meta: what pattern are you talking about?
| [Tuesday 01 March 2011] [07:34:56] <pieterh>	figure 21 is asynchronous server
| [Tuesday 01 March 2011] [07:35:11] <pieterh>	clients don't see workers, workers don't see clients
| [Tuesday 01 March 2011] [07:35:20] <private_meta>	pieterh: I was talking about figure 21 because it made it understandable somewhat more easily
| [Tuesday 01 March 2011] [07:36:01] <pieterh>	jugg: all the old API links should properly redirect now
| [Tuesday 01 March 2011] [07:36:08] <pieterh>	I sent them to 2.1.1
| [Tuesday 01 March 2011] [07:39:21] <private_meta>	pieterh: I need custom routing, something like router-to-dealer, but with heartbeating, but in both directions, as workers and clients should be aware of each other
| [Tuesday 01 March 2011] [07:39:57] <private_meta>	I don't know if there is a pattern more fitting to that
| [Tuesday 01 March 2011] [07:40:06] <pieterh>	take a look at http://zero.mq/md, specifically the server protocol, it may what you need
| [Tuesday 01 March 2011] [07:40:29] <pieterh>	your client could implement the broker part of the protocol
| [Tuesday 01 March 2011] [07:40:56] <jugg>	pieterh, looks like it.
| [Tuesday 01 March 2011] [07:41:05] <pieterh>	if you implement precisely the protocol as specified it'll interoperate with other code using the same spec
| [Tuesday 01 March 2011] [07:41:09] <pieterh>	jugg: great!
| [Tuesday 01 March 2011] [07:46:20] <private_meta>	pieterh: ok, so I would have n Clients and 1 Worker I assume
| [Tuesday 01 March 2011] [08:03:24] <private_meta>	So if I adhere to the protocol specifications best as possible, a guide chapter is in the works to help me with the problem specificied
| [Tuesday 01 March 2011] [08:03:29] <private_meta>	?
| [Tuesday 01 March 2011] [08:15:17] <skm>	if i have 1 client pushing and 3 clients pulling - if the client pushes 100msgs will they be sent to the first client that connects
| [Tuesday 01 March 2011] [08:15:24] <skm>	or in order of each client recving
| [Tuesday 01 March 2011] [08:19:31] <private_meta>	pieterh: should I create an issue for the ZMQ_LINGER problem in the c++ translation?
| [Tuesday 01 March 2011] [08:21:01] <cremes>	private_meta: put up a pastie with the compilation error; that c++ you posted earlier looked correct
| [Tuesday 01 March 2011] [08:21:17] <private_meta>	cremes: there's a runtime error, not a compilation error
| [Tuesday 01 March 2011] [08:21:47] <cremes>	ok, then post that error (all of it)
| [Tuesday 01 March 2011] [08:22:04] <private_meta>	Yeah, just wanted to say that it doesn't change that I should post the error :)
| [Tuesday 01 March 2011] [08:22:12] <cremes>	heh
| [Tuesday 01 March 2011] [08:26:34] <private_meta>	cremes: theoretically, if it's translated correctly, the C server should work with the C++ client, shouldn't it?
| [Tuesday 01 March 2011] [08:27:17] <cremes>	yes; i have 0mq from ruby interacting with 0mq from C on a regular basis
| [Tuesday 01 March 2011] [08:27:39] <cremes>	and it's not even theoretical!
| [Tuesday 01 March 2011] [08:27:43] <cremes>	:)
| [Tuesday 01 March 2011] [08:27:55] <stimpie>	Iam having some problems using an xrep socket on en inproc transport, any way of sniffing or logging the inproc transport?
| [Tuesday 01 March 2011] [08:28:47] <cremes>	stimpie: i am not sure.... there is a new "sys" logging facility that may be of use
| [Tuesday 01 March 2011] [08:29:01] <cremes>	check the mail archives for discussion or the git log for patches
| [Tuesday 01 March 2011] [08:29:09] <private_meta>	ok, c server works with c client, c++ server works with c client, but both servers won't work with c++ client
| [Tuesday 01 March 2011] [08:29:41] <cremes>	private_meta: ok; please post the error *and* the code for all of the components
| [Tuesday 01 March 2011] [08:29:56] <cremes>	you might have something wired wrong
| [Tuesday 01 March 2011] [08:30:46] <cremes>	(i'm expecting a gist with five files: error, c client, c server, c++ client, c++ server)
| [Tuesday 01 March 2011] [08:31:49] <private_meta>	Well, I write 4 gists with the 4 c/c++ files and I write the error in the issue
| [Tuesday 01 March 2011] [08:32:41] <private_meta>	cremes: then again the c client and server are exactly those from the docs
| [Tuesday 01 March 2011] [08:32:50] <private_meta>	so i won't need to "gist" them
| [Tuesday 01 March 2011] [08:34:08] <cremes>	private_meta: i'm reading "cremes, i don't really want your help"
| [Tuesday 01 March 2011] [08:34:20] <private_meta>	lol
| [Tuesday 01 March 2011] [08:34:21] <cremes>	at least send me a link to the components that are from the docs
| [Tuesday 01 March 2011] [08:34:32] <private_meta>	cremes: I intended to put them into the issue
| [Tuesday 01 March 2011] [08:34:36] <cremes>	don't make me do a lot of extra work to help you out; it isn't fair
| [Tuesday 01 March 2011] [08:34:55] <cremes>	i don't think we have established yet that this warrants an issue
| [Tuesday 01 March 2011] [08:35:05] <cremes>	these things interoperate all of the time
| [Tuesday 01 March 2011] [08:35:18] <cremes>	let's dig just a little before opening a ticket
| [Tuesday 01 March 2011] [08:35:33] <private_meta>	If you want to
| [Tuesday 01 March 2011] [08:37:41] <private_meta>	cremes: https://gist.github.com/dadca0c3b776aa5713da sufficient?
| [Tuesday 01 March 2011] [08:38:38] <cremes>	good enough; give me a few to look through it
| [Tuesday 01 March 2011] [08:39:20] <private_meta>	Maybe it's just a problem with me using setsockopt, but I hope not
| [Tuesday 01 March 2011] [08:40:59] <guido_g>	client->connect("tcp://localhost.5555"); <- wrong
| [Tuesday 01 March 2011] [08:41:39] <skm>	uf a pusher has pushed 100msgd, the first client to call recv then gets all 100 msgs (and has to recv 99 more times to see them) - correct?
| [Tuesday 01 March 2011] [08:42:45] <private_meta>	guido_g: I translated it with that url from the C version
| [Tuesday 01 March 2011] [08:42:50] <private_meta>	guido_g: why is it wrong?
| [Tuesday 01 March 2011] [08:42:56] <guido_g>	read it
| [Tuesday 01 March 2011] [08:43:18] <H-nes>	hint: ":"
| [Tuesday 01 March 2011] [08:43:31] <private_meta>	oh
| [Tuesday 01 March 2011] [08:43:31] <guido_g>	right
| [Tuesday 01 March 2011] [08:43:47] <private_meta>	damn me
| [Tuesday 01 March 2011] [08:43:47] <guido_g>	all thar trouble for basically nothing
| [Tuesday 01 March 2011] [08:43:51] <guido_g>	*taht
| [Tuesday 01 March 2011] [08:43:57] <guido_g>	*that
| [Tuesday 01 March 2011] [08:44:06] <guido_g>	how effective
| [Tuesday 01 March 2011] [08:44:48] <cremes>	guido_g: good eye
| [Tuesday 01 March 2011] [08:45:29] <guido_g>	cremes: we in germany are now known for our keen eyes on copied work   ,)
| [Tuesday 01 March 2011] [08:45:36] <Guthur>	guido_g: I did realise that I need to implement these options in the clrzmq2 binding due to this discussion, if that is any consolation, hehe
| [Tuesday 01 March 2011] [08:45:50] <cremes>	guido_g: ;)
| [Tuesday 01 March 2011] [08:46:07] <cremes>	private_meta: after you make that change, let us know if all is well
| [Tuesday 01 March 2011] [08:46:39] <private_meta>	hmm apparently not
| [Tuesday 01 March 2011] [08:47:06] <guido_g>	more typos?
| [Tuesday 01 March 2011] [08:47:48] <private_meta>	I hope not
| [Tuesday 01 March 2011] [08:47:53] <private_meta>	But it's a different error now
| [Tuesday 01 March 2011] [08:53:12] <private_meta>	cremes: update
| [Tuesday 01 March 2011] [08:53:21] <private_meta>	cremes: https://gist.github.com/dadca0c3b776aa5713da
| [Tuesday 01 March 2011] [08:54:40] <cremes>	private_meta: that is oftentimes a buffer sizing problem; what OS are you on?
| [Tuesday 01 March 2011] [08:55:08] <private_meta>	Ubuntu 10.4 x64
| [Tuesday 01 March 2011] [08:56:33] <cremes>	private_meta: give me a gist with:  net.core.rmem_default, net.core.rmem_max, net.core.wmem_default, net.core.wmem_max
| [Tuesday 01 March 2011] [08:57:05] <cremes>	these control the size of the buffers for "socketpairs" which are used for all internal signaling in 0mq
| [Tuesday 01 March 2011] [08:57:28] <private_meta>	How do I get those?
| [Tuesday 01 March 2011] [08:58:15] <cremes>	sysctl -a | egrep 'wmem|rmem'
| [Tuesday 01 March 2011] [08:58:25] <private_meta>	kk
| [Tuesday 01 March 2011] [08:58:49] <cremes>	how long before you saw that error? 10s, 1m, longer?
| [Tuesday 01 March 2011] [08:58:58] <private_meta>	Let me test
| [Tuesday 01 March 2011] [08:59:01] <cremes>	and does it happen on *every* run
| [Tuesday 01 March 2011] [08:59:14] <stimpie>	took me 4 hours to find out I encountered an known issue #issue/82 grrrr
| [Tuesday 01 March 2011] [08:59:45] <cremes>	private_meta: the reason i ask is because the c client should produce the same error in roughly the same timeframe
| [Tuesday 01 March 2011] [08:59:58] <private_meta>	cremes: Immediately, at every run
| [Tuesday 01 March 2011] [09:00:04] <private_meta>	But the C Client works
| [Tuesday 01 March 2011] [09:00:12] <cremes>	now that is odd
| [Tuesday 01 March 2011] [09:01:54] <private_meta>	cremes: https://gist.github.com/6c43ecadae82d425773b
| [Tuesday 01 March 2011] [09:01:58] <cremes>	you should run it run gdb and pastie the backtrace too
| [Tuesday 01 March 2011] [09:02:30] <cremes>	those sizes should be ok
| [Tuesday 01 March 2011] [09:02:39] <private_meta>	cremes: the entire gdb trace?
| [Tuesday 01 March 2011] [09:02:56] <cremes>	i use 5242880 for all of those settings, fyi
| [Tuesday 01 March 2011] [09:03:05] <cremes>	private_meta: yes, all of it
| [Tuesday 01 March 2011] [09:03:13] <cremes>	do: thread apply all bt
| [Tuesday 01 March 2011] [09:03:36] <private_meta>	cremes: https://gist.github.com/8c059893dbec50829e84
| [Tuesday 01 March 2011] [09:06:33] <cremes>	private_meta: i can't make heads or tails of that output
| [Tuesday 01 March 2011] [09:06:51] <cremes>	it looks like nonsense
| [Tuesday 01 March 2011] [09:07:11] <private_meta>	cremes: I never worked closly with gdb or traces, so I gave you what eclipse tagged as "traces"
| [Tuesday 01 March 2011] [09:07:24] <cremes>	oh...
| [Tuesday 01 March 2011] [09:07:33] <private_meta>	gdb traces to be exact
| [Tuesday 01 March 2011] [09:07:48] <cremes>	from a command line, run this:  gdb --args <name of lpclient>
| [Tuesday 01 March 2011] [09:07:52] <private_meta>	sec
| [Tuesday 01 March 2011] [09:07:52] <cremes>	(gdb) run
| [Tuesday 01 March 2011] [09:08:01] <cremes>	(gdb) thread apply all bt
| [Tuesday 01 March 2011] [09:08:04] <cremes>	pastie the output
| [Tuesday 01 March 2011] [09:11:23] <private_meta>	cremes: better? https://gist.github.com/0eba301579e05243a715
| [Tuesday 01 March 2011] [09:12:17] <cremes>	better
| [Tuesday 01 March 2011] [09:14:35] <cremes>	private_meta: change: zmq::poll (items, 1, REQUEST_TIMEOUT * 1000);
| [Tuesday 01 March 2011] [09:14:42] <cremes>	to:  zmq::poll (&items, 1, REQUEST_TIMEOUT * 1000);
| [Tuesday 01 March 2011] [09:14:55] <cremes>	(just added & in front of items)
| [Tuesday 01 March 2011] [09:17:00] <private_meta>	cremes: cannot convert 'zmq::pollitem_t (*)[1]' to 'zmq_pollitem_t*' for argument '1' to 'int zmq::poll(zmq_pollitem_t*, int, long int)'
| [Tuesday 01 March 2011] [09:21:10] <cremes>	private_meta: oops, my mistake; try this:
| [Tuesday 01 March 2011] [09:21:22] <cremes>	zmq::poll (&items[0], 1, REQUEST_TIMEOUT * 1000);
| [Tuesday 01 March 2011] [09:21:36] <guido_g>	yeah, that's c++ :)
| [Tuesday 01 March 2011] [09:21:41] <cremes>	btw, i'm getting all of this from looking at the c++ examples in the zguide
| [Tuesday 01 March 2011] [09:21:54] <guido_g>	hrhrhr
| [Tuesday 01 March 2011] [09:21:57] <cremes>	your translation needs work
| [Tuesday 01 March 2011] [09:22:16] <private_meta>	same
| [Tuesday 01 March 2011] [09:22:46] <cremes>	won't compile?
| [Tuesday 01 March 2011] [09:22:52] <private_meta>	no, same as items
| [Tuesday 01 March 2011] [09:23:01] <private_meta>	so, same runtime error
| [Tuesday 01 March 2011] [09:23:07] <cremes>	can you get any of the c++ examples in the zguide to run?
| [Tuesday 01 March 2011] [09:24:05] <private_meta>	sure
| [Tuesday 01 March 2011] [09:24:07] <guido_g>	just to make sure, try a delay (sleep) after the send and before the poll, might be that the connection is not yet established
| [Tuesday 01 March 2011] [09:24:31] <private_meta>	guido_g: nope
| [Tuesday 01 March 2011] [09:25:02] <guido_g>	why?
| [Tuesday 01 March 2011] [09:25:13] <private_meta>	"nope" as in "doesn't help"
| [Tuesday 01 March 2011] [09:25:53] <Guthur>	guido_g: would polling before the connection establishes cause issues?
| [Tuesday 01 March 2011] [09:26:09] <guido_g>	i'm not sure
| [Tuesday 01 March 2011] [09:26:18] <private_meta>	cremes: I haven't tried ALL of them, but they normally DO work
| [Tuesday 01 March 2011] [09:26:24] <guido_g>	that's why i asked to test it
| [Tuesday 01 March 2011] [09:26:46] <Guthur>	guido_g: ok, the reason I asked was I had an issue like that last night on linux
| [Tuesday 01 March 2011] [09:26:55] <private_meta>	guido_g: A sleep of 1 second didn't help
| [Tuesday 01 March 2011] [09:26:55] <Guthur>	using the clrzmq2 binding
| [Tuesday 01 March 2011] [09:27:08] <guido_g>	private_meta: where was the sleep?
| [Tuesday 01 March 2011] [09:27:35] <private_meta>	after s_send before zmq::pollitem_t, but not after every poll.
| [Tuesday 01 March 2011] [09:28:06] <guido_g>	ok
| [Tuesday 01 March 2011] [09:28:47] <cremes>	when i run it under gdb, it shows that it is spawning 2 client threads and connecting to the server twice
| [Tuesday 01 March 2011] [09:29:34] <cremes>	wtf?
| [Tuesday 01 March 2011] [09:30:39] <cremes>	no, something else is up...
| [Tuesday 01 March 2011] [09:34:36] <private_meta>	pieterh: Just out of premature curiosity, how would I then be able to use the Majordomo Protocol?
| [Tuesday 01 March 2011] [09:37:51] <cremes>	private_meta: fixed it
| [Tuesday 01 March 2011] [09:37:56] <cremes>	change: zmq::pollitem_t items [] = { { client, 0, ZMQ_POLLIN, 0 } };
| [Tuesday 01 March 2011] [09:37:59] <cremes>	to: zmq::pollitem_t items [] = { { *client, 0, ZMQ_POLLIN, 0 } };
| [Tuesday 01 March 2011] [09:38:28] <cremes>	(and keep the other changes)
| [Tuesday 01 March 2011] [09:39:06] <cremes>	wow, i haven't done any c++ in about 10 years and this experience hasn't made me miss it :)
| [Tuesday 01 March 2011] [09:39:22] <guido_g>	hehe
| [Tuesday 01 March 2011] [09:39:56] <private_meta>	cremes: wtf?
| [Tuesday 01 March 2011] [09:39:58] <cremes>	private_meta: do i get a coauthor credit on this translation? :P
| [Tuesday 01 March 2011] [09:40:27] <cremes>	private_meta: look at the other c++ examples; yours is the only one that uses 'new'
| [Tuesday 01 March 2011] [09:41:04] <cremes>	i think you had a pointer to a socket pointer
| [Tuesday 01 March 2011] [09:41:24] <cremes>	or something... i'm out of my depth :)
| [Tuesday 01 March 2011] [09:41:52] <guido_g>	cremes: oh nice, didn't spot that one
| [Tuesday 01 March 2011] [09:42:06] <private_meta>	cremes: It's not that I wanted to use new
| [Tuesday 01 March 2011] [09:42:11] <cremes>	guido_g: better lucky that good   <--- my motto
| [Tuesday 01 March 2011] [09:42:20] <cremes>	s/that/than/
| [Tuesday 01 March 2011] [09:43:09] <private_meta>	cremes: As far as I can see it's the only example where the socket is created in a different method, and for one the first example returned a pointer, so I wanted as well, and I thought it made the same problems as message_t
| [Tuesday 01 March 2011] [09:43:53] <cremes>	private_meta: what i remember about c++ could fit in a thimble; i just started matching up working code against non-working
| [Tuesday 01 March 2011] [09:43:55] <cremes>	and went from there
| [Tuesday 01 March 2011] [09:44:33] <cremes>	seems like the library should do some more sanity checking on passed arguments though
| [Tuesday 01 March 2011] [09:44:41] <private_meta>	cremes: the copy constructor of socket_t is private, so I can't return it as a non-pointer, and I didn't want to push socket_t into the parameters
| [Tuesday 01 March 2011] [09:44:58] <cremes>	it doesn't seem like we should be able to compile and run something with so many errors
| [Tuesday 01 March 2011] [09:45:21] <cremes>	(easy to make errors... i'm not poitning any fingers)
| [Tuesday 01 March 2011] [09:45:29] <Guthur>	sanity and c++?
| [Tuesday 01 March 2011] [09:45:39] <cremes>	Guthur: i know!
| [Tuesday 01 March 2011] [09:45:41] <private_meta>	Well, C takes a pointer, C++ doesn't, it's nasty
| [Tuesday 01 March 2011] [09:46:13] <private_meta>	ok
| [Tuesday 01 March 2011] [09:47:21] <private_meta>	cremes: the problem is that zmq_pollitem_t is in the zmq.h, there is no zmq.hpp version where (void *) is correctly translated to socket_t apparently
| [Tuesday 01 March 2011] [09:47:56] <cremes>	i don't know what that means ;)
| [Tuesday 01 March 2011] [09:48:02] <cremes>	heh
| [Tuesday 01 March 2011] [09:48:38] <cremes>	if that's a genuine hole in the lib, open a ticket with a patch
| [Tuesday 01 March 2011] [09:48:48] <cremes>	sounds like it would be pretty easy to make
| [Tuesday 01 March 2011] [09:49:54] <private_meta>	hmm
| [Tuesday 01 March 2011] [09:50:21] <private_meta>	either a genuine type for c++ or a sanity check in zmq::poll
| [Tuesday 01 March 2011] [09:50:35] <private_meta>	but the latter won't fix the problem at compile time
| [Tuesday 01 March 2011] [09:51:29] <private_meta>	typedef struct { void *socket; int fd; short events; short revents; } zmq_pollitem_t; <-- the void* there is the unfriendly thing
| [Tuesday 01 March 2011] [09:56:10] <private_meta>	hmm
| [Tuesday 01 March 2011] [10:02:38] <private_meta>	cremes: doesn't seem THAT easy
| [Tuesday 01 March 2011] [10:13:07] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r4c74462 10/ src/socket_base.cpp : 
| [Tuesday 01 March 2011] [10:13:07] <CIA-21>	zeromq2: Explicit identities bug in inproc transport fixed.
| [Tuesday 01 March 2011] [10:13:07] <CIA-21>	zeromq2: The identity of bound socket was not used. Instead, transient
| [Tuesday 01 March 2011] [10:13:07] <CIA-21>	zeromq2: identity was generated.
| [Tuesday 01 March 2011] [10:13:07] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/heLOOL
| [Tuesday 01 March 2011] [10:14:51] <private_meta>	Been led to the following problem, http://stackoverflow.com/questions/231760/what-does-a-type-followed-by-t-underscore-t-represent/231807#231807, don't you concern yourself with the problem because you prefix every type in C with "zmq_"?
| [Tuesday 01 March 2011] [10:40:54] <stimpie>	sustrik, great I was just running in to it.