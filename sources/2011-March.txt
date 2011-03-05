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
| [Wednesday 02 March 2011] [08:44:35] <private_meta>	pieterh: in the majordomo protocol, why does the client have a nullbyte?
| [Wednesday 02 March 2011] [08:45:26] <private_meta>	pieterh: is it because the REQ socket normally inserts it?
| [Wednesday 02 March 2011] [09:05:26] <guyvdb_>	Hi, I am just starting to read about zeromq. Is the socket event driven behind the scenes? I.e. if I do zmq_bind() on a server and then 10K low traffic clients do zmq_connect() is the library doing epoll() or similar in the background?
| [Wednesday 02 March 2011] [09:45:16] <djc>	anyone around? I could use some help with my first zmq thingy
| [Wednesday 02 March 2011] [09:45:49] <drbobbeaty>	djc: I'm no expert, but you can ask, and I can see if I can help.
| [Wednesday 02 March 2011] [09:46:08] <djc>	I'm trying to do a pub/sub thing
| [Wednesday 02 March 2011] [09:46:20] <djc>	but I'm not getting any messages on the client
| [Wednesday 02 March 2011] [09:46:38] <djc>	(the zmq_send() call on the publisher returns 0, so that seems to work at least)
| [Wednesday 02 March 2011] [09:46:45] <drbobbeaty>	Have you looked at the Guide? It's got PUB/SUB examples...
| [Wednesday 02 March 2011] [09:46:48] <djc>	the client just sits there, apparently blocking
| [Wednesday 02 March 2011] [09:46:53] <djc>	yeah, I'm looking at it
| [Wednesday 02 March 2011] [09:46:59] <djc>	that's what I derived my code from :)
| [Wednesday 02 March 2011] [09:47:01] <drbobbeaty>	The client's recv() will block - that's by design.
| [Wednesday 02 March 2011] [09:47:38] <drbobbeaty>	What transport are you using? The URL used by the PUB and SUB to know where to PUB and SUB.
| [Wednesday 02 March 2011] [09:47:55] <guido_g>	djc: paste your code (and any error message) to a paste bin, w/o the code we're guessing
| [Wednesday 02 March 2011] [09:49:36] <guido_g>	https://github.com/ <- nice paste bin
| [Wednesday 02 March 2011] [09:50:08] <guido_g>	oops https://gist.github.com/ <- take this
| [Wednesday 02 March 2011] [09:50:18] <djc>	http://dpaste.com/465507/
| [Wednesday 02 March 2011] [09:50:56] <djc>	is what I have so far
| [Wednesday 02 March 2011] [09:51:01] <guido_g>	tz tz tz
| [Wednesday 02 March 2011] [09:51:12] <guido_g>	you need to subscribe on the sub
| [Wednesday 02 March 2011] [09:51:17] <guido_g>	see manual and guide
| [Wednesday 02 March 2011] [09:52:42] <djc>	oops, missed that
| [Wednesday 02 March 2011] [09:56:01] <guido_g>	case closed, i assume ,)
| [Wednesday 02 March 2011] [09:56:07] <djc>	it works! \o/
| [Wednesday 02 March 2011] [09:56:09] <djc>	thanks :)
| [Wednesday 02 March 2011] [09:56:15] <djc>	(and sorry for not reading better)
| [Wednesday 02 March 2011] [09:57:06] <djc>	btw, kind of weird that the python bindings don't respect SIGINT
| [Wednesday 02 March 2011] [09:57:20] <djc>	oh, I guess it respects it only when it awakes or something
| [Wednesday 02 March 2011] [09:57:49] <guido_g>	depends on the version of the bindings *and* mq
| [Wednesday 02 March 2011] [09:58:29] <guido_g>	with pyzma from git master and 2.1.0 mq ctrl-c works, w/ older mq not
| [Wednesday 02 March 2011] [09:59:22] <djc>	yeah, I just picked up 2.0.10.1 because it's on the py bindings page
| [Wednesday 02 March 2011] [10:00:03] <guido_g>	way to old
| [Wednesday 02 March 2011] [10:00:58] <guido_g>	if you dare to compile mq yourself, use the git://github.com/zeromq/zeromq2-1.git repository I'd say
| [Wednesday 02 March 2011] [10:01:42] <guido_g>	this will be the "stable" for 2.1.x and is now "release candidate" or so
| [Wednesday 02 March 2011] [10:02:42] <djc>	well, it doesn't look like 2.1.x is "stable" yet
| [Wednesday 02 March 2011] [10:03:37] <guido_g>	it is more stable than 2.0.x ever was
| [Wednesday 02 March 2011] [10:04:20] <guido_g>	and if you start using mq there is no need to use the old version
| [Wednesday 02 March 2011] [10:04:44] <guido_g>	i'm using the old 2.1.0 tar and it's fine w/ pyzmq
| [Wednesday 02 March 2011] [10:06:53] <cremes>	sustrik: what is the use-case for setting ZMQ_MAXMSGSIZE to 0? your changes allow that but i don't see the point
| [Wednesday 02 March 2011] [10:39:00] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r18b9ebe 10/ (151 files in 9 dirs): 
| [Wednesday 02 March 2011] [10:39:01] <CIA-21>	zeromq2: The copyrights in file headers updated.
| [Wednesday 02 March 2011] [10:39:01] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/h7FJB3
| [Wednesday 02 March 2011] [10:47:12] <private_meta>	pieterh: does zmsg.c actually compile for you?
| [Wednesday 02 March 2011] [10:50:41] <cremes>	private_meta: i can't get it to compile on osx; it appears to compile ok on linux
| [Wednesday 02 March 2011] [10:50:56] <private_meta>	I'm trying to compile it on linux, cremes 
| [Wednesday 02 March 2011] [10:51:07] <cremes>	oh
| [Wednesday 02 March 2011] [10:51:30] <private_meta>	for every function in there I get a "multiple definition" error
| [Wednesday 02 March 2011] [10:51:41] <private_meta>	cremes: what's your problem on OSX?
| [Wednesday 02 March 2011] [10:52:23] <cremes>	https://gist.github.com/851138
| [Wednesday 02 March 2011] [10:54:39] <private_meta>	actually, "gcc -o file -lzmq ppqueue.c zmsg.c" SHOULD be sufficient, shouldn't it?
| [Wednesday 02 March 2011] [10:57:32] <private_meta>	cremes: hmm... I get the same result when compiling asyncsrv.c
| [Wednesday 02 March 2011] [10:58:36] <private_meta>	cremes: https://gist.github.com/355144225f76f096c67a
| [Wednesday 02 March 2011] [10:58:49] <private_meta>	cremes: what's your compile command?
| [Wednesday 02 March 2011] [11:00:59] <guido_g>	seems that the errors are in the link phase
| [Wednesday 02 March 2011] [11:01:22] <private_meta>	Seems so
| [Wednesday 02 March 2011] [11:01:29] <guido_g>	try to compile and link step-by-step
| [Wednesday 02 March 2011] [11:01:56] <private_meta>	phew... no idea how...
| [Wednesday 02 March 2011] [11:02:32] <private_meta>	k, -c
| [Wednesday 02 March 2011] [11:02:41] <guido_g>	compile the source files to .o then link these .o files to an executable using the relevant libs
| [Wednesday 02 March 2011] [11:03:05] <private_meta>	yeah, I know the steps, but I just never did them manually
| [Wednesday 02 March 2011] [11:03:13] <private_meta>	I mean, I hardly ever used gcc by hand to start
| [Wednesday 02 March 2011] [11:05:30] <private_meta>	guido_g: it compiled correctly, but the linker had the same error
| [Wednesday 02 March 2011] [11:07:38] <guido_g>	seems that all functions are already defined in the asyncsrv file
| [Wednesday 02 March 2011] [11:07:51] <guido_g>	check the includes i'd say
| [Wednesday 02 March 2011] [11:09:32] <private_meta>	Well, what makes it break is zmsg.c
| [Wednesday 02 March 2011] [11:09:38] <private_meta>	but apparently it should work
| [Wednesday 02 March 2011] [11:09:41] <cremes>	my compile command is "./build all"
| [Wednesday 02 March 2011] [11:09:44] <cremes>	:)
| [Wednesday 02 March 2011] [11:09:46] <guido_g>	*sigh*
| [Wednesday 02 March 2011] [11:10:27] <guido_g>	private_meta: did you really read the error message? it states that the functions are already there, comming from the async file
| [Wednesday 02 March 2011] [11:10:56] <guido_g>	which is strange, becase they also appear in the zmsg file
| [Wednesday 02 March 2011] [11:12:12] <private_meta>	I took it as is from the website. asyncsrv.c includes zhelpers and zmsg, zmsg itself includes zhelpers
| [Wednesday 02 March 2011] [11:12:58] <guido_g>	it includes zmsg.c?
| [Wednesday 02 March 2011] [11:13:08] <private_meta>	Don't ask me, it's treated as a .h file
| [Wednesday 02 March 2011] [11:13:25] <guido_g>	link to code
| [Wednesday 02 March 2011] [11:13:45] <private_meta>	https://github.com/imatix/zguide/tree/chapter4-wip/examples/C <-- zhelpers.h, zmsg.c, asyncsrv.c
| [Wednesday 02 March 2011] [11:13:58] <private_meta>	hmm
| [Wednesday 02 March 2011] [11:14:08] <guido_g>	oh my god
| [Wednesday 02 March 2011] [11:14:13] <private_meta>	wait,I took the non-branch one
| [Wednesday 02 March 2011] [11:14:22] <private_meta>	the master one
| [Wednesday 02 March 2011] [11:14:35] <private_meta>	What?
| [Wednesday 02 March 2011] [11:15:13] <guido_g>	it really includes a .c file
| [Wednesday 02 March 2011] [11:15:28] <guido_g>	one should poke pieter for that
| [Wednesday 02 March 2011] [11:15:52] <guido_g>	private_meta: leave out the zmq.* from the compile/link
| [Wednesday 02 March 2011] [11:16:18] <private_meta>	guido_g: ?
| [Wednesday 02 March 2011] [11:16:30] <guido_g>	what?
| [Wednesday 02 March 2011] [11:16:38] <private_meta>	what do you mean leave it out?
| [Wednesday 02 March 2011] [11:16:45] <guido_g>	drop it from the command
| [Wednesday 02 March 2011] [11:17:18] <private_meta>	oh
| [Wednesday 02 March 2011] [11:17:42] <private_meta>	>_<
| [Wednesday 02 March 2011] [11:17:56] <guido_g>	line noise?
| [Wednesday 02 March 2011] [11:17:59] <private_meta>	ok, then I need to set the file as "exclude from build" in eclipse for it to work
| [Wednesday 02 March 2011] [11:18:08] <guido_g>	in the 21st century?
| [Wednesday 02 March 2011] [11:18:37] <private_meta>	guido_g: k, thanks, stupid of me not to think of that
| [Wednesday 02 March 2011] [11:19:05] <guido_g>	also not very clever to *do that* in the first place
| [Wednesday 02 March 2011] [11:19:15] <private_meta>	ik
| [Wednesday 02 March 2011] [11:19:25] <guido_g>	you should tell pieterh and demand action
| [Wednesday 02 March 2011] [11:21:46] <cremes>	alternately, fix it and submit a patch
| [Wednesday 02 March 2011] [11:23:54] <private_meta>	I'm more interested in a C++ version
| [Wednesday 02 March 2011] [11:24:16] <private_meta>	But then everything should be a proper class and the problem would be gone
| [Wednesday 02 March 2011] [11:25:16] <guido_g>	zhelper thingie is for c
| [Wednesday 02 March 2011] [11:26:04] <guido_g>	you should use the c++ api and build from there, otherwise you put a layer on top of a layer...
| [Wednesday 02 March 2011] [11:26:13] <private_meta>	IK
| [Wednesday 02 March 2011] [11:26:18] <private_meta>	Doing that already
| [Wednesday 02 March 2011] [11:26:40] <private_meta>	In other words, I never intended to use zhelpers.c, but I need it for comparison
| [Wednesday 02 March 2011] [11:27:38] <guido_g>	compare to what?
| [Wednesday 02 March 2011] [11:27:55] <private_meta>	zhelpers.h to zhelpers.hpp equivalents
| [Wednesday 02 March 2011] [11:28:22] <private_meta>	If I use zmsg and translate it, I should do it in a way it's useful for the docs
| [Wednesday 02 March 2011] [11:28:23] <guido_g>	i don't see any benefit
| [Wednesday 02 March 2011] [11:28:48] <private_meta>	anyway, what I want to say is I won't use zhelpers.h for C++
| [Wednesday 02 March 2011] [11:29:01] <guido_g>	a useful c++ helper collection would not look like the c version, i'd guess
| [Wednesday 02 March 2011] [13:29:11] <pieterh>	re
| [Wednesday 02 March 2011] [13:30:03] <pieterh>	private_meta: you still around?
| [Wednesday 02 March 2011] [13:49:05] <pieterh>	guido_g: you around?
| [Wednesday 02 March 2011] [13:50:04] <guido_g>	jepp, now
| [Wednesday 02 March 2011] [13:50:26] <pieterh>	so what's the beef with my C coding style?
| [Wednesday 02 March 2011] [13:50:27] <pieterh>	:-)
| [Wednesday 02 March 2011] [13:51:35] <pieterh>	the idea is to allow people to compile and link individual examples 
| [Wednesday 02 March 2011] [13:51:36] <guido_g>	you're including a a c file
| [Wednesday 02 March 2011] [13:51:41] <pieterh>	rather than have to construct libraries
| [Wednesday 02 March 2011] [13:52:12] <guido_g>	but obviously the normal reflex of a c programmer is to compile c files
| [Wednesday 02 March 2011] [13:52:21] <pieterh>	there's even a 'build' script provided
| [Wednesday 02 March 2011] [13:52:23] <pieterh>	yeah
| [Wednesday 02 March 2011] [13:52:30] <pieterh>	anyhow, I'm renaming these mystery classes to .h
| [Wednesday 02 March 2011] [13:52:42] <guido_g>	would help
| [Wednesday 02 March 2011] [13:52:59] <pieterh>	it's either write 2,000 line examples, or include stuff
| [Wednesday 02 March 2011] [13:53:01] <guido_g>	i think back in the old times one would have used .i or so
| [Wednesday 02 March 2011] [13:53:12] <pieterh>	would that be clearer?
| [Wednesday 02 March 2011] [13:53:21] <guido_g>	imho yes
| [Wednesday 02 March 2011] [13:53:35] <guido_g>	.c is realy ment to be compiled
| [Wednesday 02 March 2011] [13:53:36] <pieterh>	in 2011 we're allowed as many as 3 chars per extension afaik
| [Wednesday 02 March 2011] [13:53:45] <pieterh>	.dnc?
| [Wednesday 02 March 2011] [13:53:48] <guido_g>	.h is for declarations
| [Wednesday 02 March 2011] [13:54:02] <pieterh>	zmsg.h is a class file in face
| [Wednesday 02 March 2011] [13:54:07] <pieterh>	in *fact
| [Wednesday 02 March 2011] [13:54:13] <pieterh>	a mix of declarations and methods
| [Wednesday 02 March 2011] [13:54:18] <pieterh>	aha
| [Wednesday 02 March 2011] [13:54:25] <guido_g>	sure, but it's c++ then
| [Wednesday 02 March 2011] [13:54:25] <pieterh>	#include "zmsg.class"
| [Wednesday 02 March 2011] [13:54:32] <pieterh>	yes :-)
| [Wednesday 02 March 2011] [13:54:44] <pieterh>	no, it's class-oriented C
| [Wednesday 02 March 2011] [13:54:50] <pieterh>	C++ did not take patents on that
| [Wednesday 02 March 2011] [13:55:06] <guido_g>	the only problem was to use an extension that's been assocciated w/ a specific action
| [Wednesday 02 March 2011] [13:55:18] <pieterh>	yes, you're right, makefiles and such get very confused
| [Wednesday 02 March 2011] [13:55:27] <pieterh>	people will ask me wtf the class file business is, and I can then upsell ZFL
| [Wednesday 02 March 2011] [13:55:31] <pieterh>	very neat, thanks!
| [Wednesday 02 March 2011] [13:56:59] <guido_g>	np
| [Wednesday 02 March 2011] [13:57:57] <pieterh>	this makes my evening, in fact
| [Wednesday 02 March 2011] [13:58:09] <pieterh>	I love it when a semantic comes together
| [Wednesday 02 March 2011] [14:00:33] <guido_g>	i'm still touched by the idea of including code this way
| [Wednesday 02 March 2011] [14:00:42] <guido_g>	seems odd after some decades ,)
| [Wednesday 02 March 2011] [14:03:30] <pieterh>	well, however you do it, you need to say "I want to use class XYZ"
| [Wednesday 02 March 2011] [14:03:42] <guido_g>	sure
| [Wednesday 02 March 2011] [14:04:01] <pieterh>	if I break the classes into .h and .c I *force* people to make libraries and maintain them
| [Wednesday 02 March 2011] [14:04:14] <pieterh>	this way, they can build just the single example and it works
| [Wednesday 02 March 2011] [14:04:18] <private_meta>	pieterh:  what is it?
| [Wednesday 02 March 2011] [14:04:18] <guido_g>	i finally figured it from the error messages private_meta got while linking
| [Wednesday 02 March 2011] [14:04:48] <pieterh>	well, people who are smart enough to go make their own compile / link commands instead of using the ones I provided...
| [Wednesday 02 March 2011] [14:04:53] <pieterh>	'build all'
| [Wednesday 02 March 2011] [14:04:57] <pieterh>	'build asyncsrc'
| [Wednesday 02 March 2011] [14:05:09] <guido_g>	this use of import has become uncommon in the last decades, that's all I wanted to mention ,)
| [Wednesday 02 March 2011] [14:05:32] <guido_g>	s/import/include/
| [Wednesday 02 March 2011] [14:05:45] <guido_g>	curse you, python! :)
| [Wednesday 02 March 2011] [14:06:07] <pieterh>	Python uses import, right?
| [Wednesday 02 March 2011] [14:06:19] <guido_g>	yes
| [Wednesday 02 March 2011] [14:06:25] <private_meta>	pieterh:  what did you want?
| [Wednesday 02 March 2011] [14:06:26] <guido_g>	but it's not like include
| [Wednesday 02 March 2011] [14:06:26] <pieterh>	even for basic stuff like command line arguments, which I find very quaint, as a modern C programmer
| [Wednesday 02 March 2011] [14:06:52] <guido_g>	import deals w/ namespaces
| [Wednesday 02 March 2011] [14:07:17] <guido_g>	so it's more like a combination of include w/ c++ namespaces
| [Wednesday 02 March 2011] [14:07:41] <guido_g>	w/ some dynmaic linking...
| [Wednesday 02 March 2011] [14:07:48] <guido_g>	ok
| [Wednesday 02 March 2011] [14:07:59] <guido_g>	in fact, it's not like include
| [Wednesday 02 March 2011] [14:08:53] <Guthur>	are messages beginning with 0 reserved for ZMQ, or am I imagining things?
| [Wednesday 02 March 2011] [14:09:04] <Guthur>	maybe it was identities
| [Wednesday 02 March 2011] [14:09:49] <guido_g>	the latter, afair
| [Wednesday 02 March 2011] [14:10:13] <guido_g>	mq generated identities are starting w/ a 0 byte
| [Wednesday 02 March 2011] [14:10:49] <Guthur>	ok
| [Wednesday 02 March 2011] [14:11:01] <Guthur>	at least I wasn't completely imagining things, hehe
| [Wednesday 02 March 2011] [14:11:27] <guido_g>	yeah
| [Wednesday 02 March 2011] [14:11:49] <guido_g>	it's amazing how much information is in the so sparse looking documentation
| [Wednesday 02 March 2011] [14:12:20] <cremes>	pieterh: any particular roadmap or timeframe until 2.1.1 is blessed as a final release?
| [Wednesday 02 March 2011] [14:12:35] <cremes>	reason i ask is we still have so many folks popping in here asking questions about 2.0.10
| [Wednesday 02 March 2011] [14:12:35] <pieterh>	... phone... busy
| [Wednesday 02 March 2011] [14:12:44] <cremes>	because it is the last "official" release
| [Wednesday 02 March 2011] [14:12:51] <cremes>	sure, answer whenever
| [Wednesday 02 March 2011] [14:13:24] <guido_g>	true
| [Wednesday 02 March 2011] [14:14:16] <guido_g>	and it's somewhat hard to tell people to use a "release candidate" because it's more stable than the "stable" 
| [Wednesday 02 March 2011] [14:14:25] <cremes>	agreed
| [Wednesday 02 March 2011] [14:14:53] <private_meta>	pieterh:  Btw I'm implementing zmsg as a class, I hope that helps with the c++ examples, I just didn't finish yet
| [Wednesday 02 March 2011] [14:15:56] <private_meta>	 c++ class that is
| [Wednesday 02 March 2011] [14:29:01] <pieterh>	ok, back...
| [Wednesday 02 March 2011] [14:29:19] <pieterh>	private_meta: zmsg is IMO useful in any language
| [Wednesday 02 March 2011] [14:29:44] <pieterh>	presumably modified to suit
| [Wednesday 02 March 2011] [14:29:59] <pieterh>	what it does is let you manipulate whole 0MQ multipart messages as single objects
| [Wednesday 02 March 2011] [14:30:10] <pieterh>	this is extremely useful unless you like writing repetitive code
| [Wednesday 02 March 2011] [14:30:26] <pieterh>	cremes: wrt 2.1.x, it's ASAP
| [Wednesday 02 March 2011] [14:30:36] <pieterh>	I'd like to make an rc2 this week
| [Wednesday 02 March 2011] [14:30:49] <pieterh>	and then it's probably 7-10 more days for a final stable release
| [Wednesday 02 March 2011] [14:32:16] <private_meta>	pieterh: I'm just saying I'll write a nice c++ class based version , more or Less
| [Wednesday 02 March 2011] [14:32:48] <pieterh>	IMO it will be useful in general for C++ developers
| [Wednesday 02 March 2011] [14:33:15] <cremes>	pieterh: great, i like that timeline
| [Wednesday 02 March 2011] [14:33:24] <cremes>	only 2 more weeks of questions on 2.0.10 :)
| [Wednesday 02 March 2011] [14:33:45] <pieterh>	cremes: my goal is to make new stable releases every 3 months or so
| [Wednesday 02 March 2011] [14:33:51] <pieterh>	perhaps even faster
| [Wednesday 02 March 2011] [14:34:00] <guido_g>	hmmm
| [Wednesday 02 March 2011] [14:34:01] <pieterh>	but not every six months like before
| [Wednesday 02 March 2011] [14:34:09] <pieterh>	s/six/24/
| [Wednesday 02 March 2011] [14:34:12] <cremes>	good idea; i've been "living" out of master for the past 3 months
| [Wednesday 02 March 2011] [14:34:16] <guido_g>	any news on the (e)pgm problem i reported?
| [Wednesday 02 March 2011] [14:35:21] <pieterh>	guido_g: it wasn't this one? https://github.com/zeromq/zeromq2/commit/29e0e7dbadfcd0bab70feee119bd7c5e623b38d4
| [Wednesday 02 March 2011] [14:35:44] <guido_g>	no idea
| [Wednesday 02 March 2011] [14:36:29] <guido_g>	i was just going to compile from zerom2-1
| [Wednesday 02 March 2011] [14:36:37] <guido_g>	is this fix in there?
| [Wednesday 02 March 2011] [14:37:05] <private_meta>	 pieterh,  how's Majordomo coming along?
| [Wednesday 02 March 2011] [14:37:29] <pieterh>	private_meta: quickly, I have client and worker APIs, and heartbeating in the broker
| [Wednesday 02 March 2011] [14:37:59] <pieterh>	it's all on that chapter4-wip branch that you should not be looking at
| [Wednesday 02 March 2011] [14:38:54] <private_meta>	 I've looked through it but thought as this is much WIP, should wait
| [Wednesday 02 March 2011] [14:39:37] <pieterh>	guido_g: that fix is in the zeromq2-1 git master
| [Wednesday 02 March 2011] [14:40:01] <pieterh>	we've been backporting all bug fixes from 2.2 to 2.1
| [Wednesday 02 March 2011] [14:40:06] <guido_g>	ok, just compiled it 
| [Wednesday 02 March 2011] [14:41:25] <guido_g>	ahhh.. great!
| [Wednesday 02 March 2011] [14:41:33] <guido_g>	multicast is back
| [Wednesday 02 March 2011] [14:41:37] <pieterh>	excellent!
| [Wednesday 02 March 2011] [14:42:08] <private_meta>	 hmm... "Developing a port was quite difficult as it took us guile long to port all the bugs correctly"
| [Wednesday 02 March 2011] [14:42:24] <private_meta>	 -guilt + quite
| [Wednesday 02 March 2011] [15:30:00] <guido_g>	pieterh: care to explain wich application would need a 10ms heartbeat?
| [Wednesday 02 March 2011] [15:30:13] <pieterh>	anything far away
| [Wednesday 02 March 2011] [15:30:15] <guido_g>	just reading ch4 of the guide
| [Wednesday 02 March 2011] [15:30:23] <pieterh>	it's strictly dependent on network architecture
| [Wednesday 02 March 2011] [15:30:27] <pieterh>	sorry!
| [Wednesday 02 March 2011] [15:30:39] <pieterh>	:) I read "would need more than 10ms"
| [Wednesday 02 March 2011] [15:30:49] <guido_g>	ok
| [Wednesday 02 March 2011] [15:30:49] <pieterh>	anything really close and extremely low latency
| [Wednesday 02 March 2011] [15:31:01] <guido_g>	but...
| [Wednesday 02 March 2011] [15:31:11] Notice	-NickServ- This nickname is registered. Please choose a different nickname, or identify via /msg NickServ identify <password>.
| [Wednesday 02 March 2011] [15:31:14] <guido_g>	heratbeat is going over the same socket as the data
| [Wednesday 02 March 2011] [15:31:17] <pieterh>	if you're getting 1M messages a second and suddenly there's silence for 10msec... that's serious
| [Wednesday 02 March 2011] [15:31:28] <guido_g>	ack
| [Wednesday 02 March 2011] [15:31:32] <pieterh>	you want to know after maybe 1msec
| [Wednesday 02 March 2011] [15:31:36] <pieterh>	and then switch to a backup
| [Wednesday 02 March 2011] [15:31:43] <guido_g>	but you don't send heartbeats when sending data
| [Wednesday 02 March 2011] [15:31:50] <pieterh>	precisely
| [Wednesday 02 March 2011] [15:32:13] <guido_g>	so a received data packet counts as "alive"
| [Wednesday 02 March 2011] [15:32:24] <pieterh>	to do this optimally, you create a slope
| [Wednesday 02 March 2011] [15:32:31] <guido_g>	ack
| [Wednesday 02 March 2011] [15:32:41] <pieterh>	so heartbeat immediately as data stops, then double the time until it's infinite
| [Wednesday 02 March 2011] [15:32:52] <guido_g>	done this in prototype of a rmc protocol
| [Wednesday 02 March 2011] [15:32:55] <pieterh>	but that's a lot of work for an example and overkill for 99% of cases
| [Wednesday 02 March 2011] [15:33:09] <guido_g>	sure
| [Wednesday 02 March 2011] [15:33:36] <pieterh>	I'd suspect the minimum sane heartbeating is around 1msec for low latency apps
| [Wednesday 02 March 2011] [15:33:45] <pieterh>	that's a typical SLA
| [Wednesday 02 March 2011] [15:33:58] <guido_g>	ok
| [Wednesday 02 March 2011] [15:34:28] 	 * pieterh is really liking the zmsg.class style
| [Wednesday 02 March 2011] [15:34:37] <pieterh>	C99 just became C2011
| [Wednesday 02 March 2011] [15:34:48] <guido_g>	but still the sender should only send a marker (heartbeat) when there is no data to send
| [Wednesday 02 March 2011] [15:35:22] <guido_g>	should go into spec7, somnehow
| [Wednesday 02 March 2011] [15:35:28] <guido_g>	*somehow
| [Wednesday 02 March 2011] [15:35:57] <mikko>	hello
| [Wednesday 02 March 2011] [15:36:35] <guido_g>	hiho
| [Wednesday 02 March 2011] [15:38:41] <pieterh>	guido_g: indeed, thanks
| [Wednesday 02 March 2011] [15:39:03] <guido_g>	its a nice read, btw
| [Wednesday 02 March 2011] [15:39:26] <mikko>	i've been at a customer lately and no irc during the day
| [Wednesday 02 March 2011] [15:39:40] <guido_g>	overall i like the idea of sketching these things in this semi-formal form
| [Wednesday 02 March 2011] [15:40:16] <pieterh>	guido_g: it makes life surprisingly easy
| [Wednesday 02 March 2011] [15:40:27] <pieterh>	sketch the protocol, implement it
| [Wednesday 02 March 2011] [15:41:00] <guido_g>	no, not w/ six bytes for the protocol version ,)
| [Wednesday 02 March 2011] [15:41:29] <pieterh>	what do you mean?
| [Wednesday 02 March 2011] [15:41:45] <guido_g>	"Frame 0: "MDPW01" (six bytes, representing MDP/Worker v0.1)" <- that
| [Wednesday 02 March 2011] [15:42:07] <guido_g>	it's even in the heartbeat
| [Wednesday 02 March 2011] [15:42:27] <pieterh>	yes
| [Wednesday 02 March 2011] [15:42:32] <pieterh>	there's a good reason for that
| [Wednesday 02 March 2011] [15:42:43] <guido_g>	i mean, we're talking about the machine where 1byte messages are use for benchmarks, right?
| [Wednesday 02 March 2011] [15:42:50] <pieterh>	I want to make brokers that can handle any mix of protocols over a single socket
| [Wednesday 02 March 2011] [15:43:01] <pieterh>	request-reply is *not* performance sensitive
| [Wednesday 02 March 2011] [15:43:25] <pieterh>	at least not at the 6M msg/second level
| [Wednesday 02 March 2011] [15:43:36] <guido_g>	depend on the amount of packets send on the segment, right?
| [Wednesday 02 March 2011] [15:43:51] <pieterh>	use cases are key
| [Wednesday 02 March 2011] [15:44:01] <pieterh>	data distribution -> millions / second, microsecond latency
| [Wednesday 02 March 2011] [15:44:15] <pieterh>	task distribution -> thousands / second, millisecond latency
| [Wednesday 02 March 2011] [15:44:21] <guido_g>	sure
| [Wednesday 02 March 2011] [15:44:45] <guido_g>	but still, 6 bytes for a protocol version?
| [Wednesday 02 March 2011] [15:45:17] <pieterh>	didn't hurt HTTP
| [Wednesday 02 March 2011] [15:45:31] <pieterh>	it should be printable, unique, and include a version number
| [Wednesday 02 March 2011] [15:45:39] <pieterh>	'M' is not a protocol name
| [Wednesday 02 March 2011] [15:45:47] <guido_g>	ah
| [Wednesday 02 March 2011] [15:45:59] <pieterh>	seriously, this is not worth optimizing, not even marginally
| [Wednesday 02 March 2011] [15:46:02] <guido_g>	so the command doesn't need to be printable then?
| [Wednesday 02 March 2011] [15:46:09] <pieterh>	the payload is opaque binary
| [Wednesday 02 March 2011] [15:46:19] <pieterh>	the command... good suggestion
| [Wednesday 02 March 2011] [15:46:31] <pieterh>	nope
| [Wednesday 02 March 2011] [15:46:37] <pieterh>	identities aren't either
| [Wednesday 02 March 2011] [15:46:44] <guido_g>	i'd say 2 bytes for proto version would be more then enough
| [Wednesday 02 March 2011] [15:47:03] <guido_g>	how many incarnations could one expect?
| [Wednesday 02 March 2011] [15:47:13] <pieterh>	it is two bytes for proto version...
| [Wednesday 02 March 2011] [15:47:19] <pieterh>	MDPSxx
| [Wednesday 02 March 2011] [15:47:33] <guido_g>	*sigh*
| [Wednesday 02 March 2011] [15:47:47] <pieterh>	proto name = 3 chars, proto subname = 1 char, proto version = 2 chars
| [Wednesday 02 March 2011] [15:47:49] <Guthur>	pieterh, do you have a timeframe on when you hope to finished Ch4?
| [Wednesday 02 March 2011] [15:48:05] <pieterh>	Guthur: depends how long guido_g keeps nagging about these six bytes...
| [Wednesday 02 March 2011] [15:48:11] <Guthur>	hehe
| [Wednesday 02 March 2011] [15:48:14] <pieterh>	:-)
| [Wednesday 02 March 2011] [15:48:26] <guido_g>	pfff...
| [Wednesday 02 March 2011] [15:48:27] <cremes>	guido_g: i mentioned the same thing when i reviewed an earlier version of the rfc
| [Wednesday 02 March 2011] [15:48:28] <guido_g>	,)
| [Wednesday 02 March 2011] [15:48:39] <cremes>	guido_g: i agree though that it isn't worth arguing about
| [Wednesday 02 March 2011] [15:48:48] <guido_g>	sure
| [Wednesday 02 March 2011] [15:49:12] <pieterh>	look...
| [Wednesday 02 March 2011] [15:49:21] <pieterh>	the mdbroker opens a single socket for both clients and workers
| [Wednesday 02 March 2011] [15:49:29] <guido_g>	ack
| [Wednesday 02 March 2011] [15:49:33] <pieterh>	that is much easier for admin than two endpoints
| [Wednesday 02 March 2011] [15:49:41] <guido_g>	agreed
| [Wednesday 02 March 2011] [15:49:42] <pieterh>	i want to write a couple more protocols
| [Wednesday 02 March 2011] [15:49:48] <pieterh>	there'll be one for persistence (to disk)
| [Wednesday 02 March 2011] [15:49:52] <guido_g>	dozens?
| [Wednesday 02 March 2011] [15:49:56] <guido_g>	hunderts?
| [Wednesday 02 March 2011] [15:49:57] <pieterh>	nope, a few
| [Wednesday 02 March 2011] [15:50:02] <pieterh>	but that's just me
| [Wednesday 02 March 2011] [15:50:17] <pieterh>	i assume there will be variations on MDP
| [Wednesday 02 March 2011] [15:50:26] <pieterh>	not versions but variations
| [Wednesday 02 March 2011] [15:50:27] <guido_g>	we do have the message-parts
| [Wednesday 02 March 2011] [15:50:35] <guido_g>	so lets start small
| [Wednesday 02 March 2011] [15:50:37] <pieterh>	say you want to experiment with a new command
| [Wednesday 02 March 2011] [15:50:40] <guido_g>	like ip 
| [Wednesday 02 March 2011] [15:51:03] <pieterh>	you can fork spec:7 and create a new spec:8
| [Wednesday 02 March 2011] [15:51:10] <pieterh>	but you will choose a new name
| [Wednesday 02 March 2011] [15:51:13] <guido_g>	would be more 7.1 :)
| [Wednesday 02 March 2011] [15:51:22] <pieterh>	so yes, there can be dozens or hundreds of protocols
| [Wednesday 02 March 2011] [15:51:33] <pieterh>	nope, not 7.1, read COSS if you care
| [Wednesday 02 March 2011] [15:51:41] <guido_g>	yes, the guttenberg-protocol
| [Wednesday 02 March 2011] [15:51:42] <pieterh>	each spec is independent, has its own editor, is forkable
| [Wednesday 02 March 2011] [15:51:48] <guido_g>	because it's mostly copied
| [Wednesday 02 March 2011] [15:52:18] <pieterh>	why do I get link errors on 0MQ of the style crti.o: No such file or directory
| [Wednesday 02 March 2011] [15:52:23] <pieterh>	(new Ubuntu install)
| [Wednesday 02 March 2011] [15:53:07] <guido_g>	compile and link use different versions?
| [Wednesday 02 March 2011] [15:53:29] <pieterh>	could be
| [Wednesday 02 March 2011] [15:53:45] <guido_g>	or some packages not properly installed
| [Wednesday 02 March 2011] [15:54:05] <pieterh>	I just swapped my notebook HDD for an SSD, copied a bunch of stuff across
| [Wednesday 02 March 2011] [15:54:12] <pieterh>	so probably mix of old/new code
| [Wednesday 02 March 2011] [15:54:20] <pieterh>	np
| [Wednesday 02 March 2011] [15:54:35] <pieterh>	look, if you don't like the 6-byte header, you fork MDP and create your own new spec
| [Wednesday 02 March 2011] [15:54:40] <guido_g>	or you didn't install c++ properly (and/or in the correct version)
| [Wednesday 02 March 2011] [15:54:53] <pieterh>	(that is, if I don't accept your suggestions)
| [Wednesday 02 March 2011] [15:54:59] <guido_g>	no, not for this one change
| [Wednesday 02 March 2011] [15:55:36] <pieterh>	it could be improved by adding a more formal start-up handshake
| [Wednesday 02 March 2011] [15:55:37] <guido_g>	btw, ssd in laptop rocks :)
| [Wednesday 02 March 2011] [15:55:54] <pieterh>	yeah, unbreakable...
| [Wednesday 02 March 2011] [15:55:56] <guido_g>	or smaller headers and the possibility for extensions
| [Wednesday 02 March 2011] [15:56:12] <guido_g>	like the ip header extensions
| [Wednesday 02 March 2011] [15:56:15] <pieterh>	bleh... it's a draft protocol, it has to be _simple_ above all
| [Wednesday 02 March 2011] [15:56:23] <guido_g>	sure
| [Wednesday 02 March 2011] [15:56:31] <pieterh>	it is counter-productive to optimize a draft, pathological even
| [Wednesday 02 March 2011] [15:56:53] <guido_g>	but talking (and sometimes even thinking) about it helps
| [Wednesday 02 March 2011] [15:57:09] <pieterh>	clients and workers would have to 'sign in' and specify a protocol
| [Wednesday 02 March 2011] [15:57:28] <guido_g>	or more then one
| [Wednesday 02 March 2011] [15:57:30] <pieterh>	then every message would first require a lookup to determine, "ah, this peer is using protocol XYZ"
| [Wednesday 02 March 2011] [15:57:45] <pieterh>	and then you could remove the protocol header from every command except the first
| [Wednesday 02 March 2011] [15:57:58] <pieterh>	you'd save 6 bytes on requests of 1K and responses of 20K
| [Wednesday 02 March 2011] [15:58:01] <pieterh>	the world would rejoice
| [Wednesday 02 March 2011] [15:58:06] <guido_g>	if workers stick to one protocol yes
| [Wednesday 02 March 2011] [15:58:17] <pieterh>	and every single implementor would get that handshake wrong at least once
| [Wednesday 02 March 2011] [15:58:45] <guido_g>	this is one of those assuptions i generally don't like
| [Wednesday 02 March 2011] [15:59:02] <pieterh>	so spec:7 makes as few assumptions as it can
| [Wednesday 02 March 2011] [15:59:08] <guido_g>	they lead to a "cover foreign asses" mentality
| [Wednesday 02 March 2011] [15:59:41] <pieterh>	i'm not sure we have a good pattern for a connected dialog, yet
| [Wednesday 02 March 2011] [15:59:57] <pieterh>	when we do, this will become much easier
| [Wednesday 02 March 2011] [16:02:25] <guido_g>	i think spec:7 is a nice starting point
| [Wednesday 02 March 2011] [16:02:42] <guido_g>	i'll try to implemnt it w/ pyzmq
| [Wednesday 02 March 2011] [16:03:28] <pieterh>	guido_g: if you take the chapter4-wip branch, there are already working client & worker APIs in mdcliapi and mdwrkapi
| [Wednesday 02 March 2011] [16:03:50] <pieterh>	they expose simple classes to applications
| [Wednesday 02 March 2011] [16:04:04] 	 * pieterh has to go rename them to .class as well... lol
| [Wednesday 02 March 2011] [16:04:14] <guido_g>	uhhh
| [Wednesday 02 March 2011] [16:04:32] <mikko>	pieterh: so you are coming on 16th?
| [Wednesday 02 March 2011] [16:04:33] <guido_g>	pyzmq makes this even more simple
| [Wednesday 02 March 2011] [16:04:39] <pieterh>	mikko: yes
| [Wednesday 02 March 2011] [16:04:45] <pieterh>	guido_g: how so?
| [Wednesday 02 March 2011] [16:04:59] <pieterh>	mikko: I'll be there earlier
| [Wednesday 02 March 2011] [16:05:45] <guido_g>	it has a eventloop built in, including timers etc.  http://zeromq.github.com/pyzmq/eventloop.html
| [Wednesday 02 March 2011] [16:06:22] <mikko>	pieterh: how much earlier?
| [Wednesday 02 March 2011] [16:06:32] <mikko>	pieterh: i work very close to oxford circus
| [Wednesday 02 March 2011] [16:06:48] <pieterh>	mikko: I can be there (in London) at lunchtime
| [Wednesday 02 March 2011] [16:07:02] <pieterh>	might meet some other people for lunch, or before
| [Wednesday 02 March 2011] [16:07:04] <mikko>	pieterh: are you having any meetings during the day?
| [Wednesday 02 March 2011] [16:07:10] <pieterh>	you want to catch up?
| [Wednesday 02 March 2011] [16:07:21] <pieterh>	happy to come and evangelize 0MQ
| [Wednesday 02 March 2011] [16:07:54] <pieterh>	guido_g: the complete worker API, in C, is 200 lines of code
| [Wednesday 02 March 2011] [16:07:56] <mikko>	maybe, not sure about my schedule yet
| [Wednesday 02 March 2011] [16:08:38] <guido_g>	pieterh: http://zeromq.github.com/pyzmq/api/generated/zmq.eventloop.zmqstream.html  <- less then 50 lines w/ this
| [Wednesday 02 March 2011] [16:08:41] <pieterh>	guido_g: of which maybe 30 lines is the central poll loop & timers
| [Wednesday 02 March 2011] [16:10:07] <pieterh>	guido_g: yes, I'm sure it can be even less than 200 lines, maybe 180 or 174, but that's not fair to readers who are learning 0MQ core, rather than language-specific frameworks
| [Wednesday 02 March 2011] [16:10:14] <mikko>	pieterh: but it would be nice to catch up
| [Wednesday 02 March 2011] [16:10:33] <pieterh>	mikko: I'll keep some time free in the afternoon, no problem
| [Wednesday 02 March 2011] [16:10:35] <mikko>	i can ask if devs at the company are interested in hearing about zeromq
| [Wednesday 02 March 2011] [16:10:39] <mikko>	from horse's mouth
| [Wednesday 02 March 2011] [16:10:55] <pieterh>	:-) 
| [Wednesday 02 March 2011] [16:11:03] <mikko>	some of them saw ianbarber last friday
| [Wednesday 02 March 2011] [16:11:13] <guido_g>	pieterh: agreed, but we'll see more bindings with additional functionality i assume
| [Wednesday 02 March 2011] [16:11:31] <pieterh>	guido_g: any useful pattern should be documented in a language neutral form
| [Wednesday 02 March 2011] [16:11:32] <guido_g>	anyway, i'm much more a python than a c programmer nowadays
| [Wednesday 02 March 2011] [16:11:37] <pieterh>	otherwise it's just fragmentation
| [Wednesday 02 March 2011] [16:11:44] <pieterh>	the language is not relevant, barely
| [Wednesday 02 March 2011] [16:11:46] <guido_g>	pieterh: ack, i was going for an implementation
| [Wednesday 02 March 2011] [16:11:51] <guido_g>	the spec:7 is fine
| [Wednesday 02 March 2011] [16:12:01] <pieterh>	guido_g: yeah, but it's a shame to not first translate the guide examples
| [Wednesday 02 March 2011] [16:12:18] <pieterh>	if you Pythonistos can hit 100%, you achieve an ianbarbarism
| [Wednesday 02 March 2011] [16:12:29] <pieterh>	that is, you get a Guide in Python
| [Wednesday 02 March 2011] [16:12:52] <pieterh>	but I guess it's too difficult... :-/ Python has a reputation as harder to use than PHP or C
| [Wednesday 02 March 2011] [16:13:24] <guido_g>	i can't avoid the feeling that some wants to talk me into doing something... but i can't put a finger on it...
| [Wednesday 02 March 2011] [16:13:41] <Guthur>	i really should finish ch3 for clrzmq2
| [Wednesday 02 March 2011] [16:13:52] <pieterh>	no, in fact I formally forbid you from even thinking about it...!
| [Wednesday 02 March 2011] [16:13:57] <Guthur>	I got lazy
| [Wednesday 02 March 2011] [16:14:16] <pieterh>	Guthur: guido_g: race on... C# vs Python! who will be first to get their own Guide???
| [Wednesday 02 March 2011] [16:14:24] <pieterh>	my money is on Perl, to be honest
| [Wednesday 02 March 2011] [16:14:28] <Guthur>	pieterh, you like your reverse physiology
| [Wednesday 02 March 2011] [16:14:33] <Guthur>	hehe
| [Wednesday 02 March 2011] [16:14:37] <mikko>	PHP won ?
| [Wednesday 02 March 2011] [16:14:47] <guido_g>	he has to train it, he has kids :)
| [Wednesday 02 March 2011] [16:14:54] <pieterh>	yup, mikko, Ian Barber won...
| [Wednesday 02 March 2011] [16:15:16] <pieterh>	http://zguide.zeromq.org/php:all
| [Wednesday 02 March 2011] [16:15:19] <Guthur>	my c# examples wouldn't really qualify, I had using blocks to avoid explicit disposal 
| [Wednesday 02 March 2011] [16:15:34] <pieterh>	to be honest, it's pretty cool to see the examples in random other languages
| [Wednesday 02 March 2011] [16:15:47] <Guthur>	and other sugar
| [Wednesday 02 March 2011] [16:16:46] <pieterh>	Guthur: if the sugar makes it easier to write, use it
| [Wednesday 02 March 2011] [16:17:15] <pieterh>	after all, it's about teaching developers in language X how best to use the 0MQ binding/API
| [Wednesday 02 March 2011] [16:17:15] <Guthur>	yeah things like returning and accepting strings, instead of byte arrays
| [Wednesday 02 March 2011] [16:18:00] <Guthur>	even if it can't get its own guide it would be good experience for me with 0MQ
| [Wednesday 02 March 2011] [16:18:16] <Guthur>	the more the better I think, hehe
| [Wednesday 02 March 2011] [16:18:55] <pieterh>	One day, when Google human resources conduct their 10-minute screenings they will ask, "how would you rate your 0MQ knowledge, 0 to 10?"
| [Wednesday 02 March 2011] [16:19:25] <mikko>	haha
| [Wednesday 02 March 2011] [16:19:27] <guido_g>	who cares  ]:->
| [Wednesday 02 March 2011] [16:20:33] <guido_g>	there are already a lot of python examples
| [Wednesday 02 March 2011] [16:20:58] <pieterh>	guido_g: yes, only a few left, your chance for eternal fame is slipping away fast
| [Wednesday 02 March 2011] [16:22:48] <Guthur>	hehe, it's sad but I actually liked seeing my name at the top of the guide
| [Wednesday 02 March 2011] [16:22:58] <Guthur>	my one bit of programming fame
| [Wednesday 02 March 2011] [16:23:27] <pieterh>	To be honest, being named as contributor to a successful open source project is better than a good CV
| [Wednesday 02 March 2011] [16:23:52] <guido_g>	depends on where you want to apply
| [Wednesday 02 March 2011] [16:23:57] <pieterh>	precisely
| [Wednesday 02 March 2011] [16:24:22] <guido_g>	my last gig was at a bank...
| [Wednesday 02 March 2011] [16:24:29] <pieterh>	i mean, any firm that does not google you and check you on github is going to be painful to work for
| [Wednesday 02 March 2011] [16:24:54] <guido_g>	makes approx. 99.99% of all companies :)
| [Wednesday 02 March 2011] [16:25:32] <guido_g>	and the others... well there not that much of them
| [Wednesday 02 March 2011] [16:25:41] <Guthur>	guido_g, Did you find that banks don't dig work on OSS 
| [Wednesday 02 March 2011] [16:25:44] <pieterh>	the thing that eventually caused 0MQ started 6 years ago because someone was once impressed by the C library I wrote
| [Wednesday 02 March 2011] [16:25:53] <pieterh>	and it was a bank
| [Wednesday 02 March 2011] [16:26:25] <guido_g>	sure, there might be exceptions
| [Wednesday 02 March 2011] [16:26:46] <pieterh>	ok, I have a messaging broker to write before the sun rises or the vampires will get me
| [Wednesday 02 March 2011] [16:26:47] <pieterh>	cyal
| [Wednesday 02 March 2011] [16:26:57] <guido_g>	Guthur: dig work on? sorry, don't understand that
| [Wednesday 02 March 2011] [16:27:16] <guido_g>	pieterh: cu
| [Wednesday 02 March 2011] [16:27:28] <pieterh>	guido_g: ciao
| [Wednesday 02 March 2011] [16:28:37] <Guthur>	guido_g, rate approvingly
| [Wednesday 02 March 2011] [16:29:52] <guido_g>	i've been lucky, the bank i worked for used python, this is why i got the job
| [Wednesday 02 March 2011] [16:30:03] <guido_g>	but they didn't know about oss in general
| [Wednesday 02 March 2011] [16:30:39] <guido_g>	and now, neither the bank nor the headhunters did check my (non-existant) oss track record
| [Wednesday 02 March 2011] [16:31:01] <Guthur>	did you mention standout projects in your CV?
| [Wednesday 02 March 2011] [16:31:46] <guido_g>	i mostly worked w/ oss software in the last 12 years, so lots of names in my cv
| [Wednesday 02 March 2011] [16:32:18] <guido_g>	but they don't know even postgresql 
| [Wednesday 02 March 2011] [16:32:35] <guido_g>	totaly closed shop (and minds)
| [Wednesday 02 March 2011] [16:33:49] <Guthur>	yeah that can be quite prevalent in corporate culture
| [Wednesday 02 March 2011] [16:34:27] <guido_g>	http://site.despair.com/images/dpage/consulting03.jpg  <- true :)
| [Wednesday 02 March 2011] [16:40:01] <dijix>	guido_g: sounds like my .NET shop..  I can't even carry on a conversation with most of them - they haven't even heard of things like Python.. and most assuredly, not ZeroMQ..
| [Wednesday 02 March 2011] [16:40:22] <guido_g>	dijix: not even that
| [Wednesday 02 March 2011] [16:41:16] <guido_g>	they run programs, that's it
| [Wednesday 02 March 2011] [16:41:39] <guido_g>	they do have 2 or 3 people w/ some technical know-how
| [Wednesday 02 March 2011] [16:42:21] <guido_g>	but given the fact that of the most important pieces of software there is still written in cobol...
| [Wednesday 02 March 2011] [16:42:36] <eyecue>	*yawn*
| [Wednesday 02 March 2011] [16:42:37] <eyecue>	morning
| [Wednesday 02 March 2011] [16:42:39] <guido_g>	my python gig there was ok
| [Wednesday 02 March 2011] [16:43:09] <guido_g>	howdy
| [Wednesday 02 March 2011] [16:43:16] <eyecue>	:)
| [Wednesday 02 March 2011] [16:43:43] <eyecue>	0mq kinda blew me away last night, i got home at 6:30 after work, and before i knew it had been reading for a good 5 hours
| [Wednesday 02 March 2011] [16:44:16] <guido_g>	i'd treat that as a good start
| [Wednesday 02 March 2011] [16:44:28] <eyecue>	yeh :)
| [Wednesday 02 March 2011] [16:54:40] <cremes>	anyone know why i would get errno=2 and error_string "No such file or directory" when trying to connect using inproc?
| [Wednesday 02 March 2011] [16:57:40] <sustrik>	strange
| [Wednesday 02 March 2011] [16:57:47] <sustrik>	do you have SWAP set?
| [Wednesday 02 March 2011] [16:59:53] <cremes>	no
| [Wednesday 02 March 2011] [17:00:13] <cremes>	will it report that error if i bind/connect two sockets within the same context?
| [Wednesday 02 March 2011] [17:00:34] <cremes>	btw, syntax is: "inproc://some_name" right?
| [Wednesday 02 March 2011] [17:02:03] <sustrik>	right
| [Wednesday 02 March 2011] [17:02:16] <sustrik>	the errno looks to be bogus
| [Wednesday 02 March 2011] [17:02:20] <sustrik>	is it reproducible?
| [Wednesday 02 March 2011] [17:02:41] <cremes>	it might be a problem with my binding... investigating <sigh>
| [Wednesday 02 March 2011] [17:03:36] <sustrik>	cremes: win32?
| [Wednesday 02 March 2011] [17:04:00] <cremes>	no, linux
| [Wednesday 02 March 2011] [17:04:06] <sustrik>	hm
| [Wednesday 02 March 2011] [17:04:14] <sustrik>	no idea then
| [Wednesday 02 March 2011] [17:06:01] <cremes>	now i'm getting:  errno [111], error_string [Connection refused]
| [Wednesday 02 March 2011] [17:18:36] <Guthur>	cremes, which binding is that out of interest
| [Wednesday 02 March 2011] [17:19:13] <cremes>	ruby
| [Wednesday 02 March 2011] [17:19:38] <cremes>	looks like it isn't a binding bug... 0mq throws that error if you try to zmq_connect() an inproc before yu zmq_bind() it
| [Wednesday 02 March 2011] [17:20:57] <guido_g>	ahhh
| [Wednesday 02 March 2011] [17:26:27] <mikko>	cremes: thats a known limitation
| [Wednesday 02 March 2011] [17:27:03] <cremes>	mikko: yeah, but i thought it failed silently 
| [Wednesday 02 March 2011] [17:27:19] <cremes>	it now returns -1.... which is new to 2.1.1 i think
| [Wednesday 02 March 2011] [17:29:25] <guido_g>	effect of an assert that got removed?
| [Wednesday 02 March 2011] [17:37:40] <guido_g>	oh late already, night all!
| [Wednesday 02 March 2011] [17:42:25] <pieterh>	cremes: afaik it always returned a -1
| [Wednesday 02 March 2011] [18:20:25] <JoderCoder>	Hi everyone, I am trying to write some IPC code that can pass data between 2 processes on a single machine. Am I at right place? :)
| [Wednesday 02 March 2011] [18:24:44] <Guthur>	JoderCoder, You can certainly use ZeroMQ to do IPC
| [Wednesday 02 March 2011] [18:24:55] <Guthur>	what platform?
| [Wednesday 02 March 2011] [18:28:16] <JoderCoder>	Guthur, Linux initially, then Windows..
| [Wednesday 02 March 2011] [18:29:19] <JoderCoder>	http://lists.zeromq.org/pipermail/zeromq-dev/2011-March/009637.html
| [Wednesday 02 March 2011] [18:29:25] <Guthur>	you can use IPC transport on Linux but on Windows you would need to use TCP
| [Wednesday 02 March 2011] [18:29:33] <JoderCoder>	this is the mail I sent to the forum
| [Wednesday 02 March 2011] [18:29:45] <Guthur>	IPC via named pipes on windows is not yet available
| [Wednesday 02 March 2011] [18:29:58] <JoderCoder>	yes, I came across with that note on the docs somewhere
| [Wednesday 02 March 2011] [18:30:09] <JoderCoder>	Linux is my priority anyways..
| [Wednesday 02 March 2011] [18:30:59] <JoderCoder>	is there any sample code available somewhere that I could re-use?
| [Wednesday 02 March 2011] [18:31:09] <Guthur>	the guide is a code place to start
| [Wednesday 02 March 2011] [18:31:10] <pieterh>	JoderCoder: have you read the Guide?
| [Wednesday 02 March 2011] [18:31:30] <Guthur>	code/good
| [Wednesday 02 March 2011] [18:31:46] <Guthur>	hehe, too much coding in the brain
| [Wednesday 02 March 2011] [18:32:29] <JoderCoder>	pieterh, I did read it, to some extend. Firstly, I am not sure what pattern to use.
| [Wednesday 02 March 2011] [18:32:49] <pieterh>	JoderCoder: read it again, until it makes sense
| [Wednesday 02 March 2011] [18:32:50] <JoderCoder>	I was recommended to use Router-to-Router
| [Wednesday 02 March 2011] [18:33:02] <pieterh>	this would be your first 0MQ program?
| [Wednesday 02 March 2011] [18:33:12] <JoderCoder>	yes
| [Wednesday 02 March 2011] [18:33:20] <pieterh>	so please start at Ch1 not Ch3
| [Wednesday 02 March 2011] [18:33:27] <pieterh>	do take the time to learn this properly
| [Wednesday 02 March 2011] [18:33:39] <pieterh>	otherwise you're going to get lost
| [Wednesday 02 March 2011] [18:33:52] <pieterh>	walk, then run
| [Wednesday 02 March 2011] [18:33:57] <JoderCoder>	:-)
| [Wednesday 02 March 2011] [18:36:03] <JoderCoder>	well, I guess I am not the first one, but under some pressure due to the tight schedule.. but you're right.. I will read it tomorrow.
| [Wednesday 02 March 2011] [18:36:29] <pieterh>	if you want to save time, hire someone who already knows the technology well
| [Wednesday 02 March 2011] [18:36:51] <JoderCoder>	:-)
| [Wednesday 02 March 2011] [18:36:56] <pieterh>	but jumping into deep water before you can swim will really not save you time
| [Wednesday 02 March 2011] [18:37:18] <pieterh>	it's about 2-3 days to learn the basics and feel them 'click' in your mind
| [Wednesday 02 March 2011] [18:37:33] <pieterh>	you will save that easily on the first app you make properly
| [Wednesday 02 March 2011] [18:37:43] <Guthur>	JoderCoder, what language are you going to use, out of interest
| [Wednesday 02 March 2011] [18:37:43] <JoderCoder>	I will replace my current Sys V MQ with ZMQ since we plan to use it as a MQ across network 
| [Wednesday 02 March 2011] [18:37:51] <JoderCoder>	c++
| [Wednesday 02 March 2011] [18:40:21] <JoderCoder>	OK guys, thanks for your time.. I'll get to it tomorrow morning. g'night
| [Wednesday 02 March 2011] [18:40:34] <pieterh>	JoderCoder: cyat
| [Wednesday 02 March 2011] [18:40:54] <Guthur>	night JoderCoder 
| [Wednesday 02 March 2011] [18:40:59] <Guthur>	it's worth reading the guide
| [Wednesday 02 March 2011] [18:41:05] <Guthur>	lots of idea
| [Wednesday 02 March 2011] [18:41:08] <Guthur>	ideas*
| [Wednesday 02 March 2011] [18:41:36] <JoderCoder>	ok danke schon
| [Wednesday 02 March 2011] [18:42:00] <Guthur>	your welcome, i must sleep now too
| [Wednesday 02 March 2011] [18:56:20] <jugg>	yrashk, pieterh:  The only reason the csrl/erlzmq fork exists is because the zeromq/erlzmq bindings are incomplete/broken.  I'd love to use yrashk/ezmq, but my application runs on R13B04 which can't run ezmq (requires R14).  When I have time to move to R14, I'll most likely move to ezmq.
| [Wednesday 02 March 2011] [18:56:30] <jugg>	yrashk, nice perf results.
| [Wednesday 02 March 2011] [18:56:56] <pieterh>	jugg: makes sense, I'd advise you to agree on one name and two version numbers, for your users' sanity
| [Wednesday 02 March 2011] [20:16:46] <cremes>	ha, figured out why my zmq_connect() calls were returning an error
| [Wednesday 02 March 2011] [20:17:03] <cremes>	i was trying to connect two sockets in *different* contexts via inproc
| [Wednesday 02 March 2011] [20:17:11] <cremes>	that doesn't work :)
| [Wednesday 02 March 2011] [21:58:18] <cremes>	i'm digging this inproc transport
| [Wednesday 02 March 2011] [21:58:48] <cremes>	it reduces latency by at least 30%... me likey
| [Wednesday 02 March 2011] [22:07:59] <Steve-o>	just need a Windows version
| [Thursday 03 March 2011] [01:51:31] <Steve-o>	mikko: pingu
| [Thursday 03 March 2011] [01:58:36] <Steve-o>	mikko: ready for bumping zeromq with autoconf of openpgm
| [Thursday 03 March 2011] [02:44:09] <guido_g>	mornig all
| [Thursday 03 March 2011] [02:44:19] <pieterh>	guido_g: g'morning
| [Thursday 03 March 2011] [02:44:27] <guido_g>	hi pieterh 
| [Thursday 03 March 2011] [02:44:51] <guido_g>	just saw that you've been busy 
| [Thursday 03 March 2011] [02:46:35] <guido_g>	will have a look at the mdp broker later
| [Thursday 03 March 2011] [02:48:13] <pieterh>	it does everything but leaks a little memory, and is slow
| [Thursday 03 March 2011] [02:50:05] <guido_g>	"The biggest improvement in performance is the non-working-to-working
| [Thursday 03 March 2011] [02:50:05] <guido_g>	transition."
| [Thursday 03 March 2011] [02:50:05] <guido_g>	   -- John Ousterhout
| [Thursday 03 March 2011] [02:50:42] <pieterh>	what's nice is how it all handles when you stop/restart pieces
| [Thursday 03 March 2011] [02:51:24] <guido_g>	will use it as counterpart for my python mdp implementation
| [Thursday 03 March 2011] [02:52:40] <pieterh>	I'd start by implementing the client and worker APIs
| [Thursday 03 March 2011] [02:52:49] <pieterh>	you can then test against the existing broker
| [Thursday 03 March 2011] [02:53:03] <guido_g>	that was the idea
| [Thursday 03 March 2011] [02:53:12] <guido_g>	i'm on the client atm
| [Thursday 03 March 2011] [02:53:15] <pieterh>	I'm keen to see what you come up with
| [Thursday 03 March 2011] [02:53:27] <pieterh>	mdp will also solve the problem of reliable pipelines
| [Thursday 03 March 2011] [02:54:04] <pieterh>	today I profile to see where the CPU time is going
| [Thursday 03 March 2011] [02:54:13] <pieterh>	I suspect too much envelope stuffing
| [Thursday 03 March 2011] [02:54:24] <guido_g>	my idea is not to write another mdp example, but a lib that can be used for apps
| [Thursday 03 March 2011] [02:54:37] <pieterh>	this is what the two APIs are meant to be
| [Thursday 03 March 2011] [02:55:07] <guido_g>	so i figured that right at least :)
| [Thursday 03 March 2011] [02:55:44] <pieterh>	so an actual client looks like: https://github.com/imatix/zguide/blob/chapter4-wip/examples/C/mdclient.c
| [Thursday 03 March 2011] [02:55:57] <pieterh>	and the worker: https://github.com/imatix/zguide/blob/chapter4-wip/examples/C/mdworker.c
| [Thursday 03 March 2011] [02:56:14] <guido_g>	sweet
| [Thursday 03 March 2011] [02:56:33] <pieterh>	yeah, I think so too... :-)
| [Thursday 03 March 2011] [02:56:50] <guido_g>	no really
| [Thursday 03 March 2011] [02:56:50] <pieterh>	especially since it's like 3-4 days' total work so far from concept to running code
| [Thursday 03 March 2011] [02:57:10] <guido_g>	as one who is not used to c anymore, this is very easy to read
| [Thursday 03 March 2011] [02:57:27] <pieterh>	well, it's not about the language, just the semantics you implement
| [Thursday 03 March 2011] [02:57:51] <pieterh>	the class-based C style we developed at iMatix is pleasant to work with
| [Thursday 03 March 2011] [02:58:30] <pieterh>	i'm curious to see how that maps into Python
| [Thursday 03 March 2011] [02:58:34] <guido_g>	sure, but you need to know a language quite well to come up w/ a good api for something
| [Thursday 03 March 2011] [02:58:43] <pieterh>	indeed
| [Thursday 03 March 2011] [03:13:13] <yrashk>	I forgot this again -- in the latest 0mq can you or can you not use sockets in diff threads?
| [Thursday 03 March 2011] [03:13:19] <yrashk>	this was getting confusing at some point
| [Thursday 03 March 2011] [03:13:37] <guido_g>	you can, but you should do it *very* carefully
| [Thursday 03 March 2011] [03:13:50] <guido_g>	as always when using threads
| [Thursday 03 March 2011] [03:13:56] <yrashk>	what consitutes carefulness in this case?
| [Thursday 03 March 2011] [03:14:25] <sustrik>	no parallel access
| [Thursday 03 March 2011] [03:14:54] <yrashk>	so if mutexed around, we're fine?
| [Thursday 03 March 2011] [03:15:02] <eyecue>	moin
| [Thursday 03 March 2011] [03:15:04] <guido_g>	which means the same usage-pattern as before, but you can migrate a socket from thread to another
| [Thursday 03 March 2011] [03:15:12] <guido_g>	yrashk: no
| [Thursday 03 March 2011] [03:15:30] <guido_g>	yrashk: doesn't make sense
| [Thursday 03 March 2011] [03:15:47] <sustrik>	guido_g: it would work
| [Thursday 03 March 2011] [03:16:00] <sustrik>	basically it means you migrate the socket each time the mutex is locked
| [Thursday 03 March 2011] [03:16:04] <eyecue>	pieterh; nice coincidence, a vendor we're engaging today uses zeromq to arbitrate their mail and messaging infrastructure :)
| [Thursday 03 March 2011] [03:16:13] <sustrik>	yrashk: it's going to be slow
| [Thursday 03 March 2011] [03:16:18] <yrashk>	sustrik: yeah
| [Thursday 03 March 2011] [03:16:26] <yrashk>	mutexes add a penalty
| [Thursday 03 March 2011] [03:16:31] <sustrik>	yes
| [Thursday 03 March 2011] [03:16:32] <guido_g>	sustrik: technically yes, but you should be the one pointing out that it is broken by design and start to protect the innocent developers...
| [Thursday 03 March 2011] [03:16:32] <pieterh>	eyecue: nice
| [Thursday 03 March 2011] [03:16:39] <eyecue>	pieterh; taguchimail :]
| [Thursday 03 March 2011] [03:16:39] <sustrik>	exactly
| [Thursday 03 March 2011] [03:16:43] <eyecue>	in case youre interested
| [Thursday 03 March 2011] [03:16:49] 	 * pieterh goes to check
| [Thursday 03 March 2011] [03:17:01] <sustrik>	that's why we added scary stuff about memory barriers into docs :)
| [Thursday 03 March 2011] [03:17:21] <guido_g>	obviously didn't work
| [Thursday 03 March 2011] [03:17:24] <guido_g>	]:->
| [Thursday 03 March 2011] [03:17:27] <eyecue>	i might need to pick some irc brains soon for how i can apply 0mq to our stuff
| [Thursday 03 March 2011] [03:17:41] <pieterh>	sustrik: problem is that 'memory barriers' isn't very explanatory
| [Thursday 03 March 2011] [03:17:47] <guido_g>	i'm available for hire ,)
| [Thursday 03 March 2011] [03:17:51] <sustrik>	that's the point
| [Thursday 03 March 2011] [03:18:03] <sustrik>	for most people it translates to "don't do this"
| [Thursday 03 March 2011] [03:18:04] <pieterh>	sustrik: doesn't help to be mysterious
| [Thursday 03 March 2011] [03:18:15] <sustrik>	which is exactly the message
| [Thursday 03 March 2011] [03:18:16] <pieterh>	passing sockets from thread to thread is a valid pattern
| [Thursday 03 March 2011] [03:18:20] <pieterh>	bleh
| [Thursday 03 March 2011] [03:18:40] <eyecue>	pieterh; would this sentence make sense: i would get a developer to build a daemon'able queueing application using the 0mq library and add support for some form of persistant storage?
| [Thursday 03 March 2011] [03:19:05] <pieterh>	eyecue: depends whom you're talking to
| [Thursday 03 March 2011] [03:19:05] <sustrik>	pieterh: we can remove the memory barrier text
| [Thursday 03 March 2011] [03:19:14] <pieterh>	sustrik: the explanation needs to be precise
| [Thursday 03 March 2011] [03:19:26] <sustrik>	but actually, you *do* have to do the memory barrier
| [Thursday 03 March 2011] [03:19:30] <pieterh>	you can create a socket in one thread and pass that to another thread
| [Thursday 03 March 2011] [03:19:32] <eyecue>	pieterh; in the strictest sense that 0mq is a programming 'library' which one can use to then build daemons (instead of say a client app)
| [Thursday 03 March 2011] [03:19:44] <pieterh>	you MUST NOT read/write/close the same socket in multiple threads
| [Thursday 03 March 2011] [03:19:49] <sustrik>	the thing is that in 99% of cases it's done for you
| [Thursday 03 March 2011] [03:20:02] <sustrik>	so you don't have to care about it
| [Thursday 03 March 2011] [03:20:02] <eyecue>	pieterh; compared to say your beanstalkd's, which implement and provide a daemon out of the box
| [Thursday 03 March 2011] [03:20:08] <pieterh>	sustrik: not one person has hit a problem related to memory barriers afaics
| [Thursday 03 March 2011] [03:20:17] <yrashk>	the proble is that we DON'T WANT to do this
| [Thursday 03 March 2011] [03:20:25] <pieterh>	eyecue: yes, 0MQ is a toolkit with which you build frameworks
| [Thursday 03 March 2011] [03:20:26] <yrashk>	but we have to deal with the way erlang uses schedulers
| [Thursday 03 March 2011] [03:20:28] <sustrik>	right, so should we remove the text?
| [Thursday 03 March 2011] [03:20:31] <yrashk>	each scheduler is a differnet OS thread
| [Thursday 03 March 2011] [03:20:32] <eyecue>	pieterh; ta :]
| [Thursday 03 March 2011] [03:20:50] <yrashk>	and we can't tell Erlang to use one specific scheduler only
| [Thursday 03 March 2011] [03:20:54] <pieterh>	eyecue: look at zero.mq/md for an example, that's 3-4 days from concept to running code
| [Thursday 03 March 2011] [03:21:03] <pieterh>	with full APIs etc, and in C
| [Thursday 03 March 2011] [03:21:05] <eyecue>	roger that
| [Thursday 03 March 2011] [03:21:23] <pieterh>	that's less time than it takes to *learn* a conventional messaging API
| [Thursday 03 March 2011] [03:21:47] <eyecue>	pieterh; i read the guide last night, and the most intriguing part was the self-healing slash self adapting node network concept
| [Thursday 03 March 2011] [03:21:49] <pieterh>	sustrik: any text in the docs has to reference people's real questions and needs
| [Thursday 03 March 2011] [03:22:05] <eyecue>	pieterh; yeh, i got one of our django guys to take a look at 0mq today
| [Thursday 03 March 2011] [03:22:14] <pieterh>	sustrik: if you like I'll review that man page and propose changes
| [Thursday 03 March 2011] [03:22:57] <eyecue>	pieterh; i have a particular problem to solve where i dont know what the load of the input system will be ahead of time, nor do i want to care necessarily about the message/payload size (email bodies * mailing list members)
| [Thursday 03 March 2011] [03:23:19] <sustrik>	sure, give it a try
| [Thursday 03 March 2011] [03:23:42] <eyecue>	pieterh; i want to avoid serially queueing campaigns, and i dont really care about fair queueing, so im toying with the concept of an abstract fifo queue per campaign. the issue that i have is the idea that any campaign can 'start' or be scheduled at any time
| [Thursday 03 March 2011] [03:23:47] <pieterh>	eyecue: my advice would be to ask here for someone to spend a short time training & helping your team use 0MQ
| [Thursday 03 March 2011] [03:23:54] <sustrik>	reference should be complete though, so the memory barrier issue should be at least mentioned
| [Thursday 03 March 2011] [03:23:58] <eyecue>	pieterh; we're in .au, know anyone here? :)
| [Thursday 03 March 2011] [03:23:59] <sustrik>	maybe in a note?
| [Thursday 03 March 2011] [03:24:07] <eyecue>	pieterh; id be more than happy to entertain that idea
| [Thursday 03 March 2011] [03:24:53] <eyecue>	*reads mdp*
| [Thursday 03 March 2011] [03:25:08] <pieterh>	sustrik: do we know anyone in .au? 
| [Thursday 03 March 2011] [03:25:20] <sustrik>	let me see
| [Thursday 03 March 2011] [03:25:54] <eyecue>	do you have have an active/developed advocacy network/framework/contact list going?
| [Thursday 03 March 2011] [03:26:00] <sustrik>	i have kind of vague feeling that we do, but not sure
| [Thursday 03 March 2011] [03:26:24] <eyecue>	pieterh; well, apart from taguchimail ;) i may go and pick his brain a bit (since we're already paying him)
| [Thursday 03 March 2011] [03:26:54] <eyecue>	haha very cute -> The Majordomo pattern has no relation to the open source mailing list software with the same name.
| [Thursday 03 March 2011] [03:27:14] <pieterh>	eyecue: someone pointed out the risk of confusion
| [Thursday 03 March 2011] [03:27:21] <eyecue>	that was me last night :]
| [Thursday 03 March 2011] [03:27:24] <eyecue>	too much beer? :]
| [Thursday 03 March 2011] [03:27:24] <pieterh>	ah!
| [Thursday 03 March 2011] [03:27:33] <pieterh>	hey, it's all one big blur...
| [Thursday 03 March 2011] [03:27:41] <eyecue>	amen, and so it should be
| [Thursday 03 March 2011] [03:28:18] <eyecue>	actually mdp may well solve for our problem domain
| [Thursday 03 March 2011] [03:28:33] <eyecue>	each worker can say how many active campaigns are available to dequeue
| [Thursday 03 March 2011] [03:28:48] <eyecue>	it could assign itself one of the 'service names'
| [Thursday 03 March 2011] [03:28:50] <pieterh>	eyecue: yes, mdp seems to cover a lot of problems
| [Thursday 03 March 2011] [03:28:52] <eyecue>	ensuring a 1:1
| [Thursday 03 March 2011] [03:29:01] <sejo>	if I would want to persist all the messages (untill they are processed) what backend would you suggest (need a fast backing)
| [Thursday 03 March 2011] [03:29:24] <eyecue>	pieterh; i could then interleave/loadbalance the MTA injection form that point
| [Thursday 03 March 2011] [03:29:24] <pieterh>	sejo: it's not that simple but you might look at Tokyo Cabinet or similar
| [Thursday 03 March 2011] [03:29:46] <sejo>	pieterh: tokio cabinet, mongodb, couchdb etc?
| [Thursday 03 March 2011] [03:29:57] <eyecue>	hmm, could even spawn new workers based on workload that mdp knows about
| [Thursday 03 March 2011] [03:30:09] <eyecue>	id say threadpool, but i only mean in concept.
| [Thursday 03 March 2011] [03:30:42] <eyecue>	this may be a kicker though -> Workers are idempotent, i.e. it is safe to execute the same request more than once.
| [Thursday 03 March 2011] [03:30:55] <pieterh>	eyecue: that's a matter of shared database
| [Thursday 03 March 2011] [03:30:59] <eyecue>	we need to ensure non-duplicate delivery of mail/messages
| [Thursday 03 March 2011] [03:31:02] <pieterh>	sure
| [Thursday 03 March 2011] [03:31:07] <eyecue>	im not sure how it applies, but yeh
| [Thursday 03 March 2011] [03:31:12] <guido_g>	sejo: redis for speed only, if you have the memory
| [Thursday 03 March 2011] [03:31:42] <sejo>	guido_g: needs to be persistable and distributed :p
| [Thursday 03 March 2011] [03:31:52] <sejo>	(not that I'm asking a lot :p)
| [Thursday 03 March 2011] [03:32:00] <guido_g>	sure, go read
| [Thursday 03 March 2011] [03:32:05] <pieterh>	sejo: what're the performance requirements?
| [Thursday 03 March 2011] [03:32:27] <guido_g>	sejo: mongodb is quite fast too
| [Thursday 03 March 2011] [03:32:30] <pieterh>	eyecue: if you're up for sponsoring work on MDP and/or broker implementations, drop me a line
| [Thursday 03 March 2011] [03:32:36] <sejo>	pieterh: 100-500 reqs a second
| [Thursday 03 March 2011] [03:32:43] <sejo>	might even go up
| [Thursday 03 March 2011] [03:32:56] <pieterh>	sejo: can you wait a week or two? I'm working on a rust-based reliability pattern
| [Thursday 03 March 2011] [03:33:00] <pieterh>	fire and forget
| [Thursday 03 March 2011] [03:33:08] <eyecue>	pieterh; i was just about to ask you about 'pausing' queues, or something semantically similar. i note that some of your socket types block or drop, depending on which is chosen, so that may be a way
| [Thursday 03 March 2011] [03:33:08] <pieterh>	client sends to rust-based broker
| [Thursday 03 March 2011] [03:33:20] <pieterh>	broker then sends to workers
| [Thursday 03 March 2011] [03:33:48] <pieterh>	whole thing is brute-force ack'd 
| [Thursday 03 March 2011] [03:33:52] <sejo>	cool, looks what I need, but sorry no time for wait (startup here and my money isn't unlimited)
| [Thursday 03 March 2011] [03:34:24] <pieterh>	sejo: where do you want your persistence, in client, or in center?
| [Thursday 03 March 2011] [03:34:46] <sejo>	on the broker
| [Thursday 03 March 2011] [03:34:52] <pieterh>	ugh
| [Thursday 03 March 2011] [03:34:56] <pieterh>	that's the worst choice
| [Thursday 03 March 2011] [03:34:59] <sejo>	worker should just execute and send results
| [Thursday 03 March 2011] [03:35:12] <pieterh>	so the problem here is that when you want the broker to hold the state
| [Thursday 03 March 2011] [03:35:35] <sejo>	well not much states just a group of key-value's
| [Thursday 03 March 2011] [03:35:50] <eyecue>	im out, thanks for the help pieter
| [Thursday 03 March 2011] [03:35:50] <pieterh>	you need extra work to speak to that state reliably
| [Thursday 03 March 2011] [03:35:54] <pieterh>	eyecue: ciao
| [Thursday 03 March 2011] [03:36:07] <pieterh>	sejo: if you place the persistence in the client API, for example
| [Thursday 03 March 2011] [03:36:13] <pieterh>	you can use dumb brokers
| [Thursday 03 March 2011] [03:37:26] <sejo>	ok, basicly i need a group of brokers (that share data) which is pulled by workers, the same workers will push new tasks generated from the result to the broker. State is kept in worker, the minute it reaches the broker, only the messagedata is state
| [Thursday 03 March 2011] [03:37:54] <pieterh>	sure
| [Thursday 03 March 2011] [03:38:05] <sejo>	btw redis is master-slave
| [Thursday 03 March 2011] [03:39:37] <pieterh>	sustrik: random question about style
| [Thursday 03 March 2011] [03:39:38] <sejo>	couchdb is master:master
| [Thursday 03 March 2011] [03:39:45] <pieterh>	the man pages are written in the form of specifications
| [Thursday 03 March 2011] [03:39:51] <pieterh>	(which is excellent IMO)
| [Thursday 03 March 2011] [03:40:27] <pieterh>	to make this more contractual, we could use http://tools.ietf.org/html/rfc2119
| [Thursday 03 March 2011] [03:41:00] <pieterh>	e.g. "Applications MAY create a socket in one thread with _zmq_socket()_ and then pass it to a _newly created_ thread as part of thread initialization, for example via a structure passed as an argument to _pthread_create()_. Applications MUST NOT do stupid stuff."
| [Thursday 03 March 2011] [03:44:59] <sejo>	nice did you guys use couchdb already? 
| [Thursday 03 March 2011] [03:45:07] <sejo>	looks pretty good
| [Thursday 03 March 2011] [03:45:11] 	 * sejo plays with it
| [Thursday 03 March 2011] [03:47:11] 	 * sejo just fell in love
| [Thursday 03 March 2011] [03:54:24] <pieterh>	sustrik: ok, patch to zmq_socket sent
| [Thursday 03 March 2011] [03:54:30] <pieterh>	that should help IMO
| [Thursday 03 March 2011] [03:56:54] <djc>	sejo: couchdb is awesome, we use it a lot at work
| [Thursday 03 March 2011] [03:57:10] <sejo>	djc: Yeah going to use it also
| [Thursday 03 March 2011] [03:57:25] <sejo>	already started playing with it :p
| [Thursday 03 March 2011] [03:57:27] <sejo>	=80
| [Thursday 03 March 2011] [03:58:04] <sustrik>	pieterh: does that help in any way?
| [Thursday 03 March 2011] [03:58:13] <sustrik>	it doesn't answer yrashk's question
| [Thursday 03 March 2011] [03:58:13] <pieterh>	does what help?
| [Thursday 03 March 2011] [03:58:17] <sustrik>	the patch
| [Thursday 03 March 2011] [03:58:31] <pieterh>	what's yrashk's question? sorry, I missed something
| [Thursday 03 March 2011] [03:58:43] <sustrik>	the one that started the disussion
| [Thursday 03 March 2011] [03:58:56] <sustrik>	whether sockets can be used from 2 threads
| [Thursday 03 March 2011] [03:59:04] <pieterh>	" can you or can you not use sockets in diff threads?"
| [Thursday 03 March 2011] [03:59:15] <pieterh>	I think the patch makes this very clear
| [Thursday 03 March 2011] [03:59:16] <sustrik>	then the argument was that speaking about memory barriers is not clear
| [Thursday 03 March 2011] [03:59:18] <pieterh>	sure
| [Thursday 03 March 2011] [03:59:25] <pieterh>	the man page started by talking about contexts
| [Thursday 03 March 2011] [03:59:38] <pieterh>	now it says "sockets are not thread safe. period".
| [Thursday 03 March 2011] [03:59:41] <sustrik>	and that haven't changed 
| [Thursday 03 March 2011] [04:00:04] <sustrik>	?
| [Thursday 03 March 2011] [04:00:05] <sustrik>	+0MQ 'sockets' are _not_ thread safe. Applications MAY create a socket in one
| [Thursday 03 March 2011] [04:00:05] <sustrik>	+thread with _zmq_socket()_ and then pass it to a _newly created_ thread as
| [Thursday 03 March 2011] [04:00:05] <sustrik>	+part of thread initialization, for example via a structure passed as an
| [Thursday 03 March 2011] [04:00:09] <sustrik>	+argument to _pthread_create()_. Applications MUST NOT otherwise use a socket
| [Thursday 03 March 2011] [04:00:10] <sustrik>	+from multiple threads except after migrating a socket from one thread to
| [Thursday 03 March 2011] [04:00:13] <sustrik>	+another with a "full fence" memory barrier.
| [Thursday 03 March 2011] [04:00:18] <pieterh>	the first sentence is the most important
| [Thursday 03 March 2011] [04:00:30] <sustrik>	yep, that's ok
| [Thursday 03 March 2011] [04:00:35] <pieterh>	the second sentence provides the ONE valid use case
| [Thursday 03 March 2011] [04:00:41] <pieterh>	the third sentence explains it for those who care
| [Thursday 03 March 2011] [04:00:51] <pieterh>	and fourth, some bla blah about contexts
| [Thursday 03 March 2011] [04:00:55] <sustrik>	why singling out one valid use case?
| [Thursday 03 March 2011] [04:01:01] <pieterh>	it's the only one I know of
| [Thursday 03 March 2011] [04:01:07] <pieterh>	for normal apps
| [Thursday 03 March 2011] [04:01:07] <sustrik>	that's more of a guide stuff
| [Thursday 03 March 2011] [04:01:22] <pieterh>	that was already in the man page... I just trimmed it a little
| [Thursday 03 March 2011] [04:01:39] <pieterh>	plus it really does need to be there
| [Thursday 03 March 2011] [04:01:56] <guido_g>	ha! client just passed first send unittest
| [Thursday 03 March 2011] [04:01:58] <sustrik>	you mean the memory barrier stuff?
| [Thursday 03 March 2011] [04:02:00] <sustrik>	yes
| [Thursday 03 March 2011] [04:02:15] <sustrik>	the one use case should be moved to guide imo
| [Thursday 03 March 2011] [04:02:20] <pieterh>	sustrik: please, no
| [Thursday 03 March 2011] [04:02:30] <pieterh>	don't make life harder for users than it has to be
| [Thursday 03 March 2011] [04:02:50] <pieterh>	i agree that this is explanatory and not a specification
| [Thursday 03 March 2011] [04:02:59] <pieterh>	but this is so important for MT apps
| [Thursday 03 March 2011] [04:03:11] <pieterh>	you can't afford to hide it somewhere in a 1000-page book
| [Thursday 03 March 2011] [04:03:19] <sustrik>	i mean there are many use cases, so singling one of them out gives wrong impression
| [Thursday 03 March 2011] [04:03:24] <sustrik>	what about making it an example?
| [Thursday 03 March 2011] [04:03:25] <pieterh>	there are not many use cases!
| [Thursday 03 March 2011] [04:03:28] <pieterh>	sorry, 
| [Thursday 03 March 2011] [04:03:33] <pieterh>	that's just not accurate
| [Thursday 03 March 2011] [04:03:57] <pieterh>	i've hit precisely one, in 40-50 examples that cover every angle
| [Thursday 03 March 2011] [04:04:06] <pieterh>	you may imagine use cases, that's not the same
| [Thursday 03 March 2011] [04:04:27] <sustrik>	garbage collecting the socket is pretty common
| [Thursday 03 March 2011] [04:04:30] <pieterh>	if you fix the inproc connect/bind issue, this use case disapepars
| [Thursday 03 March 2011] [04:04:33] <pieterh>	*disappears
| [Thursday 03 March 2011] [04:04:47] <pieterh>	that would be ideal IMO
| [Thursday 03 March 2011] [04:05:05] <pieterh>	only 5 people, globally, will ever write a socket garbage collector
| [Thursday 03 March 2011] [04:05:17] <pieterh>	maybe 10, ever
| [Thursday 03 March 2011] [04:05:24] <sustrik>	wait a sec, you are saying that this use case is *necessary*?
| [Thursday 03 March 2011] [04:05:27] <sustrik>	how so?
| [Thursday 03 March 2011] [04:05:28] <pieterh>	yes
| [Thursday 03 March 2011] [04:05:34] <sustrik>	you can pass context to the other thread
| [Thursday 03 March 2011] [04:05:39] <pieterh>	because there's no other way to create a working inproc socket pair
| [Thursday 03 March 2011] [04:05:40] <sustrik>	and create the socket there
| [Thursday 03 March 2011] [04:05:41] <sustrik>	no?
| [Thursday 03 March 2011] [04:05:44] <pieterh>	due to the bind/connect issue
| [Thursday 03 March 2011] [04:05:53] <pieterh>	sustrik: have you read the Guide?
| [Thursday 03 March 2011] [04:05:57] <sustrik>	yes
| [Thursday 03 March 2011] [04:06:03] <pieterh>	read it again until you understand 0MQ
| [Thursday 03 March 2011] [04:06:06] <pieterh>	:-)
| [Thursday 03 March 2011] [04:06:09] <pieterh>	heh
| [Thursday 03 March 2011] [04:06:15] <sustrik>	what's wrong with this:
| [Thursday 03 March 2011] [04:06:26] <sustrik>	c = context()
| [Thursday 03 March 2011] [04:06:35] <sustrik>	s = socket (c);
| [Thursday 03 March 2011] [04:06:44] <sustrik>	s.bind (...);
| [Thursday 03 March 2011] [04:06:57] <sustrik>	pthread_create (c);
| [Thursday 03 March 2011] [04:07:02] <sustrik>	and in the worker thread:
| [Thursday 03 March 2011] [04:07:06] <sustrik>	s = socket(c);
| [Thursday 03 March 2011] [04:07:09] <sustrik>	s.connect (...)
| [Thursday 03 March 2011] [04:07:11] <pieterh>	the example in the Guide has 3 stages
| [Thursday 03 March 2011] [04:07:51] <sustrik>	same thing, no?
| [Thursday 03 March 2011] [04:08:10] <pieterh>	let me double check
| [Thursday 03 March 2011] [04:08:21] <pieterh>	if there is a valid pattern, this use case disappears
| [Thursday 03 March 2011] [04:09:23] <pieterh>	ok, you're right afaics
| [Thursday 03 March 2011] [04:09:33] <pieterh>	bind before creating child threads
| [Thursday 03 March 2011] [04:09:59] <pieterh>	I need to change some stuff in the guide
| [Thursday 03 March 2011] [04:10:25] <pieterh>	we can indeed remove that example from the man page... hang on a sec then...
| [Thursday 03 March 2011] [04:12:38] <pieterh>	sustrik: patch sent, this is much cleaner
| [Thursday 03 March 2011] [04:12:51] <sustrik>	ok, thanks
| [Thursday 03 March 2011] [04:12:57] 	 * pieterh enjoys learning new stuff about 0MQ
| [Thursday 03 March 2011] [04:13:48] <sustrik>	pieterh: you've sent the old patch i think
| [Thursday 03 March 2011] [04:14:04] <sustrik>	looks the same
| [Thursday 03 March 2011] [04:14:40] <pieterh>	git did something... hang on
| [Thursday 03 March 2011] [04:15:39] <pieterh>	weird, git produces the wrong patch
| [Thursday 03 March 2011] [04:16:38] <sustrik>	never mind, i can do it myself
| [Thursday 03 March 2011] [04:16:46] <sustrik>	it's just reversing two paragraphs
| [Thursday 03 March 2011] [04:16:49] <pieterh>	sigh, just use this paragraph:
| [Thursday 03 March 2011] [04:16:51] <sustrik>	and adding a period
| [Thursday 03 March 2011] [04:16:53] <sustrik>	right?
| [Thursday 03 March 2011] [04:16:53] <pieterh>	0MQ 'sockets' are _not_ thread safe. Applications MUST NOT use a socket
| [Thursday 03 March 2011] [04:16:53] <pieterh>	from multiple threads except after migrating a socket from one thread to 
| [Thursday 03 March 2011] [04:16:53] <pieterh>	another with a "full fence" memory barrier.
| [Thursday 03 March 2011] [04:16:59] <pieterh>	and move the context stuff below
| [Thursday 03 March 2011] [04:17:10] <pieterh>	i forgot a 'git add'
| [Thursday 03 March 2011] [04:17:27] <pieterh>	too many little bitty steps
| [Thursday 03 March 2011] [04:18:03] <pieterh>	BTW "full fence" is the proper jargon afaics
| [Thursday 03 March 2011] [04:18:33] <sustrik>	possibly
| [Thursday 03 March 2011] [04:18:51] <sustrik>	btw, we've changed the wording a bit
| [Thursday 03 March 2011] [04:19:00] <sustrik>	but haven't addressed the original issue
| [Thursday 03 March 2011] [04:19:10] <sustrik>	that speaking about 'fences' is mysterious
| [Thursday 03 March 2011] [04:19:15] <sustrik>	rather than helpful
| [Thursday 03 March 2011] [04:19:21] <pieterh>	the question was 'are sockets thread safe'?
| [Thursday 03 March 2011] [04:19:30] <pieterh>	and the answer is 'no'... how is that not answering it?
| [Thursday 03 March 2011] [04:19:50] <sustrik>	the docs said so even before
| [Thursday 03 March 2011] [04:19:57] <pieterh>	they hid that in a lot of other text
| [Thursday 03 March 2011] [04:20:03] <pieterh>	obviously people didn't see it clearly
| [Thursday 03 March 2011] [04:20:48] <sustrik>	ok
| [Thursday 03 March 2011] [04:20:51] <sustrik>	the period helps
| [Thursday 03 March 2011] [04:21:22] <pieterh>	shrug, I'm not sure what you're asking, yrashk's question was clear, and it seems clear the man page had way too much wrapping around the essential statement, "don't do it, but if you must, use full fence memory barriers"
| [Thursday 03 March 2011] [04:23:45] <sustrik>	well, the only real change seems to be the period; what i'm asking is: should it say something like "you can use socket from multiple threads given you synchronise the access"
| [Thursday 03 March 2011] [04:24:11] <pieterh>	people will start using mutexes all over the place
| [Thursday 03 March 2011] [04:24:14] <sustrik>	it's antipattern in most cases, but technically, the statement is sound
| [Thursday 03 March 2011] [04:24:19] <sustrik>	exactly
| [Thursday 03 March 2011] [04:24:55] <sustrik>	that was the original discussion, whether it's ok to scare people using terms like "memory barrier"
| [Thursday 03 March 2011] [04:25:07] <sustrik>	or rather be technically precise
| [Thursday 03 March 2011] [04:25:12] <pieterh>	i don't think fear is a valid tool
| [Thursday 03 March 2011] [04:25:17] <pieterh>	this is a contract
| [Thursday 03 March 2011] [04:25:28] <pieterh>	it should simply state what is allowed, and what is not
| [Thursday 03 March 2011] [04:25:59] <sustrik>	ok, then it should be "you can use socket from multiple threads given you synchronise the access"
| [Thursday 03 March 2011] [04:26:22] <sustrik>	that's more comprehensible than memory barrier stuff
| [Thursday 03 March 2011] [04:26:23] <pieterh>	every contract aims to force the signer to behave in some way
| [Thursday 03 March 2011] [04:26:39] <pieterh>	look, we don't want people to share sockets between threads, period
| [Thursday 03 March 2011] [04:26:45] <pieterh>	it's the cause of repeated failures
| [Thursday 03 March 2011] [04:27:04] <sustrik>	ok, good
| [Thursday 03 March 2011] [04:27:04] <pieterh>	we see one or two bizarre 0MQ crash reports a week due to this
| [Thursday 03 March 2011] [04:27:18] 	 * sustrik has no strong opinion on this matter
| [Thursday 03 March 2011] [04:28:23] 	 * pieterh wants to steer people away from misusing the tool
| [Thursday 03 March 2011] [04:34:53] <pieterh>	I'm ripping out all explanation of socket migration from the guide, we'll use the pattern you explained, bind before starting child thread
| [Thursday 03 March 2011] [04:49:33] <sejo>	if you have a zmq.PULL and recv() something, is it possible to know what worker sent that?
| [Thursday 03 March 2011] [04:49:59] <pieterh>	sejo: you have to add the information yourself to the message
| [Thursday 03 March 2011] [04:50:14] <pieterh>	otherwise, use a ROUTER (XREP) socket instead
| [Thursday 03 March 2011] [04:50:16] <sejo>	pieterh: ok good! thanks!
| [Thursday 03 March 2011] [04:50:30] <sejo>	I think it'll be better to put it in the message
| [Thursday 03 March 2011] [04:52:49] <pieterh>	sustrik: so, I've removed all examples of socket migration from the guide
| [Thursday 03 March 2011] [04:53:09] <pieterh>	your pattern is actually much clearer and simpler than passing sockets around
| [Thursday 03 March 2011] [05:03:47] <sustrik>	ok, good
| [Thursday 03 March 2011] [05:03:56] <sustrik>	i'll update the reference accordingly
| [Thursday 03 March 2011] [05:19:54] 	 * guido_g is going offline, getting new internet! :)
| [Thursday 03 March 2011] [05:58:08] <guido_g>	re with new internet :)
| [Thursday 03 March 2011] [06:03:26] <pieterh>	sustrik: is there any recommended way to trap Ctrl-C in a 0MQ program (C++ or C)?
| [Thursday 03 March 2011] [06:04:22] <sustrik>	standard C way
| [Thursday 03 March 2011] [06:04:27] <sustrik>	no specifics
| [Thursday 03 March 2011] [06:04:40] <pieterh>	ok, I'll give it a shot...
| [Thursday 03 March 2011] [06:16:58] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r97add1e 10/ (doc/zmq_init.txt doc/zmq_socket.txt): 
| [Thursday 03 March 2011] [06:16:58] <CIA-21>	zeromq2: Documentation wrt thread-safety cleaned up.
| [Thursday 03 March 2011] [06:16:58] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/dLdfr0
| [Thursday 03 March 2011] [06:25:32] <pieterh>	sustrik: cool, signal handling works perfectly to shut down 0MQ...
| [Thursday 03 March 2011] [06:25:39] <pieterh>	I'll document it, it's simple and clean
| [Thursday 03 March 2011] [06:38:28] <sejo>	hmm I created a small zmq.PULL and try to send with telnet a message to it... when debugging it it never gets to recv() 
| [Thursday 03 March 2011] [06:38:51] <AlexB>	Hello. :) I've found an issue with having inproc sockets that are bound but without any connected end-point. With recent versions of ZeroMQ and PyZMQ, closing a context with socket like that hangs. Here's a short test-case: https://gist.github.com/852644
| [Thursday 03 March 2011] [06:39:33] <CIA-21>	zeromq2: 03Martin Sustrik 07master * r184bdb8 10/ src/xrep.cpp : 
| [Thursday 03 March 2011] [06:39:33] <CIA-21>	zeromq2: Bug caused by interaction of REQ/REP routing and HWM fixed.
| [Thursday 03 March 2011] [06:39:33] <CIA-21>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/ec5ykN
| [Thursday 03 March 2011] [06:39:39] <guido_g>	sejo: mq does have its own wire-format
| [Thursday 03 March 2011] [06:40:01] <sejo>	guido_g: ach ok, so i'd better write my client then :p
| [Thursday 03 March 2011] [06:40:04] <sejo>	thanks!
| [Thursday 03 March 2011] [06:40:31] <pieterh>	AlexB: this is a known issue
| [Thursday 03 March 2011] [06:40:40] <pieterh>	you need to close the socket before closing the context
| [Thursday 03 March 2011] [06:46:25] <AlexB>	I see. I found it in the docs now.
| [Thursday 03 March 2011] [06:46:53] <AlexB>	Thanks. :)
| [Thursday 03 March 2011] [06:50:37] <pieterh>	sustrik: can 184bdb8 go to 2.0.x?
| [Thursday 03 March 2011] [06:52:11] <sustrik>	yes, if applicable
| [Thursday 03 March 2011] [06:53:32] <pieterh>	:-) do you really trust me to figure that out and make the change?
| [Thursday 03 March 2011] [06:53:45] <pieterh>	the code in xrep.cpp looks similar enough
| [Thursday 03 March 2011] [06:54:07] <pieterh>	but I'm not comfortable backporting patches that I did not write myself
| [Thursday 03 March 2011] [06:54:44] <private_meta>	pieterh: hmm... renaming the .c files to .class somewhat broke online viewing on github :/
| [Thursday 03 March 2011] [06:54:51] <sustrik>	this is why i said maintaining a stable branch needs a dedicated person :)
| [Thursday 03 March 2011] [06:55:18] <pieterh>	sustrik: the process can work fine if we are consistent about patch flow
| [Thursday 03 March 2011] [06:55:29] <pieterh>	i.e. anyone wants a patch to version X they send it
| [Thursday 03 March 2011] [06:55:43] <pieterh>	separate the work of making the release, and making the code
| [Thursday 03 March 2011] [06:55:52] <pieterh>	it should be two separate hats / people
| [Thursday 03 March 2011] [06:56:28] <pieterh>	imagine it's not you...
| [Thursday 03 March 2011] [06:56:51] <pieterh>	who would be best to backport OpenPGM 5 support to 2.0?
| [Thursday 03 March 2011] [06:57:06] <pieterh>	clearly, the person who made that work in 2.1
| [Thursday 03 March 2011] [06:57:30] <pieterh>	private_meta: well, you were the one trying to compile these classes
| [Thursday 03 March 2011] [06:57:32] <guido_g>	private_meta: i bet that's because .class files are compiled .java files 
| [Thursday 03 March 2011] [06:57:41] <pieterh>	lol java
| [Thursday 03 March 2011] [06:58:13] <pieterh>	private_meta: indeed, nothing shows at all... :-/
| [Thursday 03 March 2011] [06:58:33] <guido_g>	so another rename...
| [Thursday 03 March 2011] [06:58:40] <pieterh>	ok, alternate suggestions?
| [Thursday 03 March 2011] [06:58:42] <private_meta>	pieterh: Well, I wouldn't mind just ".h"
| [Thursday 03 March 2011] [06:58:52] <private_meta>	if it were c++, I'd go with ".hpp" with those classes
| [Thursday 03 March 2011] [06:59:11] <pieterh>	i suppose it's consistent with zhelpers.h
| [Thursday 03 March 2011] [06:59:20] <private_meta>	It would be, yes
| [Thursday 03 March 2011] [06:59:42] <pieterh>	sigh, 'clever' software...
| [Thursday 03 March 2011] [07:00:24] <private_meta>	heh
| [Thursday 03 March 2011] [07:00:30] <guido_g>	hehe
| [Thursday 03 March 2011] [07:00:47] <pieterh>	sustrik: if you want that patch to go into 2.0.11 (which it should IMO), please spend 2 minutes at https://github.com/zeromq/zeromq2-0/blob/master/src/xrep.cpp
| [Thursday 03 March 2011] [07:00:59] <pieterh>	it's not going to work if you ask the release maintainer to do backports
| [Thursday 03 March 2011] [07:01:16] <pieterh>	(a) I refuse, it would be insane, and (b) it's impossible if you have a real community of developers
| [Thursday 03 March 2011] [07:01:43] <pieterh>	just like you ask contributors to provide you with patches, I'm asking you
| [Thursday 03 March 2011] [07:01:47] <pieterh>	pretty please
| [Thursday 03 March 2011] [07:07:40] <sustrik>	well, i don't have resources to maintain 3 branches, sorry
| [Thursday 03 March 2011] [07:07:49] <sustrik>	i've warned you
| [Thursday 03 March 2011] [07:12:30] <pieterh>	this is not about maintaining branches, martin
| [Thursday 03 March 2011] [07:12:42] <pieterh>	it's about how we backport changes when we have N contributors and N release versions
| [Thursday 03 March 2011] [07:12:57] <pieterh>	did you understand my example of OpenPGM?
| [Thursday 03 March 2011] [07:13:09] <pieterh>	if you want this to scale, it's the only way I can see
| [Thursday 03 March 2011] [07:13:52] <pieterh>	it's literally two minutes for you, you know the code perfectly, it's a 10-line patch
| [Thursday 03 March 2011] [07:14:10] <pieterh>	and I take care of delivering that to the user community
| [Thursday 03 March 2011] [07:14:26] <pieterh>	but if you comingle these two tasks, there will never be properly maintained stable releases
| [Thursday 03 March 2011] [07:14:28] <pieterh>	period
| [Thursday 03 March 2011] [07:14:54] <pieterh>	do you have another suggestion?
| [Thursday 03 March 2011] [07:15:58] <sustrik>	it's not a 2 minute work
| [Thursday 03 March 2011] [07:16:15] <sustrik>	the code has changed in the meanwhile and works somewhat differentlu
| [Thursday 03 March 2011] [07:16:31] <sustrik>	so it needs, careful patching, testing etc.
| [Thursday 03 March 2011] [07:16:35] <sustrik>	backporting is hard work
| [Thursday 03 March 2011] [07:16:46] <pieterh>	this is perfectly acceptable as an answer
| [Thursday 03 March 2011] [07:16:48] <pieterh>	"no"
| [Thursday 03 March 2011] [07:18:00] <pieterh>	you have two sets of people, those able to make release packages (follow procedures perfectly) and those able to backport patches
| [Thursday 03 March 2011] [07:18:14] <pieterh>	the intersection of those two sets is close to zero, if not literally zero
| [Thursday 03 March 2011] [07:18:20] <pieterh>	that's the major issue here
| [Thursday 03 March 2011] [07:18:33] <Steve-o>	:O
| [Thursday 03 March 2011] [07:18:58] <pieterh>	in the 0MQ world, specifically
| [Thursday 03 March 2011] [07:19:26] <Steve-o>	backporting networking code is hard and tedious work
| [Thursday 03 March 2011] [07:19:32] <jsimmons>	backporting sucks everywhere
| [Thursday 03 March 2011] [07:19:33] <pieterh>	it gets much worse if you consider a 'release' to include multiple projects
| [Thursday 03 March 2011] [07:19:56] <Steve-o>	I did it once for you guys with pgm 5.0, not again :/
| [Thursday 03 March 2011] [07:20:25] <jsimmons>	forwardport dont go backwards :D
| [Thursday 03 March 2011] [07:20:50] <Steve-o>	I only maintain critical fixes to old branches now
| [Thursday 03 March 2011] [07:20:52] <pieterh>	well, the way I see it, someone *wants* fix X on version Y
| [Thursday 03 March 2011] [07:20:59] <pieterh>	customer needs it, perhaps
| [Thursday 03 March 2011] [07:21:05] <pieterh>	so the backport has an economic basis
| [Thursday 03 March 2011] [07:21:20] <Steve-o>	which is what support contracts are about
| [Thursday 03 March 2011] [07:21:24] <pieterh>	yes
| [Thursday 03 March 2011] [07:22:06] <pieterh>	my goal with 2.0 and 2.1 is to accept and manage backports provided by people who *want* them to be in a specific released version
| [Thursday 03 March 2011] [07:22:55] <pieterh>	so, sustrik, my question was really "do you *want* 184bdb8 to go into 2.0.x?"
| [Thursday 03 March 2011] [07:24:08] <Guthur>	surely it a customer wants a new feature you say 'upgrade'
| [Thursday 03 March 2011] [07:27:11] <Steve-o>	Looks like mikko not about today?
| [Thursday 03 March 2011] [07:30:07] <private_meta>	pieterh: A question about zmsg_recv in the zmsg.[h|class] file. You exit the entire application if a message isn't received, is that intentional?
| [Thursday 03 March 2011] [07:30:23] <pieterh>	private_meta: nope, I've changed that, just now
| [Thursday 03 March 2011] [07:30:29] <private_meta>	oh
| [Thursday 03 March 2011] [07:30:31] <pieterh>	it should return NULL
| [Thursday 03 March 2011] [07:30:34] <private_meta>	ok
| [Thursday 03 March 2011] [07:30:54] <private_meta>	I'll think of something equivalent in C++
| [Thursday 03 March 2011] [07:37:20] <sustrik>	pieterh: it would be nice if someone backported it
| [Thursday 03 March 2011] [07:38:03] <pieterh>	sustrik: that's what I felt but someone has to want to, enough to do it, and then convince the maintainer (me) to accept the patch
| [Thursday 03 March 2011] [07:38:11] <pieterh>	it's the same workflow for all projects, right?
| [Thursday 03 March 2011] [07:38:46] <pieterh>	I think there are compromises possible here...
| [Thursday 03 March 2011] [07:38:59] <sustrik>	yes, i think so
| [Thursday 03 March 2011] [07:38:59] <pieterh>	for example, I'm happy to test a release heavily before it goes out
| [Thursday 03 March 2011] [07:39:08] <pieterh>	but that demands proper test cases for every (new) patch
| [Thursday 03 March 2011] [07:39:20] <sustrik>	right, lot of work
| [Thursday 03 March 2011] [07:39:21] <pieterh>	I'm happy to coordinate with mikko to ensure the rc builds
| [Thursday 03 March 2011] [07:39:28] <pieterh>	divide the work, then it's not so much
| [Thursday 03 March 2011] [07:39:49] <pieterh>	the only thing I totally refuse to do is patch code I did not write
| [Thursday 03 March 2011] [07:40:15] <pieterh>	not in stable production releases 
| [Thursday 03 March 2011] [07:40:19] <sustrik>	so no  backports?
| [Thursday 03 March 2011] [07:40:26] <pieterh>	again: divide the work
| [Thursday 03 March 2011] [07:40:37] <sustrik>	then i would suggest dropping the stable repos and using tags on master instead
| [Thursday 03 March 2011] [07:40:37] <pieterh>	author of code can confidently do a backport if there is incentive
| [Thursday 03 March 2011] [07:40:41] <pieterh>	sigh
| [Thursday 03 March 2011] [07:40:54] <sustrik>	ah, yes, sure
| [Thursday 03 March 2011] [07:41:15] <pieterh>	if you insist on mixing the two roles, we're going to get badly stuck
| [Thursday 03 March 2011] [07:41:25] <pieterh>	that's MHO
| [Thursday 03 March 2011] [07:41:31] <pieterh>	s/you/we/
| [Thursday 03 March 2011] [07:42:21] <pieterh>	look, you provide me with a patch to 2.1, it applies cleanly, ok
| [Thursday 03 March 2011] [07:42:30] <pieterh>	I'm still going to test the thing before it's released
| [Thursday 03 March 2011] [07:42:48] <pieterh>	but you can't assume I know the code well enough to do that manualluy
| [Thursday 03 March 2011] [07:42:50] <pieterh>	*manually
| [Thursday 03 March 2011] [07:42:58] <pieterh>	so there must also be proper test cases for new patches
| [Thursday 03 March 2011] [07:43:05] <pieterh>	all of this makes it possible to scale
| [Thursday 03 March 2011] [07:43:30] <pieterh>	if you depend on unique people able to do *everything*, you cannot scale
| [Thursday 03 March 2011] [07:43:45] <pieterh>	s/you/we/
| [Thursday 03 March 2011] [07:43:57] <sustrik>	ok, let me explain my pov
| [Thursday 03 March 2011] [07:44:02] <pieterh>	shoot
| [Thursday 03 March 2011] [07:44:08] <sustrik>	it's a problem of cost
| [Thursday 03 March 2011] [07:44:21] <sustrik>	the process we've had before was the minimal-cost process
| [Thursday 03 March 2011] [07:44:29] <pieterh>	in what sense was is cheap before?
| [Thursday 03 March 2011] [07:44:36] <pieterh>	*it
| [Thursday 03 March 2011] [07:44:41] <sustrik>	no backporting
| [Thursday 03 March 2011] [07:44:51] <sustrik>	there was maint
| [Thursday 03 March 2011] [07:45:01] <pieterh>	well, there should have been backporting of critical fixes
| [Thursday 03 March 2011] [07:45:04] <sustrik>	the patches to maint were upstreamed to master
| [Thursday 03 March 2011] [07:45:09] <sustrik>	but not other way round
| [Thursday 03 March 2011] [07:45:21] <pieterh>	... ok, and how often did that happen?
| [Thursday 03 March 2011] [07:45:28] <pieterh>	last fix to maint was 1 december afaict
| [Thursday 03 March 2011] [07:45:42] <sustrik>	rarely
| [Thursday 03 March 2011] [07:45:42] <sustrik>	that's why the cost was low
| [Thursday 03 March 2011] [07:45:47] <pieterh>	the process was cheap because the process was never used
| [Thursday 03 March 2011] [07:45:49] <sustrik>	so the user was faced with following choice:
| [Thursday 03 March 2011] [07:45:53] <pieterh>	hey, I can do that now as well
| [Thursday 03 March 2011] [07:46:10] <pieterh>	and we can upstream today just as easily
| [Thursday 03 March 2011] [07:46:14] <pieterh>	it's no different
| [Thursday 03 March 2011] [07:46:19] <sustrik>	1. stay with maint, patch the problem there, submit the patch
| [Thursday 03 March 2011] [07:46:25] <sustrik>	2. move to master
| [Thursday 03 March 2011] [07:46:33] <pieterh>	1. stay with 2.0, patch the problem there, submit the patch
| [Thursday 03 March 2011] [07:46:44] <pieterh>	2. move to 2.1, patch the problem there, submit the patch
| [Thursday 03 March 2011] [07:46:49] <pieterh>	3. move to 2.2 master, etc...
| [Thursday 03 March 2011] [07:46:55] <sustrik>	yeah
| [Thursday 03 March 2011] [07:46:56] <pieterh>	it is exactly the same process
| [Thursday 03 March 2011] [07:47:06] <sustrik>	nope, it's unidirectional
| [Thursday 03 March 2011] [07:47:20] <pieterh>	ok, theoretical question
| [Thursday 03 March 2011] [07:47:36] <pieterh>	if someone provides a patch to 2.0, how does that get upstreamed?
| [Thursday 03 March 2011] [07:47:40] <pieterh>	who does that work?
| [Thursday 03 March 2011] [07:47:46] <sustrik>	myself
| [Thursday 03 March 2011] [07:48:01] <sustrik>	i'm maintainer of master
| [Thursday 03 March 2011] [07:48:10] <sustrik>	so i want it to be bug-free
| [Thursday 03 March 2011] [07:48:15] <pieterh>	but you're not following the old releases
| [Thursday 03 March 2011] [07:48:23] <pieterh>	how do you even know there was a change? 
| [Thursday 03 March 2011] [07:48:31] <sustrik>	so if someone finds a bug in maint and submits a patch
| [Thursday 03 March 2011] [07:48:34] <sustrik>	i want it to get to master
| [Thursday 03 March 2011] [07:48:41] <sustrik>	all the patches flew via myself
| [Thursday 03 March 2011] [07:48:48] <pieterh>	ah
| [Thursday 03 March 2011] [07:48:53] <pieterh>	so you also maintain maint?
| [Thursday 03 March 2011] [07:49:08] <pieterh>	and if there are three branches, you maintain all 3?
| [Thursday 03 March 2011] [07:49:41] <pieterh>	afaics we agree on the problem and the solution
| [Thursday 03 March 2011] [07:50:04] <sustrik>	'maintain' in terms of applying patches that i get from other people
| [Thursday 03 March 2011] [07:50:20] <pieterh>	yes, but you don't want to get patches to old versions, do you
| [Thursday 03 March 2011] [07:50:27] <pieterh>	because that makes you maintainer of those
| [Thursday 03 March 2011] [07:50:43] <sustrik>	git apply
| [Thursday 03 March 2011] [07:50:46] <sustrik>	git commit
| [Thursday 03 March 2011] [07:50:50] <sustrik>	git push
| [Thursday 03 March 2011] [07:50:59] <sustrik>	easy
| [Thursday 03 March 2011] [07:51:23] <pieterh>	that assumes the patch is tested and perfect
| [Thursday 03 March 2011] [07:51:28] <pieterh>	ok, let's assume that
| [Thursday 03 March 2011] [07:51:32] <sustrik>	yes, that's up to submitter
| [Thursday 03 March 2011] [07:51:44] <pieterh>	so we do the same today, except you don't have to do that
| [Thursday 03 March 2011] [07:51:54] <pieterh>	the patch must be tested and perfect
| [Thursday 03 March 2011] [07:52:10] <pieterh>	then *anyone* who follows the process can apply/commit/push
| [Thursday 03 March 2011] [07:52:19] <pieterh>	does not require your time
| [Thursday 03 March 2011] [07:52:30] <pieterh>	that then becomes scalable
| [Thursday 03 March 2011] [07:52:56] <sustrik>	it's up to you what process you use for stable branches
| [Thursday 03 March 2011] [07:53:04] <pieterh>	and if the patch is not perfect, you don't want to be fixing up old branches, do you
| [Thursday 03 March 2011] [07:53:14] <pieterh>	retesting 2.0?
| [Thursday 03 March 2011] [07:53:44] <pieterh>	so what we've done with the separate gits, and why we both like it
| [Thursday 03 March 2011] [07:54:01] <pieterh>	is that you have delegated the grunt work of applying *perfect* patches to old versions
| [Thursday 03 March 2011] [07:54:18] <pieterh>	followed by documentation, release packaging, uploading, emails, etc. etc.
| [Thursday 03 March 2011] [07:54:28] <pieterh>	ack?
| [Thursday 03 March 2011] [07:54:43] <pieterh>	second aspect is upstream vs. downstream
| [Thursday 03 March 2011] [07:55:00] <pieterh>	totally orthogonal, this applies equally if we had 1 repo or 3 repos
| [Thursday 03 March 2011] [07:55:02] <sustrik>	yeah, i've delegated hat work to you
| [Thursday 03 March 2011] [07:55:09] <sustrik>	now i don't care about it amymore
| [Thursday 03 March 2011] [07:55:11] <pieterh>	yes, and that is a big improvement
| [Thursday 03 March 2011] [07:55:22] <sustrik>	life is beautiful now :)
| [Thursday 03 March 2011] [07:55:33] <pieterh>	well, that is what I call a saving in time and cost
| [Thursday 03 March 2011] [07:55:51] <pieterh>	so now we look at the orthogonal issue of up/down streaming
| [Thursday 03 March 2011] [07:56:24] <pieterh>	as maintainer, I'll accept *perfect* patches from anyone I trust
| [Thursday 03 March 2011] [07:57:15] <pieterh>	I don't necessarily see 2.0 as downstream from 2.1, they act as two independent projects, almost
| [Thursday 03 March 2011] [07:57:34] <sustrik>	sure, it's up to you
| [Thursday 03 March 2011] [07:58:46] <pieterh>	do you understand why I want to separate the role of coding from release management?
| [Thursday 03 March 2011] [07:58:58] <ianbarber>	in that process there must be an agent who wants a patch from <new version> in <maintenance version> and is willing to do the work to test and submit the perfect patch. But, the people most likely to be trusted by the maintainer are also mostly likely to be working on the later/latest versions, I would guess. 
| [Thursday 03 March 2011] [07:59:28] <ianbarber>	and the people that are on the older versions don't necessarily have the awareness that there are improvements that would benefit them
| [Thursday 03 March 2011] [07:59:30] <pieterh>	ianbarber: to a point, but if we are smarter, it scales better
| [Thursday 03 March 2011] [07:59:40] <pieterh>	for example, better test cases
| [Thursday 03 March 2011] [07:59:46] <ianbarber>	yeah
| [Thursday 03 March 2011] [07:59:47] <sustrik>	it's hard to get someone to do that kind of work
| [Thursday 03 March 2011] [07:59:59] <sustrik>	linux has GregKH
| [Thursday 03 March 2011] [07:59:59] <pieterh>	sustrik: there has to be an economic incentive in every case
| [Thursday 03 March 2011] [07:59:59] <ianbarber>	better test cases would let you apply patches more speculatively
| [Thursday 03 March 2011] [08:00:13] <ianbarber>	if you could know things will shout if you break stuff
| [Thursday 03 March 2011] [08:00:13] <sustrik>	but i would guess people like that are pretty rare
| [Thursday 03 March 2011] [08:00:31] <pieterh>	ianbarber: indeed, I'd rather trust a test case I can understand than someone's patch
| [Thursday 03 March 2011] [08:00:46] <ianbarber>	definitely. 
| [Thursday 03 March 2011] [08:00:47] <pieterh>	sustrik: not only rare, but counter-productive in the end
| [Thursday 03 March 2011] [08:00:54] <pieterh>	if you know too much, you cut corners
| [Thursday 03 March 2011] [08:01:25] 	 * sustrik doesn't follow
| [Thursday 03 March 2011] [08:01:28] <pieterh>	being naive forces better process in many cases
| [Thursday 03 March 2011] [08:01:40] <pieterh>	e.g. I don't know the internals so I insist on better test cases
| [Thursday 03 March 2011] [08:01:42] <sustrik>	having a dedicated maintainer of stable is counter-productive?
| [Thursday 03 March 2011] [08:01:51] <pieterh>	if I know the code really well, I won't use test cases
| [Thursday 03 March 2011] [08:02:02] <pieterh>	and the product and process will suffer (this has already happened a lot)
| [Thursday 03 March 2011] [08:02:30] <pieterh>	sustrik: you say "maintainer" to mean two different things in my view
| [Thursday 03 March 2011] [08:02:50] <pieterh>	I am the dedicated maintainer but not in the sense of "I own the code"
| [Thursday 03 March 2011] [08:02:55] <pieterh>	I own the release and the process
| [Thursday 03 March 2011] [08:03:04] <pieterh>	the code is owned by its authors
| [Thursday 03 March 2011] [08:03:27] <sustrik>	maintainer in terms of "i am willing to spend all my free time to maintain stable"
| [Thursday 03 March 2011] [08:03:34] <pieterh>	define "maintain" please
| [Thursday 03 March 2011] [08:03:34] <sustrik>	that's pretty rare i would say :)
| [Thursday 03 March 2011] [08:04:18] <pieterh>	look, I maintain the Guide, yes?
| [Thursday 03 March 2011] [08:04:46] <pieterh>	that is, I'm responsible for the repository, publishing it, and I write the text
| [Thursday 03 March 2011] [08:04:57] <pieterh>	but every set of translations has their authors
| [Thursday 03 March 2011] [08:05:03] <pieterh>	they own that code
| [Thursday 03 March 2011] [08:05:09] <pieterh>	I don't maintain it
| [Thursday 03 March 2011] [08:05:10] <sustrik>	this discussion is pointless
| [Thursday 03 March 2011] [08:05:21] <sustrik>	the process in stable is entirely up to you
| [Thursday 03 March 2011] [08:05:27] 	 * sustrik shuts up
| [Thursday 03 March 2011] [08:05:45] <pieterh>	if you want that patch to go into 2.0, send it my way, thanks
| [Thursday 03 March 2011] [08:05:52] 	 * pieterh goes back to work
| [Thursday 03 March 2011] [08:05:57] <Guthur>	pieterh: Do you think it would be nice to have some readily available statistic of the guide example coverage for each language binding?
| [Thursday 03 March 2011] [08:06:07] <pieterh>	Gurthur: hang on...
| [Thursday 03 March 2011] [08:06:23] <Guthur>	it's ok i'm not going anywhere soon
| [Thursday 03 March 2011] [08:06:38] <Guthur>	hehe, and I know you guys are having a heated debate
| [Thursday 03 March 2011] [08:06:43] <pieterh>	Translations (48 in total):
| [Thursday 03 March 2011] [08:06:43] <pieterh>	Ada               0,   0%
| [Thursday 03 March 2011] [08:06:43] <pieterh>	Basic             0,   0%
| [Thursday 03 March 2011] [08:06:43] <pieterh>	C                48, 100%
| [Thursday 03 March 2011] [08:06:43] <pieterh>	C++              33,  68%
| [Thursday 03 March 2011] [08:06:43] <pieterh>	C#               26,  54%
| [Thursday 03 March 2011] [08:06:43] <pieterh>	Common Lisp      32,  66%
| [Thursday 03 March 2011] [08:06:44] <pieterh>	Erlang            0,   0%
| [Thursday 03 March 2011] [08:06:44] <pieterh>	Go                2,   4%
| [Thursday 03 March 2011] [08:06:45] <pieterh>	Haskell           0,   0%
| [Thursday 03 March 2011] [08:06:45] <pieterh>	Java             17,  35%
| [Thursday 03 March 2011] [08:06:46] <pieterh>	Lua               0,   0%
| [Thursday 03 March 2011] [08:06:46] <pieterh>	Objective-C       0,   0%
| [Thursday 03 March 2011] [08:06:47] <pieterh>	ooc               0,   0%
| [Thursday 03 March 2011] [08:06:57] <Guthur>	oh whao
| [Thursday 03 March 2011] [08:07:07] <Guthur>	I wasn't expecting there to be any
| [Thursday 03 March 2011] [08:07:54] <Guthur>	Would that be worth making visible, do you think?
| [Thursday 03 March 2011] [08:08:02] <pieterh>	where?
| [Thursday 03 March 2011] [08:08:17] <Guthur>	top of the guide maybe
| [Thursday 03 March 2011] [08:08:23] <pieterh>	hang on...
| [Thursday 03 March 2011] [08:08:42] <pieterh>	I'll post it next time I do an update, if I remember
| [Thursday 03 March 2011] [08:08:47] <Guthur>	cool
| [Thursday 03 March 2011] [08:09:02] <Guthur>	I need to bump that C# number up a bit, hehe
| [Thursday 03 March 2011] [08:21:00] <private_meta>	pieterh: about zmsg, is it made to cater other types but standard character strings?
| [Thursday 03 March 2011] [08:21:13] <pieterh>	nope
| [Thursday 03 March 2011] [08:21:30] <pieterh>	this is not meant to be production code, it's for the examples
| [Thursday 03 March 2011] [08:21:51] <private_meta>	pieterh: in the dump function you differ between non-character blob and string, that's why I ask
| [Thursday 03 March 2011] [08:22:12] <pieterh>	yes, because a socket can get anything
| [Thursday 03 March 2011] [08:22:26] <pieterh>	the class *could* be expanded to allow binary message parts
| [Thursday 03 March 2011] [08:22:38] <pieterh>	but that gets complex quickly, and was not worth it for here
| [Thursday 03 March 2011] [08:22:51] <pieterh>	I'd do it in zfl_msg, which is a more serious implementation
| [Thursday 03 March 2011] [08:23:14] <private_meta>	hmm ok. If it were string only, i would use std::string and the implementation would be a little more clean
| [Thursday 03 March 2011] [08:23:37] <private_meta>	but the example should follow the same functionality as the C version i guess
| [Thursday 03 March 2011] [08:24:49] <pieterh>	you can implement it any way you like, I'd suggest keeping the API similar so people can follow
| [Thursday 03 March 2011] [08:25:21] <pieterh>	the methods that muck with envelopes... wrap/unwrap/push/ etc.
| [Thursday 03 March 2011] [09:38:36] <guido_g>	pieterh: ping?
| [Thursday 03 March 2011] [09:38:44] <pieterh>	hi guido_g
| [Thursday 03 March 2011] [09:38:56] <guido_g>	question about mdp spec
| [Thursday 03 March 2011] [09:39:00] <pieterh>	shoot
| [Thursday 03 March 2011] [09:39:16] <guido_g>	worker send ready message to broker
| [Thursday 03 March 2011] [09:39:25] <guido_g>	there will be no response to that, right?
| [Thursday 03 March 2011] [09:39:35] <pieterh>	there is a response but it's not immediate
| [Thursday 03 March 2011] [09:39:41] <pieterh>	it's the lru pattern
| [Thursday 03 March 2011] [09:40:01] <guido_g>	i'm talking about the ready message
| [Thursday 03 March 2011] [09:40:03] <pieterh>	worker waits, indefinitely, for a client request to arrive, that's the response
| [Thursday 03 March 2011] [09:40:07] <guido_g>	from the worker
| [Thursday 03 March 2011] [09:40:13] <guido_g>	to the broker
| [Thursday 03 March 2011] [09:40:17] <guido_g>	aka handshake
| [Thursday 03 March 2011] [09:40:32] <guido_g>	ok, half of a handshake
| [Thursday 03 March 2011] [09:40:40] <pieterh>	yes, I do understand what you are asking
| [Thursday 03 March 2011] [09:40:47] <pieterh>	it is the lru pattern
| [Thursday 03 March 2011] [09:41:12] <guido_g>	i can't find any answer to the ready message is the spec
| [Thursday 03 March 2011] [09:41:18] <guido_g>	*in the spec
| [Thursday 03 March 2011] [09:41:20] <pieterh>	there is no answer to the ready spec, as such
| [Thursday 03 March 2011] [09:41:26] <pieterh>	the first REQUEST is the answer
| [Thursday 03 March 2011] [09:41:31] <guido_g>	ahh we're getting closer
| [Thursday 03 March 2011] [09:41:38] <pieterh>	a DISCONNECT would be a negative acknowledgement
| [Thursday 03 March 2011] [09:41:53] <pieterh>	sorry, when I say "lru pattern" does that make any sense?
| [Thursday 03 March 2011] [09:42:03] <guido_g>	ok, so till a request arrives the woker does not know if the broker has his service registered correctly, right?
| [Thursday 03 March 2011] [09:42:34] <guido_g>	no it doesn't, because we're on mdp protcol level
| [Thursday 03 March 2011] [09:42:42] <pieterh>	it can safely assume all is OK unless it (a) gets a disconnect or (b) no heartbeat within whatever time
| [Thursday 03 March 2011] [09:43:06] <pieterh>	ok, good point, I'll add this explicitly
| [Thursday 03 March 2011] [09:43:41] <guido_g>	so a received hb from the broker will count as "registration is fine"
| [Thursday 03 March 2011] [09:44:09] <guido_g>	so we need a basic timeout value for the handshake
| [Thursday 03 March 2011] [09:44:26] <guido_g>	or a dedicated "got your ready" reply
| [Thursday 03 March 2011] [09:45:48] <pieterh>	what is the value of a dedicated "OK" command?
| [Thursday 03 March 2011] [09:46:02] <pieterh>	I'm not against it, but it seems unnecessary
| [Thursday 03 March 2011] [09:46:53] <guido_g>	the value would be that the worker from this point on knows that his service is registered and he does receive heartbeats etc.
| [Thursday 03 March 2011] [09:47:32] <pieterh>	what is the value of the worker knowing?
| [Thursday 03 March 2011] [09:47:46] <guido_g>	would allow for small timeouts in the handshake phase
| [Thursday 03 March 2011] [09:47:54] <pieterh>	I'm being serious, remember we're on disconnected TCP
| [Thursday 03 March 2011] [09:48:01] <pieterh>	so the broker can arrive 30 minutes late
| [Thursday 03 March 2011] [09:48:25] <pieterh>	do we want to break that? I'd rather not, it's valuable
| [Thursday 03 March 2011] [09:48:49] <guido_g>	wouldn't break that, just needs a longer timeout
| [Thursday 03 March 2011] [09:48:56] <pieterh>	which is the heartbeat
| [Thursday 03 March 2011] [09:49:05] <guido_g>	right
| [Thursday 03 March 2011] [09:49:11] <pieterh>	so you don't need a positive ack
| [Thursday 03 March 2011] [09:49:24] <guido_g>	but not the "i'm ok" hb, but the one for the connection handshake
| [Thursday 03 March 2011] [09:49:25] <pieterh>	a negative ack gives you just the same semantics
| [Thursday 03 March 2011] [09:50:15] <guido_g>	example: no broker , worker starts, broker comes 30 seconds later
| [Thursday 03 March 2011] [09:50:25] <guido_g>	general hb interval is 1 sec
| [Thursday 03 March 2011] [09:50:35] <guido_g>	client died due to lots of missed hbs
| [Thursday 03 March 2011] [09:50:38] <pieterh>	worker will reconnect over and over and eventually get a HB back
| [Thursday 03 March 2011] [09:50:46] <pieterh>	clients have different timescales
| [Thursday 03 March 2011] [09:51:07] <pieterh>	the client could easily retry like the worker does
| [Thursday 03 March 2011] [09:51:17] <pieterh>	that's not MDP's problem
| [Thursday 03 March 2011] [09:51:27] <guido_g>	shit, s/client/worker/
| [Thursday 03 March 2011] [09:51:42] <pieterh>	worker does not die, if you look at my API
| [Thursday 03 March 2011] [09:51:45] <guido_g>	again
| [Thursday 03 March 2011] [09:52:00] <pieterh>	it keeps reconnecting forever (or until Ctrl-C in my latest code)
| [Thursday 03 March 2011] [09:52:03] <guido_g>	i do look at the spec
| [Thursday 03 March 2011] [09:52:12] <pieterh>	right
| [Thursday 03 March 2011] [09:52:43] <pieterh>	"If the worker detects that the broker has disconnected, it MUST restart a new conversation."
| [Thursday 03 March 2011] [09:52:55] <pieterh>	I'm not sure that's accurate
| [Thursday 03 March 2011] [09:52:58] <guido_g>	ok
| [Thursday 03 March 2011] [09:53:17] <pieterh>	but it allows the broker to kick workers that come in without doing 'ready'
| [Thursday 03 March 2011] [09:53:29] <guido_g>	would mean: after x missed hbs close socket and start from the beginning
| [Thursday 03 March 2011] [09:53:33] <pieterh>	yes
| [Thursday 03 March 2011] [09:53:47] <pieterh>	"Both broker and worker MUST send heartbeats at regular and agreed-upon intervals. A peer can consider the other peer "disconnected" if no heartbeat arrives within some multiple of that interval (usually 3-5)."
| [Thursday 03 March 2011] [09:53:48] <guido_g>	ok, i'll implement it that way
| [Thursday 03 March 2011] [09:53:57] <pieterh>	s/can/SHOULD/
| [Thursday 03 March 2011] [09:54:14] <guido_g>	MUST even
| [Thursday 03 March 2011] [09:54:25] <guido_g>	otherwise the whole thing would be useless
| [Thursday 03 March 2011] [09:54:52] <guido_g>	i'll start the hb timer after sending the ready message then
| [Thursday 03 March 2011] [09:55:06] <pieterh>	ack, MUST it is
| [Thursday 03 March 2011] [09:55:37] <guido_g>	fine
| [Thursday 03 March 2011] [09:55:43] <pieterh>	I need to reboot this box, it's starting to act funny
| [Thursday 03 March 2011] [09:55:51] <pieterh>	cy in a minute or two
| [Thursday 03 March 2011] [09:55:55] <guido_g>	np
| [Thursday 03 March 2011] [09:59:10] <pieter_hintjens>	back
| [Thursday 03 March 2011] [09:59:18] <pieter_hintjens>	what did I miss? :-)
| [Thursday 03 March 2011] [10:00:11] <cremes>	is your new laptop with the ssd giving you fits?
| [Thursday 03 March 2011] [10:01:40] <pieter_hintjens>	cremes: it all works... :-)
| [Thursday 03 March 2011] [10:01:46] <pieter_hintjens>	it's silent and uses a little less power, and it's faster
| [Thursday 03 March 2011] [10:01:54] <guido_g>	pieter_hintjens: why are you talking about missing x hbs? why not simply set the hb interval and barf if one is missed?
| [Thursday 03 March 2011] [10:02:13] <pieter_hintjens>	guido_g: bitter experience
| [Thursday 03 March 2011] [10:02:19] <guido_g>	uh
| [Thursday 03 March 2011] [10:02:43] <guido_g>	could you explain that a bit?
| [Thursday 03 March 2011] [10:02:55] <pieter_hintjens>	it's relatively easy to miss single HBs due to the two peers each sending out at intervals
| [Thursday 03 March 2011] [10:03:15] <pieter_hintjens>	it's also relatively easy to get them delayed when there's congestion
| [Thursday 03 March 2011] [10:03:32] <pieter_hintjens>	we did extensive testing of this for AMQP
| [Thursday 03 March 2011] [10:04:22] <pieter_hintjens>	you basically really do not want false positives
| [Thursday 03 March 2011] [10:04:39] 	 * pieter_hintjens is not being very clear...
| [Thursday 03 March 2011] [10:04:52] <guido_g>	ah its ok
| [Thursday 03 March 2011] [10:04:59] <pieter_hintjens>	try it yourself, set the liveness to 1, run it in real use
| [Thursday 03 March 2011] [10:07:08] <guido_g>	so basically the hb interval is the max. time w/o a message divided by the liveness as you call it
| [Thursday 03 March 2011] [10:07:33] <pieter_hintjens>	yes
| [Thursday 03 March 2011] [10:07:52] <pieter_hintjens>	this is a simpleminded design, I'm sure we can do better over time
| [Thursday 03 March 2011] [10:08:01] <guido_g>	me too :)
| [Thursday 03 March 2011] [10:08:12] <pieter_hintjens>	here's one key aspect...
| [Thursday 03 March 2011] [10:08:18] <pieter_hintjens>	say the clock is 1 second
| [Thursday 03 March 2011] [10:08:30] <pieter_hintjens>	and a HB comes in at 1.001 seconds
| [Thursday 03 March 2011] [10:08:36] <pieter_hintjens>	and your liveness is 1
| [Thursday 03 March 2011] [10:08:45] <pieter_hintjens>	you now disconnect
| [Thursday 03 March 2011] [10:09:00] <pieter_hintjens>	so liveness must be at least 2 to allow for fractional delays in HBs
| [Thursday 03 March 2011] [10:09:03] <guido_g>	you have to draw the border somwwhere
| [Thursday 03 March 2011] [10:09:08] <guido_g>	*somewhere
| [Thursday 03 March 2011] [10:09:22] <pieter_hintjens>	what border?
| [Thursday 03 March 2011] [10:09:36] <guido_g>	connection alive or not
| [Thursday 03 March 2011] [10:09:37] <pieter_hintjens>	yes, how delayed can a HB be...
| [Thursday 03 March 2011] [10:09:49] <pieter_hintjens>	if it's 0.1% delayed, that's not a dead peer
| [Thursday 03 March 2011] [10:09:50] <guido_g>	infinite?
| [Thursday 03 March 2011] [10:10:01] <pieter_hintjens>	if it's infinite, you don't have heartbeating any more
| [Thursday 03 March 2011] [10:10:05] <guido_g>	by a femto second?
| [Thursday 03 March 2011] [10:10:16] <pieter_hintjens>	by a couple of heartbeats, is the best answer we found
| [Thursday 03 March 2011] [10:10:59] <pieter_hintjens>	it's like your own heart can miss one beat, two if you're really shocked, but three means you're dead
| [Thursday 03 March 2011] [10:11:34] <guido_g>	this is more a problem of how to define the border between alive and not
| [Thursday 03 March 2011] [10:12:06] <pieter_hintjens>	yes, and it's a heuristic you can't really make until you have real apps
| [Thursday 03 March 2011] [10:12:13] <guido_g>	you get the same problem when counting hbs
| [Thursday 03 March 2011] [10:12:15] <pieter_hintjens>	that's why it's configurable in my latest api
| [Thursday 03 March 2011] [10:12:43] <guido_g>	ok
| [Thursday 03 March 2011] [10:13:13] <guido_g>	i'll implement that as a simple counter decremented by a periodically called method
| [Thursday 03 March 2011] [10:13:40] <guido_g>	so one can adjust the interval and the count as he/she/it sees fit
| [Thursday 03 March 2011] [10:19:34] <pieter_hintjens>	kiss...
| [Thursday 03 March 2011] [10:19:40] <guido_g>	thanks :)
| [Thursday 03 March 2011] [10:19:43] <pieter_hintjens>	it just has to detect real failure
| [Thursday 03 March 2011] [10:19:50] <pieter_hintjens>	 :-)
| [Thursday 03 March 2011] [10:20:46] <guido_g>	i need to read http://www.tldp.org/HOWTO/html_single/TCP-Keepalive-HOWTO/ 
| [Thursday 03 March 2011] [10:24:58] <pieter_hintjens>	guido_g: there may also be some threads on the websocket heartbeating discussions
| [Thursday 03 March 2011] [10:27:28] <guido_g>	first i'll implement the simple version
| [Thursday 03 March 2011] [10:32:11] <sustrik>	guido_g: tcp's keepalives in just a afterthought
| [Thursday 03 March 2011] [10:32:30] <sustrik>	even explictly discouraged by the spec
| [Thursday 03 March 2011] [10:32:36] <guido_g>	ah ok
| [Thursday 03 March 2011] [10:32:50] <sustrik>	if you want to read about sane heartbeating mechanism, have a look at SCTP heartbeats
| [Thursday 03 March 2011] [10:32:56] <guido_g>	one tab less open in the browser then :)
| [Thursday 03 March 2011] [10:33:48] <guido_g>	ok, will do, but later
| [Thursday 03 March 2011] [10:33:56] <sustrik>	just a tip :)
| [Thursday 03 March 2011] [11:00:18] <ok2>	hi!
| [Thursday 03 March 2011] [11:02:02] <ok2>	question, how can i see with zmq, on send() that the other end is not here anymore?
| [Thursday 03 March 2011] [11:02:23] <ok2>	zmq simply hangs for me, if the other side crashes
| [Thursday 03 March 2011] [11:05:35] <cremes>	ok2: you need to use zmq_poll(), zmq_send() with ZM_NOBLOCK and setup your own timeout logic
| [Thursday 03 March 2011] [11:06:13] <cremes>	there is some work being done to wrap up this pattern (it gets asked about a lot)
| [Thursday 03 March 2011] [11:06:34] <cremes>	but i have no idea what the status is on that work
| [Thursday 03 March 2011] [11:06:59] <cremes>	i've built this myself but using ruby instead of C
| [Thursday 03 March 2011] [11:08:36] <ok2>	it means that i make zmq_poll(x, NOBLOCK) and wait on zmq_poll for POLLOUT?
| [Thursday 03 March 2011] [11:08:46] <ok2>	zmq_send(x, NONBLOCK)
| [Thursday 03 March 2011] [11:09:08] <ok2>	no, on POLLERR ...
| [Thursday 03 March 2011] [11:20:57] <cremes>	ok2: no, that isn't correct
| [Thursday 03 March 2011] [11:21:27] <cremes>	let's say you are using a req/rep socket pair and you want to timeout on the request 
| [Thursday 03 March 2011] [11:21:43] <cremes>	you would do something like:
| [Thursday 03 March 2011] [11:22:25] <cremes>	zmq_send(req_socket, message, ZM_NOBLOCK)
| [Thursday 03 March 2011] [11:22:46] <cremes>	register req_socket with zmq_poll()
| [Thursday 03 March 2011] [11:23:18] <cremes>	and POLLIN (you are looking for a reply, so that will be a recv operation)
| [Thursday 03 March 2011] [11:24:10] <cremes>	when req_socket returns POLLIN, call zmq_recv(req_socket, replymsg, 0)
| [Thursday 03 March 2011] [11:24:15] <cremes>	OR
| [Thursday 03 March 2011] [11:24:33] <cremes>	generate an application error if your timeout has expired before req_socket returns POLLIN
| [Thursday 03 March 2011] [11:24:39] <cremes>	make sense?
| [Thursday 03 March 2011] [11:39:30] <pieter_hintjens>	ok2: it's explained here: http://zguide.zeromq.org/page:all#toc68
| [Thursday 03 March 2011] [11:42:15] <guido_g>	pieter_hintjens: any chance that the frame order in spec:7 is wrong?
| [Thursday 03 March 2011] [11:42:26] <pieter_hintjens>	where exactly?
| [Thursday 03 March 2011] [11:42:48] <guido_g>	given that the broker is a XREQ type, it needs to prepend the target identity
| [Thursday 03 March 2011] [11:42:55] <pieter_hintjens>	guido_g: you know, I'm so pleased to see you implementing this 
| [Thursday 03 March 2011] [11:43:08] <guido_g>	sarcasm?
| [Thursday 03 March 2011] [11:43:16] <pieter_hintjens>	no
| [Thursday 03 March 2011] [11:43:20] <guido_g>	puh
| [Thursday 03 March 2011] [11:43:24] <guido_g>	:)
| [Thursday 03 March 2011] [11:43:42] <pieter_hintjens>	seriously, it's magic to see someone implement a spec the day after it's published
| [Thursday 03 March 2011] [11:43:49] <pieter_hintjens>	what command are you looking at?
| [Thursday 03 March 2011] [11:44:33] <guido_g>	worker <-> broker
| [Thursday 03 March 2011] [11:44:50] <guido_g>	broker is XREQ
| [Thursday 03 March 2011] [11:44:58] <pieter_hintjens>	this is why all the framing says "on the wire"
| [Thursday 03 March 2011] [11:45:10] <guido_g>	pardon?
| [Thursday 03 March 2011] [11:45:29] <pieter_hintjens>	when you send a message to a router socket you always prepend the address
| [Thursday 03 March 2011] [11:45:33] <pieter_hintjens>	but that does not go on the wire
| [Thursday 03 March 2011] [11:45:41] <pieter_hintjens>	it's not sent, thus is not relevant to the protocol
| [Thursday 03 March 2011] [11:45:56] <pieter_hintjens>	however I'll explain this, it's confusing
| [Thursday 03 March 2011] [11:46:01] <guido_g>	it is
| [Thursday 03 March 2011] [11:53:15] <pieter_hintjens>	guido_g: ok, I've added a note, can you see if it's clear?
| [Thursday 03 March 2011] [11:53:25] <pieter_hintjens>	http://rfc.zeromq.org/spec:7#toc11
| [Thursday 03 March 2011] [11:55:11] <guido_g>	GREAT!
| [Thursday 03 March 2011] [12:01:43] <guido_g>	getting close now
| [Thursday 03 March 2011] [12:01:47] <guido_g>	*closer
| [Thursday 03 March 2011] [12:03:43] <ok2>	cremes and pieter_hintjens: thank you very much, i think i got what i need :-)
| [Thursday 03 March 2011] [12:03:52] <pieter_hintjens>	ok2, np
| [Thursday 03 March 2011] [12:05:02] <guido_g>	first success for the worker
| [Thursday 03 March 2011] [12:09:42] <pieter_hintjens>	broker is tricky to get right
| [Thursday 03 March 2011] [12:10:01] <pieter_hintjens>	am still finding undispatched messages in some cases
| [Thursday 03 March 2011] [12:11:31] <guido_g>	so, short break and then testing my worker against your broker
| [Thursday 03 March 2011] [12:12:09] <pieter_hintjens>	I'll need to commit, almost ready
| [Thursday 03 March 2011] [12:12:28] <guido_g>	ok, no hurry
| [Thursday 03 March 2011] [12:24:00] <Altxp>	Hello there.
| [Thursday 03 March 2011] [12:36:31] <pieter_hintjens>	guido_g: ok, done
| [Thursday 03 March 2011] [12:36:44] <pieter_hintjens>	the broker is, afaict, complete and robust
| [Thursday 03 March 2011] [12:40:49] <pieter_hintjens>	I've pushed this to the website, and committed all the source code
| [Thursday 03 March 2011] [12:41:11] <djc>	okay, I have some questions with my distro hat on
| [Thursday 03 March 2011] [12:41:30] <djc>	are there options to rely on external openpgm instead of the bundled one?
| [Thursday 03 March 2011] [12:41:56] <djc>	what versions of openpgm are compatible with zeromq-2.1.1?
| [Thursday 03 March 2011] [12:42:22] <djc>	does zeromq actually depend on the xmlParser, or can that be disableD?
| [Thursday 03 March 2011] [12:45:22] <guido_g>	pieter_hintjens: thanks
| [Thursday 03 March 2011] [12:45:56] <guido_g>	after some phineas and ferb i'll check it out
| [Thursday 03 March 2011] [12:49:03] <private_meta>	pieter_hintjens: so it's basically finished?
| [Thursday 03 March 2011] [12:52:32] <guido_g>	pieter_hintjens: simple hb works
| [Thursday 03 March 2011] [12:54:08] <guido_g>	ahh my worker crashes when the broker is restarted
| [Thursday 03 March 2011] [13:08:17] <guido_g>	ha! works now
| [Thursday 03 March 2011] [13:24:53] Notice	-tomaw- [Global Notice] Hi all.  As you probably noticed we're experiencing some connectivity issues currently.  We're investigating options and will continue with any updates via wallops (/mode yournick +w to enable)
| [Thursday 03 March 2011] [13:52:56] <guido_g>	pieter_hintjens: python client and worker are running against your broker
| [Thursday 03 March 2011] [14:21:23] <yrashk>	according to our latest fixes to erlzmq tests, ezmq is still way faster
| [Thursday 03 March 2011] [15:07:28] <pieter_hintjens>	guido_g: I'm back... that's great!
| [Thursday 03 March 2011] [15:07:53] <pieter_hintjens>	private_meta: yes, it's finished for now
| [Thursday 03 March 2011] [15:11:36] <guido_g>	pieter_hintjens: wb
| [Thursday 03 March 2011] [15:11:59] <pieter_hintjens>	guido_g: I added you as contributor to the spec, if that's ok
| [Thursday 03 March 2011] [15:12:00] <guido_g>	small thing, the mdbroker segfaults sometimes :)
| [Thursday 03 March 2011] [15:12:08] <guido_g>	thanks
| [Thursday 03 March 2011] [15:12:14] <pieter_hintjens>	can you get me a backtrace?
| [Thursday 03 March 2011] [15:12:29] <pieter_hintjens>	or reproducible case
| [Thursday 03 March 2011] [15:12:29] <guido_g>	i'll try my best
| [Thursday 03 March 2011] [15:12:41] <travlr>	pieter_hintjens: hey pieter, how would suggest I implement a mail list service for an open source community project i'm ready to start?
| [Thursday 03 March 2011] [15:12:45] <pieter_hintjens>	ulimit -u
| [Thursday 03 March 2011] [15:12:46] <guido_g>	it's related to a worker beeing killed
| [Thursday 03 March 2011] [15:12:52] <pieter_hintjens>	and then you'll get core files
| [Thursday 03 March 2011] [15:13:02] <pieter_hintjens>	yeah, cleaning up dead workers is tricky
| [Thursday 03 March 2011] [15:13:18] <pieter_hintjens>	travlr: hmm... I'd avoid email lists altogether, personally
| [Thursday 03 March 2011] [15:13:23] <guido_g>	are your build scripts compiling w/ debug on?
| [Thursday 03 March 2011] [15:13:32] <pieter_hintjens>	guido_g: should be, now
| [Thursday 03 March 2011] [15:13:39] <pieter_hintjens>	try 'c -C' for sure
| [Thursday 03 March 2011] [15:13:54] <travlr>	pieter_hintjens: what might be your suggestion then.
| [Thursday 03 March 2011] [15:13:59] <pieter_hintjens>	travlr: you might take one of the wikis at http://irongiant.wikidot.com
| [Thursday 03 March 2011] [15:14:11] <pieter_hintjens>	that works well for community projects
| [Thursday 03 March 2011] [15:14:29] <pieter_hintjens>	forum + email alerts + wiki combinations
| [Thursday 03 March 2011] [15:14:30] <travlr>	is that just using wikidot's forum widgets?
| [Thursday 03 March 2011] [15:14:48] <pieter_hintjens>	no, pages + comments in those ones
| [Thursday 03 March 2011] [15:15:18] <travlr>	ah, ok so its irongiant specific... let me look at the link, thank you.
| [Thursday 03 March 2011] [15:15:36] <pieter_hintjens>	email lists are ok but a bit useless for dynamic work
| [Thursday 03 March 2011] [15:15:42] <pieter_hintjens>	thus we all hang out here on irc...
| [Thursday 03 March 2011] [15:16:03] <travlr>	yes, i was hoping for forum, email notication integration
| [Thursday 03 March 2011] [15:16:10] <pieter_hintjens>	you got it all there
| [Thursday 03 March 2011] [15:16:17] <pieter_hintjens>	there is an open source project template afair
| [Thursday 03 March 2011] [15:16:24] <travlr>	k
| [Thursday 03 March 2011] [15:16:27] <travlr>	thanks
| [Thursday 03 March 2011] [15:16:33] <pieter_hintjens>	clickety-clone and it's done, very simple
| [Thursday 03 March 2011] [15:16:35] <pieter_hintjens>	np
| [Thursday 03 March 2011] [15:25:27] <guido_g>	pieter_hintjens: https://gist.github.com/853467  is not enough info i guess
| [Thursday 03 March 2011] [15:26:00] <pieter_hintjens>	guido_g: when did you pull the branch from git?
| [Thursday 03 March 2011] [15:26:08] <pieter_hintjens>	this is a bug I fixed afaik
| [Thursday 03 March 2011] [15:26:18] <guido_g>	ok, i'll check
| [Thursday 03 March 2011] [15:26:31] <pieter_hintjens>	also it's not debug, so I think the previous version...
| [Thursday 03 March 2011] [15:26:45] <pieter_hintjens>	I'll have to put a version number in the broker :-)
| [Thursday 03 March 2011] [15:30:28] <guido_g>	it's up-to-date when i do a pull
| [Thursday 03 March 2011] [15:30:53] <pieter_hintjens>	hmm
| [Thursday 03 March 2011] [15:31:06] <pieter_hintjens>	master branch...
| [Thursday 03 March 2011] [15:31:26] <pieter_hintjens>	ok, let me add a version number print...
| [Thursday 03 March 2011] [15:31:36] <guido_g>	https://gist.github.com/853483 <- output of run
| [Thursday 03 March 2011] [15:31:58] <guido_g>	trying to get more info out of gdb
| [Thursday 03 March 2011] [15:33:25] <pieter_hintjens>	can you grab the latest master, rebuild the broker?
| [Thursday 03 March 2011] [15:35:06] <guido_g>	grml the c script ignores the -g
| [Thursday 03 March 2011] [15:35:23] <pieter_hintjens>	how are you building?
| [Thursday 03 March 2011] [15:35:31] <pieter_hintjens>	'./build mdbroker' should work
| [Thursday 03 March 2011] [15:36:00] <guido_g>	the c script does not pass the -g to the compiler
| [Thursday 03 March 2011] [15:36:07] <pieter_hintjens>	nope, it doesn't
| [Thursday 03 March 2011] [15:36:13] <pieter_hintjens>	that's not how it works
| [Thursday 03 March 2011] [15:36:21] <guido_g>	??
| [Thursday 03 March 2011] [15:36:28] <pieter_hintjens>	sigh... it's a long story
| [Thursday 03 March 2011] [15:36:32] <guido_g>	build calls this script
| [Thursday 03 March 2011] [15:36:34] <pieter_hintjens>	can't you just './build all'?
| [Thursday 03 March 2011] [15:36:39] <pieter_hintjens>	ah hang on
| [Thursday 03 March 2011] [15:36:44] <guido_g>	*sigh*
| [Thursday 03 March 2011] [15:36:51] <guido_g>	yes, i can but w/o debug info
| [Thursday 03 March 2011] [15:36:58] <pieter_hintjens>	yes, but it doesn't pass a -g option
| [Thursday 03 March 2011] [15:37:15] <guido_g>	then the header of c should be changed
| [Thursday 03 March 2011] [15:37:21] <guido_g>	there is a -g mentioned
| [Thursday 03 March 2011] [15:37:42] <pieter_hintjens>	yes, that's wrong
| [Thursday 03 March 2011] [15:37:58] <guido_g>	double *sigh*
| [Thursday 03 March 2011] [15:38:07] <pieter_hintjens>	what git commit are you on?
| [Thursday 03 March 2011] [15:38:11] <pieter_hintjens>	git log -1
| [Thursday 03 March 2011] [15:39:39] <guido_g>	new clone and fresh broker (w/o debug info)
| [Thursday 03 March 2011] [15:39:44] <guido_g>	testing...
| [Thursday 03 March 2011] [15:39:56] <pieter_hintjens>	what git commit are you on?
| [Thursday 03 March 2011] [15:40:11] <pieter_hintjens>	the c script is ok, it doesn't pass -g to the compiler as such, it processes it
| [Thursday 03 March 2011] [15:40:17] <pieter_hintjens>	but all this is beside the point
| [Thursday 03 March 2011] [15:40:24] <guido_g>	 git log -1
| [Thursday 03 March 2011] [15:40:24] <guido_g>	commit a8121994b0c25f4d242bbf06074dc6cc389ff336
| [Thursday 03 March 2011] [15:40:42] <pieter_hintjens>	ok
| [Thursday 03 March 2011] [15:40:51] <pieter_hintjens>	take hammer, break glass
| [Thursday 03 March 2011] [15:40:58] <pieter_hintjens>	export BOOM_MODEL=debug; build all
| [Thursday 03 March 2011] [15:41:23] <djc>	pieter_hintjens: if you have a moment later, could you take a peek at my questions from 3h ago?
| [Thursday 03 March 2011] [15:41:46] <pieter_hintjens>	djc: let me look...
| [Thursday 03 March 2011] [15:42:04] <pieter_hintjens>	ok... for openpgm, I don't know
| [Thursday 03 March 2011] [15:42:18] <pieter_hintjens>	for the XML dependency, it's there in some random main programs still being built with 0MQ
| [Thursday 03 March 2011] [15:42:37] <pieter_hintjens>	they resist being killed because they theoretically form part of the 'API' and thus are holy
| [Thursday 03 March 2011] [15:42:49] <djc>	ah yes, that is how it goes
| [Thursday 03 March 2011] [15:42:59] <pieter_hintjens>	guido_g: the build script _should_ be making debug builds
| [Thursday 03 March 2011] [15:43:08] <guido_g>	it does not
| [Thursday 03 March 2011] [15:43:17] <djc>	so for openpgm I should probably stick to .92 and wait for you guys to test something newer?
| [Thursday 03 March 2011] [15:43:26] <pieter_hintjens>	djc: you need to ask steve-o
| [Thursday 03 March 2011] [15:43:33] <djc>	pieter_hintjens: okay, thanks
| [Thursday 03 March 2011] [15:43:45] <djc>	does he come around here, and if so, in what tz?
| [Thursday 03 March 2011] [15:43:50] <pieter_hintjens>	guido_g: ok, can you add 'c -C' to build just before the first if statement?
| [Thursday 03 March 2011] [15:44:08] <pieter_hintjens>	that'll produce a report of the actual C compiler syntax it uses
| [Thursday 03 March 2011] [15:44:17] <guido_g>	w/ debug info https://gist.github.com/853467
| [Thursday 03 March 2011] [15:44:18] 	 * pieter_hintjens is annoyed when small things don't work as they should
| [Thursday 03 March 2011] [15:44:27] <guido_g>	hehe
| [Thursday 03 March 2011] [15:44:41] <guido_g>	i did the export hingie and it seemed to work
| [Thursday 03 March 2011] [15:44:46] <guido_g>	*thingie
| [Thursday 03 March 2011] [15:45:26] <pieter_hintjens>	which the dratted build script is meant to do itself if necessary
| [Thursday 03 March 2011] [15:45:41] <pieter_hintjens>	one line of shell, how complex can it be... :-(
| [Thursday 03 March 2011] [15:46:02] <pieter_hintjens>	ok, looking at that backtrace, thanks
| [Thursday 03 March 2011] [15:46:52] <guido_g>	this happens when the (only) worker exits w/o disconnect (just disapears)
| [Thursday 03 March 2011] [15:47:03] 	 * pieter_hintjens will try to reproduce
| [Thursday 03 March 2011] [15:47:13] <guido_g>	oops
| [Thursday 03 March 2011] [15:47:27] <guido_g>	tested this w/ my worker
| [Thursday 03 March 2011] [15:47:34] <guido_g>	will try the c worker now
| [Thursday 03 March 2011] [15:48:36] <pieter_hintjens>	if your worker makes it crash, send that to me
| [Thursday 03 March 2011] [15:48:41] <pieter_hintjens>	I can't get the crash using the C worker
| [Thursday 03 March 2011] [15:48:50] <guido_g>	i can :)
| [Thursday 03 March 2011] [15:49:19] <guido_g>	you stopped the worker w/ ctrl-c?
| [Thursday 03 March 2011] [15:49:24] <pieter_hintjens>	yes
| [Thursday 03 March 2011] [15:49:28] <guido_g>	tz tz tz
| [Thursday 03 March 2011] [15:49:38] <pieter_hintjens>	kill -9?
| [Thursday 03 March 2011] [15:49:49] <pieter_hintjens>	should not make any difference
| [Thursday 03 March 2011] [15:49:57] <guido_g>	it looks like the woker sends a disconnect on sigint
| [Thursday 03 March 2011] [15:50:09] <pieter_hintjens>	nope, don't think so...
| [Thursday 03 March 2011] [15:50:24] <guido_g>	ok
| [Thursday 03 March 2011] [15:50:59] <pieter_hintjens>	well, valgrind is also real good for this
| [Thursday 03 March 2011] [15:51:09] <pieter_hintjens>	valgrind --tool=memcheck mdbroker
| [Thursday 03 March 2011] [15:51:22] <guido_g>	crash when killing the worker w/ ctrl-c too
| [Thursday 03 March 2011] [15:51:34] <pieter_hintjens>	hmm, can't be a timing issue, it's all one thread
| [Thursday 03 March 2011] [15:51:44] <pieter_hintjens>	are you also running a client?
| [Thursday 03 March 2011] [15:51:45] <guido_g>	bt looks like its the same place
| [Thursday 03 March 2011] [15:52:01] <guido_g>	no, client has been disconnected before
| [Thursday 03 March 2011] [15:52:15] <pieter_hintjens>	but do you start it in the test case?
| [Thursday 03 March 2011] [15:52:37] <guido_g>	i've a one shot client that sends one request
| [Thursday 03 March 2011] [15:52:48] <pieter_hintjens>	this makes a difference
| [Thursday 03 March 2011] [15:52:53] <pieter_hintjens>	yes, I got the crash now
| [Thursday 03 March 2011] [15:53:00] <pieter_hintjens>	need to have a client request
| [Thursday 03 March 2011] [15:53:12] <guido_g>	even a processed one?
| [Thursday 03 March 2011] [15:53:31] <pieter_hintjens>	it all affects the broker state
| [Thursday 03 March 2011] [15:53:49] <guido_g>	obviously
| [Thursday 03 March 2011] [15:54:17] <pieter_hintjens>	ok, I got the error, but will look at it tomorrow
| [Thursday 03 March 2011] [15:54:32] <pieter_hintjens>	i appreciate the feedback enormously, guido_g
| [Thursday 03 March 2011] [15:54:35] <guido_g>	mq is like a time machine, didn't use gdb for 10 years
| [Thursday 03 March 2011] [15:54:42] <pieter_hintjens>	heh
| [Thursday 03 March 2011] [15:57:31] <guido_g>	any idea where to put the python version of mdp?
| [Thursday 03 March 2011] [15:58:07] <guido_g>	i'll make a repo for it
| [Thursday 03 March 2011] [16:05:44] <pieter_hintjens>	guido_g: I'd hope for Python translations that can be used for the Guide
| [Thursday 03 March 2011] [16:06:12] <pieter_hintjens>	these are minimal implementations, we can make a real product & repository after
| [Thursday 03 March 2011] [16:06:14] <guido_g>	sure, but there not translations of the c code, as i said
| [Thursday 03 March 2011] [16:06:46] <guido_g>	this a mdp implementation using the async features of pyzmq
| [Thursday 03 March 2011] [16:07:11] <pieter_hintjens>	that sounds fine
| [Thursday 03 March 2011] [16:07:18] <pieter_hintjens>	the point isn't to write C in Python
| [Thursday 03 March 2011] [16:07:32] <pieter_hintjens>	the point is to show Python programmers how to make the example in question
| [Thursday 03 March 2011] [16:07:38] <pieter_hintjens>	so, client API, worker API, broker
| [Thursday 03 March 2011] [16:07:47] <pieter_hintjens>	using whatever the language offers
| [Thursday 03 March 2011] [16:07:56] <guido_g>	https://gist.github.com/853561  <- the test worker
| [Thursday 03 March 2011] [16:09:04] <pieter_hintjens>	did you read mdwrkapi.c?
| [Thursday 03 March 2011] [16:09:08] <pieter_hintjens>	and mdworker.c
| [Thursday 03 March 2011] [16:09:11] <guido_g>	no
| [Thursday 03 March 2011] [16:09:23] <pieter_hintjens>	probably worth doing
| [Thursday 03 March 2011] [16:09:45] <guido_g>	why?
| [Thursday 03 March 2011] [16:09:51] <pieter_hintjens>	simply to see if we can offer a consistent API
| [Thursday 03 March 2011] [16:10:01] <pieter_hintjens>	worker API in C or Python can look similar
| [Thursday 03 March 2011] [16:10:08] <guido_g>	pieter_hintjens> the point isn't to write C in Python  <- ...
| [Thursday 03 March 2011] [16:10:15] <pieter_hintjens>	the API I made is not C
| [Thursday 03 March 2011] [16:10:19] <pieter_hintjens>	it's implemented in C
| [Thursday 03 March 2011] [16:10:40] <pieter_hintjens>	I'd thought of specifying the API as a rfc
| [Thursday 03 March 2011] [16:10:44] <pieter_hintjens>	both APIs
| [Thursday 03 March 2011] [16:11:04] <pieter_hintjens>	for example, in mdworker.c there is no 0MQ context, it's invisible
| [Thursday 03 March 2011] [16:12:29] <pieter_hintjens>	see https://gist.github.com/853581
| [Thursday 03 March 2011] [16:12:53] <pieter_hintjens>	and yes it includes a .c, please don't complain... :-)
| [Thursday 03 March 2011] [16:15:25] <guido_g>	https://github.com/guidog/pyzmq-mdp <- first go
| [Thursday 03 March 2011] [16:16:11] <guido_g>	see, the api is completely different because of the mechanisms used
| [Thursday 03 March 2011] [16:16:47] <guido_g>	as i said, i want to make use of the async features built into pyzmq
| [Thursday 03 March 2011] [16:17:48] <pieter_hintjens>	for sure
| [Thursday 03 March 2011] [16:18:10] <pieter_hintjens>	though I've no idea what the value is in offering such a complex API to app developers...
| [Thursday 03 March 2011] [16:18:20] <guido_g>	complex?
| [Thursday 03 March 2011] [16:18:51] <pieter_hintjens>	look, my API has three methods
| [Thursday 03 March 2011] [16:18:58] <pieter_hintjens>	create, send/recv, destroy
| [Thursday 03 March 2011] [16:19:05] <pieter_hintjens>	yours exposes the internals of MDP
| [Thursday 03 March 2011] [16:19:10] <pieter_hintjens>	every timeout, every message
| [Thursday 03 March 2011] [16:19:24] <pieter_hintjens>	it's not a wrapper at all, just a deconfobulatorix
| [Thursday 03 March 2011] [16:19:25] <guido_g>	the create is line 31 in the example worker
| [Thursday 03 March 2011] [16:19:35] <pieter_hintjens>	i made that up, btw
| [Thursday 03 March 2011] [16:19:42] <pieter_hintjens>	sorry :-) it's late
| [Thursday 03 March 2011] [16:19:51] <guido_g>	the worker method is the on_request
| [Thursday 03 March 2011] [16:20:04] <guido_g>	and the reply is sent by self.reply
| [Thursday 03 March 2011] [16:20:12] <pieter_hintjens>	i'm not complaining, this is fantastic work
| [Thursday 03 March 2011] [16:20:15] <guido_g>	very complicated, i've to admit
| [Thursday 03 March 2011] [16:20:27] <pieter_hintjens>	please do look at that gist I posted just now
| [Thursday 03 March 2011] [16:20:36] <pieter_hintjens>	that's what the app developer sees
| [Thursday 03 March 2011] [16:20:51] <pieter_hintjens>	when my C code is shorter than your Python code, to do the same work... that's... well...
| [Thursday 03 March 2011] [16:21:02] <pieter_hintjens>	ok
| [Thursday 03 March 2011] [16:21:05] <pieter_hintjens>	projects...
| [Thursday 03 March 2011] [16:21:13] <pieter_hintjens>	MDP is the protocol, not software
| [Thursday 03 March 2011] [16:21:45] <guido_g>	shorter?
| [Thursday 03 March 2011] [16:21:46] <pieter_hintjens>	do you see value in a project with mixed pieces, e.g. brokers / apis in different languages
| [Thursday 03 March 2011] [16:21:54] <pieter_hintjens>	https://gist.github.com/853581
| [Thursday 03 March 2011] [16:21:59] <guido_g>	yes
| [Thursday 03 March 2011] [16:22:03] <pieter_hintjens>	that's the echo worker
| [Thursday 03 March 2011] [16:22:06] <pieter_hintjens>	ok, let'
| [Thursday 03 March 2011] [16:22:10] <pieter_hintjens>	let's invent a name
| [Thursday 03 March 2011] [16:22:18] <guido_g>	i might be shocked, but can still read
| [Thursday 03 March 2011] [16:22:39] <pieter_hintjens>	majordomo already been taken by some random FOSS project apparently
| [Thursday 03 March 2011] [16:23:00] <guido_g>	random... *cough*
| [Thursday 03 March 2011] [16:23:04] 	 * pieter_hintjens searches for random but memorable name...
| [Thursday 03 March 2011] [16:23:18] <pieter_hintjens>	do you prefer memorable or meaningful?
| [Thursday 03 March 2011] [16:23:18] <guido_g>	the interoperability is there
| [Thursday 03 March 2011] [16:23:21] <pieter_hintjens>	yes
| [Thursday 03 March 2011] [16:23:36] <guido_g>	i'm using my worker w/ your broker and and client
| [Thursday 03 March 2011] [16:23:39] <pieter_hintjens>	interop is a funny thing though, it operates at multiple levels
| [Thursday 03 March 2011] [16:23:45] <pieter_hintjens>	e.g. 0mq api is interop
| [Thursday 03 March 2011] [16:24:00] <Guthur>	pieter_hintjens, what's the link to this protocol?
| [Thursday 03 March 2011] [16:24:06] <pieter_hintjens>	zero.mq/md
| [Thursday 03 March 2011] [16:24:18] 	 * pieter_hintjens likes the link shorterner at zero.mq...
| [Thursday 03 March 2011] [16:24:20] <guido_g>	http://rfc.zeromq.org/spec:7
| [Thursday 03 March 2011] [16:24:23] <Guthur>	cheers
| [Thursday 03 March 2011] [16:24:33] <pieter_hintjens>	:-)
| [Thursday 03 March 2011] [16:24:50] <Guthur>	did you find that majordomo is trademarked?
| [Thursday 03 March 2011] [16:25:00] <pieter_hintjens>	nope, it's not afaics
| [Thursday 03 March 2011] [16:25:25] <guido_g>	but still, the name is known for a quite long time
| [Thursday 03 March 2011] [16:25:26] <pieter_hintjens>	but it's a bad idea to mix the pattern - protocol - implementation
| [Thursday 03 March 2011] [16:26:37] <pieter_hintjens>	oh god, a bank email hit the list
| [Thursday 03 March 2011] [16:26:46] <pieter_hintjens>	you can tell them by the 1000-word disclaimers
| [Thursday 03 March 2011] [16:27:02] <pieter_hintjens>	And someone's acidic reply, "It took me a moment to realize your ridiculous disclaimer is not the message itself..."
| [Thursday 03 March 2011] [16:27:04] <pieter_hintjens>	hehe
| [Thursday 03 March 2011] [16:27:15] <guido_g>	hehe
| [Thursday 03 March 2011] [16:29:38] <Guthur>	it then has another link to even more disclaimer talk
| [Thursday 03 March 2011] [16:30:05] <pieter_hintjens>	I think I just sold my soul to BoA by replying to that email
| [Thursday 03 March 2011] [16:31:00] <pieter_hintjens>	ok, guido, let's make a project called Popcorn
| [Thursday 03 March 2011] [16:31:10] <pieter_hintjens>	cause I'm finishing a large bowl I made a while ago
| [Thursday 03 March 2011] [16:31:46] <pieter_hintjens>	there are dozens of FOSS projects called popcorn so there's no chance of confusion
| [Thursday 03 March 2011] [16:31:55] <guido_g>	there was a song called like that... back when music came these black large discs...
| [Thursday 03 March 2011] [16:32:02] <pieter_hintjens>	8" floppies?
| [Thursday 03 March 2011] [16:32:10] 	 * pieter_hintjens vaguely remembers...
| [Thursday 03 March 2011] [16:32:11] <guido_g>	no, harder
| [Thursday 03 March 2011] [16:32:23] <pieter_hintjens>	12" removable winchesters?
| [Thursday 03 March 2011] [16:32:37] <pieter_hintjens>	did they have MP3s in those days? don't think so...
| [Thursday 03 March 2011] [16:32:45] <guido_g>	but drive was open mostly
| [Thursday 03 March 2011] [16:32:47] <pieter_hintjens>	you're making this up as you're going along!
| [Thursday 03 March 2011] [16:33:03] <pieter_hintjens>	so, guido_g, shall I make this as an official zeromq community project?
| [Thursday 03 March 2011] [16:33:20] <guido_g>	let it cook a bit more first
| [Thursday 03 March 2011] [16:33:27] <pieter_hintjens>	embrace the chaos!
| [Thursday 03 March 2011] [16:33:38] <pieter_hintjens>	it burns if you leave it cooking too long
| [Thursday 03 March 2011] [16:34:09] <guido_g>	if we have full interop w/ the c version, then it might be worth to be announced
| [Thursday 03 March 2011] [16:34:29] <guido_g>	for this it needs a broker
| [Thursday 03 March 2011] [16:34:29] <pieter_hintjens>	ah, but the trick with projects is to announce a stunning goal way before you can make it happen
| [Thursday 03 March 2011] [16:34:35] <Guthur>	what is this new project
| [Thursday 03 March 2011] [16:34:45] <pieter_hintjens>	guido_g: see, we have interest already...
| [Thursday 03 March 2011] [16:34:53] <pieter_hintjens>	Guthur: sorry, can't tell you, it's confidential
| [Thursday 03 March 2011] [16:34:55] <guido_g>	*sigh*
| [Thursday 03 March 2011] [16:34:58] <pieter_hintjens>	:-)
| [Thursday 03 March 2011] [16:35:02] <Guthur>	I could try the logs hehe
| [Thursday 03 March 2011] [16:35:09] <Guthur>	they are quite long though
| [Thursday 03 March 2011] [16:35:16] <guido_g>	https://github.com/guidog/pyzmq-mdp
| [Thursday 03 March 2011] [16:35:25] <Guthur>	you guys were chatting for ages, hehe
| [Thursday 03 March 2011] [16:35:48] <pieter_hintjens>	guido_g: cook it a while, anyhow
| [Thursday 03 March 2011] [16:36:17] <pieter_hintjens>	if it was my project, I'd insist on common APIs in all languages
| [Thursday 03 March 2011] [16:36:18] <guido_g>	at the least the broker should be there and working with your worker and client
| [Thursday 03 March 2011] [16:36:24] <pieter_hintjens>	yes
| [Thursday 03 March 2011] [16:36:43] <pieter_hintjens>	defining good, language neutral APIs is quite fun
| [Thursday 03 March 2011] [16:36:52] <pieter_hintjens>	and extraordinarily useful to app developers
| [Thursday 03 March 2011] [16:36:54] <guido_g>	pieter_hintjens: then i'd remove the repo immediately
| [Thursday 03 March 2011] [16:37:32] <pieterh>	i can make event driven APIs in C, that's not the issue
| [Thursday 03 March 2011] [16:37:55] <pieterh>	the issue is just the semantics you show to users, and whether these can be consistent between languages
| [Thursday 03 March 2011] [16:38:15] <pieterh>	I'm pretty adamant they can be consistent
| [Thursday 03 March 2011] [16:38:17] <guido_g>	there is more than language
| [Thursday 03 March 2011] [16:38:39] <pieterh>	guido_g: are you in London by any chance?
| [Thursday 03 March 2011] [16:38:44] <guido_g>	nope
| [Thursday 03 March 2011] [16:38:48] <pieterh>	sigh...
| [Thursday 03 March 2011] [16:39:05] <guido_g>	too expensive just for a beer
| [Thursday 03 March 2011] [16:39:31] <pieterh>	I'd actually take a train somewhere to thrash this out
| [Thursday 03 March 2011] [16:39:57] <guido_g>	wouldn't make it cheaper
| [Thursday 03 March 2011] [16:40:55] <pieterh>	ok, let's cook this a while.
| [Thursday 03 March 2011] [16:41:15] <pieterh>	I need to get onto the rest of Ch4 anyhow
| [Thursday 03 March 2011] [16:41:21] <pieterh>	there is a lot still to do
| [Thursday 03 March 2011] [16:41:55] <pieterh>	I'll fix that broker crash tomorrow when I find an hour, it's a busy day
| [Thursday 03 March 2011] [16:42:06] <guido_g>	fine with me
| [Thursday 03 March 2011] [16:42:57] <pieterh>	ok, gnite !
| [Thursday 03 March 2011] [16:43:02] <guido_g>	good night!
| [Thursday 03 March 2011] [16:55:50] <guido_g>	has been a long day, need some sleep
| [Thursday 03 March 2011] [16:55:57] <guido_g>	cya
| [Thursday 03 March 2011] [17:32:52] <Guthur>	pieterh, umm did the implementation of zhelpers.h not use to be in the guide text
| [Thursday 03 March 2011] [17:33:41] <pieterh>	Guthur: (a) it got very long and (b) the translation model only works for .c files so it was showing C code in the PHP/whatever versions
| [Thursday 03 March 2011] [17:33:59] <Guthur>	ok
| [Thursday 03 March 2011] [17:34:09] <pieterh>	Did you like having it in the guide?
| [Thursday 03 March 2011] [17:34:32] <Guthur>	doesn't matter too much, I just wanted to check the dump implementation
| [Thursday 03 March 2011] [17:35:04] <pieterh>	I think the Guide is moving towards being less focused on C
| [Thursday 03 March 2011] [17:35:16] <Guthur>	true
| [Thursday 03 March 2011] [17:35:36] <pieterh>	Though I think C is the future... but still...
| [Thursday 03 March 2011] [17:35:43] <pieterh>	:-)
| [Thursday 03 March 2011] [17:35:46] <Guthur>	I thought C was the past, hehe
| [Thursday 03 March 2011] [17:35:58] <Guthur>	Lisp is the future, hehe
| [Thursday 03 March 2011] [17:36:06] <pieterh>	Lisp is older than C afair
| [Thursday 03 March 2011] [17:37:10] <Guthur>	that was LISP
| [Thursday 03 March 2011] [17:37:53] <Guthur>	but true, Lisps ancestor is the second oldest high level language
| [Thursday 03 March 2011] [17:38:03] <Guthur>	after Fortran
| [Thursday 03 March 2011] [17:38:19] <Guthur>	First with a Garbage Collector as well
| [Thursday 03 March 2011] [17:38:43] <Guthur>	afaik
| [Thursday 03 March 2011] [17:38:57] 	 * pieterh resists all language discussions
| [Thursday 03 March 2011] [17:39:04] <pieterh>	gawk rules
| [Thursday 03 March 2011] [17:39:29] <Guthur>	Lisp is a very enlightening experience as they say
| [Thursday 03 March 2011] [17:40:25] <Guthur>	Javascript is pretty awesome as well, it's just a pity it always lives in a browser, hehe
| [Thursday 03 March 2011] [17:46:34] <Guthur>	pieterh, have you ever tried Forth? last language mention, I swear
| [Thursday 03 March 2011] [17:47:02] <sp4ke>	hi guys
| [Thursday 03 March 2011] [17:47:06] <pieterh>	Guthur: I used to build Forth machines in 6502 assembler, quite freaky
| [Thursday 03 March 2011] [17:47:29] <pieterh>	hi sp4ke
| [Thursday 03 March 2011] [17:47:44] <Guthur>	pieterh, cool, 6502 was one of my first programming experiences
| [Thursday 03 March 2011] [17:47:54] <pieterh>	The sign of a Real Programmer
| [Thursday 03 March 2011] [17:47:55] <Guthur>	BBC micros
| [Thursday 03 March 2011] [17:48:02] <sp4ke>	want just to post this link for people who want to use zmq with MSVC 2010 i made a tutorial after struggling to make it work
| [Thursday 03 March 2011] [17:48:03] <sp4ke>	http://www.mansysadmin.com/2011/03/using-zeromq-framework-with-visual-studio-2010-tutorial/
| [Thursday 03 March 2011] [17:48:14] <sp4ke>	it could be useful on irc archive 
| [Thursday 03 March 2011] [17:49:00] <pieterh>	sp4ke: ... it's ... 
| [Thursday 03 March 2011] [17:49:04] <pieterh>	it comes down to "VS2010 made some changes to output properties, go to projects properties -> General -> , then change the Output Directory field to"..\..\..\lib\" (the same path as in (Linker -> General -> Output File) property"
| [Thursday 03 March 2011] [17:49:19] <pieterh>	why not add that to http://zero.mq/tips
| [Thursday 03 March 2011] [17:49:54] <sp4ke>	yes indeed but for a new comer to MSVC it is not obvious 
| [Thursday 03 March 2011] [17:50:03] <sp4ke>	ok i will do
| [Thursday 03 March 2011] [17:50:11] <sp4ke>	did not know that link
| [Thursday 03 March 2011] [17:50:39] <pieterh>	lol
| [Thursday 03 March 2011] [17:52:31] <Guthur>	it always works without any bother for me
| [Thursday 03 March 2011] [17:52:38] <Guthur>	I convert and compile
| [Thursday 03 March 2011] [17:53:06] <Guthur>	maybe I'm just lucky, hehe
| [Thursday 03 March 2011] [17:53:35] <pieterh>	yeah, but he made a *screenshot*
| [Thursday 03 March 2011] [18:08:48] <Guthur>	pieterh, the identity.c is setting the identity after connecting
| [Thursday 03 March 2011] [18:09:15] <Guthur>	no sorry
| [Thursday 03 March 2011] [18:09:18] <Guthur>	my bad
| [Thursday 03 March 2011] [18:09:29] <Guthur>	tired eyes
| [Thursday 03 March 2011] [18:09:53] <pieterh>	yeah, it does it twice
| [Thursday 03 March 2011] [18:10:03] <pieterh>	get some sleep, man!
| [Thursday 03 March 2011] [18:10:39] <Guthur>	soon, just want to get this dump working right
| [Thursday 03 March 2011] [18:11:34] <pieterh>	:-) well, I fixed the Last Bug in mdbroker, am now crashing...
| [Thursday 03 March 2011] [20:42:49] <yrashk>	looks like ezmq got much more stable now
| [Thursday 03 March 2011] [20:43:12] <yrashk>	and thanks to evaxsoftware it doesn't have a thread per socket design anymore
| [Thursday 03 March 2011] [20:43:15] <yrashk>	we're multiplexing now :)
| [Thursday 03 March 2011] [21:16:31] <catlee_>	hello
| [Thursday 03 March 2011] [21:16:40] <catlee_>	how does zeromq compare to something like rabbitmq?
| [Thursday 03 March 2011] [22:05:27] <datuanmac>	hi
| [Thursday 03 March 2011] [22:06:42] <datuanmac>	I'm trying integrate zmq to my project in Visual c++ version 6 but it's conflic version winsock2 ?
| [Thursday 03 March 2011] [22:16:04] <datuanmac>	What solution for visual 6 ?
| [Thursday 03 March 2011] [23:43:30] <ctrlc-root>	hello, im trying to run the hello world client/server example from the website on windows with vs2010 and the server isnt running right
| [Thursday 03 March 2011] [23:43:54] <ctrlc-root>	it starts but then it fails with an unhandled exception, error number 156384763
| [Thursday 03 March 2011] [23:44:06] <ctrlc-root>	"The operation cannot be completed because the socket is not in the right state"
| [Thursday 03 March 2011] [23:44:14] <ctrlc-root>	this is on the socket.recv() call in teh c++ api
| [Thursday 03 March 2011] [23:44:19] <ctrlc-root>	anyone know what could be going wrong?
| [Friday 04 March 2011] [01:34:31] <guido_g>	morning all
| [Friday 04 March 2011] [01:45:07] <eyecue>	tgif
| [Friday 04 March 2011] [02:03:06] <guido_g>	hehehe
| [Friday 04 March 2011] [02:07:05] <guido_g>	http://1.bp.blogspot.com/-LkXUSknbalU/TXB1HTDJs_I/AAAAAAAB_gw/q8Njub9H2e4/s1600/ironic_sign_situations_01.jpg  <- see what bad naming can do
| [Friday 04 March 2011] [02:07:42] <guido_g>	and now up for mor mdp fun
| [Friday 04 March 2011] [02:09:59] <eyecue>	that looks like its from the brisbane flood in australia
| [Friday 04 March 2011] [02:10:36] <eyecue>	guido_g; there was also this one during the same event :) http://resources1.news.com.au/images/2011/01/13/1225987/039817-suncorp-stadium.jpg
| [Friday 04 March 2011] [02:11:16] <guido_g>	hehe
| [Friday 04 March 2011] [02:11:35] <guido_g>	this is the humor one would expect 
| [Friday 04 March 2011] [02:11:43] <eyecue>	:]
| [Friday 04 March 2011] [02:11:46] <eyecue>	from aussies? yeh :)
| [Friday 04 March 2011] [02:12:48] <guido_g>	must be hard
| [Friday 04 March 2011] [02:13:12] <guido_g>	living close to water for the larger part of my life, but luckily never got flooded
| [Friday 04 March 2011] [02:14:21] <jsimmons>	i live on a hill, handy.
| [Friday 04 March 2011] [02:14:26] <guido_g>	once i saw a flood mark 1m above a telephoneboth in a small coastal town i lived
| [Friday 04 March 2011] [02:14:50] <guido_g>	coward! :)
| [Friday 04 March 2011] [02:15:31] <jsimmons>	im not going to slum it with the plebs down near the waterline :D
| [Friday 04 March 2011] [02:17:01] <eyecue>	guido_g; http://ian.umces.edu/blog/wp-content/uploads/2011/02/ipswich_in_flood.jpg :)
| [Friday 04 March 2011] [02:17:26] <eyecue>	we do everything bigger and better in .au
| [Friday 04 March 2011] [02:17:40] <guido_g>	seems so
| [Friday 04 March 2011] [02:18:00] <eyecue>	http://images.brisbanetimes.com.au/2011/01/12/2130176/420ipswich-420x0.jpg <-- shopping centre :)
| [Friday 04 March 2011] [02:18:08] <eyecue>	i think they got upwards of 15m in some parts there
| [Friday 04 March 2011] [02:21:11] 	 * guido_g should move to the mountains
| [Friday 04 March 2011] [02:34:36] <jsimmons>	http://www.youtube.com/watch?v=LdOwFTo4Q3I
| [Friday 04 March 2011] [02:34:41] <jsimmons>	weirdo queenslanders
| [Friday 04 March 2011] [03:14:56] <eyecue>	:]
| [Friday 04 March 2011] [04:13:06] <mikko>	good morning
| [Friday 04 March 2011] [04:18:17] <Steve-o>	top of the morning to you mikko
| [Friday 04 March 2011] [04:20:22] <mikko>	i don't fully understand this mingw32 vs mingw64 business
| [Friday 04 March 2011] [04:20:58] <Steve-o>	mingw64 is just an updated fork of mingw32
| [Friday 04 March 2011] [04:21:05] <Steve-o>	with 32-bit and 64-bit compilers
| [Friday 04 March 2011] [04:21:44] <Steve-o>	some rfit causing the split
| [Friday 04 March 2011] [04:21:49] <Steve-o>	rfit
| [Friday 04 March 2011] [04:21:51] <Steve-o>	rift
| [Friday 04 March 2011] [04:21:54] <Steve-o>	third time lucky
| [Friday 04 March 2011] [04:22:19] <mikko>	can i cross-compile 64bit binaries on 32bit machine with it?
| [Friday 04 March 2011] [04:22:36] <mikko>	looks like my own win7 build machine is offline
| [Friday 04 March 2011] [04:22:39] <Steve-o>	I guess you should be able to
| [Friday 04 March 2011] [04:22:45] <mikko>	probably installed updates again *sigh*
| [Friday 04 March 2011] [04:22:51] <Steve-o>	SP1
| [Friday 04 March 2011] [04:23:06] <Steve-o>	haven't installed it myself, 
| [Friday 04 March 2011] [04:23:25] <Steve-o>	looking for api changes, cannot find any docs but just found some notes on getaddrinfo() today
| [Friday 04 March 2011] [04:24:38] <Steve-o>	you can tag interfaces to be excluded from the results using netsh
| [Friday 04 March 2011] [04:24:41] <mikko>	confusing situation
| [Friday 04 March 2011] [04:25:06] <mikko>	are mingw32 dlls compatible with mingw64 binaries?
| [Friday 04 March 2011] [04:25:30] <Steve-o>	are 32-bit and 64-dlls interchangable, no
| [Friday 04 March 2011] [04:25:42] <mikko>	whats about 32bit ones?
| [Friday 04 March 2011] [04:26:03] <Steve-o>	via wow64 you can run 32-bit windows winsock apps on 64-bit windows
| [Friday 04 March 2011] [04:26:15] <Steve-o>	there are api changes that hide the details
| [Friday 04 March 2011] [04:26:33] <Steve-o>	and new apis like getnativesysteminfo() just for wow64
| [Friday 04 March 2011] [04:27:20] <Steve-o>	wow = windows on windows
| [Friday 04 March 2011] [04:34:10] <Steve-o>	but it's all transparent to the user
| [Friday 04 March 2011] [04:36:11] <mikko>	so building 32bit target with mingw64 doesn't really provide value over 32bit mingw32?
| [Friday 04 March 2011] [04:36:14] <mikko>	from user's point of view
| [Friday 04 March 2011] [04:44:57] <Steve-o_>	weeee, Google Chrome's hardware acceleration is definitely not stable yet :/
| [Friday 04 March 2011] [04:55:38] <Steve-o_>	downside with mingw is that it brings in a lot of compiler dependencies and debugging is ass
| [Friday 04 March 2011] [04:56:48] <mikko>	one of the downsides*
| [Friday 04 March 2011] [05:03:47] <Steve-o_>	more annoying is that it is slower than msvc
| [Friday 04 March 2011] [05:05:43] <Steve-o_>	I guess mingw-w64 is more updated and closer to gcc trunk and should be faster
| [Friday 04 March 2011] [05:09:20] <Steve-o_>	Should try ICC on Windows, haven't done that yet
| [Friday 04 March 2011] [05:10:17] <Steve-o_>	any numbers for 0mq and tcp?
| [Friday 04 March 2011] [05:10:37] <mikko>	5 - 6.5 million 1 byte messages over localhost
| [Friday 04 March 2011] [05:10:41] <mikko>	per sec
| [Friday 04 March 2011] [05:10:50] <mikko>	but it's questionable how accurate that is
| [Friday 04 March 2011] [05:11:48] <Steve-o_>	that was msvc on numa?
| [Friday 04 March 2011] [05:12:19] <mikko>	oh you mean windows
| [Friday 04 March 2011] [05:12:23] <mikko>	no numbers on windows
| [Friday 04 March 2011] [05:14:40] <Steve-o_>	ah ok
| [Friday 04 March 2011] [05:16:29] <Steve-o_>	was thinking of testing windows IPC after this release
| [Friday 04 March 2011] [05:17:07] <Steve-o_>	be easy to get something working and then see how the numbers get worse or better
| [Friday 04 March 2011] [05:18:10] <Steve-o_>	I sent an idea for broadcast IPC to sustrik before as an expansion on the idea, but I don't have numa boxes to performance test
| [Friday 04 March 2011] [05:20:13] <mikko>	i think Guthur is working for named pipes for windows
| [Friday 04 March 2011] [05:20:28] <mikko>	to get ipc:// working
| [Friday 04 March 2011] [06:24:32] <Guthur>	mikko: 'working' is a little strong at the moment
| [Friday 04 March 2011] [06:24:52] <Guthur>	Initial research completed at the moment
| [Friday 04 March 2011] [06:25:06] <Guthur>	need to develop a strategy for integration
| [Friday 04 March 2011] [06:26:43] <Guthur>	On my agenda is talk to sustrik more about what an abstraction of the name pipes using IOCP would need to emulate the current functionality provided and required by the polling methods on POSIX
| [Friday 04 March 2011] [06:27:38] <Guthur>	the problem is that plain IOCP is only a completion notification system
| [Friday 04 March 2011] [06:27:54] <Guthur>	and polling on POSIX provides more than that
| [Friday 04 March 2011] [06:41:35] <yrashk>	hey
| [Friday 04 March 2011] [06:41:50] <yrashk>	any idea on how we can check whether there are any unclosed sockets prior to zmq_term?
| [Friday 04 March 2011] [06:42:04] <yrashk>	we need to avoid blocking Erlang's VM in all possible situations
| [Friday 04 March 2011] [06:42:15] <yrashk>	so we'd rather not call zmq_term if we know that it will block
| [Friday 04 March 2011] [07:10:11] <guido_g>	no, that i know of
| [Friday 04 March 2011] [07:10:26] <guido_g>	this kind of information is not ment for us mere mortals
| [Friday 04 March 2011] [07:49:17] <private_meta>	Isn't there a way to tell zmq_term to terminate all sockets without waiting for finished messages? I thought I read something about it
| [Friday 04 March 2011] [07:50:02] <guido_g>	per socket
| [Friday 04 March 2011] [07:50:10] <guido_g>	via LINGER option
| [Friday 04 March 2011] [07:50:26] <guido_g>	but the sockets still have to be closed first
| [Friday 04 March 2011] [07:50:47] <yrashk>	well, we've got around this
| [Friday 04 March 2011] [07:51:05] <yrashk>	we now terminate context in a separate thread that we have anyway
| [Friday 04 March 2011] [09:32:44] <sejo>	hey all what are the pitfals for speed? what is the n* of messages i can send/receive with zeromq?
| [Friday 04 March 2011] [09:35:11] <guido_g>	depends on hardware and message size, so the question is futile
| [Friday 04 March 2011] [09:35:39] <guido_g>	btw, there are benchmarks in the mq git, use them
| [Friday 04 March 2011] [09:36:01] <sejo>	ach I will thx!
| [Friday 04 March 2011] [09:38:25] <sejo>	hmm with my code I only get 1/sec 
| [Friday 04 March 2011] [09:38:30] <sejo>	that is way to few :p
| [Friday 04 March 2011] [09:39:11] <sejo>	but I use it from python
| [Friday 04 March 2011] [09:39:49] <guido_g>	even w/ serialization i get ~4k messages per second using python
| [Friday 04 March 2011] [09:41:10] 	 * sejo slaps own head
| [Friday 04 March 2011] [09:41:35] <sejo>	please accept my apologies... still had time.sleep(1)  in my code :/
| [Friday 04 March 2011] [09:41:41] <sejo>	I'm a moron
| [Friday 04 March 2011] [09:41:59] <guido_g>	ok, we'll take that for granted
| [Friday 04 March 2011] [09:42:02] <guido_g>	:)
| [Friday 04 March 2011] [10:02:17] <sejo>	guido_g: apparently you should :p
| [Friday 04 March 2011] [10:02:35] <sejo>	now get approx 30/s (with saving to chouchdb)
| [Friday 04 March 2011] [10:02:40] <sejo>	so not that bad
| [Friday 04 March 2011] [10:03:19] <guido_g>	slow db?
| [Friday 04 March 2011] [10:13:33] <sejo>	guido_g: no slow way of doing it, I save document after document and not bulk save... that would improve a lot. Also python is owesome to write in but not _the_ fastest language there is
| [Friday 04 March 2011] [10:14:15] <sejo>	if we get funding and have more time I might redo in C, right now... python it is :p
| [Friday 04 March 2011] [10:14:22] <guido_g>	depends on how you do things
| [Friday 04 March 2011] [10:14:49] <guido_g>	usually python is fast enough
| [Friday 04 March 2011] [10:16:52] <guido_g>	ok, time for a break
| [Friday 04 March 2011] [10:16:55] <guido_g>	laters!
| [Friday 04 March 2011] [11:31:47] Notice	-tomaw- [Global Notice] Hi again.  As you will have noticed we're having some connectivity problems again this afternoon.  We're working with sponsors to rectify it.
| [Friday 04 March 2011] [11:57:30] <lt_schmidt_jr>	A couple of quesitons for the experts
| [Friday 04 March 2011] [11:58:11] <lt_schmidt_jr>	If a receiving socket goes unpolled can I detect if HWM has overflowed?
| [Friday 04 March 2011] [12:03:44] <mikko>	lt_schmidt_jr: yes
| [Friday 04 March 2011] [12:03:58] <mikko>	lt_schmidt_jr: non-blocking send should return EAGAIN assuming it's a socket that would block
| [Friday 04 March 2011] [12:05:22] <lt_schmidt_jr>	mikko: I am using pub sub, are you saying the pub socket will return eagain if a subscriber goes unpolled?
| [Friday 04 March 2011] [12:05:35] <mikko>	no, it would drop the message
| [Friday 04 March 2011] [12:05:48] <mikko>	you can't really detect HWM overflow with pub socket
| [Friday 04 March 2011] [12:05:56] <mikko>	as the messages are simply dropped
| [Friday 04 March 2011] [12:06:10] <mikko>	unless you poll
| [Friday 04 March 2011] [12:06:29] <mikko>	i am not sure whether poll indicates that it's writable
| [Friday 04 March 2011] [12:06:52] <lt_schmidt_jr>	interesting
| [Friday 04 March 2011] [12:07:06] <lt_schmidt_jr>	I thought I could have a sub-socket queue
| [Friday 04 March 2011] [12:07:21] <lt_schmidt_jr>	build up and it could overflow there
| [Friday 04 March 2011] [12:07:35] <lt_schmidt_jr>	as opposed on the publisher
| [Friday 04 March 2011] [12:07:55] <mikko>	i'm not really 100% how hwm interacts with pub-sub
| [Friday 04 March 2011] [12:08:18] <mikko>	let me check
| [Friday 04 March 2011] [12:08:37] <lt_schmidt_jr>	I am using inproc btw
| [Friday 04 March 2011] [12:08:47] <mikko>	http://api.zeromq.org/master:zmq-socket
| [Friday 04 March 2011] [12:09:00] <mikko>	if you look at the ZMQ_HWM option action under SUB
| [Friday 04 March 2011] [12:09:03] <mikko>	not applicable
| [Friday 04 March 2011] [12:10:10] <lt_schmidt_jr>	I see
| [Friday 04 March 2011] [12:10:17] <lt_schmidt_jr>	darn
| [Friday 04 March 2011] [12:14:34] <lt_schmidt_jr>	I wanted to pause socket polling on behalf of disconnected clients, but I guess I will have to build my own queue
| [Friday 04 March 2011] [12:14:57] <lt_schmidt_jr>	instead of relying on socket to queue
| [Friday 04 March 2011] [12:21:52] <lt_schmidt_jr>	mikko: thanks for the RTFM :) I forgot about that part of the doc having been studying the Guide
| [Friday 04 March 2011] [12:22:50] <mikko>	no problem
| [Friday 04 March 2011] [13:37:10] <Phantom_>	hello all
| [Friday 04 March 2011] [13:37:17] <Phantom_>	has anyone got the perl binding to work ?  it seems...nonfunctional.
| [Friday 04 March 2011] [13:41:04] <Phantom_>	'ello.  Is anyone out there ?
| [Friday 04 March 2011] [13:45:24] <andrewvc>	cremes: wish I had a better answer re: ffi as a dependency
| [Friday 04 March 2011] [13:45:34] <andrewvc>	the alternate gems thing doesn't really solve it
| [Friday 04 March 2011] [13:45:56] <cremes>	andrewvc: yeah, i hate that solution
| [Friday 04 March 2011] [13:46:12] <cremes>	i'm going to open up a feature request with the rubygems project
| [Friday 04 March 2011] [13:46:13] <andrewvc>	I was thinking actually, it'd be best if maybe the FFI project just did nothing if it was required in a non MRI ruby
| [Friday 04 March 2011] [13:46:21] <andrewvc>	yeah, that's the right long term solution
| [Friday 04 March 2011] [13:46:42] <cremes>	it's not the 'require' step that breaks things
| [Friday 04 March 2011] [13:46:47] <cremes>	it's the installation of the gem
| [Friday 04 March 2011] [13:46:55] <cremes>	it tries to install the 'ffi' gem and blows up
| [Friday 04 March 2011] [13:46:57] <andrewvc>	oh, what happens if you try and install in on rbx or jruby
| [Friday 04 March 2011] [13:47:04] <cremes>	kaboom
| [Friday 04 March 2011] [13:47:06] <andrewvc>	oh, because it tries to compile the ext
| [Friday 04 March 2011] [13:47:08] <andrewvc>	damn
| [Friday 04 March 2011] [13:47:09] <cremes>	right
| [Friday 04 March 2011] [13:48:01] <andrewvc>	yeah, RUBY_PLATFORM isn't enough, rubygems needs RUBY_ENGINE
| [Friday 04 March 2011] [13:48:07] <andrewvc>	is I'm guessing what you're going to request
| [Friday 04 March 2011] [13:48:41] <andrewvc>	it's funny, because the alternate gem thing works fine for jruby, just not rbx
| [Friday 04 March 2011] [13:53:37] <mikko>	pieter_hintjens: there?
| [Friday 04 March 2011] [14:47:49] <mathijs>	Hi all, is zmq_poll edge-triggered? in other words: if I poll on 10 items, and 3 of them have events waiting, but I only handle 1 and poll again, will the second poll call still return the other 2, or those be forgotten, letting poll wait for new events?
| [Friday 04 March 2011] [15:11:59] <mikko>	mathijs: it is
| [Friday 04 March 2011] [15:12:03] <Guthur>	http://api.zeromq.org/master:zmq-poll
| [Friday 04 March 2011] [15:12:11] <Guthur>	oh mikko beat me to it
| [Friday 04 March 2011] [15:12:31] <mathijs>	mikko: so I should take care to handle all events that occured before re-polling?
| [Friday 04 March 2011] [15:12:39] <mikko>	yes
| [Friday 04 March 2011] [15:12:43] <Guthur>	it says level triggered there
| [Friday 04 March 2011] [15:12:55] <mikko>	that sounds wrong
| [Friday 04 March 2011] [15:13:13] <mathijs>	ah, I was reading that page for some minutes but couldn't find it :P
| [Friday 04 March 2011] [15:13:34] <mikko>	i'm almost certain that the manual page there is wrong 
| [Friday 04 March 2011] [15:14:03] <mathijs>	level triggered is wrong I think. level triggered normally means that the trigger keeps popping up as long as the "level"/state is positive
| [Friday 04 March 2011] [15:15:27] <mikko>	see this one from el sustrik: http://www.mail-archive.com/zeromq-dev@lists.zeromq.org/msg01620.html
| [Friday 04 March 2011] [15:15:32] <mikko>	"Say there are two messages available. You read one of them. If you wait 
| [Friday 04 March 2011] [15:15:33] <mikko>	for the fd at this point it may never unblock, because there's still one 
| [Friday 04 March 2011] [15:15:33] <mikko>	message to read. Command saying "there are new messages available" is 
| [Friday 04 March 2011] [15:15:33] <mikko>	sent to your thread only if you've read all the messages before. You can 
| [Friday 04 March 2011] [15:15:33] <mikko>	think of it as edge-triggered polling"
| [Friday 04 March 2011] [15:15:42] <mikko>	longer paste than i expected
| [Friday 04 March 2011] [15:15:59] <Guthur>	is that maybe specific to FD though?
| [Friday 04 March 2011] [15:16:19] <Guthur>	i.e. not a zmq socket
| [Friday 04 March 2011] [15:16:23] <mikko>	it's possible
| [Friday 04 March 2011] [15:16:36] <mikko>	i was always under the impression that zmq socket is edge-triggered as well
| [Friday 04 March 2011] [15:16:38] <mathijs>	yeah, I knew that behavior is like that for FD, it was stated that was truely edge-triggered.
| [Friday 04 March 2011] [15:17:00] <mikko>	double check with sustrik or pieter_hintjens when either one of them is back
| [Friday 04 March 2011] [15:17:17] <mathijs>	well I'll do some quick tests, not too hard to find out
| [Friday 04 March 2011] [15:18:02] <Guthur>	my quick test seems to confirm its level
| [Friday 04 March 2011] [15:18:49] <mikko>	i guess if you need edge triggered you can always get the ZMQ_FD and poll on that
| [Friday 04 March 2011] [15:20:01] <mathijs>	no, I don't really need either of them, just want to make sure my expectations are right and I don't accidentally abuse some loophole
| [Friday 04 March 2011] [15:20:49] <mikko>	level triggered certainly makes it easier
| [Friday 04 March 2011] [15:21:41] <mathijs>	indeed, but not as die-hard :P
| [Friday 04 March 2011] [17:30:01] <lt_schmidt_jr>	What happens when a HWM is reached by a publisher in pub/sub?
| [Friday 04 March 2011] [17:30:14] <lt_schmidt_jr>	are the new messages dropped or the old ones are dequeud?
| [Friday 04 March 2011] [17:33:11] <Guthur>	new messages dropped
| [Friday 04 March 2011] [17:33:28] <lt_schmidt_jr>	Guthur: thanks
| [Friday 04 March 2011] [17:33:46] <Guthur>	you're welcome
| [Friday 04 March 2011] [17:42:36] <yrashk>	so, what would be the best way to add a library to http://www.zeromq.org/bindings:erlang ?
| [Friday 04 March 2011] [17:55:57] <Guthur>	yrashk, you mean add another erlang binding?
| [Friday 04 March 2011] [17:56:11] <yrashk>	yep
| [Friday 04 March 2011] [18:00:14] <Guthur>	is it publicly available
| [Friday 04 March 2011] [18:00:30] <Guthur>	tbh I'm not sure if there is a procedure
| [Friday 04 March 2011] [18:00:41] <Guthur>	pieter_hintjens, ping
| [Friday 04 March 2011] [18:08:22] <kdj>	I am having some trouble getting pyzmq installed on Ubuntu...
| [Friday 04 March 2011] [18:12:09] <kdj>	I follow the steps in the docs, and it works fine, but if I log out and back in, I seem to lose some env variable
| [Friday 04 March 2011] [18:20:26] <yrashk>	Guthur: new binding? yes, it is
| [Friday 04 March 2011] [18:23:09] <Guthur>	yrashk, I'm not sure if there is a process, best to mention it on the mailing list then pieter or martin can see it
| [Friday 04 March 2011] [18:23:51] <Guthur>	I'd imagine you just add a description and links to that page
| [Friday 04 March 2011] [18:24:11] <yrashk>	well they are aware of it
| [Friday 04 March 2011] [18:24:33] <yrashk>	anyway, will take care of this later
| [Saturday 05 March 2011] [02:47:07] <vrc>	hi
| [Saturday 05 March 2011] [02:47:18] <vrc>	had a quick question about the pub-sub model and reliability
| [Saturday 05 March 2011] [02:48:25] <vrc>	i set up a pub-sub model..and if my subscribers receive packets (in a loop) -> and spend a lot of time processing them, will they lose packets
| [Saturday 05 March 2011] [02:49:22] <vrc>	or is the pub-sub model guaranteed to provide reliability i.e, all packets sent by the pub are received by each sub..i do realize that some packets in the beginning could be lost due to connection delays, etc
| [Saturday 05 March 2011] [02:49:31] <vrc>	thanks - i'm new to zeromq
| [Saturday 05 March 2011] [02:51:24] <cremes>	vrc: think of a PUB socket as a radio broadcast
| [Saturday 05 March 2011] [02:51:45] <cremes>	if your subscriber isn't around to "hear" it, there is no guarantee it will get all packets
| [Saturday 05 March 2011] [02:52:21] <cremes>	by default, PUB will queue packets for all connected subscribers but a slow subscriber can cause a huge backlog
| [Saturday 05 March 2011] [02:52:29] <cremes>	and memory pressure on the publisher if they can't keep up
| [Saturday 05 March 2011] [02:52:42] <cremes>	so, there is a mechanism called ZM_HWM (high water mark)
| [Saturday 05 March 2011] [02:53:07] <cremes>	if there are more than X outstanding packets (where X is the HWM) then the pub socket drops them to /dev/null
| [Saturday 05 March 2011] [02:53:34] <cremes>	if you need reliability, then you need to work out some kind of 'ack' mechanism and a pub/sub pattern is no 
| [Saturday 05 March 2011] [02:53:36] <cremes>	longer appropriate
| [Saturday 05 March 2011] [02:53:55] <cremes>	be sure to read all 4 chapters of the guide... of lot of these use-cases are discussed in there
| [Saturday 05 March 2011] [02:54:20] <cremes>	vrc: did that help?
| [Saturday 05 March 2011] [02:57:30] <vrc>	cremes - thank you very much. that was very useful - in fact, i was reading your comments somewhere else on the internet
| [Saturday 05 March 2011] [02:57:47] <cremes>	heh
| [Saturday 05 March 2011] [02:58:00] <cremes>	well, it's bed time; good luck with your investigations
| [Saturday 05 March 2011] [02:58:06] <vrc>	even if you use PUB/SUB over TCP-IP, there's no guaranteed delivery ?
| [Saturday 05 March 2011] [02:58:17] <cremes>	this channel is usually pretty well covered during the weekdays
| [Saturday 05 March 2011] [02:58:38] <cremes>	no
| [Saturday 05 March 2011] [02:59:05] <cremes>	read the guide... this is almost faq :)
| [Saturday 05 March 2011] [02:59:11] <vrc>	ok. thanks - won't keep you up
| [Saturday 05 March 2011] [02:59:16] <cremes>	cool
| [Saturday 05 March 2011] [03:16:49] <guido_g>	good morning all
| [Saturday 05 March 2011] [04:43:17] <pieter_hintjens>	guido_g: good morning
| [Saturday 05 March 2011] [04:43:29] <guido_g>	howdy pieter_hintjens 
| [Saturday 05 March 2011] [04:43:39] <pieter_hintjens>	how's it going... ?
| [Saturday 05 March 2011] [04:44:24] <guido_g>	didn't do anything yesterday
| [Saturday 05 March 2011] [04:44:42] <guido_g>	except finding a glitch in the spec, but i need to verify that first
| [Saturday 05 March 2011] [04:45:05] <pieter_hintjens>	a glitch, interesting
| [Saturday 05 March 2011] [04:45:22] <guido_g>	yep
| [Saturday 05 March 2011] [04:46:05] <guido_g>	in client <-> broker there is no client address mentioned
| [Saturday 05 March 2011] [04:46:36] <guido_g>	but it appears magically (as full list even) in worker <-> broker
| [Saturday 05 March 2011] [04:46:56] <pieter_hintjens>	right, it's the same as for broker-worker
| [Saturday 05 March 2011] [04:47:23] <pieter_hintjens>	that note should be made to cover both sides
| [Saturday 05 March 2011] [04:47:36] <guido_g>	i mean where does the client address in frame 2 come from? that should be explaind
| [Saturday 05 March 2011] [04:47:41] <guido_g>	*ed
| [Saturday 05 March 2011] [04:47:54] <pieter_hintjens>	hmm, one assumes the implementor knows his XREP/ROUTER stuff
| [Saturday 05 March 2011] [04:48:51] <guido_g>	but still it's not clear where the address in frame 2 comes from, itr should be mentioned in the spec -- imho
| [Saturday 05 March 2011] [04:50:23] <pieter_hintjens>	indeed... it assumes too much, I'll fix that
| [Saturday 05 March 2011] [04:50:48] <guido_g>	oh and eventually move the XREQ note to the front of the spec
| [Saturday 05 March 2011] [04:51:18] <guido_g>	so one can see it before its needed
| [Saturday 05 March 2011] [04:52:31] <pieter_hintjens>	indeed
| [Saturday 05 March 2011] [04:53:15] <guido_g>	i think i'll start on some broker parts this afternoon
| [Saturday 05 March 2011] [04:54:21] <guido_g>	if we could get that running, all these "but i need reliability" questions could be answered w/ a link :)
| [Saturday 05 March 2011] [04:55:59] <pieter_hintjens>	ah, almost :-)
| [Saturday 05 March 2011] [04:56:06] <pieter_hintjens>	after this, it's the Titanic pattern
| [Saturday 05 March 2011] [04:56:28] <mikko>	looks like steve got openpgm out
| [Saturday 05 March 2011] [04:56:34] <pieter_hintjens>	"but I need reliability on spinning rust"
| [Saturday 05 March 2011] [04:56:59] <pieter_hintjens>	mikko: saw that...
| [Saturday 05 March 2011] [04:57:00] <guido_g>	rust?
| [Saturday 05 March 2011] [04:57:36] <pieter_hintjens>	guido_g: iron oxide? magnetised brown stuff used to hold data
| [Saturday 05 March 2011] [04:57:49] <guido_g>	ahhh...
| [Saturday 05 March 2011] [04:58:20] <guido_g>	sorry, thought you just got a ssd, so it'll be "built on sand"
| [Saturday 05 March 2011] [04:59:20] <pieter_hintjens>	guido_g: I replaced the HD in my notebook with an SSD that Sustrik gave me a while back
| [Saturday 05 March 2011] [04:59:27] <pieter_hintjens>	quite neat
| [Saturday 05 March 2011] [04:59:38] <djc>	in the guide's fig9, shouldn't the second right-hand box be "Start the SUB sockets before the PUB to avoid loss" (i.e. the other way around)?
| [Saturday 05 March 2011] [04:59:53] <pieter_hintjens>	djc: let me check...
| [Saturday 05 March 2011] [05:00:41] <guido_g>	pieter_hintjens: spec:7 "Clients will issue at most one request at a time, and will wait for a reply in realtime." <- can this be lifted, i can't see why
| [Saturday 05 March 2011] [05:01:13] <djc>	pieter_hintjens: in the bottom box it also says 9zeromq, I think it means #zeromq?
| [Saturday 05 March 2011] [05:01:17] <guido_g>	oops... time for furniture shopping
| [Saturday 05 March 2011] [05:01:25] <guido_g>	l8tr
| [Saturday 05 March 2011] [05:02:07] <pieter_hintjens>	guido_g: it can't be lifted without other changes
| [Saturday 05 March 2011] [05:02:25] <pieter_hintjens>	djc: fixed both errors, thanks
| [Saturday 05 March 2011] [05:02:32] <djc>	awesome, thanks
| [Saturday 05 March 2011] [05:02:42] <djc>	I could write up a list of language refinements if you're interested
| [Saturday 05 March 2011] [05:02:53] <djc>	I presume you're not a native speaker, either? :)
| [Saturday 05 March 2011] [05:03:28] <pieter_hintjens>	djc: of what language?
| [Saturday 05 March 2011] [05:03:46] <djc>	the refinements, or a native speaker?
| [Saturday 05 March 2011] [05:03:57] <djc>	if the former, some things in the guide read awkwardly
| [Saturday 05 March 2011] [05:04:01] <pieter_hintjens>	uhm, English is my native language, yes
| [Saturday 05 March 2011] [05:04:11] <pieter_hintjens>	feel free to point out the awkward parts
| [Saturday 05 March 2011] [05:04:18] <djc>	oh, ok, I assumed from your name
| [Saturday 05 March 2011] [05:04:43] <djc>	sorry about that!
| [Saturday 05 March 2011] [05:04:56] <pieter_hintjens>	np
| [Saturday 05 March 2011] [05:05:13] <pieter_hintjens>	there's an issue tracker on the Guide github
| [Saturday 05 March 2011] [05:05:18] <djc>	ok
| [Saturday 05 March 2011] [05:06:02] <djc>	another question: what's the reason I have to memcpy() my data to the zmq_message, for example in the guide's pub/sub example's publisher
| [Saturday 05 March 2011] [05:06:42] <djc>	it seems like it should be okay to reference it as long as I make sure it stays around until the zmq_msg_close()?
| [Saturday 05 March 2011] [05:07:13] <pieter_hintjens>	sure
| [Saturday 05 March 2011] [05:07:21] <mikko>	djc: with inproc that is ok
| [Saturday 05 March 2011] [05:07:33] <pieter_hintjens>	the examples don't try to optimise
| [Saturday 05 March 2011] [05:08:26] <pieter_hintjens>	mikko: fixed issue #3 on ztools
| [Saturday 05 March 2011] [05:09:18] <mikko>	thanks
| [Saturday 05 March 2011] [05:09:37] <mikko>	im trying to figure out a good build order for zeromq2 in the daily builds
| [Saturday 05 March 2011] [05:09:52] <mikko>	tests use the same ports so concurrent builds have intermittent test fails
| [Saturday 05 March 2011] [05:10:19] <pieter_hintjens>	how so?
| [Saturday 05 March 2011] [05:10:58] <mikko>	well, multiple builds run test that tries to bind to 5555
| [Saturday 05 March 2011] [05:11:12] <mikko>	which throws EADDRINUSE
| [Saturday 05 March 2011] [05:11:20] <mikko>	btw, did you see this: https://github.com/mkoppanen/zeromq2-docs
| [Saturday 05 March 2011] [05:11:35] <mikko>	that uses submobules to bring everything in to same 'workspace'
| [Saturday 05 March 2011] [05:12:17] <pieter_hintjens>	ah, right... tests should use unique ports
| [Saturday 05 March 2011] [05:12:27] <mikko>	you mean randomise the port?
| [Saturday 05 March 2011] [05:12:49] <pieter_hintjens>	not randomize, but allocate sequentially or something
| [Saturday 05 March 2011] [05:12:53] <pieter_hintjens>	number the tests 1 up
| [Saturday 05 March 2011] [05:13:09] <mikko>	that's all fine but i build 4 zeromq builds on the same machine at the same time
| [Saturday 05 March 2011] [05:13:14] <pieter_hintjens>	oh, hang on, it's the same test running in parallel, right
| [Saturday 05 March 2011] [05:13:16] <pieter_hintjens>	bleh
| [Saturday 05 March 2011] [05:13:17] <mikko>	so sequence would be the same
| [Saturday 05 March 2011] [05:13:42] <pieter_hintjens>	no answer except "serialize the tests"
| [Saturday 05 March 2011] [05:14:06] <pieter_hintjens>	btw, we forked off zeromq2-0 as well
| [Saturday 05 March 2011] [05:14:34] <djc>	hmmm, so what does it mean for zmq_msg_init_data() to "take ownership of the supplied buffer"? for example, I want to send a part of a stack-allocated buffer, what would be the optimal way to put this into a message?
| [Saturday 05 March 2011] [05:14:44] <djc>	given that there are no weird threading things going on in my app
| [Saturday 05 March 2011] [05:15:11] <pieter_hintjens>	djc: 'optimal' as in 'save the last CPU cycle' or as in 'don't write code that confuses me'?
| [Saturday 05 March 2011] [05:15:35] <pieter_hintjens>	if you aren't really comfortable with the API you should not be trying to optimize, period
| [Saturday 05 March 2011] [05:15:50] <pieter_hintjens>	and even when you are, you should still not be optimizing
| [Saturday 05 March 2011] [05:16:11] <djc>	this is me trying to become comfortable with the API :)
| [Saturday 05 March 2011] [05:16:24] <djc>	I know, I know, I should only optimize after stress-testing
| [Saturday 05 March 2011] [05:16:34] <djc>	I was just wondering about the underlying model
| [Saturday 05 March 2011] [05:17:04] <pieter_hintjens>	use mempcy and focus on more interesting aspects of the model
| [Saturday 05 March 2011] [05:17:29] <djc>	ok
| [Saturday 05 March 2011] [05:38:13] <mikko>	pieter_hintjens: i updated zfl README.txt last night
| [Saturday 05 March 2011] [05:38:32] <mikko>	but didnt have time to investigate into generating README.md 
| [Saturday 05 March 2011] [05:38:40] <mikko>	can you update that?
| [Saturday 05 March 2011] [05:39:00] <pieter_hintjens>	sure, it uses gitdown
| [Saturday 05 March 2011] [05:39:03] <pieter_hintjens>	will do now
| [Saturday 05 March 2011] [05:39:29] <pieter_hintjens>	done
| [Saturday 05 March 2011] [05:53:54] <mikko>	thanks
| [Saturday 05 March 2011] [09:05:04] <larhat>	Hi, folks! If i set ZMQ_HWM=1 and ZMQ_SWP=N (N>0) on socket, process will store all, that cannot be processed immediately, on disk. But it process fails, can it restore swapped messages and retry sending? I wonder, can i use this for some kind of persistence queue? 
| [Saturday 05 March 2011] [09:13:03] <Guthur>	larhat, I have a feeling it cannot
| [Saturday 05 March 2011] [09:51:40] <mikko>	larhat: no, it cannot be done at the moment
| [Saturday 05 March 2011] [09:51:54] <mikko>	larhat: there has been discussion about creating persistence devices
| [Saturday 05 March 2011] [09:52:12] <mikko>	where you could 'plug in' persistence on sockets you need
| [Saturday 05 March 2011] [09:54:31] <larhat>	ok, thanks, guys