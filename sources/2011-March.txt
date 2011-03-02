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
| [Tuesday 01 March 2011] [11:02:27] <sustrik>	stimpie :)
| [Tuesday 01 March 2011] [11:52:39] <private_meta>	https://gist.github.com/5beb18da2cdb0ed04e02 https://gist.github.com/427a77b7837b5010483a <-- I thought that would be an easy class based example for communicated through zmq_poll, shouldn't I get the "START" message at the worker? What am I doing wrong?
| [Tuesday 01 March 2011] [11:53:26] <ianbarber>	pieterh: are the lazy pirate examples translatable now then?
| [Tuesday 01 March 2011] [12:12:27] <private_meta>	k, got it to work >_>
| [Tuesday 01 March 2011] [12:12:58] <cremes>	private_meta: you're going through some of the same growing pains most of us did when we first
| [Tuesday 01 March 2011] [12:13:02] <cremes>	started playing with 0mq
| [Tuesday 01 March 2011] [12:13:15] <cremes>	though i'll say maybe the c++ aspect is throwing an additional monkey-wrench into the process
| [Tuesday 01 March 2011] [12:13:17] <cremes>	:)
| [Tuesday 01 March 2011] [12:15:58] <private_meta>	cremes: my problem is that we had to switch from a different comm library because it threw it's own monkey wrench into the project, and now everybody tells me "quick, we need it, immediately, if you don't, we have problems"
| [Tuesday 01 March 2011] [12:16:07] <private_meta>	cremes: and I'm completely new with zmq
| [Tuesday 01 March 2011] [12:16:15] <cremes>	uh oh
| [Tuesday 01 March 2011] [12:16:42] <cremes>	not to say you won't have success with 0mq, but it comes with time & experience
| [Tuesday 01 March 2011] [12:17:36] <private_meta>	uhm... do durable sockets send multipart messages with the id as the first part?
| [Tuesday 01 March 2011] [12:19:00] <ianbarber>	xrep does
| [Tuesday 01 March 2011] [12:19:11] <private_meta>	hmm
| [Tuesday 01 March 2011] [12:19:32] <cremes>	the ID is only sent upon connect/bind for each socket type
| [Tuesday 01 March 2011] [12:19:36] <cremes>	this is invisible to the application
| [Tuesday 01 March 2011] [12:19:43] <private_meta>	cremes: quote from my project manager: "If you take too long with zmq I assume it won't help us, and you have to implement communication from scratch"
| [Tuesday 01 March 2011] [12:19:55] <ianbarber>	ouch!
| [Tuesday 01 March 2011] [12:20:11] <ianbarber>	xrep wraps the message with the ID, so it knows who to route back to
| [Tuesday 01 March 2011] [12:20:17] <cremes>	xrep sends the identity as a visible message part as part of a routing envelope on a reply
| [Tuesday 01 March 2011] [12:20:19] <ianbarber>	it'll unwrap when you send back
| [Tuesday 01 March 2011] [12:20:38] <cremes>	private_meta: your manager must have pointy hair
| [Tuesday 01 March 2011] [12:21:13] <private_meta>	cremes: actually, he's a programmer, he even programmed in projects
| [Tuesday 01 March 2011] [12:21:22] <private_meta>	cremes: and apparently the projects didn't fail
| [Tuesday 01 March 2011] [12:21:38] <private_meta>	hmm
| [Tuesday 01 March 2011] [12:21:47] <cremes>	well, making that statement undermines past performance
| [Tuesday 01 March 2011] [12:22:01] <cremes>	he may be a good programmer but he doesn't seem to be too hot of a manager (IMHO)
| [Tuesday 01 March 2011] [12:22:03] <private_meta>	That's the paradox
| [Tuesday 01 March 2011] [12:22:32] <cremes>	we'll help where we can; have you read the guide from start to finish twice yet? ;)
| [Tuesday 01 March 2011] [12:22:53] <ianbarber>	and tried the examples!
| [Tuesday 01 March 2011] [12:23:07] <cremes>	ianbarber: indeed!
| [Tuesday 01 March 2011] [12:23:20] <private_meta>	I read much of it and tried some examples, tried modifying them and stuff
| [Tuesday 01 March 2011] [12:23:45] <ianbarber>	it does help to thing of XREP and XREQ as router and dealer
| [Tuesday 01 March 2011] [12:23:53] <ianbarber>	makes it clearer what they do 
| [Tuesday 01 March 2011] [12:23:56] <ianbarber>	s/thing/think
| [Tuesday 01 March 2011] [12:24:34] <private_meta>	Well, I did try to build a router/dealer
| [Tuesday 01 March 2011] [12:24:35] <private_meta>	sec
| [Tuesday 01 March 2011] [12:24:46] <private_meta>	https://gist.github.com/5beb18da2cdb0ed04e02 https://gist.github.com/427a77b7837b5010483a
| [Tuesday 01 March 2011] [12:25:27] <private_meta>	I was just confused that I got something like <id>\n<message>\n<id>\n<message2>\n<id>\n<message3>
| [Tuesday 01 March 2011] [12:26:07] <sarikan>	greetings
| [Tuesday 01 March 2011] [12:26:10] <ianbarber>	yeah, that's just xrep doing its thing, you can use req and rep for straightforward client server
| [Tuesday 01 March 2011] [12:26:30] <private_meta>	Well, I already established I need something in the range of router/dealer
| [Tuesday 01 March 2011] [12:26:42] <ianbarber>	if you went req -> xrep -> xreq -> rep the 'req' and 'rep' would never see the extra field
| [Tuesday 01 March 2011] [12:26:51] <private_meta>	pieterh said something that would fit my requirements would be the majordomo protocol he is currently working on
| [Tuesday 01 March 2011] [12:28:05] <private_meta>	ianbarber: I don't think the extra layer is all that neccessary
| [Tuesday 01 March 2011] [12:28:26] <private_meta>	damn.... still wanted to buy food :/
| [Tuesday 01 March 2011] [12:28:42] <private_meta>	damn this town and it's stores closing at 18.30
| [Tuesday 01 March 2011] [12:29:30] <ianbarber>	takeaway! friend to the hungry coder :)
| [Tuesday 01 March 2011] [12:30:04] <private_meta>	hmm
| [Tuesday 01 March 2011] [12:30:13] <private_meta>	I don't have a car :D
| [Tuesday 01 March 2011] [12:31:08] <private_meta>	And the only pizza delivery service here requires you to order 2-3 pizzas for them to deliver *sigh*
| [Tuesday 01 March 2011] [12:31:13] <ianbarber>	maybe pieterh has a fast food distribution system planned for chapter 5 of the guide
| [Tuesday 01 March 2011] [12:31:17] <private_meta>	hahaha
| [Tuesday 01 March 2011] [12:31:35] <cremes>	private_meta: it might be best if you described your use-case in detail
| [Tuesday 01 March 2011] [12:31:39] <cremes>	then we can make suggestions
| [Tuesday 01 March 2011] [12:31:45] <private_meta>	hmm
| [Tuesday 01 March 2011] [12:31:46] <cremes>	this might also be a good thing to take to the mailing list
| [Tuesday 01 March 2011] [12:32:04] <cremes>	i'm going to have to go "async" on irc in a few... lots of work to do
| [Tuesday 01 March 2011] [12:32:07] <ianbarber>	yeah, probably better if it's more than a one-line job to describe it
| [Tuesday 01 March 2011] [12:32:14] <cremes>	so following a conversation will be hard for me
| [Tuesday 01 March 2011] [12:32:18] <ianbarber>	also helpful for future people searching
| [Tuesday 01 March 2011] [12:32:43] <cremes>	private_meta: feel free to leave out the super-secret-squirrel-intellectual-property parts
| [Tuesday 01 March 2011] [12:32:47] <private_meta>	I'll start drawing a pic
| [Tuesday 01 March 2011] [12:32:52] <cremes>	that would make your boss mad if they were public :)
| [Tuesday 01 March 2011] [12:40:18] <cremes>	sustrik: ping
| [Tuesday 01 March 2011] [12:40:25] <sustrik>	pong
| [Tuesday 01 March 2011] [12:40:31] <cremes>	anything i can do to make https://github.com/zeromq/zeromq2/issues/174 clearer for you and pieterh?
| [Tuesday 01 March 2011] [12:40:54] <cremes>	he can't seem to repro the problem as stated
| [Tuesday 01 March 2011] [12:41:30] <cremes>	maybe file descriptors need to be bumped for the process to some larger value?
| [Tuesday 01 March 2011] [12:41:53] <cremes>	or src/config.hpp needs to be modified so max_sockets is > 512 (default)
| [Tuesday 01 March 2011] [12:42:07] <cremes>	i usually build the lib with 51200 as my max_sockets :)
| [Tuesday 01 March 2011] [12:42:41] <private_meta>	I have 1 "manager", the worker. I have n clients, nodes. The manager needs to send routed messages to single specified nodes which logon beforehand. Communication needs to be asynchroneous, bidirectional, so both have to initiate communication if neccessary. I also need awareness of connection termination, so a heartbeat on both sides.
| [Tuesday 01 March 2011] [12:43:11] <private_meta>	cremes, ianbarber, that would be an overall description
| [Tuesday 01 March 2011] [12:43:30] <cremes>	private_meta: yep, sounds like pieterh's new mdp project
| [Tuesday 01 March 2011] [12:43:43] <cremes>	he's hard at work on it right now; perhaps there could be collaboration?
| [Tuesday 01 March 2011] [12:43:52] <private_meta>	As soon as these asynchroneous messages arrive at their respective endpoints, a logic is already in place to handle these messages, if needed even to create synchronity out of async messages
| [Tuesday 01 March 2011] [12:44:54] <private_meta>	Well, I would like to help, it would make it faster for me in some respect, I just don't know how I can helpo
| [Tuesday 01 March 2011] [12:44:57] <private_meta>	-o
| [Tuesday 01 March 2011] [12:50:54] <private_meta>	cremes: Well... I can ask pieterh if I could do anything to help, but if not I guess that the best thing to do right now would be to get to understand zmq better until he's done
| [Tuesday 01 March 2011] [12:51:25] <cremes>	good plan... you are kind of diving into the deep end
| [Tuesday 01 March 2011] [12:51:52] <private_meta>	cremes: well, I guess it wouldn't be good for me if he finished it and I still don't know that much about it >_>
| [Tuesday 01 March 2011] [12:52:10] <private_meta>	pieterh: so anything I can do to help, just tell :D
| [Tuesday 01 March 2011] [12:52:55] <private_meta>	k, bbl
| [Tuesday 01 March 2011] [12:57:33] <sarikan>	if I use the java bindings for zeromq in a web application, would I run into threading issues?
| [Tuesday 01 March 2011] [12:58:23] <sarikan>	multiple java threads will be using jni to access zeromq 
| [Tuesday 01 March 2011] [12:59:32] <cremes>	sarikan: only if you try to access the same socket from multiple threads; allocate a 0mq socket per thread and you'll be fine
| [Tuesday 01 March 2011] [13:02:15] <sarikan>	cremes:  so If I create, use and close a socket for each request, I should be fine
| [Tuesday 01 March 2011] [13:03:08] <cremes>	sarikan: sure, but that's an anti-pattern
| [Tuesday 01 March 2011] [13:03:13] <cremes>	what's your use-case?
| [Tuesday 01 March 2011] [13:03:42] <sarikan>	java web services, talking to some native code using 0mq as the middleware
| [Tuesday 01 March 2011] [13:03:53] <sarikan>	each request to java web service ends up being a thread
| [Tuesday 01 March 2011] [13:04:15] <cremes>	sarikan: a new thread or a thread from a pool?
| [Tuesday 01 March 2011] [13:04:17] <sarikan>	so I can't think of anything other than what I've written above
| [Tuesday 01 March 2011] [13:04:34] <sarikan>	more likely to be a thread from a pool
| [Tuesday 01 March 2011] [13:05:00] <cremes>	ok, so allocate a socket for each thread in the pool and reuse the socket just like you're reusing the thread
| [Tuesday 01 March 2011] [13:05:43] <sarikan>	cremes: that is an interesting approach, if I can monitor and control thread creation in the java web server, it should work fine
| [Tuesday 01 March 2011] [13:07:12] <sarikan>	cremes: do you think I need to watch for this if I'm using c++ instead of java? I guess it would be the same
| [Tuesday 01 March 2011] [13:08:45] <sarikan>	cremes: thanks anyway, helpful starting point
| [Tuesday 01 March 2011] [14:03:00] <Guthur>	I just noticed ZMQ_FD, is that not going to be a little problematic if we manage to get named pipes on Windows?
| [Tuesday 01 March 2011] [15:20:14] <Guthur>	is there some overriding technical reason why it is not possible to query for assigned subscription patterns
| [Tuesday 01 March 2011] [16:51:49] <mikko>	man, i love london
| [Tuesday 01 March 2011] [16:51:56] <mikko>	it's full of random things and events
| [Tuesday 01 March 2011] [17:02:38] <Guthur>	mikko, you a londoner then?
| [Tuesday 01 March 2011] [17:02:53] <mikko>	yep
| [Tuesday 01 March 2011] [17:03:01] <Guthur>	I was there last week actually, it's ok.
| [Tuesday 01 March 2011] [17:03:20] <Guthur>	I was only there for 2 days though, and it was mostly business
| [Tuesday 01 March 2011] [17:03:27] <mikko>	you should've told!
| [Tuesday 01 March 2011] [17:03:33] <mikko>	we could've had a mini-meetup
| [Tuesday 01 March 2011] [17:03:43] <Guthur>	never thought actually
| [Tuesday 01 March 2011] [17:04:01] <mikko>	we went out for beers last time sustrik was here
| [Tuesday 01 March 2011] [17:04:12] <mikko>	one other guy from london came out as well
| [Tuesday 01 March 2011] [17:04:55] <Guthur>	i'm sure i'll be there again sometime, i'm only across the irish sea, hehe
| [Tuesday 01 March 2011] [17:05:16] <ianbarber>	definitely up for london mini-meetups if everyone is about
| [Tuesday 01 March 2011] [17:05:22] <Guthur>	actually does anyone leave near Hamburg
| [Tuesday 01 March 2011] [17:05:24] <Guthur>	leave/live
| [Tuesday 01 March 2011] [17:05:25] <mikko>	we could organise one
| [Tuesday 01 March 2011] [17:05:58] <Guthur>	i'm in hamburg for the European Lisp Symposium
| [Tuesday 01 March 2011] [17:06:46] <Guthur>	it's a shame I never thought of setting up some demo with ZeroMQ and Common Lisp,  the theme for this year is concurrency
| [Tuesday 01 March 2011] [17:07:00] <mikko>	ianbarber: why don't we organise one at some point?
| [Tuesday 01 March 2011] [17:07:39] <ianbarber>	mikko: that's a good idea! 
| [Tuesday 01 March 2011] [17:07:51] <ianbarber>	we can setup a meetup event or something, and email the list
| [Tuesday 01 March 2011] [17:07:59] <ianbarber>	mid-late march?
| [Tuesday 01 March 2011] [17:09:00] <ianbarber>	i'm at confoo next week, but maybe the 17th or something like that
| [Tuesday 01 March 2011] [17:09:47] <mikko>	groupspaces
| [Tuesday 01 March 2011] [17:09:52] <mikko>	support local industries
| [Tuesday 01 March 2011] [17:10:56] <ianbarber>	good point :)
| [Tuesday 01 March 2011] [17:18:51] <ianbarber>	done: http://groupspaces.com/zeromq-london/ :)
| [Tuesday 01 March 2011] [19:30:07] <skm>	if a pusher has pushed 100msgd, the first client to call recv then gets all 100 msgs (and has to recv 99 more times to see them) - correct?
| [Tuesday 01 March 2011] [20:22:02] <Guthur>	skm, according to the docs push will go into an exceptional state if there is nothing downstream to recv
| [Tuesday 01 March 2011] [20:22:12] <Guthur>	http://api.zeromq.org/master:zmq-socket#toc12
| [Tuesday 01 March 2011] [20:23:19] <Guthur>	and it's load balanced across any connected downstream peers 
| [Tuesday 01 March 2011] [20:28:16] <skm>	i want to know what happens though when multiple clients connect with 100pending messages
| [Tuesday 01 March 2011] [20:28:23] <skm>	and the first connected client calls recv
| [Tuesday 01 March 2011] [20:28:51] <skm>	does it get one message or are all messages then sent to that
| [Tuesday 01 March 2011] [20:29:37] <skm>	im using the nodejs javascript binding which that is the case - the first recv gets all messages (and needs to call recv another 99 times to read the other messages)
| [Tuesday 01 March 2011] [20:29:59] <skm>	im just wondering if that is because of the binding or if that's the way 0mq works
| [Tuesday 01 March 2011] [20:30:03] <Guthur>	umm does sound right to me
| [Tuesday 01 March 2011] [20:30:06] <Guthur>	doesn't
| [Tuesday 01 March 2011] [20:30:43] <Guthur>	well that doesn't sound like it full fills the load-balancing aspect
| [Tuesday 01 March 2011] [20:32:17] <Guthur>	I can't say for sure to be honest
| [Tuesday 01 March 2011] [20:32:32] <Guthur>	someone else will have to clarify
| [Tuesday 01 March 2011] [21:43:50] <jugg>	pieterh, api.zeromq.org defaults to 'master/2.2.0'.  Perhaps it should default to the current stable release?
| [Tuesday 01 March 2011] [21:44:20] <jugg>	eg, the same as the redirects from the old api pages.
| [Wednesday 02 March 2011] [02:19:25] <Steve-o>	almost complete for next release of OpenPGM, just need platform tests on Autoconf & Cmake
| [Wednesday 02 March 2011] [02:19:58] <Steve-o>	performance docs uploaded for Windows, Linux, Sparc, general latency improvement all around
| [Wednesday 02 March 2011] [03:01:48] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r5fcef1c 10/ (9 files in 3 dirs): 
| [Wednesday 02 March 2011] [03:01:48] <CIA-21>	zeromq2: ZMQ_MAXMSGSIZE option added
| [Wednesday 02 March 2011] [03:01:48] <CIA-21>	zeromq2: The new option allows user to guard against peers sending
| [Wednesday 02 March 2011] [03:01:48] <CIA-21>	zeromq2: oversized messages. Connection to peer sending oversized message
| [Wednesday 02 March 2011] [03:01:48] <CIA-21>	zeromq2: is dropped.
| [Wednesday 02 March 2011] [03:01:48] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/eXNW24
| [Wednesday 02 March 2011] [03:48:00] <eyecue>	*waves* o/~
| [Wednesday 02 March 2011] [03:48:22] <eyecue>	watching pieters preso, very cool
| [Wednesday 02 March 2011] [04:30:04] <yrashk>	ok so apparently erlang binding (say, ezmq) isn't that slow
| [Wednesday 02 March 2011] [04:30:29] <yrashk>	the perf tests were erroneously scripted as interpreted code
| [Wednesday 02 March 2011] [04:30:33] <yrashk>	which slowed things down
| [Wednesday 02 March 2011] [04:30:52] <sustrik>	heh
| [Wednesday 02 March 2011] [04:30:59] <sustrik>	what are the figures now?
| [Wednesday 02 March 2011] [04:31:25] <yrashk>	11-13mb/s
| [Wednesday 02 March 2011] [04:31:41] <sustrik>	and in msgs/sec?
| [Wednesday 02 March 2011] [04:31:53] <yrashk>	I don't have that data yet, let me ask the guy who discovered this
| [Wednesday 02 March 2011] [04:32:10] <sustrik>	sure
| [Wednesday 02 March 2011] [04:35:39] <yrashk>	750694msg/s
| [Wednesday 02 March 2011] [04:36:34] <yrashk>	minor correction, with erlang-to-erlang local-remote it's rather 6mb/s
| [Wednesday 02 March 2011] [04:36:42] <yrashk>	but still that 750694msg/s
| [Wednesday 02 March 2011] [04:36:54] <yrashk>	still way better
| [Wednesday 02 March 2011] [04:43:35] <yrashk>	this is exciting
| [Wednesday 02 March 2011] [04:43:38] <yrashk>	sustrik: ^^
| [Wednesday 02 March 2011] [04:51:06] <Steve-o>	that's on 100mb or 1gb?
| [Wednesday 02 March 2011] [04:51:45] <yrashk>	that's on localhost I believe
| [Wednesday 02 March 2011] [04:53:00] <Steve-o>	eek
| [Wednesday 02 March 2011] [04:55:50] <Steve-o>	that's a bit of a hit
| [Wednesday 02 March 2011] [05:02:08] <jugg>	yrashk, have you confirmed this, as I tried compiling the code previously and it made no difference.
| [Wednesday 02 March 2011] [05:02:52] <yrashk>	jugg: I can't confirm this myself yet, but the guy clais this is what he gets on compiled modules (not on compiled escripts), and he's promising to send a pull req soon
| [Wednesday 02 March 2011] [05:03:10] <yrashk>	jugg: have you been trying to compile for erlzmq? using -mode(compile) or by converting them into modules?
| [Wednesday 02 March 2011] [05:03:21] <jugg>	both, neither changes performance.
| [Wednesday 02 March 2011] [05:03:24] <pieterh>	re
| [Wednesday 02 March 2011] [05:03:35] <yrashk>	well maybe ezmq is superior? ;)
| [Wednesday 02 March 2011] [05:03:44] <jugg>	:)
| [Wednesday 02 March 2011] [05:03:59] <yrashk>	after all it doesn't have that decoding/encoding overhead
| [Wednesday 02 March 2011] [05:04:23] <jugg>	I'll be interested if you can confirm the results.
| [Wednesday 02 March 2011] [05:06:09] <yrashk>	I am waiting for that pull req
| [Wednesday 02 March 2011] [05:06:14] 	 * eyecue blinks
| [Wednesday 02 March 2011] [05:06:28] <yrashk>	I hope I will be able to confirm this soon
| [Wednesday 02 March 2011] [05:06:35] <eyecue>	reading the guide :]
| [Wednesday 02 March 2011] [05:09:44] <eyecue>	the install guide mentions uuid-dev and uuid/e2fsprogs libs, but the FreeBSD port for ezmq doesnt seem to depend on them. are these conditional/optional dependencies?
| [Wednesday 02 March 2011] [05:11:45] <yrashk>	you mean the fbsd port of 0mq?
| [Wednesday 02 March 2011] [05:11:52] <yrashk>	because ezmq is an erlang library
| [Wednesday 02 March 2011] [05:12:00] <yrashk>	because ezmq is the erlang library for 0mq*
| [Wednesday 02 March 2011] [05:12:18] <eyecue>	apologies :)
| [Wednesday 02 March 2011] [05:12:20] <eyecue>	0mq.
| [Wednesday 02 March 2011] [05:12:35] <eyecue>	under http://www.freshports.org/net/zmq for reference
| [Wednesday 02 March 2011] [05:13:36] <eyecue>	yay, python bindings are in ports too
| [Wednesday 02 March 2011] [05:19:22] <pieterh>	yrashk: are those figures published anywhere?
| [Wednesday 02 March 2011] [05:23:03] <yrashk>	pieterh: not yet, it's the other guy who's fixing perf tests
| [Wednesday 02 March 2011] [05:23:33] <pieterh>	750K, up from, what was it, 20K or so?
| [Wednesday 02 March 2011] [05:23:37] <pieterh>	pretty nice
| [Wednesday 02 March 2011] [05:28:46] <yrashk>	pieterh: ya
| [Wednesday 02 March 2011] [05:28:54] <yrashk>	from 30Kish
| [Wednesday 02 March 2011] [05:33:48] <yrashk>	pieterh: it's basically without changing ezmq, just fixing perf tests
| [Wednesday 02 March 2011] [05:34:04] <yrashk>	although according to jugg the same approach didn't help speeding up erlzmq perf tests
| [Wednesday 02 March 2011] [05:34:37] 	 * pieterh is somewhat confused with all the e{rl}zmq versions
| [Wednesday 02 March 2011] [05:35:06] <pieterh>	ezmq is the latest rewrite, right?
| [Wednesday 02 March 2011] [05:35:20] <yrashk>	pieterh: ezmq is my NIF-based complete rewrite
| [Wednesday 02 March 2011] [05:35:33] <yrashk>	both erlzmqs (yeah, there are two of them) are port driver-based
| [Wednesday 02 March 2011] [05:35:56] <pieterh>	right, so eventually you want to merge all these together and call the result erlzmq again, I guess
| [Wednesday 02 March 2011] [05:36:05] <yrashk>	not necessarily
| [Wednesday 02 March 2011] [05:36:21] <yrashk>	and this is unlikely to happen I think
| [Wednesday 02 March 2011] [05:36:26] <pieterh>	hmm
| [Wednesday 02 March 2011] [05:36:27] <yrashk>	they are both quite different
| [Wednesday 02 March 2011] [05:36:36] <pieterh>	different APIs for apps?
| [Wednesday 02 March 2011] [05:36:40] <yrashk>	different approaches to interfacing with C
| [Wednesday 02 March 2011] [05:37:06] <pieterh>	is that relevant to users, except for performance?
| [Wednesday 02 March 2011] [05:37:25] <yrashk>	it is not
| [Wednesday 02 March 2011] [05:37:32] <yrashk>	for the most part
| [Wednesday 02 March 2011] [05:37:41] <pieterh>	so when I say 'merge' I mean, replace
| [Wednesday 02 March 2011] [05:38:09] <yrashk>	it's really up to saleyn and jugg, really
| [Wednesday 02 March 2011] [05:38:38] <pieterh>	of course
| [Wednesday 02 March 2011] [05:38:43] <yrashk>	I am just trying to maintain my own binding as I personally prefer NIF bindings
| [Wednesday 02 March 2011] [05:39:00] <yrashk>	I don't really care if it will be an official binding or not
| [Wednesday 02 March 2011] [05:39:03] <eyecue>	yrashk; sorry, newbie here, NIF? :)
| [Wednesday 02 March 2011] [05:39:18] <yrashk>	eyecue: Native Implemented Function, erlang term
| [Wednesday 02 March 2011] [05:39:23] <eyecue>	ta :]
| [Wednesday 02 March 2011] [05:39:56] <yrashk>	pieterh: I am fine if ezmq will remain as secondary binding
| [Wednesday 02 March 2011] [05:40:02] <yrashk>	as a*
| [Wednesday 02 March 2011] [05:40:07] <eyecue>	pieterh; btw, loving what i see/read about 0mq so far. trying to figure out how i can apply it to our email architecture
| [Wednesday 02 March 2011] [05:40:50] <pieterh>	yrashk: I'd personally use names that are more explanatory
| [Wednesday 02 March 2011] [05:41:01] <pieterh>	e.g. erlzmq-nif
| [Wednesday 02 March 2011] [05:41:10] <pieterh>	but it's not my call
| [Wednesday 02 March 2011] [05:41:44] <pieterh>	eyecue: glad you like it
| [Wednesday 02 March 2011] [05:41:56] <eyecue>	yrashk; just came across the UUID reference in the guide btw: All ?MQ sockets have identities but by default they are generated 'unique universal identifiers' (UUIDs)
| [Wednesday 02 March 2011] [05:42:31] <eyecue>	perhaps only relevent when using identies with durable sockets?
| [Wednesday 02 March 2011] [05:42:57] <yrashk>	pieterh: well... I don't have an opinion on that right now
| [Wednesday 02 March 2011] [05:43:24] <yrashk>	I think erlzmq and erlzmq-nif implies that the latter is a fork of a sort or soemthing
| [Wednesday 02 March 2011] [05:44:16] <yrashk>	but ezmq is in fact a full rewrite
| [Wednesday 02 March 2011] [05:44:21] <yrashk>	except for the constants
| [Wednesday 02 March 2011] [05:44:29] <yrashk>	I admit I stole the header file
| [Wednesday 02 March 2011] [05:44:52] <yrashk>	either way
| [Wednesday 02 March 2011] [05:45:01] <yrashk>	this is a minor issue (naming and whatnot)
| [Wednesday 02 March 2011] [05:46:12] <pieterh>	there are similarly several versions of clrzmq
| [Wednesday 02 March 2011] [05:46:27] <pieterh>	the latest one simply called itself clrzmq2 
| [Wednesday 02 March 2011] [05:46:34] <yrashk>	.net?
| [Wednesday 02 March 2011] [05:46:47] <pieterh>	yes
| [Wednesday 02 March 2011] [05:47:18] <yrashk>	well
| [Wednesday 02 March 2011] [05:47:24] <pieterh>	naming is always delicate
| [Wednesday 02 March 2011] [05:47:29] <yrashk>	yes and no
| [Wednesday 02 March 2011] [05:47:35] <pieterh>	imagine ezmq really takes off (it's lovely and fast)
| [Wednesday 02 March 2011] [05:47:49] <pieterh>	you'll have confused users asking, for years, why it's 'ezmq' and not 'erlzmq'...
| [Wednesday 02 March 2011] [05:47:54] <pieterh>	just my 5c
| [Wednesday 02 March 2011] [05:48:00] <eyecue>	i can vouch for that already :D
| [Wednesday 02 March 2011] [05:48:03] <yrashk>	I'll take care of this later
| [Wednesday 02 March 2011] [05:48:17] <yrashk>	I am just too lazy to think about this now
| [Wednesday 02 March 2011] [05:48:20] <pieterh>	lol
| [Wednesday 02 March 2011] [05:48:29] <yrashk>	sipping beer feels better
| [Wednesday 02 March 2011] [05:48:47] <yrashk>	I just hate renaming all files and module names
| [Wednesday 02 March 2011] [05:49:07] <eyecue>	pieterh; are you guys talking about various iterations/forks of the same  essential codebase implementing various new structures/patterns/paradigms, or something entirely different?
| [Wednesday 02 March 2011] [05:49:27] <pieterh>	yrashk: it doesn't get easier over time, indeed the name will stick
| [Wednesday 02 March 2011] [05:49:34] <eyecue>	and subsequently what to name the resulting output codebase?
| [Wednesday 02 March 2011] [05:49:36] <pieterh>	eyecue: it's a rewrite, as yrashk said
| [Wednesday 02 March 2011] [05:49:56] <yrashk>	ya from scratch
| [Wednesday 02 March 2011] [05:50:01] <pieterh>	but it exposes the same API to applications, so from users' point of view it's a Version 2
| [Wednesday 02 March 2011] [05:50:07] <eyecue>	whats the purpose /goal / driving motivator behind it ?
| [Wednesday 02 March 2011] [05:50:08] <yrashk>	pieterh: not the same
| [Wednesday 02 March 2011] [05:50:20] <yrashk>	pieterh: it's slightly different
| [Wednesday 02 March 2011] [05:50:26] <eyecue>	internal extensibility, or abstracting away upgrades behind the scenes?
| [Wednesday 02 March 2011] [05:50:27] <pieterh>	yrashk: sure
| [Wednesday 02 March 2011] [05:55:49] <yrashk>	this is ezmq results with fixed perf tests on my mac pro
| [Wednesday 02 March 2011] [05:55:49] <yrashk>	message size: 1 [B]
| [Wednesday 02 March 2011] [05:55:49] <yrashk>	message count: 1000000
| [Wednesday 02 March 2011] [05:55:50] <yrashk>	mean throughput: 1330266.625339717 [msg/s]
| [Wednesday 02 March 2011] [05:55:50] <yrashk>	mean throughput: 10.642133002717735 [Mb/s]
| [Wednesday 02 March 2011] [05:56:17] <pieterh>	yrashk: you should do 10M messages, perhaps
| [Wednesday 02 March 2011] [05:56:54] <pieterh>	I love the 17-digit precision
| [Wednesday 02 March 2011] [05:57:10] <pieterh>	1.3M msg/sec is pretty impressive
| [Wednesday 02 March 2011] [05:57:59] <eyecue>	certainly for sync tasks, id be keen to see the relative changes at incremental message sizes
| [Wednesday 02 March 2011] [05:58:04] <yrashk>	sure
| [Wednesday 02 March 2011] [05:58:05] <yrashk>	message size: 1 [B]
| [Wednesday 02 March 2011] [05:58:05] <yrashk>	message count: 10000000
| [Wednesday 02 March 2011] [05:58:05] <yrashk>	mean throughput: 1312724.6071802885 [msg/s]
| [Wednesday 02 March 2011] [05:58:05] <yrashk>	mean throughput: 10.501796857442308 [Mb/s]
| [Wednesday 02 March 2011] [05:58:30] <eyecue>	yrashk; ipc or?
| [Wednesday 02 March 2011] [05:58:35] <yrashk>	tcp
| [Wednesday 02 March 2011] [05:58:45] <eyecue>	local i take it ?
| [Wednesday 02 March 2011] [05:58:47] <yrashk>	ya
| [Wednesday 02 March 2011] [05:58:52] <eyecue>	sweet
| [Wednesday 02 March 2011] [05:58:56] <yrashk>	not bad
| [Wednesday 02 March 2011] [05:59:01] <yrashk>	jugg: ^^^
| [Wednesday 02 March 2011] [05:59:01] <eyecue>	whats the tcp overhead above ipc ?
| [Wednesday 02 March 2011] [05:59:09] <eyecue>	on the same 'box'
| [Wednesday 02 March 2011] [05:59:10] <yrashk>	I have no #s
| [Wednesday 02 March 2011] [05:59:12] <yrashk>	ah
| [Wednesday 02 March 2011] [05:59:13] <yrashk>	that
| [Wednesday 02 March 2011] [05:59:23] <eyecue>	quite interesting
| [Wednesday 02 March 2011] [05:59:51] <eyecue>	i can so tell im going to be spending alot more time on 0mq.
| [Wednesday 02 March 2011] [06:00:47] <yrashk>	never used ipc
| [Wednesday 02 March 2011] [06:00:54] <yrashk>	what would be an example ipc:// url?
| [Wednesday 02 March 2011] [06:01:21] <eyecue>	correct me if im wrong, but ipc:///tmp/somesocketname?
| [Wednesday 02 March 2011] [06:02:04] <eyecue>	first video on http://www.zeromq.org/intro:read-the-manual shows an example (i may be wrong)
| [Wednesday 02 March 2011] [06:02:42] <yrashk>	pieterh: on my hw c-to-c perf test is about twice as fast
| [Wednesday 02 March 2011] [06:02:50] <yrashk>	it makes me sad :-(
| [Wednesday 02 March 2011] [06:03:09] <pieterh>	yrashk: it's tragic
| [Wednesday 02 March 2011] [06:03:25] <yrashk>	this is on ipc: 
| [Wednesday 02 March 2011] [06:03:25] <yrashk>	mean throughput: 1343429.6550005474 [msg/s]
| [Wednesday 02 March 2011] [06:03:25] <yrashk>	mean throughput: 10.747437240004379 [Mb/s]
| [Wednesday 02 March 2011] [06:03:31] <eyecue>	again, excuse what might be a silly question, c-to-c ?
| [Wednesday 02 March 2011] [06:03:31] <yrashk>	pretty much the same
| [Wednesday 02 March 2011] [06:03:32] <pieterh>	eyecue: yes, that would be a good place to put ipc files
| [Wednesday 02 March 2011] [06:03:42] <eyecue>	yrashk; thats pretty cool
| [Wednesday 02 March 2011] [06:04:06] <yrashk>	eyecue: perf tests from zeromq itself as opposed those implemented in erlang (which is what I am testing right now)
| [Wednesday 02 March 2011] [06:04:13] <pieterh>	ipc:// uses a filename, e.g. ipc://somefile.ipc
| [Wednesday 02 March 2011] [06:04:20] <yrashk>	pieterh: sarcasm? ;)
| [Wednesday 02 March 2011] [06:04:23] <pieterh>	must be writeable by all processes that use it
| [Wednesday 02 March 2011] [06:04:27] <eyecue>	yrashk; thats what i thought :)
| [Wednesday 02 March 2011] [06:04:28] <pieterh>	yrashk: gentle irony
| [Wednesday 02 March 2011] [06:04:33] <eyecue>	pieterh; i saw the uid note for it :]
| [Wednesday 02 March 2011] [06:04:38] <yrashk>	pieterh: do you think this is a good result?
| [Wednesday 02 March 2011] [06:04:43] <pieterh>	yrashk: rather good, yes
| [Wednesday 02 March 2011] [06:05:00] <eyecue>	i find it interesting that an ipc socket and tcp perf is roughly the same
| [Wednesday 02 March 2011] [06:05:17] <pieterh>	eyecue: they are identical, on Linux localhost
| [Wednesday 02 March 2011] [06:05:23] <pieterh>	local domain sockets
| [Wednesday 02 March 2011] [06:05:38] <yrashk>	it's osx
| [Wednesday 02 March 2011] [06:06:01] <pieterh>	osx is linux, it just hasn't quite realized it yet
| [Wednesday 02 March 2011] [06:06:04] <pieterh>	:-)
| [Wednesday 02 March 2011] [06:06:11] <eyecue>	still the file socket stack and tcp stacks often have quite not-the-same performance characteristics, and tuning parameters
| [Wednesday 02 March 2011] [06:06:14] <pieterh>	yrashk: you could try inproc to see what the raw API costs are
| [Wednesday 02 March 2011] [06:06:44] <yrashk>	pieterh: for that I have to tweak tests... not in this beer mode :)
| [Wednesday 02 March 2011] [06:07:26] <pieterh>	ah, beer mode... :-)
| [Wednesday 02 March 2011] [06:07:30] <pieterh>	i'm in coffee mode here
| [Wednesday 02 March 2011] [06:08:04] <eyecue>	i wish i was in coffee mode, food search mode here :)
| [Wednesday 02 March 2011] [06:08:07] <eyecue>	<-- .au
| [Wednesday 02 March 2011] [06:09:03] <sejo>	quick question, if I create a FIFO que with 2 servers and multiple clients, is it possible to save the items in the que somewhere to make sure when the servers crash the items are retrievable?
| [Wednesday 02 March 2011] [06:09:13] <sejo>	or should I write such code myself?
| [Wednesday 02 March 2011] [06:10:27] <pieterh>	sejo: it's being explained in Chapter 4 of the guide
| [Wednesday 02 March 2011] [06:10:34] <eyecue>	workers can die too, so resilience there can often be more important than queue resilience
| [Wednesday 02 March 2011] [06:10:35] <pieterh>	see http://zero.mq/md
| [Wednesday 02 March 2011] [06:10:46] <pieterh>	I'm working on an implementation of that right now
| [Wednesday 02 March 2011] [06:10:50] <eyecue>	ooo, a new page to look at
| [Wednesday 02 March 2011] [06:11:03] <eyecue>	pieterh; why the name majordomo?
| [Wednesday 02 March 2011] [06:11:12] <Guthur>	pieterh: what stage of completeness is Ch4? out of interest
| [Wednesday 02 March 2011] [06:11:13] <pieterh>	eyecue: all the patterns in Ch4 get cute names
| [Wednesday 02 March 2011] [06:11:22] <pieterh>	and Ch4 is about 50% done afaics
| [Wednesday 02 March 2011] [06:11:28] <eyecue>	not worried about the open source app by the same name ? :]
| [Wednesday 02 March 2011] [06:11:32] <pieterh>	Majordomo because it provides a reliable service
| [Wednesday 02 March 2011] [06:11:34] <eyecue>	or are you leveraging it ;)
| [Wednesday 02 March 2011] [06:11:39] <pieterh>	what other app?
| [Wednesday 02 March 2011] [06:11:44] 	 * pieterh is happily ignorant
| [Wednesday 02 March 2011] [06:11:48] <eyecue>	majordomo the mailing list manager :]
| [Wednesday 02 March 2011] [06:11:54] <pieterh>	no idea what you're talking about
| [Wednesday 02 March 2011] [06:12:27] <eyecue>	one of the most widely used open source mailing list management softwares :]
| [Wednesday 02 March 2011] [06:12:40] <pieterh>	does it use 0MQ?
| [Wednesday 02 March 2011] [06:12:48] <eyecue>	nono, its name is just majordomo
| [Wednesday 02 March 2011] [06:13:00] <pieterh>	do they have a trademark on their name?
| [Wednesday 02 March 2011] [06:13:07] 	 * pieterh checks that rapidly...
| [Wednesday 02 March 2011] [06:13:15] <Guthur>	I'd guess no
| [Wednesday 02 March 2011] [06:13:24] <eyecue>	greatcircle software is the company who makes it, but ive never thought of that :)
| [Wednesday 02 March 2011] [06:13:25] <pieterh>	they don't even own majordomo.org
| [Wednesday 02 March 2011] [06:13:34] <ianbarber>	you're probably all right on this one, it's more of a protocol thing than a particular bit of software
| [Wednesday 02 March 2011] [06:13:51] <Guthur>	wiki has this on the majordomo page: Development status	End of life
| [Wednesday 02 March 2011] [06:13:53] <pieterh>	legally, if there is a trademark and risk of confusion, I'd have to choose another name
| [Wednesday 02 March 2011] [06:14:07] <ianbarber>	wordpress inspired the ire of many recently by naming their most recent release django, which was clever
| [Wednesday 02 March 2011] [06:14:18] <eyecue>	yah it was more out of interest than to point out any/possible risks :]
| [Wednesday 02 March 2011] [06:14:23] <Guthur>	last stable release 11 years ago
| [Wednesday 02 March 2011] [06:14:30] <pieterh>	morally, this is a 0MQ pattern name, there is no confusion
| [Wednesday 02 March 2011] [06:14:34] <Guthur>	it's possible it is perfect though
| [Wednesday 02 March 2011] [06:14:39] <pieterh>	like Libero
| [Wednesday 02 March 2011] [06:14:40] <eyecue>	there is of course the issue of user confusion, but i digress
| [Wednesday 02 March 2011] [06:15:04] <pieterh>	Libero is a FSM tool I wrote in the early 90's, which actually had no bugs and no more features to add
| [Wednesday 02 March 2011] [06:15:22] <pieterh>	so perhaps Majordomo-the-software was perfect, but ... probably it's just dead
| [Wednesday 02 March 2011] [06:15:31] 	 * pieterh can digress with the best of them
| [Wednesday 02 March 2011] [06:15:40] <Guthur>	it can even run on newer versions of Unix, apparently
| [Wednesday 02 March 2011] [06:15:41] <eyecue>	its still one of the most widely deployed mailing list managers for open source projects full stop :]
| [Wednesday 02 March 2011] [06:15:47] <Guthur>	all this from the wiki page mind you
| [Wednesday 02 March 2011] [06:15:52] <Guthur>	can/can't
| [Wednesday 02 March 2011] [06:15:55] <eyecue>	im actually quite suprised youd never heard of it
| [Wednesday 02 March 2011] [06:16:29] <pieterh>	aiksaurus suggests 'chamberlain' as an alternative but somehow I prefer 'Majordomo'
| [Wednesday 02 March 2011] [06:16:40] <eyecue>	it sounds authoritive :)
| [Wednesday 02 March 2011] [06:16:59] 	 * pieterh gets back to coding
| [Wednesday 02 March 2011] [06:37:37] <pieterh>	ianbarber: so we're on for the 16th?
| [Wednesday 02 March 2011] [06:38:54] <ianbarber>	yep
| [Wednesday 02 March 2011] [06:40:38] <ianbarber>	just tweeted about it, i haven't actually been to this place before, but mikko knows it
| [Wednesday 02 March 2011] [06:41:46] <ianbarber>	it's near oxford circus so it's just straight down the victoria line for kings cross, if you can come, and come in by train
| [Wednesday 02 March 2011] [06:45:57] <ianbarber>	will be awesome! do you have any clients in London to see or similar, feel bad for your travel if you're just coming to chat to us :) 
| [Wednesday 02 March 2011] [06:58:52] <pieterh>	ianbarber: yes, there are always people to meet in London
| [Wednesday 02 March 2011] [06:59:05] <yrashk>	night everybody :)
| [Wednesday 02 March 2011] [06:59:10] <ianbarber>	:)
| [Wednesday 02 March 2011] [06:59:11] <pieterh>	yrashk: night :-)
| [Wednesday 02 March 2011] [07:12:24] <eyecue>	night
| [Wednesday 02 March 2011] [07:21:14] <private_meta>	haven't been in London for 3 years
| [Wednesday 02 March 2011] [07:45:44] <pieterh>	ianbarber: do you want a link shortener at zero.mq? I've set this up at zero.mq/go
| [Wednesday 02 March 2011] [07:46:00] <ianbarber>	oh, that's an idea
| [Wednesday 02 March 2011] [07:46:21] <ianbarber>	have to chuck canonical links in heads of pages
| [Wednesday 02 March 2011] [07:47:27] <ianbarber>	that looks very handy
| [Wednesday 02 March 2011] [07:47:49] <pieterh>	register at Wikidot if not done, click Join and I'll give you access
| [Wednesday 02 March 2011] [07:49:25] <ianbarber>	done
| [Wednesday 02 March 2011] [07:52:04] <pieterh>	done: to create a shortcut you just enter the short URL you want, then click Create, and enter the target URL in the page title and save
| [Wednesday 02 March 2011] [07:52:53] <pieterh>	ianbarber: I've made you site admin too, so you can give others ccess
| [Wednesday 02 March 2011] [07:52:58] <pieterh>	*access
| [Wednesday 02 March 2011] [07:53:01] <sejo>	ping
| [Wednesday 02 March 2011] [07:53:07] <sejo>	sorry
| [Wednesday 02 March 2011] [07:53:38] <pieterh>	ianbarber: yay :-) it works
| [Wednesday 02 March 2011] [07:53:53] <ianbarber>	cool :)
| [Wednesday 02 March 2011] [07:53:58] <ianbarber>	thanks!
| [Wednesday 02 March 2011] [07:55:48] <pieterh>	hey, thanks to you for zero.mq, it's quite a fun toy
| [Wednesday 02 March 2011] [07:57:09] <pieterh>	have to leave, cyal