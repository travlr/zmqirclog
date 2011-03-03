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