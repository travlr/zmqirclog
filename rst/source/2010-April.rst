===============
2010-April
===============

| [Thursday 01 April 2010] [04:02:21] <sustrik>   mikko: hi
| [Thursday 01 April 2010] [04:03:24] <mikko> hi
| [Thursday 01 April 2010] [04:03:49] <sustrik>   what's the problem?
| [Thursday 01 April 2010] [04:03:52] <mikko> /usr/local/lib/libzmq.so.0: undefined symbol: _ZN3zmq7epoll_t4loopEv
| [Thursday 01 April 2010] [04:04:08] <sustrik>   only a single one?
| [Thursday 01 April 2010] [04:04:19] <sustrik>   single undefined symbol?
| [Thursday 01 April 2010] [04:04:23] <mikko> there are other symbols as well but it all seems very random
| [Thursday 01 April 2010] [04:04:47] <mikko> i can run the program let's say 8 times successfully and on ninth i get lookup error
| [Thursday 01 April 2010] [04:04:58] <mikko> i wonder if something happened to my environment
| [Thursday 01 April 2010] [04:05:01] <sustrik>   strange
| [Thursday 01 April 2010] [04:05:20] <sustrik>   looks like your system is broken
| [Thursday 01 April 2010] [04:08:06] <mikko> trying with LD_DEBUG now
| [Thursday 01 April 2010] [04:11:15] <mikko> http://pastie.org/898514
| [Thursday 01 April 2010] [04:11:19] <mikko> not sure what this tells me
| [Thursday 01 April 2010] [04:12:01] <mikko> trying with clean system
| [Thursday 01 April 2010] [04:21:10] <mikko> sustrik: also getting this occasionally symbol lookup error: /usr/local/lib/libzmq.so.0: undefined symbol: uuid_unparse, version UUID_1.0
| [Thursday 01 April 2010] [04:21:20] <mikko> but not on all runs, it seems very random
| [Thursday 01 April 2010] [04:21:53] <sustrik>   there must be something wrong with your system; library loading should be a deterministic process
| [Thursday 01 April 2010] [04:22:10] <sustrik>   can you try on a different box?
| [Thursday 01 April 2010] [04:22:57] <mikko> yeah, setting up another VM on the background
| [Thursday 01 April 2010] [05:24:46] <sjampoo>   Cool, got PGM working in Python code. Seems that i can only use a single context per process (because of refcounting?). 
| [Thursday 01 April 2010] [05:25:11] <sjampoo>   How do i set an optimal multicast rate, by experimentation? 
| [Thursday 01 April 2010] [05:47:54] <sustrik>   sjampoo: yes, one context per process suffices
| [Thursday 01 April 2010] [05:48:17] <sustrik>   as for the rate, set it up to match your requirements
| [Thursday 01 April 2010] [05:48:27] <mikko> oh, btw i forgot to mention: i am working on php bindings for zeromq
| [Thursday 01 April 2010] [05:48:35] <mikko> should have something working by the end of the day
| [Thursday 01 April 2010] [05:48:46] <sustrik>   mikko: nice
| [Thursday 01 April 2010] [05:49:05] <sustrik>   btw, there were several people messing with php
| [Thursday 01 April 2010] [05:49:22] <sustrik>   so you may ask about it on the mailing list
| [Thursday 01 April 2010] [05:49:57] <sustrik>   the main problem afaiu is to have a persistent connection from php
| [Thursday 01 April 2010] [05:50:14] <sustrik>   rather than establishing and tearing the connection all the time
| [Thursday 01 April 2010] [05:51:42] <mikko> sustrik: that should not really be hard
| [Thursday 01 April 2010] [05:53:02] <mikko> sustrik: i'll take a peek at the mailing-lists
| [Thursday 01 April 2010] [06:02:52] <ud_>   hi
| [Thursday 01 April 2010] [06:03:04] <ud_>   Why PGM may loss messages ?
| [Thursday 01 April 2010] [06:10:09] <sjampoo>   ud, it might be that you are sending the messages from one context and that all your sends have finished but ZMQ is still pushing them to the network (because of the multicast rate). However, if you close the context before that is finished the rest of your message will never arrive. 
| [Thursday 01 April 2010] [06:24:45] <sustrik>   ud_: also there's a problem of the finite retransmit window
| [Thursday 01 April 2010] [06:25:05] <sustrik>   sender may store at most that much data
| [Thursday 01 April 2010] [06:25:46] <sustrik>   thus is receiver requests retransmission of data that were already dropped by the sender
| [Thursday 01 April 2010] [06:25:59] <sustrik>   sender has no way to retransmit
| [Thursday 01 April 2010] [06:36:50] <ud_>   Also, somtimes I handle this: Assertion failed: it != peers.end () (pgm_receiver.cpp:161)
| [Thursday 01 April 2010] [06:39:48] <sustrik>   ud_: let me see
| [Thursday 01 April 2010] [06:40:56] <sustrik>   ud_: there have been a bug in OpenPGM lately
| [Thursday 01 April 2010] [06:41:04] <sustrik>   this looks like it may be the consequence
| [Thursday 01 April 2010] [06:41:46] <sustrik>   however, if you don't overload your network, you shouldn't hit the problem
| [Thursday 01 April 2010] [06:42:12] <sustrik>   anyway, the original bug will be solved in next release (2.0.7)
| [Thursday 01 April 2010] [06:46:07] <ud_>   ok, when will the next release ? :)
| [Thursday 01 April 2010] [07:08:22] <sustrik>   ud_: couple of weeks from now
| [Thursday 01 April 2010] [07:09:19] <sjampoo>   ud, i got the same message when closing the context prematurely and then firing up a different context.
| [Thursday 01 April 2010] [07:12:57] <sustrik>   sjampoo: that's interesting
| [Thursday 01 April 2010] [07:13:11] <sustrik>   i can imagine a way how that could happen
| [Thursday 01 April 2010] [07:13:28] <sustrik>   can you fill a bug report, please?
| [Thursday 01 April 2010] [07:14:49] <sjampoo>   hmm, i did not expect it to be a bug really, just misunderstanding on my part
| [Thursday 01 April 2010] [07:16:45] <sustrik>   sjampoo: i think it is a bug
| [Thursday 01 April 2010] [07:16:55] <sjampoo>   ok, ill file a report
| [Thursday 01 April 2010] [07:17:15] <sustrik>   what's happening imo is that the two subsequent PGM session interact in a strange way
| [Thursday 01 April 2010] [07:17:18] <sustrik>   yes, please
| [Thursday 01 April 2010] [07:17:53] <sustrik>   it definitely shouldn't assert, in worse case it should return error
| [Thursday 01 April 2010] [07:18:10] <sjampoo>   I am running it from Python code, also when loading two context in a single process i get an assertion error as well
| [Thursday 01 April 2010] [07:18:18] <sjampoo>   (when i compiled zmq with pgm support)
| [Thursday 01 April 2010] [07:18:54] <sjampoo>   not sure if this is somewhat related
| [Thursday 01 April 2010] [07:34:24] <sustrik>   what's the assertion in that case?
| [Thursday 01 April 2010] [07:34:55] <sjampoo>   Assertion failed: !pgm_supported () (zmq.cpp:234)
| [Thursday 01 April 2010] [07:35:06] <sjampoo>   There is a comment about refcounting above it
| [Thursday 01 April 2010] [07:40:10] <sustrik>   that's 0MQ/2.0.6?
| [Thursday 01 April 2010] [07:40:18] <sjampoo>   yes
| [Thursday 01 April 2010] [07:41:22] <sustrik>   ok, i see; to solve the problem OpenPGM has to be patched
| [Thursday 01 April 2010] [07:43:55] <sjampoo>   Hmmm, was just able to succesfully reproduce the peer.end() problem with the performance tools local_thr, and remote_thr
| [Thursday 01 April 2010] [07:44:00] <sjampoo>   Where should i file the bug? 
| [Thursday 01 April 2010] [07:44:39] <sustrik>   go to github repo
| [Thursday 01 April 2010] [07:44:47] <sjampoo>   zeromq right? 
| [Thursday 01 April 2010] [07:44:50] <sustrik>   there's "issues" tab ther
| [Thursday 01 April 2010] [07:44:50] <sjampoo>   Nog OpenPGM? 
| [Thursday 01 April 2010] [07:44:56] <sjampoo>   not even
| [Thursday 01 April 2010] [07:45:13] <sustrik>   the peer.end() is 0mq problem
| [Thursday 01 April 2010] [07:45:18] <sjampoo>   ok.
| [Thursday 01 April 2010] [07:45:48] <sustrik>   if you want the pgm_supported problem solved you should ask on OpenPGM mailing list
| [Thursday 01 April 2010] [07:46:35] <sjampoo>   ok, thanks for the info
| [Thursday 01 April 2010] [07:47:57] <sustrik>   np
| [Thursday 01 April 2010] [07:53:24] <keenerd>   Dumb question; where did the C bindings go in 2.0.6?  The docs just loop back on themselves.
| [Thursday 01 April 2010] [07:59:10] <mikko> keenerd: you mean http://api.zeromq.org/zmq.html ?
| [Thursday 01 April 2010] [08:02:02] <keenerd>   Yeah.  Is there an undocumented configure flag?
| [Thursday 01 April 2010] [08:02:22] <mikko> sustrik: http://pastie.org/898701 am i waiting on a message?
| [Thursday 01 April 2010] [08:02:41] <sustrik>   mikko: looks like
| [Thursday 01 April 2010] [08:03:04] <sustrik>   keenerd, what configure flag>
| [Thursday 01 April 2010] [08:03:05] <sustrik>   ?
| [Thursday 01 April 2010] [08:03:11] <sustrik>   ./configure --help
| [Thursday 01 April 2010] [08:03:15] <mikko> hmm. the same thing works on a single process but as soon as i got multiple forks things go downhill
| [Thursday 01 April 2010] [08:03:20] <sustrik>   gives you list of all available flags
| [Thursday 01 April 2010] [08:03:21] <keenerd>   By loop back on themselves, I mean the homepage.  It presumes C bindings are just there, and does not give a source to make them.
| [Thursday 01 April 2010] [08:04:02] <sustrik>   0MQ native interface is C
| [Thursday 01 April 2010] [08:04:16] <sustrik>   so when you build it, you have it
| [Thursday 01 April 2010] [08:04:26] <sustrik>   no separate project is needed
| [Thursday 01 April 2010] [08:04:29] <keenerd>   No, nothing helpful in configure --help
| [Thursday 01 April 2010] [08:04:48] <keenerd>   sustrik: You sure?  It really looks like C++ is the naitive interface now.
| [Thursday 01 April 2010] [08:05:01] <sustrik>   no, C is native (zmq.h)
| [Thursday 01 April 2010] [08:05:10] <sustrik>   C++ is a thin wrapper over C (zmq.hpp)
| [Thursday 01 April 2010] [08:05:30] <sustrik>   the documentation is confusing though
| [Thursday 01 April 2010] [08:05:51] <sustrik>   when clicking on C in the left pane is should say that it's native interface etc.
| [Thursday 01 April 2010] [08:06:04] <keenerd>   Okay, I see it.  "make install" ignores it, though.
| [Thursday 01 April 2010] [08:06:38] <sustrik>   nope, it should copy it to use/local/include
| [Thursday 01 April 2010] [08:06:50] <keenerd>   Does not work for me.
| [Thursday 01 April 2010] [08:06:50] <sustrik>   it's possible that you dan't have that on your path
| [Thursday 01 April 2010] [08:07:26] <keenerd>   No, I'm packaging the library.  It does not get moved from the source directoey to the package directory.
| [Thursday 01 April 2010] [08:07:47] <sustrik>   by packaging you mean make dist?
| [Thursday 01 April 2010] [08:07:57] <keenerd>   No.
| [Thursday 01 April 2010] [08:08:06] <keenerd>   I maintain it for Arch.
| [Thursday 01 April 2010] [08:08:30] <sustrik>   ok, can you be more specific on what you are doing?
| [Thursday 01 April 2010] [08:08:34] <sustrik>   ./autogen.sh
| [Thursday 01 April 2010] [08:08:37] <sustrik>   ./configure
| [Thursday 01 April 2010] [08:08:39] <sustrik>   make
| [Thursday 01 April 2010] [08:08:42] <sustrik>   make install
| [Thursday 01 April 2010] [08:08:43] <sustrik>   ?
| [Thursday 01 April 2010] [08:09:16] <keenerd>   ./configure prefix=... 
| [Thursday 01 April 2010] [08:09:17] <keenerd>   make
| [Thursday 01 April 2010] [08:09:21] <keenerd>   make install
| [Thursday 01 April 2010] [08:09:25] <sustrik>   ok
| [Thursday 01 April 2010] [08:09:33] <sustrik>   what's missing afterwards?
| [Thursday 01 April 2010] [08:09:44] <keenerd>   zmq.h, at the very least :-)
| [Thursday 01 April 2010] [08:09:51] <sustrik>   ok, let me try...
| [Thursday 01 April 2010] [08:10:17] <sustrik>   sjampoo: thanks
| [Thursday 01 April 2010] [08:10:23] <keenerd>   Is autogen really needed now?  Trying that...
| [Thursday 01 April 2010] [08:10:39] <sustrik>   depends on whether you build from the tar.gz package
| [Thursday 01 April 2010] [08:10:45] <sustrik>   if so, you don't need it
| [Thursday 01 April 2010] [08:10:57] <sustrik>   if you are building directly from github repo, you need it
| [Thursday 01 April 2010] [08:11:39] <keenerd>   Ah, no.  Someone else maintains the git.
| [Thursday 01 April 2010] [08:12:17] <sustrik>   then just ommit the autogen step
| [Thursday 01 April 2010] [08:13:55] <keenerd>   Otherwise, building it is a lot simpler now.
| [Thursday 01 April 2010] [08:14:23] <keenerd>   The old --with would crash easily.
| [Thursday 01 April 2010] [08:14:30] <mikko> sustrik: the interesting thing is that it looks like im waiting for a message but i dont see the "request" in tcpdump
| [Thursday 01 April 2010] [08:14:40] <mikko> so nothing has been sent at that point
| [Thursday 01 April 2010] [08:15:28] <sustrik>   keenerd: yes, we've trew out all the stuf that wasn't absolutely needed
| [Thursday 01 April 2010] [08:16:46] <sustrik>   mikko: different things may got wrong, send your test prog to the mailing list and i'll have a look
| [Thursday 01 April 2010] [08:18:42] <mikko> sustrik: my test prog is the full php extension
| [Thursday 01 April 2010] [08:18:45] <mikko> it might be a bit heavy
| [Thursday 01 April 2010] [08:19:12] <sustrik>   then just describe what you are doing
| [Thursday 01 April 2010] [08:19:17] <mikko> i think it might have something to do with this http://pastie.org/898721
| [Thursday 01 April 2010] [08:19:50] <mikko> but not sure yet
| [Thursday 01 April 2010] [08:19:56] <sustrik>   grr, that's the bug i cannot get my hands on
| [Thursday 01 April 2010] [08:20:05] <sustrik>   i am not able to reproduce it here
| [Thursday 01 April 2010] [08:20:14] <sustrik>   would it be able to get access to your box?
| [Thursday 01 April 2010] [08:20:24] <mikko> Assertion failed: !incomplete_in (session.cpp:123)
| [Thursday 01 April 2010] [08:20:24] <mikko> Aborted
| [Thursday 01 April 2010] [08:20:29] <mikko> on the server side
| [Thursday 01 April 2010] [08:20:36] <mikko> sustrik: it's a virtual machine
| [Thursday 01 April 2010] [08:20:41] <mikko> i can zip it up and send it to you
| [Thursday 01 April 2010] [08:21:01] <mikko> i can try to make it available online first though (not sure about local firewall)
| [Thursday 01 April 2010] [08:21:19] <sustrik>   that would be great
| [Thursday 01 April 2010] [08:24:06] <sustrik>   mikko: you are using bleeding edge version, this is a problem with the code committed last week
| [Thursday 01 April 2010] [08:24:33] <sustrik>   you may want to use 2.0.6 instead
| [Thursday 01 April 2010] [08:25:40] <sustrik>   keenerd: i've tested the build:
| [Thursday 01 April 2010] [08:25:51] <sustrik>   ./configure --prefix=xyz
| [Thursday 01 April 2010] [08:25:52] <sustrik>   make
| [Thursday 01 April 2010] [08:25:56] <sustrik>   make install
| [Thursday 01 April 2010] [08:26:04] <sustrik>   ls xyz/include
| [Thursday 01 April 2010] [08:26:08] <sustrik>     zmq.h
| [Thursday 01 April 2010] [08:26:10] <sustrik>     zmq.hpp
| [Thursday 01 April 2010] [08:26:15] <keenerd>   Huh.
| [Thursday 01 April 2010] [08:27:51] <keenerd>   Very odd.
| [Thursday 01 April 2010] [08:28:18] <sustrik>   maybe a typo in the path?
| [Thursday 01 April 2010] [08:28:36] <keenerd>   Which path?  I see zmq.hpp.
| [Thursday 01 April 2010] [08:29:29] <sustrik>   --prefix=path
| [Thursday 01 April 2010] [08:29:33] <mikko> sustrik: can you give me your pubkey?
| [Thursday 01 April 2010] [08:29:54] <sustrik>   what's your email?
| [Thursday 01 April 2010] [08:30:15] <mikko> mkoppanen@php.net
| [Thursday 01 April 2010] [08:30:26] <sustrik>   wait a sec
| [Thursday 01 April 2010] [08:30:59] <sustrik>   mikko: ok, sent
| [Thursday 01 April 2010] [08:31:41] <keenerd>   sustrik: Okay, I reinstalled make and related packages.  Problem seems to be gone.  I blame cosmic rays, and will replace my aging drive soon.
| [Thursday 01 April 2010] [08:31:49] <keenerd>   Sorry for the hassle.
| [Thursday 01 April 2010] [08:31:53] <sustrik>   :)
| [Thursday 01 April 2010] [08:32:37] <keenerd>   Thanks.
| [Thursday 01 April 2010] [08:34:13] <sustrik>   np, autotools is a mysterious piece of software with it's own will
| [Thursday 01 April 2010] [11:20:29] <mikko> sustrik: still here?
| [Thursday 01 April 2010] [11:36:55] <mikko> anyone had this:
| [Thursday 01 April 2010] [11:36:57] <mikko> Assertion failed: !engine (session.cpp:263)
| [Thursday 01 April 2010] [12:20:08] <Skaag> ping?
| [Thursday 01 April 2010] [12:38:39] <mikko> pong
| [Thursday 01 April 2010] [13:28:33] <Skaag> an active person!
| [Thursday 01 April 2010] [13:36:32] <mikko> well, active and active
| [Thursday 01 April 2010] [13:36:35] <mikko> my first day here
| [Thursday 01 April 2010] [13:41:30] <mikko> Skaag: looks like you found my github repo
| [Thursday 01 April 2010] [13:41:59] <Skaag> lol
| [Thursday 01 April 2010] [13:42:09] <Skaag> yes :-)
| [Thursday 01 April 2010] [13:42:25] <Skaag> I wondered if you'd notice while here
| [Thursday 01 April 2010] [13:43:06] <Skaag> While it was a half joke, I will be happy to test it and add/edit documentation
| [Thursday 01 April 2010] [13:43:35] <Skaag> I think I may have made a mistake wt
| [Thursday 01 April 2010] [13:43:36] <mikko> sure, that would probably be useful
| [Thursday 01 April 2010] [13:43:41] <mikko> especially missing features
| [Thursday 01 April 2010] [13:43:44] <Skaag> with choosing rabbitmq prematurely
| [Thursday 01 April 2010] [13:43:47] <mikko> brb
| [Thursday 01 April 2010] [14:05:15] <sustrik>   mikko: Assertion failed: !engine (session.cpp:263) looks like a bug
| [Thursday 01 April 2010] [14:05:26] <sustrik>   any idea how to reproduct it?
| [Thursday 01 April 2010] [14:05:41] <mikko> sustrik: yes
| [Thursday 01 April 2010] [14:05:44] <sustrik>   reproduce*
| [Thursday 01 April 2010] [14:05:45] <mikko> i downgraded to 2.0.6
| [Thursday 01 April 2010] [14:05:49] <mikko> when i set IDENTITY
| [Thursday 01 April 2010] [14:05:53] <sustrik>   aha
| [Thursday 01 April 2010] [14:05:58] <mikko> it happens on second request
| [Thursday 01 April 2010] [14:06:06] <mikko> sustrik: btw i got the php bindings running
| [Thursday 01 April 2010] [14:06:14] <mikko> also persistent connections should be working
| [Thursday 01 April 2010] [14:06:16] <sustrik>   the IDENTITY is set on req or rep?
| [Thursday 01 April 2010] [14:06:21] <sustrik>   mikko: great
| [Thursday 01 April 2010] [14:06:25] <mikko> REQ
| [Thursday 01 April 2010] [14:06:42] <sustrik>   ok, i'll give it a try - although after easter holiday
| [Thursday 01 April 2010] [14:06:59] <sustrik>   as for the binding, would you like me to link to it from the website?
| [Thursday 01 April 2010] [14:07:21] <mikko> that's would nice, although it's not stable yet
| [Thursday 01 April 2010] [14:07:31] <mikko> i guess people understand as its on github
| [Thursday 01 April 2010] [14:07:33] <sustrik>   call it "alpha", no?
| [Thursday 01 April 2010] [14:07:37] <mikko> http://github.com/mkoppanen/php-zeromq
| [Thursday 01 April 2010] [14:07:44] <mikko> well, no tags / releases yet
| [Thursday 01 April 2010] [14:08:02] <mikko> let me add EXPERIMENTAL file
| [Thursday 01 April 2010] [14:08:08] <sustrik>   ok
| [Thursday 01 April 2010] [14:08:50] <mikko> sustrik: i think the earlier epoll issue is related to forks
| [Thursday 01 April 2010] [14:09:00] <mikko> context created in parent and accessed in forked child
| [Thursday 01 April 2010] [14:09:07] <mikko> i might be mistaken on that 
| [Thursday 01 April 2010] [14:09:43] <sustrik>   mikko: i am not sure whether that works
| [Thursday 01 April 2010] [14:09:49] <sustrik>   never tried it myself
| [Thursday 01 April 2010] [14:10:02] <mikko> i think that's what i ended up with php module running in apache
| [Thursday 01 April 2010] [14:10:15] <mikko> i moved the context creation 'per object' and all my problems went away
| [Thursday 01 April 2010] [14:10:35] <sustrik>   in any case it's more clean solution
| [Thursday 01 April 2010] [14:10:45] <mikko> btw, zmq_msg_t seems to be empty after it's been sent. is that due to possible async sending where everything is not sent on one go?
| [Thursday 01 April 2010] [14:10:47] <Skaag> very nice
| [Thursday 01 April 2010] [14:10:49] <sustrik>   context basically represents "library instance"
| [Thursday 01 April 2010] [14:11:38] <sustrik>   mikko: it's a performance issue
| [Thursday 01 April 2010] [14:11:49] <sustrik>   if the message was retained
| [Thursday 01 April 2010] [14:12:01] <sustrik>   there would have to be a reference count attached to it
| [Thursday 01 April 2010] [14:12:17] <sustrik>   (one reference from sending I/O thread, other from client's thread)
| [Thursday 01 April 2010] [14:12:32] <sustrik>   the refcount would have to be manipulated using atomic operations
| [Thursday 01 April 2010] [14:12:39] <sustrik>   those are pretty expensive
| [Thursday 01 April 2010] [14:12:50] <mikko> ok, now i get it
| [Thursday 01 April 2010] [14:12:56] <sustrik>   however, if you need to retain the message, there's zmq_msg_copy
| [Thursday 01 April 2010] [14:13:04] <sustrik>   just copy it before sending
| [Thursday 01 April 2010] [14:14:03] <mikko> i would think copy is as expensive as initing a new one?
| [Thursday 01 April 2010] [14:14:35] <mikko> ah
| [Thursday 01 April 2010] [14:14:40] <mikko> reading man pages 
| [Thursday 01 April 2010] [14:14:47] <sustrik>   no, there's ref count turned on in such case
| [Thursday 01 April 2010] [14:14:53] <sustrik>   so it doens't really copy the data
| [Thursday 01 April 2010] [14:15:52] <mikko> one thing i noticed here: http://api.zeromq.org/zmq_setsockopt.html
| [Thursday 01 April 2010] [14:15:52] <sustrik>   mikko: ok, go here:
| [Thursday 01 April 2010] [14:15:53] <sustrik>   http://www.zeromq.org/bindings:php
| [Thursday 01 April 2010] [14:15:58] <mikko> Setting I/O thread affinity
| [Thursday 01 April 2010] [14:16:05] <sustrik>   i've copied the text from python binding
| [Thursday 01 April 2010] [14:16:11] <mikko> it passes 2 as the parameter
| [Thursday 01 April 2010] [14:16:25] <sustrik>   create an account on the website and you may modify it as you see fit
| [Thursday 01 April 2010] [14:16:25] <mikko> which causes zmq to crash 
| [Thursday 01 April 2010] [14:16:33] <mikko> thanks!
| [Thursday 01 April 2010] [14:16:36] <sustrik>   np
| [Thursday 01 April 2010] [14:16:54] <sustrik>   let me know your login so I can grant you write access btq
| [Thursday 01 April 2010] [14:16:57] <sustrik>   btw
| [Thursday 01 April 2010] [14:17:41] <sustrik>   as for the crash, does it crash in zmq_setsockopt itself?
| [Thursday 01 April 2010] [14:17:46] <mikko> yep
| [Thursday 01 April 2010] [14:17:51] <sustrik>   segfault?
| [Thursday 01 April 2010] [14:18:04] <mikko> invalid read size of 8 (on my arch)
| [Thursday 01 April 2010] [14:18:11] <mikko> probably due to it expecting a pointer
| [Thursday 01 April 2010] [14:18:20] <sustrik>   yes, it expects a pointer
| [Thursday 01 April 2010] [14:18:38] <sustrik>   it similar to standard POSIX setsockopt
| [Thursday 01 April 2010] [14:18:58] <mikko> the example passes: rc = zmq_setsockopt (socket, ZMQ_AFFINITY, 2, sizeof (int64_t));
| [Thursday 01 April 2010] [14:19:15] <sustrik>   coincidence
| [Thursday 01 April 2010] [14:19:22] <sustrik>   it should look like this:
| [Thursday 01 April 2010] [14:19:30] <sustrik>   int64_t affinity =2;
| [Thursday 01 April 2010] [14:19:51] <sustrik>   zmq_setsockopt (s, ZMQ_AFFINITY, &affinity, sizeof (affinity));
| [Thursday 01 April 2010] [14:20:00] <mikko> yep
| [Thursday 01 April 2010] [14:20:14] <mikko> seems like all other examples are correct (camera, chat etc)
| [Thursday 01 April 2010] [14:20:42] <mikko> i seem to have a wikidot account already
| [Thursday 01 April 2010] [14:20:44] <mikko> 'mkoppanen'
| [Thursday 01 April 2010] [14:20:49] <sustrik>   wait a sec
| [Thursday 01 April 2010] [14:20:56] <mikko> it must be because liblqr was hosted on wikidot
| [Thursday 01 April 2010] [14:21:00] <mikko> the website
| [Thursday 01 April 2010] [14:21:20] <Skaag> I never had one, made it now
| [Thursday 01 April 2010] [14:21:55] <sustrik>   Skaag: you want access too?
| [Thursday 01 April 2010] [14:22:00] <Skaag> sure
| [Thursday 01 April 2010] [14:22:05] <sustrik>   mikko: you are invited
| [Thursday 01 April 2010] [14:22:14] <sustrik>   jst accept and you can alter the page
| [Thursday 01 April 2010] [14:22:21] <Skaag> I'll probably mostly fix typos if I find them, or rephrase sentences to clarify
| [Thursday 01 April 2010] [14:22:41] <Skaag> and maybe contribute some code samples, if applicable
| [Thursday 01 April 2010] [14:22:55] <Skaag> I'm 'skaag' on wikidot
| [Thursday 01 April 2010] [14:23:00] <sustrik>   Skaag: you are working on PHP as well?
| [Thursday 01 April 2010] [14:23:12] <Skaag> PHP, C++ and Java
| [Thursday 01 April 2010] [14:23:41] <sustrik>   ok, feel free to change the page of the binding you are working on
| [Thursday 01 April 2010] [14:23:47] <Skaag> thanks
| [Thursday 01 April 2010] [14:23:53] <sustrik>   however, when changing generic content first discuss it on thr mailing listy
| [Thursday 01 April 2010] [14:24:31] <sustrik>   Skaag: you are invited
| [Thursday 01 April 2010] [14:25:41] <Skaag> awesome
| [Thursday 01 April 2010] [14:25:53] <Skaag> I assume you copied the python page content to the php binding page for convenience?
| [Thursday 01 April 2010] [14:28:06] <sustrik>   Skaag: yes, to give you a template
| [Thursday 01 April 2010] [14:28:14] <Skaag> awesome. it's helpful.
| [Thursday 01 April 2010] [14:28:15] <sustrik>   however, feel free to modify it in any way
| [Thursday 01 April 2010] [14:28:41] <sustrik>   once you have something ready ping me and I'll link your page from the main page
| [Thursday 01 April 2010] [14:29:29] <mikko> will do
| [Thursday 01 April 2010] [14:29:31] <mikko> thanks a lot
| [Thursday 01 April 2010] [16:35:06] <sustrik>   mikko: still there?
| [Thursday 01 April 2010] [16:41:19] <mikko> sustrik: yes
| [Thursday 01 April 2010] [18:15:00] <mikko> initial round on docs http://www.zeromq.org/bindings:php
| [Thursday 01 April 2010] [18:15:20] <mikko> at least doesnt say py0MQ anymore :)
| [Thursday 01 April 2010] [18:15:50] <Skaag> awesome work
| [Thursday 01 April 2010] [18:15:55] <Skaag> I will test and give feedback
| [Thursday 01 April 2010] [20:24:39] <mikko> Skaag: http://wiki.github.com/mkoppanen/php-zeromq/api-documentation
| [Thursday 01 April 2010] [20:24:42] <mikko> initial api docs
| [Thursday 01 April 2010] [20:24:46] <mikko> getting a bit late
| [Thursday 01 April 2010] [21:03:55] <dermoth>   mikko, I am myself working on a php binding, but i'm focusing on the procedural interface with access to persistent sockets and thread safety... I wasn't planning an OO interface.
| [Thursday 01 April 2010] [21:05:08] <dermoth>   mikko, persistence is very important for what I want as I will send data in short-lived request and expect best-effort delivery while the SAPI is running...
| [Thursday 01 April 2010] [21:07:13] <dermoth>   mikko, I haven't written much code yet but I've already read nearly half a book on php extentions and was planning to start real coding very soon... i'm wondering if you'd like any help from me...
| [Thursday 01 April 2010] [21:11:49] <dermoth>   hummm I see you have persistence too. I was thinking of doing it explicitly though, with an optional key to allow re-using unique contexts, sockets, etc.
| [Thursday 01 April 2010] [21:17:30] <mikko> dermoth: in my case context is always tied to ZeroMQSocket object
| [Thursday 01 April 2010] [21:17:50] <mikko> and the ZeroMQSocket is stored with persistent_id
| [Thursday 01 April 2010] [21:18:13] <mikko> i didn't see much point for multiple threads as there is no userland threading in php
| [Thursday 01 April 2010] [21:19:48] <mikko> dermoth: hmmm.. what was the idea behind using contexts explicitly?
| [Thursday 01 April 2010] [21:20:05] <mikko> allow setting thread counts and choose different context for a socket?
| [Thursday 01 April 2010] [21:20:09] <dermoth>   mikko, this would be my first module, but I was trying to do everything the right way... do you think it would be worth completing it then we can take the best of both? I've also been told OO interface are often built on top or procedural extentions...
| [Thursday 01 April 2010] [21:20:27] <dermoth>   mikko, at first I just wanted proper thread separation
| [Thursday 01 April 2010] [21:20:46] <dermoth>   i.e. each thread acting as a standalone process
| [Thursday 01 April 2010] [21:21:20] <dermoth>   ZMQ sockets cannot be shared anyway, even with locking (according to the api dioc) so only the xcontext could be shared, it there's any advantage with that.
| [Thursday 01 April 2010] [21:21:22] <mikko> which threads?
| [Thursday 01 April 2010] [21:21:44] <dermoth>   mpm_worker for example...
| [Thursday 01 April 2010] [21:22:15] <mikko> i'm not that fuzzed about php + threading as large amounts of libraries php interacts with are not thread-safe
| [Thursday 01 April 2010] [21:22:22] <dermoth>   and before you ask the fact that many modules still crash in mpm_worker doesn't mean a new module don't need to be thread-safe ;)
| [Thursday 01 April 2010] [21:22:34] <mikko> and with large amounts of globals state the threaded version of php is often slower than single proces
| [Thursday 01 April 2010] [21:22:35] <dermoth>   awww you asked! :)
| [Thursday 01 April 2010] [21:22:45] <mikko> globals=global
| [Thursday 01 April 2010] [21:22:51] <dermoth>   yeah I know
| [Thursday 01 April 2010] [21:23:09] <dermoth>   but i beliebe it's still the best wai under IIS  though
| [Thursday 01 April 2010] [21:23:31] <dermoth>   I believe it's still the best way...
| [Thursday 01 April 2010] [21:23:32] <mikko> i think microsoft is now recommending fcgi since IIS7
| [Thursday 01 April 2010] [21:23:39] <dermoth>   really?
| [Thursday 01 April 2010] [21:23:43] <mikko> yep
| [Thursday 01 April 2010] [21:23:53] <dermoth>   I though fcgi was nearly dead...
| [Thursday 01 April 2010] [21:23:56] <mikko> most of their php related development efforts seem to go to fcgi
| [Thursday 01 April 2010] [21:24:44] <dermoth>   any chances they fear php competing their .NET market?
| [Thursday 01 April 2010] [21:24:48] <dermoth>   lol
| [Thursday 01 April 2010] [21:24:50] <mikko> ISAPI is faster but less stable
| [Thursday 01 April 2010] [21:25:05] <dermoth>   yes, but that's only because of php
| [Thursday 01 April 2010] [21:25:24] <dermoth>   fix php and isapi will be much better, imho
| [Thursday 01 April 2010] [21:25:26] <mikko> well, by definition native SAPI is always going to be faster
| [Thursday 01 April 2010] [21:25:46] <mikko> fix php and libraries that it uses
| [Thursday 01 April 2010] [21:26:00] <dermoth>   yes...
| [Thursday 01 April 2010] [21:27:21] <dermoth>   back to php-zeromq, itn't it would be wasteful of resources to have one context per socket, when an application use many sockets?
| [Thursday 01 April 2010] [21:29:00] <mikko> but the sockets are persisted so the context is created only once
| [Thursday 01 April 2010] [21:29:20] <mikko> i had problems allocating the context globally
| [Thursday 01 April 2010] [21:29:48] <mikko> i think the persistence should use EG(persistent_list) instead of random hashtable though
| [Thursday 01 April 2010] [21:30:15] <dermoth>   I was wondering, in a threaded environment, if there would be any advantage to have a single context shared amongst threads. but anyway my plan was to have contexts handled by the php code like in the c and python APIs that I use already.
| [Thursday 01 April 2010] [21:32:35] <dermoth>   and make persistence explicit trough separate function or optional arguments - persistent contexts/sockets would also have an associated key so that could could have separate persistent sockets going to the same endpoint - and same soe ctx.
| [Thursday 01 April 2010] [21:33:36] <dermoth>   I'm not sure how useful this is but I fear trouble when multiple application start doing advanced things using the same sockets...
| [Thursday 01 April 2010] [21:34:27] <dermoth>   ex what if cone app gets a rep intended for another...
| [Thursday 01 April 2010] [21:35:21] <mikko> but that's always going to be problematic if you run in a shared environment
| [Thursday 01 April 2010] [21:36:05] <dermoth>   yes, but at least I planned an api that allow explicit separation...
| [Thursday 01 April 2010] [21:36:30] <mikko> explicit separation of sockets?
| [Thursday 01 April 2010] [21:38:08] <dermoth>   ex: zmq_socket_p($context, $type [, $key]);
| [Thursday 01 April 2010] [21:38:52] <mikko> the only difference is that it allows setting context excplicitly
| [Thursday 01 April 2010] [21:38:59] <mikko> i guess that would make sense in some scenarios
| [Thursday 01 April 2010] [21:40:35] <dermoth>   I think we should mimic the zmq api as much as possible. There's a reason behind its design, alter all. copying it gives as much versatility to the language it's being bound to
| [Thursday 01 April 2010] [21:42:26] <dermoth>   and adding to it where it makes sense, like adding optional persistence to php to accommodate  get general workflow in web servers...
| [Thursday 01 April 2010] [21:44:40] <mikko> not sure how much the threading makes sense without userland threading
| [Thursday 01 April 2010] [21:44:44] <mikko> which C and python have
| [Thursday 01 April 2010] [21:49:12] <dermoth>   python threading isn't so much better... although at least it doesn't crash ;)
| [Thursday 01 April 2010] [21:50:52] <mikko> and there is a difference between userland threading and engine level threading
| [Thursday 01 April 2010] [21:51:08] <mikko> to the users point of view php is always 'single threaded'
| [Thursday 01 April 2010] [21:51:27] <dermoth>   yea...  by thread-safe I mean separating the threads so that they don't clobber each-other
| [Thursday 01 April 2010] [21:51:30] <dermoth>   yes
| [Thursday 01 April 2010] [21:52:32] <dermoth>   i.e. instead of declaring statics, you have to use macros so that the threaded-version will allocate per-thread structures in a hash.
| [Thursday 01 April 2010] [21:52:48] <dermoth>   without zts, though, the macros evaluate to a simple static
| [Thursday 01 April 2010] [21:54:59] <dermoth>   ok maybe I will get back to coding then, and than we can see what comes out. 
| [Thursday 01 April 2010] [21:55:43] <mikko> but still, i don't get what the point of having different contexts would be
| [Thursday 01 April 2010] [21:55:51] <mikko> as you would store those into resource lists
| [Thursday 01 April 2010] [21:55:56] <mikko> which would be shared between threads
| [Thursday 01 April 2010] [21:56:02] <mikko> and you end up into same problem
| [Thursday 01 April 2010] [21:56:03] <dermoth>   no
| [Thursday 01 April 2010] [21:56:11] <dermoth>   now shared between threads
| [Thursday 01 April 2010] [21:56:14] <dermoth>   not
| [Thursday 01 April 2010] [21:56:43] <dermoth>   each thread will have its own contextes...
| [Thursday 01 April 2010] [21:57:15] <mikko> yes, i tried allocating context in GINIT phase but it seemed to mess up everything
| [Thursday 01 April 2010] [21:57:50] <mikko> GINIT should be called per globals invocation, on single process when the process starts and with threading when a thread starts
| [Thursday 01 April 2010] [21:58:10] <dermoth>   contexts will be initialized on demand
| [Thursday 01 April 2010] [21:58:34] <dermoth>   i will expost zmw_init and zmq_init_p to userland...
| [Thursday 01 April 2010] [21:58:34] <mikko> where do you store them internally?
| [Thursday 01 April 2010] [21:59:11] <dermoth>   in EG(persistent_list)
| [Thursday 01 April 2010] [21:59:26] <mikko> i thought persistent_list is shared between threads
| [Thursday 01 April 2010] [21:59:46] <mikko> i might be wrong on that though
| [Thursday 01 April 2010] [21:59:50] <dermoth>   is it? you can add the thread_id in that case...
| [Thursday 01 April 2010] [22:00:12] <dermoth>   but i hope not as it would all lots of useless locking...
| [Thursday 01 April 2010] [22:00:17] <dermoth>   would add
| [Thursday 01 April 2010] [22:01:10] <dermoth>   and worst case i'm just enclose a die between #ifdef ZTS :p
| [Thursday 01 April 2010] [22:01:29] <mikko> no, it has to be thread-safe
| [Thursday 01 April 2010] [22:01:30] <dermoth>   problem solved...
| [Thursday 01 April 2010] [22:01:34] <dermoth>   lol
| [Thursday 01 April 2010] [22:01:41] <mikko> executor globals contains stuff like user erorr handlers
| [Thursday 01 April 2010] [22:01:43] <mikko> and so on
| [Thursday 01 April 2010] [22:01:48] <mikko> they couldn't be shared between threads
| [Thursday 01 April 2010] [22:02:11] <mikko> so effectively my implementation is fairly thread-safe then
| [Thursday 01 April 2010] [22:02:20] <mikko> you live you learn :)
| [Thursday 01 April 2010] [22:03:07] <dermoth>   my primary goal is learning anyway... if it might be useful it's a plug :)
| [Thursday 01 April 2010] [22:03:09] <dermoth>   plus
| [Thursday 01 April 2010] [22:03:28] <mikko> yes, i think combined procedural + oo is very good for learning
| [Thursday 01 April 2010] [22:03:38] <mikko> you can probably learn alot from pecl/memcache
| [Thursday 01 April 2010] [22:03:47] <mikko> or ext/mysqli
| [Thursday 01 April 2010] [22:04:04] <dermoth>   awwww I prefer not to think about oo just yet...
| [Thursday 01 April 2010] [22:04:32] <dermoth>   i don't even code PHP! Actually I manage to write simple scripts but that'S all...
| [Thursday 01 April 2010] [22:05:13] <mikko> if the context is in a single thread does it make sense to allocate more than 1 app thread and 1 io thread?
| [Thursday 01 April 2010] [22:05:22] <dermoth>   i'm not the one that the use it... I'm the sysadmin
| [Thursday 01 April 2010] [22:05:50] <dermoth>   the contex threads are on the library side
| [Thursday 01 April 2010] [22:06:00] <dermoth>   the library use threading internally
| [Thursday 01 April 2010] [22:07:18] <dermoth>   so yes, someone might want to set more threads if that's the only way to squeeze the last bits of performance out of his cpu cores...
| [Thursday 01 April 2010] [22:07:43] <dermoth>   but I have doubts this would apply to php...
| [Thursday 01 April 2010] [22:09:32] <dermoth>   it's like putting a huge truck engine on a f1... the vehicle it fast but the engine won't allow it!
| [Thursday 01 April 2010] [22:11:42] <dermoth>   i might rip your header... is that the "standard" php extention header?
| [Thursday 01 April 2010] [22:12:08] <dermoth>   i mean the copyright block...
| [Thursday 01 April 2010] [22:16:37] <mikko> nope
| [Thursday 01 April 2010] [22:16:40] <mikko> thats the BSD license
| [Thursday 01 April 2010] [22:17:21] <mikko> normally the PHP stuff is under PHP license
| [Thursday 01 April 2010] [22:17:44] <mikko> the stuff in php.net at least
| [Thursday 01 April 2010] [22:18:23] <dermoth>   and it  that more like LGPL?
| [Thursday 01 April 2010] [22:19:16] <mikko> http://en.wikipedia.org/wiki/BSD_licenses#3-clause_license_.28.22New_BSD_License.22.29
| [Thursday 01 April 2010] [22:19:29] <dermoth>   no, the php license
| [Thursday 01 April 2010] [22:19:51] <mikko> the only difference between PHP license and BSD license is that PHP license has a naming clause
| [Thursday 01 April 2010] [22:20:07] <mikko> http://www.php.net/license/3_01.txt
| [Thursday 01 April 2010] [22:20:10] <mikko> see 4th clause
| [Thursday 01 April 2010] [22:20:26] <dermoth>   ok, like the 3-clause BSD
| [Thursday 01 April 2010] [22:22:09] <mikko> added an ini-setting for setting thread counts
| [Thursday 01 April 2010] [22:23:13] <dermoth>   so technically php-zeromq wouldn't even be allowed without permission!
| [Thursday 01 April 2010] [22:24:19] <mikko> that's just the name of the repository
| [Thursday 01 April 2010] [22:24:26] <mikko> the product is not called 'php-zeromq'
| [Thursday 01 April 2010] [22:26:35] <mikko> committed a fix to the header to indicate it more clearly :)
| [Thursday 01 April 2010] [22:27:14] <dermoth>   i see... i'm not saying that they would though, but packaging it in something like php-zeromq-x.xx.tar.gz would be very borderline...
| [Thursday 01 April 2010] [22:28:39] <mikko> it's just to clarify on github as there is "zeromq2" project already and the language isn't really clear from the context
| [Thursday 01 April 2010] [22:29:56] <mikko> i'm done, 18 hours straight coding is enough for a day
| [Thursday 01 April 2010] [22:30:13] <mikko> good night and good luck with your php expedition
| [Friday 02 April 2010] [02:21:08] <desrt>   hello.
| [Friday 02 April 2010] [02:22:26] <desrt>   what's the amqp story?
| [Friday 02 April 2010] [02:25:05] <desrt>   hm.  i'll be back tomorrow. :)
| [Friday 02 April 2010] [02:31:04] <sustrik> desrt: no big deal, imatix has no stakes in amqp anymore so it's leaving the amqp working group
| [Friday 02 April 2010] [02:52:02] <sustrik> dermoth, mikko: what about bringing the issue of explicit/implicit context in PHP on the mailing list?
| [Friday 02 April 2010] [02:52:37] <sustrik> i belive other languages with limited thread support (python? ruby?) are facing the same dilemma
| [Friday 02 April 2010] [02:53:48] <dermoth> sustrik, sure... I'd like to have something at least partially working first though :)
| [Friday 02 April 2010] [02:54:17] <dermoth> talking about amqp, why was support for it dropped, I though that was a really nice feature
| [Friday 02 April 2010] [02:54:35] <dermoth> no patent should cover the basic functionality anyway...
| [Friday 02 April 2010] [02:57:21] <sustrik> hm, it's a long story...
| [Friday 02 April 2010] [02:57:53] <sustrik> basically the participation in WG was pain
| [Friday 02 April 2010] [02:58:14] <sustrik> it's a design-by-committee thing so it's political rather than technical
| [Friday 02 April 2010] [02:58:38] <sustrik> furthermore, the resulting design is extremely complex
| [Friday 02 April 2010] [02:58:42] <dermoth> I couldn't find much about it exceps some obscure "patent" issue, but I really liked the feature for one thing I had in mind...
| [Friday 02 April 2010] [02:58:53] <sustrik> so making it work is really costly
| [Friday 02 April 2010] [02:59:33] <sustrik> so you have to invest in political fight in the working group as well as in implementation
| [Friday 02 April 2010] [02:59:34] <dermoth> there is no standard yet?
| [Friday 02 April 2010] [02:59:41] <sustrik> several versions
| [Friday 02 April 2010] [02:59:48] <sustrik> mutually incompatible :)
| [Friday 02 April 2010] [02:59:52] <dermoth> backward-compatible?
| [Friday 02 April 2010] [02:59:56] <sustrik> nope
| [Friday 02 April 2010] [02:59:56] <dermoth> ouch
| [Friday 02 April 2010] [03:00:06] <sustrik> design-be-committee
| [Friday 02 April 2010] [03:00:16] <sustrik> anyway, so you are investing a lot in the thing
| [Friday 02 April 2010] [03:00:37] <sustrik> and then you find out the partners are patenting around of the standard
| [Friday 02 April 2010] [03:00:45] <sustrik> so you get mad and quit
| [Friday 02 April 2010] [03:00:55] <sustrik> that's basically it
| [Friday 02 April 2010] [03:01:03] <dermoth> so could it possibly be re-implemented if the WG settles on a final protocol?
| [Friday 02 April 2010] [03:01:16] <sustrik> you've seen the specification?
| [Friday 02 April 2010] [03:01:19] <dermoth> no
| [Friday 02 April 2010] [03:01:21] <dermoth> lol
| [Friday 02 April 2010] [03:01:23] <sustrik> latest version is 270 pages long
| [Friday 02 April 2010] [03:01:32] <sustrik> who's going to pay for that?
| [Friday 02 April 2010] [03:01:38] <dermoth> yes but I guess you don't need all of it...
| [Friday 02 April 2010] [03:02:03] <sustrik> hm, i think that's the basic spec, let me check...
| [Friday 02 April 2010] [03:02:12] <dermoth> nm
| [Friday 02 April 2010] [03:03:32] <dermoth> well anyway it wouldn't be hard to add a glue to it... write a piece of code that use both APIs.
| [Friday 02 April 2010] [03:04:36] <dermoth> like the zmq devices...
| [Friday 02 April 2010] [03:04:36] <sustrik> they've got it down to 106 pages, but it's core spec, you have to implement it all
| [Friday 02 April 2010] [03:04:50] <sustrik> well, you can try
| [Friday 02 April 2010] [03:05:01] <sustrik> but it's not as easy as it seems
| [Friday 02 April 2010] [03:05:11] <sustrik> let me explain
| [Friday 02 April 2010] [03:05:13] <dermoth> i'l talking of using an existing library...
| [Friday 02 April 2010] [03:05:36] <sustrik> something like a bridge?
| [Friday 02 April 2010] [03:05:39] <dermoth> yes
| [Friday 02 April 2010] [03:05:45] <sustrik> yes, that's doable
| [Friday 02 April 2010] [03:06:02] <dermoth> like a forwarded that use both zmq and an AMQP lib, like RabbitMQ
| [Friday 02 April 2010] [03:06:20] <sustrik> yes that makes sense
| [Friday 02 April 2010] [03:06:21] <dermoth> a forwarder
| [Friday 02 April 2010] [03:06:39] <sustrik> combine rabbitma C client with 0MQ devices
| [Friday 02 April 2010] [03:06:45] <sustrik> rabbitmq*
| [Friday 02 April 2010] [03:07:15] <sustrik> if there's an Erlang binding to 0MQ
| [Friday 02 April 2010] [03:07:33] <sustrik> you would be even able to create a "custome exchange" in rabbitmq server
| [Friday 02 April 2010] [03:07:41] <sustrik> that would publish messages in 0MQ format
| [Friday 02 April 2010] [03:07:47] <dermoth> I think rabbitmq had sifferent binding, including python
| [Friday 02 April 2010] [03:08:05] <sustrik> yes, it does
| [Friday 02 April 2010] [03:08:19] <dermoth> or could be another broker, but I remember I tested some stuff with python
| [Friday 02 April 2010] [03:08:51] <sustrik> i think it's real python AMQP client
| [Friday 02 April 2010] [03:10:48] <dermoth> But in about the same time I found an usable AMQP API I already has finished a working client/server test with ZeroMQ... that's what I like about it :)
| [Friday 02 April 2010] [03:11:06] <dermoth> had
| [Friday 02 April 2010] [03:11:06] <sustrik> yup, it's simpler
| [Friday 02 April 2010] [03:12:29] <sustrik> the basic difference is that AMQP was developed by adding features
| [Friday 02 April 2010] [03:12:43] <sustrik> while 0MQ was developed by ditching features
| [Friday 02 April 2010] [03:12:45] <sustrik> :)
| [Friday 02 April 2010] [03:12:55] <dermoth> btw I was thinking this could be a nice fit for adding authentication/encryption to zeromq: http://nacl.cace-project.eu/
| [Friday 02 April 2010] [03:13:26] <sustrik> definitely
| [Friday 02 April 2010] [03:13:39] <dermoth> another project built on simplicity and speed... unfortunately it doesn't seem very active lately.
| [Friday 02 April 2010] [03:14:04] <sustrik> i am not very familiar with security
| [Friday 02 April 2010] [03:14:21] <sustrik> but you may speak to Martin Lucina, he's looking at security aspects of 0mq
| [Friday 02 April 2010] [03:14:49] <sustrik> As for me, I was thinking of it in terms of messaging on Internet
| [Friday 02 April 2010] [03:14:58] <sustrik> imagine a network of devices
| [Friday 02 April 2010] [03:15:15] <sustrik> two terminal application points trust each other
| [Friday 02 April 2010] [03:15:25] <sustrik> but they don't trust the devices in the middle
| [Friday 02 April 2010] [03:15:31] <sustrik> what should they do?
| [Friday 02 April 2010] [03:15:37] <sustrik> it's an interesting area
| [Friday 02 April 2010] [03:15:51] <dermoth> well I don't think a single open-source crypto package out there takes security as seriously and professionally as this project, which is based on work and participation by D. J. Bernstein
| [Friday 02 April 2010] [03:16:16] <dermoth> pki is likely what you want...
| [Friday 02 April 2010] [03:16:35] <sustrik> quite possible, i am not an expert though, feel free to discuss it on the mailing list
| [Friday 02 April 2010] [03:16:47] <dermoth> share secret keys securely the first time, then tou can trust each other<
| [Friday 02 April 2010] [03:17:11] <dermoth> err
| [Friday 02 April 2010] [03:17:13] <sustrik> yes, that's the basic idea
| [Friday 02 April 2010] [03:17:14] <dermoth> share public keys
| [Friday 02 April 2010] [03:17:31] <sustrik> not think of 1 to many data distribution
| [Friday 02 April 2010] [03:17:43] <sustrik> each subscriber had paid for the content
| [Friday 02 April 2010] [03:17:47] <sustrik> got the key
| [Friday 02 April 2010] [03:17:57] <sustrik> now, couple of months later
| [Friday 02 April 2010] [03:18:05] <sustrik> one of the subscribers haven't paid
| [Friday 02 April 2010] [03:18:13] <sustrik> what now?
| [Friday 02 April 2010] [03:18:30] <sustrik> change the keys each month?
| [Friday 02 April 2010] [03:18:53] <dermoth> if you don'T multicast you can use each subscriber public key to encrypt their feed
| [Friday 02 April 2010] [03:19:20] <sustrik> you can't because you don't trust devices in the middle
| [Friday 02 April 2010] [03:19:28] <dermoth> that won't wotk with a PUB socket unless you tie in in tight with NaCL though
| [Friday 02 April 2010] [03:19:32] <sustrik> they cannot do the encryption
| [Friday 02 April 2010] [03:19:50] <desrt>   sustrik: ya... but you almost get the impression that [something] happened
| [Friday 02 April 2010] [03:19:53] <dermoth> you just have to trust the public key
| [Friday 02 April 2010] [03:19:57] <desrt>   sustrik: just wondering what the something is :)
| [Friday 02 April 2010] [03:20:18] <dermoth> then ouy know the private key associated with it is the only one that can ecrypt it
| [Friday 02 April 2010] [03:20:44] <sustrik> desrt: have a look above, we've just discussed it with dermoth
| [Friday 02 April 2010] [03:20:52] <desrt>   oh.  ok.  i'll read :)
| [Friday 02 April 2010] [03:22:09] <sustrik> dermoth: i mean, if the middle node has to encrypt messages, original provider has to deliver unecrypted content to the middle node - now recall we don't trust the middle node
| [Friday 02 April 2010] [03:22:43] <desrt>   sustrik: hmm.  that seems pretty much like how i imagined
| [Friday 02 April 2010] [03:23:00] <dermoth> the original provider has to encrypt, or it won't work... or you can di a trust chain between each forwarder
| [Friday 02 April 2010] [03:23:07] <sustrik> desrt: shrug
| [Friday 02 April 2010] [03:23:30] <desrt>   sustrik: it's not so hard to believe large standards descending into design-by-comittee patent messes
| [Friday 02 April 2010] [03:24:10] <sustrik> dermoth: if you are interested in the area, take it to the mailing list; you'll get much more educated audience there
| [Friday 02 April 2010] [03:24:20]    * sustrik is security idiot
| [Friday 02 April 2010] [03:24:41] <sustrik> desrt: it happens all the time
| [Friday 02 April 2010] [03:24:50] <sustrik> think of telco standards
| [Friday 02 April 2010] [03:24:50] <dermoth> ok, but it's not on my roadmap just yet
| [Friday 02 April 2010] [03:24:55] <sustrik> sure
| [Friday 02 April 2010] [03:26:11] <desrt>   my only concern is taht amqp will become a widely-deployed standard nonetheless
| [Friday 02 April 2010] [03:26:20] <desrt>   and 0mq will be this thing that nobody uses
| [Friday 02 April 2010] [03:26:51] <desrt>   although the community around 0mq looks pretty active at the moment, which is nice
| [Friday 02 April 2010] [03:27:01] <sustrik> desrt: think of it this way:
| [Friday 02 April 2010] [03:27:21] <sustrik> "standard" means formalisation of best practices in the area
| [Friday 02 April 2010] [03:27:32] <sustrik> it's strictly non-experimental
| [Friday 02 April 2010] [03:27:58] <sustrik> so what AMQP does is to formalise best practices for messaging in corporate environment
| [Friday 02 April 2010] [03:28:06] <dermoth> well i'm out, it's pretty late here. see you...
| [Friday 02 April 2010] [03:28:12] <sustrik> cyl
| [Friday 02 April 2010] [03:28:16] <desrt>   ta
| [Friday 02 April 2010] [03:28:24] <sustrik> which are kind of broken anyway
| [Friday 02 April 2010] [03:28:28] <sustrik> or maybe not broken
| [Friday 02 April 2010] [03:28:39] <sustrik> but require large IT depts
| [Friday 02 April 2010] [03:28:52] <desrt>   the other thing is that 0mq seems not to support as rich of a routing model...
| [Friday 02 April 2010] [03:29:26] <sustrik> you mean complex routing criteria, say a SQL-like subscriptions
| [Friday 02 April 2010] [03:29:27] <sustrik> ?
| [Friday 02 April 2010] [03:29:42] <desrt>   no.  not criteria
| [Friday 02 April 2010] [03:29:57] <desrt>   but more like network traversal/propagation
| [Friday 02 April 2010] [03:30:18] <desrt>   the stuff that brokers did
| [Friday 02 April 2010] [03:30:35] <sustrik> there are devices that do the same thing
| [Friday 02 April 2010] [03:30:51] <sustrik> say zmq_forwarder is an app that acts a simple broker
| [Friday 02 April 2010] [03:31:09] <desrt>   so there is still support for asynchronous message queuing, etc
| [Friday 02 April 2010] [03:31:16] <sustrik> definitely
| [Friday 02 April 2010] [03:31:23] <desrt>   well
| [Friday 02 April 2010] [03:31:29] <desrt>   definitely seems like it's worth looking into for me
| [Friday 02 April 2010] [03:31:38] <sustrik> sure, have a look
| [Friday 02 April 2010] [03:31:44] <desrt>   you guys made reddit, btw
| [Friday 02 April 2010] [03:31:56] <sustrik> ah, let me see...
| [Friday 02 April 2010] [03:32:01] <desrt>   http://www.reddit.com/r/programming/comments/bl9rb/while_imatix_was_the_original_designer_of_amqp_we/
| [Friday 02 April 2010] [03:32:10] <desrt>   that's what brought me here
| [Friday 02 April 2010] [03:32:48] <desrt>   well, it made the frontpage of the programming reddit, anyway
| [Friday 02 April 2010] [03:34:02] <sustrik> 1000 hits on the website yesterday
| [Friday 02 April 2010] [03:34:17] <sustrik> not that bad for esoteric networking product
| [Friday 02 April 2010] [03:34:21] <sustrik> :)
| [Friday 02 April 2010] [03:41:52] <desrt>   you guys need to get ubuntu packages
| [Friday 02 April 2010] [03:47:32] <sustrik> desrt: there are debian packages atm
| [Friday 02 April 2010] [03:47:38] <sustrik> should work with ubuntu
| [Friday 02 April 2010] [03:47:50] <desrt>   hm  nice
| [Friday 02 April 2010] [03:50:22] <desrt>   i meant more like having stuff in the repository :)
| [Friday 02 April 2010] [03:51:28] <sustrik> you mean the package build sources?
| [Friday 02 April 2010] [03:51:38] <sustrik> it's in /debian subdirectory
| [Friday 02 April 2010] [03:51:42] <desrt>   no
| [Friday 02 April 2010] [03:51:51] <sustrik> a download?
| [Friday 02 April 2010] [03:51:53] <desrt>   i mean like, i should be able to type apt-get install zeromq
| [Friday 02 April 2010] [03:52:03] <sustrik> ah
| [Friday 02 April 2010] [03:52:09] <sustrik> it's moving upstream
| [Friday 02 April 2010] [03:52:17] <sustrik> it takes time till it gets there
| [Friday 02 April 2010] [03:52:31] <desrt>   probably too late for this cycle anyway
| [Friday 02 April 2010] [03:52:45]    * desrt has already been pushing his luck with freeze breaks
| [Friday 02 April 2010] [03:53:39] <sustrik> it's in "unstable" state
| [Friday 02 April 2010] [03:53:40] <sustrik> http://packages.debian.org/unstable/zeromq-bin
| [Friday 02 April 2010] [03:53:52] <desrt>   bin, eh?
| [Friday 02 April 2010] [03:53:56] <desrt>   what utils are those?
| [Friday 02 April 2010] [03:54:43] <sustrik> ah, those are just the devices
| [Friday 02 April 2010] [03:55:39] <sustrik> source package:
| [Friday 02 April 2010] [03:55:40] <sustrik> http://packages.debian.org/source/sid/zeromq
| [Friday 02 April 2010] [03:55:56] <sustrik> there are links to lib and dev packages there
| [Friday 02 April 2010] [03:56:05] <desrt>   thanks
| [Friday 02 April 2010] [04:05:41] <desrt>   sustrik: is this debian package up-to-date and in good standing?
| [Friday 02 April 2010] [04:07:00] <desrt>   (ie: no terrible bugs in it that have been fixed in master)
| [Friday 02 April 2010] [04:07:15] <sustrik> it's the last release (2.0.6)
| [Friday 02 April 2010] [04:07:32] <sustrik> the master is a bit ustable now
| [Friday 02 April 2010] [04:07:40] <sustrik> so rather use the last release
| [Friday 02 April 2010] [04:08:59] <desrt>   ok
| [Friday 02 April 2010] [04:15:58] <desrt>   ok.  i'm going to push my luck one more time :)
| [Friday 02 April 2010] [04:21:40] <desrt>   sustrik: it seems that the freeze exception is likely to be granted
| [Friday 02 April 2010] [04:27:04] <sustrik> desrt: i'm not familir with the process
| [Friday 02 April 2010] [04:27:09] <sustrik> what does that mean?
| [Friday 02 April 2010] [04:27:27] <desrt>   sustrik: normally ubuntu is frozen for new packages at this point (the release is coming out later this month)
| [Friday 02 April 2010] [04:27:35] <desrt>   but i've requested a freeze break
| [Friday 02 April 2010] [04:27:47] <sustrik> desrt: nice
| [Friday 02 April 2010] [04:27:48] <sustrik> thanks
| [Friday 02 April 2010] [04:28:09] <desrt>   i want to use this stuff and having packages in the OS obviously makes that a lot easier for me :)
| [Friday 02 April 2010] [04:28:55] <sustrik> helping with packaging is appreciated
| [Friday 02 April 2010] [04:29:22] <desrt>   heh.  i'm not helping.  just asking for favours. :)
| [Friday 02 April 2010] [04:29:37] <sustrik> i'm leaving now; see you all after the holiday
| [Friday 02 April 2010] [04:29:41] <sustrik> happy Easter!
| [Friday 02 April 2010] [04:29:45] <desrt>   have a good weekend
| [Friday 02 April 2010] [04:29:49] <desrt>   thanks for your help this evening
| [Friday 02 April 2010] [06:57:57] <mikko>   sustrik: good morning
| [Friday 02 April 2010] [07:59:08] <jldupont>    hi - where is the wire-format for 0mq?  I'd like to build an Erlang binding for it.
| [Friday 02 April 2010] [07:59:21] <jldupont>    been browsing the site like crazy!!!
| [Friday 02 April 2010] [08:01:32] <jldupont>    anybody??
| [Friday 02 April 2010] [08:04:40] <mikko>   jldupont: can erlang use C libraries?
| [Friday 02 April 2010] [08:07:41] <jldupont>    mikko: yes... but the comm between the C library and erlang will be through.... sockets!
| [Friday 02 April 2010] [08:08:17] <jldupont>    mikko: that's one way of doing it... there is a direct binding but the polling issue surfaces then....
| [Friday 02 April 2010] [08:08:27] <jldupont>    I'd rather bind directly over TCP/UDP
| [Friday 02 April 2010] [08:09:20] <mikko>   jldupont: ok, i think if you wait for a while you might get some help
| [Friday 02 April 2010] [08:09:28] <mikko>   it's good friday and people might be with their families
| [Friday 02 April 2010] [08:11:24] <jldupont>    mikko: understood... thanks!
| [Friday 02 April 2010] [08:15:29] <mikko>   jldupont: it might even be that you need to wait until holiday is over. although you can probably extract the wire protocol from the source
| [Friday 02 April 2010] [08:37:58] <FlaPer87>    hey guys, are there some guidlines to install 0mq on windows?
| [Friday 02 April 2010] [08:38:37] <FlaPer87>    I built it with visual studio but I can't find the zeromq_server command, how do I start the server?
| [Friday 02 April 2010] [09:37:47] <FlaPer87>    is there a sample configuration file somewhere?
| [Friday 02 April 2010] [17:51:30] <jomofo_> Any pointers for troubleshooting UnsatisfiedLinkError (no jzmq on java.library.path) on 64-bit Ubuntu 9.10 ?  I installed both libzmq and libjzmq to /usr/local/lib, ran ldconfig, set java.library.path and go, but no luck
| [Friday 02 April 2010] [23:01:34] <old_sound>   hi, I've just cloned the github repo, but I can't find instructions on how to build it, there's no INSTALL file as reported in the README
| [Friday 02 April 2010] [23:03:22] <old_sound>   OK, found it, had to run ./autogen.sh
| [Saturday 03 April 2010] [02:14:15] <dermoth>   old_sound, I've heard the master is a bit unstable, so unless you're doing development you should use the latest release instead
| [Saturday 03 April 2010] [02:14:30] <old_sound> ok
| [Saturday 03 April 2010] [12:47:44] <jomofo_>   Any pointers for troubleshooting UnsatisfiedLinkError (no jzmq on java.library.path) on 64-bit Ubuntu 9.10 ?  I installed both libzmq and libjzmq to /usr/local/lib, ran ldconfig, set java.library.path and go, but no luck
| [Saturday 03 April 2010] [13:17:45] <jomofo_>   I think I found my problem I was setting java.library.path correctly, but wasn't setting LD_LIBRARY_PATH.  I guess libjzmq wasn't able to load libzmq because of that.  Thanks for listening to me ramble
| [Saturday 03 April 2010] [13:42:11] <jomofo_>   Just out of curiosity, why is the Java namespace org.zmq instead of org.zeromq?  If I visit zmq.org I get a parking lot
| [Saturday 03 April 2010] [16:36:44] <mikko> good evening
| [Saturday 03 April 2010] [16:37:43] <mikko> jomofo_: do you have /usr/local/lib in ld.so.conf ?
| [Saturday 03 April 2010] [16:37:52] <mikko> jomofo_: does ldconfig --print | grep zmq show the library?
| [Saturday 03 April 2010] [16:45:34] <jomofo_>   mikki, yes, both libzmq and libjzmq are there
| [Saturday 03 April 2010] [16:46:33] <jomofo_>   mikko: oops, %s/mikki/mikko/
| [Saturday 03 April 2010] [16:55:57] <jomofo_>   mikko: and /usr/local/lib is in /etc/ld.so.conf.d/libc.conf which is included by /etc/ld.so.conf
| [Saturday 03 April 2010] [16:56:35] <jomofo_>   mikko: If I define $LD_LIBRARY_PATH as /usr/local/lib it works, but not without it
| [Saturday 03 April 2010] [17:52:43] <mikko> jomofo_: does the java program you start override LD_LIBRARY_PATH?
| [Saturday 03 April 2010] [18:02:43] <jomofo_>   mikko: I don't believe so.  It's just a simple unit test to see if I can use the jzmq bindings, but I am running it via Maven2
| [Saturday 03 April 2010] [18:07:24] <mikko> have you tried mvn -X ?
| [Saturday 03 April 2010] [18:07:31] <mikko> it might give more insight (or not)
| [Sunday 04 April 2010] [08:24:27] <mikko>   good morning
| [Sunday 04 April 2010] [08:34:37] <Skaag>   good morning mikko
| [Sunday 04 April 2010] [08:34:39] <Skaag>   :-)
| [Sunday 04 April 2010] [08:41:59] <mikko>   i added a couple of more doc pages 
| [Sunday 04 April 2010] [08:42:00] <mikko>   http://wiki.github.com/mkoppanen/php-zeromq/persistent-context-socket
| [Sunday 04 April 2010] [08:42:10] <mikko>   and updated this a bit http://wiki.github.com/mkoppanen/php-zeromq/api-documentation
| [Sunday 04 April 2010] [08:55:17] <Skaag>   awesome
| [Sunday 04 April 2010] [08:56:48] <mikko>   now, time to head out to see tiergarten and brandenburg tor
| [Sunday 04 April 2010] [08:56:50] <mikko>   laters
| [Sunday 04 April 2010] [09:45:47] <Skaag>   tiergarten or biergarten?! :-)
| [Sunday 04 April 2010] [12:31:31] <jomofo_> If I want to create a new language binding for 0MQ, should I use the LGPL? The language is friendlier toward the Eclipse license, but I think either would work.  
| [Sunday 04 April 2010] [14:10:40] <desrt>   sustrik: hey
| [Sunday 04 April 2010] [14:12:03] <sustrik> desrt: hi
| [Sunday 04 April 2010] [14:13:20] <desrt>   sustrik: are you a zmq developer?
| [Sunday 04 April 2010] [14:13:27] <desrt>   (just out of curiosity)
| [Sunday 04 April 2010] [14:13:45] <sustrik> you mean whether i wrote the 0mq code?
| [Sunday 04 April 2010] [14:13:51] <sustrik> yes, most of it
| [Sunday 04 April 2010] [14:13:56] <desrt>   cool
| [Sunday 04 April 2010] [14:14:12] <desrt>   a few questions
| [Sunday 04 April 2010] [14:14:28] <desrt>   1) is there any chance of some convenience additions/cleanups to some of the APIs?
| [Sunday 04 April 2010] [14:14:46] <sustrik> jomofo_: you can use any license that suits you
| [Sunday 04 April 2010] [14:15:02] <desrt>   like maybe using opaque structure types zmq_socket_t, zmq_context_t instead of void*
| [Sunday 04 April 2010] [14:15:16] <desrt>   and having all methods on sockets start like zmq_socket_ {send, recv, whatever}
| [Sunday 04 April 2010] [14:15:35] <desrt>   (note: zmq_msg follows this convention, but not socket and context)
| [Sunday 04 April 2010] [14:15:38] <sustrik> desrt: the method names are based on POSIX socket API
| [Sunday 04 April 2010] [14:15:51] <desrt>   ah.  interesting.
| [Sunday 04 April 2010] [14:15:58] <sustrik> usign zmq_type_function would break the 1:1 correspondence
| [Sunday 04 April 2010] [14:16:19] <desrt>   well.. the correspondence is already fairly loose...
| [Sunday 04 April 2010] [14:16:24] <desrt>   they take pointers intaed of fds
| [Sunday 04 April 2010] [14:16:35] <desrt>   and strings instead of struct sockaddr and size
| [Sunday 04 April 2010] [14:16:49] <sustrik> that's because POSIX doesn't allow for user-space implementation of fds
| [Sunday 04 April 2010] [14:17:23] <sustrik> if the codebase ever moves to kernel space the void* would of course be replaced by fd
| [Sunday 04 April 2010] [14:17:25] <desrt>   hm.
| [Sunday 04 April 2010] [14:17:32] <sustrik> context will drop out entirely
| [Sunday 04 April 2010] [14:17:34] <desrt>   interesting.
| [Sunday 04 April 2010] [14:18:15] <desrt>   ok.  higher level question:
| [Sunday 04 April 2010] [14:18:41] <desrt>   say i have a publisher of a stream of events and many subscribers to that stream
| [Sunday 04 April 2010] [14:18:57] <desrt>   and some devices in between storing the events
| [Sunday 04 April 2010] [14:19:11] <desrt>   how does a subscriber tell a device about which events it has already seen?
| [Sunday 04 April 2010] [14:20:04] <desrt>   is this part of the ZMQ_SUBSCRIBE sockopt?
| [Sunday 04 April 2010] [14:20:31] <sustrik> it's like a radio transmission, you start getting messages at the point when you create the connection
| [Sunday 04 April 2010] [14:20:39] <sustrik> you'll never get older messages
| [Sunday 04 April 2010] [14:20:49] <desrt>   oh.
| [Sunday 04 April 2010] [14:21:20] <desrt>   i was under the impressiont that devices could queue up events
| [Sunday 04 April 2010] [14:21:56] <desrt>   so that implies that it's quite possible to miss events in the case of shaky connectivity, then?
| [Sunday 04 April 2010] [14:21:56] <sustrik> they can, but in PUB/SUB messaging pattern it simply doesn't make sense
| [Sunday 04 April 2010] [14:22:07] <sustrik> how long would you cache the events?
| [Sunday 04 April 2010] [14:22:09] <sustrik> a day?
| [Sunday 04 April 2010] [14:22:12] <sustrik> month?
| [Sunday 04 April 2010] [14:22:14] <sustrik> year?
| [Sunday 04 April 2010] [14:22:26] <desrt>   i have two possible answers
| [Sunday 04 April 2010] [14:22:29] <desrt>   the easy one is "forever"
| [Sunday 04 April 2010] [14:22:38] <sustrik> out of memory results
| [Sunday 04 April 2010] [14:22:40] <desrt>   the less easy one goes something like this:
| [Sunday 04 April 2010] [14:22:47] <desrt>   you maintain a list of active subscribers
| [Sunday 04 April 2010] [14:23:01] <desrt>   each subscriber must check in at least once a month (say) to keep their subscription valid
| [Sunday 04 April 2010] [14:23:11] <desrt>   and you keep events so long as you have active subscribers who the server knows are not up-to-date
| [Sunday 04 April 2010] [14:23:33] <sustrik> how do you know there'll be a subscriber before it evn connects?
| [Sunday 04 April 2010] [14:23:53] <desrt>   i'm saying that a subscriber isn't a subscriber until they first subscribe
| [Sunday 04 April 2010] [14:24:11] <sustrik> ah, sure, it works that way
| [Sunday 04 April 2010] [14:24:33] <desrt>   ah.  nice.
| [Sunday 04 April 2010] [14:24:37] <desrt>   so i can subscribe
| [Sunday 04 April 2010] [14:24:39] <sustrik> the only thing you need to do is set the identity of the subscriber
| [Sunday 04 April 2010] [14:24:39] <desrt>   go away for a week
| [Sunday 04 April 2010] [14:24:44] <desrt>   come back and say "i'm back!"
| [Sunday 04 April 2010] [14:24:50] <desrt>   and get a list of everything that happened meanwhile?
| [Sunday 04 April 2010] [14:24:50] <sustrik> so that the peer knows it's the same subscriber
| [Sunday 04 April 2010] [14:24:57] <sustrik> when reconnection happens
| [Sunday 04 April 2010] [14:24:59] <desrt>   yes.  that's exactly what i'm getting at
| [Sunday 04 April 2010] [14:25:02] <desrt>   awesome :)
| [Sunday 04 April 2010] [14:25:10] <sustrik> you just get it
| [Sunday 04 April 2010] [14:25:17] <sustrik> no need to do anything special
| [Sunday 04 April 2010] [14:25:58] <desrt>   so just popping a uuid in there is a reasonable thing to do
| [Sunday 04 April 2010] [14:26:33] <sustrik> well, the uuid is generated automatically anyway
| [Sunday 04 April 2010] [14:26:39] <sustrik> what you have to ensure
| [Sunday 04 April 2010] [14:26:49] <desrt>   ya.  but i need it to be the same oen across invocations
| [Sunday 04 April 2010] [14:26:55] <sustrik> if you want the subscription to last after subscriber's restart
| [Sunday 04 April 2010] [14:27:06] <sustrik> is that the identity is always the same
| [Sunday 04 April 2010] [14:27:11] <desrt>   so how does that work with respect to subscriptions timing out?
| [Sunday 04 April 2010] [14:27:20] <desrt>   surely the server won't save messages for an identity forever...
| [Sunday 04 April 2010] [14:27:21] <sustrik> no timeouts
| [Sunday 04 April 2010] [14:27:29] <sustrik> it would now :)
| [Sunday 04 April 2010] [14:27:33] <desrt>   heh
| [Sunday 04 April 2010] [14:27:43] <desrt>   so it has an on-disk cache, or....?
| [Sunday 04 April 2010] [14:27:44] <sustrik> feel free to make a patch
| [Sunday 04 April 2010] [14:27:54] <sustrik> in-memory
| [Sunday 04 April 2010] [14:27:58] <desrt>   oh
| [Sunday 04 April 2010] [14:28:01] <desrt>   so it only saves it until reboot...
| [Sunday 04 April 2010] [14:28:08] <sustrik> yes
| [Sunday 04 April 2010] [14:28:11] <desrt>   hrmph
| [Sunday 04 April 2010] [14:28:25]    * desrt was looking for something a little more reliable
| [Sunday 04 April 2010] [14:28:43] <sustrik> sure, there's a lot of messaging solutions out there
| [Sunday 04 April 2010] [14:28:51] <sustrik> rabbitma, activemq etc.
| [Sunday 04 April 2010] [14:29:02] <sustrik> try one of those
| [Sunday 04 April 2010] [14:29:02] <desrt>   ya.  i've had a look around
| [Sunday 04 April 2010] [14:29:08] <desrt>   what attracted me to zmq was its simplicity
| [Sunday 04 April 2010] [14:29:24] <sustrik> yup
| [Sunday 04 April 2010] [14:29:30] <desrt>   my original introduction to this stuff was via a talk about amqp at fudcon
| [Sunday 04 April 2010] [14:29:35] <sustrik> however, it's not as feature complete as other projects
| [Sunday 04 April 2010] [14:30:13] <sustrik> they've mentioned 0mq?
| [Sunday 04 April 2010] [14:30:15] <desrt>   i walked out of the room thinking "neat.  sounds useful.  way too bloated/complex."
| [Sunday 04 April 2010] [14:30:17] <sustrik> interesting
| [Sunday 04 April 2010] [14:30:20] <desrt>   no
| [Sunday 04 April 2010] [14:30:43] <desrt>   a few days ago i saw a post on reddit about 0mq being by the original makers of amqp because amqp had gotten too bloated/complex
| [Sunday 04 April 2010] [14:30:51] <sustrik> ok, i see
| [Sunday 04 April 2010] [14:30:57] <desrt>   and i was like "hm.  i agree.  it must be nice!"
| [Sunday 04 April 2010] [14:31:13] <sustrik> well, persistence is still missing
| [Sunday 04 April 2010] [14:31:21] <desrt>   i'm writing the configuration system for GNOME 3
| [Sunday 04 April 2010] [14:31:31] <desrt>   currently figuring out how to do network support
| [Sunday 04 April 2010] [14:31:46] <sustrik> why do you need persistence?
| [Sunday 04 April 2010] [14:32:09] <desrt>   it has support for databases on your computer that are controlled by someone else
| [Sunday 04 April 2010] [14:32:13] <desrt>   "site settings"
| [Sunday 04 April 2010] [14:32:28] <desrt>   the way it works, when you are online with the network the updates come right away
| [Sunday 04 April 2010] [14:32:34] <desrt>   and you keep a local copy
| [Sunday 04 April 2010] [14:32:38] <desrt>   so when you go offline you still have the settings
| [Sunday 04 April 2010] [14:32:44] <desrt>   and when you connect again, it syncs back up
| [Sunday 04 April 2010] [14:33:22] <sustrik> ok, understood
| [Sunday 04 April 2010] [14:33:41] <desrt>   i currently have a flaky hand-written tcp protocol to do this
| [Sunday 04 April 2010] [14:33:54] <desrt>   was looking for something a bit less crappy
| [Sunday 04 April 2010] [14:34:37] <desrt>   also: i'm sort of drawn to the idea that people could do cool stuff with zeromq that has nothing to do with my particular use case that would result in new ways for people to use my stuff
| [Sunday 04 April 2010] [14:34:52] <desrt>   like add new queue or distribution logic, etc...
| [Sunday 04 April 2010] [14:35:04] <sustrik> desrt: right
| [Sunday 04 April 2010] [14:35:12] <sustrik> still, at the moment there's no persistence
| [Sunday 04 April 2010] [14:35:33] <sustrik> so you have 3 options:
| [Sunday 04 April 2010] [14:35:41] <sustrik> 1. build persistence on top of 0mq
| [Sunday 04 April 2010] [14:35:44] <sustrik> 2. patch 0mq
| [Sunday 04 April 2010] [14:35:56] <sustrik> 3. move to a different solution
| [Sunday 04 April 2010] [14:36:10] <desrt>   4. use it anyway :)
| [Sunday 04 April 2010] [14:36:29] <sustrik> 5. hack the persistence in
| [Sunday 04 April 2010] [14:37:00] <sustrik> persistence is really a very complex problem
| [Sunday 04 April 2010] [14:37:14] <sustrik> to do it properly, lot of resources is needed
| [Sunday 04 April 2010] [14:37:35] <sustrik> however, to server a particulat use case, it's normally pretty easy to do
| [Sunday 04 April 2010] [14:37:35] <desrt>   i'm thinking along these lines: if i can detect that i missed events then i can just redownload the whole DB
| [Sunday 04 April 2010] [14:38:02] <sustrik> so you can place sequence numbers into messages
| [Sunday 04 April 2010] [14:38:09] <desrt>   that's what i do now
| [Sunday 04 April 2010] [14:38:24] <desrt>   each change to the DB has a sequence number
| [Sunday 04 April 2010] [14:38:29] <desrt>   the connecting client tells of the last change it saw
| [Sunday 04 April 2010] [14:38:34] <desrt>   and the server replays what happened since
| [Sunday 04 April 2010] [14:38:55] <sustrik> you can use req/rep sockets for that
| [Sunday 04 April 2010] [14:39:00] <desrt>   sequence numbers are 64bit, so i assume they never wrap
| [Sunday 04 April 2010] [14:39:06] <desrt>   right.
| [Sunday 04 April 2010] [14:39:12] <sustrik> it's much more natural than pub/sub anyway
| [Sunday 04 April 2010] [14:39:12] <desrt>   that gets me RPC-over-TCP(ish), right?
| [Sunday 04 April 2010] [14:39:20] <sustrik> pub/sub is for things like stock quotes
| [Sunday 04 April 2010] [14:39:22] <sustrik> media
| [Sunday 04 April 2010] [14:39:24] <sustrik> etc.
| [Sunday 04 April 2010] [14:39:34] <sustrik> content that lookses value quickly
| [Sunday 04 April 2010] [14:39:42] <sustrik> looses*
| [Sunday 04 April 2010] [14:39:52] <sustrik> desrt: yes
| [Sunday 04 April 2010] [14:39:59] <sustrik> do you mind a roundtrip?
| [Sunday 04 April 2010] [14:39:59] <desrt>   might be appropriate
| [Sunday 04 April 2010] [14:40:09] <desrt>   well
| [Sunday 04 April 2010] [14:40:12] <desrt>   my protocol works sort of like imap now
| [Sunday 04 April 2010] [14:40:28] <desrt>   it's very much not structured RPC-like
| [Sunday 04 April 2010] [14:40:50] <desrt>   the client understands that the server sends it a stream of events
| [Sunday 04 April 2010] [14:41:03] <desrt>   those events are because things happened [some time]
| [Sunday 04 April 2010] [14:41:09] <sustrik> still, the subscriber must acknowledge update receival
| [Sunday 04 April 2010] [14:41:11] <desrt>   so when the client goes online it just says "last time you saw me was _____"
| [Sunday 04 April 2010] [14:41:15] <desrt>   and the server sends events.....
| [Sunday 04 April 2010] [14:41:22] <desrt>   and the client just sees those as events....
| [Sunday 04 April 2010] [14:41:33] <desrt>   no.  they need not.
| [Sunday 04 April 2010] [14:41:41] <desrt>   since the client keeps track of what it knows -- not the server
| [Sunday 04 April 2010] [14:41:54] <sustrik> how do you know how long you keep the updates in the database?
| [Sunday 04 April 2010] [14:42:00] <desrt>   so if the client gets the new events then it will update its serial number and ask for new events next time
| [Sunday 04 April 2010] [14:42:01] <sustrik> hm, forever, i guess?
| [Sunday 04 April 2010] [14:42:11] <desrt>   yes and no
| [Sunday 04 April 2010] [14:42:29] <desrt>   events will eventually drop from the queue if they are overridden by newer events
| [Sunday 04 April 2010] [14:42:36] <desrt>   like if someone writes to /some/setting with sequence number 5
| [Sunday 04 April 2010] [14:42:42] <desrt>   then laster /some/setting again with sequence number 8
| [Sunday 04 April 2010] [14:42:48] <desrt>   5 will never be sent ever again
| [Sunday 04 April 2010] [14:42:57] <sustrik> sure, understood
| [Sunday 04 April 2010] [14:43:31] <desrt>   so the number of events is bound by the natural size of the database
| [Sunday 04 April 2010] [14:44:40] <sustrik> well, i don't believe abt queueing system has functionality like that
| [Sunday 04 April 2010] [14:44:58] <sustrik> if you send X to the queue
| [Sunday 04 April 2010] [14:44:58] <desrt>   k
| [Sunday 04 April 2010] [14:45:03] <sustrik> it will be delivered
| [Sunday 04 April 2010] [14:45:03] <desrt>   i might just stick with my homebrew then
| [Sunday 04 April 2010] [14:45:18] <sustrik> not depending on whether you send X+1 later on
| [Sunday 04 April 2010] [14:45:41] <sustrik> yes, that's an option
| [Sunday 04 April 2010] [14:45:58] <sustrik> anyway, the scenario is interesting
| [Sunday 04 April 2010] [14:46:03] <sustrik> i'll keep it in mind
| [Sunday 04 April 2010] [14:46:24] <sustrik> it's somehow similar to a thing called "last value cache"
| [Sunday 04 April 2010] [14:46:49] <sustrik> it's almost the same as with your scenario
| [Sunday 04 April 2010] [14:47:02] <sustrik> however, after client connect it get _whole_ set of settings
| [Sunday 04 April 2010] [14:47:13] <sustrik> not just those that have been changed in the meantime
| [Sunday 04 April 2010] [14:47:50] <desrt>   hmm
| [Sunday 04 April 2010] [14:47:58] <desrt>   well, my situation is slightly more complicated
| [Sunday 04 April 2010] [14:48:10] <desrt>   since writes may contain more than one value
| [Sunday 04 April 2010] [14:48:22] <desrt>   and there could be non-simple overlaps between different write events
| [Sunday 04 April 2010] [14:48:48] <sustrik> then you definitely have to perform the logic on application level
| [Sunday 04 April 2010] [14:48:59] <sustrik> however, you can still use 0mq instead of raw sockets
| [Sunday 04 April 2010] [14:49:24] <sustrik> just to transport the updates
| [Sunday 04 April 2010] [14:49:34] <desrt>   i'm using GNIO anyway (glib's socket library)
| [Sunday 04 April 2010] [14:49:43] <desrt>   which has the benefit of glib mainloop integration
| [Sunday 04 April 2010] [14:49:49] <desrt>   (which is another question i wanted to ask about 0mq)
| [Sunday 04 April 2010] [14:50:06] <sustrik> what question exactly?
| [Sunday 04 April 2010] [14:50:13] <desrt>   i notice you have your own poll abstraction
| [Sunday 04 April 2010] [14:50:25] <desrt>   but most non-headless apps will already have their own mainloop
| [Sunday 04 April 2010] [14:50:40] <desrt>   and i didn't see a way to integrate 0mq with another mainloop (or even get the fd...)
| [Sunday 04 April 2010] [14:50:48] <sustrik> well, there's no way out of that
| [Sunday 04 April 2010] [14:51:12] <sustrik> POSIX doesn't allow for creating your own fd implementation in user space
| [Sunday 04 April 2010] [14:51:45] <sustrik> lot of political pressure would be needed to amend POSIX
| [Sunday 04 April 2010] [14:52:04] <sustrik> still, it'll take lot of time till all OSes would implement the new functionality
| [Sunday 04 April 2010] [14:52:08] <desrt>   many libraries provide mainloop integration hooks
| [Sunday 04 April 2010] [14:52:26] <desrt>   dbus comes to mind
| [Sunday 04 April 2010] [14:52:37] <sustrik> how does it achieve it?
| [Sunday 04 April 2010] [14:52:49] <desrt>   you give it a set of functions to call
| [Sunday 04 April 2010] [14:52:58] <desrt>   to start watching an fd for read/write
| [Sunday 04 April 2010] [14:53:15] <sustrik> ah, sure that's easy
| [Sunday 04 April 2010] [14:53:31] <desrt>   i guess your case is hard since you're essentially using a synchronous interface
| [Sunday 04 April 2010] [14:53:33] <sustrik> what i mean is that you cannot create your own "fd" in user space
| [Sunday 04 April 2010] [14:53:46] <sustrik> on Linux you have eventfd
| [Sunday 04 April 2010] [14:53:51] <sustrik> which is almost it
| [Sunday 04 April 2010] [14:54:18] <sustrik> (a little bit is missing that can be theoretically added in Linux)
| [Sunday 04 April 2010] [14:54:22] <sustrik> however, it's not POSIX
| [Sunday 04 April 2010] [14:54:32] <sustrik> so other OSes have no equivalent
| [Sunday 04 April 2010] [17:45:56] <mikko>   sustrik: hi!
| [Sunday 04 April 2010] [17:54:47] <mikko>   too late
| [Monday 05 April 2010] [02:19:34] <Bakafish>    Hello group. I was hacking on the new "Butterfly" Example code and have an issue where I successfully send a message over an ipc channel but the blocked read side never seems to see it.
| [Monday 05 April 2010] [02:26:09] <Bakafish>    I'm referring to the final 'sync' message indicating that all the test packets were received. The test packets are going across a similar channel just fine.  But the final sync packet to trigger the end of the timer is sent and the "Sending" process never seems to see it.
| [Monday 05 April 2010] [02:30:45] <sustrik> Bakafish: does the packet cross the network?
| [Monday 05 April 2010] [02:30:55] <sustrik> mikko: re
| [Monday 05 April 2010] [02:31:12] <Bakafish>    It's using ipc (Pipes) so, no :-)
| [Monday 05 April 2010] [02:31:17] <sustrik> ah
| [Monday 05 April 2010] [02:33:46] <Bakafish>    Is it a situation where the packet is below some threshold so it's being cached in a queue? I'm reaching for straws here.
| [Monday 05 April 2010] [02:34:23] <sustrik> Bakafish: no
| [Monday 05 April 2010] [02:34:31] <sustrik> it should be passed immediately
| [Monday 05 April 2010] [02:34:55] <sustrik> so all the components are running on the same box
| [Monday 05 April 2010] [02:35:03] <sustrik> using IPC for communication
| [Monday 05 April 2010] [02:35:05] <sustrik> right?
| [Monday 05 April 2010] [02:35:37] <Bakafish>    I'm getting a good return on the send side. The blocking read blocks correctly, it just never sees the packet. 
| [Monday 05 April 2010] [02:35:50] <Bakafish>    That's correct. 
| [Monday 05 April 2010] [02:36:15] <Bakafish>    The other, seemingly identical connections are behaving correctly.
| [Monday 05 April 2010] [02:36:34] <sustrik> is the IPC filename same on the send and recv side?
| [Monday 05 April 2010] [02:36:46] <sustrik> (sanity check)
| [Monday 05 April 2010] [02:38:25] <Bakafish>    :-) I checked for that, and low and behold, one arg was ipc:///tmp/zmq/send_sync the other ipc://tmp/zmq/send_sync
| [Monday 05 April 2010] [02:38:40] <Bakafish>    Way to introduce myself to the group :-(
| [Monday 05 April 2010] [02:39:56] <Bakafish>    I was ls ing my tmp directory and saw the 3 expected files, didn't think to check for a missing slash. Thanks for the help!
| [Monday 05 April 2010] [02:40:42] <sustrik> no problem :)
| [Monday 05 April 2010] [03:29:51] <Bakafish>    Okay, a question probably rivaling the level of stupidity of my prior one. In the case of more than one agent connecting to a ZMQ_DOWNSTREAM it round robins great, but if an agent goes away it doesn't seem to be aware and packets are seemingly queued or lost for that agent. How do you access the queue registry and manipulate it?
| [Monday 05 April 2010] [03:43:19] <sustrik> Bakafish: the messages already delivered to an application are lost once the application crashes
| [Monday 05 April 2010] [03:43:28] <sustrik> you can limit the damage
| [Monday 05 April 2010] [03:43:42] <sustrik> by setting HWM socket option
| [Monday 05 April 2010] [03:43:58] <sustrik> which specifies how much messages may be queued in any given moment
| [Monday 05 April 2010] [03:46:23] <Bakafish>    That's fair. But it's not what I mean. If I launch the 'Sender' with two 'processor' nodes and one 'results' node and run 1000 checks, everything is fine. 500 each. Then I kill one processor node, so there is only a single node in the pipeline. The queue still thinks there are two (timeout not met yet?) and a second run will result in 500 checks sent to the single processor instance.
| [Monday 05 April 2010] [03:47:09] <sustrik> let me see...
| [Monday 05 April 2010] [03:48:32] <sustrik> hm, i am not sure how UNIX domain sockets handle application crashes
| [Monday 05 April 2010] [03:48:52] <sustrik> maybe it takes some time to notify the sender that the receiver is dead?
| [Monday 05 April 2010] [03:49:19] <sustrik> can you try sleeping for a second after killing the app
| [Monday 05 April 2010] [03:49:30] <sustrik> ?
| [Monday 05 April 2010] [03:49:51] <Bakafish>    If I have to write my own code to see if a process is alive or not that's fine, but how do I identify the processor nodes attached to a paticular queue?
| [Monday 05 April 2010] [03:50:30] <Bakafish>    The server is dispatching these checks and so it has some knowledge of how many there are I'd assume. 
| [Monday 05 April 2010] [03:50:48] <Bakafish>    Ahh, this isn't a problem with TCP?
| [Monday 05 April 2010] [03:51:45] <Bakafish>    Meaning, if I was using TCP instead of sockets I shouldn't expect this behavior?
| [Monday 05 April 2010] [03:51:57] <sustrik> well, i am not sure what's happening, however, the obvious explanation would be that there's an delay between receiver dying and sender being notified about the fact
| [Monday 05 April 2010] [03:52:04] <Bakafish>    sockets, bah. Pipes
| [Monday 05 April 2010] [03:52:16] <sustrik> in the meantime the mesages will be dispatched to that receiver
| [Monday 05 April 2010] [03:52:50] <sustrik> it applies to any communication channel (TCP, IPC, ...)
| [Monday 05 April 2010] [03:53:20] <Bakafish>    I see. I will check to see if it eventually times out. Is there a setting (I recall someone mentioning there was.)
| [Monday 05 April 2010] [03:53:39] <sustrik> nope, it's dependent on IPC implementation
| [Monday 05 April 2010] [03:53:54] <sustrik> there's probably a timeout in the kernel somewhere
| [Monday 05 April 2010] [03:56:12] <Bakafish>    Ahhh the HWM socket option was  what was discussed. I think someone was saying you could limit it but that there were all sorts of places where it could be queued along the path and reducing the number of messages in the queue had performance issues.
| [Monday 05 April 2010] [03:58:00] <Bakafish>    Let me play with it some more since I was using local pipes for convenience, I will be using TCP in production so it may behave better.
| [Monday 05 April 2010] [09:34:03] <mikko>   sustrik: did you notice the issue i opened at github over the hols?
| [Monday 05 April 2010] [09:47:37] <sustrik> mikko: yes, i did
| [Monday 05 April 2010] [10:09:17] <mikko>   cool
| [Monday 05 April 2010] [10:09:25] <mikko>   i got zmq_poll soon implemented 
| [Monday 05 April 2010] [10:09:27] <mikko>   hopefully
| [Monday 05 April 2010] [10:15:16] <sustrik> mikko: seen you've did ~20 commits a day during the holiday :)
| [Monday 05 April 2010] [10:21:45] <mikko>   open source is made by night
| [Monday 05 April 2010] [10:21:47] <mikko>   :)
| [Monday 05 April 2010] [10:21:52] <mikko>   at least in my case
| [Monday 05 April 2010] [10:28:30] <sustrik> mikko: i've linked the PHP wiki page from the main page
| [Monday 05 April 2010] [10:28:52] <mikko>   sustrik: thanks
| [Monday 05 April 2010] [10:28:57] <sustrik> you should announce availability of the binding on the mailing list
| [Monday 05 April 2010] [10:29:15] <mikko>   sustrik: i'll announce as soon as the api stabilizes
| [Monday 05 April 2010] [10:29:22] <sustrik> goodo
| [Monday 05 April 2010] [10:29:24] <mikko>   still need to add polling support
| [Monday 05 April 2010] [10:29:29] <sustrik> sure
| [Monday 05 April 2010] [10:29:31] <mikko>   after that it's fairly complete
| [Monday 05 April 2010] [10:29:55] <mikko>   some of the tests are failing due to the zeromq2 / issue #12
| [Monday 05 April 2010] [10:32:22] <sustrik> i've reproduced the problem
| [Monday 05 April 2010] [10:32:31] <sustrik> trying to fix it...
| [Monday 05 April 2010] [10:32:38] <mikko>   different errors with different socket types
| [Monday 05 April 2010] [10:32:58] <sustrik> yes
| [Monday 05 April 2010] [10:37:31] <mikko>   i'm gonna take a short nap, been touring around berlin all day
| [Monday 05 April 2010] [10:37:32] <mikko>   laters
| [Monday 05 April 2010] [10:52:20] <sustrik> see you
| [Tuesday 06 April 2010] [01:34:20] <CIA-5>  zeromq2: 03Martin Sustrik 07master * r0777567 10/ doc/zmq_bind.txt : ENODEV from zmq_bind error described - http://bit.ly/bvC4mu
| [Tuesday 06 April 2010] [09:23:34] <CIA-5>  zeromq2: 03Martin Lucina 07master * ra7973a2 10/ (doc/zmq_bind.txt doc/zmq_setsockopt.txt): Documentation fixes - http://bit.ly/b03kAA
| [Tuesday 06 April 2010] [09:27:06] <jldupont>   hi - where is the wire-format for 0mq?  I'd like to build an Erlang binding for it.
| [Tuesday 06 April 2010] [09:27:31] <sustrik>    jldupont: hi
| [Tuesday 06 April 2010] [09:27:37] <sustrik>    yes, there is 
| [Tuesday 06 April 2010] [09:27:47] <sustrik>    have a look at zmq_tcp(7)
| [Tuesday 06 April 2010] [09:28:25] <sustrik>    however, wrapping the C library is much simpler than writing it anew in a different language
| [Tuesday 06 April 2010] [09:28:38] <mato>   it's also much faster :-)
| [Tuesday 06 April 2010] [09:28:41] <sustrik>    while the API looks simple the entrails are pretty complex
| [Tuesday 06 April 2010] [09:29:10] <jldupont>   sustrik: hi - I don't want to wrap the C library - there are two ways of interfacing with Erlang: through sockets or through a "driver" written in C.
| [Tuesday 06 April 2010] [09:29:27] <sustrik>    what's the problem with the latter?
| [Tuesday 06 April 2010] [09:29:42] <jldupont>   sustrik: through the "C" driver, it is a pain - the polling part is not nice to do...
| [Tuesday 06 April 2010] [09:30:06] <sustrik>    you mean zmq_poll, right?
| [Tuesday 06 April 2010] [09:30:09] <jldupont>   writing code to handle sockets is very easy in Erlang.
| [Tuesday 06 April 2010] [09:30:39] <jldupont>   no: I don't know zmq_poll but I know the pain of interfacing with Erlang through a C driver though.
| [Tuesday 06 April 2010] [09:30:50] <sustrik>    ok, i see
| [Tuesday 06 April 2010] [09:31:23] <jldupont>   If there isn't a readily available wire-format doc, then I might reconsider writing a binding library for it.
| [Tuesday 06 April 2010] [09:31:33] <mato>   jldupont: hi, I would strongly recommend wrapping libzmq using the C API
| [Tuesday 06 April 2010] [09:32:04] <sustrik>    mato: well, if he wants just a silly sync library he can write it in Erlang
| [Tuesday 06 April 2010] [09:32:12] <mato>   jldupont: the higher level protocols are still in flux and not documented, so while you can "trivially" implement the framing layer, it won't be very useful
| [Tuesday 06 April 2010] [09:32:29] <mato>   sustrik: yeah, but what would be the point of that? nothing to do with 0MQ really...
| [Tuesday 06 April 2010] [09:32:42] <jldupont>   mato: I see.  Then maybe 0MQ is not for me at this point then - I'll stick with RabbitMQ.
| [Tuesday 06 April 2010] [09:33:32] <jldupont>   Thanks, ciao ciao.
| [Tuesday 06 April 2010] [09:33:41] <sustrik>    jldupond bye
| [Tuesday 06 April 2010] [09:40:19] <sustrik>    mato: there's a fix for darwin build system in today's email
| [Tuesday 06 April 2010] [09:40:26] <sustrik>    i haven't apply it
| [Tuesday 06 April 2010] [09:40:36] <sustrik>    left it to you to check it
| [Tuesday 06 April 2010] [09:40:40] <mato>   thanks
| [Tuesday 06 April 2010] [09:40:46] <mato>   haven't got that far in emails yet
| [Tuesday 06 April 2010] [09:40:53] <sustrik>    sure
| [Tuesday 06 April 2010] [10:11:53] <mato>   sustrik: where is the email about darwin? I'm missing it
| [Tuesday 06 April 2010] [10:12:05] <sustrik>    wait a sec
| [Tuesday 06 April 2010] [10:13:00] <sustrik>    [zeromq-dev] Publish/subscribe example "Operation not supported by  device"
| [Tuesday 06 April 2010] [10:13:03] <sustrik>    5:59 AM
| [Tuesday 06 April 2010] [10:13:25] <mato>   ah, people not using useful subjects, i hate that
| [Tuesday 06 April 2010] [10:44:28] <mato>   sustrik: i've fixed it in the jzmq git, i think
| [Tuesday 06 April 2010] [10:44:34] <mato>   will see what michael replies
| [Tuesday 06 April 2010] [10:46:11] <sustrik>    thx
| [Tuesday 06 April 2010] [10:46:47] <sustrik>    mato: you do the highlights?
| [Tuesday 06 April 2010] [10:46:56] <sustrik>    i was just getting to do it myself
| [Tuesday 06 April 2010] [10:47:02] <mato>   i'll do it
| [Tuesday 06 April 2010] [10:47:05] <sustrik>    ok
| [Tuesday 06 April 2010] [10:47:08] <mato>   i know how listpages works more or less
| [Tuesday 06 April 2010] [10:47:14] <sustrik>    good, thanks
| [Tuesday 06 April 2010] [13:47:37] <BusError>   hi guys. Can I use multicast/udp without openpgm ?
| [Tuesday 06 April 2010] [13:48:27] <sustrik>    hi BusError :)
| [Tuesday 06 April 2010] [13:48:33] <sustrik>    no, you can't
| [Tuesday 06 April 2010] [13:48:37] <BusError>   Hey :-)
| [Tuesday 06 April 2010] [13:48:42] <BusError>   ta !
| [Tuesday 06 April 2010] [13:49:04] <BusError>   I need the multicast bit, without necessarily the integrity bit
| [Tuesday 06 April 2010] [13:49:28] <sustrik>    you mean you need unreliable multicast, right?
| [Tuesday 06 April 2010] [13:49:45] <sustrik>    where messages can disapper randomly
| [Tuesday 06 April 2010] [13:49:57] <BusError>   yeah. It's for mostly sending sensor data, and with just a bit of control
| [Tuesday 06 April 2010] [13:50:24] <sustrik>    several people spoke about adding support for that kind of thing to 0MQ
| [Tuesday 06 April 2010] [13:50:30] <sustrik>    but so far nobody did it
| [Tuesday 06 April 2010] [13:50:41] <sustrik>    currently you have to do with reliable multicast
| [Tuesday 06 April 2010] [13:50:58] <BusError>   openpgm looks "heavy" is it just an impression ?
| [Tuesday 06 April 2010] [13:51:16]   * BusError is doing embedded. He counts bytes :-)
| [Tuesday 06 April 2010] [13:51:40] <sustrik>    it's dependent on glib which makes it somewhat fat
| [Tuesday 06 April 2010] [13:52:00] <BusError>   ah yeah. no kidding
| [Tuesday 06 April 2010] [13:52:38] <sustrik>    afaik there's glib-less version of openpgm being worked on
| [Tuesday 06 April 2010] [13:52:53] <sustrik>    that may take some time though
| [Tuesday 06 April 2010] [13:53:22] <BusError>   well I think I'll stick to my poor multicast for now then
| [Tuesday 06 April 2010] [13:54:15] <sustrik>    well, unless you have some time to plug unreliable multicast to 0mq, you are on your own :(
| [Tuesday 06 April 2010] [13:56:01] <BusError>   I'm already on WAY too many mailing lists :-)
| [Tuesday 06 April 2010] [13:56:25] <BusError>   but I'll keep a tab in zeromq, looks fab, good job
| [Tuesday 06 April 2010] [13:56:36] <sustrik>    thanks
| [Tuesday 06 April 2010] [13:56:56] <sustrik>    keep eye on it, presumably someone will add unreliable multicast support
| [Tuesday 06 April 2010] [13:57:03] <BusError>   thanks for your help too
| [Tuesday 06 April 2010] [13:57:09] <sustrik>    you are welcome
| [Tuesday 06 April 2010] [13:57:23] <BusError>   well if I get desperate with my system, I'll keep it in mind :-)
| [Tuesday 06 April 2010] [17:47:43] <|flyte|>    hornetQ vs 0MQ.... FIGTH!
| [Tuesday 06 April 2010] [17:47:46] <|flyte|>    heh.
| [Tuesday 06 April 2010] [17:47:49] <|flyte|>    hornetQ vs 0MQ.... FIGHT
| [Wednesday 07 April 2010] [02:21:22] <CIA-5>    zeromq2: 03Jon Dyte 07master * redfd05d 10/ (13 files in 5 dirs): devices can be created via API - http://bit.ly/dhJb8o
| [Wednesday 07 April 2010] [02:21:24] <CIA-5>    zeromq2: 03Martin Sustrik 07master * r065e4d0 10/ (doc/zmq_bind.txt doc/zmq_setsockopt.txt): Merge branch 'master' of git@github.com:sustrik/zeromq2 - http://bit.ly/brkzAh
| [Wednesday 07 April 2010] [04:41:39] <CIA-5>    zeromq2: 03Martin Sustrik 07master * rb0250cc 10/ builds/msvc/libzmq/libzmq.vcproj : Win32 build fixed - http://bit.ly/9F6ImT
| [Wednesday 07 April 2010] [05:02:04] <mikko>    good morning
| [Wednesday 07 April 2010] [05:11:42] <sustrik>  mikko: morning
| [Wednesday 07 April 2010] [05:12:58] <mikko>    sunny berlin
| [Wednesday 07 April 2010] [05:13:12] <mikko>    drinking double espresso in a cafe and waiting for my flight back
| [Wednesday 07 April 2010] [05:14:16] <sustrik>  lucky you :)
| [Wednesday 07 April 2010] [05:15:15] <mikko>    gdb is acting weird
| [Wednesday 07 April 2010] [05:15:23] <mikko>    (gdb) thread apply all bt
| [Wednesday 07 April 2010] [05:15:24] <mikko>    Cannot find new threads: generic error
| [Wednesday 07 April 2010] [05:15:27] <mikko>    do you ever get this?
| [Wednesday 07 April 2010] [05:15:46] <sustrik>  no
| [Wednesday 07 April 2010] [05:15:57] <sustrik>  but gdb sometimes acks in strange ways
| [Wednesday 07 April 2010] [05:16:04] <sustrik>  memory overwrites (?)
| [Wednesday 07 April 2010] [05:17:10] <mikko>    i get this whenever i run anything using libzmq
| [Wednesday 07 April 2010] [05:17:19] <mikko>    might be a kernel issue as well
| [Wednesday 07 April 2010] [05:17:44] <sustrik>  linux?
| [Wednesday 07 April 2010] [05:17:47] <mikko>    yep
| [Wednesday 07 April 2010] [05:17:56] <mikko>    Linux newdev 2.6.32-3-amd64 #1 SMP Wed Feb 24 18:07:42 UTC 2010 x86_64 GNU/Linux
| [Wednesday 07 April 2010] [05:18:25] <sustrik>  it behaves normally here:
| [Wednesday 07 April 2010] [05:18:26] <sustrik>  Linux istvan 2.6.31-20-generic #58-Ubuntu SMP Fri Mar 12 04:38:19 UTC 2010 x86_64 GNU/Linux
| [Wednesday 07 April 2010] [05:18:40] <mikko>    #58-ubuntu
| [Wednesday 07 April 2010] [05:18:45] <mikko>    thats a lot of compiles :)
| [Wednesday 07 April 2010] [05:18:52] <mikko>    ermm builds
| [Wednesday 07 April 2010] [05:19:04] <sustrik>  :)
| [Wednesday 07 April 2010] [05:19:47] <sustrik>  gcc 4.4.1
| [Wednesday 07 April 2010] [05:20:00] <mikko>    gcc version 4.4.3 20100108 (prerelease) (Debian 4.4.2-9) 
| [Wednesday 07 April 2010] [05:20:19] <mikko>    i'll try compiling with -ggdb3
| [Wednesday 07 April 2010] [05:20:51] <mikko>    shouldnt make difference though
| [Wednesday 07 April 2010] [05:21:50] <mikko>    or my env is just a bit too bleeding edge
| [Wednesday 07 April 2010] [05:22:01] <mikko>    i added polling support last night to php-zeromq
| [Wednesday 07 April 2010] [05:22:12] <mikko>    i think it starts to be feature complete soon
| [Wednesday 07 April 2010] [05:22:36] <sustrik>  great
| [Wednesday 07 April 2010] [05:23:20] <sustrik>  we've started a 0MQ blog, so when you have it ready it can be announced via blog (if you are willing to write few paragraphs about the binding)
| [Wednesday 07 April 2010] [05:25:45] <mikko>    sure
| [Wednesday 07 April 2010] [05:46:00] <mikko>    sustrik: http://pastie.org/907178
| [Wednesday 07 April 2010] [05:46:09] <mikko>    is that me or libzmq?
| [Wednesday 07 April 2010] [05:48:42] <sustrik>  mikko: it's trunk or 2.0.6?
| [Wednesday 07 April 2010] [05:50:44] <sustrik>  looks like trunk...
| [Wednesday 07 April 2010] [05:51:30] <sustrik>  there's
| [Wednesday 07 April 2010] [05:51:36] <sustrik>  a bug there
| [Wednesday 07 April 2010] [05:51:40] <sustrik>  let me fix it
| [Wednesday 07 April 2010] [05:52:40] <mikko>    trunk
| [Wednesday 07 April 2010] [05:52:44] <mikko>    thanks
| [Wednesday 07 April 2010] [05:54:57] <CIA-5>    zeromq2: 03Martin Sustrik 07master * r745db9c 10/ src/session.cpp : unitialised member in seesion_t class - fixed - http://bit.ly/dfTd1L
| [Wednesday 07 April 2010] [05:54:58] <CIA-5>    zeromq2: 03Martin Sustrik 07master * r0f7aab5 10/ builds/msvc/libzmq/libzmq.vcproj : Merge branch 'master' of git@github.com:sustrik/zeromq2 - http://bit.ly/aQv9SX
| [Wednesday 07 April 2010] [05:55:09] <sustrik>  mikko: try now
| [Wednesday 07 April 2010] [06:01:20] <mikko>    sustrik: ok, sec
| [Wednesday 07 April 2010] [06:02:13] <mikko>    off to the airport
| [Wednesday 07 April 2010] [06:02:18] <mikko>    i'll be back later ->
| [Wednesday 07 April 2010] [06:04:58] <sustrik>  cya
| [Wednesday 07 April 2010] [15:32:34] <mikko>    back!
| [Wednesday 07 April 2010] [15:36:25] <mikko>    sustrik: are you still here?
| [Wednesday 07 April 2010] [15:43:45] <sustrik>  mikko: yes
| [Wednesday 07 April 2010] [15:44:49] <mikko>    i found something new
| [Wednesday 07 April 2010] [15:44:57] <mikko>    http://pastie.org/908107
| [Wednesday 07 April 2010] [15:45:04] <mikko>    haven't got down to it yet
| [Wednesday 07 April 2010] [15:45:19] <mikko>    but seems to happen when i create pollitem but don't execute poll
| [Wednesday 07 April 2010] [15:46:15] <sustrik>  hm, pollitem is a dumb structure
| [Wednesday 07 April 2010] [15:46:21] <sustrik>  it should have no effect
| [Wednesday 07 April 2010] [15:47:04] <mikko>    yep, i noticed
| [Wednesday 07 April 2010] [15:47:14] <mikko>    it might be something in my code as well
| [Wednesday 07 April 2010] [15:48:15] <mikko>    # ./test
| [Wednesday 07 April 2010] [15:48:15] <mikko>    Assertion failed: load.get () == 0 (epoll.cpp:49)
| [Wednesday 07 April 2010] [15:48:15] <mikko>    Aborted
| [Wednesday 07 April 2010] [15:48:18] <mikko>    here we go
| [Wednesday 07 April 2010] [15:48:59] <mikko>    that's not the one i get though
| [Wednesday 07 April 2010] [15:49:19] <sustrik>  ok, there's definitely a race condition in socket shutdown mechanism
| [Wednesday 07 April 2010] [15:49:29] <sustrik>  it've been reported serveral times
| [Wednesday 07 April 2010] [15:49:42] <sustrik>  what i need is to reproduce it here
| [Wednesday 07 April 2010] [15:49:51] <sustrik>  do you have a test program?
| [Wednesday 07 April 2010] [15:49:52] <mikko>    ok, let me pastebin it
| [Wednesday 07 April 2010] [15:49:54] <mikko>    yes i do
| [Wednesday 07 April 2010] [15:50:08] <sustrik>  great, can you send it to me?
| [Wednesday 07 April 2010] [15:50:08] <mikko>    http://pastie.org/908126
| [Wednesday 07 April 2010] [15:50:09] <mikko>    there
| [Wednesday 07 April 2010] [15:50:16] <sustrik>  thx
| [Wednesday 07 April 2010] [15:50:41] <mikko>    testing with github master
| [Wednesday 07 April 2010] [15:50:45] <mikko>    (i think)
| [Wednesday 07 April 2010] [15:50:49] <sustrik>  ok
| [Wednesday 07 April 2010] [15:51:53] <mikko>    yes, interesting enough similar code generates: Invalid argument (mutex.hpp:97) under valgrind
| [Wednesday 07 April 2010] [15:52:21] <mikko>    so might be a race condition indeed
| [Wednesday 07 April 2010] [15:53:00] <mikko>    i'm probably stumbling into all possible edge cases here :)
| [Wednesday 07 April 2010] [15:54:13] <sustrik>  looks like it has to do with closing an unconnected socket...
| [Wednesday 07 April 2010] [15:54:23] <sustrik>  i'll give it a closer look tomorrow
| [Wednesday 07 April 2010] [15:54:41] <mikko>    you are right
| [Wednesday 07 April 2010] [16:03:03] <mikko>    Assertion failed: !sending_reply || !more || reply_pipe != pipe_ (rep.cpp:96)
| [Wednesday 07 April 2010] [16:03:04] <mikko>    Aborted
| [Wednesday 07 April 2010] [16:03:08] <mikko>    this is interesting as well
| [Wednesday 07 April 2010] [17:38:32] <lvh>  Hello.
| [Wednesday 07 April 2010] [17:39:01] <lvh>  I've got a use case and I'm wondering how it translates into 0MQ.
| [Wednesday 07 April 2010] [17:39:25] <lvh>  Stuff comes in, all of it gets persisted. Some of it gets pushed to a COMET server and eventually to someone's browser.
| [Wednesday 07 April 2010] [17:40:54] <lvh>  For persistence, I'd like something with load balancing and possibly failover (if possible), but the COMET part is special: out of all the persisters, only one of them needs to be pushed to, but all of the COMET listeners need to be pushed to.
| [Wednesday 07 April 2010] [17:41:13] <lvh>  Can I do that without sending a message twice?
| [Wednesday 07 April 2010] [17:41:30] <lvh>  Can I send a message twice into two exchanges?
| [Thursday 08 April 2010] [01:03:45] <sustrik>   mikko: Assertion failed: !sending_reply || !more || reply_pipe != pipe_ (rep.cpp:96)
| [Thursday 08 April 2010] [01:03:53] <sustrik>   are you playing with multi-part messages?
| [Thursday 08 April 2010] [02:34:34] <CIA-5> zeromq2: 03Martin Sustrik 07master * r38e9103 10/ src/object.cpp : issue 13 (Assertion failed: load.get () == 0 (epoll.cpp:49)) fixed - http://bit.ly/b86MQU
| [Thursday 08 April 2010] [03:20:53] <mikko> sustrik: nope
| [Thursday 08 April 2010] [03:22:42] <mikko> normal request reply
| [Thursday 08 April 2010] [04:15:06] <mikko> sustrik: although i still can't get gdb to work
| [Thursday 08 April 2010] [04:19:14] <sustrik>   mikko: i've fixed thr load.get () == 0 problem
| [Thursday 08 April 2010] [04:19:29] <sustrik>   now looking at !sending_reply || !more || reply_pipe != pipe_ (rep.cpp:96)
| [Thursday 08 April 2010] [04:19:31] <mikko> sustrik: nice!
| [Thursday 08 April 2010] [04:23:53] <mikko> i wonder what's going on now
| [Thursday 08 April 2010] [04:24:24] <mikko> http://pastie.org/908956
| [Thursday 08 April 2010] [04:24:28] <mikko> it get's stuck there
| [Thursday 08 April 2010] [04:26:46] <mikko> that is request-reply pattern: create server, create client, client sends, server recvs, server sends, client recvs
| [Thursday 08 April 2010] [04:27:47] <sustrik>   can you do a quick check with local_lat/remote_lat?
| [Thursday 08 April 2010] [04:27:51] <sustrik>   it's the same pattern
| [Thursday 08 April 2010] [04:28:07] <sustrik>   and the test used to work before the multi-part message changes
| [Thursday 08 April 2010] [04:28:10] <mikko> downgrading to 2.0.6 works 
| [Thursday 08 April 2010] [04:28:18] <sustrik>   ok
| [Thursday 08 April 2010] [04:28:21] <mikko> ok, give me a sec
| [Thursday 08 April 2010] [04:29:03] <mikko> local_lat ?
| [Thursday 08 April 2010] [04:29:31] <sustrik>   perf/local_lat
| [Thursday 08 April 2010] [04:29:35] <sustrik>   latency test
| [Thursday 08 April 2010] [04:30:01] <sustrik>   local_lat tcp://lo:5555 1 1000
| [Thursday 08 April 2010] [04:30:09] <mikko> ah
| [Thursday 08 April 2010] [04:30:10] <sustrik>   remote_lat tcp://localhost:5555 1 1000
| [Thursday 08 April 2010] [04:30:21] <mikko> Assertion failed: false (xrep.cpp:37)
| [Thursday 08 April 2010] [04:30:21] <mikko> Aborted
| [Thursday 08 April 2010] [04:30:28] <mikko> tested with XREP/XREQ
| [Thursday 08 April 2010] [04:30:43] <sustrik>   these are not functional at the moment
| [Thursday 08 April 2010] [04:30:50] <sustrik>   they are not even documented
| [Thursday 08 April 2010] [04:31:05] <mikko> ok
| [Thursday 08 April 2010] [04:31:49] <mikko> message size: 1 [B]
| [Thursday 08 April 2010] [04:31:49] <mikko> roundtrip count: 1000
| [Thursday 08 April 2010] [04:31:49] <mikko> average latency: 17.049 [us]
| [Thursday 08 April 2010] [04:33:21] <sustrik>   hm, that works
| [Thursday 08 April 2010] [04:33:52] <sustrik>   can i get the test peogram that caused the  http://pastie.org/908956 problem?
| [Thursday 08 April 2010] [04:33:55] <mikko> let me make a reproducable case
| [Thursday 08 April 2010] [04:33:59] <sustrik>   thanks
| [Thursday 08 April 2010] [04:34:03] <mikko> sustrik: it's one of the php tests
| [Thursday 08 April 2010] [04:34:07] <sustrik>   :|
| [Thursday 08 April 2010] [04:34:22] <mikko> i should be able to make a C test case
| [Thursday 08 April 2010] [04:45:55] <mikko> no, can't reproduce outside php extension
| [Thursday 08 April 2010] [04:46:24] <mikko> REQ send, REP recv
| [Thursday 08 April 2010] [04:46:29] <mikko> it gets stuck on recv
| [Thursday 08 April 2010] [04:49:11] <mikko> similar thing works if i run client and server in different processes
| [Thursday 08 April 2010] [04:49:37] <sustrik>   it's inproc transport?
| [Thursday 08 April 2010] [04:49:51] <mikko> tcp://
| [Thursday 08 April 2010] [04:50:03] <sustrik>   within a single process?
| [Thursday 08 April 2010] [04:50:11] <mikko> yes
| [Thursday 08 April 2010] [04:50:42] <sustrik>   hm, given that gdb doesn't work for you, there's no chance of getting a backtrace, right?
| [Thursday 08 April 2010] [04:51:23] <mikko> i can test on more stable environment later
| [Thursday 08 April 2010] [04:52:51] <sustrik>   ok
| [Thursday 08 April 2010] [04:53:08] <sustrik>   now for the !sending_reply || !more || reply_pipe != pipe_ (rep.cpp:96) problem
| [Thursday 08 April 2010] [04:53:31] <sustrik>   it looks like there must be multipart message involved somehow
| [Thursday 08 April 2010] [04:53:33] <sustrik>   strange
| [Thursday 08 April 2010] [04:53:40] <sustrik>   is it php or c test?
| [Thursday 08 April 2010] [04:53:55] <mikko> php
| [Thursday 08 April 2010] [04:54:07] <sustrik>   2 endpoints?
| [Thursday 08 April 2010] [04:54:15] <mikko> in two separate processes
| [Thursday 08 April 2010] [04:54:20] <sustrik>   tcp?
| [Thursday 08 April 2010] [04:54:23] <mikko> yes
| [Thursday 08 April 2010] [04:54:27] <mikko> REQ/REP
| [Thursday 08 April 2010] [04:54:39] <sustrik>   ok, do you know how to work with wireshark?
| [Thursday 08 April 2010] [04:54:47] <sustrik>   or tcpdump
| [Thursday 08 April 2010] [04:54:53] <mikko> i can tcpdump
| [Thursday 08 April 2010] [04:55:03] <mikko> wireshark requires a qui iirc?
| [Thursday 08 April 2010] [04:55:42] <sustrik>   there's command line version called tshark
| [Thursday 08 April 2010] [04:55:52] <sustrik>   tcpdump is ok
| [Thursday 08 April 2010] [04:56:05] <sustrik>   i just want to know what data are passed between the two
| [Thursday 08 April 2010] [04:56:11] <sustrik>   can you get that for me?
| [Thursday 08 April 2010] [04:58:11] <mikko> ok, i'll try to get a dump
| [Thursday 08 April 2010] [05:00:03] <mikko> can't seem to lure it out after the latest epoll fix
| [Thursday 08 April 2010] [05:02:59] <mikko> i wonder if it was related to that (something wrong in my end)
| [Thursday 08 April 2010] [05:08:11] <CIA-5> zeromq2: 03Martin Sustrik 07master * r77cbd18 10/ src/pgm_receiver.cpp : issue 11 - Assertion failed: it != peers.end () (pgm_receiver.cpp:161) - http://bit.ly/djxu54
| [Thursday 08 April 2010] [05:20:00] <mikko> sustrik: now i can reproduce
| [Thursday 08 April 2010] [05:20:02] <mikko> time for tcpdump
| [Thursday 08 April 2010] [05:22:53] <olivier_c> hello everybody
| [Thursday 08 April 2010] [05:24:17] <sustrik>   olivier_c: hi
| [Thursday 08 April 2010] [05:26:45] <mikko> sustrik: http://valokuva.org/~mikko/comm.pcap.gz
| [Thursday 08 April 2010] [05:26:59] <mikko> that is tcpdump -vvv -w comm.pcap -i lo port 5555
| [Thursday 08 April 2010] [05:38:46] <olivier_c> sustrik, i've a little question about the behavior of sub multiple sockets.
| [Thursday 08 April 2010] [05:38:55] <sustrik>   sure
| [Thursday 08 April 2010] [05:38:58] <olivier_c> *multiple sub
| [Thursday 08 April 2010] [05:39:07] <sustrik>   mikko: (inspecting the pcap)
| [Thursday 08 April 2010] [05:39:43] <olivier_c>  if i create 2 sub sockets (in different threads), and send messages on them, the reception is "alternate".  i-e socket_one receive a message, then zmq is waiting on socket_two, and ignore messages arriving on socket_one. 
| [Thursday 08 April 2010] [05:39:54] <olivier_c> multiple sub sockets can't receive messages simultaneously ?
| [Thursday 08 April 2010] [05:40:57] <sustrik>   they should
| [Thursday 08 April 2010] [05:41:18] <sustrik>   what socket type are you using on sender side?
| [Thursday 08 April 2010] [05:41:35] <olivier_c> ZMQ_PUB
| [Thursday 08 April 2010] [05:42:08] <sustrik>   " if i create 2 sub sockets (in different threads), and send messages on them"
| [Thursday 08 April 2010] [05:42:13] <sustrik>   you mean "to them"
| [Thursday 08 April 2010] [05:42:14] <sustrik>   right?
| [Thursday 08 April 2010] [05:42:57] <olivier_c> yes,
| [Thursday 08 April 2010] [05:43:26] <mikko> sustrik: possibly related symptom: my poll server example stopped working as well, it doesn't send a message even though zmq_send returns 0 and the socket is continously marked as writable
| [Thursday 08 April 2010] [05:43:33] <mikko> which causes eternal loop in polling
| [Thursday 08 April 2010] [05:43:51] <sustrik>   olivier_c: do you have a test program?
| [Thursday 08 April 2010] [05:44:20] <sustrik>   mikko: ok, as for the tcp dump
| [Thursday 08 April 2010] [05:44:39] <olivier_c> yes, i send you this in few minutes
| [Thursday 08 April 2010] [05:44:42] <mikko> hopefully gdb works on my other box
| [Thursday 08 April 2010] [05:44:44] <sustrik>   there seem to be 3 connections established
| [Thursday 08 April 2010] [05:44:47] <sustrik>   right>
| [Thursday 08 April 2010] [05:44:48] <sustrik>   ?
| [Thursday 08 April 2010] [05:44:58] <sustrik>   olivier_c: please, do
| [Thursday 08 April 2010] [05:46:04] <sustrik>   the on one of them "hello there!" message is sent
| [Thursday 08 April 2010] [05:50:40] <sustrik>   mikko: a double check - the pcap you've sent caused the !sending_reply || !more || reply_pipe != pipe_ (rep.cpp:96) assertion, right?
| [Thursday 08 April 2010] [05:52:42] <mikko> sustrik: yes
| [Thursday 08 April 2010] [05:52:56] <sustrik>   ok
| [Thursday 08 April 2010] [06:03:01] <sustrik>   mikko: hm, there seems to be no way how this can heppen :(
| [Thursday 08 April 2010] [06:03:04] <sustrik>   it's php?
| [Thursday 08 April 2010] [06:03:13] <mikko> yep
| [Thursday 08 April 2010] [06:03:39] <mikko> seems like most of the things are not working with github master
| [Thursday 08 April 2010] [06:04:26] <mikko> the poll-server.php example gets stuck in eternal loop where socket is constantly writable
| [Thursday 08 April 2010] [06:04:31] <mikko> even though message was just sent
| [Thursday 08 April 2010] [06:04:36] <mikko> but the client does not receive the message
| [Thursday 08 April 2010] [06:04:55] <mikko> downgrading to 2.0.6 and everything works
| [Thursday 08 April 2010] [06:05:08] <sustrik>   it possibly has to do with multipart messages
| [Thursday 08 April 2010] [06:05:21] <sustrik>   i have to get it reproduced somehow...
| [Thursday 08 April 2010] [06:05:31] <mikko> you could try with the php extension?
| [Thursday 08 April 2010] [06:05:45] <sustrik>   if you instruct me how to do it
| [Thursday 08 April 2010] [06:06:00]      * sustrik never used php
| [Thursday 08 April 2010] [06:06:25] <mikko> http://php.net/distributions/php-5.3.2.tar.bz2
| [Thursday 08 April 2010] [06:06:36] <mikko> tar xfj php-5.3.2.tar.bz2
| [Thursday 08 April 2010] [06:06:39] <mikko> cd php-5.3.2
| [Thursday 08 April 2010] [06:06:56] <mikko> ./configure --disable-all --prefix=/opt/local --enable-debug
| [Thursday 08 April 2010] [06:07:08] <mikko> make && make install
| [Thursday 08 April 2010] [06:07:16] <mikko> to get php running with debug
| [Thursday 08 April 2010] [06:07:49] <mikko> to install zeromq extension
| [Thursday 08 April 2010] [06:07:50] <mikko> git clone git://github.com/mkoppanen/php-zeromq.git
| [Thursday 08 April 2010] [06:07:54] <mikko> cd php-zeromq
| [Thursday 08 April 2010] [06:08:14] <mikko> /opt/local/bin/phpize && ./configure --with-php-config=/opt/local/bin/php-config
| [Thursday 08 April 2010] [06:08:21] <mikko> make install
| [Thursday 08 April 2010] [06:10:42] <sustrik>   mikko: done
| [Thursday 08 April 2010] [06:10:44] <sustrik>   what now?
| [Thursday 08 April 2010] [06:12:00] <mikko> ls -l /opt/local/lib/php/extensions/debug-non-zts-20090626/
| [Thursday 08 April 2010] [06:12:05] <mikko> do you have zeromq.so there?
| [Thursday 08 April 2010] [06:12:16] <sustrik>   yes, i do
| [Thursday 08 April 2010] [06:12:34] <mikko> create new file /opt/local/lib/php.ini and add:
| [Thursday 08 April 2010] [06:12:38] <mikko> extension_dir=/opt/local/lib/php/extensions/debug-non-zts-20090626/
| [Thursday 08 April 2010] [06:12:42] <mikko> extension=zeromq.so
| [Thursday 08 April 2010] [06:12:56] <mikko> after that /opt/local/bin/php -m should show zeromq in the extension list
| [Thursday 08 April 2010] [06:13:34] <mikko> then in the php-zeromq dir run /opt/local/bin/php examples/poll-server.php 
| [Thursday 08 April 2010] [06:13:41] <mikko> and the client /opt/local/bin/php examples/client.php
| [Thursday 08 April 2010] [06:13:50] <mikko> the client should send and recv single message
| [Thursday 08 April 2010] [06:14:52] <sustrik>   it did
| [Thursday 08 April 2010] [06:15:01] <mikko> are you using 2.0.6 ?
| [Thursday 08 April 2010] [06:15:16] <sustrik>   it's trunk
| [Thursday 08 April 2010] [06:15:20] <sustrik>   i think
| [Thursday 08 April 2010] [06:15:23] <sustrik>   let me double check
| [Thursday 08 April 2010] [06:15:43] <mikko> for me it works with 2.0.6 but trunk gets into eternal loop on the server side
| [Thursday 08 April 2010] [06:16:46] <sustrik>   how do i know?
| [Thursday 08 April 2010] [06:17:03] <sustrik>   it says: Received message: hello there!
| [Thursday 08 April 2010] [06:17:08] <sustrik>   then does nothing
| [Thursday 08 April 2010] [06:17:15] <mikko> does the client exit after that?
| [Thursday 08 April 2010] [06:17:32] <sustrik>   nope 
| [Thursday 08 April 2010] [06:17:37] <sustrik>   one cpu core 100%
| [Thursday 08 April 2010] [06:17:51] <mikko> yep
| [Thursday 08 April 2010] [06:17:57] <mikko> the server is in a loop
| [Thursday 08 April 2010] [06:18:13] <mikko> exit the server using ctrl c
| [Thursday 08 April 2010] [06:18:25] <sustrik>   zmq_poll return POLLIN
| [Thursday 08 April 2010] [06:18:30] <sustrik>   but there's no message
| [Thursday 08 April 2010] [06:18:31] <mikko> if you rerun the same thing and exit client with ctrl c
| [Thursday 08 April 2010] [06:18:32] <sustrik>   right?
| [Thursday 08 April 2010] [06:18:38] <mikko> Received message: hello there!
| [Thursday 08 April 2010] [06:18:39] <mikko> Assertion failed: !sending_reply || !more || reply_pipe != pipe_ (rep.cpp:96)
| [Thursday 08 April 2010] [06:18:39] <mikko> Aborted
| [Thursday 08 April 2010] [06:18:40] <mikko> yep
| [Thursday 08 April 2010] [06:18:56] <mikko> if the client goes away that assertion should appear
| [Thursday 08 April 2010] [06:19:01] <sustrik>   bingo!
| [Thursday 08 April 2010] [06:19:18] <sustrik>   thanks for helping me with reproducing it
| [Thursday 08 April 2010] [06:21:50] <mikko> no prob
| [Thursday 08 April 2010] [06:24:23] <mikko> it might be my code as well, but seems like with 2.0.6 things work as expected
| [Thursday 08 April 2010] [06:52:11] <sustrik>   mikko: how is it linked?
| [Thursday 08 April 2010] [06:52:23] <sustrik>   if i tweak and reinstall 0mq
| [Thursday 08 April 2010] [06:52:30] <mikko> dynamic linking
| [Thursday 08 April 2010] [06:52:31] <sustrik>   will it do
| [Thursday 08 April 2010] [06:52:37] <sustrik>   ok
| [Thursday 08 April 2010] [06:52:37] <mikko> ldd /opt/local/lib/php/extensions/debug-non-zts-20090626/zeromq.so
| [Thursday 08 April 2010] [06:52:50] <mikko> you can make clean && make install in case there are ABI changes
| [Thursday 08 April 2010] [07:15:10] <mikko> sustrik: installed debian stable and gdb works there
| [Thursday 08 April 2010] [07:15:15] <mikko> broken in testing
| [Thursday 08 April 2010] [07:18:47] <sustrik>   fine
| [Thursday 08 April 2010] [07:21:48] <olivier_c> Ah, thanks for the answer sustrik :)
| [Thursday 08 April 2010] [07:22:40] <sustrik>   you are welcome
| [Thursday 08 April 2010] [07:28:10] <olivier_c> btw, other little things : there is still the same problem for doc when install (solution : touch doc/zmq.7) and after that "make" doesn't find rules for "forwarder.1".  (i've comment some lines in Makefile of the "doc" repertory to ignore this)
| [Thursday 08 April 2010] [07:33:46] <sustrik>   olivier_c: that's 2.0.6 or trunk?
| [Thursday 08 April 2010] [07:35:15] <olivier_c> from git,  "sustrik-zeromq2-0f7aab5.tar.gz"
| [Thursday 08 April 2010] [07:36:19] <sustrik>   can you paste the error here?
| [Thursday 08 April 2010] [07:39:12] <olivier_c> so the first one (with "./configure --with-pgm")
| [Thursday 08 April 2010] [07:39:14] <olivier_c> checking whether to install manpages... configure: error: configure thinks we want to install manpages but they're not present. Help!
| [Thursday 08 April 2010] [07:39:27] <olivier_c> => touch doc/zmq.7
| [Thursday 08 April 2010] [07:39:34] <olivier_c> then ok
| [Thursday 08 April 2010] [07:40:34] <sustrik>   hm, have you run autogen.sh?
| [Thursday 08 April 2010] [07:40:59] <olivier_c> yes
| [Thursday 08 April 2010] [07:41:09] <sustrik>   let me try it myself...
| [Thursday 08 April 2010] [07:43:52] <sustrik>   olivier_c: ok, got it
| [Thursday 08 April 2010] [07:43:59] <sustrik>   i'll open a ticket
| [Thursday 08 April 2010] [07:44:24] <sustrik>   btw, if you clone the repo using standard git clone, you won't get the error
| [Thursday 08 April 2010] [07:44:52] <olivier_c_>    re :/
| [Thursday 08 April 2010] [07:45:56] <sustrik>   <sustrik> olivier_c: ok, got it
| [Thursday 08 April 2010] [07:45:56] <sustrik>   <sustrik> i'll open a ticket
| [Thursday 08 April 2010] [07:45:56] <sustrik>   <sustrik> btw, if you clone the repo using standard git clone, you won't get the error
| [Thursday 08 April 2010] [07:46:22] <olivier_c_>    ok 
| [Thursday 08 April 2010] [08:01:44] <keenerd>   Hi.
| [Thursday 08 April 2010] [08:02:07] <keenerd>   Another makefile question
| [Thursday 08 April 2010] [08:03:04] <keenerd>   libzmq.la gets make install'd, and it seems like it should not be
| [Thursday 08 April 2010] [08:04:40] <sustrik>   i am not sure
| [Thursday 08 April 2010] [08:04:44] <sustrik>   shouldn't it?
| [Thursday 08 April 2010] [08:05:18] <keenerd>   It seems to be a bit of scrap from the build process.
| [Thursday 08 April 2010] [08:05:52] <sustrik>   yes, it's a libtool bit
| [Thursday 08 April 2010] [08:06:01] <sustrik>   i am not sure how it is supposed to work
| [Thursday 08 April 2010] [08:06:21] <sustrik>   maybe it can be included by other libtool-based builds?
| [Thursday 08 April 2010] [08:06:45] <sustrik>   keenerd: try ask on the mailing list, please
| [Thursday 08 April 2010] [08:06:55] <sustrik>   someone may have an idea about it
| [Thursday 08 April 2010] [08:07:51] <keenerd>   I'm still trying to sort it out.
| [Thursday 08 April 2010] [08:08:40] <keenerd>   "Optional and frowned upon, but required in some magical cases" seems to be the opinion of .la files.
| [Thursday 08 April 2010] [08:09:21] <sustrik>   so i would say let's rather keep it there
| [Thursday 08 April 2010] [08:09:33] <sustrik>   in case a magical case happens
| [Thursday 08 April 2010] [08:09:51] <keenerd>   I have a user complaining otherwise.
| [Thursday 08 April 2010] [08:10:01] <sustrik>   why so?
| [Thursday 08 April 2010] [08:10:06] <sustrik>   does it mess with anyting?
| [Thursday 08 April 2010] [08:11:07] <keenerd>   Not sure.  It seems my distro has a policy against .la files, that they can quickly become a cross linked mess.
| [Thursday 08 April 2010] [08:11:45] <keenerd>   (Every week [for years now] I learn something new about the underbelly of linux, it seems.)
| [Thursday 08 April 2010] [08:12:15] <sustrik>   well, autotools by itself is complex and mysterious
| [Thursday 08 April 2010] [08:12:21] <keenerd>   True.
| [Thursday 08 April 2010] [08:12:24] <sustrik>   anyway, I have no opinion on the matter
| [Thursday 08 April 2010] [08:12:29] <sustrik>   ask on the mailing list
| [Thursday 08 April 2010] [08:12:37] <sustrik>   if nobody complains we can try to remove it
| [Thursday 08 April 2010] [08:13:19] <keenerd>   Righto.  Thanks.
| [Thursday 08 April 2010] [08:15:24] <keenerd>   Wow, the zmq site is hilariously broken in elinks :-)
| [Thursday 08 April 2010] [08:15:57] <sustrik>   works for me...
| [Thursday 08 April 2010] [08:16:14] <sustrik>   (firefox)
| [Thursday 08 April 2010] [08:17:05] <sustrik>   here's the direct link: http://lists.zeromq.org/mailman/listinfo/zeromq-dev
| [Thursday 08 April 2010] [08:19:38] <keenerd>   Yeah, that is the page.  Had to fire up X just to look at it.
| [Thursday 08 April 2010] [08:20:25] <keenerd>   It ended up crashing Elinks, maybe a stack overflow from some bad JS?
| [Thursday 08 April 2010] [08:24:34] <sustrik>   no idea, it's hosted on a wikifarm
| [Thursday 08 April 2010] [08:24:43] <sustrik>   so we don't write the html ourselves
| [Thursday 08 April 2010] [08:32:56] <keenerd>   ML'ed.
| [Thursday 08 April 2010] [08:33:46] <keenerd>   Thanks again.
| [Thursday 08 April 2010] [09:40:15] <mikko> sustrik: did you find out anything more regarding the assertion?
| [Thursday 08 April 2010] [10:15:05] <sustrik>   mikko: not yet
| [Thursday 08 April 2010] [10:15:15] <sustrik>   been out of office
| [Thursday 08 April 2010] [10:41:00] <sustrik>   mikko: you there?
| [Thursday 08 April 2010] [10:41:09] <sustrik>   here's the problem
| [Thursday 08 April 2010] [10:41:15] <mikko> im here
| [Thursday 08 April 2010] [10:41:16] <sustrik>   zeromq.c:282
| [Thursday 08 April 2010] [10:41:18] <sustrik>   http://github.com/sustrik/zeromq2/blob/master/src/prefix_tree.hpp
| [Thursday 08 April 2010] [10:41:21] <sustrik>   oops
| [Thursday 08 April 2010] [10:41:26] <sustrik>   rc = zmq_send(intern->zms->socket, &message, zmq_msg_size(&message));
| [Thursday 08 April 2010] [10:41:38] <sustrik>   the third parameter is 'flags' not 'size'
| [Thursday 08 April 2010] [10:41:50] <sustrik>   the message contains the size all right
| [Thursday 08 April 2010] [10:41:57] <sustrik>   you don't have to specify it second time
| [Thursday 08 April 2010] [10:42:10] <mikko> makes a lot of sense 
| [Thursday 08 April 2010] [10:42:21] <sustrik>   accidentaly message size of "Got it!" is 7
| [Thursday 08 April 2010] [10:42:21] <mikko> i guess flags were unused in 2.0.6?
| [Thursday 08 April 2010] [10:42:31] <sustrik>   which means bit 0 is set
| [Thursday 08 April 2010] [10:42:51] <sustrik>   there's a ZMQ_NOBLOCK flag
| [Thursday 08 April 2010] [10:43:04] <sustrik>   you haven't hit the problem by chance
| [Thursday 08 April 2010] [10:44:57] <sustrik>   still, it shouldn't fail
| [Thursday 08 April 2010] [10:45:24] <sustrik>   i'll fix my part
| [Thursday 08 April 2010] [10:45:29] <sustrik>   you fix yours
| [Thursday 08 April 2010] [10:45:47] <mikko> thanks alot 
| [Thursday 08 April 2010] [10:45:50] <sustrik>   np
| [Thursday 08 April 2010] [12:01:38] <sophacles> Hey all, slightly offtopic, but I'm instrumenting some systems to learn how they operate under various forms of contention. CPU loading is cake, as is CPU+Network loading. Now im looking for a tool to fill the network pipe without bogging down the cpu. Does anyone here have experience with such a tool?
| [Thursday 08 April 2010] [12:03:31] <sophacles> (all the ones ive come across so far use 100%cpu when filling the pipe)
| [Thursday 08 April 2010] [12:20:26] <sustrik>   no idea, iperf?
| [Thursday 08 April 2010] [12:36:27] <sophacles> unfortunately iperf eats all the cpu. thanks for the suggestion tho!
| [Thursday 08 April 2010] [12:41:25] <sustrik>   :\
| [Thursday 08 April 2010] [12:41:40] <sustrik>   sophacles: what about local_the/remote_thr?
| [Thursday 08 April 2010] [12:41:52] <sustrik>   with a VERY BIG MESSAGE
| [Thursday 08 April 2010] [12:50:38] <sophacles> not sure i follow...
| [Thursday 08 April 2010] [12:52:08] <sustrik>   sophacles: 0MQ performance test
| [Thursday 08 April 2010] [12:52:31] <sustrik>   it does nothing but send large chunk of memory down TCP
| [Thursday 08 April 2010] [12:52:56] <sophacles> cool... ill give that a try!
| [Thursday 08 April 2010] [12:53:14] <sustrik>   ./configure && make
| [Thursday 08 April 2010] [12:53:20] <sustrik>   then it's in perf subdirectory
| [Thursday 08 April 2010] [12:54:04] <sophacles> yeah, i see them there... i just never thought to actually *use* them  :)
| [Thursday 08 April 2010] [12:54:22] <sophacles> kind of a facepalm moment on my part really
| [Thursday 08 April 2010] [12:55:36] <sustrik>   try using message size of several megabytes
| [Thursday 08 April 2010] [12:55:49] <sustrik>   that should ensure the least possible CPU usage
| [Thursday 08 April 2010] [12:56:40] <sophacles> ok, thanks for the tip... ill let you know how that works once i get the stuff pushed to all the right places :
| [Thursday 08 April 2010] [13:05:23] <CIA-5> zeromq2: 03Martin Sustrik 07master * r5cd9f74 10/ src/rep.cpp : few fixed related to multi-part messages in REP socket - http://bit.ly/aMGndT
| [Thursday 08 April 2010] [13:21:39] <CIA-5> zeromq2: 03Martin Sustrik 07master * r027bb1d 10/ src/zmq.cpp : issue 10 - zmq_strerror problem on Windows - http://bit.ly/d8SQ7M
| [Thursday 08 April 2010] [17:08:00] <sophacles> sustrik: so, with the latest zeromq2 stuff debian packaging should probably be cleaned up to not include all the language bindings, correct?
| [Thursday 08 April 2010] [18:37:01] <dirtmcgirt>    hi all. getting a "Exception in thread "main" java.lang.UnsatisfiedLinkError: /usr/local/lib/libjzmq.0.dylib:  no suitable image found." with the latest checkout of jzmq
| [Thursday 08 April 2010] [18:37:17] <dirtmcgirt>    trying the test program: "java -Djava.library.path=/usr/local/lib -classpath ../src/Zmq.jar:. local_lat tcp://127.0.0.1:5555 1 100"
| [Friday 09 April 2010] [09:52:06] <mikko>   sustrik: thanks for r716f4ac!
| [Friday 09 April 2010] [09:59:21] <sustrik> np, i wanted to implement it anyway :)
| [Friday 09 April 2010] [09:59:50] <mikko>   i'll add it to the php extension soon
| [Friday 09 April 2010] [09:59:56] <mikko>   is next release likely to be 2.0.7 ?
| [Friday 09 April 2010] [10:00:11] <mikko>   i guess i'll just add check for zeromq > 2.0.6
| [Friday 09 April 2010] [10:00:53] <sustrik> well, if you want to add support for getsockopt you should chack for 2.0.7
| [Friday 09 April 2010] [10:01:03] <sustrik> check*
| [Friday 09 April 2010] [10:01:28] <mikko>   i'm gonna check for that in any case because most of the tests fail with previous versions
| [Friday 09 April 2010] [10:01:38] <mikko>   due to the 'closing unused socket'
| [Friday 09 April 2010] [10:03:08] <sustrik> ack
| [Friday 09 April 2010] [10:12:43] <mikko>   sustrik: can you up the version number in github?
| [Friday 09 April 2010] [10:12:54] <mikko>   it shows 2.0.6 still (naturally pkg-config check fails)
| [Friday 09 April 2010] [10:20:21] <sustrik> mato: you there?
| [Friday 09 April 2010] [10:20:38] <sustrik> where's the version number defined?
| [Friday 09 April 2010] [10:23:08] <sustrik> there's one in configure.in; i wonder whether that's the only instance...
| [Friday 09 April 2010] [10:23:08] <mato>    sustrik: in configure.in, right at the top, there's a nice big comment that tells you all about it :-)
| [Friday 09 April 2010] [10:23:13] <mato>    yes, it is
| [Friday 09 April 2010] [10:23:23] <sustrik> great
| [Friday 09 April 2010] [10:24:30] <CIA-5>   zeromq2: 03Martin Sustrik 07master * r6ea76e9 10/ configure.in : version bumped to 2.0.7 - http://bit.ly/a8K6TO
| [Friday 09 April 2010] [10:39:59] <mikko>   thanks!
| [Friday 09 April 2010] [10:40:11] <mikko>   sorry, missed the follow-up question
| [Friday 09 April 2010] [10:42:17] <mikko>   checking that libzmq version is at least 2.0.7... yes
| [Friday 09 April 2010] [10:42:19] <mikko>   works !
| [Friday 09 April 2010] [10:42:20] <mikko>   awesome
| [Friday 09 April 2010] [10:47:17] <sustrik> :)
| [Friday 09 April 2010] [12:25:33] <sustrik> mato: can you have a look at this:
| [Friday 09 April 2010] [12:25:34] <sustrik> http://github.com/sustrik/zeromq2/issues#issue/14
| [Friday 09 April 2010] [12:28:48] <mato>    sustrik: AGAIN?!
| [Friday 09 April 2010] [12:29:15] <sustrik> it only happens if you download the github generated tar
| [Friday 09 April 2010] [12:29:24] <mato>    aw crap
| [Friday 09 April 2010] [12:29:27] <sustrik> no idea what's the difference
| [Friday 09 April 2010] [12:29:32] <mato>    you're not supposed to download the github generated tar :)
| [Friday 09 April 2010] [12:29:50] <sustrik> i haven't
| [Friday 09 April 2010] [12:29:53] <sustrik> someone else did
| [Friday 09 April 2010] [12:32:02] <rossij>  If one needs to secure send messages does one have to implement outside of zeromq or is their some way to emable secure network traffic.  From looking at the docs i am guessing I would have to do everything.  
| [Friday 09 April 2010] [12:32:39] <mato>    rossij: see http://www.zeromq.org/faq
| [Friday 09 April 2010] [12:32:59]    * rossij is retarded ;)
| [Friday 09 April 2010] [12:33:17] <rossij>  mato: thank you
| [Friday 09 April 2010] [12:33:29] <mato>    rossij: no problem
| [Friday 09 April 2010] [12:36:51] <mato>    sustrik: the problem is i need some way to differentiate a "release" tarball from anything else
| [Friday 09 April 2010] [12:37:21] <sustrik> what's release tarbal?
| [Friday 09 April 2010] [12:37:30] <mato>    one created with make dist
| [Friday 09 April 2010] [12:37:37] <mato>    which includes the generated documentation
| [Friday 09 April 2010] [12:37:47] <mato>    and thus does not depend on asciidoc being present
| [Friday 09 April 2010] [12:38:19] <sustrik> one thing puzzles me: what's the difference between git clone and downloading and unpacking the tarbal?
| [Friday 09 April 2010] [12:38:31] <sustrik> i would assume i get exactly the same result
| [Friday 09 April 2010] [12:38:33] <sophacles>   Has anyone ever used 0m one way sockets (UPSTREAM/DOWNSTEAM) in conjunction with "digital diodes"?
| [Friday 09 April 2010] [12:38:47] <sustrik> 8o
| [Friday 09 April 2010] [12:38:53] <mato>    sustrik: the difference is that the git clone contains a .git directory so configure knows it's a git clone
| [Friday 09 April 2010] [12:39:20] <mato>    sustrik: if there's no git directory it assumes it's building a release tarball
| [Friday 09 April 2010] [12:39:26] <sustrik> a-ha
| [Friday 09 April 2010] [12:40:15] <sustrik> sophacles: what's "digital diodes"? sounds intriguing.
| [Friday 09 April 2010] [12:40:32] <mato>    the only way to work around it would be to have make dist include some special "stamp" file in the distribution tarball and do the detection on that
| [Friday 09 April 2010] [12:40:49] <sophacles>   lemme find the paper, but short version is: hardware enforced one-way packet flow
| [Friday 09 April 2010] [12:41:11] <sophacles>   secure network concept power grid folks (and other critical infrastructure) are looking at
| [Friday 09 April 2010] [12:41:15] <sustrik> mato: it's your call
| [Friday 09 April 2010] [12:41:32] <sustrik> but depending on .git sounds strange
| [Friday 09 April 2010] [12:43:36] <mato>    well i didn't think anyone would be grabbing tarballs that were not made with make dist
| [Friday 09 April 2010] [12:45:24] <kristianpaul>    hola :)
| [Friday 09 April 2010] [12:45:58] <sustrik> hola
| [Friday 09 April 2010] [12:48:10] <kristianpaul>    what is luuid ?
| [Friday 09 April 2010] [12:48:27] <kristianpaul>    i cant  compile zeromq because of that
| [Friday 09 April 2010] [12:48:41] <sustrik> what's your system?
| [Friday 09 April 2010] [12:49:12] <kristianpaul>    debian squeeze
| [Friday 09 April 2010] [12:49:33] <mato>    kristianpaul: apt-get install uuid-dev
| [Friday 09 April 2010] [12:50:02] <mato>    sustrik: can't we just disable the 'download source' link on github, or (better) redirect it to the zeromq.org download page?
| [Friday 09 April 2010] [12:50:08] <mato>    sustrik: that would make the problem go away
| [Friday 09 April 2010] [12:50:24] <sustrik> mato: thx
| [Friday 09 April 2010] [12:50:33] <mato>    sustrik: if people want to use the git version then they should just clone it
| [Friday 09 April 2010] [12:50:33] <sustrik> can we?
| [Friday 09 April 2010] [12:50:38] <mato>    i don't know
| [Friday 09 April 2010] [12:50:54] <sustrik> never seen such a button
| [Friday 09 April 2010] [12:54:28] <mato>    looks like it can't be done :-(
| [Friday 09 April 2010] [12:57:11] <kristianpaul>    compiled :)
| [Friday 09 April 2010] [12:59:28] <kristianpaul>    i cloned this git://github.com/sustrik/zeromq-chat.git and was okay
| [Friday 09 April 2010] [12:59:47] <sophacles>   sustrik: http://www.dsto.defence.gov.au/publications/2110/DSTO-TR-0785.pdf for the digital diode paper we are looking at
| [Friday 09 April 2010] [13:01:00] <sustrik> sophacles: i give it a look later on
| [Friday 09 April 2010] [13:01:16] <sustrik> however, with one-way communication TCP is not possible, right?
| [Friday 09 April 2010] [13:04:13] <sophacles>   sustrik correct, hence our looking at middleware that has one-way semantics.
| [Friday 09 April 2010] [13:05:36] <sophacles>   so then we can have a box that on one interface has a sock_downstream listening, and pushes the data over another interface which is a hardware diode
| [Friday 09 April 2010] [13:05:59] <sustrik> sophacles: 0MQ is potentially capable of that but you must write true udp transport for that
| [Friday 09 April 2010] [13:06:11] <sustrik> true udp = unrealiable, no acks no nacks
| [Friday 09 April 2010] [13:06:31] <sustrik> couple of people already announced that they want to implement it
| [Friday 09 April 2010] [13:06:42] <sustrik> but obviously nobody have even started with it
| [Friday 09 April 2010] [13:07:23] <kristianpaul>    can i install zeromq i a 8 bit microcontroller?
| [Friday 09 April 2010] [13:07:45] <sustrik> kristianpaul: no idea
| [Friday 09 April 2010] [13:07:55] <kristianpaul>    it uses sdcc
| [Friday 09 April 2010] [13:07:59] <kristianpaul>    ok
| [Friday 09 April 2010] [13:08:11] <sustrik> you need at least c++ runtime, pthreads and libuuid
| [Friday 09 April 2010] [13:08:17] <kristianpaul>    }:/
| [Friday 09 April 2010] [13:08:26] <kristianpaul>    then not :)
| [Friday 09 April 2010] [13:08:57] <sophacles>   this is why im looking at the gateway concept. it provides realiability to the place where the diode is implemented, after the diode there is no reliablility of course, but hte assumption is the hard part is reliability to the diode and ont he other side of the diode
| [Friday 09 April 2010] [13:09:43] <sustrik> then just implement udp transport in 0mq and you can place a forwarder device on each end of the diode
| [Friday 09 April 2010] [13:10:14] <sustrik> tcp->forwarder->udp->diode->forwarder->tcp
| [Friday 09 April 2010] [13:10:15] <sophacles>   right, thats why we like 0mq for this :)
| [Friday 09 April 2010] [13:10:45] <sustrik> implementing udp shouldn't be a big deal
| [Friday 09 April 2010] [13:11:10] <sustrik> if you decide to go that way let me know and i'll point you in the right direction
| [Friday 09 April 2010] [13:11:46] <sophacles>   ok, thanks, for now we have enough for our proposal tho :)
| [Friday 09 April 2010] [13:11:58] <sustrik> goodo
| [Friday 09 April 2010] [13:16:59] <CIA-5>   zeromq2: 03Martin Lucina 07master * r1d28dc9 10/ configure.in : 
| [Friday 09 April 2010] [13:16:59] <CIA-5>   zeromq2: Fix for Issue #14
| [Friday 09 April 2010] [13:16:59] <CIA-5>   zeromq2: Don't fail hard if an unreleased tarball is being built and asciidoc is
| [Friday 09 April 2010] [13:16:59] <CIA-5>   zeromq2: not installed; instead just print a big fat warning - http://bit.ly/9mRdzJ
| [Friday 09 April 2010] [13:25:44] <mato>    sustrik: ok, fixed, i decided not to care and just print a big fat warning if someone has a tarball from git/git clone and no asciidoc
| [Friday 09 April 2010] [13:26:07] <sustrik> sure, np
| [Friday 09 April 2010] [13:26:26] <mato>    the github issue tracker is a bit sucky
| [Friday 09 April 2010] [13:26:30] <mato>    i seem to get random emails
| [Friday 09 April 2010] [13:26:44] <mato>    ah
| [Friday 09 April 2010] [13:26:47] <sustrik> yes, people do
| [Friday 09 April 2010] [13:26:52] <sustrik> get random emials
| [Friday 09 April 2010] [13:27:13] <mato>    yes, but the reason the emails look random is because you're entering issues with no structure
| [Friday 09 April 2010] [13:27:22] <mato>    e.g. GH-13
| [Friday 09 April 2010] [13:27:35] <sustrik> eee
| [Friday 09 April 2010] [13:27:38] <mato>    I get an email with a looooong subject, and a body that says "Here's the test program"
| [Friday 09 April 2010] [13:27:55] <mato>    which is totally unparseable at 1st glance :-)
| [Friday 09 April 2010] [13:28:08] <sustrik> what's the magic then?
| [Friday 09 April 2010] [13:28:22] <mato>    we should have a template for issues
| [Friday 09 April 2010] [13:28:30] <mato>    so that the body of the email actually makes sense
| [Friday 09 April 2010] [13:28:35] <sustrik> ah
| [Friday 09 April 2010] [13:28:44] <sustrik> lemme see
| [Friday 09 April 2010] [13:28:44] <mato>    but i'm not sure if github can do that, i know that google code can
| [Friday 09 April 2010] [13:29:10] <sustrik> still i don't get why emails are send _randomly_
| [Friday 09 April 2010] [13:29:23] <mato>    me neither
| [Friday 09 April 2010] [13:29:30] <sustrik> can we turn it off?
| [Friday 09 April 2010] [13:29:35] <mato>    don't know
| [Friday 09 April 2010] [13:29:47] <mato>    i'll look into it and try and file bugs/contact the github people
| [Friday 09 April 2010] [13:29:58] <mato>    it's very hard to follow the way it works now
| [Friday 09 April 2010] [13:30:54] <sustrik> hm, i wanted to ask you to kill the jira
| [Friday 09 April 2010] [13:31:06] <sustrik> but it seems it's maybe to early for that
| [Friday 09 April 2010] [13:31:11] <mato>    maybe
| [Friday 09 April 2010] [13:31:18] <sustrik> but you can definitely kill the old svn
| [Friday 09 April 2010] [13:31:25] <sustrik> nobody using it anymore
| [Friday 09 April 2010] [13:31:38] <mato>    not my job, email ewen
| [Friday 09 April 2010] [13:31:43] <sustrik> ok
| [Friday 09 April 2010] [13:31:55] <mato>    but i suggest you wait until we can kill the jira
| [Friday 09 April 2010] [13:32:07]    * sustrik is waiting
| [Friday 09 April 2010] [13:32:08] <mato>    then you can get ewen to just kill the entire svfastmq vm
| [Friday 09 April 2010] [13:32:09] <mato>    in one go
| [Friday 09 April 2010] [13:32:35] <mato>    i will try and talk to the github people to see if we can get some improvements made to the issue tracker
| [Friday 09 April 2010] [13:32:40] <sustrik> ack
| [Friday 09 April 2010] [13:32:48] <mato>    templates that users must fill in when submitting would be especially good
| [Friday 09 April 2010] [13:33:10] <mato>    "Please describe your Operating System, version," and so on
| [Friday 09 April 2010] [13:33:16] <mato>    otherwise it'll be a total mess
| [Friday 09 April 2010] [13:33:31] <sustrik> yup
| [Friday 09 April 2010] [13:34:48] <dirtmcgirt>  sustrik: about the java problem
| [Friday 09 April 2010] [13:35:01] <dirtmcgirt>  sustrik: OS is OS X
| [Friday 09 April 2010] [13:35:20] <dirtmcgirt>  getting a "Exception in thread "main" java.lang.UnsatisfiedLinkError: /usr/local/lib/libjzmq.0.dylib:  no suitable image found." with the latest checkout of jzmq
| [Friday 09 April 2010] [13:35:32] <dirtmcgirt>  trying the test program: "java -Djava.library.path=/usr/local/lib -classpath ../src/Zmq.jar:. local_lat tcp://127.0.0.1:5555 1 100"
| [Friday 09 April 2010] [13:35:43] <sustrik> is there the library on the path?
| [Friday 09 April 2010] [13:35:59] <dirtmcgirt>  yep
| [Friday 09 April 2010] [13:36:01] <sustrik>  /usr/local/lib/libjzmq.0.dylib
| [Friday 09 April 2010] [13:36:25] <sustrik> what does "no suitable image found" mean then?
| [Friday 09 April 2010] [13:37:07] <dirtmcgirt>  going to try an rebuild from scratch
| [Friday 09 April 2010] [13:38:19] <mato>    sustrik: dinnertime, cyl in kut?
| [Friday 09 April 2010] [13:38:29] <sustrik> yes
| [Friday 09 April 2010] [13:41:25] <sustrik> dirtmcgirt: i cannot help you much as i have no experience with osx, however, try asking at the mailing list, there are definitely OSX people there
| [Friday 09 April 2010] [13:58:10] <dirtmcgirt>  dirtmcgirt: no known problems on linux (CentOS 5)?
| [Friday 09 April 2010] [13:58:14] <dirtmcgirt>  oops, sustrik
| [Friday 09 April 2010] [13:58:41] <sustrik> i am not aware of any
| [Friday 09 April 2010] [16:36:28] <sophacles>   interesting: on host A - an ubuntu maching, the toy client and server from the webpage compile just fine, on a debian machine tho, the client breaks with errors about context_t and socket_t not being members of zmq
| [Friday 09 April 2010] [16:36:35] <sophacles>   anyone seen this before?
| [Friday 09 April 2010] [16:45:40] <sophacles>   hahaha nevermind -- the deb box had an ancient copy of zeromq1 sitting on it 
| [Friday 09 April 2010] [18:19:29] <dirtmcgirt>  any binary builds for java?
| [Friday 09 April 2010] [18:19:34] <dirtmcgirt>  jar files?
| [Friday 09 April 2010] [18:24:09] <dirtmcgirt>  getting build problems on CentOS 5
| [Friday 09 April 2010] [18:24:19] <dirtmcgirt>  make[2]: util.hpp: Command not found
| [Saturday 10 April 2010] [04:52:41] <mikko> good morning
| [Saturday 10 April 2010] [04:52:58] <sustrik>   mikko: morning
| [Saturday 10 April 2010] [05:02:03] <mikko> getSockOpt added
| [Saturday 10 April 2010] [05:02:37] <sustrik>   !
| [Saturday 10 April 2010] [05:02:51] <mikko> ended up adding ifndef and http://github.com/mkoppanen/php-zeromq/blob/master/config.m4#L37
| [Saturday 10 April 2010] [05:04:37] <sustrik>   2.0.6 vs. 2.0.7 isn't sufficient?
| [Saturday 10 April 2010] [05:05:24] <mikko> if you do $z = new ZeroMq(ZeroMQ::SOCKET_REP); $z->connect("tcp://lo:5555"); unset($z); in 2.0.6 it will crash on assertion error
| [Saturday 10 April 2010] [05:10:27] <mikko> with 2.0.6 people need to remember that socket needs recv/send or when the object get garbage collected it might terminate the script
| [Saturday 10 April 2010] [05:10:41] <mikko> but other than that it should work with 2.0.6 as well
| [Saturday 10 April 2010] [05:26:48] <mato>  sustrik: are you there?
| [Saturday 10 April 2010] [05:26:55] <sustrik>   mato: yes
| [Saturday 10 April 2010] [05:27:16] <mato>  sustrik: do you have the original patch for the debian packaging by peter busser? (that which is currently in  git)
| [Saturday 10 April 2010] [05:27:44] <sustrik>   i presume
| [Saturday 10 April 2010] [05:27:50] <mato>  sustrik: can you find it please?
| [Saturday 10 April 2010] [05:27:54] <sustrik>   but why not get it from git?
| [Saturday 10 April 2010] [05:28:08] <mato>  sustrik: i need to see that he sent it under the MIT license
| [Saturday 10 April 2010] [05:28:51] <mato>  sustrik: could you please find the email with the original patch and forward it to me? it must have gone to you privately since i don't see anything obvious in the list archive
| [Saturday 10 April 2010] [05:30:36] <sustrik>   found couple of them
| [Saturday 10 April 2010] [05:30:39] <sustrik>   forwarding...
| [Saturday 10 April 2010] [05:30:42] <mato>  thanks
| [Saturday 10 April 2010] [05:31:39] <sustrik>   anyway, it's just packaging, the license is irrelevant imo
| [Saturday 10 April 2010] [05:31:44] <mato>  no it's not
| [Saturday 10 April 2010] [05:32:03]      * sustrik leaving now
| [Saturday 10 April 2010] [05:32:10] <sustrik>   starting test env
| [Saturday 10 April 2010] [05:32:14] <mato>  thanks
| [Saturday 10 April 2010] [05:42:06] <mikko> github is interesting: when you go to the wiki side it doesnt show you are logged in
| [Saturday 10 April 2010] [05:42:12] <mikko> shows "Pricing and signup"
| [Saturday 10 April 2010] [05:45:28] <mikko> have you got redhat packaging ?
| [Saturday 10 April 2010] [05:45:35] <mato>  nope
| [Saturday 10 April 2010] [05:45:40] <mikko> i can do spec files if that is needed
| [Saturday 10 April 2010] [05:45:49] <mikko> i've been doing them at work for the past year and a half
| [Saturday 10 April 2010] [05:46:25] <mato>  might be useful
| [Saturday 10 April 2010] [05:46:39] <mato>  tho we'll have to figure out where the spec files will go
| [Saturday 10 April 2010] [05:46:52] <mato>  i had to spend 3 days convincing sustrik that the debian packaging could be in debian/
| [Saturday 10 April 2010] [05:47:15] <mikko> redhat/ usually
| [Saturday 10 April 2010] [05:47:43] <mato>  that'll just annoy him about "creating more mess in the top level directory" :-)
| [Saturday 10 April 2010] [05:47:52] <mikko> usually in release packages .spec is in the root of the release package
| [Saturday 10 April 2010] [05:48:09] <mikko> that allows building with rpmbuild -tb zeromq-x.x.x.tar.gz
| [Saturday 10 April 2010] [05:48:15] <mato>  right
| [Saturday 10 April 2010] [05:48:37] <mato>  well, we can figure something out
| [Saturday 10 April 2010] [05:48:45] <mato>  it'd be nice to have RPM-land accounted for
| [Saturday 10 April 2010] [05:48:48] <mikko> maybe in builds/ ?
| [Saturday 10 April 2010] [05:48:51] <mato>  yeah
| [Saturday 10 April 2010] [05:49:12] <mato>  and make dist can copy them to the toplevel when making the tarball, sustrik will never know :-)
| [Saturday 10 April 2010] [05:49:26] <mato>  that way the rpmbuild trick you mentioned will work
| [Saturday 10 April 2010] [05:49:33] <mato>  if that's what people are used to
| [Saturday 10 April 2010] [05:49:40] <mato>  i've not used a rpm-based distro for years
| [Saturday 10 April 2010] [05:49:57] <mikko> most of the companies where i've worked for use RHEL
| [Saturday 10 April 2010] [05:50:35] <mato>  yeah, i know
| [Saturday 10 April 2010] [05:50:46] <mato>  if you have the time, the contribution would be welcome
| [Saturday 10 April 2010] [05:50:54] <mikko> im already on it
| [Saturday 10 April 2010] [05:51:09] <mato>  i suggest you copy the current debian packaging
| [Saturday 10 April 2010] [05:51:16] <mato>  (that in adrian's hg repository)
| [Saturday 10 April 2010] [05:51:21] <mato>  in terms of actual packages built
| [Saturday 10 April 2010] [05:51:29] <mato>  you want something equivalent to:
| [Saturday 10 April 2010] [05:51:34] <mato>  dpkg-deb: building package `libzmq0' in `../libzmq0_2.0.6beta.dfsg-2_amd64.deb'.
| [Saturday 10 April 2010] [05:51:34] <mato>  dpkg-deb: building package `zeromq-bin' in `../zeromq-bin_2.0.6beta.dfsg-2_amd64.deb'.
| [Saturday 10 April 2010] [05:51:37] <mato>  dpkg-deb: building package `libzmq-dev' in `../libzmq-dev_2.0.6beta.dfsg-2_amd64.deb'.
| [Saturday 10 April 2010] [05:51:40] <mato>  dpkg-deb: building package `libzmq-dbg' in `../libzmq-dbg_2.0.6beta.dfsg-2_amd64.deb'.
| [Saturday 10 April 2010] [06:11:59] <mikko> hmm.. testing the spec file and i didn't have 'g++' but configure still passes
| [Saturday 10 April 2010] [06:13:11] <mato>  that's strange :) I've not tried on a machine w/o g++
| [Saturday 10 April 2010] [06:33:20] <mikko> does --with-pgm add additional dependencies?
| [Saturday 10 April 2010] [06:37:27] <mikko> ah got it
| [Saturday 10 April 2010] [06:52:23] <mato>  yes
| [Saturday 10 April 2010] [06:52:27] <mato>  glib and gthread
| [Saturday 10 April 2010] [06:52:42] <mato>  but you only want --with-pgm on x86 and amd64
| [Saturday 10 April 2010] [06:53:47] <mikko> 95% of the hosts?
| [Saturday 10 April 2010] [06:53:48] <mikko> maybe
| [Saturday 10 April 2010] [06:54:42] <mato>  the point is pgm is not supported and won't build on anything else atm
| [Saturday 10 April 2010] [06:55:05] <mato>  so on anything non-x86 you want to build packages w/o that
| [Saturday 10 April 2010] [06:55:11] <mato>  which is what the debian package does
| [Saturday 10 April 2010] [06:55:18] <mikko> RHEL supports
| [Saturday 10 April 2010] [06:55:19] <mikko> # Intel Itanium2
| [Saturday 10 April 2010] [06:55:19] <mikko> # IBM POWER
| [Saturday 10 April 2010] [06:55:19] <mikko> # IBM System z and S/390
| [Saturday 10 April 2010] [06:55:24] <mikko> apart from the others
| [Saturday 10 April 2010] [06:55:29] <mikko> i'll add a condition for that
| [Saturday 10 April 2010] [07:18:43] <mikko> http://github.com/mkoppanen/zeromq2/blob/master/zeromq2.spec
| [Saturday 10 April 2010] [07:18:47] <mikko> initial version there
| [Saturday 10 April 2010] [07:18:54] <mikko> i'll do some tweaking later today
| [Saturday 10 April 2010] [07:30:04] <CIA-5> zeromq2: 03Adrian von Bidder 07master * r8aa2acd 10/ (35 files in 2 dirs): Debian packaging update from Adrian von Bidder - http://bit.ly/bfp9zr
| [Saturday 10 April 2010] [07:30:06] <CIA-5> zeromq2: 03Martin Lucina 07master * r1dc0380 10/ (4 files): 
| [Saturday 10 April 2010] [07:30:06] <CIA-5> zeromq2: Debian packaging fixes suitable for 0MQ git
| [Saturday 10 April 2010] [07:30:06] <CIA-5> zeromq2: Removed README.source, TODO.source since these are irrelevant to a generic
| [Saturday 10 April 2010] [07:30:06] <CIA-5> zeromq2: git package.
| [Saturday 10 April 2010] [07:30:07] <CIA-5> zeromq2: Fixed spelling in debian/copyright.
| [Saturday 10 April 2010] [07:30:07] <CIA-5> zeromq2: Removed RFC check in debian/rules, again irrelevant to a generic git package. - http://bit.ly/cNRlAG
| [Saturday 10 April 2010] [10:19:01] <sustrik>   mato: ping
| [Saturday 10 April 2010] [10:19:08] <mato>  sustrik: yes?
| [Saturday 10 April 2010] [10:19:18] <sustrik>   still using the test env?
| [Saturday 10 April 2010] [10:19:23] <mato>  no
| [Saturday 10 April 2010] [10:19:29] <mato>  didnt get around to it at all
| [Saturday 10 April 2010] [10:19:29] <sustrik>   can i switch it off?
| [Saturday 10 April 2010] [10:19:33] <mato>  am mucking with the build stuff
| [Saturday 10 April 2010] [10:19:34] <mato>  yes
| [Saturday 10 April 2010] [10:19:42] <sustrik>   goodo, it's kind of noisy
| [Saturday 10 April 2010] [10:20:20] <sustrik>   btw, can we set cia for the projects that don't support it yet?
| [Saturday 10 April 2010] [10:20:36] <mato>  ?
| [Saturday 10 April 2010] [10:21:01] <sustrik>   i have at least rbzmq and jzmq
| [Saturday 10 April 2010] [10:21:11] <sustrik>   are those reported via CIA?
| [Saturday 10 April 2010] [10:21:18] <mato>  just a moment
| [Saturday 10 April 2010] [10:21:24] <mato>  let me finish what i'm doing :)
| [Saturday 10 April 2010] [10:21:43] <sustrik>   fine, ping me then
| [Saturday 10 April 2010] [10:22:05] <CIA-5> zeromq2: 03Martin Lucina 07master * r770aedb 10/ (configure.in src/Makefile.am): 
| [Saturday 10 April 2010] [10:22:05] <CIA-5> zeromq2: Build fixes for Solaris and non-GNU compilers
| [Saturday 10 April 2010] [10:22:05] <CIA-5> zeromq2: Compiling C++ code with -D_POSIX_SOURCE on Solaris is unsupported, so remove it.
| [Saturday 10 April 2010] [10:22:05] <CIA-5> zeromq2: Isolate GCC-isms inside checks that we are actually using GCC/G++.
| [Saturday 10 April 2010] [10:22:05] <CIA-5> zeromq2: Only check for -lstdc++ when on GCC and doing static linking. - http://bit.ly/bvl9cL
| [Saturday 10 April 2010] [10:27:12] <CIA-5> zeromq2: 03Martin Sustrik 07master * rc214a24 10/ (src/forwarder.cpp src/queue.cpp src/streamer.cpp): fix for Sun C++ 5.8 - http://bit.ly/9gea7k
| [Saturday 10 April 2010] [10:33:38] <mikko> make[2]: *** No rule to make target `zmq_forwarder.1', needed by `dist-hook'.  Stop.
| [Saturday 10 April 2010] [10:33:43] <mikko> during make dist
| [Saturday 10 April 2010] [10:33:48] <mikko> do i need to do something special?
| [Saturday 10 April 2010] [10:34:02] <mato>  make dist generates documentation
| [Saturday 10 April 2010] [10:34:14] <mato>  so you need asciidoc and xmlto installed
| [Saturday 10 April 2010] [10:34:21] <mato>  then re-run configure and it'll work fine
| [Saturday 10 April 2010] [10:35:40] <mikko> mm
| [Saturday 10 April 2010] [10:35:44] <mikko> hefty package
| [Saturday 10 April 2010] [10:35:44] <mikko> Need to get 492MB/494MB of archives.
| [Saturday 10 April 2010] [10:35:45] <mikko> After this operation, 899MB of additional disk space will be used.
| [Saturday 10 April 2010] [10:35:50] <mato>  :-)
| [Saturday 10 April 2010] [10:35:55] <mato>  yeah, i know
| [Saturday 10 April 2010] [10:36:13] <mato>  normal users need never see it though
| [Saturday 10 April 2010] [10:36:32] <mato>  what are you doing 'make dist' for anyway? :-)
| [Saturday 10 April 2010] [10:37:14] <mato>  crap
| [Saturday 10 April 2010] [10:37:15] <mikko> moved the spec file to builds/redhat/zeromq2.spec and making a dist-hook to copy to top-level
| [Saturday 10 April 2010] [10:37:16] <mato>  sustrik: ping
| [Saturday 10 April 2010] [10:37:20] <mikko> and remove after distclean
| [Saturday 10 April 2010] [10:37:24] <mato>  ah :)
| [Saturday 10 April 2010] [10:37:26] <mato>  fair enough
| [Saturday 10 April 2010] [10:37:50] <mikko> also trying to look into why configure succeeds when g++ is missing
| [Saturday 10 April 2010] [10:38:01] <mikko> or why it tries to use g++ even though it's not there
| [Saturday 10 April 2010] [10:38:10] <mato>  default behaviour
| [Saturday 10 April 2010] [10:38:23] <mato>  http://www.gnu.org/software/hello/manual/autoconf/C_002b_002b-Compiler.html#C_002b_002b-Compiler
| [Saturday 10 April 2010] [10:38:26] <sustrik>   mato: pong
| [Saturday 10 April 2010] [10:38:34] <mato>  . If none of those checks succeed, then as a last resort set CXX to g++. 
| [Saturday 10 April 2010] [10:38:44] <mato>  sustrik: I have a problem with the perf tests
| [Saturday 10 April 2010] [10:38:52] <mikko> If none of those checks succeed, then as a last resort set CXX to g++. 
| [Saturday 10 April 2010] [10:38:53] <mikko> ah
| [Saturday 10 April 2010] [10:39:07] <sustrik>   yes?
| [Saturday 10 April 2010] [10:39:34] <mato>  they need to link against the C++ runtime
| [Saturday 10 April 2010] [10:39:46] <sustrik>   they do
| [Saturday 10 April 2010] [10:39:50] <mato>  no they don't
| [Saturday 10 April 2010] [10:39:57] <sustrik>   the libzmq does
| [Saturday 10 April 2010] [10:40:04] <mato>  I have a heap of checks in configure.in to deal with exactly this
| [Saturday 10 April 2010] [10:40:13] <mato>  No it doesn't
| [Saturday 10 April 2010] [10:40:16] <mato>  let me explain
| [Saturday 10 April 2010] [10:40:23]      * sustrik is listening
| [Saturday 10 April 2010] [10:40:47] <mato>  the only case where it "just works" is if libzmq.so is a shared library
| [Saturday 10 April 2010] [10:40:54] <sustrik>   ack
| [Saturday 10 April 2010] [10:40:57] <mato>  even then only reliably on Linux/gcc
| [Saturday 10 April 2010] [10:41:12] <mato>  now, I cannot realistically make all the other combinations work
| [Saturday 10 April 2010] [10:41:20] <mato>  however there's a trivial way to make it "just work" for us
| [Saturday 10 April 2010] [10:41:44] <mato>  which is to rename those source files to .cpp, which will cause them to be built with the C++ compiler, whatever that may be, which will just work
| [Saturday 10 April 2010] [10:41:56] <sustrik>   sure, why not
| [Saturday 10 April 2010] [10:42:00] <mato>  so, can i make that chage?
| [Saturday 10 April 2010] [10:42:01] <mato>  good
| [Saturday 10 April 2010] [10:42:10] <mato>  i'll do that, i just wanted you to understand why
| [Saturday 10 April 2010] [10:43:31]      * sustrik thinks there should be a slim C++ variant with no specific runtime
| [Saturday 10 April 2010] [10:43:45] <sustrik>   OO-macros for CV
| [Saturday 10 April 2010] [10:43:47] <sustrik>   C
| [Saturday 10 April 2010] [10:43:52] <mato>  go complain to Bjarne Stroustrup
| [Saturday 10 April 2010] [10:44:02] <mikko> Bjarne hates macros
| [Saturday 10 April 2010] [10:44:17] <sustrik>   i mean, i am using nothing out of C++ runtime
| [Saturday 10 April 2010] [10:44:28] <sustrik>   almost
| [Saturday 10 April 2010] [10:44:49] <sustrik>   :|
| [Saturday 10 April 2010] [10:46:24] <sustrik>   btw, what about linking C++ runtime statically?
| [Saturday 10 April 2010] [10:46:49] <mato>  sustrik: there is *no* portable way to "link the C++ runtime" other than using the C++ compiler
| [Saturday 10 April 2010] [10:47:00] <sustrik>   gh
| [Saturday 10 April 2010] [10:47:18] <mato>  the libstdc++ stuff i had in configure was a hack for gcc
| [Saturday 10 April 2010] [10:47:22] <mato>  and it's getting in the way
| [Saturday 10 April 2010] [10:47:44] <sustrik>   go on, get rid of it
| [Saturday 10 April 2010] [10:47:48] <mato>  which is why i want to compile/link all our binaries with the C++ compiler and not care about the problem
| [Saturday 10 April 2010] [10:52:53] <CIA-5> rbzmq: 03Martin Sustrik 07master * rcd25ce4 10/ rbzmq.cpp : setting integer socket options fixed - http://bit.ly/d0pygW
| [Saturday 10 April 2010] [10:59:59] <sustrik>   mato: i've enabled CIA for jzmq and clrzmq in github, please update your part of it later on
| [Saturday 10 April 2010] [11:00:15] <mato>  ok
| [Saturday 10 April 2010] [11:05:02] <CIA-5> zeromq2: 03Martin Lucina 07master * rf6fa41d 10/ (10 files in 2 dirs): 
| [Saturday 10 April 2010] [11:05:02] <CIA-5> zeromq2: Compile perf tests with the C++ compiler
| [Saturday 10 April 2010] [11:05:02] <CIA-5> zeromq2: This lets us build the binaries in a portable fashion w/o having to worry
| [Saturday 10 April 2010] [11:05:02] <CIA-5> zeromq2: about how to link with the C++ runtime. - http://bit.ly/aJcfUn
| [Saturday 10 April 2010] [11:05:02] <CIA-5> zeromq2: 03Martin Lucina 07master * rb668387 10/ (5 files in 5 dirs): Remove -Wxxx gcc-isms from subdir Makefiles - http://bit.ly/a0KHqq
| [Saturday 10 April 2010] [11:07:45] <mikko> ok, make dist in debian -> copy tarball to CentOS -> rpmbuild -tb zeromq-2.0.7.tar.gz seems to generate RPMs as expected
| [Saturday 10 April 2010] [11:08:05] <mikko> i wonder if the debian/ should be moved to builds and copied during make dist
| [Saturday 10 April 2010] [11:10:01] <mato>  libtool: link: CC -g -o .libs/local_lat local_lat.o  ../src/.libs/libzmq.so -luuid -lrt -lnsl -lsocket -lpthread -R/usr/local/lib
| [Saturday 10 April 2010] [11:10:05] <mato>  Undefined                       first referenced symbol                             in file
| [Saturday 10 April 2010] [11:10:08] <mato>  bool std::operator==<char,std::char_traits<char>,std::allocator<char> >(const std::basic_string<__type_0,__type_1,__type_2>&,const __type_0*) ../src/.libs/libzmq.so
| [Saturday 10 April 2010] [11:10:11] <mato>  ld: fatal: Symbol referencing errors. No output written to .libs/local_lat
| [Saturday 10 April 2010] [11:10:16] <mato>  wtf
| [Saturday 10 April 2010] [11:11:20] <mato>  mikko: cool
| [Saturday 10 April 2010] [11:11:48] <mato>  mikko: maybe, i'd need to check with adrian
| [Saturday 10 April 2010] [11:12:05]      * sustrik nods in accord
| [Saturday 10 April 2010] [11:12:43] <sustrik>   i would guess the equality operator on string class should be in libstdc++
| [Saturday 10 April 2010] [11:16:00] <mato>  grrr
| [Saturday 10 April 2010] [11:16:11] <mato>  I don't know
| [Saturday 10 April 2010] [11:16:17] <mato>  that is, it should
| [Saturday 10 April 2010] [11:16:27] <mato>  and libzmq.so does pull in the relevant Sun C++ libraries
| [Saturday 10 April 2010] [11:16:35] <mato>  but it doesn't work when linking the perf tests
| [Saturday 10 April 2010] [11:16:55] <mato>  enough for today, I'll look at it again tomorrow
| [Saturday 10 April 2010] [11:21:36] <mikko> pull request sent
| [Saturday 10 April 2010] [11:21:43] <mikko> i think im gonna play for a minute 
| [Saturday 10 April 2010] [11:21:44] <mikko> bbl
| [Saturday 10 April 2010] [11:26:02] <mato>  i'm off into town
| [Saturday 10 April 2010] [11:26:02] <mato>  bbl
| [Saturday 10 April 2010] [11:32:15] <sustrik>   cyl
| [Sunday 11 April 2010] [01:59:12] <CIA-5>   zeromq2: 03Martin Sustrik 07master * r6fea422 10/ include/zmq.hpp : getsockopt added to c++ binding - http://bit.ly/aWN1od
| [Sunday 11 April 2010] [04:08:32] <mikko>   sustrik: pretty early commit, huh
| [Sunday 11 April 2010] [04:08:50] <mikko>   (assuming you are somewhat close to GMT)
| [Sunday 11 April 2010] [04:08:58] <sustrik> GMT+1
| [Sunday 11 April 2010] [04:09:08] <sustrik> what about you?
| [Sunday 11 April 2010] [04:09:46] <mikko>   GMT + 1 at the moment i think
| [Sunday 11 April 2010] [04:09:52] <mikko>   british summer time
| [Sunday 11 April 2010] [04:09:56] <mikko>   (london)
| [Sunday 11 April 2010] [04:10:35] <sustrik> ah, GMT+2 here then (CET summer time)
| [Sunday 11 April 2010] [04:10:49] <mikko>   is imatix a belgian company?
| [Sunday 11 April 2010] [04:11:02] <mikko>   at least the contact details seem to point to belgium
| [Sunday 11 April 2010] [04:11:18] <sustrik> imatix is belgain, but i am independent, just managing the project
| [Sunday 11 April 2010] [04:11:29] <sustrik> i'm based in bratislava, slovakia
| [Sunday 11 April 2010] [04:12:21] <sustrik> btw, i'll have to go to london next week or so, so we can have a beer
| [Sunday 11 April 2010] [04:12:36] <mikko>   sure, just let me know when and where
| [Sunday 11 April 2010] [04:12:40] <sustrik> ack
| [Sunday 11 April 2010] [04:12:56] <mikko>   i visited bratislava in 2006
| [Sunday 11 April 2010] [04:13:12] <sustrik> haven't changed much since :)
| [Sunday 11 April 2010] [04:13:13] <mikko>   after football world cup
| [Sunday 11 April 2010] [04:13:17] <mikko>   a lot of road works
| [Sunday 11 April 2010] [04:13:23] <sustrik> still the same
| [Sunday 11 April 2010] [04:13:29] <mikko>   seems like the whole city was being rebuilt
| [Sunday 11 April 2010] [04:13:54] <sustrik> that's how cities look in balkans
| [Sunday 11 April 2010] [04:14:01] <sustrik> like they are rebuilt all the time
| [Sunday 11 April 2010] [04:14:10] <sustrik> bratislava is a bit on edge of the area
| [Sunday 11 April 2010] [04:14:15] <sustrik> but the impression is the same
| [Sunday 11 April 2010] [04:15:06] <sustrik> btw, how does the php api look like?
| [Sunday 11 April 2010] [04:15:31] <sustrik> i think i've noticed you are using 'zeromq' prefix
| [Sunday 11 April 2010] [04:15:36] <mikko>   i tagged 0.1.0 beta
| [Sunday 11 April 2010] [04:15:43] <sustrik> yep, seen that
| [Sunday 11 April 2010] [04:16:20] <sustrik> some time ago we've tried to write a guidelines for APIs so that all the language bindings look more or less the same
| [Sunday 11 April 2010] [04:16:22] <mikko>   yep, class name in php can't start with a number
| [Sunday 11 April 2010] [04:16:25] <sustrik> have tou seen that?
| [Sunday 11 April 2010] [04:16:32] <mikko>   no, missed that 
| [Sunday 11 April 2010] [04:16:36] <sustrik> wait a sec
| [Sunday 11 April 2010] [04:16:42] <mikko>   it's an easy change if needed
| [Sunday 11 April 2010] [04:16:59] <sustrik> http://www.zeromq.org/guidelines:bindings
| [Sunday 11 April 2010] [04:17:07] <sustrik> it's entirely up to you
| [Sunday 11 April 2010] [04:17:25] <sustrik> but following the guidelines is meant to ease the transition between different languages
| [Sunday 11 April 2010] [04:17:42] <sustrik> as well as to make communication between developers in different languages easier
| [Sunday 11 April 2010] [04:18:00] <mikko>   Preferred name of the object/namespace/prefix is "zmq"
| [Sunday 11 April 2010] [04:18:06] <sustrik> yes
| [Sunday 11 April 2010] [04:18:08] <mikko>   let me change that 
| [Sunday 11 April 2010] [04:26:57] <CIA-5>   zeromq2: 03Martin Sustrik 07master * r00cf3ce 10/ (include/zmq.h src/socket_base.cpp src/socket_base.hpp): multi-part message functionality available via ZMQ_SNDMORE and ZMQ_RCVMORE - http://bit.ly/aKIAhA
| [Sunday 11 April 2010] [04:40:00] <mikko>   i renamed the extension from 'zeromq' to 'zmq' as well
| [Sunday 11 April 2010] [04:40:11] <mikko>   Search -> Replace All
| [Sunday 11 April 2010] [04:40:14] <mikko>   :)
| [Sunday 11 April 2010] [04:40:20] <sustrik> mikko: great, thanks
| [Sunday 11 April 2010] [04:51:57] <mikko>   repo renamed, links updated, docs update
| [Sunday 11 April 2010] [04:52:02] <mikko>   i think it's almost done
| [Sunday 11 April 2010] [04:58:00] <sustrik> mikko: you've already done the poll part, right?
| [Sunday 11 April 2010] [04:58:33] <mikko>   yep
| [Sunday 11 April 2010] [04:58:36] <sustrik> as you've seen in the guidelines there's no standard for polling API at the moment
| [Sunday 11 April 2010] [04:58:48] <sustrik> on the mailing list there's a thread called "polling API"
| [Sunday 11 April 2010] [04:59:09] <sustrik> i would be gread if you can comment on what the API looks like in PHP
| [Sunday 11 April 2010] [04:59:47] <sustrik> the ultimate goal is to get some common understanding how polling interface should look like to be acceptable for all languages
| [Sunday 11 April 2010] [05:00:59] <mikko>   i modelled the polling interface after existing "select" api in php
| [Sunday 11 April 2010] [05:01:10] <mikko>   so it would be somewhat familiar for the developer already
| [Sunday 11 April 2010] [05:01:21] <mikko>   i'll take a look
| [Sunday 11 April 2010] [05:01:31] <sustrik> thx
| [Sunday 11 April 2010] [05:02:59] <mikko>   hm, i actually hid away the context from the developer
| [Sunday 11 April 2010] [05:03:11] <mikko>   due to the complexicity of persistent resources in php
| [Sunday 11 April 2010] [05:03:42] <mikko>   inside one process i create one context per combination of options which is persisted based on configuration setting which can be set by administrator
| [Sunday 11 April 2010] [05:03:59] <mikko>   that way in shared hosting scenario the admins can disable persistence altogether
| [Sunday 11 April 2010] [05:12:14] <mikko>   is there any reason why you didn't use existing event loop libraries for polling?
| [Sunday 11 April 2010] [05:12:17] <mikko>   such as libev
| [Sunday 11 April 2010] [05:15:19] <sustrik> mikko: how would you do that?
| [Sunday 11 April 2010] [05:15:27] <sustrik> 0mq socket is not a file descriptor
| [Sunday 11 April 2010] [05:16:11] <sustrik> as for the context, it's intent is to separate different applications running in the same process
| [Sunday 11 April 2010] [05:16:42] <sustrik> if PHP doesn't allow that kind of thing, there's no point in having context object exposed
| [Sunday 11 April 2010] [05:17:16] <mikko>   i don't think for 99.9% of phps usecases context object is not needed
| [Sunday 11 April 2010] [05:17:46] <mikko>   as sharing context inside a php script should be advantage rather than harmful
| [Sunday 11 April 2010] [05:18:01] <mikko>   if there are other extensions that use zeromq they would have their own context
| [Sunday 11 April 2010] [05:18:09] <sustrik> it was originally designed for C
| [Sunday 11 April 2010] [05:18:15] <mikko>   usually i tend to try to design with simplicity in mind for php :)
| [Sunday 11 April 2010] [05:18:24] <sustrik> the use case was that if there are 2 libraries, each using 0MQ
| [Sunday 11 April 2010] [05:18:30] <mikko>   yeah, in C it makes a lot of sense
| [Sunday 11 April 2010] [05:18:33] <sustrik> you can link them to the same process
| [Sunday 11 April 2010] [05:18:42] <sustrik> without them misiteracting
| [Sunday 11 April 2010] [05:19:15] <sustrik> exactly, if a misinteraction probelm cannot happen in PHP there's no point in having context
| [Sunday 11 April 2010] [05:20:25] <mikko>   hmm, how does the polling work in 0mq at the moment?
| [Sunday 11 April 2010] [05:20:45] <mikko>   i would've thought that it checks for io at some point
| [Sunday 11 April 2010] [05:20:59] <sustrik> I/O is done in I/O threads
| [Sunday 11 April 2010] [05:21:20] <sustrik> what you are checking in zmq_poll is whether there are messages queued by I/O threads
| [Sunday 11 April 2010] [05:21:27] <sustrik> destined for application threads
| [Sunday 11 April 2010] [05:21:49] <sustrik> it's done via a lock-free polling object
| [Sunday 11 April 2010] [05:21:55] <sustrik> ypollset.hpp
| [Sunday 11 April 2010] [05:21:57] <sustrik> iirc
| [Sunday 11 April 2010] [05:22:35] <sustrik> but the real point is that there's no way to simulate an fd in user space
| [Sunday 11 April 2010] [05:22:45] <sustrik> so you can either go kernel
| [Sunday 11 April 2010] [05:22:51] <sustrik> thus loosing portability
| [Sunday 11 April 2010] [05:23:16] <sustrik> or you sacrifice fd's
| [Sunday 11 April 2010] [05:24:09] <sustrik> the latter means that system polling mechanism - such as select of poll - cannot be used with your implementation
| [Sunday 11 April 2010] [05:24:09] <sustrik> :(
| [Sunday 11 April 2010] [05:24:19] <mikko>   now i get it
| [Sunday 11 April 2010] [05:24:29] <mikko>   i've only used event loops in very simple scenarios
| [Sunday 11 April 2010] [05:24:37] <mikko>   such as websocket daemon etc
| [Sunday 11 April 2010] [05:24:49] <mikko>   where there is a writable/readable fd
| [Sunday 11 April 2010] [05:24:57] <sustrik> ack
| [Sunday 11 April 2010] [05:25:17] <sustrik> when /me is rich and powerful, i'll loby for adding user-space fds to POSIX
| [Sunday 11 April 2010] [05:27:19] <mikko>   http://pod.tst.eu/http://cvs.schmorp.de/libev/ev.pod#code_ev_prepare_code_and_code_ev_che
| [Sunday 11 April 2010] [05:27:37] <mikko>   "Their main purpose is to integrate other event mechanisms into libev and their use is somewhat advanced. They could be used, for example, to track variable changes, implement your own watchers, integrate net-snmp or a coroutine library and lots more."
| [Sunday 11 April 2010] [05:28:07] <mikko>   that might be fd based as well
| [Sunday 11 April 2010] [05:29:52] <sustrik> not sure
| [Sunday 11 April 2010] [05:30:06] <sustrik> maybe its just a way to to say "use zmq_poll instead of poll"
| [Sunday 11 April 2010] [05:30:25] <sustrik> and 0mq sockets instead of fds
| [Sunday 11 April 2010] [05:31:49] <sustrik> hm, looking at the example, it's probably fd-based
| [Sunday 11 April 2010] [05:32:51] <mikko>   "The drawback with this solution is that the main loop is now no longer controllable by EV. The Glib::EV  module uses this approach, effectively embedding EV as a client into the horrible libglib event loop."
| [Sunday 11 April 2010] [05:33:01] <mikko>   the author does not seem to be the most polite person
| [Sunday 11 April 2010] [05:34:02] <sustrik> :)
| [Sunday 11 April 2010] [05:34:24] <sustrik> but that seems to imply you can actually merge it with 0mq
| [Sunday 11 April 2010] [05:35:04] <sustrik> i am not sure i understand it correctly
| [Sunday 11 April 2010] [05:35:21] <sustrik> but does it mean you can delegate the actuall polling to zmq_poll
| [Sunday 11 April 2010] [05:35:31] <sustrik> ?
| [Sunday 11 April 2010] [05:35:35] <mikko>   i think event_poll_func is a callback for Glib::EV
| [Sunday 11 April 2010] [05:35:42] <mikko>   yes, seems like that
| [Sunday 11 April 2010] [05:36:39] <sustrik> ok, if someone appears with a need for libev integration, let's point him this way
| [Sunday 11 April 2010] [07:21:58] <mikko>   sustrik: is the maximum size for ZMQ_IDENTITY exposed somehow?
| [Sunday 11 April 2010] [07:24:21] <sustrik> it's 255
| [Sunday 11 April 2010] [07:24:30] <sustrik> you mean like a constant or so?
| [Sunday 11 April 2010] [07:25:04] <mikko>   i mean is that subject to change?
| [Sunday 11 April 2010] [07:25:15] <sustrik> no, it's not
| [Sunday 11 April 2010] [07:25:22] <sustrik> 255 characters should be enough
| [Sunday 11 April 2010] [07:33:25] <sustrik> mikko: do you expect longer identites?
| [Sunday 11 April 2010] [07:33:59] <mikko>   no, just that if i hardcore the value and it changes in the future
| [Sunday 11 April 2010] [07:33:59] <sustrik> strictly speaking, there's no real technological reason to limit the size of identity
| [Sunday 11 April 2010] [07:34:12] <sustrik> in theory it can be made unbound
| [Sunday 11 April 2010] [07:34:24]    * sustrik is thinking
| [Sunday 11 April 2010] [07:35:13] <sustrik> having identities longer than 255 characters is not a good idea
| [Sunday 11 April 2010] [07:35:29] <sustrik> but why limit those that want to do this kind of ugly stuff?
| [Sunday 11 April 2010] [07:36:01] <mikko>   retrieving is easier if its limited
| [Sunday 11 April 2010] [07:36:14] <sustrik> true
| [Sunday 11 April 2010] [07:36:32] <sustrik> a different question: should the identity even be retrievable?
| [Sunday 11 April 2010] [07:36:41] <sustrik> what is it good for?
| [Sunday 11 April 2010] [07:37:34] <mikko>   well, in case of php you might instantiate the object and then use it a few requests later
| [Sunday 11 April 2010] [07:37:50] <mikko>   effectively the socket is persisted and then tied to a new php object later
| [Sunday 11 April 2010] [07:38:02] <sustrik> right, but why would you want to retrieve the identity?
| [Sunday 11 April 2010] [07:38:14] <mikko>   you mean instead of resetting it each time?
| [Sunday 11 April 2010] [07:38:56]    * sustrik is not following
| [Sunday 11 April 2010] [07:39:19] <sustrik> the question is what's the scenario where you need getsockopt (ZMQ_IDENTITY)?
| [Sunday 11 April 2010] [07:40:45] <mikko>   let's a say you got a following php script: <?php $object = new ZMQ(ZMQ::SOCKET_REP, 'mysock1'); ?>
| [Sunday 11 April 2010] [07:40:59] <mikko>   the socket structure is stored internally over multiple executions of this script
| [Sunday 11 April 2010] [07:41:04] <mikko>   to get persistent connections
| [Sunday 11 April 2010] [07:41:14] <mikko>   now, let's say you have an identity 
| [Sunday 11 April 2010] [07:41:48] <mikko>   the script becomes <?php $object = new ZMQ(ZMQ::SOCKET_REP, 'mysock1'); $object->setSockOpt(ZMQ::SOCKOPT_IDENTITY, 'my best socket'); ?>
| [Sunday 11 April 2010] [07:42:14] <mikko>   so on each execution of this script (page load) you would reset the identity
| [Sunday 11 April 2010] [07:42:19] <mikko>   i dont know if that makes any difference
| [Sunday 11 April 2010] [07:43:00] <mikko>   if you can retrieve it you could do <?php $object = new ZMQ(ZMQ::SOCKET_REP, 'mysock1'); if ($object->getSockOpt(ZMQ::SOCKOPT_IDENTITY) != 'my best socket') { $object->setSockOpt(ZMQ::SOCKOPT_IDENTITY, 'my best socket'); }
| [Sunday 11 April 2010] [07:43:30] <sustrik> the identity is meant to stay the same
| [Sunday 11 April 2010] [07:43:35] <sustrik> so you open socket
| [Sunday 11 April 2010] [07:43:41] <sustrik> set the identity
| [Sunday 11 April 2010] [07:43:45] <sustrik> and that's it
| [Sunday 11 April 2010] [07:43:53] <sustrik> you don't need to touch it anymore
| [Sunday 11 April 2010] [07:44:06] <mikko>   indeed, but in phps case if you can't retrieve the identity you can not know if it's set already
| [Sunday 11 April 2010] [07:44:30] <mikko>   as the socket is persisted over multiple requests but the PHP object is recreated each time
| [Sunday 11 April 2010] [07:45:04] <sustrik> true, but still, setting it each time doesn't really matter
| [Sunday 11 April 2010] [07:45:18] <sustrik> except as performance problem
| [Sunday 11 April 2010] [07:45:54] <sustrik> but i would suspect there are much more perf problems in PHP itself and setting a single string shouldn't really matter
| [Sunday 11 April 2010] [07:46:51] <mikko>   well, in C you might have a large array sockets and each one have identity set at different stages
| [Sunday 11 April 2010] [07:47:30] <sustrik> yes, that's the only use case i can think of
| [Sunday 11 April 2010] [07:49:10] <mikko>   i would think it makes no harm to limit/allow retrieving
| [Sunday 11 April 2010] [07:49:23] <mikko>   if someone needs longer identities let's cross that bridge when we get there
| [Sunday 11 April 2010] [07:49:47] <sustrik> ok, good
| [Sunday 11 April 2010] [07:49:56] <sustrik> let it stay as it is now
| [Sunday 11 April 2010] [08:00:46] <CIA-5>   zeromq2: 03Martin Sustrik 07master * r6cf0765 10/ include/zmq.h : C-style comments in zmq.h - http://bit.ly/dw16x4
| [Sunday 11 April 2010] [08:09:29] <mikko>   mmm
| [Sunday 11 April 2010] [08:09:34] <mikko>   protein bars taste horrible
| [Sunday 11 April 2010] [08:14:16] <mikko>   hmm
| [Sunday 11 April 2010] [08:14:24] <mikko>   one thing i was wondering that might be useful
| [Sunday 11 April 2010] [08:14:37] <mikko>   have the libzmq version exposed as constant as well
| [Sunday 11 April 2010] [08:14:49] <mikko>   that would show which version people compiled against vs runtime version
| [Sunday 11 April 2010] [08:18:02] <sustrik> yeah, it would be useful, but the version numbers are generated from configure.in
| [Sunday 11 April 2010] [08:18:10] <sustrik> try asking about it on the mailing list
| [Sunday 11 April 2010] [08:18:30] <sustrik> people who understand how the build system works may have an opinion
| [Sunday 11 April 2010] [08:20:09] <CIA-5>   zeromq2: 03Martin Sustrik 07master * rdff79d7 10/ builds/msvc/platform.hpp : version number bumped to 2.0.7 for MSVC build - http://bit.ly/b2cKvx
| [Sunday 11 April 2010] [09:45:29] <sustrik> people who understand how the build system works may have an opinion
| [Sunday 11 April 2010] [10:36:36] <CIA-5>   zeromq2: 03Martin Sustrik 07master * rfba28c7 10/ (6 files in 2 dirs): issue 1 - Change zmq_term semantics - http://bit.ly/c7n0NQ
| [Sunday 11 April 2010] [10:55:09] <mikko>   reply-to "&#216;MQ development list" <zeromq-dev@lists.zeromq.org>
| [Sunday 11 April 2010] [10:55:12] <mikko>   odd
| [Sunday 11 April 2010] [10:59:06] <sustrik> it've been discussed on the mailing list
| [Sunday 11 April 2010] [10:59:14] <sustrik> i have no opinion on it
| [Sunday 11 April 2010] [10:59:21] <sustrik> feel free to complain
| [Sunday 11 April 2010] [10:59:27] <mikko>   sorry?
| [Sunday 11 April 2010] [10:59:35] <sustrik> the reply-to thing
| [Sunday 11 April 2010] [10:59:38] <mikko>   ah
| [Sunday 11 April 2010] [10:59:39] <mikko>   :)
| [Sunday 11 April 2010] [10:59:49] <mikko>   im just wondering why it goes like that
| [Sunday 11 April 2010] [11:00:07] <mikko>   noticed your post of zmq_term semantics and trying to formulate my idea into an email
| [Sunday 11 April 2010] [11:00:25] <sustrik> because people are used to hit reply button instead of reply to all
| [Sunday 11 April 2010] [11:00:52] <sustrik> thus the conversations tend to disappear from public view
| [Sunday 11 April 2010] [11:06:10] <sustrik> ah, you meant the strange character?
| [Sunday 11 April 2010] [11:06:11] <sustrik> "&#216;
| [Sunday 11 April 2010] [11:06:22] <sustrik> I've just changes that to ordinary 0
| [Sunday 11 April 2010] [11:06:27] <sustrik> changed*
| [Sunday 11 April 2010] [11:08:20] <mikko>   yeah, i mean the strange character
| [Sunday 11 April 2010] [11:08:22] <mikko>   meant*
| [Sunday 11 April 2010] [11:08:39] <sustrik> fixed!
| [Sunday 11 April 2010] [11:17:15] <mikko>   my first mail to list sent
| [Sunday 11 April 2010] [11:18:11] <sustrik> :)
| [Sunday 11 April 2010] [11:18:15] <sustrik> let me reply
| [Sunday 11 April 2010] [12:01:17] <mikko>   im gonna hit the gym
| [Sunday 11 April 2010] [12:01:18] <mikko>   bbl
| [Sunday 11 April 2010] [14:47:01] <mikko>   back
| [Monday 12 April 2010] [03:25:14] <CIA-5>   zeromq2: 03Martin Sustrik 07master * r3236cb1 10/ (7 files): ETERM is accounted for in the documentation - http://bit.ly/9KxYaI
| [Monday 12 April 2010] [03:57:45] <CIA-5>   zeromq2: 03Martin Sustrik 07master * r7668e79 10/ (doc/zmq_socket.txt src/zmq.cpp): zmq_poll returns ETERM in case of context termination - http://bit.ly/br7liv
| [Monday 12 April 2010] [04:05:39] <CIA-5>   zeromq2: 03Martin Sustrik 07master * r3496476 10/ (4 files in 4 dirs): MSVC perf build fixed - http://bit.ly/aF5lWU
| [Monday 12 April 2010] [04:43:08] <mikko>   good morning
| [Monday 12 April 2010] [05:11:05] <sustrik> morning
| [Monday 12 April 2010] [07:15:58] <olivier_c>   hello everybody
| [Monday 12 April 2010] [07:37:47] <sustrik> olivier_c: hi
| [Monday 12 April 2010] [07:42:25] <olivier_c>   sustrik, could you bring me some clarifications on assertion in pgm_socket.cpp line 130, please ? I've got an assertion fail (assert false) there, and i don't have any clue on what could have fail :/.
| [Monday 12 April 2010] [07:45:22] <sustrik> wait a sec
| [Monday 12 April 2010] [07:47:08] <sustrik> it's an unexpected result code from OpenPGM library
| [Monday 12 April 2010] [07:47:21] <sustrik> can you check what exact error are you getting?
| [Monday 12 April 2010] [07:47:35] <sustrik> (both domain and code)
| [Monday 12 April 2010] [07:49:41] <olivier_c_>  ok I'm going to have a look on it
| [Monday 12 April 2010] [07:49:55] <sustrik> thanks
| [Monday 12 April 2010] [08:24:52] <olivier_c>   so. i just get "Assertion failed: false (pgm_socket.cpp line 130). Aborted.  i'm just trying to connect a SUB socket to "epgm://eth0;224.0.0.1:5555". does it mean that pgm isn't supported ?
| [Monday 12 April 2010] [08:41:31] <sustrik> olivier_c: no, it means that OpenPGM returned unexpected error
| [Monday 12 April 2010] [08:41:39] <sustrik> can you run the app under gdb
| [Monday 12 April 2010] [08:41:46] <sustrik> and check what the actual error is:
| [Monday 12 April 2010] [08:42:03] <sustrik> pgm_error->domain
| [Monday 12 April 2010] [08:42:13] <sustrik> and
| [Monday 12 April 2010] [08:42:14] <sustrik> pgm_error->code
| [Monday 12 April 2010] [08:43:59] <olivier_c>   ah ok, sorry for misunderstanding.
| [Monday 12 April 2010] [08:49:09] <sustrik> np
| [Monday 12 April 2010] [08:56:14] <mato>    sustrik: _WIN32 is always defined on Win32, yes?
| [Monday 12 April 2010] [08:56:36] <mato>    sustrik: at the top of zmq.h we have:
| [Monday 12 April 2010] [08:56:41] <mato>    (...)
| [Monday 12 April 2010] [08:56:46] <mato>    #include <errno.h>
| [Monday 12 April 2010] [08:56:46] <mato>    #include <stddef.h>
| [Monday 12 April 2010] [08:56:46] <mato>    #if defined _WIN32
| [Monday 12 April 2010] [08:56:47] <mato>    #include "winsock2.h"
| [Monday 12 April 2010] [08:56:47] <mato>    #endif
| [Monday 12 April 2010] [08:56:48] <mato>    #if defined ZMQ_BUILDING_LIBZMQ_WITH_MSVC
| [Monday 12 April 2010] [08:56:51] <mato>    #define ZMQ_EXPORT __declspec(dllexport)
| [Monday 12 April 2010] [08:56:53] <mato>    #elif defined _MSC_VER
| [Monday 12 April 2010] [08:56:56] <mato>    #define ZMQ_EXPORT __declspec(dllimport)
| [Monday 12 April 2010] [08:56:58] <mato>    #else
| [Monday 12 April 2010] [08:57:01] <mato>    #define ZMQ_EXPORT
| [Monday 12 April 2010] [08:57:03] <mato>    #endif
| [Monday 12 April 2010] [08:57:06] <mato>    (...)
| [Monday 12 April 2010] [08:58:47] <sustrik> at least with MSVC
| [Monday 12 April 2010] [08:58:54] <sustrik> not sure how gcc handles this
| [Monday 12 April 2010] [08:59:35] <mato>    ok and that BUILDING_LIBZMQ_WITH_MSVC is something you define in your project file, right?
| [Monday 12 April 2010] [08:59:42] <sustrik> right
| [Monday 12 April 2010] [08:59:50] <mato>    for libzmq only, and not for e.g. the perf tests or devices
| [Monday 12 April 2010] [08:59:51] <mato>    right?
| [Monday 12 April 2010] [08:59:57] <sustrik> right
| [Monday 12 April 2010] [09:00:09] <sustrik> and it's not relevant to anyting except msvc
| [Monday 12 April 2010] [09:00:17] <mato>    no, it's relevant to win32 in general
| [Monday 12 April 2010] [09:00:23] <sustrik> ?
| [Monday 12 April 2010] [09:00:29] <mato>    MinGW also supports the __declspec(dll...) stuff
| [Monday 12 April 2010] [09:00:36] <sustrik> whoa
| [Monday 12 April 2010] [09:00:38] <mato>    at least it seems that way
| [Monday 12 April 2010] [09:00:43]    * sustrik haven't know that
| [Monday 12 April 2010] [09:00:57] <mato>    well it certainly doesn't complain
| [Monday 12 April 2010] [09:01:03] <sustrik> ok then
| [Monday 12 April 2010] [09:01:07] <mato>    so I'm thinking that the above if's should be changed
| [Monday 12 April 2010] [09:01:18] <sustrik> maybe a more sound name should be used then?
| [Monday 12 April 2010] [09:01:31] <mato>    1. ZMQ_BUILDING... becomes something like LIBZMQ_DLL ?
| [Monday 12 April 2010] [09:01:49] <mato>    2. that can probably become #elif defined _WIN32, but I'm going to check
| [Monday 12 April 2010] [09:02:14] <sustrik> ZMQ_BUILD_IN_PROGRESS
| [Monday 12 April 2010] [09:02:25] <mato>    no, it's only to do with a win32 dll
| [Monday 12 April 2010] [09:02:25] <sustrik> that  can be defined for all platforms
| [Monday 12 April 2010] [09:02:32] <mato>    ah
| [Monday 12 April 2010] [09:02:42] <sustrik> but then we'll need _WIN32
| [Monday 12 April 2010] [09:02:47] <mato>    that's no problem
| [Monday 12 April 2010] [09:05:21] <mato>    i'll do something experimental on a branch, no hurry for this to go into git proper right now
| [Monday 12 April 2010] [09:06:21] <sustrik> ok
| [Monday 12 April 2010] [09:19:43] <lvh> Hello
| [Monday 12 April 2010] [09:19:52] <lvh> Anyone know where the zmq_server binary is in debian?
| [Monday 12 April 2010] [09:21:06] <mato>    lvh: there is no zmq_server binary :-)
| [Monday 12 April 2010] [09:21:34] <mato>    lvh: in any case the device binaries are in zeromq-bin
| [Monday 12 April 2010] [09:22:27] <lvh> So why does www.zeromq.org/code:examples-chat#toc15 tell me to run it? :-(
| [Monday 12 April 2010] [09:23:16] <mato>    that's old 1.x material
| [Monday 12 April 2010] [09:23:35] <mato>    sorry, it really needs to be removed :(
| [Monday 12 April 2010] [09:23:42] <mato>    and/or updated
| [Monday 12 April 2010] [09:24:20] <lvh> Aha, I see.
| [Monday 12 April 2010] [09:24:26] <lvh> I'm trying to use pyzmq
| [Monday 12 April 2010] [09:24:32] <lvh> I'm not sure if that's 1.x material
| [Monday 12 April 2010] [09:24:34] <mato>    see the Cookbook for up to date examples
| [Monday 12 April 2010] [09:24:43] <mato>    no, pyzmq is definitely 2.x
| [Monday 12 April 2010] [09:24:48] <lvh> okay :-)
| [Monday 12 April 2010] [09:24:50] <mato>    how did you get to the old chat example?
| [Monday 12 April 2010] [09:24:58] <mato>    anyway, you want to look here: http://www.zeromq.org/docs:cookbook
| [Monday 12 April 2010] [09:25:13] <mato>    and also on the pyzmq page itself
| [Monday 12 April 2010] [09:25:16] <mato>    http://www.zeromq.org/bindings:python
| [Monday 12 April 2010] [09:25:17] <lvh> errrrrr
| [Monday 12 April 2010] [09:26:11] <lvh> I'm not sure.
| [Monday 12 April 2010] [09:27:50] <lvh> I'm trying to get the python chat example to work with no dice
| [Monday 12 April 2010] [09:28:05] <lvh> An address like tcp://localhost:5555 is fine, right?
| [Monday 12 April 2010] [09:29:14] <lvh> Oh, I figured out how I got to that page.
| [Monday 12 April 2010] [09:29:17] <lvh> Google indexes it.
| [Monday 12 April 2010] [09:29:49] <mato>    localhost:5555 will work for connecting to localhost
| [Monday 12 April 2010] [09:30:06] <mato>    use (interface):5555 when binding, or just use IP addresses
| [Monday 12 April 2010] [09:30:14] <mato>    zee the zmq_connect() and zmq_bind() reference
| [Monday 12 April 2010] [09:30:18] <lvh> right
| [Monday 12 April 2010] [09:30:34] <lvh> the display.py script just blocks and doesnt react to signals other than SIGKILL
| [Monday 12 April 2010] [09:30:50] <mato>    read the FAQ :-)
| [Monday 12 April 2010] [09:31:21] <lvh> Just localhost:5555 gets me zmq._zmq.ZMQError: Invalid argument
| [Monday 12 April 2010] [09:31:21] <lvh>  
| [Monday 12 April 2010] [09:31:41] <mato>    I meant tcp://... of course.
| [Monday 12 April 2010] [09:31:52] <lvh> Aha :-)
| [Monday 12 April 2010] [09:33:22] <lvh> paste.pocoo.org/show/200839/
| [Monday 12 April 2010] [09:34:18] <mato>    I'm sorry, I can't help you right now. Not sure who wrote the python examples, maybe sustrik.
| [Monday 12 April 2010] [09:34:39] <lvh> ellisonbg
| [Monday 12 April 2010] [09:35:14] <mato>    Suggest you ask on the mailing list or wait for Brian to show up here (nick: bgranger).
| [Monday 12 April 2010] [09:35:33] <lvh> http://www.zeromq.org/code:pyzmq
| [Monday 12 April 2010] [09:35:40] <lvh> this appears to be something completely different too
| [Monday 12 April 2010] [09:35:45] <lvh> it has a ZMQ object in the zmq modul
| [Monday 12 April 2010] [09:35:49] <lvh> mine doesn't have that
| [Monday 12 April 2010] [09:36:12] <lvh> and the module's called "pyzmq" instead of just "zmq"
| [Monday 12 April 2010] [09:36:13] <mato>    that'll be 1.x also
| [Monday 12 April 2010] [09:36:23] <lvh> (but the thing on github *is* called pyzmq, yay)
| [Monday 12 April 2010] [09:36:27] <mato>    sustrik: We need to kill the 1.x stuff from the site.
| [Monday 12 April 2010] [09:37:20] <lvh> sustrik: (even the stuff that doesn't have internal links: google got me there)
| [Monday 12 April 2010] [09:39:47] <sustrik> lvh: the paste is a pyzmq problem
| [Monday 12 April 2010] [09:39:58] <sustrik> it's brian's pyzmq
| [Monday 12 April 2010] [09:40:03] <sustrik> not the old 1.0 pyzmq
| [Monday 12 April 2010] [09:40:21] <sustrik> mato: yes, i think it's time to ditch 1.0 stuff
| [Monday 12 April 2010] [09:40:41] <sustrik> i've kept it there so that people still using 1.0 have reference
| [Monday 12 April 2010] [09:40:52] <sustrik> but they had enough time to migrate by now
| [Monday 12 April 2010] [09:41:23] <lvh> sustrik: so these are the bindings I should be using, but I've found a bug?
| [Monday 12 April 2010] [09:41:40] <sustrik> yes, it looks like that
| [Monday 12 April 2010] [09:41:59] <sustrik> i would try filling an error report with pyzmq project
| [Monday 12 April 2010] [09:42:27] <lvh> will do :-)
| [Monday 12 April 2010] [09:42:42] <sustrik> lvh: wait a sec
| [Monday 12 April 2010] [09:42:52] <sustrik> where does the chat example come from
| [Monday 12 April 2010] [09:42:53] <sustrik> ?
| [Monday 12 April 2010] [09:43:46] <sustrik> aha, looks like brian's project
| [Monday 12 April 2010] [09:44:00] <sustrik> so yes, please report it with pyzmq
| [Monday 12 April 2010] [09:45:08] <sustrik> lvh: i am not a python programmer, but what about this:
| [Monday 12 April 2010] [09:45:09] <sustrik> msg = raw_input("%s> " % who)
| [Monday 12 April 2010] [09:45:09] <sustrik> EOFError
| [Monday 12 April 2010] [09:45:13] <sustrik> ?
| [Monday 12 April 2010] [09:45:23] <lvh> oh that just means it was waiting for imput and I mashed C-d
| [Monday 12 April 2010] [09:45:32] <lvh> input, even
| [Monday 12 April 2010] [09:45:51] <lvh> not a bug, expected behavior :-)
| [Monday 12 April 2010] [09:45:56] <sustrik> :)
| [Monday 12 April 2010] [09:47:12] <lvh> the test suite doesn't work because there's no pgm support, apparently
| [Monday 12 April 2010] [09:47:28] <lvh> somewhat weird that multicast doesn't work -- does that need userspace libs, or something?
| [Monday 12 April 2010] [09:47:55] <lvh> apt-cache search multicast lib dev doesn't yield any likely candidates
| [Monday 12 April 2010] [09:48:23] <sustrik> lvh: does it work with tcp?
| [Monday 12 April 2010] [09:48:58] <lvh> sustrik: Nope, that pasted example was tcp
| [Monday 12 April 2010] [09:49:01] <lvh> I'm trying to run the test suite
| [Monday 12 April 2010] [09:49:15] <lvh> which fails (more quitely than I'd have liked it to), because pgm doesn't work
| [Monday 12 April 2010] [09:49:52] <sustrik> lvh: this one: paste.pocoo.org/show/200839/ ?
| [Monday 12 April 2010] [09:50:05] <sustrik> the error is caused by Ctrl+C, no?
| [Monday 12 April 2010] [09:50:17] <lvh> right, but i was expecting display.py to display that message i did send
| [Monday 12 April 2010] [09:50:28] <sustrik> have you run zmq_forwarder?
| [Monday 12 April 2010] [09:50:39] <lvh> I didn't know I was supposed to, so no
| [Monday 12 April 2010] [09:50:44] <sustrik> read README
| [Monday 12 April 2010] [09:50:53] <sustrik> aha
| [Monday 12 April 2010] [09:51:02] <sustrik> no README in the directory
| [Monday 12 April 2010] [09:51:04] <lvh> which one
| [Monday 12 April 2010] [09:51:05] <lvh> :D
| [Monday 12 April 2010] [09:51:11] <sustrik> you should complain to Brian
| [Monday 12 April 2010] [09:51:22] <sustrik> anyway, the C chat example is exactly the same
| [Monday 12 April 2010] [09:51:29] <sustrik> and there's README
| [Monday 12 April 2010] [09:51:33] <sustrik> wait a sec
| [Monday 12 April 2010] [09:51:36] <lvh> i should open a ticket, branch, fix it, deploy patch
| [Monday 12 April 2010] [09:51:39] <lvh> there's README.rst
| [Monday 12 April 2010] [09:51:42] <lvh> that describes building
| [Monday 12 April 2010] [09:51:55] <sustrik> http://github.com/sustrik/zeromq-chat/blob/master/README
| [Monday 12 April 2010] [09:53:17] <lvh> so if you wanted people to be able log in and have everything published to them automatically, you'd use PUBSUB mode?
| [Monday 12 April 2010] [09:53:22] <lvh> eg "like IRC"
| [Monday 12 April 2010] [09:54:10] <lvh> I'm building zmq2 manually now, I think pyzmq was building against my system installed libzeromq-dev files and that might be why it was breaking
| [Monday 12 April 2010] [10:00:54] <sustrik> lvh: yes, PUB/SUB
| [Monday 12 April 2010] [10:01:11] <sustrik> what system-insalled libzeromq-dev?
| [Monday 12 April 2010] [10:01:20] <lvh> library_dirs = /home/lvh/dev/zeromq2/lib
| [Monday 12 April 2010] [10:01:20] <lvh> include_dirs = /home/lvh/dev/zeromq2/include
| [Monday 12 April 2010] [10:01:20] <lvh>  
| [Monday 12 April 2010] [10:01:43] <lvh> Any idea what the library_dirs is supposed to be on git checkouts of zeromq2?
| [Monday 12 April 2010] [10:01:55] <lvh> libzmq-dev - Development files and static library for the ZeroMQ library
| [Monday 12 April 2010] [10:02:10] <lvh> 2.0.6beta.dfsg-2 (/var/lib/apt/lists/ftp.kulnet.kuleuven.ac.be_debian_dists_unstable_main_binary-amd64_Packages)
| [Monday 12 April 2010] [10:02:26] <sustrik> you've had that installed by default?
| [Monday 12 April 2010] [10:02:43] <sustrik> strange
| [Monday 12 April 2010] [10:03:06] <lvh> nope, I installed it myself when I started playing with zmq
| [Monday 12 April 2010] [10:03:27] <sustrik> ok
| [Monday 12 April 2010] [10:03:35] <lvh> it makes pyzmq compile, but not necessarily work (apparently)
| [Monday 12 April 2010] [10:03:54] <sustrik> the best thing you can do is to remove all of it
| [Monday 12 April 2010] [10:04:20] <lvh> just did. what am I supposed to use as lib dir? /usr/bin/ld: cannot find -lzmq
| [Monday 12 April 2010] [10:04:20] <sustrik> and build both 0mq and pyzmq from git
| [Monday 12 April 2010] [10:04:31] <lvh> sustrik: build, or build and install?
| [Monday 12 April 2010] [10:04:38] <lvh> I haven't installed 0mq, just built it
| [Monday 12 April 2010] [10:04:49] <sustrik> autotools by default use /usr/local as install directory
| [Monday 12 April 2010] [10:04:50] <lvh> ./autogen.sh && ./configure && make
| [Monday 12 April 2010] [10:05:18] <sustrik> where do you want to install it?
| [Monday 12 April 2010] [10:05:29] <lvh> /usr/local's fine, home dir's better
| [Monday 12 April 2010] [10:05:47] <lvh> ~/lib/
| [Monday 12 April 2010] [10:05:52] <lvh> That's where all my python stuff lives, at least
| [Monday 12 April 2010] [10:06:32] <sustrik> pretty unorthodox
| [Monday 12 April 2010] [10:06:48] <sustrik> rather do it this way:
| [Monday 12 April 2010] [10:06:51] <sustrik> ./autogen.sh
| [Monday 12 April 2010] [10:07:26] <sustrik> ./configure --prefix=/usr
| [Monday 12 April 2010] [10:07:29] <sustrik> make
| [Monday 12 April 2010] [10:07:33] <sustrik> sudo make install
| [Monday 12 April 2010] [10:07:50] <lvh> right, got that
| [Monday 12 April 2010] [10:08:00] <lvh> where does it install the headers?
| [Monday 12 April 2010] [10:08:15] <sustrik> /usr/include
| [Monday 12 April 2010] [10:08:16] <lvh> ah, /usr/local/include
| [Monday 12 April 2010] [10:08:45] <mato>    sustrik: installing to /usr is not a good idea unless you know the implications
| [Monday 12 April 2010] [10:09:04] <mato>    sustrik: that's what /usr/local is for, and most distributions have support for e.g. python/ruby/perl stuff in /usr/local also
| [Monday 12 April 2010] [10:09:04] <sustrik> ok, i am not an expert
| [Monday 12 April 2010] [10:09:20] <sustrik> ok, then use just ./configure
| [Monday 12 April 2010] [10:09:25] <lvh> mato: debian by default doesn't, apparently ;-)
| [Monday 12 April 2010] [10:09:27] <lvh> ImportError: libzmq.so.0: cannot open shared object file: No such file or directory
| [Monday 12 April 2010] [10:10:48] <lvh> similarly letting setuptools loose on something your distro occasionally uses is a terrible idea
| [Monday 12 April 2010] [10:10:55] <lvh> but setuptools in general is a terrible idea
| [Monday 12 April 2010] [10:11:01] <lvh> it's marginally worse than auto*hell
| [Monday 12 April 2010] [10:11:28] <mato>    lvh: so you have libzmq.so in /usr/local/lib and python can't find it?
| [Monday 12 April 2010] [10:11:36] <mato>    lvh: did you run ldconfig as root after doing make install?
| [Monday 12 April 2010] [10:11:53] <mikko>   is /usr/local/lib in ld.so.conf?
| [Monday 12 April 2010] [10:12:00] <lvh> woo, that works
| [Monday 12 April 2010] [10:12:04] <lvh> nope, forgot ldconfig
| [Monday 12 April 2010] [10:12:18] <lvh> Ran 13 tests in 9.303s, yay
| [Monday 12 April 2010] [10:12:23] <mato>    there you go :-)
| [Monday 12 April 2010] [10:12:45] <mato>    mikko: on debian at least, yes
| [Monday 12 April 2010] [10:14:26] <mikko>   i think RHEL leaves it out by default
| [Monday 12 April 2010] [10:14:39] <mikko>   seems to be in /etc/ld.so.conf.d/libc.conf for deb
| [Monday 12 April 2010] [10:14:39] <lvh> is there a magic zmq_thing I have to run before the pubsub example'll work?
| [Monday 12 April 2010] [10:14:53] <sustrik> zmq_forwarder
| [Monday 12 April 2010] [10:15:04] <lvh> I'm seeing zmq._zmq.ZMQError: No such device, afaik devices are things like zmq_*
| [Monday 12 April 2010] [10:16:47] <sustrik> http://github.com/sustrik/zeromq-chat/blob/master/README
| [Monday 12 April 2010] [10:17:01] <lvh> is the man page for that supposed to be empty?
| [Monday 12 April 2010] [10:19:15] <olivier_c>   fiou, sorry for the delay, so the error is AGAIN (pgm_error->code = 1 and pgm_error->domain = 8) and AGAIN isn't in the "if" line 115 of pgm_socket.cpp 
| [Monday 12 April 2010] [10:19:39] <olivier_c>   that's why i get  this assert
| [Monday 12 April 2010] [10:19:56] <lvh> oh, that reminds me. in a pubsub context, what happens if I publish to things that have no listeners (subscribers)? stuff gets silently dropped, right?
| [Monday 12 April 2010] [10:20:00] <lvh> if so that would be ideal for my use case
| [Monday 12 April 2010] [10:20:43] <sustrik> lvh: right
| [Monday 12 April 2010] [10:20:52] <sustrik> olivier_c: wait a sec, checking...
| [Monday 12 April 2010] [10:24:22] <sustrik> olivier_c: PGM_IF_ERROR_AGAIN?
| [Monday 12 April 2010] [10:24:29] <olivier_c>   yes
| [Monday 12 April 2010] [10:26:27] <sustrik> hm, pretty vague error
| [Monday 12 April 2010] [10:27:02] <lvh> ack, now it works
| [Monday 12 April 2010] [10:27:11] <sustrik> EAI_AGAIN
| [Monday 12 April 2010] [10:27:12] <sustrik>               The name server returned a temporary failure indication.  Try again later.
| [Monday 12 April 2010] [10:27:25] <sustrik> olivier_c: is your name server working?
| [Monday 12 April 2010] [10:29:24] <olivier_c>   hmmm good question . it need a check !
| [Monday 12 April 2010] [10:30:59] <sustrik> anyway, i would say bind shouldn't even try to access name server, probably an openPGM bug...
| [Monday 12 April 2010] [10:31:35] <lvh> what's the difference between zmq.POLL and zmq.NOBLOCK? Both appear to be flags set on the Context.
| [Monday 12 April 2010] [10:31:52] <lvh> (and both want to not block)
| [Monday 12 April 2010] [10:32:10] <mikko>   NOBLOCK is send/recv flag
| [Monday 12 April 2010] [10:32:29] <lvh> I don't really care if 0MQ blocks internally, as long as I can write my python code as if it doesn't (but how does it tell me it has data when not blocking? callbacks?)
| [Monday 12 April 2010] [10:33:47] <lvh> aha, okay, so s.recv(flags=zmq.NOBLOCK), and then call that in perpetuity until ther's something there? that sounds like busy waiting
| [Monday 12 April 2010] [10:34:34] <sustrik> that's what non-blocking access is meant to be, if you want to block, don't specify the flag
| [Monday 12 April 2010] [10:34:50] <lvh> perhaps I should be asking brian this
| [Monday 12 April 2010] [10:35:03] <lvh> sustrik: I'm used to non-blocking api's that take callbacks
| [Monday 12 April 2010] [10:36:10] <lvh> apparently brian knows twisted, he might know how to best integrate the two
| [Monday 12 April 2010] [10:36:23] <lvh> having select and poll-likes sounds promising :-)
| [Monday 12 April 2010] [10:46:44] <mato>    sustrik: I am going to commit my magic Win32 changes, since they don't break anything
| [Monday 12 April 2010] [10:47:09] <sustrik> ack
| [Monday 12 April 2010] [10:47:09] <mato>    sustrik: but I need two things from you
| [Monday 12 April 2010] [10:47:43] <mato>    sustrik: 1) Change your "DLL being built" define for the MSVC builds to just define "DLL_EXPORT", don't ask why :-)
| [Monday 12 April 2010] [10:48:03] <mato>    sustrik: 2) then when you have time retest the MSVC builds to make sure they still work (they should, but we need to be sure)
| [Monday 12 April 2010] [10:48:26] <sustrik> ok, commit it and I change MSVC build
| [Monday 12 April 2010] [10:48:37] <sustrik> however, are you sure about DLL_EXPORT
| [Monday 12 April 2010] [10:48:42] <sustrik> no ZMQ_ prefix?
| [Monday 12 April 2010] [10:48:44] <mato>    sustrik: yes, don't ask
| [Monday 12 April 2010] [10:49:18] <sustrik> no possible collisions with other projects?
| [Monday 12 April 2010] [10:49:49] <mato>    it shouldn't matter right now, if someone complains i'll do something else
| [Monday 12 April 2010] [10:50:41] <sustrik> well, you should know better than myself, but it sounds suspicious
| [Monday 12 April 2010] [10:52:05] <CIA-5>   zeromq2: 03Martin Lucina 07master * r0024d29 10/ (4 files in 4 dirs): Build fixes for cross compiling and Win32 - http://bit.ly/9kNUJ1
| [Monday 12 April 2010] [10:52:21] <sustrik> ok, i'm switching to win
| [Monday 12 April 2010] [11:00:58] <CIA-5>   zeromq2: 03Martin Sustrik 07master * r370cde0 10/ builds/msvc/libzmq/libzmq.vcproj : win build fixed - http://bit.ly/d0rMDb
| [Monday 12 April 2010] [11:38:37] <lvh> brian granger follows zeromq-dev, right?
| [Monday 12 April 2010] [11:39:15] <mato>    yup
| [Monday 12 April 2010] [11:39:54] <lvh> what exactly is zmq.POLL supposed to do? use async IO internally?
| [Monday 12 April 2010] [11:40:15] <lvh> ideally, I'd like to have an api that fires a callback as soon as messages come in
| [Monday 12 April 2010] [11:40:22] <lvh> I think that can be implemented using zmq_select
| [Monday 12 April 2010] [11:40:33] <lvh> well, zmq.select
| [Monday 12 April 2010] [13:02:24] <lvh> Does select busy-wait until something is available?
| [Monday 12 April 2010] [13:48:32] <sophacles>   2
| [Monday 12 April 2010] [13:49:13] <lvh> sophacles: ?
| [Monday 12 April 2010] [14:18:34] <sophacles>   sorry typo
| [Monday 12 April 2010] [15:45:51] <lvh> Hello.
| [Monday 12 April 2010] [21:08:10] <iFire>   mato, sustrik if I decide to make a custom udp layer for game communication i.e. custom (reliability, ordered) where should I start?
| [Monday 12 April 2010] [21:27:51] <iFire>   i.e. making 0mq do that
| [Monday 12 April 2010] [23:06:38] <enki>    yo, i'm sure you guys are biased - but any opinions on beanstalkd?
| [Tuesday 13 April 2010] [01:06:47] <sustrik>    iFire: reliable ordered UDP or unreliable unordered UDP?
| [Tuesday 13 April 2010] [01:06:52] <iFire>  both
| [Tuesday 13 April 2010] [01:07:07] <iFire>  http://www.jenkinssoftware.com/raknet/manual/reliabilitytypes.html
| [Tuesday 13 April 2010] [01:07:09] <iFire>  example
| [Tuesday 13 April 2010] [01:07:18] <sustrik>    why not use TCP for the former?
| [Tuesday 13 April 2010] [01:08:08] <sustrik>    as for the latter, clone the PGM part of the codebase
| [Tuesday 13 April 2010] [01:08:08] <iFire>  well sometimes if you miss you get a visual error
| [Tuesday 13 April 2010] [01:08:33] <iFire>  there's unreliable, unreliable sequenced, reliable, reliable sequenced
| [Tuesday 13 April 2010] [01:08:37] <iFire>  in that raknet page
| [Tuesday 13 April 2010] [01:08:51] <sustrik>    tcp is reliable sequenced
| [Tuesday 13 April 2010] [01:09:26] <sustrik>    that's what you want, no?
| [Tuesday 13 April 2010] [01:09:38] <iFire>  I want unreliable sequenced
| [Tuesday 13 April 2010] [01:09:50] <iFire>  and unrealiable
| [Tuesday 13 April 2010] [01:10:01] <sustrik>    ok, then clone the pgm part
| [Tuesday 13 April 2010] [01:10:03] <sustrik>    (4 files)
| [Tuesday 13 April 2010] [01:10:12] <sustrik>    ditch the entrails
| [Tuesday 13 April 2010] [01:10:19] <sustrik>    and replace them by UDP code
| [Tuesday 13 April 2010] [01:10:58] <sustrik>    to get sequenced you'll have to number the packets and drop out-of-order packets
| [Tuesday 13 April 2010] [01:11:42] <sustrik>    enki: sorry, never used it
| [Tuesday 13 April 2010] [01:12:49] <iFire>  well it's be symmetrical if I have all four combinations in udp
| [Tuesday 13 April 2010] [01:13:06] <iFire>  sustrik it's in zeromq2/src?
| [Tuesday 13 April 2010] [01:13:20] <sustrik>    reliabilty is not easy to implement
| [Tuesday 13 April 2010] [01:13:26] <sustrik>    and it's provided by tcp anyway
| [Tuesday 13 April 2010] [01:13:35] <sustrik>    iFire: yes
| [Tuesday 13 April 2010] [01:13:43] <sustrik>    pgm_sender/pgm_receiver
| [Tuesday 13 April 2010] [01:16:56] <iFire>  there's not problem with mixing messages right?
| [Tuesday 13 April 2010] [01:17:00] <iFire>  no problem
| [Tuesday 13 April 2010] [01:17:05] <sustrik>    mixing?
| [Tuesday 13 April 2010] [01:17:10] <iFire>  udp/tcp
| [Tuesday 13 April 2010] [01:17:20] <sustrik>    no, it's different protocol
| [Tuesday 13 April 2010] [01:17:41] <sustrik>    btw, for a wire format you have to implement have a look here
| [Tuesday 13 April 2010] [01:17:42] <sustrik>    http://api.zeromq.org/zmq_pgm.html
| [Tuesday 13 April 2010] [01:18:01] <sustrik>    it's already in the pgm part so you can leave that in
| [Tuesday 13 April 2010] [01:20:18] <iFire>  well I want the benefits of being packet based rather than stream based
| [Tuesday 13 April 2010] [01:20:48] <iFire>  but just implementing unreliable and unreliable sequenced I can see how much  work to do
| [Tuesday 13 April 2010] [01:22:51] <sustrik>    iFire: designing a sane raliable protocol is hard; unless you are a networking researcher you don't even want to try
| [Tuesday 13 April 2010] [01:23:08] <sustrik>    you would have to implement tx/rx windowing
| [Tuesday 13 April 2010] [01:23:12] <sustrik>    congestion control
| [Tuesday 13 April 2010] [01:23:14] <sustrik>    etc.
| [Tuesday 13 April 2010] [01:23:28] <sustrik>    all that stuff have been done over the years by tcp folks
| [Tuesday 13 April 2010] [01:23:50] <iFire>  I see
| [Tuesday 13 April 2010] [01:24:02] <sustrik>    as for the unreliable thing, i would estimate it as 1-2 days of work
| [Tuesday 13 April 2010] [01:29:32] <iFire>  I think you can migate the problem of older packets blocking newer packets by having different channels of tcp
| [Tuesday 13 April 2010] [01:30:14] <iFire>  hmm
| [Tuesday 13 April 2010] [01:30:28] <iFire>  sustrik are you familiar with sctp
| [Tuesday 13 April 2010] [01:35:49] <sustrik>    iFire: yes
| [Tuesday 13 April 2010] [01:36:10] <iFire>  the last message I received is iFire sustrik are you familiar with sctp
| [Tuesday 13 April 2010] [01:36:21] <iFire>  last message I saw
| [Tuesday 13 April 2010] [01:37:21] <sustrik>    yes, i am familiar with SCTP
| [Tuesday 13 April 2010] [01:37:31] <iFire>  sustrik last message was iFire sustrik are you familiar with sctp
| [Tuesday 13 April 2010] [01:37:55] <iFire>  well tcp is notorious for packet blocking
| [Tuesday 13 April 2010] [01:38:23] <iFire>  so unreliable udp and sctp
| [Tuesday 13 April 2010] [01:38:37] <sustrik>    that's the price for reliability
| [Tuesday 13 April 2010] [01:38:46] <sustrik>    same thing with sctp btw
| [Tuesday 13 April 2010] [01:38:52] <iFire>  well sctp is reliable and has this concept of channel
| [Tuesday 13 April 2010] [01:39:08] <sustrik>    what do you need exactly?
| [Tuesday 13 April 2010] [01:39:14] <iFire>  well it counts in terms of messages
| [Tuesday 13 April 2010] [01:39:34] <iFire>  I want something that works well in a 3d online game aspect
| [Tuesday 13 April 2010] [01:39:51] <sustrik>    i am not familiar with game development
| [Tuesday 13 April 2010] [01:39:57] <sustrik>    what are the requirements?
| [Tuesday 13 April 2010] [01:40:16] <iFire>  sctp has this
| [Tuesday 13 April 2010] [01:40:17] <iFire>  Multi-streaming is an important feature of SCTP, especially when you consider some of the control and data issues in protocol design. In TCP, control and data typically share the same connection, which can be problematic because control packets can be delayed behind data packets. If control and data were split into independent streams, control data could be dealt with in a more timely manner, resulting in better utilization of available resources.
| [Tuesday 13 April 2010] [01:40:40] <sustrik>    yes, it's same as having several tcp connections
| [Tuesday 13 April 2010] [01:43:43] <sustrik>    also, you should be aware that sctp is not available on windows as a part of OS
| [Tuesday 13 April 2010] [01:44:07] <iFire>  I did not know that
| [Tuesday 13 April 2010] [01:44:21] <iFire>  what does using several tcp connections require?
| [Tuesday 13 April 2010] [01:44:33] <iFire>  different ports?
| [Tuesday 13 April 2010] [01:44:40] <sustrik>    yes
| [Tuesday 13 April 2010] [01:45:57] <sustrik>    also, there's a possibility of opening several connections to the same source port
| [Tuesday 13 April 2010] [01:46:21] <sustrik>    then you would have to tag the messages so that you know which connection it went through
| [Tuesday 13 April 2010] [01:46:29] <sustrik>    - if you need to know it at all
| [Tuesday 13 April 2010] [01:49:09] <iFire>  found http://www.bluestop.org/SctpDrv/
| [Tuesday 13 April 2010] [01:50:19] <iFire>  no 64bit windows signing
| [Tuesday 13 April 2010] [02:02:17] <iFire>  Good Morning sustrik 
| [Tuesday 13 April 2010] [02:06:49] <sustrik>    morning
| [Tuesday 13 April 2010] [02:15:12] <iFire>  sustrik here's a good list of requirements http://stackoverflow.com/questions/1200901/why-is-udp-a-software-reliable-ordering-system-faster-than-tcp/2445227#2445227
| [Tuesday 13 April 2010] [02:15:32] <iFire>  but I not sure if zeromq is the right solution
| [Tuesday 13 April 2010] [02:18:33] <sustrik>    which part of the discussion makes you believe you want to implement reliability on top of UDP>
| [Tuesday 13 April 2010] [02:18:34] <sustrik>    ?
| [Tuesday 13 April 2010] [02:18:46] <iFire>  so I would have to add a unreliable sequenced/unsequenced to the 0mq message
| [Tuesday 13 April 2010] [02:18:55] <iFire>  sustrik I found a library which did that
| [Tuesday 13 April 2010] [02:19:14] <iFire>  routing
| [Tuesday 13 April 2010] [02:20:10] <iFire>  http://enet.bespin.org/ but how would a routing message in zeromq work
| [Tuesday 13 April 2010] [02:20:30]   * iFire looks up wire format
| [Tuesday 13 April 2010] [02:21:18] <sustrik>    udp packets are routed in ip layer
| [Tuesday 13 April 2010] [02:21:57] <iFire>  I mean if I  put enet beneath 0mq, I'll need some way of signaling which 0mq messages have to be routed some way
| [Tuesday 13 April 2010] [02:22:58] <iFire>  i.e. reliability/sequenced
| [Tuesday 13 April 2010] [02:23:57] <sustrik>    if you have a library that does what you need why bother about 0mq at all?
| [Tuesday 13 April 2010] [02:24:04] <iFire>  I don't
| [Tuesday 13 April 2010] [02:24:11] <iFire>  it's just a udp library
| [Tuesday 13 April 2010] [02:24:15] <iFire>  doesn't do messenging
| [Tuesday 13 April 2010] [02:24:47] <iFire>  let's go back to that discussion about adding unreliable to zeromq
| [Tuesday 13 April 2010] [02:25:24] <iFire>  I'll take a look a the code and talk about it later
| [Tuesday 13 April 2010] [02:25:43] <sustrik>    sure
| [Tuesday 13 April 2010] [02:28:19] <enki>   ha, you guys could try using uTP for this :p
| [Tuesday 13 April 2010] [02:48:49] <iFire>  sustrik where are the zmq_msg_t flag definitions?
| [Tuesday 13 April 2010] [02:49:38] <sustrik>    zmq.h
| [Tuesday 13 April 2010] [02:49:47] <sustrik>    ZMQ_MSG_MORE
| [Tuesday 13 April 2010] [02:49:54] <sustrik>    ZMQ_MSG_SHARED
| [Tuesday 13 April 2010] [03:29:17] <mikko>  sndmore/recvmore added
| [Tuesday 13 April 2010] [06:01:44] <sustrik>    mato: ESHUTDOWN is not POSIX, it's Linux-specific, leaving ETERM as is
| [Tuesday 13 April 2010] [07:12:32] <sjampoo>    Martin, just read your message regarding the Polling interface on the mailinglist, seems like you read my mind. 
| [Tuesday 13 April 2010] [07:13:05] <sjampoo>    Do you suggest to have functions that register a socket within the ZMQ api? 
| [Tuesday 13 April 2010] [07:15:54] <sjampoo>    Also, wouldn't a linkedlist be a much nicer datastructure to store the pollable items? 
| [Tuesday 13 April 2010] [07:31:38] <mikko>  sjampoo: the php bindings currently have "add"
| [Tuesday 13 April 2010] [07:31:46] <mikko>  i dont know how orthodox it is
| [Tuesday 13 April 2010] [07:32:19] <mikko>  http://github.com/mkoppanen/php-zmq/blob/master/examples/poll-server.php
| [Tuesday 13 April 2010] [07:32:29] <mikko>  might be subject to change in future
| [Tuesday 13 April 2010] [07:38:06] <sjampoo>    yes, well I really wished that ZMQ had native support for managing a pollset, thus a level on top of the raw zmq_poll so that each binding does not have to implement its own pollset
| [Tuesday 13 April 2010] [07:40:53] <sjampoo>    pyzmq has register / unregister
| [Tuesday 13 April 2010] [07:42:44] <sjampoo>    but on each call to poll() the pollitems array gets rebuild from scratch, which will be expensive with lots of sockets
| [Tuesday 13 April 2010] [07:45:50] <mikko>  at the moment i just realloc up
| [Tuesday 13 April 2010] [07:45:54] <mikko>  never down
| [Tuesday 13 April 2010] [07:46:27] <sjampoo>    what do you do when you remove a socket? 
| [Tuesday 13 April 2010] [07:46:31] <mikko>  why do you build the array on each poll?
| [Tuesday 13 April 2010] [07:46:42] <sjampoo>    (i don't, pyzmq does)
| [Tuesday 13 April 2010] [07:46:48] <mikko>  you only need full rebuild on remove
| [Tuesday 13 April 2010] [07:46:58] <mikko>  add should only cause append
| [Tuesday 13 April 2010] [07:47:06] <mikko>  currently there is no remove in php
| [Tuesday 13 April 2010] [07:48:34] <mikko>  i got a local branch for making some changes to pollset which contains remove as well
| [Tuesday 13 April 2010] [07:49:13] <sustrik>    re
| [Tuesday 13 April 2010] [07:49:18] <sjampoo>    I use the same approach currently as you are suggesting.
| [Tuesday 13 April 2010] [07:49:46] <sjampoo>    I just think it would be nicer if it was implemented in ZMQ directly, ie as a linked list or whatever to get great performance.
| [Tuesday 13 April 2010] [07:50:00] <mikko>  yes, it would make sense
| [Tuesday 13 April 2010] [07:50:15] <sjampoo>    I don't think the API directly matters, as the binding can then provide a thin layer on top of it.
| [Tuesday 13 April 2010] [07:51:05] <sustrik>    i'll definitely move it to 0mq core once the api is agreed on
| [Tuesday 13 April 2010] [07:51:23] <sustrik>    sjampoo: i wouldn't worry about creating the pollset each time
| [Tuesday 13 April 2010] [07:51:38] <sustrik>    there should never be more than couple of sockets in the pollset
| [Tuesday 13 April 2010] [07:52:47] <sjampoo>    Well, there are going to be lots if you are going to use it in some sort of IOLoop that also polls regular TCP sockets.
| [Tuesday 13 April 2010] [07:53:55] <sustrik>    true
| [Tuesday 13 April 2010] [07:54:55] <sustrik>    mikko, sjampoo: so what about the api, how do you believe the results should be retrieved from the pollset?
| [Tuesday 13 April 2010] [08:00:55] <mikko>  int revents; int id; zmq_pollset_t set; zmq_pollset_init(&set); id = zmq_pollset_add_socket(set, s, ZMQ_POLLOUT); zmq_poll(set, -1); revents = zmq_get_events(set, id); if (revents & ZMQ_POLLOUT) {}
| [Tuesday 13 April 2010] [08:01:00] <mikko>  top of my head
| [Tuesday 13 April 2010] [08:01:23] <mikko>  probably not any more flexible than the current one
| [Tuesday 13 April 2010] [08:06:27] <sustrik>    i don't like the 'id' part
| [Tuesday 13 April 2010] [08:06:50] <sustrik>    it somehow presuposes a hash inside the poller to map id to actual pollitem
| [Tuesday 13 April 2010] [08:07:18] <sustrik>    => performance impact
| [Tuesday 13 April 2010] [08:32:04] <sjampoo>    sustrik, it would be nice if i could simply iterate over some sort of result set, but i am not sure what the best approach would be.
| [Tuesday 13 April 2010] [08:34:58] <sustrik>    what about getting events one by one?
| [Tuesday 13 April 2010] [08:35:18] <sustrik>    event = pollset.next_event ();
| [Tuesday 13 April 2010] [08:37:44] <sjampoo>    i would like that i suppose, fe in python one could simply turn that into a generator and yield ready sockets
| [Tuesday 13 April 2010] [08:43:09] <mikko>  how do you know which socket the event ties to?
| [Tuesday 13 April 2010] [08:47:59] <sustrik>    that's the question: what is the event?
| [Tuesday 13 April 2010] [08:48:08] <sustrik>    maybe a triple: socket, event, hint?
| [Tuesday 13 April 2010] [08:48:14] <sustrik>    any better ideas?
| [Tuesday 13 April 2010] [08:48:20] <sjampoo>    Event is actually an object consisting of 'socket', 'event' and a 'hint', as you suggested in your mailing list.
| [Tuesday 13 April 2010] [08:48:32] <sjampoo>    And then the hint can be set while 'adding' the pollitem.
| [Tuesday 13 April 2010] [08:48:43] <sustrik>    that's how epoll does it
| [Tuesday 13 April 2010] [08:48:53] <sjampoo>    What are the restrictions on the hint? 
| [Tuesday 13 April 2010] [08:49:07] <sjampoo>    What type is it? 
| [Tuesday 13 April 2010] [08:49:24] <sustrik>    for epoll it's void* or something like that
| [Tuesday 13 April 2010] [08:49:31] <sjampoo>    aha
| [Tuesday 13 April 2010] [08:49:43] <sjampoo>    well that would be perfect imho
| [Tuesday 13 April 2010] [08:49:52]   * sustrik is not sure how that tanslates to individual languages
| [Tuesday 13 April 2010] [08:50:11] <sustrik>    presumably not every language has 'any' type
| [Tuesday 13 April 2010] [08:53:42] <sjampoo>    well, it shouldn't be that difficult to translate it to something the language does understand by the binding maintainer
| [Tuesday 13 April 2010] [09:06:38] <mato>   re
| [Tuesday 13 April 2010] [09:06:40] <mato>   sustrik: ack
| [Tuesday 13 April 2010] [09:55:18] <mato>   sustrik: you're following the pgm discussion on the mailing list?
| [Tuesday 13 April 2010] [09:55:40] <mato>   sustrik: i think we have finally hit on the problem and everyone agrees it's there, which makes me happy 
| [Tuesday 13 April 2010] [09:55:49] <mato>   sustrik: the question is now, what to do about it ...
| [Tuesday 13 April 2010] [09:57:37] <sustrik>    mato: yup, i am following it
| [Tuesday 13 April 2010] [09:58:00] <sustrik>    afaics what openpgm does is ok
| [Tuesday 13 April 2010] [09:58:07] <sustrik>    you advertise limit of x
| [Tuesday 13 April 2010] [09:58:15] <sustrik>    then publish >x
| [Tuesday 13 April 2010] [09:58:24] <sustrik>    you experience message loss
| [Tuesday 13 April 2010] [09:58:30] <sustrik>    fair enough
| [Tuesday 13 April 2010] [09:58:45] <sustrik>    the problem is that 0mq adds queueing to the picture
| [Tuesday 13 April 2010] [09:59:00] <sustrik>    so you have queue full of data
| [Tuesday 13 April 2010] [09:59:11] <sustrik>    and want it pushed out through multicast
| [Tuesday 13 April 2010] [09:59:25] <sustrik>    you set the rate limit
| [Tuesday 13 April 2010] [09:59:33] <vtl>    sustrik: commit 716f4ac8714d33d21f9853f58482e35c1e3ad934 why do you use int64_t when it should be size_t?
| [Tuesday 13 April 2010] [09:59:43] <sustrik>    and publish much more than that
| [Tuesday 13 April 2010] [10:00:28] <sustrik>    my feeling is that steven may be right about us having to implement some rathe control on top of openpgm
| [Tuesday 13 April 2010] [10:00:33] <sustrik>    vtl: wait a sec
| [Tuesday 13 April 2010] [10:01:54] <sustrik>    vtl: where exactly?
| [Tuesday 13 April 2010] [10:02:00] <mato>   sustrik: us implementing rate control seems silly to me
| [Tuesday 13 April 2010] [10:02:15] <mato>   sustrik: openpgm already has all the information it needs 
| [Tuesday 13 April 2010] [10:02:25] <sustrik>    note that what we do now when we hit the limit is busy looping
| [Tuesday 13 April 2010] [10:02:36] <sustrik>    that feels kind of strange anyway
| [Tuesday 13 April 2010] [10:03:12] <vtl>    sustrik: almost everywhere. socket options has type of size_t
| [Tuesday 13 April 2010] [10:03:23] <sustrik>    ?
| [Tuesday 13 April 2010] [10:03:31] <mato>   sustrik: my point is that the current situation is broken. AFAICS pgm with 0mq does not work. at all.
| [Tuesday 13 April 2010] [10:03:32] <vtl>    or I miss something?
| [Tuesday 13 April 2010] [10:03:39] <sustrik>    you mean POSIX socket options?
| [Tuesday 13 April 2010] [10:04:12] <vtl>    yeah, I messed it up. sorry
| [Tuesday 13 April 2010] [10:04:18] <sustrik>    np
| [Tuesday 13 April 2010] [10:04:39] <sustrik>    mato: it works unless the limit is hit, no?
| [Tuesday 13 April 2010] [10:05:22] <mato>   sustrik: yes, but the application has no way of controlling that
| [Tuesday 13 April 2010] [10:05:30] <mato>   sustrik: therefore it does not work
| [Tuesday 13 April 2010] [10:05:39] <sustrik>    then it's not completely broken
| [Tuesday 13 April 2010] [10:05:54] <sustrik>    and btw pub/sub doesn't guarantee delivery anyway
| [Tuesday 13 April 2010] [10:06:06] <mato>   sustrik: it's not about guaranteeing delivery
| [Tuesday 13 April 2010] [10:06:08] <sustrik>    so it may be less reliable than expected but not broken
| [Tuesday 13 April 2010] [10:06:28] <mato>   sustrik: yes, but with the latest changes steven made, you saw what happened when i tried the performance tests
| [Tuesday 13 April 2010] [10:06:45] <sustrik>    hang up?
| [Tuesday 13 April 2010] [10:06:47] <mato>   sustrik: you run the _thr tests and the moment you hit the limit everything just hangs
| [Tuesday 13 April 2010] [10:06:50] <mato>   yes
| [Tuesday 13 April 2010] [10:06:55] <mato>   hangs == broken in my book
| [Tuesday 13 April 2010] [10:07:15] <sustrik>    thr tests should be modified to use P2P sockets
| [Tuesday 13 April 2010] [10:07:47] <mato>   huh?
| [Tuesday 13 April 2010] [10:07:50] <sustrik>    P2P sovkets don't allow for PGM as underlying protocol
| [Tuesday 13 April 2010] [10:07:56] <sustrik>    that solves the problem
| [Tuesday 13 April 2010] [10:07:59] <mato>   you're side-stepping the issue
| [Tuesday 13 April 2010] [10:08:04] <sustrik>    nope
| [Tuesday 13 April 2010] [10:08:10] <sustrik>    PUB/SUB is unreliable
| [Tuesday 13 April 2010] [10:08:20] <sustrik>    thus you cannot base the test on it
| [Tuesday 13 April 2010] [10:08:37] <sustrik>    there's always a chance of message being dropped
| [Tuesday 13 April 2010] [10:08:52] <sustrik>    that's the nature of pub/sub
| [Tuesday 13 April 2010] [10:09:16] <sustrik>    "rather drop messages then let the slow consumer block the whole system"
| [Tuesday 13 April 2010] [10:09:29] <mato>   the problem here is *not* about slow consumers 
| [Tuesday 13 April 2010] [10:09:35] <sustrik>    i know
| [Tuesday 13 April 2010] [10:09:54] <sustrik>    but the semantics of pub/sub based on the slow consumer scenario
| [Tuesday 13 April 2010] [10:10:08] <sustrik>    fit even the case we are seeing niw
| [Tuesday 13 April 2010] [10:10:12] <sustrik>    now*
| [Tuesday 13 April 2010] [10:10:20] <sustrik>    what's happening is annoying
| [Tuesday 13 April 2010] [10:10:25] <sustrik>    bet technically sound
| [Tuesday 13 April 2010] [10:10:32] <sustrik>    but*
| [Tuesday 13 April 2010] [10:10:48] <mato>   it might be technically sound according to the (vague) PGM spec, and according to the implementation
| [Tuesday 13 April 2010] [10:11:09] <mato>   but it seems to me that the current behaviour is totally useless from an application developer's point of view
| [Tuesday 13 April 2010] [10:11:14] <sustrik>    ack
| [Tuesday 13 April 2010] [10:12:02] <mato>   the question remains, what to do about it...
| [Tuesday 13 April 2010] [10:12:52] <sustrik>    my feeling is that another rate limit has to be implemeted on 0mq level
| [Tuesday 13 April 2010] [10:13:50] <mato>   what's wrong with reserving x% of the bandwidth for RDATA at the openpgm level?
| [Tuesday 13 April 2010] [10:14:23] <sustrik>    nothing, but you still end up with busy looping
| [Tuesday 13 April 2010] [10:15:06] <mato>   why are we busy looping?
| [Tuesday 13 April 2010] [10:15:51] <sustrik>    because when you try to send openPGM says: EAGAIN (because od the rate limit)
| [Tuesday 13 April 2010] [10:16:08] <sustrik>    you cannot poll for POLLOT
| [Tuesday 13 April 2010] [10:16:11] <sustrik>    POLLOUT
| [Tuesday 13 April 2010] [10:19:24] <mato>   well, i don't know what to do now
| [Tuesday 13 April 2010] [10:19:57] <mato>   presumably 2.0.7 should include steven's changes post openpgm 2.0.24 that fix the crashes, but introduce the hangs
| [Tuesday 13 April 2010] [10:20:19] <mato>   but as for what to do with the current behaviour...
| [Tuesday 13 April 2010] [10:20:24] <sustrik>    it's not easy
| [Tuesday 13 April 2010] [10:20:40] <sustrik>    what i am saying it's good enough to let it be for now
| [Tuesday 13 April 2010] [10:21:03] <sustrik>    if the actual rate is lower than specified max rate everyting works as expected
| [Tuesday 13 April 2010] [10:21:18] <sustrik>    it you publish faster, messages get lost
| [Tuesday 13 April 2010] [10:21:35] <mato>   no, if you publish faster your publisher hangs
| [Tuesday 13 April 2010] [10:21:44] <sustrik>    publisher?
| [Tuesday 13 April 2010] [10:21:54] <mato>   sorry, consumer
| [Tuesday 13 April 2010] [10:22:10] <sustrik>    it doesn't hang, it only looses some messages, no?
| [Tuesday 13 April 2010] [10:22:16] <mato>   no, it hangs
| [Tuesday 13 April 2010] [10:22:19] <mato>   forever
| [Tuesday 13 April 2010] [10:22:21] <sustrik>    a-ha
| [Tuesday 13 April 2010] [10:22:37] <sustrik>    how does that happen?
| [Tuesday 13 April 2010] [10:23:16] <mato>   that was discussed in the long thread between me and steven
| [Tuesday 13 April 2010] [10:23:30] <sustrik>    i;ve missed the consumer hanging part
| [Tuesday 13 April 2010] [10:23:39] <mato>   due to the packet loss, and the absence of RDATA, the receiver is unable to recover, ever
| [Tuesday 13 April 2010] [10:24:03] <sustrik>    if says "unrecoverable message loss", no?
| [Tuesday 13 April 2010] [10:24:13] <mato>   no
| [Tuesday 13 April 2010] [10:24:21] <sustrik>    yuck
| [Tuesday 13 April 2010] [10:24:35] <mato>   well, i'm not 100% sure
| [Tuesday 13 April 2010] [10:24:52] <mato>   i'd have to retest at your place again
| [Tuesday 13 April 2010] [10:25:24] <sustrik>    i though local_the hangs because it does not get all the messages
| [Tuesday 13 April 2010] [10:25:34] <sustrik>    hm
| [Tuesday 13 April 2010] [10:26:25] <mato>   no, the behaviour i saw with local_thr was it gets ~2k messages, then (presumably) some packet loss occurs and it just sits there forever
| [Tuesday 13 April 2010] [10:26:57] <sustrik>    right, because the rest of the messages are lost
| [Tuesday 13 April 2010] [10:27:39] <sustrik>    it happens because you publish faster than the rate is set
| [Tuesday 13 April 2010] [10:28:57] <sustrik>    i am not saying it is great
| [Tuesday 13 April 2010] [10:29:30] <sustrik>    but it's not a real bug
| [Tuesday 13 April 2010] [10:29:44] <sustrik>    it's reliability deficiency problem :)
| [Tuesday 13 April 2010] [10:36:55] <sustrik>    mato: btw, there's a pull request from mikko for the RPM packaging
| [Tuesday 13 April 2010] [10:38:52] <mato>   sustrik: yes, requires license-foo
| [Tuesday 13 April 2010] [10:39:16] <sustrik>    are you sure these are needed for packaging scripts/
| [Tuesday 13 April 2010] [10:39:17] <sustrik>    ?
| [Tuesday 13 April 2010] [10:39:21] <mato>   yes
| [Tuesday 13 April 2010] [10:39:28] <mato>   anything that goes into the 0mq git
| [Tuesday 13 April 2010] [10:39:32] <sustrik>    mikko: are you there?
| [Tuesday 13 April 2010] [10:40:44] <sustrik>    he seems to be out
| [Tuesday 13 April 2010] [10:46:38] <sustrik>    sent him a message
| [Tuesday 13 April 2010] [10:52:06] <mikko>  almost here
| [Tuesday 13 April 2010] [10:52:11] <mikko>  @work 
| [Tuesday 13 April 2010] [10:52:33] <mikko>  is there a CLA i can sign?
| [Tuesday 13 April 2010] [10:52:47] <mikko>  so that all my contributions would be automatically under the license
| [Tuesday 13 April 2010] [10:53:53] <mato>   mikko: we haven't really formulated one yet
| [Tuesday 13 April 2010] [10:54:03] <mato>   adrian sent me this, for example:
| [Tuesday 13 April 2010] [10:54:09] <mato>   +++
| [Tuesday 13 April 2010] [10:54:09] <mato>   I, Adrian von Bidder, Switzerland, license my work on the Debian packaging of
| [Tuesday 13 April 2010] [10:54:09] <mato>   the zeromq library to iMatrix under the MIT/X11 licsense.
| [Tuesday 13 April 2010] [10:54:09] <mato>   +++
| [Tuesday 13 April 2010] [10:54:17] <mato>   by email, with the relevant patch attached
| [Tuesday 13 April 2010] [10:54:47] <sustrik>    shouldn't it go to the mailing list?
| [Tuesday 13 April 2010] [10:54:55] <mato>   yes, he sent it to the mailing list
| [Tuesday 13 April 2010] [10:55:11] <mato>   sustrik: we need to decide how to handle this, and ph needs to agree
| [Tuesday 13 April 2010] [10:55:40] <sustrik>    yes, it's a mess
| [Tuesday 13 April 2010] [10:55:52] <sustrik>    i am trying to direct this kind of thing to the mailing list
| [Tuesday 13 April 2010] [10:56:04] <sustrik>    as it's presumably more persistent than personal mail boxes
| [Tuesday 13 April 2010] [10:56:15] <mato>   yeah, but even there the relevant statements will get lost 
| [Tuesday 13 April 2010] [10:56:45] <sustrik>    shrug
| [Tuesday 13 April 2010] [10:56:54] <mikko>  CLA would make most sense
| [Tuesday 13 April 2010] [10:57:16] <mikko>  that in theory would eliminate the need for patches etc
| [Tuesday 13 April 2010] [10:57:42] <mato>   mikko: I'm thinking of two things
| [Tuesday 13 April 2010] [10:58:02] <mato>   mikko: 1) Simple template "CLA" or whatever you want to call it by email
| [Tuesday 13 April 2010] [10:58:29] <mato>   mikko: 2) Signed-off-by: on any git commits which is explicitly defined as "falls under the CLA"
| [Tuesday 13 April 2010] [10:58:50] <mikko>  1) probably needs a signature (fax / scan / etc)
| [Tuesday 13 April 2010] [10:58:54] <mikko>  2) makes sense
| [Tuesday 13 April 2010] [10:59:05] <mato>   no, we want to deliberately avoid the whole fax/scan/etc
| [Tuesday 13 April 2010] [10:59:14] <mato>   email is enough, this is 2010 after all
| [Tuesday 13 April 2010] [10:59:33] <mikko>  is it legally binding? i've had to scan+email to many places
| [Tuesday 13 April 2010] [10:59:46] <mato>   mikko: the consensus is that it's "Good enough"
| [Tuesday 13 April 2010] [11:00:02] <sustrik>    what's signed-off-by?
| [Tuesday 13 April 2010] [11:00:19] <mato>   mikko: see the commentary by Pieter Hintjens at http://www.zeromq.org/blog:why-the-mit-license-for-contributions
| [Tuesday 13 April 2010] [11:00:53] <mato>   sustrik: it's just an extra header you can add to git commits/patches
| [Tuesday 13 April 2010] [11:00:56] <mikko>  http://www.apache.org/licenses/icla.txt
| [Tuesday 13 April 2010] [11:01:02] <mikko>  thats apache one
| [Tuesday 13 April 2010] [11:01:29] <sustrik>    isn't the signed-off-by better then?
| [Tuesday 13 April 2010] [11:01:31] <mato>   sustrik: the Linux kernel people use it to mean "I sign off this patch and state that it came from me" or something similar
| [Tuesday 13 April 2010] [11:01:39] <sustrik>    everyone going to commit anyway
| [Tuesday 13 April 2010] [11:01:47] <sustrik>    so adding one field is not big a hassle
| [Tuesday 13 April 2010] [11:01:52] <mato>   sustrik: yeah, but you need to define somewhere *else* what the Signed-Off-By in the context of 0mq git means
| [Tuesday 13 April 2010] [11:01:55] <sustrik>    and we can pull the patches directly
| [Tuesday 13 April 2010] [11:02:21] <sustrik>    hm
| [Tuesday 13 April 2010] [11:03:06] <mikko>  http://www.oss-watch.ac.uk/resources/cla.xml#body.1_div.4
| [Tuesday 13 April 2010] [11:03:09] <mikko>  4. Associating commits to CLAs
| [Tuesday 13 April 2010] [11:03:15] <mato>   sustrik: hence the combination of a simple email statement "I, XXX, of YYY, hereby state that any commits of mine containing Signed-Off-By: ..., are licensed under the MIT license.
| [Tuesday 13 April 2010] [11:03:28] <mato>   sustrik: with actual Signed-Off-By headers
| [Tuesday 13 April 2010] [11:03:55] <sustrik>    mikko:  right
| [Tuesday 13 April 2010] [11:04:08] <sustrik>    mato: yes, seems to make sense
| [Tuesday 13 April 2010] [11:04:39] <mato>   sustrik: it should also be possible to put a hook in github to reject commits w/o a Signed-Off-By
| [Tuesday 13 April 2010] [11:04:51] <sustrik>    mikko's link suggest that's it's necessary to be able to blame each line of code
| [Tuesday 13 April 2010] [11:05:10] <sustrik>    that can be done only by direct pulling => singed-off-by
| [Tuesday 13 April 2010] [11:05:36] <mato>   no, it can work for all models
| [Tuesday 13 April 2010] [11:05:44] <mato>   at least i think so, here's an example
| [Tuesday 13 April 2010] [11:05:52] <sustrik>    ah, the --author option
| [Tuesday 13 April 2010] [11:05:53] <sustrik>    right
| [Tuesday 13 April 2010] [11:06:20] <mato>   the point is you can set up your git so that *all* your commits to zeromq2 contain the signed-off-by tag
| [Tuesday 13 April 2010] [11:06:37] <sustrik>    that would be good, no?
| [Tuesday 13 April 2010] [11:06:44] <mato>   then, when those commits are pushed/pulled/whatever, the signed-off-by tags propagate 
| [Tuesday 13 April 2010] [11:06:54] <mato>   sustrik: yes, that is what i have in mind
| [Tuesday 13 April 2010] [11:07:35] <sustrik>    mato: post a proposal to the mailing list and let's see what will people say
| [Tuesday 13 April 2010] [11:08:24] <mato>   i'll email a proposal to pieter first, and get him to make that post
| [Tuesday 13 April 2010] [11:08:28] <mato>   i don't speak for imatix
| [Tuesday 13 April 2010] [11:08:29] <sustrik>    ok
| [Tuesday 13 April 2010] [11:09:11] <sustrik>    however, this is discussion of technical aspect of contributing so community should have a say
| [Tuesday 13 April 2010] [11:09:37] <mato>   right, well then i can make a proposal
| [Tuesday 13 April 2010] [11:52:46] <mikko>  hmm
| [Tuesday 13 April 2010] [11:53:23] <mikko>  if i add fd to pollset and close the remote peer the socket is marked readable in a loop
| [Tuesday 13 April 2010] [11:55:26] <mikko>  ermm confusing terms
| [Tuesday 13 April 2010] [11:55:53] <mikko>  adding normal fd that is connected to a remote peer. remote peer closes and poll marks it readable in in a loop
| [Tuesday 13 April 2010] [11:55:58] <mikko>  and chews 100% cpu 
| [Tuesday 13 April 2010] [11:57:34] <mikko>  i guess i need to check for that
| [Tuesday 13 April 2010] [11:59:45] <sustrik>    mikko: "if i add fd to pollset and close the remote peer the socket is marked readable"
| [Tuesday 13 April 2010] [11:59:52] <sustrik>    that's standard POSIX behaviour
| [Tuesday 13 April 2010] [12:00:10] <sustrik>    in case of orderly shutdown POLLIN is signaled
| [Tuesday 13 April 2010] [12:00:18] <sustrik>    and subsequent read returns 0 bytes
| [Tuesday 13 April 2010] [12:00:20] <sustrik>    iirc
| [Tuesday 13 April 2010] [12:03:55] <mikko>  indeed
| [Tuesday 13 April 2010] [12:04:57] <mikko>  i need to work on this a bit on the evening
| [Tuesday 13 April 2010] [12:05:07] <mikko>  to make the removing of objects more fluent
| [Tuesday 13 April 2010] [12:09:15] <mato>   argh
| [Tuesday 13 April 2010] [12:09:31] <mato>   the whole signed-off-by thing with git is complicated :-(
| [Tuesday 13 April 2010] [12:09:43] <mato>   i don't want to deal with this right now, i'd rather get some real work done 
| [Tuesday 13 April 2010] [12:10:14] <sustrik>    ok, mikko, won't you mind simply sending the patch to the mailing list and stating it's MIT licensed?
| [Tuesday 13 April 2010] [12:10:22] <mato>   mikko: in the interim, can you just send a copy of your patch made with git-format-patch to the mailing list, and include one line that says "This patch is submitted under the MIT license"?
| [Tuesday 13 April 2010] [12:10:27] <sustrik>    :)
| [Tuesday 13 April 2010] [12:10:27] <mato>   sustrik: my words exactly :-)
| [Tuesday 13 April 2010] [12:11:07] <mato>   sustrik: ok, ad openpgm: i guess i should just email steven to make a 2.0.25 release with his latest changes, since that stops the crashes
| [Tuesday 13 April 2010] [12:11:17] <mato>   sustrik: that can go into our 2.0.7
| [Tuesday 13 April 2010] [12:11:21] <sustrik>    ack
| [Tuesday 13 April 2010] [12:11:44] <mato>   sustrik: therefore the only other thing is looking at the options/flags stuff, which i will write about
| [Tuesday 13 April 2010] [12:12:04] <mato>   and then i can get onto writing that nginx plugin which is actually interesting :-)
| [Tuesday 13 April 2010] [12:12:07] <mato>   sustrik: ack?
| [Tuesday 13 April 2010] [12:12:17] <sustrik>    sure, more useful even
| [Tuesday 13 April 2010] [12:12:47]   * mato is trying to ignore the list of administrivia and actually enjoy making something useful
| [Tuesday 13 April 2010] [12:12:47] <sustrik>    mato, mikko: the rpm spac file in the patch in in builds subdirectory
| [Tuesday 13 April 2010] [12:12:53] <mato>   good, we're agreed then
| [Tuesday 13 April 2010] [12:13:08] <sustrik>    shouldn't it go to 'packages' ?
| [Tuesday 13 April 2010] [12:13:16] <sustrik>    mato: yes
| [Tuesday 13 April 2010] [12:13:27] <mato>   sustrik: why create packages when we already have builds, it doesn't really matter
| [Tuesday 13 April 2010] [12:13:57] <mato>   sustrik: the point is at make dist time that spec file will get copied into the tarball root anyway
| [Tuesday 13 April 2010] [12:14:02] <sustrik>    dunno, msvc build system and rpm packaging script seem to be distinct kind of thing
| [Tuesday 13 April 2010] [12:14:05] <mato>   sustrik: this is similar to why debian is in /
| [Tuesday 13 April 2010] [12:14:35] <sustrik>    up to you guys, i'm giving up :)
| [Tuesday 13 April 2010] [12:14:43] <mato>   who cares
| [Tuesday 13 April 2010] [12:14:45] <mato>   it's just trivia
| [Tuesday 13 April 2010] [12:14:50] <mato>   less directories is better :-)
| [Tuesday 13 April 2010] [12:14:57] <mikko>  "redhat builds", "debian builds", "windows builds"
| [Tuesday 13 April 2010] [12:14:59] <mikko>  sounds logical
| [Tuesday 13 April 2010] [12:15:01] <mato>   exactly
| [Tuesday 13 April 2010] [12:15:16] <sustrik>    ah, it also builds the thing?
| [Tuesday 13 April 2010] [12:15:24] <mikko>  it creates binaries
| [Tuesday 13 April 2010] [12:15:29] <mikko>  or source rpms
| [Tuesday 13 April 2010] [12:15:31]   * sustrik has no idea how packaging works
| [Tuesday 13 April 2010] [12:15:39] <sustrik>    then it makes perfect sense
| [Tuesday 13 April 2010] [12:15:42] <mikko>  spec-file defines how it's built 
| [Tuesday 13 April 2010] [12:15:48] <sustrik>    sorry for trolling
| [Tuesday 13 April 2010] [12:15:51] <mikko>  and creates installable rpm package
| [Tuesday 13 April 2010] [12:16:00] <mikko>  i guess you are entitled for a bit of trolling :)
| [Tuesday 13 April 2010] [12:54:22] <iFire>  wow vmware is on a roll. They acquired rabbitmq
| [Tuesday 13 April 2010] [12:54:34] <iFire>  previously it was redis
| [Tuesday 13 April 2010] [12:57:43] <sustrik>    yup, looks like they are making a portfolio of cloud infrastructure
| [Tuesday 13 April 2010] [12:58:50] <iFire>  I hope vmware deals with rabbitmq the same way they dealt with redis. i.e. keep the same license, except pay the developers for work
| [Tuesday 13 April 2010] [12:59:52] <iFire>  (background info: redis is in bsd license)
| [Tuesday 13 April 2010] [13:01:25] <sustrik>    I've just spoke to rabbitmq guys, seems that that's the plan
| [Tuesday 13 April 2010] [13:02:20] <sustrik>    from the press release: "RabbitMQ will continue to be open source and distributed in the same way 
| [Tuesday 13 April 2010] [13:02:21] <sustrik>    as before. The RabbitMQ community can expect to see increased investment 
| [Tuesday 13 April 2010] [13:02:21] <sustrik>    in this outstanding technology which should result in significant 
| [Tuesday 13 April 2010] [13:02:21] <sustrik>    improvements to the open source release."
| [Tuesday 13 April 2010] [14:04:59] <dirtmcgirt> hi all.
| [Tuesday 13 April 2010] [14:05:09] <dirtmcgirt> can zeromq be used along side libevent?
| [Tuesday 13 April 2010] [14:05:58] <mikko>  dirtmcgirt: we actually discussed the other day about 0MQ and libev
| [Tuesday 13 April 2010] [14:06:15] <dirtmcgirt> mikko: ah! i missed it.
| [Tuesday 13 April 2010] [14:06:55] <mikko>  http://pod.tst.eu/http://cvs.schmorp.de/libev/ev.pod#code_ev_prepare_code_and_code_ev_che
| [Tuesday 13 April 2010] [14:07:04] <mikko>  libev provides something like that looks like it could be used
| [Tuesday 13 April 2010] [14:07:13] <mikko>  you could check whether libevent provides something similar
| [Tuesday 13 April 2010] [14:09:07] <dirtmcgirt> interesting, thanks
| [Tuesday 13 April 2010] [14:09:33] <mikko>  i've written most of my stuff using libev lately (instead of libevent)
| [Tuesday 13 April 2010] [14:09:49] <mikko>  libevent has a nice http library though
| [Tuesday 13 April 2010] [14:09:58] <mikko>  evhttp i think it's called
| [Tuesday 13 April 2010] [14:10:05] <dirtmcgirt> yes, we are using that
| [Tuesday 13 April 2010] [14:10:08] <dirtmcgirt> it's great
| [Wednesday 14 April 2010] [13:35:48] <jomofo>   When I try to build libzmq from master I get this error (Linux x86) :  make[1]: *** No rule to make target `local_lat.c', needed by `local_lat.o'.  Stop.
| [Wednesday 14 April 2010] [13:37:01] <jomofo>   Guessing it's a makefile issue, but don't have enough experience with automake to solve on my own.  Any hints?  Thanks
| [Wednesday 14 April 2010] [14:16:06] <mikko>    jomofo: lemme test
| [Wednesday 14 April 2010] [14:16:07] <mikko>    sec
| [Wednesday 14 April 2010] [14:19:12] <mikko>    builds fine here from clean git clone
| [Wednesday 14 April 2010] [14:20:32] <jomofo>   I will try a fresh clone
| [Wednesday 14 April 2010] [14:25:47] <jomofo>   mikko: it builds now, thanks.  I guess maybe I didn't clean before I pulled and some remnant was causing that?
| [Wednesday 14 April 2010] [14:26:23] <mikko>    no harm in make clean && ./autogen.sh after pull
| [Wednesday 14 April 2010] [14:26:36] <mikko>    and ./configure && make
| [Wednesday 14 April 2010] [14:28:38] <jomofo>   mikko: I went through those steps several times after I pulled before I decided to come here.  Maybe clean was not wiping something?  
| [Wednesday 14 April 2010] [14:29:09] <mikko>    make distclean might wipe more
| [Wednesday 14 April 2010] [14:29:12] <mikko>    or just fail
| [Wednesday 14 April 2010] [14:29:14] <mikko>    not sure
| [Wednesday 14 April 2010] [14:29:26] <mikko>    but make clean doesnt remove auto* artifacts
| [Wednesday 14 April 2010] [14:31:43] <jomofo>   That makes sense.  I still have the old working copy so I'll play around and see if I can discover more about the black box I'm playing with... Thanks for the idea of starting over though
| [Wednesday 14 April 2010] [14:33:45] <jomofo>   make distclean did the trick in the old working copy
| [Wednesday 14 April 2010] [15:00:59] <sustrik>  jomofo: the files in question were renamed
| [Wednesday 14 April 2010] [15:01:13] <sustrik>  automake has problem couping with it
| [Wednesday 14 April 2010] [15:01:26] <sustrik>  in any case, fresh copy solves it
| [Wednesday 14 April 2010] [15:07:51] <sophacles>    sustrik: a few days back you mentioned to me using *_thr for some throughput testing using very large numbers for message sizes.  its strange when I do that remote_thr quits fairly soon and local_thr doesn't ever finish.
| [Wednesday 14 April 2010] [15:07:58] <sophacles>    any thoughts as to why?
| [Wednesday 14 April 2010] [15:08:20] <sustrik>  there's sleep(10) hardcoded in the sender
| [Wednesday 14 April 2010] [15:08:47] <sustrik>  it transmission takes more than that, the sender quits in the middle of the transmission
| [Wednesday 14 April 2010] [15:08:50] <sustrik>  ugly, i know
| [Wednesday 14 April 2010] [15:11:59] <sophacles>    ahhh ok. ill dig into the code then. thanks for the pointer
| [Wednesday 14 April 2010] [15:13:40] <sustrik>  to sanitize the throughput test, P2P sockets should be used instead of PUB/SUB
| [Wednesday 14 April 2010] [15:13:53] <sophacles>    is there a better way to determine if all messages have been sent? (e.g a zmq_wait() or zmq_join())?
| [Wednesday 14 April 2010] [15:14:08] <sustrik>  P2P being bi-directional would allow for "the end" message to be passed back to the sender
| [Wednesday 14 April 2010] [15:14:41] <sustrik>  that's it, i think
| [Wednesday 14 April 2010] [15:15:18] <sustrik>  just change to socket type to P2P, after the receiver receives all messages make it send a dummy message
| [Wednesday 14 April 2010] [15:15:36] <sustrik>  the sender should send all messages and wait for the dummy message from receiver
| [Wednesday 14 April 2010] [15:16:01] <sustrik>  the problem is that there are ~10 instances of perf tests for various languages
| [Wednesday 14 April 2010] [15:16:11] <sustrik>  lot of work to fix all of it
| [Wednesday 14 April 2010] [15:17:07] <sophacles>    OK thanks. ill do that. sounds simple enough. sanity check on my approach: a simple blocking read place of zmq_sleep is the magic mechanism correct?
| [Wednesday 14 April 2010] [15:17:16] <sustrik>  ack
| [Wednesday 14 April 2010] [15:28:37] <jomofo>   sustrik: troubleshooting an error with JNI and came across this:  http://forums.sun.com/thread.jspa?threadID=5379144
| [Wednesday 14 April 2010] [15:29:42] <jomofo>   sustrik: thought it was kinda funny when I noticed it was your thread
| [Wednesday 14 April 2010] [15:31:30] <sustrik>  :)
| [Wednesday 14 April 2010] [15:32:16] <sustrik>  i am not sure what the problem is now - gonzalo diethelm introduced the latest changes
| [Wednesday 14 April 2010] [15:32:26] <sustrik>  he probably got something wrong
| [Wednesday 14 April 2010] [15:33:44] <jomofo>   I will keep digging, I was just hoping someone on the list could tell me if I was doing something silly
| [Wednesday 14 April 2010] [15:35:57] <sustrik>  jomofo: any chance the old version of jzmq is being loaded?
| [Wednesday 14 April 2010] [15:38:46] <jomofo>   sustrik: I don't believe so, but I've done crazier things.  I will wipe /usr/local/lib, verify it breaks my test, then build again
| [Wednesday 14 April 2010] [15:39:40] <sustrik>  the code looks more or less correct:
| [Wednesday 14 April 2010] [15:39:41] <sustrik>  JNIEXPORT void JNICALL Java_org_zeromq_ZMQ_00024Context_construct (JNIEnv *env,
| [Wednesday 14 April 2010] [15:39:41] <sustrik>                                                                     jobject obj,
| [Wednesday 14 April 2010] [15:39:41] <sustrik>                                                                     jint app_threads,
| [Wednesday 14 April 2010] [15:39:41] <sustrik>                                                                     jint io_threads,
| [Wednesday 14 April 2010] [15:39:43] <sustrik>                                                                     jint flags)
| [Wednesday 14 April 2010] [15:40:05] <sustrik>  I am not sure what the 00024 thing means...
| [Wednesday 14 April 2010] [15:40:39] <jomofo>   I think that must be somehow escaping the '$' you usually see with inner classes
| [Wednesday 14 April 2010] [15:41:24] <sustrik>  0x24 = $ ?
| [Wednesday 14 April 2010] [15:41:31] <sustrik>  lemme see
| [Wednesday 14 April 2010] [15:41:51] <jomofo>   yup
| [Wednesday 14 April 2010] [15:41:56] <sustrik>  bingo
| [Wednesday 14 April 2010] [15:42:30] <jomofo>   But I don't know what's making that translation or if it's possibly broken at runtime?
| [Wednesday 14 April 2010] [15:42:49] <sustrik>  shrug
| [Wednesday 14 April 2010] [15:43:55] <sustrik>  can you check the prototype of the function in your JNI-generated header file?
| [Wednesday 14 April 2010] [15:44:01] <sustrik>  is it the same?
| [Wednesday 14 April 2010] [15:44:28] <sustrik>  org_zeromq_ZMQ_Context.h
| [Wednesday 14 April 2010] [15:44:47] <jomofo>   JNIEXPORT void JNICALL Java_org_zeromq_ZMQ_00024Context_construct
| [Wednesday 14 April 2010] [15:44:47] <jomofo>     (JNIEnv *, jobject, jint, jint, jint);
| [Wednesday 14 April 2010] [15:46:07] <sustrik>  hm
| [Wednesday 14 April 2010] [15:46:33] <sustrik>  let me try here
| [Wednesday 14 April 2010] [15:49:02] <sustrik>  yuck, i cannot even build it
| [Wednesday 14 April 2010] [15:49:09] <sustrik>  /usr/bin/ld: /usr/local/lib/libzmq.a(libzmq_la-zmq.o): relocation R_X86_64_32 against `.rodata' can not be used when making a shared object; recompile with -fPIC
| [Wednesday 14 April 2010] [15:49:09] <sustrik>  /usr/local/lib/libzmq.a: could not read symbols: Bad value
| [Wednesday 14 April 2010] [15:51:18] <sophacles>    so with p2p sockets, do i bind/connect or...? (wierd segfaulting issues)
| [Wednesday 14 April 2010] [15:51:52] <jomofo>   sustrik: eek, I don't get that ... I can build it on Ubuntu 9.04 32-bit and 64-bit
| [Wednesday 14 April 2010] [15:52:02] <jomofo>   Does this mean anything to you? http://stackoverflow.com/1147890/relocation-r-x86-64-32-against-a-local-symbol-error
| [Wednesday 14 April 2010] [15:53:38] <sustrik>  page not found
| [Wednesday 14 April 2010] [15:54:37] <jomofo>   doh, copy/paste error http://stackoverflow.com/questions/1147890/relocation-r-x86-64-32-against-a-local-symbol-error
| [Wednesday 14 April 2010] [15:58:40] <sustrik>  my fault, i had libzmq compiled with --disable-shared on my system
| [Wednesday 14 April 2010] [15:58:45] <sustrik>  now it builds ok
| [Wednesday 14 April 2010] [16:06:17] <sophacles>    ok, better phrasing/more info: when i change the perf example to use P2P sockets, in local_thr, the first call to zmq_recv in the for loop segfaults. it is very odd, as i haven't changed anything other than changing the socket type and droping the setsockopt for subscription.
| [Wednesday 14 April 2010] [16:08:22] <sustrik>  :(
| [Wednesday 14 April 2010] [16:08:31] <sustrik>  P2P are experimental
| [Wednesday 14 April 2010] [16:08:47] <sustrik>  there must be some bug there...
| [Wednesday 14 April 2010] [16:08:56] <sustrik>  any chance of getting the backtrace?
| [Wednesday 14 April 2010] [16:09:20] <sustrik>  jomofo: it seems to work on my box
| [Wednesday 14 April 2010] [16:10:35] <sophacles>    I can do that, how do you want the trace?
| [Wednesday 14 April 2010] [16:11:06] <sustrik>  just run it under gdb
| [Wednesday 14 April 2010] [16:11:10] <sustrik>  when it breaks
| [Wednesday 14 April 2010] [16:11:11] <sustrik>  bt
| [Wednesday 14 April 2010] [16:16:27] <jomofo>   sustrik: if you don't mind, what distro/version/arch is your box running?  It is similarly broken on both of my boxes.  I verified only one copy of libjzmq, but maybe I should try again in a clean VM
| [Wednesday 14 April 2010] [16:17:02] <sustrik>  Linux istvan 2.6.31-20-generic #58-Ubuntu SMP Fri Mar 12 04:38:19 UTC 2010 x86_64 GNU/Linux
| [Wednesday 14 April 2010] [16:17:45] <sophacles>    sustrik: http://paste.pocoo.org/show/201908/ has my version of local_thr and the gdb output. if you want any other info let me know
| [Wednesday 14 April 2010] [16:20:19] <sustrik>  sophacles: created new issue for that (no. 18)
| [Wednesday 14 April 2010] [16:20:47] <sustrik>  as for now you'll have to do with manually tweaking the sleep(10) thing :(
| [Wednesday 14 April 2010] [16:23:37] <sophacles>    before anyone spends too much effort on that issue, it is linked against 2.0.6, which is hte current debian packaged version in Adrian's repo. If relevant work has been done since then i can build the latest git repo and try that
| [Wednesday 14 April 2010] [17:43:56] <sophacles>    sustrik: i forgot to mention, thanks for the tip about remote_thr/local_thr w/ big message sizes, they fill the pipe w/out maxin the cpu :)
| [Wednesday 14 April 2010] [18:07:09] <jomofo>   sustrik: do you use Sun JDK or OpenJDK or ... ?  I don't think it matters much, but don't want to introduce more variables than I have to
| [Wednesday 14 April 2010] [18:07:55] <jomofo>   P.S. I kept saying Ubuntu 9.04 earlier, but it is 9.10 which looks like what you're running
| [Thursday 15 April 2010] [01:34:14] <CIA-5> zeromq2: 03Martin Sustrik 07master * rea18d30 10/ (include/zmq.h src/atomic_ptr.hpp): atomic_ptr fix of Win64 - http://bit.ly/aJ8j4j
| [Thursday 15 April 2010] [01:34:15] <CIA-5> zeromq2: 03Martin Sustrik 07master * r1c33941 10/ (9 files in 9 dirs): Merge branch 'master' of git@github.com:sustrik/zeromq2 - http://bit.ly/bQDCHM
| [Thursday 15 April 2010] [01:49:48] <CIA-5> clrzmq: 03Martin Sustrik 07master * r360286b 10/ clrzmq/zmq.cs : zmq_msg_t size if estimated correctly idependent on microarchitecture used - http://bit.ly/bDlyVB
| [Thursday 15 April 2010] [10:42:12] <sophacles> do the latest versions of 0mq compile with -g automatically or something, im suddenly getting glibc backtraces when I blow stuff up.
| [Thursday 15 April 2010] [10:56:08] <sustrik>   hm, doesn't seem to happen here
| [Thursday 15 April 2010] [10:56:09] <sustrik>   /bin/bash ../libtool  --tag=CXX   --mode=compile g++ -DHAVE_CONFIG_H -I.   -Werror -pedantic -Wall -D_GNU_SOURCE -D_REENTRANT -D_THREAD_SAFE   -fPIC -MT libzmq_la-downstream.lo -MD -MP -MF .deps/libzmq_la-downstream.Tpo -c -o libzmq_la-downstream.lo `test -f 'downstream.cpp' || echo './'`downstream.cpp
| [Thursday 15 April 2010] [10:59:33] <sophacles> hmm. must be some wierd debian thing then.
| [Thursday 15 April 2010] [10:59:47] <sophacles> there are definately a lot of those :)
| [Thursday 15 April 2010] [11:02:51] <sustrik>   do you see the -g option when you compile it?
| [Thursday 15 April 2010] [11:10:00] <sophacles> yeah, seems it ends up in CFLAGS in the makefile. Not sure how, but no big deal, i think it's what provided the backtrace i recently posted so net win
| [Thursday 15 April 2010] [11:22:23] <sustrik>   ok, issue reproduced
| [Thursday 15 April 2010] [13:00:44] <mato>  sustrik/sophacles: configure/autotools use -g -O2 with gcc by default
| [Thursday 15 April 2010] [13:01:20] <sustrik>   mato: it doesn't seem to appear in the command line, see above
| [Thursday 15 April 2010] [13:02:15] <mato>  sustrik: that's because that command line is not the real compile command, just some libtool/automake dependency-foo
| [Thursday 15 April 2010] [13:02:26] <sustrik>   aaah
| [Thursday 15 April 2010] [13:02:46] <sustrik>   btw, that makes the binary pretty large, no?
| [Thursday 15 April 2010] [13:02:55] <mato>  yes
| [Thursday 15 April 2010] [13:03:08] <sustrik>   does it affect resident memory footprint?
| [Thursday 15 April 2010] [13:03:25] <mato>  yes
| [Thursday 15 April 2010] [13:03:38] <sustrik>   shouldn't we turn it off then?
| [Thursday 15 April 2010] [13:03:46] <mato>  definitely not by default
| [Thursday 15 April 2010] [13:04:02] <sustrik>   can it be turned off?
| [Thursday 15 April 2010] [13:05:01] <mato>  not right now, we could add a --disable-debug or similar option to configure
| [Thursday 15 April 2010] [13:05:08] <mato>  which would drop the -g
| [Thursday 15 April 2010] [13:05:37] <mato>  also, distribution packagers tend to muck with this
| [Thursday 15 April 2010] [13:06:03] <mato>  so for example on debian you will get libzmq0 which is the library w/o debugging symbols and libzmq-dbg or similar which includes them
| [Thursday 15 April 2010] [13:06:10] <mato>  i'm not sure of the exact details
| [Thursday 15 April 2010] [13:06:39] <sustrik>   what i mean is that we advertise small memory footprint, so we should at least document how to achieve it...
| [Thursday 15 April 2010] [13:07:31] <sustrik>   maybe alongside the instructions for building from git
| [Thursday 15 April 2010] [13:11:50] <mato>  hmm, maybe, i don't want to muck with it right now
| [Thursday 15 April 2010] [13:12:03] <mato>  gets in the way of "real work" :-)
| [Thursday 15 April 2010] [13:14:09] <mato>  sustrik: since you asked:
| [Thursday 15 April 2010] [13:14:15] <mato>  [dezo:.libs]$ ls -l libzmq.so.0.0.0 
| [Thursday 15 April 2010] [13:14:15] <mato>  -rwxr-xr-x 1 mato users 1996994 2010-04-15 19:13 libzmq.so.0.0.0
| [Thursday 15 April 2010] [13:14:24] <mato>  [dezo:.libs]$ strip libzmq.so.0.0.0
| [Thursday 15 April 2010] [13:14:25] <mato>  [dezo:.libs]$ ls -l libzmq.so.0.0.0 
| [Thursday 15 April 2010] [13:14:25] <mato>  -rwxr-xr-x 1 mato users 260880 2010-04-15 19:14 libzmq.so.0.0.0
| [Thursday 15 April 2010] [13:14:34] <mato>  (amd64, w/o pgm)
| [Thursday 15 April 2010] [13:14:47] <sustrik>   that's -g vs. no g?
| [Thursday 15 April 2010] [13:15:04] <mato>  no, that's the same library, then i strip the debugging symbols from it
| [Thursday 15 April 2010] [13:15:19] <sustrik>   size down by 85%
| [Thursday 15 April 2010] [13:15:24] <mato>  yes, of course
| [Thursday 15 April 2010] [13:15:45] <mato>  C++ debugging symbols especially take up a lot of space
| [Thursday 15 April 2010] [13:16:02] <sustrik>   what about a one-line warning alongside the build instructions?
| [Thursday 15 April 2010] [13:16:09] <mato>  what warning?
| [Thursday 15 April 2010] [13:16:14] <mato>  what are you warning about?
| [Thursday 15 April 2010] [13:16:35] <sustrik>   "default build contains debugging symbols and thus can take a lot of space"
| [Thursday 15 April 2010] [13:16:50] <sustrik>   "turn if off if you care"
| [Thursday 15 April 2010] [13:17:33] <mato>  "strip your binaries and libzmq.so if you care"
| [Thursday 15 April 2010] [13:17:40] <sustrik>   right
| [Thursday 15 April 2010] [13:17:54] <mato>  you will get people asking "what is strip" :-)
| [Thursday 15 April 2010] [13:18:04] <mato>  anyway, whatever, feel free
| [Thursday 15 April 2010] [13:19:43] <mato>  the reason it's not the default is if you strip the library/binaries you will not get useful backtraces of any kind
| [Thursday 15 April 2010] [13:19:52] <sustrik>   i know
| [Thursday 15 April 2010] [13:20:23] <sustrik>   i just dont like false advertising: "Is thin. The core requires just a couple of pages in resident memory."
| [Thursday 15 April 2010] [13:20:37] <mato>  it's your advertising :-)
| [Thursday 15 April 2010] [13:20:48] <sustrik>   i've measured it :|
| [Thursday 15 April 2010] [13:20:48] <mato>  260k still != "a couple of pages" :-)
| [Thursday 15 April 2010] [13:21:11] <sustrik>   not all of that seems to go to memory
| [Thursday 15 April 2010] [13:21:31] <sustrik>   there's a lot of linking info afaiu
| [Thursday 15 April 2010] [13:21:45] <mato>  of course
| [Thursday 15 April 2010] [13:21:52] <mato>  there are ways to measure this
| [Thursday 15 April 2010] [13:22:05] <sustrik>   yup
| [Thursday 15 April 2010] [13:22:08] <mato>  you could write a couple of paragraphs and link to them from the "advertisement"
| [Thursday 15 April 2010] [13:22:20] <sustrik>   hm
| [Thursday 15 April 2010] [13:22:33] <sustrik>   seems like work
| [Thursday 15 April 2010] [13:22:37] <sustrik>   :)
| [Thursday 15 April 2010] [13:22:39] <mato>  :-)
| [Thursday 15 April 2010] [13:23:08] <sustrik>   i'll put it on my todo list
| [Thursday 15 April 2010] [13:23:28] <mato>  that's always a good way of resolving "work" :-)
| [Thursday 15 April 2010] [13:24:05] <mato>  anyway, let's wait and see what proposal ph comes up with for the zeromq.org page, he has been promising something
| [Thursday 15 April 2010] [18:31:10] <mikko> a lot of changes going into 2.0.7 which also break bwc in places
| [Thursday 15 April 2010] [18:31:19] <mikko> should it really be 2.1.0 or 3.0.0?
| [Thursday 15 April 2010] [19:00:08] <mato>  mikko: nope, this is why 2.0.6 is still called "Beta"
| [Thursday 15 April 2010] [19:00:29] <mato>  mikko: the "Beta" refers to API/ABI stability rather than code stability.
| [Thursday 15 April 2010] [19:09:03] <mikko> mato: just to check, this is correct format: http://valokuva.org/~mikko/0001-Import-redhat-packaging.patch ?
| [Thursday 15 April 2010] [19:23:36] <mikko> im going to sleep for a while
| [Thursday 15 April 2010] [19:23:38] <mikko> ->
| [Friday 16 April 2010] [03:53:49] <CIA-5>   zeromq2: 03Martin Sustrik 07master * rd524c4e 10/ doc/zmq_setsockopt.txt : fix of documentation typo - http://bit.ly/cawYnX
| [Friday 16 April 2010] [04:21:06] <mato>    mikko: that patch looks good to me, yes
| [Friday 16 April 2010] [04:21:39] <mikko>   mato: is sed -i portable?
| [Friday 16 April 2010] [04:21:43] <mikko>   or is it gnuism
| [Friday 16 April 2010] [04:29:43] <mato>    mikko: the POSIX manpage for sed doesn't mention -i
| [Friday 16 April 2010] [04:29:54] <mikko>   bummer
| [Friday 16 April 2010] [04:30:26] <mikko>   sed .. orig  > f.tmp && cat f.tmp > orig && rm f.tmp i guess
| [Friday 16 April 2010] [04:31:03] <mato>    something like that; i did use RPM packaging on non-Linux systems years ago but i wonder if anyone else does that :)
| [Friday 16 April 2010] [04:33:07] <mikko>   i would think it would be safe to assume gsed for now
| [Friday 16 April 2010] [04:33:30] <mikko>   "there is gnuism in linux build files" kinda makes sense
| [Friday 16 April 2010] [05:37:46] <mikko>   redhat packaging sent to lists
| [Friday 16 April 2010] [05:38:05] <mikko>   let me know if anything else is needed, i got full day of meetings but should be back this evening
| [Friday 16 April 2010] [05:40:06] <mato>    will do, thanks
| [Friday 16 April 2010] [07:17:26] <sjampoo> I know hardly anything about multicast, but zmq makes it so easy to use. Are there any pointers somewhere with more information about multicast?
| [Friday 16 April 2010] [07:17:40] <sjampoo> Specifically recommendations / its limitations? 
| [Friday 16 April 2010] [07:18:45] <sjampoo> I am afraid i'll run into problems when i create lots of multicast channels, but don't know if there is any reason to.
| [Friday 16 April 2010] [07:19:42] <sjampoo> fe, i read somewhere that a NIC can handle 15 addresses fine but will into problems when needing to handle more than 100.
| [Friday 16 April 2010] [07:21:21] <sustrik> sjampoo: multicast is not easy to manage
| [Friday 16 April 2010] [07:21:40] <sustrik> if you don't really need it don't use ti
| [Friday 16 April 2010] [07:21:42] <sustrik> it*
| [Friday 16 April 2010] [07:23:40] <sjampoo> aha, so i really should invest some time in the app logic instead of just dumping it on the network.
| [Friday 16 April 2010] [07:26:11] <sustrik> ok, multicast:
| [Friday 16 April 2010] [07:26:14] <sustrik> 1. only on LAN
| [Friday 16 April 2010] [07:26:35] <sustrik> 2. use it only if your traffic exceeds the capacity of the LAN
| [Friday 16 April 2010] [07:26:53] <sustrik> 3. you need high-end networking harware
| [Friday 16 April 2010] [07:27:12] <sustrik> 4. you can still easily kill your network by overloading it with multicast packets
| [Friday 16 April 2010] [07:28:05] <sustrik> 0mq makes it easy NOT to use multicast, simply use PUB/SUB sockets on top of TCP and what you get is basically multicast semantics
| [Friday 16 April 2010] [07:30:57] <guido_g> for the price of higher system load, one should mention that
| [Friday 16 April 2010] [07:30:57] <sjampoo> I agree with that, but you still need some sort of DS to manage the socket connections, when using multicast you could just dump it on a channel and let the network figure it out. That makes it so tempting.
| [Friday 16 April 2010] [07:31:59] <guido_g> what about something unicast on top of udp? would at least make lots of subscriptions more ressource friendly, wouldn't it?
| [Friday 16 April 2010] [07:37:43] <sjampoo> ill stay away from multicast for now, thanks for the info
| [Friday 16 April 2010] [07:37:50] <sustrik> sjampoo: you can do the same thing with PUB socket, no? Just dump your data to the socket and let 0mq do the work
| [Friday 16 April 2010] [07:37:56] <sustrik> you are welcome
| [Friday 16 April 2010] [07:39:04] <sjampoo> sustrik, well with multicast you could have 2 servers publish to a channel and a single subscriber all without extra logic
| [Friday 16 April 2010] [07:39:17] <sjampoo> In unicast you need to subscribe to the 2 servers
| [Friday 16 April 2010] [07:39:23] <sustrik> ah, multicast bus
| [Friday 16 April 2010] [07:39:47] <sjampoo> yes, thats really tempting
| [Friday 16 April 2010] [07:39:50] <sustrik> consider that that moves a lot of logic to your application
| [Friday 16 April 2010] [07:40:00] <sustrik> who does the message come from?
| [Friday 16 April 2010] [07:40:05] <sustrik> what should i do with it?
| [Friday 16 April 2010] [07:40:32] <sustrik> what if one of the senders fails while i am in the middle of transaction
| [Friday 16 April 2010] [07:40:33] <sustrik> etc.
| [Friday 16 April 2010] [07:42:33] <guido_g> sorry for my ignorance, but the other transports also have issues w/ the probs shown, right?
| [Friday 16 April 2010] [07:43:20] <sjampoo> Doesn't zmq take care of the nasty parts already? 
| [Friday 16 April 2010] [07:44:04] <sustrik> what i meant is that several publishers publishing to the same "group" is almost an antipattern
| [Friday 16 April 2010] [07:44:42] <sustrik> it can be used in some constrained scenarios
| [Friday 16 April 2010] [07:44:46] <sjampoo> i am thinking about distributed logging fe
| [Friday 16 April 2010] [07:45:07] <guido_g> ahh, here the bus semantic is really useful, imho
| [Friday 16 April 2010] [07:45:21] <sustrik> well, then you have just one logger no?
| [Friday 16 April 2010] [07:45:26] <guido_g> no
| [Friday 16 April 2010] [07:45:51] <guido_g> think about specialised clients that do filtering, storing etc.
| [Friday 16 April 2010] [07:46:21] <sjampoo> exactly
| [Friday 16 April 2010] [07:46:28] <guido_g> i.e. one could attach a special looger to the system to find a bug w/o changeing hte behaviour of the system
| [Friday 16 April 2010] [07:48:03] <sustrik> sure, if you don't care about system producing log messages all the time, even when not needed, it should work
| [Friday 16 April 2010] [07:48:57] <guido_g> this is what's recommended anyway
| [Friday 16 April 2010] [07:49:42] <guido_g> most of the larger sites don't have log-levels anymore, when it's true what's published about them
| [Friday 16 April 2010] [07:50:40] <guido_g> infoq.com and highscalability.com do have articels/videos about that topic
| [Friday 16 April 2010] [07:51:04] <sustrik> feel free to post the links on the mailing list
| [Friday 16 April 2010] [07:51:20] <guido_g> ok
| [Friday 16 April 2010] [07:51:43] <guido_g> does posting via gmane work? i'm  reading via gmane
| [Friday 16 April 2010] [07:52:13] <sustrik> no idea, give it a try
| [Friday 16 April 2010] [07:52:19] <guido_g> i'll do
| [Friday 16 April 2010] [09:20:27] <sustrik> guid_g: no lock?
| [Friday 16 April 2010] [09:20:29] <sustrik> luck*
| [Friday 16 April 2010] [09:21:36] <guido_g> sustrik: lock?
| [Friday 16 April 2010] [09:21:51] <guido_g> luck with what?
| [Friday 16 April 2010] [09:22:17] <sustrik> sending the email?
| [Friday 16 April 2010] [09:22:18] <guido_g> if you meen the links, i just came home from work and started the search
| [Friday 16 April 2010] [09:22:28]    * guido_g should type faster :)
| [Friday 16 April 2010] [09:22:45] <sustrik> :)
| [Friday 16 April 2010] [09:23:04] <guido_g> http://delicious.com/guido_g/logging  <- in principle :)
| [Friday 16 April 2010] [09:23:21] <guido_g> but i'll write a wrap-up
| [Friday 16 April 2010] [09:24:03] <sustrik> thanks
| [Friday 16 April 2010] [10:18:55] <guido_g> sustrik: news posting sent
| [Friday 16 April 2010] [10:33:22] <sustrik> nothing arrived yet.. let's wait a while
| [Friday 16 April 2010] [10:33:46] <guido_g> yep, sure
| [Friday 16 April 2010] [10:37:56] <guido_g> btw, we talked about lots of servers, right? this is the current status of _lots_: http://www.intac.net/a-comparison-of-dedicated-servers-by-company_2010-04-13/   :)
| [Friday 16 April 2010] [10:42:31] <sustrik> still, if all the 1M google servers would start logging using multicast :)
| [Friday 16 April 2010] [10:43:00] <guido_g> hmmm...
| [Friday 16 April 2010] [10:43:33] <guido_g> at least, multicast would be much more prominent then
| [Friday 16 April 2010] [11:02:10] <jomofo>  Is something akin to TLS out of scope for 0MQ?   (Just performing thought experiments to better understand the architecture)
| [Friday 16 April 2010] [11:02:54] <sustrik> jomofo: what's the idea?
| [Friday 16 April 2010] [11:05:11] <jomofo>  sustrik: Just thinking for a health care application or something along those lines you might want authentication and encryption on the wire.  Just wondering if it's within the architectural constraints of 0mq to provide a TLS transport, or if this is something you need to do in the application protocol
| [Friday 16 April 2010] [11:05:51] <jomofo>  Not really an enhancement request, per se, but just trying to wrap my head around some of the abstractions
| [Friday 16 April 2010] [11:06:29] <mikko>   the question about TLS seems to come up fairly often
| [Friday 16 April 2010] [11:07:39] <sustrik> yep, but i'm not the right person to ask, i have very little security experience
| [Friday 16 April 2010] [11:07:52] <sustrik> maybe discussing it on list would help?
| [Friday 16 April 2010] [11:08:42] <jomofo>  sure, i'll send something to the list
| [Saturday 17 April 2010] [03:44:54] <guido_g>   just compild 0mq, tried epgm, doesn't work *grml*
| [Saturday 17 April 2010] [03:55:18] <guido_g>   guido@nathan:~/prog/apps/zmq-trunk/perf$ ./local_thr epgm://eth0\;239.1.1.1:5000 800 1000000
| [Saturday 17 April 2010] [03:55:18] <guido_g>   Assertion failed: false (pgm_socket.cpp:130)
| [Saturday 17 April 2010] [03:55:18] <guido_g>   Aborted
| [Saturday 17 April 2010] [03:55:26] <guido_g>   should work, shouldn't it?
| [Saturday 17 April 2010] [04:02:05]      * guido_g stupid
| [Saturday 17 April 2010] [04:02:06] <guido_g>   forgot to set ZMQ_RATE
| [Saturday 17 April 2010] [04:50:45] <sustrik>   guido_g: still, it shouldn't assert
| [Saturday 17 April 2010] [04:51:10] <sustrik>   can you possibly find out what error did OpenPGM returned that caused the assert?
| [Saturday 17 April 2010] [04:52:30] <guido_g>   omg, multicast kills the wifi router :(
| [Saturday 17 April 2010] [04:52:50] <sustrik>   yes, it does :)
| [Saturday 17 April 2010] [04:53:15] <sustrik>   set the rate to very low to keep it alive
| [Saturday 17 April 2010] [04:53:56] <guido_g>   i turned wifi of, now it works
| [Saturday 17 April 2010] [04:54:26] <guido_g>   *sigh*
| [Saturday 17 April 2010] [04:54:35] <guido_g>   the world is not ready for multicast
| [Saturday 17 April 2010] [04:56:20] <guido_g>   guido@nathan:~/prog/apps/zmq-trunk/perf$ ./local_thr epgm://192.168.1.5\;239.1.1.1:5000 500 100000
| [Saturday 17 April 2010] [04:56:20] <guido_g>   receiving first
| [Saturday 17 April 2010] [04:56:21] <guido_g>   received first
| [Saturday 17 April 2010] [04:56:21] <guido_g>   starting
| [Saturday 17 April 2010] [04:56:22] <guido_g>   msg_count: 10000
| [Saturday 17 April 2010] [04:56:24] <guido_g>   msg_count: 20000
| [Saturday 17 April 2010] [04:56:26] <guido_g>   *** glibc detected *** /home/guido/prog/apps/zmq-trunk/perf/.libs/lt-local_thr: malloc(): memory corruption: 0xb7205100 ***
| [Saturday 17 April 2010] [04:56:29] <guido_g>   message of incorrect size received
| [Saturday 17 April 2010] [04:56:31] <guido_g>   ======= Backtrace: =========
| [Saturday 17 April 2010] [04:56:33] <guido_g>   /lib/i686/cmov/libc.so.6[0xb7c7e824]
| [Saturday 17 April 2010] [04:56:37] <guido_g>   /lib/i686/cmov/libc.so.6[0xb7c812cb]
| [Saturday 17 April 2010] [04:56:39] <guido_g>   /lib/i686/cmov/libc.so.6[0xb7c82072]
| [Saturday 17 April 2010] [04:56:41] <guido_g>   /lib/i686/cmov/libc.so.6(__libc_memalign+0x9c)[0xb7c8369c]
| [Saturday 17 April 2010] [04:56:43] <guido_g>   /lib/i686/cmov/libc.so.6(posix_memalign+0x57)[0xb7c838e7]
| [Saturday 17 April 2010] [04:56:45] <guido_g>   /lib/libglib-2.0.so.0[0xb7ba506e]
| [Saturday 17 April 2010] [04:56:47] <guido_g>   /lib/libglib-2.0.so.0(g_slice_alloc+0x663)[0xb7ba6003]
| [Saturday 17 April 2010] [04:56:49] <guido_g>   /lib/libglib-2.0.so.0(g_slist_prepend+0x12)[0xb7ba7202]
| [Saturday 17 April 2010] [04:56:55] <guido_g>   nice one
| [Saturday 17 April 2010] [04:58:57] <sustrik>   looks like OpenPGM bug, 0MQ itself doesn't use glib
| [Saturday 17 April 2010] [04:59:31] <guido_g>   ah thx
| [Saturday 17 April 2010] [05:04:36] <guido_g>   ok, and now for the python bindings...
| [Saturday 17 April 2010] [05:19:03] <guido_g>   yes! success! :)
| [Saturday 17 April 2010] [05:19:27] <guido_g>   message size: 500 [B]
| [Saturday 17 April 2010] [05:19:27] <guido_g>   array count: 100000
| [Saturday 17 April 2010] [05:19:27] <guido_g>   mean throughput: 97087 [msg/s]
| [Saturday 17 April 2010] [05:19:27] <guido_g>   mean throughput: 388.350 [Mb/s]
| [Saturday 17 April 2010] [05:20:43] <sustrik>   :)
| [Saturday 17 April 2010] [05:21:24]      * guido_g is happy
| [Tuesday 20 April 2010] [06:58:26] <sjampoo>    Quick question, zmq_msg_init_data(3) is relatively cheap to call right? 
| [Tuesday 20 April 2010] [06:59:44] <sjampoo>    run in to the following issue, while working with Python bindings and non-copy. I want resend a message received with zmq_recv, but i think i have to reinit that with zmq_msg_init_data to get access to the callback
| [Tuesday 20 April 2010] [07:01:34] <sjampoo>    Because if i just resend the received message again without explicitly closing+reinitiazing it i can run in all sorts of problems.
| [Tuesday 20 April 2010] [07:07:14] <sustrik>    sjampoo: i don't know how pyzmq works
| [Tuesday 20 April 2010] [07:07:21] <sustrik>    however, with raw C API
| [Tuesday 20 April 2010] [07:07:31] <sustrik>    sending a message deinitialises it
| [Tuesday 20 April 2010] [07:07:56] <sustrik>    there's no copy made, existing copy is sent to I/O thread
| [Tuesday 20 April 2010] [07:08:14] <sustrik>    if you want to send the same message to multiple sockets
| [Tuesday 20 April 2010] [07:08:19] <sustrik>    you have to copy it
| [Tuesday 20 April 2010] [07:08:25] <sustrik>    (zmg_msg_copy)
| [Tuesday 20 April 2010] [07:08:39] <sjampoo>    aha
| [Tuesday 20 April 2010] [07:08:48] <sustrik>    note that zmq_msg_copy actually just adds refcount rather than doing deep copy
| [Tuesday 20 April 2010] [07:09:09] <sjampoo>    Yes.
| [Tuesday 20 April 2010] [07:09:36] <sjampoo>    why is the callback function attached to the message and not to the close call? 
| [Tuesday 20 April 2010] [07:13:04] <sustrik>    message is handed to the I/O thread
| [Tuesday 20 April 2010] [07:13:18] <sustrik>    once that's done user cannot access it
| [Tuesday 20 April 2010] [07:13:30] <sustrik>    so he has no way to supply the free function
| [Tuesday 20 April 2010] [07:32:51] <sjampoo>    hmm it makes a little bit more sense now, i never understood the existence of msg_copy and msg_move
| [Tuesday 20 April 2010] [07:33:38] <sjampoo>    So, what do you mean with de-initializes the message on send? What would happen if you would still send the message with the C-api? 
| [Tuesday 20 April 2010] [07:35:43] <sustrik>    it would be empty
| [Tuesday 20 April 2010] [07:35:53] <sustrik>    the whole point is zero-copy
| [Tuesday 20 April 2010] [07:35:59] <sustrik>    message object owns a buffer
| [Tuesday 20 April 2010] [07:36:17] <sustrik>    when you send the message, buffer is passed to the I/O thread
| [Tuesday 20 April 2010] [07:36:34] <sustrik>    message has no buffer any more
| [Tuesday 20 April 2010] [07:39:21] <sjampoo>    Okay, say i'll have a message M1 i will have to copy it to M2 before sending M1 out. Now what does happen if i send M1? 
| [Tuesday 20 April 2010] [07:39:52] <sjampoo>    M2 is just a pointer to M1 I believe with an added ref. count to M1
| [Tuesday 20 April 2010] [07:44:43] <sustrik>    exactly
| [Tuesday 20 April 2010] [07:46:12] <sjampoo>    but then, if i have send M1 out, M2 would point to a deinitialzed message right?
| [Tuesday 20 April 2010] [07:52:08] <sustrik>    actually bith M1 and M2 point to shared buffer
| [Tuesday 20 April 2010] [07:52:46] <sustrik>    ref count is 2
| [Tuesday 20 April 2010] [07:52:50] <sustrik>    then you send M1
| [Tuesday 20 April 2010] [07:53:06] <sustrik>    M1 is deinitialised, but the buffer is passed to I/O thread
| [Tuesday 20 April 2010] [07:53:09] <sustrik>    refcount is still 2
| [Tuesday 20 April 2010] [07:53:40] <sustrik>    when I/O thread sends the message it doesn't need it any more so it decerements the refcount and drops the pointer
| [Tuesday 20 April 2010] [07:53:51] <sustrik>    now the refcount is 1
| [Tuesday 20 April 2010] [07:54:02] <sustrik>    (only M2 points to the buffer)
| [Tuesday 20 April 2010] [08:32:12] <sjampoo>    ok, got it. thanks for the info. 
| [Tuesday 20 April 2010] [09:37:40] <pieter_hintjens>    anyone familiar with MPI or OpenMP?
| [Tuesday 20 April 2010] [09:37:48] <pieter_hintjens>    especially how these compare to 0MQ...
| [Tuesday 20 April 2010] [10:04:07] <sustrik>    pieter: i have a dim idea
| [Tuesday 20 April 2010] [10:11:44] <sophacles>  pieter_hintjens: compare in a numbers/performance sense or compare in a user interface (api) sense?
| [Tuesday 20 April 2010] [10:12:36] <sophacles>  in the case of the latter, 0mq is nicer for pure messaging, but mpi does cool rpc and call balancing stuff for you... it really depends on the use case
| [Tuesday 20 April 2010] [10:14:33] <sophacles>  also mpi has semantics for addressing remote memory a bit easier, so its real nice for distributed matrix multiplies and the like
| [Tuesday 20 April 2010] [10:16:58] <sophacles>  the downside to mpi is that unless you really need the features for parallel computing, it is way too complex.
| [Tuesday 20 April 2010] [10:41:26] <pieter_hintjens>    sophacles: thanks, this is helpful
| [Tuesday 20 April 2010] [10:43:52] <sophacles>  y/w
| [Tuesday 20 April 2010] [12:13:26] <mikko__>    hello
| [Tuesday 20 April 2010] [12:13:38] <sophacles>  oh cool: talk tomorrow titled: Towards Secure Message Systems. ill send the list my notes :) (also if anyone is in the middle of illinois i can send you details)
| [Tuesday 20 April 2010] [12:15:31] <sustrik>    mikko__: hi
| [Tuesday 20 April 2010] [12:15:51] <sustrik>    sophacles: sounds interesting
| [Tuesday 20 April 2010] [12:25:14] <sophacles>  yeah the abstract is a little.. er.. abstrct, so im only 50% on if it actually applies to 0mq but there is also pizza there, so i figured at worst i still get lunch out of it.
| [Wednesday 21 April 2010] [06:22:28] <sjampoo>  awesome, got PyZMQ working without message copying, even with acquiring and releasing the GIL it isn't slower on small messages and about twice as fast on messages larger than 512K
| [Wednesday 21 April 2010] [06:22:57] <sustrik>  sjampoo: is that a patch to pyzmq?
| [Wednesday 21 April 2010] [06:23:03] <sjampoo>  yes
| [Wednesday 21 April 2010] [06:23:20] <sjampoo>  haven't committed it yet. 
| [Wednesday 21 April 2010] [06:23:48] <sjampoo>  I want to have a chat with Brian first changed a few things
| [Wednesday 21 April 2010] [06:24:07] <sustrik>  can it in be made switching from copy to non-copy depending on message size?
| [Wednesday 21 April 2010] [06:24:52] <sjampoo>  I don't see any reason too, it is even faster on smaller messages!
| [Wednesday 21 April 2010] [06:25:04] <sjampoo>  So there hardly seems to be any locking overhead
| [Wednesday 21 April 2010] [06:25:12] <sustrik>  ah, i see
| [Wednesday 21 April 2010] [06:25:32] <sustrik>  anyway, nice work!
| [Wednesday 21 April 2010] [06:26:02] <sjampoo>  it works now with a message object instead of a string
| [Wednesday 21 April 2010] [06:26:12] <sjampoo>  so you could also pass it directly a buffer
| [Wednesday 21 April 2010] [06:26:49] <sustrik>  how does the buffer get deallocated?
| [Wednesday 21 April 2010] [06:26:54] <sjampoo>  I think this will allow for neat stuff such as Tee-ing from a regular TCP socket buffer and than feeding it to ZMQ
| [Wednesday 21 April 2010] [06:27:13] <sjampoo>  I use the callback function to decrease the reference count
| [Wednesday 21 April 2010] [06:27:30] <sjampoo>  (the python ref. count)
| [Wednesday 21 April 2010] [06:27:34] <sustrik>  python refcount?
| [Wednesday 21 April 2010] [06:27:38] <sustrik>  :)
| [Wednesday 21 April 2010] [06:28:11] <sustrik>  doesn't python object about decreasing the ref count from a different thread?
| [Wednesday 21 April 2010] [06:28:16] <sjampoo>  and i artificially increase the python ref. count prior to setting the call back
| [Wednesday 21 April 2010] [06:28:23] <sjampoo>  Well the callback acquires the GIL
| [Wednesday 21 April 2010] [06:28:41] <sjampoo>  (The Python Global Interpreter Lock)
| [Wednesday 21 April 2010] [06:29:07] <sjampoo>  so there only runs one Python Thread at all time
| [Wednesday 21 April 2010] [06:29:58] <sustrik>  the lock is held all the time from invoking send to message being deallocated?
| [Wednesday 21 April 2010] [06:30:51] <sustrik>  ... to free function being called?
| [Wednesday 21 April 2010] [06:30:58] <sjampoo>  the lock gets released on blocking calls
| [Wednesday 21 April 2010] [06:31:09] <sjampoo>  and on calls to zmq_send / zmq_recv etc..
| [Wednesday 21 April 2010] [06:31:52] <sjampoo>  not sure if that answers your question
| [Wednesday 21 April 2010] [06:32:11] <sustrik>  what i meant is 'how long it the lock held'
| [Wednesday 21 April 2010] [06:32:30] <sjampoo>  Oh right you are worrying about me overwriting the buffer right prior to the message being dequeued by ZMQ ? 
| [Wednesday 21 April 2010] [06:32:41] <sustrik>  say if the peer is offline and the message cannot be sent for a prolonged time
| [Wednesday 21 April 2010] [06:33:06] <sustrik>  i meant, what if message stays in a queue for an hour
| [Wednesday 21 April 2010] [06:33:19] <sjampoo>  Then the message object will stay alive
| [Wednesday 21 April 2010] [06:33:25] <sustrik>  does that block all python threads for 1 hour?
| [Wednesday 21 April 2010] [06:33:31] <sjampoo>  No no
| [Wednesday 21 April 2010] [06:37:30] <sjampoo>  Python will just keep on running and doing its stuff in its own separate thread, meanwhile all Python references set by the user might be gone, but Python will not garbage collect it.
| [Wednesday 21 April 2010] [06:37:56] <sjampoo>  the message object itself is immutable
| [Wednesday 21 April 2010] [06:40:27] <sustrik>  great
| [Wednesday 21 April 2010] [06:42:23] <sjampoo>  The only thing that could mess it up is when you have an external blocking call which doesn't release the GIL.
| [Wednesday 21 April 2010] [06:42:48] <sjampoo>  This would of course block the Python thread, but I think it could also block the ZMQ thread as the callback will hang.
| [Wednesday 21 April 2010] [06:47:22] <sustrik>  ack
| [Wednesday 21 April 2010] [06:59:10] <guido_g>  whooo... sounds great!
| [Wednesday 21 April 2010] [11:32:56] <sjampoo>  i've plotted the latency results btw http://nichol.as/wp-content/latency.png
| [Wednesday 21 April 2010] [11:34:27] <guido_g>  looks good
| [Wednesday 21 April 2010] [11:48:31] <sjampoo>  right now i have an api something like this: m = Message('blabla')   
| [Wednesday 21 April 2010] [11:48:37] <sjampoo>  s.send(m)
| [Wednesday 21 April 2010] [11:48:45] <sjampoo>  I wonder if Message is the right name
| [Wednesday 21 April 2010] [11:49:42] <sjampoo>  On the one hand, if you send a message you do not really have it anymore
| [Wednesday 21 April 2010] [11:50:38] <sjampoo>  just as in real life, but it might be a little bit counter intuitive if you come across it for the first time in the object sense
| [Thursday 22 April 2010] [06:06:30] <sjampoo>   Lets say I have multiple servers and i want to simulate the multicast bus, would it make sense to have them discover each other by using multicast and then have all the servers connect to each other?
| [Thursday 22 April 2010] [06:09:09] <sjampoo>   Now, if i also want to have several 'message groups' (in a pub/sub setting) i can set the message filter with setsockopt. But i will have to do this for all the server it subscribes to, right? 
| [Thursday 22 April 2010] [07:48:36] <b0gg1e>    Hello!
| [Thursday 22 April 2010] [07:49:30] <b0gg1e>    Is it possible to transplant a socket pointer between threads?
| [Thursday 22 April 2010] [07:49:56] <b0gg1e>    How does one use zeromq in an actor-like runtime environment where lightweight threads get scheduled to arbitrary threads?
| [Thursday 22 April 2010] [08:06:01] <b0gg1e>    I'm asking this because I wonder what would be the best way to write zmq bindings for the go language.  Go has lightweight processes that get scheduled by the runtime to some thread pool. So one can not easily ensure that the thread that is using a socket is the one that created it.  What I would like to say is: "Use this socket from now on in this thread, I promise to not use it from some other thread concurrently."
| [Thursday 22 April 2010] [09:27:57] <guido_g>   re
| [Thursday 22 April 2010] [11:59:05] <bgranger>  sustrik: hi
| [Friday 23 April 2010] [15:29:34] <sophacles>   Does 0mq have a google summer of code thing?
| [Friday 23 April 2010] [15:31:02] <sophacles>   also, regarding research stuff previously discussed, I was given the greenlight to put some stuff to our students mailing list, but need a bit more in the way of guided ideas for research.
| [Friday 23 April 2010] [15:31:45] <sophacles>   also there may be some other interest but thats waiting on responses to followup emails :)
| [Friday 23 April 2010] [15:32:20] <sophacles>   (i finally cornered some people if you couldn't tell -- i now hate the all-hands meetings slightly less)
| [Friday 23 April 2010] [17:07:04] <jomofo>  are there any known race conditions in zeromq2 HEAD for TCP transport over REQ/REP sockets?  
| [Friday 23 April 2010] [17:08:55] <jomofo>  I have a single-threaded server, multi-threaded client using jzmq ... Can both crash and deadlock JVM pretty consistently against HEAD, but not against 2.0.6 release
| [Saturday 24 April 2010] [16:42:13] <unomystEz> hey all
| [Saturday 24 April 2010] [16:42:41] <unomystEz> anyone here developing ultra high-frequency pipelines with zeromq?
| [Saturday 24 April 2010] [18:20:38] <sustrik>   hi
| [Saturday 24 April 2010] [18:20:49]      * sustrik is back from abroad
| [Saturday 24 April 2010] [18:21:39] <sustrik>   sophacles: the research ideas - sure, i'll put some down tomorrow, however, we'll have to discuss it to make it suitable for students
| [Saturday 24 April 2010] [18:21:46] <sustrik>   no summer of code, sorry
| [Saturday 24 April 2010] [18:21:58] <sustrik>   i've missed the deadline this year :(
| [Saturday 24 April 2010] [18:22:19] <sustrik>   jomofo: please, send the report to the mailing list
| [Saturday 24 April 2010] [18:22:25] <sustrik>   or open an issue at github
| [Saturday 24 April 2010] [18:30:45] <jomofo>    sustrik: I think I will just build on top of 2.0.6 and wait for your next beta/RC before bug testing it ... Problem is, I'm sort of learning the Linux C++ toolchain on the fly here, so I don't want to bother you with issues with my setup
| [Saturday 24 April 2010] [18:31:17] <jomofo>    PS, welcome back. Where did you go?
| [Saturday 24 April 2010] [21:33:05] <unomystEz> hey guys
| [Saturday 24 April 2010] [21:33:49] <unomystEz> anyone know of a good document that describes low-latency networking at the kernel level? ie, packet comes in the NIC, through the driver, in the kernel, etc..
| [Sunday 25 April 2010] [01:39:14] <sustrik> jomofo: ok, it's your call
| [Sunday 25 April 2010] [01:39:26] <sustrik> back from london
| [Sunday 25 April 2010] [01:39:56] <sustrik> mikko__: sorry, it was just a roundtrip, no evening spare for having a beer
| [Sunday 25 April 2010] [01:40:22] <sustrik> unomystEz: it depends on operating system
| [Sunday 25 April 2010] [01:42:01] <sustrik> for Linux there's say "TCP/IP architecture, design and Implementation in Linux" book
| [Sunday 25 April 2010] [01:42:05] <sustrik> etc.
| [Sunday 25 April 2010] [02:26:33] <sustrik> unomystEz: btw, i recall an interesting presentation about Open-MX
| [Sunday 25 April 2010] [02:26:51] <sustrik> not a standard kernel, rather kernel-bypass HPC networking
| [Sunday 25 April 2010] [02:26:52] <sustrik> http://www.cse.scitech.ac.uk/disco/presentations/BriceGoglin.shtml
| [Sunday 25 April 2010] [09:04:41] <CIA-5>   zeromq2: 03Jon Dyte 07master * r7d9603d 10/ devices/zmq_queue/zmq_queue.cpp : Bug in zmq_queue fixed - http://bit.ly/bs03xP
| [Sunday 25 April 2010] [10:07:58] <unomystEz>   sustrik, interesting material
| [Sunday 25 April 2010] [10:08:26] <sustrik> depends on what you are interested in
| [Sunday 25 April 2010] [10:08:43] <sustrik> hacking networking stack in kernel?
| [Sunday 25 April 2010] [10:08:53] <unomystEz>   for now, I'm interested mostly in learning how the current TCP/IP stack is implemented in Linux
| [Sunday 25 April 2010] [10:09:10] <unomystEz>   and what the bottlenecks and scalability issues are
| [Sunday 25 April 2010] [10:09:14] <sustrik> ah, the book i've mentioned is pretty detailed
| [Sunday 25 April 2010] [10:09:17] <unomystEz>   with respect to both throughput and latency
| [Sunday 25 April 2010] [10:09:20] <unomystEz>   nice
| [Sunday 25 April 2010] [10:09:23] <unomystEz>   I"ll have to order it
| [Sunday 25 April 2010] [10:09:31] <sustrik> a bit boring but detailed :)
| [Sunday 25 April 2010] [10:09:48] <sustrik> also, i believe it's about 2.4 kernel
| [Sunday 25 April 2010] [10:10:07] <sustrik> but the NW stack haven't changed that much since
| [Sunday 25 April 2010] [10:10:08] <unomystEz>   im reading 'Professional Linux Architecture' right now
| [Sunday 25 April 2010] [10:10:41] <unomystEz>                                            ^ Kernel
| [Sunday 25 April 2010] [10:10:46] <sustrik> also, the video i've sent the link to is worth viewing
| [Sunday 25 April 2010] [10:10:53] <unomystEz>   im reading the slides now
| [Sunday 25 April 2010] [10:10:53] <sustrik> the guy has heavy french accent
| [Sunday 25 April 2010] [10:10:56] <unomystEz>   haha
| [Sunday 25 April 2010] [10:11:05] <sustrik> but it's rather relevant
| [Sunday 25 April 2010] [10:11:35] <unomystEz>   where are you from?
| [Sunday 25 April 2010] [10:11:39] <sustrik> europe
| [Sunday 25 April 2010] [10:11:42] <sustrik> slovakia
| [Sunday 25 April 2010] [10:11:44] <unomystEz>   nice
| [Sunday 25 April 2010] [10:11:57] <unomystEz>   I'm part slovakian
| [Sunday 25 April 2010] [10:12:01] <unomystEz>   miss the food
| [Sunday 25 April 2010] [10:12:13] <sustrik> ah
| [Sunday 25 April 2010] [10:12:20] <sustrik> where are you based now?
| [Sunday 25 April 2010] [10:12:25] <unomystEz>   NYC
| [Sunday 25 April 2010] [10:12:38] <sustrik> far away
| [Sunday 25 April 2010] [10:12:44] <unomystEz>   yup
| [Sunday 25 April 2010] [10:15:47] <unomystEz>   what are you guys using 0mq for?
| [Sunday 25 April 2010] [10:18:22] <unomystEz>   omg
| [Sunday 25 April 2010] [10:18:28] <unomystEz>   that's the worst french accent I've ever heard
| [Sunday 25 April 2010] [10:26:40] <sustrik> :)
| [Sunday 25 April 2010] [10:26:58] <unomystEz>   im gonna go out and buy that book instead
| [Sunday 25 April 2010] [10:27:04] <unomystEz>   he doesn't explain a lot of the concepts
| [Sunday 25 April 2010] [10:27:08] <unomystEz>   he's basically just commenting on his slides
| [Sunday 25 April 2010] [10:27:24] <sustrik> yeah, but it's more about high-perf
| [Sunday 25 April 2010] [10:27:34] <sustrik> the book is about how the standard stack works
| [Sunday 25 April 2010] [10:27:49] <unomystEz>   true
| [Sunday 25 April 2010] [10:27:55] <sustrik> not sure whether there's relevant literature about high-perf networking
| [Sunday 25 April 2010] [10:28:00] <sustrik> in kernel
| [Sunday 25 April 2010] [10:28:06] <unomystEz>   well, i read the zeromq docs
| [Sunday 25 April 2010] [10:28:08] <sustrik> pretty small niche
| [Sunday 25 April 2010] [10:28:10] <unomystEz>   which were pretty good
| [Sunday 25 April 2010] [10:28:26] <sustrik> a bit messy and uncomplete though
| [Sunday 25 April 2010] [10:28:51] <sustrik> anyway, good resource are hard to be found in the area
| [Sunday 25 April 2010] [19:25:16] <mikko__> sustrik: ah, i guessed you are busy when visiting
| [Monday 26 April 2010] [02:33:13] <sjampoo> Hmm, i'm looking at pub.cpp. Shouldn't the message flushing come before closing all the message objects? What if the ffn callback from zmq_msg_close clears the data? 
| [Monday 26 April 2010] [02:47:34] <sjampoo> Ah got it, please ignore that last question.
| [Monday 26 April 2010] [03:28:01] <sustrik> sjampoo: :)
| [Monday 26 April 2010] [03:44:29] <sjampoo> Hmm if i just send my messages, i do not really need to close them right, as this gets done on a successful send anyway? 
| [Monday 26 April 2010] [04:03:08] <sustrik> sjampoo: now you are speaking of internals of pub_t right?
| [Monday 26 April 2010] [04:03:36] <sustrik> consider this scenario:
| [Monday 26 April 2010] [04:03:47] <sustrik> user sends message with refcount 1
| [Monday 26 April 2010] [04:04:06] <sustrik> pub_t writes it to a pipe
| [Monday 26 April 2010] [04:04:16] <sustrik> leaves the refcount to be 1
| [Monday 26 April 2010] [04:04:54] <sustrik> it ommits close thus not decreasing the refcount
| [Monday 26 April 2010] [04:05:12] <sustrik> and inits user's copy of the message to be blank
| [Monday 26 April 2010] [04:05:29] <sustrik> the refcount of the original message is still 1
| [Monday 26 April 2010] [04:06:16] <sustrik> but nows it refers to the pointer in the pipe rather than pointer in user's zmq_msg_t object
| [Monday 26 April 2010] [04:12:14] <sjampoo> a-ha!
| [Monday 26 April 2010] [04:12:16] <sjampoo> thanks.
| [Monday 26 April 2010] [05:54:18] <sustrik> sjampoo: btw, if you find places like this in the code, where it's not obvious what the code is doing feel free to write a comment explaining the behaviour and submit it as a patch
| [Monday 26 April 2010] [05:54:43] <sustrik> it'll help improve overall quality of the codebase
| [Monday 26 April 2010] [10:51:23] <CIA-5>   zeromq2: 03Martin Sustrik 07master * rbeffee9 10/ (8 files in 3 dirs): P2P renamed to PAIR - http://bit.ly/dCMQhz
| [Monday 26 April 2010] [10:59:04] <CIA-5>   zeromq2: 03Martin Sustrik 07master * r1ad6ade 10/ builds/msvc/libzmq/libzmq.vcproj : MSVC build fixed - http://bit.ly/cLmsJP
| [Monday 26 April 2010] [11:42:09] <CIA-5>   rbzmq: 03Martin Sustrik 07master * r9f1b337 10/ (perf/local_lat.rb rbzmq.cpp): P2P renamed to PAIR - http://bit.ly/bs1QwB
| [Monday 26 April 2010] [11:49:01] <CIA-5>   clrzmq: 03Martin Sustrik 07master * r52a9158 10/ clrzmq/zmq.cs : P2P renamed to PAIR - http://bit.ly/9fOAUO
| [Monday 26 April 2010] [12:17:49] <mikko__> sustrik: there?
| [Monday 26 April 2010] [12:18:14] <sustrik> nikko__: yes, hi
| [Monday 26 April 2010] [12:18:27] <mikko__> http://valokuva.org/~mikko/iothreads/
| [Monday 26 April 2010] [12:18:31] <mikko__> might not be C++ish
| [Monday 26 April 2010] [12:18:50] <mikko__> noticed a TODO item
| [Monday 26 April 2010] [12:19:23] <sustrik> ah, i see
| [Monday 26 April 2010] [12:19:44] <sustrik> the ugly thing about it is that is has to be done at 3 places
| [Monday 26 April 2010] [12:20:25] <mikko__> yeah
| [Monday 26 April 2010] [12:20:32] <sustrik> jon dyte is working on merging all 3 devices into a single executable which would allow for having it at a single place
| [Monday 26 April 2010] [12:20:32] <mikko__> i guess it would be easy to write a macro
| [Monday 26 April 2010] [12:20:34] <mikko__> or something
| [Monday 26 April 2010] [12:20:44] <mikko__> that works as well
| [Monday 26 April 2010] [12:21:22] <sustrik> you may want to synchronise with him
| [Monday 26 April 2010] [12:21:38] <sustrik> he seems busy so we would surely appreciate patches like this one
| [Monday 26 April 2010] [12:21:55] <mikko__> im not sure how you are supposed to cast in C++
| [Monday 26 April 2010] [12:22:01] <sustrik> ()
| [Monday 26 April 2010] [12:22:04] <sustrik> (int) x
| [Monday 26 April 2010] [12:22:08] <mikko__> with const_cast, static_cast and reinterpret_cast
| [Monday 26 April 2010] [12:22:24] <sustrik> well, you mostly don't need those
| [Monday 26 April 2010] [12:22:36] <mikko__> was reading about casts last night in C++
| [Monday 26 April 2010] [12:22:43] <mikko__> seems a lot more confusing than C :)
| [Monday 26 April 2010] [12:22:49] <sustrik> they are useful only for casting types with virtual function tables
| [Monday 26 April 2010] [12:23:05] <sustrik> ah, not so for const_cast 
| [Monday 26 April 2010] [12:23:43] <sustrik> anyway, I would stick to (int) x
| [Monday 26 April 2010] [12:24:38] <mikko__> you can cast const char * with (int) ?
| [Monday 26 April 2010] [12:24:48] <sustrik> i mean (type) x
| [Monday 26 April 2010] [12:25:10] <sustrik> braces syntax
| [Monday 26 April 2010] [12:25:13] <mikko__> const char *foo = "123412423"; int x = (int) foo; ?
| [Monday 26 April 2010] [12:25:42] <sustrik> you'll get numeric representation of the pointer to the string :)
| [Monday 26 April 2010] [12:26:01] <mikko__> yeah, that's what i expected
| [Monday 26 April 2010] [12:26:22] <sustrik> atoi is OK
| [Monday 26 April 2010] [12:26:42] <sustrik> anyway, to give you some context
| [Monday 26 April 2010] [12:27:00] <sustrik> the xml files for devices should define a lot of properties
| [Monday 26 April 2010] [12:27:11] <sustrik> aside of io_threads, it's all the socket options
| [Monday 26 April 2010] [12:27:39] <sustrik> so the code will be rather long
| [Monday 26 April 2010] [12:27:50] <sustrik> thus having it 3x in the codebase seems to be a bad idea
| [Monday 26 April 2010] [12:28:05] <sustrik> that's why I would prefer to have devices merged first
| [Monday 26 April 2010] [12:28:19] <sustrik> then add the property-managing code
| [Monday 26 April 2010] [13:01:42] <impl>    mikko__: you should use intptr_t for that though
| [Monday 26 April 2010] [13:04:48] <sustrik> impl: i think this is only a theoretical discussion, no need for that kind of thing in the code
| [Monday 26 April 2010] [13:05:02] <impl>    ah
| [Monday 26 April 2010] [13:09:26] <mikko__> impl: i'm not storing a pointer 
| [Monday 26 April 2010] [13:09:36] <mikko__> just casting const char * to integer
| [Monday 26 April 2010] [13:09:59] <mikko__> or i was wondering how do you cast that in C++
| [Monday 26 April 2010] [13:10:03] <mikko__> if there was some magic
| [Monday 26 April 2010] [17:02:45] <ADruz>   Can zeromq serve as a job queue system?
| [Monday 26 April 2010] [17:03:45] <mikko__> not really without added application logic
| [Monday 26 April 2010] [17:04:42] <mikko__> take a look at gearman or citrine scheduler if you want job queue / scheduling functionality
| [Monday 26 April 2010] [20:37:18] <ADruz>   mikko__: thanks
| [Monday 26 April 2010] [21:12:56] <mike8901>    How should I go about determining the proper value of io_threads?
| [Monday 26 April 2010] [21:47:57] <mike8901>    Is there any way to have multiple clients connect to a single TCP port(but be represented by multiple unicast sockets) with zmq?
| [Tuesday 27 April 2010] [00:31:14] <rmancy> Is this the best place to ask for help with my zeromq app?
| [Tuesday 27 April 2010] [00:31:58] <mike8901>   I guess so.
| [Tuesday 27 April 2010] [00:35:04] <rmancy> ok great :-) I'm trying to make a simple server/client with ZMQ_REP/ZMQ_REQ respectively. The server does the recv(), then send() seemingly fine, however my client after doing it's initial send() to server (which the server gets), it sits there waiting for recv(). Is REP and REQ appropriate here ? 
| [Tuesday 27 April 2010] [00:36:03] <guido_g>    yes, what did you expect?
| [Tuesday 27 April 2010] [00:37:09] <rmancy> guido_g, Well I'm expecting the client to actually recv the data that server sends back...however it doesn't seem to receive it. Just seems to sit there _waiting_ to receive something, but doesn't actually receive it
| [Tuesday 27 April 2010] [00:37:26] <rmancy> Have I missed something ?
| [Tuesday 27 April 2010] [00:37:42] <guido_g>    w/o seeing the code, hard to tell
| [Tuesday 27 April 2010] [00:38:06] <guido_g>    is there a packet filter in the way?
| [Tuesday 27 April 2010] [00:38:12] <guido_g>    aka firewall
| [Tuesday 27 April 2010] [00:38:19] <rmancy> guido_g, hmmmm.
| [Tuesday 27 April 2010] [00:38:23] <rmancy> will check
| [Tuesday 27 April 2010] [00:41:16] <rmancy> guido_g, nope
| [Tuesday 27 April 2010] [00:42:03] <rmancy> I'm running zmq_forwarder with a basic 'in' and 'out' elements that obviously work on the initial send, just not on the response it seems
| [Tuesday 27 April 2010] [00:42:06] <guido_g>    did you compare your code against the cookbok example?
| [Tuesday 27 April 2010] [00:42:25] <guido_g>    ouch
| [Tuesday 27 April 2010] [00:43:02] <guido_g>    as far as I understood, req/rep is meant for direct connection between the requesting client and the services
| [Tuesday 27 April 2010] [00:43:39] <rmancy> guido_g, oh ok. So no forwarder? I had used the forwarder from a SUB/PUB example, and just assumed I still needed it. Perhaps not though !
| [Tuesday 27 April 2010] [00:44:08] <guido_g>    not only perhaps
| [Tuesday 27 April 2010] [00:44:12] <guido_g>    see http://www.zeromq.org/docs:cookbook
| [Tuesday 27 April 2010] [00:44:37] <guido_g>    a forwarder spreads out the messages to all subscribed entities
| [Tuesday 27 April 2010] [00:44:45] <guido_g>    req/rep works differently
| [Tuesday 27 April 2010] [00:51:03] <rmancy> guido_g, thanks. Didn't realise :-( 
| [Tuesday 27 April 2010] [00:51:46] <rmancy> I'm also not using 'localhost' and 'lo' as I get errors creating sockets on those. Using my public IP instead, but I don't think that should have a bearing
| [Tuesday 27 April 2010] [00:52:11] <rmancy> or possible it does
| [Tuesday 27 April 2010] [00:52:16] <guido_g>    try 127.0.0.1, might be a naming issue
| [Tuesday 27 April 2010] [00:57:44] <guido_g>    i'm off, laters
| [Tuesday 27 April 2010] [00:58:02] <rmancy> guido_g, thanks, with that help i should be able to nut it out :-)
| [Tuesday 27 April 2010] [02:58:13] <guido_g>    re
| [Tuesday 27 April 2010] [08:20:06] <rmancy> Hi, anyone able to help with a simple zeromq prob I have ?
| [Tuesday 27 April 2010] [08:55:32] <sustrik>    rmancy: hi
| [Tuesday 27 April 2010] [08:55:38] <sustrik>    what's the problem?
| [Tuesday 27 April 2010] [10:59:56] <ka3ak>  hello
| [Tuesday 27 April 2010] [11:00:10] <ka3ak>  can someone help me out with a zmq issue
| [Tuesday 27 April 2010] [11:00:41] <sustrik>    ka3ak: hello
| [Tuesday 27 April 2010] [11:00:51] <ka3ak>  hi
| [Tuesday 27 April 2010] [11:01:05] <sustrik>    what's the problem?
| [Tuesday 27 April 2010] [11:01:36] <ka3ak>  i have a simple server set up with a ZMQ_REP socket ...
| [Tuesday 27 April 2010] [11:01:56] <ka3ak>  once in a while the recv will hang
| [Tuesday 27 April 2010] [11:02:31] <ka3ak>  the client send an enourmous amount of messages, so i'm not sure if the queue is getting backed up or what
| [Tuesday 27 April 2010] [11:02:42] <sustrik>    nope
| [Tuesday 27 April 2010] [11:02:48] <sustrik>    looks like a bug
| [Tuesday 27 April 2010] [11:02:51] <ka3ak>  i've tried increasing the high water mark and swap, but nothing works
| [Tuesday 27 April 2010] [11:03:06] <sustrik>    can you send the test program to the mailing list?
| [Tuesday 27 April 2010] [11:03:19] <sustrik>    or open an issue in a bug tracker?
| [Tuesday 27 April 2010] [11:03:30] <ka3ak>  sure
| [Tuesday 27 April 2010] [11:03:33] <sustrik>    thx
| [Tuesday 27 April 2010] [11:03:43] <ka3ak>  just to give you a bit more info on the hack to get around this ...
| [Tuesday 27 April 2010] [11:04:28] <ka3ak>  while (1) { message_t req; if (!sock_.recv(&req, ZMQ_NONBLOCK)) continue; }    but this will spike up the cpu to 100 for a second or so for obvious reasons
| [Tuesday 27 April 2010] [11:05:06] <ka3ak>  but this fixes the problem albeit with a short pause and cpu spike on the server side of things
| [Tuesday 27 April 2010] [11:05:34] <sustrik>    ok, i see
| [Tuesday 27 April 2010] [11:36:02] <CIA-15> zeromq2: 03Martin Sustrik 07master * rad6fa9d 10/ (src/rep.cpp src/req.cpp src/xrep.cpp src/xrep.hpp): initial version of multi-hop REQ/REP - http://bit.ly/cbReUI
| [Tuesday 27 April 2010] [15:38:34] <mike8901>   If I send a message, and the message gets deallocated immediately after I send the message, will the message still go through OK?
| [Tuesday 27 April 2010] [15:38:54] <mike8901>   i.e. will send copy the message?
| [Tuesday 27 April 2010] [15:45:58] <sustrik>    mike8901: it won't copy the message, it will take possession of it
| [Tuesday 27 April 2010] [15:46:11] <sustrik>    there's nothing left for you to deallocate
| [Tuesday 27 April 2010] [15:53:19] <mike8901>   so I can allocate a message_t on the stack, copy the data into the message, and send it, without worrying about what happens to the data?
| [Tuesday 27 April 2010] [16:00:53] <sustrik>    yes
| [Tuesday 27 April 2010] [16:04:02] <mike8901>   ok, cool :)
| [Tuesday 27 April 2010] [17:40:54] <bgranger>   sustrik:  I am going to be working on the Python bindings some more and have a few questions about release schedules...
| [Tuesday 27 April 2010] [18:20:07] <CIA-15> pyzmq: 03Brian E. Granger 07master * r506679b 10/ (6 files in 4 dirs): Renaming P2P -> PAIR. - http://bit.ly/9MC0TY
| [Tuesday 27 April 2010] [18:22:02] <CIA-15> pyzmq: 03Brian E. Granger 07master * r5177246 10/ (5 files in 2 dirs): Finish renaming of P2P -> PAIR in filenames. - http://bit.ly/92CZZQ
| [Tuesday 27 April 2010] [18:36:39] <CIA-15> pyzmq: 03Brian E. Granger 07master * rbb7c339 10/ (zmq/_zmq.c zmq/_zmq.pyx zmq/tests/test_poll.py): Removed stopwatch stuff and fixed select. - http://bit.ly/9GT4M8
| [Tuesday 27 April 2010] [18:39:53] <CIA-15> pyzmq: 03Brian E. Granger 07master * r16b0c20 10/ setup.py : Adding zmq.tests to setup.py packages. - http://bit.ly/ceobEw
| [Tuesday 27 April 2010] [19:26:10] <mikko__>    sustrik: hi
| [Tuesday 27 April 2010] [19:26:20] <mikko__>    http://pastie.org/938296
| [Tuesday 27 April 2010] [19:26:28] <mikko__>    ending up to this with git HEAD
| [Tuesday 27 April 2010] [19:31:30] <mikko__>    ah
| [Tuesday 27 April 2010] [19:31:32] <mikko__>    my mistake
| [Tuesday 27 April 2010] [20:28:20] <mike8901>   Is it possible to do a read and a write simultaneously to a socket without breaking anything?
| [Tuesday 27 April 2010] [20:31:16] <mike8901>   I am doing nonblocking reads, if that makes any difference.
| [Tuesday 27 April 2010] [22:00:38] <CIA-15> pyzmq: 03Brian E. Granger 07master * rb0352c8 10/ (zmq/_zmq.c zmq/_zmq.pyx): 
| [Tuesday 27 April 2010] [22:00:39] <CIA-15> pyzmq: Fixing ctypedef of int64_t.
| [Tuesday 27 April 2010] [22:00:39] <CIA-15> pyzmq: Thanks to Lisandro Dalcin for the tip. - http://bit.ly/9ReFJF
| [Tuesday 27 April 2010] [22:03:26] <CIA-15> pyzmq: 03Fernando Perez 07master * r811389d 10/ (examples/pubsub/topics_pub.py examples/pubsub/topics_sub.py): New example for publish/subscribe sockets with multiple topics. - http://bit.ly/9nMYsJ
| [Tuesday 27 April 2010] [22:12:32] <rmancy> Hi, does anyone know of a c++ example using ZMQ_REP ?
| [Tuesday 27 April 2010] [22:13:47] <rmancy> I was able to get the ZMQ_REP/ZMQ_REQ example using C/C++ fine, but looking for a C++ example using ZMQ_REP so I can find out what I'm doing wrong
| [Tuesday 27 April 2010] [22:31:07] <mike8901>   What's the best way to have a vector of zmq::socket_t's? Just have pointers to the vectors?
| [Tuesday 27 April 2010] [22:31:11] <mike8901>   **pointers to the sockets
| [Tuesday 27 April 2010] [22:31:15] <mike8901>   (or smart pointers)
| [Tuesday 27 April 2010] [23:47:01] <CIA-15> pyzmq: 03Brian E. Granger 07master * r792a621 10/ (zmq/_zmq.c zmq/_zmq.pyx): Added support for getsockopt and multipart messages. - http://bit.ly/cgZOqv
| [Wednesday 28 April 2010] [01:42:31] <sustrik>  re
| [Wednesday 28 April 2010] [01:43:38] <sustrik>  mike8901: simultaneous read & write? each socket can be used only from a single thread
| [Wednesday 28 April 2010] [01:43:49] <mike8901> okay
| [Wednesday 28 April 2010] [01:53:12] <sustrik>  mike8901: as for storing zmq::socket_t's in vector
| [Wednesday 28 April 2010] [01:53:25] <sustrik>  they actually _are_ smart pointers
| [Wednesday 28 April 2010] [01:53:46] <sustrik>  they cannot be stored in a vector because they are not assignable
| [Wednesday 28 April 2010] [01:54:06] <sustrik>  i.e. they have no copy constructor and assignment operator
| [Wednesday 28 April 2010] [01:54:20] <mike8901> yes, I figured that out
| [Wednesday 28 April 2010] [01:54:26] <sustrik>  if you add those two, i'll accept the patch to c++ binding
| [Wednesday 28 April 2010] [01:55:17] <mike8901> from my understanding, smart pointers aren't _SUPPOSED_ to be stored in a vector
| [Wednesday 28 April 2010] [01:55:32] <sustrik>  what you can do is add reference count
| [Wednesday 28 April 2010] [01:55:48] <sustrik>  so when socket_t is copied reference count increases by 1
| [Wednesday 28 April 2010] [01:55:51] <mike8901> that's not my main concern
| [Wednesday 28 April 2010] [01:56:09] <mike8901> I ended up just storing pointers to zmq::socket_t's in the vector
| [Wednesday 28 April 2010] [01:56:25] <sustrik>  yes, can be done that way as well
| [Wednesday 28 April 2010] [01:56:57] <sustrik>  although you have to delete them manually afterwards
| [Wednesday 28 April 2010] [01:57:05] <mike8901> yes, of course
| [Wednesday 28 April 2010] [01:57:23] <mike8901> C++ would be so much nicer if it had -retain and -release like Obj-C
| [Wednesday 28 April 2010] [01:57:39] <sustrik>  that's what refcounting can do
| [Wednesday 28 April 2010] [01:57:52] <mike8901> yeah, it would be nice if refcounting was builtin
| [Wednesday 28 April 2010] [01:58:44] <mike8901> btw, are there any plans to make zeromq BSD/MIT licensed?
| [Wednesday 28 April 2010] [01:58:44] <sustrik>  well, it can at least be done for socket_t
| [Wednesday 28 April 2010] [01:59:29] <sustrik>  in theory, once it's established enough to make sure that contributions are flowing back to the project automatically
| [Wednesday 28 April 2010] [01:59:50] <sustrik>  at the present the fear is that people would patch it and don't contribute back
| [Wednesday 28 April 2010] [02:00:12] <sustrik>  why do you need that?
| [Wednesday 28 April 2010] [02:00:15] <mike8901> I'm currently using zeromq for a project with clang(basically implementing distcc at a layer tightly coupled with the compiler)
| [Wednesday 28 April 2010] [02:00:35] <mike8901> I'm using zeromq because it's easy to use and I'm running up against a tight deadline
| [Wednesday 28 April 2010] [02:00:38] <mike8901> (plus it's fast)
| [Wednesday 28 April 2010] [02:00:50] <mike8901> but clang won't accept my patch if it uses an LGPL library
| [Wednesday 28 April 2010] [02:00:54] <mike8901> everything has to be BSD licensed
| [Wednesday 28 April 2010] [02:01:09] <sustrik>  static linking?
| [Wednesday 28 April 2010] [02:01:20] <mike8901> I think they won't even allow dynamic linking
| [Wednesday 28 April 2010] [02:01:28] <mike8901> (I'm dynamically linking now)
| [Wednesday 28 April 2010] [02:01:35] <mike8901> basically, their policy is BSD only
| [Wednesday 28 April 2010] [02:01:42] <sustrik>  there's a clause explicitly allowing for static linking in 0mq license text
| [Wednesday 28 April 2010] [02:02:00] <sustrik>  anyway, if it's their policy, there's little to do at the moment
| [Wednesday 28 April 2010] [02:02:31] <sustrik>  you'll have to keep the patch out of the tree
| [Wednesday 28 April 2010] [02:02:35] <mike8901> ok, I guess I'll stick with zmq now, and hopefully by the time to patch back to mainline comes, zmq will be licensed for the process :)
| [Wednesday 28 April 2010] [02:02:50] <mike8901> *licensed using BSD
| [Wednesday 28 April 2010] [02:03:50] <sustrik>  hm, btw, what good is messaging layer in a compiler?
| [Wednesday 28 April 2010] [02:05:45] <rmancy_>  I'm sure this is a silly Q. Can I make zmq libs from the git repo? I checked it out the other day, but didn't have much luck.
| [Wednesday 28 April 2010] [02:06:16] <sustrik>  rmancy_: what went wrong?
| [Wednesday 28 April 2010] [02:06:59] <rmancy_>  sustrik, first off I'm not too ofey with C Makefiles. It's Been a while. Well there didn't seem to be a configure script, so I just did autoconfigure. Is this right ?
| [Wednesday 28 April 2010] [02:07:13] <sustrik>  yes
| [Wednesday 28 April 2010] [02:07:23] <sustrik>  the script is generated so it's not stored in git
| [Wednesday 28 April 2010] [02:07:38] <sustrik>  ./autogen.sh
| [Wednesday 28 April 2010] [02:07:43] <sustrik>  ./configure
| [Wednesday 28 April 2010] [02:07:47] <sustrik>  make
| [Wednesday 28 April 2010] [02:08:24] <rmancy_>  sustrik, excellent. Thanks so much. 
| [Wednesday 28 April 2010] [02:08:32] <sustrik>  np
| [Wednesday 28 April 2010] [02:31:44] <rmancy_>  sustrik, I've been having a problem with a very simple ZMQ_REP/ZMQ_REQ app. Can you recommend a good ZMQ_REP example in c++ (I just converted the Server example from the 0mq site that was in C) ?
| [Wednesday 28 April 2010] [02:32:22] <sustrik>  what was the problem?
| [Wednesday 28 April 2010] [02:33:22] <rmancy_>  Well, the ZMQ_REP (server) gets the recv() and then _appears_ to send(), but the ZMQ_REQ (client) does not get the response. the client code works fine with the example written in C.
| [Wednesday 28 April 2010] [02:34:29] <sustrik>  send the test program to the mailing list
| [Wednesday 28 April 2010] [02:37:29] <rmancy_>  sustrik, ok cheers. I'm sure it's an obvious problem to most other people. I'm brand new to C++ and it's been over 4 years since I've even done C.
| [Wednesday 28 April 2010] [03:02:13] <mike8901> sustrik: I'm building a distributed compiler
| [Wednesday 28 April 2010] [03:02:37] <mike8901> similar to distcc, but much more efficient
| [Wednesday 28 April 2010] [03:10:46] <sustrik>  aha, interesting
| [Wednesday 28 April 2010] [03:10:58] <sustrik>  the point is make it compile faster?
| [Wednesday 28 April 2010] [03:12:34] <sustrik>  by running compilation of several machines at the same time?
| [Wednesday 28 April 2010] [09:46:56] <b0gg1e>   Hi
| [Wednesday 28 April 2010] [09:47:38] <b0gg1e>   I pushed some very early bindings for zeromq to go on github http://github.com/boggle/gozero
| [Wednesday 28 April 2010] [09:49:25] <b0gg1e>   Currently barely works there seems to happen some weirdness between go's scheduler and zmq which I havent managed to understand yet, anyways feel free to peek or help
| [Wednesday 28 April 2010] [09:52:50] <sustrik>  b0ggle: great, thanks
| [Wednesday 28 April 2010] [09:53:10] <sustrik>  do you want to be referenced from zeromq.org website?
| [Wednesday 28 April 2010] [09:59:26] <b0gg1e>   its not actually usable right now, so that doesnt seem apropriate
| [Wednesday 28 April 2010] [10:00:27] <sustrik>  well, at least people would know about it
| [Wednesday 28 April 2010] [10:00:31] <b0gg1e>   more looking for help actually and am a bit lost whom to ask.. go people or zeromq people :-)
| [Wednesday 28 April 2010] [10:00:44] <sustrik>  you can place a big "EXPERIMENTAL" tag on the top of the page
| [Wednesday 28 April 2010] [10:01:19] <b0gg1e>   more like (BROKEN, NEEDS HELP)
| [Wednesday 28 April 2010] [10:01:28] <sustrik>  yes, sure
| [Wednesday 28 April 2010] [10:01:31] <b0gg1e>   ill do that on github
| [Wednesday 28 April 2010] [10:01:38] <sustrik>  as you wish
| [Wednesday 28 April 2010] [10:01:54] <b0gg1e>   maybe put a Go (EXPERIMENTAL) on the page if you like to
| [Wednesday 28 April 2010] [10:02:03] <sustrik>  sure
| [Wednesday 28 April 2010] [10:02:11] <sustrik>  do you want a wiki page on zeromq.org?
| [Wednesday 28 April 2010] [10:02:26] <sustrik>  or should i link to your page somewhere?
| [Wednesday 28 April 2010] [10:04:14] <b0gg1e>   A wiki page on zeromq.org would be nice
| [Wednesday 28 April 2010] [10:04:40] <sustrik>  ok, do this: open www.zeromq.org and create an account (top right of the page)
| [Wednesday 28 April 2010] [10:05:01] <sustrik>  let me know your login then and i'll give you write access
| [Wednesday 28 April 2010] [10:09:18] <b0gg1e>   recovering wikidot account...
| [Wednesday 28 April 2010] [10:29:48] <b0gg1e>   account name is "splant"
| [Wednesday 28 April 2010] [10:31:13] <sustrik>  ok, you are invited
| [Wednesday 28 April 2010] [10:31:20] <sustrik>  i've created http://www.zeromq.org/bindings:go
| [Wednesday 28 April 2010] [10:31:45] <sustrik>  put the python binding wiki page content there to give you some template
| [Wednesday 28 April 2010] [10:31:55] <sustrik>  feel free to edit it as you see fit
| [Wednesday 28 April 2010] [10:32:21] <sustrik>  b0ggle: let me know when it's ready to be linked from the front page
| [Wednesday 28 April 2010] [10:38:36] <b0gg1e>   k thanks might take a while... the go folks are changing their gc and i might sit this out unless i have a good fast idea on how to fix things
| [Wednesday 28 April 2010] [10:39:06] <sustrik>  b0ggle: sure, it's up to you
| [Wednesday 28 April 2010] [10:41:43] <b0gg1e>   i cant edit the page / dont see an edit link
| [Wednesday 28 April 2010] [11:22:36] <sustrik>  b0ggle: have you accepted the invitation?
| [Wednesday 28 April 2010] [11:25:00] <sustrik>  it doesn't look so, i don't see you among members
| [Wednesday 28 April 2010] [11:29:09] <b0gg1e>   ah
| [Wednesday 28 April 2010] [11:29:10] <b0gg1e>   :-)
| [Wednesday 28 April 2010] [11:29:46] <b0gg1e>   can edit now, thanks
| [Wednesday 28 April 2010] [11:32:36] <sustrik>  :)
| [Wednesday 28 April 2010] [11:59:10] <b0gg1e>   contexts are bound to the thread in which they are created.  is it possible to relax that to "contexts should only ever be used from a single thread at atime"?
| [Wednesday 28 April 2010] [11:59:52] <b0gg1e>   systems like erlang/go etc schedule lightweight processes on thread pools meaning the executing thread can change underneath you stackframe
| [Wednesday 28 April 2010] [12:06:10] <sustrik>  b0ggle: no, context are thread-safe and can be used from any thread
| [Wednesday 28 April 2010] [12:06:23] <sustrik>  the restricvtion you are speaking about applies to sockets
| [Wednesday 28 April 2010] [12:07:03] <sustrik>  and if you meant sockets, then no, it cannot be relaxed
| [Wednesday 28 April 2010] [12:07:16] <b0gg1e>   ah i ment sockets sure
| [Wednesday 28 April 2010] [12:08:24] <b0gg1e>   hm guess that has to do with the lock-free algos.  too bad, now i have to find out why go's LockOSThread isnt working ;-(
| [Wednesday 28 April 2010] [12:08:39] <b0gg1e>   or what else is blocking.
| [Wednesday 28 April 2010] [12:09:02] <sustrik>  yes, it's about lock-free queues
| [Wednesday 28 April 2010] [12:12:02] <b0gg1e>   that also means one cannot move contexts between threads which might also be nice for loadbalancing purposes
| [Wednesday 28 April 2010] [13:05:33] <mike8901> sustrik: Yup, the idea is to preproc on the master, do everything through object code generation on slave, and link together on master.
| [Wednesday 28 April 2010] [13:07:52] <mike8901> (in a much more efficient manner than distcc)
| [Wednesday 28 April 2010] [14:00:13] <CIA-15>   pyzmq: 03Brian E. Granger 07master * r1ffcf0e 10/ (zmq/_zmq.c zmq/_zmq.pyx): Removing SUBSCRIBE/UNSUBSCRIBE from the options in getsockopt. - http://bit.ly/cmNMa4
| [Wednesday 28 April 2010] [15:28:51] <sustrik>  mike8901: aha, looks like good match for 0mq; pitty there's the licensing problem
| [Wednesday 28 April 2010] [16:26:10] <CIA-15>   pyzmq: 03Brian E. Granger 07master * r7a9d487 10/ (zmq/_zmq.c zmq/_zmq.pyx zmq/zmq_compat.h): 
| [Wednesday 28 April 2010] [16:26:10] <CIA-15>   pyzmq: Created zmq_compat.h for a compatibility header file.
| [Wednesday 28 April 2010] [16:26:10] <CIA-15>   pyzmq: This will hopefully fix the int64_t issue. - http://bit.ly/91UClL
| [Wednesday 28 April 2010] [16:43:20] <mike8901> sustrik: yeah, zmq has worked out pretty nicely so far... you're welcome to follow along at http://github.com/jhoush/dist-clang
| [Wednesday 28 April 2010] [16:43:55] <mike8901> comments on (mis-)use of zeromq are greatly appriciated... there are probably some ways to use it better
| [Wednesday 28 April 2010] [16:44:32] <mike8901> right now, we're just doing basic point-to-point communication between nodes
| [Wednesday 28 April 2010] [16:45:25] <mike8901> it might be better to do a multicast setup so work-stealing can be done without rebroadcasting the data(i.e. slaves maintain a cache of files sent out to other slaves so they can steal work from another slave without asking for the data to be sent out again)
| [Wednesday 28 April 2010] [16:46:23] <mike8901> It's a shame we have a deadline in 2.5 weeks, so we're basocally racing to finish this, and can't do too many interesting optimizations
| [Wednesday 28 April 2010] [16:46:27] <mike8901> *basically
| [Wednesday 28 April 2010] [16:51:30] <CIA-15>   pyzmq: 03Brian E. Granger 07master * r6ff6da2 10/ README.rst : Edits to the README.rst. - http://bit.ly/dmPyGi
| [Wednesday 28 April 2010] [17:27:29] <mike8901> sustrik: I ran into an issue where error_t was being defined by one(I don't know which) of the headers included... I had to #undef error_t to use zmq.hpp.
| [Wednesday 28 April 2010] [17:27:35] <mike8901> Is that a known issue?
| [Wednesday 28 April 2010] [17:42:20] <bgranger> sustrik: I am trying out the XREP/XREQ support that you added yesterday
| [Thursday 29 April 2010] [01:34:52] <sustrik>   mike8901: no
| [Thursday 29 April 2010] [01:35:07] <sustrik>   can you check out where's the other error_t included?
| [Thursday 29 April 2010] [01:35:13] <sustrik>   defined*
| [Thursday 29 April 2010] [01:38:40] <sustrik>   if it was a type, it wouldn't be a problem - 0MQ error_t is defined within namespace zmq - the define is worse
| [Thursday 29 April 2010] [01:39:14] <sustrik>   bgranger: it's almost untested
| [Thursday 29 April 2010] [01:39:20] <sustrik>   any problems with it?
| [Thursday 29 April 2010] [05:36:10] <CIA-15>    zeromq2: 03Steven McCoy 07master * r7cb076e 10/ (3 files): Defer NetBSD atomic ops to GCC builtins. Revert Sun atomic ops #define. - http://bit.ly/bJ10EV
| [Thursday 29 April 2010] [05:59:30] Notice  -NickServ- This nickname is registered. Please choose a different nickname, or identify via /msg NickServ identify <password>.
| [Thursday 29 April 2010] [05:59:30] Notice  -NickServ- You are now identified for travlr.
| [Thursday 29 April 2010] [05:59:31] CTCP    Received Version request from frigg.
| [Thursday 29 April 2010] [05:59:33] Notice  -ChanServ- [#qt-labs] Welcome to the Qt developers public hideout. Qt Development Frameworks personnel will have Voice status, so they should be easy to pinpoint in the crowd. Please do not paste large blocks of code in the channel, but rather use a pastebin site.
| [Thursday 29 April 2010] [05:59:33] Notice  -ChanServ- [#rekonq] welcome to rekonq, webkit KDE browser, channel
| [Thursday 29 April 2010] [05:59:33] Notice  -ChanServ- [#qt] Here are the rules for #qt: (1) Don't just join, ask, and quit - stay around and answer questions yourself! (2) Be patient, people may not see your question right away.
| [Thursday 29 April 2010] [11:20:16] <CIA-15>    zeromq2: 03Martin Sustrik 07master * rc193fd1 10/ (18 files in 3 dirs): lock-free polling removed; ZMQ_POLL flag removed - http://bit.ly/csD6bs
| [Thursday 29 April 2010] [11:31:50] <CIA-15>    zeromq2: 03Martin Sustrik 07master * r37128b7 10/ (10 files): fd_signaler_t renamed to signaler_t - http://bit.ly/d8kupZ
| [Thursday 29 April 2010] [11:46:01] <bgranger>  sustrik:  I am back, I might have found a bug with the new XREP/XREQ stuff, but I am not sure.
| [Thursday 29 April 2010] [11:46:10] <sustrik>   hi
| [Thursday 29 April 2010] [11:46:15] <sustrik>   what bug?
| [Thursday 29 April 2010] [11:46:23] <bgranger>  But I want to make sure I understand what it should be doing
| [Thursday 29 April 2010] [11:46:32]      * sustrik is listening
| [Thursday 29 April 2010] [11:46:44] <bgranger>  The identity string should still be there, as the first part of a multipart message?
| [Thursday 29 April 2010] [11:47:15] <sustrik>   in REQ/REP
| [Thursday 29 April 2010] [11:47:17] <sustrik>   yes
| [Thursday 29 April 2010] [11:47:24] <bgranger>  In XREP/XREQ
| [Thursday 29 April 2010] [11:47:37] <sustrik>   well, it works in this way:
| [Thursday 29 April 2010] [11:47:56] <sustrik>   each node identifies itself when the connection is created to its peer
| [Thursday 29 April 2010] [11:48:19] <sustrik>   when REQ sends a request, the only prefix is empty message part
| [Thursday 29 April 2010] [11:48:23] <bgranger>  Is this the same as the ZMQ_IDENTITY 
| [Thursday 29 April 2010] [11:48:38] <sustrik>   no, it's just a delimiter
| [Thursday 29 April 2010] [11:48:44] <bgranger>  OK
| [Thursday 29 April 2010] [11:48:56] <sustrik>   then on the XREP side XREP sockets adds new prefix
| [Thursday 29 April 2010] [11:49:01] <sustrik>   the identity of the sender
| [Thursday 29 April 2010] [11:49:06] <bgranger>  Right
| [Thursday 29 April 2010] [11:49:16] <sustrik>   XREQ socket sends the message further with no change
| [Thursday 29 April 2010] [11:49:29] <sustrik>   at the end of the chain there's a REP socket
| [Thursday 29 April 2010] [11:49:40] <sustrik>   which extracts all the prefixes from the message
| [Thursday 29 April 2010] [11:49:53] <sustrik>   until it finds an empty message part (the delimiter)
| [Thursday 29 April 2010] [11:50:03] <sustrik>   the rest is passed to the user
| [Thursday 29 April 2010] [11:50:09] <bgranger>  OK
| [Thursday 29 April 2010] [11:50:13] <sustrik>   when user send a reply
| [Thursday 29 April 2010] [11:50:30] <bgranger>  I am using a single XREP socket, so when I do a recv, I see the identity string
| [Thursday 29 April 2010] [11:50:35] <sustrik>   REP socket attaches all the prefixes from the request to the reply and sends it further
| [Thursday 29 April 2010] [11:50:49] <sustrik>   let me finish
| [Thursday 29 April 2010] [11:50:53] <bgranger>  OK
| [Thursday 29 April 2010] [11:51:05] <sustrik>   XREQ socket passes the reply further unchanged
| [Thursday 29 April 2010] [11:51:25] <sustrik>   XREP socket strips the first prefix and uses it to forward the reply to the right connection
| [Thursday 29 April 2010] [11:51:43] <sustrik>   finally REQ socket strips the delimiter and returns the reply to the user
| [Thursday 29 April 2010] [11:51:48] <sustrik>   that's all
| [Thursday 29 April 2010] [11:51:53] <bgranger>  This is in a configuration where an XREP forwards to an XREQ.
| [Thursday 29 April 2010] [11:52:05] <sustrik>   right, standard shared queue thing
| [Thursday 29 April 2010] [11:52:17] <sustrik>   now you have XREQ/XREP setting, right?
| [Thursday 29 April 2010] [11:53:14] <bgranger>  Right
| [Thursday 29 April 2010] [11:53:26] <sustrik>   so this is what is expected:
| [Thursday 29 April 2010] [11:53:30] <bgranger>  I am not forwarding the XREP onto an XREQ
| [Thursday 29 April 2010] [11:53:42] <sustrik>   you send a request to XREQ socket
| [Thursday 29 April 2010] [11:53:49] <sustrik>   retrieve is from XREP socket
| [Thursday 29 April 2010] [11:54:04] <sustrik>   it should be prefixed by XREQ's identity
| [Thursday 29 April 2010] [11:54:07] <bgranger>  Yes
| [Thursday 29 April 2010] [11:54:14] <sustrik>   however, you shouldn't see the identity on the wire
| [Thursday 29 April 2010] [11:54:20] <bgranger>  Right
| [Thursday 29 April 2010] [11:54:23] <sustrik>   (it's passed on connection initiation only)
| [Thursday 29 April 2010] [11:54:33] <sustrik>   when you send a reply
| [Thursday 29 April 2010] [11:54:50] <sustrik>   first prefix is used to route the message to the right XREQ socket
| [Thursday 29 April 2010] [11:55:06] <sustrik>   if there's no such peer, the reply is dropped
| [Thursday 29 April 2010] [11:55:16] <bgranger>  Right, we had that working fine before the multipart message stuff.
| [Thursday 29 April 2010] [11:55:28] <sustrik>   once again, the prefix should not be visible on the wire
| [Thursday 29 April 2010] [11:55:50] <sustrik>   also, you should receive the reply _w/o_ the prefix
| [Thursday 29 April 2010] [11:55:53] <sustrik>   that's it
| [Thursday 29 April 2010] [11:55:58] <bgranger>  Right
| [Thursday 29 April 2010] [11:56:04] <bgranger>  Here is what we are seeing now:
| [Thursday 29 April 2010] [11:56:20] <bgranger>  s = c.socket(zmq.XREP)
| [Thursday 29 April 2010] [11:56:28] <bgranger>  s.bind('tcp://127.0.0.1')
| [Thursday 29 April 2010] [11:56:41] <bgranger>  s.recv()
| [Thursday 29 April 2010] [11:56:48] <bgranger>  '\x00\xba\xd2T\x96\xd6\x8eL\xab\x84\x19\xa9\xa5\xe6\x1f\x95\xeb'
| [Thursday 29 April 2010] [11:56:54] <bgranger>  s.rcvmore()
| [Thursday 29 April 2010] [11:56:58] <bgranger>  False
| [Thursday 29 April 2010] [11:57:05] <bgranger>  s.recv()
| [Thursday 29 April 2010] [11:57:10] <bgranger>  'themessage'
| [Thursday 29 April 2010] [11:57:37] <bgranger>  Is this correct?  I was expecting rcvmore() to return True (more is coming).
| [Thursday 29 April 2010] [11:57:50] <sustrik>   yeah
| [Thursday 29 April 2010] [11:57:55] <sustrik>   looks like a bug
| [Thursday 29 April 2010] [11:58:19] <bgranger>  So, the identity should show up as the first part of a multipart message in this type of situation?
| [Thursday 29 April 2010] [11:58:27] <sustrik>   yes
| [Thursday 29 April 2010] [11:58:34] <sustrik>   and it's there AFAIU
| [Thursday 29 April 2010] [11:58:43] <sustrik>   (auto-generated UUID)
| [Thursday 29 April 2010] [11:59:00] <sustrik>   have you set identity manually on the XREQ socket?
| [Thursday 29 April 2010] [11:59:09] <bgranger>  No, not in this case
| [Thursday 29 April 2010] [11:59:11] <bgranger>  Should I
| [Thursday 29 April 2010] [11:59:13] <sustrik>   then it's ok
| [Thursday 29 April 2010] [11:59:21] <sustrik>   the False is bug though
| [Thursday 29 April 2010] [11:59:56] <sustrik>   i'll have a look at it shortly...
| [Thursday 29 April 2010] [11:59:57] <bgranger>  How is the auto-generated UUID related to the ZMQ_IDENTITY if it is set?
| [Thursday 29 April 2010] [12:00:14] <sustrik>   UUID is generated only if there's no identity
| [Thursday 29 April 2010] [12:00:32] <bgranger>  OK, so I should see the ZMQ_IDENTITY there if it has been set
| [Thursday 29 April 2010] [12:00:36] <sustrik>   right
| [Thursday 29 April 2010] [12:00:46] <bgranger>  Also, what do you think of the socket.rcvmore() API?
| [Thursday 29 April 2010] [12:00:59] <bgranger>  I also wrapped getsockopt as well.
| [Thursday 29 April 2010] [12:01:13] <sustrik>   it's shorthand for getsockopt (ZMQ_MORE) ?
| [Thursday 29 April 2010] [12:01:20] <bgranger>  Yes
| [Thursday 29 April 2010] [12:01:27] <sustrik>   yes, seems reasonable
| [Thursday 29 April 2010] [12:01:33] <bgranger>  Isn't it ZMQ_RCVMORE though?
| [Thursday 29 April 2010] [12:01:42] <sustrik>   :)
| [Thursday 29 April 2010] [12:01:49] <sustrik>   lemme see
| [Thursday 29 April 2010] [12:01:54] <bgranger>  Cool, thanks!
| [Thursday 29 April 2010] [12:02:15] <sustrik>   right RCVMORE :)
| [Thursday 29 April 2010] [12:02:55] <bgranger>  The multipart stuff is fantastic though - will *really* help us
| [Thursday 29 April 2010] [12:03:30] <bgranger>  I will write a test suite for the multipart stuff to help test it all
| [Thursday 29 April 2010] [12:03:45] <CIA-15>    zeromq2: 03Martin Sustrik 07master * r1ffc6dd 10/ (configure.in src/signaler.cpp src/signaler.hpp): eventfd-style signaling removed - http://bit.ly/9Jk5gv
| [Thursday 29 April 2010] [12:09:15] <sustrik>   bgranger: great, test suite will be of much help
| [Thursday 29 April 2010] [13:44:33] <sustrik>   bgranger: i don't seem to have an option to close the issue
| [Thursday 29 April 2010] [13:45:00] <sustrik>   presumably only the original create of the issue can close it
| [Thursday 29 April 2010] [13:45:18] <bgranger>  Which issue?
| [Thursday 29 April 2010] [13:45:34] <bgranger>  I just close the one about ZMQ_IDENTITY a second ago
| [Thursday 29 April 2010] [13:45:45] <sustrik>   ah, good
| [Thursday 29 April 2010] [13:45:54] <sustrik>   thanks
| [Thursday 29 April 2010] [13:46:49] <bgranger>  sustrik:  so is ZMQ_POLL gone for good?
| [Thursday 29 April 2010] [13:47:10] <sustrik>   yes
| [Thursday 29 April 2010] [13:47:28] <sustrik>   well, it's still there to retain backward compatibility
| [Thursday 29 April 2010] [13:47:36] <sustrik>   but it does nothing
| [Thursday 29 April 2010] [13:48:06] <sustrik>   zmq_poll can be used by default now
| [Thursday 29 April 2010] [13:48:19] <CIA-15>    pyzmq: 03Brian E. Granger 07master * r4bf8945 10/ (zmq/_zmq.c zmq/_zmq.pyx): Fixing but in Python bindings to getsockopt with IDENTITY. - http://bit.ly/atHUvJ
| [Thursday 29 April 2010] [13:48:36] <bgranger>  Nice, wasn't there a small performance issue before?
| [Thursday 29 April 2010] [13:49:28] <sustrik>   it's still there
| [Thursday 29 April 2010] [13:49:36] <sustrik>   the impact is ~2us on the latency side
| [Thursday 29 April 2010] [13:49:47] <sustrik>   on Linux
| [Thursday 29 April 2010] [13:50:03] <sustrik>   but the advantages seem worth of it
| [Thursday 29 April 2010] [13:50:37] <sustrik>   1. no annoying ZMQ_POLL flag
| [Thursday 29 April 2010] [13:50:50] <sustrik>   2. any number of threads can be used! even >64
| [Thursday 29 April 2010] [13:51:04] <sustrik>   3. significant codebase simplification
| [Thursday 29 April 2010] [13:59:49] <bgranger>  Seems like a good trade off.  I like simplicity :)
| [Thursday 29 April 2010] [14:34:38] <CIA-15>    zeromq2: 03Martin Sustrik 07master * rae93ed3 10/ (12 files): signaler rewritten in such a way that any number (>64) of threads can be used - http://bit.ly/chon4a
| [Thursday 29 April 2010] [14:53:41] <CIA-15>    zeromq2: 03Martin Sustrik 07master * rbeb4da3 10/ (builds/msvc/libzmq/libzmq.vcproj src/signaler.cpp): windows port fixed - http://bit.ly/9BogHN
| [Thursday 29 April 2010] [22:54:17] <CIA-15>    zeromq2: 03Martin Sustrik 07master * racfd0f8 10/ src/xrep.cpp : prefix in XREP recv'd message misses MORE flag - http://bit.ly/aPynXa
| [Thursday 29 April 2010] [22:54:17] <CIA-15>    zeromq2: 03Martin Sustrik 07master * r4a6bac1 10/ (builds/msvc/libzmq/libzmq.vcproj src/signaler.cpp): Merge branch 'master' of git@github.com:sustrik/zeromq2 - http://bit.ly/axsva4
| [Thursday 29 April 2010] [22:54:25] <sustrik>   bgranger: try now
| [Friday 30 April 2010] [11:46:40] <CIA-15>  pyzmq: 03Brian E. Granger 07master * rb2097cf 10/ setup.cfg.template : Adding runtime_library_dirs option to setup.cfg.template. - http://bit.ly/aw2Xtd
| [Friday 30 April 2010] [18:51:46] <bgranger>    sustrik: are you around?