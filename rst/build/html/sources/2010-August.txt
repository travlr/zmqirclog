===============
2010-August
===============

| [Sunday 01 August 2010] [23:23:32] <indygreg>   I have a client-server model where a stateless server receives a request from a client. But instead of a single response message, I'd like the server to send multiple response messages. I'm seeking advice for the best way to do this in 0MQ.
| [Sunday 01 August 2010] [23:24:01] <indygreg>   I tried ZMQ_REP/ZMQ_REP sockets with sending a multipart response message, but it appears the message parts are being buffered
| [Sunday 01 August 2010] [23:25:30] <indygreg>   as far as I can tell, the only other solution is to open a new PUB socket on the server and instruct the client how to connect to it. is there a better way?
| [Monday 02 August 2010] [01:43:30] <sustrik>    indygreg: use XREQ/XREP sockets
| [Monday 02 August 2010] [01:51:29] <sustrik>    even better, use multi-part messages
| [Monday 02 August 2010] [01:53:26] <indygreg>   sustrik: I was using multi-part messages but it appears the entire message is being buffered. I'm looking to send a long-running (over hours) stream of messages
| [Monday 02 August 2010] [01:53:56] <sustrik>    then use XREQ/XREP
| [Monday 02 August 2010] [01:55:16] <indygreg>   I'm relatively new to 0MQ - is there documentation on XREQ/XREP vs REQ/REP? I've seen them mentioned here and there but can't find a concise description
| [Monday 02 August 2010] [01:56:18] <sustrik>    nope, the documentation is missing yet
| [Monday 02 August 2010] [01:56:46] <sustrik>    xreq/xrep is similar to req/rep but doesn't require strictly alternate sequence of reqs and reps
| [Monday 02 August 2010] [01:57:13] <sustrik>    otoh, you'll have to do a bit of routing by hand
| [Monday 02 August 2010] [01:57:14] <indygreg>   ahh - sounds just what I'm looking for
| [Monday 02 August 2010] [01:57:31] <sustrik>    REQ socket prepends an empty message part (bottom of the backtrace stack) to each message you send. It also removes the empty message part from the beginning of each message you receive.
| [Monday 02 August 2010] [01:57:31] <sustrik>    REP socket stores all the message parts up to the first empty message part when you receive and passes the rest to the user. When message is sent, it prepends the saved backtrace stack to the message.
| [Monday 02 August 2010] [01:57:31] <sustrik>    XREQ does basically nothing but load balances the sent messages and fair queues the received messages.
| [Monday 02 August 2010] [01:57:31] <sustrik>    XREP prepends a message part containing peer's identity to each received message. It also chops of the first message part from every sent message and uses that as a routing info to find out which peer the message should be sent to. 
| [Monday 02 August 2010] [01:58:43] <indygreg>   interesting. I'll definitely take a look. thanks for the pointer
| [Monday 02 August 2010] [02:54:40] <indygreg>   well, that was easy: just capture the first message part of a XREQ request and send it out as the first message part in the response
| [Monday 02 August 2010] [02:59:46] <sustrik>    yes
| [Monday 02 August 2010] [12:13:48] <Balistic>   Can one create a SUB socket, then bind it and have a PUB socket connect to it?
| [Monday 02 August 2010] [12:26:28] <sustrik>    yes
| [Monday 02 August 2010] [12:27:16] <Balistic>   hmm, so far I cant get it to work. Having a SUB connecting to a PUB works fine, but not the other way round.
| [Monday 02 August 2010] [12:27:25] <sustrik>    ?
| [Monday 02 August 2010] [12:27:34] <sustrik>    what's goign wrong?
| [Monday 02 August 2010] [12:28:15] <Balistic>   recv() on the SUB side never returns, even though I can see the packets of messages via wireshark
| [Monday 02 August 2010] [12:29:04] <sustrik>    is that on TCP?
| [Monday 02 August 2010] [12:29:08] <Balistic>   yea
| [Monday 02 August 2010] [12:29:26] <Balistic>   btw, this is with pyzmq also
| [Monday 02 August 2010] [12:29:30] <sustrik>    have you subscribed btw?
| [Monday 02 August 2010] [12:29:37] <Balistic>   yea, to ''
| [Monday 02 August 2010] [12:29:46] <Balistic>   ie emtpy string
| [Monday 02 August 2010] [12:30:02] <sustrik>    strange
| [Monday 02 August 2010] [12:30:09] <sustrik>    report it as a bug then
| [Monday 02 August 2010] [12:30:22] <Balistic>   ill try with the c lib and see if it does the same
| [Monday 02 August 2010] [12:30:31] <sustrik>    please, do
| [Monday 02 August 2010] [12:30:46] <sustrik>    when reporting the bug, attach your test prog
| [Monday 02 August 2010] [12:31:32] <Balistic>   anycase, what im trying todo is write a basic 'hub' that will relay messages of clients to each other. there isnt anything like that atm?
| [Monday 02 August 2010] [12:34:24] <sustrik>    check the zmq_forwarder device
| [Monday 02 August 2010] [12:34:38] <Balistic>   i saw it, but there are little docs for it
| [Monday 02 August 2010] [12:34:58] <sustrik>    http://github.com/zeromq/zeromq-chat/blob/master/README
| [Monday 02 August 2010] [12:35:50] <Balistic>   heh, i think ill go read the source also
| [Monday 02 August 2010] [12:36:02] <sustrik>    have a look :)
| [Monday 02 August 2010] [12:36:07] <Balistic>   ta
| [Monday 02 August 2010] [12:36:09] <sustrik>    it's ~5 lines long :)
| [Monday 02 August 2010] [13:27:43] <Balistic>   sustrik: found my problem. my sender would exit immediatly after doing .send(). adding a slight delay before exiting solved the problem
| [Monday 02 August 2010] [19:27:14] <zmqserverQ> HI
| [Monday 02 August 2010] [19:27:30] <zmqserverQ> where is zmq_server?i can find it
| [Monday 02 August 2010] [19:27:38] <zmqserverQ> thinks
| [Tuesday 03 August 2010] [08:47:03] <cremes>    interesting poll analysis from zed; may influence 0mq polling architecture
| [Tuesday 03 August 2010] [08:47:04] <cremes>    http://sheddingbikes.com/posts/1280829388.html
| [Tuesday 03 August 2010] [09:10:22] <sustrik>   yes, seen it
| [Tuesday 03 August 2010] [09:11:01] <sustrik>   if anyone wants to experiment with different polling algorithms 0mq offers a compile time option to enforce usage of a particular one
| [Tuesday 03 August 2010] [09:11:07] <sustrik>   ZMQ_FORCE_POLL
| [Tuesday 03 August 2010] [09:11:12] <sustrik>   ZMQ_FORCE_EPOLL
| [Tuesday 03 August 2010] [09:11:13] <sustrik>   etc.
| [Tuesday 03 August 2010] [09:13:32] <CIA-19>    jzmq: 03Gonzalo Diethelm 07master * r362370e 10/ src/org/zeromq/ZMQ.java : 
| [Tuesday 03 August 2010] [09:13:33] <CIA-19>    jzmq: Added in Socket a reference to Context, so that Java's GC
| [Tuesday 03 August 2010] [09:13:33] <CIA-19>    jzmq: won't deem the Context as unused because there are no references
| [Tuesday 03 August 2010] [09:13:33] <CIA-19>    jzmq: to it. - http://bit.ly/d2uhuU
| [Tuesday 03 August 2010] [10:46:53] <cremes>    any reason zed's suggestion for dynamically shuttling FDs between poll & epoll couldn't be wrapped up in 0mq?
| [Tuesday 03 August 2010] [11:15:04] <sustrik>   cremes: no technical reason
| [Tuesday 03 August 2010] [11:15:15] <sustrik>   however, i am not sure it would help much
| [Tuesday 03 August 2010] [11:16:01] <sustrik>   what 0mq does in its I/O thread is opportunistic polling
| [Tuesday 03 August 2010] [11:16:20] <sustrik>   if it has no data to send
| [Tuesday 03 August 2010] [11:16:28] <sustrik>   it never polls the socket for OUT
| [Tuesday 03 August 2010] [11:16:41] <cremes>    it's probably wise to let zed experiment with the idea (and implementation) a bit before changing the library :)
| [Tuesday 03 August 2010] [11:16:46] <sustrik>   if it does have data to send it polls the socket *once*
| [Tuesday 03 August 2010] [11:16:52] <sustrik>   then writes the data
| [Tuesday 03 August 2010] [11:17:06] <cremes>    sustrik: that seems smart
| [Tuesday 03 August 2010] [11:17:14] <sustrik>   if the write succeeds it assumes the socket is still available for writing
| [Tuesday 03 August 2010] [11:17:18] <sustrik>   so it does not poll again
| [Tuesday 03 August 2010] [11:17:37] <sustrik>   until send fails
| [Tuesday 03 August 2010] [11:17:46] <sustrik>   same thing on the recv side
| [Tuesday 03 August 2010] [11:18:12] <sustrik>   this kind of algorithm would heavily distort any perf results we have
| [Tuesday 03 August 2010] [11:18:30] <sustrik>   however, if you want to go experimenting with different poll types
| [Tuesday 03 August 2010] [11:18:46] <sustrik>   there's the compile time setting (ZMQ_FORCE_EPOLL etc.)
| [Tuesday 03 August 2010] [11:18:57] <sustrik>   so you may do some benchmarking yourself
| [Tuesday 03 August 2010] [11:19:05] <cremes>    sure
| [Tuesday 03 August 2010] [11:19:49] <cremes>    assuming zed's results are trustworthy, i do think it could help 0mq
| [Tuesday 03 August 2010] [11:20:12] <cremes>    let's assume that there are half a dozen 0mq sockets fronting thousands of tcp sockets
| [Tuesday 03 August 2010] [11:20:31] <sustrik>   yes?
| [Tuesday 03 August 2010] [11:20:57] <cremes>    further, assume they are XREQ/XREP pairs
| [Tuesday 03 August 2010] [11:21:40] <cremes>    as the XREQ sends data round-robin to the XREP sockets, the majority of those sockets are idle
| [Tuesday 03 August 2010] [11:22:07] <cremes>    hmmm... as i'm writing this out i see your point...
| [Tuesday 03 August 2010] [11:22:17] <sustrik>   :)
| [Tuesday 03 August 2010] [11:22:28] <cremes>    you wouldn't poll any of the other sockets for writability until their "turn" came up in the round-robin scheme
| [Tuesday 03 August 2010] [11:22:35] <cremes>    never mind!
| [Tuesday 03 August 2010] [11:22:38] <cremes>    ;)
| [Tuesday 03 August 2010] [11:22:38] <sustrik>   right
| [Tuesday 03 August 2010] [11:24:18] <cremes>    so if zed is building mongrel2 on top of 0mq, i'm wondering if he needs to split poll/epoll like he wrote in his latest posting
| [Tuesday 03 August 2010] [11:24:33] <sjampoo>   for the other side (http)
| [Tuesday 03 August 2010] [11:25:07] <cremes>    sjampoo: ah... yes, that makes sense; it would be necessary for the non-0mq sockets
| [Tuesday 03 August 2010] [11:25:44] <cremes>    but then why not make "superpoll" into "opportunisticpoll" and use the same concept as 0mq for polling regular FDs
| [Tuesday 03 August 2010] [11:26:03] <cremes>    perhaps that would result in too many syscalls?
| [Tuesday 03 August 2010] [11:27:02] <sustrik>   sjampoo: as far as i understand the superpoll thing is intended for HTTP sockets
| [Tuesday 03 August 2010] [11:27:06] <sustrik>   not the 0mq sockets
| [Tuesday 03 August 2010] [11:38:42] <sjampoo>   sustrik: yah i believe so too ;)
| [Tuesday 03 August 2010] [11:41:52] <sjampoo>   cremes, I am not sure if he does or doesn't do that. Maybe it has to with how he uses/wants to use libtask, which currently uses poll.
| [Tuesday 03 August 2010] [11:43:44] <sjampoo>   It could be that such an opportunistic poll is difficult to implement in his FSM approach, but then again it could be that i am just talking out of my ass.
| [Tuesday 03 August 2010] [11:44:48] <cremes>    heh
| [Tuesday 03 August 2010] [11:44:56] <cremes>    perhaps zedas will enlighten us in channel
| [Tuesday 03 August 2010] [12:02:28] <Utopiah>   hi #zeromq 
| [Tuesday 03 August 2010] [12:04:00] <Utopiah>   does MQ beats NodeJS and APE Project hands down?
| [Tuesday 03 August 2010] [12:04:14] <sjampoo>   heh. it is something completely different
| [Tuesday 03 August 2010] [12:04:32] <Utopiah>   I take it as a yes
| [Tuesday 03 August 2010] [12:04:44] <sjampoo>   depends on what you want to do ;)
| [Tuesday 03 August 2010] [12:04:49] <sjampoo>   0MQ is a messaging serevr
| [Tuesday 03 August 2010] [12:05:00] <Utopiah>   right
| [Tuesday 03 August 2010] [12:05:02] <sjampoo>   the other two you mentioned are web servers that allow you to write javascript
| [Tuesday 03 August 2010] [12:05:22] <sjampoo>   0MQ has nothing to do with javascript
| [Tuesday 03 August 2010] [12:05:26] <Utopiah>   hmmm they describe themselves as event frameworks with efficient messaging capabilities though AFAIK
| [Tuesday 03 August 2010] [12:05:40] <Utopiah>   JS is just used because it's a fast event loop
| [Tuesday 03 August 2010] [12:05:46] <guido_g>   sjampoo: it's not a server
| [Tuesday 03 August 2010] [12:05:49] <Utopiah>   (thanks to Google V8 for NodeJS at least)
| [Tuesday 03 August 2010] [12:05:57] <sjampoo>   guido, correct
| [Tuesday 03 August 2010] [12:06:08] <sjampoo>   0MQ is a library even.
| [Tuesday 03 August 2010] [12:06:24] <guido_g>   http://www.zeromq.org/docs:user-guide  <- nice read 
| [Tuesday 03 August 2010] [12:06:52] <Utopiah>   "Node's goal is to provide an easy way to build scalable network programs. "
| [Tuesday 03 August 2010] [12:07:27] <Utopiah>   (note that Im *not* a JS/NodeJS/APE advoce, I jsut try to compare with what I kind of know)
| [Tuesday 03 August 2010] [12:07:35] <Utopiah>   s/advoce/advocate/
| [Tuesday 03 August 2010] [12:07:44] <guido_g>   apples and oranges
| [Tuesday 03 August 2010] [12:07:57] <guido_g>   you know both but can't really compare them
| [Tuesday 03 August 2010] [12:09:18] <sjampoo>   Ape and Node.JS allows you to write web application in javascript, they might be able to scale over multiple CPU's but I doubt if they can scale over multiple machines. 0MQ is a messaging library which doesn't understand HTTP but can provide you with the messaging to scale over multiple machine.
| [Tuesday 03 August 2010] [12:10:32] <Utopiah>   right AFAIK NodeJS doesn't aim at being scaled over different machines
| [Tuesday 03 August 2010] [12:12:00] <Utopiah>   hmm Ill watch the video and scan through the docs, thanks
| [Tuesday 03 August 2010] [12:12:57] <Utopiah>   (and grab another coffee ;)
| [Tuesday 03 August 2010] [12:13:25] <sjampoo>   :)
| [Tuesday 03 August 2010] [12:14:24] <Utopiah>   quick question before, are there torrent/virtual file system/freenode-like projects? EC2 projects?
| [Tuesday 03 August 2010] [13:07:20] <cremes>    Utopiah: 0mq is at a lower level than node.js; for a better comparison of 0mq to node.js take a look at a few projects built on top of 0mq that mimic some node.js features...
| [Tuesday 03 August 2010] [13:07:37] <cremes>    git://github.com/mjw9100/zmq_reactor.git
| [Tuesday 03 August 2010] [13:07:52] <cremes>    http://github.com/chuckremes/zmqmachine
| [Tuesday 03 August 2010] [13:08:04] <cremes>    both of those projects implement the reactor pattern using 0mq sockets
| [Tuesday 03 August 2010] [13:08:17] <Utopiah>   because for example NodeJS can't handle UDP?
| [Tuesday 03 August 2010] [13:08:21] <cremes>    the first is in c while the second is in ruby
| [Tuesday 03 August 2010] [13:08:59] <cremes>    i don't know what udp has to do with it
| [Tuesday 03 August 2010] [13:09:52] <Utopiah>   well if you can't handle UDP you're higher level
| [Tuesday 03 August 2010] [13:09:58] <Utopiah>   on the network stack I mean
| [Tuesday 03 August 2010] [13:10:26] <cremes>    i see... yeah, you need to read a bit more about 0mq to understand its purpose
| [Tuesday 03 August 2010] [13:10:51] <cremes>    did you read the link guido_g posted?
| [Tuesday 03 August 2010] [13:12:42] <Utopiah>   yes Im starting to see the point and where it's called
| [Tuesday 03 August 2010] [13:13:52] <Utopiah>   ironically maybe it's easier to read than watch a video to discover it
| [Tuesday 03 August 2010] [13:13:55] <Utopiah>   (at least for me)
| [Tuesday 03 August 2010] [13:14:37] <CIA-19>    pyzmq: 03Brian Granger 07master * rf98ee71 10/ zmq/eventloop/ioloop.py : Minor changes to ioloop.py. - http://bit.ly/d2dwCg
| [Tuesday 03 August 2010] [13:15:17] <cremes>    Utopiah: it's probably worthwhile for you to read through the blog postings and available docs
| [Tuesday 03 August 2010] [13:15:45] <cremes>    we're a pretty friendly bunch in here but it's hard to explain 0mq from A to Z when there are already lots of words available on the website ;)
| [Tuesday 03 August 2010] [13:16:41] <Utopiah>   don't worry I won't ask for an over the shoulder tutorial
| [Tuesday 03 August 2010] [13:17:18] <Utopiah>   but it gives me a quick boost to situate sth new against sth related I know
| [Tuesday 03 August 2010] [13:18:15] <cremes>    right; feel free to ask questions as you peruse the docs
| [Tuesday 03 August 2010] [13:18:49] <cremes>    i'll try to answer if i'm around/free or there are about 5 or 6 other folks who are usually in channel around this time who may speak up
| [Tuesday 03 August 2010] [16:40:12] <MrEvil>    if more messages are being sent faster than the subscribers can process them are the messages queued by the sender or the receiver?
| [Tuesday 03 August 2010] [16:43:21] <MrEvil>    and is this queue backed by a the filesystem?  I'm not looking for anything complicated.  If the items scheduled to be sent or items received but not yet processed were backed by a memory mapped file I would be happy.
| [Tuesday 03 August 2010] [16:47:44] <sustrik>   MrEvil: yes, they are queued
| [Tuesday 03 August 2010] [16:48:16] <sustrik>   you can set ZMQ_HWM socket option to limit the size of the queue in the memory
| [Tuesday 03 August 2010] [16:48:33] <sustrik>   when the size is reached messages start to be dropped
| [Tuesday 03 August 2010] [16:48:42] <sustrik>   however, you can set ZMQ_SWAP socket option
| [Tuesday 03 August 2010] [16:49:02] <sustrik>   if set, messages start to be offloaded on disk in case HWM is reached
| [Tuesday 03 August 2010] [16:49:12] <sustrik>   instead of being dropped
| [Tuesday 03 August 2010] [16:53:32] <MrEvil>    what happens if a process crashes?  are those messages lost?
| [Tuesday 03 August 2010] [22:02:47] <ateTate>   From experiementing w/ zeromq today, it seems like if a request socket does not successfully recieve after sending, the message is not sent.  Why is that?
| [Wednesday 04 August 2010] [08:45:16] <CIA-19>  zeromq2: 03Pieter Hintjens 07master * r11a410b 10/ (11 files in 2 dirs): 
| [Wednesday 04 August 2010] [08:45:16] <CIA-19>  zeromq2: Renamed ZMQ_UPSTREAM to ZMQ_PULL, and ZMQ_DOWNSTREAM to ZMQ_PUSH. Left the old
| [Wednesday 04 August 2010] [08:45:16] <CIA-19>  zeromq2: definitions as aliases, to be removed in release 3.0. Also renamed the source
| [Wednesday 04 August 2010] [08:45:16] <CIA-19>  zeromq2: files implementing these two socket types. This change does not break existing
| [Wednesday 04 August 2010] [08:45:16] <CIA-19>  zeromq2: applications nor bindings, but allows us to fix the documentation and user guide
| [Wednesday 04 August 2010] [08:45:17] <CIA-19>  zeromq2: now, rather than keeping the old (confusing) names. - http://bit.ly/bXUNom
| [Wednesday 04 August 2010] [08:45:18] <CIA-19>  zeromq2: 03Pieter Hintjens 07master * rf575f25 10/ doc/zmq_device.txt : Added man page for the zmq_device method - http://bit.ly/cOwku4
| [Wednesday 04 August 2010] [08:45:18] <CIA-19>  zeromq2: 03Pieter Hintjens 07master * r6cd9030 10/ doc/Makefile.am : Added clean target that deletes generated man pages - http://bit.ly/9jsaSI
| [Wednesday 04 August 2010] [08:45:19] <CIA-19>  zeromq2: 03Pieter Hintjens 07master * r77a3c36 10/ (33 files): 
| [Wednesday 04 August 2010] [08:45:20] <CIA-19>  zeromq2: Various changes to documentation project:
| [Wednesday 04 August 2010] [08:45:20] <CIA-19>  zeromq2: * Added documentation for zmq_deviced, which we're developing
| [Wednesday 04 August 2010] [08:45:21] <CIA-19>  zeromq2: * Created consistent page footer in documentation template
| [Wednesday 04 August 2010] [08:45:21] <CIA-19>  zeromq2: * Page footer notes doc authors and copyright statement - http://bit.ly/d2130a
| [Wednesday 04 August 2010] [08:57:16] <CIA-19>  zeromq2: 03Pieter Hintjens 07master * rc51de31 10/ doc/Makefile.am : Reverting 'clean' change to Makefile - http://bit.ly/93Hkm2
| [Wednesday 04 August 2010] [09:07:28] <CIA-19>  zeromq2: 03Pieter Hintjens 07master * r6ff1939 10/ (4 files): Removed empty man pages for old standalone devices - http://bit.ly/csTExH
| [Wednesday 04 August 2010] [09:27:23] <mato>    pieterh: ok, i'm here now
| [Wednesday 04 August 2010] [09:28:13] <pieterh> mato: any particular advantage in breaking manual text into lines?
| [Wednesday 04 August 2010] [09:28:19] <mato>    pieterh: manual line breaks mean that a) the doc text can be meaningfully read with less in a terminal b) i can edit it with vim/emacs/other standard unixy editor
| [Wednesday 04 August 2010] [09:28:41] <mato>    pieterh: also, the long lines don't show up on github nicely
| [Wednesday 04 August 2010] [09:28:50] <pieterh> ok, i
| [Wednesday 04 August 2010] [09:28:50] <mato>    see e.g. http://github.com/zeromq/zeromq2/blob/master/doc/zmq_deviced.txt
| [Wednesday 04 August 2010] [09:29:00] <pieterh> i'll buy the github argument
| [Wednesday 04 August 2010] [09:29:23] <mato>    hey, it's a .txt file... 80 columns is your friend :)
| [Wednesday 04 August 2010] [09:29:36] <pieterh> perhaps in 1992, yes
| [Wednesday 04 August 2010] [09:29:50] <pieterh> it's been a long long time since 80 columns had any mystical value
| [Wednesday 04 August 2010] [09:29:57] <guido_g> no, noone knows how wide you editor windows was
| [Wednesday 04 August 2010] [09:29:58] <pieterh> everyone knows today the magic number is 140
| [Wednesday 04 August 2010] [09:30:30] <mato>    well, please just use 80 column text, thanks
| [Wednesday 04 August 2010] [09:30:46]    * pieterh needs to find a new text editor capable of reformatting text
| [Wednesday 04 August 2010] [09:30:59] <mato>    how about an old one? vim? emacs? :)
| [Wednesday 04 August 2010] [09:31:11] <guido_g> :)
| [Wednesday 04 August 2010] [09:31:17]    * pieterh learns emacs, goes back in time to kill younger self
| [Wednesday 04 August 2010] [09:31:38] <mato>    i'm sure even gedit or whatever it's called can format text :)
| [Wednesday 04 August 2010] [09:35:15] <pieterh> mato: would you review zmq_device(3) in trunk and confirm it makes sense?
| [Wednesday 04 August 2010] [09:35:57] <mato>    pieterh: ok, but i'll have to reformat it :)
| [Wednesday 04 August 2010] [09:36:05] <pieterh> i'll do that, mato
| [Wednesday 04 August 2010] [09:36:10] <mato>    pieterh: also, it's 'master' not trunk :)
| [Wednesday 04 August 2010] [09:36:13] <pieterh> am in process of doing so
| [Wednesday 04 August 2010] [09:36:17] <mato>    thx
| [Wednesday 04 August 2010] [09:36:19] <pieterh> and yes, it's master, not trunk, my bad
| [Wednesday 04 August 2010] [09:44:00] <pieterh> uhm, mato
| [Wednesday 04 August 2010] [09:44:21] <mato>    yes?
| [Wednesday 04 August 2010] [09:44:23] <pieterh> there are quite a few instances of lines longer than 80 chars in the text files
| [Wednesday 04 August 2010] [09:44:31] <pieterh> i'll fix them all up
| [Wednesday 04 August 2010] [09:44:42] <mato>    there are places where due to syntax limitations in asciidoc you can't wrap lines properly
| [Wednesday 04 August 2010] [09:44:50] <mato>    please wrap "normal text body" properly
| [Wednesday 04 August 2010] [09:44:51] <mato>    thx
| [Wednesday 04 August 2010] [09:45:03] <pieterh> ? asciidoc lets you do it properly
| [Wednesday 04 August 2010] [09:45:26] <pieterh> also its "its" not "it's" when you use the possessive
| [Wednesday 04 August 2010] [09:45:33] <pieterh> grammarnazi is on the loose
| [Wednesday 04 August 2010] [09:45:42] <mato>    i think you are referring mainly to the SYNOPSIS section?
| [Wednesday 04 August 2010] [09:45:58] <pieterh> nope, random text
| [Wednesday 04 August 2010] [09:46:00] <mato>    and unfortunately those don't render properly when wrapped
| [Wednesday 04 August 2010] [09:46:10] <pieterh> egrep ".{80,}" *.txt is your friend
| [Wednesday 04 August 2010] [09:46:30] <pieterh> i'll fix it all up and double check it renders properly when wrapped
| [Wednesday 04 August 2010] [09:47:10] <mato>    what i see are mostly SYNOPSIS sections and definition lists
| [Wednesday 04 August 2010] [09:47:33] <mato>    if you can get them to format properly when wrapped (check manpage result *and* HTML) then by all means fix them
| [Wednesday 04 August 2010] [09:48:16] <pieterh> let's give it a shot :-)
| [Wednesday 04 August 2010] [09:48:26] <pieterh> how do I generate the html?
| [Wednesday 04 August 2010] [09:48:40] <mato>    make dist will do it
| [Wednesday 04 August 2010] [09:49:19] <pieterh> "no rule to make target dist" when I run that in /doc
| [Wednesday 04 August 2010] [09:49:21] <pieterh> np
| [Wednesday 04 August 2010] [09:49:27] <mato>    make dist at toplevel
| [Wednesday 04 August 2010] [09:49:32] <pieterh> ack
| [Wednesday 04 August 2010] [09:49:41] <pieterh> man pages format correctly, will now check html
| [Wednesday 04 August 2010] [09:50:14] <pieterh> seems fine
| [Wednesday 04 August 2010] [09:50:44] <mato>    hmm, can you commit it, i'll double-check here (since i build releases on this machine)
| [Wednesday 04 August 2010] [09:50:52] <mato>    that's if you're done...
| [Wednesday 04 August 2010] [09:51:10] <pieterh> tried on some docs, am now doing rest and checking individually
| [Wednesday 04 August 2010] [09:51:30] <mato>    also i assume you're not going to reformat *everything* just the wrong bits?
| [Wednesday 04 August 2010] [09:51:43] <pieterh> only the lines that are more than 80 chars, mato
| [Wednesday 04 August 2010] [09:51:54] <mato>    thx
| [Wednesday 04 August 2010] [09:51:57] <pieterh> also some spelling mistakes as i find them
| [Wednesday 04 August 2010] [09:52:11] <pieterh> minor stuff
| [Wednesday 04 August 2010] [09:52:13]    * mato ran the docs through a spell checker once :-)
| [Wednesday 04 August 2010] [09:52:37] <mato>    (a UK spell checker, to be precise)
| [Wednesday 04 August 2010] [09:52:56] <pieterh> its/it's in a few places
| [Wednesday 04 August 2010] [09:53:17] <mato>    ah, sorry, i have a problem with that one for some reason
| [Wednesday 04 August 2010] [09:53:39] <pieterh> me too, i get it right but always think i got it wrong
| [Wednesday 04 August 2010] [09:53:49] <pieterh> just remember, his, hers, its
| [Wednesday 04 August 2010] [09:53:58] <pieterh> not hi's her's it's
| [Wednesday 04 August 2010] [09:54:11] <pieterh> and it's, they're, we're, you're
| [Wednesday 04 August 2010] [09:54:18] <pieterh> not its, theyre, were, youre
| [Wednesday 04 August 2010] [09:54:20] <pieterh> :-)
| [Wednesday 04 August 2010] [09:54:30] <pieterh> english can be remarkably consistent
| [Wednesday 04 August 2010] [10:07:14] <CIA-19>  zeromq2: 03Pieter Hintjens 07master * r13f3481 10/ (10 files): 
| [Wednesday 04 August 2010] [10:07:15] <CIA-19>  zeromq2: Further cleanups on reference manual
| [Wednesday 04 August 2010] [10:07:15] <CIA-19>  zeromq2: - fixed unwrapped text in new man pages
| [Wednesday 04 August 2010] [10:07:15] <CIA-19>  zeromq2: - fixed over-long lines in older pages, where possible
| [Wednesday 04 August 2010] [10:07:15] <CIA-19>  zeromq2: - removed reference to old standalong devices from index page
| [Wednesday 04 August 2010] [10:07:15] <CIA-19>  zeromq2: - added refernce to new zmq_device[3] documented from index page
| [Wednesday 04 August 2010] [10:07:15] <CIA-19>  zeromq2: - some minor spelling corrections - http://bit.ly/d9NCpE
| [Wednesday 04 August 2010] [10:07:20] <pieterh> mato: ok, done, double-checked, and committed
| [Wednesday 04 August 2010] [10:07:36] <pieterh> wow, CIA-19 got there before me :-)
| [Wednesday 04 August 2010] [10:07:44] <mato>    :-)
| [Wednesday 04 August 2010] [10:09:08] <mato>    -.Polling indefinitely for input events on both a 0MQ socket and a standard socket.
| [Wednesday 04 August 2010] [10:09:11] <mato>    103     
| [Wednesday 04 August 2010] [10:09:14] <mato>    +.Polling indefinitely for input events on both a 0MQ socket and a TCP socket.
| [Wednesday 04 August 2010] [10:09:30] <mato>    pieterh: perhaps pedantic, but 'socket' can be any old socket :)
| [Wednesday 04 August 2010] [10:09:34] <mato>    no big deal
| [Wednesday 04 August 2010] [10:09:47] <mato>    anyhow, thx
| [Wednesday 04 August 2010] [10:10:03] <mato>    pieterh: which did you want reviewed? zmq_device?
| [Wednesday 04 August 2010] [10:16:48] <mato>    pieterh: re zmq_device:
| [Wednesday 04 August 2010] [10:17:10] <mato>    pieterh: you talk about "proxy" and "broker", but only provide examples for the 2nd one
| [Wednesday 04 August 2010] [10:19:04] <mato>    pieterh: also, not sure a :: list is the best way to format the model list. I would have probably used either subsections, or *XXX model*. ...Body text...
| [Wednesday 04 August 2010] [10:19:20] <mato>    pieterh: mostly I just don't just the lowercase "proxy" and "broker" :)
| [Wednesday 04 August 2010] [10:20:15] <mato>    pieterh: also the references to "downstream" are a bit confusing, but i don't have a better idea
| [Wednesday 04 August 2010] [10:20:18] <mato>    pieterh: that's all, thx
| [Wednesday 04 August 2010] [10:55:08] <pieterh> mato: re
| [Wednesday 04 August 2010] [10:55:24] <pieterh> zmq_device(3) covers the core of how devices work
| [Wednesday 04 August 2010] [10:55:38] <pieterh> zmq_deviced(1) covers the api for the command line tool
| [Wednesday 04 August 2010] [10:57:11] <pieterh> thanks for the review, i'll fix the text
| [Wednesday 04 August 2010] [11:07:31] <CIA-19>  zeromq2: 03Pieter Hintjens 07master * r96bcc9e 10/ doc/zmq_device.txt : 
| [Wednesday 04 August 2010] [11:07:31] <CIA-19>  zeromq2: Small improvements to zmq_device(3) page
| [Wednesday 04 August 2010] [11:07:31] <CIA-19>  zeromq2: * Clarified broker model and proxy model
| [Wednesday 04 August 2010] [11:07:31] <CIA-19>  zeromq2: * Added example of proxy model - http://bit.ly/aH2jNL
| [Wednesday 04 August 2010] [12:58:24] <cremes>  fyi, http://github.com/rabbitmq/rmq-0mq
| [Wednesday 04 August 2010] [14:02:59] <erickt>  good morning! would it be possible to get dates displayed on the zeromq.org documents? I've found myself looking at the old 1.0 era docs and getting confused :)
| [Wednesday 04 August 2010] [14:09:36] <sustrik> erickt: please do complain on the mailing list, someone has to go through all the content and remove out-of-date pieces
| [Wednesday 04 August 2010] [14:10:01] <sustrik> cremes: yes, that's 0MQ/AMQP bridge project
| [Wednesday 04 August 2010] [14:10:12] <sustrik> see its wiki for design diagrams
| [Wednesday 04 August 2010] [14:10:21] <sustrik> however, implementation is still missing :)
| [Wednesday 04 August 2010] [14:10:45] <cremes>  yes, i just wanted to highlight it for folks lurking in channel
| [Wednesday 04 August 2010] [14:23:03] <erickt>  sustrik: sure
| [Wednesday 04 August 2010] [14:24:17] <erickt>  i was just hoping that the wiki software had an option to turn on the dates :)
| [Wednesday 04 August 2010] [14:35:52] <pieterh> erickt: it does
| [Wednesday 04 August 2010] [14:36:06] <pieterh> i will need to modify some templates
| [Wednesday 04 August 2010] [14:36:34] <pieterh> give me a minute, I'll try this on the whitepapers section...
| [Wednesday 04 August 2010] [14:37:47] <erickt>  pieterh: thank you so much
| [Wednesday 04 August 2010] [14:45:31] <pieterh> erickt: small catch
| [Wednesday 04 August 2010] [14:45:51] <pieterh> it works, see http://www.zeromq.org/docs:projects
| [Wednesday 04 August 2010] [14:46:12] <pieterh> however for the whitepapers it'll mean editing every single whitepaper to remove cruft
| [Wednesday 04 August 2010] [14:46:14] <pieterh> hmm...
| [Wednesday 04 August 2010] [14:46:36]    * pieterh will have to leave the cruft in the whitepapers and work around it
| [Wednesday 04 August 2010] [14:46:57] <erickt>  thanks pieterh
| [Wednesday 04 August 2010] [14:47:23] <erickt>  i'm used to the docs enough that I'm not running into too many problems, I just figured any newbies would run into the same trouble
| [Wednesday 04 August 2010] [14:48:00] <pieterh> it'd be better to delete old stuff and move speculation to a separate category, don't you think?
| [Wednesday 04 August 2010] [14:48:46] <pieterh> i'll add the date/time to the category templates now
| [Wednesday 04 August 2010] [14:48:52] <pieterh> and then clean up the entire wiki later
| [Wednesday 04 August 2010] [14:49:02] <pieterh> there's no reason for 1.0 docs to still be there IMO
| [Wednesday 04 August 2010] [14:51:11] <erickt>  sure that seems reasonable
| [Wednesday 04 August 2010] [15:09:54] <pieterh> sustrik: i've started a page to capture ideas for 0MQ/3.0
| [Wednesday 04 August 2010] [15:10:11] <pieterh> i assume API changes as you proposed for simpler message passing will require a major version
| [Wednesday 04 August 2010] [15:10:50] <sustrik> do we have a versioning policy?
| [Wednesday 04 August 2010] [15:10:58] <pieterh> http://www.zeromq.org/docs:3-0
| [Wednesday 04 August 2010] [15:11:17] <pieterh> i think there was consensus on versioning, yes
| [Wednesday 04 August 2010] [15:11:30] <sustrik> is it written down somewher
| [Wednesday 04 August 2010] [15:11:38] <pieterh> it's in the mailing list :-)
| [Wednesday 04 August 2010] [15:11:44] <sustrik> i, for example, have no idea what the outcome was
| [Wednesday 04 August 2010] [15:11:48] <sustrik> which email?
| [Wednesday 04 August 2010] [15:11:59] <pieterh> i was being somewhat facetious
| [Wednesday 04 August 2010] [15:12:03] <sustrik> i know
| [Wednesday 04 August 2010] [15:12:10] <pieterh> it *is* the list but that is not a database
| [Wednesday 04 August 2010] [15:12:25] <pieterh> i will write a versioning policy strawman, beat up as desired
| [Wednesday 04 August 2010] [15:12:32] <sustrik> ok
| [Wednesday 04 August 2010] [15:12:42] <pieterh> to cover the product version and API, not library versioning
| [Wednesday 04 August 2010] [15:12:54] <sustrik> yes, sure
| [Wednesday 04 August 2010] [15:13:02] <sustrik> library versioning is a different kind of beast
| [Wednesday 04 August 2010] [15:13:37] <sustrik> as for 3.0 i would like to have sockets to be represented as 'int' instead of 'void*'
| [Wednesday 04 August 2010] [15:13:49] <sustrik> not a pleasant change for users...
| [Wednesday 04 August 2010] [15:15:08] <sustrik> btw
| [Wednesday 04 August 2010] [15:15:09] <sustrik> http://www.zeromq.org/whitepapers:traffic-monitoring-v20
| [Wednesday 04 August 2010] [15:15:14] <sustrik> seems to have two tocs
| [Wednesday 04 August 2010] [15:23:48] <pieterh> all the whitepapers have two tocs until i get around to editing them all
| [Wednesday 04 August 2010] [15:24:09] <pieterh> i've started the policy page: http://www.zeromq.org/docs:policies
| [Wednesday 04 August 2010] [15:24:36] <pieterh> sockets as ints is a great idea and necessary for kernelization
| [Wednesday 04 August 2010] [15:24:46] <pieterh> would you add that to the 3.0 page?
| [Wednesday 04 August 2010] [15:54:31] <pieterh> sustrik: i'm cleaning up all the whitepapers
| [Wednesday 04 August 2010] [16:04:30] <sustrik> ok, will have a look
| [Wednesday 04 August 2010] [16:05:04] <sustrik> btw, mentioning author in the date header is confusing
| [Wednesday 04 August 2010] [16:05:08] <sustrik> erlag binding:
| [Wednesday 04 August 2010] [16:05:10] <sustrik> Written: 2010.05.15 by pieterh
| [Wednesday 04 August 2010] [16:05:10] <sustrik> Revised: 2010.08.4 by pieterh
| [Wednesday 04 August 2010] [16:05:21] <sustrik> date would do imo
| [Wednesday 04 August 2010] [16:08:06] <pieterh> ok, now i've gone through all the whitepapers
| [Wednesday 04 August 2010] [16:08:24] <pieterh> deleted (moved to deleted:whatever) the old binding descriptions
| [Wednesday 04 August 2010] [16:08:34] <pieterh> other historical ones are clearly marked
| [Wednesday 04 August 2010] [16:08:36] <pieterh> http://www.zeromq.org/navigator/order/title/category/whitepapers/
| [Wednesday 04 August 2010] [16:08:40] <pieterh> gives you a navigator
| [Wednesday 04 August 2010] [16:08:57] <pieterh> i'll remove the 'by' info from the templates
| [Wednesday 04 August 2010] [16:09:10] <pieterh> but the advantage is to know who to blame
| [Wednesday 04 August 2010] [16:09:22] <pieterh> please confirm you want that gone
| [Wednesday 04 August 2010] [16:11:34] <sustrik> well, you'll remove it yourself once people start spamming you about erlang binding
| [Wednesday 04 August 2010] [16:12:39] <pieterh> well, it's gone now
| [Wednesday 04 August 2010] [16:13:06] <pieterh> it is nicer to not have names overtly visible on every piece IMO
| [Wednesday 04 August 2010] [16:13:10] <pieterh> there is the history
| [Wednesday 04 August 2010] [16:14:11] <sustrik> my point was that creator & last editor != author
| [Wednesday 04 August 2010] [16:14:32] <sustrik> we may add author to the heading of each document
| [Wednesday 04 August 2010] [16:14:51] <pieterh> in most normal cases, last author and creator do represent the people to contact
| [Wednesday 04 August 2010] [16:14:56] <pieterh> this kind of mass update is very rare
| [Wednesday 04 August 2010] [16:15:08] <pieterh> it's only because we did not template the pages originally
| [Wednesday 04 August 2010] [16:15:26] <pieterh> templates allow a clean split between structure and content
| [Wednesday 04 August 2010] [16:15:36] <pieterh> the whole site is now properly templated i think
| [Wednesday 04 August 2010] [16:15:44] <sustrik> so why are you creator of erlang binding?
| [Wednesday 04 August 2010] [16:15:50] <pieterh> because i created that page :-)
| [Wednesday 04 August 2010] [16:15:53] <pieterh> obviously
| [Wednesday 04 August 2010] [16:15:58] <sustrik> you see
| [Wednesday 04 August 2010] [16:16:07] <sustrik> my point
| [Wednesday 04 August 2010] [16:16:29] <pieterh> no, normally it would show, accurately, person A creating, and person B maintaining
| [Wednesday 04 August 2010] [16:16:45] <pieterh> and you could ask person A, "why did you create the page HERE"
| [Wednesday 04 August 2010] [16:16:52] <pieterh> and person B, "why does it say XYZ?"
| [Wednesday 04 August 2010] [16:16:56] <sustrik> that's not the state of afairs now
| [Wednesday 04 August 2010] [16:17:09] <pieterh> indeed, because exceptionally, i had to restructure 50+ pages
| [Wednesday 04 August 2010] [16:17:10] <sustrik> it'll just mention either you or me
| [Wednesday 04 August 2010] [16:17:18] <sustrik> no much point
| [Wednesday 04 August 2010] [16:17:28] <pieterh> do you understand how the templates work?
| [Wednesday 04 August 2010] [16:17:38] <sustrik> yes, but look at the outcome
| [Wednesday 04 August 2010] [16:17:51] <pieterh> sigh
| [Wednesday 04 August 2010] [16:17:54] <sustrik> right now, those two fields are just garbage
| [Wednesday 04 August 2010] [16:18:02] <pieterh> this is a one off that will be fixed as soon as people start to edit their pages again
| [Wednesday 04 August 2010] [16:18:07] <pieterh> anyhow, it's moot
| [Wednesday 04 August 2010] [16:18:13] <pieterh> the names are gone
| [Wednesday 04 August 2010] [16:18:19] <sustrik> ok, let's add the two fields back once that happens
| [Wednesday 04 August 2010] [16:18:23] <pieterh> i'm only explaining their value in normal circumstances
| [Wednesday 04 August 2010] [16:18:32] <sustrik> sure, i understand
| [Wednesday 04 August 2010] [16:19:03] <pieterh> it's like saying "the knife cut me" and then arguing with the person telling you to not hold the sharp end
| [Wednesday 04 August 2010] [16:19:20] <pieterh> wikidot has powerful tools for doing this right
| [Wednesday 04 August 2010] [16:19:35] <pieterh> my fault for not doing this reorganization earlier
| [Wednesday 04 August 2010] [16:20:02] <sustrik> the point is that right now the normal circumstances are the norm
| [Wednesday 04 August 2010] [16:20:02] <sustrik> not the norm
| [Wednesday 04 August 2010] [16:20:02] <sustrik> so what you see is garbage
| [Wednesday 04 August 2010] [16:20:03] <sustrik> when normal circumstances become normal
| [Wednesday 04 August 2010] [16:20:03] <sustrik> it would be easy to modify the templete
| [Wednesday 04 August 2010] [16:20:20] <pieterh> indeed
| [Wednesday 04 August 2010] [16:20:24] <pieterh> templates are excellent
| [Wednesday 04 August 2010] [16:20:36] <pieterh> i strongly advise to never create wikidot pages without templates
| [Wednesday 04 August 2010] [16:21:03] <pieterh> its like trying to do everything using ZMQ_PAIR
| [Wednesday 04 August 2010] [16:21:11] <pieterh> mixed with semaphores
| [Wednesday 04 August 2010] [16:22:07] <pieterh> there is a long and somewhat painful discussion on HyBi
| [Wednesday 04 August 2010] [16:22:14] <pieterh> (IETF list discussing WebSockets)
| [Wednesday 04 August 2010] [16:22:20] <pieterh> including framing and multiplexing
| [Wednesday 04 August 2010] [16:22:40] <pieterh> i am trying to suggest 0MQ-style framing and delegating multiplexing to SCTP
| [Wednesday 04 August 2010] [16:24:11] <pieterh> i mention this because at some point 0MQ is going to bump gently against WebSockets
| [Wednesday 04 August 2010] [16:27:15]    * sustrik has no idea what web sockets are
| [Wednesday 04 August 2010] [16:27:42] <Utopiah> the future of the intarwebs
| [Wednesday 04 August 2010] [16:28:00] <Utopiah> http://dev.w3.org/html5/websockets/
| [Wednesday 04 August 2010] [16:28:03] <Nwallins>    they make webserver-initiated conversations (as opposed to client-initiated with HTTP req/resp) easier
| [Wednesday 04 August 2010] [16:28:26] <pieterh> it would be worth understanding websockets briefly, or at least the goals behind it
| [Wednesday 04 August 2010] [16:28:56] <pieterh> it is supposed to provide something as close as possible to TCP (async streaming) to browsers talking to servers
| [Wednesday 04 August 2010] [16:29:07] <sustrik> once i have some time free i'll have a look
| [Wednesday 04 August 2010] [16:29:24] <pieterh> its is pushed by WHATWG, representing browser builders, esp. Google
| [Wednesday 04 August 2010] [16:29:32] <pieterh> s/its/it's/
| [Wednesday 04 August 2010] [16:29:40] <pieterh> s/is//
| [Wednesday 04 August 2010] [16:29:53] <pieterh> i'll explain over our next beer
| [Wednesday 04 August 2010] [16:29:57] <sustrik> is there any one-to-many concept involved?
| [Wednesday 04 August 2010] [16:30:04] <pieterh> no
| [Wednesday 04 August 2010] [16:30:05] <pieterh> tcp
| [Wednesday 04 August 2010] [16:30:17] <pieterh> no patterns except peer
| [Wednesday 04 August 2010] [16:30:22] <sustrik> then it shouldn't be hard to layer 0mq semantics on top of it
| [Wednesday 04 August 2010] [16:30:36] <sustrik> the actual wire format doesn't matter that much
| [Wednesday 04 August 2010] [16:30:40] <pieterh> yes, that's for sure
| [Wednesday 04 August 2010] [16:30:59] <pieterh> but websockets risks being too close to the application
| [Wednesday 04 August 2010] [16:41:25] <sjampoo> Mixing websockets and zeromq is like a baileys cola. I don't think they go well together.
| [Wednesday 04 August 2010] [16:42:58] <sjampoo> Also, i'm not sure if there is much to be gained as it needs to be transported over HTTP anyway. The connection is always initiated from the client as a regular HTTP connection and can then be upgraded to allow streaming of data frames both ways. 
| [Wednesday 04 August 2010] [16:44:08] <sjampoo> A ZeroMQ client implemented in JS would be cute, but you would end up needing a central (proxy) server anyway.
| [Wednesday 04 August 2010] [16:46:39] <sjampoo> Actually, If I had to pick I would say ZeroMQ is more like a Vodka, transparent, mixes well with everything and no bad hangovers.
| [Wednesday 04 August 2010] [16:47:34] <Nwallins>    well, vodka cola sounds pretty bad ;)
| [Wednesday 04 August 2010] [16:48:02] <sjampoo> It is not that bad really ;) 
| [Wednesday 04 August 2010] [16:49:31] <Nwallins>    plus, martinis are high-powered, sophisticated tools that promote communication
| [Wednesday 04 August 2010] [16:49:49] <Nwallins>    though I must admit a gin preference, there
| [Wednesday 04 August 2010] [16:50:30] <sjampoo> with tonic? 
| [Wednesday 04 August 2010] [16:50:51] <Nwallins>    just olives :)
| [Wednesday 04 August 2010] [16:52:01] <sjampoo> Hmmm, did you know that they say that Gin Tonic was the reason the british where able to invade Africa? 
| [Wednesday 04 August 2010] [16:52:14] <Nwallins>    the quinine, I heard
| [Wednesday 04 August 2010] [16:52:32] <sjampoo> Yes, it worked well against Malaria and the Gin made it drinkable.
| [Wednesday 04 August 2010] [16:53:10] <Nwallins>    usually it's the other way around.  mixer makes the drink palatable, and then you get sick ;)
| [Wednesday 04 August 2010] [18:26:17] <ateTate> I want to establish communication between two public webservers.  What's a good way to ensure that messages recieved by my REP handler are from one of my servers and not someone else?
| [Wednesday 04 August 2010] [18:28:52] <Nwallins>    http://lists.zeromq.org/pipermail/zeromq-dev/2010-July/004354.html
| [Thursday 05 August 2010] [02:13:24] <hvd>  does anybody know where i can grab the examples?
| [Thursday 05 August 2010] [02:13:44] <hvd>  i can't seem to find them in the source download, not sure if i'm missing anything....
| [Thursday 05 August 2010] [02:14:49] <TheEffigy>    i didn't think there was anything other than http://www.zeromq.org/docs:cookbook
| [Thursday 05 August 2010] [02:16:14] <hvd>  i was going through this: http://www.zeromq.org/code:examples-chat
| [Thursday 05 August 2010] [02:16:41] <sjampoo>  hvd, you can find that on GITHUB http://github.com/zeromq
| [Thursday 05 August 2010] [02:17:10] <hvd>  great!
| [Thursday 05 August 2010] [02:17:16] <sjampoo>  I am not sure if and here it is included in the source package
| [Thursday 05 August 2010] [02:17:17] <hvd>  thats so much! you rock!
| [Thursday 05 August 2010] [02:17:44] <hvd>  yeah, i don't believe its included in the source download from the website
| [Thursday 05 August 2010] [02:18:01] <hvd>  which really confused me, because no other place pointed me to the right direction
| [Thursday 05 August 2010] [02:18:06] <hvd>  just something to think about...
| [Thursday 05 August 2010] [02:21:42] <sjampoo>  Hrm that tutorial is outdated
| [Thursday 05 August 2010] [11:30:50] <mato> sustrik: i found a bug in zmq::signaler_t
| [Thursday 05 August 2010] [11:31:01] <sustrik>  ?
| [Thursday 05 August 2010] [11:31:04] <mato> sustrik: it's not EINTR-resistant
| [Thursday 05 August 2010] [11:31:32] <sustrik>  well, why not fix it then?
| [Thursday 05 August 2010] [11:31:48] <mato> have a patch, d'you want it on the mailing list for review first?
| [Thursday 05 August 2010] [11:32:19] <sustrik>  the policy is send everything to mailing list first
| [Thursday 05 August 2010] [11:32:30] <sustrik>  we should start to abide by it outselves
| [Thursday 05 August 2010] [11:32:43] <mato> well, kind of :)
| [Thursday 05 August 2010] [11:32:58] <mato> obviously, you're the master of the code, no need to ask for review unless you need it :)
| [Thursday 05 August 2010] [11:33:05] <mato> same as i would do with the autoconf stuff...
| [Thursday 05 August 2010] [11:33:22] <mato> anyway, i'll send it to the mailing list since it exposes other issues
| [Thursday 05 August 2010] [11:33:26] <sustrik>  it's a matter of process
| [Thursday 05 August 2010] [11:33:31] <sustrik>  it should be transparent
| [Thursday 05 August 2010] [11:33:38] <sustrik>  even it there's no real reason
| [Thursday 05 August 2010] [11:33:48] <mato> not for every commit, don't be silly
| [Thursday 05 August 2010] [11:34:02] <sustrik>  how would you manage the codebase then?
| [Thursday 05 August 2010] [11:34:19] <mato> well, there will always be two groups of people
| [Thursday 05 August 2010] [11:34:38] <mato> one, the core developers (those who have access to git), who have experience with the codebase and are trusted to not do anything silly
| [Thursday 05 August 2010] [11:35:16] <mato> there is no reason why these people working on fixing bugs or work that does not require discussion (i.e. no API changes) should send email to the mailing list
| [Thursday 05 August 2010] [11:35:21] <sustrik>  hm, haven't pieter just committed something that broke MSVC build?
| [Thursday 05 August 2010] [11:35:26] <mato> not automatically anyway
| [Thursday 05 August 2010] [11:35:40] <mato> i don't really count pieter as a trusted committer to be honest
| [Thursday 05 August 2010] [11:35:51] <mato> but there is nothing i can do since ... well... you know...
| [Thursday 05 August 2010] [11:36:08] <sustrik>  my point is that review is good
| [Thursday 05 August 2010] [11:36:10] <sustrik>  always
| [Thursday 05 August 2010] [11:36:23] <mato> yes, of course, but people can always do this by voluntarily following git
| [Thursday 05 August 2010] [11:36:32] <mato> or asking for review when they need it
| [Thursday 05 August 2010] [11:36:37] <mato> otherwise it does not scale
| [Thursday 05 August 2010] [11:37:12] <sustrik>  dunno, we should think about it a bit more
| [Thursday 05 August 2010] [11:37:20] <mato> well, i mean to document the policy
| [Thursday 05 August 2010] [11:37:21] <sustrik>  if your patch is trivial, just commit it
| [Thursday 05 August 2010] [11:37:23] <mato> but i have work to do :)
| [Thursday 05 August 2010] [11:37:38]     * sustrik is back to big shutdown rewrite
| [Thursday 05 August 2010] [11:37:49] <mato> the patch itself is trivial and correct, but exposes other stuff related precisely to shutdown, so i'll send it to the list
| [Thursday 05 August 2010] [11:37:53] <mato> so that you can comment on it
| [Thursday 05 August 2010] [11:37:57] <sustrik>  wondering who's going to review that
| [Thursday 05 August 2010] [11:38:04] <mato> martin hurton?
| [Thursday 05 August 2010] [11:38:21] <sustrik>  it's touches like 50% of the codebase :(
| [Thursday 05 August 2010] [11:38:25] <mato> i would but i'm not sure that i understand enough of the codebase
| [Thursday 05 August 2010] [11:38:44] <mato> ask martin hurton to review it
| [Thursday 05 August 2010] [11:38:45] <sustrik>  ok, send it to the list
| [Thursday 05 August 2010] [11:38:52] <sustrik>  i'll have a look
| [Thursday 05 August 2010] [14:02:14] <sustrik>  mato: hooo!
| [Thursday 05 August 2010] [14:04:48] <mato> sustrik: jaa?
| [Thursday 05 August 2010] [14:04:57] <mato> sustrik: oooh! :-)
| [Thursday 05 August 2010] [14:05:35] <sustrik>  i have a problem with getaddrinfo on the notebook
| [Thursday 05 August 2010] [14:05:47] <mato> what's that?
| [Thursday 05 August 2010] [14:05:52] <sustrik>  addr=127.0.0.1 service=5555
| [Thursday 05 August 2010] [14:05:55] <sustrik>  returns -2
| [Thursday 05 August 2010] [14:06:12] <mato> and you have the latest master with the fix that removes AI_ADDRCONFIG?
| [Thursday 05 August 2010] [14:06:23] <sustrik>  no it's the old version
| [Thursday 05 August 2010] [14:06:30] <mato> well, then it won't work :-)
| [Thursday 05 August 2010] [14:06:35] <sustrik>  i've removed AI_NUMERICSVR
| [Thursday 05 August 2010] [14:06:41] <sustrik>  but that didn't help :)
| [Thursday 05 August 2010] [14:06:47] <mato> of course it won't
| [Thursday 05 August 2010] [14:07:09] <sustrik>  i recalled that something was to be removed...
| [Thursday 05 August 2010] [14:07:13] <sustrik>  let me try
| [Thursday 05 August 2010] [14:07:25] <mato> you want commit 5b1a6a4bea1cebe860769f82702410f6c1d0ab1b
| [Thursday 05 August 2010] [14:07:42] <mato> remove AI_ADDRCONFIG, leave AI_NUMERICSERV
| [Thursday 05 August 2010] [14:07:50] <mato> and it will work fine
| [Thursday 05 August 2010] [14:09:00] <sustrik>  yes, it helped
| [Thursday 05 August 2010] [14:09:02] <sustrik>  thanks
| [Thursday 05 August 2010] [17:42:02] <CIA-19>   zeromq2: 03Martin Lucina 07master * r9ac2ff4 10/ src/signaler.cpp : 
| [Thursday 05 August 2010] [17:42:02] <CIA-19>   zeromq2: zmq::signaler_t: Restart syscalls on EINTR
| [Thursday 05 August 2010] [17:42:02] <CIA-19>   zeromq2: This patch restarts the send() or recv() inside zmq::signaler_t if the call fails
| [Thursday 05 August 2010] [17:42:02] <CIA-19>   zeromq2: due to EINTR. - http://bit.ly/akouYq
| [Thursday 05 August 2010] [17:42:02] <CIA-19>   zeromq2: 03Martin Lucina 07master * r16b43e6 10/ doc/zmq_device.txt : Merge branch 'master' of github.com:zeromq/zeromq2 - http://bit.ly/aschF1
| [Thursday 05 August 2010] [20:50:39] <dos000>   when you push messages into a pub socket how can you make sure (only)  some them comeout of the queue as sequential ?
| [Thursday 05 August 2010] [20:53:02] <dos000>   so if i send a.1,b.1,a.2,c.1,a.3 on the socket i want a.1,b.1,c.1 processed first .. then a.2, then a.3 
| [Thursday 05 August 2010] [20:55:15] <dos000>   i know it is not supported. just want to know how you would do it.
| [Thursday 05 August 2010] [20:59:31] <TheEffigy>    well, if you can sort them before sending them, or after receiving them it should be a problem. of course this requires some sort of condition to buffer the packets up until
| [Thursday 05 August 2010] [20:59:44] <TheEffigy>     shouldn't be a problem i meant
| [Thursday 05 August 2010] [21:06:18] <dos000>   mmmmmmmmmm
| [Thursday 05 August 2010] [21:07:18] <dos000>   i am trying to avoid sorting
| [Thursday 05 August 2010] [21:07:48] <TheEffigy>    how else can you receive the packets in an other than what they were sent in if you don't sort? 
| [Thursday 05 August 2010] [21:07:51] <dos000>   because sort means wait for a bunch of them eaither before or after sending
| [Thursday 05 August 2010] [21:08:29] <TheEffigy>    yes, but there is no way to order the data unless you've got multiple elements to compare 
| [Thursday 05 August 2010] [21:09:06] <dos000>   ok is i make them so that the topic is based on the id of the message ? 
| [Thursday 05 August 2010] [21:10:10] <dos000>   so they will have top:a1,top:b1,top:a2,top:c1,top:a3 
| [Thursday 05 August 2010] [21:10:25] <dos000>   and on the other end i am listening for "top"
| [Thursday 05 August 2010] [21:10:45] <TheEffigy>    you should receive them serially 
| [Thursday 05 August 2010] [21:10:52] <dos000>   the index is a counter for incoming messages that is incremented by message type
| [Thursday 05 August 2010] [21:12:03] <dos000>   but if i have say 4 subscribers ? how can i make sure a1 is not processed  before a1 in distributed way ?
| [Thursday 05 August 2010] [21:12:04] <TheEffigy>    if you are expecting a specific sequence number and you receive an out of order message you should just store it until you get the required one, then process the rest if you have them buffered - or wait for the next one if not
| [Thursday 05 August 2010] [21:12:15] <dos000>   oops a2 before a1
| [Thursday 05 August 2010] [21:13:12] <dos000>   one sec ... i will be right back
| [Thursday 05 August 2010] [21:17:54] <dos000>   TheEffigy, sorry .. i have to take care of something important.
| [Thursday 05 August 2010] [21:18:00] <dos000>   thanks for your help
| [Friday 06 August 2010] [00:10:42] <dos000> howdy all
| [Friday 06 August 2010] [00:11:32] <TheEffigy>  hi
| [Friday 06 August 2010] [00:18:27] <dos000> hey TheEffigy
| [Friday 06 August 2010] [00:18:59] <dos000> ok so i finally put out the familly pressing matter .
| [Friday 06 August 2010] [00:19:09] <dos000> now .. onto zmq
| [Friday 06 August 2010] [00:19:40] <dos000> <TheEffigy> if you are expecting a specific sequence number and you receive an out of order message you should just store it until you get the required one, then process the rest if you have them buffered - or wait for the next one if not
| [Friday 06 August 2010] [00:19:49] <dos000> trying to digest this one still
| [Friday 06 August 2010] [00:21:38] <TheEffigy>  well, say you have a message, and you know it's sequence number (index) 
| [Friday 06 August 2010] [00:22:00] <dos000> ok 
| [Friday 06 August 2010] [00:22:02] <TheEffigy>  if it is higher than what you expected, you could store it
| [Friday 06 August 2010] [00:22:18] <dos000> wait i am assigning the seq number
| [Friday 06 August 2010] [00:22:27] <dos000> as they came in 
| [Friday 06 August 2010] [00:22:48] <TheEffigy>  hmm
| [Friday 06 August 2010] [00:23:29] <dos000> the only diffrence between the messages is the id 
| [Friday 06 August 2010] [00:23:47] <dos000> based on the id i am getting a seq number
| [Friday 06 August 2010] [00:23:56] <TheEffigy>  ok
| [Friday 06 August 2010] [00:24:28] <TheEffigy>  well if that number isn't contiguous with the previous you could buffer it, and keep waiting until you do get the one you want
| [Friday 06 August 2010] [00:24:52] <dos000> wait ... 
| [Friday 06 August 2010] [00:25:01] <dos000> i have incoming messages 
| [Friday 06 August 2010] [00:25:08] <dos000> eahc one as an id
| [Friday 06 August 2010] [00:25:33] <dos000> based on the id i am generating a uniq seq for each id
| [Friday 06 August 2010] [00:25:56] <dos000> si if 5 messages come in with ids a,b,a,c,a
| [Friday 06 August 2010] [00:26:55] <dos000> i will tag them as a:1,b:1,a:2,c:1,a:3
| [Friday 06 August 2010] [00:27:19] <TheEffigy>  ok
| [Friday 06 August 2010] [00:27:42] <dos000> now i need the msg with the same ids to be processed sequentially
| [Friday 06 August 2010] [00:27:59] <dos000> and the messages with different ids to be processed in parallel
| [Friday 06 August 2010] [00:28:02] <TheEffigy>  so all a then all b and so forth?
| [Friday 06 August 2010] [00:28:11] <dos000> no
| [Friday 06 August 2010] [00:28:18] <dos000> a,b,c first 
| [Friday 06 August 2010] [00:28:25] <dos000> then a2
| [Friday 06 August 2010] [00:28:27] <dos000> then a3
| [Friday 06 August 2010] [00:28:30] <TheEffigy>  ahh
| [Friday 06 August 2010] [00:28:34] <TheEffigy>  ok
| [Friday 06 August 2010] [00:41:34] <TheEffigy>  so how about buffering them in a structure like this: std::map<int, std::vector<msg> > 
| [Friday 06 August 2010] [00:42:25] <dos000> ok .. 
| [Friday 06 August 2010] [00:42:57] <TheEffigy>  if you use a map::iterator you will be going over the messages in numerical order
| [Friday 06 August 2010] [00:43:11] <TheEffigy>  because it is sorted
| [Friday 06 August 2010] [00:43:37] <dos000> ok ... 
| [Friday 06 August 2010] [00:43:46] <TheEffigy>  it is then simply a matter of clearing the map before you next read messages
| [Friday 06 August 2010] [00:44:45] <dos000> wait ...
| [Friday 06 August 2010] [00:45:03] <dos000> the int are the ids ?
| [Friday 06 August 2010] [00:45:28] <TheEffigy>  if you have a:1, a:2 then the int is 1 and 2
| [Friday 06 August 2010] [00:45:40] <dos000> but a map will overwrite the previous message if you do a put no ?
| [Friday 06 August 2010] [00:45:59] <dos000> thtas the point of maps , they are unique
| [Friday 06 August 2010] [00:46:06] <TheEffigy>  you would do map[int].push_back(msg);
| [Friday 06 August 2010] [00:46:32] <dos000> i am coming from java sorry
| [Friday 06 August 2010] [00:46:36] <TheEffigy>  ahh
| [Friday 06 August 2010] [00:47:31] <TheEffigy>  hmm.. ok i don't really use java but you need something like Map<int, ArrayList<Msg> >
| [Friday 06 August 2010] [00:47:33] <dos000> but how do you process the messages in parallel then ?
| [Friday 06 August 2010] [00:47:53] <TheEffigy>  each msg in the array list can be passed off to a thread
| [Friday 06 August 2010] [00:48:58] <dos000> and how long do you wait till you go for the next bunch ?
| [Friday 06 August 2010] [00:49:11] <TheEffigy>  i guess once you have processed everythign
| [Friday 06 August 2010] [00:49:13] <TheEffigy>  everything*
| [Friday 06 August 2010] [00:49:31] <dos000> i cant wait till the end 
| [Friday 06 August 2010] [00:49:38] <TheEffigy>  hmm
| [Friday 06 August 2010] [00:49:40] <dos000> i have to do this in online
| [Friday 06 August 2010] [00:49:46] <dos000> real time
| [Friday 06 August 2010] [00:49:58] <TheEffigy>  hmm
| [Friday 06 August 2010] [00:50:16] <dos000> thats the problem!
| [Friday 06 August 2010] [00:51:10] <TheEffigy>  isn't it possible to just have a concurrent queue for each type of message and then append the next one of that type from the socket directly onto it?
| [Friday 06 August 2010] [00:51:29] <TheEffigy>  then threads can continuously process the data as it arrives 
| [Friday 06 August 2010] [00:52:30] <dos000> 1) i cannot predict how many different type of messages will comein. it is unbunded
| [Friday 06 August 2010] [00:53:25] <dos000> 2) i have to make sure same messages are still done in sequence if the machine reading from the queue are more than the one producing them queue
| [Friday 06 August 2010] [00:54:47] <TheEffigy>  you could create a queue each time you see a new data type
| [Friday 06 August 2010] [00:56:33] <dos000> thats what i was saying regarding the message ids
| [Friday 06 August 2010] [00:57:42] <dos000> now if the consumers (subscribers) of message queues are more than the producers (pub) then messages with same id will be processed in parallel
| [Friday 06 August 2010] [00:58:17] <dos000> welcome mimcpher, i appreciate you taking the time for this
| [Friday 06 August 2010] [01:00:12] <dos000> so if i have a queue of a,a,a | b | c i want a,b,c in parallel then a,a in sequence
| [Friday 06 August 2010] [01:01:03] <dos000> but if i have more than 1 subscribers for the queue a,a will be processed in parallel
| [Friday 06 August 2010] [01:02:11] <dos000> makes sense ?
| [Friday 06 August 2010] [01:16:25] <TheEffigy>  i see. 
| [Friday 06 August 2010] [01:16:50] <TheEffigy>  so, doing what i said would work just fine
| [Friday 06 August 2010] [01:17:57] <dos000> but if i had only items with the same id your method will not work
| [Friday 06 August 2010] [01:18:13] <dos000> they will be processed in parallel
| [Friday 06 August 2010] [01:18:30] <mimcpher>   TheEffigy: What was your solution? (dos000 asked a similar question in another channel and I'm curious)
| [Friday 06 August 2010] [01:18:35] <TheEffigy>  if the threads have a work queue, then you just need another thread that will look at the incoming message queues and delegate the messages to follow the method that you have described
| [Friday 06 August 2010] [01:19:20] <dos000> this is not happening on machine tho .. 
| [Friday 06 August 2010] [01:19:31] <dos000> i have to distribute across many machines
| [Friday 06 August 2010] [01:19:49] <dos000> dont think a single machine
| [Friday 06 August 2010] [01:20:01] <TheEffigy>  sure, well then the work queue becomes a socket 
| [Friday 06 August 2010] [01:20:14] <TheEffigy>  which is connected to some machine 
| [Friday 06 August 2010] [01:20:19] <dos000> ok .. how many subscribers to the socket ?
| [Friday 06 August 2010] [01:20:46] <dos000> if i have more than one a,a,a will be processed in parallel
| [Friday 06 August 2010] [01:21:06] <TheEffigy>  well, if you have multiple then you need to have some communication between the processes
| [Friday 06 August 2010] [01:21:37] <TheEffigy>  machines with no work can be added to the pool, and then delegated work - which may be one item or maybe be a list of several of the same type
| [Friday 06 August 2010] [01:22:01] <dos000> thats the problem i am trying to solve !
| [Friday 06 August 2010] [01:22:02] <TheEffigy>  it's the same concept, just replace thread with a machine
| [Friday 06 August 2010] [01:22:39] <dos000> how do you say to everyone dont process messages with same ids 
| [Friday 06 August 2010] [01:22:51] <dos000> wait unti the first one is done
| [Friday 06 August 2010] [01:23:09] <TheEffigy>  at any one time the process just that id 
| [Friday 06 August 2010] [01:23:31] <TheEffigy>  but depending on what is available it may process a different id each time it has resources available
| [Friday 06 August 2010] [01:23:32] <dos000> ok .. 
| [Friday 06 August 2010] [01:24:34] <dos000> where does it pickup the ids from ? and how does it make sure no one else is processing other messages in the queue with same ids
| [Friday 06 August 2010] [01:25:12] <dos000> if other messages are coming i want then to be processed as most parall as possible
| [Friday 06 August 2010] [01:25:28] <TheEffigy>  so in the delegator process, you need to receive the messages and keep them in queues for each type, but also maintain a list of free streams and assigned streams - assigned streams can be kept in a map
| [Friday 06 August 2010] [01:25:54] <dos000> ok ... 
| [Friday 06 August 2010] [01:26:09] <dos000> this has to be one machine correct ?
| [Friday 06 August 2010] [01:26:13] <TheEffigy>  yes
| [Friday 06 August 2010] [01:26:16] <dos000> ouch
| [Friday 06 August 2010] [01:26:34] <TheEffigy>  it's a simple process really, it will be very efficient 
| [Friday 06 August 2010] [01:26:46] <TheEffigy>  it is just a router
| [Friday 06 August 2010] [01:26:53] <dos000> i know but it will be a spof (single point of failure)
| [Friday 06 August 2010] [01:27:20] <dos000> the reason i am using zmq is to avoid spof
| [Friday 06 August 2010] [01:27:30] <TheEffigy>  ok
| [Friday 06 August 2010] [01:27:31] <TheEffigy>  well
| [Friday 06 August 2010] [01:28:11] <TheEffigy>  you can take the router out of the equation and then have each machine communicate with each other about what they have to process 
| [Friday 06 August 2010] [01:28:52] <mimcpher>   You could have two routers that communicate with each other
| [Friday 06 August 2010] [01:29:01] <mimcpher>   Well, N routers.
| [Friday 06 August 2010] [01:29:09] <dos000> ok ...
| [Friday 06 August 2010] [01:29:11] <mimcpher>   But that'd be more involved to write.
| [Friday 06 August 2010] [01:29:12] <TheEffigy>  if necessary you can have the machines send data to another process if if has already taken up processing of that message type
| [Friday 06 August 2010] [01:29:26] <dos000> now they need to also sync when the pull off messages with same ids
| [Friday 06 August 2010] [01:29:35] <TheEffigy>  then given all available machines need to keep in sync with the ids yes
| [Friday 06 August 2010] [01:30:14] <dos000> ok ... 
| [Friday 06 August 2010] [01:30:14] <TheEffigy>  so you should build a graph which can be kept in sync on each machine
| [Friday 06 August 2010] [01:30:51] <TheEffigy>  and then consult the graph as to where messages should go and what messages are being processed to keep it all running in sync 
| [Friday 06 August 2010] [01:30:54] <dos000> so i get a message off the zmq stack .. then boadcast a msg to say who has the same ?
| [Friday 06 August 2010] [01:31:20] <TheEffigy>  yes
| [Friday 06 August 2010] [01:31:25] <dos000> ok ... 
| [Friday 06 August 2010] [01:31:39] <TheEffigy>  or perhaps 'i have this message'
| [Friday 06 August 2010] [01:31:46] <dos000> then if someone else has the same wait until they are done
| [Friday 06 August 2010] [01:32:08] <dos000> mmmm
| [Friday 06 August 2010] [01:32:16] <TheEffigy>  if everyone is sending those messages you can maintain a graph of where everything is easily and then push messages to other streams or maintain them for processing 
| [Friday 06 August 2010] [01:32:50] <dos000> ok that could work .. not withstanding error conditions
| [Friday 06 August 2010] [01:33:00] <TheEffigy>  it's a bit trickier, but does avoid a single point of failure. though that being said if a machine goes down, the received data would be lost
| [Friday 06 August 2010] [01:33:42] <dos000> and everyone else will be waiting for the completion .. so these are the erro conditions i have to deal with
| [Friday 06 August 2010] [01:33:59] <dos000> nice man!
| [Friday 06 August 2010] [01:34:01] <TheEffigy>  to avoid that you'd have to push the data to machines but maintain an owner machine identifier - if that machine is lost then message that haven't been notified as being processed then another machine could take over
| [Friday 06 August 2010] [01:34:45] <TheEffigy>  that means a bit more sync between machines but it provides data redundancy 
| [Friday 06 August 2010] [01:34:59] <dos000> i have to keep the state of each message  then .. its better to drop 
| [Friday 06 August 2010] [01:35:22] <TheEffigy>  if that isn't catastrophic then it makes things easier to just accept it
| [Friday 06 August 2010] [01:35:32] <dos000> if a message is droped in the middle of the processing i have no way of knowing how far it went
| [Friday 06 August 2010] [01:35:53] <dos000> ok ... 
| [Friday 06 August 2010] [01:37:16] <TheEffigy>  sounds like a fun project 
| [Friday 06 August 2010] [01:37:49] <dos000> yeah .. it got mo feeling like those old days .. 
| [Friday 06 August 2010] [01:38:18] <dos000> all the cs stuff. i assumed this stuff was all well documented in one of the computer science papers
| [Friday 06 August 2010] [01:38:34] <TheEffigy>  maybe, i've never read one
| [Friday 06 August 2010] [01:38:59] <dos000> heh
| [Friday 06 August 2010] [01:41:20] <dos000> i bet you this has a nice and nifty paper in either hw or software somewhere
| [Friday 06 August 2010] [01:41:26] <dos000> maybe one day i will find
| [Friday 06 August 2010] [01:41:53] <TheEffigy>  most likely 
| [Friday 06 August 2010] [01:42:26] <dos000> but my half assed implementation should take me until then
| [Friday 06 August 2010] [01:42:49] <TheEffigy>  haha
| [Friday 06 August 2010] [01:42:50] <dos000> thanks a lot man
| [Friday 06 August 2010] [01:42:56] <TheEffigy>  no problems
| [Friday 06 August 2010] [01:48:06] <dos000> there is a nice algorithm the guys who implemented cassandra are using called gossip for clustering. this would be nice if zmq had it.
| [Friday 06 August 2010] [01:49:41] <TheEffigy>  well, you could always build it :-p
| [Friday 06 August 2010] [01:49:54] <dos000> one day .. one day 
| [Friday 06 August 2010] [05:05:42] <CIA-19> zeromq2: 03Pieter Hintjens 07master * r2100a91 10/ src/signaler.cpp : Merge branch 'master' of github.com:zeromq/zeromq2 - http://bit.ly/cg7gA3
| [Friday 06 August 2010] [06:01:52] <CIA-19> zeromq2: 03Martin Lucina 07master * r6d35e82 10/ src/signaler.cpp : Fix uninitialized use of nbytes in signaler fix - http://bit.ly/aPlMBv
| [Friday 06 August 2010] [06:01:52] <CIA-19> zeromq2: 03Martin Lucina 07master * rb579aa9 10/ builds/msvc/libzmq/libzmq.vcproj : Merge branch 'master' of github.com:zeromq/zeromq2 - http://bit.ly/9hHQ0J
| [Friday 06 August 2010] [08:02:54] <aleator_>   Hi! Can anyone point me at an example using xrep/xreq?
| [Friday 06 August 2010] [09:13:06] <cremes> aleator: i recommend taking a look at the python or ruby-ffi bindings; both have small examples using xreq/xrep
| [Friday 06 August 2010] [09:23:10] <aleator>    cremes: Thanks! I think I figured it out. Haskell interface was missing ZMQ_SNDMORE which was making things tad difficult with XREP. (I sent a patch)
| [Friday 06 August 2010] [09:29:15] <aleator>    Does Xrep/Xreq preserve order of messages?
| [Friday 06 August 2010] [09:30:22] <guido_g>    xreq -> xrep: the messages are delivered in the order sent
| [Friday 06 August 2010] [09:30:35] <guido_g>    the way back depends on you
| [Friday 06 August 2010] [11:57:41] <CIA-19> zeromq2: 03Martin Sustrik 07wip-shutdown * r20411a7 10/ (47 files in 2 dirs): (log message trimmed)
| [Friday 06 August 2010] [11:57:41] <CIA-19> zeromq2: WIP: Socket migration between threads, new zmq_close() semantics
| [Friday 06 August 2010] [11:57:41] <CIA-19> zeromq2: Sockets may now be migrated between OS threads; sockets may not be used by
| [Friday 06 August 2010] [11:57:41] <CIA-19> zeromq2: more than one thread at any time. To migrate a socket to another thread the
| [Friday 06 August 2010] [11:57:41] <CIA-19> zeromq2: caller must ensure that a full memory barrier is called before using the
| [Friday 06 August 2010] [11:57:42] <CIA-19> zeromq2: socket from the target thread.
| [Friday 06 August 2010] [11:57:42] <CIA-19> zeromq2: The new zmq_close() semantics implement the behaviour discussed at:
| [Friday 06 August 2010] [12:29:51] <pieterh_>   hi yall
| [Friday 06 August 2010] [12:30:00] <pieterh_>   I added a twitter box to the main page
| [Friday 06 August 2010] [12:30:44] <pieterh_>   If this is annoying, please let me know
| [Friday 06 August 2010] [12:31:03] <mato>   not for me, my browser security policy just ignores it :-)
| [Friday 06 August 2010] [12:34:12] <pieterh_>   mato: you are missing out on such wisdom
| [Friday 06 August 2010] [12:34:41] <pieterh_>   "DEVOPS_BORAT Azamat is sick of whale fail, is write Twitter clone in modern technology: cloud, NoSQL, erlang, clojure, ZeroMQ. Is for Central Asia only."
| [Friday 06 August 2010] [12:37:12] <pieterh_>   yay! i seem to have convinced HyBi to adopt the ZeroMQ framing standard...!
| [Friday 06 August 2010] [12:37:19] <pieterh_>   for WebSockets
| [Friday 06 August 2010] [12:37:49] <sustrik>    funny
| [Friday 06 August 2010] [12:38:15] <sustrik>    i though websockets is something that's more or less used already
| [Friday 06 August 2010] [12:38:32] <pieterh_>   well
| [Friday 06 August 2010] [12:38:42] <pieterh_>   there are versions that browsers support
| [Friday 06 August 2010] [12:38:52] <pieterh_>   and there is a new version emerging from IETF discussion
| [Friday 06 August 2010] [12:38:58] <sustrik>    reminds me of something...
| [Friday 06 August 2010] [12:39:03] <pieterh_>   it's not clear whether the IETF can win over WhatWG
| [Friday 06 August 2010] [12:39:12] <pieterh_>   implementors vs. consensus and quality
| [Friday 06 August 2010] [12:39:15] <pieterh_>   yes, familiar
| [Friday 06 August 2010] [12:39:19] <sustrik>    yup
| [Friday 06 August 2010] [12:39:27] <pieterh_>   except IETF is kind of not a puppy dog
| [Friday 06 August 2010] [12:39:37] <sustrik>    right
| [Friday 06 August 2010] [12:39:43] <sustrik>    anyway, there's a deficiency in 0mq wire format
| [Friday 06 August 2010] [12:39:50] <sustrik>    instead of continuation bit
| [Friday 06 August 2010] [12:40:03] <sustrik>    there should be two bits: begin and end
| [Friday 06 August 2010] [12:40:16] <pieterh_>   specific effects?
| [Friday 06 August 2010] [12:40:19] <sustrik>    that makes it easier for late jointer
| [Friday 06 August 2010] [12:40:23] <sustrik>    joiners
| [Friday 06 August 2010] [12:40:43] <sustrik>    say you join a multicast group and get a message
| [Friday 06 August 2010] [12:40:53] <sustrik>    saying 'not continued'
| [Friday 06 August 2010] [12:41:03] <sustrik>    it can be either single-part message
| [Friday 06 August 2010] [12:41:04] <pieterh_>   right, you don' t know what that means
| [Friday 06 August 2010] [12:41:17] <sustrik>    in which case you should pass it to the receiver
| [Friday 06 August 2010] [12:41:34] <sustrik>    or the last part of multi-part message in witch case you should drop it
| [Friday 06 August 2010] [12:41:38] <pieterh_>   indeed
| [Friday 06 August 2010] [12:41:57] <pieterh_>   we need to write spbv3
| [Friday 06 August 2010] [12:42:02] <pieterh_>   sbpv3
| [Friday 06 August 2010] [12:42:05] <sustrik>    but there are no late joiners with websockets i assume
| [Friday 06 August 2010] [12:42:12] <pieterh_>   its tcp for now
| [Friday 06 August 2010] [12:42:26] <pieterh_>   anyhow the discussion is still about 10000 emails from being over
| [Friday 06 August 2010] [12:42:36] <sustrik>    ack
| [Friday 06 August 2010] [12:43:17] <sustrik>    begin/end style is also good for packet capturing
| [Friday 06 August 2010] [12:43:35] <sustrik>    say inspecting the flow with wireshark
| [Friday 06 August 2010] [12:44:52] <pieterh_>   do you think we can unify all our different miniprotocols into a single new SPB?
| [Friday 06 August 2010] [12:45:02] <pieterh_>   i'd like one document that defines "the" ZeroMQ wire format
| [Friday 06 August 2010] [12:45:16] <pieterh_>   including multipart, identities, etc.
| [Friday 06 August 2010] [12:45:36] <pieterh_>   including subscription upstreaming, etc.
| [Friday 06 August 2010] [12:46:19] <pieterh_>   right now it is impossible to know what the frames mean unless you know what the socket types are, at each end
| [Friday 06 August 2010] [12:46:26] <pieterh_>   that makes true interop impossible
| [Friday 06 August 2010] [14:58:15] <CIA-19> zeromq2: 03Martin Sustrik 07wip-shutdown * r89cd2ea 10/ (src/pipe.cpp src/pipe.hpp src/session.cpp): Destruction of session is delayed till both in & out pipes are closed - http://bit.ly/9BrZmy
| [Friday 06 August 2010] [15:00:28] <sustrik>    mato: as for the zmq_poll implementation in the shutdown branch, can you check & possibly apply this patch:
| [Friday 06 August 2010] [15:00:29] <sustrik>    http://github.com/joshcarter/zeromq2/commit/f3a5b66521dc43e04cc52b92c792be6887585287
| [Friday 06 August 2010] [17:10:35] <zedas>  sustrik: what's the chance i can get a void *data added to zmq_pollitem_t ?
| [Friday 06 August 2010] [17:39:22] <zedas>  sustrik: yeah, so if there was a void *data pointer in the zmq_pollitem_t then it'd solve a problem with matching events to data.
| [Friday 06 August 2010] [17:40:05] <zedas>  sustrik: basically, because zmq_pollitem_t has an int fd, and a void *socket, it's difficult to put it in a data structure to match the socket.  i'd need two, one for the int fd and one for the void *socket.
| [Friday 06 August 2010] [17:40:34] <zedas>  i'm gonna change up with i'm doing with this, but let me know if it's a thought and i'll put up a ticket somewhere
| [Friday 06 August 2010] [17:40:44] <zedas>  oh and i did the change locally and tested it, works fine.
| [Saturday 07 August 2010] [02:40:56] <sustrik>  zadas: why does the pointer has to be in zmq_pollitem_t?
| [Saturday 07 August 2010] [02:41:22] <sustrik>  keeping a different array of data pointers would work equally well, no?
| [Saturday 07 August 2010] [03:52:50] <CIA-19>   zeromq2: 03Martin Sustrik 07wip-shutdown * rc001223 10/ (src/fq.cpp src/pipe.cpp src/req.cpp src/req.hpp): REQ socket implementation is layered on top of XREQ - http://bit.ly/brXle9
| [Saturday 07 August 2010] [05:24:22] <CIA-19>   zeromq2: 03Martin Sustrik 07wip-shutdown * rb5fc565 10/ (src/rep.cpp src/rep.hpp): REP socket layered on top of XREP socket - http://bit.ly/cEXRbB
| [Saturday 07 August 2010] [07:05:37] <sustrik>  pieterh: i like the story of ordinary socket turning into supersocket :)
| [Saturday 07 August 2010] [07:26:18] <pieterh>  sustrik: the idea was to give a striking visual image :-)
| [Saturday 07 August 2010] [07:26:24] <pieterh>  Zap! Pow!
| [Saturday 07 August 2010] [07:26:45]     * pieterh goes to add some sound effects...
| [Saturday 07 August 2010] [07:28:49] <pieterh>  sustrik: i have to admit, i'm impressed
| [Saturday 07 August 2010] [07:28:59] <pieterh>  translated the C++ multithreaded server into C
| [Saturday 07 August 2010] [07:29:02] <pieterh>  it worked first time
| [Saturday 07 August 2010] [07:29:14] <pieterh>  that is kind of scary
| [Saturday 07 August 2010] [07:37:05] <sustrik>  :)
| [Saturday 07 August 2010] [07:37:59] <sustrik>  with previous enterprise messaging experience it makes you a bit suspicious
| [Saturday 07 August 2010] [07:39:04] <sustrik>  this has to be some kind of cheat...
| [Saturday 07 August 2010] [07:39:10] <sustrik>  no way it's that easy...
| [Saturday 07 August 2010] [07:41:26] <sustrik>  maybe we should provide an "enterprise" wrapper that'll some complexy to make corporate users feel comfortable :)
| [Saturday 07 August 2010] [07:48:08] <pieterh>  someone started an AMQP-to-0MQ bridge... I guess that counts?
| [Saturday 07 August 2010] [08:46:58] <mato> sustrik: i just tested remote_thr on the wip-shutdown branch and it does *not* freeze
| [Saturday 07 August 2010] [08:47:25] <sustrik>  it fails then...
| [Saturday 07 August 2010] [08:47:27] <mato> sustrik: maybe you forgot to comment out the zmq_sleep(10) ? :-)
| [Saturday 07 August 2010] [08:47:33] <mato> sustrik: doesn't fail either :-)
| [Saturday 07 August 2010] [08:47:36] <sustrik>  ha
| [Saturday 07 August 2010] [08:47:49] <sustrik>  anyway, it freezes on my box, so i'll work on that
| [Saturday 07 August 2010] [08:47:56] <sustrik>  in the meantime you can do some tests
| [Saturday 07 August 2010] [08:48:03] <mato> and you did comment out the zmq_sleep(), right? :-)
| [Saturday 07 August 2010] [08:48:30] <sustrik>  i've tried both commenting it out and not commenting it out
| [Saturday 07 August 2010] [08:48:36] <sustrik>  freezes in both cases
| [Saturday 07 August 2010] [08:48:48] <mato> ah, interesting
| [Saturday 07 August 2010] [08:49:05] <mato> sustrik: it freezes if you start remote first
| [Saturday 07 August 2010] [08:49:17] <mato> at least that's what i see...
| [Saturday 07 August 2010] [08:49:39] <mato> if i start local_thr, then remote_thr it works fine (with or without sleep)
| [Saturday 07 August 2010] [08:49:55] <sustrik>  doesn't really matter, the code is still a bit creaky, i'll have to do few fixes
| [Saturday 07 August 2010] [08:50:04] <mato> yes, yes
| [Saturday 07 August 2010] [08:50:12] <mato> it sort of works
| [Saturday 07 August 2010] [08:50:15] <sustrik>  kind of
| [Saturday 07 August 2010] [08:50:23] <mato> not for small amounts of messages :)
| [Saturday 07 August 2010] [08:53:35] <sustrik>  i have to leave no for an hour
| [Saturday 07 August 2010] [08:53:48] <sustrik>  can you have a look at the poll stuff in the meantime?
| [Saturday 07 August 2010] [08:53:52] <mato> ok, will do
| [Saturday 07 August 2010] [08:54:02] <mato> sustrik: where did that patch come from?
| [Saturday 07 August 2010] [08:54:17] <mato> sustrik: all i have from you is some github url...
| [Saturday 07 August 2010] [08:54:42] <sustrik>  it's a pull request
| [Saturday 07 August 2010] [08:54:46] <sustrik>  from that repo
| [Saturday 07 August 2010] [08:54:50] <mato> sustrik: aha, ok
| [Saturday 07 August 2010] [08:55:03] <mato> sustrik: we should disable pull requests via github somehow
| [Saturday 07 August 2010] [08:55:09] <mato> sustrik: not transparent :(
| [Saturday 07 August 2010] [10:54:48] <mato> sustrik: back yet?
| [Saturday 07 August 2010] [10:55:12] <sustrik>  yes, i'm back
| [Saturday 07 August 2010] [10:55:24] <mato> sustrik: that patch kind of works, but not really
| [Saturday 07 August 2010] [10:55:33] <sustrik>  ?
| [Saturday 07 August 2010] [10:55:39] <mato> sustrik: i'm rewriting zmq_poll to use ZMQ_FD and ZMQ_EVENTS which is what it should be doing
| [Saturday 07 August 2010] [10:55:55] <sustrik>  yes, that's the idea
| [Saturday 07 August 2010] [10:55:56] <mato> sustrik: which also kills this business of zmq_poll() poking around inside socket_base_t
| [Saturday 07 August 2010] [10:56:09] <sustrik>  right
| [Saturday 07 August 2010] [10:56:16] <mato> sustrik: anyway, getting there... maybe poll will not be a hack after i've finished :)
| [Saturday 07 August 2010] [10:56:32] <sustrik>  :)
| [Saturday 07 August 2010] [11:05:44] <mato> sustrik: so the idea is I'm supposed to poll for POLLIN on ZMQ_FD, then if I get POLLIN get the "real" events using ZMQ_EVENTS
| [Saturday 07 August 2010] [11:05:47] <mato> sustrik: correct?
| [Saturday 07 August 2010] [11:31:14] <sustrik>  mato: correct
| [Saturday 07 August 2010] [12:11:51] <mato> sustrik: ok, do you have a minute?
| [Saturday 07 August 2010] [12:12:23] <mato> sustrik: i have zmq_poll () working, at least the version using poll ()
| [Saturday 07 August 2010] [12:12:49] <mato> sustrik: but, I'm using some test programs Brian Granger wrote and things are breaking (as we would expect)
| [Saturday 07 August 2010] [12:13:23] <mato> sustrik: what I can do now, is commit the poll () version of zmq_poll (), leaving the select () version #ifdefed out
| [Saturday 07 August 2010] [12:13:45] <mato> sustrik: and then, either you use Brian's test programs, or I can rewrite them in C++ which might be easier for you
| [Saturday 07 August 2010] [12:13:57] <mato> sustrik: and you can squash the bugs ...
| [Saturday 07 August 2010] [12:26:00] <sustrik>  ok, commit it
| [Saturday 07 August 2010] [12:26:32] <CIA-19>   zeromq2: 03Martin Lucina 07wip-shutdown * rf4db0f6 10/ src/zmq.cpp : 
| [Saturday 07 August 2010] [12:26:32] <CIA-19>   zeromq2: zmq_poll(): Rewrite to use ZMQ_FD/ZMQ_EVENTS pt1
| [Saturday 07 August 2010] [12:26:32] <CIA-19>   zeromq2: Rewrite zmq_poll() to use ZMQ_FD and ZMQ_EVENTS introduced on the
| [Saturday 07 August 2010] [12:26:32] <CIA-19>   zeromq2: wip-shutdown branch. Only do the poll()-based version of zmq_poll (), the
| [Saturday 07 August 2010] [12:26:32] <CIA-19>   zeromq2: select()-based version will not compile at the moment. - http://bit.ly/b9yiFc
| [Saturday 07 August 2010] [12:26:43] <mato> sustrik: done
| [Saturday 07 August 2010] [12:26:45] <sustrik>  i am running into different tricky races between delayed socket close and reconnection functionality
| [Saturday 07 August 2010] [12:26:55] <sustrik>  it'll take a while to get that sorted out
| [Saturday 07 August 2010] [12:27:03] <mato> sustrik: d'you want those test programs rewritten in C++?
| [Saturday 07 August 2010] [12:27:12] <sustrik>  for poll?
| [Saturday 07 August 2010] [12:27:15] <mato> sustrik: yeah
| [Saturday 07 August 2010] [12:27:23] <sustrik>  no need thanks
| [Saturday 07 August 2010] [12:27:32] <sustrik>  i have to make simple cases work first
| [Saturday 07 August 2010] [12:27:49] <mato> sustrik: ok, so there's nothing i can do in the mean time?
| [Saturday 07 August 2010] [12:28:02] <mato> sustrik: ...except complete the poll() rewrite (fix the select() based version)
| [Saturday 07 August 2010] [12:28:17] <mato> sustrik: ack?
| [Saturday 07 August 2010] [12:28:17] <sustrik>  that would be one good thing to do
| [Saturday 07 August 2010] [12:28:27] <mato> well i'll go and do it then
| [Saturday 07 August 2010] [12:28:39] <sustrik>  the other would be to make poll's timeout behave as expected
| [Saturday 07 August 2010] [12:28:46] <mato> yeah, i was going to do that too :-)
| [Saturday 07 August 2010] [12:28:51] <sustrik>  :)
| [Saturday 07 August 2010] [12:29:11] <sustrik>  now the performance problem of calling getimeofday is not critical
| [Saturday 07 August 2010] [12:29:18] <mato> yup
| [Saturday 07 August 2010] [12:29:48] <mato> actually zmq_poll() is much simpler now
| [Saturday 07 August 2010] [12:30:01] <mato> so these are all good changes (ZMQ_FD, ZMQ_EVENTS...)
| [Saturday 07 August 2010] [12:30:28] <sustrik>  those who need fast version can use ZMQ_FD and ZMQ_EVENTS instead
| [Saturday 07 August 2010] [12:31:31] <sustrik>  ack
| [Saturday 07 August 2010] [12:34:31] <CIA-19>   zeromq2: 03Martin Lucina 07wip-shutdown * r39abee0 10/ src/zmq.cpp : 
| [Saturday 07 August 2010] [12:34:31] <CIA-19>   zeromq2: Fix whitespace
| [Saturday 07 August 2010] [12:34:31] <CIA-19>   zeromq2: Dunno where those <TAB>s came from... - http://bit.ly/c3hytK
| [Saturday 07 August 2010] [13:37:26] <pieterh>  sustrik: does zmq_errno not work portably?
| [Saturday 07 August 2010] [13:37:43] <sustrik>  it should
| [Saturday 07 August 2010] [13:38:25] <pieterh>  the man page strongly advises people not to use the function except on win32
| [Saturday 07 August 2010] [13:38:56] <sustrik>  on any sane platform errno should do
| [Saturday 07 August 2010] [13:38:59] <mato> pieterh: that's because it's really just a hack for win32
| [Saturday 07 August 2010] [13:39:15] <mato> pieterh: and it's mess with multiple CRTs
| [Saturday 07 August 2010] [13:39:20] <pieterh>  i understand from the "0mq will become a linux kernel module" PoV
| [Saturday 07 August 2010] [13:39:33] <pieterh>  but from "i want to write an app that runs anywhere" PoV it's... not useful
| [Saturday 07 August 2010] [13:40:07] <pieterh>  do we have an explicit policy of not trying to help people write portable code?
| [Saturday 07 August 2010] [13:40:20] <pieterh>  fine by me, but we should say so explicitly IMO
| [Saturday 07 August 2010] [13:40:21] <mato> more or less
| [Saturday 07 August 2010] [13:41:01] <sustrik>  the question is how much api contamination we are willing to accept as to support broken platforms
| [Saturday 07 August 2010] [13:41:03] <pieterh>  it's ok for non-OMQ functions, we can tell people to use random portability layer
| [Saturday 07 August 2010] [13:41:22] <pieterh>  but in this case the only solution is for people to themselves wrap zmq_errno and errno
| [Saturday 07 August 2010] [13:41:29] <pieterh>  which is insane IMO
| [Saturday 07 August 2010] [13:42:09]     * mato is stuck in a twisty little maze of fd_sets
| [Saturday 07 August 2010] [13:42:13] <mato> write an email
| [Saturday 07 August 2010] [13:42:16] <pieterh>  will do
| [Saturday 07 August 2010] [14:26:17] <pieterh>  sustrik: is there a reason the C api does not assert if its passed null objects, e.g. context in zmq_socket?
| [Saturday 07 August 2010] [14:26:30] <pieterh>  *it's
| [Saturday 07 August 2010] [14:27:22] <sustrik>  no
| [Saturday 07 August 2010] [14:27:35] <sustrik>  it can possibly return EFAULT
| [Saturday 07 August 2010] [14:27:47] <sustrik>  (invalid pointer)
| [Saturday 07 August 2010] [14:28:09] <sustrik>  but if you want to do so, check whether the error exists on Win32
| [Saturday 07 August 2010] [14:28:22] <sustrik>  and if it does not, define it in zmq.h
| [Saturday 07 August 2010] [14:28:49] <pieterh>  ack
| [Saturday 07 August 2010] [14:28:50] <mato> of course it has no way to tell if a non-NULL pointer passed in is a valid object...
| [Saturday 07 August 2010] [14:28:54] <pieterh>  indeed
| [Saturday 07 August 2010] [14:29:05] <mato> so not really worth it imho
| [Saturday 07 August 2010] [14:29:36] <sustrik>  pieterh: btw, this won't work:
| [Saturday 07 August 2010] [14:29:37] <mato> you would also need to update the docs specifying that EFAULT is a valid return, etc etc
| [Saturday 07 August 2010] [14:29:37] <sustrik>  c -lzmq -l myprogram
| [Saturday 07 August 2010] [14:29:51] <sustrik>  there's also a uuid library needed
| [Saturday 07 August 2010] [14:30:07] <pieterh>  I'd not bother returning EFAULT, but asserting if it gets NULL is cheap and useful
| [Saturday 07 August 2010] [14:30:28] <mato> hmm, maybe, no opinion right now
| [Saturday 07 August 2010] [14:30:40] <mato> also -lzmq is sufficient if that points to a shared lib
| [Saturday 07 August 2010] [14:31:03]     * mato goes back to zmq_poll()
| [Saturday 07 August 2010] [14:38:39] <CIA-19>   zeromq2: 03Martin Lucina 07wip-shutdown * r3d72e38 10/ src/zmq.cpp : 
| [Saturday 07 August 2010] [14:38:40] <CIA-19>   zeromq2: zmq_poll(): Rewrite to use ZMQ_FD/ZMQ_EVENTS pt2
| [Saturday 07 August 2010] [14:38:40] <CIA-19>   zeromq2: Rewrite the select()-based zmq_poll() implementation to use
| [Saturday 07 August 2010] [14:38:40] <CIA-19>   zeromq2: ZMQ_FD and ZMQ_EVENTS.
| [Saturday 07 August 2010] [14:38:40] <CIA-19>   zeromq2: Also fix some corner cases: We should not pollute revents with
| [Saturday 07 August 2010] [14:38:40] <CIA-19>   zeromq2: unrequested events, and we don't need to poll on ZMQ_FD at all
| [Saturday 07 August 2010] [14:38:41] <CIA-19>   zeromq2: if a pollitem with no events set was passed in. - http://bit.ly/9x0r7G
| [Saturday 07 August 2010] [14:51:24] <CIA-19>   zeromq2: 03Pieter Hintjens 07master * r677b3d9 10/ src/zmq.cpp : (log message trimmed)
| [Saturday 07 August 2010] [14:51:24] <CIA-19>   zeromq2: Added not-null assertions on pointer arguments in C API functions
| [Saturday 07 August 2010] [14:51:24] <CIA-19>   zeromq2: * zmq_term
| [Saturday 07 August 2010] [14:51:24] <CIA-19>   zeromq2: * zmq_socket
| [Saturday 07 August 2010] [14:51:24] <CIA-19>   zeromq2: * zmq_close
| [Saturday 07 August 2010] [14:51:24] <CIA-19>   zeromq2: * zmq_setsockopt
| [Saturday 07 August 2010] [14:51:24] <CIA-19>   zeromq2: * zmq_getsockopt
| [Saturday 07 August 2010] [15:11:19] <CIA-19>   zeromq2: 03Martin Lucina 07wip-shutdown * rc240ece 10/ src/zmq.cpp : 
| [Saturday 07 August 2010] [15:11:19] <CIA-19>   zeromq2: zmq_poll(): Fix some corner cases
| [Saturday 07 August 2010] [15:11:19] <CIA-19>   zeromq2: Trying to optimize out the case where items_[i]. events is 0 would
| [Saturday 07 August 2010] [15:11:19] <CIA-19>   zeromq2: result in a bogus pollfds[i]. Similarly in the select()-based impl,
| [Saturday 07 August 2010] [15:11:19] <CIA-19>   zeromq2: while not strictly necessary it's better to get ZMQ_FD even if
| [Saturday 07 August 2010] [15:11:19] <CIA-19>   zeromq2: events is 0 since that detects ETERM and friends. - http://bit.ly/cSKumL
| [Saturday 07 August 2010] [15:17:27] <mato> pieterh: incidentally i'd somewhat prefer the EFAULT approach as opposed to asserting... the only reason is asserting makes it look as if there's a problem in zmq which in this case there's not...
| [Saturday 07 August 2010] [15:17:47] <pieterh>  yeah, i was kind of thinking the same
| [Saturday 07 August 2010] [15:17:59] <pieterh>  EFAULT exists on win32, I checked
| [Saturday 07 August 2010] [15:18:13] <pieterh>  and the assertion is kind of useless anyhow
| [Saturday 07 August 2010] [15:18:14] <mato> well, then, it's a bit more work but you may as well do it that way...
| [Saturday 07 August 2010] [15:18:17] <mato> exactly
| [Saturday 07 August 2010] [15:18:18] <pieterh>  yes
| [Saturday 07 August 2010] [15:19:41] <sustrik>  mato: semantics quizz
| [Saturday 07 August 2010] [15:19:51] <mato> sustrik: go on
| [Saturday 07 August 2010] [15:20:00] <sustrik>  how should zmq_close behave
| [Saturday 07 August 2010] [15:20:08] <sustrik>  here's my suggestion:
| [Saturday 07 August 2010] [15:20:25] <sustrik>  1. for connections created by zmq_connect
| [Saturday 07 August 2010] [15:20:34] <sustrik>  send all data to the wire
| [Saturday 07 August 2010] [15:20:44] <sustrik>  even if the peer is disconnected at the moment
| [Saturday 07 August 2010] [15:20:50] <sustrik>  in such case wait till it reconnects
| [Saturday 07 August 2010] [15:20:55] <sustrik>  and send the data
| [Saturday 07 August 2010] [15:21:06] <sustrik>  2. connections established via bind
| [Saturday 07 August 2010] [15:21:23] <sustrik>  send the data to connections that are connected at the moment
| [Saturday 07 August 2010] [15:21:31] <sustrik>  ignore disconnected ones
| [Saturday 07 August 2010] [15:21:42] <sustrik>  if disconnection happens during sending the data
| [Saturday 07 August 2010] [15:21:52] <sustrik>  drop all the remaining messages
| [Saturday 07 August 2010] [15:22:07] <sustrik>  how does that feel?
| [Saturday 07 August 2010] [15:22:12] <mato> hmm
| [Saturday 07 August 2010] [15:22:20] <mato> i would unify 1) and 2)
| [Saturday 07 August 2010] [15:22:38] <sustrik>  how?
| [Saturday 07 August 2010] [15:22:41] <mato> i.e. for 1) if there are no connections then discard the data
| [Saturday 07 August 2010] [15:23:04] <sustrik>  what if there's a disconnected connection?
| [Saturday 07 August 2010] [15:23:10] <mato> also if a disconnect occurs during sending then discard the remaining data
| [Saturday 07 August 2010] [15:23:12] <mato> ignore it
| [Saturday 07 August 2010] [15:23:20] <sustrik>  consider this:
| [Saturday 07 August 2010] [15:23:23] <sustrik>  zmq_connect
| [Saturday 07 August 2010] [15:23:36] <sustrik>  connecting happens in background, will take some time
| [Saturday 07 August 2010] [15:23:38] <sustrik>  zmq_send
| [Saturday 07 August 2010] [15:23:41] <sustrik>  zmq_close
| [Saturday 07 August 2010] [15:23:45] <sustrik>  not yet connected
| [Saturday 07 August 2010] [15:23:47] <mato> yeh, i know what you're going to say ... yes
| [Saturday 07 August 2010] [15:23:49] <sustrik>  => drop the data
| [Saturday 07 August 2010] [15:23:52] <mato> yes yes
| [Saturday 07 August 2010] [15:23:54] <mato> how about this
| [Saturday 07 August 2010] [15:24:24] <mato> if we've never tried to connect, then behave as you describe
| [Saturday 07 August 2010] [15:24:37] <mato> if a connection has been seen, but is now disconnected, then ignore it
| [Saturday 07 August 2010] [15:24:53] <mato> don't know if it makes sense, just brainstorming
| [Saturday 07 August 2010] [15:24:58] <sustrik>  pretty inconsistent
| [Saturday 07 August 2010] [15:25:14] <sustrik>  behaves differently based on something invisible to user
| [Saturday 07 August 2010] [15:25:26] <mato> so does 2) in your case
| [Saturday 07 August 2010] [15:25:46] <sustrik>  i would prefer dropping the data straight away in 2)
| [Saturday 07 August 2010] [15:26:11] <sustrik>  however, at least trying gets the least surprise behaviour
| [Saturday 07 August 2010] [15:26:16] <sustrik>  with ZMQ_PUSH socket
| [Saturday 07 August 2010] [15:26:23] <pieterh>  i thought you were going to drop nothing until zmq_term?
| [Saturday 07 August 2010] [15:26:43] <sustrik>  how would you do that with zmq_bind?
| [Saturday 07 August 2010] [15:26:54] <sustrik>  you don't know what connections are going to arrive
| [Saturday 07 August 2010] [15:27:21] <pieterh>  it depends on the pattern, no?
| [Saturday 07 August 2010] [15:27:23] <sustrik>  at some point you have to decide:
| [Saturday 07 August 2010] [15:27:35] <sustrik>  "i don't care about connections that arrive from this point on"
| [Saturday 07 August 2010] [15:27:41] <pieterh>  if it's a pub socket and there are no connections, data will be dropped
| [Saturday 07 August 2010] [15:27:56] <pieterh>  if it's a req or xreq socket and there are no connections, data will be queued
| [Saturday 07 August 2010] [15:28:09] <pieterh>  but if you do zmq_term, it'll get dropped anyhow
| [Saturday 07 August 2010] [15:28:12] <pieterh>  no?
| [Saturday 07 August 2010] [15:28:24] <mato> no
| [Saturday 07 August 2010] [15:28:26] <pieterh>  :-)
| [Saturday 07 August 2010] [15:28:55] <mato> with the current implementation zmq_term() will just block forever if the data can't be sent
| [Saturday 07 August 2010] [15:29:17] <pieterh>  imo any working design that fixes that is already good enough for now
| [Saturday 07 August 2010] [15:29:25] <pieterh>  no need to attain perfection in a single cycle
| [Saturday 07 August 2010] [15:29:34] <mato> fixes what?
| [Saturday 07 August 2010] [15:29:44] <sustrik>  let's consider the pieter's algorithm
| [Saturday 07 August 2010] [15:29:46] <pieterh>  the blocking zmq_term() and/or lost messages
| [Saturday 07 August 2010] [15:30:00] <sustrik>  say we have a bound ZMQ_REP socket
| [Saturday 07 August 2010] [15:30:07] <pieterh>  sustrik: my algorithm is 90% ignorance
| [Saturday 07 August 2010] [15:30:16] <sustrik>  thinkng about it aloud...
| [Saturday 07 August 2010] [15:30:24] <sustrik>  so if clients disconnects
| [Saturday 07 August 2010] [15:30:31] <sustrik>  the reply will be queued
| [Saturday 07 August 2010] [15:30:43] <sustrik>  if the client doesn't reconnect
| [Saturday 07 August 2010] [15:30:47] <sustrik>  zmq_term will block
| [Saturday 07 August 2010] [15:31:02] <sustrik>  doesn't sound right
| [Saturday 07 August 2010] [15:31:15] <sustrik>  servers should terminate in more or less forcefull way
| [Saturday 07 August 2010] [15:31:21] <pieterh>  sustrik: i suggested zmq_term drop all waiting messages
| [Saturday 07 August 2010] [15:31:32] <pieterh>  but that zmq_close act more or less asynchronously
| [Saturday 07 August 2010] [15:31:38] <sustrik>  consider this:
| [Saturday 07 August 2010] [15:31:41] <sustrik>  zmq_send
| [Saturday 07 August 2010] [15:31:47] <sustrik>  zmq_close
| [Saturday 07 August 2010] [15:31:48] <sustrik>  zmq_term
| [Saturday 07 August 2010] [15:31:57] <sustrik>  the message will never get to the other side
| [Saturday 07 August 2010] [15:32:00] <mato> yes, that case must work, so term must block
| [Saturday 07 August 2010] [15:32:09] <mato> but we need to find some kind of middle ground here
| [Saturday 07 August 2010] [15:32:25] <pieterh>  question
| [Saturday 07 August 2010] [15:32:33] <pieterh>  "must work, term must block", but for how long?
| [Saturday 07 August 2010] [15:32:44] <pieterh>  does it make sense to block indefinitely?
| [Saturday 07 August 2010] [15:33:01] <sustrik>  yes?
| [Saturday 07 August 2010] [15:33:12] <sustrik>  in first iteration ye
| [Saturday 07 August 2010] [15:33:14] <pieterh>  besides, that scenario seems artificial, is it a real use case?
| [Saturday 07 August 2010] [15:33:14] <sustrik>  yes
| [Saturday 07 August 2010] [15:33:20] <sustrik>  :)
| [Saturday 07 August 2010] [15:33:25] <sustrik>  it's standard client case
| [Saturday 07 August 2010] [15:33:29] <sustrik>  zmq_connect
| [Saturday 07 August 2010] [15:33:31] <sustrik>  zmq_send
| [Saturday 07 August 2010] [15:33:34] <sustrik>  zmq_close
| [Saturday 07 August 2010] [15:33:34] <pieterh>  no, client is send/recv/close/term
| [Saturday 07 August 2010] [15:33:38] <sustrik>  zmq_term
| [Saturday 07 August 2010] [15:33:44] <mato> pieterh: it's precisely the case people are having a problem with at the moment
| [Saturday 07 August 2010] [15:33:46] <pieterh>  ah, push sockets, ok
| [Saturday 07 August 2010] [15:33:48] <sustrik>  that's for req/rep
| [Saturday 07 August 2010] [15:33:50] <mato> pieterh: and solving with various sleep() hacks
| [Saturday 07 August 2010] [15:33:58] <sustrik>  think of say push
| [Saturday 07 August 2010] [15:34:04] <pieterh>  i think it depends on the pattern, it's a policy issue
| [Saturday 07 August 2010] [15:34:15] <pieterh>  e.g. for pub socket, you'd drop data
| [Saturday 07 August 2010] [15:34:24] <pieterh>  but a push socket tries to deliver data
| [Saturday 07 August 2010] [15:34:34] <pieterh>  like an xreq socket will also do
| [Saturday 07 August 2010] [15:34:54] <sustrik>  see above
| [Saturday 07 August 2010] [15:35:07] <sustrik>  <sustrik> so if clients disconnects
| [Saturday 07 August 2010] [15:35:08] <sustrik>  <sustrik> the reply will be queued
| [Saturday 07 August 2010] [15:35:08] <sustrik>  <sustrik> if the client doesn't reconnect
| [Saturday 07 August 2010] [15:35:08] <sustrik>  <sustrik> zmq_term will block
| [Saturday 07 August 2010] [15:35:24] <sustrik>  the question is how to shut down a server
| [Saturday 07 August 2010] [15:35:41] <pieterh>  request/reply or push? i'm confused, you are mixing the two
| [Saturday 07 August 2010] [15:35:41] <mato> well, the counter-question is how to shut down a client with no server :-)
| [Saturday 07 August 2010] [15:35:45] <pieterh>  and i think the use cases are not the same
| [Saturday 07 August 2010] [15:35:59] <sustrik>  mato: block the client
| [Saturday 07 August 2010] [15:36:05] <sustrik>  that one is easy
| [Saturday 07 August 2010] [15:36:10] <pieterh>  reply socket is like push, it should block forever until someone can collect the message
| [Saturday 07 August 2010] [15:36:28] <pieterh>  where "forever" can be tuned with a timeout
| [Saturday 07 August 2010] [15:36:33] <pieterh>  imho
| [Saturday 07 August 2010] [15:36:45] <sustrik>  hm
| [Saturday 07 August 2010] [15:36:56] <mato> sustrik: what if the client *really* wants the context to go away...?
| [Saturday 07 August 2010] [15:36:57] <sustrik>  actually it makes sense
| [Saturday 07 August 2010] [15:36:59] <pieterh>  but xrep and pub sockets should not do thuis
| [Saturday 07 August 2010] [15:37:02] <pieterh>  *this
| [Saturday 07 August 2010] [15:37:08] <pieterh>  they have no delivery promise
| [Saturday 07 August 2010] [15:37:23] <pieterh>  we're talking about a basic reliability policy here
| [Saturday 07 August 2010] [15:37:41] <mato> sustrik: actually, pieter is right about PUB sockets... the policy should be similar to what happens on HWM being hit
| [Saturday 07 August 2010] [15:37:42] <pieterh>  pull and sub sockets are not relevant, obviously
| [Saturday 07 August 2010] [15:37:48] <sustrik>  mato: set SO_LINGER to 0?
| [Saturday 07 August 2010] [15:38:05] <pieterh>  yes, mato, it's a policy decision
| [Saturday 07 August 2010] [15:38:35]     * pieterh is so glad to be back on the caffeine...
| [Saturday 07 August 2010] [15:39:50] <mato> sustrik: yes, i just have a feeling that for trivial cases there should essentially be a "linger" option to zmq_term()
| [Saturday 07 August 2010] [15:40:23] <mato> hmm
| [Saturday 07 August 2010] [15:40:26] <sustrik>  what about this case:
| [Saturday 07 August 2010] [15:40:29] <pieterh>  setsockopt, please don't add options to zmq_init() or zmq_term()
| [Saturday 07 August 2010] [15:40:42] <pieterh>  and it can't be an option to zmq_term because it differs per socket
| [Saturday 07 August 2010] [15:40:55] <sustrik>  zmq_socket (PUB)
| [Saturday 07 August 2010] [15:41:10] <sustrik>  zmq_connect
| [Saturday 07 August 2010] [15:41:12] <sustrik>  zmq_send
| [Saturday 07 August 2010] [15:41:13] <sustrik>  zmq_close
| [Saturday 07 August 2010] [15:41:15] <sustrik>  zmq_term
| [Saturday 07 August 2010] [15:41:18] <sustrik>  message is lost
| [Saturday 07 August 2010] [15:41:39] <pieterh>  sustrik: you're right that connect/bind are relevant
| [Saturday 07 August 2010] [15:41:41] <sustrik>  is that the least surprise scenario?
| [Saturday 07 August 2010] [15:41:53] <pieterh>  no, PUB sockets don't normally connect anyhow
| [Saturday 07 August 2010] [15:42:08] <sustrik>  yes, it's the corner case
| [Saturday 07 August 2010] [15:42:12] <pieterh>  if you're using a PUB socket like that you should probably be using PUSH or XREQ
| [Saturday 07 August 2010] [15:42:23] <sustrik>  ?
| [Saturday 07 August 2010] [15:42:29] <pieterh>  if connect/bind are 100% orthogonal to socket policy
| [Saturday 07 August 2010] [15:42:39] <pieterh>  THEN whether the PUB socket connects or binds is immateriel
| [Saturday 07 August 2010] [15:42:44] <sustrik>  PUB is fanout while PUSH/XREQ are load-balanced
| [Saturday 07 August 2010] [15:42:55] <pieterh>  yes, my bad
| [Saturday 07 August 2010] [15:43:14] <sustrik>  i mean, dropping the message in the case above is ok
| [Saturday 07 August 2010] [15:43:20] <sustrik>  but it's kind of surprising
| [Saturday 07 August 2010] [15:43:30] <pieterh>  anyhow, PUB sockets as 'clients' is weird and does not (yet) count as a realistic use case
| [Saturday 07 August 2010] [15:43:44] <mato> pieterh: not for you, but people do weird things...
| [Saturday 07 August 2010] [15:43:52] <pieterh>  mato: yes, but often they should not
| [Saturday 07 August 2010] [15:44:08] <pieterh>  part of education is to help them not do that
| [Saturday 07 August 2010] [15:44:28] <sustrik>  ok, let me put the problem in another way
| [Saturday 07 August 2010] [15:44:34] <pieterh>  anyhow, if you make connect/bind direction relevant to socket policy you can do this
| [Saturday 07 August 2010] [15:44:42] <pieterh>  but that is a fairly big change semantically
| [Saturday 07 August 2010] [15:44:48] <sustrik>  the people often complain about not being able to write regular "clients"
| [Saturday 07 August 2010] [15:44:59] <sustrik>  i.e. dumb apps that connect to the server
| [Saturday 07 August 2010] [15:45:01] <mato> yeah, i'm wondering about that [connect/bind semantic change]
| [Saturday 07 August 2010] [15:45:13] <pieterh>  mato: i don't like it from a complexity PoV
| [Saturday 07 August 2010] [15:45:18] <sustrik>  the problem is that messages from the client may be lost
| [Saturday 07 August 2010] [15:45:28] <pieterh>  sustrik: PUB as client is weird
| [Saturday 07 August 2010] [15:45:32] <mato>  
| [Saturday 07 August 2010] [15:45:36] <sustrik>  it is
| [Saturday 07 August 2010] [15:45:46] <sustrik>   
| [Saturday 07 August 2010] [15:45:47] <pieterh>  it's not a use case I care to cuddle
| [Saturday 07 August 2010] [15:45:54] <sustrik>   
| [Saturday 07 August 2010] [15:46:14] <sustrik>  ok, i'll give it a thought
| [Saturday 07 August 2010] [15:46:18] <mato> sustrik: i'm thinking... the fact is, a lot of the time it's not obvious in zmq apps which end is a "server" and which is a "client"
| [Saturday 07 August 2010] [15:46:27] <sustrik>  true
| [Saturday 07 August 2010] [15:46:28] <pieterh>  mato: yes, it is
| [Saturday 07 August 2010] [15:46:33] <pieterh>  the static nodes are servers
| [Saturday 07 August 2010] [15:46:34] <sustrik>  you can be both
| [Saturday 07 August 2010] [15:46:38] <pieterh>  the dynamic nodes are clients
| [Saturday 07 August 2010] [15:46:45] <mato> bah
| [Saturday 07 August 2010] [15:46:51] <pieterh>  yes, this is clear
| [Saturday 07 August 2010] [15:46:58] <pieterh>  it's how every IETF protocol uses the semantics
| [Saturday 07 August 2010] [15:46:59] <mato> i can't discuss this with people talking all over one another
| [Saturday 07 August 2010] [15:47:20] <sustrik>  ok, go on
| [Saturday 07 August 2010] [15:47:20] <pieterh>  :-)
| [Saturday 07 August 2010] [15:47:24]     * sustrik is quiet
| [Saturday 07 August 2010] [15:47:28]     * pieterh shuts up
| [Saturday 07 August 2010] [15:48:04] <mato> so, i think that making such policy decisions on whether or not the connection came from bind or connect is a bad idea
| [Saturday 07 August 2010] [15:48:21] <mato> now, sustrik, you have the problem that a "server will never exit"
| [Saturday 07 August 2010] [15:48:36] <mato> i can counter that with what you told me about the client never exiting -- just use SO_LINGER
| [Saturday 07 August 2010] [15:49:11] <mato> and I can answer my own problem by saying that we need a setcontextopt() which lets you set a timeout for zmq_term()
| [Saturday 07 August 2010] [15:49:17] <mato> which can also be set to 0
| [Saturday 07 August 2010] [15:49:21]     * pieterh agrees with mato, connection direction must remain orthogonal to socket policy
| [Saturday 07 August 2010] [15:49:22] <mato> which solves all the cases
| [Saturday 07 August 2010] [15:49:23] <mato> no?
| [Saturday 07 August 2010] [15:49:38] <pieterh>  mato: yes
| [Saturday 07 August 2010] [15:49:56] <pieterh>  plus per socket-type policy similar to how we handle HWM
| [Saturday 07 August 2010] [15:50:07] <pieterh>  it's clear and systematic
| [Saturday 07 August 2010] [15:50:35] <mato> well, that only affects PUB really... i'm undecided on that but leaning towards doing what HWM does for consistency
| [Saturday 07 August 2010] [15:50:39] <mato> altough
| [Saturday 07 August 2010] [15:50:48] <mato> let me find the flow control docs... 2mins
| [Saturday 07 August 2010] [15:50:59] <sustrik>  ok, say we agree on the above
| [Saturday 07 August 2010] [15:51:07] <sustrik>  now let's enter level 2
| [Saturday 07 August 2010] [15:51:45] <sustrik>  there's no such thing as "socket queue"
| [Saturday 07 August 2010] [15:51:46] <pieterh>  mato: yes, it should be like HWM since it's about delivery guarantees
| [Saturday 07 August 2010] [15:51:59] <sustrik>  what we have is a queue per _connection_
| [Saturday 07 August 2010] [15:52:06] <pieterh>  right
| [Saturday 07 August 2010] [15:52:17] <sustrik>  so the messages sent are destined for a specific connection
| [Saturday 07 August 2010] [15:52:35] <sustrik>  now, the connection can be either reconnectable, or transient
| [Saturday 07 August 2010] [15:52:36] <pieterh>  how about an XREQ socket with zero connections?
| [Saturday 07 August 2010] [15:52:43] <sustrik>  it blocks
| [Saturday 07 August 2010] [15:52:48] <pieterh>  on send()?
| [Saturday 07 August 2010] [15:52:52] <sustrik>  blocks
| [Saturday 07 August 2010] [15:52:52] <pieterh>  ok
| [Saturday 07 August 2010] [15:52:58] <mato> one person at a time please, i can't follow
| [Saturday 07 August 2010] [15:53:13] <mato> else i'll go talk to sustrik out of band and face to face :-)
| [Saturday 07 August 2010] [15:53:35] <pieterh>  mato: this is... irc, people chat.
| [Saturday 07 August 2010] [15:53:44] <pieterh>  sustrik: please, don't let mato interrupt you
| [Saturday 07 August 2010] [15:53:50] <sustrik>  :)
| [Saturday 07 August 2010] [15:53:56] <sustrik>  eee...
| [Saturday 07 August 2010] [15:54:02] <sustrik>  i've lost my train of thought
| [Saturday 07 August 2010] [15:54:07] <mato> see :)
| [Saturday 07 August 2010] [15:54:10] <pieterh>  no queues per socket...
| [Saturday 07 August 2010] [15:54:11] <sustrik>  aha
| [Saturday 07 August 2010] [15:54:38] <sustrik>  if the connection is transient and it disconnects
| [Saturday 07 August 2010] [15:54:44] <sustrik>  it will never get reconnected
| [Saturday 07 August 2010] [15:55:02] <sustrik>  in such case there's nothing to do but to drop the messages
| [Saturday 07 August 2010] [15:55:14] <sustrik>  even if socket type is REQ or whatever
| [Saturday 07 August 2010] [15:55:21] <pieterh>  sure
| [Saturday 07 August 2010] [15:55:31] <sustrik>  which gives us inconsistent semantics:
| [Saturday 07 August 2010] [15:55:33] <pieterh>  it's an unrecoverable network error
| [Saturday 07 August 2010] [15:55:38] <sustrik>  1. transient connecitons - drop
| [Saturday 07 August 2010] [15:55:51] <sustrik>  2. permanent connection - wait till send
| [Saturday 07 August 2010] [15:55:52] <pieterh>  what defines a transient connection?
| [Saturday 07 August 2010] [15:55:53] <sustrik>  sent
| [Saturday 07 August 2010] [15:56:10] <mato> sustrik: just a minute, ignoring close(), send() handles transient connections reconnecting, does it not?
| [Saturday 07 August 2010] [15:56:19] <sustrik>  basically it's a connection client's connection to server
| [Saturday 07 August 2010] [15:56:44] <pieterh>  you mean as compared to incoming connection on bound endpoint?
| [Saturday 07 August 2010] [15:57:07] <pieterh>  why will a transient connection never get reconnected?
| [Saturday 07 August 2010] [15:57:15] <pieterh>  there is too much data missing from your explanation, sorry
| [Saturday 07 August 2010] [15:57:55] <mato> sustrik: by "transient connection", you mean an inbound connection?
| [Saturday 07 August 2010] [15:57:58]     * mato is confused
| [Saturday 07 August 2010] [15:58:32] <mato> sustrik: if so, by definition, that inbound (transient) connection will be someone else's outbound (permanent) connection
| [Saturday 07 August 2010] [15:58:39] <sustrik>  when the client has no identity
| [Saturday 07 August 2010] [15:58:39] <sustrik>  if client dies
| [Saturday 07 August 2010] [15:58:39] <sustrik>  it'll never get reconnected
| [Saturday 07 August 2010] [15:58:40] <sustrik>  there are 3 options:
| [Saturday 07 August 2010] [15:58:40] <sustrik>  1. zmq_connect
| [Saturday 07 August 2010] [15:58:41] <sustrik>  here we are proactively creating a connection, we can reconnect if the connection breaks
| [Saturday 07 August 2010] [15:58:42] <sustrik>  2. zmq_bind
| [Saturday 07 August 2010] [15:58:43] <sustrik>  here we are waiting for connections, if connections breaks there's no way of telling the new connection is actually a reincarnation of the old one
| [Saturday 07 August 2010] [15:58:44] <sustrik>  3. zmq_bind + connecter has an unique identity
| [Saturday 07 August 2010] [15:59:03] <sustrik>  ok
| [Saturday 07 August 2010] [15:59:06] <sustrik>  think of a server
| [Saturday 07 August 2010] [15:59:15] <pieterh>  hmm... so when an anonymous connection breaks, it's dead
| [Saturday 07 August 2010] [15:59:33] <pieterh>  but if the application did not specify an identity
| [Saturday 07 August 2010] [15:59:42] <pieterh>  this should not change ITS semantic view of things
| [Saturday 07 August 2010] [16:00:22] <sustrik>  connection is accepted
| [Saturday 07 August 2010] [16:00:22] <sustrik>  pieterh: exactly
| [Saturday 07 August 2010] [16:00:22] <sustrik>  that's case 2
| [Saturday 07 August 2010] [16:00:22] <sustrik>  case 3 is when client has a strong identity
| [Saturday 07 August 2010] [16:00:23] <sustrik>  in that case it can announce its identity on reconnect
| [Saturday 07 August 2010] [16:00:24] <sustrik>  and server can attach it to the existing session
| [Saturday 07 August 2010] [16:00:26] <sustrik>  it does not
| [Saturday 07 August 2010] [16:00:48] <pieterh>  sustrik: would you perhaps write this up on the wiki somewhere?
| [Saturday 07 August 2010] [16:00:58] <pieterh>  i'm tired and need to leave soon but would like to understand this fully
| [Saturday 07 August 2010] [16:01:11] <mato> sustrik: but all connections have an identity. weak identity still means we can see when that client comes back
| [Saturday 07 August 2010] [16:01:35] <mato> sustrik: it won't come back if it's restarted, but then we never know if a client *will* come back
| [Saturday 07 August 2010] [16:01:44] <mato> sustrik: strong identity or not
| [Saturday 07 August 2010] [16:02:54] <sustrik>  the only semantic diference can be observed on client restart
| [Saturday 07 August 2010] [16:02:54] <sustrik>  i am not sure how it works/should work myself
| [Saturday 07 August 2010] [16:02:54] <sustrik>  identity stuff is not trivial
| [Saturday 07 August 2010] [16:02:55] <sustrik>  it's actually about how 0mq handles application restart
| [Saturday 07 August 2010] [16:02:56] <sustrik>  we have something that kind of works in some scenarios
| [Saturday 07 August 2010] [16:02:56] <sustrik>  but is in no way theoretically sound
| [Saturday 07 August 2010] [16:02:58] <sustrik>  the whole thing intersects with intended REQ/REP resend functionality
| [Saturday 07 August 2010] [16:04:06] <mato> sustrik: well, we can do two things...
| [Saturday 07 August 2010] [16:04:22] <mato> sustrik: i think it would be helpful if all the cases of the new semantics are formally written down
| [Saturday 07 August 2010] [16:04:30] <pieterh>  yes
| [Saturday 07 August 2010] [16:04:43] <pieterh>  this should be written down first
| [Saturday 07 August 2010] [16:04:46] <mato> sustrik: then we can discuss that in person which may help, and present any results on the mailing list
| [Saturday 07 August 2010] [16:05:04] <pieterh>  IMO the intended REQ/REP resend can be built on top of this
| [Saturday 07 August 2010] [16:05:17] <pieterh>  or perhaps it will be the same thing
| [Saturday 07 August 2010] [16:06:10] <mato> sustrik: we can discuss this tomorrow if you like? after all, that's why i'm here over the weekend
| [Saturday 07 August 2010] [16:06:22] <mato> sustrik: and we can write the proposal together if you want
| [Saturday 07 August 2010] [16:06:22] <pieterh>  mato: i have the git workflows from wikidot, will post to the wiki tomorrow in edited form
| [Saturday 07 August 2010] [16:06:44] <mato> pieterh: ok
| [Saturday 07 August 2010] [16:07:02] <mato> sustrik: ack?
| [Saturday 07 August 2010] [16:07:23] <sustrik>  not relevant, because if it comes back its treated as a different client
| [Saturday 07 August 2010] [16:07:23] <sustrik>  thus messages queued for it's first reincarnation
| [Saturday 07 August 2010] [16:07:24] <sustrik>  won't be delivered to the next one
| [Saturday 07 August 2010] [16:07:25] <sustrik>  so, from the point of server, disconnection on anonymous session = permanently dead
| [Saturday 07 August 2010] [16:07:26] <sustrik>  in other words, there is no permanent session created on server side for anonymous connections
| [Saturday 07 August 2010] [16:07:27] <sustrik>  that kind of thing would very quickly exhaust all the memory
| [Saturday 07 August 2010] [16:07:29] <sustrik>  anyway, thanks for the "algorithm based on socket type" suggestion
| [Saturday 07 August 2010] [16:07:29] <sustrik>  i'm going to think about it
| [Saturday 07 August 2010] [16:07:33] <mato> ah, sustrik is lagged
| [Saturday 07 August 2010] [16:07:38] <mato> this is why the conversation sucks
| [Saturday 07 August 2010] [16:07:41] <pieterh>  lol
| [Saturday 07 August 2010] [16:07:59] <mato> i'll call him :)
| [Saturday 07 August 2010] [16:08:04]     * pieterh considers using CIA-19 as proxy for IRC conversations...
| [Saturday 07 August 2010] [16:08:08] <sustrik>  here i am again
| [Saturday 07 August 2010] [16:08:22] <sustrik>  my connection block regularlu
| [Saturday 07 August 2010] [16:08:28] <sustrik>  hello world!
| [Saturday 07 August 2010] [16:08:33] <sustrik>  hoo!
| [Saturday 07 August 2010] [16:08:36] <mato> :-)
| [Saturday 07 August 2010] [16:08:44] <sustrik>  is anyone there???
| [Saturday 07 August 2010] [16:08:46] <pieterh>  sustrik is on a transient connection
| [Saturday 07 August 2010] [16:08:48] <mato> sustrik: yes
| [Saturday 07 August 2010] [16:08:53] <pieterh>  sustrik: no
| [Saturday 07 August 2010] [16:08:58] <sustrik>  :)
| [Saturday 07 August 2010] [16:08:58] <mato> bah
| [Saturday 07 August 2010] [16:09:10]     * mato goes off to use this thing called a telephone
| [Saturday 07 August 2010] [16:09:25] <pieterh>  sustrik: IMO anonymous connection that is dead is the same as no connection at all
| [Saturday 07 August 2010] [16:09:30] <pieterh>  ex-parrots do not count
| [Saturday 07 August 2010] [16:10:37] <pieterh>  you might want to requeue message(s) that failed
| [Saturday 07 August 2010] [16:10:41] <pieterh>  or not
| [Saturday 07 August 2010] [16:10:54] <pieterh>  its kind of an edge case and does not need to be solved properly now
| [Saturday 07 August 2010] [16:16:55] <sustrik>  it's the case that's used all the time
| [Saturday 07 August 2010] [16:17:11] <sustrik>  people normally don't use identities to create permanent connections
| [Saturday 07 August 2010] [16:19:32]     * sustrik is leaving
| [Saturday 07 August 2010] [16:19:36] <sustrik>  cyl
| [Saturday 07 August 2010] [16:20:58] <mato> sustrik: i'll think about it/sleep on it and will try to enumerate the cases tomorrow
| [Saturday 07 August 2010] [16:21:01] <mato> sustrik: cyl
| [Sunday 08 August 2010] [07:17:03] <pieter_hintjens>    Have written proposal for git workflow: http://www.zeromq.org/docs:procedures
| [Sunday 08 August 2010] [07:17:20] <pieter_hintjens>    what we're doing now is not really scalable
| [Sunday 08 August 2010] [07:21:29] <sustrik>    pieterh: ok, i'll give it a read in ~1hour
| [Sunday 08 August 2010] [07:21:54] <pieterh>    no hurry
| [Sunday 08 August 2010] [07:22:10] <pieterh>    it really needs a git guru to give it a quick review
| [Sunday 08 August 2010] [07:22:52] <pieterh>    but most of it is based on experience from wikidot.com
| [Sunday 08 August 2010] [07:22:53] <sustrik>    martin hurton seems to know git quite well
| [Sunday 08 August 2010] [07:23:12] <pieterh>    ah, great
| [Sunday 08 August 2010] [07:54:57] <mato>   pieterh: i'll take a look at it also in some time
| [Sunday 08 August 2010] [07:55:23] <mato>   pieterh: please note that could you maybe prominently mark your various strawmen with "*** PROPOSAL ***" or something?
| [Sunday 08 August 2010] [07:56:04] <mato>   pieterh: so that it's obvious that is not a final decision and is still being discussed, and may not reflect reality
| [Sunday 08 August 2010] [07:56:20] <mato>   pieterh: otherwise it's a bit confusing for people (think also of random people browsing the site)
| [Sunday 08 August 2010] [07:56:43] <mato>   pieterh: oh, and the page title is "Source" for some reason...
| [Sunday 08 August 2010] [07:59:43] <mato>   pieterh: I see you changed the C binding to push the age-old iMatix 'c' script, this is also somewhat counter-productive... the documentation should be environment-agnostic
| [Sunday 08 August 2010] [08:00:15] <pieterh>    mato: proposal, indeed.
| [Sunday 08 August 2010] [08:00:22] <pieterh>    i wrote that but not in huge letters.
| [Sunday 08 August 2010] [08:00:39] <mato>   pieterh: i'm almost thinking of something damn-bleedin-obvious for proposals
| [Sunday 08 August 2010] [08:00:44] <pieterh>    i find the 'c' script useful and felt it was worth sharing but feel free to remove it
| [Sunday 08 August 2010] [08:00:51] <pieterh>    mato: ?
| [Sunday 08 August 2010] [08:00:54] <mato>   pieterh: big header in colorful background at the start of the page
| [Sunday 08 August 2010] [08:01:40] <mato>   pieterh: i'm not against the 'c' script, i'm against the C binding docs having a single example about compiling which only mentions the 'c' script
| [Sunday 08 August 2010] [08:02:02] <pieterh>    i'll put something in large bold for the proposal, you can adjust to taste
| [Sunday 08 August 2010] [08:02:16] <mato>   pieterh: one proposal...
| [Sunday 08 August 2010] [08:02:21] <pieterh>    shoot
| [Sunday 08 August 2010] [08:02:37] <mato>   pieterh: I find it hard to see what's changed on the Wiki (notification emails are useless)... can we do one or both of the following?
| [Sunday 08 August 2010] [08:02:58] <mato>   pieterh: 1. Put a Recent Wiki Changes link on the sidebar or at least the home page
| [Sunday 08 August 2010] [08:03:10] <pieterh>    the emails are useless, they don't show diffs, i know
| [Sunday 08 August 2010] [08:03:12] <mato>   pieterh: 2. Maybe better, make that part of a box on the home page with a feed of the last X changes
| [Sunday 08 August 2010] [08:03:16] <pieterh>    recent changes would be good, yes
| [Sunday 08 August 2010] [08:03:35] <mato>   pieterh: ah, i see you took the ML summary out of the home page, why?
| [Sunday 08 August 2010] [08:03:52] <mato>   pieterh: Having the home page at least partly as a dashboard for all recent activity seemed useful
| [Sunday 08 August 2010] [08:04:04] <mato>   pieterh: also reassures newcomers that lots of stuff is going on
| [Sunday 08 August 2010] [08:04:07] <pieterh>    i was experimenting with the twitter box
| [Sunday 08 August 2010] [08:04:21] <mato>   forget twitter, it's just pass-along value
| [Sunday 08 August 2010] [08:04:33] <pieterh>    maybe but i get a lot of stuff off that
| [Sunday 08 August 2010] [08:04:33] <mato>   having a ML and recent changes feeds on the home page seems much more useful to me
| [Sunday 08 August 2010] [08:04:40] <pieterh>    sure
| [Sunday 08 August 2010] [08:04:54] <pieterh>    i'm pretty agnostic about this, it's good to try stuff and see what sticks
| [Sunday 08 August 2010] [08:05:02] <pieterh>    the ML stuff is there, commented
| [Sunday 08 August 2010] [08:05:24] <mato>   besides, i don't see the twitter box anyway :)
| [Sunday 08 August 2010] [08:05:37] <pieterh>    yeah, that explains something
| [Sunday 08 August 2010] [08:05:48] <mato>   what's that? :-)
| [Sunday 08 August 2010] [08:06:00] <pieterh>    that you ask where the ML history went to
| [Sunday 08 August 2010] [08:06:03] <pieterh>    otherwise it'd be obvious
| [Sunday 08 August 2010] [08:06:06] <mato>   yeah :)
| [Sunday 08 August 2010] [08:06:17] <pieterh>    i'll kill it, it's kind of annoying anyhow but it'd be nice to get one 'hate/like' response from a newcomer
| [Sunday 08 August 2010] [08:06:32] <pieterh>    we're both way too familiar with the project to know what visitors like
| [Sunday 08 August 2010] [08:07:01] <mato>   yeah, but the home page is also about being useful to all members of the community, not just impressing naive noobs 
| [Sunday 08 August 2010] [08:07:06] <mato>   so there's a compromise there somewhere :-)
| [Sunday 08 August 2010] [08:07:48] <mato>   oh and you still have "Thanks to Matt Weinstein for the picture." which appears to have also gone
| [Sunday 08 August 2010] [08:07:55] <pieterh>    ah
| [Sunday 08 August 2010] [08:08:00] <pieterh>    btw, it's a wiki :-)
| [Sunday 08 August 2010] [08:08:33] <mato>   true
| [Sunday 08 August 2010] [08:08:43] <pieterh>    i mean, feel free to edit when you feel it's necessary
| [Sunday 08 August 2010] [08:08:50] <pieterh>    shoot first, argue later
| [Sunday 08 August 2010] [08:08:53] <pieterh>    that's the whole fun :-)
| [Sunday 08 August 2010] [08:09:17] <pieterh>    shall i restore the lolcat?
| [Sunday 08 August 2010] [08:09:23] <pieterh>    i figured that or twitter but not both
| [Sunday 08 August 2010] [08:11:34] <mato>   well, it's kind of cute... 
| [Sunday 08 August 2010] [08:13:48] <pieterh>    futurama did it
| [Sunday 08 August 2010] [08:14:52] <mato>   makes me want to add in the ZMQ_IWANTBITES and ZMQ_ICANHAZBITES 
| [Sunday 08 August 2010] [08:14:59] <mato>   software should not be too serious :-)
| [Sunday 08 August 2010] [08:17:03] <pieterh>    well, it got my vote
| [Sunday 08 August 2010] [08:17:09] <pieterh>    i think those would make
| [Sunday 08 August 2010] [08:17:22] <pieterh>    *would make good aliases for PULL/PUSH
| [Sunday 08 August 2010] [08:31:12] <pieterh>    mato: recent site changes added to front page
| [Sunday 08 August 2010] [08:33:10] <mato>   pieterh: nice
| [Sunday 08 August 2010] [08:33:38] <pieterh>    changed to show page size instead of editor
| [Sunday 08 August 2010] [08:33:49] <pieterh>    only shows pages from docs/whitepapers/areas
| [Sunday 08 August 2010] [08:33:51] <mato>   editor is not bad actually
| [Sunday 08 August 2010] [08:34:08] <mato>   page size is kind of useless
| [Sunday 08 August 2010] [08:34:18] <mato>   who cares if page is XXXX chars
| [Sunday 08 August 2010] [08:34:25] <pieterh>    well, this editor does :-)
| [Sunday 08 August 2010] [08:34:29] <pieterh>    anyhow, reverted
| [Sunday 08 August 2010] [08:34:59] <sustrik>    if you want all three (mailing list, wiki, blog) on the front page you should limit number of items in each
| [Sunday 08 August 2010] [08:35:01] <sustrik>    say 5
| [Sunday 08 August 2010] [08:35:53] <mato>   yeah. it'd also be really nice to get the date in the mailing list posts, but i remember trying to make that work and failing miserably :-(
| [Sunday 08 August 2010] [08:36:03] <mato>   due to the rss feed being kind of broken
| [Sunday 08 August 2010] [08:36:21] <pieterh>    yup
| [Sunday 08 August 2010] [08:37:49] <mato>   pieterh: i see you're editing it (ha, it said locked) can you change the line-height in the recent changes to match the others?
| [Sunday 08 August 2010] [08:38:03] <pieterh>    mato: ack
| [Sunday 08 August 2010] [08:40:11] <pieterh>    mato: it's kind of hacky, but now the right column is a lot more compact and IMO readable
| [Sunday 08 August 2010] [08:40:14] <mato>   sustrik: i'm trying to enumerate those cases we discussed yesterday. for (x)req/(x)rep/push it all makes sense
| [Sunday 08 August 2010] [08:40:48] <mato>   sustrik: PUB is the only "funny" one
| [Sunday 08 August 2010] [08:41:15] <mato>   sustrik: For PUB sockets, all connections are basically transient, right?
| [Sunday 08 August 2010] [08:41:17] <pieterh>    sustrik: i had a thought about identities... could they not always be permanent but with a timeout at the server side?
| [Sunday 08 August 2010] [08:42:18] <pieterh>    this would solve (a) resource death when using explicit identities and (b) weirdness due to permanent/transient differences
| [Sunday 08 August 2010] [08:42:44] <mato>   actually, the cases I have (except PUB) are all quite systematic:
| [Sunday 08 August 2010] [08:42:51] <pieterh>    by 'server side' i obviously mean 'node that binds endpoint'
| [Sunday 08 August 2010] [08:42:51] <mato>    Permanent, strong: Retry
| [Sunday 08 August 2010] [08:42:52] <mato>    Permanent, weak: Retry
| [Sunday 08 August 2010] [08:42:52] <mato>    Transient, strong: Retry
| [Sunday 08 August 2010] [08:42:52] <mato>    Transient, weak: Ignore
| [Sunday 08 August 2010] [08:43:13] <pieterh>    4 kinds of connection?
| [Sunday 08 August 2010] [08:43:23] <mato>   yup
| [Sunday 08 August 2010] [08:43:29] <pieterh>    times X types of socket policy?
| [Sunday 08 August 2010] [08:43:34] <pieterh>    seriously?
| [Sunday 08 August 2010] [08:44:15] <pieterh>    how about PAIR sockets?
| [Sunday 08 August 2010] [08:44:19] <mato>   in my doc it's all the same actually for all sockets except PUB(to be discussed) and the sockets which don't do send() where the policy is N/A
| [Sunday 08 August 2010] [08:44:23] <sustrik>    i thouht of it as well
| [Sunday 08 August 2010] [08:44:45] <sustrik>    the point is that in this case we are not trying to ensure consistent semantics
| [Sunday 08 August 2010] [08:44:58] <sustrik>    instead, we want to improve reliability a little
| [Sunday 08 August 2010] [08:45:08] <sustrik>    in a non-systematic way
| [Sunday 08 August 2010] [08:45:09] <pieterh>    reliability is semantics
| [Sunday 08 August 2010] [08:45:12] <mato>   yes, but the consistent semantics actually seem to make sense when you write them down
| [Sunday 08 August 2010] [08:45:29] <sustrik>    consider this case:
| [Sunday 08 August 2010] [08:45:34] <pieterh>    mato: if pub sockets are always transient then it's also consistent, no?
| [Sunday 08 August 2010] [08:45:41] <mato>   pieterh: precisely
| [Sunday 08 August 2010] [08:45:48] <sustrik>    pub/sub used for notifying all the componetns on the network to shut down
| [Sunday 08 August 2010] [08:45:53] <pieterh>    fair enough
| [Sunday 08 August 2010] [08:46:06] <sustrik>    if the component is disconnected, it's ok to loose the message
| [Sunday 08 August 2010] [08:46:11] <pieterh>    i suspect we want a new kind of socket that does reliable fanout
| [Sunday 08 August 2010] [08:46:15] <pieterh>    eventually
| [Sunday 08 August 2010] [08:46:20] <sustrik>    the admin should then shut it down by hand
| [Sunday 08 August 2010] [08:46:23] <mato>   sustrik: can you answer my question please? PUB sockets have only transient connections, right?
| [Sunday 08 August 2010] [08:46:35] <mato>   sustrik: that's the nature of a PUB socket..., right?
| [Sunday 08 August 2010] [08:46:48] <sustrik>    kind of
| [Sunday 08 August 2010] [08:46:57] <mato>   please explain "kind of" :-)
| [Sunday 08 August 2010] [08:46:58] <sustrik>    currently it allows you to set an identuity
| [Sunday 08 August 2010] [08:47:05] <sustrik>    but probably it should not
| [Sunday 08 August 2010] [08:47:22]   * sustrik is back to coding
| [Sunday 08 August 2010] [08:47:40] <mato>   sustrik: how can i propose or discuss these cases with you?
| [Sunday 08 August 2010] [08:47:51] <pieterh>    sustrik: imo you are reinventing UDP and TCP to some extent
| [Sunday 08 August 2010] [08:48:02] <mato>   sustrik: i think the 1st naive consistent policy will work "well enough" for a 1st release
| [Sunday 08 August 2010] [08:48:38]   * pieterh is not complaining but thinking that explicit identities will be inevitable for any mock TCP patterns
| [Sunday 08 August 2010] [08:48:48] <pieterh>    mato: gets my vote, yes
| [Sunday 08 August 2010] [08:48:51] <mato>   that's the point of my policy
| [Sunday 08 August 2010] [08:49:24] <mato>   try something "good enough" as a first cut, and then deal with the corners later 
| [Sunday 08 August 2010] [08:49:35] <mato>   unless there's something terribly wrong with my "good enough" proposal
| [Sunday 08 August 2010] [08:49:36] <pieterh>    mato: what is 'strong' vs. 'weak'?
| [Sunday 08 August 2010] [08:49:44] <pieterh>    connect vs. bind?
| [Sunday 08 August 2010] [08:49:46] <mato>   pieterh: strong is where an identity has been set
| [Sunday 08 August 2010] [08:49:55] <pieterh>    and permanent vs. transient?
| [Sunday 08 August 2010] [08:50:05] <mato>   pieterh: weak is where the identity is auto-generated (i.e. won't persist against restarts of the context)
| [Sunday 08 August 2010] [08:50:12] <pieterh>    right
| [Sunday 08 August 2010] [08:50:32] <mato>   pieterh: permanent is basically outbound/connect and transient is inbound/bind
| [Sunday 08 August 2010] [08:50:36] <pieterh>    does receiver know if identity is generated (by sender) or not?
| [Sunday 08 August 2010] [08:50:42] <mato>   afaik yes
| [Sunday 08 August 2010] [08:50:47] <pieterh>    it's in the WLP?
| [Sunday 08 August 2010] [08:50:49] <pieterh>    ok. noted.
| [Sunday 08 August 2010] [08:50:51] <mato>   s/afaik/definitely/
| [Sunday 08 August 2010] [08:50:54] <mato>   what's the WLP?
| [Sunday 08 August 2010] [08:51:11] <pieterh>    it's the secret wire level protocol 
| [Sunday 08 August 2010] [08:51:26] <mato>   pieterh: ah, yes
| [Sunday 08 August 2010] [08:51:35] <pieterh>    there _is_ a single 0MQ WLP there somewhere :-)
| [Sunday 08 August 2010] [08:51:41] <pieterh>    i'll extract it and document it
| [Sunday 08 August 2010] [08:51:46] <mato>   sustrik: hello?
| [Sunday 08 August 2010] [08:51:54] <pieterh>    so the one thing that's unpleasant about your model is that it's no longer orthogonal to connect/bind direction
| [Sunday 08 August 2010] [08:52:13] <pieterh>    but i don't agree with the thesis that connect/bind direction is irrelevant, i think it matters very mucjh
| [Sunday 08 August 2010] [08:52:15] <pieterh>    *much
| [Sunday 08 August 2010] [08:52:21] <pieterh>    so i endorse your model 100%
| [Sunday 08 August 2010] [08:52:49] <pieterh>    basically transient connections to dynamic nodes are not reliable
| [Sunday 08 August 2010] [08:52:54] <pieterh>    and all other ones are kind of reliable
| [Sunday 08 August 2010] [08:53:04] <mato>   yup
| [Sunday 08 August 2010] [08:53:07] <pieterh>    if you want reliable pub
| [Sunday 08 August 2010] [08:53:15] <pieterh>    then pub has to connect to all subs
| [Sunday 08 August 2010] [08:53:21] <pieterh>    nice use case in fact
| [Sunday 08 August 2010] [08:53:33] <mato>   well, no, actually if you want reliable pub you set identity on your subs
| [Sunday 08 August 2010] [08:53:37] <mato>   that's the idea
| [Sunday 08 August 2010] [08:53:53] <mato>   pub doesn't really have the concept of "connecting" anywhere
| [Sunday 08 August 2010] [08:53:53] <pieterh>    no, because then pub will crash
| [Sunday 08 August 2010] [08:54:07] <mato>   ?
| [Sunday 08 August 2010] [08:54:40] <pieterh>    sustrik: currently it [PUB] allows you to set an identuity
| [Sunday 08 August 2010] [08:54:41] <pieterh>    sustrik: but probably it should not
| [Sunday 08 August 2010] [08:54:52] <pieterh>    accumulation of identities will kill server
| [Sunday 08 August 2010] [08:55:03] <mato>   pieterh: i'm talking about identity being set on the SUB side, not on the PUB side
| [Sunday 08 August 2010] [08:55:19] <pieterh>    ok, maybe i'm confused
| [Sunday 08 August 2010] [08:55:27] <pieterh>    but still... you don't need identities for this
| [Sunday 08 August 2010] [08:55:28] <mato>   pieterh: that way the SUB connection to PUB becomes transient, strong, which is "reliable"
| [Sunday 08 August 2010] [08:55:42] <pieterh>    ok, fair enough
| [Sunday 08 August 2010] [08:55:57]   * mato would like sustrik's opinion
| [Sunday 08 August 2010] [08:56:03] <pieterh>    sustrik is coding, IMO :_)
| [Sunday 08 August 2010] [08:56:08] <pieterh>    :~)
| [Sunday 08 August 2010] [08:56:12] <pieterh>    :=)
| [Sunday 08 August 2010] [08:56:17] <pieterh>    damn, can't get it working
| [Sunday 08 August 2010] [08:56:38] <mato>   yeah, but then i'm not sure what he's coding, and why he asked for opinions in the 1st place :-)
| [Sunday 08 August 2010] [08:57:03] <pieterh>    mato: your model looks right, from my perspective
| [Sunday 08 August 2010] [09:01:59] <mato>   let's see what sustrik comes up with, there's nothing else i can do right now
| [Sunday 08 August 2010] [09:23:32] <sustrik>    re for a second
| [Sunday 08 August 2010] [09:23:59] <sustrik>    mato: your proposal doesn't solve the case when connection is not yet established when zmq_close is called
| [Sunday 08 August 2010] [09:25:46] <mato>   sustrik: hmm, i'm thinking about it
| [Sunday 08 August 2010] [09:26:22] <mato>   sustrik: why does it not solve the case
| [Sunday 08 August 2010] [09:27:00] <mato>   sustrik: Permanent, strong: Retry, Permanent, weak: Retry
| [Sunday 08 August 2010] [09:27:10] <mato>   sustrik: seems to work to me...
| [Sunday 08 August 2010] [09:27:50] <mato>   sustrik: it makes PUB behave funny, but that's because I have a problem understanding PUB semantics, which is why I asked you about it
| [Sunday 08 August 2010] [09:29:13] <sustrik>    that's what i was trying to explain
| [Sunday 08 August 2010] [09:29:23] <mato>   sustrik: however, it does give you a case where you can make PUB behave "reliably", namely by setting your identity on the SUB side
| [Sunday 08 August 2010] [09:30:04] <sustrik>    as already noted, that shouldn't be allowed
| [Sunday 08 August 2010] [09:30:28] <mato>   sustrik: if PUB/SUB should not allow identities then the point is moot./
| [Sunday 08 August 2010] [09:30:53] <sustrik>    consider the shutdown example abover
| [Sunday 08 August 2010] [09:31:11] <sustrik>    publication is not reliable
| [Sunday 08 August 2010] [09:31:21] <sustrik>    message can not be delivered in certain cases
| [Sunday 08 August 2010] [09:31:32] <sustrik>    it's ok as admin can shut down the component by hand
| [Sunday 08 August 2010] [09:32:11] <sustrik>    however, systematic consequence of such behaviour => drop all messages-in-flight at zmq_close
| [Sunday 08 August 2010] [09:32:21] <sustrik>    doesn't really work
| [Sunday 08 August 2010] [09:32:31] <sustrik>    foreach (components)
| [Sunday 08 August 2010] [09:32:39] <sustrik>        send (component, shutdown)
| [Sunday 08 August 2010] [09:32:45] <sustrik>    close()
| [Sunday 08 August 2010] [09:32:53] <sustrik>    would result in no message being delivered
| [Sunday 08 August 2010] [09:33:01] <sustrik>    even to boxes that are online and connected
| [Sunday 08 August 2010] [09:33:22] <sustrik>    what we need is kind of IP's "best effort" policy
| [Sunday 08 August 2010] [09:33:32] <sustrik>    i.e. send if possible, drop otherwise
| [Sunday 08 August 2010] [09:33:55] <sustrik>    that's not a theoretically coherent behaviour
| [Sunday 08 August 2010] [09:34:06] <mato>   the problem is the "send if possible" policy collides with connect being completely asynchronous
| [Sunday 08 August 2010] [09:34:07] <sustrik>    it's just making it work in least-surprise way
| [Sunday 08 August 2010] [09:34:49] <sustrik>    just devise a heuristic that would handle all the cases is not surprising manner
| [Sunday 08 August 2010] [09:34:51] <sustrik>    that's it
| [Sunday 08 August 2010] [09:35:02] <sustrik>    no need for real coherency
| [Sunday 08 August 2010] [09:35:21] <mato>   sustrik: i think that heuristic has something to do with "first connection showing up on socket"
| [Sunday 08 August 2010] [09:35:31] <sustrik>    yes, somethig like that
| [Sunday 08 August 2010] [09:35:53] <mato>   and timeouts...
| [Sunday 08 August 2010] [09:35:58] <sustrik>    possibly
| [Sunday 08 August 2010] [09:36:05] <mato>   but timeouts are step 2
| [Sunday 08 August 2010] [09:36:11] <mato>   in step 1 (what we're doing now)...
| [Sunday 08 August 2010] [09:36:12] <sustrik>    sure
| [Sunday 08 August 2010] [09:36:44] <sustrik>    step 0, is composing i/o objects into bundles
| [Sunday 08 August 2010] [09:36:47] <mato>   is it not sufficient to make the heuristic be that we wait forever for a connection to show up *iff* none have at the point close was called?
| [Sunday 08 August 2010] [09:37:06] <sustrik>    so that i/o object A can postpone termination of i/o object B
| [Sunday 08 August 2010] [09:37:12] <sustrik>    that's what i am working on now
| [Sunday 08 August 2010] [09:37:41] <sustrik>    mato: we can do it that way for the starters
| [Sunday 08 August 2010] [09:37:55] <mato>   sustrik: that would seem to be the right thing to do now
| [Sunday 08 August 2010] [09:38:00] <sustrik>    on zmq_connect side of course
| [Sunday 08 August 2010] [09:38:32] <mato>   sustrik: it seems to me the only problem is PUB, actually
| [Sunday 08 August 2010] [09:39:20] <mato>   sustrik: can we talk about this face to face when you finish your step 0 ?
| [Sunday 08 August 2010] [09:39:27] <sustrik>    sure
| [Sunday 08 August 2010] [09:39:46] <mato>   sustrik: good. maybe this evening?
| [Sunday 08 August 2010] [09:40:03] <sustrik>    step 0 is a lot of work
| [Sunday 08 August 2010] [09:40:09] <sustrik>    will be working till night i suppose
| [Sunday 08 August 2010] [09:40:16] <mato>   sustrik: well, whenever you want
| [Sunday 08 August 2010] [09:40:37] <mato>   sustrik: so this step 0 is mandatory to make everything else work?
| [Sunday 08 August 2010] [09:41:06] <sustrik>    it's mandatory to wait for first connection
| [Sunday 08 August 2010] [09:41:18] <mato>   right, makes sense, and we need that in any case
| [Sunday 08 August 2010] [09:41:33] <sustrik>    connecter object cannot be terminated while it's session is still alive wanting to send data
| [Sunday 08 August 2010] [09:41:47] <mato>   right
| [Sunday 08 August 2010] [09:42:09] <mato>   sustrik: ok well, i'll leave you to it. am happy to discuss when you have time.
| [Sunday 08 August 2010] [09:42:20] <sustrik>    ok
| [Sunday 08 August 2010] [09:42:22] <mato>   sustrik: i don't think there's anything else i can do on the core side right now
| [Sunday 08 August 2010] [09:42:29] <sustrik>    hm
| [Sunday 08 August 2010] [09:42:33] <mato>   sustrik: no point testing until things are at least half-working, no?
| [Sunday 08 August 2010] [09:42:44] <sustrik>    right
| [Sunday 08 August 2010] [09:42:45] <mato>   right now they're all on the floor
| [Sunday 08 August 2010] [09:43:26] <sustrik>    you are right, it's up to me right now
| [Sunday 08 August 2010] [09:43:31] <mato>   sustrik: what i don't understand is the current (pre-refactoring) codebase had to handle this already, no? (wait for a connection to show up)
| [Sunday 08 August 2010] [09:43:44] <mato>   sustrik: so why is it so complex all of a sudden? 
| [Sunday 08 August 2010] [09:43:57] <mato>   (naive question maybe, but worth asking just so i understand what's going on)
| [Sunday 08 August 2010] [09:44:04] <sustrik>    because back then when you called zmq_close it just terminated both session and connecter
| [Sunday 08 August 2010] [09:44:10] <sustrik>    easy
| [Sunday 08 August 2010] [09:44:13] <mato>   ah, ok
| [Sunday 08 August 2010] [09:44:28] <mato>   i get it
| [Sunday 08 August 2010] [09:44:31] <mato>   sustrik: ok, i'll leave you to it
| [Sunday 08 August 2010] [09:44:53] <mato>   sustrik: do call if you want a break or something, marathon coding is not a mandatory requirement :-)
| [Sunday 08 August 2010] [09:45:25] <sustrik>    i have to deliver the article to linux congress till 16th
| [Sunday 08 August 2010] [09:45:35] <sustrik>    so i'm in a hurry
| [Sunday 08 August 2010] [09:46:24]   * mato would like to help
| [Sunday 08 August 2010] [09:46:58] <mato>   being in a hurry while doing this sort of stuff is not a good sign
| [Sunday 08 August 2010] [09:47:25] <mato>   anyway, if there's some way i can help you, shout
| [Sunday 08 August 2010] [13:55:30] <dos000> can someone tell me if you can have zmq_poll while other sockets are happening ? is is mutually exclusive ?
| [Sunday 08 August 2010] [13:58:14] <travlr> you can use standard sockets in zmq_poll() along with zmq sockets. is that what you are asking? if not i don't understand the question.
| [Monday 09 August 2010] [11:02:20] <drbobbeaty> Question - maybe off-topic, but I thought I'd ask anyway... is the Java Driver for ZeroMQ - the one that's on github at 'zeromq/jzmq'... is it working with the latest ZeroMQ? I ask because I'm working with someone that's getting a simple server going, but the client is giving him a consistent error. Same error as using the Java code in the "cookbook" Java code.
| [Monday 09 August 2010] [11:02:34] <drbobbeaty> Just didn't know if there's something I should know about the Java client.
| [Monday 09 August 2010] [11:03:01] <drbobbeaty> ...like you have to be on a specific version of the JDK, or use a specific compiler for the JNI... that kind of stuff.
| [Monday 09 August 2010] [11:03:20] <drbobbeaty> (if it matters, this is all on linux)
| [Monday 09 August 2010] [11:03:35] <drbobbeaty> Thanks for any help anyone can provide.
| [Monday 09 August 2010] [11:06:30] <sustrik>    it should work, what's the error?
| [Monday 09 August 2010] [11:15:16] <drbobbeaty> hang on just a sec... I'll get it from him.
| [Monday 09 August 2010] [11:18:41] <drbobbeaty> OK... here it is...
| [Monday 09 August 2010] [11:18:50] <drbobbeaty> the output is:
| [Monday 09 August 2010] [11:18:56] <drbobbeaty> ENTERED Calling COnnect
| [Monday 09 August 2010] [11:19:01] <drbobbeaty> Calling Connect
| [Monday 09 August 2010] [11:19:10] <drbobbeaty> DONE Calling Connect 22
| [Monday 09 August 2010] [11:19:41] <drbobbeaty> Exception in thread "main" java.lang.Exception: 22 - 0x16 - Invalid argument
| [Monday 09 August 2010] [11:20:06] <drbobbeaty>     at org.zeromq.ZMQ$Socket.connect(Native Method)
| [Monday 09 August 2010] [11:20:25] <drbobbeaty>     at remote_lat.main
| [Monday 09 August 2010] [11:22:18] <drbobbeaty> The logging is his, but the exception is the problem. The code is the simple connection example off the Cookbook.
| [Monday 09 August 2010] [11:26:13] <drbobbeaty> I'm looking at the JNI code and seeing that it appears that the zmq_connect() is returning a 22 as opposed to a 0, and that's what's throwing the exception, but I'm at a loss to know what the 22 returned from zmq_connect() means.
| [Monday 09 August 2010] [11:26:38] <mato>   drbobbeaty: it's EINVAL, which you're seeing the strerror() of, "Invalid argument"
| [Monday 09 August 2010] [11:26:44] <mato>   drbobbeaty: which example, specifically?
| [Monday 09 August 2010] [11:27:52] <mato>   ah
| [Monday 09 August 2010] [11:28:01] <mato>   the cookbook is using non-pertable addressing
| [Monday 09 August 2010] [11:28:48] <drbobbeaty> Oh? OK... what needs to change? I believe he's using the Java pub/sub example
| [Monday 09 August 2010] [11:29:01] <mato>   i'll go edit the cookbook
| [Monday 09 August 2010] [11:29:10] <mato>   drbobbeaty: what platform is he on?
| [Monday 09 August 2010] [11:29:25] <drbobbeaty> My correection... he's using the "perf" directory in the Java codebase.
| [Monday 09 August 2010] [11:30:07] <mato>   drbobbeaty: no idea about that. but basically zmq is saying it can't resolve your connect or bind
| [Monday 09 August 2010] [11:30:40] <mato>   drbobbeaty: also, if he's on a machine disconnected from the net there's a bug in 2.0.7 that will just stop things from working 
| [Monday 09 August 2010] [11:31:24] <drbobbeaty> On CentOS5.1
| [Monday 09 August 2010] [11:31:34] <drbobbeaty> He's connected to the net.
| [Monday 09 August 2010] [11:32:14] <mato>   drbobbeaty: well, i can't see what doesn't work w/o his exact code, sorry. can't really help, the answer is EINVAL in zmq_connect() or zmq_bind() means it doesn't like the address you're passing for some reason
| [Monday 09 August 2010] [11:32:15] <drbobbeaty> I'm going to try to get things built on my box and help in the debugging... but if there's something I need to know about the cookbook example, or something with Java, please let me know. I've been using the C++ version for several weeks without a problem.
| [Monday 09 August 2010] [11:32:39] <drbobbeaty> OK, I'll dig and get a more concise problem statement - or a fix.
| [Monday 09 August 2010] [11:32:48] <mato>   nothing, what i said about being non-portable just means the examples won't work out of the box on systems other than Linux
| [Monday 09 August 2010] [11:32:53] <mato>   which i'll fix in the cookbook
| [Monday 09 August 2010] [11:33:03] <sustrik>    aren't you using PGM btw?
| [Monday 09 August 2010] [11:33:05] <mato>   for jzmq ask on the mailing list, i'm not the maintainer there
| [Monday 09 August 2010] [11:33:26] <sustrik>    if so, 0MQ has to be compiled with --with-pgm option
| [Monday 09 August 2010] [12:14:10] <drbobbeaty> mato, sustrik... thanks for the help and we figured it out. But it might be something that could be put in the Cookbook or docs to make it simpler for new comers. Basically, in using the local_lat and remote_lat the definition of the URL is different. In the local, you need to use a physical NIC to bind to, and in the remote you need to giv it an IP address.
| [Monday 09 August 2010] [12:14:49] <drbobbeaty> So... using the same URL of "tcp://eth0:5555" on both will get you an error on the remote_lat
| [Monday 09 August 2010] [12:14:57] <mato>   drbobbeaty: yeah, the perf tests really need more docs...
| [Monday 09 August 2010] [12:15:15] <drbobbeaty> So you need to use the "eth0" on the local and the machine name on the remote.
| [Monday 09 August 2010] [12:15:33] <drbobbeaty> Easy fix to our understanding, but kinda puzzling for a bit.
| [Monday 09 August 2010] [12:15:52] <mato>   yes, or use *:5555 on local, or numeric-ip:5555 on both
| [Monday 09 August 2010] [12:15:53] <drbobbeaty> Thanks for a great product... it's really been great so far. Just a little hiccup.
| [Monday 09 August 2010] [12:16:09] <drbobbeaty> True, good use of wildcards, mato.
| [Monday 09 August 2010] [12:16:25] <drbobbeaty> Thanks for the help. The "address" hint was really helpful.
| [Monday 09 August 2010] [12:17:17] <mato>   You're welcome.
| [Tuesday 10 August 2010] [03:00:28] <mikko> sustrik: there?
| [Tuesday 10 August 2010] [03:01:21] <sustrik>   mikko: hi
| [Tuesday 10 August 2010] [03:01:47] <mikko> i am having a presentation at company evening today
| [Tuesday 10 August 2010] [03:01:49] <mikko> suprisingly
| [Tuesday 10 August 2010] [03:02:02] <mikko> how would you put "Internet Scale Messaging" in one short sentence?
| [Tuesday 10 August 2010] [03:02:21] <sustrik>   i am having a problem with that one myself
| [Tuesday 10 August 2010] [03:02:38] <sustrik>   maybe "decentralised" rather than Internet-scale
| [Tuesday 10 August 2010] [03:03:00] <sustrik>   no central authority
| [Tuesday 10 August 2010] [03:03:12] <sustrik>   same way as IP or Web
| [Tuesday 10 August 2010] [03:03:13] <mikko> no guarantees on link speeds
| [Tuesday 10 August 2010] [03:03:14] <mikko> i guess
| [Tuesday 10 August 2010] [03:03:20] <mikko> unreliable networks
| [Tuesday 10 August 2010] [03:03:27] <sustrik>   no trust
| [Tuesday 10 August 2010] [03:03:42] <sustrik>   yes, that kind of things
| [Tuesday 10 August 2010] [03:04:15] <sustrik>   actually, comparison with ip/web can be an eye-opener imo
| [Tuesday 10 August 2010] [03:04:25] <sustrik>   people know how those work
| [Tuesday 10 August 2010] [03:04:48] <sustrik>   so "the same thing for distributed services"
| [Tuesday 10 August 2010] [03:07:41] <mikko> I think I can explain it to the audience
| [Tuesday 10 August 2010] [03:07:48] <mikko> luckily just a small audience
| [Tuesday 10 August 2010] [03:11:45] <sustrik>   well, good luck
| [Tuesday 10 August 2010] [03:12:19] <sustrik>   if there's any interesting feedback let us know
| [Tuesday 10 August 2010] [04:51:56] <pieter_hintjens>   mikko: perhaps something like "connecting nodes over an infinitely scalable, totally untrusted, and highly redundant network"
| [Tuesday 10 August 2010] [04:57:54] <aleator>   I need to make parallel requests for my worker nodes. Should I use XReq or device or something else entirely?
| [Tuesday 10 August 2010] [04:58:35] <pieterh>   parallel requests meaning the same requests sent to all workers, or requests distributed among workers?
| [Tuesday 10 August 2010] [04:59:13] <aleator>   different request for each worker, all at the same time
| [Tuesday 10 August 2010] [05:00:11] <guido_g>   you might want to use DOWNSTREAM/PUSH vs UPSTREAM/PULL sockets
| [Tuesday 10 August 2010] [05:00:19] <pieterh>   you could use the pipeline pattern, so ZMQ_DOWNSTREAM on client side, ZMQ_UPSTREAM on worker side, and then ZMQ_DOWNSTREAM from worker, back to ZMQ_UPSTREAM back on client
| [Tuesday 10 August 2010] [05:00:36] <pieterh>   DOWNSTREAM is now called PUSH and UPSTREAM is PULL btw
| [Tuesday 10 August 2010] [05:01:30] <pieterh>   you could also use a queue device, see figure 11 here: http://www.zeromq.org/docs:user-guide#toc14
| [Tuesday 10 August 2010] [05:01:46] <aleator>   Ok. So in essence I need to supply my own machinery for matching requests and replies with push/pull?
| [Tuesday 10 August 2010] [05:02:03] <pieterh>   aleator: yes, if you use push/pull you need to do the matching yourself
| [Tuesday 10 August 2010] [05:02:24] <pieterh>   if you use req-xrep-xreq-rep then it's done for you
| [Tuesday 10 August 2010] [05:03:15] <aleator>   I had originally just xreq/xrep and it seems to randomly utilise only some workers.
| [Tuesday 10 August 2010] [05:03:23] <aleator>   (I'm rather new at this)
| [Tuesday 10 August 2010] [05:03:24] <pieterh>   but the request-reply chain is hard to use if you try to start with xreq
| [Tuesday 10 August 2010] [05:04:00] <pieterh>   how many clients do you have?
| [Tuesday 10 August 2010] [05:04:26] <aleator>   In range 10-160, depending.
| [Tuesday 10 August 2010] [05:04:38] <aleator>   Tasks take few minutes each
| [Tuesday 10 August 2010] [05:05:24] <pieterh>   and each client sends one request at a time?
| [Tuesday 10 August 2010] [05:06:00] <aleator>   Ah. sorry, my bad. I meant workers. For clients there is at this point just one.
| [Tuesday 10 August 2010] [05:06:19] <pieterh>   so the client sends out jobs in parallel?
| [Tuesday 10 August 2010] [05:06:35] <aleator>   Thats my goal.
| [Tuesday 10 August 2010] [05:06:53] <pieterh>   then i'd suggest push/pull, and match the results up
| [Tuesday 10 August 2010] [05:07:03] <pieterh>   you can connect a pipeline in loops
| [Tuesday 10 August 2010] [05:07:09] <aleator>   Thank you.
| [Tuesday 10 August 2010] [05:07:12] <pieterh>   i don't have diagrams for that in the user guide yet, sorry
| [Tuesday 10 August 2010] [05:07:40] <aleator>   I just thought to ask since this seems rather basic operation that might have had support already.
| [Tuesday 10 August 2010] [05:08:24] <aleator>   But it is not difficult to do by hand either.
| [Tuesday 10 August 2010] [05:08:42] <pieterh>   you can do it by using the request-reply pattern as drawn in the diagram BUT then
| [Tuesday 10 August 2010] [05:08:56] <pieterh>   you need to use an XREQ socket at the client side and manually construct the frames
| [Tuesday 10 August 2010] [05:09:11] <pieterh>   since that is not documented, it's kind of hard to do
| [Tuesday 10 August 2010] [05:10:29] <aleator>   I did something like that with the result that just few workers got anything to do. Are there known pitfalls with this that I've might have stumbled upon?
| [Tuesday 10 August 2010] [05:11:30] <guido_g>   pieterh: is there a piece of code or a document that shows how req -> xrep is done?
| [Tuesday 10 August 2010] [05:11:34] <aleator>   Anyways, thank you for your help!
| [Tuesday 10 August 2010] [05:12:27] <pieterh>   guido_g: not in detail yet. The way I'm explaining XREP and XREQ in the user guide (basic section) is that they "extend" the request-reply pattern over intermediaries
| [Tuesday 10 August 2010] [05:12:54] <pieterh>   so you connect req-rep, or req-xrep-(code)-xreq-rep
| [Tuesday 10 August 2010] [05:13:23] <pieterh>   that is sufficient to use them in devices and stuff like multithreaded servers
| [Tuesday 10 August 2010] [05:13:55] <pieterh>   it's not sufficiently documented to do other stuff like aleator wants to do, e.g. client sending requests in parallel
| [Tuesday 10 August 2010] [05:14:17] <pieterh>   you can read the 0MQ code, people do, and it is helpful
| [Tuesday 10 August 2010] [05:14:20] <guido_g>   what is see is the (common?) pattern of simple clients -- using req -- connecting to a dispatcher (using x*)
| [Tuesday 10 August 2010] [05:14:26] <guido_g>   ok
| [Tuesday 10 August 2010] [05:15:14] <pieterh>   yes, that's probably the most common use case for X*
| [Tuesday 10 August 2010] [05:15:50] <pieterh>   mato: can i commit a man page change to git or will that provoke panic again?
| [Tuesday 10 August 2010] [05:15:53] <guido_g>   built something like that saturday morning while re-learning c++
| [Tuesday 10 August 2010] [05:16:21] <guido_g>   MQ is great for this kind of stuff
| [Tuesday 10 August 2010] [05:22:31] <aleator>   pieterh: Anyhow, I think my problem is so common that it might make good addition to zmg or tutorial of.
| [Tuesday 10 August 2010] [05:23:01] <pieterh>   aleator: i think so, yes.  it's just a matter of documenting the request-reply chain fully
| [Tuesday 10 August 2010] [05:23:09] <pieterh>   i'll get to that in the user guide
| [Tuesday 10 August 2010] [05:23:29] <pieterh>   it's going to be huge...
| [Tuesday 10 August 2010] [05:26:13] <aleator>   Hope you do :)
| [Tuesday 10 August 2010] [06:15:25] <mato>  pieterh: if you want, the man pages won't conflict with anything
| [Tuesday 10 August 2010] [06:15:29] <mato>  pieterh: what change, by the way?
| [Tuesday 10 August 2010] [06:16:00] <pieterh>   promote use of "*" in binding, reduce emphasis on non-portable interface names
| [Tuesday 10 August 2010] [06:16:11] <pieterh>   it's a small change to zmq_tcp(7)
| [Tuesday 10 August 2010] [06:16:19] <mato>  pieterh: can i review that please? thanks?
| [Tuesday 10 August 2010] [06:16:24] <pieterh>   sure
| [Tuesday 10 August 2010] [06:18:12] <pieterh>   sent to list
| [Tuesday 10 August 2010] [06:18:32] <pieterh>   in the user guide i'm treating non-portable interfaces as 'advanced'
| [Tuesday 10 August 2010] [06:18:41] <mato>  that's fine
| [Tuesday 10 August 2010] [06:18:49] <mato>  now that there is actually a user guide
| [Tuesday 10 August 2010] [06:19:21] <pieterh>   further, it's more useful IMO to describe "*" in terms of positive outcome ("binds to all available interfaces") rather than negative semantics ("does not specify interface")
| [Tuesday 10 August 2010] [06:19:42] <pieterh>   "does not make coffee"... the list of negatives is long
| [Tuesday 10 August 2010] [06:19:58] <mato>  hmm, i will complain first about your mail client, as usual :-)
| [Tuesday 10 August 2010] [06:20:17] <pieterh>   after you convince github to fix the issue tracker, i've got Google's address for you too...
| [Tuesday 10 August 2010] [06:20:28] <pieterh>   i'm sure they would like the feedback on gmale
| [Tuesday 10 August 2010] [06:20:39] <pieterh>   freudian slip?
| [Tuesday 10 August 2010] [06:20:41] <pieterh>   gmail
| [Tuesday 10 August 2010] [06:20:55] <pieterh>   :-)
| [Tuesday 10 August 2010] [06:20:56] <mato>  pieterh: ah, gmail
| [Tuesday 10 August 2010] [06:21:48] <mato>  pieterh: suggestion...
| [Tuesday 10 August 2010] [06:21:53] <pieterh>   ja?
| [Tuesday 10 August 2010] [06:22:29] <mato>  pieterh: either include the patch inline in email, or call it something.diff.txt (gmail is stupid)
| [Tuesday 10 August 2010] [06:22:32] <mato>  all i see is:
| [Tuesday 10 August 2010] [06:22:37] <mato>  [-- Attachment #2: zmq_tcp.txt.diff --]
| [Tuesday 10 August 2010] [06:22:38] <mato>  [-- Type: application/octet-stream, Encoding: base64, Size: 3.0K --]
| [Tuesday 10 August 2010] [06:22:38] <mato>  [-- application/octet-stream is unsupported (use 'v' to view this part) --]
| [Tuesday 10 August 2010] [06:23:07] <pieterh>   ah, it takes two (email clients) to get confusion over attachments
| [Tuesday 10 August 2010] [06:23:18] <pieterh>   why don't you just upgrade to gmail like everyone else? :-)
| [Tuesday 10 August 2010] [06:23:20] <pieterh>   i'll resend it
| [Tuesday 10 August 2010] [06:23:23] <mato>  no need
| [Tuesday 10 August 2010] [06:23:32] <mato>  pieterh: i can view the attachment, that's not a problem
| [Tuesday 10 August 2010] [06:23:35] <mato>  just a suggestion
| [Tuesday 10 August 2010] [06:23:40] <mato>  that's all
| [Tuesday 10 August 2010] [06:23:49] <pieterh>   usually i just commit directly to master
| [Tuesday 10 August 2010] [06:24:06] <pieterh>   and allow CIA19 to announce the good news
| [Tuesday 10 August 2010] [06:31:29]      * mato is wondering if it would be a good idea to have Mailman bounce messages with non-text attachments to the list
| [Tuesday 10 August 2010] [06:32:44] <sjampoo>   No! The zeromq is my primary source for my fix of L0lcatZ
| [Tuesday 10 August 2010] [06:33:00] <sjampoo>   s/zeromq/0mq list
| [Tuesday 10 August 2010] [06:33:01] <mato>  :-)
| [Tuesday 10 August 2010] [06:34:14] <mato>  ok, attachments with application/octet-stream which is useless anyway
| [Tuesday 10 August 2010] [06:34:24] <mato>  or we can make an exception for image/x-lolcat :-)
| [Tuesday 10 August 2010] [06:34:35] <sjampoo>   heh :)
| [Tuesday 10 August 2010] [06:40:55] <CIA-20>    zeromq2: 03Pieter Hintjens 07master * rb6cdd36 10/ (12 files in 2 dirs): 
| [Tuesday 10 August 2010] [06:40:55] <CIA-20>    zeromq2: Added error checking (EFAULT) for null arguments
| [Tuesday 10 August 2010] [06:40:55] <CIA-20>    zeromq2: * Fixed zmq_term, zmq_socket, zmq_close, zmq_setsockopt,
| [Tuesday 10 August 2010] [06:40:55] <CIA-20>    zeromq2: * zmq_getsockopt, zmq_bind, zmq_connect, zmq_send,
| [Tuesday 10 August 2010] [06:40:55] <CIA-20>    zeromq2: * zmq_recv, zmq_poll, zmq_device, zmq_stopwatch_stop
| [Tuesday 10 August 2010] [06:40:56] <CIA-20>    zeromq2: * Updated Reference Manual for these methods - http://bit.ly/a3QF1N
| [Tuesday 10 August 2010] [06:40:57] <CIA-20>    zeromq2: 03Pieter Hintjens 07master * ra12f446 10/ doc/zmq_tcp.txt : Modified zmq_tcp(7) to emphasize wildcard interfaces - http://bit.ly/cWYMOK
| [Tuesday 10 August 2010] [06:45:02] <mato>  pieterh: not meaning to argue, but you trolled there a bit
| [Tuesday 10 August 2010] [06:45:22] <mato>  pieterh: there really is nothing stopping you from organising your repo branches any way you want...
| [Tuesday 10 August 2010] [06:45:30] <mato>  pieterh: that's part of the power of Git AFAICS
| [Tuesday 10 August 2010] [06:46:11] <mato>  pieterh: e.g. you can have an 'unstable' branch that pushes into zeromq2 'master', you can have local topic branches, and so on.
| [Tuesday 10 August 2010] [06:49:21] <pieterh>   mato: its only a part troll
| [Tuesday 10 August 2010] [06:49:30] <mato>  :)
| [Tuesday 10 August 2010] [06:49:37] <pieterh>   you said it yourself, we follow documented procedures
| [Tuesday 10 August 2010] [06:49:46] <pieterh>   few of us are git gurus
| [Tuesday 10 August 2010] [06:49:57] <mato>  yes, but those are being hashed out right now, and that will take some time
| [Tuesday 10 August 2010] [06:50:01] <pieterh>   i don't want to have to organize my branches any way I want
| [Tuesday 10 August 2010] [06:50:11] <pieterh>   i want to follow some clear procedure that stops me making mistakes
| [Tuesday 10 August 2010] [06:50:19] <pieterh>   if i have to invent it, i'll get it wrong
| [Tuesday 10 August 2010] [06:50:50] <pieterh>   thus, and i assume you work like that too, you avoid using stuff you are likely to get wrong
| [Tuesday 10 August 2010] [06:51:20] <mato>  yes, of course
| [Tuesday 10 August 2010] [06:51:27] <pieterh>   which was the point of my email
| [Tuesday 10 August 2010] [06:51:33] <mato>  but there's nothing wrong with experimenting with a procedure in your local git
| [Tuesday 10 August 2010] [06:51:42] <pieterh>   i do not want to experiment
| [Tuesday 10 August 2010] [06:51:46] <pieterh>   i have "real work" to do
| [Tuesday 10 August 2010] [06:51:53] <mato>  and then saying, hey guys, i have this all working nicely in my git, here's how it works
| [Tuesday 10 August 2010] [06:52:11] <pieterh>   no, because someone (you) will come along with a huge argument about why it's NFG
| [Tuesday 10 August 2010] [06:52:20] <pieterh>   i did in fact do that, and wrote it down, and that happened
| [Tuesday 10 August 2010] [06:52:29] <mato>  sigh
| [Tuesday 10 August 2010] [06:53:51] <pieterh>   i just point out that discarding rather than improving / fixing is kind of wasteful
| [Tuesday 10 August 2010] [06:54:02] <pieterh>   and certainly discouraging
| [Tuesday 10 August 2010] [06:54:06] <mato>  i saw several things with your proposed procedure that did things "differently" from what i percieve as the best practice being used by people out there
| [Tuesday 10 August 2010] [06:54:12] <pieterh>   it is a wiki
| [Tuesday 10 August 2010] [06:54:16] <pieterh>   edit / change / save
| [Tuesday 10 August 2010] [06:54:40] <mato>  if i edit/change/save without explaning why, that doesn't help, does it?
| [Tuesday 10 August 2010] [06:54:46] <pieterh>   simply pointing to another document and saying "i like that better" is not helpful
| [Tuesday 10 August 2010] [06:54:52] <pieterh>   yes, it helps
| [Tuesday 10 August 2010] [06:55:01] <pieterh>   you make the changes you feel necessary, then you explain why
| [Tuesday 10 August 2010] [06:55:12] <pieterh>   if someone else feels strongly, they take the effort to make more changes
| [Tuesday 10 August 2010] [06:55:13] <pieterh>   etc.
| [Tuesday 10 August 2010] [06:55:24] <pieterh>   it's a good process
| [Tuesday 10 August 2010] [06:56:06] <mato>  pieterh: note that i was not the only person who immediately pointed out that "unstable" was "different from everyone else" in your proposal
| [Tuesday 10 August 2010] [06:56:12] <mato>  anyhow
| [Tuesday 10 August 2010] [06:56:47] <pieterh>   it seems incredibly minor: you edit one sentence and that's it
| [Tuesday 10 August 2010] [06:57:45] <pieterh>   what i really needed was input on the git aspects themselves
| [Tuesday 10 August 2010] [06:57:46] <mato>  i can't think about this right now, and no, it is not just a question of naming, it's also a question of how commits flow between branches which you are completely ignoring out of i presume ignorance
| [Tuesday 10 August 2010] [06:57:53] <pieterh>   indeed
| [Tuesday 10 August 2010] [06:58:05] <pieterh>   that is the part which matters
| [Tuesday 10 August 2010] [06:58:06] <mato>  and i would like to write that down, but that needs time
| [Tuesday 10 August 2010] [06:58:28] <pieterh>   actually i did describe how commits flow between branches
| [Tuesday 10 August 2010] [06:58:40] <pieterh>   at least one way of doing it
| [Tuesday 10 August 2010] [06:59:01] <pieterh>   but that's the part which needs expert input
| [Tuesday 10 August 2010] [06:59:18]      * mato is getting stressed because he feels pressure to "get a Git process working"
| [Tuesday 10 August 2010] [06:59:27] <pieterh>   not... sigh... whether work branches are called "issue" or "topic" fgs
| [Tuesday 10 August 2010] [06:59:38] <pieterh>   well
| [Tuesday 10 August 2010] [06:59:44] <mato>  pieterh: would you like me to drop everything and spend today working out the Git process?
| [Tuesday 10 August 2010] [06:59:48] <mato>  pieterh: yes?
| [Tuesday 10 August 2010] [06:59:51] <pieterh>   mato: no
| [Tuesday 10 August 2010] [07:00:00] <mato>  then let's just leave the damn thing alone for a while
| [Tuesday 10 August 2010] [07:00:01] <pieterh>   i'd like to thrash it out high bandwidth next week
| [Tuesday 10 August 2010] [07:00:01] <mato>  ok?
| [Tuesday 10 August 2010] [07:00:05] <pieterh>   ano ano
| [Tuesday 10 August 2010] [07:00:19] <pieterh>   in any case we need sustrik to mindmeld on the process
| [Tuesday 10 August 2010] [07:00:42] <mato>  so, topic "Git" is closed for now
| [Tuesday 10 August 2010] [07:05:52] <sustrik>   i would say let's adopt the linux kernel process
| [Tuesday 10 August 2010] [07:06:00]      * sustrik is willing to learn a stable process
| [Tuesday 10 August 2010] [07:06:21]      * sustrik doesn't want to learn something that keeps changing every week
| [Tuesday 10 August 2010] [09:56:18] <pieterh>   sustrik: random question... PUB drops messages if it hits HWM.  Does it drop oldest or newest messages?
| [Tuesday 10 August 2010] [09:56:50] <sustrik>   newest
| [Tuesday 10 August 2010] [09:57:52] <pieterh>   is that deliberate policy? (usually for pubsub you'd drop oldest messages)
| [Tuesday 10 August 2010] [09:58:23] <sustrik>   the reason is that what you are working with are basically pipes
| [Tuesday 10 August 2010] [09:58:36] <sustrik>   pipe can be a network connection, inter-thread connection
| [Tuesday 10 August 2010] [09:58:39] <sustrik>   a HW device
| [Tuesday 10 August 2010] [09:58:42] <sustrik>   whatever
| [Tuesday 10 August 2010] [09:58:52] <sustrik>   if you want to drop oldest message
| [Tuesday 10 August 2010] [09:59:19] <sustrik>   the publisher end of the pipe has to notify the receiver end of the pipe to drop a message
| [Tuesday 10 August 2010] [09:59:31] <sustrik>   the question is how to pass the notification
| [Tuesday 10 August 2010] [09:59:37] <sustrik>   so you have to have another pipe
| [Tuesday 10 August 2010] [09:59:46] <sustrik>   what if that one gets full
| [Tuesday 10 August 2010] [09:59:47] <sustrik>   etc.
| [Tuesday 10 August 2010] [09:59:50] <pieterh>   the HWM is not known to the receiver end
| [Tuesday 10 August 2010] [09:59:52] <pieterh>   right
| [Wednesday 11 August 2010] [05:19:42] <mato>    sustrik: quick C++ best practice question
| [Wednesday 11 August 2010] [05:20:17] <mato>    sustrik: exceptions in constructors are fine, no? it's just exceptions in destructors that should be avoided
| [Wednesday 11 August 2010] [05:25:59] <sustrik> mato: kind of
| [Wednesday 11 August 2010] [05:26:11] <sustrik> but it's complex
| [Wednesday 11 August 2010] [05:26:24] <sustrik> better to not throw exceptions from constructors
| [Wednesday 11 August 2010] [05:26:59] <mato>    hmm
| [Wednesday 11 August 2010] [05:27:40] <mato>    then I would need an extra "start" method that does anything interesting, which seems superfluous
| [Wednesday 11 August 2010] [05:27:57] <sustrik> you can have an exception in constructor
| [Wednesday 11 August 2010] [05:28:23] <sustrik> but then you should be aware that stack unwind can start with half-constructed object
| [Wednesday 11 August 2010] [05:28:41] <sustrik> it you don't do anything strange, it's mostly ok
| [Wednesday 11 August 2010] [05:29:10] <sustrik> if there are virtual functions involved it become a bit more tricky
| [Wednesday 11 August 2010] [05:29:12] <sustrik> etc.
| [Wednesday 11 August 2010] [05:29:13] <mato>    ok, i'll try the naive way... not doing anything too strange i think
| [Wednesday 11 August 2010] [05:29:19] <mato>    no virtual functions
| [Wednesday 11 August 2010] [05:29:22] <mato>    no inheritance
| [Wednesday 11 August 2010] [05:29:25] <mato>    no nothing
| [Wednesday 11 August 2010] [05:29:29] <sustrik> then it's ok
| [Wednesday 11 August 2010] [05:29:32] <mato>    thanks
| [Wednesday 11 August 2010] [07:44:58] <Zao> Exceptions in ctors are handy to indicate that the invariant of the class cannot be ensured.
| [Wednesday 11 August 2010] [07:45:14] <Zao> It sure beats leaving zombie objects that fail to do things on first use.
| [Wednesday 11 August 2010] [08:04:35] <sustrik> yup, but can get messy once you start getting 'pure virtual function called' errors etc.
| [Wednesday 11 August 2010] [08:09:03] <Zao> I can't quite see how any such behaviour would arise, unless you've built something incorrectly.
| [Wednesday 11 August 2010] [08:10:20] <CIA-20>  zeromq2: 03Martin Sustrik 07wip-shutdown * r45bac29 10/ (51 files): I/O object hierarchy implemented - http://bit.ly/cpsGJy
| [Wednesday 11 August 2010] [08:10:24] <Zao> As with everything else, know the rules and pray that your implementation is not broken :D
| [Wednesday 11 August 2010] [08:15:26] <sustrik> mato: you there?
| [Wednesday 11 August 2010] [08:28:10] <mato>    sustrik: kind of
| [Wednesday 11 August 2010] [08:28:29] <sustrik> how do i push my commit to the branch?
| [Wednesday 11 August 2010] [08:30:39] <mato>    sustrik: ?
| [Wednesday 11 August 2010] [08:30:45] <mato>    sustrik: AFAICS you already did
| [Wednesday 11 August 2010] [08:30:52] <mato>    sustrik: at least CIA-20 said so :-)
| [Wednesday 11 August 2010] [08:31:22] <sustrik> a-ha
| [Wednesday 11 August 2010] [08:31:31] <mato>    sustrik: git push origin on that branch should do the trick if your branches are configured normally
| [Wednesday 11 August 2010] [08:31:38] <sustrik> git complained so i though it was unsuccessgul
| [Wednesday 11 August 2010] [08:31:47] <pieterh> sustrik: here is how you merge one branch into master
| [Wednesday 11 August 2010] [08:31:48] <pieterh> #   Switch to the issue branch
| [Wednesday 11 August 2010] [08:31:49] <pieterh> git checkout -b 123_nice_feature
| [Wednesday 11 August 2010] [08:31:49] <pieterh> #   Switch to the master branch and get latest version
| [Wednesday 11 August 2010] [08:31:49] <pieterh> git checkout master
| [Wednesday 11 August 2010] [08:31:49] <pieterh> git pull
| [Wednesday 11 August 2010] [08:31:49] <pieterh> #   Merge the issue branch into the current (master) branch
| [Wednesday 11 August 2010] [08:31:49] <pieterh> git merge 123_nice_feature
| [Wednesday 11 August 2010] [08:31:50] <pieterh> #   Push new master back to repository
| [Wednesday 11 August 2010] [08:31:50] <pieterh> git push origin master
| [Wednesday 11 August 2010] [08:31:53] <mato>    sustrik: what did it complain about?
| [Wednesday 11 August 2010] [08:32:02] <sustrik> random stuff
| [Wednesday 11 August 2010] [08:32:05] <sustrik> let me see
| [Wednesday 11 August 2010] [08:32:30] <mato>    sustrik: it probably said something like "you didn't tell me that i should push to this remote branch by default, but i'll do it anyway"
| [Wednesday 11 August 2010] [08:32:53] <pieterh> you used "git push" without arguments?
| [Wednesday 11 August 2010] [08:33:43] <mato>    pieterh: he's trying to push to a remote branch from a local branch which may or may not have been configured as a tracking branch
| [Wednesday 11 August 2010] [08:34:16] <pieterh> hmm
| [Wednesday 11 August 2010] [08:34:17] <sustrik> failed to push some refs to ...
| [Wednesday 11 August 2010] [08:34:27] <mato>    pieterh: he is also not trying trying to do anything like the $random_procedure you just pasted :-)
| [Wednesday 11 August 2010] [08:34:36] <sustrik> to preven from losing history
| [Wednesday 11 August 2010] [08:34:51] <pieterh> mato: sure
| [Wednesday 11 August 2010] [08:34:52] <sustrik> non-fast-forward updates were rejected
| [Wednesday 11 August 2010] [08:35:16] <sustrik> merge the remote changes before pushing again
| [Wednesday 11 August 2010] [08:35:20] <mato>    sustrik: ah
| [Wednesday 11 August 2010] [08:35:35] <mato>    sustrik: yeah, that's normal... remember i committed changes to that branch
| [Wednesday 11 August 2010] [08:35:42] <mato>    sustrik: do a git pull origin
| [Wednesday 11 August 2010] [08:35:47] <sustrik> i did
| [Wednesday 11 August 2010] [08:35:56] <mato>    so, what's the problem?
| [Wednesday 11 August 2010] [08:36:01] <sustrik> same error
| [Wednesday 11 August 2010] [08:36:22] <mato>    sustrik: when doing what?
| [Wednesday 11 August 2010] [08:36:28] <mato>    sustrik: what exact command ... ?
| [Wednesday 11 August 2010] [08:36:32] <sustrik> git push origin
| [Wednesday 11 August 2010] [08:36:51] <mato>    huh? and "git pull origin" did nothing?
| [Wednesday 11 August 2010] [08:37:33] <sustrik> it completed without error
| [Wednesday 11 August 2010] [08:37:39] <sustrik> following push failed again
| [Wednesday 11 August 2010] [08:37:46] <sustrik> with the same error
| [Wednesday 11 August 2010] [08:37:57] <mato>    ok, can you paste the entire error please? not re-type it?
| [Wednesday 11 August 2010] [08:38:11] <sustrik> it's on the notebook
| [Wednesday 11 August 2010] [08:38:21] <sustrik> let me send it to you
| [Wednesday 11 August 2010] [08:38:49] <mato>    sustrik: pastebin.com or similar is your friend
| [Wednesday 11 August 2010] [08:39:01] <pieterh> mato: $random_procedure is simply a way of resolving merge issues locally
| [Wednesday 11 August 2010] [08:39:11] <mato>    pieterh: he is trying to do something else
| [Wednesday 11 August 2010] [08:40:02] <sustrik> done
| [Wednesday 11 August 2010] [08:40:23] <pieterh> mato: ack
| [Wednesday 11 August 2010] [08:41:13] <mato>    sustrik: oh, interesting, it seems to be complaining about something on your local 'master' branch
| [Wednesday 11 August 2010] [08:41:17] <mato>    sustrik: irrelevant
| [Wednesday 11 August 2010] [08:41:34] <mato>    sustrik: if you do "git push origin wip-shutdown" it should not complain
| [Wednesday 11 August 2010] [08:41:48] <sustrik> ok
| [Wednesday 11 August 2010] [08:41:54] <mato>    sustrik: same goes for pull
| [Wednesday 11 August 2010] [08:42:05] <mato>    sustrik: you can always tell it to push/pull only a specific branch
| [Wednesday 11 August 2010] [08:42:24] <sustrik> ack
| [Wednesday 11 August 2010] [08:42:39] <mato>    sustrik: it's possible we left your local 'master' on that machine in some weird state, shouldn't matter
| [Wednesday 11 August 2010] [08:43:10] <mato>    sustrik: at least not until you want to do something with 'master' 
| [Wednesday 11 August 2010] [08:43:15] <mato>    sustrik: which you don't right now
| [Wednesday 11 August 2010] [08:43:22] <sustrik> ok
| [Wednesday 11 August 2010] [09:08:38] <sustrik> mato: how come git fetch doesn't result in me seeing the wip branch?
| [Wednesday 11 August 2010] [09:10:10] <sustrik> gh
| [Wednesday 11 August 2010] [09:10:12] <sustrik> aargh
| [Wednesday 11 August 2010] [09:10:19] <mato>    sustrik: ?
| [Wednesday 11 August 2010] [09:10:23] <mato>    sustrik: who's "me"?
| [Wednesday 11 August 2010] [09:10:29] <sustrik> martin sustrik
| [Wednesday 11 August 2010] [09:10:45] <mato>    sustrik: you're trying to pull the branch on another machine?
| [Wednesday 11 August 2010] [09:10:50] <sustrik> yes
| [Wednesday 11 August 2010] [09:11:10] <sustrik> ghhh
| [Wednesday 11 August 2010] [09:11:11] <mato>    sustrik: /me never quite understood how fetch works
| [Wednesday 11 August 2010] [09:11:19] <sustrik> so far i'm here:
| [Wednesday 11 August 2010] [09:11:20] <sustrik> * (no branch)
| [Wednesday 11 August 2010] [09:11:20] <sustrik>   master
| [Wednesday 11 August 2010] [09:11:32] <mato>    go back to master
| [Wednesday 11 August 2010] [09:11:34] <sustrik> what should i do to clone the branch?
| [Wednesday 11 August 2010] [09:12:00] <mato>    sustrik: what does "git branch -av" say?
| [Wednesday 11 August 2010] [09:12:13] <sustrik> * (no branch)                 45bac29 I/O object hierarchy implemented
| [Wednesday 11 August 2010] [09:12:13] <sustrik>   master                      a12f446 Modified zmq_tcp(7) to emphasize wildcard interfaces
| [Wednesday 11 August 2010] [09:12:13] <sustrik>   remotes/origin/HEAD         -> origin/master
| [Wednesday 11 August 2010] [09:12:13] <sustrik>   remotes/origin/master       a12f446 Modified zmq_tcp(7) to emphasize wildcard interfaces
| [Wednesday 11 August 2010] [09:12:13] <sustrik>   remotes/origin/wip-shutdown 45bac29 I/O object hierarchy implemented
| [Wednesday 11 August 2010] [09:12:42] <mato>    huh?
| [Wednesday 11 August 2010] [09:12:45] <sustrik> just tell me how to get to the source code
| [Wednesday 11 August 2010] [09:12:52] <sustrik> from the scratch
| [Wednesday 11 August 2010] [09:13:00] <sustrik> rm -rf zeromq2
| [Wednesday 11 August 2010] [09:13:04] <sustrik> now what?
| [Wednesday 11 August 2010] [09:13:19] <mato>    nothing, if it's from scratch just clone and then do "git checkout wip-output"
| [Wednesday 11 August 2010] [09:13:23] <mato>    that should work
| [Wednesday 11 August 2010] [09:14:00] <mato>    it's when it's not from scratch that you have to sometimes do something funny and i can never remember what
| [Wednesday 11 August 2010] [09:14:43] <sustrik> sustrik@istvan:~/zeromq2$ git checkout wip-shutdown
| [Wednesday 11 August 2010] [09:14:44] <sustrik> error: pathspec 'wip-shutdown' did not match any file(s) known to git.
| [Wednesday 11 August 2010] [09:15:57] <mato>    sustrik: give me a sec
| [Wednesday 11 August 2010] [09:17:06] <mato>    sustrik: i don't understand
| [Wednesday 11 August 2010] [09:17:18] <mato>    [dezo:tmp]$ mkdir zzz
| [Wednesday 11 August 2010] [09:17:18] <mato>    [dezo:tmp]$ cd zzz
| [Wednesday 11 August 2010] [09:17:18] <mato>    [dezo:zzz]$ git clone git@github.com:zeromq/zeromq2.git
| [Wednesday 11 August 2010] [09:17:20] <mato>    ...
| [Wednesday 11 August 2010] [09:17:30] <mato>    [dezo:zzz]$ cd zeromq2/
| [Wednesday 11 August 2010] [09:17:30] <mato>    [dezo:zeromq2]$ git branch -av
| [Wednesday 11 August 2010] [09:17:30] <mato>    * master                      a12f446 Modified zmq_tcp(7) to emphasize wildcard interfaces remotes/origin/HEAD         -> origin/master remotes/origin/master       a12f446 Modified zmq_tcp(7) to emphasize wildcard interfaces remotes/origin/wip-shutdown 45bac29 I/O object hierarchy implemented
| [Wednesday 11 August 2010] [09:17:35] <mato>    [dezo:zeromq2]$ git checkout wip-shutdown
| [Wednesday 11 August 2010] [09:17:38] <mato>    Branch wip-shutdown set up to track remote branch wip-shutdown from origin.
| [Wednesday 11 August 2010] [09:17:39] <mato>    [dezo:zeromq2]$ git branch master
| [Wednesday 11 August 2010] [09:17:41] <mato>    Switched to a new branch 'wip-shutdown'
| [Wednesday 11 August 2010] [09:17:44] <mato>    * wip-shutdown
| [Wednesday 11 August 2010] [09:17:47] <mato>    sustrik: you are doing something different?
| [Wednesday 11 August 2010] [09:18:16] <sustrik> sustrik@istvan:~$ git clone git@github.com:zeromq/zeromq2.git
| [Wednesday 11 August 2010] [09:18:17] <sustrik> Initialized empty Git repository in /home/sustrik/zeromq2/.git/
| [Wednesday 11 August 2010] [09:18:17] <sustrik> remote: Counting objects: 5764, done.
| [Wednesday 11 August 2010] [09:18:17] <sustrik> remote: Compressing objects: 100% (1489/1489), done.
| [Wednesday 11 August 2010] [09:18:17] <sustrik> remote: Total 5764 (delta 4169), reused 5654 (delta 4083)
| [Wednesday 11 August 2010] [09:18:23] <sustrik> sustrik@istvan:~$ cd zeromq2/
| [Wednesday 11 August 2010] [09:18:25] <sustrik> sustrik@istvan:~/zeromq2$ 
| [Wednesday 11 August 2010] [09:18:27] <sustrik> sustrik@istvan:~/zeromq2$ 
| [Wednesday 11 August 2010] [09:18:29] <sustrik> sustrik@istvan:~/zeromq2$ git checkout wip-shutdown
| [Wednesday 11 August 2010] [09:18:31] <sustrik> error: pathspec 'wip-shutdown' did not match any file(s) known to git.
| [Wednesday 11 August 2010] [09:19:19] <mato>    ?!?!
| [Wednesday 11 August 2010] [09:19:41] <sustrik> !
| [Wednesday 11 August 2010] [09:19:53] <sustrik> 8oO
| [Wednesday 11 August 2010] [09:20:27] <sustrik> http://www2.ivcc.edu/rambo/eng1001/munch.htm
| [Wednesday 11 August 2010] [09:20:41] <mato>    sustrik: try "git checkout -b wip-shutdown origin/wip-shutdown" instead
| [Wednesday 11 August 2010] [09:21:17] <sustrik> ok, this one works
| [Wednesday 11 August 2010] [09:21:35] <mato>    seems like that is the canonical way
| [Wednesday 11 August 2010] [09:21:50] <mato>    no idea why my 'git' is being smart and just doing the right thing :)
| [Wednesday 11 August 2010] [09:22:19] <sustrik> ok, never mind
| [Wednesday 11 August 2010] [09:35:16] <mato>    arrrrgh
| [Wednesday 11 August 2010] [09:36:40] <mato>    why is it that there are 1001 ways to do anything in C++, of which only ways 1,17,354,771 and 997 actually work !?
| [Wednesday 11 August 2010] [09:37:11] <mato>    of course and of those only the subset of (17, 771) is any good :-)
| [Wednesday 11 August 2010] [09:38:23] <pieterh> mato: the only person who understands 354 is the guy who wrote that part of the template
| [Wednesday 11 August 2010] [09:39:32] <drbobbeaty>  I can here knowing I'd get good help on ZeroMQ, but this is great comic relief. I feel your pain, mato... but it still makes me giggle.
| [Wednesday 11 August 2010] [09:39:38] <pieterh> I think this carries on in the tradition of Algol-68, but it only had 15 ways of doing anything due to bitsize limitations
| [Wednesday 11 August 2010] [09:42:08] <mato>    :-)
| [Wednesday 11 August 2010] [09:43:21] <pieterh> luckily the grand tradition of "just how complex can we make this before people realize we're trolling them" of language construction is dying out...
| [Wednesday 11 August 2010] [09:43:37] <pieterh> it is nice to use 0MQ in Python :-)
| [Wednesday 11 August 2010] [09:43:45] <mato>    yes yes
| [Wednesday 11 August 2010] [09:52:19] <CIA-20>  jzmq: 03Gonzalo Diethelm 07master * r21d7a43 10/ (src/Socket.cpp src/org/zeromq/ZMQ.java): 
| [Wednesday 11 August 2010] [09:52:20] <CIA-20>  jzmq: Added specific methods for each of the sockopt cases.
| [Wednesday 11 August 2010] [09:52:20] <CIA-20>  jzmq: Added support for all missing sockopt cases.
| [Wednesday 11 August 2010] [09:52:20] <CIA-20>  jzmq: Added support for getting all sockopt cases. - http://bit.ly/akWvk8
| [Wednesday 11 August 2010] [10:22:07] <pieterh> mato: quick question
| [Wednesday 11 August 2010] [10:22:39] <pieterh> Gonzalo points out that the get/setsockopt man pages seem to be using the wrong int64 type for some options
| [Wednesday 11 August 2010] [10:22:56] <pieterh> shall i fix those pages or is this deliberate?
| [Wednesday 11 August 2010] [10:28:07] <mato>    pieterh: not deliberate, problematic, old bug, requires mucking with most/all the language bindings
| [Wednesday 11 August 2010] [10:28:31] <mato>    pieterh: don't attempt to fix it
| [Wednesday 11 August 2010] [10:28:56] <sustrik> pieterh: socket option types are a mess
| [Wednesday 11 August 2010] [10:29:08] <mato>    pieterh: if it annoys you, define all the proper types, put out an announcement and solicit replies from as many (ideally all) language binding maintainers that those are ok for them
| [Wednesday 11 August 2010] [10:29:11] <pieterh> i won't but could you explain why the man pages specify the wrong sign for most cases?
| [Wednesday 11 August 2010] [10:29:20] <pieterh> i don't intend to change the code but document it accurately
| [Wednesday 11 August 2010] [10:29:34] <mato>    pieterh: ah, just the man pages?
| [Wednesday 11 August 2010] [10:29:36] <pieterh> yes
| [Wednesday 11 August 2010] [10:29:46] <mato>    pieterh: there was chaos for a while
| [Wednesday 11 August 2010] [10:30:06] <mato>    pieterh: the man pages probably try to be "correct", the code is not really "correct"
| [Wednesday 11 August 2010] [10:30:18] <mato>    pieterh: so yeah, just update the man pages to match the code
| [Wednesday 11 August 2010] [10:30:29] <mato>    pieterh: but in any case, it's a mess...
| [Wednesday 11 August 2010] [10:30:47] <mato>    pieterh: bunch of the options should just be e.g. "int"
| [Wednesday 11 August 2010] [10:30:58] <pieterh> i don't think anyone minds what types are actually used
| [Wednesday 11 August 2010] [10:30:59] <mato>    pieterh: impossible to fix w/o going thru a massive procedure as i wrote above
| [Wednesday 11 August 2010] [10:31:01] <pieterh> perhaps for bindings
| [Wednesday 11 August 2010] [10:31:16] <pieterh> i'll fix the docs then, thanks
| [Wednesday 11 August 2010] [10:31:28] <pieterh> also i assume getsockopt will fetch ZMQ_SWAP?
| [Wednesday 11 August 2010] [10:31:42] <mato>    hmm, yes, it should, read the code 
| [Wednesday 11 August 2010] [10:31:43] <pieterh> options.cpp does that
| [Wednesday 11 August 2010] [10:31:48] <pieterh> ok, i'll add that as well
| [Wednesday 11 August 2010] [10:31:51] <pieterh> thx, over and out
| [Wednesday 11 August 2010] [11:00:38] <CIA-20>  zeromq2: 03Pieter Hintjens 07master * re74d350 10/ (doc/zmq_getsockopt.txt doc/zmq_setsockopt.txt): Fixed (un)signed type errors in get/setsockopt manual - http://bit.ly/cX70vO
| [Wednesday 11 August 2010] [11:07:37] <CIA-20>  zeromq2: 03Martin Sustrik 07wip-shutdown * r6e9744f 10/ (6 files): engine termination on disconnect fixed - http://bit.ly/cDpnTx
| [Wednesday 11 August 2010] [11:08:15] <CIA-20>  zeromq2: 03Pieter Hintjens 0746_device_robustness * r5be54b9 10/ src/xrep.cpp : 
| [Wednesday 11 August 2010] [11:08:15] <CIA-20>  zeromq2: 46 - Devices vulnerable to invalid messages
| [Wednesday 11 August 2010] [11:08:15] <CIA-20>  zeromq2: http://github.com/zeromq/zeromq2/issues#issue/46
| [Wednesday 11 August 2010] [11:08:15] <CIA-20>  zeromq2: Invalid messages are now discarded silently, instead of causing an assertion
| [Wednesday 11 August 2010] [11:08:15] <CIA-20>  zeromq2: failure. - http://bit.ly/c8H1WC
| [Wednesday 11 August 2010] [11:10:19] <pieterh> mato: you asked for review of all code changes
| [Wednesday 11 August 2010] [11:10:40] <mato>    pieterh: yes...
| [Wednesday 11 August 2010] [11:10:58] <pieterh> it's a two-line change, no hurry though, I'm waiting for confirmation from Benjamin that it works
| [Wednesday 11 August 2010] [11:11:41] <mato>    pieterh: thx for putting it on a branch
| [Wednesday 11 August 2010] [11:11:42] <pieterh> does pushing topic branches to the repository work as a way of publishing proposed changes?
| [Wednesday 11 August 2010] [11:11:58] <pieterh> i would delete the branch once issue is closed
| [Wednesday 11 August 2010] [11:11:59] <mato>    pieterh: it does for you since you have commit access
| [Wednesday 11 August 2010] [11:12:19] <pieterh> yes, for any committer
| [Wednesday 11 August 2010] [11:12:49] <mato>    yes, more or less
| [Wednesday 11 August 2010] [11:13:12] <pieterh> ok, cause i don't want to create chaos in the git
| [Wednesday 11 August 2010] [11:13:23] <mato>    pieterh: although given that sustrik has not yet been taught to work with branches, you're probably better off just emailing patches...
| [Wednesday 11 August 2010] [11:13:53] <mato>    pieterh: note that emailing patches has the added advantage of anyone on the list being able to review your code...
| [Wednesday 11 August 2010] [11:14:05] <pieterh> mato: i already emailed the patch to the list this morning
| [Wednesday 11 August 2010] [11:14:12] <mato>    pieterh: so... ?
| [Wednesday 11 August 2010] [11:14:39] <pieterh> so i need closure on my own workflow, can't leave random branches lying around
| [Wednesday 11 August 2010] [11:14:47] <pieterh> working in too many places, on too many boxes
| [Wednesday 11 August 2010] [11:15:09] <pieterh> and would like to use branches, in any case
| [Wednesday 11 August 2010] [11:15:13] <mato>    pieterh: sure
| [Wednesday 11 August 2010] [11:15:19] <pieterh> ok, great
| [Wednesday 11 August 2010] [11:15:24] <mato>    pieterh: of course, the canonical way to do this is to create your own fork of zeromq
| [Wednesday 11 August 2010] [11:15:31] <mato>    pieterh: push to that, etc etc
| [Wednesday 11 August 2010] [11:15:49] <pieterh> yes, of course but then it becomes complex for anyone wanting to try work in progress
| [Wednesday 11 August 2010] [11:15:54] <pieterh> this way it's all in the single place
| [Wednesday 11 August 2010] [11:16:08] <mato>    hey, it's a distributed system
| [Wednesday 11 August 2010] [11:16:09] <mato>    :)
| [Wednesday 11 August 2010] [11:16:15] <mato>    the point is there is no "single place", really
| [Wednesday 11 August 2010] [11:16:27] <mato>    anyway, i don't care either way right now
| [Wednesday 11 August 2010] [11:16:29] <pieterh> i know, mato... recall it was me who proposed we used git for 0mq in the first place
| [Wednesday 11 August 2010] [11:16:31] <pieterh> :-)
| [Wednesday 11 August 2010] [11:16:37] <mato>    so?
| [Wednesday 11 August 2010] [11:16:49] <pieterh> it's only about reducing complexity
| [Wednesday 11 August 2010] [11:17:07] <mato>    yes, sure
| [Wednesday 11 August 2010] [11:17:26] <mato>    but you had to announce the work to the mailing list anyway
| [Wednesday 11 August 2010] [11:17:29] <mato>    (the patch)
| [Wednesday 11 August 2010] [11:17:35] <pieterh> yes but...
| [Wednesday 11 August 2010] [11:17:45] <pieterh> that ends up using the mailing list as database
| [Wednesday 11 August 2010] [11:17:54] <mato>    :-)
| [Wednesday 11 August 2010] [11:17:55] <pieterh> we know that is suboptimal
| [Wednesday 11 August 2010] [11:18:05] <pieterh> "where is patch for change XYZ?"
| [Wednesday 11 August 2010] [11:18:25] <mato>    sure, whatever, i have no opinion right now
| [Wednesday 11 August 2010] [11:18:54]    * pieterh always a spare bag of opinions, slightly used
| [Wednesday 11 August 2010] [11:19:06] <mato>    yes :)
| [Wednesday 11 August 2010] [11:19:15] <pieterh> the more the merrier, i say!
| [Wednesday 11 August 2010] [11:19:27] <mato>    i found it very refreshing to see a "i don't know" reply from you today or last night :-)
| [Wednesday 11 August 2010] [11:19:32] <mato>    much appreciated !
| [Wednesday 11 August 2010] [11:19:55] <pieterh> sincerity is easy, once you learn how to fake it
| [Wednesday 11 August 2010] [11:20:17] <mato>    anyhow, gotta go to dinner
| [Wednesday 11 August 2010] [11:20:24] <mato>    cyl
| [Wednesday 11 August 2010] [11:20:27] <pieterh> cyl mato
| [Wednesday 11 August 2010] [11:20:56] <guido_g> hi all
| [Wednesday 11 August 2010] [11:21:48] <pieterh> hi guido_g!
| [Wednesday 11 August 2010] [11:22:25] <guido_g> the zmq_deviced mentioned in THE GUIDE (tm), where does it come from?
| [Wednesday 11 August 2010] [11:22:44] <pieterh> guido_g: its a work in progress
| [Wednesday 11 August 2010] [11:22:51] <guido_g> ahhh ok
| [Wednesday 11 August 2010] [11:22:56] <pieterh> i should mention that in the user guide
| [Wednesday 11 August 2010] [11:23:12] <pieterh> my intention was to finished the device daemon earlier but it got sidetracked
| [Wednesday 11 August 2010] [11:23:23] <pieterh> there is a man page describing how it will work, on master
| [Wednesday 11 August 2010] [11:23:37] <guido_g> ok
| [Wednesday 11 August 2010] [11:23:47] <pieterh> it's a mix of Jon Dyte's zmqd and the existing devices
| [Wednesday 11 August 2010] [11:24:06] <pieterh> but i figured it would be more useful in C, for people who want to reuse the code for their own devices
| [Wednesday 11 August 2010] [11:24:20] <pieterh> also i am still 21 years away from learning C++... :-)
| [Wednesday 11 August 2010] [11:24:24] <guido_g> that's clear, i was just confused becaue of the missing program
| [Wednesday 11 August 2010] [11:24:46] <pieterh> i'll add a note to the User Guide, confusion is not good ...
| [Wednesday 11 August 2010] [11:25:49] <mato>    pieterh: see, the zmq_deviced you're writing should (even if in progress) be sitting on a nice branch somewhere, whether in your private repo or on zeromq2 is moot right now...
| [Wednesday 11 August 2010] [11:25:58] <mato>    pieterh: anyhow, me is really gone ...
| [Wednesday 11 August 2010] [11:26:07] <pieterh> mato: yes, yes, with an issue etc. will do, thanks
| [Wednesday 11 August 2010] [11:26:25] <mato>    pieterh: with the manpage too, which should not be on master :-)
| [Wednesday 11 August 2010] [11:26:30] <mato>    pieterh: just being pedantic ...
| [Wednesday 11 August 2010] [11:26:34] <pieterh> ur right
| [Wednesday 11 August 2010] [11:26:41] <pieterh> pedantic is perfect
| [Wednesday 11 August 2010] [11:27:07] <pieterh> this new process will be really helpful
| [Wednesday 11 August 2010] [11:27:46] <guido_g> obviously my first idea that tools like git should make things easier is wrong ,)
| [Wednesday 11 August 2010] [11:39:22] <guido_g> hmm... the REP/REP typo seems to have survived the changes...
| [Wednesday 11 August 2010] [11:40:11] <guido_g> http://www.zeromq.org/docs:user-guide is current, isn't it?
| [Wednesday 11 August 2010] [11:41:48] <pieterh> guido_g: no, it's not current
| [Wednesday 11 August 2010] [11:42:34] <pieterh> tools like git and issue trackers are more work superficially
| [Wednesday 11 August 2010] [11:43:24] <pieterh> i'll post an update later today but i'm writing offline
| [Wednesday 11 August 2010] [11:43:54] <guido_g> no problem
| [Wednesday 11 August 2010] [11:44:36] <travlr>  hi pieter. maybe issue tracker should be for convenience rather than hard protocol.
| [Wednesday 11 August 2010] [11:45:08] <pieterh> travlr: for sure... it's always an effort/benefit tradeoff
| [Wednesday 11 August 2010] [11:45:30] <pieterh> using an issue tracker systematically makes it much easier for others to know what's going on and participate
| [Wednesday 11 August 2010] [11:47:19] <pieterh> i think there is empirical evidence that projects that don't use issue trackers systematically are less successful
| [Wednesday 11 August 2010] [11:47:32] <pieterh> but since we're a community of volunteers, it's always optional
| [Wednesday 11 August 2010] [11:48:13] <travlr>  yup, this is all true too. I think the (pragmatic) protocol you all decide upon will evently resolve itself upon experimentation.
| [Wednesday 11 August 2010] [11:48:33] <guido_g> pieterh: and there is postgresql :)
| [Wednesday 11 August 2010] [11:48:44] <guido_g> no issue tracker and such
| [Wednesday 11 August 2010] [11:48:55] <pieterh> unfortunately if i have strong opinions on this it's because experience tells me people do not always like the inconvenience of making life easier for others
| [Wednesday 11 August 2010] [11:49:19] <pieterh> this goes from how we write code, how we communicate what we're working on, to how we document our processes
| [Wednesday 11 August 2010] [11:49:26] <pieterh> its always extra effort upfront
| [Wednesday 11 August 2010] [11:49:34] <guido_g> right
| [Wednesday 11 August 2010] [11:49:39] <travlr>  pieterh: i could not agree more
| [Wednesday 11 August 2010] [11:49:59] <guido_g> most code-workers don't think in these categories (/me included)
| [Wednesday 11 August 2010] [11:50:14] <pieterh> most programmers (including me) focus on the results
| [Wednesday 11 August 2010] [11:50:24] <pieterh> and they need others to remind them of due process
| [Wednesday 11 August 2010] [11:50:36] <guido_g> *sigh* how true
| [Wednesday 11 August 2010] [11:50:57] <travlr>  being a self taught cs guy.. i always think in terms of the guy trying to pick up the torch ;)
| [Wednesday 11 August 2010] [11:50:59] <pieterh> i don't think this will emerge organically, it does need deliberate work
| [Wednesday 11 August 2010] [11:51:09] <pieterh> no-one likes other peoples' processes
| [Wednesday 11 August 2010] [11:51:51] <pieterh> anyhow, next week i'll work through this with Martin and Mato and we'll come to a clear and simple way of working
| [Wednesday 11 August 2010] [11:52:00] <travlr>  +1
| [Wednesday 11 August 2010] [11:52:02] <pieterh> i hope that will make it easier for everyone who tracks the project
| [Wednesday 11 August 2010] [11:52:43] <pieterh> travlr: yes, documenting the torch is key
| [Wednesday 11 August 2010] [11:53:19] <travlr>  yes the torch..lol.
| [Wednesday 11 August 2010] [11:59:48] <sustrik> mikko: are you there?
| [Wednesday 11 August 2010] [12:01:08] <sustrik> btw: i am not sure that adding stuff that you would like to do into issue tracker is a good idea
| [Wednesday 11 August 2010] [12:01:20] <sustrik> i've done that in the past
| [Wednesday 11 August 2010] [12:01:38] <sustrik> and the tracker just become polluted with old and abandoned projects
| [Wednesday 11 August 2010] [12:01:48] <pieterh> sustrik: more for work in progress rather than ideas
| [Wednesday 11 August 2010] [12:02:13] <pieterh> you're right that issue trackers rapidly get polluted otherwise
| [Wednesday 11 August 2010] [12:02:26] <sustrik> work in progress is the same thing
| [Wednesday 11 August 2010] [12:02:36] <mikko>   sustrik: ye
| [Wednesday 11 August 2010] [12:02:48] <sustrik> if everyone starts putting his work in progress into bug tracker we'll get a mess
| [Wednesday 11 August 2010] [12:03:07] <sustrik> working on something doesn't necessarily mean it'll get merged in
| [Wednesday 11 August 2010] [12:03:15] <sustrik> mikko: how was the talk?
| [Wednesday 11 August 2010] [12:03:28] <guido_g> isn't that the reason behind categories for tracker entries?
| [Wednesday 11 August 2010] [12:03:28] <pieterh> sustrik: i don't disagree but then we need somewhere for people to publish their wips
| [Wednesday 11 August 2010] [12:03:41] <mikko>   sustrik: http://twitter.com/harrieverveer/status/20818282466
| [Wednesday 11 August 2010] [12:03:41] <travlr>  re: issue tracker entries could be qualified into categories like "bug | feature request | todo | fixed"
| [Wednesday 11 August 2010] [12:03:45] <pieterh> if i want to publish a branch to the git, i need a issue number
| [Wednesday 11 August 2010] [12:04:01] <mikko>   sustrik: i think that summarises it well
| [Wednesday 11 August 2010] [12:04:11] <sustrik> :)
| [Wednesday 11 August 2010] [12:04:13] <guido_g> so you *need* an issue for a feature?
| [Wednesday 11 August 2010] [12:04:13] <pieterh> if i want my code reviewed, i need to publish to the git (principle of least surprise)
| [Wednesday 11 August 2010] [12:04:14] <sustrik> what's BS?
| [Wednesday 11 August 2010] [12:04:18] <mikko>   sustrik: bullshit
| [Wednesday 11 August 2010] [12:04:25] <pieterh> lol
| [Wednesday 11 August 2010] [12:04:51] <sustrik> great, looks it was successful
| [Wednesday 11 August 2010] [12:04:57] <sustrik> you are in finland?
| [Wednesday 11 August 2010] [12:05:02] <pieterh> mikko: did you use slides?
| [Wednesday 11 August 2010] [12:05:44] <mikko>   sustrik: nope, i am from finland
| [Wednesday 11 August 2010] [12:05:50] <sustrik> guido_g: i would say no
| [Wednesday 11 August 2010] [12:05:53] <mikko>   sustrik: living in london and visiting netherlands at the moment
| [Wednesday 11 August 2010] [12:05:58] <mikko>   pieterh: yeah
| [Wednesday 11 August 2010] [12:06:02] <mikko>   pieterh: not very good slides
| [Wednesday 11 August 2010] [12:06:16] <sustrik> implementing a feature is your private matter
| [Wednesday 11 August 2010] [12:06:20] <mikko>   pieterh: did them in the plane on the way here. im gonna do a few iterations on them at some point
| [Wednesday 11 August 2010] [12:06:29] <sustrik> pushing it to the trunk is a different thing
| [Wednesday 11 August 2010] [12:06:48] <pieterh> i'd be interested in how people responded, what they understood, did not, etc.
| [Wednesday 11 August 2010] [12:07:31] <pieterh> sustrik: there is probably a balance between not announcing any wip, and trying to record all of it
| [Wednesday 11 August 2010] [12:07:53] <guido_g> sustrik: that's what i was goiung for, if something needs to be commited to the official repo, it has to have an issue attached
| [Wednesday 11 August 2010] [12:08:01] <pieterh> and for instance the wip you have now, has no issue, no tracked discussion
| [Wednesday 11 August 2010] [12:08:14] <pieterh> right?
| [Wednesday 11 August 2010] [12:08:15] <sustrik> should it?
| [Wednesday 11 August 2010] [12:08:20] <sustrik> it's my wip
| [Wednesday 11 August 2010] [12:08:33] <pieterh> so... :-)
| [Wednesday 11 August 2010] [12:08:38] <pieterh> why is it in the main git?
| [Wednesday 11 August 2010] [12:08:39] <sustrik> once i'm going to push it to the trunk
| [Wednesday 11 August 2010] [12:08:45] <sustrik> that's the time for the discussion
| [Wednesday 11 August 2010] [12:08:56] <pieterh> the point of upfront issues is to have discussion upfront as well
| [Wednesday 11 August 2010] [12:08:57] <sustrik> because mato put it there
| [Wednesday 11 August 2010] [12:09:11] <sustrik> i was developing on my repo originally
| [Wednesday 11 August 2010] [12:09:15] <pieterh> yes, because that's where people expect it... :-)
| [Wednesday 11 August 2010] [12:09:22] <pieterh> principle of least surprise
| [Wednesday 11 August 2010] [12:09:45] <sustrik> i still don't see why anyone should be interested in my wip
| [Wednesday 11 August 2010] [12:09:52] <sustrik> i mean while it is not ready
| [Wednesday 11 August 2010] [12:09:54] <pieterh> look... 
| [Wednesday 11 August 2010] [12:09:59] <pieterh> it is a big bugfix
| [Wednesday 11 August 2010] [12:10:30] <sustrik> nope, it's a change of semantics
| [Wednesday 11 August 2010] [12:10:42] <pieterh> that's a point of view
| [Wednesday 11 August 2010] [12:10:53] <pieterh> it fixes the bug that messages are dropped if you exit too early
| [Wednesday 11 August 2010] [12:11:03] <sustrik> that's a documented feature afaik
| [Wednesday 11 August 2010] [12:11:21] <pieterh> you're kind of justifying working outside of any formal process
| [Wednesday 11 August 2010] [12:11:27] <pieterh> which i have no issue with
| [Wednesday 11 August 2010] [12:11:37] <sustrik> the process beging once you share
| [Wednesday 11 August 2010] [12:11:39] <pieterh> but it makes it harder for others to participate
| [Wednesday 11 August 2010] [12:11:48] <pieterh> yes
| [Wednesday 11 August 2010] [12:11:52] <pieterh> the process begins once you share
| [Wednesday 11 August 2010] [12:12:05] <sustrik> rightr
| [Wednesday 11 August 2010] [12:12:08] <pieterh> which is why sharing analysis of the problem starts the process
| [Wednesday 11 August 2010] [12:12:35] <pieterh> the earlier you share, the better it works, empirically
| [Wednesday 11 August 2010] [12:12:43] <pieterh> i think that's it
| [Wednesday 11 August 2010] [12:13:10] <sustrik> so you propose to have feature discussions in issue tracker
| [Wednesday 11 August 2010] [12:13:16] <sustrik> rather than mailing list
| [Wednesday 11 August 2010] [12:13:16] <pieterh> yes, or somewhere
| [Wednesday 11 August 2010] [12:13:25] <pieterh> IMO the mailing list and IRC are excellent for some aspects
| [Wednesday 11 August 2010] [12:13:33] <pieterh> and the issue tracker is too limited for real discussions
| [Wednesday 11 August 2010] [12:13:53] <pieterh> ... 
| [Wednesday 11 August 2010] [12:13:54] <sustrik> yes, and feature discussion in transient in its nature
| [Wednesday 11 August 2010] [12:14:00] <pieterh> yes
| [Wednesday 11 August 2010] [12:14:10] <pieterh> but not so transient it always gets lost
| [Wednesday 11 August 2010] [12:14:19] <sustrik> so mailing list seems the best option
| [Wednesday 11 August 2010] [12:14:20] <pieterh> email is information, not knowledge
| [Wednesday 11 August 2010] [12:14:25] <pieterh> there's a substantive difference
| [Wednesday 11 August 2010] [12:14:38] <pieterh> "find all discussion on the problem with devices crashing if you send them bad messages"
| [Wednesday 11 August 2010] [12:14:46] <pieterh> -> issue 46
| [Wednesday 11 August 2010] [12:14:53] <sustrik> yes, that's a bug
| [Wednesday 11 August 2010] [12:15:00] <pieterh> not my point, sorry
| [Wednesday 11 August 2010] [12:15:24] <sustrik> i am rather speaking of "random chat on how to implement ipv6 support"
| [Wednesday 11 August 2010] [12:15:27] <pieterh> finding knowledge on an issue (bug, misfeature, improvement, api) is crucial to solving it accurately
| [Wednesday 11 August 2010] [12:15:32] <pieterh> exactly
| [Wednesday 11 August 2010] [12:15:38] <pieterh> where is the ipv6 discussion page?
| [Wednesday 11 August 2010] [12:15:42] <pieterh> i was looking for it the other day
| [Wednesday 11 August 2010] [12:15:43] <sustrik> no
| [Wednesday 11 August 2010] [12:15:52] <pieterh> i could not find it
| [Wednesday 11 August 2010] [12:15:56] <pieterh> therefore i did not participate
| [Wednesday 11 August 2010] [12:16:15] <sustrik> search mail archives for the random chat on ipv6
| [Wednesday 11 August 2010] [12:16:19] <pieterh> i'm not going to spend 2 hours searching old mail discussions
| [Wednesday 11 August 2010] [12:16:33] <pieterh> a waste of my time, i have real work to do, as mato likes to say
| [Wednesday 11 August 2010] [12:16:40] <pieterh> this is the problem
| [Wednesday 11 August 2010] [12:16:45] <sustrik> unless there's a code backing the discussion it is almost by definition random and transient
| [Wednesday 11 August 2010] [12:17:06] <sustrik> no point in storing it at a wiki page or so
| [Wednesday 11 August 2010] [12:17:10] <pieterh> why are you against recording knowledge in a predictable way?
| [Wednesday 11 August 2010] [12:17:22] <sustrik> it's not a knowledge
| [Wednesday 11 August 2010] [12:17:28] <sustrik> it's people ranting about features
| [Wednesday 11 August 2010] [12:17:32] <pieterh> "why 0MQ does not support IPv6" is knowledge
| [Wednesday 11 August 2010] [12:17:37] <sustrik> sure
| [Wednesday 11 August 2010] [12:17:37] <pieterh> i know it is
| [Wednesday 11 August 2010] [12:17:40] <sustrik> FAQ?
| [Wednesday 11 August 2010] [12:17:58]    * pieterh does not enjoy this discussion, sorry
| [Wednesday 11 August 2010] [12:18:13] <sustrik> ok, it's kind of pointless
| [Wednesday 11 August 2010] [12:18:27] <sustrik> back to coding!
| [Wednesday 11 August 2010] [12:19:39] <travlr>  why not, as a reference see what tried and true projects are doing for these workflows... like the linux kernel for instance
| [Wednesday 11 August 2010] [12:20:51] <sustrik> travlr +1
| [Wednesday 11 August 2010] [12:24:17] <dos000_> travlr, what do they do ?
| [Wednesday 11 August 2010] [12:26:58] <travlr>  dos000_: can't say specifically, but there are plenty of examples of growing/successful large project workflows out there.
| [Wednesday 11 August 2010] [12:27:56] <pieterh> linux kernel tracker only tracks bugs
| [Wednesday 11 August 2010] [12:28:10] <pieterh> other links projects track bugs, feature requests, patches, e.g. http://sourceforge.net/tracker/?group_id=429
| [Wednesday 11 August 2010] [12:28:16] <travlr>  i would also mention something like KDE but they are only transitioning to git now
| [Wednesday 11 August 2010] [12:28:46] <pieterh> i think sustrik is right that the git issue tracker should hold bugs only
| [Wednesday 11 August 2010] [12:28:58] <travlr>  and feature requests?
| [Wednesday 11 August 2010] [12:29:07] <pieterh> but i also think we need a place to discuss feature requests
| [Wednesday 11 August 2010] [12:29:10] <dos000_> pieterh, my point is what do people use beside forums,maillist tocatch these random bits of info
| [Wednesday 11 August 2010] [12:29:13] <pieterh> that is not the email list
| [Wednesday 11 August 2010] [12:29:36] <sustrik> i was just trying to say that 90% of feature discussion will be trash anyway
| [Wednesday 11 August 2010] [12:29:48] <pieterh> sustrik: 90% of all discussion is trash :-)
| [Wednesday 11 August 2010] [12:29:50] <pieterh> sturgeon's law
| [Wednesday 11 August 2010] [12:30:05] <dos000_> is this irc logged to begin with ?
| [Wednesday 11 August 2010] [12:30:13] <travlr>  if someone in the community has a feature request, it should be recorded in the tracker... imo
| [Wednesday 11 August 2010] [12:30:20] <pieterh> dos000_: probably
| [Wednesday 11 August 2010] [12:30:27] <dos000_> i find a lot of info just glancing over here from other people questions
| [Wednesday 11 August 2010] [12:30:28] <sustrik> note zmqircd participant
| [Wednesday 11 August 2010] [12:30:35] <sustrik> someone is spying on us
| [Wednesday 11 August 2010] [12:30:37] <pieterh> travlr: at the least, just to answer "no, because"
| [Wednesday 11 August 2010] [12:30:37] <sustrik> hm
| [Wednesday 11 August 2010] [12:30:45] <sustrik> not even speaking of CIA-20
| [Wednesday 11 August 2010] [12:31:14] <sustrik> in short, there's a log somewhere
| [Wednesday 11 August 2010] [12:31:24] <pieterh> i'm willing to put up and manage a secondary tracker for feature discussion
| [Wednesday 11 August 2010] [12:31:32] <pieterh> experimentally then
| [Wednesday 11 August 2010] [12:31:40] <dos000_> but going to the mailing list is against the "least resistance path" unless i have a specific issue in my head to solve
| [Wednesday 11 August 2010] [12:31:43] <pieterh> that will ensure the main issue tracker remains focussed
| [Wednesday 11 August 2010] [12:31:59] <pieterh> dos000_: what would seem least surprising to you?
| [Wednesday 11 August 2010] [12:32:03] <sustrik> you can try
| [Wednesday 11 August 2010] [12:32:16] <sustrik> i just expect the feature tracker would look like this:
| [Wednesday 11 August 2010] [12:32:31] <sustrik> "John Smith believes the IPv6 feature is not needed"
| [Wednesday 11 August 2010] [12:32:51] <sustrik> "mato thinks that there should be new IPv6 transports (tcp6:// etc.)"
| [Wednesday 11 August 2010] [12:32:59] <sustrik> "mato have changed his mind"
| [Wednesday 11 August 2010] [12:33:03] <pieterh> yes, this is the kind of discussion you'd expect
| [Wednesday 11 August 2010] [12:33:06] <pieterh> hmm
| [Wednesday 11 August 2010] [12:33:12] <pieterh> for example, the thread on reliability
| [Wednesday 11 August 2010] [12:33:18] <pieterh> that is a good example of a feature discussion
| [Wednesday 11 August 2010] [12:33:31] <pieterh> it's a really useful thread
| [Wednesday 11 August 2010] [12:33:42] <sustrik> what have you used it for?
| [Wednesday 11 August 2010] [12:33:49] <pieterh> to read people's use cases and experience
| [Wednesday 11 August 2010] [12:33:59] <travlr>  the issue could simply point to the discussion on the mail list
| [Wednesday 11 August 2010] [12:34:01] <sustrik> yes, use cases
| [Wednesday 11 August 2010] [12:34:05] <sustrik> that's useful
| [Wednesday 11 August 2010] [12:34:07] <pieterh> there is no mail list thread
| [Wednesday 11 August 2010] [12:34:14] <pieterh> at best, loads of URIs into the archives
| [Wednesday 11 August 2010] [12:34:18] <pieterh> ugh :-(
| [Wednesday 11 August 2010] [12:34:30] <pieterh> use cases, sample code, etc. etc.
| [Wednesday 11 August 2010] [12:35:15] <pieterh> look... what I'll do is start a section on the wiki for feature discussion
| [Wednesday 11 August 2010] [12:35:24] <pieterh> i'll move the reliability page there to seed it
| [Wednesday 11 August 2010] [12:35:25] <sustrik> sure, do so
| [Wednesday 11 August 2010] [12:35:34] <sustrik> we'll see how it works
| [Wednesday 11 August 2010] [12:35:38] <pieterh> sure
| [Wednesday 11 August 2010] [12:35:39] <travlr>  +1
| [Wednesday 11 August 2010] [12:35:44] <pieterh> email is great for transient stuff
| [Wednesday 11 August 2010] [12:35:52] <pieterh> but it is sand on the beach
| [Wednesday 11 August 2010] [12:35:56] <pieterh> come back tomorrow, it's all gone
| [Wednesday 11 August 2010] [12:36:05] <pieterh> ok
| [Wednesday 11 August 2010] [12:36:48] <pieterh> sustrik: what i'll also do is when people discuss features on the list, try to capture this as new discussion threads on the wiki
| [Wednesday 11 August 2010] [12:37:02] <dos000_> pieterh, what you mean ? i have not found a good medium to capture feature discussion . beside mailing lists. thats what i mean
| [Wednesday 11 August 2010] [12:37:14] <travlr>  pieterh: that makes sense to this mere and humble mortal
| [Wednesday 11 August 2010] [12:37:17] <sustrik> i have no real opinion
| [Wednesday 11 August 2010] [12:37:27] <pieterh> dos000_: look at http://www.zeromq.org/blog:requirements-for-reliability
| [Wednesday 11 August 2010] [12:37:57] <pieterh> forget my initial text, it's rubbish, but the discussion that follows is pure gold
| [Wednesday 11 August 2010] [12:37:57] <sustrik> the fact is that at some point someone arrives with an implementation of the feature
| [Wednesday 11 August 2010] [12:38:07] <dos000_> pieterh, nice
| [Wednesday 11 August 2010] [12:38:07] <sustrik> at that point we either merge it or not
| [Wednesday 11 August 2010] [12:38:10] <pieterh> sustrik: yes, that's always an option
| [Wednesday 11 August 2010] [12:38:37] <pieterh> and that certainly represents the mindset of those looking after the repository
| [Wednesday 11 August 2010] [12:38:45] <pieterh> changeset -> review -> merge
| [Wednesday 11 August 2010] [12:39:06] <sustrik> yes. but the feature discussion is kind of orphaned
| [Wednesday 11 August 2010] [12:39:13] <dos000_> pieterh, this is based on what ? is the site on full wiki ?
| [Wednesday 11 August 2010] [12:39:25] <pieterh> dos000_: the site is using wikidot.com
| [Wednesday 11 August 2010] [12:39:38] <travlr>  sustrik: you have a good point.. thinking also about long term maintainence
| [Wednesday 11 August 2010] [12:39:45] <travlr>  kiss
| [Wednesday 11 August 2010] [12:39:59] <travlr>  k.i.s.s
| [Wednesday 11 August 2010] [12:40:00] <pieterh> yes, it's orphaned, i agree
| [Wednesday 11 August 2010] [12:40:17] <sustrik> what i suspect is that we'll end up with feature discussion completely unrelated to actual code
| [Wednesday 11 August 2010] [12:40:38] <pieterh> sustrik: feature discussion should really focus on external aspects anyhow
| [Wednesday 11 August 2010] [12:40:45] <pieterh> such as use cases, and apis
| [Wednesday 11 August 2010] [12:40:55] <sustrik> right
| [Wednesday 11 August 2010] [12:41:12] <sustrik> use case should be captured
| [Wednesday 11 August 2010] [12:41:35] <pieterh> i like the notion that how that discussion works is orthogonal to how stuff gets into master
| [Wednesday 11 August 2010] [12:41:48] <dos000_> pieterh, the search actually works !
| [Wednesday 11 August 2010] [12:41:58] <pieterh> dos000_: yes :-)
| [Wednesday 11 August 2010] [12:42:08] <pieterh> it is actually a very powerful wiki engine
| [Wednesday 11 August 2010] [12:42:56] <travlr>  pieterh: how about a tag cloud too on the wiki
| [Wednesday 11 August 2010] [12:43:25] <pieterh> its possible but tag clouds tend to be pretty but useless
| [Wednesday 11 August 2010] [12:43:42] <pieterh> search and categorization work better, by experience
| [Wednesday 11 August 2010] [12:43:47] <travlr>  sure
| [Wednesday 11 August 2010] [12:44:27] <pieterh> if you want to learn about wikidot there is a very active community at http://community.wikidot.com
| [Wednesday 11 August 2010] [12:44:37] <pieterh> many template site types at http://irongiant.wikidot.com
| [Wednesday 11 August 2010] [12:44:43] <pieterh> here ends the commercial
| [Wednesday 11 August 2010] [12:44:57] <travlr>  the problem with wikidot info is the needed information is EVERYWHERE
| [Wednesday 11 August 2010] [12:45:14] <travlr>  can't find specific info easily
| [Wednesday 11 August 2010] [12:45:18] <pieterh> :-) http://doc.wikidot.com
| [Wednesday 11 August 2010] [12:45:24] <dos000_> pieterh, i will keep wikidot in my radar. we might need it inhouse
| [Wednesday 11 August 2010] [12:46:08] <pieterh> dos000_: disclaimer, i was running wikidot.com last year as we built it up, so I'm not neutral
| [Wednesday 11 August 2010] [12:46:44] <travlr>  pieterh: i think this is the first time i have seen this page
| [Wednesday 11 August 2010] [12:47:02] <travlr>  _all_ info needs to be gathered into one location
| [Wednesday 11 August 2010] [12:47:07] <dos000_> which template is 0mq using ?
| [Wednesday 11 August 2010] [12:47:28] <pieterh> dos000_: customisable CSS, see http://themes.wikidot.com
| [Wednesday 11 August 2010] [12:47:39] <pieterh> travlr: there is much too much information for one place
| [Wednesday 11 August 2010] [12:47:46] <travlr>  links then
| [Wednesday 11 August 2010] [12:47:53] <travlr>  something
| [Wednesday 11 August 2010] [12:48:04] <pieterh> http://dashboard.wikidot.com/helmuti-pdorf:_start
| [Wednesday 11 August 2010] [12:48:08] <travlr>  i have a hard time finding what i need
| [Wednesday 11 August 2010] [12:49:06] <pieterh> travlr: usually, just ask the community and they'll point you to it... it is a huge project with no accurate map
| [Wednesday 11 August 2010] [12:49:29] <travlr>  i would rather be able to find it myself
| [Wednesday 11 August 2010] [12:50:13] <pieterh> i did make an index, it is no longer published but: http://blog.wikidot.com/main:index
| [Wednesday 11 August 2010] [12:51:28] <travlr>  pieterh: with all do respect to the wikidot folks.. a better job needs to be done for access to this information
| [Wednesday 11 August 2010] [12:52:18] <pieterh> travlr: for sure... wikidot is messy, its a good example of what happens when things just grow organically
| [Wednesday 11 August 2010] [12:53:58] <pieterh> zeromq.org systematically tries to be a map of every available resource
| [Wednesday 11 August 2010] [12:54:37] <travlr>  pieterh: i agree and understand... but someone like me just does not have time to find all the ins and outs as wikidot appears to be a wonderful platform
| [Wednesday 11 August 2010] [12:55:31] <pieterh> travlr: mostly with wikidot, it kind of works because each time you get more sophisticated you discover a new set of resources for you
| [Wednesday 11 August 2010] [12:56:51] <travlr>  cool. i have to spend more time with it.. i just get frustrated with any project, that does not provide the answer to a question i may have, easily
| [Wednesday 11 August 2010] [12:57:12] <travlr>  any project... thats one of my pet peeves
| [Wednesday 11 August 2010] [12:57:13] <pieterh> there is a global search option, from the www.wikidot.com page
| [Wednesday 11 August 2010] [12:57:31] <travlr>  thats for all wikidot websites.. isn't it?
| [Wednesday 11 August 2010] [12:57:41] <travlr>  not how to use wikidot
| [Wednesday 11 August 2010] [12:57:45] <pieterh> all websites you can access
| [Wednesday 11 August 2010] [12:57:47] <pieterh> yes, well organized knowledge is kind of critical
| [Wednesday 11 August 2010] [12:58:00] <feroz_>  Hello.
| [Wednesday 11 August 2010] [12:58:09] <pieterh> :-) hi
| [Wednesday 11 August 2010] [12:58:42] <travlr>  in my dreams, i'd like to organize an effort of a doc template for all of the oss community to adopt
| [Wednesday 11 August 2010] [12:59:57] <feroz_>  Wondering if anyone has made any benchmark on the performance of pubsub
| [Wednesday 11 August 2010] [13:00:03] <pieterh> travel: one of the joys and strengths of the oss community is we will never agree totally on anything
| [Wednesday 11 August 2010] [13:00:23] <travlr>  yup... its just a dream
| [Wednesday 11 August 2010] [13:00:27] <pieterh> feroz_: there is a performance test program for pubsub included with 0mq
| [Wednesday 11 August 2010] [13:00:45] <pieterh> and there are afair whitepapers that report test results
| [Wednesday 11 August 2010] [13:01:13] <pieterh> but the best is to make your own tests
| [Wednesday 11 August 2010] [13:02:00] <dos000_> i was looking at rackspace last night for running tests on large sacale.
| [Wednesday 11 August 2010] [13:02:22] <pieterh> see perf subdirectory, local_thr.cpp and remote_thr.cpp are a pubsub test case for throughput
| [Wednesday 11 August 2010] [13:02:24] <dos000_> a 16g machine will cost $.98 for one hour
| [Wednesday 11 August 2010] [13:02:42] <feroz_>  pieterh: okay, i'll lookup for the whitepapers. I just wanted to read what has already been done before doing my own. thanks
| [Wednesday 11 August 2010] [13:03:34] <dos000_> thats a full machine btw with16g of ram
| [Wednesday 11 August 2010] [13:04:19] <dos000_> and if you are running tests there is no extra money for internall traffic nor for storage
| [Wednesday 11 August 2010] [13:05:03] <pieterh> dos000_: for 0MQ, 20MB of ram will do... the real issues are network infrastructure
| [Wednesday 11 August 2010] [13:05:57] <dos000_> pieterh, i am running cassadra behind 0mq.
| [Wednesday 11 August 2010] [13:06:28] <dos000_> but you are right i cant decide about the switches and routers between machines
| [Wednesday 11 August 2010] [13:07:25] <dos000_> i cant go and buy those stuff on my own .. the idea is to test this on the cloud. since it will run on the cloud
| [Wednesday 11 August 2010] [13:08:05] <dos000_> the point is getting a machine is soo cheap that you try this with large scale
| [Wednesday 11 August 2010] [13:09:57] <dos000_> i am worried about the context switching if you are running the code java binding for zmq
| [Wednesday 11 August 2010] [13:11:49] <sustrik> dos000_: if you are going to run on a VM, the context switching is out of your control
| [Wednesday 11 August 2010] [13:12:15] <dos000_> i meant between c and java
| [Wednesday 11 August 2010] [13:12:38] <sustrik> afaik there's no context switching there
| [Wednesday 11 August 2010] [13:12:47] <sustrik> c functions are called in context of the java thread
| [Wednesday 11 August 2010] [13:12:52] <dos000_> not in the kernel sense yes
| [Wednesday 11 August 2010] [13:13:50] <dos000_> when traffic comes it comes to zmq then i have to read the bytes in java
| [Wednesday 11 August 2010] [13:14:21] <dos000_> the protocol handler is done in java
| [Wednesday 11 August 2010] [13:14:32] <sustrik> you are worried about the cost of copy?
| [Wednesday 11 August 2010] [13:15:31] <dos000_> i think i can pass a pointer . but the fact that the c code has to call jvm byte code has to incur some delay i assume
| [Wednesday 11 August 2010] [13:15:50] <sustrik> maybe
| [Wednesday 11 August 2010] [13:16:03] <sustrik> but JNI looks pretty straighjtforward
| [Wednesday 11 August 2010] [13:16:21] <dos000_> i would like to be proven (very) wrong
| [Wednesday 11 August 2010] [13:16:23] <sustrik> try checking on some Java forum
| [Wednesday 11 August 2010] [13:16:52] <dos000_> i will actually do the actual tests at some time
| [Wednesday 11 August 2010] [13:17:13] <dos000_> this will give clear answer as to if i need to solve this or a non issue
| [Wednesday 11 August 2010] [13:17:45] <sustrik> ack
| [Wednesday 11 August 2010] [13:31:37] <dos000_> where is the irc deamon loggin this channel ? 
| [Wednesday 11 August 2010] [13:32:00] <dos000_> i need to go back to discussions i had a while ago
| [Wednesday 11 August 2010] [13:34:37] <travlr>  dos000_: re: irc log... i'm doing it soon.. i got real busy lately.
| [Wednesday 11 August 2010] [13:37:45] <travlr>  if anyone has an archive of the logs on their computer, let me know because i have to fill a couple of holes in my collection.
| [Wednesday 11 August 2010] [14:57:15]    * dos000_ just sent his first mail to the mailing list
| [Wednesday 11 August 2010] [14:58:30] <sustrik> dos000_: what are you asking about?
| [Wednesday 11 August 2010] [14:58:34] <sustrik> it's not clear
| [Wednesday 11 August 2010] [14:59:33] <dos000_> someone told me here that if i use zmq_poll i have to use it for all sockets. 
| [Wednesday 11 August 2010] [14:59:53] <dos000_> which was weird
| [Wednesday 11 August 2010] [15:01:26] <sustrik> it's just about combining standard and 0mq sockets
| [Wednesday 11 August 2010] [15:01:42] <sustrik> the only way to poll for both in a single go is zmq_poll
| [Wednesday 11 August 2010] [15:02:09] <sustrik> however, you are free to use whatever polling mechanism if all you are interested in are standard sockets
| [Wednesday 11 August 2010] [15:03:03] <dos000_> i have this : incoming traffic --> dispatcher --> 0mq subscribers
| [Wednesday 11 August 2010] [15:03:21] <dos000_> i want to use poll on the left of the dispatcher .. not on the right
| [Wednesday 11 August 2010] [15:03:45] <sustrik> what's on the left?
| [Wednesday 11 August 2010] [15:03:49] <sustrik> standard sockets?
| [Wednesday 11 August 2010] [15:03:56] <sustrik> if so, use any mechanism you like
| [Wednesday 11 August 2010] [15:03:59] <dos000_> nop zmq subscribers
| [Wednesday 11 August 2010] [15:04:13] <sustrik> ?
| [Wednesday 11 August 2010] [15:04:20] <dos000_> so the dispatcher is publishing to subscribers
| [Wednesday 11 August 2010] [15:04:32] <sustrik> via 0mq i suppose
| [Wednesday 11 August 2010] [15:04:36] <sustrik> ok
| [Wednesday 11 August 2010] [15:04:37] <dos000_> yes indeed
| [Wednesday 11 August 2010] [15:04:40] <sustrik> what's on the left side?
| [Wednesday 11 August 2010] [15:05:12] <dos000_> incoming network traffic. disoatcher is listener 
| [Wednesday 11 August 2010] [15:05:24] <sustrik> standard sockets, right?
| [Wednesday 11 August 2010] [15:05:53] <dos000_> yes. i am using zmq_poll on the left
| [Wednesday 11 August 2010] [15:06:14] <sustrik> if 0mq sockets are not involved
| [Wednesday 11 August 2010] [15:06:20] <dos000_> just to read traffic off the network card
| [Wednesday 11 August 2010] [15:06:23] <sustrik> then you can use select/pol etc.
| [Wednesday 11 August 2010] [15:06:31] <sustrik> whatever you like
| [Wednesday 11 August 2010] [15:06:53] <dos000_> ah!
| [Wednesday 11 August 2010] [15:07:32] <sustrik> use zmq_poll only if there are 0mq sockets you need to poll for
| [Wednesday 11 August 2010] [15:07:34] <dos000_> so on the right side if i want to use zmq_poll then i have to do so for all zmq socket in the dispatcher ?
| [Wednesday 11 August 2010] [15:08:01] <sustrik> ?
| [Wednesday 11 August 2010] [15:08:09] <sustrik> it's easy
| [Wednesday 11 August 2010] [15:08:17] <Chris_____>  I want to use zeromq to talk to Nasdaq and receive NLS protocol messages.
| [Wednesday 11 August 2010] [15:08:17] <sustrik> is there a 0mq socket in the pollset?
| [Wednesday 11 August 2010] [15:08:24] <sustrik> if so, use zmq_poll
| [Wednesday 11 August 2010] [15:08:32] <sustrik> otherwise use whatever you like
| [Wednesday 11 August 2010] [15:08:41] <dos000_> ok i got that.
| [Wednesday 11 August 2010] [15:08:59] <dos000_> thanks a lot
| [Wednesday 11 August 2010] [15:09:04] <Chris_____>  The NLS spec uses SoupTCP which is an easy protocol that sits on top of TCP
| [Wednesday 11 August 2010] [15:09:41] <sustrik> i am afraid nasdaq doesn't use 0mq
| [Wednesday 11 August 2010] [15:09:43] <sustrik> :)
| [Wednesday 11 August 2010] [15:10:22] <Chris_____>  That's what I wonder whether this is the right forum. Can I build a protocol with sockets using zeromq?
| [Wednesday 11 August 2010] [15:10:43] <sustrik> 0mq has it's own message framing
| [Wednesday 11 August 2010] [15:10:49] <sustrik> basically size+data
| [Wednesday 11 August 2010] [15:11:09] <sustrik> presumably, nasdaq wouldn't understand that
| [Wednesday 11 August 2010] [15:11:19] <sustrik> you'll have to build a bridge
| [Wednesday 11 August 2010] [15:11:37] <sustrik> that would speak SoupTCP on one side and 0mq on another
| [Wednesday 11 August 2010] [15:11:47] <Chris_____>  No, I need to build a client that understands SoupTCP and am searching for a network API to help me.
| [Wednesday 11 August 2010] [15:12:05] <sustrik> no SoupTCP support in 0mq
| [Wednesday 11 August 2010] [15:12:08] <sustrik> sorry
| [Wednesday 11 August 2010] [15:12:17] <Chris_____>  I am actively looking at Boost ASIO and am also curios about zeromq
| [Wednesday 11 August 2010] [15:12:35] <CIA-20>  zeromq2: 03Pieter Hintjens 07master * rde01737 10/ (doc/Makefile.am doc/zmq.txt doc/zmq_deviced.txt): Removed wip zmq_deviced from master - http://bit.ly/aZn9NX
| [Wednesday 11 August 2010] [15:12:47] <Chris_____>  How hard is it to build SoupTCP into zeromq?
| [Wednesday 11 August 2010] [15:13:01] <sustrik> dunno, depends on how complex SoupTCP is
| [Wednesday 11 August 2010] [15:13:12] <sustrik> you would have to write a parser etc.
| [Wednesday 11 August 2010] [15:13:49] <Chris_____>  It's a simple line-oriented protocol that is mostly 1-way (Nasdaq -> user) whereby stock pricing information is sent to the user.
| [Wednesday 11 August 2010] [15:14:35] <Chris_____>  Upstream heartbests are needed about once-per-second. The protocol needs to support 15mbps streaming with burst of 30-35mbps.
| [Wednesday 11 August 2010] [15:15:03] <sustrik> you would have to implement whole the SoupTCP stuff
| [Wednesday 11 August 2010] [15:15:09] <sustrik> it's up to you
| [Wednesday 11 August 2010] [15:15:30] <Chris_____>  Yes, they give the spec and it is up to me to build the sofftware to interact with the system.
| [Wednesday 11 August 2010] [15:15:39] <sustrik> :)
| [Wednesday 11 August 2010] [15:15:51] <sustrik> try to find out an existing implementation first
| [Wednesday 11 August 2010] [15:15:59] <sustrik> you may save a lot of work that way
| [Wednesday 11 August 2010] [15:16:34] <Chris_____>  Well, I saw that iMatrix did stuff in the financial world so that is why I thought maybe the zeromq approach would work for this application too.
| [Wednesday 11 August 2010] [15:16:51] <dos000_> Chris_____, do you have a parser now ? and in which lang ?
| [Wednesday 11 August 2010] [15:17:06] <Chris_____>  No parser but I plan to use C++
| [Wednesday 11 August 2010] [15:17:23] <dos000_> there is no open implementation already out there ?
| [Wednesday 11 August 2010] [15:17:53] <guido_g> http://cargocult.ca/ccc_doc/classCargoCult_1_1SoupTCP.html
| [Wednesday 11 August 2010] [15:18:00] <Chris_____>  I did Google but it seems like only proprietary stuff which includes other streams.
| [Wednesday 11 August 2010] [15:19:15] <Chris_____>  Dooo.
| [Wednesday 11 August 2010] [15:19:24] <Chris_____>  Thanks Guido_g.
| [Wednesday 11 August 2010] [15:19:39] <guido_g> this google thing is incredible...
| [Wednesday 11 August 2010] [15:19:44] <dos000_> cargocult is canadian (from the domain) thats gotta be good !
| [Wednesday 11 August 2010] [15:20:58] <pieterh> Chris_____: what I'd do to start is make a SoupTCP->0MQ bridge
| [Wednesday 11 August 2010] [15:21:03] <guido_g> souptcp includes authentication, so it seems not to fit into the current mq model
| [Wednesday 11 August 2010] [15:21:19] <pieterh> read SoupTCP at one side (with authentication etc.) and push out the other side
| [Wednesday 11 August 2010] [15:21:46] <Chris_____>  That's correct; part of the direction to Nasdaq includes a socket with login/password information and a response.
| [Wednesday 11 August 2010] [15:21:49] <pieterh> I really wish I'd called our business "iMatrix" but that was a small graphics firm, in 1996
| [Wednesday 11 August 2010] [15:23:08] <sjampoo> pieterh, seriously i've read iMatix zillions and it wasn't until I tried to google it that I noticed there was no 'r' in there.
| [Wednesday 11 August 2010] [15:23:10] <sjampoo> really weird
| [Wednesday 11 August 2010] [15:23:11] <pieterh> Chris_____: what message sizes? 
| [Wednesday 11 August 2010] [15:23:21] <pieterh> sjampoo: this is how we parse words 
| [Wednesday 11 August 2010] [15:23:24] <pieterh> :-)
| [Wednesday 11 August 2010] [15:23:44] <sjampoo> i knw thts wh u cn undrstnd me
| [Wednesday 11 August 2010] [15:23:49] <pieterh> wtf?
| [Wednesday 11 August 2010] [15:23:52] <sjampoo> hehe
| [Wednesday 11 August 2010] [15:23:52] <dos000_> howabout s : incoming traffic --> dispatcher publish raw packets to zmq req/reply --> distributed req/reply to parse suoptcp in any lang
| [Wednesday 11 August 2010] [15:24:09] <Chris_____>  Sorry, I see now that the company is iMatix. :)
| [Wednesday 11 August 2010] [15:24:29] <Chris_____>  My typeface is small but my face is now red.
| [Wednesday 11 August 2010] [15:25:27] <pieterh> it's a common mistake...
| [Wednesday 11 August 2010] [15:26:18] <pieterh> Chris_____: do you need a design for a bridge?
| [Wednesday 11 August 2010] [15:27:09] <Chris_____>  I do need knowledge to make the solution; if I can leverage off of other designs, that'd be great.
| [Wednesday 11 August 2010] [15:27:10] <sjampoo> I think he would prefer an implementation 
| [Wednesday 11 August 2010] [15:28:25] <Chris_____>  Is this right place to solicit jobs? If not, accept my apologies and I won't bring it up again.
| [Wednesday 11 August 2010] [15:29:49] <Chris_____>  Anyway, I will study Guido's URL and continue to work with zeromq. Thanks for the discussion thus far.
| [Wednesday 11 August 2010] [15:31:42] <Chris_____>  Message size in SoupTCP are around 100 bytes usually.
| [Wednesday 11 August 2010] [15:31:52] <pieterh> Chris____: here's a design: http://www.zeromq.org/docs:how-to-bridge-to-souptcp
| [Wednesday 11 August 2010] [15:32:15] <pieterh> When you say "solicit jobs" what do you mean precisely?
| [Wednesday 11 August 2010] [15:32:19] <dos000_> pieterh, wow!
| [Wednesday 11 August 2010] [15:32:33] <Chris_____>  It is basically a realtime connection to obtain last price.
| [Wednesday 11 August 2010] [15:32:53] <Chris_____>  I will try to do it myself but could pay someone(s) for help.
| [Wednesday 11 August 2010] [15:32:57] <pieterh> Chris:
| [Wednesday 11 August 2010] [15:33:01] <dos000_> pieterh, what do you use for the images ?
| [Wednesday 11 August 2010] [15:33:18] <pieterh> contact me and we'll make you an offer
| [Wednesday 11 August 2010] [15:33:28] <pieterh> iMatix funds the project this way
| [Wednesday 11 August 2010] [15:33:33] <pieterh> dos000_: ditaa
| [Wednesday 11 August 2010] [15:33:43] <pieterh> it is really sweet
| [Wednesday 11 August 2010] [15:34:01] <pieterh> Use the contact link on http://www.zeromq.org
| [Wednesday 11 August 2010] [15:34:55] <Chris_____>  You mean go to iMatix website and fill out the contact info?
| [Wednesday 11 August 2010] [15:35:24] <pieterh> Chris____: right
| [Wednesday 11 August 2010] [15:35:35] <Chris_____>  OK; thanks. All for now.
| [Wednesday 11 August 2010] [15:35:43] <pieterh> so bursts of 350,000 messages/second, that is really not a problem
| [Wednesday 11 August 2010] [15:36:16] <pieterh> a bridge will add about 15-30usec of latency
| [Wednesday 11 August 2010] [15:36:49] <Chris_____>  Seems like it could work.
| [Wednesday 11 August 2010] [15:36:56] <dos000_> pieterh, if this is pub/sub how do you channel responses bacck from subscribers ?
| [Wednesday 11 August 2010] [15:37:16] <pieterh> dos000_: you don't... the bridge does the heartbeating and the 0MQ doesn't use it
| [Wednesday 11 August 2010] [15:37:17] <dos000_> pieterh, unless this is only a read only
| [Wednesday 11 August 2010] [15:37:25] <pieterh> it's market data, so strictly one-way
| [Wednesday 11 August 2010] [15:37:31] <dos000_> ah!
| [Wednesday 11 August 2010] [15:37:48] <dos000_> i assumed it was two way .. dumb me
| [Wednesday 11 August 2010] [15:37:59] <pieterh> the key is low latency, so probably you'd use a multicast bus 
| [Wednesday 11 August 2010] [15:38:10] <dos000_> ah!
| [Wednesday 11 August 2010] [15:38:26] <pieterh> this is actually the original main use case for 0MQ
| [Wednesday 11 August 2010] [15:39:01] <dos000_> if you had tow way what would you do ?
| [Wednesday 11 August 2010] [15:39:20] <pieterh> tow way? sorry... can't parse...
| [Wednesday 11 August 2010] [15:39:35]    * dos000_ is yound zmq jedi learning from master pieterh 
| [Wednesday 11 August 2010] [15:39:52] <pieterh> oh no, i'm not a master in 0MQ, only in more general aspects of messaging
| [Wednesday 11 August 2010] [15:39:56] <dos000_> pieterh, i mean if the suptcp protocol required a response for exemple
| [Wednesday 11 August 2010] [15:40:17] <pieterh> well, it doesn't :-)
| [Wednesday 11 August 2010] [15:40:27] <dos000_> my protocol does
| [Wednesday 11 August 2010] [15:40:30] <pieterh> but if it did, you'd use a separate pattern to collect responses
| [Wednesday 11 August 2010] [15:40:43] <pieterh> it has been observed by people who know 0MQ better than me that...
| [Wednesday 11 August 2010] [15:40:51] <dos000_> ok .. 
| [Wednesday 11 August 2010] [15:40:57] <pieterh> - break down your use cases into individual patterns
| [Wednesday 11 August 2010] [15:41:07] <pieterh> - solve each pattern using the appropriate 0MQ style
| [Wednesday 11 August 2010] [15:41:14] <pieterh> - creates harmony and scalability
| [Wednesday 11 August 2010] [15:41:27] <pieterh> so whereas you might mix control and data on one tcp socket
| [Wednesday 11 August 2010] [15:41:39] <pieterh> you might well use two 0MQ sockets
| [Wednesday 11 August 2010] [15:41:50] <dos000_> ah huh .. 
| [Wednesday 11 August 2010] [15:42:18] <pieterh> the reason is that policies for different patterns are different
| [Wednesday 11 August 2010] [15:42:29] <pieterh> and when you get the policy *right* you can scale it easily
| [Wednesday 11 August 2010] [15:42:39] <dos000_> ok ..
| [Wednesday 11 August 2010] [15:42:45] <pieterh> if you mix policies in one connection it can't be scaled (or only with great cost)
| [Wednesday 11 August 2010] [15:43:04] <dos000_> mmmmm digesting
| [Wednesday 11 August 2010] [15:43:07] <pieterh> policy includes things like "do we send replies and if so, how do we route them", and "do we sent asynchronously or synchronously"
| [Wednesday 11 August 2010] [15:43:19] <dos000_> ok .. 
| [Wednesday 11 August 2010] [15:43:40] <pieterh> i can give a concrete example
| [Wednesday 11 August 2010] [15:43:47] <pieterh> which illustrates this nicely IMO
| [Wednesday 11 August 2010] [15:43:51] <dos000_> please .. 
| [Wednesday 11 August 2010] [15:43:56] <pieterh> in OpenAMQ we had a performance problem
| [Wednesday 11 August 2010] [15:44:09] <pieterh> where we could only pump 100,000 messages/second through a connection
| [Wednesday 11 August 2010] [15:44:19] <pieterh> less, actually, 60k or so
| [Wednesday 11 August 2010] [15:44:26] <pieterh> AMQP connections have a mix of policies
| [Wednesday 11 August 2010] [15:44:35] <pieterh> request-reply commands plus streaming data
| [Wednesday 11 August 2010] [15:44:40] <pieterh> but all mixed up
| [Wednesday 11 August 2010] [15:44:54] <pieterh> we separated those into two connections
| [Wednesday 11 August 2010] [15:44:58] <pieterh> one for commands, one for streaming data
| [Wednesday 11 August 2010] [15:45:16] <pieterh> we were able to get 300,000 message/second finally
| [Wednesday 11 August 2010] [15:45:39] <pieterh> plus we moved queues off the broker, making it a lot more stable
| [Wednesday 11 August 2010] [15:46:05] <pieterh> http://wiki.amqp.org/spec:6
| [Wednesday 11 August 2010] [15:46:26] <pieterh> it was significantly simpler once we moved to one policy per connection
| [Wednesday 11 August 2010] [15:46:41] <pieterh> and simpler meant we could optimize and make it faster
| [Wednesday 11 August 2010] [15:47:02] <pieterh> does this help?
| [Wednesday 11 August 2010] [15:47:27] <dos000_> ok ..
| [Wednesday 11 August 2010] [15:47:32] <dos000_> so far so good.
| [Wednesday 11 August 2010] [15:47:55] <dos000_> so on the way back i would put data on another queue
| [Wednesday 11 August 2010] [15:48:05] <pieterh> send it via another socket
| [Wednesday 11 August 2010] [15:48:50] <dos000_> the question is when it comes to the bridge then the bridge has to use a hash to figure where is the object corelation
| [Wednesday 11 August 2010] [15:49:12] <dos000_> i mean to figure which socket to send it back
| [Wednesday 11 August 2010] [15:49:22] <pieterh> yes, that's probably a good way
| [Wednesday 11 August 2010] [15:49:35] <dos000_> nice
| [Wednesday 11 August 2010] [15:49:51] <pieterh> are you prototyping it?
| [Wednesday 11 August 2010] [15:49:57] <pieterh> in python or something?
| [Wednesday 11 August 2010] [15:50:03] <dos000_> not yet .. this stuff is still in head
| [Wednesday 11 August 2010] [15:50:13] <dos000_> its a mix of java and c/c++
| [Wednesday 11 August 2010] [15:50:26] <dos000_> bridge is definitely c/++
| [Wednesday 11 August 2010] [15:50:41] <dos000_> subscribers are java (for now)
| [Wednesday 11 August 2010] [15:52:30] <dos000_> very interesting indeed
| [Wednesday 11 August 2010] [15:54:03] <dos000_> pieterh, the only problem is the has will have to be protected for multithreaded use
| [Wednesday 11 August 2010] [15:54:10] <dos000_> the hash table
| [Wednesday 11 August 2010] [15:54:46] <pieterh> why multithreaded?
| [Wednesday 11 August 2010] [15:55:08] <pieterh> I'd use a single thread for routing
| [Wednesday 11 August 2010] [15:55:10] <dos000_> i have say 300 threads wating for messages from subscribers
| [Wednesday 11 August 2010] [15:55:20] <dos000_> ok
| [Wednesday 11 August 2010] [15:55:40] <pieterh> furthermore, a single thread can collect replies from 300 subscribers
| [Wednesday 11 August 2010] [15:55:56] <pieterh> this is what 0MQ does for you, handle the connections transparently
| [Wednesday 11 August 2010] [15:56:16] <dos000_> ok that was my next question ... btw i apprciate all this time you are spending here
| [Wednesday 11 August 2010] [15:56:32]    * pieterh has to emphasize this in the user guide, you do not use the "1 thread per peer" style
| [Wednesday 11 August 2010] [15:56:35] <pieterh> shoot
| [Wednesday 11 August 2010] [15:57:14] <dos000_> in the zmq_poll how many sockets until you need a second thread in zmq_poll
| [Wednesday 11 August 2010] [15:57:32] <pieterh> no limit as such
| [Wednesday 11 August 2010] [15:57:38] <dos000_> ah
| [Wednesday 11 August 2010] [15:57:59] <pieterh> in fact you would never have multiple threads polling the same sockets
| [Wednesday 11 August 2010] [15:58:02] <dos000_> so one thread doing zmq_poll is enough
| [Wednesday 11 August 2010] [15:58:06] <pieterh> yes
| [Wednesday 11 August 2010] [15:58:11] <dos000_> cool
| [Wednesday 11 August 2010] [15:58:21] <pieterh> you can do a *lot* of work in one thread
| [Wednesday 11 August 2010] [15:58:46] <dos000_> thanks a lot pieterh 
| [Wednesday 11 August 2010] [15:59:09] <pieterh> i'm only three lessons ahead of you, dos000_ :-)
| [Wednesday 11 August 2010] [16:08:52] <dos000_> pieterh, do you have the src for that picture http://www.zeromq.org/docs:how-to-bridge-to-souptcp ?
| [Wednesday 11 August 2010] [16:09:11] <pieterh> I'll add it to the page along with the perl script that does the transformation
| [Wednesday 11 August 2010] [16:09:18] <dos000_> cool
| [Wednesday 11 August 2010] [16:09:18] <pieterh> you need to get the ditaa jar
| [Wednesday 11 August 2010] [16:09:37] <dos000_> yes i am planning to keep this jar with my projects
| [Wednesday 11 August 2010] [16:14:31] <pieterh> dos000_: i've added the links to that page
| [Wednesday 11 August 2010] [16:14:43] <dos000_> thansk a lot
| [Wednesday 11 August 2010] [16:14:47] <pieterh> np
| [Wednesday 11 August 2010] [18:14:55] <CIA-20>  jzmq: 03Sam Aarons 07master * r30712eb 10/ perf/local_thr.java : Update perf test to reflect changes to setsockopt. - http://bit.ly/cdi0QU
| [Thursday 12 August 2010] [02:16:37] <CIA-20>   zeromq2: 03Martin Sustrik 07wip-shutdown * radb8ecb 10/ (7 files): dezombification procedure fixed - http://bit.ly/bgEdXg
| [Thursday 12 August 2010] [05:43:34] <mato> pieterh: Git tip for you: You manually reverted the zmq_deviced changes when you could have just done "git revert <commit>"
| [Thursday 12 August 2010] [05:44:42] <mato> pieterh: Which basically applies the changes from <commit> in reverse and writes the log message (Reverted "<title>" commit <commit> or similar) for you.
| [Thursday 12 August 2010] [05:51:21] <pieterh>  mato: yes, you're right
| [Thursday 12 August 2010] [05:51:32] <pieterh>  worth documenting as well
| [Thursday 12 August 2010] [05:51:40] <pieterh>  i knew it but forgot
| [Thursday 12 August 2010] [05:52:00] <sustrik>  pieterh: would you be willing to help with the linux kongress article
| [Thursday 12 August 2010] [05:52:12] <sustrik>  ?
| [Thursday 12 August 2010] [05:52:15] <pieterh>  sustrik: i already sent you that several days ago
| [Thursday 12 August 2010] [05:52:23] <sustrik>  yep, that's the first part
| [Thursday 12 August 2010] [05:52:34] <pieterh>  ? that's already 3x too long... :-)
| [Thursday 12 August 2010] [05:52:35] <sustrik>  i have to write next one till 15th
| [Thursday 12 August 2010] [05:52:53] <sustrik>  i'll shave the excess load off
| [Thursday 12 August 2010] [05:52:54] <pieterh>  you have multiple articles to present?
| [Thursday 12 August 2010] [05:53:09] <sustrik>  nope, it's just one, but i want it to consist of 2 parts
| [Thursday 12 August 2010] [05:53:14] <sustrik>  1. introduction to 0mq
| [Thursday 12 August 2010] [05:53:19] <pieterh>  ah, you didn't explain this
| [Thursday 12 August 2010] [05:53:25] <mato> sustrik: you could try asking them nicely if it's at all possible to deliver it later...
| [Thursday 12 August 2010] [05:53:30] <mato> sustrik: worth a try, no?
| [Thursday 12 August 2010] [05:53:35] <sustrik>  maybe
| [Thursday 12 August 2010] [05:53:41] <sustrik>  still have 3 days...
| [Thursday 12 August 2010] [05:53:44] <pieterh>  sustrik: I don't mind helping if you tell me what you want
| [Thursday 12 August 2010] [05:53:47] <pieterh>  :-)
| [Thursday 12 August 2010] [05:54:05] <sustrik>  pieter: i'll send you a concept via email
| [Thursday 12 August 2010] [05:54:08] <sustrik>  wait a sec
| [Thursday 12 August 2010] [05:55:16] <pieterh>  sustrik: ok, and the first part is at http://www.zeromq.org/docs:introduction
| [Thursday 12 August 2010] [05:55:26] <pieterh>  there are some fixes done in parallel with fixes to the Guide
| [Thursday 12 August 2010] [05:56:06] <sustrik>  ok, i'll do the editing part
| [Thursday 12 August 2010] [06:02:04] <sustrik>  gh, gh, i am trying to formulate what i want to say...
| [Thursday 12 August 2010] [06:02:14] <sustrik>  irc would be better than email
| [Thursday 12 August 2010] [06:02:50] <sustrik>  after showing how 0mq works (based on simple examples) i would like to convey the large picture
| [Thursday 12 August 2010] [06:03:27] <sustrik>  that is, in short, inteligent endpoints and dumb intermediaries
| [Thursday 12 August 2010] [06:03:46] <sustrik>  standard internet end-to-end principle
| [Thursday 12 August 2010] [06:03:57] <sustrik>  it should be explained on example
| [Thursday 12 August 2010] [06:04:08] <sustrik>  there are 3 examples i can think of
| [Thursday 12 August 2010] [06:04:33] <pieterh>  who is 'gh'? :-)
| [Thursday 12 August 2010] [06:04:55] <sustrik>  it's expression of desperation
| [Thursday 12 August 2010] [06:04:57] <sustrik>  :)
| [Thursday 12 August 2010] [06:05:14] <sustrik>  1. i can start with moglen's quote about ditributed servies, move to how diaspora should work
| [Thursday 12 August 2010] [06:05:32] <sustrik>  and show that 0mq is a generic infrastructure for that kind interconnect
| [Thursday 12 August 2010] [06:05:33] <pieterh>  would you take a second to read the new introduction text i wrote for the guide?
| [Thursday 12 August 2010] [06:05:44] <pieterh>  it might be part of what you want to say already
| [Thursday 12 August 2010] [06:05:49] <sustrik>  yep, i read it
| [Thursday 12 August 2010] [06:05:55] <sustrik>  it's ok but it's too abstract
| [Thursday 12 August 2010] [06:06:03] <pieterh>  its the problem spec
| [Thursday 12 August 2010] [06:06:09] <sustrik>  i need an example, that's the best way to convey the idea
| [Thursday 12 August 2010] [06:06:21] <pieterh>  just one question first
| [Thursday 12 August 2010] [06:06:25] <mato> sustrik: what about that narrative you wrote?
| [Thursday 12 August 2010] [06:06:35] <sustrik>  it's good but clumsy
| [Thursday 12 August 2010] [06:06:39] <mato> sustrik: so, polish it
| [Thursday 12 August 2010] [06:06:43] <sustrik>  that was my option 2
| [Thursday 12 August 2010] [06:06:56] <mato> sustrik: it's already there, a good starting point
| [Thursday 12 August 2010] [06:07:01] <pieterh>  sustrik: do you think the user guide should try to explain the big picture up front or not?
| [Thursday 12 August 2010] [06:07:10] <pieterh>  do people care?
| [Thursday 12 August 2010] [06:07:11] <sustrik>  not really
| [Thursday 12 August 2010] [06:07:16] <sustrik>  maybe a different article
| [Thursday 12 August 2010] [06:07:21] <pieterh>  maybe
| [Thursday 12 August 2010] [06:07:32] <pieterh>  so why do you want to explain this to your audience?
| [Thursday 12 August 2010] [06:07:56] <mato> pieterh: yeah, this was my main feeling from the user guide at the moment... it's good, but quite longwinded and i was missing more of a "practical" feel
| [Thursday 12 August 2010] [06:07:57] <sustrik>  because i want involve kernel developers
| [Thursday 12 August 2010] [06:08:10] <sustrik>  those are not interested what 0mq offers from user's point of view
| [Thursday 12 August 2010] [06:08:12] <mato> pieterh: but to be honest, i've not really read it, this is just an off-the-cuff feeling
| [Thursday 12 August 2010] [06:08:15] <sustrik>  they cannot use it anyway
| [Thursday 12 August 2010] [06:08:25] <pieterh>  mato: sure, it's to read, not use as reference...
| [Thursday 12 August 2010] [06:08:48] <mato> pieterh: yeah, but even then the assumption is the person is reading it with the intent of doing something practical
| [Thursday 12 August 2010] [06:08:49] <sustrik>  what they need to understand to get interested is exactly the big picture
| [Thursday 12 August 2010] [06:08:51] <mato> pieterh: that's all...
| [Thursday 12 August 2010] [06:08:53] <pieterh>  sustrik: ok, you need to establish who your audience is and what you want them to take away with them
| [Thursday 12 August 2010] [06:09:11] <sustrik>  audience: kernel developers
| [Thursday 12 August 2010] [06:09:18] <sustrik>  message: this stuff should be in kernel
| [Thursday 12 August 2010] [06:09:36] <pieterh>  mato: ... it swings around, if i start with code people want more exposition, and if there's exposition, people ask for more practicality
| [Thursday 12 August 2010] [06:09:45] <pieterh>  sustrik: ok that's clear
| [Thursday 12 August 2010] [06:09:57] <pieterh>  then i'd suggest starting with eben moglen's speech
| [Thursday 12 August 2010] [06:10:00] <pieterh>  take it from there
| [Thursday 12 August 2010] [06:10:04] <mato> pieterh: a format i've found useful is that of e.g. the rails books, and indeed many of the "practical" books that exist today...
| [Thursday 12 August 2010] [06:10:15] <sustrik>  yes, i had the same idea
| [Thursday 12 August 2010] [06:10:23] <pieterh>  linux kernel developers are well inside the GPL camp
| [Thursday 12 August 2010] [06:10:35] <mato> pieterh: which is, you build a practical system, or more than one, from simpler to more complex
| [Thursday 12 August 2010] [06:10:47] <mato> pieterh: as you go along, you then explain the hard bits, but not upfront
| [Thursday 12 August 2010] [06:10:57] <mato> pieterh: just a suggestion...
| [Thursday 12 August 2010] [06:10:58] <pieterh>  mato: yes, i know
| [Thursday 12 August 2010] [06:11:00] <pieterh>  i agree too
| [Thursday 12 August 2010] [06:11:12] <pieterh>  this was in fact the plan
| [Thursday 12 August 2010] [06:11:20] <mato> based from experience i get the most out of books like that when the subject matter is complex
| [Thursday 12 August 2010] [06:11:32] <pieterh>  in between "basic concepts" and the rest should come a worked example
| [Thursday 12 August 2010] [06:11:59] <pieterh>  i'm not sure how much of the basic concepts remains, then
| [Thursday 12 August 2010] [06:12:09] <pieterh>  it does not matter, the text is highly fungible
| [Thursday 12 August 2010] [06:12:38] <pieterh>  this is really phase 1, capture 
| [Thursday 12 August 2010] [06:12:59] <pieterh>  sustrik: i'm not sure the intro i wrote for you will work, then
| [Thursday 12 August 2010] [06:13:09] <sustrik>  it edit it
| [Thursday 12 August 2010] [06:13:15] <sustrik>  but it should be there
| [Thursday 12 August 2010] [06:13:25] <sustrik>  because otherwise people would be simply confused
| [Thursday 12 August 2010] [06:13:34] <pieterh>  ok, what i suggest is you hack that text as you like, put bullets where you want more detail, etc.
| [Thursday 12 August 2010] [06:13:36] <sustrik>  it shows "what the thing is"
| [Thursday 12 August 2010] [06:13:44] <pieterh>  then pass it to me and i'll continue the work
| [Thursday 12 August 2010] [06:13:48] <sustrik>  ok
| [Thursday 12 August 2010] [06:13:52] <pieterh>  i'm playing with gist.github.com
| [Thursday 12 August 2010] [06:14:09] <sustrik>  so let me explain what the part 2 should say
| [Thursday 12 August 2010] [06:14:23] <pieterh>  shoot
| [Thursday 12 August 2010] [06:14:27] <sustrik>  starting with the moglen's quote looks good
| [Thursday 12 August 2010] [06:14:31] <sustrik>  that brings us to diaspora as a comprehensible example of end-to-end messaging
| [Thursday 12 August 2010] [06:14:46] <pieterh>  i like "diaspora"
| [Thursday 12 August 2010] [06:14:51] <sustrik>  it's easy to grasp because everyone knws how facebook works
| [Thursday 12 August 2010] [06:15:08] <pieterh>  facebook is diaspora?  or not diaspora?
| [Thursday 12 August 2010] [06:15:10] <sustrik>  and can understand the centralised=>distributed transition
| [Thursday 12 August 2010] [06:15:16] <sustrik>  it is not
| [Thursday 12 August 2010] [06:15:18] <pieterh>  aha
| [Thursday 12 August 2010] [06:15:29] <pieterh>  sustrik: we need to invent a killer app for 0MQ
| [Thursday 12 August 2010] [06:15:35] <sustrik>  but it's an generally comprehensible example to show
| [Thursday 12 August 2010] [06:15:41] <pieterh>  call it diaspora
| [Thursday 12 August 2010] [06:15:53] <sustrik>  how centralised messaging applications can be decetralised
| [Thursday 12 August 2010] [06:16:07] <sustrik>  keep in mind i have just few minutes to present it
| [Thursday 12 August 2010] [06:16:19] <sustrik>  so the example has to be extremely easy to grasp
| [Thursday 12 August 2010] [06:16:33] <sustrik>  mato: that's the problem with my article
| [Thursday 12 August 2010] [06:16:41] <sustrik>  it's message is not that obvious
| [Thursday 12 August 2010] [06:16:47] <sustrik>  as to grasp it in 10 mins
| [Thursday 12 August 2010] [06:16:48] <pieterh>  you won't present the article as such, you'll talk and the article gets published, right?
| [Thursday 12 August 2010] [06:16:53] <sustrik>  yes
| [Thursday 12 August 2010] [06:17:03] <pieterh>  so would you start by ignoring all existing text
| [Thursday 12 August 2010] [06:17:06] <sustrik>  but there should be some correleation i suppose
| [Thursday 12 August 2010] [06:17:17] <pieterh>  and write down your speech in bullet points
| [Thursday 12 August 2010] [06:17:31] <pieterh>  standard rule for short speech:
| [Thursday 12 August 2010] [06:17:36] <pieterh>  - explain what you are going to say
| [Thursday 12 August 2010] [06:17:42] <pieterh>  - say it, in three parts
| [Thursday 12 August 2010] [06:17:48] <pieterh>  - explain what you just said
| [Thursday 12 August 2010] [06:18:01] <jsimmons> 0mq in the kernel ey
| [Thursday 12 August 2010] [06:18:17] <sustrik>  the whole speach is 45 mins i think
| [Thursday 12 August 2010] [06:18:20] <sustrik>  so it's not that short
| [Thursday 12 August 2010] [06:18:27] <pieterh>  10 or 45? /me is confused now
| [Thursday 12 August 2010] [06:18:31] <sustrik>  the problem is that to present the kernel stuff
| [Thursday 12 August 2010] [06:18:38] <sustrik>  i have to introduce 0mq first
| [Thursday 12 August 2010] [06:18:42] <jsimmons> what would the advantage of having 0mq in the kernel as opposed to an external library?
| [Thursday 12 August 2010] [06:18:45] <sustrik>  which will take say 15 mins
| [Thursday 12 August 2010] [06:19:04] <sustrik>  jsimmons: i'll explain in part 3 :)
| [Thursday 12 August 2010] [06:19:15] <pieterh>  sustrik: i can't follow any longer
| [Thursday 12 August 2010] [06:19:17] <sustrik>  then i need to explain why the stuff is *importatnt*
| [Thursday 12 August 2010] [06:19:21] <sustrik>  say another 15 mins
| [Thursday 12 August 2010] [06:19:37] <sustrik>  then say 5 mins as for "why it should be implemented at kernel level"
| [Thursday 12 August 2010] [06:19:40] <sustrik>  + question
| [Thursday 12 August 2010] [06:19:43] <sustrik>  questions
| [Thursday 12 August 2010] [06:19:57] <sustrik>  pieterh: summary:
| [Thursday 12 August 2010] [06:20:03] <pieterh>  sustrik: irc is not a database
| [Thursday 12 August 2010] [06:20:05] <sustrik>  1. example of 0mq, how it works
| [Thursday 12 August 2010] [06:20:14] <sustrik>  2. why is it important
| [Thursday 12 August 2010] [06:20:24] <sustrik>  3. why it should be in kernal
| [Thursday 12 August 2010] [06:20:27] <sustrik>  4. Q & A
| [Thursday 12 August 2010] [06:20:39]     * mato finds that pieterh's quote of the month is "XYZ is not a database" :-)
| [Thursday 12 August 2010] [06:20:47]     * pieterh is not a database
| [Thursday 12 August 2010] [06:20:52] <sustrik>  :)
| [Thursday 12 August 2010] [06:20:59]     * mato is a database :-)
| [Thursday 12 August 2010] [06:20:59] <pieterh>  so you have your three points
| [Thursday 12 August 2010] [06:21:04] <sustrik>  1 is done
| [Thursday 12 August 2010] [06:21:09] <sustrik>  3 i can write myself
| [Thursday 12 August 2010] [06:21:23] <sustrik>  2 ???
| [Thursday 12 August 2010] [06:21:27] <pieterh>  profit, obviously
| [Thursday 12 August 2010] [06:21:46] <sustrik>  it needs some kind of comprehensible narrative
| [Thursday 12 August 2010] [06:21:49] <mato> sustrik: 2) is your narrative, polished with a good "cloud" example
| [Thursday 12 August 2010] [06:21:50] <pieterh>  why is it important?
| [Thursday 12 August 2010] [06:21:51] <sustrik>  based on example
| [Thursday 12 August 2010] [06:21:58] <pieterh>  why is 0mq important?
| [Thursday 12 August 2010] [06:22:02] <mato> sustrik: since you want to start with eben moglens quote
| [Thursday 12 August 2010] [06:22:23] <mato> sustrik: it would seem that a narrative based around a cloud example is good
| [Thursday 12 August 2010] [06:22:32] <mato> pieterh: incidentally, did you read the narrative sustrik wrote?
| [Thursday 12 August 2010] [06:22:37] <sustrik>  whatever
| [Thursday 12 August 2010] [06:22:50] <pieterh>  sustrik: i'm asking for an ideology of sorts
| [Thursday 12 August 2010] [06:22:52] <sustrik>  the point is that there's only ~15 mins to present it
| [Thursday 12 August 2010] [06:22:57] <sustrik>  so it has to be dead simple
| [Thursday 12 August 2010] [06:22:59] <jsimmons> 1) what is the current situation 2) what is the omq solution 3) why it needs to be included at kernel level. It being important should be blatantly obvious from your excellent example.
| [Thursday 12 August 2010] [06:23:15] <pieterh>  mato: ??? lookup function failed
| [Thursday 12 August 2010] [06:23:55] <mato> pieterh: 1st paper on www.250bpm.com
| [Thursday 12 August 2010] [06:24:00] <sustrik>  http://www.250bpm.com/joe
| [Thursday 12 August 2010] [06:24:07] <sustrik>  but it's too complex imo
| [Thursday 12 August 2010] [06:24:18] <mato> sustrik: nope, assume kernel developers are smart
| [Thursday 12 August 2010] [06:24:40] <pieterh>  sustrik: obviously i think 0MQ is important but can we assume people share our assumptions?
| [Thursday 12 August 2010] [06:24:55] <sustrik>  that's why i wanted to give a real example
| [Thursday 12 August 2010] [06:24:57] <sustrik>  like diaspora
| [Thursday 12 August 2010] [06:25:17] <sustrik>  it's about freedom, the other example (my paper) is about business
| [Thursday 12 August 2010] [06:25:26] <pieterh>  ok, freedom is a good hook
| [Thursday 12 August 2010] [06:25:42] <sustrik>  but i have no example that's both about business and freedom and can be explained in 15 mins
| [Thursday 12 August 2010] [06:25:56] <mato> sustrik: decentralized facebook?
| [Thursday 12 August 2010] [06:25:56] <pieterh>  yes, this is possible
| [Thursday 12 August 2010] [06:26:04] <sustrik>  easy to grasp
| [Thursday 12 August 2010] [06:26:10] <mato> sustrik: remember, everyone knows what facebook does
| [Thursday 12 August 2010] [06:26:21] <pieterh>  mato: "kernel developers are smart"
| [Thursday 12 August 2010] [06:26:27] <pieterh>  you don't need facebook as a reference
| [Thursday 12 August 2010] [06:26:28] <sustrik>  you can even mention "groups"
| [Thursday 12 August 2010] [06:26:31] <jsimmons> yeah but diaspora is a large complicated example
| [Thursday 12 August 2010] [06:26:33] <sustrik>  as an example of a device
| [Thursday 12 August 2010] [06:26:42] <sustrik>  jsimmons: any better idea?
| [Thursday 12 August 2010] [06:26:42] <pieterh>  freedom is about communication
| [Thursday 12 August 2010] [06:26:50] <pieterh>   and the cost of communication
| [Thursday 12 August 2010] [06:26:56] <pieterh>  centralization is anti-freedom
| [Thursday 12 August 2010] [06:27:02] <mato> pieterh: ja, but using facebook as a reference makes it completely obvious
| [Thursday 12 August 2010] [06:27:08] <mato> pieterh: no harm in that...
| [Thursday 12 August 2010] [06:27:31] <pieterh>  sure but what's the alternative to centralized facebook?
| [Thursday 12 August 2010] [06:27:35] <jsimmons> yeah but your software should stand on its own. I think brining politics into it is a mistake.
| [Thursday 12 August 2010] [06:27:45] <jsimmons> and a large complicated non-materialised example, too. on the diaspora thing.
| [Thursday 12 August 2010] [06:27:57] <mato> jsimmons: good point.
| [Thursday 12 August 2010] [06:28:07] <sustrik>  yes, but what's the alternative
| [Thursday 12 August 2010] [06:28:12] <jsimmons> You need something concrete where people can see one thing that ain't zeromq and one thing that is and go wow that's so much better
| [Thursday 12 August 2010] [06:28:21] <pieterh>  yes
| [Thursday 12 August 2010] [06:28:30] <pieterh>  you can take it one step more abstract
| [Thursday 12 August 2010] [06:28:37] <pieterh>  one centralized vs. one distributed
| [Thursday 12 August 2010] [06:28:42] <sustrik>  yes
| [Thursday 12 August 2010] [06:28:47] <pieterh>  but no more than that
| [Thursday 12 August 2010] [06:28:52] <sustrik>  yes
| [Thursday 12 August 2010] [06:28:58] <pieterh>  so what's the most successful distributed system?
| [Thursday 12 August 2010] [06:29:03] <sustrik>  IP
| [Thursday 12 August 2010] [06:29:04] <sustrik>  web
| [Thursday 12 August 2010] [06:29:08] <pieterh>  that every linux kernel developer knows and loves?
| [Thursday 12 August 2010] [06:29:10] <pieterh>  :-)
| [Thursday 12 August 2010] [06:29:11] <mato> IP actually
| [Thursday 12 August 2010] [06:29:13] <pieterh>  git
| [Thursday 12 August 2010] [06:29:19] <mato> yeah, git :)
| [Thursday 12 August 2010] [06:29:21] <jsimmons> git, I thought that too pieterh.
| [Thursday 12 August 2010] [06:29:21] <pieterh>  git
| [Thursday 12 August 2010] [06:29:40] <sustrik>  the question is how to base a narrative on IP
| [Thursday 12 August 2010] [06:29:41] <pieterh>  now imagine you could turn every centralized app into a git
| [Thursday 12 August 2010] [06:29:51] <pieterh>  all it requires is freedom to communicate
| [Thursday 12 August 2010] [06:30:01] <sustrik>  i have an idea
| [Thursday 12 August 2010] [06:30:10] <sustrik>  think of dystopia instead of utopia:
| [Thursday 12 August 2010] [06:30:12] <mato> one important point about the freedom to communicate bit - this is what the internet was originally designed to do
| [Thursday 12 August 2010] [06:30:17] <sustrik>  what if web was centralised?
| [Thursday 12 August 2010] [06:30:20] <pieterh>  mato: absolutely
| [Thursday 12 August 2010] [06:30:38] <sustrik>  each link has to be resolved by a centeralised entity
| [Thursday 12 August 2010] [06:30:41] <mato> now, 0mq enables you to use the net for what it was designed for, for certain problems
| [Thursday 12 August 2010] [06:30:55] <pieterh>  sustrik: i don't think you need to explain why centralization is bad
| [Thursday 12 August 2010] [06:30:58] <pieterh>  people get that
| [Thursday 12 August 2010] [06:30:59] <mato> something along those lines anyway
| [Thursday 12 August 2010] [06:31:02] <pieterh>  especially your audience
| [Thursday 12 August 2010] [06:31:19] <pieterh>  problem is that the cost of distribution is still tooooooo high
| [Thursday 12 August 2010] [06:31:28] <pieterh>  no-one doubts eben's message
| [Thursday 12 August 2010] [06:31:36] <pieterh>  but it's almost impossible to see how to make it
| [Thursday 12 August 2010] [06:31:43] <sustrik>  right
| [Thursday 12 August 2010] [06:31:55] <jsimmons> I think you're talking too abstractly. If they're kernel developers they're developers, give them something that works.
| [Thursday 12 August 2010] [06:31:59] <sustrik>  so the message is "this is IT"
| [Thursday 12 August 2010] [06:32:02] <pieterh>  yes
| [Thursday 12 August 2010] [06:32:05] <pieterh>  this is IT
| [Thursday 12 August 2010] [06:32:13] <pieterh>  did you read my Fixing the World intro?
| [Thursday 12 August 2010] [06:32:16] <sustrik>  yes
| [Thursday 12 August 2010] [06:32:33] <sustrik>  it misses example
| [Thursday 12 August 2010] [06:32:39] <pieterh>  yes
| [Thursday 12 August 2010] [06:32:50] <pieterh>  eben at the start, example after, and you have part two
| [Thursday 12 August 2010] [06:32:57] <sustrik>  exactly
| [Thursday 12 August 2010] [06:32:58] <pieterh>  though I'd move that to part 1
| [Thursday 12 August 2010] [06:33:04] <pieterh>  part 2 is then how 0mq works
| [Thursday 12 August 2010] [06:33:11] <pieterh>  part 3 is then why it must be in the kernel
| [Thursday 12 August 2010] [06:33:17] <pieterh>  /works/ is used/
| [Thursday 12 August 2010] [06:33:18] <sustrik>  pt3 is easy
| [Thursday 12 August 2010] [06:33:21] <pieterh>  yes
| [Thursday 12 August 2010] [06:33:53] <sustrik>  i wanted to have intro to 0mq first so that people can make more sense of the example in part2
| [Thursday 12 August 2010] [06:34:04] <pieterh>  problem spec has to come before solution
| [Thursday 12 August 2010] [06:34:24] <sustrik>  what i wanted to show was"
| [Thursday 12 August 2010] [06:34:37] <sustrik>  1. You can do network programming easy with 0mq
| [Thursday 12 August 2010] [06:34:58] <sustrik>  (no big ideas there, just "how to write client sercer in 10 mins")
| [Thursday 12 August 2010] [06:35:01] <pieterh>  0. Your freedom depends on easy network programming
| [Thursday 12 August 2010] [06:35:27] <pieterh>  2. Your kernel is the best way to get this to the whole world
| [Thursday 12 August 2010] [06:35:27] <sustrik>  2. Here's how it grows to ludicrous scales
| [Thursday 12 August 2010] [06:35:54] <pieterh>  you can point out that in 5 years' time Linux will be the only kernel
| [Thursday 12 August 2010] [06:35:59] <sustrik>  :)
| [Thursday 12 August 2010] [06:36:38] <pieterh>  this is the structure i'd use, to do evangelizing
| [Thursday 12 August 2010] [06:36:53] <pieterh>  0. dystopia, unless...
| [Thursday 12 August 2010] [06:36:53] <sustrik>  sure, why not
| [Thursday 12 August 2010] [06:36:59] <pieterh>  1. perfect solution, look
| [Thursday 12 August 2010] [06:37:06] <pieterh>  2. we need you to make this happen
| [Thursday 12 August 2010] [06:37:12] <sustrik>  yes, can be
| [Thursday 12 August 2010] [06:37:24] <sustrik>  still, what should be the example
| [Thursday 12 August 2010] [06:37:40] <sustrik>  i still like the social networking thing
| [Thursday 12 August 2010] [06:37:42] <pieterh>  you can simply list centralized examples
| [Thursday 12 August 2010] [06:37:45] <pieterh>  and distributed examples
| [Thursday 12 August 2010] [06:37:49] <pieterh>  these are smart people
| [Thursday 12 August 2010] [06:37:53] <sustrik>  i can explicitly NOT mention facebook and diaspora
| [Thursday 12 August 2010] [06:37:59] <sustrik>  if we want ot keep it neutral
| [Thursday 12 August 2010] [06:38:06] <pieterh>  centralized development practices vs. linux kernel process
| [Thursday 12 August 2010] [06:38:16] <pieterh>  centralized mobile phone networks vs. VoIP
| [Thursday 12 August 2010] [06:38:26] <sustrik>  sure, the question is how that maps to 0mq
| [Thursday 12 August 2010] [06:38:31] <pieterh>  doesn't matter
| [Thursday 12 August 2010] [06:38:35] <sustrik>  just listing examples won't do
| [Thursday 12 August 2010] [06:38:43] <jsimmons> just drop the speech, put your desktop on the big screen and implement a massively scalable example x in the few minutes you have, then have everybody in the room grab it and make a ad-hoc distributed network that does something cool. finish with a quick speech about why it should be in the kernel. :)
| [Thursday 12 August 2010] [06:38:44] <pieterh>  doesn't have to map directly
| [Thursday 12 August 2010] [06:38:59] <pieterh>  one level of abstraction will work fine
| [Thursday 12 August 2010] [06:39:03] <sustrik>  jsimmons: :)
| [Thursday 12 August 2010] [06:39:24] <pieterh>  everyone there is wondering, as you give examples, "yes, yes, yes but how can I make distributed systems?"
| [Thursday 12 August 2010] [06:39:40] <pieterh>  which you answer right afterwards
| [Thursday 12 August 2010] [06:39:51] <sustrik>  what would be the answer?
| [Thursday 12 August 2010] [06:40:00] <pieterh>  5-line python example
| [Thursday 12 August 2010] [06:40:00] <sustrik>  showing a client/server example is not exactly it
| [Thursday 12 August 2010] [06:40:04] <pieterh>  yes it's fine
| [Thursday 12 August 2010] [06:40:10] <jsimmons> To me if I were going to talk to kernel developers I'd be taking codes. and they'd better be good ones too.
| [Thursday 12 August 2010] [06:40:12] <sustrik>  that's what people call "centralised"
| [Thursday 12 August 2010] [06:40:35] <pieterh>  you need to clearly explain that the only reason for centralization
| [Thursday 12 August 2010] [06:40:42] <pieterh>  is the high cost of doing network programming
| [Thursday 12 August 2010] [06:40:46] <pieterh>  if that is lower
| [Thursday 12 August 2010] [06:40:51] <sustrik>  what's missing is the idea of interjecting devices in the middle
| [Thursday 12 August 2010] [06:40:54] <pieterh>  decentralization is inevitable
| [Thursday 12 August 2010] [06:41:04] <pieterh>  i don't agree you need to speak of scale
| [Thursday 12 August 2010] [06:41:16] <pieterh>  devices, etc. who cares
| [Thursday 12 August 2010] [06:41:22] <pieterh>  :-)
| [Thursday 12 August 2010] [06:41:24] <mato> wrong
| [Thursday 12 August 2010] [06:41:29] <sustrik>  agreed
| [Thursday 12 August 2010] [06:41:33] <pieterh>  don't talk about your technology
| [Thursday 12 August 2010] [06:41:33] <mato> that's the *major* point
| [Thursday 12 August 2010] [06:41:39] <mato> that's the *major* point
| [Thursday 12 August 2010] [06:41:39] <mato> that's the *major* point
| [Thursday 12 August 2010] [06:41:42] <mato> :-)
| [Thursday 12 August 2010] [06:41:43] <pieterh>  you think it is
| [Thursday 12 August 2010] [06:41:46] <pieterh>  i disagree
| [Thursday 12 August 2010] [06:41:52] <pieterh>  you can't jump from Eben'
| [Thursday 12 August 2010] [06:41:58] <pieterh>  Eben's speech to devices in 1 hour
| [Thursday 12 August 2010] [06:42:10] <pieterh>  you will lose them
| [Thursday 12 August 2010] [06:42:15] <sustrik>  you don't have to go into detail
| [Thursday 12 August 2010] [06:42:30] <pieterh>  this is detail
| [Thursday 12 August 2010] [06:42:35] <pieterh>  that's my view, anyhow
| [Thursday 12 August 2010] [06:42:39] <sustrik>  but it should be clear that 0mq can be used to produce distributed systems
| [Thursday 12 August 2010] [06:42:47] <pieterh>  45 minutes goes by *really quickly*
| [Thursday 12 August 2010] [06:42:57] <sustrik>  if the only thing you show is client/server, you haven't proven your point
| [Thursday 12 August 2010] [06:43:01] <sustrik>  i know
| [Thursday 12 August 2010] [06:43:13] <pieterh>  you can show something like this, hang on...
| [Thursday 12 August 2010] [06:43:22] <sustrik>  diagrams maybe
| [Thursday 12 August 2010] [06:43:27] <pieterh>  http://www.zeromq.org/docs:user-guide#toc24
| [Thursday 12 August 2010] [06:43:36] <pieterh>  it's still a trivial code example
| [Thursday 12 August 2010] [06:43:41] <pieterh>  but shows scale
| [Thursday 12 August 2010] [06:43:45] <sustrik>  yes, distribution tree
| [Thursday 12 August 2010] [06:44:03] <pieterh>  but don't go into theories of dumb networks and smart endpoints etc.
| [Thursday 12 August 2010] [06:44:06] <sustrik>  that's good but should be shown in the context of an example
| [Thursday 12 August 2010] [06:44:13] <pieterh>  yes
| [Thursday 12 August 2010] [06:44:23] <pieterh>  data distribution by itself is a very important use case
| [Thursday 12 August 2010] [06:44:29] <sustrik>  say decentralised social networking
| [Thursday 12 August 2010] [06:44:31] <pieterh>  forget request-reply
| [Thursday 12 August 2010] [06:44:34] <pieterh>  right
| [Thursday 12 August 2010] [06:44:35] <pieterh>  updates
| [Thursday 12 August 2010] [06:44:36] <sustrik>  the box on the top is you
| [Thursday 12 August 2010] [06:44:39] <pieterh>  sure
| [Thursday 12 August 2010] [06:44:48] <sustrik>  the boxes in the bottom are your friends
| [Thursday 12 August 2010] [06:44:49] <jsimmons> I presume everyone will have computers?
| [Thursday 12 August 2010] [06:44:53] <pieterh>  ok, i have it
| [Thursday 12 August 2010] [06:44:54] <pieterh>  :-)
| [Thursday 12 August 2010] [06:44:57] <sustrik>  the boxes in the middle are groups
| [Thursday 12 August 2010] [06:44:59] <pieterh>  you can make this live
| [Thursday 12 August 2010] [06:45:04] <pieterh>  you'll like this
| [Thursday 12 August 2010] [06:45:05] <sustrik>  jsimmons: no idea
| [Thursday 12 August 2010] [06:45:05] <pieterh>  decentralized twitter
| [Thursday 12 August 2010] [06:45:23] <pieterh>  push updates to all
| [Thursday 12 August 2010] [06:45:32] <pieterh>  subscribe to anyone
| [Thursday 12 August 2010] [06:45:39] <sustrik>  no central authority
| [Thursday 12 August 2010] [06:45:40] <pieterh>  i'm going to use this as the example in the Guide
| [Thursday 12 August 2010] [06:45:46] <pieterh>  no more fail whale
| [Thursday 12 August 2010] [06:45:54] <sustrik>  actualy yes, twitter is even better than facebook
| [Thursday 12 August 2010] [06:45:57] <sustrik>  as it is simpler
| [Thursday 12 August 2010] [06:46:00] <pieterh>  yup cause it's a pure push
| [Thursday 12 August 2010] [06:46:11] <jsimmons> what's the free twitter :)
| [Thursday 12 August 2010] [06:46:16] <pieterh>  fritter?
| [Thursday 12 August 2010] [06:46:28] <sustrik>  :)
| [Thursday 12 August 2010] [06:46:30] <mato> pieterh: people have already implemented this, look at the ostatus/statusnet/identi.ca crowd
| [Thursday 12 August 2010] [06:46:37] <jsimmons> sustrik, find out, I'd presume so. If you could whip up a sample that everyone can compile real quick and instantly become part of a distributed network
| [Thursday 12 August 2010] [06:46:50] <pieterh>  mato: yes, but not in 10 lines of python
| [Thursday 12 August 2010] [06:47:14] <mato> pieterh: sure, i'm just pointing out that it exists, and taking that into account is useful
| [Thursday 12 August 2010] [06:47:18] <sustrik>  jsimmons: not enough time for that i think
| [Thursday 12 August 2010] [06:47:35] <pieterh>  sustrik: just describe it and show one chart
| [Thursday 12 August 2010] [06:47:38] <mato> pieterh: "here's a quick reimplementation of statusnet in 10 lines of python" :-)
| [Thursday 12 August 2010] [06:47:41] <pieterh>  that'll prove the point
| [Thursday 12 August 2010] [06:47:43] <pieterh>  mato: sure
| [Thursday 12 August 2010] [06:47:52] <pieterh>  except i have no idea what statusnet is
| [Thursday 12 August 2010] [06:48:07] <mato> pieterh: open source and decentralized twitter afaik
| [Thursday 12 August 2010] [06:48:09] <sustrik>  distributed trwitter i assume :)
| [Thursday 12 August 2010] [06:48:21] <pieterh>  sure
| [Thursday 12 August 2010] [06:48:32] <mato> see, /me is a database :-)
| [Thursday 12 August 2010] [06:48:33] <sustrik>  ok, can you write that down?
| [Thursday 12 August 2010] [06:48:44] <pieterh>  sustrik: you speaking to me?
| [Thursday 12 August 2010] [06:48:47] <sustrik>  yes
| [Thursday 12 August 2010] [06:48:55] <pieterh>  "that" is the structure?
| [Thursday 12 August 2010] [06:48:58] <pieterh>  ok
| [Thursday 12 August 2010] [06:49:06] <sustrik>  i mean the text
| [Thursday 12 August 2010] [06:49:14] <sustrik>  moglen/twitter thing
| [Thursday 12 August 2010] [06:49:33] <pieterh>  ok... i'll give it a shot
| [Thursday 12 August 2010] [06:49:43] <mato> sustrik, pieterh: i think you should mention at least in passing that 0mq is also applicable to a distributed facebook
| [Thursday 12 August 2010] [06:49:47] <sustrik>  thanks, you'll help me tremendously
| [Thursday 12 August 2010] [06:49:54] <mato> no detail, but worth mentioning
| [Thursday 12 August 2010] [06:50:01] <sustrik>  i can do that, np
| [Thursday 12 August 2010] [06:50:56] <mato> hmm
| [Thursday 12 August 2010] [06:51:02] <pieterh>  sustrik: what I will do is expand the text i already wrote into what feels workable for 45 minutes of talking, ok?
| [Thursday 12 August 2010] [06:51:19] <mato> another interesting example would be a modern reimplementation of irc
| [Thursday 12 August 2010] [06:51:22] <mato> using 0mq
| [Thursday 12 August 2010] [06:51:27] <jsimmons> If you had a python script hosted on your machine, ready to go and you just publish your ip at the start. only problem is they might be too interested in that to listen to you :)
| [Thursday 12 August 2010] [06:51:39] <mato> since irc is inherently both peer to peer and distributed, and has the concept of intermediate servers afaik
| [Thursday 12 August 2010] [06:51:41] <pieterh>  mato: indeed, but this is about cutting down, not adding more
| [Thursday 12 August 2010] [06:51:44] <mato> i.e. devices
| [Thursday 12 August 2010] [06:51:51] <mato> pieterh: sure, i'm just thinking aloud
| [Thursday 12 August 2010] [06:51:53] <sustrik>  pieterh: slightly less
| [Thursday 12 August 2010] [06:52:06] <sustrik>  time for Q & A should be allowed
| [Thursday 12 August 2010] [06:52:19] <mato> pieterh: /me makes a note in database (self) to think about a "irc over 0mq" example
| [Thursday 12 August 2010] [06:52:22] <pieterh>  sustrik: yes, ok, 30 mins but please do not read the text aloud!
| [Thursday 12 August 2010] [06:52:26] <pieterh>  :-)
| [Thursday 12 August 2010] [06:52:30] <mato> pieterh: with the whole hog including devices and the p2p bits
| [Thursday 12 August 2010] [06:52:59] <pieterh>  mato: i think there are some killer 0mq applications waiting to be born
| [Thursday 12 August 2010] [06:53:03] <sustrik>  pieterh: no, i am improvising when speaking
| [Thursday 12 August 2010] [06:53:12] <sustrik>  but i need something to publish in proceedings
| [Thursday 12 August 2010] [06:53:17] <pieterh>  sustrik: excellent, this'll work
| [Thursday 12 August 2010] [06:53:33] <pieterh>  i have to write some code first, will work on the text later
| [Thursday 12 August 2010] [06:53:53] <pieterh>  it is a busy weekend and my wife is going to go to hospital at any moment to have our baby
| [Thursday 12 August 2010] [06:53:53] <sustrik>  jsimmons: yes, that's the problem, it's hard to convey the message in 30 mins even if people are not busy compiling stuff
| [Thursday 12 August 2010] [06:54:26] <sustrik>  are you able to make it till 15th?
| [Thursday 12 August 2010] [06:54:35] <sustrik>  if not, i'll do it myself
| [Thursday 12 August 2010] [06:55:03] <pieterh>  15th, yeah, today probably
| [Thursday 12 August 2010] [06:55:22] <pieterh>  at least an outline, there are parts you'll want to add
| [Thursday 12 August 2010] [06:55:32] <sustrik>  ok, great, thanks
| [Thursday 12 August 2010] [06:55:43] <pieterh>  thank me when its done :-)
| [Thursday 12 August 2010] [06:55:49] <sustrik>  ok
| [Thursday 12 August 2010] [07:51:29]     * pieterh feels really stupid, just realized what diaspora is
| [Thursday 12 August 2010] [08:01:29] <AndrewBC> heh
| [Thursday 12 August 2010] [08:59:26] <pieterh>  sustrik: i have a really good example
| [Thursday 12 August 2010] [09:04:16] <CIA-20>   zeromq2: 03Martin Sustrik 07wip-shutdown * r28c8b5b 10/ (8 files): one more dezombification bug fixed - http://bit.ly/bkK0xS
| [Thursday 12 August 2010] [09:04:28] <sustrik>  pieterh: shoot
| [Thursday 12 August 2010] [09:04:34] <pieterh>  well... email
| [Thursday 12 August 2010] [09:04:47] <pieterh>  essentially distributed, and successful as such
| [Thursday 12 August 2010] [09:04:52] <pieterh>  slowly being replaced by gmail
| [Thursday 12 August 2010] [09:05:05] <pieterh>  i have an explanation why
| [Thursday 12 August 2010] [09:05:09] <sustrik>  ?
| [Thursday 12 August 2010] [09:05:14] <pieterh>  which is taken from one of my books in progress
| [Thursday 12 August 2010] [09:05:28] <pieterh>  basically gmail is a mediocre client
| [Thursday 12 August 2010] [09:05:37]     * mato senses pieterh theory of the world #1752 coming up 
| [Thursday 12 August 2010] [09:05:52] <pieterh>  mato: just put away the knee-jerk reaction for a second
| [Thursday 12 August 2010] [09:06:02] <mato> trolled!
| [Thursday 12 August 2010] [09:06:03] <pieterh>  gmail solves the most vital problem for (normal) users
| [Thursday 12 August 2010] [09:06:06] <pieterh>  that is, spam
| [Thursday 12 August 2010] [09:06:17] <pieterh>  how it does that is by sharing knowledge of "this is spam"
| [Thursday 12 August 2010] [09:06:27] <pieterh>  20 people mark a message as spam, 20M never see it
| [Thursday 12 August 2010] [09:06:38] <pieterh>  now in theory you COULD do that for distributed email
| [Thursday 12 August 2010] [09:06:45] <pieterh>  people have kind of... tried... but failed
| [Thursday 12 August 2010] [09:06:54] <pieterh>  it requires massive distribution of data
| [Thursday 12 August 2010] [09:07:06] <pieterh>  and really rapidly, no point it arriving after people already got the spam
| [Thursday 12 August 2010] [09:07:21] <sustrik>  pieterh: it's not an uncontroversial example
| [Thursday 12 August 2010] [09:07:24] <pieterh>  "high cost of writing connected code" makes it practically impossible to solve problems
| [Thursday 12 August 2010] [09:07:34] <pieterh>  that centralized systems can solve trivially
| [Thursday 12 August 2010] [09:07:34] <sustrik>  what we need is somethig obvious
| [Thursday 12 August 2010] [09:07:42] <pieterh>  why is this controversial?
| [Thursday 12 August 2010] [09:07:44] <mato> pieterh: i think you're very wrong about gmail and spam
| [Thursday 12 August 2010] [09:07:52] <pieterh>  mato: you don't use gmail, do you
| [Thursday 12 August 2010] [09:07:56] <mato> pieterh: tell me if you're interested in why...
| [Thursday 12 August 2010] [09:08:06] <sustrik>  people have to think about, then they can either agree or disagree
| [Thursday 12 August 2010] [09:08:08] <mato> pieterh: i don't use gmail for other reasons
| [Thursday 12 August 2010] [09:08:18] <pieterh>  mato: no, i'm interested in examples that compare distributed vs. centralized services
| [Thursday 12 August 2010] [09:08:18] <sustrik>  that takes valuable time
| [Thursday 12 August 2010] [09:08:24] <mato> pieterh: but i believe there are several flaws in your hypothesis
| [Thursday 12 August 2010] [09:08:31] <mato> pieterh: about spam & gmail
| [Thursday 12 August 2010] [09:08:36] <sustrik>  what we need is something that people just say: "ah, ok"
| [Thursday 12 August 2010] [09:09:21] <mato> pieterh: anyway, i'm happy to expand on why exactly if you're interested
| [Thursday 12 August 2010] [09:09:23] <pieterh>  i'm listening to suggestions of distributed vs. centralized services where cost of messaging is the differentiating factor
| [Thursday 12 August 2010] [09:09:44] <pieterh>  mato: you don't use gmail so it's like a virgin discussing sex
| [Thursday 12 August 2010] [09:09:54] <pieterh>  fun to watch but not useful at this stage
| [Thursday 12 August 2010] [09:09:55] <pieterh>  sorry
| [Thursday 12 August 2010] [09:10:07] <sustrik>  the cost is irrelevant to the topic imo
| [Thursday 12 August 2010] [09:10:17] <sustrik>  what's needed is an obvious example
| [Thursday 12 August 2010] [09:10:22] <pieterh>  sustrik: cost of messaging is the key factor
| [Thursday 12 August 2010] [09:10:34] <pieterh>  people do want to build distributed systems but can't
| [Thursday 12 August 2010] [09:10:36] <pieterh>  IMO
| [Thursday 12 August 2010] [09:10:37] <sustrik>  i am trying to explain not sell
| [Thursday 12 August 2010] [09:10:43] <pieterh>  ok, whatever
| [Thursday 12 August 2010] [09:10:45] <AndrewBC> I tried to set up email on my server once
| [Thursday 12 August 2010] [09:10:55] <pieterh>  i'll continue my text, do what you like with it afterwards
| [Thursday 12 August 2010] [09:10:57] <mato> pieterh: right, i will go fuck off then, seeing as you're obviously not interested in my opinion
| [Thursday 12 August 2010] [09:10:58]     * AndrewBC uses gmail
| [Thursday 12 August 2010] [09:11:01] <pieterh>  mato: trolled! :-)
| [Thursday 12 August 2010] [09:11:04] <pieterh>  lol
| [Thursday 12 August 2010] [09:11:19] <mato> 1:1
| [Thursday 12 August 2010] [09:11:26] <pieterh>  yo mama
| [Thursday 12 August 2010] [09:11:30] <pieterh>  ok, tell me
| [Thursday 12 August 2010] [09:12:33] <mato> ok, first, i've yet to see anyone claim that spam can be solved with distributed automation using a single corpus
| [Thursday 12 August 2010] [09:12:45] <mato> maybe this is what google are doing, maybe not
| [Thursday 12 August 2010] [09:13:01] <mato> having said that, spam is a mostly solved problem without that anyway
| [Thursday 12 August 2010] [09:13:21] <mato> i have been using a spam filter (CRM114 specifically) on all my mail for years now
| [Thursday 12 August 2010] [09:13:44] <mato> you train it more or less efortlessly and it works
| [Thursday 12 August 2010] [09:13:46] <pieterh>  i recall endless (endless!) problems with spam before moving to gmail and letting it handle all my email
| [Thursday 12 August 2010] [09:14:05] <mato> sure, because you didn't choose the right tool
| [Thursday 12 August 2010] [09:14:16] <mato> i tried various things, picked this one, it worked
| [Thursday 12 August 2010] [09:14:18] <pieterh>  that kind of proves my point
| [Thursday 12 August 2010] [09:14:23] <AndrewBC> This is why users choose gmail instead of doing it themselves.
| [Thursday 12 August 2010] [09:14:27] <AndrewBC> The pains of doing it right.
| [Thursday 12 August 2010] [09:14:33] <pieterh>  i don't have time, almost no-one does, to become an expert in "tools" just to use email
| [Thursday 12 August 2010] [09:14:44] <pieterh>  you represent a very select part of a very select elite
| [Thursday 12 August 2010] [09:15:02] <mato> yes, sure, it's one of the reasons
| [Thursday 12 August 2010] [09:15:06] <pieterh>  my thesis is that requiring people to find and use those tools is a failure
| [Thursday 12 August 2010] [09:15:17] <mato> of course
| [Thursday 12 August 2010] [09:15:18] <pieterh>  and Google's trick is to share the corpus
| [Thursday 12 August 2010] [09:15:24] <AndrewBC> Writing a whole thesis on that? :)
| [Thursday 12 August 2010] [09:15:27] <pieterh>  and that can be done except messaging is too expensive
| [Thursday 12 August 2010] [09:15:38] <pieterh>  AndrewBC: I was writing a book...
| [Thursday 12 August 2010] [09:15:39] <mato> so you think yahoo, hotmail, etc do not share the corpus?
| [Thursday 12 August 2010] [09:15:40] <pieterh>  one of several...
| [Thursday 12 August 2010] [09:15:55] <pieterh>  mato: they did not do this as well, Google used their experience from search
| [Thursday 12 August 2010] [09:16:02] <mato> pieterh: the point i'm trying to make is that gmail is not that special, at least not for spam
| [Thursday 12 August 2010] [09:16:15] <mato> there's something else which in my opinion makes it special
| [Thursday 12 August 2010] [09:16:18] <AndrewBC> pieterh, oh you were serious. Add a couple of degrees of incredulity to my original question then. :P
| [Thursday 12 August 2010] [09:16:39] <pieterh>  AndrewBC: it's half a page in a book of 250 pages...
| [Thursday 12 August 2010] [09:16:39]     * AndrewBC is just kidding, though.
| [Thursday 12 August 2010] [09:16:40] <mato> which is, search, and through search the use of email as a database :-)
| [Thursday 12 August 2010] [09:16:49] <pieterh>  mato: yes, indeed, you are right
| [Thursday 12 August 2010] [09:16:55] <AndrewBC> Oh see, now you've gone and ruined all my fun
| [Thursday 12 August 2010] [09:17:25] <pieterh>  AndrewBC: fun, you want fun?  Down the hall, room 5b
| [Thursday 12 August 2010] [09:17:26] <mato> pieterh: and that search has nothing to do with distributed systems really
| [Thursday 12 August 2010] [09:17:38] <pieterh>  mato: i agree
| [Thursday 12 August 2010] [09:17:42] <AndrewBC> I have a feeling that I'm in for an argument
| [Thursday 12 August 2010] [09:17:59] <pieterh>  AndrewBC: no, this is insults.  arguments are up in 11c
| [Thursday 12 August 2010] [09:18:08] <AndrewBC> Oh, okay. :D
| [Thursday 12 August 2010] [09:18:17] <jsimmons> and in gmail where you have a centralised client. as opposed to email's annoying decentralised model, as far as client<>server goes anyway.
| [Thursday 12 August 2010] [09:18:35] <pieterh>  mato: point taken, i shall have lunch and reflect on this
| [Thursday 12 August 2010] [09:18:59] <mato> yes... lunch...
| [Thursday 12 August 2010] [09:19:18] <jsimmons> although I'm really just talking about POP, IMAP has other issues
| [Thursday 12 August 2010] [09:19:31] <pieterh>  well apart from searching, spam filtering, huge mailboxes, labels, no fuss, what has Gmail EVER DONE FOR US?
| [Thursday 12 August 2010] [09:19:35] <pieterh>  it's a serious question :-)
| [Thursday 12 August 2010] [09:19:39] <mato> pieterh: i would also be very interested to actually hear someone from google say if they do use the distributed method for flagging spam
| [Thursday 12 August 2010] [09:19:53] <pieterh>  mato: trade secrets, i'm almost certain
| [Thursday 12 August 2010] [09:20:04] <pieterh>  and it's not distributed, really
| [Thursday 12 August 2010] [09:20:10] <jsimmons> gmail android pieterh. best mobile email client eva
| [Thursday 12 August 2010] [09:20:19] <AndrewBC> I hope they do, because I'm such a good spam tagger
| [Thursday 12 August 2010] [09:20:25] <jsimmons> now with copy+paste!
| [Thursday 12 August 2010] [09:20:28] <pieterh>  :-)
| [Thursday 12 August 2010] [09:20:45] <jsimmons> I don't get any spam to tag :(
| [Thursday 12 August 2010] [09:20:56] <AndrewBC> Haha, sucker.
| [Thursday 12 August 2010] [09:21:03] <AndrewBC> Wait.. that's not right.
| [Thursday 12 August 2010] [09:21:07]     * mato keeps all his tagged spam to himself, suckers :-)
| [Thursday 12 August 2010] [09:21:26] <mato> mine. all mine. :-)
| [Thursday 12 August 2010] [09:21:28] <jsimmons> only cus you keep the details so you can get cheap viagra on the down low
| [Thursday 12 August 2010] [09:21:46] <AndrewBC> farming the pharma
| [Thursday 12 August 2010] [09:21:52] <mato> :-)
| [Thursday 12 August 2010] [09:23:15] <sustrik>  mato: wip-shutdown
| [Thursday 12 August 2010] [09:23:23] <mato> sustrik: jaaa?
| [Thursday 12 August 2010] [09:23:28] <sustrik>  it's in the state where termination is delayed till messages are sent
| [Thursday 12 August 2010] [09:23:34] <sustrik>  then it fails or freezes :)
| [Thursday 12 August 2010] [09:23:51] <sustrik>  but at least the basic thing looks workign
| [Thursday 12 August 2010] [09:24:24] <mato> goody good
| [Thursday 12 August 2010] [09:24:31] <mato> so needs lots of testing, right?
| [Thursday 12 August 2010] [09:24:44] <sustrik>  yes, the code is completely rewritten
| [Thursday 12 August 2010] [09:24:55] <mato> ok
| [Thursday 12 August 2010] [09:25:05] <mato> sustrik: unlikely i will get to it before next week
| [Thursday 12 August 2010] [09:25:12] <sustrik>  sure, no haste
| [Thursday 12 August 2010] [09:25:13] <mato> sustrik: i have to deliver this c++ thingy by tomorrow
| [Thursday 12 August 2010] [09:25:17] <sustrik>  np
| [Thursday 12 August 2010] [09:25:57] <mato> sustrik: so, next week i can do some basic testing
| [Thursday 12 August 2010] [09:26:06] <mato> sustrik: i'd also like to announce that work on the list
| [Thursday 12 August 2010] [09:26:14] <mato> sustrik: and make it destined for 2.1
| [Thursday 12 August 2010] [09:26:33] <mato> sustrik: that's if you agree...
| [Thursday 12 August 2010] [09:27:33] <sustrik>  yes, sure, i do
| [Thursday 12 August 2010] [09:42:43] <pieterh_lunch>    ok, mato
| [Thursday 12 August 2010] [09:43:07] <pieterh>  why do people tend to build centralized services?
| [Thursday 12 August 2010] [09:43:52] <mato> pieterh: well, for search the answer is it's a hard problem which we don't know how to decentralize well
| [Thursday 12 August 2010] [09:44:16] <mato> pieterh: (search == web search)
| [Thursday 12 August 2010] [09:44:32] <pieterh>  yes, search
| [Thursday 12 August 2010] [09:44:47] <pieterh>  but why in general do people tend to build centralized services?
| [Thursday 12 August 2010] [09:44:56] <mato> control? power? profit?
| [Thursday 12 August 2010] [09:44:58] <mato> tell me...
| [Thursday 12 August 2010] [09:45:12] <pieterh>  part is the control instinct
| [Thursday 12 August 2010] [09:45:23] <pieterh>  the movie industry is highly centralized
| [Thursday 12 August 2010] [09:45:30] <pieterh>  so that people can control distribution
| [Thursday 12 August 2010] [09:45:39] <pieterh>  the fashion industry is highly decentralized
| [Thursday 12 August 2010] [09:45:42] <pieterh>  it's 4x larger
| [Thursday 12 August 2010] [09:45:56] <pieterh>  part is the simplicity of a star network
| [Thursday 12 August 2010] [09:46:06] <pieterh>  conceptually, much easier to grok
| [Thursday 12 August 2010] [09:46:24] <pieterh>  skype is hard to understand as p2p, easy as centralized service
| [Thursday 12 August 2010] [09:46:43] <mato> for the end user, yes...
| [Thursday 12 August 2010] [09:46:48] <pieterh>  you go somewhere for data, data does not come to you
| [Thursday 12 August 2010] [09:47:01] <pieterh>  but i think the reason is even more stupid than that
| [Thursday 12 August 2010] [09:47:11] <pieterh>  here's the results of my lunch rumination
| [Thursday 12 August 2010] [09:47:39] <pieterh>  - it is really hard to build a working communications stack
| [Thursday 12 August 2010] [09:48:02] <pieterh>  - the only one that kind of worked widely, by the 90s as we got all that network capacity was HTTP
| [Thursday 12 August 2010] [09:48:15] <pieterh>  - therefore every programmer reaches for HTTP as their first choice
| [Thursday 12 August 2010] [09:48:23] <mato> um, IP, surely?
| [Thursday 12 August 2010] [09:48:34] <pieterh>  no-one programs IP and it's not a stack
| [Thursday 12 August 2010] [09:48:41] <mato> huh?
| [Thursday 12 August 2010] [09:48:45] <pieterh>  - therefore every architect thinks in terms of HTTP and centralized services
| [Thursday 12 August 2010] [09:48:58]     * pieterh searches for IP library for Python
| [Thursday 12 August 2010] [09:49:06] <soren>    python-ipy
| [Thursday 12 August 2010] [09:49:06] <mato> pieterh: it's called "sockets" :-)
| [Thursday 12 August 2010] [09:49:15] <pieterh>  exactly
| [Thursday 12 August 2010] [09:49:22] <pieterh>  its a real pain to use sockets in anger
| [Thursday 12 August 2010] [09:49:33] <soren>    Oh, that sort of IP library. Not python-ipy then :)
| [Thursday 12 August 2010] [09:49:35] <pieterh>  thus a $bn messaging middleware industry
| [Thursday 12 August 2010] [09:49:46] <pieterh>  we know the list of problems you have to solve
| [Thursday 12 August 2010] [09:49:51] <pieterh>  it's endless and horrible
| [Thursday 12 August 2010] [09:49:56] <pieterh>  ja? 
| [Thursday 12 August 2010] [09:50:02] <mato> more or less
| [Thursday 12 August 2010] [09:50:09] <pieterh>  thus, people reach for what works
| [Thursday 12 August 2010] [09:50:22] <pieterh>  SOAP, XMLrpc, etc.
| [Thursday 12 August 2010] [09:50:25] <mato> yes, of course
| [Thursday 12 August 2010] [09:50:32] <pieterh>  which leads them all to centralized services
| [Thursday 12 August 2010] [09:50:33] <mato> it's always easier to take something that "mostly works"
| [Thursday 12 August 2010] [09:50:36] <pieterh>  yes
| [Thursday 12 August 2010] [09:50:49] <pieterh>  so i see 0MQ as the antidote to HTTP
| [Thursday 12 August 2010] [09:51:04] <mato> interesting line of thought...
| [Thursday 12 August 2010] [09:51:05] <mato> yes.
| [Thursday 12 August 2010] [09:51:07] <mato> i like it
| [Thursday 12 August 2010] [09:51:12] <pieterh>  HTTP as level7 stack is toxic to humanity
| [Thursday 12 August 2010] [09:51:13] <pieterh>  ok
| [Thursday 12 August 2010] [09:51:35] <mato> sustrik: you reading this? pieterh has a nice point
| [Thursday 12 August 2010] [09:51:57] <pieterh>  the contrast is nice: sync vs. async, patterns, knowledge in centre vs. edges, etc.
| [Thursday 12 August 2010] [09:52:22] <mato> of course it's all blue-sky future, but the point is 0MQ *could* be the antidote to all this use of HTTP-as-universal-messaging
| [Thursday 12 August 2010] [09:52:28] <pieterh>  yes, that's it
| [Thursday 12 August 2010] [09:52:36] <pieterh>  i don't see a conspiracy to create facebook
| [Thursday 12 August 2010] [09:52:50] <pieterh>  its just been easier up to now
| [Thursday 12 August 2010] [09:53:08] <pieterh>  ok, me needs coffee now
| [Thursday 12 August 2010] [09:53:23] <mato> well, actually, there is... since the gravy train is more obvious with a centralized facebook
| [Thursday 12 August 2010] [09:53:38] <mato> versus eben moglen's wall-wart distributed server thingy
| [Thursday 12 August 2010] [09:54:24] <mato> i wouldn't go so far to call it a conspiracy, it's just the plain old capitalist profit motive
| [Thursday 12 August 2010] [09:54:51] <mato> 1.5 billion users using centralized facebook == obvious $$$$$$
| [Thursday 12 August 2010] [09:55:15] <pieterh>  mato: that ignores my example that distributed systems are worth many more $$$$$$
| [Thursday 12 August 2010] [09:55:45] <mato> pieterh: maybe, yes, i'm just comparing the facebook example
| [Thursday 12 August 2010] [09:56:02] <pieterh>  if we want to position 0MQ as "internet scale messaging" it's nice to consider that we have two internets
| [Thursday 12 August 2010] [09:56:11] <pieterh>  like two parallel realities or futures
| [Thursday 12 August 2010] [09:56:19] <pieterh>  one, centralized.  two, distributed.
| [Thursday 12 August 2010] [09:56:24] <pieterh>  one, HTTP. two, 0MQ.
| [Thursday 12 August 2010] [09:56:44] <pieterh>  and that is why 0MQ MUST go into the Kernel! 
| [Thursday 12 August 2010] [09:56:46] <pieterh>  :-)
| [Thursday 12 August 2010] [09:56:54] <mato> :-)
| [Thursday 12 August 2010] [09:57:35] <mato> pieterh: ok, back to work, /me wants to get this $%#^%# c++ working
| [Thursday 12 August 2010] [09:57:40] <mato> almost there...
| [Thursday 12 August 2010] [09:57:51] <pieterh>  ack
| [Thursday 12 August 2010] [09:57:55] <pieterh>  thanks btw
| [Thursday 12 August 2010] [09:58:08] <mato> np
| [Thursday 12 August 2010] [09:58:18] <cremes>   any word from the ietf guys on websocket framing?
| [Thursday 12 August 2010] [09:59:04] <pieterh>  cremes: discussion paused, but i think the "consensus" is at a 0MQ-style frame
| [Thursday 12 August 2010] [09:59:20] <cremes>   good to hear
| [Thursday 12 August 2010] [09:59:42] <cremes>   at some point i would like to be able to use 0mq from the browser
| [Thursday 12 August 2010] [09:59:58] <pieterh>  yes, it would be good to tunnel over websockets
| [Thursday 12 August 2010] [09:59:59] <cremes>   similar framing will only make that easier i would think
| [Thursday 12 August 2010] [10:00:02] <pieterh>  indeed
| [Thursday 12 August 2010] [10:00:21] <cremes>   are you aware of any 0mq javascript projects?
| [Thursday 12 August 2010] [10:00:28] <pieterh>  though i was thinking of a very simple way to bridge HTTP to 0MQ
| [Thursday 12 August 2010] [10:00:43] <cremes>   i haven't seen any here on irc or the ML, but you might know of some below-the-radar projects
| [Thursday 12 August 2010] [10:00:51] <pieterh>  i have a design
| [Thursday 12 August 2010] [10:00:55] <pieterh>  but no time to start on it
| [Thursday 12 August 2010] [10:01:02] <cremes>   heh
| [Thursday 12 August 2010] [10:01:10] <pieterh>  basically, AMQP stripped down to run as native HTTP
| [Thursday 12 August 2010] [10:01:20] <pieterh>  not even RESTful, just plain HTTP methods
| [Thursday 12 August 2010] [10:01:42] <pieterh>  request-reply, pubsub, pipeline
| [Thursday 12 August 2010] [10:01:48] <cremes>   right
| [Thursday 12 August 2010] [10:01:56] <pieterh>  it would not be 0MQ but it would feed smoothly into a 0MQ network
| [Thursday 12 August 2010] [10:02:02] <pieterh>  which is just as good IMO
| [Thursday 12 August 2010] [10:02:07] <pieterh>  plus you get all the benefits of HTTP
| [Thursday 12 August 2010] [10:02:12] <cremes>   you probably need a paying customer to find time for it... :)
| [Thursday 12 August 2010] [10:02:17] <pieterh>  yup
| [Thursday 12 August 2010] [10:02:19] <pieterh>  as usual
| [Thursday 12 August 2010] [10:02:34] <pieterh>  pure R&D is a waste of time, it produces things no-one uses
| [Thursday 12 August 2010] [10:03:02]     * cremes shakes his piggy bank again
| [Thursday 12 August 2010] [10:03:07] <pieterh>  lol
| [Thursday 12 August 2010] [10:04:28]     * cremes back to coding...
| [Thursday 12 August 2010] [11:02:02] <sustrik>  mato: yes, read it now
| [Thursday 12 August 2010] [11:02:06] <sustrik>  pieter is right
| [Thursday 12 August 2010] [11:02:13] <sustrik>  http is misused in terrible ways
| [Thursday 12 August 2010] [11:09:58] <dos000>   http is used as a transport protocol .. when it is an app protocol
| [Thursday 12 August 2010] [11:10:14] <dos000>   and a beautifully simple  app protocol 
| [Thursday 12 August 2010] [13:00:46] <moorooboorai> hello, this a good time and place to raise an issue on installing the erlang bindings?
| [Thursday 12 August 2010] [13:16:53] <cremes>   moorooboorai: i recommend you ask and see; it may be hours but if you stay in the channel you may eventually get a response from an erlang person
| [Thursday 12 August 2010] [13:17:26] <moorooboorai> hi cremes: thanks, I will take my time ;-)
| [Thursday 12 August 2010] [13:18:20] <moorooboorai> main problem: the installation instructions as described on http://www.zeromq.org/bindings:erlang don't work out
| [Thursday 12 August 2010] [13:19:05] <moorooboorai> the git-extracted sources don't include the ./configure - using autconf on it (running Ubuntu here) doesn't help either
| [Thursday 12 August 2010] [13:19:16] <cremes>   moorooboorai: try searching the ML for an answer too
| [Thursday 12 August 2010] [13:20:00] <moorooboorai> will do, but was kinda hoping for follow up on the 'running within 5 minutes' slogan...
| [Thursday 12 August 2010] [13:21:57] <cremes>   moorooboorai: heh, yeah... try it with the C, python or ruby bindings then :)
| [Thursday 12 August 2010] [13:23:26] <moorooboorai> yeah, right...that's not what I am after, of course..
| [Thursday 12 August 2010] [13:24:50] <moorooboorai> really a shame, though. Think Pieter's writing's are very convincing. Was coming from RabbitMQ/AMQP and found exactly the right words in Pieter's 'rant' on AMQP. I am sure my issue will just be a minor glitch.
| [Thursday 12 August 2010] [13:25:13] <sustrik>  pieterh, mato, all: here's a first shot on introduction: http://www.250bpm.com/hits
| [Thursday 12 August 2010] [13:26:08] <cremes>   moorooboorai: i took a look at the erlang bindings page; it notes that it requires a feature not present in the 2.0.7 release
| [Thursday 12 August 2010] [13:26:23] <cremes>   if you are trying to track master right now, then i'm not surprised the erlang bindings blow up
| [Thursday 12 August 2010] [13:26:45] <cremes>   master is undergoing a lot of changes right now and is probably moving faster than the erlang-bindings folks are tracking it
| [Thursday 12 August 2010] [13:27:01] <cremes>   that's one of the downsides of immature libraries, unfortunately
| [Thursday 12 August 2010] [13:27:49] <sustrik>  moorooboorai: as for now use sustrik/zeromq2 branch
| [Thursday 12 August 2010] [13:28:00] <sustrik>  it's kind of freezes on exit
| [Thursday 12 August 2010] [13:28:08] <sustrik>  but should be ok for prototyping
| [Thursday 12 August 2010] [13:28:28] <sustrik>  the whole thing is going to be settled down shortly
| [Thursday 12 August 2010] [13:30:28] <moorooboorai> Thanks, but I am using the sustrick/zeromq2 branch.
| [Thursday 12 August 2010] [13:30:37] <moorooboorai> As per the instructions.
| [Thursday 12 August 2010] [13:31:25] <sustrik>  ah
| [Thursday 12 August 2010] [13:31:29] <sustrik>  sorry, i've misread
| [Thursday 12 August 2010] [13:31:38] <sustrik>  you have to run ./autogen.sh first
| [Thursday 12 August 2010] [13:31:48] <sustrik>  that will generate the configure script
| [Thursday 12 August 2010] [13:32:38] <moorooboorai> okay, cloning again now
| [Thursday 12 August 2010] [13:34:15] <moorooboorai> Thanks! It's building now. Thinks the instructions could use some updates?
| [Thursday 12 August 2010] [13:34:48] <sustrik>  sure, if you find it confusing, fix the instructions
| [Thursday 12 August 2010] [13:34:57] <moorooboorai> Also for the part where the command "git git@github.com..." is used. It ends up with a permission denied.
| [Thursday 12 August 2010] [13:35:07] <sustrik>  :(
| [Thursday 12 August 2010] [13:35:19] <moorooboorai> Can I fix them? If so, then I will do that of course.
| [Thursday 12 August 2010] [13:35:24] <sustrik>  click join wiki button on the left bottom of the page
| [Thursday 12 August 2010] [13:35:35] <sustrik>  once you've joined you can edit documents
| [Thursday 12 August 2010] [13:44:09] <moorooboorai> have made the changes; if anything else pops up I will come back here
| [Thursday 12 August 2010] [13:44:16] <moorooboorai> Thanks for the help so far!
| [Thursday 12 August 2010] [13:44:48] <sustrik>  you are welcome
| [Thursday 12 August 2010] [15:09:54] <pieterh>  re
| [Thursday 12 August 2010] [15:11:01] <pieterh>  moorooboorai: thanks for fixing the Erlang page
| [Thursday 12 August 2010] [15:12:20] <pieterh>  sustrik: the introduction makes sense but it takes 2-3 readings to understand the point
| [Thursday 12 August 2010] [15:12:25] <pieterh>  maybe i'm just tired :-)
| [Thursday 12 August 2010] [15:15:48] <sustrik>  hm
| [Thursday 12 August 2010] [15:15:56] <sustrik>  what do you think is unclear?
| [Thursday 12 August 2010] [15:18:10] <sustrik>  i should probably state the point fists, then discuss it, then re-state it at the end
| [Thursday 12 August 2010] [15:27:04] <pieterh>  sustrik: your core argument is that distributed systems are more successful
| [Thursday 12 August 2010] [15:27:14] <pieterh>  this argument is easily disproven, unfortunately
| [Thursday 12 August 2010] [15:27:21] <pieterh>  at least superficially
| [Thursday 12 August 2010] [15:27:57] <sustrik>  ?
| [Thursday 12 August 2010] [15:28:00] <pieterh>  100% adoption of GSM (centralized), 100% adoption of centralized movie distribution, 90% adoption of Windows, 100% of Euro in Eurozone, etc.
| [Thursday 12 August 2010] [15:28:08] <moorooboorai> pieterh: glad to be of service - truly hope zeromq lives up to my (now) great expectations!
| [Thursday 12 August 2010] [15:28:19] <sustrik>  true, i drop the 100% thing
| [Thursday 12 August 2010] [15:28:34] <pieterh>  moorooboorai: i'm interested to know what you appreciated about my amqp analysis
| [Thursday 12 August 2010] [15:29:34] <pieterh>  sustrik: you are going to argue that a distributed service bus is essential, right?
| [Thursday 12 August 2010] [15:30:12] <pieterh>  then you step into economics and politics even
| [Thursday 12 August 2010] [15:30:30] <sustrik>  yes, but i have no time for that
| [Thursday 12 August 2010] [15:30:35] <pieterh>  exactly
| [Thursday 12 August 2010] [15:30:38] <sustrik>  i'll try to keep it minimal
| [Thursday 12 August 2010] [15:30:47] <sustrik>  jsut an introduction like this one
| [Thursday 12 August 2010] [15:30:55] <sustrik>  then some technical example
| [Thursday 12 August 2010] [15:31:04] <sustrik>  then the kernel thing
| [Thursday 12 August 2010] [15:31:10] <pieterh>  drop the claim that tcp/ip dominates because it's distributed, that is not accurate
| [Thursday 12 August 2010] [15:31:22] <sustrik>  why so?
| [Thursday 12 August 2010] [15:31:29] <pieterh>  it is simply "natural monopoly"
| [Thursday 12 August 2010] [15:31:36] <sustrik>  if it was cetnralised who would use it?
| [Thursday 12 August 2010] [15:31:45] <pieterh>  220v is centralized
| [Thursday 12 August 2010] [15:31:49] <pieterh>  euro is centralized
| [Thursday 12 August 2010] [15:31:52] <pieterh>  i repeat all the examples
| [Thursday 12 August 2010] [15:32:12] <pieterh>  it dominates because it was cheaper than its competitors
| [Thursday 12 August 2010] [15:32:31] <sustrik>  which is consequence of being distributed
| [Thursday 12 August 2010] [15:32:42] <pieterh>  it's a consequence mainly of having no patents
| [Thursday 12 August 2010] [15:32:45] <pieterh>  no license fees
| [Thursday 12 August 2010] [15:33:03] <pieterh>  ok, 110 patents on the RJ45 socket, but not the digital part
| [Thursday 12 August 2010] [15:33:04] <moorooboorai> pieterh: first one has to do with style: you were able to keep a very lenghty argument interesting to read; whilst reading the user guide I am - again - pleasantly surprised by your style of writing. It is humorous, takes a broad view and still singles out the subject.
| [Thursday 12 August 2010] [15:33:22] <sustrik>  sure, that two
| [Thursday 12 August 2010] [15:33:25] <sustrik>  too
| [Thursday 12 August 2010] [15:33:46] <pieterh>  whereas, for example, Microsoft launched MSN precisely to try to kill IP
| [Thursday 12 August 2010] [15:33:49] <sustrik>  but if there was a single party in control it would try to get as much money from it as possible
| [Thursday 12 August 2010] [15:34:11] <pieterh>  so IP enabled a competitive market whereas MSN et al did not
| [Thursday 12 August 2010] [15:34:19] <sustrik>  exactly
| [Thursday 12 August 2010] [15:34:33] <sustrik>  and the competitive market got the price down to zero
| [Thursday 12 August 2010] [15:34:37] <pieterh>  yes
| [Thursday 12 August 2010] [15:34:46] <pieterh>  as will always happen in a friction free market
| [Thursday 12 August 2010] [15:34:53] <sustrik>  if it weren't distributed there wouldn't be a competitive market
| [Thursday 12 August 2010] [15:35:01] <pieterh>  that is correct and that's the chain of logic
| [Thursday 12 August 2010] [15:35:09] <pieterh>  you can't skip the intermediate step
| [Thursday 12 August 2010] [15:35:12] <pieterh>  IMO
| [Thursday 12 August 2010] [15:35:18] <sustrik>  which one is that?
| [Thursday 12 August 2010] [15:35:26] <pieterh>  the economics of it
| [Thursday 12 August 2010] [15:35:38] <sustrik>  eh?
| [Thursday 12 August 2010] [15:35:46] <sustrik>  i mean what would you skip?
| [Thursday 12 August 2010] [15:36:12] <pieterh>  sorry, i'll try to clarify
| [Thursday 12 August 2010] [15:36:18] <moorooboorai> pieterh: second one is concerned content-wise: you nailed the 'feeling' that slowly crept upon me. Seeing the guys from RabbitMQ faltering in keeping the pace made me worry big time. Then stumbling upon your argument (pinpointed by the wiki on AMQP) which suddenly gave me a very keen sense on the real reasons behind that faltering. It's very much reminiscent of the company politics you enter into in big enterprises. So point 
| [Thursday 12 August 2010] [15:36:18] <moorooboorai> being: you've persuaded me to give zeromq a try, not on the technical specs but on it's apparent "better" organizational setting.
| [Thursday 12 August 2010] [15:36:52] <pieterh>  sustrik: a second, let me re-read your abstract
| [Thursday 12 August 2010] [15:37:21] <pieterh>  moorooboorai: this is sadly where AMQP seems to have landed
| [Thursday 12 August 2010] [15:39:37] <pieterh>  moorooboorai: BTW, welcome to our little community, and thanks for not fleeing when it didn't work right away
| [Thursday 12 August 2010] [15:40:02] <sustrik>  yes, the argument can be made much clearer if i focus on the single fact: distributed architecture creates a competitive market whereas centralised architecture does not
| [Thursday 12 August 2010] [15:40:32] <sustrik>  consequently, markets created on distributed architectures flourish
| [Thursday 12 August 2010] [15:40:45] <sustrik>  and the price is drawn down
| [Thursday 12 August 2010] [15:40:53] <sustrik>  which increases adoption etc.
| [Thursday 12 August 2010] [15:41:31] <sustrik>  the question is: should i completely omit freedom, scalability, security etc.?
| [Thursday 12 August 2010] [15:41:58] <pieterh>  sustrik: i'm going to propose a new first paragraph
| [Thursday 12 August 2010] [15:42:04] <pieterh>  based on economics and standards 
| [Thursday 12 August 2010] [15:42:23] <pieterh>  simple argumentation but rock solid
| [Thursday 12 August 2010] [15:42:28] <pieterh>  see if you like it, 5 mins...
| [Thursday 12 August 2010] [15:42:32] <sustrik>  ok
| [Thursday 12 August 2010] [16:05:56] <moorooboorai> Hi guys: although the make for erlzmq works - the make docs command crashes erlang. Error message: erl -noshell -run edoc_run application "'zmq'" '"."' \
| [Thursday 12 August 2010] [16:05:56] <moorooboorai>         '[{dir, "../doc"}, {def, [{version, "0.1"}]}]' -run init stop
| [Thursday 12 August 2010] [16:05:57] <moorooboorai> {"init terminating in do_boot",{undef,[{edoc_run,application,[["'zmq'","\".\"","[{dir, \"../doc\"}, {def, [{version, \"0.1\"}]}]"]]},{init,start_it,1},{init,start_em,1}]}}
| [Thursday 12 August 2010] [16:06:37] <sustrik>  what platform you are on?
| [Thursday 12 August 2010] [16:06:54] <moorooboorai> Ubuntu 10.04 LTS 
| [Thursday 12 August 2010] [16:07:02] <moorooboorai> (Desktop, not server.)
| [Thursday 12 August 2010] [16:07:11] <sustrik>  hm, dunno
| [Thursday 12 August 2010] [16:07:17]     * sustrik is not an erlang expert
| [Thursday 12 August 2010] [16:07:29]     * sustrik is actually an erlang dummy
| [Thursday 12 August 2010] [16:07:38] <moorooboorai> :-))
| [Thursday 12 August 2010] [16:08:06] <moorooboorai> That's okay. Will work it out somehow and bring fixes back - if any.
| [Thursday 12 August 2010] [16:08:17] <sustrik>  that would be great
| [Thursday 12 August 2010] [16:08:20] <sustrik>  thanks
| [Thursday 12 August 2010] [16:09:11] <travlr>   pieterh: off topi -- wikidot.. how do i hide the edit button and other "wiki" options at the bottom of a page from vistors.. i.e. for admin only
| [Thursday 12 August 2010] [16:09:34] <travlr>   i can't find this info anywhere
| [Thursday 12 August 2010] [16:09:36] <pieterh>  travlr: in your site manager, permissions, uncheck the "Show page options" option for that category
| [Thursday 12 August 2010] [16:09:47] <travlr>   thanks
| [Thursday 12 August 2010] [16:09:51] <pieterh>  np
| [Thursday 12 August 2010] [16:10:11] <moorooboorai> (Travlr must be concerned because of my 'wild' adjustments... ;-) )
| [Thursday 12 August 2010] [16:10:15] <pieterh>  sustrik: i've found a major flaw in the argument
| [Thursday 12 August 2010] [16:10:21] <sustrik>  ?
| [Thursday 12 August 2010] [16:11:01] <pieterh>  true competition is possible only with freedom of clients to choose suppliers
| [Thursday 12 August 2010] [16:11:07] <pieterh>  i.e. standards for interoperability
| [Thursday 12 August 2010] [16:11:15] <sustrik>  yes, and?
| [Thursday 12 August 2010] [16:11:25] <pieterh>  a natural monopoly emerges from such a standard, when it's free and open
| [Thursday 12 August 2010] [16:11:30] <pieterh>  0mq is not a standard
| [Thursday 12 August 2010] [16:11:38] <sustrik>  not yet
| [Thursday 12 August 2010] [16:11:48] <pieterh>  a product cannot become a standard
| [Thursday 12 August 2010] [16:12:02] <sustrik>  that's why i talk of 'scalability layer'
| [Thursday 12 August 2010] [16:12:18] <sustrik>  i'll explain that later on
| [Thursday 12 August 2010] [16:12:27] <pieterh>  if you want to make this argument solid you need to add "wire level protocol standards for service interop" to your 20 year vision
| [Thursday 12 August 2010] [16:12:37] <pieterh>  like i've been complaining for years :-)
| [Thursday 12 August 2010] [16:12:44] <sustrik>  yes, it'll be mentioned
| [Thursday 12 August 2010] [16:13:43] <sustrik>  i agree, it should be there, but we need to make semantics clear first; once the semantics are clear, drafting a WLP is trivial
| [Thursday 12 August 2010] [16:13:50] <pieterh>  if you want to understand the importance of free and open standards to this process please read http://www.digistan.org/text:rationale
| [Thursday 12 August 2010] [16:13:56] <pieterh>  no, it is not trivial
| [Thursday 12 August 2010] [16:14:03] <pieterh>  sorry, that is really wrong :-)
| [Thursday 12 August 2010] [16:14:15] <pieterh>  especially if you try to work backwards from code
| [Thursday 12 August 2010] [16:15:06] <pieterh>  i think we need to urgently create a standards workgroup
| [Thursday 12 August 2010] [16:15:14] <sustrik>  too early
| [Thursday 12 August 2010] [16:15:21] <sustrik>  we need a semantics wiorkgroup
| [Thursday 12 August 2010] [16:15:31] <sustrik>  what is identity?
| [Thursday 12 August 2010] [16:15:41] <sustrik>  how does it interact with different patterns?
| [Thursday 12 August 2010] [16:15:42] <sustrik>  etc.
| [Thursday 12 August 2010] [16:15:44] <pieterh>  semantics is part of standards
| [Thursday 12 August 2010] [16:15:48] <sustrik>  yes
| [Thursday 12 August 2010] [16:15:56] <pieterh>  but without a deliberate statement "we want to deliver standards"
| [Thursday 12 August 2010] [16:15:56] <sustrik>  but it precedes WLP
| [Thursday 12 August 2010] [16:16:07] <sustrik>  here it is"
| [Thursday 12 August 2010] [16:16:18] <sustrik>  "We want to deliver standards"
| [Thursday 12 August 2010] [16:16:21] <pieterh>  then the argument "we know how to enable competition between service providers" fails
| [Thursday 12 August 2010] [16:16:28] <pieterh>  yes, put that on the web
| [Thursday 12 August 2010] [16:16:34] <pieterh>  write that on the main page
| [Thursday 12 August 2010] [16:16:36] <pieterh>  it's sufficient
| [Thursday 12 August 2010] [16:16:47] <sustrik>  sure, do so
| [Thursday 12 August 2010] [16:16:47] <pieterh>  but it must be a stated goal of the project
| [Thursday 12 August 2010] [16:16:58] <sustrik>  i'm going to discuss that in part 3 of the article
| [Thursday 12 August 2010] [16:17:07] <pieterh>  :-) you, please, since otherwise it's pieter injecting his "OMG lets standardize everything" ideology :-)
| [Thursday 12 August 2010] [16:17:18] <pieterh>  ok, almost done with the intro
| [Thursday 12 August 2010] [16:17:26] <sustrik>  lemme see
| [Thursday 12 August 2010] [16:17:32] <pieterh>  hang on... 
| [Thursday 12 August 2010] [16:17:42] <pieterh>  if you are bored plz go read that digistan article
| [Thursday 12 August 2010] [16:18:33] <sustrik>  reading an article on stratification of plant seeds right now :)
| [Thursday 12 August 2010] [16:18:54] <sustrik>  but i read your rationale before
| [Thursday 12 August 2010] [16:19:07] <sustrik>  i have nothing against standards
| [Thursday 12 August 2010] [16:19:22] <sustrik>  the only thing i am saying is "do it properly"
| [Thursday 12 August 2010] [16:19:43] <sustrik>  AMQP trauma, you know
| [Thursday 12 August 2010] [16:19:59] <pieterh>  you should always learn from trauma
| [Thursday 12 August 2010] [16:20:05] <pieterh>  AMQP was a brilliant concept badly done
| [Thursday 12 August 2010] [16:21:01] <pieterh>  the part that was done correctly was the careful "consensus on the standard and running code" that preceded the madness
| [Thursday 12 August 2010] [16:21:13] <pieterh>  this is also how IP was built
| [Thursday 12 August 2010] [16:21:16] <sustrik>  sure i know
| [Thursday 12 August 2010] [16:21:21] <pieterh>  not by people writing code
| [Thursday 12 August 2010] [16:21:29] <pieterh>  sorry but that's the truth: RFCs came before code
| [Thursday 12 August 2010] [16:21:48] <pieterh>  they also came out of code but everything before the RFC was thrown away
| [Thursday 12 August 2010] [16:22:06] <sustrik>  seems reasonable
| [Thursday 12 August 2010] [16:23:06] <pieterh>  next week in bratislava i'd like to take a few hours to sketch a draft 0mq WLP covering everything we do
| [Thursday 12 August 2010] [16:23:18] <sustrik>  np
| [Thursday 12 August 2010] [16:23:54] <pieterh>  gr8
| [Thursday 12 August 2010] [16:27:32] <pieterh>  sustrik: ok, see http://gist.github.com/521665
| [Thursday 12 August 2010] [16:27:52] <pieterh>  it is kind of pedantic but the argumentation is correct IMO, yours to play with as you like
| [Thursday 12 August 2010] [16:29:13] <sustrik>  twenty orders of magnitude?
| [Thursday 12 August 2010] [16:29:29] <sustrik>  100000000000000000000x?
| [Thursday 12 August 2010] [16:30:11] <pieterh>  yes, i think so
| [Thursday 12 August 2010] [16:30:26] <sustrik>  good god
| [Thursday 12 August 2010] [16:30:27] <pieterh>  look, it costs me 10 euro to send 500MB by phone
| [Thursday 12 August 2010] [16:30:34] <pieterh>  and that is CHEAP for Belgium
| [Thursday 12 August 2010] [16:30:39] <sustrik>  that's what i call a meargin
| [Thursday 12 August 2010] [16:30:42] <sustrik>  margin
| [Thursday 12 August 2010] [16:30:52] <pieterh>  if you count SMS as your unit of transfer
| [Thursday 12 August 2010] [16:30:59] <pieterh>  it's 0.10 euro for 160 bytes
| [Thursday 12 August 2010] [16:31:17] <pieterh>  that is actually the basis for the comparison
| [Thursday 12 August 2010] [16:33:30] <pieterh>  100TB for $200/month - http://www.100tb.com/
| [Thursday 12 August 2010] [16:33:37] <sustrik>  :)
| [Thursday 12 August 2010] [16:33:41] <sustrik>  the text is nice
| [Thursday 12 August 2010] [16:34:03] <pieterh>  ah, ok
| [Thursday 12 August 2010] [16:34:08] <sustrik>  but it's extremely focused on market issues
| [Thursday 12 August 2010] [16:34:15] <pieterh>  yes, its very digistan
| [Thursday 12 August 2010] [16:34:18] <sustrik>  are kernel devs interested in that?
| [Thursday 12 August 2010] [16:34:36] <pieterh>  i suspect more than you'd think, anyhow this is the printed paper
| [Thursday 12 August 2010] [16:34:51] <pieterh>  smart people like to understand the argumentation
| [Thursday 12 August 2010] [16:35:04] <sustrik>  what i mean, isn't it worth of stressing some other aspects of the thing as well?
| [Thursday 12 August 2010] [16:35:07] <sustrik>  freedom
| [Thursday 12 August 2010] [16:35:09] <sustrik>  security
| [Thursday 12 August 2010] [16:35:14] <sustrik>  scalability
| [Thursday 12 August 2010] [16:35:15] <sustrik>  ?
| [Thursday 12 August 2010] [16:35:37] <pieterh>  i think they are all emergent properties of free and open standards that enable pure competition
| [Thursday 12 August 2010] [16:35:38] <pieterh>  :-)
| [Thursday 12 August 2010] [16:35:58] <pieterh>  there was no charter for freedom in RFCxxx 
| [Thursday 12 August 2010] [16:36:06] <sustrik>  nope, if you have a free and open standard for centralised services
| [Thursday 12 August 2010] [16:36:14] <sustrik>  it won't provide any of it
| [Thursday 12 August 2010] [16:36:49] <pieterh>  HTTP vs IP, perhaps
| [Thursday 12 August 2010] [16:37:01] <pieterh>  SOAP is a free and open standard for centralized services
| [Thursday 12 August 2010] [16:37:07] <sustrik>  yes
| [Thursday 12 August 2010] [16:37:09] <pieterh>  it allows centralized services to compete with each other
| [Thursday 12 August 2010] [16:37:20] <sustrik>  is it scalable?
| [Thursday 12 August 2010] [16:37:29] <pieterh>  HTTP is scalable, yes
| [Thursday 12 August 2010] [16:37:41] <pieterh>  Ajax, websockets, etc. scales
| [Thursday 12 August 2010] [16:38:07] <sustrik>  i mean what happens on the "server" side if there's too much requests?
| [Thursday 12 August 2010] [16:38:11] <sustrik>  it'll fail
| [Thursday 12 August 2010] [16:38:12] <pieterh>  oh, it scales
| [Thursday 12 August 2010] [16:38:28] <pieterh>  this is a solved problem
| [Thursday 12 August 2010] [16:38:32] <sustrik>  ?
| [Thursday 12 August 2010] [16:38:34] <pieterh>  you throw money at it
| [Thursday 12 August 2010] [16:38:41] <sustrik>  ah, that way
| [Thursday 12 August 2010] [16:38:49] <pieterh>  caches, distributed static file servers, larger machines, clusters, etc.
| [Thursday 12 August 2010] [16:38:57] <dos000>   pieterh, i am going through the guide .. very amazing work btw ... 
| [Thursday 12 August 2010] [16:38:58] <sustrik>  sure
| [Thursday 12 August 2010] [16:39:12] <pieterh>  dos000: glad you like it...:)
| [Thursday 12 August 2010] [16:39:22] <sustrik>  anyway, doesn't matter
| [Thursday 12 August 2010] [16:39:23] <pieterh>  sustrik: so scalability is not the magic ingredient
| [Thursday 12 August 2010] [16:39:41] <pieterh>  and in theory HTTP does enable distributed services
| [Thursday 12 August 2010] [16:39:57] <pieterh>  that was the idea behind web services, really
| [Thursday 12 August 2010] [16:39:57] <sustrik>  yes, sure, even SOAP
| [Thursday 12 August 2010] [16:40:15] <dos000>   pieterh, how can you that guaranties state based processing of incoming sockets .. so a socket is only processed following a state machine
| [Thursday 12 August 2010] [16:40:15] <pieterh>  why did it fail?
| [Thursday 12 August 2010] [16:40:18] <sustrik>  the problem that the "scalability layer" on top of it is not defined
| [Thursday 12 August 2010] [16:40:37] <pieterh>  dos000: you mean in 0MQ or in your app?
| [Thursday 12 August 2010] [16:40:40] <sustrik>  things like: if the service is unavailable, what should I do?
| [Thursday 12 August 2010] [16:40:43] <dos000>   pieterh, in the figure 6 example worker threads will share the load ..
| [Thursday 12 August 2010] [16:40:46] <sustrik>  SOAP doesn't address the problem
| [Thursday 12 August 2010] [16:40:49] <dos000>   pieterh, in my app 
| [Thursday 12 August 2010] [16:41:00] <pieterh>  dos000: ah, i have no answer for that, yet
| [Thursday 12 August 2010] [16:41:06] <dos000>   ah!
| [Thursday 12 August 2010] [16:41:11] <pieterh>  it is actually not possible today
| [Thursday 12 August 2010] [16:41:24] <pieterh>  you have to delegate the management of peer connections to 0MQ
| [Thursday 12 August 2010] [16:41:37] <pieterh>  you can manage sockets individually using poll() but it will not give you state per remote peer
| [Thursday 12 August 2010] [16:41:43] <pieterh>  this is by design
| [Thursday 12 August 2010] [16:42:03] <pieterh>  sustrik: it looks like an answer searching for a problem
| [Thursday 12 August 2010] [16:42:12] <pieterh>  "I have this scalability layer, now I need to explain why you need it"
| [Thursday 12 August 2010] [16:42:25] <pieterh>  "But I don't have a scalability problem!"
| [Thursday 12 August 2010] [16:42:33] <dos000>   i have to process these requests sequentially so i have to keep track of the state of each socket in my protocol
| [Thursday 12 August 2010] [16:42:37] <pieterh>  "Ah, but if you didn't rely on Google, you would have!"
| [Thursday 12 August 2010] [16:42:44] <sustrik>  well, yes
| [Thursday 12 August 2010] [16:42:46] <sustrik>  and?
| [Thursday 12 August 2010] [16:42:57] <pieterh>  dos000: if you are trying to track individual sockets, you're probably doing it wrong
| [Thursday 12 August 2010] [16:43:02] <pieterh>  sustrik: there has to be another hook
| [Thursday 12 August 2010] [16:43:15] <sustrik>  there is lot of them
| [Thursday 12 August 2010] [16:43:31] <sustrik>  what i am asking whether economics is the right hook for kernel devs
| [Thursday 12 August 2010] [16:43:49] <dos000>   pieterh, the protocol requires that requests coming from the same client be treated in sequence 
| [Thursday 12 August 2010] [16:44:03] <pieterh>  dos000: sorry, a moment...
| [Thursday 12 August 2010] [16:44:08] <dos000>   pieterh, ok
| [Thursday 12 August 2010] [16:44:59] <pieterh>  sustrik: http already offers scalable, free, distributed services
| [Thursday 12 August 2010] [16:45:07] <pieterh>  you're right that the scaling happens inside, not outside the wall
| [Thursday 12 August 2010] [16:45:12] <pieterh>  that is perhaps the key difference
| [Thursday 12 August 2010] [16:45:33] <pieterh>  this is what you mean by 0MQ in the Internet fabric
| [Thursday 12 August 2010] [16:45:40] <sustrik>  yes
| [Thursday 12 August 2010] [16:45:45] <pieterh>  your switch does pubsub and request-reply
| [Thursday 12 August 2010] [16:45:51] <sustrik>  yes
| [Thursday 12 August 2010] [16:46:02] <sustrik>  but that's too complex
| [Thursday 12 August 2010] [16:46:03] <pieterh>  this is the hook, then
| [Thursday 12 August 2010] [16:46:14] <pieterh>  right, but it's the critical path
| [Thursday 12 August 2010] [16:46:21] <sustrik>  waht i meant was whether it's not worth of putting some more emphasis on freedom or so
| [Thursday 12 August 2010] [16:46:37] <pieterh>  you want to appeal to emotions?
| [Thursday 12 August 2010] [16:46:39] <pieterh>  perhaps
| [Thursday 12 August 2010] [16:46:45] <sustrik>  right now the argument is 95% economics and 5% freedom
| [Thursday 12 August 2010] [16:46:54] <sustrik>  rather a more balanced view
| [Thursday 12 August 2010] [16:46:58] <pieterh>  freedom and economics are not different things
| [Thursday 12 August 2010] [16:47:30] <sustrik>  i am just commenting on your text
| [Thursday 12 August 2010] [16:47:40] <sustrik>  it's seems to focused on economic aspect
| [Thursday 12 August 2010] [16:47:43] <sustrik>  "which is primarily a vehicle for delivering Google services (and ads) had 1.9% of the US smartphone market by Q2. In 2010, 12 months later, it had 17% of the US market"
| [Thursday 12 August 2010] [16:47:43] <pieterh>  ok, so you want some more familiar keywords ;-)
| [Thursday 12 August 2010] [16:47:58] <pieterh>  yes, linux is dominating
| [Thursday 12 August 2010] [16:48:07] <pieterh>  but it's not quite as pretty as you thought it might be
| [Thursday 12 August 2010] [16:48:33] <sustrik>  i mean why should that kind of info even be there
| [Thursday 12 August 2010] [16:48:45] <sustrik>  it's for kernel devs, not businessmen
| [Thursday 12 August 2010] [16:48:52] <pieterh>  that is to demonstrate the utter power involved
| [Thursday 12 August 2010] [16:49:12] <pieterh>  a new kind of power on a scale you can't really comprehend
| [Thursday 12 August 2010] [16:49:24] <sustrik>  ok, too late today, let's continue tomorrow
| [Thursday 12 August 2010] [16:49:36] <pieterh>  sure
| [Thursday 12 August 2010] [16:49:47] <sustrik>  good night
| [Thursday 12 August 2010] [16:49:48] <pieterh>  dos000: we can continue if you like
| [Thursday 12 August 2010] [16:49:53] <pieterh>  g'night martin!
| [Thursday 12 August 2010] [16:50:02] <dos000>   pieterh, ok ..
| [Thursday 12 August 2010] [16:50:13] <dos000>   so i did this java nio before
| [Thursday 12 August 2010] [16:50:32] <pieterh>  right, so i probably have the answer for you
| [Thursday 12 August 2010] [16:50:35] <pieterh>  speaking of nio
| [Thursday 12 August 2010] [16:50:47] <pieterh>  which is one of the reactors on 0MQ Labs
| [Thursday 12 August 2010] [16:51:16] <dos000>   the only one way i could track the state using multiple threads was to remove the scket from the polling thread 
| [Thursday 12 August 2010] [16:51:41] <pieterh>  a quick question: how much have you already used 0MQ?
| [Thursday 12 August 2010] [16:52:33] <dos000>   pieterh, no actual code yet
| [Thursday 12 August 2010] [16:52:56] <pieterh>  ok, so what you need to do is spend a day just writing different simple 0MQ cases
| [Thursday 12 August 2010] [16:53:07] <pieterh>  before trying to design anything using 0MQ
| [Thursday 12 August 2010] [16:53:23] <dos000>   ok .. i buy the argument
| [Thursday 12 August 2010] [16:53:32] <dos000>   good point i mean
| [Thursday 12 August 2010] [16:53:34] <pieterh>  this is something I need to explain in the Guide
| [Thursday 12 August 2010] [16:54:04] <dos000>   can i ask how the reactor is going to handle this ou it will go over my head ?
| [Thursday 12 August 2010] [16:54:49] <pieterh>  i've not used the reactors
| [Thursday 12 August 2010] [16:54:52] <dos000>   i can also wait for the guide
| [Thursday 12 August 2010] [16:55:04] <pieterh>  so my ignorant understanding is: the reactor is like poll turned inside out, it will invoke your code based on events arriving on sockets
| [Thursday 12 August 2010] [16:55:42] <dos000>   and it will do it on multiple threads ? or it will be a thread per request ?
| [Thursday 12 August 2010] [16:55:54] <dos000>   thread per connection i mean
| [Thursday 12 August 2010] [16:57:21] <dos000>   for the reactor pattern the ace lib explains it very well .. but maybe zmq is not following the way ace/tao did it
| [Thursday 12 August 2010] [16:59:51] <pieterh>  dos000: sorry, was on another thread
| [Thursday 12 August 2010] [17:00:03] <pieterh>  threads, requests, sockets...
| [Thursday 12 August 2010] [17:00:17] <pieterh>  most of what you think you know about this won't map to 0MQ
| [Thursday 12 August 2010] [17:00:27] <dos000>   ah
| [Thursday 12 August 2010] [17:01:28] <dos000>   how expensive is it to add or remove a socket to/from the poll ?
| [Thursday 12 August 2010] [17:01:35] <pieterh>  there should be a sign above the entrance saying "Warning: leave your understanding of threads, requests, and sockets at the door"
| [Thursday 12 August 2010] [17:01:49] <pieterh>  pollsets are just structures
| [Thursday 12 August 2010] [17:02:01] <dos000>   ok .. thats what i hoped 
| [Thursday 12 August 2010] [17:02:17] <dos000>   so please review this algo rithm with me
| [Thursday 12 August 2010] [17:02:35] <pieterh>  dos000: seriously... what you are going to explain to me is broken :-)
| [Thursday 12 August 2010] [17:02:48] <dos000>   please .. 
| [Thursday 12 August 2010] [17:02:56] <pieterh>  :-) shoot
| [Thursday 12 August 2010] [17:03:02] <dos000>   as soon a activity comes on a socket the polling thread removes the socket from the pollset
| [Thursday 12 August 2010] [17:03:29] <dos000>   this guaranties that only one thread will always hadle a socket at a time.
| [Thursday 12 August 2010] [17:03:49] <dos000>   after the worker thread is done with the socket it puts it back in the pollset
| [Thursday 12 August 2010] [17:03:55] <pieterh>  can i stop you now?
| [Thursday 12 August 2010] [17:03:58] <dos000>   sure .
| [Thursday 12 August 2010] [17:04:20] <pieterh>  so you are thinking in terms of managing, yourself, the sockets that speak to remote peers
| [Thursday 12 August 2010] [17:04:42] <pieterh>  you are trying to map your knowledge of how to build a multithreaded server onto the 0MQ example
| [Thursday 12 August 2010] [17:04:44] <pieterh>  right?
| [Thursday 12 August 2010] [17:05:04] <dos000>   yes correct
| [Thursday 12 August 2010] [17:05:30] <pieterh>  here is the key piece of information your mind is refusing to accept, because it goes against everything you know
| [Thursday 12 August 2010] [17:05:36] <pieterh>  there is no connection
| [Thursday 12 August 2010] [17:05:53] <pieterh>  or rather, you cannot see, work with, open, close, attach state to the connection
| [Thursday 12 August 2010] [17:06:01] <pieterh>  the socket is NOT the connection
| [Thursday 12 August 2010] [17:06:06] <dos000>   ah
| [Thursday 12 August 2010] [17:06:21] <dos000>   unless you do your own poll correct ?
| [Thursday 12 August 2010] [17:06:25] <pieterh>  no
| [Thursday 12 August 2010] [17:06:28] <pieterh>  no unless
| [Thursday 12 August 2010] [17:06:35] <dos000>   ok .. then i am greatly mistaken
| [Thursday 12 August 2010] [17:06:40] <pieterh>  there is no unless here, it's fundamental to 0MQ
| [Thursday 12 August 2010] [17:06:57] <pieterh>  the socket is a smart application that manages ALL the connections for you
| [Thursday 12 August 2010] [17:07:06] <pieterh>  you can talk to the socket
| [Thursday 12 August 2010] [17:07:12] <pieterh>  and poll lets you talk to multiple sockets at once
| [Thursday 12 August 2010] [17:07:32] <pieterh>  but you cannot talk to the socket's connections, that is private, hidden
| [Thursday 12 August 2010] [17:07:44] <dos000>   ok .. got you ..
| [Thursday 12 August 2010] [17:07:47] <pieterh>  this abstraction is what lets you build properly scalable applications
| [Thursday 12 August 2010] [17:07:55] <pieterh>  at first you're like... "... wtf?"
| [Thursday 12 August 2010] [17:08:07] <pieterh>  and after you've tried it for a while, you're... "... dude!"
| [Thursday 12 August 2010] [17:08:25] <dos000>   i am not at the  ... duude yet !
| [Thursday 12 August 2010] [17:08:32] <pieterh>  it'll come
| [Thursday 12 August 2010] [17:08:38] <pieterh>  :-)
| [Thursday 12 August 2010] [17:08:56] <pieterh>  i'm going to capture this little discussion for the Guide, it's been very useful, thanks
| [Thursday 12 August 2010] [17:09:05] <dos000>   thanks to you man
| [Thursday 12 August 2010] [17:09:11] <pieterh>  np duude
| [Thursday 12 August 2010] [17:09:42] <dos000>   should be daman
| [Thursday 12 August 2010] [17:10:04] <dos000>   u-da-man
| [Thursday 12 August 2010] [17:10:19] <man>  nah, sustrik is daman
| [Thursday 12 August 2010] [17:37:03] <travlr>   huh. what just happened?
| [Thursday 12 August 2010] [17:38:07] <dos000>   when you see these it means ... they changed something in the mattrix
| [Thursday 12 August 2010] [17:38:33] <travlr>   odd
| [Thursday 12 August 2010] [17:38:49] <dos000>   all my channels dropped
| [Thursday 12 August 2010] [17:39:18] <travlr>   weird again..
| [Thursday 12 August 2010] [17:47:29] <pieterh>  travlr: ?
| [Thursday 12 August 2010] [17:49:09] <travlr>   pieterh: yes sir
| [Thursday 12 August 2010] [17:49:17] <pieterh>  what's weird? 
| [Thursday 12 August 2010] [17:49:26] <pieterh>  just curious...
| [Thursday 12 August 2010] [17:49:47] <travlr>   oh, the irc server bugged out and dropped a bunch of users and then joined them again
| [Thursday 12 August 2010] [17:50:24] <pieterh>  ah, right, and i thought everyone except me went for a quick beer... :-)
| [Thursday 12 August 2010] [17:50:56] <travlr>   congrats on the upcoming new family member btw
| [Thursday 12 August 2010] [17:51:06] <pieterh>  hey, thanks
| [Thursday 12 August 2010] [17:59:05] <AndrewBC> travlr, that happens when physical servers get desynchronized or lose connection between each other in the irc server set
| [Thursday 12 August 2010] [18:12:01] <travlr>   cool, thanks andrew
| [Thursday 12 August 2010] [18:38:14] <cremes>   they need to replace their buggy networking code with 0mq!  ;)
| [Thursday 12 August 2010] [18:38:24] <mato> :)
| [Thursday 12 August 2010] [20:18:17]     * pieterh has finally published an update of the Guide
| [Thursday 12 August 2010] [20:18:46] <pieterh>  new feature: translations of code examples into every available language
| [Thursday 12 August 2010] [20:20:03]     * pieterh wonders what happens if he shoves a .jar in a gist...
| [Thursday 12 August 2010] [21:50:41] <travlr>   pieterh: "MQ uses C as the reference language and this is the language we'll use for examples."
| [Thursday 12 August 2010] [21:50:51] <travlr>   except they are in python
| [Thursday 12 August 2010] [22:00:07] <AndrewBC> some are in python, some are in C
| [Thursday 12 August 2010] [22:01:06] <AndrewBC> the API reference is also for C
| [Friday 13 August 2010] [01:06:33] <shekispeaks>    hi 
| [Friday 13 August 2010] [01:06:48] <shekispeaks>    i am just checking out zeromq for my use case
| [Friday 13 August 2010] [01:07:05] <shekispeaks>    i need persistence in my use case 
| [Friday 13 August 2010] [01:07:21] <shekispeaks>    that is on a system reboot, the messages and the queues must be availble
| [Friday 13 August 2010] [01:09:41] <guido_g>    mq has no persistence built in
| [Friday 13 August 2010] [01:10:25] <guido_g>    depending on the app, you should do that yourself anyway (but that's imho)
| [Friday 13 August 2010] [01:13:39] <shekispeaks>    has anyone done it before
| [Friday 13 August 2010] [01:13:48] <shekispeaks>    what are the options
| [Friday 13 August 2010] [01:23:54] <guido_g>    the options are that you look at the requirements that say that you need message persistence and then find a way of implementing it on top of the delivery layer (mq)
| [Friday 13 August 2010] [02:38:39] <sustrik>    shekispeaks: there's an 0MQ/AMQP bridge project in the works that would allow you to place AMQP brokers into 0MQ network to achieve persistence; helping with it may be a better choice than writing everything from scratch
| [Friday 13 August 2010] [02:40:46] <shekispeaks>    sustrik: thanks, but looking for some out of the box solutions, need to get a queue up and running
| [Friday 13 August 2010] [02:40:58] <sustrik>    ack
| [Friday 13 August 2010] [02:54:28] <guido_g>    re
| [Friday 13 August 2010] [07:29:38] <moorooboorai>   hi guys, still struggling to get the Erlang client running. Have finally gotten to the point where zmqd will no longer complain when it starts. But now it wants a config file. Have scraped the mailing list and the website but to no avail. From source and indirect references I can tell there it's an XML-formatted file with an apparent <device> root node. But, before I start studying the sources to reverse engineer the xml spec, 
| [Friday 13 August 2010] [07:29:38] <moorooboorai>   am kinda hoping you can pinpoint me to the format spec on the website.
| [Friday 13 August 2010] [08:02:45] <pieterh>    moorooboorai: hi
| [Friday 13 August 2010] [08:02:57] <moorooboorai>   hi
| [Friday 13 August 2010] [08:03:02] <pieterh>    give me a second and i'll post an example cfg file
| [Friday 13 August 2010] [08:03:10] <pieterh>    i'm rewriting the zmqd program
| [Friday 13 August 2010] [08:04:48] <moorooboorai>   great: have gotten as far as <config> <device type="forwarder|streamer|queue><in addr=""></in><out addr=""></out></device></config> ... but then still have to figure out what's expected in the addr attribute.
| [Friday 13 August 2010] [08:06:27] <pieterh>    addr is an endpoint
| [Friday 13 August 2010] [08:06:37] <pieterh>    if you're binding, use tcp://*:port
| [Friday 13 August 2010] [08:06:46] <pieterh>    if you're connecting, tcp://ipaddress:port
| [Friday 13 August 2010] [08:08:06] <moorooboorai>   okay. Thanks. So if that's all there is to the config file then I am in good shape for now.
| [Friday 13 August 2010] [08:08:14] <pieterh>    hang on, it's not quite that
| [Friday 13 August 2010] [08:09:27] <pieterh>    this is what I *think* it is: http://gist.github.com/522767
| [Friday 13 August 2010] [08:09:32] <pieterh>    i'm going to test that
| [Friday 13 August 2010] [08:10:11] <sustrik>    wait a sec
| [Friday 13 August 2010] [08:10:24] <sustrik>    moorooboorai is using sustrik/zeromq2 branch
| [Friday 13 August 2010] [08:10:35] <pieterh>    yes, that's where the zmqd is
| [Friday 13 August 2010] [08:10:46] <sustrik>    ah, ok then
| [Friday 13 August 2010] [08:18:37] <pieterh>    moorooboorai: so that's the correct format for the config file BUT zmqd.cpp will only work with that git, as far as i can tell
| [Friday 13 August 2010] [08:19:51] <moorooboorai>   is zmqd supposed to return a "happy message" when supplied with a proper config file? It's not returning right now and it's not showing up when netstat'ing for it.
| [Friday 13 August 2010] [08:20:35] <moorooboorai>   in other words: it just silently 'hangs' there...
| [Friday 13 August 2010] [08:21:43] <moorooboorai>   after command $ sudo zmqd zmq-connect.xml
| [Friday 13 August 2010] [08:21:58] <AndrewBC>   unixy programs are usually silent when all is well
| [Friday 13 August 2010] [08:22:07] <AndrewBC>   (unless explicitly silenced)
| [Friday 13 August 2010] [08:23:17] <moorooboorai>   andrewbc: yep, I know - but then I expect other telltale signs to show up: like connections to ports I've asked the program to connect to
| [Friday 13 August 2010] [08:23:54] <moorooboorai>   (and since the masters are online, I thought to that picking their brain on this would be the easiest way out for now.)
| [Friday 13 August 2010] [08:26:06] <moorooboorai>   brb - lunch
| [Friday 13 August 2010] [11:16:47] <dos000> how would you tell zmq to stop procesing sockets momentarily (say for maintenance ) whithout doing a server shutdown ? this is an app thingy. but i am asking how would you do it.
| [Friday 13 August 2010] [11:24:23] <dos000> ok scratch what i said
| [Friday 13 August 2010] [12:49:45] <CIA-20> jzmq: 03Alexey Ermakov 07master * rc6836cd 10/ src/org/zeromq/ZMQ.java : Added missing ZMQ.SNDMORE constant. - http://bit.ly/dxcfNJ
| [Friday 13 August 2010] [12:55:21] <CIA-20> jzmq: 03Gonzalo Diethelm 07master * r31a216e 10/ src/org/zeromq/ZMQ.java : Added new constants PULL and PUSH. - http://bit.ly/a9UgAu
| [Friday 13 August 2010] [13:55:30]   * pieterh is going to catch a beer at the beach
| [Saturday 14 August 2010] [02:38:03] <CIA-20>   zeromq2: 03Martin Sustrik 07wip-shutdown * r83835ec 10/ (10 files): engine leak fixed; pgm compilation fixed - http://bit.ly/9yLoku
| [Saturday 14 August 2010] [02:54:18] <CIA-20>   zeromq2: 03Martin Sustrik 07wip-shutdown * rf1812b2 10/ (perf/remote_thr.cpp src/object.cpp): added ZMQ_MAKE_VALGRIND_HAPPY compile-time option - http://bit.ly/dzHF5x
| [Saturday 14 August 2010] [12:24:30] <cremes>   you guys might want to chime in on the recent thread [hybi] Framing Take VI (a compromise proposal)
| [Saturday 14 August 2010] [16:45:53] <Xenofur>  hey guys, are you aware that your perl module does not install under windows?
| [Saturday 14 August 2010] [16:49:57] <travlr>   Xenofur: Hi. the language bindings other than c and c++ are not supported by ZeroMQ. Every other binding has their own maintainers... you'll need to contact who ever that maybe and post the problem for a perl issue at http://github.com/tsee/ZeroMQ-Perl/issues
| [Saturday 14 August 2010] [16:50:33] <Xenofur>  i'm just looking for some general conversation
| [Saturday 14 August 2010] [16:51:40] <Xenofur>  as in, trying to see if there is anything known about that, or find out whether the error i'm seeing is a known problem unrelated to perl itself, etc.
| [Saturday 14 August 2010] [16:54:24] <travlr>   yeah I don't do perl so i'm sorry.. i wouldn't know. but i sure its the perl binding's problem though and not otherwise.
| [Saturday 14 August 2010] [16:55:55] <Xenofur>  welp, ok then, thanks the link in any case o/
| [Saturday 14 August 2010] [16:55:56] <sustrik>  best way is to contact perl devs via bug tracker
| [Saturday 14 August 2010] [16:56:19] <Xenofur>  best way to contact perl devs is usually to chat to them :p
| [Saturday 14 August 2010] [16:56:22] <sustrik>  not much chance anyome will be on the irc on saturday :)
| [Saturday 14 August 2010] [16:56:28] <Xenofur>  not sure if c devs are different there
| [Saturday 14 August 2010] [16:56:41] <Xenofur>  oh right, it's saturday
| [Saturday 14 August 2010] [16:56:50] <sustrik>  :)
| [Saturday 14 August 2010] [16:56:52] <Xenofur>  i keep forgetting people have weekends
| [Saturday 14 August 2010] [16:57:03] <sustrik>  some do
| [Saturday 14 August 2010] [16:57:05] <sustrik>  strange
| [Saturday 14 August 2010] [16:57:16] <Xenofur>  very much so
| [Saturday 14 August 2010] [16:57:22] <travlr>   i never know what day of the week it is either... lost :D
| [Saturday 14 August 2010] [16:57:29] <Xenofur>  :D
| [Saturday 14 August 2010] [16:59:51] <sustrik>  cremes: seen it, i've told them the size should go first, they've ignored me, i'll ignore them :)
| [Saturday 14 August 2010] [16:59:52]     * sustrik don't really care about websockets myself anyway
| [Saturday 14 August 2010] [17:00:21] <travlr>   The maintainers still need to be listed on their 0mq sub-page. 
| [Saturday 14 August 2010] [17:01:04] <Xenofur>  i saw the link you gave somewhere before
| [Saturday 14 August 2010] [17:01:17] <Xenofur>  it's just that my first instinct is "go bother people on irc"
| [Saturday 14 August 2010] [17:01:24] <travlr>   on the perl sub-page probably.
| [Saturday 14 August 2010] [17:01:48] <travlr>   irc is the place to be.. lol.
| [Saturday 14 August 2010] [17:02:24] <Xenofur>  any idea if Steffen Mueller shows up here?
| [Saturday 14 August 2010] [17:02:55] <travlr>   i dont
| [Saturday 14 August 2010] [17:04:06] <Xenofur>  ok :)
| [Monday 16 August 2010] [07:09:51] <pieter_hintjens>    sustrik: random question
| [Monday 16 August 2010] [07:09:57] <sustrik>    yes?
| [Monday 16 August 2010] [07:10:06] <pieter_hintjens>    can i connect a pull socket to a pub socket?
| [Monday 16 August 2010] [07:10:25] <sustrik>    you can but you should not
| [Monday 16 August 2010] [07:10:41] <pieterh>    i have a problem that this solves very elegantly
| [Monday 16 August 2010] [07:10:50] <sustrik>    ?
| [Monday 16 August 2010] [07:10:57] <pieterh>    in parallel pipeline, workers read off pull sockets
| [Monday 16 August 2010] [07:11:02] <pieterh>    at some point i want to kill them all
| [Monday 16 August 2010] [07:11:09] <pieterh>    broadcast a kill message to them
| [Monday 16 August 2010] [07:11:38] <pieterh>    simplest is that they connect their pull socket to a pub socket on coordinator node
| [Monday 16 August 2010] [07:11:44] <pieterh>    which can then kill them when the batch is done
| [Monday 16 August 2010] [07:11:57] <pieterh>    if i can't make this connection, i need to manage two sockets with poll
| [Monday 16 August 2010] [07:12:04] <pieterh>    which is significantly more work
| [Monday 16 August 2010] [07:12:09] <sustrik>    using same socket to transfer both work and admin messages?
| [Monday 16 August 2010] [07:12:14] <pieterh>    on input only
| [Monday 16 August 2010] [07:12:21] <pieterh>    separate patterns on the topology
| [Monday 16 August 2010] [07:12:31] <pieterh>    i want a single input queue
| [Monday 16 August 2010] [07:12:52] <sustrik>    1. it wouldn't work
| [Monday 16 August 2010] [07:13:16] <sustrik>    2. mingling disparate data flows is never a good idea
| [Monday 16 August 2010] [07:13:28] <pieterh>    1. why not?
| [Monday 16 August 2010] [07:13:38] <pieterh>    2. it's only fanin of disparate data flows
| [Monday 16 August 2010] [07:13:45] <pieterh>    no different than polling two sockets and reading from each
| [Monday 16 August 2010] [07:13:54] <pieterh>    just more work
| [Monday 16 August 2010] [07:14:24] <sustrik>    because the work won't be load-balanced but sent to all workers
| [Monday 16 August 2010] [07:14:24] <sustrik>    that's what PUB socekt does
| [Monday 16 August 2010] [07:14:38] <pieterh>    that is the point
| [Monday 16 August 2010] [07:14:42] <pieterh>    push/pull for the work
| [Monday 16 August 2010] [07:14:48] <pieterh>    pub/sub for the control
| [Monday 16 August 2010] [07:15:08] <pieterh>    except worker merges sub into pull to get a single queue and easier API
| [Monday 16 August 2010] [07:15:18] <pieterh>    conceptually it's two data flows
| [Monday 16 August 2010] [07:15:28] <sustrik>    yes, it's an API problem
| [Monday 16 August 2010] [07:15:35] <sustrik>    you don't want to use zmq_poll
| [Monday 16 August 2010] [07:15:38] <pieterh>    nope
| [Monday 16 August 2010] [07:15:40] <sustrik>    but something simples
| [Monday 16 August 2010] [07:15:42] <sustrik>    simpler
| [Monday 16 August 2010] [07:15:47] <pieterh>    it's too complex for this part of the guide
| [Monday 16 August 2010] [07:15:57] <keffo>  speaking of pub/sub, is there any timeframe for when the filtering will move to the source, if ever?
| [Monday 16 August 2010] [07:15:57] <sustrik>    mixing the messaging patterns is not a solution
| [Monday 16 August 2010] [07:16:01] <pieterh>    i could use a fanin device
| [Monday 16 August 2010] [07:16:12] <pieterh>    keffo: it'll come but it's not priority for now
| [Monday 16 August 2010] [07:16:34] <sustrik>    filtering is at destination atm
| [Monday 16 August 2010] [07:16:42] <keffo>  and what about ipc/inproc support for win platform?
| [Monday 16 August 2010] [07:16:55] <pieterh>    keffo: sorry, there is no clear roadmap for various reasons
| [Monday 16 August 2010] [07:17:04] <pieterh>    we will try to make one to clarify this
| [Monday 16 August 2010] [07:17:04] <sustrik>    no, using a device means mixing the feeds
| [Monday 16 August 2010] [07:17:15] <sustrik>    what you need is a better API
| [Monday 16 August 2010] [07:17:37] <keffo>  it's not a prio for me at the moment though, my workloads are usually far longer than any latency tcp adds.. 
| [Monday 16 August 2010] [07:17:38] <pieterh>    sustrik: probably, but i'm explaining how to use what we have today... :-)
| [Monday 16 August 2010] [07:18:00] <pieterh>    keffo: in naive tests, tcp and ipc are pretty comparable
| [Monday 16 August 2010] [07:18:26] <pieterh>    the biggest difference is perhaps security, ipc maybe comes from a 'more secure' origin
| [Monday 16 August 2010] [07:19:09] <pieterh>    sustrik: my use case does require mixing the feeds at the worker side
| [Monday 16 August 2010] [07:19:28] <sustrik>    not messing with flows
| [Monday 16 August 2010] [07:19:28] <sustrik>    you may, for example, implement a multi-socket recv:
| [Monday 16 August 2010] [07:19:30] <sustrik>    zmq_recv_mutliple (s1, s2, s3, ...);
| [Monday 16 August 2010] [07:19:38] <pieterh>    sure
| [Monday 16 August 2010] [07:19:43] <sustrik>    application obviously has to process the messages from all connected feeds
| [Monday 16 August 2010] [07:19:50] <pieterh>    but connecting a socket to two endpoints is semantically just the same
| [Monday 16 August 2010] [07:20:01] <sustrik>    the point is that the messaging infrastructure should keep them separate
| [Monday 16 August 2010] [07:20:19] <sustrik>    once you mix the feeds you are never going to get them apart
| [Monday 16 August 2010] [07:20:32] <sustrik>    it's asking for a trouble in future
| [Monday 16 August 2010] [07:20:55] <pieterh>    "don't cross the streams!"
| [Monday 16 August 2010] [07:21:03] <sustrik>    yes
| [Monday 16 August 2010] [07:21:13] <sustrik>    divide and conquer!
| [Monday 16 August 2010] [07:21:17] <pieterh>    you mean, specifically, never connect socket types to ones they're not explicitly designed to talk to?
| [Monday 16 August 2010] [07:21:18] <sustrik>    (your streams)
| [Monday 16 August 2010] [07:21:29] <pieterh>    it's a ghostbusters quote 
| [Monday 16 August 2010] [07:21:53] <sustrik>    ah, don't recall that one
| [Monday 16 August 2010] [07:22:15] <sustrik>    yes, i mean, pipeline is a pipeline is a pipeline
| [Monday 16 August 2010] [07:22:26] <sustrik>    and distribution  tree is a distribution tree
| [Monday 16 August 2010] [07:22:46] <sustrik>    well, frankesteing is frankestein..,
| [Monday 16 August 2010] [07:23:00] <pieterh>    ok, so some random observations on this
| [Monday 16 August 2010] [07:23:28] <pieterh>    1- there is no checking of this vital rule in the infrastructure
| [Monday 16 August 2010] [07:23:38] <pieterh>    2- it's not documented anywhere afaics
| [Monday 16 August 2010] [07:23:45] <sustrik>    :(
| [Monday 16 August 2010] [07:23:47] <sustrik>    i know
| [Monday 16 August 2010] [07:23:48] <pieterh>    3- breaking this rule makes things work nicely in cases
| [Monday 16 August 2010] [07:24:01] <pieterh>    4- there seems to be no nice alternative in cases
| [Monday 16 August 2010] [07:24:20] <pieterh>    5- the objections are theoretical, because in fact these sockets are compatible
| [Monday 16 August 2010] [07:24:47] <sustrik>    mixing the patterns breaks scalability
| [Monday 16 August 2010] [07:24:50] <sustrik>    shrug
| [Monday 16 August 2010] [07:24:57] <sustrik>    just don't doo that
| [Monday 16 August 2010] [07:25:11] <sustrik>    if you have an API problem solve the API problem
| [Monday 16 August 2010] [07:25:19] <pieterh>    sorry, i'm a writer, not a fighter
| [Monday 16 August 2010] [07:25:32] <pieterh>    i have to mix two streams
| [Monday 16 August 2010] [07:25:50] <sustrik>    it's up to you
| [Monday 16 August 2010] [07:25:52] <pieterh>    if i can't use a fanin model (that would seem to make sense)
| [Monday 16 August 2010] [07:25:54] <sustrik>    but you should not
| [Monday 16 August 2010] [07:25:56] <pieterh>    what can i do, easily?
| [Monday 16 August 2010] [07:26:00] <sustrik>    use zmq_poll
| [Monday 16 August 2010] [07:26:05] <pieterh>    sorry, not 'easy'
| [Monday 16 August 2010] [07:26:13] <sustrik>    that you cannot do it
| [Monday 16 August 2010] [07:26:15] <pieterh>    please provide me a simple, stupid solution
| [Monday 16 August 2010] [07:26:25] <sustrik>    that's what zmq_poll is for
| [Monday 16 August 2010] [07:27:07] <pieterh>    i'm going to explain zmq_poll but it's not something i want to throw into the basic examples
| [Monday 16 August 2010] [07:27:16] <sustrik>    allowing a component to handle multiple streams
| [Monday 16 August 2010] [07:27:21] <pieterh>    yes
| [Monday 16 August 2010] [07:27:30] <sustrik>    ok, think of the same problem with TCP
| [Monday 16 August 2010] [07:27:34] <pieterh>    hang on
| [Monday 16 August 2010] [07:27:43] <sustrik>    i want to get data from 2 TCP connections
| [Monday 16 August 2010] [07:27:59] <sustrik>    therefore i patch the kernel to mix the packets for me
| [Monday 16 August 2010] [07:28:00] <pieterh>    can i recv on both sockets, non-blocking, with small nanosleep?
| [Monday 16 August 2010] [07:28:12] <sustrik>    yes, you can
| [Monday 16 August 2010] [07:28:19] <pieterh>    is that going to break scalability?
| [Monday 16 August 2010] [07:28:19] <sustrik>    but you'll get busy loop
| [Monday 16 August 2010] [07:28:24] <sustrik>    nope
| [Monday 16 August 2010] [07:28:27] <pieterh>    not busy loop, sleeping
| [Monday 16 August 2010] [07:28:40] <sustrik>    spinlocking basically
| [Monday 16 August 2010] [07:28:42] <pieterh>    and when there is work, no sleeping, obviously
| [Monday 16 August 2010] [07:28:59] <sustrik>    it's dirty but it doesn't break anything
| [Monday 16 August 2010] [07:29:06] <pieterh>    why is this dirty, specifically?
| [Monday 16 August 2010] [07:29:24] <sustrik>    i wouldn't use it personally
| [Monday 16 August 2010] [07:29:29] <pieterh>    please don't just say "because poll is cleaner", that's opinion
| [Monday 16 August 2010] [07:29:31] <sustrik>    in real world i mean
| [Monday 16 August 2010] [07:29:44] <pieterh>    technically, what's wrong with it?
| [Monday 16 August 2010] [07:29:51] <sustrik>    increase in latency
| [Monday 16 August 2010] [07:30:03] <pieterh>    only for first message, and it's for heavy parallel workloads
| [Monday 16 August 2010] [07:30:37] <sustrik>    sure, if that's your use case then it's ok
| [Monday 16 August 2010] [07:30:40] <pieterh>    ok, this is good, i have a simple way to work with multiple sockets that can be done 'better' with zmq_poll at a later stage
| [Monday 16 August 2010] [07:30:43] <pieterh>    thanks
| [Monday 16 August 2010] [07:30:48] <sustrik>    np
| [Monday 16 August 2010] [07:45:27] <sustrik>    btwL http://github.com/jeffplaisance/jeffmq
| [Monday 16 August 2010] [07:49:53] <sustrik>    AMQP on top of 0MQ?
| [Monday 16 August 2010] [08:39:56] <pieterh>    sustrik: nice find, I've added it to http://www.zeromq.org/docs:labs
| [Monday 16 August 2010] [09:04:31] <pieterh>    sustrik: i have a strange case of message loss, can i ask you for help?
| [Monday 16 August 2010] [09:04:37] <sustrik>    sure
| [Monday 16 August 2010] [09:04:42] <sustrik>    what happened?
| [Monday 16 August 2010] [09:04:49] <pieterh>    ok, three programs in a pipeline
| [Monday 16 August 2010] [09:04:50] <pieterh>    http://gist.github.com/526909
| [Monday 16 August 2010] [09:05:14] <pieterh>    the worker does this 'receive from two sockets' thing
| [Monday 16 August 2010] [09:05:27] <pieterh>    simply creating/binding a second socket causes message loss
| [Monday 16 August 2010] [09:05:40] <pieterh>    if you run taskvent, taskwork, tasksink and then start it, you will see
| [Monday 16 August 2010] [09:05:46] <pieterh>    should do 100 tasks
| [Monday 16 August 2010] [09:06:25] <pieterh>    if the '#if/#endif' in the worker is removed, it does 100 tasks but only 50 get to the sink
| [Monday 16 August 2010] [09:07:20] <pieterh>    if i run the code as its shown in the gist, the worker doesn't get all messages
| [Monday 16 August 2010] [09:07:53] <pieterh>    thx
| [Monday 16 August 2010] [09:12:29] <sustrik>    pieterh: the second program
| [Monday 16 August 2010] [09:12:34] <pieterh>    yes?
| [Monday 16 August 2010] [09:12:37] <sustrik>    you send messages then  you exit
| [Monday 16 August 2010] [09:12:44] <sustrik>    those not already sent will be dropped
| [Monday 16 August 2010] [09:13:13] <pieterh>    ah... of course, it'll give EAGAIN and the loop will exit
| [Monday 16 August 2010] [09:13:32] <pieterh>    hang on, no
| [Monday 16 August 2010] [09:13:43] <pieterh>    it loops forever, there's no exit except on real errors
| [Monday 16 August 2010] [09:13:43] <sustrik>    it'll give OK
| [Monday 16 August 2010] [09:14:04] <pieterh>    which is the 'second' program?
| [Monday 16 August 2010] [09:14:20] <pieterh>    taskwork?
| [Monday 16 August 2010] [09:14:23] <sustrik>    "task ventilator"
| [Monday 16 August 2010] [09:14:37] <sustrik>    taksevent.xc
| [Monday 16 August 2010] [09:14:38] <sustrik>    c
| [Monday 16 August 2010] [09:14:47] <pieterh>    right... ok
| [Monday 16 August 2010] [09:14:58] <pieterh>    let me add the necessary sleep to that
| [Monday 16 August 2010] [09:15:03] <sustrik>    ack
| [Monday 16 August 2010] [09:15:24] <sustrik>    this should work when the big patch i woked on last weeks is merged though
| [Monday 16 August 2010] [09:15:30] <sustrik>    next release presuambly
| [Monday 16 August 2010] [09:16:53] <pieterh>    ok, this solves one problem but not the weird one
| [Monday 16 August 2010] [09:17:07] <pieterh>    tasks now get to the worker properly (this happened most of the time anyhow)
| [Monday 16 August 2010] [09:17:21] <pieterh>    the sink only gets half the result messages
| [Monday 16 August 2010] [09:17:25] <pieterh>    1 in 2 get dropped
| [Monday 16 August 2010] [09:18:22] <pieterh>    it is not systematic :-(
| [Monday 16 August 2010] [09:19:32] <pieterh>    hah!
| [Monday 16 August 2010] [09:19:37] <sustrik>    found it?
| [Monday 16 August 2010] [09:19:47] <pieterh>    well, doing this:
| [Monday 16 August 2010] [09:19:47] <pieterh>        control = zmq_socket (context, ZMQ_SUB);
| [Monday 16 August 2010] [09:19:48] <pieterh>        zmq_connect (output, "tcp://localhost:5559");
| [Monday 16 August 2010] [09:19:48] <pieterh>        zmq_setsockopt (control, ZMQ_SUBSCRIBE, "", 0);
| [Monday 16 August 2010] [09:19:58] <pieterh>    causes outputs to be lost, whereas when that is commented out, it works
| [Monday 16 August 2010] [09:20:07] <pieterh>    systematically, at least on my box
| [Monday 16 August 2010] [09:20:15] <pieterh>    this is in the taskwork program
| [Monday 16 August 2010] [09:21:29] <sustrik>    the control socket is never used in the program, right?
| [Monday 16 August 2010] [09:21:33] <pieterh>    nope
| [Monday 16 August 2010] [09:21:46] <pieterh>    the connect is the critical thing
| [Monday 16 August 2010] [09:22:30] <sustrik>    i mean, the control socket is just opened and never used
| [Monday 16 August 2010] [09:22:35] <pieterh>    yes, that's right
| [Monday 16 August 2010] [09:22:48] <sustrik>    that's strange
| [Monday 16 August 2010] [09:22:49] <pieterh>    if i don't do the connect, it works
| [Monday 16 August 2010] [09:23:16] <pieterh>    the setsockopt() is innocent
| [Monday 16 August 2010] [09:23:24] <pieterh>    it loses exactly 1 message in two
| [Monday 16 August 2010] [09:24:02] <sustrik>    what do the workers say?
| [Monday 16 August 2010] [09:24:13] <sustrik>    are they processing messages?
| [Monday 16 August 2010] [09:24:16] <pieterh>    the workers process 100 tasks and send 100 results
| [Monday 16 August 2010] [09:24:21] <pieterh>    the sink receives 50 results
| [Monday 16 August 2010] [09:24:22] <sustrik>    hm
| [Monday 16 August 2010] [09:24:53] <pieterh>    it looks like a bug in 0MQ, to be honest
| [Monday 16 August 2010] [09:25:08] <pieterh>    let me try opening a 3rd random socket
| [Monday 16 August 2010] [09:25:08] <sustrik>    yes, it does
| [Monday 16 August 2010] [09:25:28] <sustrik>    the workers end up looping forever, right?
| [Monday 16 August 2010] [09:25:58] <pieterh>    hang on... lol
| [Monday 16 August 2010] [09:26:04] <pieterh>    sorry, mea culpa
| [Monday 16 August 2010] [09:26:04] <sustrik>    !!
| [Monday 16 August 2010] [09:26:05] <sustrik>        control = zmq_socket (context, ZMQ_SUB);
| [Monday 16 August 2010] [09:26:05] <sustrik>        zmq_connect (output, "tcp://localhost:5559");
| [Monday 16 August 2010] [09:26:05] <sustrik>        zmq_setsockopt (control, ZMQ_SUBSCRIBE, "", 0);
| [Monday 16 August 2010] [09:26:10] <pieterh>    i'm connecting the /output/ not the /control/ socket!
| [Monday 16 August 2010] [09:26:15] <pieterh>    fairqueuing of results... lol
| [Monday 16 August 2010] [09:26:23] <sustrik>    :)
| [Monday 16 August 2010] [09:26:39] <pieterh>    could 0MQ not detect this kind of misconnection, it's illegal...
| [Monday 16 August 2010] [09:26:51] <pieterh>    perhaps add the peer socket type in opening message
| [Monday 16 August 2010] [09:26:54] <sustrik>    uncompatible socket types?
| [Monday 16 August 2010] [09:26:57] <pieterh>    yeah
| [Monday 16 August 2010] [09:26:59] <sustrik>    yes, it should
| [Monday 16 August 2010] [09:27:10] <pieterh>    ok, let's add that to the 3.0 wishlist
| [Monday 16 August 2010] [09:27:14] <sustrik>    ack
| [Monday 16 August 2010] [09:27:22] <pieterh>    nice! thanks, martin
| [Monday 16 August 2010] [09:28:39] <sustrik>    you are welcome
| [Monday 16 August 2010] [09:45:32] <pieterh>    sustrik: just to confirm, it all works perfectly, including reading from two sockets
| [Monday 16 August 2010] [09:45:34] <pieterh>    thanks... :-)
| [Monday 16 August 2010] [09:48:12] <sustrik>    it's part of the user guide or a separate tutorial?
| [Monday 16 August 2010] [10:01:26] <pieterh>    sustrik: this is in the guide
| [Monday 16 August 2010] [10:01:45] <pieterh>    what i might do later is separate the different examples into mini-tutorials
| [Monday 16 August 2010] [10:01:49] <pieterh>    they are fairly self-contained
| [Monday 16 August 2010] [10:02:16] <sustrik>    ok
| [Monday 16 August 2010] [10:02:46] <pieterh>    i'm reorganizing the guide so that it develops more and more complex examples, each time illustrating some aspects
| [Monday 16 August 2010] [10:26:04] <sustrik>    ack
| [Monday 16 August 2010] [18:51:03] <pieterh>    sustrik: not sure if you're still around but on the off-chance...
| [Monday 16 August 2010] [18:51:17] <pieterh>    are the built-in forwarder/streamer devices multipart safe?
| [Monday 16 August 2010] [18:51:47] <pieterh>    it looks like they
| [Monday 16 August 2010] [18:51:59] <pieterh>    *they'll read multipart messages but not send them correctly
| [Monday 16 August 2010] [19:30:51] <JohnMcL>    Can anyone here tell me the scoop on cross-compiling ZeroMQ?
| [Monday 16 August 2010] [19:31:14] <JohnMcL>    Web site makes reference to CMake... but seems to be lissing a key config file
| [Monday 16 August 2010] [19:31:21] <JohnMcL>    missing
| [Monday 16 August 2010] [19:36:07] <pieterh>    JohnMcL: sorry, never tried that 
| [Monday 16 August 2010] [21:47:38] <sustrik>    pieterh: there's a bug there
| [Monday 16 August 2010] [21:47:39] <sustrik>    fix is on the mailing list
| [Monday 16 August 2010] [21:47:47] <sustrik>    sent by jon dyte yesterdat
| [Monday 16 August 2010] [21:47:51] <sustrik>    yesterday
| [Monday 16 August 2010] [21:48:13] <jhawk28>    hello, does anyone know if the Java bindings can compile on the mac?
| [Monday 16 August 2010] [21:49:58] <jhawk28>    I'm getting this error: http://pastebin.com/Vng9YCNn
| [Tuesday 17 August 2010] [04:43:19] <pieterh>   sustrik: just saw that now, it didn't register...
| [Tuesday 17 August 2010] [04:43:38] <sustrik>   ok
| [Tuesday 17 August 2010] [05:42:25] <shekispeaks>   hi i am trying to install the Java Bindings on my mac
| [Tuesday 17 August 2010] [05:42:25] <shekispeaks>   a
| [Tuesday 17 August 2010] [05:42:38] <shekispeaks>   the ./configure always says JAVA_HOME not set
| [Tuesday 17 August 2010] [05:42:46] <shekispeaks>   i already have it set
| [Tuesday 17 August 2010] [05:42:52] <shekispeaks>   I am using java 1.6+
| [Tuesday 17 August 2010] [05:48:54] <sustrik>   skekispeaks: try to locate jni.h on your box
| [Tuesday 17 August 2010] [05:48:58] <sustrik>   where does it reside?
| [Tuesday 17 August 2010] [05:49:44] <shekispeaks>   should i point JAVA_HOME to that directory or its parent?
| [Tuesday 17 August 2010] [05:49:54] <sustrik>   its parent
| [Tuesday 17 August 2010] [05:49:55] <shekispeaks>   "/System/Library/Frameworks/JavaVM.framework/Home/include
| [Tuesday 17 August 2010] [05:50:07] <sustrik>   point it to Home
| [Tuesday 17 August 2010] [05:50:20] <shekispeaks>   ya JAVA_HOME is already set to Home still the config always throws the same error
| [Tuesday 17 August 2010] [05:50:42] <sustrik>   what's exactly the error?
| [Tuesday 17 August 2010] [05:51:43] <sustrik>   there's this in the configure.in:
| [Tuesday 17 August 2010] [05:51:44] <sustrik>   if test "x$JAVA_HOME" = "x"; then
| [Tuesday 17 August 2010] [05:51:44] <sustrik>       AC_MSG_ERROR([the JAVA_HOME environment variable must be set to your JDK location.]);
| [Tuesday 17 August 2010] [05:51:44] <sustrik>   fi
| [Tuesday 17 August 2010] [05:52:04] <sustrik>   so if that's the message you are seeing
| [Tuesday 17 August 2010] [05:52:21] <sustrik>   it looks like $JAVA_HOME resolves into empty string
| [Tuesday 17 August 2010] [05:53:56] <shekispeaks>   abhishek:jzmq abhishekk$ echo $JAVA_HOME
| [Tuesday 17 August 2010] [05:54:43] <shekispeaks>   "/System/Library/Frameworks/JavaVM.framework/Home"
| [Tuesday 17 August 2010] [05:54:49] <shekispeaks>   this is the variable
| [Tuesday 17 August 2010] [05:54:59] <shekispeaks>   and the next command is ./configure
| [Tuesday 17 August 2010] [05:55:27] <shekispeaks>   it ends in configure: error: the JAVA_HOME environment variable must be set to your JDK location.
| [Tuesday 17 August 2010] [05:56:03] <shekispeaks>   the variable is set
| [Tuesday 17 August 2010] [06:10:23] <pieterh>   shekispeaks: try 'export JAVA_HOME'
| [Tuesday 17 August 2010] [06:10:45] <shekispeaks>   i have exported it
| [Tuesday 17 August 2010] [06:11:42] <pieterh>   I'd suggest: edit configure script to echo $JAVA_HOME or 'set > vars' before error message
| [Tuesday 17 August 2010] [06:11:45] <shekispeaks>   abhishek:pyzmq abhishekk$ export JAVA_HOME=/System/Library/Frameworks/JavaVM.framework/Home
| [Tuesday 17 August 2010] [06:11:45] <shekispeaks>   abhishek:pyzmq abhishekk$ echo $JAVA_HOME
| [Tuesday 17 August 2010] [06:11:46] <shekispeaks>   "/System/Library/Frameworks/JavaVM.framework/Home"
| [Tuesday 17 August 2010] [06:12:40] <pieterh>   shekispeaks: not sure you can do export like that, try 'set JAVA_HOME=...; export JAVA_HOME'
| [Tuesday 17 August 2010] [06:14:51] <pieterh>   sustrik: is there any valid semantic in doing a blocking recv on a SUB socket with zero subscriptions?
| [Tuesday 17 August 2010] [06:15:49] <sustrik>   yes
| [Tuesday 17 August 2010] [06:15:53] <sustrik>   waiting for ETERM
| [Tuesday 17 August 2010] [06:16:13] <shekispeaks>   both set export does not work
| [Tuesday 17 August 2010] [06:16:22] <shekispeaks>   even though the variable is set in the shell
| [Tuesday 17 August 2010] [06:16:31] <shekispeaks>   it is printing a null in the script
| [Tuesday 17 August 2010] [06:17:07] <sustrik>   what about JAVA_HOME="/System/Library/Frameworks/JavaVM.framework/Home ./configure
| [Tuesday 17 August 2010] [06:17:28] <sustrik>   JAVA_HOME="/System/Library/Frameworks/JavaVM.framework/Home" ./configure
| [Tuesday 17 August 2010] [06:17:47] <pieterh>   shekispeaks: Darwin weirdness...  are you using any non-standard shell?
| [Tuesday 17 August 2010] [06:18:07] <pieterh>   sustrik: isn't that an abuse of the SUB semantics?  If you want to wait for ETERM, surely there are more explicit ways
| [Tuesday 17 August 2010] [06:18:31] <pieterh>   such as bind to private inproc endpoint and recv on it
| [Tuesday 17 August 2010] [06:20:47] <shekispeaks>   ok i just set the variable in the config script and it ran
| [Tuesday 17 August 2010] [06:21:04] <sustrik>   pieter: yes, you are right
| [Tuesday 17 August 2010] [06:21:11] <sustrik>   waiting for ETRM using recv is silly
| [Tuesday 17 August 2010] [06:21:30] <pieterh>   sustrik: i'd like to propose that blocking recv on SUB with no subscriptions is a semantic error -> assertion
| [Tuesday 17 August 2010] [06:22:14] <pieterh>   not even worth returning an error code, an app that does this should fail quickly
| [Tuesday 17 August 2010] [06:22:47] <pieterh>   let me throw this suggestion to the dev list...
| [Tuesday 17 August 2010] [06:56:35] <pieterh>   sustrik: the XML parser in foreign, it's only for devices, right?
| [Tuesday 17 August 2010] [07:05:17] <sustrik>   pieterh: yes, not used elsewhere so far
| [Tuesday 17 August 2010] [07:05:34] <pieterh>   i'd like to use libconfig as a 'standard' way of reading config files
| [Tuesday 17 August 2010] [07:05:53] <sustrik>   what's that?
| [Tuesday 17 August 2010] [07:06:07] <pieterh>   its a pretty standard library for parsing config files
| [Tuesday 17 August 2010] [07:06:13] <pieterh>   http://www.hyperrealm.com/libconfig/libconfig_manual.html
| [Tuesday 17 August 2010] [07:06:17] <pieterh>   the 0MQ of config files
| [Tuesday 17 August 2010] [07:06:38] <pieterh>   it would absolve us of having that foreign package
| [Tuesday 17 August 2010] [07:07:23] <pieterh>   i want to document how to use that to configure a device process
| [Tuesday 17 August 2010] [07:08:03] <sustrik>   for version 3.0?
| [Tuesday 17 August 2010] [07:08:06] <pieterh>   advantage of libconfig is lots of language support and standard package on many linuxes
| [Tuesday 17 August 2010] [07:08:11] <pieterh>   for version 2.1, I think
| [Tuesday 17 August 2010] [07:08:26] <pieterh>   devices were not documented up to now
| [Tuesday 17 August 2010] [07:08:41] <sustrik>   two problems i see:
| [Tuesday 17 August 2010] [07:08:49] <sustrik>   1. one more dependency
| [Tuesday 17 August 2010] [07:09:03] <sustrik>   what platforms it is supported on?
| [Tuesday 17 August 2010] [07:09:10] <sustrik>   you have to check
| [Tuesday 17 August 2010] [07:09:12] <pieterh>   1. yes, but only for main devices
| [Tuesday 17 August 2010] [07:09:15] <pieterh>   2. pretty much everything
| [Tuesday 17 August 2010] [07:09:19] <sustrik>   OpenVMS?
| [Tuesday 17 August 2010] [07:09:49] <sustrik>   2. it breaks backward compatibility, so be careful
| [Tuesday 17 August 2010] [07:09:56] <pieterh>   The library runs on modern POSIX-compilant systems, such as Linux, Solaris, and Mac OS X (Darwin), as well as on Microsoft Windows 2000/XP and later
| [Tuesday 17 August 2010] [07:10:22] <pieterh>   2. we can leave the XML library in there until 3.0, for sure
| [Tuesday 17 August 2010] [07:10:40] <pieterh>   but it's a long term maintenance cost
| [Tuesday 17 August 2010] [07:10:54] <sustrik>   it was never changed since it was included
| [Tuesday 17 August 2010] [07:10:58] <pieterh>   yes, it was
| [Tuesday 17 August 2010] [07:11:03] <pieterh>   i made several security fixes
| [Tuesday 17 August 2010] [07:11:07] <sustrik>   i had to revert your changes
| [Tuesday 17 August 2010] [07:11:12] <pieterh>   ah
| [Tuesday 17 August 2010] [07:11:14] <sustrik>   they broke win32 build
| [Tuesday 17 August 2010] [07:11:21] <pieterh>   kind of proves my poibnt
| [Tuesday 17 August 2010] [07:11:23] <pieterh>   *point
| [Tuesday 17 August 2010] [07:11:36] <pieterh>   anyhow, i don't like xml config files (after using them for years!)
| [Tuesday 17 August 2010] [07:11:45] <sustrik>   as i said, it's up to
| [Tuesday 17 August 2010] [07:11:46] <pieterh>   any non-trivial 0MQ application will have dependencies
| [Tuesday 17 August 2010] [07:12:19] <sustrik>   if you don't care about exotic platforms and possible dependency problems, just do ti
| [Tuesday 17 August 2010] [07:12:27] <pieterh>   in fact... i'm thinking we don't need standard external device programs
| [Tuesday 17 August 2010] [07:12:46] <pieterh>   just zmq_device(3) and decent docs on how to write your own
| [Tuesday 17 August 2010] [07:12:56] <pieterh>   so I'd like to make a tutorial on how to write devices
| [Tuesday 17 August 2010] [07:13:05] <pieterh>   (already have most of that)
| [Tuesday 17 August 2010] [07:13:08] <pieterh>   in the guide
| [Tuesday 17 August 2010] [07:13:22] <sustrik>   yes, it's convenience stuff
| [Tuesday 17 August 2010] [07:13:25] <sustrik>   ok
| [Tuesday 17 August 2010] [07:13:32] <pieterh>   ok, great
| [Tuesday 17 August 2010] [07:14:03] <sustrik>   we can for example split pre-compiled into a separate project
| [Tuesday 17 August 2010] [07:14:11] <pieterh>   i think it's important that 0MQ users understand the internals of devices rapidly
| [Tuesday 17 August 2010] [07:14:21] <pieterh>   and write their own
| [Tuesday 17 August 2010] [07:14:24] <sustrik>   leaving 0mq to be what it is supposed to be, i.e. library
| [Tuesday 17 August 2010] [07:14:26] <pieterh>   indeed
| [Tuesday 17 August 2010] [07:14:41] <pieterh>   that turns zmq_deviced(1) into a worked example
| [Tuesday 17 August 2010] [07:14:46] <pieterh>   and template code that's trivial to reuse
| [Tuesday 17 August 2010] [07:15:04] <pieterh>   we don't need a separate project at all ... if you build the Guide you get these examples running
| [Tuesday 17 August 2010] [07:15:12] <pieterh>   it's all on github now
| [Tuesday 17 August 2010] [07:15:29] <pieterh>   this simplifies the packaging
| [Tuesday 17 August 2010] [07:15:36] <sustrik>   it's up to you
| [Tuesday 17 August 2010] [07:15:54] <sustrik>   precompiled devices may be handy sometimes though
| [Tuesday 17 August 2010] [07:15:57] <pieterh>   for me, when we can remove things, we should
| [Tuesday 17 August 2010] [07:16:11] <pieterh>   always make it lighter
| [Tuesday 17 August 2010] [07:16:45] <pieterh>   http://www.zeromq.org/docs:user-guide#toc24
| [Tuesday 17 August 2010] [07:16:56] <pieterh>   it is 20 lines of C
| [Tuesday 17 August 2010] [07:17:57] <pieterh>   for me, having precompiled devices actually became a barrier to understanding how they work
| [Tuesday 17 August 2010] [07:18:02] <sustrik>   actually, yes
| [Tuesday 17 August 2010] [07:18:11] <sustrik>   full blown devices can be stand alone projects
| [Tuesday 17 August 2010] [07:18:14] <pieterh>   yes
| [Tuesday 17 August 2010] [07:18:42] <pieterh>   i like this, it solves a number of things I was wondering about
| [Tuesday 17 August 2010] [07:19:19] <sustrik>   hm, inproc devices may become an annoyance
| [Tuesday 17 August 2010] [07:19:29] <sustrik>   rewriting same 20 lines of code over and over again
| [Tuesday 17 August 2010] [07:20:17] <pieterh>   what's an inproc device?
| [Tuesday 17 August 2010] [07:20:38] <sustrik>   zmq_device()
| [Tuesday 17 August 2010] [07:20:52] <sustrik>   have a look at mutli-threaded server example
| [Tuesday 17 August 2010] [07:20:57] <pieterh>   yes
| [Tuesday 17 August 2010] [07:21:04] <pieterh>   what's the code we're rewriting over and over?
| [Tuesday 17 August 2010] [07:21:18] <pieterh>   calling these inbuilt devices?
| [Tuesday 17 August 2010] [07:21:22] <sustrik>   queue.cpp forwarder.cpp streamer.cpp
| [Tuesday 17 August 2010] [07:21:59] <pieterh>   it's not clear to me
| [Tuesday 17 August 2010] [07:22:18] <pieterh>   otoh it's useful to have properly engineered devices there
| [Tuesday 17 August 2010] [07:22:28] <pieterh>   otoh, there's nothing special about these and why are they in the core?
| [Tuesday 17 August 2010] [07:22:36] <sustrik>   exactly
| [Tuesday 17 August 2010] [07:22:44] <sustrik>   it's clean vs. usable
| [Tuesday 17 August 2010] [07:22:48] <pieterh>   i'd rather, for example, have a reactor in the core
| [Tuesday 17 August 2010] [07:22:48] <sustrik>   a tradeoff
| [Tuesday 17 August 2010] [07:22:57] <pieterh>   and then implement devices using that
| [Tuesday 17 August 2010] [07:23:05] <pieterh>   a reactor is a generic tool
| [Tuesday 17 August 2010] [07:23:34] <sustrik>   dunno, i have no real opinion, ask on the list
| [Tuesday 17 August 2010] [07:24:06] <pieterh>   well, it works for now, i'd rather solve real problems
| [Tuesday 17 August 2010] [07:24:16] <sustrik>   ok
| [Tuesday 17 August 2010] [07:24:28] <pieterh>   if there really is an issue it'll become clear sooner or later
| [Tuesday 17 August 2010] [07:25:28] <sustrik>   yes, solving real problems makes the design cleaner than theoretical messing with the design
| [Tuesday 17 August 2010] [07:38:43] <rbraley>   http://www.cs.wustl.edu/~schmidt/PDF/proactor.pdf I'd prefer proactor to reactor
| [Tuesday 17 August 2010] [07:53:12] <pieterh>   rbraley: excellent idea, I'm curious to see what you make... 
| [Tuesday 17 August 2010] [07:57:11] <rbraley>   I have an interview with Google tomorrow so I've been busy studying the best algorithms and data structures I could find. Haven't had much time to implement a proactor system for 0mq.
| [Tuesday 17 August 2010] [07:57:27] <rbraley>   I would like to, however
| [Tuesday 17 August 2010] [07:57:55] <keffo_>    lol, everyone gets a call from google at some point :)
| [Tuesday 17 August 2010] [07:58:43] <rbraley>   I have some pretty ambitious ideas using 0mq 
| [Tuesday 17 August 2010] [07:59:53] <rbraley>   such as implementing an octree for a game engine made of many communicating entities via the prefix of PUB/SUB connections
| [Tuesday 17 August 2010] [08:01:41] <rbraley>   a mostly asynchronous game engine at that based on the actor model or communicating sequential processes depending on which is a better fit
| [Tuesday 17 August 2010] [08:03:21] <keffo_>    a bup/sub based distributed octree?
| [Tuesday 17 August 2010] [08:04:44] <rbraley>   yessir keffo, a prefix will allow entities to only listen to events from nearby in their game region
| [Tuesday 17 August 2010] [08:06:45] <keffo_>    you mean over inproc I hope?
| [Tuesday 17 August 2010] [08:07:19] <rbraley>   yes
| [Tuesday 17 August 2010] [08:07:41] <keffo_>    imo an octree is a poor choice to begin with.. 
| [Tuesday 17 August 2010] [08:07:55] <rbraley>   it wouldn't have to be an octree
| [Tuesday 17 August 2010] [08:08:36] <keffo_>    gvh would fit much better
| [Tuesday 17 August 2010] [08:08:40] <keffo_>    oops, bvh
| [Tuesday 17 August 2010] [08:09:31] <keffo_>    that's besides the point though... You want to publish 'presense' for a region, or something like that?
| [Tuesday 17 August 2010] [08:10:10] <rbraley>   presense?
| [Tuesday 17 August 2010] [08:11:20] <keffo_>    yeah, not fully clear on what you mean :)
| [Tuesday 17 August 2010] [08:11:52] <rbraley>   every game entity would be a composition of components
| [Tuesday 17 August 2010] [08:12:18] <rbraley>   each component would publish events 
| [Tuesday 17 August 2010] [08:12:41] <keffo_>    yeah, that's what I meant, for instance "I entered this region", or something like that?
| [Tuesday 17 August 2010] [08:12:46] <rbraley>   yeah
| [Tuesday 17 August 2010] [08:14:25] <rbraley>   it is an idea I want to refine further, perhaps you'd be interested in helping me think it through?
| [Tuesday 17 August 2010] [08:15:24] <keffo_>    So for example (with a simple 2d grid here), an 'enemy' would subscribe to a topic which would be it's gridindex, and a 'player' would publish it's presese using the same gridindex-topic, triggerin for instance an 'attack' event in the 'enemy'? Something like that?
| [Tuesday 17 August 2010] [08:15:55] <rbraley>   yes
| [Tuesday 17 August 2010] [08:16:01] <keffo_>    not an entirely bad idea, would remove the need for entities to have an active role
| [Tuesday 17 August 2010] [08:16:07] <rbraley>   although a bit more circuitous
| [Tuesday 17 August 2010] [08:16:15] <keffo_>    other than pubish what they're doing, sortof
| [Tuesday 17 August 2010] [08:16:33] <rbraley>   the AI component would subscribe to the local region looking for things to react to
| [Tuesday 17 August 2010] [08:16:54] <rbraley>   then decide what to do based on that
| [Tuesday 17 August 2010] [08:18:01] <keffo_>    But this would again rely on the fact that the subscriber does the topicfiltering, not the publisher.. That's a major waste of resources..  If the filtering happened on the publisher, it would mean all entities would be completely idle until it reacts to something
| [Tuesday 17 August 2010] [08:18:11] <rbraley>   entities' components would ideally do most of the publishing and subscribing for them
| [Tuesday 17 August 2010] [08:19:51] <rbraley>   yes I'll need to take that into account
| [Tuesday 17 August 2010] [08:21:34] <keffo_>    not sure I see how the octree would fit in though
| [Tuesday 17 August 2010] [08:21:46] <rbraley>   the entities could be completely asynchronous if they published messages with deltas of their variables and a timestamp, then the renderer could do a finite difference to intepolate a valid game state to render
| [Tuesday 17 August 2010] [08:22:04] <rbraley>   every entity would then not need to update each "frame"
| [Tuesday 17 August 2010] [08:22:29] <keffo_>    they probably do more than just wait though
| [Tuesday 17 August 2010] [08:22:34] <keffo_>    animations and such
| [Tuesday 17 August 2010] [08:23:03] <rbraley>   that could be hidden away in the render component
| [Tuesday 17 August 2010] [08:23:24] <rbraley>   only when animations change would the entities themselves need to publish a change
| [Tuesday 17 August 2010] [08:23:45] <keffo_>    most game engines already treat entities in an async fashion to begin with
| [Tuesday 17 August 2010] [08:23:51] <keffo_>    the ones Ive worked on anyway
| [Tuesday 17 August 2010] [08:24:33] <keffo_>    fibers/coroutines/etc
| [Tuesday 17 August 2010] [08:24:59] <rbraley>   most game engines don't have entities as simply compositions of components though, most of them are designed with deep inheritance hierarchies
| [Tuesday 17 August 2010] [08:25:49] <keffo_>    that's mostly a sideeffect of people insisting on inherently oo languages though :)
| [Tuesday 17 August 2010] [08:26:58] <rbraley>   heh, it is more a side-effect of people's thinking. Composition is favored over inheritance by OO gurus anyway.
| [Tuesday 17 August 2010] [08:27:05] <pieterh>   keffo_:, rbraley: you familiar with the http://www.bitsquid.se project?
| [Tuesday 17 August 2010] [08:27:18] <pieterh>   different kind of game engine, maybe
| [Tuesday 17 August 2010] [08:27:21] <keffo_>    yes
| [Tuesday 17 August 2010] [08:27:38] <keffo_>    not really, it's where most engines tend to go towards
| [Tuesday 17 August 2010] [08:27:59] <pieterh>   seems 0MQ makes a natural fabric for game engines
| [Tuesday 17 August 2010] [08:28:01] <keffo_>    valve & unreal etc, are all stuck in the quake engine swamp though
| [Tuesday 17 August 2010] [08:28:05] <rbraley>   oooh
| [Tuesday 17 August 2010] [08:28:24] <rbraley>   pieterh, I will dig into this
| [Tuesday 17 August 2010] [08:29:36] <pieterh>   rbraley: i spoke to the bitsquid guys about 0MQ and they were "nah, messaging is too heavy, we'd rather do concurrency ourselves"
| [Tuesday 17 August 2010] [08:30:02] <keffo_>    lol, they already do json fiddling for that :)
| [Tuesday 17 August 2010] [08:30:23] <keffo_>    the whole industry seems to move towards msg passing for concurrency anyway
| [Tuesday 17 August 2010] [08:30:32] <keffo_>    for good reason, obviously
| [Tuesday 17 August 2010] [08:30:33] <pieterh>   there's not a lot of choice
| [Tuesday 17 August 2010] [08:30:36] <pieterh>   yeah
| [Tuesday 17 August 2010] [08:31:07] <keffo_>    valve employs a more worker oriented threading model now
| [Tuesday 17 August 2010] [08:31:54] <rbraley>   hehe you really need a messaging infrastructure for more than task parallelism
| [Tuesday 17 August 2010] [08:32:07] <keffo_>    "The BitSquid engine accomplishes this by being completely job-based with no explicit thread synchronization points except the mandated frame flipping. Jobs operate on abstract data streams of simple struct data, which enables them to run transparently on co-processors through DMA transfer"
| [Tuesday 17 August 2010] [08:32:23] <keffo_>    I dont see how that could be anything other than msg passing, to be honest..
| [Tuesday 17 August 2010] [08:33:18] <rbraley>   it's about time message passing came into use, it's been 40 years
| [Tuesday 17 August 2010] [08:34:02] <rbraley>   and moore's law isn't a free ride anymore
| [Tuesday 17 August 2010] [08:35:09] <keffo_>    hehe no
| [Tuesday 17 August 2010] [08:36:13] <keffo_>    pieterh, Reading their blog, specifically http://bitsquid.blogspot.com/2010/03/task-management-practical-example.html, I dont understand their comment they gave to you..
| [Tuesday 17 August 2010] [08:36:30] <pieterh>   standard NIH syndrome
| [Tuesday 17 August 2010] [08:36:36] <pieterh>   they admitted they'd not looked at 0MQ in detail
| [Tuesday 17 August 2010] [08:37:12] <keffo_>    the game industry here isn't that big, odds are I'll run into them at some point (if I havent already, not sure)
| [Tuesday 17 August 2010] [08:37:55] <keffo_>    that blogpost isnt entirely far off from what I'm doing actually, except much more general and large scale (not purely a multithreading remedy)
| [Tuesday 17 August 2010] [08:39:06] <keffo_>    I prefer to see it as a 'distributed dependency graph of code' though :)
| [Tuesday 17 August 2010] [08:39:35] <rbraley>   keffo_,  some links to our game http://dungeonhack.sf.net http://dungeonhack.sourceforge.net/forums/viewtopic.php?f=2&t=744 http://dungeonhack.sourceforge.net/forums/viewtopic.php?f=2&t=794
| [Tuesday 17 August 2010] [08:41:18] <keffo_>    nice
| [Tuesday 17 August 2010] [08:41:41] <keffo_>    sadly, with most opensource game projects, it fails on artistry, not code :)
| [Tuesday 17 August 2010] [08:41:43] <rbraley>   I see ZeroMQ as a large part of this, so I will probably need to make another addendum to the new game architecture once a design is worked out
| [Tuesday 17 August 2010] [08:41:46] <keffo_>    no idea why that is though
| [Tuesday 17 August 2010] [08:41:55] <pieterh>   would either of you guys like to write a little blog post about 0MQ and game engines?
| [Tuesday 17 August 2010] [08:42:15] <rbraley>   keffo_, I am actively recruiting artists ;)
| [Tuesday 17 August 2010] [08:44:16] <keffo_>    pieterh, I'd love to once I get more work done..  The main usage for my stuff now is a generic job framework, which I'll use to build "game-oriented" tools and plugins for modelling packages like 3dsmax/maya/zbrush etc.. not directly game engine
| [Tuesday 17 August 2010] [08:44:35] <keffo_>    currently calculating PI though :)
| [Tuesday 17 August 2010] [08:45:04] <rbraley>   pieterh, yeah I would be interested, but I'd need to have a more solid grasp of 0MQ and how I'd use it. I'll probably have one up on the dungeonhack forums when I am ready. I would happily put it on your blog too, with appropriate edits.
| [Tuesday 17 August 2010] [08:46:11] <pieterh>   rbraley: even if it's just speculative, it'd be nice to have some public discussion of 0MQ's potential for new generation game engines
| [Tuesday 17 August 2010] [08:46:17] <pieterh>   np
| [Tuesday 17 August 2010] [08:49:48] <rbraley>   yes, that sounds great. I could do that. I'll talk to you in the coming weeks and see if I can't get that done.
| [Tuesday 17 August 2010] [08:51:02] <rbraley>   my skype is ryan.braley please add me pieterh, keffo_, and other interested parties if you have one
| [Tuesday 17 August 2010] [08:51:46] <pieterh>   if skype would work on Android, I'd use it... :-/
| [Tuesday 17 August 2010] [08:51:57] <rbraley>   it works on the droid
| [Tuesday 17 August 2010] [08:52:04] <keffo_>    maemo ftw! :)
| [Tuesday 17 August 2010] [08:52:07] <rbraley>   but I don't have it for my G1
| [Tuesday 17 August 2010] [08:52:29] <rbraley>   you could look for the .apk and see if it exists online
| [Tuesday 17 August 2010] [08:52:46] <rbraley>   but it isn't in the market unless you have a droid or something
| [Tuesday 17 August 2010] [08:53:54] <keffo_>    skype should release a lib, so people arent forced to use that awful client
| [Tuesday 17 August 2010] [08:54:21] <rbraley>   yeah
| [Tuesday 17 August 2010] [08:58:16] <AndrewBC>  Mmm, I think they did release an API recently
| [Tuesday 17 August 2010] [08:58:34] <keffo_>    really?
| [Tuesday 17 August 2010] [08:58:49] <keffo_>    not the one where you need the client running at the same time?
| [Tuesday 17 August 2010] [08:59:51] <AndrewBC>  I don't know. According to this it might be: http://developer.skype.com/accessories
| [Tuesday 17 August 2010] [08:59:57] <AndrewBC>  Which is meh.
| [Tuesday 17 August 2010] [09:00:30] <AndrewBC>  Oh, SkypeKit
| [Tuesday 17 August 2010] [09:00:37] <AndrewBC>  .. in beta.
| [Tuesday 17 August 2010] [09:00:38] <AndrewBC>  Meh.
| [Tuesday 17 August 2010] [09:00:59] <AndrewBC>  http://developer.skype.com/public/skypekit
| [Tuesday 17 August 2010] [09:02:03] <rbraley>   at least skype plays nice with linux... 64bit at that.
| [Tuesday 17 August 2010] [09:07:13] <rbraley>   well if you folks don't use skype I'll just keep in touch with you here. My entire dungeonhack team uses it ;)
| [Tuesday 17 August 2010] [09:08:57] <pieterh>   rbraley: at least this channel is public and anyone can participate
| [Tuesday 17 August 2010] [09:10:20] <rbraley>   indeed :)
| [Tuesday 17 August 2010] [09:20:11] <rbraley>   what does zmqircd do for you?
| [Tuesday 17 August 2010] [09:29:48] <pieterh>   rbraley: someone (travlr, I think) logs this channel
| [Tuesday 17 August 2010] [09:30:06] <pieterh>   sustrik: what could cause an assertion failure in rep.cpp:232?
| [Tuesday 17 August 2010] [09:33:13] <sustrik>   let me see
| [Tuesday 17 August 2010] [09:33:25] <sustrik>   trunk?
| [Tuesday 17 August 2010] [09:33:29] <sustrik>   2.0.7?
| [Tuesday 17 August 2010] [09:33:29] <pieterh>   i assume so
| [Tuesday 17 August 2010] [09:34:02] <pieterh>   reported by David Briant on zeromq-dev, did not mention what version
| [Tuesday 17 August 2010] [09:34:11] <pieterh>   that's the right line number on trunk, in any case
| [Tuesday 17 August 2010] [09:34:46] <sustrik>   no assert at that line in trunk...
| [Tuesday 17 August 2010] [09:35:03] <pieterh>   I'm looking at it now
| [Tuesday 17 August 2010] [09:35:08] <sustrik>   aha, 2.07
| [Tuesday 17 August 2010] [09:35:12] <pieterh>               //  Get next part of the message.
| [Tuesday 17 August 2010] [09:35:12] <pieterh>               bool fetched = in_pipes [current]->read (msg_);
| [Tuesday 17 August 2010] [09:35:12] <pieterh>               zmq_assert (fetched);
| [Tuesday 17 August 2010] [09:35:26] <pieterh>   maybe your recent changes on trunk shifted stuff around
| [Tuesday 17 August 2010] [09:35:57] <sustrik>   the assert basically says:
| [Tuesday 17 August 2010] [09:36:18] <sustrik>   after you've read the empty message part
| [Tuesday 17 August 2010] [09:36:29] <sustrik>   (the bottom of the backtrace stack)
| [Tuesday 17 August 2010] [09:36:52] <sustrik>   there should be at least one user-supplied message part
| [Tuesday 17 August 2010] [09:36:57] <pieterh>   sustrik: i just updated my master snapshot and it's really line 232
| [Tuesday 17 August 2010] [09:36:58] <sustrik>   the payload i mean
| [Tuesday 17 August 2010] [09:37:14] <pieterh>   right
| [Tuesday 17 August 2010] [09:37:27] <pieterh>   what could cause this message corruption in your opinion?
| [Tuesday 17 August 2010] [09:37:38] <sustrik>   either a bug in 0MQ
| [Tuesday 17 August 2010] [09:37:48] <sustrik>   or the user using XREQ with REP
| [Tuesday 17 August 2010] [09:38:16] <pieterh>   we really need a better way of catching illegal socket mixes
| [Tuesday 17 August 2010] [09:38:24] <sustrik>   and sending messages with a traceback stack but no payload
| [Tuesday 17 August 2010] [09:38:26] <pieterh>   second one sounds most plausible, thanks
| [Tuesday 17 August 2010] [09:38:47] <sustrik>   np
| [Tuesday 17 August 2010] [11:53:30] <keffo_>    or a wikipage listing all socket type combinations
| [Tuesday 17 August 2010] [12:33:25] <keffo_>    What's the common way to do heartbeat system?
| [Tuesday 17 August 2010] [12:35:07] <pieterh>   mato: you back? :-)
| [Tuesday 17 August 2010] [12:36:10] <pieterh>   keffo_: you have read http://api.zeromq.org/zmq_socket.html?
| [Tuesday 17 August 2010] [12:36:33] <pieterh>   there are no documented examples for heartbeating afaik
| [Tuesday 17 August 2010] [12:40:30] <keffo_>    I have a weird bug, just want to know I'm on the right track before I commit to it
| [Tuesday 17 August 2010] [12:42:55] <keffo_>    there are plenty of pages on the wiki I really wish were complete. like the "failover and recovery", "a clock device", "reliable req/rep" and custom loadbalancing 
| [Tuesday 17 August 2010] [12:43:05] <pieterh>   ah, you mean in the user guide?
| [Tuesday 17 August 2010] [12:43:08] <keffo_>    yeah
| [Tuesday 17 August 2010] [12:43:34] <pieterh>   it's a work in progress, fairly detailed work, every aspect needs working example code
| [Tuesday 17 August 2010] [12:43:41] <keffo_>    yeah :)
| [Tuesday 17 August 2010] [12:43:50] <pieterh>   would it help if I put "Coming soon..." in every empty section?
| [Tuesday 17 August 2010] [12:43:52] <keffo_>    custom loadbalancing is quite important imo.. :)
| [Tuesday 17 August 2010] [12:44:05] <keffo_>    not really, it's quite obvious it's not there yet :)
| [Tuesday 17 August 2010] [12:44:18] <pieterh>   "This page deliberately left blank"?
| [Tuesday 17 August 2010] [12:44:27] <pieterh>   "Insert $$$ to see this text!"
| [Tuesday 17 August 2010] [12:44:41] <keffo_>    naa, dont waste time on that, everyone gets its not done yet :)
| [Tuesday 17 August 2010] [12:44:44] <pieterh>   ah, I know... a link to somewhere to discuss that specific case
| [Tuesday 17 August 2010] [12:45:20] <pieterh>   i want a forum for the user guide, to not pollute zeromq-dev
| [Tuesday 17 August 2010] [12:45:51] <keffo_>    mmm
| [Tuesday 17 August 2010] [12:46:16] <keffo_>    irc is a fantastic place for code talk though, probably why it doesnt die off :)
| [Tuesday 17 August 2010] [12:46:30] <pieterh>   yeah, true
| [Tuesday 17 August 2010] [12:46:52] <pieterh>   mato: summon... dude, you around?
| [Tuesday 17 August 2010] [12:47:12] <keffo_>    I keep trying to figure out what I did to learn stuff before the advent of internet, and I really have no idea... guess I just bruteforced everything until it worked..
| [Tuesday 17 August 2010] [12:47:31] <pieterh>   like my son who could reconfigure the Ubuntu desktop before he was 3
| [Tuesday 17 August 2010] [12:47:38] <keffo_>    hehe :)
| [Tuesday 17 August 2010] [12:47:40] <pieterh>   just clicked on every single option
| [Tuesday 17 August 2010] [12:47:45] <keffo_>    hehe
| [Tuesday 17 August 2010] [12:48:04] <pieterh>   being able to ask for help does make us stupid sometimes
| [Tuesday 17 August 2010] [12:48:15] <keffo_>    I'd hardly call that configure though, more "apply entropy"
| [Tuesday 17 August 2010] [12:48:18] <pieterh>   mato: please, why doesn't my example compile?
| [Tuesday 17 August 2010] [12:48:53]      * keffo_ goes off to stare at boiling water, always helps to figure stuff out :)
| [Tuesday 17 August 2010] [12:49:05] <pieterh>   keffo_: I dunno, he was able to start youtube and find hello kitty videos
| [Tuesday 17 August 2010] [12:49:31] <pieterh>   anyhow, i gotta take my wife to hospital, baby arriving any time soon
| [Tuesday 17 August 2010] [12:49:34] <pieterh>   cyal
| [Tuesday 17 August 2010] [12:56:37] <mikko> http://gist.github.com/530821
| [Tuesday 17 August 2010] [12:56:45] <mikko> does the following backtrace make sense to anyone?
| [Tuesday 17 August 2010] [12:57:00] <mikko> php-zmq gets stuck on freebsd
| [Tuesday 17 August 2010] [13:06:35] <mikko> "the threading library on FreeBSD does not interact well with kqueue(); evidently, when kqueue() blocks, the entire process blocks, not just the calling thread. "
| [Tuesday 17 August 2010] [13:06:42] <mikko> is this still true with FreeBSD?
| [Tuesday 17 August 2010] [13:07:59] <sustrik>   mikko: where does the backtrace come from?
| [Tuesday 17 August 2010] [13:08:22] <mikko> sustrik: gdb
| [Tuesday 17 August 2010] [13:08:40] <sustrik>   ah, you are seeing it right now, right?
| [Tuesday 17 August 2010] [13:08:45] <mikko> yes
| [Tuesday 17 August 2010] [13:08:59] <mikko> the php code effectively creates new context
| [Tuesday 17 August 2010] [13:09:06] <mikko> and that blocks until all eternity
| [Tuesday 17 August 2010] [13:09:40] <mikko> just compiling things with more symbols
| [Tuesday 17 August 2010] [13:09:49] <sustrik>   the trace is strange
| [Tuesday 17 August 2010] [13:09:57] <sustrik>   pthread_create calling thread_kill?
| [Tuesday 17 August 2010] [13:09:58] <sustrik>   hm
| [Tuesday 17 August 2010] [13:11:35] <mikko> at this point i have no idea whats going on
| [Tuesday 17 August 2010] [13:11:41] <mikko> will be back later ->
| [Tuesday 17 August 2010] [13:11:59] <sustrik>   ok
| [Tuesday 17 August 2010] [13:14:19] <mikko> http://gist.github.com/530913
| [Tuesday 17 August 2010] [13:14:22] <mikko> there is with symbols
| [Tuesday 17 August 2010] [13:19:23] <sustrik>   mikko: is it stuck
| [Tuesday 17 August 2010] [13:19:27] <sustrik>   or does it fail?
| [Tuesday 17 August 2010] [13:19:46] <sustrik>   ah, it's Ctrl+C
| [Tuesday 17 August 2010] [13:19:50] <sustrik>   silly me
| [Tuesday 17 August 2010] [13:20:25] <sustrik>   but anyway, it looks like it's stuck in pthread_create
| [Tuesday 17 August 2010] [13:23:15] <sustrik>   hm, here's something about pthread_create blocking on freebsd:
| [Tuesday 17 August 2010] [13:23:16] <sustrik>   http://markmail.org/message/xifffeeg7dpvu7iy
| [Tuesday 17 August 2010] [13:23:21] <sustrik>   message back from 2004
| [Tuesday 17 August 2010] [13:25:32] <sustrik>   some more discussion from 2008:
| [Tuesday 17 August 2010] [13:25:33] <sustrik>   http://old.nabble.com/mysterious-hang-in-pthread_create-td19209314.html
| [Tuesday 17 August 2010] [13:26:51] <sustrik>   can you possibly place a printf before and after pthread_create, just to see whether it is really stuck inside of it?
| [Tuesday 17 August 2010] [14:12:49] <mikko> sustrik: sure
| [Tuesday 17 August 2010] [14:12:56] <mikko> will start debugging properly soon
| [Tuesday 17 August 2010] [14:13:03] <mikko> just need dinner and a quick match of sc2
| [Tuesday 17 August 2010] [14:21:31] <rbraley>   you are all smart folks. Do you know if it is possible to make an event system that triggers events based on a time (like cron) without busy waiting?
| [Tuesday 17 August 2010] [14:55:28] <mikko> rbraley: libev provides that
| [Tuesday 17 August 2010] [14:55:36] <mikko> maybe check the implementation from there
| [Tuesday 17 August 2010] [14:55:42] <rbraley>   thanks
| [Tuesday 17 August 2010] [14:58:17] <mikko> sustrik: added printf debugging around line thread.cpp:66
| [Tuesday 17 August 2010] [14:58:29] <mikko> fprintf(stderr, "About to create\n");
| [Tuesday 17 August 2010] [14:58:39] <mikko> and fprintf(stderr, "Created\n");
| [Tuesday 17 August 2010] [14:58:47] <mikko> it seems to get stuck inside pthread_create
| [Tuesday 17 August 2010] [15:37:19] <pieterh>   rbraley: what kind of 'events' do you want?  messages?
| [Tuesday 17 August 2010] [16:00:49] <travlr>    keffo_: you mentioned above about custom loadbalancing being important.. could you comment further on the zeromq-dev mail list thread I started to today with the title: "Load Balancing/Distributing/Queuing Algos: A Discussion"... thanks.
| [Tuesday 17 August 2010] [16:20:25] <rbraley>   pieterh, yeah messages
| [Tuesday 17 August 2010] [16:21:48] <pieterh>   rbraley: several things come to mind
| [Tuesday 17 August 2010] [16:21:59] <pieterh>   first, you can use zmq_poll() with a timeout
| [Tuesday 17 August 2010] [16:22:24] <pieterh>   this is a pretty classic way of generating timing events internally: you calculate the delay to the next event, use that as your timeout
| [Tuesday 17 August 2010] [16:22:29] <rbraley>   doesn't poll busy wait though?
| [Tuesday 17 August 2010] [16:22:34] <pieterh>   nope
| [Tuesday 17 August 2010] [16:22:39] <rbraley>   oh
| [Tuesday 17 August 2010] [16:23:01] <pieterh>   thread just relaxes until something happens
| [Tuesday 17 August 2010] [16:23:15] <pieterh>   second, matt weinstein developed a simple protocol for timer events
| [Tuesday 17 August 2010] [16:23:57] <pieterh>   the idea is you have, somewhere on your network, a node that uses zmq_poll() to wake up every so often and send a message to a PUB socket
| [Tuesday 17 August 2010] [16:24:20] <rbraley>   nice!
| [Tuesday 17 August 2010] [16:24:32] <pieterh>   so you can imagine the timer sending an event once a second
| [Tuesday 17 August 2010] [16:24:43] <pieterh>   now you don't need to do that event time calculation everywhere
| [Tuesday 17 August 2010] [16:24:56] <pieterh>   you just SUB to the timer stream, and include that socket in your pollset
| [Tuesday 17 August 2010] [16:25:10] <pieterh>   now, matt's real neat trick 
| [Tuesday 17 August 2010] [16:25:36] <pieterh>   is every ms, send "1", except every 10ms, send "10", except every 100ms send "100" etc.
| [Tuesday 17 August 2010] [16:25:55] <pieterh>   now you subscribe to "1", "10", or "100", etc.
| [Tuesday 17 August 2010] [16:26:01] <pieterh>   giving you the resolution you need
| [Tuesday 17 August 2010] [16:26:07] <rbraley>   nice
| [Tuesday 17 August 2010] [16:26:42] <pieterh>   he doesn't use poll even, but usleep
| [Tuesday 17 August 2010] [16:29:31] <rbraley>   so to use inproc:// I'd have to have it be a separate thread in my process 
| [Tuesday 17 August 2010] [16:30:03] <pieterh>   yup
| [Tuesday 17 August 2010] [16:30:19] <pieterh>   it's a device, really
| [Tuesday 17 August 2010] [16:30:37] <rbraley>   I don't understand the idiom of devices with 0MQ
| [Tuesday 17 August 2010] [16:31:38] <pieterh>   did you read that section in the latest user guide?
| [Tuesday 17 August 2010] [16:31:53] <pieterh>   i'd like to know if it's not clear on what a device is
| [Tuesday 17 August 2010] [16:33:07] <rbraley>   I'll take a look
| [Tuesday 17 August 2010] [16:33:27] <pieterh>   Section titled "Devil's Devices"
| [Tuesday 17 August 2010] [16:35:57] <rbraley>   it was hard to find the user guide, it should be in the contents section of the nav bar
| [Tuesday 17 August 2010] [16:38:45] <pieterh>   ok, i'll add it
| [Tuesday 17 August 2010] [16:40:38] <pieterh>   done...
| [Tuesday 17 August 2010] [16:41:22] <rbraley>   awesome!
| [Tuesday 17 August 2010] [16:41:50] <rbraley>   I really like this user guide btw, the intro is inspiring
| [Tuesday 17 August 2010] [16:42:16] <travlr>    yeah i have to concur with rbraley.. you've done a really nice job with it pieter
| [Tuesday 17 August 2010] [16:44:45] <travlr>    btw, while i'm thinking about it... it would be nice if each zmq symbol could have a complete list of "properties" listed. this is more for mato's ref manual i guess
| [Tuesday 17 August 2010] [16:47:15] <pieterh>   'inspiring'? wow...
| [Tuesday 17 August 2010] [16:47:34] <pieterh>   travlr: what do you mean by 'symbol'?
| [Tuesday 17 August 2010] [16:49:33] <travlr>    pieterh, well the different socket enums like ZMQ_PUSH, etc. should be more detailed as to what is under the hood. I still am trying to figure out details of what's under the hood for different zmq infrastructure.
| [Tuesday 17 August 2010] [16:49:52] <pieterh>   ah, i get it
| [Tuesday 17 August 2010] [16:49:56] <pieterh>   a glossary :-)
| [Tuesday 17 August 2010] [16:50:13] <pieterh>   great idea, i like it
| [Tuesday 17 August 2010] [16:51:09] <pieterh>   the man pages are pretty detailed about the socket types, for example (except they say DOWNSTREAM where the Guide says PUSH)
| [Tuesday 17 August 2010] [16:51:15] <travlr>    well, not so much a glossary but a list of properties that define all the aspects of a particular symbol. there's so much beautiful magic under the hood, and mato's work is great but no complete, imo.
| [Tuesday 17 August 2010] [16:51:41] <pieterh>   imo it is complete but too brief
| [Tuesday 17 August 2010] [16:52:10] <travlr>    under the hood magic should be explicit in the ref
| [Tuesday 17 August 2010] [16:52:50] <pieterh>   do you have an example?
| [Tuesday 17 August 2010] [16:53:42] <pieterh>   i've not found anything missing from the reference manual, except xrep/xreq, and the multipart stack stuff
| [Tuesday 17 August 2010] [16:54:09] <travlr>    let me look at it again and i'll expand my thought then, ok
| [Tuesday 17 August 2010] [16:54:41] <pieterh>   if you hit things that are not explained, or poorly, just shout
| [Tuesday 17 August 2010] [16:54:46] <travlr>    ok
| [Tuesday 17 August 2010] [16:59:40] <keffo_>    travlr, I'll read it tomorrow, quite late here now :)
| [Tuesday 17 August 2010] [17:00:42] <travlr>    keffo_: thanks
| [Tuesday 17 August 2010] [17:10:41] <rbraley>   pieterh, I read the section on devices but conceptually they remain murky for me
| [Tuesday 17 August 2010] [17:10:49] <travlr>    pieterh: mato has done more work to the ref since i saw it last.. its consice and that's good. the only thing i can add right now, in general is... think of any magic that zmq does behind the scenes and if its not included there.. it should be listed there, imo.
| [Tuesday 17 August 2010] [17:11:34] <pieterh>   travlr: yes, it should be complete
| [Tuesday 17 August 2010] [17:11:51] <pieterh>   rbraley: they remained murky to me until I wrote one
| [Tuesday 17 August 2010] [17:12:10] <pieterh>   they're just applications that you embed into the network
| [Tuesday 17 August 2010] [17:12:18] <rbraley>   Devices are anything that sit between your real applications. this isn
| [Tuesday 17 August 2010] [17:12:23] <pieterh>   so reusable, stateless, part of the fabric
| [Tuesday 17 August 2010] [17:12:48] <pieterh>   think of network switches that understand 0MQ patterns
| [Tuesday 17 August 2010] [17:12:49] <rbraley>   't really enough of a one-liner zinger to explain them
| [Tuesday 17 August 2010] [17:13:04] <pieterh>   message-switching networks
| [Tuesday 17 August 2010] [17:13:29] <rbraley>   I got that analogy
| [Tuesday 17 August 2010] [17:13:50] <rbraley>   but I can't help but think that devices are more general than that
| [Tuesday 17 August 2010] [17:14:12] <pieterh>   it's not a tight classification yet, over time i suspect it will become more so
| [Tuesday 17 August 2010] [17:14:24] <pieterh>   it's about layers, imo
| [Tuesday 17 August 2010] [17:14:28] <pieterh>   zmq core is one layer
| [Tuesday 17 August 2010] [17:14:35] <pieterh>   on top of that you have devices
| [Tuesday 17 August 2010] [17:14:43] <pieterh>   and on top of those two layers you have applications
| [Tuesday 17 August 2010] [17:15:07] <pieterh>   if you make an app that is reusable and generic, it's potentially a device
| [Tuesday 17 August 2010] [17:15:39]      * pieterh is still sooo ignorant
| [Tuesday 17 August 2010] [17:16:06] <rbraley>   perhaps I should think of devices as unix commands and 0MQ sockets as pipes
| [Tuesday 17 August 2010] [17:16:20] <pieterh>   that kind of works, yes
| [Tuesday 17 August 2010] [17:16:30] <pieterh>   filters, in Unix terms
| [Tuesday 17 August 2010] [17:16:36] <rbraley>   right
| [Tuesday 17 August 2010] [17:16:41] <pieterh>   except there are no pipes
| [Tuesday 17 August 2010] [17:16:43] <pieterh>   :-)
| [Tuesday 17 August 2010] [17:17:06] <pieterh>   i'm kidding, i mean there are no visible connections
| [Tuesday 17 August 2010] [17:17:20] <pieterh>   and sockets are what we use to talk to the network, it's not the actual network
| [Tuesday 17 August 2010] [17:18:31] <rbraley>   I was thinking that maybe the components of my game engine might be devices
| [Tuesday 17 August 2010] [17:19:12] <rbraley>   with entities just being collections of sockets to them
| [Tuesday 17 August 2010] [17:20:32] <rbraley>   a timer device would certainly help
| [Tuesday 17 August 2010] [17:21:30] <rbraley>   no that doesn't work if devices should be stateless
| [Tuesday 17 August 2010] [17:25:12] <rbraley>   ooh, a logging device would be neat
| [Tuesday 17 August 2010] [17:28:05] <pieterh>   rbraley: that would be a logging application, not device >:-)
| [Tuesday 17 August 2010] [17:28:09] <pieterh>   just kidding...
| [Tuesday 17 August 2010] [17:28:48] <pieterh>   'device' really are things you plug into the network, and logging device makes perfect sense afaics
| [Tuesday 17 August 2010] [17:29:04]      * pieterh adds this to the user guide list of things to look at
| [Tuesday 17 August 2010] [17:30:38] <rbraley>   the thing that irks me about these examples is that threading policy is not decoupled from the concurrency policy
| [Tuesday 17 August 2010] [17:31:39] <rbraley>   ideally you'd have just one thread per core and could multiplex everything to these threads
| [Tuesday 17 August 2010] [17:33:15] <CIA-20>    jzmq: 03Alexey Ermakov 07master * r2f3afe8 10/ (perf/local_thr.java src/Socket.cpp src/org/zeromq/ZMQ.java): Changed setSubscribe(), setUnsubscribe() and setIdentity() to accept byte[]'s instead of Strings. - http://bit.ly/b2AZrL
| [Tuesday 17 August 2010] [17:38:03] <travlr>    i'm beginning to realize that zmq is a 'stateless' model and that state where belongs is the app.. as said: not even in a custom device. i, on the other hand use a device on each box _for_ the state of the individual zmq endpoint components..
| [Tuesday 17 August 2010] [17:38:31] <travlr>    s/state where/where state/ :-P
| [Tuesday 17 August 2010] [17:41:26] <rbraley>   without decoupling the threading policy from the concurrency policy it isn't possible to scale 0MQ to model neurons or implement the actor model 
| [Tuesday 17 August 2010] [17:42:42] <travlr>    there are two threading aspects in zmq, afaik, the i/o threading and the app threading.. 
| [Tuesday 17 August 2010] [17:43:14] <travlr>    and if i understand your comment correctly the app threading is decoupled
| [Tuesday 17 August 2010] [17:44:02] <travlr>    from the context but not a socket... but that is to be changed soon, afaiu
| [Tuesday 17 August 2010] [17:44:52] <rbraley>   What I am saying is the actual number concurrent nodes in the app should exceed the number of app threads
| [Tuesday 17 August 2010] [17:45:23] <rbraley>   we can't have a thread per neuron for example
| [Tuesday 17 August 2010] [17:45:31] <pieterh>   rbraley: right, if you say one node is one thread
| [Tuesday 17 August 2010] [17:46:13] <rbraley>   the concurrent nodes should be multiplexed to the app threads
| [Tuesday 17 August 2010] [17:47:32] <rbraley>   so 400000 of them can be run on 8 threads for example
| [Tuesday 17 August 2010] [17:48:39] <rbraley>   when you can do that, the entire paradigm changes
| [Tuesday 17 August 2010] [17:48:45] <travlr>    i'm thinking that is doable
| [Tuesday 17 August 2010] [17:49:27] <travlr>    and thats probably where a 'device' fits into the scheme
| [Tuesday 17 August 2010] [17:49:49] <rbraley>   suddenly you are dealing with abstract flow based programs that are pure computation and run optimally on any hardware that you put them on.
| [Tuesday 17 August 2010] [17:50:42] <travlr>    ha! have you seen my ProDataLab project regarding that
| [Tuesday 17 August 2010] [17:50:44] <rbraley>   it becomes a thing of great beauty and efficiency
| [Tuesday 17 August 2010] [17:50:58] <rbraley>   no sir
| [Tuesday 17 August 2010] [17:50:59] <travlr>    www.prodatalab.wikidot.com
| [Tuesday 17 August 2010] [17:52:11] <rbraley>   that is pure sex, travlr
| [Tuesday 17 August 2010] [17:52:24] <travlr>    lol, it is beautiful
| [Tuesday 17 August 2010] [17:53:29] <rbraley>   ok we need to talk
| [Tuesday 17 August 2010] [17:53:41] <rbraley>   where is this architecture spec?
| [Tuesday 17 August 2010] [17:53:46] <travlr>    please! when ever you like
| [Tuesday 17 August 2010] [17:53:56] <travlr>    spec is in my head atm
| [Tuesday 17 August 2010] [17:54:16] <rbraley>   let's get that on paper
| [Tuesday 17 August 2010] [17:54:26] <travlr>    let's talk sometime then
| [Tuesday 17 August 2010] [17:54:30] <rbraley>   well not deadtree, you know what I mean ;)
| [Tuesday 17 August 2010] [17:54:39] <travlr>    right
| [Tuesday 17 August 2010] [17:55:18] <travlr>    i need a partner so look it over carefully and let me know if you are interested in developing it with me
| [Tuesday 17 August 2010] [17:55:33] <rbraley>   we were planning on using a similar system for our artists to create entities in our game engine without knowing C++ or Go
| [Tuesday 17 August 2010] [17:56:08] <travlr>    i don't understand why visual programming isn't more wide spread.
| [Tuesday 17 August 2010] [17:56:40] <rbraley>   because, there isn't a conceptual model that works universally that people understand yet
| [Tuesday 17 August 2010] [17:56:46] <rbraley>   I think this is it
| [Tuesday 17 August 2010] [17:57:10] <travlr>    who difficult is a flow chart... directed graphs
| [Tuesday 17 August 2010] [17:57:11] <rbraley>   marketing as well. Most people still think procedurally
| [Tuesday 17 August 2010] [17:57:26] <travlr>    s/who/how
| [Tuesday 17 August 2010] [17:57:47] <travlr>    yeah but for the user newbie
| [Tuesday 17 August 2010] [17:57:55] <travlr>    vp is ideal
| [Tuesday 17 August 2010] [17:58:15] <travlr>    the power of programming in the hands of a layman
| [Tuesday 17 August 2010] [17:58:36] <rbraley>   so the optimal way to discuss this -- probably a recorded voice chat?
| [Tuesday 17 August 2010] [17:58:50] <CIA-20>    jzmq: 03Gonzalo Diethelm 07master * r773e56f 10/ (perf/local_thr.java src/Socket.cpp src/org/zeromq/ZMQ.java): 
| [Tuesday 17 August 2010] [17:58:50] <CIA-20>    jzmq: Handle an error case when creating a byte array in C++ code.
| [Tuesday 17 August 2010] [17:58:50] <CIA-20>    jzmq: Changed the names of some Socket methods:
| [Tuesday 17 August 2010] [17:58:50] <CIA-20>    jzmq:  getMulticastLoop() => hasMulticastLoop()
| [Tuesday 17 August 2010] [17:58:50] <CIA-20>    jzmq:  getReceiveMore() => hasReceiveMore()
| [Tuesday 17 August 2010] [17:58:51] <CIA-20>    jzmq:  setSubscribe(byte[] subscribe) => subscribe(byte[] topic)
| [Tuesday 17 August 2010] [17:58:52] <CIA-20>    jzmq:  setUnsubscribe(byte[] unsubscribe) => unsubscribe(byte[] topic) - http://bit.ly/aOecvc
| [Tuesday 17 August 2010] [17:59:07] <travlr>    what ever works for you is works for me
| [Tuesday 17 August 2010] [18:01:47] <rbraley>   lemme see if i can get a skype call recorder working
| [Tuesday 17 August 2010] [18:03:03] <travlr>    what's the need for recording?
| [Tuesday 17 August 2010] [18:03:24] <rbraley>   so we can transcribe and turn it into a spec later
| [Tuesday 17 August 2010] [18:03:40] <rbraley>   also if we happen upon a great idea we won't lose it and can return to it later
| [Tuesday 17 August 2010] [18:04:15] <travlr>    sure ok, but before we get into details, we should just have a chat first
| [Tuesday 17 August 2010] [18:07:58] <rbraley>   what is your skype id travlr ?
| [Tuesday 17 August 2010] [18:10:31] <travlr>    hold on a min
| [Tuesday 17 August 2010] [18:13:05] <rbraley>   velaccel is my skype id
| [Tuesday 17 August 2010] [18:13:44] <travlr>    did you get it?
| [Tuesday 17 August 2010] [18:18:59] <pieterh>   travlr: so you are Mr ProDataLab... :-)
| [Tuesday 17 August 2010] [20:48:01] <pieterh>   prodatalab is concept i've been working on for quite some time. needless to say 0mq makes it all come together very well. i think it can be revolutionary in more than a few ways. can i possibly interest you in discussing it with me. i'm considering a partnership atm for the potential to market it.
| [Tuesday 17 August 2010] [20:48:01] Away    pieterh is away: I'm not here right now
| [Tuesday 17 August 2010] [21:00:17] Whois   rbraley is ~rbraley@ip72-222-128-78.ph.ph.cox.net (ryan braley)
| [Tuesday 17 August 2010] [21:00:17] Whois   rbraley is a user on channels: #zeromq
| [Tuesday 17 August 2010] [21:00:17] Whois   rbraley is online via wolfe.freenode.net (Manchester, England).
| [Tuesday 17 August 2010] [21:00:17] Whois   rbraley has been idle for 2 hours, 46 minutes, and 19 seconds.
| [Tuesday 17 August 2010] [21:00:17] Whois   rbraley has been online since 2010-08-17 06:54:06.
| [Tuesday 17 August 2010] [21:00:17] Whois   End of WHOIS list.
| [Tuesday 17 August 2010] [21:00:37] Whois   pieterh is ~ph@cable-212.76.229.34.static.coditel.net (purple)
| [Tuesday 17 August 2010] [21:00:37] Whois   pieterh is a user on channels: #zeromq
| [Tuesday 17 August 2010] [21:00:37] Whois   pieterh is online via zelazny.freenode.net (Corvallis, OR, USA).
| [Tuesday 17 August 2010] [21:00:37] Away    pieterh is away: I'm not here right now
| [Tuesday 17 August 2010] [21:00:37] Whois   pieterh has been idle for 2 hours, 41 minutes, and 38 seconds.
| [Tuesday 17 August 2010] [21:00:37] Whois   pieterh has been online since 2010-08-15 07:35:26.
| [Tuesday 17 August 2010] [21:00:37] Whois   End of WHOIS list.
| [Tuesday 17 August 2010] [21:23:33] <rbraley>   i was looking for that link where the guy described his google interview process and a google search provides hundreds of them.
| [Tuesday 17 August 2010] [21:25:21] Whois   travlr is ~travlr@c-69-254-44-10.hsd1.fl.comcast.net (Peter Alexander)
| [Tuesday 17 August 2010] [21:25:22] Whois   travlr is a user on channels: #gentoo-kde #gentoo-qt #zeromq
| [Tuesday 17 August 2010] [21:25:22] Whois   travlr is online via gibson.freenode.net (Oslo, Norway).
| [Tuesday 17 August 2010] [21:25:22] 378 travlr travlr is connecting from *@c-69-254-44-10.hsd1.fl.comcast.net 69.254.44.10
| [Tuesday 17 August 2010] [21:25:22] Whois   travlr has been idle for 1 minute and 48 seconds.
| [Tuesday 17 August 2010] [21:25:22] Whois   travlr has been online since 2010-08-17 05:03:41.
| [Tuesday 17 August 2010] [21:25:22] Whois   travlr is logged in as travlr.
| [Tuesday 17 August 2010] [21:25:22] Whois   End of WHOIS list.
| [Tuesday 17 August 2010] [21:36:01] <jhawk28>   any of the zeromq devs here?
| [Tuesday 17 August 2010] [21:39:38] <jhawk28>   has any work been done to migrate openamq to 0mq?
| [Wednesday 18 August 2010] [00:07:45] <CIA-20>  rbzmq: 03Brian Buchanan 07master * r2aa02db 10/ (rbzmq.c zmq.gemspec): 
| [Wednesday 18 August 2010] [00:07:45] <CIA-20>  rbzmq: Fix potential memory leak in ZMQ.select()
| [Wednesday 18 August 2010] [00:07:45] <CIA-20>  rbzmq: Reported by: Eric Wong <normalperson@yhbt.net> - http://bit.ly/coN2GW
| [Wednesday 18 August 2010] [02:01:41] <sustrik> mikko: that's bad, it looks like freebsd bug
| [Wednesday 18 August 2010] [02:01:54] <sustrik> what version of freebsd are you using?
| [Wednesday 18 August 2010] [03:05:39] <mikko>   sustrik: 8.1 i think
| [Wednesday 18 August 2010] [03:06:05] <mikko>   FreeBSD fbsd.localdomain 8.1-RELEASE FreeBSD 8.1-RELEASE #0: Mon Jul 19 02:36:49 UTC 2010     root@mason.cse.buffalo.edu:/usr/obj/usr/src/sys/GENERIC  amd64
| [Wednesday 18 August 2010] [03:10:17] <mikko>   sustrik: i can't reproduce in a simple program
| [Wednesday 18 August 2010] [03:22:46] <sustrik> mikko: what about showing the traceback on a freebsd forum?
| [Wednesday 18 August 2010] [03:23:01] <sustrik> someone may have had an experience with it there
| [Wednesday 18 August 2010] [03:25:15] <sustrik> the two links i've posted seem to indicate that there used to be such bug in freebsd...
| [Wednesday 18 August 2010] [04:14:17] <mikko>   sustrik: some progress
| [Wednesday 18 August 2010] [04:14:30] <mikko>   yep
| [Wednesday 18 August 2010] [04:14:31] <mikko>   got it
| [Wednesday 18 August 2010] [04:14:52] <sustrik> mikko: a solution?
| [Wednesday 18 August 2010] [04:14:56] <mikko>   yes
| [Wednesday 18 August 2010] [04:15:04]    * sustrik is interested
| [Wednesday 18 August 2010] [04:15:08] <mikko>   php needs to link against libthr 
| [Wednesday 18 August 2010] [04:15:23] <sustrik> several thread libraries out there?
| [Wednesday 18 August 2010] [04:15:24] <mikko>   it is not enough that libzmq links against libthr
| [Wednesday 18 August 2010] [04:15:52] <mikko>   this is my theory this far:
| [Wednesday 18 August 2010] [04:16:10] <mikko>   single threaded php linked against non-reentrant libraries
| [Wednesday 18 August 2010] [04:16:18] <mikko>   loads up and loads libzmq 
| [Wednesday 18 August 2010] [04:16:26] <sustrik> got it
| [Wednesday 18 August 2010] [04:16:28] <mikko>   which ends up using non-reentrant things
| [Wednesday 18 August 2010] [04:16:34] <mikko>   due to loading order
| [Wednesday 18 August 2010] [04:16:54] <mikko>   but this is just a theory not knowing much about freebsd internals
| [Wednesday 18 August 2010] [04:17:04] <sustrik> seems plausible to mwe
| [Wednesday 18 August 2010] [04:17:06] <sustrik> me
| [Wednesday 18 August 2010] [04:17:20] <mikko>   libthr.so.3 => /lib/libthr.so.3 (0x800883000)
| [Wednesday 18 August 2010] [04:17:25] <mikko>   is what libzmq links against
| [Wednesday 18 August 2010] [04:17:40] <mikko>   and php compilation gives option "Do you want to link against libthr?"
| [Wednesday 18 August 2010] [04:17:55] <sustrik> aha
| [Wednesday 18 August 2010] [04:18:11] <sustrik> it should be noted somewhere
| [Wednesday 18 August 2010] [04:18:18] <sustrik> so that the knowlefge is not lost
| [Wednesday 18 August 2010] [04:18:49] <mikko>   it's in github issue tracker
| [Wednesday 18 August 2010] [04:18:52] <mikko>   at least
| [Wednesday 18 August 2010] [04:19:16] <mikko>   it is odd that i can't reproduce this with a simple program
| [Wednesday 18 August 2010] [04:19:34] <sustrik> timing issue maybe
| [Wednesday 18 August 2010] [04:19:49] <sustrik> btw, is the php binding built using autotools?
| [Wednesday 18 August 2010] [04:19:50] <mikko>   possibly and php uses dlopen/load to load the php-zmq
| [Wednesday 18 August 2010] [04:19:52] <mikko>   yes
| [Wednesday 18 August 2010] [04:20:05] <sustrik> maybe it can be made automatic
| [Wednesday 18 August 2010] [04:20:15] <mikko>   but thats not the thing
| [Wednesday 18 August 2010] [04:20:17] <sustrik> FreeBSD -> link with libthr
| [Wednesday 18 August 2010] [04:20:21] <mikko>   there are three moving parts
| [Wednesday 18 August 2010] [04:20:31] <mikko>   php, php extension for zmq and libzmq
| [Wednesday 18 August 2010] [04:20:34] <mikko>   so roughly:
| [Wednesday 18 August 2010] [04:21:03] <mikko>   php <- dynamic loading -> php-zmq <- runtime linker loading > libzmq
| [Wednesday 18 August 2010] [04:21:13] <mikko>   dynamic loading being dlopen or what the platform has
| [Wednesday 18 August 2010] [04:21:32] <mikko>   i think the boundary of dlopen actually causes the confusion
| [Wednesday 18 August 2010] [04:21:44] <sustrik> looks like
| [Wednesday 18 August 2010] [04:22:03] <sustrik> but does in make sense to compile php-zmq without libthr?
| [Wednesday 18 August 2010] [04:22:03] <mikko>   i could try to create a test case
| [Wednesday 18 August 2010] [04:22:21] <mikko>   for php-zmq it doesnt matter
| [Wednesday 18 August 2010] [04:22:30] <mikko>   because libzmq links against it
| [Wednesday 18 August 2010] [04:22:46] <sustrik> ah
| [Wednesday 18 August 2010] [04:22:55] <sustrik> it's php build that has to be modified
| [Wednesday 18 August 2010] [04:22:57] <mikko>   for php it matters because it doesnt 'hard-link' against libthr at any point
| [Wednesday 18 August 2010] [04:22:58] <mikko>   yes
| [Wednesday 18 August 2010] [04:23:04] <sustrik> my god
| [Wednesday 18 August 2010] [04:23:06] <sustrik> ok, i see
| [Wednesday 18 August 2010] [04:23:11] <mikko>   i'll try to create a test case for this
| [Wednesday 18 August 2010] [04:23:17] <sustrik> ack
| [Wednesday 18 August 2010] [04:28:20] <anarchocap>  hi
| [Wednesday 18 August 2010] [04:36:42] <mikko>   sustrik: oh joy
| [Wednesday 18 August 2010] [04:36:45] <mikko>   can't reproduce
| [Wednesday 18 August 2010] [04:39:44] <sustrik> :|
| [Wednesday 18 August 2010] [04:42:17] <mikko>   in a very simple test case it work
| [Wednesday 18 August 2010] [04:42:19] <mikko>   s
| [Wednesday 18 August 2010] [04:43:27] <pieterh> mikko: this is kind of typical, you chopped out whatever it is that provokes the problem
| [Wednesday 18 August 2010] [04:44:45] <mikko>   pieterh: there are so many moving parts in the final solution, could be a race condition, could be just about anything
| [Wednesday 18 August 2010] [04:44:47] <mikko>   at least there is a work-around
| [Wednesday 18 August 2010] [04:44:51] <mikko>   http://github.com/mkoppanen/php-zmq/issues#issue/7
| [Wednesday 18 August 2010] [04:44:59] <mikko>   i'll add it to the wiki as well
| [Wednesday 18 August 2010] [04:48:11] <mikko>   http://www.zeromq.org/bindings:php#toc3
| [Wednesday 18 August 2010] [04:48:16] <mikko>   done 
| [Wednesday 18 August 2010] [04:58:57] <pieterh> sustrik: do you have a moment?
| [Wednesday 18 August 2010] [04:59:50] <pieterh> could you explain why you think subscription idempotency would let one subscriber unsubscribe another one?
| [Wednesday 18 August 2010] [05:06:27] <sustrik> pieterh: think of a pub node connected to 2 sub nodes
| [Wednesday 18 August 2010] [05:06:36] <pieterh> ack
| [Wednesday 18 August 2010] [05:06:41] <sustrik> sub node 1: SUB(ABC)
| [Wednesday 18 August 2010] [05:06:50] <sustrik> sub node 2: SUB(ABC)
| [Wednesday 18 August 2010] [05:07:04] <sustrik> sub node 1: UNSUB(ABC)
| [Wednesday 18 August 2010] [05:07:12] <sustrik> sub node2: wtf?!?
| [Wednesday 18 August 2010] [05:07:52] <pieterh> that is, if you literally take the algorithm from the SUB socket and move it to the PUB socket
| [Wednesday 18 August 2010] [05:08:11] <sustrik> yes, any such algorithm
| [Wednesday 18 August 2010] [05:08:23] <pieterh> if idempotency was part of the spec, would it be possible?
| [Wednesday 18 August 2010] [05:08:30] <sustrik> sure
| [Wednesday 18 August 2010] [05:08:33] <pieterh> (trick question: answer is "of course")
| [Wednesday 18 August 2010] [05:08:45] <sustrik> the question is whether it is desirable
| [Wednesday 18 August 2010] [05:08:59] <sustrik> there are 2 use cases afaics:
| [Wednesday 18 August 2010] [05:09:02] <pieterh> seen from the app pov it's very desirable
| [Wednesday 18 August 2010] [05:09:11] <pieterh> it removes the need to duplicate state
| [Wednesday 18 August 2010] [05:09:18] <sustrik> 1. a GUI app, user nervously clicking on sub & unsub buttons
| [Wednesday 18 August 2010] [05:09:44] <sustrik> 2. a automated app with a consistent algorithm
| [Wednesday 18 August 2010] [05:09:59] <pieterh> consistency may not be always possible
| [Wednesday 18 August 2010] [05:10:02] <sustrik> if you have idempotency, 2 has to duplicate state
| [Wednesday 18 August 2010] [05:10:13] <sustrik> if you have refcounting 1 has to duplicate state
| [Wednesday 18 August 2010] [05:10:14] <pieterh> if you don't have idempotency, 2 has to duplicate state
| [Wednesday 18 August 2010] [05:10:22] <sustrik> exactly
| [Wednesday 18 August 2010] [05:10:43] <pieterh> :-) 
| [Wednesday 18 August 2010] [05:10:57] <pieterh> how can you say 'exactly' when i say the exact opposite of you?
| [Wednesday 18 August 2010] [05:11:00] <pieterh> i'm confused now
| [Wednesday 18 August 2010] [05:11:24] <pieterh> ok, here's a point of view on this...
| [Wednesday 18 August 2010] [05:11:27] <sustrik> ah, sorry misread 2 as 1
| [Wednesday 18 August 2010] [05:11:50] <sustrik> you are NOT right
| [Wednesday 18 August 2010] [05:11:52] <sustrik> :)
| [Wednesday 18 August 2010] [05:11:56] <pieterh> that's better
| [Wednesday 18 August 2010] [05:12:07] <pieterh> ok, do you have 5 mins to walk through this?
| [Wednesday 18 August 2010] [05:12:13] <sustrik> yes
| [Wednesday 18 August 2010] [05:12:29] <pieterh> so... idempotent apis are robust against stateloss in the network
| [Wednesday 18 August 2010] [05:12:34] <pieterh> e.g. REST
| [Wednesday 18 August 2010] [05:13:07] <pieterh> that's just a desirable property... any code that handles sub/unsub control commands will be more robust if the api it talks to is idempotent
| [Wednesday 18 August 2010] [05:13:12] <pieterh> now
| [Wednesday 18 August 2010] [05:13:22] <pieterh> this is for TCP, not multicast
| [Wednesday 18 August 2010] [05:13:34] <pieterh> the PUB knows each SUB connection
| [Wednesday 18 August 2010] [05:13:49] <pieterh> has the subscriptions for each one
| [Wednesday 18 August 2010] [05:13:51] <sustrik> don't go into technical details
| [Wednesday 18 August 2010] [05:13:54] <sustrik> that's clear
| [Wednesday 18 August 2010] [05:14:17] <pieterh> it can trivially ensure that anything coming from SUB A does not interfere with SUB B
| [Wednesday 18 August 2010] [05:14:22] <pieterh> and it needs to, anyhow
| [Wednesday 18 August 2010] [05:14:39] <pieterh> since anyone can craft sub/unsub messages
| [Wednesday 18 August 2010] [05:14:41] <sustrik> sure, but not so user implemetned nodes
| [Wednesday 18 August 2010] [05:14:52] <sustrik> such as a node aggregating FIX data feeds
| [Wednesday 18 August 2010] [05:14:55] <sustrik> or similar
| [Wednesday 18 August 2010] [05:14:58] <pieterh> devices is next, we were starting with direct sub-to-pub
| [Wednesday 18 August 2010] [05:15:05] <sustrik> the only guestion is:
| [Wednesday 18 August 2010] [05:15:31] <sustrik> do we want to provide the GUI use case, or the "device" use case as default
| [Wednesday 18 August 2010] [05:15:40] <pieterh> i don't see this as the choice
| [Wednesday 18 August 2010] [05:15:49] <pieterh> that looks like a false dichotomy
| [Wednesday 18 August 2010] [05:15:55] <sustrik> shrug
| [Wednesday 18 August 2010] [05:16:07] <pieterh> based on assumptions that i'm not sharing / seeing
| [Wednesday 18 August 2010] [05:16:22] <sustrik> how would you integrate say FIX feeds?
| [Wednesday 18 August 2010] [05:16:28] <pieterh> can i refer to previous known use cases?
| [Wednesday 18 August 2010] [05:16:38] <sustrik> yes
| [Wednesday 18 August 2010] [05:16:39] <pieterh> take AMQP bindings
| [Wednesday 18 August 2010] [05:16:42] <pieterh> idempotent
| [Wednesday 18 August 2010] [05:16:44] <pieterh> federable
| [Wednesday 18 August 2010] [05:17:05] <sustrik> that's because they are encapsulated inside of the broker
| [Wednesday 18 August 2010] [05:17:14] <pieterh> work for both the GUI and the device use case
| [Wednesday 18 August 2010] [05:17:23] <sustrik> not for the latter
| [Wednesday 18 August 2010] [05:17:57] <pieterh> ah, ok
| [Wednesday 18 August 2010] [05:18:05] <pieterh> you are saying you don't want devices to keep any state
| [Wednesday 18 August 2010] [05:18:12] <sustrik> yes
| [Wednesday 18 August 2010] [05:18:15] <pieterh> thus state must be in the edges
| [Wednesday 18 August 2010] [05:18:19] <sustrik> so that they can come and go
| [Wednesday 18 August 2010] [05:18:23] <sustrik> right
| [Wednesday 18 August 2010] [05:18:27] <sustrik> end-to-end principle
| [Wednesday 18 August 2010] [05:18:30] <pieterh> ok, so sub sockets can do the refcounting and give idempotency
| [Wednesday 18 August 2010] [05:18:35] <pieterh> with amqp there is no state in the API
| [Wednesday 18 August 2010] [05:19:02] <sustrik> yes, amqp is designed other way round
| [Wednesday 18 August 2010] [05:19:13] <pieterh> devices in any case must store subscriptions
| [Wednesday 18 August 2010] [05:19:23] <pieterh> in their sub sockets
| [Wednesday 18 August 2010] [05:19:29] <sustrik> it's just transient
| [Wednesday 18 August 2010] [05:19:42] <sustrik> when the connection goes, associated subscriptions are deleted
| [Wednesday 18 August 2010] [05:19:50] <pieterh> right
| [Wednesday 18 August 2010] [05:19:54] <sustrik> when device fails, it looses them of course
| [Wednesday 18 August 2010] [05:20:05] <sustrik> when the peer reconnects it resends the subscriptions
| [Wednesday 18 August 2010] [05:20:12] <pieterh> there is an easy, trivial, stupid, scalable design
| [Wednesday 18 August 2010] [05:20:20] <sustrik> yes?
| [Wednesday 18 August 2010] [05:20:28] <pieterh> do not forward ubsub messages
| [Wednesday 18 August 2010] [05:20:32] <pieterh> *unsub
| [Wednesday 18 August 2010] [05:20:42] <pieterh> and ignore duplicate subs
| [Wednesday 18 August 2010] [05:21:12] <sustrik> that would aggregate subs in the network until congestion happens
| [Wednesday 18 August 2010] [05:21:15] <pieterh> it fails in some use cases but those would normally be on multicast anyhow
| [Wednesday 18 August 2010] [05:21:21] <pieterh> where it does not apply
| [Wednesday 18 August 2010] [05:21:50] <pieterh> scenarios that do unsubscription are arguably very rare
| [Wednesday 18 August 2010] [05:22:06] <sustrik> true
| [Wednesday 18 August 2010] [05:22:17] <sustrik> do you want to drop UNSUBSCRIBE then?
| [Wednesday 18 August 2010] [05:22:24] <pieterh> it's just a thought
| [Wednesday 18 August 2010] [05:22:39] <sustrik> "if you want to unsubscribe, close the socket"
| [Wednesday 18 August 2010] [05:22:44] <pieterh> for example, yes
| [Wednesday 18 August 2010] [05:22:44] <sustrik> it's viable
| [Wednesday 18 August 2010] [05:23:02] <sustrik> ask on list, IMO
| [Wednesday 18 August 2010] [05:23:03] <pieterh> or else don't forward unsubscribe over TCP and handle it locally
| [Wednesday 18 August 2010] [05:23:17] <sustrik> no
| [Wednesday 18 August 2010] [05:23:25] <sustrik> that's the congestion scenario
| [Wednesday 18 August 2010] [05:23:36] <pieterh> well, it's what we do today :-)
| [Wednesday 18 August 2010] [05:23:37] <sustrik> invisible traffic flowing on
| [Wednesday 18 August 2010] [05:24:08] <sustrik> yes, buth it's definitely not desirable
| [Wednesday 18 August 2010] [05:24:13] <pieterh> true
| [Wednesday 18 August 2010] [05:24:55] <pieterh> is it out of the question that forwarder devices keep track of their downstream subscribers?
| [Wednesday 18 August 2010] [05:26:04] <sustrik> ?
| [Wednesday 18 August 2010] [05:26:20] <sustrik> ah, i see
| [Wednesday 18 August 2010] [05:26:22] <pieterh> it would require that they replicate the prefix tree
| [Wednesday 18 August 2010] [05:26:33] <pieterh> and intelligently sub/unsub as needed
| [Wednesday 18 August 2010] [05:26:56] <pieterh> it is scalable and if the device dies, it works as expected
| [Wednesday 18 August 2010] [05:27:26] <pieterh> a proper proxy for subscriptions
| [Wednesday 18 August 2010] [05:27:27] <sustrik> yes, that's an option
| [Wednesday 18 August 2010] [05:27:54] <pieterh> i'm happy to help code that up in 21 years or so :-)
| [Wednesday 18 August 2010] [05:28:02] <sustrik> :)
| [Wednesday 18 August 2010] [05:28:16] <sustrik> so how about the birth?
| [Wednesday 18 August 2010] [05:28:25] <pieterh> still waiting
| [Wednesday 18 August 2010] [05:28:25] <sustrik> have it happened already?
| [Wednesday 18 August 2010] [05:28:28] <sustrik> ah
| [Wednesday 18 August 2010] [05:28:58] <sustrik> ok, cyl
| [Wednesday 18 August 2010] [05:29:00] <pieterh> sylvie is in the hospital and they're giving her stuff to provoke it but the baby is like "no way! that's a hostile world out there!"
| [Wednesday 18 August 2010] [05:29:15] <pieterh> thanks for this explanation
| [Wednesday 18 August 2010] [05:51:11] <travlr>  pieterh: yup, prodatalab is me. do you find the concept interesting?
| [Wednesday 18 August 2010] [05:51:35] <pieterh> travlr: will it be free software?
| [Wednesday 18 August 2010] [05:52:13] <travlr>  i'm trying to decide what route to take atm.. would care to discuss it with me?
| [Wednesday 18 August 2010] [05:52:34] <pieterh> certainly...
| [Wednesday 18 August 2010] [05:52:42]    * pieterh moves off irc
| [Wednesday 18 August 2010] [06:01:06] <CIA-20>  zeromq2: 03Martin Sustrik 07master * r7aba2d1 10/ doc/zmq.txt : documentation leftover from v2.0.6 cleaned in zmq(7) - http://bit.ly/9Tz5PI
| [Wednesday 18 August 2010] [07:57:46] <pietia>  is it possible to use zeromq as cron?
| [Wednesday 18 August 2010] [08:10:44] <sustrik> pietia: there are no timers
| [Wednesday 18 August 2010] [08:10:50] <sustrik> it's just an interconnect
| [Wednesday 18 August 2010] [08:11:52] <mikko>   http://pod.tst.eu/http://cvs.schmorp.de/libev/ev.pod#code_ev_timer_code_relative_and_opti
| [Wednesday 18 August 2010] [12:05:57] <pieterh> mikko: nice link
| [Wednesday 18 August 2010] [20:47:56] <sd88g93> hello.  having trouble with zero mq on freebsd; basically,  when i try to initiate a client request on a port, it just hangs.  Is there any special settings on freebsd that i should be aware of ?  just wondering if this rings a bell with anyone 
| [Thursday 19 August 2010] [08:31:30] <CIA-20>   zeromq2: 03Pieter Hintjens 07master * rde0035b 10/ README : Fixed git URL in README - http://bit.ly/cGxNGo
| [Thursday 19 August 2010] [08:51:33] <illsci>   morning
| [Thursday 19 August 2010] [17:38:48] <rbraley>  http://ptolemy.eecs.berkeley.edu/presentations/06/FutureOfEmbeddedSoftware_Lee_Graz.ppt
| [Thursday 19 August 2010] [18:30:47] <pieterh>  rbraley: excellent!
| [Thursday 19 August 2010] [19:07:11] <CIA-20>   zeromq2: 03Pieter Hintjens 07master * r87612be 10/ src/xrep.cpp : Merge branch '46_device_robustness' - http://bit.ly/d6LcAr
| [Thursday 19 August 2010] [20:07:39] <rbraley>  I recommended ZeroMQ during my Amazon interview today
| [Thursday 19 August 2010] [20:16:29] <AndrewBC> How did that go?
| [Thursday 19 August 2010] [20:22:01] <rbraley>  Slam dunk. He said of all the many applicants he'd ever interviewed my solution was by far the most scalable and ballsy! Apparently nobody had ever used Hadoop or MapReduce in a 40min interview..
| [Thursday 19 August 2010] [20:22:57] <AndrewBC> hehe
| [Thursday 19 August 2010] [20:24:20] <rbraley>  I am going to make a prediction: if anyone ever does make skynet, they will use ZeroMQ to do it.
| [Thursday 19 August 2010] [20:24:30] <rbraley>  pieterh, put that in your blog and smoke it!
| [Thursday 19 August 2010] [20:24:48] <rbraley>  :P
| [Thursday 19 August 2010] [20:25:56] <AndrewBC> Heheh
| [Thursday 19 August 2010] [21:52:25] <mattbillenstein>  hi all
| [Thursday 19 August 2010] [21:52:46] <mattbillenstein>  seems the INSTALL doc is missing from the github repo?
| [Thursday 19 August 2010] [21:53:25] <travlr>   what platform are you on?
| [Thursday 19 August 2010] [21:53:58] <mattbillenstein>  linux
| [Thursday 19 August 2010] [21:54:08] <mattbillenstein>  ubuntu
| [Thursday 19 August 2010] [21:54:19] <travlr>   call autogen.sh to generate the ./configure file
| [Thursday 19 August 2010] [21:56:54] <mattbillenstein>  okay, looks like I needed pkg-config, libtool, and autoconf
| [Thursday 19 August 2010] [22:09:03] <mattbillenstein>  alright, looks like I got it installed with the python bindings -- thx!
| [Friday 20 August 2010] [01:00:15] <rbraley>    inspiration: http://www.archive.org/details/AlanKeyD1987
| [Friday 20 August 2010] [04:55:28] <fabian__>   hi everybody, juste one question, I'd like to monitor zmq socket  by a select.   Where can I find  the  fd   of each sockets open by zmq  ??
| [Friday 20 August 2010] [05:05:52] <fabian__>   In fact I just would like to be not blocked with a zmq read
| [Friday 20 August 2010] [05:06:11] <fabian__>   May be there is an "alarm" or "timeout" for zmq read?
| [Friday 20 August 2010] [05:10:57] <Zao>    Use zmq_poll and add in a socket with which you can send anything on to break out of poll?
| [Friday 20 August 2010] [05:11:12] <Zao>    note that zmq_poll also supports regular FDs.
| [Friday 20 August 2010] [05:11:12] <Zao>    http://api.zeromq.org/zmq_poll.html
| [Friday 20 August 2010] [05:11:41] <Zao>    Oh, it even takes a timeout as third param :D
| [Friday 20 August 2010] [05:17:59] <fabian__>   Ok...  If I correctly understand, "items[0].socket ="  must be the return value of the zmq_socket ?
| [Friday 20 August 2010] [05:20:16] <jsimmons>   is there any zeromq bug that causes duplicated messages followed by a busy wait lockup? in 2.0.7 perhaps? I don't think so but I thought I'd check.
| [Friday 20 August 2010] [05:20:20] <Zao>    It's a ZMQ "socket", whatever type that is.
| [Friday 20 August 2010] [05:25:43] <pieterh>    hi sustrik: you around?
| [Friday 20 August 2010] [05:26:17] <pieterh>    jsimmons: all known bugs are on the github issue tracker
| [Friday 20 August 2010] [05:26:41] <jsimmons>   I'll have a look there then thanks pieterh
| [Friday 20 August 2010] [05:57:37] <sustrik>    Pieter: what do you think of moving all devices to a separate project?
| [Friday 20 August 2010] [05:57:40] <pieterh>    what do people think of collecting device apps in one place?
| [Friday 20 August 2010] [05:57:45] <sustrik>    :)
| [Friday 20 August 2010] [05:57:55] <sustrik>    i think it's a good idea
| [Friday 20 August 2010] [05:57:58] <pieterh>    while writing the guide i realize there are a lot of devices to make
| [Friday 20 August 2010] [05:58:01] <sustrik>    but it has to be a library
| [Friday 20 August 2010] [05:58:03] <pieterh>    clocks, queues, loggers, etc.
| [Friday 20 August 2010] [05:58:16] <sustrik>    so that it can be used inproc
| [Friday 20 August 2010] [05:58:20] <pieterh>    yes, but initially these are all applications
| [Friday 20 August 2010] [05:58:33] <pieterh>    IMO over time the best ones will get librarified
| [Friday 20 August 2010] [05:58:36] <jsimmons>   pieterh, sustrik one of you wrote a good article about zeromq with a simple example? you were discussing a talk the other day and somebody mentioned it, I think?
| [Friday 20 August 2010] [05:58:43] <pieterh>    and the utterly necessary ones can go into core
| [Friday 20 August 2010] [05:59:17] <sustrik>    jsimmons: i am having a talk but that's kind of advanced stuff
| [Friday 20 August 2010] [05:59:24] <pieterh>    jsimmons: "sustrik & lucina" "sockets on steroids is the authoritative intro
| [Friday 20 August 2010] [05:59:31] <sustrik>    simple article... maybe the one at lwn.net
| [Friday 20 August 2010] [05:59:35] <pieterh>    it's mentioned on the www.zeromq.org main page
| [Friday 20 August 2010] [05:59:56] <sustrik>    that's the same one?
| [Friday 20 August 2010] [06:00:00] <pieterh>    ya
| [Friday 20 August 2010] [06:00:02] <sustrik>    aha
| [Friday 20 August 2010] [06:00:17] <jsimmons>   http://www.250bpm.com/joe ah it was this one I was thinking of
| [Friday 20 August 2010] [06:00:35] <sustrik>    ah, that's not really simple
| [Friday 20 August 2010] [06:00:47] <sustrik>    do you need a basic introduction?
| [Friday 20 August 2010] [06:01:01] <jsimmons>   no I understand it, I just remembered that article and wanted to read it again.
| [Friday 20 August 2010] [06:01:16] <pieterh>    the joe article is great but speaks to people who already know 0MQ IMO
| [Friday 20 August 2010] [06:01:36] <sustrik>    that's why i said it's "advanced"
| [Friday 20 August 2010] [06:01:46] <sustrik>    it's more about vision than technical details
| [Friday 20 August 2010] [06:01:46] <pieterh>    yup
| [Friday 20 August 2010] [06:01:49] <pieterh>    indeed
| [Friday 20 August 2010] [06:01:55] <sustrik>    anyway, as for the devices
| [Friday 20 August 2010] [06:01:57] <pieterh>    so i stared a github project, xdevices
| [Friday 20 August 2010] [06:02:00] <pieterh>    *started
| [Friday 20 August 2010] [06:02:16] <pieterh>    my idea is to collect knowledge, really, at this stage
| [Friday 20 August 2010] [06:02:17] <sustrik>    is there any reason *not* to allow them to be used with inproc?
| [Friday 20 August 2010] [06:02:33] <pieterh>    sustrik: no reason to forbid this, it's just extra work that may not be worthwhile
| [Friday 20 August 2010] [06:02:51] <pieterh>    it demands that they be written in C/C++ for one thing
| [Friday 20 August 2010] [06:02:53] <sustrik>    ah, you mean splitting the codebase into library & executable?
| [Friday 20 August 2010] [06:03:03] <pieterh>    i mean doing this organically...
| [Friday 20 August 2010] [06:03:10] <pieterh>    1. collect knowledge and examples
| [Friday 20 August 2010] [06:03:23] <pieterh>    2. collect best practice into libraries
| [Friday 20 August 2010] [06:03:35] <pieterh>    3. move essential parts into 0MQ core over time
| [Friday 20 August 2010] [06:03:54] <sustrik>    ok, sure, as an experimental project is doesn't have to be completely versatile
| [Friday 20 August 2010] [06:03:59] <pieterh>    right
| [Friday 20 August 2010] [06:04:05] <pieterh>    also, no git process :-)
| [Friday 20 August 2010] [06:04:11] <pieterh>    everyone hacks master :-)
| [Friday 20 August 2010] [06:04:11] <sustrik>    :)
| [Friday 20 August 2010] [06:04:20] <pieterh>    which you can't do for libraries
| [Friday 20 August 2010] [06:04:29] <pieterh>    ok, so part 2 then
| [Friday 20 August 2010] [06:04:42] <pieterh>    i started ZFL, which can be the container for reusable devices for inproc use
| [Friday 20 August 2010] [06:06:28] <sustrik>    ok
| [Friday 20 August 2010] [06:06:40] <sustrik>    i'll have a look at it a bit later
| [Friday 20 August 2010] [06:06:49] <sustrik>    now, part 3
| [Friday 20 August 2010] [06:06:52] <sustrik>    the process!
| [Friday 20 August 2010] [06:07:08] <pieterh>    part 3...
| [Friday 20 August 2010] [06:07:15] <sustrik>    so, in linux kernel you have maintainers for parts of the code
| [Friday 20 August 2010] [06:07:26] <sustrik>    who should guarantee some minimal QA
| [Friday 20 August 2010] [06:07:32] <pieterh>    i've started learning http://nvie.com/git-model
| [Friday 20 August 2010] [06:08:02] <pieterh>    i think there are basic principles of ownership
| [Friday 20 August 2010] [06:08:07] <sustrik>    this has to do more with personal responsibility than with operational details
| [Friday 20 August 2010] [06:08:17] <pieterh>    we own what we make (in the sense of responsibility to users)
| [Friday 20 August 2010] [06:08:24] <sustrik>    right
| [Friday 20 August 2010] [06:08:25] <pieterh>    code that has no owner is dead or will die
| [Friday 20 August 2010] [06:08:30] <sustrik>    exaclty
| [Friday 20 August 2010] [06:08:48] <sustrik>    once we'started with this and added MAINTAINERS file to the codebase
| [Friday 20 August 2010] [06:08:52] <pieterh>    and any package of code has one identifiable 'main' owner
| [Friday 20 August 2010] [06:08:57] <pieterh>    yes, i read that
| [Friday 20 August 2010] [06:09:01] <sustrik>    right now it says:
| [Friday 20 August 2010] [06:09:08] <pieterh>    e.g. in COSS, each specification has one responsible editor
| [Friday 20 August 2010] [06:09:29] <sustrik>    lucina = build system + something, i don't exactly remember what
| [Friday 20 August 2010] [06:09:36] <sustrik>    sustrik = the rest
| [Friday 20 August 2010] [06:10:08] <sustrik>    if we can split the devices part, that would be nice
| [Friday 20 August 2010] [06:10:11] <pieterh>    sure, that's how it was for a while
| [Friday 20 August 2010] [06:10:33] <pieterh>    i think people are happy to take over parts they can help with
| [Friday 20 August 2010] [06:10:48] <pieterh>    actually that's key to scaling the contributions
| [Friday 20 August 2010] [06:11:06] <sustrik>    yes, this happened with language bindings
| [Friday 20 August 2010] [06:11:10] <pieterh>    precisely
| [Friday 20 August 2010] [06:11:22] <sustrik>    as for the code we are still not that far
| [Friday 20 August 2010] [06:11:40] <pieterh>    even if the new owners do things their own way, it's fine
| [Friday 20 August 2010] [06:11:49] <sustrik>    yes
| [Friday 20 August 2010] [06:12:07] <sustrik>    now, i can act a maintainer of the core for now
| [Friday 20 August 2010] [06:12:11] <pieterh>    for the code, i think it's still too integrated
| [Friday 20 August 2010] [06:12:13] <sustrik>    minus build system
| [Friday 20 August 2010] [06:12:15] <pieterh>    yes
| [Friday 20 August 2010] [06:12:19] <sustrik>    minus devices say
| [Friday 20 August 2010] [06:12:21] <pieterh>    yes
| [Friday 20 August 2010] [06:12:30] <sustrik>    ok
| [Friday 20 August 2010] [06:12:42] <pieterh>    even the three builtins can go into zfl
| [Friday 20 August 2010] [06:12:48] <pieterh>    no need to have these in core, in fact
| [Friday 20 August 2010] [06:12:52] <sustrik>    so I'll accept patches via email
| [Friday 20 August 2010] [06:12:59] <sustrik>    i will review them and merge them
| [Friday 20 August 2010] [06:13:17] <pieterh>    sounds like a nice simple process
| [Friday 20 August 2010] [06:13:21] <sustrik>    we have to ask mato if he's willing to do the same for build system
| [Friday 20 August 2010] [06:13:31] <sustrik>    mato: hullo!
| [Friday 20 August 2010] [06:13:34] <pieterh>    patches all go to zeromq-dev?
| [Friday 20 August 2010] [06:13:43] <sustrik>    where else?
| [Friday 20 August 2010] [06:13:52] <sustrik>    it makes them open to peer review
| [Friday 20 August 2010] [06:14:07] <pieterh>    i.e. not to github as issues, not to irc, not to you privately
| [Friday 20 August 2010] [06:14:29] <sustrik>    yes, it should be public imo
| [Friday 20 August 2010] [06:14:34] <pieterh>    yes, they must go to zeromq-dev
| [Friday 20 August 2010] [06:14:42] <mato>   sustrik: ?
| [Friday 20 August 2010] [06:14:51] <sustrik>    we are discussing process and QA
| [Friday 20 August 2010] [06:14:56] <pieterh>    with a standard subject that can be search/filtered easily
| [Friday 20 August 2010] [06:15:09] <sustrik>    i've just said i can take care of merging the patches to the core
| [Friday 20 August 2010] [06:15:18] <pieterh>    we can extend this to other Z* projects too
| [Friday 20 August 2010] [06:15:21] <sustrik>    but i cannot do the same with build system
| [Friday 20 August 2010] [06:15:32] <pieterh>    bindings, docs, zfl, zdevices, etc.
| [Friday 20 August 2010] [06:15:38] <mato>   guys, can we please discuss process and QA in person in Bratislava next week?
| [Friday 20 August 2010] [06:15:39] <sustrik>    [PATCH]
| [Friday 20 August 2010] [06:15:48] <pieterh>    mato: :-) we're thinking out loud
| [Friday 20 August 2010] [06:15:59] <pieterh>    [PATCH] is good
| [Friday 20 August 2010] [06:16:07] <mato>   pieterh: yes, fine, but i have a release to make for a client
| [Friday 20 August 2010] [06:16:15] <sustrik>    ok, no haste
| [Friday 20 August 2010] [06:16:18] <pieterh>    mato: yes, i know, no haste
| [Friday 20 August 2010] [06:16:20] <mato>   pieterh: and i would like to be part of the discussion
| [Friday 20 August 2010] [06:16:27] <sustrik>    there are not much build system patches anyway
| [Friday 20 August 2010] [06:16:51] <pieterh>    sustrik: i'm also using http://nvie.com/git-model
| [Friday 20 August 2010] [06:17:12] <pieterh>    but it may be that by keeping individual projects small, we don't need this
| [Friday 20 August 2010] [06:17:46] <sustrik>    dunno, i would like to use something that's 100% proven
| [Friday 20 August 2010] [06:18:01] <pieterh>    what does "100% proven" mean?
| [Friday 20 August 2010] [06:18:14] <pieterh>    how can you determine if something is 95.6% proven?
| [Friday 20 August 2010] [06:18:17] <sustrik>    already used in a large scale project for a reasonable amount of time
| [Friday 20 August 2010] [06:18:24] <pieterh>    this one is
| [Friday 20 August 2010] [06:18:30] <sustrik>    what's the project?
| [Friday 20 August 2010] [06:18:37] <pieterh>    read the page, if you have time
| [Friday 20 August 2010] [06:18:41] <sustrik>    ok
| [Friday 20 August 2010] [06:19:05] <pieterh>    however it's rather complex and IMO provides interesting pieces to reuse, rather than a fixed template
| [Friday 20 August 2010] [06:19:31] <pieterh>    but... it looks like very robust workflow
| [Friday 20 August 2010] [06:20:01] <guido_g>    and easy to understand
| [Friday 20 August 2010] [06:20:54] <guido_g>    mq is going to change my life... just ordered 2 books about git
| [Friday 20 August 2010] [06:21:01] <sustrik>    :)
| [Friday 20 August 2010] [06:21:02] <pieterh>    :-) 
| [Friday 20 August 2010] [06:21:25] <pieterh>    what git really really really needs is this kind of graphic workflow layer
| [Friday 20 August 2010] [06:22:50] <sustrik>    http://github.com/zeromq/zeromq2/network
| [Friday 20 August 2010] [06:23:12] <jsimmons>   the branches view is nice too
| [Friday 20 August 2010] [06:23:43] <jsimmons>   http://github.com/zeromq/zeromq2/branches
| [Friday 20 August 2010] [06:24:02] <pieterh>    sustrik: I mean, explaining how to branch and merge precisely
| [Friday 20 August 2010] [06:24:18] <sustrik>    jsimmons: nice
| [Friday 20 August 2010] [06:24:32] <sustrik>    ah, ok, true
| [Friday 20 August 2010] [06:24:39] <sustrik>    how can i get a branch to my box?
| [Friday 20 August 2010] [06:24:55] <jsimmons>   there's tortoise git, but I don't know how good that is
| [Friday 20 August 2010] [06:25:02] <sustrik>    been trying to do it yesterday, but no success
| [Friday 20 August 2010] [06:25:09] <pieterh>    git checkout -b unstable --track origin/unstable
| [Friday 20 August 2010] [06:25:22] <jsimmons>   there's a shortcut for that too...
| [Friday 20 August 2010] [06:25:33] <pieterh>    where 'unstable' is the branch name
| [Friday 20 August 2010] [06:25:42] <pieterh>    but if you clone the whole repository you get all branches
| [Friday 20 August 2010] [06:25:49] <sustrik>    no, i don't
| [Friday 20 August 2010] [06:26:02] <pieterh>    let me test that...
| [Friday 20 August 2010] [06:26:07] <sustrik>    clone zeromq2 -> i got master
| [Friday 20 August 2010] [06:26:09] <jsimmons>   yeah you get all the branches when you clone
| [Friday 20 August 2010] [06:26:11] <sustrik>    and that's it
| [Friday 20 August 2010] [06:26:22] <sustrik>    lemme show
| [Friday 20 August 2010] [06:26:27] <jsimmons>   but you have to explicitly check them out into the work directory
| [Friday 20 August 2010] [06:27:24] <pieterh>    ph@ws200901:~/tmp$ git clone git@github.com:zeromq/zeromq2.git
| [Friday 20 August 2010] [06:27:24] <pieterh>    ...
| [Friday 20 August 2010] [06:27:24] <pieterh>    Resolving deltas: 100% (4228/4228), done.
| [Friday 20 August 2010] [06:27:24] <pieterh>    ph@ws200901:~/tmp$ cd zeromq2/
| [Friday 20 August 2010] [06:27:24] <pieterh>    ph@ws200901:~/tmp/zeromq2$ git branch
| [Friday 20 August 2010] [06:27:25] <pieterh>    * master
| [Friday 20 August 2010] [06:27:25] <pieterh>    ph@ws200901:~/tmp/zeromq2$ git checkout wip-shutdown
| [Friday 20 August 2010] [06:27:26] <pieterh>    Branch wip-shutdown set up to track remote branch wip-shutdown from origin.
| [Friday 20 August 2010] [06:27:26] <pieterh>    Switched to a new branch 'wip-shutdown'
| [Friday 20 August 2010] [06:27:27] <pieterh>    ph@ws200901:~/tmp/zeromq2$
| [Friday 20 August 2010] [06:29:01] <sustrik>    here's what i get:
| [Friday 20 August 2010] [06:29:02] <sustrik>    sustrik@istvan:~$ git clone git@github.com:zeromq/zeromq2.git zeromq2-test
| [Friday 20 August 2010] [06:29:02] <sustrik>    Initialized empty Git repository in /home/sustrik/zeromq2-test/.git/
| [Friday 20 August 2010] [06:29:02] <sustrik>    ...
| [Friday 20 August 2010] [06:29:02] <sustrik>    Resolving deltas: 100% (4228/4228), done.
| [Friday 20 August 2010] [06:29:08] <sustrik>    sustrik@istvan:~/zeromq2-test$ git checkout wip-shutdown
| [Friday 20 August 2010] [06:29:10] <sustrik>    error: pathspec 'wip-shutdown' did not match any file(s) known to git.
| [Friday 20 August 2010] [06:29:12] <sustrik>    sustrik@istvan:~/zeromq2-test$ 
| [Friday 20 August 2010] [06:32:04] <jsimmons>   old git version maybe sustrik?
| [Friday 20 August 2010] [06:32:21] <mato>   sustrik: your git is weird, try git checkout origin/wip-shutdown
| [Friday 20 August 2010] [06:32:54] <pieterh>    sustrik: git --version?
| [Friday 20 August 2010] [06:33:19] <pieterh>    git checkout -b wip-shutdown --track origin/wip-shutdown
| [Friday 20 August 2010] [06:34:07] <sustrik>    yes, that works
| [Friday 20 August 2010] [06:34:27] <pieterh>    git has gotten smarter
| [Friday 20 August 2010] [06:34:55] <pieterh>    you used to have to tell it explicitly
| [Friday 20 August 2010] [06:35:09] <sustrik>    i still do for some reason
| [Friday 20 August 2010] [06:35:15] <pieterh>    git --version
| [Friday 20 August 2010] [06:35:19] <pieterh>    what does it say?
| [Friday 20 August 2010] [06:35:29] <sustrik>    1.6.3.3
| [Friday 20 August 2010] [06:35:36] <pieterh>    so, upgrade to git 1.7
| [Friday 20 August 2010] [06:35:47] <sustrik>    ok, let me try
| [Friday 20 August 2010] [06:36:22] <mato>   sustrik: only upgrade if you have a way of upgrading via your distro
| [Friday 20 August 2010] [06:36:30] <sustrik>    i don't
| [Friday 20 August 2010] [06:36:40] <pieterh>    what's your distro?
| [Friday 20 August 2010] [06:36:43] <sustrik>    but maybe i should upgrade the distro
| [Friday 20 August 2010] [06:36:47] <sustrik>    k.koala
| [Friday 20 August 2010] [06:36:51] <pieterh>    yeah
| [Friday 20 August 2010] [06:37:15] <pieterh>    latest ubuntu has great git integration: command completion etc.
| [Friday 20 August 2010] [06:37:27] <pieterh>    git checkout w[tab]
| [Friday 20 August 2010] [06:38:44] <sustrik>    !
| [Friday 20 August 2010] [06:39:55] <pieterh>    ?
| [Friday 20 August 2010] [07:13:21] <pieterh>    has anyone experienced weirdness with pipeline sockets?
| [Friday 20 August 2010] [07:13:33] <pieterh>    i have a really simple 3-stage pipeline that just won't work
| [Friday 20 August 2010] [07:13:36] <pieterh>    http://gist.github.com/540065
| [Friday 20 August 2010] [07:35:08] <pieterh>    also affects pub/sub sockets
| [Friday 20 August 2010] [07:35:34] <pieterh>    fuller description at http://github.com/zeromq/zeromq2/issues/#issue/49
| [Friday 20 August 2010] [11:46:21] <pieterh>    sustrik: I have made a bug report for that assertion failure: http://github.com/zeromq/zeromq2/issues/#issue/49
| [Friday 20 August 2010] [11:46:48] <sustrik>    pieterh: yes, seen it
| [Friday 20 August 2010] [11:47:13]   * sustrik installed lame lemming
| [Friday 20 August 2010] [11:47:17] <sustrik>    or what's the name
| [Friday 20 August 2010] [11:47:22] <sustrik>    it took like 3hrs
| [Friday 20 August 2010] [11:47:35] <pieterh>    slow downloads?
| [Friday 20 August 2010] [11:47:47] <pieterh>    did you do an upgrade or a real re-install?
| [Friday 20 August 2010] [11:47:54] <sustrik>    yes, something seems to be not ok with my isp
| [Friday 20 August 2010] [11:48:01] <sustrik>    upgrade
| [Friday 20 August 2010] [11:48:13] <pieterh>    painful
| [Friday 20 August 2010] [11:48:19] <pieterh>    but welcome to the future
| [Friday 20 August 2010] [11:48:25] <pieterh>    or at least the very recent past
| [Friday 20 August 2010] [11:48:40] <sustrik>    :)
| [Friday 20 August 2010] [11:51:14] <sustrik>    is there any way to get my toolbar buttons to the right?
| [Friday 20 August 2010] [11:51:24] <sustrik>    titlebar
| [Friday 20 August 2010] [11:51:40] <pieterh>    ubuntu or kubuntu?
| [Friday 20 August 2010] [11:52:28] <sustrik>    ubuntu
| [Friday 20 August 2010] [11:52:52] <pieterh>    there is probably a setting in the gnome configuration thingy
| [Friday 20 August 2010] [11:52:58] <pieterh>    nothing in the UI I can see
| [Friday 20 August 2010] [11:54:37] <pieterh>    sustrik: should i continue to hack on that test case, perhaps break into three processes and see if it still fails?
| [Friday 20 August 2010] [11:55:13] <sustrik>    the backtrace would be helpful
| [Friday 20 August 2010] [11:55:50] <pieterh>    ok, added to the issue
| [Friday 20 August 2010] [11:55:56] <pieterh>    can't you reproduce it?
| [Friday 20 August 2010] [11:56:17] <sustrik>    i'm doing five things in parallel
| [Friday 20 August 2010] [11:56:32] <pieterh>    ok, np
| [Friday 20 August 2010] [11:56:34] <sustrik>    haven't yet tried
| [Friday 20 August 2010] [11:56:36] <pieterh>    then put this aside for now
| [Friday 20 August 2010] [11:56:57] <pieterh>    i'm sure it will reproduce immediately
| [Friday 20 August 2010] [11:57:07] <pieterh>    it's in 2.0.7 so can't be urgent
| [Friday 20 August 2010] [11:57:18] <pieterh>    IMO it's related to multiple threads on same context
| [Friday 20 August 2010] [11:57:20] <sustrik>    let me see the backtrace
| [Friday 20 August 2010] [11:57:29] <pieterh>    http://github.com/zeromq/zeromq2/issues/#issue/49
| [Friday 20 August 2010] [11:58:56] <sustrik>    hm, values optimised out
| [Friday 20 August 2010] [11:58:58] <sustrik>    never midn
| [Friday 20 August 2010] [11:59:04] <sustrik>    i'll test it later on
| [Friday 20 August 2010] [11:59:42] <sustrik>    aha
| [Friday 20 August 2010] [11:59:49] <sustrik>    i know what's the problem
| [Friday 20 August 2010] [12:00:24] <sustrik>    pull/push require only a one-way pipe
| [Friday 20 August 2010] [12:00:47] <sustrik>    hm...
| [Friday 20 August 2010] [12:00:55] <sustrik>    combined with inproc
| [Friday 20 August 2010] [12:01:12] <sustrik>    i have to check
| [Friday 20 August 2010] [12:01:22] <sustrik>    anyway, it's inproc thing almost for sure
| [Friday 20 August 2010] [12:01:22] <pieterh>    i get the same error with pub/sub
| [Friday 20 August 2010] [12:01:26] <sustrik>    yes
| [Friday 20 August 2010] [12:01:32] <pieterh>    and similar strange behaviour with tcp: or ipc:
| [Friday 20 August 2010] [12:01:40] <sustrik>    if you swich to ipc or tcp it will go away
| [Friday 20 August 2010] [12:01:44] <pieterh>    except no assert, just nothing arrives on recv()
| [Friday 20 August 2010] [12:01:52] <sustrik>    ah
| [Friday 20 August 2010] [12:01:57] <pieterh>    see the bug report, i have 4 test programs, all do weird wrong stuff
| [Friday 20 August 2010] [12:02:08] <pieterh>    it's like the connection is not being made, at all
| [Friday 20 August 2010] [12:02:09] <sustrik>    ok, i'll have to inspect in depth
| [Friday 20 August 2010] [12:02:44] <pieterh>    could you just take a look at one program, see if i'm doing anything obviously wrong?
| [Friday 20 August 2010] [12:02:47] <pieterh>    they are really simple
| [Friday 20 August 2010] [12:03:11] <pieterh>    http://gist.github.com/540112 for example
| [Friday 20 August 2010] [12:09:40] <sustrik>    pieterh: subscription is missing in step2
| [Friday 20 August 2010] [12:10:03] <pieterh>    you're right!
| [Friday 20 August 2010] [12:10:07] <pieterh>    ok, let me retest with that...
| [Friday 20 August 2010] [12:11:03] <pieterh>    ok, i get the 'right' bad behaviour
| [Friday 20 August 2010] [12:11:08] <pieterh>    as with other socket types
| [Friday 20 August 2010] [12:11:16] <pieterh>    step1 to 2 works, step 2 to 3 always fails
| [Friday 20 August 2010] [12:11:47] <sustrik>    the assert?
| [Friday 20 August 2010] [12:11:58] <pieterh>    if i use inproc i get an assert
| [Friday 20 August 2010] [12:12:07] <pieterh>    if i use ipc or tcp the second recv hangs forever
| [Friday 20 August 2010] [12:12:28] <pieterh>    pub/sub or push/pull give same results
| [Friday 20 August 2010] [12:12:45] <pieterh>    first socket pair work, second socket pair fail
| [Friday 20 August 2010] [12:13:02] <sustrik>    ok, i'll have a look
| [Friday 20 August 2010] [12:14:53] <pieterh>    i'm testing with three separate processes now
| [Friday 20 August 2010] [12:21:30]   * pieterh is losing his hair
| [Friday 20 August 2010] [12:21:50] <pieterh>    i'm doing something really stupid with these test programs but don't know what :-(
| [Friday 20 August 2010] [12:21:56] <pieterh>    can't even make it work as separate processes...
| [Friday 20 August 2010] [12:27:10] <pieterh>    sustrik: ok, i found my utterly stupid mistake
| [Friday 20 August 2010] [12:27:26] <pieterh>    i'm going to rollback now and fix up all the testcases
| [Friday 20 August 2010] [12:27:56] <sustrik>    ?
| [Friday 20 August 2010] [12:28:12] <sustrik>    the assert is definitely a bug
| [Friday 20 August 2010] [12:28:15] <pieterh>    sigh... connecting wrong socket, input instead of output
| [Friday 20 August 2010] [12:28:36] <sustrik>    ok, so i'll fix the inproc stuff
| [Friday 20 August 2010] [12:28:40] <sustrik>    and that should do
| [Friday 20 August 2010] [12:28:42] <pieterh>    the assert is a bug but providing you broken testcases isn't useful
| [Friday 20 August 2010] [12:28:51] <pieterh>    let me clean up the issue and provide a clean testcase
| [Friday 20 August 2010] [12:31:29] <sustrik>    thx
| [Friday 20 August 2010] [12:53:19] <pieterh>    ok, just to confirm that I can provoke the assert but it requires a buggy application
| [Friday 20 August 2010] [12:53:30] <pieterh>    when i fixed my test cases they all worked perfectly
| [Friday 20 August 2010] [12:53:58] <mato>   pieterh: yo
| [Friday 20 August 2010] [12:54:04] <pieterh>    i've made minimal programs to provoke the assert, which hits SUB and PULL
| [Friday 20 August 2010] [12:54:05] <pieterh>    http://github.com/zeromq/zeromq2/issues/#issue/50
| [Friday 20 August 2010] [12:54:09] <mato>   pieterh: how's the baby & mother?
| [Friday 20 August 2010] [12:54:10] <pieterh>    hi mato
| [Friday 20 August 2010] [12:54:20] <pieterh>    mato: back home already, sylvie is made of tough stuff
| [Friday 20 August 2010] [12:54:34] <pieterh>    baby is doing great
| [Friday 20 August 2010] [12:54:45] <pieterh>    learning git workflows
| [Friday 20 August 2010] [12:54:48] <travlr> pieterh, a big congrats to you all
| [Friday 20 August 2010] [12:55:05] <mato>   pieterh: height/weight/name/sex? inquiring minds want to know...
| [Friday 20 August 2010] [12:55:26]   * mato was expecting the usual SMS SPAM but that must be just a slovak custom :-)
| [Friday 20 August 2010] [12:55:41] <pieterh>    3.3kg, Gregor Frans Mfumu Hintjens, male
| [Friday 20 August 2010] [12:55:54] <pieterh>    i posted on facebook and saved a few trees
| [Friday 20 August 2010] [12:56:07] <mato>   neat
| [Friday 20 August 2010] [12:56:31] <mato>   pieterh: are you coming here next week?
| [Friday 20 August 2010] [12:56:35] <pieterh>    travlr: thanks :-)
| [Friday 20 August 2010] [12:56:39] <pieterh>    mato: yeah, Monday
| [Friday 20 August 2010] [12:57:21] <pieterh>    sustrik: so to provoke the assert, one connects a sub to a sub, or a pull to pull, and reads from either
| [Friday 20 August 2010] [12:58:00] <pieterh>    it is kind of a DoS because it lets you crash arbitrary sockets by connecting to them wrongly
| [Friday 20 August 2010] [12:58:01] <sustrik>    yes, there's some problems with creating pipes between two sockets
| [Friday 20 August 2010] [12:58:11] <pieterh>    but it only affects inproc afaics
| [Friday 20 August 2010] [12:58:17] <pieterh>    so it's really not a big issue
| [Friday 20 August 2010] [12:58:22] <sustrik>    yes
| [Friday 20 August 2010] [12:58:29] <mato>   sustrik: is there a way we can make sure that you can't connect socket X to Y if that is just silly?
| [Friday 20 August 2010] [12:58:35] <mato>   sustrik: systematically?
| [Friday 20 August 2010] [12:58:38] <pieterh>    mato: yes, we will need to do this
| [Friday 20 August 2010] [12:58:39] <sustrik>    shouldn't be hard to fix either
| [Friday 20 August 2010] [12:58:43] <pieterh>    it has to go into the protocol IMO
| [Friday 20 August 2010] [12:59:05] <pieterh>    otherwise people will start to connect PUB to PULL, kind of stuff
| [Friday 20 August 2010] [12:59:06] <sustrik>    silly = uncompatible patterns, roght?
| [Friday 20 August 2010] [12:59:09] <pieterh>    yes
| [Friday 20 August 2010] [12:59:11] <mato>   sustrik: yes
| [Friday 20 August 2010] [12:59:17] <sustrik>    yes, it should be done
| [Friday 20 August 2010] [12:59:36] <pieterh>    yes, it's in the 3.0 page I think
| [Friday 20 August 2010] [12:59:48] <mato>   sustrik: for all except pub/sub it should be fairly easy to add this to the initial message sent on connection establishment, no?
| [Friday 20 August 2010] [12:59:55] <pieterh>    "Pattern checking" on http://www.zeromq.org/docs:3_0
| [Friday 20 August 2010] [13:00:06] <sustrik>    rather for anything aside PGM
| [Friday 20 August 2010] [13:00:13] <mato>   ah, right
| [Friday 20 August 2010] [13:00:13] <pieterh>    mato: don't you read the website ? :-)
| [Friday 20 August 2010] [13:00:15] <mato>   yes
| [Friday 20 August 2010] [13:00:17] <mato>   pieterh: no
| [Friday 20 August 2010] [13:00:23] <pieterh>    :-)
| [Friday 20 August 2010] [13:00:53] <pieterh>    it's nice that people reinvent the same solutions because it kind of proves that that's the right direction to go
| [Friday 20 August 2010] [13:02:20] <mato>   and i still have 260 unread messages in the list inbox, need to go through those :(
| [Friday 20 August 2010] [13:02:39] <pieterh>    mato: i was _going_ to send out SMSs but my lovely android phone collects every single %!$# contact it can find
| [Friday 20 August 2010] [13:02:51] <pieterh>    so my contact list is 5,000 entries long
| [Friday 20 August 2010] [13:02:55] <mato>   pieterh: ah :-) that would be true SMS SPAM then 
| [Friday 20 August 2010] [13:03:01] <mato>   expensive, too 
| [Friday 20 August 2010] [13:03:02] <pieterh>    i gave up selecting people to SMS to after the Bs
| [Friday 20 August 2010] [13:03:44] <mato>   doesn't it split the contacts into "contacts you're actually interested in" and "everything else" ?
| [Friday 20 August 2010] [13:04:01] <pieterh>    that'd be nice, wouldn't it...
| [Friday 20 August 2010] [13:04:10] <mato>   yes :-)
| [Friday 20 August 2010] [13:04:52] <pieterh>    mato: so we were discussing breaking stuff out of the zmq core project
| [Friday 20 August 2010] [13:05:16] <mato>   pieterh: breaking yet more stuff out? it's pretty minimalist as is
| [Friday 20 August 2010] [13:05:29] <pieterh>    i think the general idea is to create smaller projects, each with one or two maintainers, each focused on one thing
| [Friday 20 August 2010] [13:05:42] <pieterh>    it would allow simple workflow on each project
| [Friday 20 August 2010] [13:05:50] <mato>   yes, but what did you have in mind?
| [Friday 20 August 2010] [13:05:58] <mato>   to break out ...
| [Friday 20 August 2010] [13:06:03] <pieterh>    i like sustrik's "send me patches by email, i'll review and apply them"
| [Friday 20 August 2010] [13:06:05] <pieterh>    so...
| [Friday 20 August 2010] [13:06:30] <pieterh>    starting with stuff that does not really fit into core and which is a maintenance job
| [Friday 20 August 2010] [13:06:39] <pieterh>    devices (mains())
| [Friday 20 August 2010] [13:06:48] <pieterh>    then devices (methods)
| [Friday 20 August 2010] [13:07:16] <mato>   anything else?
| [Friday 20 August 2010] [13:07:17] <pieterh>    we already have independent projects for bindings
| [Friday 20 August 2010] [13:07:24] <pieterh>    and for the user guide
| [Friday 20 August 2010] [13:07:33] <mato>   yes, but the bindings are fairly naturally small worlds of their own
| [Friday 20 August 2010] [13:07:35] <pieterh>    yes
| [Friday 20 August 2010] [13:07:41] <mato>   devices, i'm not so sure
| [Friday 20 August 2010] [13:07:56] <mato>   given that the devices are actually both part of the overall power of 0mq
| [Friday 20 August 2010] [13:07:57] <pieterh>    so devices... this will require time to settle down
| [Friday 20 August 2010] [13:08:04] <pieterh>    but what i think, have seen so far...
| [Friday 20 August 2010] [13:08:13] <pieterh>    is that we will end up making a lot of devices
| [Friday 20 August 2010] [13:08:20] <pieterh>    timers, reactors, queues, etc.
| [Friday 20 August 2010] [13:08:24] <pieterh>    in random languages
| [Friday 20 August 2010] [13:08:34] <sustrik>    i would say devices are naturally separated from the core
| [Friday 20 August 2010] [13:08:38] <pieterh>    that's the first thing, we have already seen this start
| [Friday 20 August 2010] [13:08:42] <sustrik>    think of a HW device
| [Friday 20 August 2010] [13:08:46] <pieterh>    yes
| [Friday 20 August 2010] [13:08:55] <pieterh>    naturally separate
| [Friday 20 August 2010] [13:09:15] <pieterh>    made by different people, to solve different problems
| [Friday 20 August 2010] [13:09:31] <mato>   sustrik: well, if you think so. i just had the feeling that given that the concept of devices is so important in the long term vision
| [Friday 20 August 2010] [13:09:33] <pieterh>    the only reason the queue device is built-in today is that the protocol ain't properly documented AFAICS
| [Friday 20 August 2010] [13:09:46] <pieterh>    devices are REALLY important, no doubt about it
| [Friday 20 August 2010] [13:09:49] <mato>   sustrik: that it would be good to at least keep a core set of devices in the distribution
| [Friday 20 August 2010] [13:09:55] <pieterh>    mato: coming to that, hang on...
| [Friday 20 August 2010] [13:10:05] <pieterh>    not proposing to scrap that
| [Friday 20 August 2010] [13:10:31] <pieterh>    proposal is (and feel free to beat this up):
| [Friday 20 August 2010] [13:10:55] <pieterh>    - collect device applications (random code like zmq_deviced, etc.) in a separate repository
| [Friday 20 August 2010] [13:11:05] <pieterh>    - encourage experimentation in all languages
| [Friday 20 August 2010] [13:11:17] <pieterh>    this is the device 'wiki'... no workflow, no releases
| [Friday 20 August 2010] [13:11:24] <pieterh>    step 2:
| [Friday 20 August 2010] [13:11:37] <pieterh>    take best practice from that and package for reuse
| [Friday 20 August 2010] [13:11:54] <pieterh>    - in zfl, perhaps, or similar library depending on language
| [Friday 20 August 2010] [13:11:57] <pieterh>    step 3:
| [Friday 20 August 2010] [13:12:05] <pieterh>    take best of that and package into zmq core
| [Friday 20 August 2010] [13:12:13] <pieterh>    - like queue, forwarder, and streamer
| [Friday 20 August 2010] [13:12:33] <pieterh>    so the more mature the device the wider the distribution it gets
| [Friday 20 August 2010] [13:12:55] <mato>   pieterh: that sounds fine
| [Friday 20 August 2010] [13:12:58] <mato>   pieterh: with one caveat
| [Friday 20 August 2010] [13:13:02] <pieterh>    shoot
| [Friday 20 August 2010] [13:13:41] <mato>   pieterh: that at step 3, anything going into core follows core's rules; in other words basically C (ideally C++) with no external dependencies
| [Friday 20 August 2010] [13:13:45] <mato>   pieterh: at least for now
| [Friday 20 August 2010] [13:13:49] <pieterh>    yes, precisely
| [Friday 20 August 2010] [13:13:58] <travlr> +1... from one in the lowest depth of the peanut gallery :)
| [Friday 20 August 2010] [13:14:07] <pieterh>    that's exactly it
| [Friday 20 August 2010] [13:14:24] <pieterh>    so by doing this, we remove xmlStore or whatever from the distro
| [Friday 20 August 2010] [13:14:35] <mato>   ?
| [Friday 20 August 2010] [13:14:42] <pieterh>    don't need it any more
| [Friday 20 August 2010] [13:14:51] <pieterh>    no external dependencies
| [Friday 20 August 2010] [13:14:56] <mato>   you're proposing removing the current devices? i didn't catch that
| [Friday 20 August 2010] [13:15:01] <sustrik>    libuuid :(
| [Friday 20 August 2010] [13:15:26] <mato>   sustrik: i mean no big huge tool-du-jour dependencies
| [Friday 20 August 2010] [13:15:28] <sustrik>    i would say the devices should be in a separate package
| [Friday 20 August 2010] [13:15:31] <mato>   sustrik: unless we all agree
| [Friday 20 August 2010] [13:15:34] <pieterh>    mato: yes, moving main programs to separate git
| [Friday 20 August 2010] [13:15:39] <sustrik>    the rationale:
| [Friday 20 August 2010] [13:15:39] <pieterh>    i've already made that, see http://github.com/imatix/zdevices
| [Friday 20 August 2010] [13:15:47] <sustrik>    zmq-core can be fully stabilised
| [Friday 20 August 2010] [13:15:50] <pieterh>    yes
| [Friday 20 August 2010] [13:15:52] <sustrik>    while devices are still in move
| [Friday 20 August 2010] [13:16:01] <pieterh>    experimentation is vital but not on the same git
| [Friday 20 August 2010] [13:16:20] <pieterh>    different licenses (GPL, not LGPL)
| [Friday 20 August 2010] [13:16:26] <mato>   well, some experimentation will always happen in the "same git" since there is no such thing as the "same git" anyway
| [Friday 20 August 2010] [13:16:33] <mato>   but yes, good plan otherwise
| [Friday 20 August 2010] [13:16:48] <mato>   i suggest that this is announced on the mailing list
| [Friday 20 August 2010] [13:16:49] <pieterh>    ok... good... and this really reduces the need for formal workflows
| [Friday 20 August 2010] [13:17:00] <pieterh>    it can become: "email patch to maintainer".  period.
| [Friday 20 August 2010] [13:17:06] <pieterh>    that is zeroworkflow
| [Friday 20 August 2010] [13:17:36] <pieterh>    mato: i'd actually suggest a separate email list, zeromq-patch@etc... if we do that
| [Friday 20 August 2010] [13:17:48] <mato>   pieterh: maybe, not yet, to be discussed
| [Friday 20 August 2010] [13:17:54] <pieterh>    ack
| [Friday 20 August 2010] [13:17:56] <mato>   next week
| [Friday 20 August 2010] [13:18:05] <sustrik>    then you are missing 350 people who could possibly review the patch
| [Friday 20 August 2010] [13:18:19] <mato>   yes, not right now
| [Friday 20 August 2010] [13:18:37] <pieterh>    true
| [Friday 20 August 2010] [13:18:46] <pieterh>    i really like the lazy workflow though
| [Friday 20 August 2010] [13:18:53] <pieterh>    it seems perfect
| [Friday 20 August 2010] [13:19:27] <sustrik>    that's linux kernel way of doing it, no?
| [Friday 20 August 2010] [13:19:33] <sustrik>    send the patch to lkml
| [Friday 20 August 2010] [13:20:04] <mato>   sustrik: mostly, yes
| [Friday 20 August 2010] [13:20:16] <mato>   sustrik: but you still need a workflow for the people actually committing 
| [Friday 20 August 2010] [13:20:19] <mato>   sustrik: those patches
| [Friday 20 August 2010] [13:20:25] <sustrik>    no doubt
| [Friday 20 August 2010] [13:20:34] <mato>   sustrik: which is what we need to discuss next week
| [Friday 20 August 2010] [13:20:40] <mato>   sustrik: i will present how i think it works
| [Friday 20 August 2010] [13:20:43] <mato>   sustrik: ok?
| [Friday 20 August 2010] [13:20:49] <mato>   sustrik: next week, in person, at a table
| [Friday 20 August 2010] [13:20:54] <sustrik>    ok, np
| [Friday 20 August 2010] [13:21:21] <mato>   pieterh: for experimental repos, bindings, etc, anyhow, the workflow is mostly determined by the maintainer
| [Friday 20 August 2010] [13:21:29] <sustrik>    i like that it makes things simple for contributors
| [Friday 20 August 2010] [13:21:36] <mato>   yes, of course
| [Friday 20 August 2010] [13:21:43] <sustrik>    while burdening only committers with the process
| [Friday 20 August 2010] [13:21:50] <mato>   yes
| [Friday 20 August 2010] [13:24:42] <pieterh>    ok, i've renamed 0MQGuide repo to zguide
| [Friday 20 August 2010] [13:25:13] <pieterh>    zo, we 'af zguide, zdevices, unt zfunctionlibrary oder zfl
| [Friday 20 August 2010] [13:25:46] <pieterh>    i am going to zbeach with the family, cyal
| [Friday 20 August 2010] [13:25:52] <mato>   :)
| [Friday 20 August 2010] [13:25:55] <mato>   cya
| [Friday 20 August 2010] [13:26:00] <sustrik>    cya
| [Friday 20 August 2010] [13:26:07] <pieterh>    cya mato :-) cya sustrik
| [Friday 20 August 2010] [21:14:24] <rbraley>    say, what does zero-copy mean for message passing?
| [Friday 20 August 2010] [21:52:10] <zedas>  sustrik: hey so i've found a potential bug in zmq_poll
| [Friday 20 August 2010] [21:52:37] <zedas>  sustrik: i'll work up a fix, but you go into a permanent loop when poll sets EINTR errno
| [Friday 20 August 2010] [21:52:57] <zedas>  it still seems to work, but it's just calling poll like mad pegging that thread at 100%
| [Friday 20 August 2010] [21:53:31] <zedas>  it's also why 0mq sockets seem to "die".  we traced it down in mongrel2 to the line in zmq.cpp that does the continue on EINTR
| [Friday 20 August 2010] [21:55:30] <travlr> rbraley: http://www.zeromq.org/docs:user-guide#toc17
| [Friday 20 August 2010] [22:10:54] <rbraley>    http://www.malhar.net/sriram/kilim/ check the tech talk
| [Friday 20 August 2010] [22:11:20] <rbraley>    I want to see if I can do this with C++ and ZeroMQ 
| [Friday 20 August 2010] [22:28:14] <travlr> rbraley: after reading the first sentence, i saw that's the concept you've been reaching for with zmq
| [Friday 20 August 2010] [22:28:30] <rbraley>    yes!
| [Friday 20 August 2010] [22:28:47] <travlr> use the source luke... use the source ... lol
| [Friday 20 August 2010] [22:30:32] <travlr> you should start a new thread on zeromq-dev mail list for this topic... you'll get some interest and suggestions to boot.
| [Friday 20 August 2010] [22:32:21] <rbraley>    travlr, Since this technique requires code transformation I am thinking about either seeing if I can do it with the preprocessor(kinda doubtful) or maybe extending Qt's meta object-compiler to support the Actor Model
| [Friday 20 August 2010] [22:33:16] <travlr> ok,, here's a stupid question i've been thinking about.. this is neat stuff, but are you sure you need it?
| [Friday 20 August 2010] [22:33:48] <travlr> btw the actor model is very close to fbp itself
| [Friday 20 August 2010] [22:35:59] <rbraley>    basically the concept for an ultra-lightweight process a la erlang is just like process isolation for OS processes, they don't need to know about the other ones at all and shouldn't, unless you send messages. But they are much much smaller than threads. That means they can fail in isolation and your program doesn't die unless you tell it to die.
| [Friday 20 August 2010] [22:37:33] <rbraley>    yes I am sure I need it. My game architecture requires that every entity in the game be an actor. That means that threads can't cut it unless I only want 1000 things in my game.
| [Friday 20 August 2010] [22:38:01] <travlr> and individual processes (executables) don't have zero-copy so that scratches that idea i suppose.
| [Friday 20 August 2010] [22:38:26] <jsimmons>   why should you have an individual thread per actor?
| [Friday 20 August 2010] [22:39:04] <rbraley>    and they're huge and would mess up your system process monitor, like $ ps -eaf or $ top or some gui equivalent
| [Friday 20 August 2010] [22:39:06] <travlr> true, with inproc maybe you don't need threads
| [Friday 20 August 2010] [22:40:15] <rbraley>    messages aren't the only concurrent things that happen. Actors still need to do stuff. And they shouldn't have to wait for each other unnecessarily
| [Friday 20 August 2010] [22:40:29] <jsimmons>   aside from the difficulty in implementation, having actors individually threaded is horribly inefficient
| [Friday 20 August 2010] [22:41:09] <travlr> i see. you need light weighted threads ;)
| [Friday 20 August 2010] [22:41:34] <rbraley>    I do want to multiplex actors onto different system threads, one thread per core.
| [Friday 20 August 2010] [22:41:59] <travlr> you'll do the gaming community a big service if you do implement it zmq
| [Friday 20 August 2010] [22:42:04] <jsimmons>   you mean co-routines or cooperative multithreading
| [Friday 20 August 2010] [22:42:07] <jsimmons>   I presume
| [Friday 20 August 2010] [22:43:35] <rbraley>    jsimmons, it is possible to do preemptive scheduling of ultra-lightweight threads (as I think only erlang does right now). But yeah I would transform functions into continuation-passing style
| [Friday 20 August 2010] [22:45:31] <rbraley>    and each actor would get its own stack and context switch between other actors on the same thread entirely in user space making it around 3 orders of magnitude faster than context switching between user space and kernel space that threads do.
| [Friday 20 August 2010] [22:46:41] <rbraley>    sorry, the first occurrence of context switch in my previous statement was used incorrectly
| [Friday 20 August 2010] [22:46:46] <jsimmons>   my point is, are you really going to make it faster than say brute forcing or executing in blocks
| [Friday 20 August 2010] [22:47:05] <rbraley>    brute forcing?
| [Friday 20 August 2010] [22:47:28] <jsimmons>   as in for actor in actors do actor.update()
| [Friday 20 August 2010] [22:47:42] <jsimmons>   I should say 'buckets' rather than blocks
| [Friday 20 August 2010] [22:48:14] <travlr> you'd probably save yourself hassle if you implemented in java with kilim, but that would have to mean coding in java.. eeww :P
| [Friday 20 August 2010] [22:48:19] <rbraley>    within a single thread it will do round robin or poll() or something 
| [Friday 20 August 2010] [22:49:06] <rbraley>    but there will be n threads for n cores so it will scale as well as whatever your hardware can handle
| [Friday 20 August 2010] [22:49:47] <rbraley>    and it doesn't even need to be one machine, with zeromq.
| [Friday 20 August 2010] [22:50:30] <travlr> have you studied zmq source yet?
| [Friday 20 August 2010] [22:50:32] <rbraley>    but this may also work with GPUs
| [Friday 20 August 2010] [22:50:43] <rbraley>    travlr, yes but not since we talked
| [Friday 20 August 2010] [22:51:14] <travlr> yeah what about simply using coda for gpu or similar .... 10-100x
| [Friday 20 August 2010] [22:51:54] <rbraley>    well I was hoping to migrate actors off the threads to the GPU if possible
| [Friday 20 August 2010] [22:52:11] <jsimmons>   gpu will suck for actor logic
| [Friday 20 August 2010] [22:52:18] <travlr> yeah i know i was missing something with that thought
| [Friday 20 August 2010] [22:52:20] <jsimmons>   unless you have super super simple actors
| [Friday 20 August 2010] [22:52:35] <rbraley>    all actors tend to be super simple jsimmons 
| [Friday 20 August 2010] [22:53:02] <jsimmons>   by actors do you mean something like boids, then?
| [Friday 20 August 2010] [22:54:04] <rbraley>    no, (of course they would be good for agent-based modeling and emergent behavior) actors are in the context of the Actor Model of concurrency
| [Friday 20 August 2010] [22:54:56] <rbraley>    https://secure.wikimedia.org/wikipedia/en/wiki/Actor_model
| [Friday 20 August 2010] [22:55:20] <jsimmons>   because as soon as you start branching on the gpu you take a massive performance hit
| [Friday 20 August 2010] [22:55:41] <rbraley>    ah
| [Friday 20 August 2010] [22:55:56] <rbraley>    yes well just make two actors then 
| [Friday 20 August 2010] [22:56:16] <rbraley>    one where the branch succeeds and one where the branch fails
| [Friday 20 August 2010] [22:56:59] <rbraley>    then leave choosing which computation to keep back at the CPU
| [Friday 20 August 2010] [22:57:01] <jsimmons>   ah I've been oversimplifying 'Actor'
| [Friday 20 August 2010] [22:58:23] <rbraley>    it is hard to oversimplify actors, since they are a single primitive that is computationally universal :P
| [Friday 20 August 2010] [22:58:58] <rbraley>    even the lambda calculus has two primitives
| [Friday 20 August 2010] [23:01:03] <rbraley>    basically: the real world is concurrent, how can we model that in an optimal way? -> actors
| [Friday 20 August 2010] [23:01:06] <jsimmons>   I mean I was imposing my own meaning from traditional game engines
| [Friday 20 August 2010] [23:02:23] <rbraley>    yeah I am doing something that is either really stupid or 10-30 years ahead of its time :P so I wouldn't expect any game engine to bear a resemblance to mine.
| [Friday 20 August 2010] [23:02:50] <rbraley>    although some come close
| [Friday 20 August 2010] [23:03:08] <travlr> nothing wrong with trying to "touch" the hardware from my point of view ;-)
| [Friday 20 August 2010] [23:04:28] <rbraley>    travlr, I want to make sexy times with the hardware and blow current engines out of the water, at least from a scalability/concurrency standpoint
| [Friday 20 August 2010] [23:05:38] <travlr> no doubt.. kudos imo
| [Friday 20 August 2010] [23:06:53] <rbraley>    thanks, it's frustrating that I have to invent so much to realize my vision, but hey, at least there's 0MQ, and Protocol Buffers.
| [Friday 20 August 2010] [23:07:16] <jsimmons>   I'll be interested if you make it work :D
| [Friday 20 August 2010] [23:07:45] <travlr> i like paying attention to your vision.. as i apply some of it in my mind to my needs
| [Friday 20 August 2010] [23:07:54] <rbraley>    jsimmons, so will I :D
| [Friday 20 August 2010] [23:09:25] <rbraley>    I just need to invent the 0MQ of actor model frameworks. 
| [Friday 20 August 2010] [23:10:22] <rbraley>    well that is a recursive definition ;)
| [Friday 20 August 2010] [23:10:48] <rbraley>    I need ultra-lightweight processes for C++
| [Friday 20 August 2010] [23:11:12] <travlr> start a thread on the ml... i want to follow along ;)
| [Friday 20 August 2010] [23:12:33] <travlr> i'm sure that if implemented as you describe it will find plenty of use cases outside of a game engine
| [Friday 20 August 2010] [23:12:47] <rbraley>    of course!
| [Friday 20 August 2010] [23:12:57] <travlr> like mine 
| [Friday 20 August 2010] [23:13:09] <travlr> :-D
| [Friday 20 August 2010] [23:13:14] <rbraley>    hehe
| [Friday 20 August 2010] [23:13:51] <rbraley>    this kilim is cool, but it doesn't adhere to a unix philosophy
| [Friday 20 August 2010] [23:14:38] <travlr> for some reason anything java just rubs me the wrong way.. i don't event want to begin to play with it.. i don't know why but that's the way it is
| [Friday 20 August 2010] [23:14:52] <rbraley>    travlr, that's called bigotry :P
| [Friday 20 August 2010] [23:14:56] <travlr> lol
| [Friday 20 August 2010] [23:15:07] <jsimmons>   as far as I'm concerned, at least it's not C++ :P
| [Friday 20 August 2010] [23:15:27] <travlr> i've learned to love c++, thanks to Qt
| [Friday 20 August 2010] [23:15:30] <rbraley>    http://www.mirah.org/
| [Friday 20 August 2010] [23:15:57] <jsimmons>   I kinda despise Qt
| [Friday 20 August 2010] [23:16:14] <rbraley>    any rubyists may enjoy that link
| [Friday 20 August 2010] [23:16:22] <travlr> jsimmons: yes i understand.. to each their own..
| [Friday 20 August 2010] [23:16:32] <jsimmons>   Gtk supremacy travlr :P
| [Friday 20 August 2010] [23:16:38] <rbraley>    jsimmons, whaaat? I don't understand.
| [Friday 20 August 2010] [23:16:47] <travlr> oh, so you want to start a flame war now... lol
| [Friday 20 August 2010] [23:16:54] <rbraley>    oh Gtk, ok
| [Friday 20 August 2010] [23:17:35] <jsimmons>   Actually I'm not a big fan of the Gtk graphical toolkit bit, but I like GLib, especially GObject introspection. :D
| [Friday 20 August 2010] [23:18:10] <rbraley>    I do too, actually have you heard of Vala, jsimmons? 
| [Friday 20 August 2010] [23:18:33] <jsimmons>   Yeah rbraley, I've even patched some of the vapis :P
| [Friday 20 August 2010] [23:18:43] <rbraley>    well played
| [Friday 20 August 2010] [23:19:34] <rbraley>    Gtk is problematic, but Glib is really neat.
| [Friday 20 August 2010] [23:19:52] <jsimmons>   Have you heard of Clutter/Mx rbraley? 
| [Friday 20 August 2010] [23:20:05] <rbraley>    is that the opengl gui?
| [Friday 20 August 2010] [23:20:43] <jsimmons>   Yeah clutter is an opengl scene graph/animation framework kinda thing, and mx is a ui library that uses clutter.
| [Friday 20 August 2010] [23:21:12] <rbraley>    nice
| [Friday 20 August 2010] [23:21:25] <jsimmons>   It's used in stuff like MeeGo
| [Friday 20 August 2010] [23:21:49] <rbraley>    cool
| [Friday 20 August 2010] [23:23:05] <jsimmons>   but enough tomfoolery for now, I think I'll go stab some people in Oblivion. :D good luck with your multi-tasking madness.
| [Friday 20 August 2010] [23:25:21] <rbraley>    jsimmons, the game I am working on is very similar to a TES title
| [Friday 20 August 2010] [23:25:46] <rbraley>    jsimmons, http://dungeonhack.sf.net
| [Friday 20 August 2010] [23:27:18] <jsimmons>   bookmarked
| [Friday 20 August 2010] [23:45:35] <rbraley>    travlr, this might just do the trick http://theron.ashtonmason.net/index.php?t=page&p=threadpool
| [Friday 20 August 2010] [23:48:38] <travlr> very interesting.. get it in zmq now
| [Friday 20 August 2010] [23:50:42] <travlr> this stuff still confuses me a bit.. i'll have to study it more
| [Friday 20 August 2010] [23:53:25] <rbraley>    they have their own message passing implementation, which seems to be just within the same address space of the process and can't scale to multiple machines
| [Friday 20 August 2010] [23:53:41] <rbraley>    like 0MQ can
| [Friday 20 August 2010] [23:53:46] <travlr> right, hence my call to zmq impl
| [Friday 20 August 2010] [23:54:02] <travlr> only provides part of the story
| [Friday 20 August 2010] [23:54:24] <travlr> are you gonna do it?
| [Friday 20 August 2010] [23:55:28] <rbraley>    depends on if it is written with hard dependencies on the way they do message passing or not
| [Friday 20 August 2010] [23:56:09] <travlr> use their ideas. what's its license?
| [Friday 20 August 2010] [23:58:55] <travlr> Creative Commons Attribution 3.0 License
| [Friday 20 August 2010] [23:59:00] <rbraley>    sweet
| [Saturday 21 August 2010] [00:01:15] <travlr>   i say start a thread on the ml and get some interest going
| [Saturday 21 August 2010] [00:05:17] <travlr>   this is a new library.. you should contact the dev(s) there and convince them to work with you on zmq impl
| [Saturday 21 August 2010] [00:05:41] <travlr>   not new but very active
| [Saturday 21 August 2010] [00:05:48] <rbraley>  travlr, never used a mailinglist before. Always google groups or fora
| [Saturday 21 August 2010] [00:06:27] <travlr>   only 503 threads
| [Saturday 21 August 2010] [00:06:35] <travlr>   is that enough for you
| [Saturday 21 August 2010] [00:19:40] <rbraley>  nevar!
| [Saturday 21 August 2010] [00:21:24] <travlr>   does dabbleboard have automagic spacing for flow charts?
| [Saturday 21 August 2010] [00:37:11] <rbraley>  I don't know I just found it on the spot because you wanted something like that 
| [Saturday 21 August 2010] [00:37:20] <travlr>   k
| [Saturday 21 August 2010] [01:20:21] <sustrik>  zedas: yes, the code is messy there
| [Saturday 21 August 2010] [01:20:47] <sustrik>  zmq_poll will get rewritten in new version
| [Saturday 21 August 2010] [01:20:59] <sustrik>  in the meantime, if you get patch, i'll apply it
| [Saturday 21 August 2010] [01:48:49] <zedas>    sustrik: cool it'll be against 2.0.7
| [Saturday 21 August 2010] [01:49:02] <sustrik>  sure
| [Saturday 21 August 2010] [01:49:03] <sustrik>  thanks
| [Saturday 21 August 2010] [01:51:39] <zedas>    sustrik: ah i think i found it: //  Wait for events. Ignore interrupts if there's infinite timeout
| [Saturday 21 August 2010] [01:51:55] <zedas>    we have infinite timeout
| [Saturday 21 August 2010] [01:53:04] <sustrik>  let me see
| [Saturday 21 August 2010] [01:54:01] <sustrik>  hm, does it result in infinite loop?
| [Saturday 21 August 2010] [01:54:45] <sustrik>  once the signal is processed, the loop should exit afaics
| [Saturday 21 August 2010] [01:55:49] <sustrik>  what signal are you testing with?
| [Saturday 21 August 2010] [02:05:17] <zedas>    well, if you have -1 one timeout, then EINTR happens, and then it loops, poll runs, exits immediately with EINTR, repeate
| [Saturday 21 August 2010] [02:05:29] <zedas>    so not sure why poll thinks it has an EINTR condition again
| [Saturday 21 August 2010] [02:05:39] <sustrik>  maybe the signal is unhadled
| [Saturday 21 August 2010] [02:05:50] <zedas>    we've got SIGINT, SIGHUP, SIGQUIT, but none of those fire during this loop
| [Saturday 21 August 2010] [02:05:51] <sustrik>  so it stays in the signal queue
| [Saturday 21 August 2010] [02:06:25] <zedas>    could it be socket close for some reason?
| [Saturday 21 August 2010] [02:06:36] <zedas>    let me try a few signal catchers....see what i'm getting.
| [Saturday 21 August 2010] [02:06:36] <sustrik>  SIGPIPE?
| [Saturday 21 August 2010] [02:06:57] <zedas>    yeah but i can't see why...i pretty much block those but lemme see.
| [Saturday 21 August 2010] [02:07:05] <sustrik>  use gdb
| [Saturday 21 August 2010] [02:07:15] <sustrik>  there's an option to stop on a signal
| [Saturday 21 August 2010] [02:07:16] <sustrik>  iirc
| [Saturday 21 August 2010] [02:07:39] <sustrik>  'handle' command i think
| [Saturday 21 August 2010] [02:08:42] <zedas>    ah yeah
| [Saturday 21 August 2010] [02:10:27] <zedas>    SIGPIPE is the most frustrating signal ever
| [Saturday 21 August 2010] [02:10:35] <zedas>    whoever thought it should be part of sockets should be shot
| [Saturday 21 August 2010] [02:10:42] <sustrik>  :)
| [Saturday 21 August 2010] [02:26:05] <zedas>    sustrik: ok looks like SIGPIPE was the culprit.  i set it to SIG_IGN and haven't had the problem yet.
| [Saturday 21 August 2010] [02:26:10] <zedas>    i'll keep you posted
| [Saturday 21 August 2010] [02:27:23] <sustrik>  zedas: thanks
| [Saturday 21 August 2010] [02:38:55] <zedas>    sustrik: nope
| [Saturday 21 August 2010] [02:39:11] <zedas>    i have every possible signal blocked and it's still setting EINTR
| [Saturday 21 August 2010] [02:41:41] <sustrik>  what does gdb say?
| [Saturday 21 August 2010] [02:41:46] <sustrik>  handle all print
| [Saturday 21 August 2010] [03:29:36] <zedas>    sustrik: well in the process of adding a timer, i found out that zmq_poll has a timeout/1000 in it, so it give different poll semantics on timeout
| [Saturday 21 August 2010] [03:30:02] <zedas>    which was causing mongrel2 to thrash if there was a timer, so fixed that, now seeing if having a timeout causes it or not
| [Saturday 21 August 2010] [03:32:31] <sustrik>  are you saying the signal you've seen was the timer signal?
| [Saturday 21 August 2010] [03:36:27] <zedas>    nope, i'm saying the timeout parameter to zmq_poll is different from real poll
| [Saturday 21 August 2010] [03:36:35] <zedas>    it's /1000, so if you pass in ms it's way off
| [Saturday 21 August 2010] [03:37:06] <zedas>    i added a timout to the zmq_poll so i could see the effect of it on those branches in zmq_poll that continue if there's EINTR
| [Saturday 21 August 2010] [03:37:28] <zedas>    but, even with a solid timeout it still pegs the CPU 100% with EINTR when a handler dies
| [Saturday 21 August 2010] [03:37:36] <zedas>    and, killing the handler makes it go back to normal
| [Saturday 21 August 2010] [03:37:41] <zedas>    so, more digging.
| [Saturday 21 August 2010] [03:39:53] <jsimmons> so you can produce that bug reliably now zedas?
| [Saturday 21 August 2010] [03:40:04] <zedas>    yep, all the time.
| [Saturday 21 August 2010] [03:40:22] <zedas>    i just hit handles with 0mq messages, wait a bit, 100% cpu.  kill the dead handler, 0%
| [Saturday 21 August 2010] [03:40:44] <zedas>    it also pulls out another but so i'll just go fix that for now, this is kind of wearing me down.
| [Saturday 21 August 2010] [04:12:23] <sustrik>  zedas: hm, would returning EINTR from zmq_poll instead of looping help?
| [Saturday 21 August 2010] [04:13:04] <sustrik>  however, if you handle the EINTR by simply calling zmq_poll again, it'll behave exactly as it does now
| [Saturday 21 August 2010] [04:15:10] <sustrik>  btw, what's "the handler"
| [Saturday 21 August 2010] [04:15:13] <sustrik>  signal handler?
| [Saturday 21 August 2010] [04:15:38] <sustrik>  or the network peer?
| [Saturday 21 August 2010] [05:45:26] <jsimmons> he was talking about a handler in mongrel2 sustrik, which is just an entity that receives and sends zmq messages to/from the mongrel2 server. He's also gone to bed.
| [Saturday 21 August 2010] [07:32:52] <pieterh>  sustrik: hi
| [Saturday 21 August 2010] [07:33:11] <pieterh>  random question, I'm writing a relay example (step1->step2->step3)
| [Saturday 21 August 2010] [07:33:21] <pieterh>  to demonstrate inter-thread signalling
| [Saturday 21 August 2010] [07:46:48] <CIA-20>   zeromq2: 03Pieter Hintjens 07master * rc52d1f2 10/ doc/zmq_recv.txt : Fixed example for multipart zmq_recv() - http://bit.ly/a3r6KT
| [Saturday 21 August 2010] [07:52:47] <pieterh>  Hah... do NOT use 'socket' in example code
| [Saturday 21 August 2010] [07:52:59] <pieterh>  it compiles even if you don't define a variable called 'socket'
| [Saturday 21 August 2010] [09:47:42] <CIA-20>   zeromq2: 03Pieter Hintjens 07master * r2b2accb 10/ doc/zmq_recv.txt : Added calls to zmq_msg_close in examples - http://bit.ly/bWEUgx
| [Saturday 21 August 2010] [13:43:22] <sustrik>  jsimmons: thanks
| [Saturday 21 August 2010] [13:43:40] <kshah>    I've used homebrew to install zeromq, but I can not get the rubygem (not the ffi one) to build even when I specify the zmq-dir
| [Saturday 21 August 2010] [13:44:07] <kshah>    I've had this issue for a while, and I can't seem to hack at the extconf.rb file provided in the gem either to solve the problem
| [Saturday 21 August 2010] [13:44:29] <sustrik>  kshah: what's the problem?
| [Saturday 21 August 2010] [13:45:48] <kshah>    sustrik: when I provide the --with-zmq-dir option on "sudo gem install zmq" it can't find the necessary libraries
| [Saturday 21 August 2010] [13:45:56] <kshah>    and prints back "extconf.rb:25: Couldn't find zmq library. try setting --with-zmq-dir=<path> to tell me where it is. (RuntimeError)"
| [Saturday 21 August 2010] [13:46:31] <sustrik>  what's the OS?
| [Saturday 21 August 2010] [13:46:47] <kshah>    OSX 10.6
| [Saturday 21 August 2010] [13:46:59] <sustrik>  maybe a problem with .so vs. .dylib?
| [Saturday 21 August 2010] [13:47:43] <kshah>    sustrik: not sure, are you familiar with homebrew btw?
| [Saturday 21 August 2010] [13:48:03] <sustrik>  i haven't slightest idea what is it :)
| [Saturday 21 August 2010] [13:48:08] <kshah>    it's quickly replacing macports as the package manager of choice for OSX... I think it's formula, however, for installing zeromq is not compatible
| [Saturday 21 August 2010] [13:48:19] <sustrik>  but OSX seems to be a bit tricky
| [Saturday 21 August 2010] [13:48:45] <sustrik>  because the dynamic libraries tend to be named something.dylib
| [Saturday 21 August 2010] [13:48:58] <sustrik>  as opposed to .so on Linux
| [Saturday 21 August 2010] [13:49:17] <kshah>    this may mean something to you: http://github.com/mxcl/homebrew/blob/master/Library/Formula/zeromq.rb
| [Saturday 21 August 2010] [13:49:57] <sustrik>  no, sorry
| [Saturday 21 August 2010] [13:50:18] <kshah>    I've been using dynamic languages for most of my life/career, so .dylib and .so stuff is usually over my head :/
| [Saturday 21 August 2010] [13:50:28] <sustrik>  can you check thefilename of your zmq library?
| [Saturday 21 August 2010] [13:50:42] <kshah>    yes, I'll print the tree in a pastebin
| [Saturday 21 August 2010] [13:52:00] <kshah>    http://gist.github.com/542632
| [Saturday 21 August 2010] [13:52:12] <kshah>    that is in /usr/local/Cellar/zeromq/2.0.7/
| [Saturday 21 August 2010] [13:52:16] <sustrik>  libzmq.dylib
| [Saturday 21 August 2010] [13:52:38] <sustrik>  so i would say, your extconf.rb is checking for libzmq.so
| [Saturday 21 August 2010] [13:52:49] <sustrik>  and doesn't find it because there's no such file
| [Saturday 21 August 2010] [13:52:57] <sustrik>  instead there's libzmq.dylib :|
| [Saturday 21 August 2010] [13:53:08] <sustrik>  no idea how's that solved in ruby world
| [Saturday 21 August 2010] [13:53:56] <kshah>    well, the extconf.rb is using the mkmf library, I'll read up on that
| [Saturday 21 August 2010] [13:54:06] <sustrik>  ok
| [Saturday 21 August 2010] [13:54:07] <kshah>    I don't suppose I can pass a flag to specify the location of that lib
| [Saturday 21 August 2010] [13:54:30] <sustrik>  i assume the location is ok
| [Saturday 21 August 2010] [13:54:39] <sustrik>  the problem is that filename is different on OSX
| [Saturday 21 August 2010] [13:57:12] <sustrik>  you may also check the other ruby binding, maybe the problem is solved there is some way
| [Saturday 21 August 2010] [13:57:23] <kshah>    that homebrew formula is straight up pulling the source and running ./configure --disable-dependency-tracking and make install on it, that portion isn't ruby, even though homebrew itself is written in ruby
| [Saturday 21 August 2010] [13:58:08] <kshah>    oh, but you're saying the compiler on OSX creates the library with a different extension
| [Saturday 21 August 2010] [13:58:21] <zedas>    sustrik: i think returning EINTR might be the next step, but i have to try a few other things first.
| [Saturday 21 August 2010] [13:59:16] <sustrik>  zedas: so it's SIGPIPE caused by the peer failing, right?
| [Saturday 21 August 2010] [14:00:03] <sustrik>  kshah: yes
| [Saturday 21 August 2010] [14:00:44] <sustrik>  it's kind of weird but that seems to be the OSX way
| [Saturday 21 August 2010] [14:01:31] <zedas>    sustrik: nope, i've got no idea why poll thinks it should return EINTR
| [Saturday 21 August 2010] [14:02:04] <sustrik>  bleh
| [Saturday 21 August 2010] [14:02:44] <sustrik>  anyway, maybe it's not in general a good idea not to return on signals
| [Saturday 21 August 2010] [14:02:53] <zedas>    sustrik: and i'm pretty sure that even *if* there was a signal, poll isn't supposed to flail about because of it.  it should report EINTR once and then move on.
| [Saturday 21 August 2010] [14:03:16] <sustrik>  yeah, we were trying yo be too smart
| [Saturday 21 August 2010] [14:04:06] <sustrik>  it won't work well with users explicitly sending signals and reafing them via sigwait
| [Saturday 21 August 2010] [14:04:28] <sustrik>  they would just get stuck in an infinite loop
| [Saturday 21 August 2010] [14:04:57] <sustrik>  mato: are you here? you may have an opinion on this
| [Saturday 21 August 2010] [14:09:28] <kshah>    sustrik: would this mean it did find the library but couldnt' find a necessary function? "checking for zmq_init() in -lzmq... no"
| [Saturday 21 August 2010] [14:10:32] <sustrik>  yes, possibly
| [Saturday 21 August 2010] [14:10:46] <sustrik>  but my guess is that it's the extension problem
| [Saturday 21 August 2010] [14:20:58] <kshah>    sustrik: the ffi ruby library built with no problems at all
| [Saturday 21 August 2010] [14:21:12] <kshah>    minus the missing gem dependency on ffi, but thats just updating the gemspec
| [Saturday 21 August 2010] [14:23:15] <kshah>    the Oliver Smith video introduction is incredibly helpful
| [Saturday 21 August 2010] [14:25:31] <sustrik>  kshah: so the problem is solved?
| [Saturday 21 August 2010] [14:25:38] <kshah>    the problem is evaded
| [Saturday 21 August 2010] [14:25:44] <kshah>    so no problem! :)
| [Saturday 21 August 2010] [14:26:54] <kshah>    thank you, I forked the ruby-ffi library on GH, I'll build out some docs for the README to get people started
| [Saturday 21 August 2010] [14:34:53] <sustrik>  thanks
| [Saturday 21 August 2010] [14:35:53] <sustrik>  btw, try to push your README changes back to the original library, so that it's not lost
| [Saturday 21 August 2010] [14:36:56] <kshah>    will do
| [Saturday 21 August 2010] [14:38:22] <kshah>    i'm going to make a node services framework with this for managing remote/cloud infrastructure
| [Saturday 21 August 2010] [14:38:42] <kshah>    we have over 100 nodes in EC2 and I can't really effectively message them without clustershell
| [Saturday 21 August 2010] [14:38:46] <kshah>    which is kinda sad
| [Saturday 21 August 2010] [14:39:15] <kshah>    i'm also sure someone has done this before.. but maybe not in ruby
| [Saturday 21 August 2010] [15:18:23] <pieterh>  sustrik: ping
| [Saturday 21 August 2010] [15:20:58] <sustrik>  pieterh: pong
| [Saturday 21 August 2010] [15:21:17] <pieterh>  hi, do you have that whitepaper measuring impact of different frame encoding sizes?
| [Saturday 21 August 2010] [15:21:38] <pieterh>  i'm still lobbying HyBi to use an 8/64 algorithm
| [Saturday 21 August 2010] [15:22:16] <sustrik>  :)
| [Saturday 21 August 2010] [15:22:23] <sustrik>  it used to be on zeromq.org
| [Saturday 21 August 2010] [15:22:25] <sustrik>  let me see
| [Saturday 21 August 2010] [15:23:10] <sustrik>  http://www.zeromq.org/whitepapers:design-v01#toc5
| [Saturday 21 August 2010] [15:23:36] <pieterh>  thanks!
| [Saturday 21 August 2010] [17:29:09] <kshah>    I've got my hello world up with the ruby-ffi library, but I get a *lot* of segmentation faults
| [Saturday 21 August 2010] [17:31:04] <kshah>    http://gist.github.com/542878
| [Saturday 21 August 2010] [17:36:08] <kshah>    instance variables seem to perform better, again I don't use real languages so I don't know very much about memory allocation/management
| [Saturday 21 August 2010] [17:36:16] <kshah>    but I was able to trigger the same behavior
| [Saturday 21 August 2010] [17:57:55] <kshah>    this has got to be some sort of Ruby locking nonsense.. this cant really be tested on the same machine, at least I don't think so
| [Saturday 21 August 2010] [18:01:41] <kshah>    okay, this is FFI and Ruby 1.8.7 related, not at all zeromq related
| [Saturday 21 August 2010] [18:07:44] <cremes>   kshah: i'm the ffi-ruby bindings author; feel free to ping me with questions
| [Saturday 21 August 2010] [18:09:05] <kshah>    cremes: I saw a closed ticket related to issues on 1.8.7, am I correct to say FFI flat out doesn't work well with the 1.8.x branch?
| [Saturday 21 August 2010] [18:10:07] <cremes>   kshah: correct; the 1.8.x branch has terminally broken thread handling
| [Saturday 21 August 2010] [18:10:27] <cremes>   i recommend jruby and then the 1.9 branch (with the updated ffi build for further threading fixes)
| [Saturday 21 August 2010] [18:12:15] <kshah>    that's a many month project for my company (porting to another Ruby VM) but one which we need to get done regardless
| [Saturday 21 August 2010] [18:13:29] <cremes>   kshah: i understand
| [Saturday 21 August 2010] [18:13:47] <cremes>   at this stage it is probably a good idea to at least get on the 1.9.x branch
| [Saturday 21 August 2010] [18:14:03] <cremes>   it *is* faster and the syntax changes are mostly avoidable
| [Saturday 21 August 2010] [18:14:13] <kshah>    thats a community wide effort
| [Saturday 21 August 2010] [18:14:13] <kshah>    http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-talk/367983
| [Saturday 21 August 2010] [18:20:25] <pieterh>  I like those four support levels
| [Saturday 21 August 2010] [18:20:32] <pieterh>  could be nice to adopt that for 0MQ
| [Saturday 21 August 2010] [18:27:20] <cremes>   not a bad idea for 0mq
| [Saturday 21 August 2010] [18:27:30] <cremes>   it helps to set expectations
| [Saturday 21 August 2010] [18:30:06] <pieterh>  cremes: ack
| [Saturday 21 August 2010] [18:33:56] <kshah>    gentlemen I'll be back in a few months after I upgrade our VM, I learned *a lot* today looking at the ffi-rzmq source and reading the docs. The way we do messaging right now sucks and costs us a lot of money. I'm excited for this, thanks
| [Saturday 21 August 2010] [18:34:45] <cremes>   a few months to upgrade the VM? oh boy...
| [Saturday 21 August 2010] [18:34:50] <cremes>   go with god, my son
| [Sunday 22 August 2010] [02:14:54] Notice   -NickServ- travlr_ is not a registered nickname.
| [Sunday 22 August 2010] [02:14:55] CTCP Received Version request from frigg.
| [Sunday 22 August 2010] [06:49:39] <pieter_hintjens>    Have defined a spec for device configuration: http://rfc.zeromq.org/spec:3
| [Sunday 22 August 2010] [08:37:38] 435  travlr_ travlr #gentoo-qt Cannot change nickname while banned on channel
| [Sunday 22 August 2010] [08:38:40] 435  travlr_ travlr #gentoo-kde Cannot change nickname while banned on channel
| [Sunday 22 August 2010] [09:38:35] <pieterh>    if 0MQ added a silent null to the end of zmq_msg_t data, it'd be automatically string safe in C
| [Sunday 22 August 2010] [13:05:50] <theonewolf> hey i have a question about the REQ-REP hello world example, i notice that if i kill the server prematurely, the client blocks indefinitely on zmq_recv, even if i later bring the server back up, is that expected?
| [Sunday 22 August 2010] [15:26:38] <emacsen>    Hi. I"m going to ask a very n00b question here, and I apologize if this is dumb, but in the 0mq model, is there a 1:1 correlation between a socket and a queue?
| [Sunday 22 August 2010] [15:27:03] <emacsen>    queue|channel|message bus
| [Sunday 22 August 2010] [15:33:05] <sustrik>    no, each socket has a queue/buffer per peer
| [Sunday 22 August 2010] [15:33:44] <emacsen>    sustrik, maybe I'm not being clear
| [Sunday 22 August 2010] [15:34:09] <emacsen>    lemme look up the AMQP terminology so I'm less unclear
| [Sunday 22 August 2010] [15:35:37] <emacsen>    okay, the word I want is stores? or exchanges... the thing to which a client subscribes
| [Sunday 22 August 2010] [15:35:54] <emacsen>    I think they call that an exchange
| [Sunday 22 August 2010] [15:36:21] <sustrik>    ah, you mean a central component, that all clients connect to?
| [Sunday 22 August 2010] [15:36:48] <emacsen>    so, let me explain what I mean rather than use the word
| [Sunday 22 August 2010] [15:36:51] <sustrik>    ok
| [Sunday 22 August 2010] [15:36:58] <emacsen>    if I send a message, and want it to fan out to multiple clients
| [Sunday 22 August 2010] [15:37:21] <emacsen>    the way I address it in terms of AMQP exchange determines which queues it goes into
| [Sunday 22 August 2010] [15:37:33] <emacsen>    ...I think that's right... it's been a while since I looked at AMQP
| [Sunday 22 August 2010] [15:37:44] <sustrik>    np, use your own words
| [Sunday 22 August 2010] [15:38:08] <emacsen>    but essentially what I want is lots of "addresses" that a client can subscribe to
| [Sunday 22 August 2010] [15:38:15] <emacsen>    and the messages get to the right clients
| [Sunday 22 August 2010] [15:38:39] <emacsen>    but not to ones that the messages don't need to go to. If that makes any sense?
| [Sunday 22 August 2010] [15:38:47] <emacsen>    that is the fanning is selective
| [Sunday 22 August 2010] [15:39:25] <sustrik>    yes, it's called subscriptions
| [Sunday 22 August 2010] [15:39:50] <sustrik>    you are listining to a feed, however, you want only messages that match certain criteria
| [Sunday 22 August 2010] [15:39:55] <emacsen>    right
| [Sunday 22 August 2010] [15:40:00] <sustrik>    ok
| [Sunday 22 August 2010] [15:40:05] <sustrik>    what's the question?
| [Sunday 22 August 2010] [15:40:18] <emacsen>    Does 0mq support that, or is that at the application layer?
| [Sunday 22 August 2010] [15:40:24] <sustrik>    it does
| [Sunday 22 August 2010] [15:40:37] <sustrik>    use PUB socket on the publisher side
| [Sunday 22 August 2010] [15:40:44] <sustrik>    SUB socket on the subscriber side
| [Sunday 22 August 2010] [15:41:02] <emacsen>    okay... I'm not sure I see this in the docs, though I see the word subscriptions :)
| [Sunday 22 August 2010] [15:41:02] <sustrik>    use zmq_setsockopt(ZMQ_SUBSCRIBE, "...");
| [Sunday 22 August 2010] [15:41:11] <sustrik>    to choose which messages to receive
| [Sunday 22 August 2010] [15:41:23] <sustrik>    check the guide
| [Sunday 22 August 2010] [15:41:30] <sustrik>    let me see...
| [Sunday 22 August 2010] [15:42:16] <sustrik>    http://www.zeromq.org/docs:user-guide#toc5
| [Sunday 22 August 2010] [15:42:21] <emacsen>    ah thanks
| [Sunday 22 August 2010] [15:44:08] <emacsen>    okay, but (and this isn't a problem necessarily) the subscription seems fairly static
| [Sunday 22 August 2010] [15:44:22] <emacsen>    that is the AMQP one is both very powerful and complete, yet somehwhat complex
| [Sunday 22 August 2010] [15:44:51] <sustrik>    what do you mean by "static"/
| [Sunday 22 August 2010] [15:44:52] <sustrik>    ?
| [Sunday 22 August 2010] [15:44:57] <emacsen>    the filter is a string
| [Sunday 22 August 2010] [15:45:02] <emacsen>    or looks/acts like a string :)
| [Sunday 22 August 2010] [15:45:08] <sustrik>    can be binary
| [Sunday 22 August 2010] [15:45:21] <emacsen>    so in the zipcode example, I couldn't ask for more than one zipcode
| [Sunday 22 August 2010] [15:45:32] <emacsen>    I couldn't send to more than one, and I couldn't recieve to more than one
| [Sunday 22 August 2010] [15:46:01] <emacsen>    (that's not a terrible thing on its own, I just want to be sure I understand)
| [Sunday 22 August 2010] [15:46:02] <sustrik>    you can subscribe for as much topics as you wish
| [Sunday 22 August 2010] [15:46:10] <emacsen>    is there a practical limit?
| [Sunday 22 August 2010] [15:46:12] <sustrik>    no
| [Sunday 22 August 2010] [15:46:24] <emacsen>    16k subscriptions no problem for one server?
| [Sunday 22 August 2010] [15:46:29] <sustrik>    no
| [Sunday 22 August 2010] [15:46:33] <emacsen>    works for me :)
| [Sunday 22 August 2010] [15:46:36] <sustrik>    :)
| [Sunday 22 August 2010] [15:47:50] <emacsen>    I have a potential use for this. It'll depend on other folks
| [Sunday 22 August 2010] [15:47:56] <sustrik>    great
| [Sunday 22 August 2010] [15:48:36] <emacsen>    thanks for your help
| [Sunday 22 August 2010] [15:49:23] <sustrik>    you are welcome
| [Sunday 22 August 2010] [16:23:43] <benoitc>    hi all
| [Sunday 22 August 2010] [16:24:41] <benoitc>    i get this comilation error on osx 10.6 : http://github.com/zeromq/erlzmq/issues#issue/2 any idea what it could be ?
| [Sunday 22 August 2010] [16:26:00] <sustrik>    benoitc: you are presumably using wrong repo
| [Sunday 22 August 2010] [16:26:20] <sustrik>    erlang binding works only with experimental branch sustrik/zeromq2
| [Sunday 22 August 2010] [16:26:57] <benoitc>    hum 
| [Sunday 22 August 2010] [16:27:17] <benoitc>    at which point it is experimental ?
| [Sunday 22 August 2010] [16:28:36] <sustrik>    sockets can be migrated between OS threads
| [Sunday 22 August 2010] [16:32:31] <benoitc>    using the branch I get "./configure: line 18331: syntax error near unexpected token `GLIB,'
| [Sunday 22 August 2010] [16:32:35] <benoitc>    "
| [Sunday 22 August 2010] [16:33:34] <sustrik>    are you using ./configure --with-pgm?
| [Sunday 22 August 2010] [16:33:40] <benoitc>    yes
| [Sunday 22 August 2010] [16:34:01] <sustrik>    do you have glib installed?
| [Sunday 22 August 2010] [16:34:10] <benoitc>    yup
| [Sunday 22 August 2010] [16:34:29] <sustrik>    then it's some kin of autotools/OSX issue
| [Sunday 22 August 2010] [16:34:40] <sustrik>    sorry, i have no OSX here
| [Sunday 22 August 2010] [16:34:42] <sustrik>    cannot help
| [Sunday 22 August 2010] [16:34:50] <sustrik>    try asking at the mailing list
| [Sunday 22 August 2010] [16:34:50] <benoitc>    mok thanks
| [Sunday 22 August 2010] [16:37:29] <benoitc>    will do thx anyway
| [Sunday 22 August 2010] [17:10:41] <benoitc>    sustrik: pgmm is required for erlang stuff ?
| [Monday 23 August 2010] [00:49:07] <sustrik>    benoitc: no
| [Monday 23 August 2010] [02:21:51] <shekispeaks>    hi
| [Monday 23 August 2010] [02:22:08] <shekispeaks>    I am looking to build a similar MQ as SQS using zeromq
| [Monday 23 August 2010] [02:22:24] <shekispeaks>    are there any example which are asynch message queues
| [Monday 23 August 2010] [02:22:36] <shekispeaks>    and probably also allow persistance
| [Monday 23 August 2010] [02:35:32] <sustrik>    shekispeaks: no persistence in 0mq
| [Monday 23 August 2010] [02:36:02] <shekispeaks>    ya but if I can push into a datastore like SQLite
| [Monday 23 August 2010] [02:36:14] <sustrik>    sure, why not
| [Monday 23 August 2010] [02:36:15] <shekispeaks>    apart from persistence
| [Monday 23 August 2010] [02:36:26] <shekispeaks>    I want to implement ansynchronus MQ
| [Monday 23 August 2010] [02:36:37] <sustrik>    that's what 0mq is
| [Monday 23 August 2010] [02:36:46] <shekispeaks>    so the Queue Program should store the messages till the consumer consumes them
| [Monday 23 August 2010] [02:37:11] <sustrik>    ah, take the queue device and add persistence there
| [Monday 23 August 2010] [02:37:34] <shekispeaks>    any examples which are doing the same
| [Monday 23 August 2010] [02:37:49] <sustrik>    src/queue.cpp
| [Monday 23 August 2010] [02:37:52] <sustrik>    that's the queue
| [Monday 23 August 2010] [02:38:11] <sustrik>    you'll have to plug SQLite there
| [Monday 23 August 2010] [02:50:10] <keffo>  why on earth would you jump to an sql relational database, for persistence of a message-queue
| [Monday 23 August 2010] [02:50:11] <keffo>  ?
| [Monday 23 August 2010] [02:50:39] <shekispeaks>    what else can be the options
| [Monday 23 August 2010] [02:51:18] <keffo>  a file? =)
| [Monday 23 August 2010] [02:51:46] <shekispeaks>    :D ya file 
| [Monday 23 August 2010] [02:52:03] <keffo>  I'd just use lua though
| [Monday 23 August 2010] [02:52:30] <shekispeaks>    i am using python
| [Monday 23 August 2010] [02:53:20] <keffo>  probably not as efficient, but should work nicely
| [Monday 23 August 2010] [02:53:38] <keffo>  it all depends on how long you need to cache stuff, and how much
| [Monday 23 August 2010] [03:19:16] <shekispeaks>    can you point me to some similar examples preferably in python
| [Monday 23 August 2010] [03:35:13] <pieterh>    shekispeaks: i think it's a good idea, but we don't have examples yet
| [Monday 23 August 2010] [03:35:19] <pieterh>    it's one thing i wanted to make for the user guide
| [Monday 23 August 2010] [03:35:27] <pieterh>    it needs two parts
| [Monday 23 August 2010] [03:35:48] <pieterh>    reliable request-reply and then a queue device that sits on disk
| [Monday 23 August 2010] [03:39:24] <keffo>  pieterh, how is the reliable rep/req supposed to work, apart from the queue?
| [Monday 23 August 2010] [03:39:55] <pieterh>    well, you need a queue device in the center that can connect N clients to N services
| [Monday 23 August 2010] [03:40:04] <pieterh>    then you need a reliable way to get messages onto that queue, and off it
| [Monday 23 August 2010] [03:40:22] <pieterh>    you can start by taking apart the queue device itself
| [Monday 23 August 2010] [03:40:35] <pieterh>    and seeing how it connects XREP to XREQ
| [Monday 23 August 2010] [03:41:02] <pieterh>    you basically want to stick a persistent store in between those afaics
| [Monday 23 August 2010] [03:41:36] <pieterh>    so your chain from client to service is REQ--XREP--(queue)--XREQ--REP
| [Monday 23 August 2010] [03:41:53] <pieterh>    then you need to make the REQ--XREP and XREQ--REP parts reliable as well
| [Monday 23 August 2010] [03:42:07] <pieterh>    which also means some persistence (at least in memory) at each node
| [Monday 23 August 2010] [03:42:47] <pieterh>    as sustrik says, src/queue.cpp is the place to start
| [Monday 23 August 2010] [03:43:18] <pieterh>    kind of something i wanted to play with too...
| [Monday 23 August 2010] [03:43:33] <pieterh>    even using simple disk files would be doable IMO
| [Monday 23 August 2010] [03:49:36] <keffo>  metakit sounds perfect
| [Monday 23 August 2010] [09:01:20] Error    No such server: keffo.
| [Monday 23 August 2010] [09:07:37] <panki>  hello
| [Monday 23 August 2010] [09:07:46] <panki>  Martin, are you are here?
| [Monday 23 August 2010] [10:58:55] <cremes> is the current master branch at zeromq/zeromq2 still api compatible with the 2.0.7 release?
| [Monday 23 August 2010] [11:03:07] <cremes> the answer is "no"; zmq_poll has its contents commented out and has left an assertion that always triggers
| [Monday 23 August 2010] [11:03:35] <cremes> anyone know what the last commit was where zmq_poll was supported in master?
| [Monday 23 August 2010] [11:24:19] <cremes> i rolled back to commit 4777fe4010572d381a2ad8eb63df2fc5fb7e6642
| [Monday 23 August 2010] [11:24:41] <cremes> i am seeing a problem where i get the following assertion:   Assertion failed: !engine (session.cpp:287)
| [Monday 23 August 2010] [11:26:01] <cremes> has anyone else seen that?
| [Monday 23 August 2010] [11:26:11] <cremes> a search of the git issues doesn't provide any hits
| [Monday 23 August 2010] [11:30:06] <mato>   cremes: zeromq/zeromq2 master is api compatible with 2.0.7
| [Monday 23 August 2010] [11:30:31] <mato>   cremes: if you're looking at a commented out poll, my guess is you're using sustrik/zeromq2 master 
| [Monday 23 August 2010] [11:30:45] <mato>   cremes: maybe you forgot to switch your url's?
| [Monday 23 August 2010] [11:32:20] <cremes> mato: that's probably it; i'll reclone and try again
| [Monday 23 August 2010] [11:43:41] <cremes> argh... autoconf issues on osx :(
| [Monday 23 August 2010] [11:47:54] <cremes> "sudo port install libtool" fixed the issue
| [Monday 23 August 2010] [12:39:34] <sustrik>    cremes: the comment about building on OSX refers to build from package or build from git?
| [Monday 23 August 2010] [12:40:22] <cremes> from git
| [Monday 23 August 2010] [12:40:37] <cremes> the git sources don't include "configure" so it needs to be generated
| [Monday 23 August 2010] [12:40:43] <cremes> using autoconf & friends
| [Monday 23 August 2010] [12:43:43] <sustrik>    ok, let me see
| [Monday 23 August 2010] [12:44:25] <sustrik>    what about putting the comment here: http://www.zeromq.org/docs:procedures
| [Monday 23 August 2010] [13:00:58] <cremes> sustrik: sure, i'll move it there
| [Monday 23 August 2010] [13:03:21] <sustrik>    ok
| [Monday 23 August 2010] [13:06:32] <cremes> done
| [Monday 23 August 2010] [13:07:48] <sustrik>    thx
| [Monday 23 August 2010] [22:00:05] <zedas>  sustrik: so i'm back on the trail of that bug with the 100% cpu in mongrel2.
| [Monday 23 August 2010] [22:00:24] <zedas>  sustrik: so far, the EINTR in the zmq_poll is actually coming from one of the io threads.  it's not a real signal.
| [Monday 23 August 2010] [22:01:15] <emacsen>    I suspect sustrik is asleep :)
| [Monday 23 August 2010] [22:01:17] <zedas>  sustrik: also, when it happens, the receiver gets duplicate messages.  i've checked the mongrel2 code i'm only sending the message once.  right after they get the double message, the handler dies and mongrel2 goes 100%
| [Monday 23 August 2010] [22:01:19] <emacsen>    it's quite late there
| [Monday 23 August 2010] [22:01:37] <zedas>  emacsen: ah, well he'll see them when he gets up
| [Tuesday 24 August 2010] [00:49:27] <shekispeaks>   hi 
| [Tuesday 24 August 2010] [00:49:28] <shekispeaks>   an
| [Tuesday 24 August 2010] [00:49:38] <shekispeaks>   any examples around using zmq_queue in python
| [Tuesday 24 August 2010] [01:19:21] <sustrik>   zedas: morning
| [Tuesday 24 August 2010] [01:19:27] <sustrik>   you still there?
| [Tuesday 24 August 2010] [01:20:20] <sustrik>   shekispeaks: it's an executable, it is used the same in all languages
| [Tuesday 24 August 2010] [01:21:23] <zedas> sustrik: yep
| [Tuesday 24 August 2010] [01:21:38] <zedas> sustrik: so i've been running tests thrashing with IO threads set to 1 and no problems.
| [Tuesday 24 August 2010] [01:22:09] <zedas> definitely a problem with multiple IO threads, duplicate message gets sent, and then EINTR in zmq_poll and the receiving handler stalls.
| [Tuesday 24 August 2010] [01:22:52] <sustrik>   ok, do you have a test program?
| [Tuesday 24 August 2010] [01:23:24] <zedas> i'll work something up.  right now the test program is thrashing the hell out of mongrel2
| [Tuesday 24 August 2010] [01:23:30] <zedas> with threads > 1 it locks immediately
| [Tuesday 24 August 2010] [01:23:35] <zedas> so i should be able to reproduce
| [Tuesday 24 August 2010] [01:23:43] <sustrik>   ok
| [Tuesday 24 August 2010] [02:12:17] <shekispeaks>   what is the python binding for zmq-device 
| [Tuesday 24 August 2010] [02:13:32] <sustrik>   zmq_device is an executable
| [Tuesday 24 August 2010] [02:14:06] <sustrik>   you can launch it from the command line
| [Tuesday 24 August 2010] [02:14:39] <sustrik>   oops
| [Tuesday 24 August 2010] [02:14:58] <sustrik>   sorry, i thought you meant zmq_queue
| [Tuesday 24 August 2010] [02:15:17] <sustrik>   as for python binding for zmq_deivce, i don't know, sorry
| [Tuesday 24 August 2010] [02:17:04] <shekispeaks>   the documentation is lacking for the bindings
| [Tuesday 24 August 2010] [02:17:11] <shekispeaks>   :)
| [Tuesday 24 August 2010] [02:18:05] <sustrik>   maybe it's not there
| [Tuesday 24 August 2010] [02:18:12] <sustrik>   you can provide a patch then
| [Tuesday 24 August 2010] [02:39:40] <xrfang>    hi, I get this error: Failed to send message: Operation cannot be accomplished in current state, the program must receive the reply from server before it can send second message, why?
| [Tuesday 24 August 2010] [02:45:18] <zedas> xrfang: different types of sockets have different usage pattersn.  A REQ has to send, then receive, but a REP socket receives then sends.  PUB can only send, SUB can only receive. and so on.
| [Tuesday 24 August 2010] [02:45:29] <zedas> xrfang: you probably tried to do something that the socket type didn't support.
| [Tuesday 24 August 2010] [02:50:48] <travlr>    zedas: just got done reading mongrol2.org. i'll like what you've done with the concept, source as well as the docs.
| [Tuesday 24 August 2010] [02:51:26] <travlr>    *mongrel2.org
| [Tuesday 24 August 2010] [03:04:11] <zedas> travlr: cool glad you like it. shooting for a minimalist 1.0 aug 31 and looks like we might do it
| [Tuesday 24 August 2010] [03:04:54] <travlr>    i'm looking forward to using it..
| [Tuesday 24 August 2010] [03:39:39] <CIA-20>    zeromq2: 03Martin Sustrik 07wip-shutdown * r2a52455 10/ src/session.cpp : sessions created by listerner are correctly shut down - http://bit.ly/aZSPJY
| [Tuesday 24 August 2010] [03:57:31] <CIA-20>    zeromq2: 03Martin Sustrik 07wip-shutdown * r2022dbd 10/ (src/zmq_engine.cpp src/zmq_listener.cpp src/zmq_listener.hpp): listener object unregisters its fd correctly - http://bit.ly/dzDxI0
| [Tuesday 24 August 2010] [04:08:37] <rbraley>   zedas, say, where in your code is your coroutine implementation? Do you have an M:N threading model?
| [Tuesday 24 August 2010] [04:11:19] <rbraley>   hehe, libtask eh? I thought there might be something to do with plan9 in there. Is this derived from libthread?
| [Tuesday 24 August 2010] [04:12:02] <zedas> rbraley: not sure, i know russ cox wrote it years ago but probably just inspired by various other coroutine libs
| [Tuesday 24 August 2010] [04:12:58] <zedas> rbraley: i also don't do N:M threads explicitly.  they're pretty hard to coordinate, so instead i just have a fast as hell I/O coroutine processing in the main thread, then 0mq gives me threading on the IO it works with.
| [Tuesday 24 August 2010] [04:13:18] <zedas> next up is to let you load handlers that are inproc and taken from .so files, so you can offload work into threads safely
| [Tuesday 24 August 2010] [04:14:25] <rbraley>   zedas, I was thinking about sending coroutines over zeromq to different threads with fair queuing. That way M:N is easier.
| [Tuesday 24 August 2010] [04:14:44] <rbraley>   The trick is getting coroutines to serialize
| [Tuesday 24 August 2010] [04:15:51] <zedas> oh good luck with that! :-)
| [Tuesday 24 August 2010] [04:16:08] <zedas> you do know that *Lua* can do that though right?
| [Tuesday 24 August 2010] [04:16:58] <zedas> you can have a Lua vm start a bit of code, have the code yield in a coroutine, then back in C land pull that coroutine out and make it into a new VM, then send that whole kit over to a separate thread and let it continue there
| [Tuesday 24 August 2010] [04:17:17] <rbraley>   I suppose Lua is worth a try. I wish it's syntax was more like python but at least it doesn't have the GIL
| [Tuesday 24 August 2010] [04:17:51] <zedas> yep, lua is very threadsafe, as long as you don't share vms between threads you can go fairly crazy with it.
| [Tuesday 24 August 2010] [04:18:04] <zedas> and since it's so easy to spawn off new vms you just don't have a problem.
| [Tuesday 24 August 2010] [04:18:23] <zedas> but, as for getting something like libtask to swap around between threads, it'd be a trick and a half.
| [Tuesday 24 August 2010] [04:18:40] <zedas> i'm sure you could make it work, but coordinating the shuffle will be very error prone.
| [Tuesday 24 August 2010] [04:19:18] <rbraley>   zedas, yeah I was looking at the Go code to see if I could gain anything. I found the G struct and it is pretty nifty
| [Tuesday 24 August 2010] [04:19:46] <rbraley>   http://code.google.com/p/go/source/browse/src/pkg/runtime/runtime.h
| [Tuesday 24 August 2010] [04:21:11] <CIA-20>    zeromq2: 03Martin Sustrik 07wip-shutdown * rc573c5c 10/ (src/zmq_connecter.cpp src/zmq_connecter.hpp): connecter object unregisters its fd correctly - http://bit.ly/cnKJLS
| [Tuesday 24 August 2010] [04:21:13] <zedas> uh why is Go not written in Go?
| [Tuesday 24 August 2010] [04:21:44] <rbraley>   apparently they have Goroutines move to a different or new system thread if one of them blocks on a system call so they don't have to wait :D
| [Tuesday 24 August 2010] [04:22:10] <zedas> sigh.  i need to write my book on C.
| [Tuesday 24 August 2010] [04:22:19] <zedas> i mean yeah, the guy who wrote C works on this code.
| [Tuesday 24 August 2010] [04:22:20] <rbraley>   zedas, do tell
| [Tuesday 24 August 2010] [04:22:42] <zedas> but you think he'd stop naming shit M, G, cret, tls
| [Tuesday 24 August 2010] [04:22:52] <rbraley>   hehe
| [Tuesday 24 August 2010] [04:23:16] <zedas> i mean are they missing fingers or something?
| [Tuesday 24 August 2010] [04:23:57] <rbraley>   I kinda like the laconic naming conventions
| [Tuesday 24 August 2010] [04:24:13] <rbraley>   as long as there are adequate comments
| [Tuesday 24 August 2010] [04:24:35] <zedas> nah, it's why people think C is hard. i mean, if the experts write it this way, obviously you can't write it clean and readably
| [Tuesday 24 August 2010] [04:25:22] <zedas> and then weird things like trying to use tabs to line stuff up, but then naming variables and functions so nobody can read them.
| [Tuesday 24 August 2010] [04:25:41] <rbraley>   zedas, if you think this code is bad try the Erlang source! 
| [Tuesday 24 August 2010] [04:25:42] <zedas> oh well, i'm sure if google's using it everyone will pick it up.
| [Tuesday 24 August 2010] [04:26:07] <zedas> oh i know, i've looked at it.
| [Tuesday 24 August 2010] [04:26:11] <rbraley>   http://github.com/mfoemmel/erlang-otp/blob/master/erts/emulator/beam/erl_process.c
| [Tuesday 24 August 2010] [04:26:14] <rbraley>   yuk
| [Tuesday 24 August 2010] [04:26:22] <zedas> it's like the inverse of javascript.
| [Tuesday 24 August 2010] [04:26:54] <zedas> when good programmers code javascript their sense of style gets turned off and they crank out unreadable barely working crap.
| [Tuesday 24 August 2010] [04:27:26] <zedas> with C, their sense of style turns off and they write unreadable very magic crap.
| [Tuesday 24 August 2010] [04:27:42] <rbraley>   I wonder how big a Lua vm is? I wonder if I can spawn a bunch of em or if it is just too heavy.
| [Tuesday 24 August 2010] [04:27:55] <rbraley>   zedas, haha
| [Tuesday 24 August 2010] [04:28:34] <zedas> lua's C code is pretty good last time i read it.
| [Tuesday 24 August 2010] [04:29:04] <zedas> yep good old erlang. 9000+ lines of ifdef convolution
| [Tuesday 24 August 2010] [04:29:23] <rbraley>   I'm making a game engine where every entity is an actor (as in actor model of concurrency) which communicate by message passing with 0MQ.
| [Tuesday 24 August 2010] [04:29:39] <rbraley>   I want an M:N threading model for optimal use of the hardware
| [Tuesday 24 August 2010] [04:30:01] <rbraley>   it seems like you are after a similar architecture with mongrel2
| [Tuesday 24 August 2010] [04:31:17] <travlr>    rbraley: btw -- another tidbit for your topical-vid viewing pleasure: http://www.ted.com/talks/tan_le_a_headset_that_reads_your_brainwaves.html
| [Tuesday 24 August 2010] [04:31:19] <keffo> rbraley, lua is very performant
| [Tuesday 24 August 2010] [04:32:35] <zedas> rbraley: you want lua
| [Tuesday 24 August 2010] [04:32:44] <zedas> especially if you're doing a game.
| [Tuesday 24 August 2010] [04:33:08] <rbraley>   for those that don't know I have done some work on a Brain/Machine interface, that's why that's a topical vid
| [Tuesday 24 August 2010] [04:34:25] <rbraley>   alright, I'll see if I can make a bunch of lua + zeromq actor coroutines and see how much memory they take up
| [Tuesday 24 August 2010] [04:34:42] <keffo> a coroutine is just a stack + ip
| [Tuesday 24 August 2010] [04:35:04] <rbraley>   well in this case it would also be a Lua vm :P
| [Tuesday 24 August 2010] [04:38:49] <keffo> it mostly depends on what the vm does, starting it is very fast, loading libraries usually isnt
| [Tuesday 24 August 2010] [04:40:38] <rbraley>   travlr, yeah, a dude at my hackerspace has a neural headset like that.
| [Tuesday 24 August 2010] [04:41:57] <rbraley>   keffo, most actors will be just running functions and sending messages, the libraries will be loaded in the components which the entities will talk to.
| [Tuesday 24 August 2010] [04:42:19] <keffo> then I would just do all of them as normal coroutines in one vm
| [Tuesday 24 August 2010] [04:43:08] <rbraley>   oh right :P that is smarter.
| [Tuesday 24 August 2010] [04:43:18] <keffo> starting a vm from scratch and loading all the standard libs will take time (and ram obviously), but starting a coroutine is near instant
| [Tuesday 24 August 2010] [04:44:14] <keffo> your cant use any blocking calls though :)
| [Tuesday 24 August 2010] [04:44:17] <rbraley>   travlr, actually that's the exact same neural headset that he has. Same software and everything.
| [Tuesday 24 August 2010] [04:44:41] <travlr>    yeah its cool chit
| [Tuesday 24 August 2010] [04:44:42] <rbraley>   keffo, well, I can spawn another thread if I have to make a blocking call
| [Tuesday 24 August 2010] [04:45:22] <keffo> rbraley, why bother? Just dont block and be done with it :)
| [Tuesday 24 August 2010] [04:46:26] <keffo> unless you're aiming for linear gain in performance, spawning another thread is just a lazy way to not block..
| [Tuesday 24 August 2010] [04:47:04] <rbraley>   ;)
| [Tuesday 24 August 2010] [04:47:41] <rbraley>   I don't want any blocking calls between frames ;)
| [Tuesday 24 August 2010] [04:48:21] <keffo> then dont impose such a design :)
| [Tuesday 24 August 2010] [04:49:41] <rbraley>   I wouldn't dream of it :D
| [Tuesday 24 August 2010] [04:54:24] <jsimmons>  Lua is pretty light on memory, rbraley. ~300k with the whole shebang.
| [Tuesday 24 August 2010] [04:54:35] <rbraley>   nice!
| [Tuesday 24 August 2010] [04:54:36] <jsimmons>  you can cut it down really easily too
| [Tuesday 24 August 2010] [04:55:48] <jsimmons>  I have it down to 200k here just stripping out libraries and compiling for size.
| [Tuesday 24 August 2010] [04:55:58] <jsimmons>  but you most likely don't want to do that
| [Tuesday 24 August 2010] [04:58:55] <rbraley>   it'd be neat if Lua had pattern matching like Scala or Erlang
| [Tuesday 24 August 2010] [04:59:02] <rbraley>   or Haskell for that matter
| [Tuesday 24 August 2010] [04:59:06] <jsimmons>  lua has pro pattern matching
| [Tuesday 24 August 2010] [04:59:12] <rbraley>   really?
| [Tuesday 24 August 2010] [04:59:30] <jsimmons>  well, if by pro you mean really light, fast and covers most real use-cases.
| [Tuesday 24 August 2010] [04:59:43] <jsimmons>  and there's lpeg if you need more.
| [Tuesday 24 August 2010] [05:01:53] <jsimmons>  oh and if you need more performance, you can drop in LuaJIT 2 and get ~ the same speeds as the Java 6 vm
| [Tuesday 24 August 2010] [05:02:01] <rbraley>   interesting
| [Tuesday 24 August 2010] [05:03:38] <jsimmons>  it's a pretty cool platform, and for it's minimalism it's often used in the game/other embedded world.
| [Tuesday 24 August 2010] [05:03:44] <keffo> jsimmons, 200kb?
| [Tuesday 24 August 2010] [05:03:56] <keffo> on what platform?
| [Tuesday 24 August 2010] [05:04:09] <jsimmons>  yeah keffo linux, that's the .a, though.
| [Tuesday 24 August 2010] [05:04:48] <keffo> oh
| [Tuesday 24 August 2010] [05:06:14] <keffo> furthest I've come is a 17.8kb executable(win32), and printing hello world in a loop sits the process at around 568kb .. Could probably squeeze out more though, but not without a lot of fuzz
| [Tuesday 24 August 2010] [05:08:09] <rbraley>   woohoo it's a register-based VM
| [Tuesday 24 August 2010] [05:08:59] <rbraley>   meaning string manipulation won't take 3-4 instructions per character
| [Tuesday 24 August 2010] [05:09:42] <jsimmons>  the string manipulation is generally done in C anyway
| [Tuesday 24 August 2010] [05:10:17] <keffo> and the lua string hash algo is very fast
| [Tuesday 24 August 2010] [05:13:08] <jsimmons>  and the c api is pretty fantastic
| [Tuesday 24 August 2010] [05:14:29] <keffo> as long as you grasp the stack stuff properly, the language wont matter :)
| [Tuesday 24 August 2010] [05:15:14] <rbraley>   I like what I see. It may not be as pretty as python, but I already like two lua syntax decisions better than python ^ instead of ** and not needing to put self everywhere.
| [Tuesday 24 August 2010] [05:16:16] <keffo> you'll use self soon enough in lua too
| [Tuesday 24 August 2010] [05:19:41] <CIA-20>    zeromq2: 03Martin Sustrik 07wip-shutdown * rbdc4adc 10/ (6 files): elementary fixes to the named session - http://bit.ly/9GVADQ
| [Tuesday 24 August 2010] [07:39:23] <shekispeaks>   i am using the req/rep paradigm
| [Tuesday 24 August 2010] [07:39:38] <shekispeaks>   it is a basic server client architecture
| [Tuesday 24 August 2010] [07:40:06] <shekispeaks>   i know the requests are queued at the Server
| [Tuesday 24 August 2010] [07:40:40] <shekispeaks>   any idea how long are the messages queued. Can I break the processing into a seperate queue
| [Tuesday 24 August 2010] [09:59:26] <CIA-20>    zeromq2: 03Martin Sustrik 07wip-shutdown * r713fbdd 10/ (3 files in 2 dirs): MSVC build fixed - http://bit.ly/9supt0
| [Tuesday 24 August 2010] [10:29:17] <mato>  sustrik: what does lb_t::active (number of active pipes) actually mean?
| [Tuesday 24 August 2010] [10:29:34] <mato>  sustrik: i.e. what is an "active pipe"?
| [Tuesday 24 August 2010] [10:29:46] <sustrik>   number of outbound pipes able to accept a message
| [Tuesday 24 August 2010] [10:30:00] <sustrik>   "high watermark is not yet reached"
| [Tuesday 24 August 2010] [10:30:02] <mato>  able, i.e. not full
| [Tuesday 24 August 2010] [10:30:10] <sustrik>   yes
| [Tuesday 24 August 2010] [10:31:12] <mato>  sustrik: so, you see, we had the "xreq drops messages" behaviour in the core for a while
| [Tuesday 24 August 2010] [10:31:30] <mato>  sustrik: you may remember a thread where i took that out
| [Tuesday 24 August 2010] [10:31:38] <sustrik>   yes
| [Tuesday 24 August 2010] [10:32:00] <mato>  sustrik: now, i think that what i actually want is for xreq to drop message if and only if there are no pipes at all
| [Tuesday 24 August 2010] [10:32:17] <mato>  sustrik: if they're all full, then it must block since otherwise HWM would be useless
| [Tuesday 24 August 2010] [10:32:18] <sustrik>   or if all the pipes are full
| [Tuesday 24 August 2010] [10:32:21] <mato>  no
| [Tuesday 24 August 2010] [10:32:31] <sustrik>   HWM limits the memory used
| [Tuesday 24 August 2010] [10:32:37] <sustrik>   that's it single purpose
| [Tuesday 24 August 2010] [10:33:19] <mato>  huh? it limits the queue length
| [Tuesday 24 August 2010] [10:33:29] <sustrik>   yes
| [Tuesday 24 August 2010] [10:33:39] <sustrik>   so it's not useless
| [Tuesday 24 August 2010] [10:33:45] <sustrik>   it limits the queue length
| [Tuesday 24 August 2010] [10:34:21] <sustrik>   think of HWM as SO_SNDBUF
| [Tuesday 24 August 2010] [10:34:52] <mato>  but SO_SNDBUF being full blocks your socket
| [Tuesday 24 August 2010] [10:35:30] <mato>  which is what i want, short queues on one end which block if they are full
| [Tuesday 24 August 2010] [10:35:37] <mato>  my problem is the case where there is "no queue"
| [Tuesday 24 August 2010] [10:36:11] <sustrik>   what you are doing is a hack, so do as you please
| [Tuesday 24 August 2010] [10:37:39] <mato>  yes, but i'm trying to understand the problem at the same time
| [Tuesday 24 August 2010] [10:38:04] <sustrik>   ok, in that case the message should be dropped in pipes are full
| [Tuesday 24 August 2010] [10:38:17] <sustrik>   this would make it behave as expected in devices
| [Tuesday 24 August 2010] [10:38:58] <sustrik>   i.e. "never block the execution"
| [Tuesday 24 August 2010] [10:39:56] <mato>  ok, and in the hypothetical case of a req/rep with resend, who's job would it then be to resend the request?
| [Tuesday 24 August 2010] [10:40:01] <mato>  the original requester's ?
| [Tuesday 24 August 2010] [10:40:04] <sustrik>   yes
| [Tuesday 24 August 2010] [10:40:10] <sustrik>   end-to-end reliability
| [Tuesday 24 August 2010] [10:40:12] <sustrik>   same as TCP
| [Tuesday 24 August 2010] [16:06:22] <TPL>   my first time in 0mq chat
| [Tuesday 24 August 2010] [16:06:24] <TPL>   anyone here?
| [Tuesday 24 August 2010] [16:10:16] <travlr>    hi tpl.. welcome.. whats up?
| [Tuesday 24 August 2010] [16:34:12] <TPL>   earlier i was investigating a problem using 0mq with visual studio 2008 in debug mode
| [Tuesday 24 August 2010] [16:34:14] <TPL>   BUT
| [Tuesday 24 August 2010] [16:34:18] <TPL>   i've now worked it out
| [Tuesday 24 August 2010] [16:34:34] <TPL>   this is my first time to 0mq chatroom
| [Tuesday 24 August 2010] [16:34:42] <TPL>   is this a good place to work these kind of problems out?
| [Tuesday 24 August 2010] [16:34:52] <travlr>    cool. glad you got it worked out
| [Tuesday 24 August 2010] [16:34:57] <TPL>   thanks
| [Tuesday 24 August 2010] [16:35:04] <TPL>   actually helping a colleague
| [Tuesday 24 August 2010] [16:35:07] <travlr>    yeah.. here and on the mail list to ask for help
| [Tuesday 24 August 2010] [16:35:09] <TPL>   i wasn't directly working on it
| [Tuesday 24 August 2010] [16:37:35] <TPL>   do you use 0mq under windows with visual studio 2008?
| [Tuesday 24 August 2010] [16:37:46] <travlr>    no i don't.. sorry
| [Tuesday 24 August 2010] [16:38:35] <TPL>   where should i go for windows knowledge related to 0mq?
| [Tuesday 24 August 2010] [16:39:10] <travlr>    on the website, mail list, or here
| [Tuesday 24 August 2010] [16:39:24] <TPL>   then i guess i'm in
| [Tuesday 24 August 2010] [16:39:37] <TPL>   thanks for taking time to answer my questions
| [Tuesday 24 August 2010] [16:39:41] <travlr>    sure
| [Tuesday 24 August 2010] [17:15:24] <ModusPwnens>   Hi, I'm trying to get a basic public subscribe server/client setup
| [Tuesday 24 August 2010] [17:15:34] <ModusPwnens>   published*
| [Tuesday 24 August 2010] [17:16:57] <ModusPwnens>   I read the documentation, but I wasn't sure about the endpoint parameter for the bind function
| [Tuesday 24 August 2010] [18:37:35] <ModusPwnens>   hello?
| [Wednesday 25 August 2010] [03:35:01] <mato>    pieterh: you at eea?
| [Wednesday 25 August 2010] [03:40:06] <pieterh> mato: re
| [Wednesday 25 August 2010] [03:40:23] <pieterh> mato: i'm not there, eta around 10.30
| [Wednesday 25 August 2010] [03:40:26] <pieterh> that ok?
| [Wednesday 25 August 2010] [03:42:09] <mato>    fine with me
| [Wednesday 25 August 2010] [03:42:16] <mato>    sustrik: 10:30 then...
| [Wednesday 25 August 2010] [03:42:37] <sustrik> ok
| [Wednesday 25 August 2010] [03:44:56] <mato>    pieterh: your -EFAULT changes to zmq_stopwatch_stop do not build on Solaris, I'll take them our for that function since it's not really part of the core API
| [Wednesday 25 August 2010] [03:51:22] <CIA-20>  zeromq2: 03Martin Lucina 07master * rb66dd7a 10/ src/zmq.cpp : 
| [Wednesday 25 August 2010] [03:51:22] <CIA-20>  zeromq2: zmq_stopwatch_stop: Don't return EFAULT
| [Wednesday 25 August 2010] [03:51:22] <CIA-20>  zeromq2: Function returning unsigned long int cannot return (-1) - http://bit.ly/du23tY
| [Wednesday 25 August 2010] [03:55:39] <sustrik> mato: a question
| [Wednesday 25 August 2010] [03:55:55] <sustrik> EINTR thing
| [Wednesday 25 August 2010] [03:56:09] <sustrik> is it a good idea we hide it?
| [Wednesday 25 August 2010] [03:56:24] <sustrik> what if the app sends signals
| [Wednesday 25 August 2010] [03:56:41] <sustrik> and processes them using sigwait
| [Wednesday 25 August 2010] [03:57:08] <sustrik> we'll end up ewith infinite loop, no?
| [Wednesday 25 August 2010] [03:59:27] <mato>    sustrik: no, if the app is doing "best practice" signal handling with a thread using a sigwait loop then our not return EINTR has no effect on that...
| [Wednesday 25 August 2010] [03:59:52] <mato>    sustrik: unless something is very broken, which is of course possible with signal handling in general
| [Wednesday 25 August 2010] [04:00:20] <mato>    sustrik: anyhow, the point is, zmq only ever changes the signal mask in its own I/O threads
| [Wednesday 25 August 2010] [04:00:27] <mato>    sustrik: and never in the application threads
| [Wednesday 25 August 2010] [04:01:00] <sustrik> exactly
| [Wednesday 25 August 2010] [04:01:05] <mato>    sustrik: if you're asking, should 0mq calls be interruptible (and return EINTR) then that is of course a different question, but we'd agreed that the answer is no
| [Wednesday 25 August 2010] [04:01:58] <sustrik> so basically no signal should ever occur in the thread that's using 0mq socket
| [Wednesday 25 August 2010] [04:01:59] <sustrik> right?
| [Wednesday 25 August 2010] [04:02:04] <mato>    no
| [Wednesday 25 August 2010] [04:02:25] <mato>    no signals should ever be delivered to the 0mq I/O threads
| [Wednesday 25 August 2010] [04:02:32] <sustrik> sure
| [Wednesday 25 August 2010] [04:02:33] <mato>    what happens in the app thread(s) is up to the app
| [Wednesday 25 August 2010] [04:03:01] <sustrik> right, but a signal coming to app thread can cause a deadlock -- a busy loop actually
| [Wednesday 25 August 2010] [04:03:20] <mato>    how so?
| [Wednesday 25 August 2010] [04:03:47] <sustrik> the code looks like this:
| [Wednesday 25 August 2010] [04:03:49] <sustrik> while (errno = EINTR)
| [Wednesday 25 August 2010] [04:03:55] <sustrik>     do_blocking_op ();
| [Wednesday 25 August 2010] [04:04:08] <sustrik> so once signal arrives, it loops
| [Wednesday 25 August 2010] [04:04:26] <mato>    what is "the code"? 0mq code? app code?
| [Wednesday 25 August 2010] [04:04:33] <sustrik> 0mq code
| [Wednesday 25 August 2010] [04:04:53] <mato>    which is fine, the blocking operation will restart...
| [Wednesday 25 August 2010] [04:05:07] <sustrik> sure, but the signal is still there
| [Wednesday 25 August 2010] [04:05:14] <sustrik> so it'll retart in infinite loop
| [Wednesday 25 August 2010] [04:05:17] <mato>    huh?
| [Wednesday 25 August 2010] [04:05:38] <mato>    you only get EINTR if the call is actually *interrupted*
| [Wednesday 25 August 2010] [04:05:42] <mato>    it's not a level trigger
| [Wednesday 25 August 2010] [04:06:03] <mato>    so you will get at most one EINTR per signal
| [Wednesday 25 August 2010] [04:06:04] <sustrik> even with sigwait-style signals?
| [Wednesday 25 August 2010] [04:06:17] <sustrik> there's a queue there in the background afaiu
| [Wednesday 25 August 2010] [04:06:25] <mato>    if you're using sigwait style signals then it is your responsibility to do it right
| [Wednesday 25 August 2010] [04:06:27] <sustrik> is is still edge-trigerred
| [Wednesday 25 August 2010] [04:06:28] <sustrik> ?
| [Wednesday 25 August 2010] [04:06:37] <mato>    which means doing the signal handling in a thread of its own
| [Wednesday 25 August 2010] [04:06:58] <mato>    which does nothing except run the sigwait loop
| [Wednesday 25 August 2010] [04:07:06] <sustrik> "never combine 0MQ socket with signals"
| [Wednesday 25 August 2010] [04:07:11] <mato>    no
| [Wednesday 25 August 2010] [04:07:28] <mato>    if you're using naive signal handling with signal() it might work fine
| [Wednesday 25 August 2010] [04:07:44] <sustrik> hm
| [Wednesday 25 August 2010] [04:08:18] <mato>    unless people are actually *expecting* calls to return with EINTR
| [Wednesday 25 August 2010] [04:08:30] <sustrik> i been thinking about it because zed actually experienced the infinite looping
| [Wednesday 25 August 2010] [04:08:42] <sustrik> zedas: hullo!
| [Wednesday 25 August 2010] [04:08:45] <mato>    zedas: yo
| [Wednesday 25 August 2010] [04:09:20] <mato>    he's probably asleep, zed is somewhere in the states, no?
| [Wednesday 25 August 2010] [04:09:22] <zedas>   what's up?
| [Wednesday 25 August 2010] [04:09:25] <mato>    ah
| [Wednesday 25 August 2010] [04:09:28] <zedas>   i never sleep
| [Wednesday 25 August 2010] [04:09:34] <mato>    zedas: what's this about signals and infinite loops?
| [Wednesday 25 August 2010] [04:09:39] <zedas>   well actually i was about to :-)
| [Wednesday 25 August 2010] [04:09:43] <mato>    :-)
| [Wednesday 25 August 2010] [04:09:45] <zedas>   mato: it's not signals.
| [Wednesday 25 August 2010] [04:10:03] <zedas>   so what's happening is the following (that i haven't tracked down)
| [Wednesday 25 August 2010] [04:10:14] <zedas>   1. Mongrel2 starts up with 2 or 4 IO threads.
| [Wednesday 25 August 2010] [04:10:44] <zedas>   2. A request comes in for a handler, so M2 sends it out on 0MQ to that handler, which is in python, or lua so far, but seems to be on any of them.
| [Wednesday 25 August 2010] [04:10:56] <zedas>   3. Handler then gets *2* messages, but we only sent one.
| [Wednesday 25 August 2010] [04:11:04] <zedas>   i have confirmed this 5 times.
| [Wednesday 25 August 2010] [04:11:25] <zedas>   4. Handler responds to both messages, but Mongrel2 then gets hit with an "infinite" loop in zmq_poll.
| [Wednesday 25 August 2010] [04:11:49] <zedas>   5. What's happening is one of the IO threads is setting EINTR on each loop through, so then zmq_poll causes M2 to go 100% CPU.
| [Wednesday 25 August 2010] [04:12:12] <zedas>   6. Finally, if we restart the *handler* (not mongrel2) then the EINTR goes away immediately, and everything goes back to normal.
| [Wednesday 25 August 2010] [04:12:19] <zedas>   that's what i know so far.
| [Wednesday 25 August 2010] [04:12:25] <zedas>   so, i tested it with IO threads set to 1.
| [Wednesday 25 August 2010] [04:12:36] <zedas>   and it totally has no bugs. ran a thrashing test for a whole day to make sure.
| [Wednesday 25 August 2010] [04:12:50] <zedas>   and it's a nasty test too, and not a single lockup or 100% the whole time.
| [Wednesday 25 August 2010] [04:13:02] <zedas>   but, set threads > 1 and bam, 100% right away.
| [Wednesday 25 August 2010] [04:13:15] <mato>    in step 5, the EINTR is coming from the poll() call inside zmq_poll() ?
| [Wednesday 25 August 2010] [04:13:20] <zedas>   so there ya go, that's all I know.  the EINTR isn't caused by signals at all.
| [Wednesday 25 August 2010] [04:13:30] <zedas>   no, i think it's extraneous
| [Wednesday 25 August 2010] [04:13:39] <mato>    yeah, but what is returning EINTR?
| [Wednesday 25 August 2010] [04:13:45] <zedas>   i swear I blocked every damn signal possible and that EINTR still kept going
| [Wednesday 25 August 2010] [04:13:54] <zedas>   well EINTR isn't "returned"
| [Wednesday 25 August 2010] [04:14:06] <zedas>   i think one of these threads is setting it as an error indicator
| [Wednesday 25 August 2010] [04:14:16] <zedas>   and it's not getting caught by 0mq, so it bleeds out to poll.
| [Wednesday 25 August 2010] [04:14:44] <zedas>   anyway after i got mongrel2 1.0 out i was gonna work up a test case for it and try to narrow it down.
| [Wednesday 25 August 2010] [04:14:51] <sustrik> memory overwrite maybe
| [Wednesday 25 August 2010] [04:14:54] <zedas>   but if you guys have insight into where in the code this could happen.
| [Wednesday 25 August 2010] [04:15:11] <sustrik> as far as i see there are 2 distinct problems
| [Wednesday 25 August 2010] [04:15:12] <mato>    sustrik: or somewhere in the i/o code we are not squashing an EINTR and should be?
| [Wednesday 25 August 2010] [04:15:21] <zedas>   yeah my thinking is the IO thread gets the double response and freaks out.  that's also why the handler becomes unresponsive.
| [Wednesday 25 August 2010] [04:15:31] <sustrik> yes
| [Wednesday 25 August 2010] [04:15:47] <sustrik> the first problem may actually overwrite memory or so
| [Wednesday 25 August 2010] [04:15:59] <sustrik> so the second problem may be just a consequence of the first one
| [Wednesday 25 August 2010] [04:16:07] <mato>    it's still strange that EINTR comes into play if no signals are involved
| [Wednesday 25 August 2010] [04:16:15] <zedas>   hmm. yep and the best indicator it's a thread issue and not poll/interrupt is i kill the handler, and poof problem solved.
| [Wednesday 25 August 2010] [04:16:40] <zedas>   if it was signals then i'd still be getting them even after killing the handler.
| [Wednesday 25 August 2010] [04:16:46] <sustrik> hm
| [Wednesday 25 August 2010] [04:16:49] <zedas>   also signals coming in that fast would really nuke the process.
| [Wednesday 25 August 2010] [04:17:11] <zedas>   i mean these are tight loop poll calls going fast as hell, no way i'm getting signals that quick.
| [Wednesday 25 August 2010] [04:17:28] <mato>    zedas: just to make sure, is there any way you can trace the process when it happens with something that would show signals being delivered?
| [Wednesday 25 August 2010] [04:17:45] <mato>    zedas: e.g. running it under GDB with all signals set to "nostop pass" and logging the output?
| [Wednesday 25 August 2010] [04:17:46] <zedas>   i have a few stack traces...let me find...
| [Wednesday 25 August 2010] [04:17:53] <zedas>   mato: oh yeah, no signals
| [Wednesday 25 August 2010] [04:18:00] <zedas>   i swear up and down i cannot catch any signals
| [Wednesday 25 August 2010] [04:18:16] <zedas>   gdb gets nothing.  manually capturing every one with sigaction. nothing.
| [Wednesday 25 August 2010] [04:18:26] <sustrik> overwriting glibc memory can result in strange poll behaviour
| [Wednesday 25 August 2010] [04:18:32] <zedas>   either it's in another thread, which is really weird, or it's being set manually, or overwritten ram.
| [Wednesday 25 August 2010] [04:18:58] <mato>    we never return EINTR anywhere manually
| [Wednesday 25 August 2010] [04:18:59] <zedas>   http://mongrel2.org/tktview?name=f1691a47d1
| [Wednesday 25 August 2010] [04:19:03] <zedas>   that's our bug on it
| [Wednesday 25 August 2010] [04:19:06] <mato>    grepping src/* for EINTR will tell you that...
| [Wednesday 25 August 2010] [04:19:20] <zedas>   there's a really good stack trace in there and our debug dumps, and info i've found so far
| [Wednesday 25 August 2010] [04:19:33] <sustrik> zedas: iirc you've said that it happens only when you use multiple i/o threads; does that apply still?
| [Wednesday 25 August 2010] [04:20:05] <zedas>   yep.
| [Wednesday 25 August 2010] [04:20:14] <zedas>   if i set io threads to 1, no problems
| [Wednesday 25 August 2010] [04:20:20] <zedas>   > 1 and lock up almost immediately
| [Wednesday 25 August 2010] [04:20:39] <zedas>   and it eventually settles down, which to me says race condition in the threading
| [Wednesday 25 August 2010] [04:21:10] <sustrik> mato: we should run some tests with multiple i/o threads
| [Wednesday 25 August 2010] [04:21:24] <mato>    sustrik: yeah
| [Wednesday 25 August 2010] [04:21:27] <sustrik> everyone's using magic number of 1 so it's very much untested
| [Wednesday 25 August 2010] [04:21:41] <zedas>   http://mongrel2.org/artifact/3fcd396312653274f96cee730287bd62d8018fb0
| [Wednesday 25 August 2010] [04:21:55] <zedas>   that's the python 0mq handler that has the most frequent lockups
| [Wednesday 25 August 2010] [04:22:01] <zedas>   and it's really not doing much.
| [Wednesday 25 August 2010] [04:22:22] <sustrik> zedas: ok, thanks for the info
| [Wednesday 25 August 2010] [04:22:25] <zedas>   receive[Cs on a DOWNSTREAM socket, sends on a PUB socket.
| [Wednesday 25 August 2010] [04:22:48] <sustrik> i'll do some tests with multiple i/o threads
| [Wednesday 25 August 2010] [04:22:53] <mato>    zedas: yeah, thanks. /me thinks the EINTR is a red herring and this looks like a race between i/o threads
| [Wednesday 25 August 2010] [04:22:56] <sustrik> hopefully i'll be able to reproduce
| [Wednesday 25 August 2010] [04:22:59] <mato>    sustrik: you have that big 8-core box 
| [Wednesday 25 August 2010] [04:23:08] <sustrik> two of them :)
| [Wednesday 25 August 2010] [04:23:12] <mato>    sustrik: yeah, exactly
| [Wednesday 25 August 2010] [04:23:22] <mato>    load the hell out of it and see what breaks 
| [Wednesday 25 August 2010] [04:23:23] <zedas>   mato: ohhhh you know, i saw this more when i switched to an 8-core box....
| [Wednesday 25 August 2010] [04:25:14] <mato>    zedas: since EINTR came up, do you have any opinion on us squashing EINTR in zmq_* calls?
| [Wednesday 25 August 2010] [04:25:42] <mato>    zedas: that's the way it's done now since we considered the EINTR thing with UNIX calls a bug and felt no need to emulate it
| [Wednesday 25 August 2010] [04:26:25] <mato>    so effectively all zmq_* calls ignore EINTR and (should) never return it
| [Wednesday 25 August 2010] [04:27:01] <zedas>   mato: actually yeah, i think you shouldn't do that.  to me it should work just like poll, except handle 0mq or regular sockets together.
| [Wednesday 25 August 2010] [04:27:33] <zedas>   especially in my server since i also have to handle those anyway in other parts, so zmq_poll doing it causes problems potentially.
| [Wednesday 25 August 2010] [04:28:31] <mato>    zedas: so you prefer the standard behaviour even if it is kind of broken?
| [Wednesday 25 August 2010] [04:28:46] <mato>    most code i've seen ends up calling system calls in a loop ignoring EINTR
| [Wednesday 25 August 2010] [04:29:43] <zedas>   yep, that's what i'd prefer, but you'd probably break people's code who expect you to do this
| [Wednesday 25 August 2010] [04:29:56] <zedas>   so, as long as you fix it so it doesn't peg the cpu 100% i'm alright with it.
| [Wednesday 25 August 2010] [04:30:31] <mato>    ok
| [Wednesday 25 August 2010] [04:35:41] <mato>    pieterh: will join you in 15mins or so
| [Wednesday 25 August 2010] [04:36:36] <travlr>  are you guys at a conference?
| [Wednesday 25 August 2010] [04:37:38] <sustrik> travlr: no, but we happen to be in the same city
| [Wednesday 25 August 2010] [04:37:54] <travlr>  ah. cool. enjoy your meet.
| [Wednesday 25 August 2010] [04:37:54] <sustrik> pieterh, mato: ok, i'm leaving as well
| [Wednesday 25 August 2010] [05:40:18] <CIA-20>  zeromq2: 03Martin Lucina 07master * rc06a3cc 10/ (builds/msvc/platform.hpp configure.in): Update version number to 2.0.8 - http://bit.ly/bS3kGK
| [Wednesday 25 August 2010] [05:44:06] <CIA-20>  zeromq2: 03Pieter Hintjens 07master * rd788c1f 10/ NEWS : Updated NEWS for stable 2.0.8 release - http://bit.ly/bgBrD1
| [Wednesday 25 August 2010] [06:10:20] <CIA-20>  zeromq2: 03Pieter Hintjens 07master * r98bea86 10/ NEWS : Updated NEWS for stable 2.0.8 release - http://bit.ly/9NJIVG
| [Wednesday 25 August 2010] [06:10:21] <CIA-20>  zeromq2: 03Pieter Hintjens 07master * r6d275a8 10/ NEWS : Updated NEWS for stable 2.0.8 release - http://bit.ly/bLMHJw
| [Wednesday 25 August 2010] [06:51:59] <CIA-20>  zeromq2: 03Martin Lucina 07master * rc9076c5 10/ doc/zmq_socket.txt : 
| [Wednesday 25 August 2010] [06:51:59] <CIA-20>  zeromq2: Basic documentation for XREQ/XREP socket types
| [Wednesday 25 August 2010] [06:51:59] <CIA-20>  zeromq2: Add some basic documentation for XREQ/XREP socket types, including
| [Wednesday 25 August 2010] [06:51:59] <CIA-20>  zeromq2: a brief description of the most common use case (REQ -> XREP) and (XREQ ->
| [Wednesday 25 August 2010] [06:51:59] <CIA-20>  zeromq2: REP). - http://bit.ly/ctquxP
| [Wednesday 25 August 2010] [06:54:38] <travlr>  sustrik: you guys should commit to your local repository and make one commit to the public repo at the end of your session
| [Wednesday 25 August 2010] [06:55:05] <alfborge>    Any work on the fortran bindings?
| [Wednesday 25 August 2010] [06:55:48] <mato>    travlr: it'd still be split into multiple commits even if i do one push
| [Wednesday 25 August 2010] [06:55:55] <mato>    travlr: since the changes are separate things
| [Wednesday 25 August 2010] [06:56:51] <travlr>  yeah but you can do that locally and only do one commit to the public repo when you are done for the day
| [Wednesday 25 August 2010] [06:57:05] <travlr>  or the session
| [Wednesday 25 August 2010] [06:58:00] <pieterh> travlr: sorry about that...
| [Wednesday 25 August 2010] [06:58:04] <travlr>  :)
| [Wednesday 25 August 2010] [06:58:45] <pieterh> i generally use -amend to reduce commits but it did not work here, got some weird merge conflict... 
| [Wednesday 25 August 2010] [06:59:18] <travlr>  merge conflicts are why i stopped using rebase too.
| [Wednesday 25 August 2010] [06:59:38] <pieterh> anyhow, the good news is we're making 2.0.8 stable
| [Wednesday 25 August 2010] [06:59:54] <travlr>  i saw that w00t w00t.. lol
| [Wednesday 25 August 2010] [07:08:22] <travlr>  btw, to get technical.. i meant one push to the public repo not a commit.
| [Wednesday 25 August 2010] [07:22:07] <CIA-20>  zeromq2: 03Martin Lucina 07master * r1e089f7 10/ ChangeLog : Update ChangeLog for v2.0.8 - http://bit.ly/aYIYNs
| [Wednesday 25 August 2010] [08:23:08] <CIA-20>  jzmq: 03Gonzalo Diethelm 07master * r914cbd0 10/ src/org/zeromq/ZMQ.java : Added method Poller.getSocket(int index). - http://bit.ly/aSnrqC
| [Wednesday 25 August 2010] [09:28:09] <keffo>   oh, nice bot feature :)
| [Wednesday 25 August 2010] [09:32:26] <keffo>   meh, by the hammer of thor, I've hit my 20gb 3g transfer cap :/
| [Wednesday 25 August 2010] [09:34:18] <pieterh> keffo: you transferred 20GB via 3G????
| [Wednesday 25 August 2010] [09:34:29] <pieterh> my monthly limit is 500MB and I haven't even hit that
| [Wednesday 25 August 2010] [09:37:16] <keffo>   hehe
| [Wednesday 25 August 2010] [09:37:53] <keffo>   then at least you're familiar with how agonizing it is to do any sort of internet related work over 3g :)
| [Wednesday 25 August 2010] [09:39:27] <keffo>   this is my only connection, and 3-4 machines using it, if you include the phone itself
| [Wednesday 25 August 2010] [09:39:57] <pieterh> wow
| [Wednesday 25 August 2010] [09:41:36] <keffo>   (hence the predisposition I have about both reliability & custom loadbalancing :))
| [Wednesday 25 August 2010] [09:42:05] <CIA-20>  zeromq2: 03Martin Sustrik 07master * rb608c19 10/ (3 files in 2 dirs): MSVC build fixed (+19 more commits...) - http://bit.ly/cp3KJL
| [Wednesday 25 August 2010] [09:42:44] <keffo>   msvc build fixed?
| [Wednesday 25 August 2010] [09:48:26] <mato>    keffo: that is part of a bunch of changes that have landed on master
| [Wednesday 25 August 2010] [09:48:38] <mato>    keffo: which will become 2.1.x, to be announced shortly
| [Wednesday 25 August 2010] [09:55:19] <keffo>   how shortly? I'm just fuzzing around upgrading to 2.0.8! :)
| [Wednesday 25 August 2010] [09:55:35] <mato>    by announced i mean we'll announce what's cooking
| [Wednesday 25 August 2010] [09:55:46] <keffo>   hmm.. the #define _CRT_SECURE_NO_WARNINGS in windows.hpp probably should be guarded..
| [Wednesday 25 August 2010] [09:55:58] <mato>    no schedule for an actual 2.1.x release yet, many changes that need to be tested
| [Wednesday 25 August 2010] [09:56:29] <keffo>   what are the major ones?
| [Wednesday 25 August 2010] [09:56:41] <mato>    wait for the ml announcement :)
| [Wednesday 25 August 2010] [09:58:14] <keffo>   oki
| [Wednesday 25 August 2010] [11:18:34] <keffo>   well, that was a good 20 minutes of trying to make good old dad to stop using IE
| [Wednesday 25 August 2010] [11:52:39] <ModusPwnens> Hello
| [Wednesday 25 August 2010] [12:05:12] <keffo>   hellu
| [Wednesday 25 August 2010] [12:07:49] <ModusPwnens> hi keffo, i have a problem with zeromq
| [Wednesday 25 August 2010] [12:11:08] <keffo>   ok
| [Wednesday 25 August 2010] [12:15:07] <ModusPwnens> So i am trying to set up a basic server/client setup
| [Wednesday 25 August 2010] [12:15:13] <ModusPwnens> and I got it to work locally
| [Wednesday 25 August 2010] [12:15:39] <ModusPwnens> but when I tried to do it across the network, the server would not receive any of the clients messages
| [Wednesday 25 August 2010] [12:15:54] <ModusPwnens> but I used a network analyzer and confirmed that the computer itself was indeed receiving the messages
| [Wednesday 25 August 2010] [12:17:04] <ModusPwnens> I was following the example for the Hello World program, except I sort of rewrote it because I am also using Google Protocol Buffers
| [Wednesday 25 August 2010] [12:17:35] <keffo>   that shouldnt matter, it's just data
| [Wednesday 25 August 2010] [12:17:45] <keffo>   you probably changed something else while doodling
| [Wednesday 25 August 2010] [12:17:57] <keffo>   or screwed up the size or something
| [Wednesday 25 August 2010] [12:18:01] <ModusPwnens> That's what I thought, but I retested it locally and it works just fine
| [Wednesday 25 August 2010] [12:18:12] <ModusPwnens> its just when I try to do it over the network that it doesn't work
| [Wednesday 25 August 2010] [12:18:24] <ModusPwnens> I was wondering if there was something we have to change or add if we are doing it over a network
| [Wednesday 25 August 2010] [12:18:28] <keffo>   did the sample work?
| [Wednesday 25 August 2010] [12:18:33] <ModusPwnens> Yeah
| [Wednesday 25 August 2010] [12:18:42] <keffo>   over network?
| [Wednesday 25 August 2010] [12:19:09] <ModusPwnens> Hmm, I didn't try that. I only tried it locally to verify that it worked.
| [Wednesday 25 August 2010] [12:19:13] <ModusPwnens> Hold on, let me try that
| [Wednesday 25 August 2010] [12:19:39] <keffo>   as long as you're not using inproc or ipc, it should work provided firewalls are in order etc
| [Wednesday 25 August 2010] [12:19:56] <ModusPwnens> I'm just using tcp
| [Wednesday 25 August 2010] [12:20:27] <ModusPwnens> Also, is there some reason using localhost for the endpoint of the bind function in the server application would cause the program to crash?
| [Wednesday 25 August 2010] [12:21:07] <keffo>   programs should never crash :)
| [Wednesday 25 August 2010] [12:21:19] <ModusPwnens> bahaha, that's very true.
| [Wednesday 25 August 2010] [12:21:27] <keffo>   try with tcp://*:1234 etc
| [Wednesday 25 August 2010] [12:21:40] <ModusPwnens> Yeah that's what i had originally.
| [Wednesday 25 August 2010] [12:21:48] <ModusPwnens> But I was just trying different things to get it to work
| [Wednesday 25 August 2010] [12:21:55] <keffo>   using localhost in a server sounds pretty weird :)
| [Wednesday 25 August 2010] [12:22:35] <keffo>   eth0 etc should work though, but not in windows I think
| [Wednesday 25 August 2010] [12:22:49] <keffo>   but with one nic that doesn't matter, just use *
| [Wednesday 25 August 2010] [12:23:00] <ModusPwnens> Yeah that's what I was doing.
| [Wednesday 25 August 2010] [12:23:07] <ModusPwnens> For the client, we would use the ip address of the server, yes?
| [Wednesday 25 August 2010] [12:23:11] <keffo>   yeah
| [Wednesday 25 August 2010] [12:23:17] <ModusPwnens> I thought so..
| [Wednesday 25 August 2010] [12:23:21] <keffo>   bind vs connect
| [Wednesday 25 August 2010] [12:23:29] <ModusPwnens> hmm...well let me try the example and see if it works
| [Wednesday 25 August 2010] [12:23:37] <ModusPwnens> if it doesnt, maybe there is some more complicated issue
| [Wednesday 25 August 2010] [12:25:02] <ModusPwnens> what..? Do the change the examples on the website a lot?
| [Wednesday 25 August 2010] [12:25:14] <ModusPwnens> There are nowhere near as many examples as there were the other day
| [Wednesday 25 August 2010] [12:30:43] <ModusPwnens> ok, so I just tried using the hello world example over the network
| [Wednesday 25 August 2010] [12:31:08] <ModusPwnens> and the only change I made was to the endpoint in the client. I changed it to the ip address of the other computer I am using the server .exe on
| [Wednesday 25 August 2010] [12:32:20] <ModusPwnens> and it doesn't work, but it does work locally
| [Wednesday 25 August 2010] [12:34:05] <keffo>   it's pretty active yeah
| [Wednesday 25 August 2010] [12:34:06] <guido_g> packet filter?
| [Wednesday 25 August 2010] [12:34:33] <ModusPwnens> a packet filter?
| [Wednesday 25 August 2010] [12:34:55] <guido_g> something that filters out packets on the network
| [Wednesday 25 August 2010] [12:34:58] <ModusPwnens> I am sorry, but I am relatively new to networking and the concepts involved..
| [Wednesday 25 August 2010] [12:35:15] <guido_g> often wrongly called a firewall
| [Wednesday 25 August 2010] [12:35:34] <ModusPwnens> Hmm. I saw the data I was sending when I used wireshark to analyze the traffic
| [Wednesday 25 August 2010] [12:35:41] <ModusPwnens> would the packet filter occur before or after that?
| [Wednesday 25 August 2010] [12:35:49] <guido_g> on which machine?
| [Wednesday 25 August 2010] [12:35:53] <ModusPwnens> both
| [Wednesday 25 August 2010] [12:36:04] <guido_g> then it should be ok
| [Wednesday 25 August 2010] [12:36:21] <guido_g> but i'm notz sure... it's windows, so be prepared for the unexpected
| [Wednesday 25 August 2010] [12:36:30] <ModusPwnens> *sigh* i am well aware of that lol
| [Wednesday 25 August 2010] [12:36:56] <ModusPwnens> as far as getting the hello world example to work over networking though, all you should have to do is change the endpoint for the connect function, right? ]
| [Wednesday 25 August 2010] [12:37:16] <ModusPwnens> and if that doesn't work, there is some other underlying cause as to why?
| [Wednesday 25 August 2010] [12:37:29] <guido_g> best is you perepare a text with what you did (exactly!) and paste that to a paste bin
| [Wednesday 25 August 2010] [12:37:57] <ModusPwnens> What I did as far as modifying the hello world code?
| [Wednesday 25 August 2010] [12:38:07] <guido_g> for example
| [Wednesday 25 August 2010] [12:38:19] <guido_g> if you modifed the code, put it on the paste bin too
| [Wednesday 25 August 2010] [12:39:09] <ModusPwnens> I'm not sure I understand. What purpose would this serve?
| [Wednesday 25 August 2010] [12:39:49] <guido_g> that we do see the same code as you
| [Wednesday 25 August 2010] [12:40:11] <guido_g> now we're guessing
| [Wednesday 25 August 2010] [12:40:28] <ModusPwnens> oh. Well I'm not sure that's necessary. All i did was copy and paste the code off the website
| [Wednesday 25 August 2010] [12:41:12] <guido_g> ok, your choice
| [Wednesday 25 August 2010] [12:44:48] <ModusPwnens> I imagine that the hello world code must have been verified to work over a network
| [Wednesday 25 August 2010] [12:45:39] <ModusPwnens> i highly doubt that it wouldn't work. I'm just a little unsure of what could cause the problem on my end
| [Wednesday 25 August 2010] [12:46:52] <guido_g> because you refuse to show "your end" no one knows
| [Wednesday 25 August 2010] [12:47:06] <ModusPwnens> fine fine, I will copy my code over
| [Wednesday 25 August 2010] [12:47:46] <guido_g> btw, this is the accepted practice when asking for help
| [Wednesday 25 August 2010] [12:49:53] <ModusPwnens> oh ok..Sorry, i didn't know. One of my coworkers told me about these irc chatrooms so i have never really been on one before
| [Wednesday 25 August 2010] [12:50:23] <ModusPwnens> Ok so, you don't want me to just copy the code right over right? You said something about a paste bin..
| [Wednesday 25 August 2010] [12:50:46] <guido_g> http://paste.pocoo.org/
| [Wednesday 25 August 2010] [12:51:32] <ModusPwnens> http://paste.pocoo.org/show/254360/
| [Wednesday 25 August 2010] [12:51:53] <ModusPwnens> the only other thing that could be different is that I have additional header files
| [Wednesday 25 August 2010] [12:52:02] <ModusPwnens> but i dont think that would cause a problem
| [Wednesday 25 August 2010] [12:52:25] <guido_g> you typed it, right?
| [Wednesday 25 August 2010] [12:52:59] <guido_g> ops, wrong window
| [Wednesday 25 August 2010] [12:55:46] <guido_g> ok, given that the packets are visible on both machines, try to replace the '*' in line 69 with the ip of the machine
| [Wednesday 25 August 2010] [12:56:10] <ModusPwnens> of the client machine?
| [Wednesday 25 August 2010] [12:56:25] <guido_g> line 70 actually
| [Wednesday 25 August 2010] [12:56:41] <guido_g> no, of course not
| [Wednesday 25 August 2010] [12:56:53] <guido_g> ip of the machine the server is running on
| [Wednesday 25 August 2010] [12:57:30] <guido_g> how many interfaces does this machine have?
| [Wednesday 25 August 2010] [12:57:35] <ModusPwnens> Hmm. I didn't think that was necessary since it was being run on that computer
| [Wednesday 25 August 2010] [12:57:39] <ModusPwnens> but i will try that
| [Wednesday 25 August 2010] [12:58:52] <guido_g> ok, if it doesen't work, gather all the information incl. the changes to the programs and post a problem report to the mailing list
| [Wednesday 25 August 2010] [12:59:18] <ModusPwnens> Okie doke. Thanks for your help!
| [Wednesday 25 August 2010] [12:59:34] <guido_g> important information is operating system, compiler, mq version etc.
| [Wednesday 25 August 2010] [13:00:05] <ModusPwnens> as far as the compiler goes, is it alright to just say I'm using Visual Studio 2008? I'm not really sure what compiler it uses.
| [Wednesday 25 August 2010] [13:00:19] <guido_g> should be enough
| [Wednesday 25 August 2010] [13:00:29] <ModusPwnens> Ok. Thanks!
| [Wednesday 25 August 2010] [13:00:33] <guido_g> but i'm not a windows guy, so i can't tell for sure
| [Wednesday 25 August 2010] [13:01:30] <ModusPwnens> hey!! it works!
| [Wednesday 25 August 2010] [13:01:50] <guido_g> ok
| [Wednesday 25 August 2010] [13:01:53] <ModusPwnens> So
| [Wednesday 25 August 2010] [13:02:08] <ModusPwnens> why exactly did i need to put the ip address of the computer itself there?
| [Wednesday 25 August 2010] [13:02:14] <guido_g> what version of MQ do you use?
| [Wednesday 25 August 2010] [13:02:21] <guido_g> no idea
| [Wednesday 25 August 2010] [13:02:38] <guido_g> might be a windows issue
| [Wednesday 25 August 2010] [13:02:42] <ModusPwnens> 2.07
| [Wednesday 25 August 2010] [13:03:02] <guido_g> ok, that is sort of current
| [Wednesday 25 August 2010] [13:03:27] <ModusPwnens> how often are new versions released?
| [Wednesday 25 August 2010] [13:03:38] <guido_g> i'd say write this to the ml. might be a bug
| [Wednesday 25 August 2010] [13:03:53] <guido_g> when there is something new
| [Wednesday 25 August 2010] [13:04:00] <guido_g> no fixed times
| [Wednesday 25 August 2010] [13:05:00] <ModusPwnens> Oh ok. I will do as you suggested.
| [Wednesday 25 August 2010] [13:06:08] <guido_g> ok, have fun
| [Wednesday 25 August 2010] [14:47:59] <cremes>  i have a question about communicating between XREQ and XREP pairs
| [Wednesday 25 August 2010] [14:48:34] <cremes>  looking at the docs, it mentions adding a null message part between the identity and the body when communicating from REQ to XREP or XREQ to REP
| [Wednesday 25 August 2010] [14:48:45] <cremes>  is that also necessary when going directly from XREQ to XREP?
| [Wednesday 25 August 2010] [14:49:56] <cremes>  let me rephrase that last part...
| [Wednesday 25 August 2010] [14:50:25] <cremes>  when returning a response from a XREP to a XREQ socket, do i need to build the message chain as "identity", "delimiter", "body parts"?
| [Wednesday 25 August 2010] [19:16:15] <mato>    cremes: re. your question, no you don't need to add the delimiter when connecting XREQ
| [Wednesday 25 August 2010] [19:16:20] <mato>    cremes: ...to XREP
| [Wednesday 25 August 2010] [19:16:51] <mato>    cremes: however, if you do so you maintain the ability to connect a REQ/REP should you need to
| [Wednesday 25 August 2010] [19:17:19] <mato>    cremes: the docs for XREQ/XREP are minimalist, feel free to expand/suggest clearer wording as a patch, thx
| [Wednesday 25 August 2010] [20:59:03] <cremes>  mato: ok; i figured it out and posted a bunch of rambling messages to the ML
| [Wednesday 25 August 2010] [20:59:10] <cremes>  i'll add some thoughts to the wiki
| [Wednesday 25 August 2010] [23:22:20] <cremes>  btw, the pub_sub.rb example illustrates how multiple sub sockets can connect to one publisher
| [Wednesday 25 August 2010] [23:22:35] <andrewvc>    oh, yeah, I have that working with ffi-rzmq right now
| [Wednesday 25 August 2010] [23:23:05] <cremes>  that example is in zmqmachine
| [Wednesday 25 August 2010] [23:23:10] <cremes>  is your failing example similar?
| [Wednesday 25 August 2010] [23:23:17] <andrewvc>    lemme double check it
| [Wednesday 25 August 2010] [23:23:30] <andrewvc>    I actually just went with plain ffi-rzmq
| [Wednesday 25 August 2010] [23:23:53] <andrewvc>    and sent stuff off to eventmachine
| [Wednesday 25 August 2010] [23:23:58] <cremes>  ok
| [Wednesday 25 August 2010] [23:24:04] <andrewvc>    but I like zmqmachine style a bit better
| [Wednesday 25 August 2010] [23:24:21] <cremes>  yeah, i lifted most of the api from EM
| [Wednesday 25 August 2010] [23:24:41] <cremes>  except for EM::Connection which never made any sense to me API-wise
| [Wednesday 25 August 2010] [23:25:05] <andrewvc>    yeah, api wise, eventmachine is a bit convoluted
| [Wednesday 25 August 2010] [23:25:19] <andrewvc>    I see why node.js is stealing the show
| [Wednesday 25 August 2010] [23:25:37] <cremes>  ha... node.js is a javascript port of EM
| [Wednesday 25 August 2010] [23:26:06] <cremes>  the original author wrote about it on the home page way back when
| [Wednesday 25 August 2010] [23:26:36] <cremes>  part of EM's problem is due to async/callback programming is inherently ugly
| [Wednesday 25 August 2010] [23:27:11] <cremes>  it's very difficult to follow a single logical path through the code when it's broken up amongst 10s or 100s of small callbacks
| [Wednesday 25 August 2010] [23:27:22] <andrewvc>    yep
| [Wednesday 25 August 2010] [23:27:46] <cremes>  anyway, let me know if you need any bugs fixed
| [Wednesday 25 August 2010] [23:27:55] <andrewvc>    sure thing
| [Wednesday 25 August 2010] [23:28:02] <cremes>  i'm usually in channel from 8am-10pm cdt (chicago)
| [Wednesday 25 August 2010] [23:28:11] <cremes>  heading off to bed in a few...
| [Wednesday 25 August 2010] [23:28:12] <andrewvc>    thanks for the pointers to 2.0.8, reading the xrep/xreq docs right now
| [Wednesday 25 August 2010] [23:28:23] <cremes>  cool. good luck.
| [Wednesday 25 August 2010] [23:28:45] <andrewvc>    thanks
| [Thursday 26 August 2010] [03:31:57] <keffo>    hu, asko kauppi contributed to zmq?
| [Thursday 26 August 2010] [03:41:12] <sustrik>  some details iirc
| [Thursday 26 August 2010] [03:41:17] <sustrik>  you know him?
| [Thursday 26 August 2010] [03:51:02] <keffo>    never met him, but he's been around the lua community for ages
| [Thursday 26 August 2010] [03:52:29] <keffo>    hum, xreq/xrep across say, 10 queue devices will still work as per automagic?
| [Thursday 26 August 2010] [03:54:20] <guido_g>  it should
| [Thursday 26 August 2010] [03:54:50] <guido_g>  as long the identity of the req is properly put in front
| [Thursday 26 August 2010] [03:55:12] <keffo>    I got realy confused by the 'proper message sequence for xreq to xrep..." on the ml
| [Thursday 26 August 2010] [03:58:52] <keffo>    do I need to prepend a null delimiter, or will that be taken care of? (v2.0.8)
| [Thursday 26 August 2010] [04:09:46] <guido_g>  if you use the x* sockets, you've to add the null message yourself
| [Thursday 26 August 2010] [04:10:11] <guido_g>  but this is only needed if you also use non x* socket (aka REQ/REP)
| [Thursday 26 August 2010] [04:10:55] <guido_g>  so for interoperability: always add the null part
| [Thursday 26 August 2010] [04:11:02] <guido_g>  imho, of course
| [Thursday 26 August 2010] [04:21:19] <keffo>    ah ok
| [Thursday 26 August 2010] [04:22:04] <keffo>    so as long as the whole flow is x-based, no additional work on my part is needed to get proper routing shebang working properly?
| [Thursday 26 August 2010] [04:23:45] <guido_g>  shebang?
| [Thursday 26 August 2010] [04:25:48] <keffo>    yeah... hmm, I think it's from a book
| [Thursday 26 August 2010] [04:26:12] <guido_g>  aha
| [Thursday 26 August 2010] [04:26:38] <keffo>    as in, the big bang resulting in the universe, ie the whole shebang :)
| [Thursday 26 August 2010] [04:27:02] <keffo>    1. a situation, matter, or affair (esp in the phrase the whole shebang)
| [Thursday 26 August 2010] [04:28:50] <keffo>    anyhew, I'll have to doodle with that stuff later, right now I have to fix my server, since upgrading ubuntu always leads to something being screwed up
| [Thursday 26 August 2010] [04:33:17] <guido_g>  hehe
| [Thursday 26 August 2010] [04:33:38] <guido_g>  good luck then
| [Thursday 26 August 2010] [05:55:49] <pieterh>  sustrik: why do you want to keep the iothreads argument in zmq_init()?
| [Thursday 26 August 2010] [05:55:57] <pieterh>  it seems so wrong
| [Thursday 26 August 2010] [05:56:57] <sustrik>  pieterh: your solution would require user to call ioclt each time
| [Thursday 26 August 2010] [05:57:05] <sustrik>  so instead of zmq_init (1)
| [Thursday 26 August 2010] [05:57:07] <pieterh>  ?
| [Thursday 26 August 2010] [05:57:08] <keffo>    what's the alternative?
| [Thursday 26 August 2010] [05:57:15] <pieterh>  in 99% of cases the user wouldn't do anything extra
| [Thursday 26 August 2010] [05:57:27] <sustrik>  he would have to call the ioctl
| [Thursday 26 August 2010] [05:57:38] <sustrik>  otherwise the i/o threads wouldn't be launched
| [Thursday 26 August 2010] [05:57:38] <pieterh>  in 1% of cases they would call zmq_setctxopt() just after zmq_init()
| [Thursday 26 August 2010] [05:57:55] <pieterh>  i/o threads can be launched automatically on first use of context
| [Thursday 26 August 2010] [05:57:58] <pieterh>  this all seems obvious
| [Thursday 26 August 2010] [05:58:01] <pieterh>  what am I missing?
| [Thursday 26 August 2010] [05:58:20] <sustrik>  sync issues
| [Thursday 26 August 2010] [05:58:24] <keffo>    why not just zmq_init( int num = 1 )? =)
| [Thursday 26 August 2010] [05:58:34] <sustrik>  that would require mutex on each zmq call
| [Thursday 26 August 2010] [05:58:35] <pieterh>  its the C API
| [Thursday 26 August 2010] [05:58:43] <pieterh>  ?
| [Thursday 26 August 2010] [05:59:05] <sustrik>  you cannot initiate I/O thread launch without locking first
| [Thursday 26 August 2010] [05:59:13] <sustrik>  otherwise it can happen twice
| [Thursday 26 August 2010] [05:59:19] <sustrik>  and mess everything up
| [Thursday 26 August 2010] [05:59:27] <pieterh>  and you cannot create further i/o threads?
| [Thursday 26 August 2010] [05:59:31] <sustrik>  no
| [Thursday 26 August 2010] [05:59:49] <sustrik>  it's lock free, so you have to have infrastructure in place in advance
| [Thursday 26 August 2010] [06:00:27] <pieterh>  that '1' is really nasty
| [Thursday 26 August 2010] [06:00:53] <sustrik>  you can add one more function
| [Thursday 26 August 2010] [06:00:59] <pieterh>  indeed
| [Thursday 26 August 2010] [06:01:05] <sustrik>  zmq_init vs. zmq_init_thread_pool_size (int0
| [Thursday 26 August 2010] [06:01:05] <pieterh>  zmq_init_nasty(N)
| [Thursday 26 August 2010] [06:01:08] <pieterh>  yes
| [Thursday 26 August 2010] [06:01:49] <pieterh>  are there other context configuration aspects that can happen dynamically?
| [Thursday 26 August 2010] [06:01:56] <sustrik>  no
| [Thursday 26 August 2010] [06:02:12] <sustrik>  context is a pretty dumb object
| [Thursday 26 August 2010] [06:02:19] <sustrik>  everything is done on sockets
| [Thursday 26 August 2010] [06:02:23] <pieterh>  indeed
| [Thursday 26 August 2010] [06:02:29] <pieterh>  ok, this makes sense, thanks
| [Thursday 26 August 2010] [06:02:34] <sustrik>  np
| [Thursday 26 August 2010] [06:02:55] <pieterh>  since setctxopt was discussed several times on the list it's worth explaining why it can't happen
| [Thursday 26 August 2010] [06:03:03] <pieterh>  i'll write this up on the 3-0 design page
| [Thursday 26 August 2010] [06:03:09] <sustrik>  btw
| [Thursday 26 August 2010] [06:03:23] <sustrik>  yes, there's one more possible context option
| [Thursday 26 August 2010] [06:03:30] <sustrik>  "max_sockets"
| [Thursday 26 August 2010] [06:03:44] <pieterh>  right
| [Thursday 26 August 2010] [06:03:50] <pieterh>  to prevent DoS
| [Thursday 26 August 2010] [06:04:12] <sustrik>  i mean max 0MQ sockets
| [Thursday 26 August 2010] [06:04:19] <sustrik>  it's the same problem
| [Thursday 26 August 2010] [06:04:23] <pieterh>  what's the use case for that?
| [Thursday 26 August 2010] [06:04:31] <pieterh>  currently it's hard-coded?
| [Thursday 26 August 2010] [06:04:39] <sustrik>  infrastructure for sockets has to be created in advance
| [Thursday 26 August 2010] [06:04:44] <sustrik>  because of lock free algos
| [Thursday 26 August 2010] [06:04:46] <pieterh>  right
| [Thursday 26 August 2010] [06:04:54] <sustrik>  so now it's hard-coded to 512
| [Thursday 26 August 2010] [06:05:09] <pieterh>  ok, how about an init call that is open ended
| [Thursday 26 August 2010] [06:05:14] <pieterh>  rather than fixed arguments
| [Thursday 26 August 2010] [06:05:18] <sustrik>  elipsis?
| [Thursday 26 August 2010] [06:05:20] <pieterh>  an api that can be extended indefinitely
| [Thursday 26 August 2010] [06:05:32] <pieterh>  elipsis and named arguments in C
| [Thursday 26 August 2010] [06:05:43] <sustrik>  pretty nasty
| [Thursday 26 August 2010] [06:06:00] <pieterh>  ZMQ_MAXSOCKETS, n, ZMQ_TTL, n, 0
| [Thursday 26 August 2010] [06:06:10] <pieterh>  it'll be used mainly by bindings
| [Thursday 26 August 2010] [06:06:15] <sustrik>  yeah
| [Thursday 26 August 2010] [06:06:23] <pieterh>  and lets us add context options at any time
| [Thursday 26 August 2010] [06:06:44] <sustrik>  possibly, let's leave that for later
| [Thursday 26 August 2010] [06:07:12] <pieterh>  i'd like to fix all the extension points in the API by 3.0
| [Thursday 26 August 2010] [06:07:54] <sustrik>  that's far away still
| [Thursday 26 August 2010] [06:08:28] <pieterh>  design work takes time
| [Thursday 26 August 2010] [06:08:43] <sustrik>  btw, the other option is to make max_sockets and io_threads compile time settings
| [Thursday 26 August 2010] [06:08:59] <pieterh>  that's not a bad solution IMO
| [Thursday 26 August 2010] [06:09:06] <pieterh>  but it still breaks the API so there's no point
| [Thursday 26 August 2010] [06:09:20] <pieterh>  if we break the API it has to be for something worthwhile
| [Thursday 26 August 2010] [06:09:32] <sustrik>  sure
| [Thursday 26 August 2010] [06:09:58] <pieterh>  IMO once we make it easy to add context options there will be a bunch that appear
| [Thursday 26 August 2010] [06:10:05] <pieterh>  basically it allows defaults for sockets
| [Thursday 26 August 2010] [06:10:24] <pieterh>  e.g. modify SUB socket behavior
| [Thursday 26 August 2010] [06:10:41] <pieterh>  set timeouts
| [Thursday 26 August 2010] [06:10:44] <pieterh>  set heartbeats
| [Thursday 26 August 2010] [06:10:45] <pieterh>  etc.
| [Thursday 26 August 2010] [06:11:16] <pieterh>  these can't be compile time, they're usually per application
| [Thursday 26 August 2010] [06:14:56] <CIA-20>   zeromq2: 03Ivo Danihelka 07master * r43f2c6f 10/ (AUTHORS src/zmq.cpp): improved null checking in zmq_term - http://bit.ly/afqWj9
| [Thursday 26 August 2010] [09:53:09] <keffo>    hum, is there an established method of debugging how/why an xreq/xrep chain wont deliver properly?
| [Thursday 26 August 2010] [09:56:22] <cremes>   keffo: i debugged a xreq/xrep problem by putting a queue device in the middle and having it print each message part
| [Thursday 26 August 2010] [09:56:32] <cremes>   plus i did the same on the "client" and "server"
| [Thursday 26 August 2010] [09:57:07] <keffo>    mm true
| [Thursday 26 August 2010] [09:57:35] <keffo>    I already have that thougg..
| [Thursday 26 August 2010] [09:57:38] <keffo>    though
| [Thursday 26 August 2010] [09:58:04] <cremes>   so where does the message get stuck or disappear?
| [Thursday 26 August 2010] [09:58:34] <keffo>    on the way back :)
| [Thursday 26 August 2010] [09:58:45] <cremes>   ah...
| [Thursday 26 August 2010] [09:59:04] <cremes>   how many hops are there between your client and server? are they directly connected?
| [Thursday 26 August 2010] [09:59:09] <keffo>    client -> queue -> queue -> worker
| [Thursday 26 August 2010] [09:59:14] <cremes>   ok
| [Thursday 26 August 2010] [09:59:40] <cremes>   does it disappear from worker to queue1, queue1 to queue2, or queue2 to client?
| [Thursday 26 August 2010] [10:00:07] <keffo>    the second one isn't a regular queue, it's a much hack at the moment, so the problem is probably that..
| [Thursday 26 August 2010] [10:00:22] <cremes>   ok
| [Thursday 26 August 2010] [10:00:34] <cremes>   are they all using XREQ/XREP sockets or have you mixed them up?
| [Thursday 26 August 2010] [10:00:45] <keffo>    nono, made sure they're all x-based
| [Thursday 26 August 2010] [10:00:54] <cremes>   good
| [Thursday 26 August 2010] [10:01:17] <keffo>    but the second queue there is not using polling
| [Thursday 26 August 2010] [10:01:33] <cremes>   that shouldn't matter
| [Thursday 26 August 2010] [10:01:37] <keffo>    ah, it might be a multipart issue
| [Thursday 26 August 2010] [10:02:17] <keffo>    I think I'm gonna rewrite it though, and extend the queue to handle incoming & outgoing msg callbacks instead (for complete msgs)
| [Thursday 26 August 2010] [10:02:34] <keffo>    or does that exist somewhere in that swamp of links called wiki? =)
| [Thursday 26 August 2010] [10:03:38] <cremes>   i don't think that exists in the "swamp" ;)
| [Thursday 26 August 2010] [10:03:48] <cremes>   but if you write it, you should add it as a code recipe
| [Thursday 26 August 2010] [10:04:23] <keffo>    naa, the callback would be lua :)
| [Thursday 26 August 2010] [10:04:57] <cremes>   that's ok
| [Thursday 26 August 2010] [10:05:03] <cremes>   i'm writing a recipe now that is all in ruby
| [Thursday 26 August 2010] [10:05:14] <keffo>    I mean, I dont use the lua bindings
| [Thursday 26 August 2010] [10:05:41] <cremes>   oh, so just stub it out for the recipe; everyone will have different callbacks anyway, right?
| [Thursday 26 August 2010] [10:15:42] <sustrik>  keffo: there's one identity per hop, you have to copy all of them to the reply
| [Thursday 26 August 2010] [10:21:36] <keffo>    sustrik, do elaborate!
| [Thursday 26 August 2010] [10:21:44] <keffo>    before I dice up more code please! :)
| [Thursday 26 August 2010] [10:21:57] <cremes>   keffo: i'm writing up a recipe explaining this stuff right now
| [Thursday 26 August 2010] [10:22:02] <cremes>   give me another 15 minutes
| [Thursday 26 August 2010] [10:22:16] <keffo>    sounds awesome
| [Thursday 26 August 2010] [10:22:51] <keffo>    sustrik, I get what you mean, it puzzled me earlier, but I assumed zmq would pass along the identity on its own
| [Thursday 26 August 2010] [10:23:12] <cremes>   keffo: it does but *only* for REQ and REP sockets
| [Thursday 26 August 2010] [10:23:21] <guido_g>  not with X* sockets
| [Thursday 26 August 2010] [10:23:25] <cremes>   XREQ and XREP make you do some of the message routing work yourself
| [Thursday 26 August 2010] [10:26:52] <sustrik>  well, it's kind of separated into 2 layers
| [Thursday 26 August 2010] [10:27:00] <sustrik>  the bottom layer is XREQ/XREP
| [Thursday 26 August 2010] [10:27:27] <sustrik>  what it does is that each hop prepends the message with a new part containing the identity of the sender
| [Thursday 26 August 2010] [10:27:40] <sustrik>  that's for requests
| [Thursday 26 August 2010] [10:27:49] <sustrik>  for replies it works other way round
| [Thursday 26 August 2010] [10:28:08] <sustrik>  at each hop one message part is consumer and used to route the message to the next hop
| [Thursday 26 August 2010] [10:28:34] <sustrik>  so, when you have a look at the request after couple of hops
| [Thursday 26 August 2010] [10:28:44] <sustrik>  what you see is a backtrace stack of identities
| [Thursday 26 August 2010] [10:28:53] <sustrik>  followed by the original message
| [Thursday 26 August 2010] [10:29:08] <sustrik>  as for REQ/REP
| [Thursday 26 August 2010] [10:29:19] <sustrik>  what they do is very simple
| [Thursday 26 August 2010] [10:29:38] <keffo>    indeed, makes sense
| [Thursday 26 August 2010] [10:29:47] <sustrik>  REQ prepends the message by an empty message part
| [Thursday 26 August 2010] [10:30:06] <sustrik>  so that REP socket on the other side knows where's the bottom of the stack
| [Thursday 26 August 2010] [10:30:07] <keffo>    samples would be nice though, like a client server does >1>N hops?
| [Thursday 26 August 2010] [10:31:07] <sustrik>  REP socket then chops the backtrace stack off the request and stores it (it knows it'll end by empty message part because it assumes there's a REQ socket on the other side)
| [Thursday 26 August 2010] [10:31:34] <sustrik>  when the reply is sent it glues the backtrace stack at the beginning of the reply
| [Thursday 26 August 2010] [10:31:37] <sustrik>  that's it
| [Thursday 26 August 2010] [10:31:53] <sustrik>  keffo: what samples?
| [Thursday 26 August 2010] [10:32:24] <keffo>    A sample that uses two queues for instance, and only using xreq/xrep
| [Thursday 26 August 2010] [10:32:43] <keffo>    like, client>queue>worker for instance, all using x's
| [Thursday 26 August 2010] [10:33:10] <keffo>    or rather, 2N queues, since that's what I'm doing :)
| [Thursday 26 August 2010] [10:33:18] <keffo>    sigh.. N queues, not 2N :)
| [Thursday 26 August 2010] [10:33:35] <sustrik>  :)
| [Thursday 26 August 2010] [10:33:47] <sustrik>  ok, say 2 queues
| [Thursday 26 August 2010] [10:34:02] <sustrik>  so the requester sends message X
| [Thursday 26 August 2010] [10:34:18] <sustrik>  on first queue you'll get id1|X
| [Thursday 26 August 2010] [10:34:31] <sustrik>  in second queue you'll get id2|id1|X
| [Thursday 26 August 2010] [10:34:47] <sustrik>  on the terminal node you'll get id3|id2|id1|X
| [Thursday 26 August 2010] [10:35:15] <sustrik>  then you send a reply Y like this: id3|id2|id1|Y
| [Thursday 26 August 2010] [10:35:17] <keffo>    yup yup
| [Thursday 26 August 2010] [10:35:29] <sustrik>  etc.
| [Thursday 26 August 2010] [10:35:45] <keffo>    so each queue would need to keep track of all incoming, and then match with the outgoing?
| [Thursday 26 August 2010] [10:36:03] <sustrik>  no
| [Thursday 26 August 2010] [10:36:11] <sustrik>  all the state is in message itself
| [Thursday 26 August 2010] [10:36:26] <sustrik>  once you forward the message you can forget about it
| [Thursday 26 August 2010] [10:37:15] <keffo>    hum, so 2 queuedevices can be linked straight away out of the box?
| [Thursday 26 August 2010] [10:37:19] <keffo>    or, N
| [Thursday 26 August 2010] [10:37:23] <sustrik>  yes
| [Thursday 26 August 2010] [10:37:38] <sustrik>  that's the whole point of the design
| [Thursday 26 August 2010] [10:37:42] <sustrik>  it's hop-agnostic
| [Thursday 26 August 2010] [10:38:50] <mankins>  hi. anyone around to answer a pub/sub zeromq question?
| [Thursday 26 August 2010] [10:39:01] <sustrik>  sure
| [Thursday 26 August 2010] [10:39:17] <keffo>    sustrik, Then I'm at a loss again why this stuff fails to deliver?
| [Thursday 26 August 2010] [10:39:36] <mankins>  gr8. i'm trying to setup a pub/sub and am a little confused if its possible to bind+subscribe
| [Thursday 26 August 2010] [10:39:54] <sustrik>  keffo: how do you create the reply?
| [Thursday 26 August 2010] [10:40:06] <sustrik>  mankins: yes
| [Thursday 26 August 2010] [10:40:18] <cremes>   keffo: take a look at this draft and let me know what youthink...  http://www.zeromq.org/recipe:new-recipe
| [Thursday 26 August 2010] [10:40:28] <sustrik>  bind/connect is completely orthogonal to pub/sub
| [Thursday 26 August 2010] [10:40:47] <mankins>  sustrik: ok, good, I must have a problem somewhere else then.  That's how I read it, but the demo didn't have that.
| [Thursday 26 August 2010] [10:40:57] <keffo>    cremes, nice, I'll be back a bit later :)
| [Thursday 26 August 2010] [10:41:25] <cremes>   ok
| [Thursday 26 August 2010] [10:41:34] <mankins>  i'm also using the perl library which doesn't seem to have a poll function.
| [Thursday 26 August 2010] [10:43:35] <keffo>    cremes, more please :)
| [Thursday 26 August 2010] [10:43:42] <sustrik>  mankins: what's your problem?
| [Thursday 26 August 2010] [10:44:03] <cremes>   keffo: yessir; when i'm done feel free to give specific feedback on questions that are not adequately answered
| [Thursday 26 August 2010] [10:44:35] <mankins>  sustrik: no traffic
| [Thursday 26 August 2010] [10:45:11] <mankins>  i'm in the middle of debugging, so not quite sure yet...when I wrap my head around it, I'll come back
| [Thursday 26 August 2010] [10:45:34] <keffo>    cremes, Will do! Gonna take a shower, then reload the page and see?
| [Thursday 26 August 2010] [10:45:40] <cremes>   sure
| [Thursday 26 August 2010] [10:47:06] <sustrik>  mankins: have you subscribed?
| [Thursday 26 August 2010] [10:47:24] <sustrik>  zmq_setsockopt (s, ZMQ_SUBSCRIBE, "", 0);
| [Thursday 26 August 2010] [10:47:43] <mankins>  sustrik: I have two application processes, one which binds to a socket, and sets zmq_subscribe, ""
| [Thursday 26 August 2010] [10:47:58] <mankins>  then that process just does sock->recv
| [Thursday 26 August 2010] [10:48:03] <sustrik>  what's the socket type?
| [Thursday 26 August 2010] [10:48:09] <mankins>  zmq_sub
| [Thursday 26 August 2010] [10:48:28] <sustrik>  that's ok
| [Thursday 26 August 2010] [10:48:53] <sustrik>  however, are you aware that pub/sub is unreliable?
| [Thursday 26 August 2010] [10:48:57] <mankins>  then the other process  connects to the other socket (is that the right word for an endpoint?)
| [Thursday 26 August 2010] [10:49:09] <sustrik>  i.e. you won't get messages that were sent before you've subscribed?
| [Thursday 26 August 2010] [10:49:11] <mankins>  it does a connect, and then send.
| [Thursday 26 August 2010] [10:49:37] <mankins>  i'm not getting any messages, either way
| [Thursday 26 August 2010] [10:50:58] <mankins>  actually, I think I might have got it to work by sending multiple messages.
| [Thursday 26 August 2010] [10:51:14] <guido_g>  how so?
| [Thursday 26 August 2010] [10:51:53] <mankins>  yeah, if I wrap the sender-side in a while loop, I can receive the messages, but if the publisher sends, then dies, the message doesn't go thru
| [Thursday 26 August 2010] [10:51:56] <sustrik>  i would say the problem is that it takes some time to connect
| [Thursday 26 August 2010] [10:52:15] <mankins>  ohhh. is there a way to figure out "readiness"
| [Thursday 26 August 2010] [10:52:22] <sustrik>  nope
| [Thursday 26 August 2010] [10:52:41] <mankins>  i see. okay...I'll work with that.  thanks for your help.
| [Thursday 26 August 2010] [10:52:45] <sustrik>  np
| [Thursday 26 August 2010] [11:11:55] <mankins>  I'm trying to wrap an eval + alarm combo around the perl library's recv function to timeout, but this doesn't seem to be working...is it possible the program execution is in another thread that doesn't receive the signal?
| [Thursday 26 August 2010] [11:14:52] <Steve-o>  There was a discussion about signals before, they should be explicitly ignored so that the Perl thread should catch all of them
| [Thursday 26 August 2010] [11:15:36] <mankins>  Steve-o: that sounds like how it should work.  I wonder if the current CPAN module does that.
| [Thursday 26 August 2010] [11:15:36] <Steve-o>  as in, ZeroMQ already explicitly "ignores" signals, as in sets them to be ignored in libc
| [Thursday 26 August 2010] [11:16:36] <Steve-o>  if ZeroMQ is in another thread and the alarm signal is raised for the process it should bounce around till a thread doesn't ignore it
| [Thursday 26 August 2010] [11:17:42] <Steve-o>  probably worth trying adding a signal handling inside ZMQ to see if it receives the alarm
| [Thursday 26 August 2010] [11:18:24] <sustrik>  Steve-o: the current state of affairs is that 0MQ's internal threads block all the signals
| [Thursday 26 August 2010] [11:18:32] <sustrik>  the application threads are untouched
| [Thursday 26 August 2010] [11:19:18] <sustrik>  the unclear part is whether 0MQ API should return EINTR in case a signal arrives during a blocking operation
| [Thursday 26 August 2010] [11:19:34] <sustrik>  cremes: the next is not entirely right
| [Thursday 26 August 2010] [11:19:39] <Steve-o>  mankins: could try siggetmask() to find the state of the Perl thread
| [Thursday 26 August 2010] [11:19:53] <mankins>  Steve-o: will look into that.
| [Thursday 26 August 2010] [11:19:59] <sustrik>  it's only the XREP socket that adds/removes identities
| [Thursday 26 August 2010] [11:20:07] <cremes>   ah, ok
| [Thursday 26 August 2010] [11:20:09] <cremes>   will fix
| [Thursday 26 August 2010] [11:20:11] <sustrik>  XREQ socket leaves the messages alone
| [Thursday 26 August 2010] [11:20:30] <sustrik>  that way you have only a single identity in the stack per intermediary node (such as queue)
| [Thursday 26 August 2010] [11:20:30] <cremes>   well, it *adds* its identity to each message
| [Thursday 26 August 2010] [11:20:46] <cremes>   XREQ adds, XREP pops, yes?
| [Thursday 26 August 2010] [11:21:01] <sustrik>  actually, XREQ does nothing
| [Thursday 26 August 2010] [11:21:01] <cremes>   s/adds/pushes/
| [Thursday 26 August 2010] [11:21:26] <sustrik>  XREP pushes identity of the peer to the requests
| [Thursday 26 August 2010] [11:21:51] <sustrik>  it's a bit strange but it saves bandwidth
| [Thursday 26 August 2010] [11:22:01] <cremes>   oh, that isn't clear from observation
| [Thursday 26 August 2010] [11:22:10] <sustrik>  ie. in client/server topology, there's no identity passed on the wire
| [Thursday 26 August 2010] [11:22:23] <cremes>   so XREP pushes the identity upon receipt
| [Thursday 26 August 2010] [11:22:26] <sustrik>  yeah, you would have to inspect the traffic
| [Thursday 26 August 2010] [11:22:30] <sustrik>  right
| [Thursday 26 August 2010] [11:22:45] <cremes>   so who does the identity pop?
| [Thursday 26 August 2010] [11:22:49] <sustrik>  XREP
| [Thursday 26 August 2010] [11:22:55] <sustrik>  for replies
| [Thursday 26 August 2010] [11:23:03] <cremes>   ok
| [Thursday 26 August 2010] [11:23:03] <sustrik>  so it's XREP in both cases:
| [Thursday 26 August 2010] [11:23:09] <sustrik>  push on request
| [Thursday 26 August 2010] [11:23:11] <sustrik>  pop on reply
| [Thursday 26 August 2010] [11:23:20] <cremes>   got it
| [Thursday 26 August 2010] [11:26:47] <cremes>   page is fixed; please verify the part that was wrong is now either gone or correct
| [Thursday 26 August 2010] [11:27:15] <mankins>  do I need two sockets, one for writing, and one for reading? can I change between pub and sub?
| [Thursday 26 August 2010] [11:27:25] <cremes>   mankins: two sockets
| [Thursday 26 August 2010] [11:27:30] <mankins>  two contexts too?
| [Thursday 26 August 2010] [11:27:32] <cremes>   you can't change a socket type once it is allocated
| [Thursday 26 August 2010] [11:28:02] <cremes>   mankins: maybe; i don't know what you have discussed here previously
| [Thursday 26 August 2010] [11:28:20] <cremes>   you can have 100s or thousands of sockets per context
| [Thursday 26 August 2010] [11:28:34] <cremes>   (actually, i think the limit is 512 right now)
| [Thursday 26 August 2010] [11:28:41] <cremes>   per context
| [Thursday 26 August 2010] [11:33:23] <sustrik>  cremes: the picutre still shows four identities in the message
| [Thursday 26 August 2010] [11:33:36] <sustrik>  whereas there should be 3 as there are 3 XREP sockets
| [Thursday 26 August 2010] [11:33:43] <cremes>   ok
| [Thursday 26 August 2010] [11:34:13] <sustrik>  also, i would mark the process boundaries on the diagram
| [Thursday 26 August 2010] [11:34:36] <sustrik>  that way it would be obvious you have one identity per process
| [Thursday 26 August 2010] [11:34:49] <sustrik>  to route back
| [Thursday 26 August 2010] [11:35:33] <sustrik>  so, in your case you have a sender process, queue1, queue2 and receiver processes
| [Thursday 26 August 2010] [11:35:51] <sustrik>  when the request arrives at receiver
| [Thursday 26 August 2010] [11:35:55] <sustrik>  it looks like this:
| [Thursday 26 August 2010] [11:36:17] <sustrik>  queue2|queue1|sender|data
| [Thursday 26 August 2010] [11:36:54] <cremes>   shouldn't it be: queue2|queue1|sender|null|data
| [Thursday 26 August 2010] [11:37:40] <sustrik>  ah, there's a REQ socket?
| [Thursday 26 August 2010] [11:37:59] <sustrik>  if so, yes, REQ socket adds empty message part to the bottom of the stack
| [Thursday 26 August 2010] [11:38:08] <cremes>   no, but how else do you know when you have moved from routing parts to body parts?
| [Thursday 26 August 2010] [11:38:22] <cremes>   it seems like a reasonable default to always use a delimiter
| [Thursday 26 August 2010] [11:38:39] <sustrik>  but who will do that?
| [Thursday 26 August 2010] [11:39:02] <cremes>   the "source" prepends the null part before sending the body
| [Thursday 26 August 2010] [11:39:10] <sustrik>  yes
| [Thursday 26 August 2010] [11:39:19] <cremes>   and source is an XREQ
| [Thursday 26 August 2010] [11:39:30] <sustrik>  :)
| [Thursday 26 August 2010] [11:39:34] <cremes>   heh
| [Thursday 26 August 2010] [11:39:38] <cremes>   let me rephrase
| [Thursday 26 August 2010] [11:39:47] <sustrik>  then the stack would look like this:
| [Thursday 26 August 2010] [11:40:09] <sustrik>  queue2|null|queue1|null|sender|null|data
| [Thursday 26 August 2010] [11:40:30] <sustrik>  it's the application that has to add the delimiter
| [Thursday 26 August 2010] [11:40:38] <sustrik>  or a REQ socket
| [Thursday 26 August 2010] [11:40:41] <cremes>   right, the app adds the delimiter
| [Thursday 26 August 2010] [11:40:50] <cremes>   that's how i did it anyway
| [Thursday 26 August 2010] [11:40:57] <sustrik>  ok
| [Thursday 26 August 2010] [11:40:57] <keffo>    oh, I need to nullterminate each response?
| [Thursday 26 August 2010] [11:41:09] <cremes>   keffo: no
| [Thursday 26 August 2010] [11:41:38] <cremes>   sustrik thought i meant that each XREQ had to add a null
| [Thursday 26 August 2010] [11:41:41] <cremes>   that isn't what i meant
| [Thursday 26 August 2010] [11:42:10] <cremes>   only the source XREQ prepends the null; all queues in between just pass the message on
| [Thursday 26 August 2010] [11:42:34] <cremes>   the destination XREP uses the null to delimit between the routing parts and the application-level body parts
| [Thursday 26 August 2010] [11:42:38] <cremes>   make sense?
| [Thursday 26 August 2010] [11:43:53] <sustrik>  cremes: you should start talking in terms of processes
| [Thursday 26 August 2010] [11:44:00] <keffo>    yes
| [Thursday 26 August 2010] [11:44:03] <sustrik>  if you say "source XREQ prepends the null"
| [Thursday 26 August 2010] [11:44:11] <sustrik>  it sounds like 0mq does it
| [Thursday 26 August 2010] [11:44:21] <keffo>    agreed
| [Thursday 26 August 2010] [11:44:28] <cremes>   i'll fix that
| [Thursday 26 August 2010] [11:44:56] <keffo>    and imo, C should be the defacto language for describing things like this?
| [Thursday 26 August 2010] [11:45:11] <keffo>    or at the very least, pseudo :)
| [Thursday 26 August 2010] [11:45:34]     * sustrik prefers psaudocode
| [Thursday 26 August 2010] [11:45:36] <cremes>   keffo: ruby and python are pretty close to pseudo-code already
| [Thursday 26 August 2010] [11:45:46] <sustrik>  C is too messy
| [Thursday 26 August 2010] [11:45:56] <cremes>   feel free to edit the page when i'm done and rewrite the code however you like ;)
| [Thursday 26 August 2010] [11:46:03] <alfborge> howfuckedismydatabase.com
| [Thursday 26 August 2010] [11:46:41] <guido_g>  oh spam
| [Thursday 26 August 2010] [11:46:43] <keffo>    cremes, If I try to rewrite code from a language I dont know, nobody will understand :)
| [Thursday 26 August 2010] [11:46:49] <alfborge> guido_g :)
| [Thursday 26 August 2010] [11:46:54] <guido_g>  no joke
| [Thursday 26 August 2010] [11:47:03] <alfborge> sorry then.
| [Thursday 26 August 2010] [11:47:37] <keffo>    on a completely different note, the cute little fade-in when you expand the table of contents seems to be buggy in firefox :)
| [Thursday 26 August 2010] [11:47:39] <AndrewBC> alfborge, I find it ironic that that page spat out a "Warning: pg_connect() unable to connect to PostgreSQL server: FATAL 1: IDENT authentication failed for user "postgres" in /var/www/database/postgres/common.php on line 10"
| [Thursday 26 August 2010] [11:47:53] <AndrewBC> Unless that's intentional as a joke
| [Thursday 26 August 2010] [11:47:56] <alfborge> AndrewBC: Actually, that's what makes it really funny.
| [Thursday 26 August 2010] [11:48:03] <alfborge> AndrewBC: Check the other warnings/errors.
| [Thursday 26 August 2010] [11:48:28] <AndrewBC> Okay, yeah. Each one does a topical error.
| [Thursday 26 August 2010] [11:48:44] <AndrewBC> I was too busy debating whether that was intentional to laugh. :|
| [Thursday 26 August 2010] [11:54:50] <keffo>    cremes, Why does the page link to itself, under "see also"?
| [Thursday 26 August 2010] [11:55:13] <cremes>   i have no idea; i can't edit that part
| [Thursday 26 August 2010] [11:55:21] <cremes>   must be part of the page template
| [Thursday 26 August 2010] [11:59:51] <pieterh>  keffo: that's just part of the page template
| [Thursday 26 August 2010] [11:59:57] <pieterh>  i can fix it
| [Thursday 26 August 2010] [12:02:15] <keffo>    ;)
| [Thursday 26 August 2010] [12:02:23] <pieterh>  ok, that's fixed, all pages should update in a few seconds
| [Thursday 26 August 2010] [12:02:30] <keffo>    I need to sit down and write some idiot-samples for myself to understand what I need to do here
| [Thursday 26 August 2010] [12:11:02] <mankins>  it feels like buffers aren't getting flushed for single-message communications.  is that possible?
| [Thursday 26 August 2010] [12:15:21] <mankins>  and getting segfaults.  should I be doing this in C?
| [Thursday 26 August 2010] [12:20:30] <sustrik>  mankins: do you have a test program that causes the segfault?
| [Thursday 26 August 2010] [12:20:48] <mankins>  i'll work on it. it seems to be random
| [Thursday 26 August 2010] [12:21:16] <sustrik>  a sanity check: is your application single-threaded?
| [Thursday 26 August 2010] [12:21:19] <mankins>  i just noticed that the perl docs say they are tested with zeromq 2.0.7, and I have .8 installed.
| [Thursday 26 August 2010] [12:21:48] <mankins>  it is single threaded. i have a fcgi process and an app server 
| [Thursday 26 August 2010] [12:21:48] <sustrik>  shouldn't matter, the .8 is a stability release
| [Thursday 26 August 2010] [12:21:54] <sustrik>  ok
| [Thursday 26 August 2010] [12:22:10] <mankins>  at the moment I'm just trying to get them to echo
| [Thursday 26 August 2010] [12:23:21] <mankins>  for some reason the fcgi side seems to get stuck at the recv() an strace shows it doing a recv syscall there.
| [Thursday 26 August 2010] [12:27:09] <mankins>  i'm connecting to myself, I wonder if that's the problem. 
| [Thursday 26 August 2010] [12:27:19] <mankins>  two socks, one binds, one connects
| [Thursday 26 August 2010] [12:27:27] <sustrik>  that should be ok
| [Thursday 26 August 2010] [12:27:42] <sustrik>  obviously, only if you send first, connect afterwards
| [Thursday 26 August 2010] [12:27:50] <sustrik>  recv afterwards*
| [Thursday 26 August 2010] [12:27:52] <mankins>  it receives msgs from the client okay, but sends don't go out
| [Thursday 26 August 2010] [12:28:24] <mankins>  i init, and setup the sockets, then go into a while loop to receive, is that fitting the model?
| [Thursday 26 August 2010] [12:28:38] <sustrik>  sure
| [Thursday 26 August 2010] [12:29:01] <mankins>  and topics are | delimited, right?
| [Thursday 26 August 2010] [12:29:21] <mankins>  topic|msghere
| [Thursday 26 August 2010] [12:29:23] <sustrik>  that's up to you
| [Thursday 26 August 2010] [12:29:27] <sustrik>  0mq does not care
| [Thursday 26 August 2010] [12:29:29] <mankins>  ah
| [Thursday 26 August 2010] [12:29:34] <mankins>  good to know.
| [Thursday 26 August 2010] [12:29:46] <mankins>  then that really shouldn't matter.
| [Thursday 26 August 2010] [12:30:01] <mankins>  is there a way to turn on debug to see what happens on send?
| [Thursday 26 August 2010] [12:30:13] <sustrik>  on the wire?
| [Thursday 26 August 2010] [12:30:16] <mankins>  y
| [Thursday 26 August 2010] [12:30:21] <sustrik>  you may use wireshark
| [Thursday 26 August 2010] [12:30:28] <sustrik>  to capture the traffic
| [Thursday 26 August 2010] [12:30:46] <sustrik>  or tcpdump
| [Thursday 26 August 2010] [12:30:59] <mankins>  ok, let me start that up. so no app-level debugging flags?
| [Thursday 26 August 2010] [12:31:20] <sustrik>  nope
| [Thursday 26 August 2010] [12:40:29] <mankins>  i'd listen on the TCP port, right? the transport isn't udp
| [Thursday 26 August 2010] [12:40:49] <mankins>  nvmind
| [Thursday 26 August 2010] [12:44:36] <sustrik>  tcp
| [Thursday 26 August 2010] [12:45:05] <mankins>  wow, as soon as the communication starts, it doesn't stop. lots of packets.
| [Thursday 26 August 2010] [12:45:46] <mankins>  i ran a few seconds and got 2449... but i was just trying to send a 10 byte message and receive it.
| [Thursday 26 August 2010] [12:46:08] <sustrik>  are you sure you are not monitoring random traffic
| [Thursday 26 August 2010] [12:46:09] <sustrik>  ?
| [Thursday 26 August 2010] [12:46:47] <Steve-o>  like monitoring your own SSH connection isn't a good idea
| [Thursday 26 August 2010] [12:46:58] <sustrik>  cremes: still here?
| [Thursday 26 August 2010] [12:47:17] <cremes>   yes
| [Thursday 26 August 2010] [12:47:36] <sustrik>  i've drawn a picture...
| [Thursday 26 August 2010] [12:47:39] <sustrik>  wait a sec
| [Thursday 26 August 2010] [12:48:13] <mankins>   tcpdump -s 1000 -vvv -X 'tcp port 9010' -i lo
| [Thursday 26 August 2010] [12:48:15] <sd88g93>  greetings
| [Thursday 26 August 2010] [12:48:42] <sustrik>  cremes: http://www.zeromq.org/local--files/recipe:new-recipe/x.png
| [Thursday 26 August 2010] [12:48:50] <sustrik>  does that help?
| [Thursday 26 August 2010] [12:49:20] <cremes>   yes
| [Thursday 26 August 2010] [12:49:50] <sustrik>  if needed, you can place it on the wiki
| [Thursday 26 August 2010] [12:49:57] <sustrik>  [[=image x.png]]
| [Thursday 26 August 2010] [12:49:59] <cremes>   question...
| [Thursday 26 August 2010] [12:50:02] <sustrik>  yes?
| [Thursday 26 August 2010] [12:50:24] <cremes>   in the queue box you have "req||X" by the down arrow
| [Thursday 26 August 2010] [12:50:54] <sustrik>  right
| [Thursday 26 August 2010] [12:50:57] <cremes>   where does the "req" identity come from?
| [Thursday 26 August 2010] [12:51:11] <sustrik>  XREP socket attaches it to the message
| [Thursday 26 August 2010] [12:51:30] <cremes>   ok, so then "X" is the body?
| [Thursday 26 August 2010] [12:51:36] <sustrik>  yes
| [Thursday 26 August 2010] [12:51:39] <cremes>   ok
| [Thursday 26 August 2010] [12:51:43] <sustrik>  i should have named it body
| [Thursday 26 August 2010] [12:51:44] <sustrik>  or data
| [Thursday 26 August 2010] [12:51:51] <cremes>   that pic looks good
| [Thursday 26 August 2010] [12:52:03] <sustrik>  are you on linux?
| [Thursday 26 August 2010] [12:52:04] <cremes>   i'll add it along with a little legend so it's easier to interpret
| [Thursday 26 August 2010] [12:52:06] <cremes>   osx
| [Thursday 26 August 2010] [12:52:14] <sustrik>  ok
| [Thursday 26 August 2010] [12:52:49] <sd88g93>  is it possible to have 2 queeus set up feeding into the same socket ?  or is that a bad idea ?
| [Thursday 26 August 2010] [12:52:51] <sustrik>  i thought of sending you the source for the picture but it's a random linux drawing tool
| [Thursday 26 August 2010] [12:53:00] <cremes>   too bad you didn't put two queues in the picture; that way i could have saved myself from rewriting the explanation
| [Thursday 26 August 2010] [12:53:11] <sustrik>  cremes: let me do that
| [Thursday 26 August 2010] [12:53:18] <cremes>   great
| [Thursday 26 August 2010] [12:53:19] <sustrik>  any other changes?
| [Thursday 26 August 2010] [12:53:43] <sustrik>  sd88g93: it's ok
| [Thursday 26 August 2010] [12:53:46] <cremes>   make "X" into "body" and "Y" into "ResponseBody" or something similar
| [Thursday 26 August 2010] [12:53:58] <sustrik>  the latter is too long
| [Thursday 26 August 2010] [12:54:07] <cremes>   sure, pick something better than Y
| [Thursday 26 August 2010] [12:54:08] <sustrik>  would stretch out of picutre
| [Thursday 26 August 2010] [12:54:23] <sd88g93>  sustrik:  is there any special considerations to use ? 
| [Thursday 26 August 2010] [12:54:26] <cremes>   Y -> Reply
| [Thursday 26 August 2010] [12:54:50] <sustrik>  wouldn't it be confused with the identity "rep"
| [Thursday 26 August 2010] [12:54:59] <sustrik>  maybe change the ids to
| [Thursday 26 August 2010] [12:55:02] <sustrik>  "app1"
| [Thursday 26 August 2010] [12:55:05] <sustrik>  "queue"
| [Thursday 26 August 2010] [12:55:07] <sustrik>  "app2"
| [Thursday 26 August 2010] [12:55:12] <sustrik>  and bodies to:
| [Thursday 26 August 2010] [12:55:15] <sustrik>  "request"
| [Thursday 26 August 2010] [12:55:17] <sustrik>  "reply"
| [Thursday 26 August 2010] [12:56:15] <sd88g93>  oh tutorials added into a wiki,  neat ! 
| [Thursday 26 August 2010] [12:57:59] <cremes>   sustrik: that's better; any confusion in the picture can be cleared up with a legend for it
| [Thursday 26 August 2010] [12:58:20] <sustrik>  ok, working on it
| [Thursday 26 August 2010] [13:01:25] <mankins>  something is amiss.  if the thing that binds to the socket goes down, shouldn't the tcp connection go down as well? it looks like the client re-binds the port?
| [Thursday 26 August 2010] [13:01:55] <mankins>  or is "connect" and "bind" not related to the underlying tcp sockets?
| [Thursday 26 August 2010] [13:03:05] <cremes>   mankins: connect & bind are not directly related to the (potentially many) TCP sockets behind the 0mq socket
| [Thursday 26 August 2010] [13:03:18] <cremes>   take a look at the guide for a good explanation
| [Thursday 26 August 2010] [13:03:19] <cremes>   http://www.zeromq.org/docs:user-guide
| [Thursday 26 August 2010] [13:03:44] <mankins>  cremes: thanks, will read.  
| [Thursday 26 August 2010] [13:04:27] <sustrik>  cremes: http://www.zeromq.org/local--files/recipe:new-recipe/x.png
| [Thursday 26 August 2010] [13:04:58] <sustrik>  (reload it to get rid ofcached image)
| [Thursday 26 August 2010] [13:05:05] <cremes>   that looks *good*
| [Thursday 26 August 2010] [13:08:06] <mankins>  i wonder if I need to do the nanosleep before another read?
| [Thursday 26 August 2010] [13:08:32] <cremes>   how do i make the funky 0 with the line through it? what's the key combo?
| [Thursday 26 August 2010] [13:09:01] <guido_g>  under linux its built in :)
| [Thursday 26 August 2010] [13:09:14] <mankins>  on the mac it's alt o
| [Thursday 26 August 2010] [13:09:20] <mankins>  
| [Thursday 26 August 2010] [13:09:38] <cremes>   mankins: thanks
| [Thursday 26 August 2010] [13:09:44] <mankins>   or alt-shift-o
| [Thursday 26 August 2010] [13:20:50] <Zao>  U+00D8
| [Thursday 26 August 2010] [13:56:49] <mankins>  huh, looks like you can do recv(ZMQ_NOBLOCK) to do non-blocking recvs.
| [Thursday 26 August 2010] [13:57:21] <sustrik>  :)
| [Thursday 26 August 2010] [14:20:12] <mankins>  in case you're following along at home: I got the REQ/REP type messaging to work, but PUB/SUB would not.  I haven't been able to isolate the problem, but am forging forward.
| [Thursday 26 August 2010] [16:23:49] <andrew_cholakian> cremes, if you're around I had a quick question about ffi-rzmq and xrep
| [Thursday 26 August 2010] [16:24:06] <cremes>   ask away
| [Thursday 26 August 2010] [16:24:39] <andrew_cholakian> so, ywhen you call say copy_out_string on an xrep socket, it seems like each message comes in three parts
| [Thursday 26 August 2010] [16:24:49] <andrew_cholakian> the identifier, an empty string, and the actual message
| [Thursday 26 August 2010] [16:24:51] <andrew_cholakian> correct?
| [Thursday 26 August 2010] [16:25:24] <cremes>   right
| [Thursday 26 August 2010] [16:26:05] <cremes>   the identity, null msg and body are all separate ZMQ::Message objects
| [Thursday 26 August 2010] [16:26:18] <andrew_cholakian> oh, interesting
| [Thursday 26 August 2010] [16:26:42] <cremes>   every time you call #recv, it returns a ZMQ::Message object
| [Thursday 26 August 2010] [16:26:48] <cremes>   have you seen it do something else?
| [Thursday 26 August 2010] [16:27:05] <andrew_cholakian> no, not at all, just curious about it, because the other socket types aren't broken up like that
| [Thursday 26 August 2010] [16:27:29] <cremes>   sure they are
| [Thursday 26 August 2010] [16:27:48] <cremes>   for example, a SUB socket will return two message parts for each message
| [Thursday 26 August 2010] [16:27:56] <cremes>   part 1 is the topic, part2 is the body
| [Thursday 26 August 2010] [16:28:24] <cremes>   the bindings aren't doing anything special; they are returning exactly what the 0mq framework is generating
| [Thursday 26 August 2010] [16:28:58] <cremes>   ZMQ::Message is really just a wrapper for the zmq_msg_* functions
| [Thursday 26 August 2010] [16:29:03] <andrew_cholakian> gotcha
| [Thursday 26 August 2010] [16:30:33] <andrew_cholakian> so, http://gist.github.com/552184
| [Thursday 26 August 2010] [16:30:55] <andrew_cholakian> so is this wrong here, the way I'm doing things
| [Thursday 26 August 2010] [16:31:08] <andrew_cholakian> since the messages appear in a single part
| [Thursday 26 August 2010] [16:33:55] <cremes>   they are coming in as a single message because you are only sending a topic
| [Thursday 26 August 2010] [16:34:01] <cremes>   generally you do something like...
| [Thursday 26 August 2010] [16:34:22] <cremes>   pub_sock.send_string("Important", ZMQ::SNDMORE)
| [Thursday 26 August 2010] [16:34:34] <cremes>   pub_sock.send_string("Find Time Machine")
| [Thursday 26 August 2010] [16:34:54] <cremes>   that sends two message parts which constitute a single logical message
| [Thursday 26 August 2010] [16:34:59] <cremes>   make sense?
| [Thursday 26 August 2010] [16:34:59] <andrew_cholakian> makes sense
| [Thursday 26 August 2010] [16:35:03] <andrew_cholakian> perfect sense
| [Thursday 26 August 2010] [16:35:06] <cremes>   good
| [Thursday 26 August 2010] [16:35:26] <cremes>   then on the recv side you can change your handling based upon the received topic
| [Thursday 26 August 2010] [16:35:42] <cremes>   the first msg part will contain the topic and subsequent parts contain the body of the msg
| [Thursday 26 August 2010] [16:35:49] <cremes>   i hope that helps
| [Thursday 26 August 2010] [16:35:58] <cremes>   feel free to add some docs!  :)
| [Thursday 26 August 2010] [16:35:59] <andrew_cholakian> that does help actually
| [Thursday 26 August 2010] [16:36:17] <andrew_cholakian> I will, I'm actually working on writing documenting ruby ffi-rzmq
| [Thursday 26 August 2010] [16:36:34] <cremes>   then you are my favorite person right now
| [Thursday 26 August 2010] [16:36:35] <andrew_cholakian> I'm doing a presentation to LA ruby on it in a couple weeks
| [Thursday 26 August 2010] [16:37:25] <andrew_cholakian> I want to get a nice collection of minimal examples for every socket class, and some example apps using a mix of em up
| [Thursday 26 August 2010] [16:37:38] <cremes>   that sounds great
| [Thursday 26 August 2010] [16:37:48] <cremes>   btw, you are kind of cheating in that example you pasted; sockets should be used from the same thread where their context came from
| [Thursday 26 August 2010] [16:37:54] <cremes>   that's a 0mq requirement
| [Thursday 26 August 2010] [16:38:09] <cremes>   the 2.1.x branch that martin is working on will allow you to move sockets between threads
| [Thursday 26 August 2010] [16:38:19] <cremes>   unless i am misunderstanding something
| [Thursday 26 August 2010] [16:38:27] <cremes>   perhaps sustrik can chime in
| [Thursday 26 August 2010] [16:38:36] <andrew_cholakian> hmmm, so I should create two contexts then
| [Thursday 26 August 2010] [16:38:50] <cremes>   right, one per thread
| [Thursday 26 August 2010] [16:39:01] <cremes>   er... one per application thread
| [Thursday 26 August 2010] [16:40:30] <andrew_cholakian> that may explain why running that example requires me to kill -9 it to leave
| [Thursday 26 August 2010] [16:41:12] <cremes>   um.... maybe
| [Thursday 26 August 2010] [16:41:22] <cremes>   it's probably just MRI's crazy thread handling
| [Thursday 26 August 2010] [16:41:27] <cremes>   it works fine with jruby (no hang)
| [Thursday 26 August 2010] [16:41:49] <andrew_cholakian> nah, that was 1.9.2
| [Thursday 26 August 2010] [16:41:55] <andrew_cholakian> MRI, I think it doesn't run period
| [Thursday 26 August 2010] [16:42:55] <cremes>   MRI = Matz Ruby Interpreter
| [Thursday 26 August 2010] [16:43:05] <cremes>   so MRI is short-hand for 1.8.7, 1.9.1, 1.9.2 etc
| [Thursday 26 August 2010] [16:43:14] <andrew_cholakian> oh, I thought people usually call 1.9.2 YARV
| [Thursday 26 August 2010] [16:43:29] <cremes>   yeah, they call it that too :)
| [Thursday 26 August 2010] [16:43:31] <andrew_cholakian> I'm guessing it still has the same threading issues then
| [Thursday 26 August 2010] [16:43:46] <cremes>   1.9.2 has broken thread handling just like 1.8.6, 1.8.7 and 1.9.1
| [Thursday 26 August 2010] [16:44:09] <cremes>   it doesn't capture signals properly for external threads, so ctrl-c goes to never never land sometimes
| [Thursday 26 August 2010] [16:44:20] <cremes>   and 0mq is the source of the external threads
| [Thursday 26 August 2010] [16:44:25] <cremes>   fyi
| [Thursday 26 August 2010] [16:44:54] <andrew_cholakian> makes sense, yeah. I've been using killall -9 ruby quite a bit dealing with 1.9.2
| [Thursday 26 August 2010] [16:46:10] <cremes>   i recommend jruby for use with 0mq; it has sane thread and signal handling
| [Thursday 26 August 2010] [16:46:18] <cremes>   the main downside is it takes an extra second to start up
| [Thursday 26 August 2010] [16:49:07] <andrew_cholakian> yeah, I've had some issues with jruby and some stuff, I think related to eventmachine when combining them
| [Thursday 26 August 2010] [17:06:18] <merimus>  I'm attempting to create a simple multithread pub/sub using python but am getting lots of crashes.  Would anyone be kind enough to glance at  my code?   http://codepad.org/dRRqkeZO
| [Thursday 26 August 2010] [17:09:59] <merimus>  starting to wonder if there isn't a bug in pythons threads
| [Thursday 26 August 2010] [17:13:36] <cremes>   merimus: take a look at the Thread Safety section on this page:  http://api.zeromq.org/zmq.html
| [Thursday 26 August 2010] [17:13:50] <cremes>   Each MQ socket belonging to a particular context may only be used by the thread that created it using zmq_socket().
| [Thursday 26 August 2010] [17:14:35] <cremes>   you should only access that socket from the thread where it was created (the main thread)
| [Thursday 26 August 2010] [17:17:12] <merimus>  hmm... then how would I send from multiple threads?
| [Thursday 26 August 2010] [17:17:39] <cremes>   each thread needs its own socket
| [Thursday 26 August 2010] [17:17:56] <cremes>   let me rephrease
| [Thursday 26 August 2010] [17:18:10] <cremes>   each thread needs to create its own socket; that socket should then only be used from that thread
| [Thursday 26 August 2010] [17:19:03] <merimus>  but a socket is created on a particular port... which then cannot be reused.  Unless I'm missing something
| [Thursday 26 August 2010] [17:19:31] <cremes>   no, that's right
| [Thursday 26 August 2010] [17:19:40] <cremes>   the way you get around this is to use a zmq_device
| [Thursday 26 August 2010] [17:19:52] <cremes>   for the case of PUB/SUB, use a forwarder device
| [Thursday 26 August 2010] [17:20:06] <cremes>   the forwarder device binds to two ports, say 5500 and 5501
| [Thursday 26 August 2010] [17:20:16] <cremes>   all of your publisher sockets then connect to 5500
| [Thursday 26 August 2010] [17:20:23] <cremes>   and all of your subscribers connect to 5501
| [Thursday 26 August 2010] [17:20:40] <cremes>   the forwarder device aggregates all of the traffic from every publisher and sends to all subscribers
| [Thursday 26 August 2010] [17:20:42] <cremes>   make sense?
| [Thursday 26 August 2010] [17:21:02] <merimus>  indeed... heading back to the docs now
| [Thursday 26 August 2010] [17:21:31] <cremes>   i highly recommend curling up with the guide for an hour or two:   http://www.zeromq.org/docs:user-guide
| [Thursday 26 August 2010] [17:21:40] <cremes>   it covers all of the basics and then some
| [Thursday 26 August 2010] [17:22:08] <merimus>  had just started on that.  Thank you very much.
| [Thursday 26 August 2010] [17:23:08] <cremes>   you are welcome
| [Thursday 26 August 2010] [23:01:16] <andrewvc> cremes, you around?
| [Thursday 26 August 2010] [23:03:47] <AndrewBC> Woah, hi. :D
| [Thursday 26 August 2010] [23:10:20] <andrewvc> we have similar names eh?
| [Thursday 26 August 2010] [23:21:12] <AndrewBC> Indeed
| [Thursday 26 August 2010] [23:27:35] <andrewvc> Quick question about pub/sub if anyone's got a moment
| [Thursday 26 August 2010] [23:28:58] <andrewvc> is it best practice to send the topic separately with SNDMORE, then send the rest separately? Or is that just optional. I've seen examples both using and not using that technique
| [Friday 27 August 2010] [00:24:36] <sustrik>    andrewvc: it's up to you
| [Friday 27 August 2010] [00:24:55] <sustrik>    there's no fundmantal difference between the two
| [Friday 27 August 2010] [00:25:20] <sustrik>    other than in the former case the "topic" is cleanly separated from the "body"
| [Friday 27 August 2010] [00:36:19] <sustrik>    cremes, andrew_cholakian: no, it's OK to use context from multiple threads
| [Friday 27 August 2010] [00:36:44] <sustrik>    just use each socket only in the thread it was created in
| [Friday 27 August 2010] [00:59:57] <CIA-20> zeromq2: 03Jon Dyte 07master * r3cb84b5 10/ (src/forwarder.cpp src/queue.cpp src/streamer.cpp): forwarder and streamer devices handle multi-part messages correctly - http://bit.ly/b55mvk
| [Friday 27 August 2010] [05:33:35] <guido_g>    anyone experienced a problem with zmq::poll?
| [Friday 27 August 2010] [05:34:12] <guido_g>    _sometimes_ it doesn't sent revents correctly, as it seems
| [Friday 27 August 2010] [05:34:40] <guido_g>    it returns with a return value of 0, ignoring the received messages
| [Friday 27 August 2010] [05:35:18] <guido_g>    MQ version is latest from zeromq/zeromq2
| [Friday 27 August 2010] [05:36:06] <theICEBeardk>   Is it like this issue http://github.com/zeromq/zeromq2/issues#issue/7 ?
| [Friday 27 August 2010] [05:36:40] <guido_g>    reading...
| [Friday 27 August 2010] [05:37:31] <guido_g>    we have an issue then :)
| [Friday 27 August 2010] [05:37:43] <guido_g>    yep, seems to be the same problem
| [Friday 27 August 2010] [05:39:21] <guido_g>    any ideas why this happens?
| [Friday 27 August 2010] [05:39:32] <theICEBeardk>   I hope the workaround in the issue can help you
| [Friday 27 August 2010] [05:39:46] <theICEBeardk>   None
| [Friday 27 August 2010] [05:41:29] <guido_g>    scary that no one seems to be interested in this issue
| [Friday 27 August 2010] [05:41:46] <guido_g>    it renders nearly everything useless
| [Friday 27 August 2010] [05:41:52] <theICEBeardk>   agreed
| [Friday 27 August 2010] [05:43:23] <theICEBeardk>   Maybe the devs can't verify the problem or reproduce it. What platform are you on?
| [Friday 27 August 2010] [05:43:53] <guido_g>    GNU/linux Debian testing w/ 2.6.35 kernel
| [Friday 27 August 2010] [05:44:30] <theICEBeardk>   Okay nothing too obscure then :)
| [Friday 27 August 2010] [05:44:49] <guido_g>    ouch...
| [Friday 27 August 2010] [05:44:59] <guido_g>    the problem in the issue is different
| [Friday 27 August 2010] [05:45:07] <guido_g>    i had a timeout of -1
| [Friday 27 August 2010] [05:46:46] <guido_g>    the code says that errors other then EINTR are to be ignored
| [Friday 27 August 2010] [05:48:39] <theICEBeardk>   hmm, if you have some test code, I have to do the unhelpful thing and suggest you raise the issue on the github. 
| [Friday 27 August 2010] [05:48:59] <theICEBeardk>   I know it doesn't help much.
| [Friday 27 August 2010] [05:49:43] <guido_g>    sure
| [Friday 27 August 2010] [05:55:17] <guido_g>    okay... on a different machine it works
| [Friday 27 August 2010] [05:56:20] <theICEBeardk>   Different os or just a different machine?
| [Friday 27 August 2010] [05:57:23] <guido_g>    same os, a little bit older, kernel 2.6.27.31
| [Friday 27 August 2010] [05:57:36] <guido_g>    and older mq lib
| [Friday 27 August 2010] [05:57:49] <guido_g>    from jul 15
| [Friday 27 August 2010] [05:57:54] <guido_g>    hmm hmm hmm
| [Friday 27 August 2010] [05:58:00] <theICEBeardk>   ah a release and not from github
| [Friday 27 August 2010] [05:58:28] <sustrik>    guido_g: what timeout do you use?
| [Friday 27 August 2010] [05:58:35] <guido_g>    -1
| [Friday 27 August 2010] [05:58:40] <guido_g>    hi sustrik btw :)
| [Friday 27 August 2010] [05:58:44] <sustrik>    hello :)
| [Friday 27 August 2010] [05:59:13] <sustrik>    hm, that should never return 0
| [Friday 27 August 2010] [05:59:16] <guido_g>    http://github.com/guidog/cpp/tree/master/zmqcpp/ <- code is receiver_poll.cpp and sender.cpp
| [Friday 27 August 2010] [05:59:20] <sustrik>    0 means "timeout"
| [Friday 27 August 2010] [05:59:34] <guido_g>    right
| [Friday 27 August 2010] [06:00:20] <sustrik>    that's 2.0.8 you are using?
| [Friday 27 August 2010] [06:00:31] <guido_g>    yes
| [Friday 27 August 2010] [06:00:38] <sustrik>    let me have a look...
| [Friday 27 August 2010] [06:00:40] <guido_g>    cloned a few hours ago
| [Friday 27 August 2010] [06:01:03] <sustrik>    2.0.8 or trunk?
| [Friday 27 August 2010] [06:02:01] <sustrik>    the zmq_poll code have changed immediately after 2.0.8 release
| [Friday 27 August 2010] [06:02:12] <guido_g>    then it is trunk i fear
| [Friday 27 August 2010] [06:02:49] <sustrik>    ok, wait a sec
| [Friday 27 August 2010] [06:03:17]   * guido_g needs to read on how to check out a specific tag...
| [Friday 27 August 2010] [06:03:37]   * sustrik has no idea :)
| [Friday 27 August 2010] [06:03:54] <sustrik>    are you using windows or something else?
| [Friday 27 August 2010] [06:04:06] <guido_g>    nope, GNU/linux Debain testing
| [Friday 27 August 2010] [06:04:19] <sustrik>    ok
| [Friday 27 August 2010] [06:05:49] <guido_g>    ok, now same on the other machine that worked with 2.0.7
| [Friday 27 August 2010] [06:05:56] <sustrik>    guido_g: ok, the new version is buggy
| [Friday 27 August 2010] [06:05:58] <guido_g>    so there is something wrong in zmq
| [Friday 27 August 2010] [06:06:43] <sustrik>    the whole zmq_poll functionality should be in loop
| [Friday 27 August 2010] [06:06:54] <sustrik>    and restart the loop if there are no events to return
| [Friday 27 August 2010] [06:07:02] <sustrik>    it was like that in the old version
| [Friday 27 August 2010] [06:07:13] <sustrik>    doesn't appear to be like that now...
| [Friday 27 August 2010] [06:07:15] <guido_g>    2.0.8 is safe?
| [Friday 27 August 2010] [06:07:22] <sustrik>    yes
| [Friday 27 August 2010] [06:07:27] <sustrik>    mato: summon!
| [Friday 27 August 2010] [06:07:29] <pieterh>    guido_g: would it be easier if there was a branch "stable" for 2.0.8?
| [Friday 27 August 2010] [06:07:32] <sustrik>    bug in zmq_poll!
| [Friday 27 August 2010] [06:07:43] <guido_g>    pieterh: YES!
| [Friday 27 August 2010] [06:07:45] <guido_g>    :)
| [Friday 27 August 2010] [06:07:52] <pieterh>    ok, please harass Mato about that
| [Friday 27 August 2010] [06:08:40] <guido_g>    or have a brachn vor this kind of development, so that master is always tested
| [Friday 27 August 2010] [06:09:01]   * guido_g pulls the git books
| [Friday 27 August 2010] [06:09:28] <pieterh>    hah
| [Friday 27 August 2010] [06:10:11] <pieterh>    master should be tested, of course
| [Friday 27 August 2010] [06:10:32] <pieterh>    some disagreement about whether new code goes to master or 'develop' branch
| [Friday 27 August 2010] [06:10:42] <guido_g>    develop, please
| [Friday 27 August 2010] [06:11:19] <guido_g>    'cause this was half a day of fuzzing for me on the software that worked
| [Friday 27 August 2010] [06:11:26] <guido_g>    before the update
| [Friday 27 August 2010] [06:11:32] <pieterh>    please make your wishes known to mato
| [Friday 27 August 2010] [06:11:48] <guido_g>    send location pls   ]:->
| [Friday 27 August 2010] [06:12:00] <pieterh>    via zeromq-dev list, guido_g
| [Friday 27 August 2010] [06:12:05] <guido_g>    oh...
| [Friday 27 August 2010] [06:12:16] <pieterh>    i'd suggest simply state your requirements as user of the git
| [Friday 27 August 2010] [06:12:31] <pieterh>    perhaps referencing practice of other projects
| [Friday 27 August 2010] [06:12:41] <sustrik>    yes, that's the best
| [Friday 27 August 2010] [06:13:20] <guido_g>    sure, going to write a mail
| [Friday 27 August 2010] [06:13:26] <sustrik>    the issue is not that easy as in the future there can be several stable versions etc.
| [Friday 27 August 2010] [06:13:44] <pieterh>    sustrik: yes, indeed
| [Friday 27 August 2010] [06:13:52] <guido_g>    then we should have release branches
| [Friday 27 August 2010] [06:13:59] <pieterh>    but only one (max two) maintained stable version, normally
| [Friday 27 August 2010] [06:14:30] <pieterh>    guido_g: that would seem obvious but... last time i suggested that it was not welcomed
| [Friday 27 August 2010] [06:14:58] <pieterh>    however i think mato is coming round to that point of view
| [Friday 27 August 2010] [06:15:08] <guido_g>    pieterh: i remember there was something...
| [Friday 27 August 2010] [06:15:14] <pieterh>    up to now releases have been tags
| [Friday 27 August 2010] [06:15:21] <guido_g>    ok, then
| [Friday 27 August 2010] [06:15:27] <pieterh>    after 2.0.8 we immediately got a patch (zmq_term)
| [Friday 27 August 2010] [06:15:33] <guido_g>    how do i get the 2.0.8 release out of github?
| [Friday 27 August 2010] [06:15:39] <pieterh>    lol
| [Friday 27 August 2010] [06:15:46] <pieterh>    well, it's tagged
| [Friday 27 August 2010] [06:15:50] <pieterh>    checkout from the tag
| [Friday 27 August 2010] [06:15:57]   * guido_g git n00b
| [Friday 27 August 2010] [06:16:18] <pieterh>    it should work *obviously* for git n00bs IMO
| [Friday 27 August 2010] [06:16:28] <pieterh>    none of us are linux kernel hackers
| [Friday 27 August 2010] [06:17:09] <sustrik>    no way it could work without knowing how to check out a branch
| [Friday 27 August 2010] [06:17:16] <sustrik>    i had that last week
| [Friday 27 August 2010] [06:17:28] <sustrik>    i had a branch i wasn't able to access
| [Friday 27 August 2010] [06:17:40] <sustrik>    i think it's something like:
| [Friday 27 August 2010] [06:18:05] <sustrik>    git checkout -b name-of-the-branch remotes/origin/name-of-the-branch
| [Friday 27 August 2010] [06:20:43] <pieterh>    sustrik: you had an old version of Git
| [Friday 27 August 2010] [06:20:54] <pieterh>    actually that command was also documented in the original proposal I made
| [Friday 27 August 2010] [06:21:08] <guido_g>    git show v2.0.8 <- shows commit
| [Friday 27 August 2010] [06:21:18] <pieterh>    but with git 1.7 you no longer need to specify the remote
| [Friday 27 August 2010] [06:21:25] <guido_g>    git reset <commit> seems to work
| [Friday 27 August 2010] [06:21:48] <pieterh>    yes, the tag is just a nicer name for the commit id
| [Friday 27 August 2010] [06:22:13] <pieterh>    problem is that once we need to maintain a stable release, we can't use tags
| [Friday 27 August 2010] [06:22:21] <pieterh>    so all the commands change
| [Friday 27 August 2010] [06:22:32] <sustrik>    :(
| [Friday 27 August 2010] [06:22:37] <pieterh>    it become git checkout branchname
| [Friday 27 August 2010] [06:22:41] <pieterh>    not git reset tagname
| [Friday 27 August 2010] [06:22:51] <pieterh>    that's why i'd prefer a branch, always, for the last stable release
| [Friday 27 August 2010] [06:23:07] <pieterh>    so it's always "git checkout master" or "git checkout stable" or "git checkout develop"
| [Friday 27 August 2010] [06:23:21] <guido_g>    right
| [Friday 27 August 2010] [06:23:31] <guido_g>    ok, 2.0.8 works
| [Friday 27 August 2010] [06:23:47] <pieterh>    then we can argue about whether master is the bleeding edge, or not
| [Friday 27 August 2010] [06:23:56] <sustrik>    pieterh: a patch without MIT in the mailing list
| [Friday 27 August 2010] [06:24:06] <pieterh>    sustrik: yeah, but it's a 1-line change...
| [Friday 27 August 2010] [06:24:20] <sustrik>    should i ignore it?
| [Friday 27 August 2010] [06:24:41] <guido_g>    pieterh: wasn't that you who posted that link to http://nvie.com/git-model?
| [Friday 27 August 2010] [06:24:43] <pieterh>    ... i don't think copyright applies to single line fixes
| [Friday 27 August 2010] [06:25:00] <pieterh>    guido_g: someone else posted it, i tried it, it's great but way too complex for our needs
| [Friday 27 August 2010] [06:25:31] <guido_g>    ok
| [Friday 27 August 2010] [06:25:48] <sustrik>    if it does and if i apply the patch, project is stuck with current license forever
| [Friday 27 August 2010] [06:25:51] <pieterh>    sustrik: I'd much rather have patches arriving on a website/wiki/issue tracker where it says in huge letters, BY SUBMITTING A PATCH YOU ETC.ETC.
| [Friday 27 August 2010] [06:25:58] <sustrik>    should i proceed?
| [Friday 27 August 2010] [06:26:00] <sustrik>    yes/no
| [Friday 27 August 2010] [06:26:12] <pieterh>    i'll do the necessary, sustrik
| [Friday 27 August 2010] [06:26:16] <pieterh>    hang on...
| [Friday 27 August 2010] [06:27:32] <pieterh>    done
| [Friday 27 August 2010] [06:28:11] <pieterh>    sustrik: if I had to receive patches I'd set-up an issue tracker where anyone posting a patch had to register and accept terms of use that clearly stated the licensing for their contributions
| [Friday 27 August 2010] [06:28:49] <pieterh>    email is really suboptimal for this except that it lets everyone see the patch (do people actually review it?)
| [Friday 27 August 2010] [06:28:51] <sustrik>    it should be clear what the licensing is
| [Friday 27 August 2010] [06:29:04] <pieterh>    there should be a template for each patch
| [Friday 27 August 2010] [06:29:27] <sustrik>    please write an email explaining what the current contribution policy is
| [Friday 27 August 2010] [06:29:33] <pieterh>    it's not changed
| [Friday 27 August 2010] [06:29:42] <pieterh>    it is documented on the website afair
| [Friday 27 August 2010] [06:30:02] <sustrik>    the anouncement about a community project have confused people
| [Friday 27 August 2010] [06:30:13] <pieterh>    http://www.zeromq.org/area:contribute
| [Friday 27 August 2010] [06:30:28] <sustrik>    so make it clear that it's still not in effect
| [Friday 27 August 2010] [06:30:30] <pieterh>    "Please send it to the developer mailing list and explicitly state that you are licensing the patch under the MIT/X11 license."
| [Friday 27 August 2010] [06:30:54] <pieterh>    sustrik: if this was the cause of confusion people would be submitting patches under LGPL
| [Friday 27 August 2010] [06:31:00] <pieterh>    that's not the problem here IMO
| [Friday 27 August 2010] [06:31:07] <pieterh>    it's just that there is no automation of this
| [Friday 27 August 2010] [06:31:29] <sustrik>    they do
| [Friday 27 August 2010] [06:31:44] <pieterh>    i missed that
| [Friday 27 August 2010] [06:31:48] <sustrik>    patch to LGPL'd project is a derivative work thus LGPL
| [Friday 27 August 2010] [06:32:21] <pieterh>    not necessarily
| [Friday 27 August 2010] [06:32:34] <pieterh>    a patch that is not explicitly licensed under LGPL is simply unusable
| [Friday 27 August 2010] [06:32:56] <pieterh>    if you redistribute code with incorrect licensing you can be asked to change it
| [Friday 27 August 2010] [06:33:01] <pieterh>    however it's not automatic
| [Friday 27 August 2010] [06:34:18] <pieterh>    no matter what policy there is, the author of a patch MUST license it, or it falls under simple copyright and cannot be reused, period
| [Friday 27 August 2010] [06:34:25] <sustrik>    how does linux kernel process work then?
| [Friday 27 August 2010] [06:34:39] <pieterh>    presumably all contributors sign off somewhere along the line
| [Friday 27 August 2010] [06:34:50] <sustrik>    how does that work?
| [Friday 27 August 2010] [06:35:22] <pieterh>    i don't know how it works in the linux kernel process, martin
| [Friday 27 August 2010] [06:35:27] <sustrik>    what I see is just signed-of-by someone
| [Friday 27 August 2010] [06:35:35] <sustrik>    no mention of licensing
| [Friday 27 August 2010] [06:35:43] <pieterh>    however try to submit random piece of code without license, see what happens
| [Friday 27 August 2010] [06:35:59] <sustrik>    that's the standard
| [Friday 27 August 2010] [06:36:01] <pieterh>    note how it works for the www.zeromq.org site
| [Friday 27 August 2010] [06:36:23] <pieterh>    sorry, i need to catch a plane
| [Friday 27 August 2010] [06:36:27] <sustrik>    ok, cya
| [Friday 27 August 2010] [06:36:39] <pieterh>    the sane model is upfront agreements
| [Friday 27 August 2010] [06:36:51] <guido_g>    have a safe trip
| [Friday 27 August 2010] [06:36:53] <pieterh>    when you join a community you agree (once) about licensing your contributions
| [Friday 27 August 2010] [06:36:59] <pieterh>    thanks
| [Friday 27 August 2010] [06:37:06] <pieterh>    this is the problem with the mailing list
| [Friday 27 August 2010] [06:37:24] <pieterh>    you can fix it, but i'm repeating myself, by putting patches via a web site of some kind
| [Friday 27 August 2010] [06:37:38] <pieterh>    where you accept Terms of Use and IP Policy when you join
| [Friday 27 August 2010] [06:37:46] <pieterh>    cyal
| [Friday 27 August 2010] [09:01:32] <CIA-20> zeromq2: 03Martin Sustrik 07master * r56faac7 10/ src/zmq.cpp : zmq_poll returns prematurely even if infinite timeout is set - fixed - http://bit.ly/8XghUD
| [Friday 27 August 2010] [09:16:03] <keffo__>    any particular reason why the null delimiter between routinginfo and payload thinks it's size is 17?
| [Friday 27 August 2010] [09:16:20] <sustrik>    that's not a delimiter
| [Friday 27 August 2010] [09:16:24] <sustrik>    that's an identity
| [Friday 27 August 2010] [09:16:35] <sustrik>    if you don't set the identity yourself
| [Friday 27 August 2010] [09:16:39] <sustrik>    0mq generates one
| [Friday 27 August 2010] [09:16:52] <sustrik>    it's an UUID (in binary form) thus 16 bytes
| [Friday 27 August 2010] [09:17:12] <sustrik>    +binary zero at the beginning to distinguish it from user defined identities
| [Friday 27 August 2010] [09:17:20] <sustrik>    summa summarum 17 bytes
| [Friday 27 August 2010] [09:17:26] <keffo__>    ah makes sense
| [Friday 27 August 2010] [09:19:02] <mato>   sustrik: hmm, so a fd returned by ZMQ_FD can still become ready even if there are no events?
| [Friday 27 August 2010] [09:20:51] <sustrik>    well, there are events, such as "new connection established"
| [Friday 27 August 2010] [09:21:06] <sustrik>    but these don't map directly to pollin/pollout
| [Friday 27 August 2010] [09:21:12] <sustrik>    anyway, i've fixed it
| [Friday 27 August 2010] [09:21:35] <mato>   sure, but isn't that exposing an implementation detail to the api?
| [Friday 27 August 2010] [09:22:02] <sustrik>    if there was a workaround i would use it :(
| [Friday 27 August 2010] [09:22:15] <sustrik>    the whole ZMQ_FD thing is a hack
| [Friday 27 August 2010] [09:22:36] <sustrik>    0MQ socket should be a _real_ file descriptor
| [Friday 27 August 2010] [09:23:00] <mato>   yes, yes, but i'm talking about the current state of affairs, not the ideal state of affairs in five years time
| [Friday 27 August 2010] [09:23:17] <sustrik>    well, the current state of affairs looks like this
| [Friday 27 August 2010] [09:23:22] <sustrik>    i think you cannot really fix it
| [Friday 27 August 2010] [09:24:13] <mato>   isn't this because the fd returned by ZMQ_FD is zeromq's internal signalling fd?
| [Friday 27 August 2010] [09:24:18] <sustrik>    yes
| [Friday 27 August 2010] [09:24:49] <mato>   ok, and, hypothetical question, couldn't ZMQ_FD return a fd that only responds to a subset of the events (i.e. those exported to the API)
| [Friday 27 August 2010] [09:25:06] <sustrik>    how would you filter out the other events
| [Friday 27 August 2010] [09:25:09] <sustrik>    ?
| [Friday 27 August 2010] [09:25:47] <mato>   well, the naive idea is that ZMQ_FD actually *registers* a 2nd signalling fd internally
| [Friday 27 August 2010] [09:26:09] <mato>   and the signalling stuff only signals the events exported to the user on that fd
| [Friday 27 August 2010] [09:26:10] <sustrik>    then you have a synchronisation problem
| [Friday 27 August 2010] [09:26:27] <sustrik>    how to get two signal streams into sync
| [Friday 27 August 2010] [09:28:00] <mato>   right, because the signalling is also used for synchronization
| [Friday 27 August 2010] [09:28:06] <sustrik>    exactly
| [Friday 27 August 2010] [09:28:27] <sustrik>    on a different thread: how is submitting patches done on LKML?
| [Friday 27 August 2010] [09:28:37] <sustrik>    there doesn't seem to be explicit licensing mentioned
| [Friday 27 August 2010] [09:28:39] <mato>   ah, yes, i saw the discussion
| [Friday 27 August 2010] [09:28:41] <mato>   yes there is
| [Friday 27 August 2010] [09:28:55] <mato>   and i wrote an email about it at least once to the ml
| [Friday 27 August 2010] [09:29:22] <sustrik>    which one was that?
| [Friday 27 August 2010] [09:29:31] <mato>   email?
| [Friday 27 August 2010] [09:29:40]   * sustrik still has 200 unread emails in the inbox
| [Friday 27 August 2010] [09:29:42] <sustrik>    yes
| [Friday 27 August 2010] [09:30:29] <mato>   sustrik: see my replies to Pieter's  RFC: MQ Contributions, Copyrights and Control thread
| [Friday 27 August 2010] [09:30:42] <sustrik>    on the wiki?
| [Friday 27 August 2010] [09:30:44] <mato>   no
| [Friday 27 August 2010] [09:30:46] <mato>   on email
| [Friday 27 August 2010] [09:31:31] <sustrik>    "Apropos contributions, to ensure we don't run afoul of any licensing
| [Friday 27 August 2010] [09:31:31] <sustrik>    problems I think it would be useful to institute a "Certificate of Origin"
| [Friday 27 August 2010] [09:31:31] <sustrik>    policy using Signed-Off-By: tags in patches or Git commits, similar to what
| [Friday 27 August 2010] [09:31:31] <sustrik>    is done by the Linux kernel.
| [Friday 27 August 2010] [09:31:31] <sustrik>    "
| [Friday 27 August 2010] [09:31:37] <sustrik>    that's it?
| [Friday 27 August 2010] [09:31:59] <mato>   i also explain in another reply i think where the Linux guys explain that
| [Friday 27 August 2010] [09:32:05] <mato>   http://lxr.linux.no/#linux+v2.6.35/Documentation/SubmittingPatches
| [Friday 27 August 2010] [09:32:12] <mato>   see point 12) in that document
| [Friday 27 August 2010] [09:32:42] <mato>   basically the presence of Signed-Off-By: on a patch or Git commit indicates acceptance of the "Developer's Certificate of Origin"
| [Friday 27 August 2010] [09:33:12] <mato>   so, patches w/o a Signed-Off-By: cannot be applied (or discussed in fact, the sender should just be told to go read SubmittingPatches)
| [Friday 27 August 2010] [09:33:28] <mato>   the Signed-Off-By: tag(s) propagate from the patch into Git
| [Friday 27 August 2010] [09:33:37] <mato>   and are thus kept as history
| [Friday 27 August 2010] [09:34:07] <mato>   git also has direct support for Signed-Off-By
| [Friday 27 August 2010] [09:34:36] <sustrik>    how is the certificate bound to signed-off-by?
| [Friday 27 August 2010] [09:34:37] <mato>   by using -s on commits, or configuring your Git install/repo to automatically sign commits
| [Friday 27 August 2010] [09:34:53] <sustrik>    does the developer have to sign some agreement in advance?
| [Friday 27 August 2010] [09:34:58] <mato>   no
| [Friday 27 August 2010] [09:35:03] <mato>   why should they?
| [Friday 27 August 2010] [09:35:12] <mato>   *they* must add the Signed-Off-By
| [Friday 27 August 2010] [09:35:28] <mato>   if they add it, it states their agreement with the certificate
| [Friday 27 August 2010] [09:35:34] <mato>   i don't see the problem
| [Friday 27 August 2010] [09:35:43] <sustrik>    what's the legal procedure to infer that you've signed the certificate
| [Friday 27 August 2010] [09:35:51] <sustrik>    if you've filled up the signed-off-by?
| [Friday 27 August 2010] [09:36:02] <mato>   you don't "sign" the ceritifcate
| [Friday 27 August 2010] [09:36:43] <mato>   IANAL, but your adding of the Signed-off-by: states your intent of agreement with the ceritifcate since it's in the project policy (SubmittingPatches in this case)
| [Friday 27 August 2010] [09:37:04] <sustrik>    sounds pretty creaky from legal point of view
| [Friday 27 August 2010] [09:37:07] <sustrik>    IANAL myself
| [Friday 27 August 2010] [09:37:54] <mato>   well, it was explicitly introduced after the SCO affair IIRC
| [Friday 27 August 2010] [09:38:06] <mato>   so it must be "good enough" for Linux...
| [Friday 27 August 2010] [09:38:25] <sustrik>    presumably
| [Friday 27 August 2010] [09:38:45] <sustrik>    i just don't see the link between certificate and the signed-off-by field
| [Friday 27 August 2010] [09:38:54] <sustrik>    i can write a different certificate
| [Friday 27 August 2010] [09:39:11] <sustrik>    and say you agree with it if you fill in siged-off-by
| [Friday 27 August 2010] [09:39:28] <sustrik>    then i will claim linux for myself
| [Friday 27 August 2010] [09:39:30] <sustrik>    muahaha
| [Friday 27 August 2010] [09:40:34] <mato>   sustrik: well, if you're really worried, ask some of our lawyer friends for an opinion
| [Friday 27 August 2010] [09:40:59] <mato>   i see it as a much better alternative to the business of someone writing in email "Yes, that patch is submitted under MIT"
| [Friday 27 August 2010] [09:41:10] <mato>   there is of course no perfect alternative
| [Friday 27 August 2010] [09:41:23] <sustrik>    yes. it's much better
| [Friday 27 August 2010] [09:41:30] <mato>   unless you want to force people to go through silly click-through agreements (the legality of which is questionable anyway)
| [Friday 27 August 2010] [09:41:35] <sustrik>    but i simply don't understand how it works
| [Friday 27 August 2010] [09:41:49] <sustrik>    is it a contract between Linus Torvalds and the developer?
| [Friday 27 August 2010] [09:42:50] <sustrik>    who'e the authority to impose particular working of the certificate and accept the sing-off-by's?
| [Friday 27 August 2010] [09:42:55] <sustrik>    wording*
| [Friday 27 August 2010] [09:43:51] <mato>   http://kerneltrap.org/node/3180
| [Friday 27 August 2010] [09:44:03] <mato>   there is Linus' original request for discussion from 2004
| [Friday 27 August 2010] [09:44:51] <mato>   sustrik: anyway, what is your worry? that it's legally unenforceable?
| [Friday 27 August 2010] [09:45:33] <sustrik>    nope
| [Friday 27 August 2010] [09:46:04] <sustrik>    i'm just wondering about what pieter said that patch for GPL'd code is not necessarily a GPL code itself
| [Friday 27 August 2010] [09:46:44] <sustrik>    so that when you are submitting a patch you have to explcitly state that it's GPL
| [Friday 27 August 2010] [09:46:46] <sustrik>    or LGPL
| [Friday 27 August 2010] [09:46:48] <sustrik>    or whatever
| [Friday 27 August 2010] [09:47:06] <sustrik>    the sign-off-by afaics is only a tracking feature
| [Friday 27 August 2010] [09:47:33] <sustrik>    not meant to explicitly state what license the patch is submitted under
| [Friday 27 August 2010] [09:49:18] <sustrik>    to my naive understanding, sending the patch to the mailing list constitutes the act of "distribution"
| [Friday 27 August 2010] [09:49:25] <mato>   did you read the certificate?
| [Friday 27 August 2010] [09:49:33] <mato>   (d) I understand and agree that this project and the contribution 319            are public and that a record of the contribution (including all 320            personal information I submit with it, including my sign-off) is 321            maintained indefinitely and may be redistributed consistent with 322            this project or the open source license(s) involved.
| [Friday 27 August 2010] [09:49:47] <sustrik>    and?
| [Friday 27 August 2010] [09:50:15] <sustrik>    what i mean it doesn't even look to be a contract
| [Friday 27 August 2010] [09:50:24] <sustrik>    there's only one party involved
| [Friday 27 August 2010] [09:50:35] <sustrik>    that's kind of strange
| [Friday 27 August 2010] [09:51:35] <mato>   it's a compromise to lower the overhead of contributing
| [Friday 27 August 2010] [09:51:46] <mato>   if you want a legal opinion, ask a lawyer 
| [Friday 27 August 2010] [09:51:52] <sustrik>    shrug
| [Friday 27 August 2010] [09:52:17] <sustrik>    it's tracking system
| [Friday 27 August 2010] [09:52:25] <sustrik>    it's explicitly state in the preamble
| [Friday 27 August 2010] [09:52:35] <sustrik>    To improve tracking of who did what, ...
| [Friday 27 August 2010] [09:52:36] <mato>   feel free to suggest something better
| [Friday 27 August 2010] [09:52:45] <sustrik>    it's automatic IMO
| [Friday 27 August 2010] [09:52:47] <mato>   go and research how other sucessful projects do it
| [Friday 27 August 2010] [09:53:06] <sustrik>    patch of GPL'd work is a derivative work
| [Friday 27 August 2010] [09:53:19] <sustrik>    when you send it to the ML it's "distributed"
| [Friday 27 August 2010] [09:53:34] <sustrik>    so you are obliged to do it under the same license
| [Friday 27 August 2010] [09:53:35] <mato>   yes, but the point of signed-off-by is to track the original person claiming the right to distribute
| [Friday 27 August 2010] [09:53:42] <sustrik>    sure, that's ok
| [Friday 27 August 2010] [09:54:27] <sustrik>    what i was talking about was that pieter says the above reasoning doesn't apply
| [Friday 27 August 2010] [09:55:01] <mato>   shrug :)
| [Friday 27 August 2010] [09:55:04] <sustrik>    to my understanding linux relies on it and uses sign-off-by as an additional tracking measure
| [Friday 27 August 2010] [09:55:43] <mato>   it seems it's either that or signing over copyright explicitly
| [Friday 27 August 2010] [09:56:11] <sustrik>    yes
| [Friday 27 August 2010] [10:17:12] <sustrik>    GPLv2 says that modified versions, if released, must be licensed  to all third parties.
| [Friday 27 August 2010] [10:22:10] <guido_g>    sustrik: just tested the latest master version, poll still not working
| [Friday 27 August 2010] [10:24:50] <sustrik>    what happens?
| [Friday 27 August 2010] [10:25:02] <guido_g>    nothing on first req
| [Friday 27 August 2010] [10:25:25] <guido_g>    then it hangs sometimes after 2nd or 3rd message
| [Friday 27 August 2010] [10:25:41] <sustrik>    nothing = exits with 0
| [Friday 27 August 2010] [10:25:47] <guido_g>    going to put the debug output back into my test programs
| [Friday 27 August 2010] [10:25:57] <sustrik>    ?
| [Friday 27 August 2010] [10:26:01] <guido_g>    wait a second
| [Friday 27 August 2010] [10:26:59] <guido_g>    now poll does not return when a message has been sent
| [Friday 27 August 2010] [10:27:32] <sustrik>    hangs, right
| [Friday 27 August 2010] [10:27:55] <sustrik>    that's poll on the rep side of req/rep pair, right?
| [Friday 27 August 2010] [10:28:02] <guido_g>    these changes really should go into a branch
| [Friday 27 August 2010] [10:28:20] <guido_g>    yes, req -> xrep (with poll)
| [Friday 27 August 2010] [10:28:35] <guido_g>    code is http://github.com/guidog/cpp/blob/master/zmqcpp/receiver_poll.cpp
| [Friday 27 August 2010] [10:29:24] <sustrik>    let me try
| [Friday 27 August 2010] [10:36:20] <sustrik>    ok, reproduced
| [Friday 27 August 2010] [10:38:28] <guido_g>    ahh, good to know ,)
| [Friday 27 August 2010] [10:39:56] <cremes> is there any long term plan to add some behavioral testing to 0mq so we can quickly catch regressions?
| [Friday 27 August 2010] [10:40:41] <guido_g>    or better a short term one?
| [Friday 27 August 2010] [10:41:12] <mato>   cremes, guido_g: good point, i've also been thinking about this
| [Friday 27 August 2010] [10:42:11] <guido_g>    mato: while you're here: how do i get the stable (not fuxxed up) 2.0.8 from github w/o typing for an hour?
| [Friday 27 August 2010] [10:42:11] <mato>   i'm not a fan of the various TDD methodologies, but having at least a baseline "make test" that verifies that things more or less work would be a good start
| [Friday 27 August 2010] [10:42:27] <cremes> http://thechangelog.com/post/268009308/cspec-bdd-for-c
| [Friday 27 August 2010] [10:42:47] <mato>   guido_g: 1) clone the repo 2) git checkout v2.0.8 :)
| [Friday 27 August 2010] [10:43:10] <guido_g>    you can checkout a tag?
| [Friday 27 August 2010] [10:43:14] <mato>   sure you can
| [Friday 27 August 2010] [10:43:23] <cremes> guido_g: check the ML; i posted an answer to this 1 or 2 days ago
| [Friday 27 August 2010] [10:43:28]   * guido_g has some book to burn
| [Friday 27 August 2010] [10:43:31] <mato>   you can't easily base work off that tag w/o turning it into a branch, but that's a different issue
| [Friday 27 August 2010] [10:44:00] <guido_g>    going to check this git thing now...
| [Friday 27 August 2010] [10:44:08] <cremes> guido_g: here's a better answer...
| [Friday 27 August 2010] [10:44:09] <cremes> http://lists.zeromq.org/pipermail/zeromq-dev/2010-August/005526.html
| [Friday 27 August 2010] [10:44:17] <mato>   and git in fact will tell you straight away that if you want a local branch it's just git checkout -b <name> at that point
| [Friday 27 August 2010] [10:44:47] <cremes> mato: what are your thoughts on a set of regression tests?
| [Friday 27 August 2010] [10:45:02] <cremes> aside from 'make test'
| [Friday 27 August 2010] [10:45:15] <mato>   cremes: well, the major hurdle is that the system we're testing is distributed
| [Friday 27 August 2010] [10:45:30] <sustrik>    pretty hard to write sane tests
| [Friday 27 August 2010] [10:45:37] <mato>   yes and no
| [Friday 27 August 2010] [10:45:39] <sustrik>    some basic stuff can be done though
| [Friday 27 August 2010] [10:45:43] <guido_g>    why the *** hell is not mentioned those books...
| [Friday 27 August 2010] [10:45:51] <guido_g>    *is this
| [Friday 27 August 2010] [10:46:58] <mato>   tests can be written to use tcp over localhost
| [Friday 27 August 2010] [10:47:00] <mato>   or ipc
| [Friday 27 August 2010] [10:47:09] <mato>   and inproc separately since that is a different code path
| [Friday 27 August 2010] [10:47:23] <sustrik>    yes
| [Friday 27 August 2010] [10:47:23] <mato>   sustrik: in fact, we can have multiple contexts in a single process
| [Friday 27 August 2010] [10:47:37] <sustrik>    true
| [Friday 27 August 2010] [10:47:39] <mato>   so a test can even use multiple contexts if you need it
| [Friday 27 August 2010] [10:47:56] <mato>   basically you do all the "distributed" stuff using multiple threads
| [Friday 27 August 2010] [10:48:09] <sustrik>    the hard part is starting individual components in synchronised manner
| [Friday 27 August 2010] [10:48:21] <mato>   give me an example?
| [Friday 27 August 2010] [10:48:24] <sustrik>    it's often like:
| [Friday 27 August 2010] [10:48:28] <sustrik>    start component 1
| [Friday 27 August 2010] [10:48:35] <sustrik>    start component 2
| [Friday 27 August 2010] [10:48:46] <sustrik>    press any key at 1
| [Friday 27 August 2010] [10:48:47] <guido_g>    mato: any chance to write the git shuffle for a version into the README?
| [Friday 27 August 2010] [10:48:48] <sustrik>    etc.
| [Friday 27 August 2010] [10:49:26] <mato>   guido_g: well, until now the assumption was if you're wanting the stable release you don't work out of git
| [Friday 27 August 2010] [10:49:55] <guido_g>    ah ok
| [Friday 27 August 2010] [10:50:10] <mato>   guido_g: also, i'm still trying to get my head around what the best way to hold patches for a stable release in git actually is
| [Friday 27 August 2010] [10:50:14] <guido_g>    may i say that this assumption isn't a good one?
| [Friday 27 August 2010] [10:50:51] <mato>   well, ultimately, we can't teach people who want to use git how they should do that
| [Friday 27 August 2010] [10:50:52] <guido_g>    what about a maintenance branch?
| [Friday 27 August 2010] [10:51:35] <mato>   guido_g: yes, the plan is for a maintenance branch of some sort, but i've been spending the last day trying to understand what the best workflow for us (i.e. sustrik and myself) is
| [Friday 27 August 2010] [10:51:41] <mato>   please be patient :-)
| [Friday 27 August 2010] [10:52:00] <mato>   guido_g: anyhow, the tags are all there, for all past 2.0.x releases
| [Friday 27 August 2010] [10:52:04] <guido_g>    well, you should, 'cause these people are the user base (at least a significant part of)
| [Friday 27 August 2010] [10:52:35] <mato>   guido_g: sure, d'you have a git expert i can talk to ? :-)
| [Friday 27 August 2010] [10:52:49] <sustrik>    guido_g: are you running the code from trunk in production?
| [Friday 27 August 2010] [10:52:58] <guido_g>    mato: if i'd have, i'd talk to him myself first
| [Friday 27 August 2010] [10:53:19] <guido_g>    this is one big problem: limited understanding of the tool chain
| [Friday 27 August 2010] [10:53:35] <mato>   of course
| [Friday 27 August 2010] [10:54:02]   * guido_g is bought some books on git just for mq
| [Friday 27 August 2010] [10:54:14] <mato>   guido_g: anyhow, *any* code you're using in real production should come out of a release tarball in my opinon
| [Friday 27 August 2010] [10:54:25] <sustrik>    that's what i wanted to say
| [Friday 27 August 2010] [10:54:41] <sustrik>    it may work using a git for a while
| [Friday 27 August 2010] [10:54:48] <sustrik>    but in long run it's dangerous
| [Friday 27 August 2010] [10:55:15] <guido_g>    problem here is: mq is so young, that *important* fixes and updates are quite frequent
| [Friday 27 August 2010] [10:55:36] <guido_g>    tarballs are only available for official releases
| [Friday 27 August 2010] [10:55:39] <mato>   yes, which is what the maintenance branch is for, which i'm trying to define, etc etc :)
| [Friday 27 August 2010] [10:55:47] <guido_g>    between the two are huge gaps
| [Friday 27 August 2010] [10:56:10]   * mato wonders where he could find a git expert to talk to for a couple of hours
| [Friday 27 August 2010] [10:56:25] <sustrik>    mato: have you tried talking to martin hurton
| [Friday 27 August 2010] [10:56:44] <sustrik>    i don't know whether he's an expert but he's definitely with git longer than we are
| [Friday 27 August 2010] [10:57:11] <mato>   yeah, that's a good idea... or possibly asking for help on the Git mailing list/IRC
| [Friday 27 August 2010] [10:57:32] <mato>   the only problem with mailing lists/IRC is figuring out if the answers are any good :-)
| [Friday 27 August 2010] [10:57:40] <sustrik>    ha
| [Friday 27 August 2010] [10:57:45] <guido_g>    :)
| [Friday 27 August 2010] [10:58:34] <sustrik>    well, even if you define a viable process, there's still a question of who's going to work on the maintenance branch
| [Friday 27 August 2010] [10:58:44] <cremes> try asking on stack overflow
| [Friday 27 August 2010] [10:58:47] <sustrik>    backporting bugfixes is not much fun
| [Friday 27 August 2010] [10:59:03] <mato>   sustrik: the process i want to define forces the committer applying the fix to evaluate whether or not it also applies to the maint branch
| [Friday 27 August 2010] [10:59:13] <mato>   sustrik: it's the only viable way at the moment imo
| [Friday 27 August 2010] [10:59:56] <sustrik>    you mean that every contributor would have to post a diff for every maitenence branch?
| [Friday 27 August 2010] [10:59:59] <mato>   no
| [Friday 27 August 2010] [11:00:10] <mato>   the person integrating those changes is responsible
| [Friday 27 August 2010] [11:00:19] <sustrik>    for bakcporting?
| [Friday 27 August 2010] [11:00:25] <mato>   no
| [Friday 27 August 2010] [11:00:32] <mato>   the point is
| [Friday 27 August 2010] [11:00:45] <mato>   at the moment we have a bunch of changes which are common to stable and master
| [Friday 27 August 2010] [11:00:56] <mato>   so those changes should be merged verbatim into both
| [Friday 27 August 2010] [11:01:12] <mato>   now, about backporting
| [Friday 27 August 2010] [11:01:27] <mato>   this is entirely voluntary
| [Friday 27 August 2010] [11:01:52] <sustrik>    the above _is_ backporting, no?
| [Friday 27 August 2010] [11:02:02] <mato>   no
| [Friday 27 August 2010] [11:02:03] <sustrik>    "bunch of changes which are common to stable and master"
| [Friday 27 August 2010] [11:02:04] <guido_g>    backporting a feature should be the exception
| [Friday 27 August 2010] [11:02:07] <cremes> regarding git, this may help just a little bit
| [Friday 27 August 2010] [11:02:08] <cremes> http://tom.preston-werner.com/2009/05/19/the-git-parable.html
| [Friday 27 August 2010] [11:02:14] <sustrik>    i meant backporting the bugfixes
| [Friday 27 August 2010] [11:02:27] <mato>   sustrik: if the code has not diverged there is no concept of backporting
| [Friday 27 August 2010] [11:02:38] <mato>   sustrik: we do have a bunch of changes like that at the moment
| [Friday 27 August 2010] [11:02:44] <sustrik>    cremes: what's that?
| [Friday 27 August 2010] [11:02:54] <mato>   sustrik: e.g. the device stuff from jon dyte
| [Friday 27 August 2010] [11:03:23] <sustrik>    yes, it works as long as you don't get conflicts on merge
| [Friday 27 August 2010] [11:03:47] <mato>   if those conflicts are trivial to solve then there is no problem
| [Friday 27 August 2010] [11:04:09] <sustrik>    ok, i see what you mean
| [Friday 27 August 2010] [11:04:23] <sustrik>    sounds viable
| [Friday 27 August 2010] [11:04:23] <mato>   if they are not, then you are in a different situation
| [Friday 27 August 2010] [11:05:26] <guido_g>    i think the other way is much more important, a bug in stable has been fixed and this has to be incorporated into dev
| [Friday 27 August 2010] [11:05:42] <sustrik>    it's the same thing
| [Friday 27 August 2010] [11:05:54] <sustrik>    "bunch of changes which are common to stable and master"
| [Friday 27 August 2010] [11:06:04] <guido_g>    ok
| [Friday 27 August 2010] [11:06:12] <mato>   well, my view would be that the stable release is a volunteer effort
| [Friday 27 August 2010] [11:06:28] <guido_g>    elaborate
| [Friday 27 August 2010] [11:07:37] <mato>   what i mean by that is: if we get a fix for stable, it's our interest to merge it also into master if relevant
| [Friday 27 August 2010] [11:08:00] <mato>   however, i would expect most development to be concentrated on master
| [Friday 27 August 2010] [11:08:34] <mato>   and the backporting of fixes into stable from master to be minimal
| [Friday 27 August 2010] [11:08:50] <mato>   does that make sense?
| [Friday 27 August 2010] [11:08:55] <guido_g>    i figure you define "development" as developing new features in contrast to bug fixes
| [Friday 27 August 2010] [11:09:11] <mato>   no, not really
| [Friday 27 August 2010] [11:09:27] <guido_g>    then it doesn't make sense
| [Friday 27 August 2010] [11:09:39] <mato>   ok, let me put it this way
| [Friday 27 August 2010] [11:10:03] <mato>   the problem is that 2.1.x and 2.0.x have diverged due to large infrastructure changes
| [Friday 27 August 2010] [11:10:22] <mato>   1) if a fix is applicable trivially to both, no problem, it goes in both
| [Friday 27 August 2010] [11:10:32] <guido_g>    ok so far
| [Friday 27 August 2010] [11:10:44] <mato>   2) if not, someone has to make a decision on what effort needs to be spent
| [Friday 27 August 2010] [11:11:54] <mato>   sustrik would obviously want to concentrate on master
| [Friday 27 August 2010] [11:11:55] <guido_g>    in this case, backports shouldn't be done. stop.
| [Friday 27 August 2010] [11:12:02] <mato>   yes, pretty much
| [Friday 27 August 2010] [11:12:10] <mato>   that's what i was trying to say
| [Friday 27 August 2010] [11:12:28] <mato>   unless someone actually steps up to do the work, i won't stop them :)
| [Friday 27 August 2010] [11:12:33] <sustrik>    i think it a question of money flow
| [Friday 27 August 2010] [11:12:46] <mato>   (if it is a backport of a fix, obviously features don't get backported into stable. ever.)
| [Friday 27 August 2010] [11:13:00] <sustrik>    if support license business launches off
| [Friday 27 August 2010] [11:13:06] <sustrik>    it would obviously focus on stable
| [Friday 27 August 2010] [11:13:09] <sustrik>    not development
| [Friday 27 August 2010] [11:13:15] <guido_g>    mato: which is why there is a new version, so no problem
| [Friday 27 August 2010] [11:13:22] <mato>   guido_g: precisely
| [Friday 27 August 2010] [11:14:12] <mato>   sustrik: in that case a person from said business will step up to backport fixes
| [Friday 27 August 2010] [11:14:18] <sustrik>    exactly
| [Friday 27 August 2010] [11:14:23] <mato>   the point is, *anyone* can backport fixes if they want to
| [Friday 27 August 2010] [11:14:25] <sustrik>    and the said business is ourselves
| [Friday 27 August 2010] [11:14:38] <guido_g>    or adopt fixes from stable to master
| [Friday 27 August 2010] [11:14:41]   * mato does not have any support business :)
| [Friday 27 August 2010] [11:15:00] <sustrik>    the people on this list are probably those that can be hired to maintain the stable
| [Friday 27 August 2010] [11:15:16] <guido_g>    anyhow, a "stable" branch should be there
| [Friday 27 August 2010] [11:15:25] <mato>   sustrik: you're mixing money with community, different issues
| [Friday 27 August 2010] [11:15:28] <sustrik>    i mean, if a business wants stable to be supported, who are they going to hire?
| [Friday 27 August 2010] [11:15:38] <sustrik>    you
| [Friday 27 August 2010] [11:15:39] <sustrik>    me 
| [Friday 27 August 2010] [11:15:39] <guido_g>    did I hear hired? :)
| [Friday 27 August 2010] [11:15:41] <sustrik>    guido
| [Friday 27 August 2010] [11:16:02] <sustrik>    people from the community
| [Friday 27 August 2010] [11:16:24] <mato>   sustrik: it's still a different issue. the point is a stable branch can be there, fixes can flow into it, and releases will be made when someone has the motivation to do so
| [Friday 27 August 2010] [11:16:26] <sustrik>    eh, isn't that the right word?
| [Friday 27 August 2010] [11:16:35] <mato>   whether that motivation comes from being hired or not is irrelevant
| [Friday 27 August 2010] [11:17:04] <mato>   if the community (paid or not) has no interest in further stable releases of 2.0.x then there won't be any
| [Friday 27 August 2010] [11:17:06] <sustrik>    i'm just commenting on the fact that maintaining stable is not a fun job
| [Friday 27 August 2010] [11:17:15] <mato>   maintaining anything is not a fun job
| [Friday 27 August 2010] [11:17:27] <mato>   you can ignore all bug fixes that don't affect you
| [Friday 27 August 2010] [11:17:28] <guido_g>    what about the following: if dev has a fix, it is cut down and put aside as a commit into a branch, then _someone_ can get to this branch and try to apply the fixes to stable
| [Friday 27 August 2010] [11:17:39] <mato>   but then other people won't use your software :)
| [Friday 27 August 2010] [11:17:52] <guido_g>    full ack
| [Friday 27 August 2010] [11:18:18] <guido_g>    had a day of today and wanted to play with mq, instead i chased a bug...
| [Friday 27 August 2010] [11:18:34] <mato>   sustrik: the key point is to encourage contributions, to stable or not
| [Friday 27 August 2010] [11:18:39] <mato>   more people = more manpower
| [Friday 27 August 2010] [11:18:49] <sustrik>    sure
| [Friday 27 August 2010] [11:18:58] <mato>   = you find more people who are trustworthy, and you delegate to them 
| [Friday 27 August 2010] [11:19:05] <keffo__>    or a crappy tasting soup!
| [Friday 27 August 2010] [11:19:07] <guido_g>    unfortunately: more people -> needs more structure
| [Friday 27 August 2010] [11:19:08] <sustrik>    so guido_g today contributes as a tester :)
| [Friday 27 August 2010] [11:19:12] <mato>   precisely
| [Friday 27 August 2010] [11:19:20] <guido_g>    sustrik: *sigh*
| [Friday 27 August 2010] [11:19:42] <guido_g>    btw, just installed expect and going to use it for some tests scripts
| [Friday 27 August 2010] [11:20:27]   * sustrik is checking what expect is
| [Friday 27 August 2010] [11:20:28] <guido_g>    idea is to have small programs with defined output and using expect to verify it
| [Friday 27 August 2010] [11:21:32] <sustrik>    aha
| [Friday 27 August 2010] [11:21:46] <sustrik>    yes it would be good to put a test suite together
| [Friday 27 August 2010] [11:22:15] <guido_g>    and for devs a dependency like expect shouldn't be to hard to meet
| [Friday 27 August 2010] [11:22:42] <sustrik>    does it have to be a part of the build system?
| [Friday 27 August 2010] [11:23:03] <mato>   why use expect at all?
| [Friday 27 August 2010] [11:23:17] <mato>   the test programs themselves should either assert/abort or succeed
| [Friday 27 August 2010] [11:23:24] <mato>   no dependency required
| [Friday 27 August 2010] [11:23:29] <guido_g>    ok
| [Friday 27 August 2010] [11:23:56] <guido_g>    i'll rewrite my experiments (which uncoverd the poll issue) into one test program
| [Friday 27 August 2010] [11:24:15] <sustrik>    thanks
| [Friday 27 August 2010] [11:24:16] <mato>   sustrik: also, brian has a bunch of poll tests in the pyzmq repo
| [Friday 27 August 2010] [11:24:26] <mato>   sustrik: these could be trivially rewritten into c/c++ 
| [Friday 27 August 2010] [11:24:33] <sustrik>    ack
| [Friday 27 August 2010] [11:24:41] <sustrik>    but right now it exceeds my resources
| [Friday 27 August 2010] [11:24:43] <guido_g>    this is what i had in mind :)
| [Friday 27 August 2010] [11:25:44] <mato>   guido_g: take a look at the poll tests in pyzmq, it's what i had in mind
| [Friday 27 August 2010] [11:25:57] <guido_g>    guess what i'm doing atm? :)
| [Friday 27 August 2010] [11:26:02] <mato>   all that's needed is then figuring out the automake stuff to make a driver that runs the tests on "make test"
| [Friday 27 August 2010] [11:26:05] <mato>   i can do that
| [Friday 27 August 2010] [11:26:26] <mato>   it's just "run all of this stuff and error if any step asserts/aborts"
| [Friday 27 August 2010] [11:26:37] <mato>   which is automatic since the assert/abort will get you a non-zero exit status
| [Friday 27 August 2010] [11:27:04] <guido_g>    ack
| [Friday 27 August 2010] [11:27:37] <guido_g>    let me hack a simple test progam
| [Friday 27 August 2010] [11:55:51] <mato>   sustrik: guido_g: ok, i've figured out the automake stuff for tests
| [Friday 27 August 2010] [11:56:02] <guido_g>    oh oh
| [Friday 27 August 2010] [11:56:12]   * guido_g is scared by automake
| [Friday 27 August 2010] [11:56:25] <mato>   sure, which is why /me figured it out for you :)
| [Friday 27 August 2010] [11:56:41] <guido_g>    thx a lot then :)
| [Friday 27 August 2010] [11:56:46] <mato>   end result is, i have a tests/ directory, with a single test case in it
| [Friday 27 August 2010] [11:57:12] <mato>   and you can run "make check" which runs all the tests and prints a nice summary, complains which failed/passed, etc
| [Friday 27 August 2010] [11:57:37] <mato>   sustrik: a couple of questions
| [Friday 27 August 2010] [11:57:40] <sustrik>    yes?
| [Friday 27 August 2010] [11:57:48] <guido_g>    mato: ok
| [Friday 27 August 2010] [11:57:50] <mato>   sustrik: 1) the tests should be mostly C, not C++, right?
| [Friday 27 August 2010] [11:57:59] <mato>   sustrik: since the C API is our main deliverable
| [Friday 27 August 2010] [11:58:13] <mato>   sustrik: (there can of course be C++ tests in there, later)
| [Friday 27 August 2010] [11:58:37] <sustrik>    yes
| [Friday 27 August 2010] [11:59:01] <mato>   sustrik: then the only problem i have is this business of linking C against C++ runtime when --disable-shared is used
| [Friday 27 August 2010] [11:59:12] <sustrik>    but iirc you had a problem compiling c files anyway
| [Friday 27 August 2010] [11:59:17] <mato>   well, kind of
| [Friday 27 August 2010] [11:59:22] <sustrik>    that's why you changed the perf tests to .cpp
| [Friday 27 August 2010] [11:59:25] <mato>   yes
| [Friday 27 August 2010] [11:59:35] <mato>   this happens when you use --disable-shared
| [Friday 27 August 2010] [11:59:40] <sustrik>    i'm using it
| [Friday 27 August 2010] [11:59:44] <mato>   :)
| [Friday 27 August 2010] [11:59:49] <guido_g>    mato: if you would like to check the test_poll.cpp at http://github.com/guidog/cpp/tree/master/zmqcpp
| [Friday 27 August 2010] [12:00:42] <sustrik>    ha, i thougt it is a project called "GUI dog"
| [Friday 27 August 2010] [12:00:49] <sustrik>    now i see it's guido_g :)
| [Friday 27 August 2010] [12:00:58] <guido_g>    *sigh* :)
| [Friday 27 August 2010] [12:01:08] <mato>   guido_g: yeah, nice, that's kind of the idea i have
| [Friday 27 August 2010] [12:01:20] <guido_g>    good
| [Friday 27 August 2010] [12:01:31] <guido_g>    going to fill in some more tests now
| [Friday 27 August 2010] [12:01:38] <mato>   except i'm wondering whether test cases should be using just the C api
| [Friday 27 August 2010] [12:01:51] <mato>   or not... not sure if it matters
| [Friday 27 August 2010] [12:02:08] <guido_g>    the c++ api is the native one, right?
| [Friday 27 August 2010] [12:02:13] <mato>   no, the C API is
| [Friday 27 August 2010] [12:02:21] <sustrik>    C++ is a wrapper
| [Friday 27 August 2010] [12:02:24] <mato>   the C++ API is just a thin wrapper in zmq.hpp
| [Friday 27 August 2010] [12:02:37] <sustrik>    but it's distributed with the package so i don't really see a problem
| [Friday 27 August 2010] [12:02:44] <sustrik>    and using C++ api is much easier
| [Friday 27 August 2010] [12:02:46] <mato>   yeah, i guess not
| [Friday 27 August 2010] [12:02:50] <guido_g>    but the software is written in c++
| [Friday 27 August 2010] [12:02:56] <sustrik>    the exceptions just run out of main
| [Friday 27 August 2010] [12:03:03] <sustrik>    and cause fault
| [Friday 27 August 2010] [12:03:05] <mato>   yup
| [Friday 27 August 2010] [12:03:26] <mato>   guido_g: one minor point; independent tests should be independent programs
| [Friday 27 August 2010] [12:03:45] <mato>   in other words, in your program, test_pair() is basically main()
| [Friday 27 August 2010] [12:03:57] <mato>   the reason for this is "make check" will run all the tests
| [Friday 27 August 2010] [12:04:00] <guido_g>    ok, going to change that
| [Friday 27 August 2010] [12:04:01] <mato>   not just stop at the 1st one
| [Friday 27 August 2010] [12:04:20] <mato>   it'll then give you a nice pass/fail summary
| [Friday 27 August 2010] [12:04:32] <guido_g>    what is the grouping attribute? socket type? access type? moon phase?
| [Friday 27 August 2010] [12:05:04] <mato>   grouping? of tests?
| [Friday 27 August 2010] [12:05:55] <guido_g>    yes, because having programs for every permuation of socket type for every way to access it plus special cases would lead to an enormous amount of programs
| [Friday 27 August 2010] [12:06:29] <guido_g>    i'd say lets do it like: test_pair, test_reqrep, test_pushpull or so
| [Friday 27 August 2010] [12:06:56] <guido_g>    as a start
| [Friday 27 August 2010] [12:07:02] <CIA-20> zeromq2: 03Dhammika Pathirana 07master * r98dc118 10/ src/zmq_decoder.cpp : assert on malformed messages - http://bit.ly/a3XkbQ
| [Friday 27 August 2010] [12:07:06] <guido_g>    later we'll likely add tests for special cases
| [Friday 27 August 2010] [12:07:35] <guido_g>    going to rename test_poll.cpp to test_pair.cpp and see how far it goes
| [Friday 27 August 2010] [12:08:15] <sustrik>    i don't believe you will ever be able to devise a systematic naming for test programs
| [Friday 27 August 2010] [12:08:24] <mato>   i think start somewhere
| [Friday 27 August 2010] [12:08:34] <mato>   we can change things as we go along
| [Friday 27 August 2010] [12:08:44] <mato>   no big deal, they're just test programs
| [Friday 27 August 2010] [12:08:54] <mato>   sustrik: ok, i'm going to have to go to dinner soon
| [Friday 27 August 2010] [12:08:57] <mato>   what i can do
| [Friday 27 August 2010] [12:09:03] <guido_g>    but they have to be maintained!
| [Friday 27 August 2010] [12:09:07] <mato>   of course
| [Friday 27 August 2010] [12:09:21] <mato>   but if you don't maintain them you'll get shot pretty quickly since they'll stop working :)
| [Friday 27 August 2010] [12:09:38] <mato>   so, what i can do now, if you guys want to continue
| [Friday 27 August 2010] [12:09:46] <guido_g>    make test would make a niche pre-push hook :)
| [Friday 27 August 2010] [12:10:06] <mato>   guido_g: that is some way away, but yes, autobuilders and test is what we need
| [Friday 27 August 2010] [12:10:13] <mato>   so much to do :)
| [Friday 27 August 2010] [12:10:24] <guido_g>    as usual
| [Friday 27 August 2010] [12:10:44] <mato>   anyhow, i can push to master the framework that adds a test/ subdirectory with my one lone silly test in it (just creates and destroys a context)
| [Friday 27 August 2010] [12:11:02] <mato>   then you can start adding tests as you like
| [Friday 27 August 2010] [12:11:16] <mato>   does that sound like a plan?
| [Friday 27 August 2010] [12:11:17] <guido_g>    and i will move my test_*cpp into that dir on my local clone
| [Friday 27 August 2010] [12:11:25] <guido_g>    and see if it works
| [Friday 27 August 2010] [12:11:29] <mato>   yup yup
| [Friday 27 August 2010] [12:11:49] <guido_g>    if it does, i do what?
| [Friday 27 August 2010] [12:12:18] <mato>   sustrik: last question (i can choose here): should "make" build the tests or should they only be built if you also want to run them (with make check)
| [Friday 27 August 2010] [12:12:40] <mato>   sustrik: /me thinks 1st option is better for now
| [Friday 27 August 2010] [12:12:42] <sustrik>    build them immediately
| [Friday 27 August 2010] [12:12:53] <mato>   ok, but they'll only get run when you do "make check"
| [Friday 27 August 2010] [12:13:01] <sustrik>    sure
| [Friday 27 August 2010] [12:13:20] <sustrik>    ultimately they'll take several minutes to run
| [Friday 27 August 2010] [12:13:21] <mato>   guido_g: you send a patch with your contribution to the ml, stating it's under the MIT license, as usual and sustrik or myself can apply it
| [Friday 27 August 2010] [12:13:30] <sustrik>    so not by default please
| [Friday 27 August 2010] [12:13:37] <mato>   yes, but build by default
| [Friday 27 August 2010] [12:13:37] <mato>   ok
| [Friday 27 August 2010] [12:14:00] <guido_g>    may i use this nifty git email feature?
| [Friday 27 August 2010] [12:14:22] <mato>   indeed you may :) the only problem is how do you get the "this is under MIT license" into it?
| [Friday 27 August 2010] [12:14:34] <mato>   if you can do that, please do, but email to the list of course
| [Friday 27 August 2010] [12:14:46] <guido_g>    ok, i'll have a look then
| [Friday 27 August 2010] [12:15:11] <mato>   you could for now, if sustrik is happy, even just use git-email and then reply to your own email with "Patch is under the MIT license"
| [Friday 27 August 2010] [12:15:22] <mato>   assuming you can't figure out a way of getting git-email to do that
| [Friday 27 August 2010] [12:15:29] <guido_g>    otherwise i'll send the patches as attachments and state the license stuff in the main mail
| [Friday 27 August 2010] [12:15:34] <mato>   yup, thx
| [Friday 27 August 2010] [12:16:10] <mato>   the license stuff will hopefully go away soon, there's been an RFC out about dropping the MIT requiremenet, but this is for iMatix to decide
| [Friday 27 August 2010] [12:19:05]   * guido_g has no problem with that
| [Friday 27 August 2010] [12:41:27] <CIA-20> zeromq2: 03Martin Lucina 07master * r35cb1fa 10/ (Makefile.am configure.in tests/Makefile.am tests/simple.cpp): 
| [Friday 27 August 2010] [12:41:28] <CIA-20> zeromq2: Add a basic framework for a test suite
| [Friday 27 August 2010] [12:41:28] <CIA-20> zeromq2: The test suite uses the standard automake support. Tests are always built,
| [Friday 27 August 2010] [12:41:28] <CIA-20> zeromq2: but run only when you do a "make check". - http://bit.ly/8YwkAR
| [Friday 27 August 2010] [12:41:28] <CIA-20> zeromq2: 03Martin Lucina 07master * r0b76f23 10/ src/zmq_decoder.cpp : Merge branch 'master' of github.com:zeromq/zeromq2 - http://bit.ly/dt0av0
| [Friday 27 August 2010] [12:41:41] <mato>   sustrik: guido_g: ok, there you go
| [Friday 27 August 2010] [12:42:09] <mato>   for now all tests need to xyz.cpp even if you're using the C API
| [Friday 27 August 2010] [12:42:37] <mato>   to add a test, add it's source file to tests/, update tests/Makefile.am (should be self-explanatory)
| [Friday 27 August 2010] [12:42:46] <mato>   make check runs the tests
| [Friday 27 August 2010] [12:42:58] <mato>   have to go now, cyl
| [Friday 27 August 2010] [12:43:30] <guido_g>    ok, thx
| [Friday 27 August 2010] [12:43:33] <sustrik>    vya
| [Friday 27 August 2010] [12:43:35] <sustrik>    cya
| [Friday 27 August 2010] [12:45:34] <mems>   hey, I'm trying to work out if zeromq can do what I need for my application
| [Friday 27 August 2010] [12:46:01] <mems>   I have a server which manages a list of compute jobs
| [Friday 27 August 2010] [12:46:11] <mems>   then a variable number of worker nodes that get jobs from it
| [Friday 27 August 2010] [12:46:49] <mems>   and (because I'm new to zmq) I can't work out if with zmq I would have to have a polling based situation
| [Friday 27 August 2010] [12:48:06] <sustrik>    mems: the works will be load-balanced among workers?
| [Friday 27 August 2010] [12:48:30] <mems>   I'd like each worker to request a job from the server and then perform it
| [Friday 27 August 2010] [12:49:26] <mems>   I'm not completely familiar with the terminology here... dunno if that's what you'd regard as "load-balanced"
| [Friday 27 August 2010] [12:49:33] <sustrik>    so it's worker who plays the active role?
| [Friday 27 August 2010] [12:49:43] <sustrik>    i.e. decides to do some work
| [Friday 27 August 2010] [12:49:54] <mems>   that was my plan
| [Friday 27 August 2010] [12:50:07] <sustrik>    then create a REQ socket at each worker
| [Friday 27 August 2010] [12:50:19] <sustrik>    and a REP socket at the server
| [Friday 27 August 2010] [12:50:28] <sustrik>    it's classic client/server scenario
| [Friday 27 August 2010] [12:50:42] <mems>   and when the server's job queue is empty?
| [Friday 27 August 2010] [12:50:52] <mems>   (but will be full in the future)
| [Friday 27 August 2010] [12:50:56] <sustrik>    no jobs then :)
| [Friday 27 August 2010] [12:51:13] <mems>   but would the clients have to repeatedly poll the server in that situation?
| [Friday 27 August 2010] [12:51:19] <sustrik>    no
| [Friday 27 August 2010] [12:51:27] <sustrik>    they can idly wait for the work
| [Friday 27 August 2010] [12:52:00] <mems>   hmm... it would appear that I'm not sure what a REP and REQ socket are
| [Friday 27 August 2010] [12:52:07]   * mems noses deeper into the docs
| [Friday 27 August 2010] [12:52:42] <mems>   are there some API docs?
| [Friday 27 August 2010] [12:55:18] <sustrik>    manual pages
| [Friday 27 August 2010] [12:55:23] <sustrik>    man zmq
| [Friday 27 August 2010] [12:55:27] <mems>   yup. just found them, thanks :)
| [Friday 27 August 2010] [12:55:43] <sustrik>    also online here:
| [Friday 27 August 2010] [12:55:44] <sustrik>    http://api.zeromq.org/
| [Friday 27 August 2010] [12:56:58] <mems>   ok, so, to complicate matters, I have multiple types of worker that work on the jobs at different points in their lifetime
| [Friday 27 August 2010] [12:57:16] <mems>   so the request from the worker is more like "give me a job in state X"
| [Friday 27 August 2010] [12:57:50] <mems>   presumably this means that the server will need to be able to say "I don't have anything in that state at the moment"
| [Friday 27 August 2010] [13:00:03] <sustrik>    separate REP sockets in the server for separate kind of work then 
| [Friday 27 August 2010] [13:02:47] <mems>   hmm.  I'll have a play
| [Friday 27 August 2010] [13:10:56] <guido_g>    ha! first tests work
| [Friday 27 August 2010] [13:11:02] <sustrik>    :)
| [Friday 27 August 2010] [13:11:17] <guido_g>    now for the patch thing...
| [Friday 27 August 2010] [13:13:31] <mems>   is there a way of discovered from which client a message has come from?
| [Friday 27 August 2010] [13:13:37] <mems>   **discovering
| [Friday 27 August 2010] [13:14:03] <sustrik>    no unless you put that into the message itself
| [Friday 27 August 2010] [13:14:10] <ModusPwnens>    Hi
| [Friday 27 August 2010] [13:14:16] <sustrik>    hi
| [Friday 27 August 2010] [13:14:27] <ModusPwnens>    are you helping someone already?
| [Friday 27 August 2010] [13:14:27] <mems>   sustrik: this seems odd to me -- is this not a really common requirement?
| [Friday 27 August 2010] [13:14:39] <ModusPwnens>    mm, that answers my question
| [Friday 27 August 2010] [13:14:49] <sustrik>    :)
| [Friday 27 August 2010] [13:15:01] <sustrik>    it's the nature of the thing
| [Friday 27 August 2010] [13:15:23] <sustrik>    use 0mq where you want to communicate with a lot of homogenous peers
| [Friday 27 August 2010] [13:16:19] <sustrik>    if you want to treat each connection separately, use standard TCP sockets, that's what they are for
| [Friday 27 August 2010] [13:16:58] <mems>   mmm... but then one loses zmq's framing
| [Friday 27 August 2010] [13:17:08] <sustrik>    shrug
| [Friday 27 August 2010] [13:17:11] <mems>   hehe
| [Friday 27 August 2010] [13:17:17] <sustrik>    framing is easy
| [Friday 27 August 2010] [13:17:34] <sustrik>    write the size, then data
| [Friday 27 August 2010] [13:18:06] <sustrik>    0mq is a scalability solution
| [Friday 27 August 2010] [13:18:13] <mems>   ok
| [Friday 27 August 2010] [13:18:24] <sustrik>    thus it makes you communicate with an unknown number of peers
| [Friday 27 August 2010] [13:18:36] <sustrik>    that way you can add and remove processing nodes as you wish
| [Friday 27 August 2010] [13:18:48] <sustrik>    without tweaking your code
| [Friday 27 August 2010] [13:21:02] <mems>   ok.  I see what it's going for.
| [Friday 27 August 2010] [13:21:20] <mems>   one last question ;)
| [Friday 27 August 2010] [13:21:49] <mems>   if I have a bunch of sockets, can I block on getting a message from any one of them?
| [Friday 27 August 2010] [13:21:59] <mems>   (zmq sockets obviously)
| [Friday 27 August 2010] [13:22:03] <sustrik>    have a look at zmq_poll
| [Friday 27 August 2010] [13:22:15] <mems>   excellent
| [Friday 27 August 2010] [13:23:30] <guido_g>    when it works...  ]:->
| [Friday 27 August 2010] [13:24:00] <ModusPwnens>    oh guido is here too!
| [Friday 27 August 2010] [13:24:14] <guido_g>    yes
| [Friday 27 August 2010] [13:26:45] <ModusPwnens>    ok so, i was trying to do the throughput/latency tests that zeromq has in their install package, but for some reason the remote end doesnt think the address is valid
| [Friday 27 August 2010] [13:27:12] <ModusPwnens>    in the example, they use eth0 for the local end, but I don't think that identifier means anything in windows
| [Friday 27 August 2010] [13:28:24] <sustrik>    in windows you have no sane NIC names
| [Friday 27 August 2010] [13:28:28] <sustrik>    use an IP address
| [Friday 27 August 2010] [13:28:42] <sustrik>    guido_g: i think I've found the problem
| [Friday 27 August 2010] [13:28:57] <ModusPwnens>    Yeah, i tried that. I used the IPv4 address of the computer that the local test was running on
| [Friday 27 August 2010] [13:30:06] <guido_g>    sustrik: good, because with the current master the tests fail :)
| [Friday 27 August 2010] [13:30:36]   * guido_g will now build the patch
| [Friday 27 August 2010] [13:31:03] <guido_g>    ok, first coffee
| [Friday 27 August 2010] [13:38:51] <guido_g>    ahh... format-patch is nice
| [Friday 27 August 2010] [13:42:47] <keffo__>    finally, I got the routing working across two queues :)
| [Friday 27 August 2010] [13:50:05] <ModusPwnens>    so does anyone know whats going on with the test suite..?
| [Friday 27 August 2010] [13:51:17] <cremes> ModusPwnens: we just started chatting about it a few hours ago
| [Friday 27 August 2010] [13:54:41] <sustrik>    cremes: there's a testing infrastructure added to trunk
| [Friday 27 August 2010] [13:54:49] <sustrik>    no tests yet though
| [Friday 27 August 2010] [13:55:11] <cremes> good progress for a few hours work!
| [Friday 27 August 2010] [13:55:15] <sustrik>    'make check' will run them
| [Friday 27 August 2010] [13:55:48] <sustrik>    cremes: btw, the diagram we've made yesterday
| [Friday 27 August 2010] [13:55:55] <cremes> yes?
| [Friday 27 August 2010] [13:56:04] <sustrik>    what about changing the terminal nodes to REQ and REP
| [Friday 27 August 2010] [13:56:17] <sustrik>    that way it will show how all 4 socket types work
| [Friday 27 August 2010] [13:56:44] <ModusPwnens>    Really? what a coincidence..so what were you talking about regarding the test suite?
| [Friday 27 August 2010] [13:56:46] <cremes> sure
| [Friday 27 August 2010] [13:57:06] <cremes> since you have the source for the graphic, make the change and i'll update the text
| [Friday 27 August 2010] [13:57:11] <sustrik>    ok
| [Friday 27 August 2010] [13:57:25] <sustrik>    ModusPwnens: that it has to be done :)
| [Friday 27 August 2010] [13:57:43] <ModusPwnens>    but there is a test suite for zeromq already..
| [Friday 27 August 2010] [13:58:01] <ModusPwnens>    well at least for latency and throughput
| [Friday 27 August 2010] [13:59:16] <sustrik>    that are performace tests
| [Friday 27 August 2010] [13:59:26] <sustrik>    we were talking about functionality tests
| [Friday 27 August 2010] [13:59:54] <ModusPwnens>    Oh. I think there is a misunderstanding or something then. I'm just having trouble to get the performance tests running
| [Friday 27 August 2010] [14:00:29] <sustrik>    cremes: done
| [Friday 27 August 2010] [14:01:02] <sustrik>    Modus: paste you command lines here
| [Friday 27 August 2010] [14:01:10] <ModusPwnens>    k
| [Friday 27 August 2010] [14:02:01] <ModusPwnens>    on the local computer: local_thr.exe tcp://192.168.1.176:5555 1 100000
| [Friday 27 August 2010] [14:02:09] <ModusPwnens>    where the ipaddress used their is the ip address of that computer itself
| [Friday 27 August 2010] [14:02:13] <ModusPwnens>    there*
| [Friday 27 August 2010] [14:03:01] <sustrik>    and the remote?
| [Friday 27 August 2010] [14:03:37] <ModusPwnens>    well its the same thing except it uses remote_thr.exe
| [Friday 27 August 2010] [14:03:51] <sustrik>    what version are you using?
| [Friday 27 August 2010] [14:03:59] <ModusPwnens>    2.07
| [Friday 27 August 2010] [14:04:13] <sustrik>    does it hang?
| [Friday 27 August 2010] [14:05:40] <ModusPwnens>    yeah they seem to run but not do anything..and i changed it to 10 so that i wouldn't have to wait so long
| [Friday 27 August 2010] [14:06:24] <sustrik>    none of the two programs exits?
| [Friday 27 August 2010] [14:06:47] <ModusPwnens>    Nope.
| [Friday 27 August 2010] [14:07:23] <sustrik>    do they or do they not?
| [Friday 27 August 2010] [14:07:29] <ModusPwnens>    they don't
| [Friday 27 August 2010] [14:07:54] <sustrik>    that's pretty strange
| [Friday 27 August 2010] [14:08:04] <sustrik>    the remote at least should exit after 10 seconds
| [Friday 27 August 2010] [14:08:31] <sustrik>    can you get the backtrace from the remote, to show where it is hanging?
| [Friday 27 August 2010] [14:08:36] <ModusPwnens>    maybe something else is going on. the computer i've been using has been having a slew of other problems 
| [Friday 27 August 2010] [14:08:51] <ModusPwnens>    hmm, i will try that and get back to you
| [Friday 27 August 2010] [14:19:39] <cremes> sustrik: i have a different idea
| [Friday 27 August 2010] [14:20:05] <cremes> make a copy of the image as x2.png with req/rep as the terminal nodes and restore the original pic
| [Friday 27 August 2010] [14:20:22] <cremes> i'll write a separate paragraph explaining the new diagram
| [Friday 27 August 2010] [14:20:51] <sustrik>    ok, but i already overwrote the original pic
| [Friday 27 August 2010] [14:20:52] <cremes> i don't want to rewrite a bunch of the text but i have no problem adding another paragraph or two for a new config
| [Friday 27 August 2010] [14:21:00] <sustrik>    so x2 will be the original one
| [Friday 27 August 2010] [14:21:04] <cremes> fine, then make x2.png with xreq/xrep
| [Friday 27 August 2010] [14:24:30] <sustrik>    cremes: there you go
| [Friday 27 August 2010] [14:24:38] <cremes> thank you
| [Friday 27 August 2010] [14:29:03] <sustrik>    guido_g: testutil.hpp:36: error: extra ;
| [Friday 27 August 2010] [14:29:10] <sustrik>    i'll fix it
| [Friday 27 August 2010] [14:29:24] <sustrik>    namespaces should not be followed by ;
| [Friday 27 August 2010] [14:29:33] <sustrik>    c++ syntax is plain weird
| [Friday 27 August 2010] [14:30:13] <guido_g>    oh the mail is through :)
| [Friday 27 August 2010] [14:30:28] <guido_g>    compiled here
| [Friday 27 August 2010] [14:30:28] <sustrik>    was that a generated email?
| [Friday 27 August 2010] [14:30:56] <guido_g>    no, that would have involved things via imap
| [Friday 27 August 2010] [14:31:03] <sustrik>    ok
| [Friday 27 August 2010] [14:31:16] <guido_g>    just a format-patch as attachment
| [Friday 27 August 2010] [14:31:59] <guido_g>    sustrik: which compiler version should one use?
| [Friday 27 August 2010] [14:32:11] <sustrik>    guido_g: any
| [Friday 27 August 2010] [14:32:14] <sustrik>    the more the better
| [Friday 27 August 2010] [14:32:25] <guido_g>    ok
| [Friday 27 August 2010] [14:32:53] <sustrik>    it even compiles on icc or xlc etc.
| [Friday 27 August 2010] [14:33:32]   * guido_g has gcc 4.3 and 4.4 ready
| [Friday 27 August 2010] [14:33:57]   * sustrik is at 4.4.3
| [Friday 27 August 2010] [14:34:15] <guido_g>     c++ --version
| [Friday 27 August 2010] [14:34:15] <guido_g>    c++ (Debian 4.4.4-8) 4.4.5 20100728 (prerelease)
| [Friday 27 August 2010] [14:35:05] <guido_g>    ok, now that the process of sending patches is understood even by me, i'll produce some more
| [Friday 27 August 2010] [14:35:08] <sustrik>    anyway, the point is the more compilers the better so we catch all possible deviations from standard syntax
| [Friday 27 August 2010] [14:35:30] <guido_g>    i'll *not* try to compile mq on my n900... no way :)
| [Friday 27 August 2010] [14:36:02] <sustrik>    iirc someone already did :)
| [Friday 27 August 2010] [14:36:02] <guido_g>    sustrik: any other remarks on the patch?
| [Friday 27 August 2010] [14:36:35] <sustrik>    coding style... i'll fix that
| [Friday 27 August 2010] [14:36:38] <guido_g>    *sigh* would be nice, but given that maemo has been killed by nokia... waste of time
| [Friday 27 August 2010] [14:36:53] <guido_g>    ouch yes, i tend to forget such things
| [Friday 27 August 2010] [14:39:13] <sustrik>    one more thing:
| [Friday 27 August 2010] [14:39:18] <sustrik>    when including zmq.hpp
| [Friday 27 August 2010] [14:39:18] <guido_g>    is there a description of the wanted coding style?
| [Friday 27 August 2010] [14:39:30] <sustrik>    use #include "../include/zmq.hpp"
| [Friday 27 August 2010] [14:39:44] <sustrik>    the headers are not yet installed
| [Friday 27 August 2010] [14:39:53] <guido_g>    right
| [Friday 27 August 2010] [14:40:06] <sustrik>    so you can end up including old headers from the previously installed version
| [Friday 27 August 2010] [14:40:25] <guido_g>    yup, got it
| [Friday 27 August 2010] [14:40:39] <guido_g>    just copied the files over from my dev dir
| [Friday 27 August 2010] [14:40:48] <sustrik>    http://www.zeromq.org/docs:style
| [Friday 27 August 2010] [14:42:50] <guido_g>    ahh... 've been looking in the wrong place
| [Friday 27 August 2010] [14:52:28] <sustrik>    guido_g: i would say making the context global is not a good idea
| [Friday 27 August 2010] [14:52:38] <guido_g>    why?
| [Friday 27 August 2010] [14:52:44] <sustrik>    that way zmq_term gets called _after_ the return from main
| [Friday 27 August 2010] [14:52:49] <sustrik>    which is kind of strange
| [Friday 27 August 2010] [14:53:04] <guido_g>    ok, i'll move it into main then
| [Friday 27 August 2010] [14:53:09] <sustrik>    i'll do it
| [Friday 27 August 2010] [14:53:12] <sustrik>    just commenting
| [Friday 27 August 2010] [14:53:17] <guido_g>    as you wish :)
| [Friday 27 August 2010] [14:53:39] <guido_g>    don't do too much
| [Friday 27 August 2010] [14:53:53] <guido_g>    i already have more changes here
| [Friday 27 August 2010] [14:54:11] <guido_g>    actually making the things work and such :)
| [Friday 27 August 2010] [14:54:31] <sustrik>    wait a sec!
| [Friday 27 August 2010] [14:54:45] <guido_g>    no problem
| [Friday 27 August 2010] [14:54:49] <sustrik>    i am reformatting it so it'll be pain in the ass to merge it
| [Friday 27 August 2010] [14:55:16] <guido_g>    no merges planned
| [Friday 27 August 2010] [14:55:27] <guido_g>    only plain typing to get used to the coding style
| [Friday 27 August 2010] [14:56:00] <sustrik>    ok
| [Friday 27 August 2010] [14:56:35] <sustrik>    using assert without including <assert.h>
| [Friday 27 August 2010] [14:56:43] <sustrik>    that may fail on some platforms
| [Friday 27 August 2010] [14:57:11] <guido_g>    did i say that my last exposure to c++ was roughly 10 years ago? 
| [Friday 27 August 2010] [14:57:31] <sustrik>    i'm not complaining
| [Friday 27 August 2010] [14:57:37] <guido_g>    i really need to re-learn a lot as it seems
| [Friday 27 August 2010] [14:57:40] <sustrik>    just commenting so that you are aware of it
| [Friday 27 August 2010] [14:57:45] <guido_g>    thx
| [Friday 27 August 2010] [14:58:22] <guido_g>    i completely forgot what i wanted to do today...
| [Friday 27 August 2010] [14:58:34] <sustrik>    :o)
| [Friday 27 August 2010] [15:01:32] <sustrik>    why are you including iostream?
| [Friday 27 August 2010] [15:01:45] <sustrik>    it doesn't look to be used anywhere
| [Friday 27 August 2010] [15:01:47] <guido_g>    i tested the thing using cout
| [Friday 27 August 2010] [15:01:55] <sustrik>    ack
| [Friday 27 August 2010] [15:07:21] <sustrik>    ============================================
| [Friday 27 August 2010] [15:07:21] <sustrik>    2 of 3 tests failed
| [Friday 27 August 2010] [15:07:21] <sustrik>    Please report to zeromq-dev@lists.zeromq.org
| [Friday 27 August 2010] [15:07:21] <sustrik>    ============================================
| [Friday 27 August 2010] [15:07:25] <sustrik>    woohoo!
| [Friday 27 August 2010] [15:09:24] <guido_g>    yeah, it's the broken poll
| [Friday 27 August 2010] [15:11:15] <sustrik>    guido: do you want this address attached to the patch:
| [Friday 27 August 2010] [15:11:16] <sustrik>    zmq@a-nugget.de
| [Friday 27 August 2010] [15:11:22] <sustrik>    ?
| [Friday 27 August 2010] [15:11:37] <sustrik>    guido_g
| [Friday 27 August 2010] [15:11:51] <guido_g>    it's ok with me
| [Friday 27 August 2010] [15:13:55] <guido_g>    at least, i did something useful today :)
| [Friday 27 August 2010] [15:14:18] <CIA-20> zeromq2: 03Guido Goldstein 07master * r4d9b046 10/ (6 files in 2 dirs): two tests added - http://bit.ly/cIptEz
| [Friday 27 August 2010] [15:14:28] <sustrik>    great, done
| [Friday 27 August 2010] [15:14:38] <sustrik>    thanks for that!
| [Friday 27 August 2010] [15:14:42] <guido_g>    cool, i'll pull and have a look
| [Friday 27 August 2010] [15:14:53] <guido_g>    you're welcome
| [Friday 27 August 2010] [15:27:03] <guido_g>    i'll send the fixes i have so you have some working tests
| [Friday 27 August 2010] [15:27:35] <guido_g>    more tests should be written once we have a working poll again
| [Friday 27 August 2010] [15:27:38] <guido_g>    is that ok?
| [Friday 27 August 2010] [15:36:31] <guido_g>    so the fixes are out
| [Friday 27 August 2010] [15:36:48]   * guido_g is going to have a break
| [Friday 27 August 2010] [15:41:27] <sustrik>    guido_g: sure, it's ok
| [Friday 27 August 2010] [15:41:28] <sustrik>    thanks
| [Friday 27 August 2010] [15:47:32] <mato>   back for a bit
| [Friday 27 August 2010] [15:47:42] <mato>   guido_g: good to see the test framework is useful
| [Friday 27 August 2010] [15:50:22] <guido_g>    mato: it sure is
| [Friday 27 August 2010] [15:50:46] <mato>   i'll look  at your tests over the weekend, kind of late now
| [Friday 27 August 2010] [15:50:49] <guido_g>    we have 2 tests for now
| [Friday 27 August 2010] [15:50:56] <mato>   but the general feel is good
| [Friday 27 August 2010] [15:51:14] <mato>   i think there will be some general guidelines we'll want to write for people contributing test cases
| [Friday 27 August 2010] [15:51:18] <guido_g>    they're just testing the basics of req/reqp and pair incl. poll
| [Friday 27 August 2010] [15:51:25] <mato>   sure, it's a start, that's good!
| [Friday 27 August 2010] [15:51:32] <guido_g>    ack
| [Friday 27 August 2010] [15:51:50] <guido_g>    i'll write more after poll is back on master
| [Friday 27 August 2010] [15:57:26] <guido_g>    i'm off too, good night all
| [Friday 27 August 2010] [15:57:37] <mato>   good night guido_g
| [Friday 27 August 2010] [16:41:18] <cremes> under what circumstances should i expect to see this error?  Assertion failed: false (object.cpp:342)
| [Friday 27 August 2010] [16:41:26] <cremes> this is on 2.0.8
| [Friday 27 August 2010] [16:42:01] <cremes> i *think* it is happening when a socket is blocked on recv and i call zmq_close() on the sockets
| [Friday 27 August 2010] [16:52:54] <cremes> obviously, i am calling zmq_close on those sockets from another thread :)
| [Friday 27 August 2010] [16:54:32] <mato>   there you go then :-)
| [Friday 27 August 2010] [17:49:19] <tyler_> trying to compile with the bundled pgm (./configure  --with-pgm && make) results in an error in both 2.0.7 and 2.0.8 source distributions
| [Friday 27 August 2010] [17:49:24] <tyler_> /usr/bin/ld: .libs/libzmq_la-txwi.o: relocation R_X86_64_PC32 against `pgm_rs_create' can not be used when making a shared object; recompile with -fPIC
| [Friday 27 August 2010] [17:49:25] <tyler_> /usr/bin/ld: final link failed: Bad value
| [Friday 27 August 2010] [17:49:37] <tyler_> any help would be appreciated
| [Friday 27 August 2010] [17:54:05] <mato>   tyler_: you're on redhat ?
| [Friday 27 August 2010] [17:54:15] <tyler_> centos 5.4
| [Friday 27 August 2010] [17:54:20] <mato>   thought so
| [Friday 27 August 2010] [17:54:26] <mato>   see this thread:
| [Friday 27 August 2010] [17:54:30] <mato>   http://thread.gmane.org/gmane.network.zeromq.devel/1667/focus=1670
| [Friday 27 August 2010] [17:55:00] <mato>   specifically:
| [Friday 27 August 2010] [17:55:04] <mato>   Just quickly check altering this line in src/Makefile,
| [Friday 27 August 2010] [17:55:05] <mato>   -DPGM_GNUC_INTERNAL=G_GNUC_INTERNAL \
| [Friday 27 August 2010] [17:55:05] <mato>   to
| [Friday 27 August 2010] [17:55:06] <mato>   -DPGM_GNUC_INTERNAL= \
| [Friday 27 August 2010] [17:55:32] <mato>   try that, the problem should go away
| [Friday 27 August 2010] [17:57:00] <tyler_> that did the trick, thank you!
| [Friday 27 August 2010] [17:57:39] <mato>   tyler_: no problem... as far as i can see it's a redhat 5.4 issue only with their gcc
| [Saturday 28 August 2010] [00:31:51] <CIA-20>   zeromq2: 03Guido Goldstein 07master * r67aa788 10/ (tests/test_pair.cpp tests/test_reqrep.cpp tests/testutil.hpp): Fixed socket states in tests - http://bit.ly/cC6CA7
| [Saturday 28 August 2010] [02:45:23] <CIA-20>   zeromq2: 03Martin Sustrik 07master * r035c937 10/ src/zmq.cpp : zmq_poll: account for the fact that ZMQ_FD is edge-triggered - http://bit.ly/9RVhvI
| [Saturday 28 August 2010] [02:45:23] <CIA-20>   zeromq2: 03Martin Sustrik 07master * r92923cd 10/ (4 files in 2 dirs): bug in pipe deactivation fixed - http://bit.ly/azqLvw
| [Saturday 28 August 2010] [04:35:48] <guido_g>  oh ich checked things in while i was dreaming...
| [Saturday 28 August 2010] [04:35:55] <guido_g>  thanks
| [Saturday 28 August 2010] [05:04:33] <sustrik_> np
| [Saturday 28 August 2010] [05:05:01] <sustrik_> pieterh: i think people are starting to have problems with navigating through zeromq.org
| [Saturday 28 August 2010] [05:05:11] <guido_g>  i'm going to change the tests so that all transports are tested
| [Saturday 28 August 2010] [05:05:12] <sustrik_> there's too much content and too little structure
| [Saturday 28 August 2010] [05:05:28] <sustrik_> guido_g: great
| [Saturday 28 August 2010] [05:05:36] <sustrik_> btw, i've fixed the poll bug
| [Saturday 28 August 2010] [05:05:44] <guido_g>  greater!
| [Saturday 28 August 2010] [05:05:44] <sustrik_> but there are other bugs still lurking around
| [Saturday 28 August 2010] [05:06:12] <sustrik_> it'll take couple of days to make the trunk reasonable stable
| [Saturday 28 August 2010] [05:06:28] <guido_g>  what about some output from the tests, so one can actually see which test failed on which transport?
| [Saturday 28 August 2010] [05:06:40] <sustrik_> it works that way
| [Saturday 28 August 2010] [05:06:54] <sustrik_> i see the assert
| [Saturday 28 August 2010] [05:06:56] <guido_g>  the asserts are a little sparse i think
| [Saturday 28 August 2010] [05:07:10] <sustrik_> it leads you directly to the test program failed
| [Saturday 28 August 2010] [05:07:17] <sustrik_> and to the right line number
| [Saturday 28 August 2010] [05:07:24] <sustrik_> which is pretty good
| [Saturday 28 August 2010] [05:07:42] <guido_g>  yes, but imagine the tests are run 3 times each with a different transport
| [Saturday 28 August 2010] [05:07:53] <guido_g>  you don't know wich transport failed
| [Saturday 28 August 2010] [05:08:08] <guido_g>  it's the same code line
| [Saturday 28 August 2010] [05:08:14] <sustrik_> hm, what about putting the test body itself into a common header file
| [Saturday 28 August 2010] [05:08:23] <sustrik_> and having multiple mains to use it?
| [Saturday 28 August 2010] [05:08:51] <guido_g>  we're approaching a test framework... :/
| [Saturday 28 August 2010] [05:09:08] <guido_g>  for the simple tests that are in the repo now, this will work fine
| [Saturday 28 August 2010] [05:09:22] <sustrik_> i, as a developer, have a single requirement:
| [Saturday 28 August 2010] [05:09:39] <sustrik_> 'make check' should report which executable had failed
| [Saturday 28 August 2010] [05:09:47] <sustrik_> then i can run it myself and debug it
| [Saturday 28 August 2010] [05:09:59] <guido_g>  ok
| [Saturday 28 August 2010] [05:11:14] <guido_g>  as i said yesterday, maintainting lots of test programs will not make it easier
| [Saturday 28 August 2010] [05:11:46] <sustrik_> the nice thing about test programs is they are self-maintaining
| [Saturday 28 August 2010] [05:12:00] <sustrik_> in the sense that if you break them your tests faile
| [Saturday 28 August 2010] [05:12:05] <sustrik_> => you have to fix it
| [Saturday 28 August 2010] [05:12:44] <guido_g>  yes, but if you see 20 programs fails, it's easyier to comment them out in the makefile
| [Saturday 28 August 2010] [05:12:56] <guido_g>  i've seen that in practice, so...
| [Saturday 28 August 2010] [05:13:07] <sustrik_> yuck
| [Saturday 28 August 2010] [05:13:12] <guido_g>  ack
| [Saturday 28 August 2010] [05:13:18] <sustrik_> tests should _not_ fail
| [Saturday 28 August 2010] [05:13:56] <sustrik_> tests should be a whip to drive the developers towards perfect code :)
| [Saturday 28 August 2010] [05:14:09] <sustrik_> commenting tests out makes them useless
| [Saturday 28 August 2010] [05:14:25] <guido_g>  still it has been done
| [Saturday 28 August 2010] [05:14:34] <sustrik_> no doubt
| [Saturday 28 August 2010] [05:14:37] <guido_g>  and it hasnt been a hobby project
| [Saturday 28 August 2010] [05:14:46] <guido_g>  anyway
| [Saturday 28 August 2010] [05:15:02] <guido_g>  going to make the tests transport aware
| [Saturday 28 August 2010] [05:15:09] <sustrik_> ack
| [Saturday 28 August 2010] [05:17:51] <guido_g>  you added an assert(false) after the return in test_pair, why?
| [Saturday 28 August 2010] [05:18:44] <sustrik_> uh
| [Saturday 28 August 2010] [05:18:48] <sustrik_> sorry
| [Saturday 28 August 2010] [05:18:56] <guido_g>  ok, i'll remove it then
| [Saturday 28 August 2010] [05:19:01] <sustrik_> yes, please
| [Saturday 28 August 2010] [05:19:06] <sustrik_> i'll fix it in the git
| [Saturday 28 August 2010] [05:19:40] <guido_g>  dont't, i'll change the files anyway
| [Saturday 28 August 2010] [05:19:44] <sustrik_> ok
| [Saturday 28 August 2010] [05:36:47] <guido_g>  sustrik_: http://gist.github.com/554955 this is what i've in mind, comments please
| [Saturday 28 August 2010] [06:19:43] <sustrik_> guido_g: looks fine
| [Saturday 28 August 2010] [06:20:07] <sustrik_> i would however prefer to have the main split into three different mains
| [Saturday 28 August 2010] [06:20:26] <sustrik_> it's not that much work, mostly copy-and-paste
| [Saturday 28 August 2010] [06:20:36] <sustrik_> and it's helpful for debugging
| [Saturday 28 August 2010] [06:20:54] <sustrik_> i.e. you can debug only the use case that fails
| [Saturday 28 August 2010] [06:21:05] <sustrik_> rather than having to run the whole batch
| [Saturday 28 August 2010] [06:42:28] <guido_g>  ok, i'll do it
| [Saturday 28 August 2010] [06:50:52] <mato> hi guys
| [Saturday 28 August 2010] [06:51:03] <guido_g>  hi mato 
| [Saturday 28 August 2010] [06:51:36] <guido_g>  PASS: simple
| [Saturday 28 August 2010] [06:51:36] <guido_g>  PASS: test_reqrep
| [Saturday 28 August 2010] [06:51:36] <guido_g>  PASS: test_pair_inproc
| [Saturday 28 August 2010] [06:51:36] <guido_g>  PASS: test_pair_ipc
| [Saturday 28 August 2010] [06:51:36] <guido_g>  ==================
| [Saturday 28 August 2010] [06:51:41] <guido_g>  All 4 tests passed
| [Saturday 28 August 2010] [06:51:43] <guido_g>  ==================
| [Saturday 28 August 2010] [06:51:44] <mato> yay
| [Saturday 28 August 2010] [06:51:45] <guido_g>  ha! :)
| [Saturday 28 August 2010] [06:51:46] <mato> good stuff :-)
| [Saturday 28 August 2010] [06:51:58] <mato> sustrik has good points about the test programs
| [Saturday 28 August 2010] [06:52:02] <mato> i like it
| [Saturday 28 August 2010] [06:52:10] <guido_g>  going to do it his way
| [Saturday 28 August 2010] [06:52:19] <mato> it's the right way :-)
| [Saturday 28 August 2010] [06:52:28] <guido_g>  by definition ,)
| [Saturday 28 August 2010] [06:52:31] <mato> indeed
| [Saturday 28 August 2010] [06:53:02] <guido_g>  don't be mad at me, i'm going to remove the simple.cpp from the tests
| [Saturday 28 August 2010] [06:53:23] <mato> guido_g: hey, it's just a placeholder
| [Saturday 28 August 2010] [06:53:43] <mato> feel free to take it out, but people could use it as a template maybe?
| [Saturday 28 August 2010] [06:54:08] <guido_g>  the other tests are as small
| [Saturday 28 August 2010] [06:54:26] <guido_g>  and do show how to handle the naming and stuff
| [Saturday 28 August 2010] [06:54:34] <mato> sure, go for it
| [Saturday 28 August 2010] [06:54:49] <mato> i just added something so you had a test to start with
| [Saturday 28 August 2010] [07:27:08] <CIA-20>   zeromq2: 03Martin Sustrik 07master * r42000d2 10/ (7 files): terminology unified: revive->activate - http://bit.ly/cg8yex
| [Saturday 28 August 2010] [07:27:10] <CIA-20>   zeromq2: 03Martin Sustrik 07master * rd90b407 10/ (src/pipe.cpp src/pipe.hpp): refactoring of pipe/swap interaction - http://bit.ly/bwmYWY
| [Saturday 28 August 2010] [07:27:11] <CIA-20>   zeromq2: 03Martin Sustrik 07master * rd8b975f 10/ (7 files): msg_store_t renamed to swap_t - http://bit.ly/cHT1MH
| [Saturday 28 August 2010] [07:27:11] <CIA-20>   zeromq2: 03Martin Sustrik 07master * rbeea535 10/ (src/config.hpp src/swap.cpp src/swap.hpp): swap's block size made into a compile-time parameter - http://bit.ly/9fAL4u
| [Saturday 28 August 2010] [07:27:13] <CIA-20>   zeromq2: 03Martin Sustrik 07master * r6ec783e 10/ (6 files): prefix_tree_t renamed to trie_t - http://bit.ly/bVnAyB
| [Saturday 28 August 2010] [07:35:43] <sustrik_> mato: btw, the problem in zmq_poll was with the fact that ZMQ_FD is edge triggered
| [Saturday 28 August 2010] [07:45:47] <mato> sustrik_: please elaborate....
| [Saturday 28 August 2010] [07:46:26] <sustrik_> some messages may have already been delivered to the socket
| [Saturday 28 August 2010] [07:46:32] <sustrik_> waiting to be received
| [Saturday 28 August 2010] [07:46:47] <sustrik_> if that's the case ZMQ_FD won't signal
| [Saturday 28 August 2010] [07:47:03] <sustrik_> so you have to check events first
| [Saturday 28 August 2010] [07:47:07] <sustrik_> then poll
| [Saturday 28 August 2010] [07:47:23] <sustrik_> otherwise poll may block even though there are messages available
| [Saturday 28 August 2010] [07:47:44] <sustrik_> i've already fixed it, please, do review
| [Saturday 28 August 2010] [07:48:24] <sustrik_> guido_g:
| [Saturday 28 August 2010] [07:48:25] <sustrik_> cc1plus: warnings being treated as errors
| [Saturday 28 August 2010] [07:48:25] <sustrik_> test_pair_inproc.cpp:25: error: TEST_NAME defined but not used
| [Saturday 28 August 2010] [07:48:53] <mato> i'll review it soonish, fighting some client panic here
| [Saturday 28 August 2010] [07:49:29] <sustrik_> ok
| [Saturday 28 August 2010] [07:58:34] <CIA-20>   zeromq2: 03Guido Goldstein 07master * r0a8473d 10/ (11 files): Added tests for transports per socket - http://bit.ly/c9dA8c
| [Saturday 28 August 2010] [08:04:15] <guido_g>  ok, i'll remember that
| [Saturday 28 August 2010] [08:07:35] <CIA-20>   zeromq2: 03Martin Sustrik 07master * r68d62cf 10/ builds/msvc/libzmq/libzmq.vcproj : MSVC build fixed - http://bit.ly/aut9jg
| [Saturday 28 August 2010] [08:09:56] <sustrik>  re
| [Saturday 28 August 2010] [08:10:50] <guido_g>  wb
| [Saturday 28 August 2010] [08:11:14] <sustrik>  i've commited your latest tests
| [Saturday 28 August 2010] [08:11:24] <guido_g>  yes, thx
| [Saturday 28 August 2010] [08:11:26] <sustrik>  all seem to pass on my box
| [Saturday 28 August 2010] [08:11:32] <guido_g>  here too
| [Saturday 28 August 2010] [08:15:51] <guido_g>  but one of the other test programs segfaults now in poll
| [Saturday 28 August 2010] [08:22:29] <sustrik>  guido_g: which other test?
| [Saturday 28 August 2010] [08:22:48] <sustrik>  mato: there's one problem with the new connection with the same identity
| [Saturday 28 August 2010] [08:22:50] <guido_g>  the program i discovered the poll bug in yesterday
| [Saturday 28 August 2010] [08:23:04] <sustrik>  ah, the one with the timeout?
| [Saturday 28 August 2010] [08:23:10] <mato> sustrik: are the two assertions i'm seeing the same issue?
| [Saturday 28 August 2010] [08:23:20] <sustrik>  mato: can be
| [Saturday 28 August 2010] [08:23:24] <mato> sustrik: one on the receiving end, and one on the connecting end?
| [Saturday 28 August 2010] [08:23:30] <sustrik>  quite possible
| [Saturday 28 August 2010] [08:23:34] <mato> sustrik: would seem to make sense from the behaviour i'm seeing
| [Saturday 28 August 2010] [08:23:50] <sustrik>  anyway, when fixing it
| [Saturday 28 August 2010] [08:23:51] <guido_g>  sustrik: no, poll w/o timeout but threads
| [Saturday 28 August 2010] [08:24:12] <sustrik>  you have to drop one of the connections
| [Saturday 28 August 2010] [08:24:19] <sustrik>  if you drop the new one
| [Saturday 28 August 2010] [08:24:42] <sustrik>  you have no way to force hanged connection to go away
| [Saturday 28 August 2010] [08:24:48] <sustrik>  it you drop the old one
| [Saturday 28 August 2010] [08:25:10] <sustrik>  two clients with same identities create a busy loop of connecting & dropping
| [Saturday 28 August 2010] [08:25:16] <mato> hang on
| [Saturday 28 August 2010] [08:25:21] <sustrik>  guido_g: can you pass the test?
| [Saturday 28 August 2010] [08:25:29] <mato> sustrik: the thing is, it's the same client
| [Saturday 28 August 2010] [08:25:41] <sustrik>  oh
| [Saturday 28 August 2010] [08:25:49] <mato> sustrik: the client is *not* being restarted
| [Saturday 28 August 2010] [08:26:05] <sustrik>  server is restarted?
| [Saturday 28 August 2010] [08:26:06] <guido_g>  http://github.com/guidog/cpp/tree/master/zmqcpp/ <- using the zmqcpp program with the sender program gives segfault in poll according to ltrace
| [Saturday 28 August 2010] [08:26:16] <sustrik>  guido_g: thx
| [Saturday 28 August 2010] [08:26:48] <mato> no, nothing is restarted
| [Saturday 28 August 2010] [08:27:09] <guido_g>  sustrik: using mq master from just before your msvc commit
| [Saturday 28 August 2010] [08:27:17] <sustrik>  mato: so what do you do?
| [Saturday 28 August 2010] [08:27:25] <sustrik>  guido_g: ok
| [Saturday 28 August 2010] [08:27:37] <mato> sustrik: i don't know if i can discuss it here :(
| [Saturday 28 August 2010] [08:27:55] <guido_g>  i'll close my eyes then :)
| [Saturday 28 August 2010] [09:31:14] <sustrik>  pieter_hitnjens: are you there?
| [Saturday 28 August 2010] [09:46:34] <speedy1>  hey guys, does 0mq work well when compiled for x64 arch on windows, visual studio 2008 SP1?
| [Saturday 28 August 2010] [09:48:03] <speedy1>  compilation goes through but gives lots of warnings like
| [Saturday 28 August 2010] [09:48:04] <speedy1>  1>..\..\..\src\zmq_engine.cpp(97) : warning C4267: 'argument' : conversion from 'size_t' to 'int', possible loss of data
| [Saturday 28 August 2010] [09:48:58] <speedy1>  on line insize = tcp_socket.read (inpos, insize);
| [Saturday 28 August 2010] [09:49:05] <speedy1>  zmq_engine.cpp
| [Saturday 28 August 2010] [09:50:02] <speedy1>  for example this is conversion betwenn unsigned and signed int
| [Saturday 28 August 2010] [09:53:58] <speedy1>  and it looks like it would work ok
| [Saturday 28 August 2010] [09:54:24] <speedy1>  but it's kinda bad coding style to mix unsigned and signed ints like that
| [Saturday 28 August 2010] [09:59:02] <sustrik>  speed1: i don't have a win64 box
| [Saturday 28 August 2010] [09:59:12] <sustrik>  feel free to submit a patch
| [Saturday 28 August 2010] [10:01:27] <speedy1>  ok, can I submit it to you?
| [Saturday 28 August 2010] [10:02:14] <guido_g>  who's the moderator of the ml? the last patch mail seems to be to big :/
| [Saturday 28 August 2010] [10:03:12]     * guido_g stupid
| [Saturday 28 August 2010] [10:03:19] <guido_g>  added generated file to pacht
| [Saturday 28 August 2010] [10:03:23] <guido_g>  *patch
| [Saturday 28 August 2010] [10:05:11] <sustrik>  guido_g: i've already allowed itr
| [Saturday 28 August 2010] [10:05:18] <guido_g>  oh thx
| [Saturday 28 August 2010] [10:05:35] <sustrik>  sppedy1: just generate the patch and send it to the mailing lis
| [Saturday 28 August 2010] [10:05:36] <sustrik>  list
| [Saturday 28 August 2010] [10:05:53] <sustrik>  stating it's submitted under MIT license
| [Saturday 28 August 2010] [10:06:04] <guido_g>  stay below 40kb :=)
| [Saturday 28 August 2010] [10:06:14] <speedy1>  :)
| [Saturday 28 August 2010] [10:06:35] <speedy1>  do you have an open SVN repository?
| [Saturday 28 August 2010] [10:07:34] <speedy1>  ah its git - ok
| [Saturday 28 August 2010] [10:07:38] <sustrik>  it's git repo
| [Saturday 28 August 2010] [10:07:43] <guido_g>  it's on github http://github.com/zeromq/zeromq2
| [Saturday 28 August 2010] [10:34:58] <speedy1>  yo keffo :)
| [Saturday 28 August 2010] [11:24:58] <keffo>    yoyo! :)
| [Saturday 28 August 2010] [14:19:01] <pieter_hintjens>  martin_sutsirk: yo!
| [Saturday 28 August 2010] [15:31:50] <keffo>    rawr, I calc pi :)
| [Saturday 28 August 2010] [15:55:03] <keffo>    ah, this is so coool!
| [Saturday 28 August 2010] [16:04:58] <andrewvc> Question, what's the recommended way to stop a thread blocked on recv?
| [Saturday 28 August 2010] [16:06:03] <andrewvc> or are you just not supposed to do that?
| [Saturday 28 August 2010] [16:19:45] <pieter_hintjens>  andrewvc: stop all threads by killing context
| [Saturday 28 August 2010] [16:19:49] <pieter_hintjens>  stop one thread by sending it a message
| [Saturday 28 August 2010] [16:21:30] <pieter_hintjens>  what this means in practice, I think, is using a second control socket and zmq_poll rather than zmq_recv
| [Saturday 28 August 2010] [16:21:36] <andrewvc> gotcha, interesting
| [Saturday 28 August 2010] [16:21:58]     * pieter_hintjens thinks there will emerge frameworks over 0mq that do this kind of thing automatically
| [Saturday 28 August 2010] [16:22:03] <pieter_hintjens>  reactors are one example
| [Saturday 28 August 2010] [16:23:21] <andrewvc> thanks pieter, I'l definitely look into that
| [Saturday 28 August 2010] [16:27:53] <KBrock>   Anyone know just how sensitive to cancelation slot zmq is internally?  I.e. after a reset_pollout, will zmq deal with data that comes in unexpectedly ok or will it get pissy?
| [Saturday 28 August 2010] [16:28:19] <KBrock>   *slop
| [Saturday 28 August 2010] [16:32:50] <pieter_hintjens>  KBrock: polling does not affect message arrival processing
| [Saturday 28 August 2010] [16:33:06] <pieter_hintjens>  only signaling to calling app
| [Saturday 28 August 2010] [16:33:35] <KBrock>   Well, I'm working on the IOCP stuff, worried about some of the internal behavior.
| [Saturday 28 August 2010] [16:33:54]     * pieter_hintjens hits his knowledge barrier
| [Saturday 28 August 2010] [16:34:04] <KBrock>   IOCP doesn't work even vaguely like kevent/epoll. :)
| [Saturday 28 August 2010] [16:34:04] <pieter_hintjens>  you'll have to ask Sustrik
| [Saturday 28 August 2010] [16:34:29] <KBrock>   Well, going to give it a try.  Suspect I'll get fireworks.
| [Saturday 28 August 2010] [16:34:51] <pieter_hintjens>  i suspect the closer you can emulate kevent/epoll the better
| [Saturday 28 August 2010] [16:35:06] <pieter_hintjens>  but having never used IOCP that is just unfounded opinion :-)
| [Saturday 28 August 2010] [16:35:14] <KBrock>   Yup, but canceling things is nasty under IOCP. :(
| [Saturday 28 August 2010] [16:35:33] <pieter_hintjens>  how so?
| [Saturday 28 August 2010] [16:36:13] <KBrock>   Well, you actually perform the recv/send "first" and then wait for success on the port.  Instead of kevent/epoll where you wait for available buffer space on the socket.
| [Saturday 28 August 2010] [16:36:33] <pieter_hintjens>  right, i'm reading about iocp now...
| [Saturday 28 August 2010] [16:37:10] <KBrock>   I'm going to try the slow way and request 0 byte read/writes and just monitor for activity but it's still not a very comparable thing.
| [Saturday 28 August 2010] [16:37:24] <pieter_hintjens>  you're using this to do inproc: or to do kevent/epoll?
| [Saturday 28 August 2010] [16:37:32] <pieter_hintjens>  sorry
| [Saturday 28 August 2010] [16:37:34] <pieter_hintjens>  ipc:
| [Saturday 28 August 2010] [16:37:37] <KBrock>   I'm just throwing this together really quick and stupid to see what a proper version will require.
| [Saturday 28 August 2010] [16:38:12] <pieter_hintjens>  good... luck...
| [Saturday 28 August 2010] [16:38:13] <KBrock>   sockets/pipes only right now.
| [Saturday 28 August 2010] [16:38:15] <pieter_hintjens>  :-)
| [Saturday 28 August 2010] [16:39:13] <KBrock>   Yeah, it's unfortunate that Winblows has to be such a pain in the ass sometimes.  Not to mention that's the platform I'm paid to work on. :)
| [Saturday 28 August 2010] [16:42:28] <KBrock>   Hate when things work the first time.. :)
| [Saturday 28 August 2010] [17:15:10] <KBrock>   Anyone have a copy of the head branch available for a code comparison check?
| [Saturday 28 August 2010] [17:15:49] <KBrock>   socket_base.cpp line 162 looks like the comparison is supposed to be "==" ?
| [Saturday 28 August 2010] [18:23:38] <CIA-20>   pyzmq: 03Brian Granger 07master * r6633c5d 10/ (zmq/_zmq.c zmq/_zmq.pyx): Added comment about PyEval_InitThreads(). - http://bit.ly/b42OTG
| [Saturday 28 August 2010] [18:44:01] <CIA-20>   pyzmq: 03Brian Granger 07master * r42a1472 10/ README.rst : Updating README.rst with build info for Windows and Linux. - http://bit.ly/dbBzus
| [Saturday 28 August 2010] [21:15:35] <manveru>  does anybody have an example of using 0mq with tcl?
| [Saturday 28 August 2010] [21:16:06] <manveru>  i saw tcl support in some announcement, but haven't found any code...
| [Saturday 28 August 2010] [21:26:54] <manveru>  not even a mention in the repo...
| [Saturday 28 August 2010] [21:27:07] <manveru>  nowhere in the history
| [Saturday 28 August 2010] [21:31:04] <manveru>  hm, ok... seems like all bindings where removed
| [Saturday 28 August 2010] [21:31:29] <manveru>  but there is no reference to a tcl binding on zeromq.org
| [Saturday 28 August 2010] [21:32:05] <manveru>  so it just... disappeared?
| [Sunday 29 August 2010] [04:21:08] <sustrik>    manveru: there was a tcl binding for 0MQ/1.0
| [Sunday 29 August 2010] [04:21:46] <manveru>    sustrik: yeah, i linked it above
| [Sunday 29 August 2010] [04:22:10] <sustrik>    ah, i must have missed that
| [Sunday 29 August 2010] [04:22:26] <sustrik>    you may want to update it to match 0MQ/2 API
| [Sunday 29 August 2010] [04:22:51] <manveru>    i've never written any C...
| [Sunday 29 August 2010] [04:23:19] <sustrik>    a nice way to try it :)
| [Sunday 29 August 2010] [04:23:39] <sustrik>    looking at the code it looks pretty trivial
| [Sunday 29 August 2010] [04:23:40] <sustrik>    http://github.com/zeromq/zeromq1/blob/master/libtclzmq/zmq.c
| [Sunday 29 August 2010] [04:24:03] <sustrik>    basically just converting Tcp types to C types and vice versa
| [Sunday 29 August 2010] [04:24:14] <sustrik>    Tcl*
| [Sunday 29 August 2010] [04:44:10] <guido_g>    good morning
| [Sunday 29 August 2010] [05:49:54] <pieter_hintjens>    guido_g: good morning! :-)
| [Sunday 29 August 2010] [05:52:25] <guido_g>    hi pieter_hintjens 
| [Sunday 29 August 2010] [05:52:43] <guido_g>    hope you had a good trip
| [Sunday 29 August 2010] [05:53:03] <pieter_hintjens>    RyanAir... brutally minimalistic, cheap, fast
| [Sunday 29 August 2010] [05:54:42] <guido_g>    but still seats and not standing places, right? :)
| [Sunday 29 August 2010] [05:55:25] <pieter_hintjens>    :-) that was a weird plan they had... though it makes sense for short hops
| [Sunday 29 August 2010] [05:56:08] <guido_g>    ok
| [Sunday 29 August 2010] [05:56:42]   * guido_g ment this as a joke...
| [Sunday 29 August 2010] [05:57:16] <guido_g>    anyway
| [Sunday 29 August 2010] [05:57:25] <pieter_hintjens>    http://www.thestar.com/news/world/article/831562--ryanair-looking-at-standing-seats-pay-toilets
| [Sunday 29 August 2010] [05:58:18] <pieter_hintjens>    manveru: I've added a Tcl bindings page and linked to the old 0MQ/1.0 binding
| [Sunday 29 August 2010] [05:58:38] <guido_g>    argh...
| [Sunday 29 August 2010] [05:59:00] <pieter_hintjens>    someone who knows Tcl and C will spend a happy evening making this work
| [Sunday 29 August 2010] [07:18:36] <rbraley>    https://code.google.com/p/pubsubhubbub/wiki/Hubs probably a good source of publicity for 0MQ if someone makes a 0MQ interface to pubsubhubbub as they have with RabbitMQ. Also, is there a wish list managed somewhere to post such suggestions?
| [Sunday 29 August 2010] [08:14:29] <pieter_hintjens>    rbraley: you might want to add the idea to the Labs page, that's the closest to a wishlist for things like bridges
| [Sunday 29 August 2010] [08:45:42] <manveru>    pieter_hintjens: thank you
| [Sunday 29 August 2010] [08:46:07] <pieter_hintjens>    manveru: np, let's see if this provokes someone to do it
| [Sunday 29 August 2010] [08:46:17] <pieter_hintjens>    i'd try myself but never used tcl
| [Sunday 29 August 2010] [08:46:33] <manveru>    heh
| [Sunday 29 August 2010] [08:46:52] <manveru>    i'm not really that good with tcl myself yet... and i've never done C
| [Sunday 29 August 2010] [08:47:27] <pieter_hintjens>    you might want to contact the original author and see if he wants to upgrade it
| [Sunday 29 August 2010] [08:48:57] <pieter_hintjens>    http://github.com/inbox/new/malosek
| [Sunday 29 August 2010] [08:53:34] <sustrik>    it was brett cameron, malosek just cheked it in
| [Sunday 29 August 2010] [09:02:41] <gebi>   hi all :)
| [Sunday 29 August 2010] [09:21:16] <pieter_hintjens>    sustrik: good to know... I'll ping Brett then
| [Sunday 29 August 2010] [09:22:42] <pieter_hintjens>    OK, done...
| [Sunday 29 August 2010] [12:22:34] <sustrik>    @igrigorik: 0mq has the highest ratio of great code/features to poor marketing/docs/clarity, I've seen in a while. (name included)
| [Sunday 29 August 2010] [12:23:08] <sustrik>    the guy is right that's extremely hard to find content on zeromq.org
| [Sunday 29 August 2010] [13:29:36] <pieter_hintjens>    sustrik: it's not hard to improve the website, but what do we do about the name?
| [Sunday 29 August 2010] [14:22:51] <sustrik>    nothing can be done about the name
| [Sunday 29 August 2010] [14:22:59] <sustrik>    but we can improve the site
| [Sunday 29 August 2010] [14:23:25] <sustrik>    it's just too chaotic right now
| [Sunday 29 August 2010] [14:24:24] <sustrik>    first time visitor needs say 3 links, instead there's something like 50 on the front page
| [Sunday 29 August 2010] [14:28:00] <jond>   hi martin
| [Sunday 29 August 2010] [14:28:26] <sustrik>    jond: jon dyte?
| [Sunday 29 August 2010] [14:28:35] <jond>   yep
| [Sunday 29 August 2010] [14:28:37] <sustrik>    hi
| [Sunday 29 August 2010] [14:28:54] <jond>   finally got to grips with this chat stuff
| [Sunday 29 August 2010] [14:29:09] <sustrik>    :)
| [Sunday 29 August 2010] [14:29:12] <sustrik>    how it's going?
| [Sunday 29 August 2010] [14:29:29] <jond>   i think the page needs some stuff removing, it's very noisy these days.
| [Sunday 29 August 2010] [14:29:46] <sustrik>    yes, that's my impression as well
| [Sunday 29 August 2010] [14:29:57] <pieter_hintjens>    feel free to suggest what to remove and/or click edit
| [Sunday 29 August 2010] [14:30:00] <pieter_hintjens>    it's a wiki :-)
| [Sunday 29 August 2010] [14:30:18] <sustrik>    i've had a look at it as if i was a newbie, and i was just confused
| [Sunday 29 August 2010] [14:30:29] <sustrik>    let me see...
| [Sunday 29 August 2010] [14:30:33] <jond>   havent been doing much coding , but did find an issue with prefix tree
| [Sunday 29 August 2010] [14:30:41] <pieter_hintjens>    the color scheme does not help, bright red links are painful
| [Sunday 29 August 2010] [14:30:51] <sustrik>    jond: seen your patch
| [Sunday 29 August 2010] [14:30:58] <sustrik>    i'll have a look at it tomorrow
| [Sunday 29 August 2010] [14:31:28] <jond>   i think the font, logo are great.
| [Sunday 29 August 2010] [14:31:41] <sustrik>    i like the design myself
| [Sunday 29 August 2010] [14:31:51] <sustrik>    the problem is rather with usability
| [Sunday 29 August 2010] [14:32:04] <sustrik>    especially for new people
| [Sunday 29 August 2010] [14:32:07] <jond>   personally I liked 'destroy any network' from back in the day.
| [Sunday 29 August 2010] [14:32:31] <sustrik>    that was pieter's text :)
| [Sunday 29 August 2010] [14:32:34] <pieter_hintjens>    sustrik: what new visitors want is pretty obvious
| [Sunday 29 August 2010] [14:32:41] <pieter_hintjens>    huge Download button
| [Sunday 29 August 2010] [14:32:52] <pieter_hintjens>    all the rest is for returning visitors
| [Sunday 29 August 2010] [14:32:56] <sustrik>    nope
| [Sunday 29 August 2010] [14:33:10] <sustrik>    new visitor is not going to download immediately
| [Sunday 29 August 2010] [14:33:23] <sustrik>    first he wants to know what is the whole thing about
| [Sunday 29 August 2010] [14:33:30] <jond>   FWIW I think the blog bit, user comments are taking up too much real estate.
| [Sunday 29 August 2010] [14:33:32] <pieter_hintjens>    that's what you assume
| [Sunday 29 August 2010] [14:33:41] <pieter_hintjens>    jond: yeah
| [Sunday 29 August 2010] [14:33:46] <sustrik>    have a look at google analytics
| [Sunday 29 August 2010] [14:33:54] <sustrik>    content pane
| [Sunday 29 August 2010] [14:33:55] <pieter_hintjens>    i keep removing them and keep getting asked to put them back
| [Sunday 29 August 2010] [14:34:10] <pieter_hintjens>    well
| [Sunday 29 August 2010] [14:34:20] <jond>   the languages list is too long 'others' should suffice for some
| [Sunday 29 August 2010] [14:34:21] <pieter_hintjens>    what I *like* about the current site
| [Sunday 29 August 2010] [14:34:33] <pieter_hintjens>    is that it's a navigation panel for the 0MQ community
| [Sunday 29 August 2010] [14:34:35] <pieter_hintjens>    more or less
| [Sunday 29 August 2010] [14:34:51] <sustrik>    that's the problem i think
| [Sunday 29 August 2010] [14:35:05] <sustrik>    most of the people cominf to the site are not community
| [Sunday 29 August 2010] [14:35:20] <pieter_hintjens>    sustrik: sunday evening... :-/
| [Sunday 29 August 2010] [14:35:22] <pieter_hintjens>    i'm coding
| [Sunday 29 August 2010] [14:35:23] <sustrik>    we get some 800 hits per day
| [Sunday 29 August 2010] [14:35:34] <pieter_hintjens>    not really into this topic now, can we discuss tomorrow at the office?
| [Sunday 29 August 2010] [14:35:34] <jond>   for returning users don't we need a dev.zeromq.org seperate url?
| [Sunday 29 August 2010] [14:35:46] <pieter_hintjens>    jond: two sites?
| [Sunday 29 August 2010] [14:35:47] <sustrik>    pieter: you are in BA?
| [Sunday 29 August 2010] [14:36:01] <pieter_hintjens>    sustrik: yes, from 2.30pm or so
| [Sunday 29 August 2010] [14:36:07] <sustrik>    ah, good
| [Sunday 29 August 2010] [14:36:27] <sustrik>    jond: what i had in mind is that main site must be compreensible for a random visitor
| [Sunday 29 August 2010] [14:36:30] <pieter_hintjens>    wikis are always busy
| [Sunday 29 August 2010] [14:36:41] <pieter_hintjens>    sustrik: there are no "random" visitors....
| [Sunday 29 August 2010] [14:36:42] <sustrik>    as these account for say 90% of the traffic
| [Sunday 29 August 2010] [14:36:48] <jond>   ph: yes, I've been wondering whether we need a dev and users maling list as well
| [Sunday 29 August 2010] [14:36:49] <pieter_hintjens>    almost everyone comes via a recommendation
| [Sunday 29 August 2010] [14:36:54] <sustrik>    i mean "non community" visitors
| [Sunday 29 August 2010] [14:37:04] <pieter_hintjens>    jond: yes, but later, is our feeling 
| [Sunday 29 August 2010] [14:37:21] <pieter_hintjens>    sustrik: almost everyone comes because they've read a blog or a twitter comment 
| [Sunday 29 August 2010] [14:37:24] <pieter_hintjens>    they want to try it
| [Sunday 29 August 2010] [14:37:29] <pieter_hintjens>    that is my assumption
| [Sunday 29 August 2010] [14:37:33] <sustrik>    exactly
| [Sunday 29 August 2010] [14:37:39] <jond>   if you are marketing a product then the front site needs to be clear and pretty stable
| [Sunday 29 August 2010] [14:37:41] <sustrik>    they want to try it
| [Sunday 29 August 2010] [14:38:04] <pieter_hintjens>    jond: it's an open source community, more than a product
| [Sunday 29 August 2010] [14:38:10] <sustrik>    they are not really intrested in dev stuff
| [Sunday 29 August 2010] [14:38:11] <jond>   the wiki aspect makes it a bit of a free for all, which is fine on the dev side
| [Sunday 29 August 2010] [14:38:17] <pieter_hintjens>    well
| [Sunday 29 August 2010] [14:38:20] <pieter_hintjens>    we're guessing
| [Sunday 29 August 2010] [14:38:25] <pieter_hintjens>    this is pointless, it can go on for years
| [Sunday 29 August 2010] [14:38:29] <sustrik>    that can be placed one click away
| [Sunday 29 August 2010] [14:38:40] <sustrik>    have a look at analytics
| [Sunday 29 August 2010] [14:38:44] <pieter_hintjens>    we need to actually get feedback from those newbies who apparently get lost
| [Sunday 29 August 2010] [14:38:50] <jond>   i don't make that distinction, free software or not it's still a product and the brand needs managing
| [Sunday 29 August 2010] [14:38:56] <pieter_hintjens>    one twitter comment does not make a study
| [Sunday 29 August 2010] [14:39:08] <pieter_hintjens>    jond: yes, the brand is the community
| [Sunday 29 August 2010] [14:39:19] <sustrik>    have a look what pages people are looking at
| [Sunday 29 August 2010] [14:40:06] <jond>   ph: that could be construed as negative though, but i'm no marketing expert
| [Sunday 29 August 2010] [14:40:18] <sustrik>    "cookbook"
| [Sunday 29 August 2010] [14:40:39] <pieter_hintjens>    jond: 0MQ is first and foremost meant to be attractive to engineers, not managers
| [Sunday 29 August 2010] [14:40:49] <pieter_hintjens>    here is an example of another community site: http://community.wikidot.com/
| [Sunday 29 August 2010] [14:41:01] <pieter_hintjens>    it handles 1,000's of newbies every day
| [Sunday 29 August 2010] [14:41:28] <sustrik>    the guy comes to the site, reads the one paragraph introduction on the main page and wants to see a piece of code
| [Sunday 29 August 2010] [14:41:41] <pieter_hintjens>    trying to keep the sparse look and a single page is a problem
| [Sunday 29 August 2010] [14:41:42] <sustrik>    he checks the code and if it looks reasonable clicks on download
| [Sunday 29 August 2010] [14:41:43] <jond>   ph: that might be a hard sell on a place with 10 yr old networking code
| [Sunday 29 August 2010] [14:41:54]   * pieter_hintjens wants to get back to coding
| [Sunday 29 August 2010] [14:42:10] <pieter_hintjens>    sorry, guys, i'm not in the right frame of mind for this discussion
| [Sunday 29 August 2010] [14:42:26] <sustrik>    pieter: sure, np
| [Sunday 29 August 2010] [14:42:30] <pieter_hintjens>    too much caffeine :-)
| [Sunday 29 August 2010] [14:42:42] <jond>   i'm on the rioja
| [Sunday 29 August 2010] [14:42:57] <pieter_hintjens>    ah, i need to wait until the caffeine wears off
| [Sunday 29 August 2010] [14:43:05] <pieter_hintjens>    look, it's easy to experiment
| [Sunday 29 August 2010] [14:43:13] <pieter_hintjens>    copy the start page to a sandbox page, edit
| [Sunday 29 August 2010] [14:43:28] <jond>   we need edward tuffe
| [Sunday 29 August 2010] [14:43:51] <pieter_hintjens>    where's edward tuffe when you need him!?
| [Sunday 29 August 2010] [14:43:57] <pieter_hintjens>    and who is edward tuffe?
| [Sunday 29 August 2010] [14:45:11] <jond>   sorry it's tufte.  http://www.edwardtufte.com/tufte/
| [Sunday 29 August 2010] [14:46:09] <jond>   envisioning information is the book, bit pre-web though. he invented sparklines
| [Sunday 29 August 2010] [14:46:36] <pieter_hintjens>    i like the idea of two websites
| [Sunday 29 August 2010] [14:46:45] <pieter_hintjens>    1. newbies
| [Sunday 29 August 2010] [14:46:49] <pieter_hintjens>    2. community
| [Sunday 29 August 2010] [14:47:22] <sustrik>    yes
| [Sunday 29 August 2010] [14:47:26] <pieter_hintjens>    the newbie site should be minimalistic and pure to reflect the spirit of MQ
| [Sunday 29 August 2010] [14:47:37] <sustrik>    it's only way not to overwhelm newbies
| [Sunday 29 August 2010] [14:47:45] <pieter_hintjens>    while the community site should be rich and diverse and organic to reflect the spirt of the community
| [Sunday 29 August 2010] [14:47:49] <sustrik>    yes
| [Sunday 29 August 2010] [14:48:17] <pieter_hintjens>    the jond principle
| [Sunday 29 August 2010] [14:48:48] <pieter_hintjens>    hah...
| [Sunday 29 August 2010] [14:48:52] <pieter_hintjens>    we can do it with a single site
| [Sunday 29 August 2010] [14:48:56] <pieter_hintjens>    with two different landing pages
| [Sunday 29 August 2010] [14:48:59] <pieter_hintjens>    for members and non-members
| [Sunday 29 August 2010] [14:49:03] <sustrik>    yes
| [Sunday 29 August 2010] [14:49:13] <sustrik>    with a "community" button on the newbies page
| [Sunday 29 August 2010] [14:49:15] <pieter_hintjens>    that means, when you register you see the full site
| [Sunday 29 August 2010] [14:49:32] <pieter_hintjens>    hmm, well, technical issues maybe
| [Sunday 29 August 2010] [14:49:52] <pieter_hintjens>    simplest is two wiki sites, they are trivial to create
| [Sunday 29 August 2010] [14:50:04] <pieter_hintjens>    with, as you say, community button on newbies page
| [Sunday 29 August 2010] [14:50:12] <sustrik>    one is ok, no registration should be requiread
| [Sunday 29 August 2010] [14:50:19] <pieter_hintjens>    no, can't do it with one site
| [Sunday 29 August 2010] [14:50:23] <sustrik>    so that newbie can click on "community"
| [Sunday 29 August 2010] [14:50:32] <pieter_hintjens>    unless you want to annoy everyone with having a two-step access to the real site
| [Sunday 29 August 2010] [14:50:33] <sustrik>    and see: wow! a lot of things going on!
| [Sunday 29 August 2010] [14:50:41] <pieter_hintjens>    it's a link
| [Sunday 29 August 2010] [14:50:42] <sustrik>    and the get back to newbies page :)
| [Sunday 29 August 2010] [14:51:08] <pieter_hintjens>    we need www.zeromq.org to be simple, and community.zeromq.org to be the full site
| [Sunday 29 August 2010] [14:51:08] <sustrik>    different urls?
| [Sunday 29 August 2010] [14:51:10] <pieter_hintjens>    yes
| [Sunday 29 August 2010] [14:51:17] <sustrik>    dev.zeromq.org
| [Sunday 29 August 2010] [14:51:22] <pieter_hintjens>    yes, dev
| [Sunday 29 August 2010] [14:51:28] <pieter_hintjens>    wikidot has cross-site includes
| [Sunday 29 August 2010] [14:51:36] <pieter_hintjens>    so www. can pull pages in from dev.
| [Sunday 29 August 2010] [14:51:40] <pieter_hintjens>    css and so on, content too
| [Sunday 29 August 2010] [14:51:40] <sustrik>    ok, why not
| [Sunday 29 August 2010] [14:51:59] <pieter_hintjens>    we would rename the current site to dev. and make a new clean www. then
| [Sunday 29 August 2010] [14:52:04] <pieter_hintjens>    1 hour work
| [Sunday 29 August 2010] [14:52:07] <sustrik>    ack
| [Sunday 29 August 2010] [14:52:12] <pieter_hintjens>    let's do that tomorrow :-)
| [Sunday 29 August 2010] [14:52:16] <sustrik>    ok
| [Sunday 29 August 2010] [14:53:23] <pieter_hintjens>    btw i've stuck a loud and annoying "Please vote if you liked it" on the page template
| [Sunday 29 August 2010] [14:53:44] <pieter_hintjens>    experimental, to see if we can filter out pages people use more often
| [Sunday 29 August 2010] [14:53:50] <jond>   i've gotta go for now ; martin be interested in view on pftree patch and socket option thing tomorrow
| [Sunday 29 August 2010] [14:54:00] <pieter_hintjens>    g'nite jond
| [Sunday 29 August 2010] [14:54:47] <jond>   cheers, best
| [Sunday 29 August 2010] [14:54:55] <sustrik>    jon: good noght
| [Sunday 29 August 2010] [14:55:00] <sustrik>    night
| [Sunday 29 August 2010] [14:55:22] <sustrik>    pieter: i would rely on analytics
| [Sunday 29 August 2010] [14:55:52] <sustrik>    i don't believe enough people would vote to make it statistically relevant
| [Sunday 29 August 2010] [14:56:29] <pieter_hintjens>    analytics shows what people read but not what they like
| [Sunday 29 August 2010] [14:56:30] <sustrik>    especially newbies as voting requires creating a wikidot account iirc
| [Sunday 29 August 2010] [14:56:34] <pieter_hintjens>    sure
| [Sunday 29 August 2010] [14:56:42] <pieter_hintjens>    i see this more relevant to dev content
| [Sunday 29 August 2010] [14:56:48] <sustrik>    ok
| [Sunday 29 August 2010] [14:56:58] <pieter_hintjens>    in fact the www site should not have anything like this sophistication
| [Sunday 29 August 2010] [14:57:14] <sustrik>    no, i would like it to have ~3 links
| [Sunday 29 August 2010] [14:57:16] <sustrik>    maybe 4
| [Sunday 29 August 2010] [14:57:17] <pieter_hintjens>    right
| [Sunday 29 August 2010] [14:57:29] <pieter_hintjens>    random question, do you do memory leak tests on 0MQ?
| [Sunday 29 August 2010] [14:57:33] <pieter_hintjens>    valgrind?
| [Sunday 29 August 2010] [14:57:40] <sustrik>    yes
| [Sunday 29 August 2010] [14:57:43] <sustrik>    valgrind
| [Sunday 29 August 2010] [14:57:55] <pieter_hintjens>    have you tried mtrace?
| [Sunday 29 August 2010] [14:58:01] <sustrik>    no
| [Sunday 29 August 2010] [14:58:27] <pieter_hintjens>    ok, np, just wondered if anyone had experience with it
| [Sunday 29 August 2010] [15:34:09] <bgranger>   pieter_hintjens:  I just  posted a question to the list, but it probably makes sense to discuss...
| [Sunday 29 August 2010] [15:34:44] <sustrik>    brian, it's a matter of stability
| [Sunday 29 August 2010] [15:35:09] <bgranger>   OK, that makes sense.  Keep zeromq stable and have the other repos with less stable code?
| [Sunday 29 August 2010] [15:35:12] <pieter_hintjens>    yes
| [Sunday 29 August 2010] [15:35:20] <sustrik>    right
| [Sunday 29 August 2010] [15:35:22] <bgranger>   OK, that sounds great.
| [Sunday 29 August 2010] [15:36:08] <bgranger>   Are you sort of thinking of handling it like Apache does:  projects start out as "incubator" until they are stable and then they move into "official" status?
| [Sunday 29 August 2010] [15:36:31] <bgranger>   I mean, once other things become stable, would you consider moving them  into zeromq?
| [Sunday 29 August 2010] [15:36:37] <sustrik>    haven't thought that far yet
| [Sunday 29 August 2010] [15:36:48] <bgranger>   I am trying to think about how I would handle wrapping these other things into Python...
| [Sunday 29 August 2010] [15:36:51] <sustrik>    quite possibly imo
| [Sunday 29 August 2010] [15:37:23] <bgranger>   i.e., do I start separate Python bindings for ZFL or just keep them in pyzmq...
| [Sunday 29 August 2010] [15:37:48] <sustrik>    afaiu zfl is just a conveniece library
| [Sunday 29 August 2010] [15:37:58] <sustrik>    no much point in porting it to python
| [Sunday 29 August 2010] [15:38:11] <sustrik>    as for devices
| [Sunday 29 August 2010] [15:38:14] <bgranger>   OK, but it could grow?
| [Sunday 29 August 2010] [15:38:36] <sustrik>    in theory, however, i am not sure what can be possibly added
| [Sunday 29 August 2010] [15:38:58] <sustrik>    the functionality is kind of self-contained and well-rounded
| [Sunday 29 August 2010] [15:39:05] <bgranger>   Ok, I am just trying to get a sense of where it is headed
| [Sunday 29 August 2010] [15:39:17] <sustrik>    hard to tell in advance
| [Sunday 29 August 2010] [15:39:31] <bgranger>   Ok, I will just leave it for now and not worry about wrapping.
| [Sunday 29 August 2010] [15:39:38] <sustrik>    but here's what my expectation is:
| [Sunday 29 August 2010] [15:40:04] <sustrik>    the core library is pretty much stabilised and won't change much in the future
| [Sunday 29 August 2010] [15:40:15] <sustrik>    it's not even likely major additions are made
| [Sunday 29 August 2010] [15:40:32] <sustrik>    however, there may be other projects on top of 0mq
| [Sunday 29 August 2010] [15:40:43] <sustrik>    say different devices
| [Sunday 29 August 2010] [15:40:58] <sustrik>    bridges to different protocols
| [Sunday 29 August 2010] [15:41:05] <bgranger>   Definitely
| [Sunday 29 August 2010] [15:41:07] <sustrik>    etc.
| [Sunday 29 August 2010] [15:41:13] <bgranger>   We already have other devices in pyzmq.
| [Sunday 29 August 2010] [15:41:15] <bgranger>   :)
| [Sunday 29 August 2010] [15:41:20] <sustrik>    exactly
| [Sunday 29 August 2010] [15:41:30] <bgranger>   After they stablize, it may make sense to move them to zeromq
| [Sunday 29 August 2010] [15:41:31] <sustrik>    i am not sure we can say:
| [Sunday 29 August 2010] [15:41:44] <sustrik>    "this is the canonical set of devices"
| [Sunday 29 August 2010] [15:42:13] <sustrik>    it's simply on people what they'll come with
| [Sunday 29 August 2010] [15:42:30] <sustrik>    it's ecosystem rather than product
| [Sunday 29 August 2010] [15:42:40] <sustrik>    so the core thing has to be kept separate
| [Sunday 29 August 2010] [15:42:43] <bgranger>   Very true, i have a feeling that as time goes on, devices will expand.  I could even imagine that devices become bridges to other protocols as well.
| [Sunday 29 August 2010] [15:42:49] <bgranger>   This very much makes sense.
| [Sunday 29 August 2010] [15:42:50] <sustrik>    otherwise it would change a lot :|
| [Sunday 29 August 2010] [15:43:07] <sustrik>    bgranger: ack
| [Sunday 29 August 2010] [15:43:14] <bgranger>   As a bindings maintainer, I like the idea of keeping the core stable!
| [Sunday 29 August 2010] [15:43:24] <sustrik>    i think everyone does :)
| [Sunday 29 August 2010] [15:43:38] <sustrik>    the less change the less work for everyone
| [Sunday 29 August 2010] [15:44:40] <bgranger>   Yes, I was pleased with how little changed betweeen 2.0.7 and 2.0.8
| [Sunday 29 August 2010] [15:44:52] <bgranger>   It took only 5-10 minutes to update things.
| [Sunday 29 August 2010] [15:45:22] <sustrik>    we are past the "immature" phase i think
| [Sunday 29 August 2010] [15:45:35] <sustrik>    when change happens a lot of people gets pissed off
| [Sunday 29 August 2010] [15:46:08] <sustrik>    so welcome to the maintenance phase
| [Sunday 29 August 2010] [15:46:17] <bgranger>   Yes, I am already running into that with the Python bindings.  Even I can't change the core pyzmq API without getting a reaction. 
| [Sunday 29 August 2010] [15:47:02] <bgranger>   We are still doing a lot of work underneath the hood, but the core API is pretty stable for us.
| [Sunday 29 August 2010] [15:47:05] <bgranger>   as well.
| [Sunday 29 August 2010] [15:47:10] <sustrik>    yup
| [Sunday 29 August 2010] [15:47:30] <bgranger>   OK, I am trying to catch up on the list traffic.  I may be back...
| [Sunday 29 August 2010] [15:47:40] <sustrik>    cya
| [Sunday 29 August 2010] [16:44:49] <Blafasel_>  Hi there. Played with MS MQ, need a ~lifo kind of queue, reliable. Is zeromq something I should investigate more? The "Guide" on the site stops when it gets interesting.. :)
| [Monday 30 August 2010] [00:52:02] <motk>   howdy people
| [Monday 30 August 2010] [00:52:17] <snerd>  would there be any interest in adding a zeromq mirror? 
| [Monday 30 August 2010] [00:52:32] <snerd>  I'm running a large academic mirror and am looking for decent content
| [Monday 30 August 2010] [00:53:58] <guido_g>    i don't think that the hit rate on the web-site makes this necessary :)
| [Monday 30 August 2010] [00:54:30] <guido_g>    but you should ask the imatix guys
| [Monday 30 August 2010] [00:54:54] <snerd>  heh, worth a shot
| [Monday 30 August 2010] [00:55:15] <snerd>  wish I could've been using 0mq back at my last investment banking job
| [Monday 30 August 2010] [00:55:58] <guido_g>    same here for the tradings system project i'vew been on last year :)
| [Monday 30 August 2010] [00:56:19] <guido_g>    ibm wllm is a beast
| [Monday 30 August 2010] [00:56:20] <snerd>  cough mutter 'alladin' cough mutter
| [Monday 30 August 2010] [00:56:32] <snerd>  before that it was mqseries
| [Monday 30 August 2010] [00:56:35] <snerd>  guh
| [Monday 30 August 2010] [00:58:52] <guido_g>    oh btw, there discussions going to redesign the web site, so if you're interested stay tuned
| [Monday 30 August 2010] [00:59:14] <snerd>  we're already mirror apachemq, rabbitmq, amqp stuff, so might as well
| [Monday 30 August 2010] [00:59:47] <guido_g>    as i said, imatix is taking care of that
| [Monday 30 August 2010] [00:59:52] <snerd>  nod
| [Monday 30 August 2010] [01:00:19] <guido_g>    the whole thing is a wikidot page
| [Monday 30 August 2010] [01:00:33] <snerd>  eep
| [Monday 30 August 2010] [01:25:11] <sustrik>    snerd: we've actually talked about where to host the downloads
| [Monday 30 August 2010] [01:25:27] <sustrik>    uploading them to the wiki is a bit weird
| [Monday 30 August 2010] [01:26:13] <sustrik>    as for the mirroring, why not
| [Monday 30 August 2010] [01:26:19] <sustrik>    it won't hurt anybody
| [Monday 30 August 2010] [01:27:12] <sustrik>    Blafasel_: everything is FIFO in 0MQ
| [Monday 30 August 2010] [01:27:29] <snerd>  if anyone is up for it, hit me at rob.kearey@aarnet.edu.au
| [Monday 30 August 2010] [01:29:22] <sustrik>    ok
| [Monday 30 August 2010] [01:43:10] <CIA-20> rbzmq: 03Martin Sustrik 07master * re742398 10/ rbzmq.c : PUSH and PULL constants added - http://bit.ly/ctHC2I
| [Monday 30 August 2010] [01:49:00] <CIA-20> clrzmq: 03Martin Sustrik 07master * rcf394ea 10/ clrzmq/zmq.cs : PUSH and PULL constants added - http://bit.ly/9G3Gqh
| [Monday 30 August 2010] [03:49:59] <mrm2m>  guido_g: Rckmeldung zur Seite: Der "all languages"-button unter den Beispielen ist genial! 
| [Monday 30 August 2010] [03:50:15] <guido_g>    great
| [Monday 30 August 2010] [03:51:42] <mrm2m>  Sotty
| [Monday 30 August 2010] [03:51:59] <mrm2m>  Sorry, did't recorgnize it's english here
| [Monday 30 August 2010] [03:56:30] <guido_g>    np
| [Monday 30 August 2010] [03:57:07] <guido_g>    for info about crosscompiling you might want have a lookt at the maling list
| [Monday 30 August 2010] [05:05:38] <mrm2m>  just an Idea: You already use JS for this All languages. Why not replace the content of the corresponding example in place? A set Language as default would be cool, too. 
| [Monday 30 August 2010] [05:38:30] <mrm2m>  Test of pyzmq failes: http://paste.pocoo.org/show/256240/
| [Monday 30 August 2010] [05:38:34] <mrm2m>  Any ideas?
| [Monday 30 August 2010] [05:39:41] <mrm2m>  /usr/local/lib/python2.6/dist-packages/zmq/_zmq.so looks good - as far as I can tell
| [Monday 30 August 2010] [05:41:22] <mrm2m>  oh - never mind. I didn't recognize that python was looking in "/home/moritz/GEU/pyzmq/zmq/" instead of "/usr/local/lib/python2.6/dist-packages/zmq/"
| [Monday 30 August 2010] [05:47:07] <guido_g>    re
| [Monday 30 August 2010] [05:53:55] <mrm2m>  Hi, I just ran into this problem: http://blog.boxedice.com/2010/05/23/building-zeromq-and-pyzmq-on-red-hat/
| [Monday 30 August 2010] [05:54:21] <mrm2m>  It's the same for Ubuntu. Solution worked, but isn't pretty. 
| [Monday 30 August 2010] [05:55:22] <guido_g>    no probs on original debian
| [Monday 30 August 2010] [05:56:54] <mrm2m>  http://mail.scipy.org/pipermail/ipython-dev/2010-March/005900.html
| [Monday 30 August 2010] [05:58:09] <guido_g>    so?
| [Monday 30 August 2010] [05:58:16] <guido_g>    what's the problem?
| [Monday 30 August 2010] [06:01:07] <mrm2m>  Nothing. Just an info, that this topic still exists and also affects Ubuntu
| [Monday 30 August 2010] [06:10:27] <CIA-20> zeromq2: 03Martin Sustrik 07master * rfba90af 10/ src/socket_base.cpp : Issue 54 - socket_base.cpp:162 comparison error - http://bit.ly/9M5Xs2
| [Monday 30 August 2010] [06:23:00]   * pieterh is just sneaking in while waiting for a plane to take off
| [Monday 30 August 2010] [06:23:41] <guido_g>    ahh, ryanair again? :)
| [Monday 30 August 2010] [06:24:05] <pieterh>    guido_g: yeah :-)
| [Monday 30 August 2010] [06:24:34] <guido_g>    so good luck, take care
| [Monday 30 August 2010] [06:24:39] <pieterh>    http://new.zeromq.org is something I hacked up this morning
| [Monday 30 August 2010] [06:25:03] <pieterh>    this would become www.zeromq.org and the current www. would become dev.zeromq.org
| [Monday 30 August 2010] [06:25:16] <guido_g>    nice
| [Monday 30 August 2010] [06:25:51] <pieterh>    sustrik and i will strip it down until it's minimalistic
| [Monday 30 August 2010] [06:26:25] <guido_g>    but for more input you should ask mrm2m, he's the new kid on the block :)
| [Monday 30 August 2010] [06:27:15] <jond>   pieter: looks better. I am beginning to see yr point about the colours
| [Monday 30 August 2010] [06:27:41] <pieterh>    the strong red/black works for simple sites but seems painful for link-rich text
| [Monday 30 August 2010] [06:28:03] <sustrik>    the guide?
| [Monday 30 August 2010] [06:28:08] <pieterh>    ?
| [Monday 30 August 2010] [06:28:18] <pieterh>    that's a question?
| [Monday 30 August 2010] [06:28:35] <pieterh>    sorry., have to leave, cyl
| [Monday 30 August 2010] [06:28:50] <sustrik>    cyl
| [Monday 30 August 2010] [06:29:35] <sustrik>    ugh, the voting box hurts eyes
| [Monday 30 August 2010] [06:30:36] <guido_g>    the box won't be in the final version, i assume
| [Monday 30 August 2010] [06:32:07] <sustrik>    dunno, but it should be of that poisonous pink hue
| [Monday 30 August 2010] [06:35:58] <guido_g>    at least, it *does* catch attention :)
| [Monday 30 August 2010] [06:37:24] <sustrik>    guido_g: have a look at www.zeromq.org now
| [Monday 30 August 2010] [06:37:39] <sustrik>    i've removed the red
| [Monday 30 August 2010] [06:37:52] <sustrik>    pretty dull
| [Monday 30 August 2010] [06:38:29] <guido_g>    can't see the links anymore
| [Monday 30 August 2010] [06:38:42] <sustrik>    they should be grey
| [Monday 30 August 2010] [06:38:45] <guido_g>    links should stand out a little
| [Monday 30 August 2010] [06:39:11] <sustrik>    ah, you see them as black?
| [Monday 30 August 2010] [06:39:24] <guido_g>    no grey
| [Monday 30 August 2010] [06:39:51] <guido_g>    but it's hard to read
| [Monday 30 August 2010] [06:40:08] <sustrik>    ok, reverting it back to red
| [Monday 30 August 2010] [06:41:24] <jond>   what would the whole  background look like in that grey?
| [Monday 30 August 2010] [06:41:53] <sustrik>    it would make the text less readable imo
| [Monday 30 August 2010] [06:42:03] <sustrik>    the contrast is good
| [Monday 30 August 2010] [06:42:10] <sustrik>    people just complained about the red
| [Monday 30 August 2010] [06:43:32] <jond>   0MQ logo looks very close to helvetica, does it look any good in black
| [Monday 30 August 2010] [06:47:39] <sustrik>    not really, and it's not even helvetica
| [Monday 30 August 2010] [06:47:49] <sustrik>    it's custom-designed font :)
| [Monday 30 August 2010] [06:52:34] <mrm2m>  OMG! 
| [Monday 30 August 2010] [06:53:11] <mrm2m>  No, I like the design. 
| [Monday 30 August 2010] [06:53:34] <mrm2m>  The TOC could be a little bit more structured. 
| [Monday 30 August 2010] [06:53:48] <mrm2m>  But so far I found everything I was looking for. 
| [Monday 30 August 2010] [06:59:14] <sustrik>    mrm2m: thanks for feeback
| [Monday 30 August 2010] [06:59:31] <sustrik>    yes, it's not about content missing, it's about messy structure
| [Monday 30 August 2010] [07:00:30] <mrm2m>  Well - The Navigation looks a litttle bit like a tag cloud. 
| [Monday 30 August 2010] [07:01:09] <mrm2m>  A lots of people have trouble communicating with a cloud, you know ;.)
| [Monday 30 August 2010] [07:01:40] <keffo>  Personally I find dancing to be a great way!
| [Monday 30 August 2010] [07:02:25] <sustrik>    :)
| [Monday 30 August 2010] [07:07:27] <keffo>  sustrik, I just replied to the lb thread :)
| [Monday 30 August 2010] [07:38:32] <jond>   I still think the user comments and blog stuff should go and the text from the what's 0MQ spread two columns
| [Monday 30 August 2010] [07:38:46] <jond>   and there's too much red
| [Monday 30 August 2010] [07:53:28] <sustrik>    jond: yes, that kind of stuff, but it's more about ergonomy
| [Monday 30 August 2010] [07:53:49] <sustrik>    90% of visitors want to solve a problem rather then browse around
| [Monday 30 August 2010] [07:54:15] <sustrik>    and the page is not particularly well designed to help you solve your proble quickly and efficiently
| [Monday 30 August 2010] [07:54:51] <sustrik>    joel spolsky had few nice articles on this topic
| [Monday 30 August 2010] [07:55:21] <mrm2m>  by the way: Got it running at my embedded ARM platform now. 
| [Monday 30 August 2010] [07:55:41] <guido_g>    woot! :9
| [Monday 30 August 2010] [07:55:50] <mrm2m>  I will give some summery, of what I've done If you like
| [Monday 30 August 2010] [07:56:13] <guido_g>    isn't there a wiki page for this kind of stories?
| [Monday 30 August 2010] [07:56:24] <sustrik>    mrm2m: please, do post it on the mailing list
| [Monday 30 August 2010] [07:56:48] <sustrik>    to make it available
| [Monday 30 August 2010] [07:57:11] <sustrik>    the wiki would be a good choice if it's a howto rather than story
| [Monday 30 August 2010] [07:58:01] <guido_g>    ok
| [Monday 30 August 2010] [08:14:25] <mrm2m>  The user-guide is NSFW. My boss is looking strange, while I lay down in laughter. 
| [Monday 30 August 2010] [08:16:19] <sustrik>    :)
| [Monday 30 August 2010] [09:16:50] <theICEBear> Hi I wonder if anyone knows about an issue with sessions in zmq. I am hitting an assert in session::process_attach line 287
| [Monday 30 August 2010] [09:21:10] <sustrik>    theICEBear: what version is that?
| [Monday 30 August 2010] [09:21:16] <theICEBear> 2.0.8
| [Monday 30 August 2010] [09:21:45] <sustrik>    zmq_assert (!engine);
| [Monday 30 August 2010] [09:21:51] <theICEBear> Yup
| [Monday 30 August 2010] [09:21:56] <sustrik>    are you using identities?
| [Monday 30 August 2010] [09:22:00] <sustrik>    ZMQ_IDENTITY?
| [Monday 30 August 2010] [09:22:44] <theICEBear> I am trying to set my own yeah
| [Monday 30 August 2010] [09:23:06] <theICEBear> I am probably setting them in the wrong place then
| [Monday 30 August 2010] [09:23:58] <sustrik>    i think what's happening is that there are two peers trying to connect to the same socket with the same identity
| [Monday 30 August 2010] [09:24:14] <sustrik>    this case is not yet handled decently
| [Monday 30 August 2010] [09:24:38] <theICEBear> peers as in?
| [Monday 30 August 2010] [09:25:00] <sustrik>    the applications over the network
| [Monday 30 August 2010] [09:25:17] <theICEBear> Ah, thanks for the tip I will check
| [Monday 30 August 2010] [09:28:00] <CIA-20> zeromq2: 03Martin Sustrik 07master * rf0a36f9 10/ doc/zmq_cpp.txt : Minor patch to zmq_cpp(7) - http://bit.ly/bfgJOm
| [Monday 30 August 2010] [10:29:47] <sustrik>    pieterh: are you in bts already?
| [Monday 30 August 2010] [10:46:11] <pieterh>    sustrik: ano, ja jestem z bratislava
| [Monday 30 August 2010] [10:50:32] <pieterh>    sorry, i was using polish notation, it should be "som w bratislave"
| [Monday 30 August 2010] [10:50:43] <pieterh>    0MQ/5.0 will have Slavic language bindings
| [Monday 30 August 2010] [11:05:13] <CIA-20> zeromq2: 03Martin Sustrik 07master * re45583c 10/ src/semaphore.hpp : OSX build fixed -- semaphore replaced by mutex - http://bit.ly/9AYi6Y
| [Monday 30 August 2010] [11:05:46] <sustrik>    pieteh: cool
| [Monday 30 August 2010] [11:05:55] <sustrik>    just w is spelled v in slovak
| [Monday 30 August 2010] [11:06:18] <sustrik>    pieterh: in the office?
| [Monday 30 August 2010] [11:08:47] <pieterh>    sustrik: i'm with mato, we're debuggine weird pubsub issues
| [Monday 30 August 2010] [11:09:08] <pieterh>    *debugging
| [Monday 30 August 2010] [11:09:37] <sustrik>    ack
| [Monday 30 August 2010] [11:09:49] <sustrik>    i leave you in peace then
| [Monday 30 August 2010] [14:21:00] <Steve-o>    anyone see the new LBM 4,1 features from 29 West?
| [Monday 30 August 2010] [14:21:16] <Steve-o>    zero copy for c# api
| [Monday 30 August 2010] [14:26:21] <Steve-o>    surprised at the choice of terminology, I can't tell whether it is official MS API or out of someones orifice, 
| [Monday 30 August 2010] [14:26:29] <Steve-o>    "Zero Object Delivery (ZOD) has been implemented for .NET, which allows .NET messaging receivers to deliver messages to an application with no per-message object creation."
| [Monday 30 August 2010] [14:26:42] <Steve-o>    "Zero Incoming Copy (ZIC) has been implemented for .NET, which provides access to message data directly through a byte pointer returned by the LBMMessage.dataPointer() method."
| [Monday 30 August 2010] [14:32:36] <sustrik>    nope, haven't seen it yet
| [Monday 30 August 2010] [14:32:45] <sustrik>    what's the link?
| [Monday 30 August 2010] [14:44:14] <Steve-o>    marketing email, looks like most detail is here, http://blogs.informatica.com/perspectives/index.php/2010/08/27/lbm-4-1-ume-3-1-umq-1-1-released/
| [Monday 30 August 2010] [14:46:51] <guido_g>    zero object delivery sounds good :)
| [Monday 30 August 2010] [14:48:10] <Steve-o>    and presumably if 29West are using it it must show some improvement somewhere
| [Monday 30 August 2010] [14:49:02] <guido_g>    sorry, forgot the sarcasm tags
| [Monday 30 August 2010] [14:49:25] <Steve-o>    :P
| [Monday 30 August 2010] [14:49:33] <pieterh>    Lol
| [Monday 30 August 2010] [14:49:40] <guido_g>    zero objects usccessfully delivered 
| [Monday 30 August 2010] [14:49:45] <Steve-o>    you could use a zero object for confirmation reply of delivery
| [Monday 30 August 2010] [14:50:15] <Steve-o>    or just heart beating
| [Monday 30 August 2010] [14:50:19] <pieterh>    ZOD & ZIC vs ZMQ
| [Monday 30 August 2010] [14:50:57] <pieterh>    OMQ!
| [Monday 30 August 2010] [14:50:57] <guido_g>    Steve-o: depends on the protocol information in this "zero object"
| [Monday 30 August 2010] [14:51:47] <Steve-o>    guido_g: in PGM you can delivery 0 byte messages too
| [Monday 30 August 2010] [14:52:15] <guido_g>    as i said, depends on the information in the protocol if this is useful or not
| [Monday 30 August 2010] [14:52:41] <guido_g>    one can't send 0 bytes, so there *is* something on the wire
| [Monday 30 August 2010] [14:53:09] <guido_g>    heartbeat allone isn't that useful
| [Monday 30 August 2010] [14:53:37] <Steve-o>    would be a good idea for virtual circuits
| [Monday 30 August 2010] [14:53:47] <guido_g>    but if you attach the seq. no. of the last data packet, we start to have something
| [Monday 30 August 2010] [14:57:41] <guido_g>    afair, wllm docs didn't say a word about zero copy for the bindings
| [Monday 30 August 2010] [14:58:23] <sustrik>    i like this: http://www.29west.com/products/gateway.html
| [Monday 30 August 2010] [14:58:44] <sustrik>    it looks like 29west have independently arrived at the concept of "device"
| [Monday 30 August 2010] [14:59:04] <sustrik>    that kind of proves the design
| [Monday 30 August 2010] [14:59:44] <guido_g>    hehe
| [Monday 30 August 2010] [15:00:35] <Steve-o>    reads like P2PS, i.e. a TIC without caching
| [Monday 30 August 2010] [15:10:39] <rossij> I have a requirement for a single port to be opened between the agent and the server.  The agent needs to be able to connect the server and send messages on demand, but the server needs to be able to supply updates, config changes, other data to all the agents over the established connection.  I don't see a simple way of doing this without using a REQ/REP and a second SUB/PUB with zeromq.  Does anyone have a suggestions on how to do this w
| [Monday 30 August 2010] [15:10:39] <rossij> ZeroMQ?
| [Monday 30 August 2010] [15:12:03] <pieterh>    rossij: it works better when you separate the different types of message flow
| [Monday 30 August 2010] [15:12:11] <pieterh>    request-response is not publish-subscribe
| [Monday 30 August 2010] [15:12:31] <pieterh>    in old-fashioned tcp you would mix these all on one port
| [Monday 30 August 2010] [15:12:39] <pieterh>    but that becomes more complex and less scalable
| [Monday 30 August 2010] [15:12:54] <rossij> pieterh: I wish i could it would be sooo much simpler, but two ports is goign to be a no go 
| [Monday 30 August 2010] [15:12:56] <pieterh>    imagine you want to supply updates to some components across a multicast bust
| [Monday 30 August 2010] [15:12:58] <pieterh>    *bus
| [Monday 30 August 2010] [15:13:11] <pieterh>    why is two ports a no go?
| [Monday 30 August 2010] [15:13:49] <rossij> pieterh: it's what current ly is in place in a huge number of installations. 
| [Monday 30 August 2010] [15:14:07] <pieterh>    this is across a LAN?
| [Monday 30 August 2010] [15:14:10] <rossij> pieterh: zeromq plus two ports would make this simple 
| [Monday 30 August 2010] [15:14:52] <pieterh>    in any case you will need to migrate components to a new stack
| [Monday 30 August 2010] [15:15:01] <pieterh>    presumably hidden inside whatever framework you use
| [Monday 30 August 2010] [15:15:11] <pieterh>    one, two, 10 ports... it does not change that
| [Monday 30 August 2010] [15:15:37] <pieterh>    existing components cannot talk to 0MQ without having 0MQ linked with them
| [Monday 30 August 2010] [15:16:28] <rossij> understand that I am working to rip on the udp network code and put in zeromq for tcp/multicast and its just so nice to work with
| [Monday 30 August 2010] [15:16:42] <pieterh>    sure
| [Monday 30 August 2010] [15:17:11] <pieterh>    do you understand that the number of ports you end up using is not a problem
| [Monday 30 August 2010] [15:17:19] <pieterh>    unless you have firewall issues
| [Monday 30 August 2010] [15:17:30] <pieterh>    or someone who really, really hates you opening new ports
| [Monday 30 August 2010] [15:18:06] <rossij> yes - i understand that - inside the firewall it's all ok - but - for devices and installs in the DMZ and other areas 
| [Monday 30 August 2010] [15:18:20] <pieterh>    right...
| [Monday 30 August 2010] [15:18:53] <pieterh>    what I'd look at is bridging this into the DMZ using a device
| [Monday 30 August 2010] [15:19:35] <pieterh>    there is no literature yet on how to tunnel 0MQ connections over 0MQ but IMO it's possible
| [Monday 30 August 2010] [15:20:25] <rossij> that is something I will have to try.  makes the setup a little more complex but could work
| [Monday 30 August 2010] [15:20:39] <pieterh>    i'd say, a pair of devices that create a tunnel
| [Monday 30 August 2010] [15:20:51] <pieterh>    one inside the DMZ, one on the LAN
| [Monday 30 August 2010] [15:21:01] <pieterh>    XREQ/XREP between the two
| [Monday 30 August 2010] [15:21:15] <Steve-o>    ideally would be nicer to tunnel it all over http, easier to firewall
| [Monday 30 August 2010] [15:21:34] <rossij> humm anyone know if TCP virtual services / virtual endpoints is being worked on ?
| [Monday 30 August 2010] [15:21:34] <pieterh>    yes, devices could be bridges, speaking HTTP at one edge, 0MQ at the other
| [Monday 30 August 2010] [15:21:46] <pieterh>    it's an idea for 0MQ/3.0
| [Monday 30 August 2010] [15:21:53] <pieterh>    i assume you mean subports kind of thing?
| [Monday 30 August 2010] [15:21:55] <Steve-o>    is there any http/zeromq gateway?
| [Monday 30 August 2010] [15:22:01] <rossij> pieterh: yes
| [Monday 30 August 2010] [15:22:04] <pieterh>    Steve-o: not as far as I know
| [Monday 30 August 2010] [15:22:14] <pieterh>    rossij: yes, 0MQ/3.0 concept
| [Monday 30 August 2010] [15:22:39] <pieterh>    see http://www.zeromq.org/docs:3_0
| [Monday 30 August 2010] [15:22:51] <pieterh>    "TCP virtual services / virtual endpoints"
| [Monday 30 August 2010] [15:22:58] <pieterh>    oh... :-)
| [Monday 30 August 2010] [15:23:01] <pieterh>    you quoted that page
| [Monday 30 August 2010] [15:23:03] <pieterh>    lol
| [Monday 30 August 2010] [15:23:07] <rossij> yeah that is where I got - i just noticed and hoped - some might move to 2.1 :) 
| [Monday 30 August 2010] [15:23:17] <pieterh>    it might be moved to 2.1
| [Monday 30 August 2010] [15:23:58] <sustrik>    Steve-o: 0MQ/HTTP gateway => mongrel2
| [Monday 30 August 2010] [15:24:14] <pieterh>    sustrik: not really... kind of but no...
| [Monday 30 August 2010] [15:24:37] <pieterh>    it uses 0MQ to implement a higher-level API
| [Monday 30 August 2010] [15:24:47] <sustrik>    ok
| [Monday 30 August 2010] [15:24:57] <sustrik>    i've did some thinking about the virtual endpoints
| [Monday 30 August 2010] [15:25:04] <sustrik>    subports
| [Monday 30 August 2010] [15:25:07] <rossij> pieterh: thanks will keep a watch out - and see what i can do myself
| [Monday 30 August 2010] [15:25:46] <pieterh>    rossij: IMO a pair of tunneling devices will be quite easy to make, if you don't try to be generic
| [Monday 30 August 2010] [15:26:02] <sustrik>    the basic concept is simple, the only implementation problem i see is how to share a single TCP listener socket between all the sockets and i/o threads
| [Monday 30 August 2010] [15:26:46] <pieterh>    sustrik: use 0MQ messaging, internally... :-)
| [Monday 30 August 2010] [15:26:47] <sustrik>    it would require non-trivial work to solve all the synchronisation issues
| [Monday 30 August 2010] [15:27:16] <Steve-o>    the recent google work on shared sockets?
| [Monday 30 August 2010] [15:27:21] <sustrik>    pieterh: actually, that's what 0mq is doing :)
| [Monday 30 August 2010] [15:27:42] <pieterh>    so a socket with virtual endpoints becomes a device, no?
| [Monday 30 August 2010] [15:27:45] <sustrik>    inter-thread synchronisation messages are passed using same code that is used to pass real 0mq messages
| [Monday 30 August 2010] [15:27:53] <pieterh>    sustrik: neat
| [Monday 30 August 2010] [15:28:22] <sustrik>    what you are speaking about is tunnel
| [Monday 30 August 2010] [15:28:26] <sustrik>    which is doable,sure
| [Monday 30 August 2010] [15:28:34] <sustrik>    but it's nasty
| [Monday 30 August 2010] [15:28:46] <sustrik>    you get head of line blocking problem etc.
| [Monday 30 August 2010] [15:29:01] <sustrik>    real solution is to have real separate connections
| [Monday 30 August 2010] [15:29:10] <sustrik>    sharing same source port
| [Monday 30 August 2010] [15:29:43] <sustrik>    sorry for the rant btw
| [Monday 30 August 2010] [15:30:06] <sustrik>    i have another one about zero-copy
| [Monday 30 August 2010] [15:30:14] <Steve-o>    :D
| [Monday 30 August 2010] [15:30:17] <sustrik>    :)
| [Monday 30 August 2010] [15:30:40] <sustrik>    well, there are interesting things i've learned hard way with zero copy
| [Monday 30 August 2010] [15:30:51] <sustrik>    i can summarise it in an email
| [Monday 30 August 2010] [15:31:04] <sustrik>    anyone interested in that?
| [Monday 30 August 2010] [15:31:20] <pieterh>    sustrik: if you have a good rant, make it a blog posting
| [Monday 30 August 2010] [15:31:51] <sustrik>    it stems from you \x00 email, so it would be logical to reply
| [Monday 30 August 2010] [15:32:06] <pieterh>    lol, ok, go for it...
| [Monday 30 August 2010] [15:32:20] <sustrik>    goodo
| [Monday 30 August 2010] [15:32:34] <pieterh>    note that i only mentioned this because some poor user hit the door with his nose
| [Monday 30 August 2010] [15:33:22] <sustrik>    i know, the problem is that it's user feature that has profound implementation impact on the whole stack
| [Monday 30 August 2010] [15:33:56] <sustrik>    basically the feature would be "stretched" all the way down to kernel/userspace boundary
| [Monday 30 August 2010] [15:34:32] <sustrik>    and -- if kernel support is added one day -- even further down into kernel networking stack
| [Monday 30 August 2010] [15:34:39] <sustrik>    which is pretty nasty
| [Monday 30 August 2010] [15:35:41] <pieterh>    you're saying...
| [Monday 30 August 2010] [15:35:47] <pieterh>    that allocating one extra byte
| [Monday 30 August 2010] [15:35:53] <pieterh>    means the end of the universe...
| [Monday 30 August 2010] [15:36:03] <pieterh>    :-)
| [Monday 30 August 2010] [15:36:30] <sustrik>    kind of
| [Monday 30 August 2010] [15:36:36] <sustrik>    it's not obvious
| [Monday 30 August 2010] [15:36:46] <sustrik>    but it's a trap i;ve already fell in
| [Monday 30 August 2010] [15:36:50] <pieterh>    i understand that when you do zerocopy on read, it's not possible to mess with what you provide
| [Monday 30 August 2010] [15:36:54] <sustrik>    wasted weeks of coding that way
| [Monday 30 August 2010] [15:36:55] <pieterh>    claro
| [Monday 30 August 2010] [15:37:34] <pieterh>    and we always do zero copy on read?
| [Monday 30 August 2010] [15:38:05] <sustrik>    yes
| [Monday 30 August 2010] [15:38:10] <sustrik>    no point in having 2 stacks
| [Monday 30 August 2010] [15:38:16] <sustrik>    zero-copy and non-zero-copy
| [Monday 30 August 2010] [15:38:49] <pieterh>    fair enough, it obviously does not work with zerocopy reads
| [Monday 30 August 2010] [15:39:08] <pieterh>    for some reason i was imagining we allocated and copied on recv unless the app provided a buffer
| [Monday 30 August 2010] [15:39:15] <pieterh>    i'm stupid
| [Monday 30 August 2010] [15:39:43] <sustrik>    i've did the same mistake
| [Monday 30 August 2010] [15:39:58] <sustrik>    but there was noone to stop me back then :)
| [Monday 30 August 2010] [15:40:42] <pieterh>    lol
| [Monday 30 August 2010] [15:40:54] <sustrik>    i've wasted a lot of time, but otoh the multi-part messages emerged from the mess
| [Monday 30 August 2010] [15:41:10] <Steve-o>    it's very conducive for memory managment
| [Monday 30 August 2010] [15:41:19] <sustrik>    which are actually a pretty good way to retain zero copy while still being able to modify messages
| [Monday 30 August 2010] [15:41:37] <pieterh>    indeed, multipart messages are a clever solution
| [Monday 30 August 2010] [15:41:52] <sustrik>    don't work for the terminal zero though
| [Monday 30 August 2010] [15:41:55] <sustrik>    shrug
| [Monday 30 August 2010] [15:44:31] <sustrik>    pieterh: btw i though of writing little pieces of implementation experience down somehow
| [Monday 30 August 2010] [15:44:35] <sustrik>    so that it's not lost
| [Monday 30 August 2010] [15:44:42] <sustrik>    maybe a mino-blog?
| [Monday 30 August 2010] [15:44:45] <sustrik>    mini
| [Monday 30 August 2010] [15:47:03] <jond>   sustrik: think that would be an excellent idea. as i have discovered with investigating pub/sub filtering the code is quite terse and clever in places but can take quite a while to get into the headspace of 0mq internals and why it is written like it is.
| [Monday 30 August 2010] [15:48:13] <sustrik>    jond: yes, that's exactly my point
| [Monday 30 August 2010] [15:48:18] <sustrik>    there are comments in the code
| [Monday 30 August 2010] [15:48:31] <sustrik>    but that missed the big picture
| [Monday 30 August 2010] [15:48:36] <sustrik>    well, the larger picture
| [Monday 30 August 2010] [15:49:11] <sustrik>    actually, it would be great if you could help with it
| [Monday 30 August 2010] [15:49:20] <sustrik>    you had to dissect the pub/sub code
| [Monday 30 August 2010] [15:49:38] <sustrik>    so you know what the stumbling blocks there are
| [Monday 30 August 2010] [15:50:00] <jond>   hmm, my patmatch branch is so full of cout calls for me to figure out what was going on, i can barely find the code i changed now ;-)
| [Monday 30 August 2010] [15:50:26] <sustrik>    i mean, what were the things that were not obvious immediately
| [Monday 30 August 2010] [15:50:35] <sustrik>    what have taken you a long time to figure out
| [Monday 30 August 2010] [15:50:37] <sustrik>    etc.
| [Monday 30 August 2010] [15:51:06] <sustrik>    i can only guess what's hard and what's not
| [Monday 30 August 2010] [15:51:32] <sustrik>    anyway, it's just an idea
| [Monday 30 August 2010] [15:52:15] <jond>   i'll try and get some notes down, the comments  you have just made about zero copy lead me to think i better study that stuff a bit more
| [Monday 30 August 2010] [15:52:31] <sustrik>    ok. good
| [Monday 30 August 2010] [15:53:45] <jond>   that prefix tree find, was because i have my own prefix tree now and i needed to be sure that i hadnt introduced the bug.
| [Monday 30 August 2010] [15:54:58] <sustrik>    that's what peer review is for :)
| [Monday 30 August 2010] [15:55:45] <jond>   I would still prefer on the pub side to be able to use bits rather than refcount bytes. each sub socket connect results in a single write pipe on the pub side
| [Monday 30 August 2010] [15:55:56] <jond>   that is the case?
| [Monday 30 August 2010] [15:56:32] <sustrik>    yes
| [Monday 30 August 2010] [15:56:47] <sustrik>    yes, probably it can be compressed to a bit
| [Monday 30 August 2010] [15:57:04] <sustrik>    depends on how the subscription forwarding algorithm looks like
| [Monday 30 August 2010] [15:57:14] <sustrik>    if you have a single bit
| [Monday 30 August 2010] [15:57:35] <sustrik>    you have to assure that same subscription won't be sent twice over the same "logical connection"
| [Monday 30 August 2010] [15:57:43] <jond>   that is what i think, if write-pipe ==  sub endpoint effectively
| [Monday 30 August 2010] [15:58:39] <sustrik>    sure, try it that way
| [Monday 30 August 2010] [15:58:44] <sustrik>    we'll see what emerges
| [Monday 30 August 2010] [15:59:35] <jond>   think i might package up that pub matcher class and see it for review. it seems to get the right answers
| [Monday 30 August 2010] [15:59:50] <sustrik>    sure
| [Monday 30 August 2010] [15:59:50] <jond>   s/see/send/g
| [Monday 30 August 2010] [15:59:53] <sustrik>    btw
| [Monday 30 August 2010] [15:59:58] <sustrik>    the bitmap thing
| [Monday 30 August 2010] [16:00:15] <sustrik>    i've seen a performance study on exactly this problem
| [Monday 30 August 2010] [16:00:43] <sustrik>    and the interesting point there was that compressing the bitmaps pays of
| [Monday 30 August 2010] [16:00:44] <jond>   url?
| [Monday 30 August 2010] [16:00:51] <sustrik>    not public yet i think
| [Monday 30 August 2010] [16:00:59] <sustrik>    in any case
| [Monday 30 August 2010] [16:01:10] <sustrik>    the point was that the bitmaps tend to be very sparse
| [Monday 30 August 2010] [16:01:18] <sustrik>    and often pretty large
| [Monday 30 August 2010] [16:01:26] <jond>   i was wondering if dreppers memory paper might have any useful info.
| [Monday 30 August 2010] [16:01:34] <sustrik>    that way you hit cpu cache boundary very soone
| [Monday 30 August 2010] [16:01:55] <sustrik>    and your performance goes down by order of magnitude
| [Monday 30 August 2010] [16:02:03] <sustrik>    maybe even two orders of magnitude
| [Monday 30 August 2010] [16:02:26] <sustrik>    jond: it's definitely worth of reading
| [Monday 30 August 2010] [16:02:40] <sustrik>    but pretty long
| [Monday 30 August 2010] [16:02:41] <jond>   wrt the bitmap, i think that it will be very sparse and large and that is the problem. that's also why i worry about the vectors of refcount, n pipes wide at every node in the trie....
| [Monday 30 August 2010] [16:02:59] <jond>   in the current implementation
| [Monday 30 August 2010] [16:03:02] <sustrik>    right
| [Monday 30 August 2010] [16:03:09] <sustrik>    so what about compressing the vector
| [Monday 30 August 2010] [16:03:20] <sustrik>    making it say a vector of indices
| [Monday 30 August 2010] [16:03:34] <sustrik>    hm
| [Monday 30 August 2010] [16:03:45] <sustrik>    ordered vector of indices
| [Monday 30 August 2010] [16:03:54] <sustrik>    that way merge is O(n)
| [Monday 30 August 2010] [16:05:39] <jond>   it might be easier if i were to send the code. let me go look. need to be sure we are talking about the same thing...
| [Monday 30 August 2010] [16:06:00] <sustrik>    sure send it, review is good
| [Monday 30 August 2010] [16:06:23] <pieterh>    jond: how large are the bitmaps?
| [Monday 30 August 2010] [16:06:23] <sustrik>    what i said was that instead of bit vector 0000100001001001
| [Monday 30 August 2010] [16:06:43] <sustrik>    you can have a vector of indices like this: 5|10|13|16
| [Monday 30 August 2010] [16:07:01] <pieterh>    sustrik: we tested this quite extensively when making openamq
| [Monday 30 August 2010] [16:07:16] <pieterh>    we used compressed bit maps in SFL
| [Monday 30 August 2010] [16:07:27] <sustrik>    and?
| [Monday 30 August 2010] [16:07:55] <sustrik>    it must have been much faster for large amount of subscribers, no?
| [Monday 30 August 2010] [16:07:56] <pieterh>    if you use fast bit operations, uncompressed is faster
| [Monday 30 August 2010] [16:08:13] <sustrik>    how large bitmaps have you tested?
| [Monday 30 August 2010] [16:08:19] <pieterh>    8k bytes
| [Monday 30 August 2010] [16:08:25] <pieterh>    iirc
| [Monday 30 August 2010] [16:08:29] <sustrik>    too small
| [Monday 30 August 2010] [16:08:31] <pieterh>    let me check, it's in IPR
| [Monday 30 August 2010] [16:08:45] <sustrik>    the performance hit comes what cache size is hit
| [Monday 30 August 2010] [16:08:47] <pieterh>    so how large are the bitmaps?
| [Monday 30 August 2010] [16:08:54] <sustrik>    several MB these days
| [Monday 30 August 2010] [16:09:11] <sustrik>    number of topics x number of subscribers
| [Monday 30 August 2010] [16:09:20] <pieterh>    ?
| [Monday 30 August 2010] [16:09:26] <pieterh>    surely you have one bitstring per topic
| [Monday 30 August 2010] [16:09:35] <sustrik>    es
| [Monday 30 August 2010] [16:09:36] <sustrik>    yes
| [Monday 30 August 2010] [16:09:40] <pieterh>    that's the 8k
| [Monday 30 August 2010] [16:09:54]   * sustrik is confused
| [Monday 30 August 2010] [16:09:58] <sustrik>    what 8k?
| [Monday 30 August 2010] [16:10:12] <pieterh>    you asked how large our bitmaps were, I said 8K
| [Monday 30 August 2010] [16:10:17] <pieterh>    that is one bitstring
| [Monday 30 August 2010] [16:10:19] <sustrik>    ah
| [Monday 30 August 2010] [16:10:24] <pieterh>    equals 64k subscribers
| [Monday 30 August 2010] [16:10:28] <pieterh>    one bitstring per topic
| [Monday 30 August 2010] [16:10:36] <pieterh>    or per expression in OpenAMQ
| [Monday 30 August 2010] [16:10:51] <sustrik>    how sparse was the bitmap?
| [Monday 30 August 2010] [16:10:59] <pieterh>    you might want to look at ipr_bits
| [Monday 30 August 2010] [16:11:05] <sustrik>    i recall it
| [Monday 30 August 2010] [16:11:15] <pieterh>    the bitmap can be very sparse but subscribers are not randomly scattered
| [Monday 30 August 2010] [16:11:19] <pieterh>    they cluster
| [Monday 30 August 2010] [16:11:37] <sustrik>    how does that affect performance?
| [Monday 30 August 2010] [16:11:50] <pieterh>    it means you need to treat 111111111 as efficiently as 000000000
| [Monday 30 August 2010] [16:12:06] <pieterh>    well, not in all cases but afair doing that helps
| [Monday 30 August 2010] [16:12:16] <sustrik>    it's up to choosing the compression algorithm
| [Monday 30 August 2010] [16:12:20] <pieterh>    we compared sflbits, which did compression
| [Monday 30 August 2010] [16:12:41] <pieterh>    against ipr_bits, which rakan el-khalil wrote, which did not do compression
| [Monday 30 August 2010] [16:12:46] <pieterh>    ipr_bits was much faster
| [Monday 30 August 2010] [16:13:10] <sustrik>    i am not sure what happened, but the issue here is that once you start getting cache misses
| [Monday 30 August 2010] [16:13:23] <sustrik>    the performance goes down something like 70 times
| [Monday 30 August 2010] [16:14:05] <sustrik>    accessing memory is sloooooooooow
| [Monday 30 August 2010] [16:14:06] <pieterh>    well, I don't have data on that
| [Monday 30 August 2010] [16:14:41] <sustrik>    anyway, it should be retested
| [Monday 30 August 2010] [16:14:41] <pieterh>    just to point out that we already solved these problems (probably poorly) more than once
| [Monday 30 August 2010] [16:15:03] <sustrik>    yes, i recall the algos in openamq
| [Monday 30 August 2010] [16:15:13] <pieterh>    inverted bitmaps go back a long way
| [Monday 30 August 2010] [16:15:23] <sustrik>    afair they should work very fast when the whole bitmap is in cache
| [Monday 30 August 2010] [16:15:31] <pieterh>    i've seen implementations in algol-68 :-)
| [Monday 30 August 2010] [16:15:50] <sustrik>    there haven't been caches back then :)
| [Monday 30 August 2010] [16:15:51] <pieterh>    on paper, in a museum...
| [Monday 30 August 2010] [16:16:05] <pieterh>    the whole RAM was a cache, real memory was rust
| [Monday 30 August 2010] [16:16:28] <sustrik>    an alternative to compression would be a cache oblivious algorithm...
| [Monday 30 August 2010] [16:16:42] <sustrik>    but i'm not sure that can be done with tries & bitmaps
| [Monday 30 August 2010] [19:09:35] <ffred_> hello.  Where can I find the coded examples from: http://www.zeromq.org/code:_start ?
| [Monday 30 August 2010] [19:10:24] <ffred_> I looked in the 2.0.8 download, but (at least to me) it wasn't obvious if these larger examples were included somewhere.
| [Tuesday 31 August 2010] [01:19:37] <CIA-20>    zeromq2: 03Martin Sustrik 07master * rf5acbb5 10/ (13 files): naming cleanup: zmq_encoder->encoder, zmq_decoder->decoder - http://bit.ly/bDJmD7
| [Tuesday 31 August 2010] [02:53:30] <poswald>   greetings everyone! Does anyone know of a zeromq based task scheduler written in python?
| [Tuesday 31 August 2010] [02:54:04] <poswald>   or maybe can someone explain to me if celery with zmq is a viable option?
| [Tuesday 31 August 2010] [02:57:38] <keffo> I looked at it, and I cant see why not?
| [Tuesday 31 August 2010] [02:57:47] <keffo> celery seems agnostic to the transport, so try it
| [Tuesday 31 August 2010] [03:14:56] <poswald>   The zeromq site mentioned dropping support because of patents somewhere... let me try to find it
| [Tuesday 31 August 2010] [03:15:51] <poswald>   oh it's on the faq http://zeromq.wikidot.com/area:faq
| [Tuesday 31 August 2010] [03:16:12] <poswald>   "Does MQ support AMQP protocol? It used to. The feature was dropped to protect MQ users from infringement on AMQP-related patents."
| [Tuesday 31 August 2010] [03:16:49] <poswald>   I assumed that Celery+ZMQ would be over AMQP protocol
| [Tuesday 31 August 2010] [03:48:22] <sustrik>   poswald, you may want to try 0mq/amqp bridge
| [Tuesday 31 August 2010] [03:53:21] <poswald>   I wonder if it makes sense for me to build something a little more minimal on top of zeromq rather than bridge over to amqp
| [Tuesday 31 August 2010] [04:08:09] <sustrik>   you can try, why not
| [Tuesday 31 August 2010] [04:12:21] <poswald>   do you know if zeroMQ has any plans for supporting persistent queues?
| [Tuesday 31 August 2010] [04:13:18] <pieterh>   poswald: not in 0MQ core but probably one day as a layer on top
| [Tuesday 31 August 2010] [04:43:16] <keffo> lol, printing msg data can have funny sideeffects, such as a pcspeaker beep :)
| [Tuesday 31 August 2010] [04:58:49] <theICEBear>    I just posted a patch to the mailing list for the select.cpp file. Now I am running into an access violation on shutdown of my sockets (and no they've been allocated on the thread closing them). Is this a known issue I can ignore until 2.1 goes out?
| [Tuesday 31 August 2010] [05:13:28] <sustrik>   theICEBear: is that trunk?
| [Tuesday 31 August 2010] [05:15:11] <theICEBear>    I am using 2.0.8
| [Tuesday 31 August 2010] [05:15:59] <sustrik>   that looks like an unknown issue
| [Tuesday 31 August 2010] [05:16:16] <sustrik>   can you please report it as a bug?
| [Tuesday 31 August 2010] [05:16:30] <sustrik>   having a backtrace attrached would be great
| [Tuesday 31 August 2010] [05:17:06] <theICEBear>    I will hold off a little while yet to make sure I am not the cause my self first, but I will do so when I am sure.
| [Tuesday 31 August 2010] [05:17:12] <sustrik>   ok
| [Tuesday 31 August 2010] [05:18:26] <theICEBear>    btw is there a D language binding for zmq, because I might find the time to do one if there isn't
| [Tuesday 31 August 2010] [05:21:06] <sustrik>   no, there isn't
| [Tuesday 31 August 2010] [05:21:46] <sustrik>   theICEBreat: I am looking at your patch
| [Tuesday 31 August 2010] [05:21:59] <sustrik>   what was the original problem?
| [Tuesday 31 August 2010] [05:22:28] <sustrik>   the both versions look semantically equivalent
| [Tuesday 31 August 2010] [05:22:48] <theICEBear>    the STL library in MSVC comes with something called SCL a security/verification thing that complains if you use the STL in an insecure unsafe way. The old code was triggering an assert through SCL
| [Tuesday 31 August 2010] [05:22:59] <sustrik>   aah
| [Tuesday 31 August 2010] [05:23:21] <sustrik>   that's something that haven't been there back when i've been using it
| [Tuesday 31 August 2010] [05:23:35] <theICEBear>    but yeah I couldn't see anything wrong with the code either. But apparently doing it.begin() + 1 is not good.
| [Tuesday 31 August 2010] [05:23:36] <sustrik>   that's MSVC2010?
| [Tuesday 31 August 2010] [05:23:57] <sustrik>   i see
| [Tuesday 31 August 2010] [05:24:01] <sustrik>   msvc2008 sp1
| [Tuesday 31 August 2010] [05:24:06] <theICEBear>    nope MSVC 2008 sp1 (MSVC 2010 is too buggy for us and its 64-bit support is wrong)
| [Tuesday 31 August 2010] [05:24:08] <sustrik>   ok, let me apply it
| [Tuesday 31 August 2010] [05:24:43] <sustrik>   ugh, i cannot :(
| [Tuesday 31 August 2010] [05:24:57] <theICEBear>    what did I do wrong now?
| [Tuesday 31 August 2010] [05:25:01] <theICEBear>    ;)
| [Tuesday 31 August 2010] [05:25:04] <sustrik>   waiting for mato to finish the check-in process
| [Tuesday 31 August 2010] [05:25:11] <theICEBear>    aah
| [Tuesday 31 August 2010] [05:25:38] <sustrik>   pieterh: what so you think?
| [Tuesday 31 August 2010] [05:25:56] <sustrik>   are we going to maintain 2.0 or will we move to 2.1?
| [Tuesday 31 August 2010] [05:26:22] <sustrik>   if the latter i can just ignore the 2.0 and simply commit it to 2.1
| [Tuesday 31 August 2010] [05:28:21] <mato>  sustrik: it's actually about "are you willing to maintain 2.0, with the help of the community"
| [Tuesday 31 August 2010] [05:29:08] <sustrik>   i am
| [Tuesday 31 August 2010] [05:29:13] <mato>  sustrik: all the process i have in mind does is it forces you to make that decision, and it *ensures* that any fixes in 2.0.x are also propagated correctly to master
| [Tuesday 31 August 2010] [05:30:01] <sustrik>   sure, np
| [Tuesday 31 August 2010] [05:30:08] <mato>  sustrik: in other words, all fixes are forward-ported, but the converse is not necessarily true; that decision must be made by the person commiting the fix on a case by case basis
| [Tuesday 31 August 2010] [05:30:26] <sustrik>   mato: yes
| [Tuesday 31 August 2010] [05:31:09] <mato>  sustrik: sorry for not giving you more detail, but i'm still stuck on this *%^$#^# problem for a client :-(
| [Tuesday 31 August 2010] [05:31:55] <mato>  sustrik: i guess it would be best if we sat down together at some point, went thru a bunch of 2.0.x and 2.1.x pending fixes with the process and made notes
| [Tuesday 31 August 2010] [05:32:30] <mato>  since you asking "what does this do?" or "what do i do now" is better than me trying to anticipate those questions :)
| [Tuesday 31 August 2010] [05:32:46] <sustrik>   depends how long it'll take to get that done
| [Tuesday 31 August 2010] [05:32:59] <sustrik>   if a long time, let's rather forget about maintaining 2.0
| [Tuesday 31 August 2010] [05:33:12] <mato>  take what done?
| [Tuesday 31 August 2010] [05:33:26] <sustrik>   the process guideliones
| [Tuesday 31 August 2010] [05:33:28] <pieterh>   sorry... was busy...
| [Tuesday 31 August 2010] [05:33:40] <mato>  sustrik: it needs a day together at the table
| [Tuesday 31 August 2010] [05:33:44] <pieterh>   we will maintain 2.0, of course, that's the stable version
| [Tuesday 31 August 2010] [05:33:45] <mato>  sustrik: or even half a day
| [Tuesday 31 August 2010] [05:34:27] <pieterh>   people are using 0MQ in production and we cannot make them choose between an unmaintained stable version and a maintained unstable version
| [Tuesday 31 August 2010] [05:34:35] <pieterh>   they will think we're idiots :-)
| [Tuesday 31 August 2010] [05:34:59] <mato>  sustrik: random question; have you seen any issues where a PUB socket was not getting messages even though it was connected and subscribed?
| [Tuesday 31 August 2010] [05:35:18] <sustrik>   no
| [Tuesday 31 August 2010] [05:35:34] <sustrik>   have you checked whether actual TCP connection exists?
| [Tuesday 31 August 2010] [05:35:36] <mato>  yes
| [Tuesday 31 August 2010] [05:35:38] <mato>  exists
| [Tuesday 31 August 2010] [05:35:41] <sustrik>   good
| [Tuesday 31 August 2010] [05:35:47] <sustrik>   do the data cross the wire?
| [Tuesday 31 August 2010] [05:35:49] <mato>  but it *seems* like 0mq is not sending anything down that particular pipe
| [Tuesday 31 August 2010] [05:36:00] <sustrik>   so it's PUB issue
| [Tuesday 31 August 2010] [05:36:13] <mato>  yeah
| [Tuesday 31 August 2010] [05:36:23] <sustrik>   any chance to reproduce?
| [Tuesday 31 August 2010] [05:36:33] <mato>  not with a simple test case at the moment
| [Tuesday 31 August 2010] [05:36:44] <mato>  but it's definitely reproducible
| [Tuesday 31 August 2010] [05:37:08] <sustrik>   mato: you are at your place?
| [Tuesday 31 August 2010] [05:37:11] <mato>  sustrik: yup
| [Tuesday 31 August 2010] [05:37:24] <sustrik>   ok, let me have a look at it in person
| [Tuesday 31 August 2010] [05:37:31] <mato>  that would be a great help :)
| [Tuesday 31 August 2010] [05:37:42] <mato>  maybe you'll see something obvious i'm not ...
| [Tuesday 31 August 2010] [05:38:03] <pieterh>   mato: did you already see if the SUB properly announces itself at startup?
| [Tuesday 31 August 2010] [05:38:06] <pieterh>   to the PUB socket
| [Tuesday 31 August 2010] [05:38:31] <mato>  no, am going to try that
| [Tuesday 31 August 2010] [05:38:43] <pieterh>   that's pretty vital to find out
| [Tuesday 31 August 2010] [05:39:10] <pieterh>   just printf in PUB socket when it gets identity from SUB
| [Tuesday 31 August 2010] [05:45:07] <mato>  pieterh: That's an interesting idea, I'm curious to see how you implement it :-)
| [Tuesday 31 August 2010] [05:45:21] <pieterh>   lol, very good
| [Tuesday 31 August 2010] [05:45:52] <mato>  anyway, looing at what tcp_listener_t is doing is a start
| [Tuesday 31 August 2010] [05:49:25] <mato>  sustrik: what is the process when a new TCP connection is accepted on a PUB socket?
| [Tuesday 31 August 2010] [05:49:45] <mato>  sustrik: tcp_listener_t is obviously involved, what then?
| [Tuesday 31 August 2010] [05:49:56] <mato>  sustrik: the last step would be pub_t::xattach_pipes?
| [Tuesday 31 August 2010] [05:50:47] <sustrik>   let me see
| [Tuesday 31 August 2010] [05:52:18] <sustrik>   well, it creates the zmq_init object
| [Tuesday 31 August 2010] [05:52:36] <sustrik>   and launches it (possibly in a different i/o thread
| [Tuesday 31 August 2010] [05:52:58] <sustrik>   you see 2 commands at the end here:
| [Tuesday 31 August 2010] [05:52:59] <sustrik>   send_plug (init);
| [Tuesday 31 August 2010] [05:52:59] <sustrik>       send_own (owner, init);
| [Tuesday 31 August 2010] [05:53:30] <sustrik>   send_plug sends a command to the init object saying "start working in the context of your new I/O thread"
| [Tuesday 31 August 2010] [05:53:44] <sustrik>   send_own is sent to the owning socket
| [Tuesday 31 August 2010] [05:53:53] <sustrik>   (which resides in the application thread)
| [Tuesday 31 August 2010] [05:54:24] <sustrik>   saying "you are owner of this init object; you are responsible for closing it"
| [Tuesday 31 August 2010] [05:54:26] <mato>  what i'm seeing looks like the TCP connection is accepted, but no pipe ends up being attached on the socket
| [Tuesday 31 August 2010] [05:54:43] <mato>  i should have 3 pipes, i only see two (pipes.size() / active == 2)
| [Tuesday 31 August 2010] [05:54:49] <sustrik>   are there identities exchanged?
| [Tuesday 31 August 2010] [05:55:05] <mato>  where can i trace that on the 0mq side?
| [Tuesday 31 August 2010] [05:55:12] <sustrik>   zmq_init_t
| [Tuesday 31 August 2010] [05:55:40] <sustrik>   zmq_init.cpp:151
| [Tuesday 31 August 2010] [05:55:45] <sustrik>   (v2.0.8)
| [Tuesday 31 August 2010] [05:56:08] <sustrik>   that's the point where the identity is both sent to the peer and received from the peer
| [Tuesday 31 August 2010] [05:58:15]      * sustrik is moving to mato's place
| [Tuesday 31 August 2010] [05:58:19] <mato>  what creates the zmq_init_t?
| [Tuesday 31 August 2010] [05:58:28] <sustrik>   zmq_listener_t
| [Tuesday 31 August 2010] [05:58:31] <sustrik>   or zmq_connecter_t
| [Tuesday 31 August 2010] [05:58:38] <mato>  good, listener in this case 
| [Tuesday 31 August 2010] [05:58:39] <mato>  ok
| [Tuesday 31 August 2010] [08:20:11] <mato>  sustrik: ping!
| [Tuesday 31 August 2010] [08:20:13] <mato>  sustrik: got it
| [Tuesday 31 August 2010] [08:20:22] <mato>  sustrik: sudden inspiration...
| [Tuesday 31 August 2010] [08:20:35] <mato>  sustrik: the zmq code is all correct...
| [Tuesday 31 August 2010] [08:20:50] <mato>  sustrik: but, i don't close sockets (because of blah blah....)
| [Tuesday 31 August 2010] [08:21:03] <mato>  sustrik: so, why would a socket start to get ignored
| [Tuesday 31 August 2010] [08:21:22] <mato>  sustrik: i added an assert to zmq::select_t to check if we're trying to add more than FD_SETSIZE sockets 
| [Tuesday 31 August 2010] [08:21:25] <mato>  sustrik: and bang....
| [Tuesday 31 August 2010] [08:22:28] <sustrik>   mato: pong
| [Tuesday 31 August 2010] [08:22:45] <sustrik>   aha
| [Tuesday 31 August 2010] [08:22:48] <sustrik>   64 limit
| [Tuesday 31 August 2010] [08:29:58] <mato>  sustrik: ok i will discuss with PH what to do... in any case, 2.0.x and 2.1 need to get that assertion in there
| [Tuesday 31 August 2010] [08:30:03] <mato>  i will handle that 
| [Tuesday 31 August 2010] [08:30:17] <mato>  people should at least know if they're hitting that limit
| [Tuesday 31 August 2010] [08:30:26] <sustrik>   ack
| [Tuesday 31 August 2010] [08:30:37] <mato>  further, ZMQ should redefine FD_SETSIZE to 1024 on windows which at least makes it able to handle more than 64 sockets
| [Tuesday 31 August 2010] [08:30:56] <mato>  i'll take care of those two fixesa
| [Tuesday 31 August 2010] [08:31:26] <mato>  and will get you those workflow commands ASAP, but need something quick for the client now
| [Tuesday 31 August 2010] [08:31:42] <pieterh>   2G mobile internet...
| [Tuesday 31 August 2010] [08:31:49] <pieterh>   someone calls you, Internet dies...
| [Tuesday 31 August 2010] [08:32:08] <pieterh>   Xitami used to set FD_SETSIZE to 1024 on Windows, since 1996 or so
| [Tuesday 31 August 2010] [08:32:18] <pieterh>   mato: in prelude.h, it's ancient code
| [Tuesday 31 August 2010] [08:35:31] <keffo> pieterh, sustrik; Up for some discussion?
| [Tuesday 31 August 2010] [08:35:55] <keffo> I have (basically) two ideas, that would help me tremendously, open the api a bit (while retaining current functionality)
| [Tuesday 31 August 2010] [08:36:45] <keffo> A: Make xreq able to do what xrep does now, ie send down a known route (with supplied identities), and B; custom LB 
| [Tuesday 31 August 2010] [09:15:13] <mikko> sustrik: i might be in london on 14th!
| [Tuesday 31 August 2010] [09:15:35] <sustrik>   mikko: great!
| [Tuesday 31 August 2010] [09:15:43] <mikko> do you know roughly in which area you are going to be?
| [Tuesday 31 August 2010] [09:16:07] <sustrik>   in the very center
| [Tuesday 31 August 2010] [09:16:20] <mikko> i work very close to tottenham court road tube station
| [Tuesday 31 August 2010] [09:16:48] <sustrik>   let's see whether more people are interested
| [Tuesday 31 August 2010] [09:17:19] <mikko> are you coming for work or holiday?
| [Tuesday 31 August 2010] [09:17:25] <sustrik>   work
| [Tuesday 31 August 2010] [09:17:59] <sustrik>   i just though that quite a few people on mailing list may be located there
| [Tuesday 31 August 2010] [09:18:01] <sustrik>   let's see
| [Tuesday 31 August 2010] [09:41:28] <fredix>    hi
| [Tuesday 31 August 2010] [09:41:45] <sustrik>   hi
| [Tuesday 31 August 2010] [09:41:51] <fredix>    is there a zmq_server with zeromq 2 ?
| [Tuesday 31 August 2010] [09:42:04] <sustrik>   no
| [Tuesday 31 August 2010] [09:42:14] <sustrik>   where have you found reference to it?
| [Tuesday 31 August 2010] [09:42:36] <fredix>    in tutorials http://www.zeromq.org/tutorials:_start
| [Tuesday 31 August 2010] [09:43:07] <sustrik>   ugh, these are outdated
| [Tuesday 31 August 2010] [09:43:12] <sustrik>   back from version 1.0
| [Tuesday 31 August 2010] [09:43:23] <sustrik>   pieterh: why have you put these online?
| [Tuesday 31 August 2010] [09:43:31] <fredix>    in fact I'm looking for a queue server like gearman or beanstalkd, and zeromq seems to be cute
| [Tuesday 31 August 2010] [09:43:48] <sustrik>   depends on what you need
| [Tuesday 31 August 2010] [09:44:03] <sustrik>   there are "mini-servers" in 0mq
| [Tuesday 31 August 2010] [09:44:10] <sustrik>   called "devices"
| [Tuesday 31 August 2010] [09:44:17] <sustrik>   say a stand-alone queue
| [Tuesday 31 August 2010] [09:44:29] <sustrik>   but nothing as complex as real messaging server
| [Tuesday 31 August 2010] [09:44:45] <sustrik>   with all the admin stuff, monitoring etc.
| [Tuesday 31 August 2010] [09:44:55] <fredix>    I need make asynchronous job and a persistance server queu
| [Tuesday 31 August 2010] [09:44:58] <fredix>    queue
| [Tuesday 31 August 2010] [09:45:08] <sustrik>   sorry, no persistence
| [Tuesday 31 August 2010] [09:45:13] <fredix>    arg
| [Tuesday 31 August 2010] [09:45:43] <sustrik>   if you want to experiment you can use 0mq clients with RabbitMQ server
| [Tuesday 31 August 2010] [09:45:49] <sustrik>   there's a bridge project
| [Tuesday 31 August 2010] [09:45:54] <sustrik>   but it's not yet stable
| [Tuesday 31 August 2010] [09:46:05] <fredix>    ok
| [Tuesday 31 August 2010] [10:05:26] <alfborge>  sustrik: Persistant queues, does that mean that the messaging system guarantees that the message is delivered if the client succeeds in writing the message to the queue?
| [Tuesday 31 August 2010] [10:05:33] <alfborge>  Or is there more to it?
| [Tuesday 31 August 2010] [10:06:05] <sustrik>   "persistent queue" means that messages are written to the disk
| [Tuesday 31 August 2010] [10:06:33] <sustrik>   and that messages are read from the disk when queue is started
| [Tuesday 31 August 2010] [10:06:41] <sustrik>   however, there are no additional reliability guarantees
| [Tuesday 31 August 2010] [10:07:07] <alfborge>  So the point is that you can reboot the system without loosing messages in the queue?
| [Tuesday 31 August 2010] [10:08:40] <sustrik>   yes, that's what "persistent queue is for"
| [Tuesday 31 August 2010] [10:08:49] <sustrik>   you can still loose messages on the wire
| [Tuesday 31 August 2010] [10:08:56] <sustrik>   messages processed in the clients
| [Tuesday 31 August 2010] [10:08:58] <sustrik>   etc.
| [Tuesday 31 August 2010] [10:22:32] <Steve-o>   there is a significant performance difference between persistent messaging and guaranteed messaging, most people really don't need the latter or can get away with database light weight transaction managment
| [Tuesday 31 August 2010] [11:00:59] <andrewvc>  cremes, I was wondering if you were around
| [Tuesday 31 August 2010] [11:01:29] <andrewvc>  I've got a zmqmachine question I was hoping you'd answer
| [Tuesday 31 August 2010] [11:01:34] <cremes>    yeah, but i'm at work so i have limited time; what's up?
| [Tuesday 31 August 2010] [11:02:18] <andrewvc>  well if you don't have time to answer that's cool http://github.com/andrewvc/learn-ruby-zeromq/blob/master/003_ZMQMachine/002_a_pub_sub_example.rb#L28
| [Tuesday 31 August 2010] [11:02:28] <andrewvc>  sleeping there is bad right, since we're in a reactor
| [Tuesday 31 August 2010] [11:02:40] <cremes>    yes, you should never sleep
| [Tuesday 31 August 2010] [11:02:47] <cremes>    what are you trying to accomplish with that sleep?
| [Tuesday 31 August 2010] [11:02:48] <andrewvc>  but on_writable acts as a busy loop w/o that. Changing the poll interval doesn't seem to help
| [Tuesday 31 August 2010] [11:02:56] <cremes>    ah, good point
| [Tuesday 31 August 2010] [11:03:06] <cremes>    i have a little pattern that i follow when using the reactor
| [Tuesday 31 August 2010] [11:03:07] <andrewvc>  do you just register / dereister it
| [Tuesday 31 August 2010] [11:03:15] <andrewvc>  oh, what is it?
| [Tuesday 31 August 2010] [11:03:20] <cremes>    let me pastie something for you... hang on a few
| [Tuesday 31 August 2010] [11:03:24] <andrewvc>  awesome
| [Tuesday 31 August 2010] [11:07:22] <cremes>    andrewvc: try this technique:  http://gist.github.com/559166
| [Tuesday 31 August 2010] [11:07:40] <cremes>    this is why i added register_writable/deregister_writable to the Reactor class
| [Tuesday 31 August 2010] [11:07:52] <cremes>    i ran into that exact same problem; this technique cures it
| [Tuesday 31 August 2010] [11:08:22] <cremes>    of course, you *could* write directly to the socket and not use the #on_writable callback at all if you choose
| [Tuesday 31 August 2010] [11:08:27] <andrewvc>  cool, thanks, I'll put that in
| [Tuesday 31 August 2010] [11:08:38] <cremes>    np
| [Tuesday 31 August 2010] [11:08:52] <andrewvc>  hmmm, so I can just leave on_writable undefined as well?
| [Tuesday 31 August 2010] [11:09:18] <cremes>    for certain socket types you can; for others the framework enforces it
| [Tuesday 31 August 2010] [11:09:25] <andrewvc>  like req/rep?
| [Tuesday 31 August 2010] [11:09:45] <cremes>    you could just stub it out like this... def on_writable(socket); @reactor.deregister_writable(socket); end
| [Tuesday 31 August 2010] [11:09:51] <andrewvc>  oh, gotcha
| [Tuesday 31 August 2010] [11:09:53] <cremes>    assuming you have a @reactor instance var
| [Tuesday 31 August 2010] [11:09:58] <andrewvc>  yep, got one
| [Tuesday 31 August 2010] [11:10:23] <cremes>    i tried to make the defaults sensible (convention over configuration) but it's still early in zmqmachine's life
| [Tuesday 31 August 2010] [11:10:32] <cremes>    perhaps i chose the wrong defaults; feedback would be nice
| [Tuesday 31 August 2010] [11:10:38] <andrewvc>  definitely
| [Tuesday 31 August 2010] [11:11:06] <cremes>    ping me if you need anything more
| [Tuesday 31 August 2010] [11:11:25] <andrewvc>  i actually hit some weird bugs with deregister last night (probably my mistake, but needing some better err handling), that I had trouble debugging at 11:30pm :), I'm going to give it a shot today, see what happens.
| [Tuesday 31 August 2010] [11:13:30] <andrewvc>  ah, hit it just now
| [Tuesday 31 August 2010] [11:14:17] <andrewvc>  I'll open an issue on github
| [Tuesday 31 August 2010] [11:38:26] <cremes>    andrewvc: pushed new gems for ffi-rzmq and zmqmachine; i fixed a bunch of bugs but then forgot to run "gem push" to upload them to rubygems
| [Tuesday 31 August 2010] [11:38:35] <cremes>    these new releases should fix that issue you reported
| [Tuesday 31 August 2010] [11:38:44] <andrewvc>  ah, sweet, yeah hehe, events / event
| [Tuesday 31 August 2010] [11:39:08] <andrewvc>  thanks!
| [Tuesday 31 August 2010] [11:39:43] <andrewvc>  also, now I don't need to bundle the latest ffi-rzmq with learn-zeromq-ruby, which will be nice
| [Tuesday 31 August 2010] [11:40:41] <cremes>    yep
| [Tuesday 31 August 2010] [11:41:06] <cremes>    plus, there will be a new ffi gem released soon... i've been bugging the author to get one out so folks don't have to build master by hand
| [Tuesday 31 August 2010] [11:43:02] <andrewvc>  yeah, that'll be great, it's time
| [Tuesday 31 August 2010] [12:00:49] <pieterh>   keffo: sorry, was away for a while
| [Tuesday 31 August 2010] [12:03:19] <keffo> As was I, dozed off on the couch for halv an hour :)
| [Tuesday 31 August 2010] [12:04:05] <pieterh>   the last thing I saw from your was "A: make xreq able to do what xrep does now..."
| [Tuesday 31 August 2010] [12:16:18] <cremes>    pieterh: is your chicago visit connected to that financial firm i hooked you up with a few months back?
| [Tuesday 31 August 2010] [12:18:24] <pieterh>   cremes: yes, probably
| [Tuesday 31 August 2010] [12:18:43] <pieterh>   let me check if it's the same one
| [Tuesday 31 August 2010] [12:19:15] <pieterh>   cremes: yes :-)
| [Tuesday 31 August 2010] [12:24:44] <cremes>    cool... hopefully they'll open the talk to the public (though i know the cio so i'm sure i could come to it anyway...)
| [Tuesday 31 August 2010] [12:26:49] <pieterh>   yeah, but I doubt they'll have a bar
| [Tuesday 31 August 2010] [12:27:22] <pieterh>   so... i've been working on a new site for 0MQ beginners
| [Tuesday 31 August 2010] [12:28:34] <pieterh>   it's going to be www.zeromq.com
| [Tuesday 31 August 2010] [12:28:47] <pieterh>   so that the existing .org site can become a real community portal/map
| [Tuesday 31 August 2010] [13:00:59] <keffo> pieterh, Sorry, gf came home upset due to crappy boss behaviour..
| [Tuesday 31 August 2010] [13:01:33] <keffo> pieterh, So, having xreq capable of providing a route, the same way xrep does
| [Tuesday 31 August 2010] [13:10:52] <pieterh>   keffo: why do you need this, what's your use case?
| [Tuesday 31 August 2010] [13:18:24] <keffo> To reach a specific queue, so it can nuke it's worker processes, for instance
| [Tuesday 31 August 2010] [13:18:44] <keffo> N queue-steps down, so to speak :)
| [Tuesday 31 August 2010] [13:19:23] <keffo> Also, why is there no send_to_identity()? :)
| [Tuesday 31 August 2010] [13:20:10] <pieterh>   keffo: I guess a send-to-identity could be put into layers above the API, such as ZFL or any language binding
| [Tuesday 31 August 2010] [13:20:21] <pieterh>   though since identity is actually a stack it's perhaps not that simple
| [Tuesday 31 August 2010] [13:20:44] <pieterh>   you can use XREP to reach a specific node
| [Tuesday 31 August 2010] [13:21:00] <keffo> hum?
| [Tuesday 31 August 2010] [13:21:04] <pieterh>   if you are willing to disassemble, reassemble the stack you can use XREP to talk to XREP
| [Tuesday 31 August 2010] [13:21:19] <pieterh>   as far as I understand it, I've not tried this myself
| [Tuesday 31 August 2010] [13:21:35] <keffo> I already do that now to route back, I just dont see any reason that shouldnt work the other direction?
| [Tuesday 31 August 2010] [13:21:54] <pieterh>   i mean, why change XREQ's behaviour when XREP is what you want...?
| [Tuesday 31 August 2010] [13:22:29] <pieterh>   the names for XREQ and XREP don't make too much sense in fact
| [Tuesday 31 August 2010] [13:22:54] <pieterh>   what these are, is a SEND socket and a ROUTE socket or something like that
| [Tuesday 31 August 2010] [13:22:55] <keffo> That doesn't make sense, I can initiate with a reply? =)
| [Tuesday 31 August 2010] [13:23:21] <pieterh>   XREP is not really a reply (only) socket
| [Tuesday 31 August 2010] [13:23:21] <keffo> But I get what you mean
| [Tuesday 31 August 2010] [13:23:28] <pieterh>   that's just its obvious use case
| [Tuesday 31 August 2010] [13:23:47] <pieterh>   but replies are just one use case for explicitly addressed messages
| [Tuesday 31 August 2010] [13:24:07] <pieterh>   i feel we need to find better names, as we did for push/pull
| [Tuesday 31 August 2010] [13:24:24] <keffo> Hum, so in theory they could be consolidated into one type, like sendrouted( route, msg )? 
| [Tuesday 31 August 2010] [13:24:43] <pieterh>   well, no
| [Tuesday 31 August 2010] [13:24:57] <pieterh>   XREQ is exactly the same as PUSH but within the req-rep pattern
| [Tuesday 31 August 2010] [13:25:12] <pieterh>   where as XREP is like PUSH with the addition of routing capability
| [Tuesday 31 August 2010] [13:25:31] <pieterh>   uhm, sorry
| [Tuesday 31 August 2010] [13:25:41] <keffo> sure, but why cant xreq handle the routing in the same way as xrep does?
| [Tuesday 31 August 2010] [13:25:42] <pieterh>   XREP is like PUSH+PULL together
| [Tuesday 31 August 2010] [13:25:54] <sustrik>   :)
| [Tuesday 31 August 2010] [13:25:56] <pieterh>   all you're asking is "please delete XREQ socket type"
| [Tuesday 31 August 2010] [13:26:00] <pieterh>   right?
| [Tuesday 31 August 2010] [13:26:08] <pieterh>   kurva
| [Tuesday 31 August 2010] [13:26:18] <pieterh>   XREQ is like PUSH+PULL, XREP is like PUSH+PULL+routing
| [Tuesday 31 August 2010] [13:26:28] <sustrik>   i think what keffo wants is goodies from 0mq without having to conform to strictly defined patterns
| [Tuesday 31 August 2010] [13:26:32] <keffo> Not really, I want to be able to supply a route to xreq, in the same way I do to xreq... Essentially bypassing any loadbalancing I guess
| [Tuesday 31 August 2010] [13:27:09] <pieterh>   sustrik: is my assertion that "XREQ is like PUSH+PULL, XREP is like PUSH+PULL+routing" valid?
| [Tuesday 31 August 2010] [13:27:40] <sustrik>   yes
| [Tuesday 31 August 2010] [13:28:15] <sustrik>   keffo: the problem is that you don't know the route
| [Tuesday 31 August 2010] [13:28:34] <sustrik>   the only point where you get the route is when you get a request in REP socket
| [Tuesday 31 August 2010] [13:28:59] <sustrik>   you would have to hardcode the routes
| [Tuesday 31 August 2010] [13:29:00] <keffo> if I have a client that sends a message through 2-3-4 hops of queue goodness to reach a worker, I'd like to be able to traverse that same path again
| [Tuesday 31 August 2010] [13:29:01] <keffo> I guess this is a hack to get around the pub/sub subscriber overhead
| [Tuesday 31 August 2010] [13:29:17] <keffo> sustrik, I do know the route :)
| [Tuesday 31 August 2010] [13:29:18] <pieterh>   sustrik: can you set identities explicitly, send them via another flow, and then use XREP to address them?
| [Tuesday 31 August 2010] [13:29:36] <keffo> Ah, you mean the route is popped off as it goes, on a return xrep?
| [Tuesday 31 August 2010] [13:29:45] <pieterh>   keffo: yes
| [Tuesday 31 August 2010] [13:29:59] <pieterh>   xrep pops the top address, uses it to route the rest (on send)
| [Tuesday 31 August 2010] [13:30:15] <pieterh>   and xrep pushes the incoming address (on recv)
| [Tuesday 31 August 2010] [13:30:18] <sustrik>   which pieterh: imo, it's like wanting to send an IP datagram through a specific path
| [Tuesday 31 August 2010] [13:30:30] <pieterh>   yeah, it's abuse of patterns
| [Tuesday 31 August 2010] [13:30:34] <sustrik>   in theory doable
| [Tuesday 31 August 2010] [13:30:37] <keffo> I already explicitly name everything, so I'd like the end worker to send back "this is me, this is how I was reached, contact me here to get status", basically
| [Tuesday 31 August 2010] [13:30:37] <sustrik>   but not wise
| [Tuesday 31 August 2010] [13:30:48] <pieterh>   keffo: just use XREP
| [Tuesday 31 August 2010] [13:31:15] <pieterh>   hang on... you want to re-route a request BACK to the same worker through a series of hops...?
| [Tuesday 31 August 2010] [13:31:21] <keffo> Yup
| [Tuesday 31 August 2010] [13:31:25] <pieterh>   ok...
| [Tuesday 31 August 2010] [13:31:28] <pieterh>   so here's the problem
| [Tuesday 31 August 2010] [13:31:33] <pieterh>   you are mixing two different flows into one
| [Tuesday 31 August 2010] [13:31:38] <pieterh>   it won't work smoothly
| [Tuesday 31 August 2010] [13:31:49] <keffo> Care to elaborate, because I really dont see why not..?
| [Tuesday 31 August 2010] [13:31:54] <pieterh>   and when it works it'll be fragile and horrid
| [Tuesday 31 August 2010] [13:32:07] <pieterh>   OTOH you have a workload distribution abstraction
| [Tuesday 31 August 2010] [13:32:15] <pieterh>   that routes work to workers using various algorithms
| [Tuesday 31 August 2010] [13:32:19] <pieterh>   workers can come, go, etc.
| [Tuesday 31 August 2010] [13:32:22] <pieterh>   that is pattern A
| [Tuesday 31 August 2010] [13:32:27] <keffo> yep
| [Tuesday 31 August 2010] [13:32:35] <pieterh>   next, you have peer to peer addressing between clients and workers
| [Tuesday 31 August 2010] [13:32:45] <pieterh>   where you want to talk to workers specifically (bribery and corruption I assume)
| [Tuesday 31 August 2010] [13:32:47] <pieterh>   that is pattern B
| [Tuesday 31 August 2010] [13:32:58] <keffo> yeah, although only to queues, but that's besides the point
| [Tuesday 31 August 2010] [13:33:05] <pieterh>   they are not the same pattern and the 0MQ Way is to use one set of sockets per pattern / per flow
| [Tuesday 31 August 2010] [13:33:20] <pieterh>   sockets are cheap
| [Tuesday 31 August 2010] [13:33:58] <keffo> But I cant see a good way to reach a specific node?
| [Tuesday 31 August 2010] [13:34:08] <pieterh>   you perhaps want a broker in the middle
| [Tuesday 31 August 2010] [13:34:40] <pieterh>   here are some random ideas to play with...
| [Tuesday 31 August 2010] [13:34:57] <pieterh>   send endpoints in messages and get workers to connect back onto those endpoints (using REQ/REP)
| [Tuesday 31 August 2010] [13:35:21] <pieterh>   use broker to act as hub, turn the whole thing into boring hub / spoke architecture with a single fixed endpoint
| [Tuesday 31 August 2010] [13:35:38] <pieterh>   construct your own message stacks via black magic and use XREP to route these
| [Tuesday 31 August 2010] [13:37:18] <keffo> nn
| [Tuesday 31 August 2010] [13:37:18] <keffo> mm
| [Tuesday 31 August 2010] [13:37:24] <pieterh>   :-)
| [Tuesday 31 August 2010] [13:38:20] <keffo> I'm content to do heartbeating between local queue & worker processes (all localhost), but I'd rather be able to query status off that queue at will
| [Tuesday 31 August 2010] [13:39:17] <keffo> I know exactly how I reached that queue from the response, so I figured it would be a pretty decent solution if I could just supply that same route and ask about it's status whenever I want..
| [Tuesday 31 August 2010] [13:39:32] <keffo> (the first using pub/sub)
| [Tuesday 31 August 2010] [13:49:16] <pieterh>   IMO if you want health monitoring, you want a specific socket flow for that
| [Tuesday 31 August 2010] [13:56:28] <keffo> Adding another socket flow, while the first one is completely idle, doesn't really sound like a proper solution to me :)
| [Tuesday 31 August 2010] [13:59:27] <pieterh>   it's not about idle or not, but about using sockets in the way nature (and Sustrik) intended
| [Tuesday 31 August 2010] [14:01:01] <keffo> So what health monitoring system would fit then?
| [Tuesday 31 August 2010] [14:01:33] <keffo> I cant pub/sub across the whole system right now, and the endpoints cant connect directly to the source
| [Tuesday 31 August 2010] [14:01:49] <pieterh>   well... what seems to be the best practice is to build a heartbeat flow separately from data and work flow
| [Tuesday 31 August 2010] [14:01:56] <keffo> Also, I need the ability to nuke a runaway process, for instance
| [Tuesday 31 August 2010] [14:02:11] <keffo> sure, an admin-channel sortof
| [Tuesday 31 August 2010] [14:02:14] <pieterh>   i'm hoping eventually heartbeating would go into sockets as standard but that's not clear how or if
| [Tuesday 31 August 2010] [14:02:29] <pieterh>   yup, a control/admin channel
| [Tuesday 31 August 2010] [14:03:14] <sustrik>   yes, the heartbeating is a tricky stuff
| [Tuesday 31 August 2010] [14:04:06] <sustrik>   if you think about it in depth, it looks like the only real use case for it is guaranteed delivery
| [Tuesday 31 August 2010] [14:04:15] <sustrik>   which is an insolvable problem in itself
| [Tuesday 31 August 2010] [14:04:47] <pieterh>   "unsolvable" assumes the goal is "perfectly solvable", which it isn't
| [Tuesday 31 August 2010] [14:05:01] <pieterh>   the goal is "good enough", and that's solvable
| [Tuesday 31 August 2010] [14:05:03] <sustrik>   unsolvable by technical means
| [Tuesday 31 August 2010] [14:05:24] <pieterh>   i pay fedex for guaranteed delivery but packages still get lost in customs sometimes
| [Tuesday 31 August 2010] [14:05:38] <sustrik>   yes, good analogy
| [Tuesday 31 August 2010] [14:05:51] <pieterh>   it's solvable if you are willing to accept some failures and be able to detect and recover from them
| [Tuesday 31 August 2010] [14:06:01] <pieterh>   which in effect solves it
| [Tuesday 31 August 2010] [14:06:04] <pieterh>   fedex will resend
| [Tuesday 31 August 2010] [14:06:12] <keffo> the whole point I'm tryijng to make is, I get both of those for free with what I already have, given the ability to direct the route downwards as well as upstream
| [Tuesday 31 August 2010] [14:06:19] <pieterh>   customs may continue to snag the packages but eventually one will get through
| [Tuesday 31 August 2010] [14:06:33] <pieterh>   keffo: so you don't have any problem them? :-)
| [Tuesday 31 August 2010] [14:07:13] <pieterh>   keffo: routing downwards means constructing that address stack
| [Tuesday 31 August 2010] [14:07:17] <pieterh>   that's unavoidable
| [Tuesday 31 August 2010] [14:07:30] <pieterh>   it's not something you can delegate to a socket and magic will happen
| [Tuesday 31 August 2010] [14:07:44] <pieterh>   xrep only knows how to do it because the message got routed that way to start with
| [Tuesday 31 August 2010] [14:09:55] <pieterh>   you could somehow send that address stack BACK to the client so it can use it to route downwards
| [Tuesday 31 August 2010] [14:10:02] <pieterh>   but now if your infrastructure changes at all, you're dead
| [Tuesday 31 August 2010] [14:10:25] <pieterh>   it's like sending email to someone and trying to specify all the intermediate servers
| [Tuesday 31 August 2010] [14:44:55] <ModusPwnens>   hi
| [Tuesday 31 August 2010] [14:55:18] <ModusPwnens>   does anyone know what would cause an enormous drop in performance with zeromq?
| [Tuesday 31 August 2010] [14:56:07] <pieterh>   ModusPwnens: what OS?
| [Tuesday 31 August 2010] [14:56:16] <pieterh>   and do you have a simple reproducible case?
| [Tuesday 31 August 2010] [14:56:43] <ModusPwnens>   i have some code I could put on a pastebin
| [Tuesday 31 August 2010] [14:56:46] <ModusPwnens>   and its windows 7
| [Tuesday 31 August 2010] [14:57:21] <ModusPwnens>   this problem has afflicted me several times though. I am trying to do benchmark testing with code I have, but when I try to write it using the examples as a reference, I get a pitiful 12 messages per second
| [Tuesday 31 August 2010] [14:57:43] <ModusPwnens>   when I essentially copy line for line the example code, I get the normal amount, which is about 600,000 messages per second
| [Tuesday 31 August 2010] [14:57:54] <pieterh>   we've seen something similar recently
| [Tuesday 31 August 2010] [14:58:17] <ModusPwnens>   I feel like its just user error on my part
| [Tuesday 31 August 2010] [14:58:19] <ModusPwnens>   since I am new to zeromq
| [Tuesday 31 August 2010] [14:58:26] <pieterh>   but it was inside a complex case and not obvious to identity
| [Tuesday 31 August 2010] [14:58:28] <ModusPwnens>   so I must be missing something important
| [Tuesday 31 August 2010] [14:58:37] <pieterh>   what I suggest is starting with the examples, literally
| [Tuesday 31 August 2010] [14:58:51] <ModusPwnens>   Yeah i've combed through them
| [Tuesday 31 August 2010] [14:58:55] <ModusPwnens>   I did the hello world example just fine
| [Tuesday 31 August 2010] [14:58:57] <pieterh>   and then test every time you change something
| [Tuesday 31 August 2010] [14:59:10] <pieterh>   what language?
| [Tuesday 31 August 2010] [14:59:13] <ModusPwnens>   c++
| [Tuesday 31 August 2010] [14:59:22] <ModusPwnens>   although I am using the c language bindings
| [Tuesday 31 August 2010] [14:59:26] <ModusPwnens>   because that's what the examples are in
| [Tuesday 31 August 2010] [14:59:36] <pieterh>   sure
| [Tuesday 31 August 2010] [14:59:48] <pieterh>   well... what would I do... stupidly...
| [Tuesday 31 August 2010] [14:59:56] <ModusPwnens>   hmm?
| [Tuesday 31 August 2010] [15:00:02] <pieterh>   profile the code and see what it's actually doing
| [Tuesday 31 August 2010] [15:00:13] <pieterh>   insert printf statements, capture in file
| [Tuesday 31 August 2010] [15:00:28] <pieterh>   remove whole chunks until it works 'normally' and then see what the significant difference i
| [Tuesday 31 August 2010] [15:00:32] <pieterh>   *is
| [Tuesday 31 August 2010] [15:01:00] <pieterh>   finally if you get to a minimal testcase you are sure should work, but does not, report it
| [Tuesday 31 August 2010] [15:01:19] <ModusPwnens>   well no it's not that. It works. It's just really slow.
| [Tuesday 31 August 2010] [15:01:34] <pieterh>   sure
| [Tuesday 31 August 2010] [15:01:41] <pieterh>   and CPU is probably really high
| [Tuesday 31 August 2010] [15:01:49] <pieterh>   so it's doing _something_ unexpected
| [Tuesday 31 August 2010] [15:01:57] <pieterh>   not sleeping
| [Tuesday 31 August 2010] [15:02:50] <pieterh>   i gotta go, sorry, but i'm curious to know what the outcome is...
| [Tuesday 31 August 2010] [15:03:32] <ModusPwnens>   Hmm. The benchtesting I am doing is to test performance with google protocol buffers. So in the loop I am encoding messages and storing them into messages, but would that really cause something as low as 12 messages per second...?
| [Tuesday 31 August 2010] [15:03:34] <ModusPwnens>   oh ok.
| [Tuesday 31 August 2010] [15:03:56] <ModusPwnens>   I will let you know what it was when i figure it out
| [Tuesday 31 August 2010] [15:09:31] <Steve-o>   of course not, but you can also try #defing out the protobuf code to see if it changes performance
| [Tuesday 31 August 2010] [15:22:45] <CIA-20>    zeromq2: 03Martin Sustrik 07master * r090e460 10/ (10 files): naming cleanup: yarray->array - http://bit.ly/cQUTl0
| [Tuesday 31 August 2010] [19:53:53] <ModusPwnens>   hi
| [Tuesday 31 August 2010] [20:05:23] <ModusPwnens>   can anyone tell me about the size method for zeromq?