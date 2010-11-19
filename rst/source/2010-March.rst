
| [Monday 29 March 2010] [18:37:34] Part  dh1r has left this channel.
| 
| *** Logfile started
| *** on Mon Mar 29 19:06:08 2010
| 
| [Monday 29 March 2010] [19:06:08] Topic The channel topic is "Welcome!".
| [Monday 29 March 2010] [19:06:08] Topic The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Monday 29 March 2010] [19:06:14] Mode  Channel modes: no messages from outside, topic protection
| [Monday 29 March 2010] [19:06:14] Created   This channel was created on 2010-02-05 10:44.
| 
| *** Logfile started
| *** on Mon Mar 29 20:26:50 2010
| 
| [Monday 29 March 2010] [20:26:50] Topic The channel topic is "Welcome!".
| [Monday 29 March 2010] [20:26:50] Topic The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Monday 29 March 2010] [20:26:56] Mode  Channel modes: no messages from outside, topic protection
| [Monday 29 March 2010] [20:26:56] Created   This channel was created on 2010-02-05 10:44.
| 
| *** Logfile started
| *** on Mon Mar 29 21:53:10 2010
| 
| [Monday 29 March 2010] [21:53:10] Topic The channel topic is "Welcome!".
| [Monday 29 March 2010] [21:53:10] Topic The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Monday 29 March 2010] [21:53:16] Mode  Channel modes: no messages from outside, topic protection
| [Monday 29 March 2010] [21:53:16] Created   This channel was created on 2010-02-05 10:44.
| 
| *** Logfile started
| *** on Tue Mar 30 00:16:23 2010
| 
| [Tuesday 30 March 2010] [00:16:23] Topic    The channel topic is "Welcome!".
| [Tuesday 30 March 2010] [00:16:23] Topic    The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Tuesday 30 March 2010] [00:16:29] Mode Channel modes: no messages from outside, topic protection
| [Tuesday 30 March 2010] [00:16:29] Created  This channel was created on 2010-02-05 10:44.
| [Tuesday 30 March 2010] [05:34:39] <vtl>    sustrik: hi! which error code non-blocking zmq_msg_recv() will return on m$ windows if there's no bytes to read?
| 
| *** Logfile started
| *** on Tue Mar 30 20:06:31 2010
| 
| [Tuesday 30 March 2010] [20:06:31] Topic    The channel topic is "Welcome!".
| [Tuesday 30 March 2010] [20:06:31] Topic    The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Tuesday 30 March 2010] [20:06:37] Mode Channel modes: no messages from outside, topic protection
| [Tuesday 30 March 2010] [20:06:37] Created  This channel was created on 2010-02-05 10:44.
| [Tuesday 30 March 2010] [20:14:02] <davelee>    hi. So i've installed zeromq. There doesn't seem to be any docs about how to actually start the service ... ? 
| [Tuesday 30 March 2010] [20:14:41] <davelee>    (i'm on snow leopard FWIW)
| [Tuesday 30 March 2010] [20:15:05] <davelee>    there's a zmq_queue binary which wants a config file ..
| [Wednesday 31 March 2010] [01:45:29] <sustrik>  davelee: what are you trying to do?
| [Wednesday 31 March 2010] [02:44:46] <davelee>  sustrik: I was just trying to get "up and running"
| [Wednesday 31 March 2010] [02:45:10] <davelee>  to get the ruby gem demo / test running
| [Wednesday 31 March 2010] [02:45:21] <sustrik>  let me see...
| [Wednesday 31 March 2010] [02:45:38] <davelee>  i'm assuming that, like rabbitmq, there's a server you need to run  ... ? 
| [Wednesday 31 March 2010] [02:45:44] <davelee>  or is it just a p2p scenario
| [Wednesday 31 March 2010] [02:45:49] <sustrik>  both
| [Wednesday 31 March 2010] [02:45:55] <sustrik>  it depends on what you want to do
| [Wednesday 31 March 2010] [02:46:11] <sustrik>  if you just want to test it, run the perf tests
| [Wednesday 31 March 2010] [02:46:27] <sustrik>  rbzmq/perf
| [Wednesday 31 March 2010] [02:46:40] <sustrik>  someting like:
| [Wednesday 31 March 2010] [02:47:05] <sustrik>  ruby local_thr tcp://127.0.0.1:5555 1 10000
| [Wednesday 31 March 2010] [02:47:09] <sustrik>  then:
| [Wednesday 31 March 2010] [02:47:25] <sustrik>  ruby remote_thr.rb tcp://127.0.0.1:5555 1 10000
| [Wednesday 31 March 2010] [02:47:46] <davelee>  in different terminals (ie, are they communicating)? 
| [Wednesday 31 March 2010] [02:48:01] <sustrik>  yes, in different terminals
| [Wednesday 31 March 2010] [02:48:10] <sustrik>  or you can try it on two boxes
| [Wednesday 31 March 2010] [02:48:33] <sustrik>  you have to supply real IP addresses in the latter case of course
| [Wednesday 31 March 2010] [02:48:40] <sustrik>  (or names)
| [Wednesday 31 March 2010] [02:49:01] <davelee>  ok, that's the part which confused me. I ran ruby local_lat.rb tcp://127.0.0.1:5555 1 100
| [Wednesday 31 March 2010] [02:49:23] <sustrik>  yeah, you need the other endpoint
| [Wednesday 31 March 2010] [02:49:29] <davelee>  and it did nothing - i was expecting it'd want to connect to a broker / etc and complain, at which point I'd go start something
| [Wednesday 31 March 2010] [02:49:32] <davelee>  yep rgr
| [Wednesday 31 March 2010] [02:51:27] <davelee>  ok, that seemed to work; local_thr.rb closed with a message about throughput; remote_thr.rb remains running
| [Wednesday 31 March 2010] [02:51:45] <sustrik>  yup
| [Wednesday 31 March 2010] [02:53:09] <davelee>  so ... are there any other examples of how to actually use the ruby gem ?
| [Wednesday 31 March 2010] [02:53:34] <davelee>  the amqp gem is a bit arcane but reasonably easy to figure out by looking at the examples 
| [Wednesday 31 March 2010] [02:53:54] <davelee>  zmq gem has these perf scripts, and i've got a basic idea from looking at them 
| [Wednesday 31 March 2010] [02:54:48] <davelee>  oh right, time to look @ the C bindings ... 
| [Wednesday 31 March 2010] [02:55:56] <davelee>  in that case,  I'll assume there's not yet a higher-level ruby library - it's just a wrapper around the C libs? 
| [Wednesday 31 March 2010] [02:56:47] <davelee>  anyway, gotta go. thanks for the help 
| [Wednesday 31 March 2010] [02:57:01] Part   davelee has left this channel.
| [Wednesday 31 March 2010] [04:04:55] Nick   mato_ is now known as mato.
| [Wednesday 31 March 2010] [05:05:11] <mato> sustrik: take a look at my proposals regarding MSG_MORE when you get a moment
| [Wednesday 31 March 2010] [05:05:33] <mato> sustrik: i think they are nice and consistent
| [Wednesday 31 March 2010] [05:07:30] <pquerna>  hi, for $work we use lots of txAMQP and rabbitmq, but am unhappy with various parts.  I'm trying to gork zmq, but really it seems to just be a transport layer, abit a cool one that abstracts more than most tcp based transports.  
| [Wednesday 31 March 2010] [05:07:51] <pquerna>  It seems hinted at that you need to build your own mechnisims for configuration management and distribution of how to communicate between machines
| [Wednesday 31 March 2010] [05:08:28] <pquerna>  is this something zmq intends to do more of, I mean I look at for example http://api.zeromq.org/zmq_queue.html , and it makes me feel like those more higher level services just don't exist yet?
| [Wednesday 31 March 2010] [05:09:01] <mato> pquerna: the device implementations do exist, but they're still considered early days, so are not documented
| [Wednesday 31 March 2010] [05:09:41] <mato> pquerna: however, there are people using e.g. zmq_queue to successfully implement shared queues
| [Wednesday 31 March 2010] [05:10:23] <mato> and yes, zmq devices are something that we will be focusing on
| [Wednesday 31 March 2010] [05:12:20] <pquerna>  okay, and what about the brokerless design -- i read throguh http://www.zeromq.org/whitepapers:brokerless and yeha, I've done this before with my own wire format about 2 jobs back :) but doesn't seem like there are bits on the open source side of zmq that do it yet (?)
| [Wednesday 31 March 2010] [05:13:14] <pquerna>  or rather, its left as an exercise to the reader...
| [Wednesday 31 March 2010] [05:13:28] <mato> well, it depends on what you *need* from the broker
| [Wednesday 31 March 2010] [05:13:59] <mato> all the bits are in place, and if you look at recent discussion on the mailing list, you'll see that there is talk of embedding devices inside applications
| [Wednesday 31 March 2010] [05:14:25] <mato> so instead of zmq_queue being a binary, it's a call to e.g. zmq_queue_device(...) inside your app
| [Wednesday 31 March 2010] [05:14:39] <pquerna>  ah
| [Wednesday 31 March 2010] [05:14:49] <mato> which means that you decide where your "broker" bits go, if you need them
| [Wednesday 31 March 2010] [05:15:12] <pquerna>  ya, we have a mix of use cases, some of them definately could use somehting as simple as that.
| [Wednesday 31 March 2010] [05:15:35] <pquerna>  most of ours are either single writer, lots of readers, or single reader, lots of writers, both of which can fit that just fine.
| [Wednesday 31 March 2010] [05:16:30] <mato> yep, and you can probably do a lot of that without any devices at all
| [Wednesday 31 March 2010] [05:16:46] <mato> since 0mq sockets let you talk to multiple endpoints
| [Wednesday 31 March 2010] [05:17:05] <mato> take a look at the zmq_socket documentation, it describes the messaging patterns you can use
| [Wednesday 31 March 2010] [05:17:18] <mato> http://api.zeromq.org/zmq_socket.html
| [Wednesday 31 March 2010] [05:17:30] <mato> (yes, it's terse, but it's a reference so you should get the idea)
| [Wednesday 31 March 2010] [05:18:09] <mato> you might also want to skim the LWN article if you haven't read it already
| [Wednesday 31 March 2010] [05:18:14] <mato> http://lwn.net/Articles/370307/
| [Wednesday 31 March 2010] [05:19:08] <pquerna>  one thing I don't quite understand is error handling, say in the simplest case of a p2p tcp connection -- how much does zmq retry underneath, is there any way to hook in my own logging subsystem to say 'hey tcp ain't working to host xxx'
| [Wednesday 31 March 2010] [05:19:30] <mato> no there isn't, and that's kind of deliberate
| [Wednesday 31 March 2010] [05:19:55] <mato> since even with tcp you don't get a real/instant notification of e.g. "the other end went away"
| [Wednesday 31 March 2010] [05:19:59] <pquerna>  sure
| [Wednesday 31 March 2010] [05:20:06] <pquerna>  (unless you wait for a reply)
| [Wednesday 31 March 2010] [05:20:09] <mato> precisely
| [Wednesday 31 March 2010] [05:21:01] <mato> which you can also do with 0mq, but the point is that a 0mq socket lets you access an asynchronous queue
| [Wednesday 31 March 2010] [05:21:29] <pquerna>  right, we just do lots of... multi-data center stuff on cloud servers.
| [Wednesday 31 March 2010] [05:21:34] <pquerna>  the network can.. be... sucky.
| [Wednesday 31 March 2010] [05:21:55] <mato> so you want to detect and respond to that suckiness somehow?
| [Wednesday 31 March 2010] [05:21:57] <mato> right?
| [Wednesday 31 March 2010] [05:21:57] <pquerna>  also I guess no native encryption.. so vpn/ipsec everything?
| [Wednesday 31 March 2010] [05:22:14] <pquerna>  ya, at least log it a bit, ideally we switch whcih endpoint we are using
| [Wednesday 31 March 2010] [05:22:37] <mato> no encryption, so yes, vpn/ipsec... designing good encryption is hard and vpn/ipsec is proven and understood
| [Wednesday 31 March 2010] [05:22:43] <mato> we try not to reinvent the wheel
| [Wednesday 31 March 2010] [05:22:56] <pquerna>  :)
| [Wednesday 31 March 2010] [05:23:10] <mato> as for detecting the network...
| [Wednesday 31 March 2010] [05:23:28] <mato> what i would suggest is a side channel / monitoring messages using 0mq
| [Wednesday 31 March 2010] [05:23:41] <mato> so you periodically ping the other end and test latency
| [Wednesday 31 March 2010] [05:24:22] <mato> and if you start getting bad figures back your application can take evasive action/start paging netops people/whatever...
| [Wednesday 31 March 2010] [05:26:10] <pquerna>  thanks for answering all my questions
| [Wednesday 31 March 2010] [05:26:21] <mato> also, flow control (high/low water mark) on sockets has been implemented in 0mq
| [Wednesday 31 March 2010] [05:26:37] <pquerna>  yes, thank goodness
| [Wednesday 31 March 2010] [05:26:59] <pquerna>  i actually want a mode where it throws away exploding queues, but meh
| [Wednesday 31 March 2010] [05:27:00] <mato> so that can also be used to good effect and may be enough for some applications
| [Wednesday 31 March 2010] [05:27:39] <mato> pquerna: you're welcome
| [Wednesday 31 March 2010] [05:27:53] <mato> pquerna: have fun, tell a friend, come back, contribute, sponsor, etc etc :-)
| [Wednesday 31 March 2010] [05:37:44] <sustrik>  mato: test env is running
| [Wednesday 31 March 2010] [05:37:48] <mato> sustrik: thanks
| [Wednesday 31 March 2010] [07:12:44] <mato> sustrik: ok, pgm on trunk has regressed. see my emails
| [Wednesday 31 March 2010] [07:12:54] <mato> sustrik: i don't think there's anything else i can do now
| [Wednesday 31 March 2010] [07:13:02] <sustrik>  mato: ok, seen that
| [Wednesday 31 March 2010] [07:13:05] <mato> sustrik: will have to wait for feedback from steven
| [Wednesday 31 March 2010] [07:13:17] <mato> sustrik: so i'll shut down the servers...
| [Wednesday 31 March 2010] [07:13:17] <sustrik>  can i switch the boxes off now?
| [Wednesday 31 March 2010] [07:13:22] <sustrik>  ok
| [Wednesday 31 March 2010] [07:14:24] <mato> you can unplug it once they all switch off
| [Wednesday 31 March 2010] [08:21:41] <sjampoo>  Hi, i do not completely understand zmq_init(appthreads, iothreads), are there any pointers with more information? What happens when i access a context with more threads then appthreads specified?  Do i need to worry about iothreads, are there any guidelines for its size? 
| [Wednesday 31 March 2010] [08:23:17] <sustrik>  sjampoo: if you've specified say 3 application threads
| [Wednesday 31 March 2010] [08:23:24] <sustrik>  and have sockets opened from 3 threads
| [Wednesday 31 March 2010] [08:23:33] <sustrik>  and try to open a socket from 4th thread
| [Wednesday 31 March 2010] [08:23:40] <sustrik>  you'll get EMTHREAD error
| [Wednesday 31 March 2010] [08:24:07] <sustrik>  as for I/O threads think of them as of CPU cores
| [Wednesday 31 March 2010] [08:24:14] <sustrik>  say you have 8-core box
| [Wednesday 31 March 2010] [08:24:33] <sustrik>  you want 2 cores to handle to background part of 0MQ work
| [Wednesday 31 March 2010] [08:24:50] <sustrik>  use 2 I/O threads then
| [Wednesday 31 March 2010] [08:25:05] <sjampoo>  Ok I understand IOThreads now, thanks.
| [Wednesday 31 March 2010] [08:25:23] <sjampoo>  Concerning appthreads, i am planning to use it in a singe event loop with multiple light weight threads.
| [Wednesday 31 March 2010] [08:25:53] <sustrik>  each thread will have a socket open, right?
| [Wednesday 31 March 2010] [08:25:56] <sjampoo>  So i will want to open multiple ZMQ sockets on a single context and use them non-blocking, should i increase the app threads number to the amount of sockets? 
| [Wednesday 31 March 2010] [08:26:23] <sustrik>  it's number of threads you'll be using 0MQ from
| [Wednesday 31 March 2010] [08:26:34] <sustrik>  so if you are using it from 1 thread, specify 1
| [Wednesday 31 March 2010] [08:26:51] <sustrik>  is you have your event loop thread + 5 worker threads, specify 6
| [Wednesday 31 March 2010] [08:27:03] <sjampoo>  aha
| [Wednesday 31 March 2010] [08:27:33] <sjampoo>  Would 10.000 be a weird big number? 
| [Wednesday 31 March 2010] [08:28:21] <sustrik>  whoa, what kind of application are you writing?
| [Wednesday 31 March 2010] [08:28:25] <sustrik>  HPC cluster?
| [Wednesday 31 March 2010] [08:28:35] <sjampoo>  I am planning to integrate it with websockets where each user would get its own ZMQ thread.
| [Wednesday 31 March 2010] [08:28:59] <sustrik>  you are planning for 10000 threads on a single box?
| [Wednesday 31 March 2010] [08:29:10] <sustrik>  how many CPU cores there are?
| [Wednesday 31 March 2010] [08:29:14] <sjampoo>  10000 lightweight threads
| [Wednesday 31 March 2010] [08:29:33] <sjampoo>  (with stackless Python)
| [Wednesday 31 March 2010] [08:29:49] <sustrik>  ah, you mean python pseudo-threads?
| [Wednesday 31 March 2010] [08:29:54] <sustrik>  or green threads
| [Wednesday 31 March 2010] [08:29:55] <sjampoo>  yes.
| [Wednesday 31 March 2010] [08:29:58] <sjampoo>  Green Threads
| [Wednesday 31 March 2010] [08:30:01] <sjampoo>  Tasklets really
| [Wednesday 31 March 2010] [08:30:27] <sustrik>  afaik all python green threads map to a single OS thread
| [Wednesday 31 March 2010] [08:30:38] <sustrik>  so specify 1
| [Wednesday 31 March 2010] [08:30:42] <sjampoo>  Ok.
| [Wednesday 31 March 2010] [08:31:09] <sjampoo>  So that appthread does in no way limit the amount of sockets i can open is my real question i think.
| [Wednesday 31 March 2010] [08:31:48] <sjampoo>  (I mean the appthread setting to zmq_init)
| [Wednesday 31 March 2010] [08:33:53] <sustrik>  no, it's just number of threads
| [Wednesday 31 March 2010] [08:33:59] <sustrik>  even if you have 1 thread
| [Wednesday 31 March 2010] [08:34:05] <sustrik>  you can open 1000 sockets
| [Wednesday 31 March 2010] [08:34:23] <sjampoo>  ok thanks for clearing that up for me
| [Wednesday 31 March 2010] [08:34:45] <sustrik>  np
| [Wednesday 31 March 2010] [08:34:45] <sjampoo>  ZMQ is really nice, did some benchmarks its really fast
| [Wednesday 31 March 2010] [08:34:52] <sustrik>  we've tried :)
| [Wednesday 31 March 2010] [08:41:49] <sjampoo>  I also love the design of the website and the documentation. But it took me some time to understand the level at which ZMQ operates, which is pretty low compared to other messaging systems. But, really like it for that. 
| [Wednesday 31 March 2010] [08:46:59] <sustrik>  sjampoo: if you have any suggestion how to organise the documentation better
| [Wednesday 31 March 2010] [08:47:12] <sustrik>  give us a hint
| [Wednesday 31 March 2010] [08:47:37] <sustrik>  what kind of info would you have preferred to see first?
| [Wednesday 31 March 2010] [08:47:39] <sustrik>  etc.
| [Wednesday 31 March 2010] [08:48:33] <sjampoo>  i'll give it some thought and might get back to it on the mailing list
| [Wednesday 31 March 2010] [08:49:03] <sustrik>  sjampoo: thanks
| [Wednesday 31 March 2010] [08:49:54] <sjampoo>  I think the main thing that i know understand is that ZMQ isn't really a messaging system but an awesome socket implementation on which you can build your own MS.
| [Wednesday 31 March 2010] [08:51:34] <sustrik>  it depends on the exact meaning of "messaging system"
| [Wednesday 31 March 2010] [08:51:46] <sustrik>  the problem is that the terminology is pretty vague
| [Wednesday 31 March 2010] [08:52:37] <sustrik>  so what we thought of was ditching all the "messaging middleware" terminology on the front page
| [Wednesday 31 March 2010] [08:52:52] <sustrik>  and instead presenting what you can do with the product
| [Wednesday 31 March 2010] [08:53:05] <sustrik>  something like:
| [Wednesday 31 March 2010] [08:53:15] <sustrik>  "write a server in 10 lines of code"
| [Wednesday 31 March 2010] [08:54:06] <sjampoo>  I completely agree with that.  The problem with my specific case is, that I started looking at ZMQ after i read about a comparison on the SecondLife wiki, it is different than RabbitMQ or ActiveMQ.
| [Wednesday 31 March 2010] [08:54:54] <sustrik>  yup, but the difference is hard to explain, we've been struggling with explaining it for years
| [Wednesday 31 March 2010] [08:55:06] <sustrik>  i mean, explaining it in 1-2 paragrahs on the frontpage
| [Wednesday 31 March 2010] [08:55:38] <sustrik>  so that all kinds of people that come to the website get at least a dim idea of what the hell is it about
| [Wednesday 31 March 2010] [09:16:53] <sjampoo>  I think a good analogy would be that where ActiveMQ/RabbitMQ gives you a post office, ZMQ gives you couriers. While being lightweight and fast you do need to take care of them yourself. 
| [Wednesday 31 March 2010] [09:21:35] <sustrik>  hm, makes sense
| [Wednesday 31 March 2010] [09:21:55] <sustrik>  what about "a new layer of Internet stack"
| [Wednesday 31 March 2010] [09:22:10] <sustrik>  + a picture showing Ethernet, IP, TCP, UDP and 0MQ on top of that?
| [Wednesday 31 March 2010] [09:24:56] <sjampoo>  yes that makes sense, i personally think of ZMQ as TCP/IP covered in sugar. All the flexibility without the headaches. 
| [Wednesday 31 March 2010] [09:25:52] <sjampoo>  I think it makes a perfect combination with high level languages such as Python.
| [Wednesday 31 March 2010] [09:36:42] <sjampoo>  I really think it is important to stress the level at which ZMQ operates. I remember that i read the article: 'broker vs brokerless' a while ago and after finishing it started looking for broker/directory service options. 
| [Wednesday 31 March 2010] [09:37:08] <sjampoo>  Now that i understand what ZMQ provides and doesn't provide it makes sense. 
| [Wednesday 31 March 2010] [09:50:10] <sustrik>  ok, i'll try to improve the frontpage...
| [Wednesday 31 March 2010] [10:10:47] Part   hurtonm has left this channel.
| [Wednesday 31 March 2010] [10:13:31] <mato> sustrik: i had an idea
| [Wednesday 31 March 2010] [10:13:37] <mato> sustrik: are you around?
| [Wednesday 31 March 2010] [10:37:12] <CIA-5>    zeromq2: 03Martin Hurton 07master * r37fd1a7 10/ src/rep.cpp : Handle full-pipe for REP sockets more gracefully - http://bit.ly/aAszD1
| [Wednesday 31 March 2010] [12:10:01] <sjampoo>  Hmm what is causing the huge interest spike in ZMQ at the moment? I see lots of people bookmarking it at delicious today and yesterday. 
| [Wednesday 31 March 2010] [12:14:09] <sjampoo>  ah, probably the 'AMQP fundamentally flawed' article by Hintjes (which hit Hacker News)
| [Wednesday 31 March 2010] [12:16:03] <squeeky>  few people tweeted about it.
| [Wednesday 31 March 2010] [12:16:13] <sjampoo>  yah saw that too
| [Wednesday 31 March 2010] [15:30:06] <mikko>    howdy
| [Wednesday 31 March 2010] [17:02:20]     * impl looks at mikko 
| [Wednesday 31 March 2010] [20:03:20] <wutang>   I am very familiar with 29west...are there any documents out there describing the differences in architecture and possible API differences between the two?
| [Wednesday 31 March 2010] [20:03:49] <wutang>   Also, I haven't found many examples beyond the most basic...are there any good repositories of examples or real applications that are open source?
| [Wednesday 31 March 2010] [21:34:26] Part   gz_ has left this channel ("Konversation terminated!").
| [Monday 29 March 2010] [18:37:34] Part  dh1r has left this channel.
| 
| *** Logfile started
| *** on Mon Mar 29 19:06:08 2010
| 
| [Monday 29 March 2010] [19:06:08] Topic The channel topic is "Welcome!".
| [Monday 29 March 2010] [19:06:08] Topic The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Monday 29 March 2010] [19:06:14] Mode  Channel modes: no messages from outside, topic protection
| [Monday 29 March 2010] [19:06:14] Created   This channel was created on 2010-02-05 10:44.
| 
| *** Logfile started
| *** on Mon Mar 29 20:26:50 2010
| 
| [Monday 29 March 2010] [20:26:50] Topic The channel topic is "Welcome!".
| [Monday 29 March 2010] [20:26:50] Topic The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Monday 29 March 2010] [20:26:56] Mode  Channel modes: no messages from outside, topic protection
| [Monday 29 March 2010] [20:26:56] Created   This channel was created on 2010-02-05 10:44.
| 
| *** Logfile started
| *** on Mon Mar 29 21:53:10 2010
| 
| [Monday 29 March 2010] [21:53:10] Topic The channel topic is "Welcome!".
| [Monday 29 March 2010] [21:53:10] Topic The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Monday 29 March 2010] [21:53:16] Mode  Channel modes: no messages from outside, topic protection
| [Monday 29 March 2010] [21:53:16] Created   This channel was created on 2010-02-05 10:44.
| 
| *** Logfile started
| *** on Tue Mar 30 00:16:23 2010
| 
| [Tuesday 30 March 2010] [00:16:23] Topic    The channel topic is "Welcome!".
| [Tuesday 30 March 2010] [00:16:23] Topic    The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Tuesday 30 March 2010] [00:16:29] Mode Channel modes: no messages from outside, topic protection
| [Tuesday 30 March 2010] [00:16:29] Created  This channel was created on 2010-02-05 10:44.
| [Tuesday 30 March 2010] [05:34:39] <vtl>    sustrik: hi! which error code non-blocking zmq_msg_recv() will return on m$ windows if there's no bytes to read?
| 
| *** Logfile started
| *** on Tue Mar 30 20:06:31 2010
| 
| [Tuesday 30 March 2010] [20:06:31] Topic    The channel topic is "Welcome!".
| [Tuesday 30 March 2010] [20:06:31] Topic    The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Tuesday 30 March 2010] [20:06:37] Mode Channel modes: no messages from outside, topic protection
| [Tuesday 30 March 2010] [20:06:37] Created  This channel was created on 2010-02-05 10:44.
| [Tuesday 30 March 2010] [20:14:02] <davelee>    hi. So i've installed zeromq. There doesn't seem to be any docs about how to actually start the service ... ? 
| [Tuesday 30 March 2010] [20:14:41] <davelee>    (i'm on snow leopard FWIW)
| [Tuesday 30 March 2010] [20:15:05] <davelee>    there's a zmq_queue binary which wants a config file ..
| [Wednesday 31 March 2010] [01:45:29] <sustrik>  davelee: what are you trying to do?
| [Wednesday 31 March 2010] [02:44:46] <davelee>  sustrik: I was just trying to get "up and running"
| [Wednesday 31 March 2010] [02:45:10] <davelee>  to get the ruby gem demo / test running
| [Wednesday 31 March 2010] [02:45:21] <sustrik>  let me see...
| [Wednesday 31 March 2010] [02:45:38] <davelee>  i'm assuming that, like rabbitmq, there's a server you need to run  ... ? 
| [Wednesday 31 March 2010] [02:45:44] <davelee>  or is it just a p2p scenario
| [Wednesday 31 March 2010] [02:45:49] <sustrik>  both
| [Wednesday 31 March 2010] [02:45:55] <sustrik>  it depends on what you want to do
| [Wednesday 31 March 2010] [02:46:11] <sustrik>  if you just want to test it, run the perf tests
| [Wednesday 31 March 2010] [02:46:27] <sustrik>  rbzmq/perf
| [Wednesday 31 March 2010] [02:46:40] <sustrik>  someting like:
| [Wednesday 31 March 2010] [02:47:05] <sustrik>  ruby local_thr tcp://127.0.0.1:5555 1 10000
| [Wednesday 31 March 2010] [02:47:09] <sustrik>  then:
| [Wednesday 31 March 2010] [02:47:25] <sustrik>  ruby remote_thr.rb tcp://127.0.0.1:5555 1 10000
| [Wednesday 31 March 2010] [02:47:46] <davelee>  in different terminals (ie, are they communicating)? 
| [Wednesday 31 March 2010] [02:48:01] <sustrik>  yes, in different terminals
| [Wednesday 31 March 2010] [02:48:10] <sustrik>  or you can try it on two boxes
| [Wednesday 31 March 2010] [02:48:33] <sustrik>  you have to supply real IP addresses in the latter case of course
| [Wednesday 31 March 2010] [02:48:40] <sustrik>  (or names)
| [Wednesday 31 March 2010] [02:49:01] <davelee>  ok, that's the part which confused me. I ran ruby local_lat.rb tcp://127.0.0.1:5555 1 100
| [Wednesday 31 March 2010] [02:49:23] <sustrik>  yeah, you need the other endpoint
| [Wednesday 31 March 2010] [02:49:29] <davelee>  and it did nothing - i was expecting it'd want to connect to a broker / etc and complain, at which point I'd go start something
| [Wednesday 31 March 2010] [02:49:32] <davelee>  yep rgr
| [Wednesday 31 March 2010] [02:51:27] <davelee>  ok, that seemed to work; local_thr.rb closed with a message about throughput; remote_thr.rb remains running
| [Wednesday 31 March 2010] [02:51:45] <sustrik>  yup
| [Wednesday 31 March 2010] [02:53:09] <davelee>  so ... are there any other examples of how to actually use the ruby gem ?
| [Wednesday 31 March 2010] [02:53:34] <davelee>  the amqp gem is a bit arcane but reasonably easy to figure out by looking at the examples 
| [Wednesday 31 March 2010] [02:53:54] <davelee>  zmq gem has these perf scripts, and i've got a basic idea from looking at them 
| [Wednesday 31 March 2010] [02:54:48] <davelee>  oh right, time to look @ the C bindings ... 
| [Wednesday 31 March 2010] [02:55:56] <davelee>  in that case,  I'll assume there's not yet a higher-level ruby library - it's just a wrapper around the C libs? 
| [Wednesday 31 March 2010] [02:56:47] <davelee>  anyway, gotta go. thanks for the help 
| [Wednesday 31 March 2010] [02:57:01] Part   davelee has left this channel.
| [Wednesday 31 March 2010] [04:04:55] Nick   mato_ is now known as mato.
| [Wednesday 31 March 2010] [05:05:11] <mato> sustrik: take a look at my proposals regarding MSG_MORE when you get a moment
| [Wednesday 31 March 2010] [05:05:33] <mato> sustrik: i think they are nice and consistent
| [Wednesday 31 March 2010] [05:07:30] <pquerna>  hi, for $work we use lots of txAMQP and rabbitmq, but am unhappy with various parts.  I'm trying to gork zmq, but really it seems to just be a transport layer, abit a cool one that abstracts more than most tcp based transports.  
| [Wednesday 31 March 2010] [05:07:51] <pquerna>  It seems hinted at that you need to build your own mechnisims for configuration management and distribution of how to communicate between machines
| [Wednesday 31 March 2010] [05:08:28] <pquerna>  is this something zmq intends to do more of, I mean I look at for example http://api.zeromq.org/zmq_queue.html , and it makes me feel like those more higher level services just don't exist yet?
| [Wednesday 31 March 2010] [05:09:01] <mato> pquerna: the device implementations do exist, but they're still considered early days, so are not documented
| [Wednesday 31 March 2010] [05:09:41] <mato> pquerna: however, there are people using e.g. zmq_queue to successfully implement shared queues
| [Wednesday 31 March 2010] [05:10:23] <mato> and yes, zmq devices are something that we will be focusing on
| [Wednesday 31 March 2010] [05:12:20] <pquerna>  okay, and what about the brokerless design -- i read throguh http://www.zeromq.org/whitepapers:brokerless and yeha, I've done this before with my own wire format about 2 jobs back :) but doesn't seem like there are bits on the open source side of zmq that do it yet (?)
| [Wednesday 31 March 2010] [05:13:14] <pquerna>  or rather, its left as an exercise to the reader...
| [Wednesday 31 March 2010] [05:13:28] <mato> well, it depends on what you *need* from the broker
| [Wednesday 31 March 2010] [05:13:59] <mato> all the bits are in place, and if you look at recent discussion on the mailing list, you'll see that there is talk of embedding devices inside applications
| [Wednesday 31 March 2010] [05:14:25] <mato> so instead of zmq_queue being a binary, it's a call to e.g. zmq_queue_device(...) inside your app
| [Wednesday 31 March 2010] [05:14:39] <pquerna>  ah
| [Wednesday 31 March 2010] [05:14:49] <mato> which means that you decide where your "broker" bits go, if you need them
| [Wednesday 31 March 2010] [05:15:12] <pquerna>  ya, we have a mix of use cases, some of them definately could use somehting as simple as that.
| [Wednesday 31 March 2010] [05:15:35] <pquerna>  most of ours are either single writer, lots of readers, or single reader, lots of writers, both of which can fit that just fine.
| [Wednesday 31 March 2010] [05:16:30] <mato> yep, and you can probably do a lot of that without any devices at all
| [Wednesday 31 March 2010] [05:16:46] <mato> since 0mq sockets let you talk to multiple endpoints
| [Wednesday 31 March 2010] [05:17:05] <mato> take a look at the zmq_socket documentation, it describes the messaging patterns you can use
| [Wednesday 31 March 2010] [05:17:18] <mato> http://api.zeromq.org/zmq_socket.html
| [Wednesday 31 March 2010] [05:17:30] <mato> (yes, it's terse, but it's a reference so you should get the idea)
| [Wednesday 31 March 2010] [05:18:09] <mato> you might also want to skim the LWN article if you haven't read it already
| [Wednesday 31 March 2010] [05:18:14] <mato> http://lwn.net/Articles/370307/
| [Wednesday 31 March 2010] [05:19:08] <pquerna>  one thing I don't quite understand is error handling, say in the simplest case of a p2p tcp connection -- how much does zmq retry underneath, is there any way to hook in my own logging subsystem to say 'hey tcp ain't working to host xxx'
| [Wednesday 31 March 2010] [05:19:30] <mato> no there isn't, and that's kind of deliberate
| [Wednesday 31 March 2010] [05:19:55] <mato> since even with tcp you don't get a real/instant notification of e.g. "the other end went away"
| [Wednesday 31 March 2010] [05:19:59] <pquerna>  sure
| [Wednesday 31 March 2010] [05:20:06] <pquerna>  (unless you wait for a reply)
| [Wednesday 31 March 2010] [05:20:09] <mato> precisely
| [Wednesday 31 March 2010] [05:21:01] <mato> which you can also do with 0mq, but the point is that a 0mq socket lets you access an asynchronous queue
| [Wednesday 31 March 2010] [05:21:29] <pquerna>  right, we just do lots of... multi-data center stuff on cloud servers.
| [Wednesday 31 March 2010] [05:21:34] <pquerna>  the network can.. be... sucky.
| [Wednesday 31 March 2010] [05:21:55] <mato> so you want to detect and respond to that suckiness somehow?
| [Wednesday 31 March 2010] [05:21:57] <mato> right?
| [Wednesday 31 March 2010] [05:21:57] <pquerna>  also I guess no native encryption.. so vpn/ipsec everything?
| [Wednesday 31 March 2010] [05:22:14] <pquerna>  ya, at least log it a bit, ideally we switch whcih endpoint we are using
| [Wednesday 31 March 2010] [05:22:37] <mato> no encryption, so yes, vpn/ipsec... designing good encryption is hard and vpn/ipsec is proven and understood
| [Wednesday 31 March 2010] [05:22:43] <mato> we try not to reinvent the wheel
| [Wednesday 31 March 2010] [05:22:56] <pquerna>  :)
| [Wednesday 31 March 2010] [05:23:10] <mato> as for detecting the network...
| [Wednesday 31 March 2010] [05:23:28] <mato> what i would suggest is a side channel / monitoring messages using 0mq
| [Wednesday 31 March 2010] [05:23:41] <mato> so you periodically ping the other end and test latency
| [Wednesday 31 March 2010] [05:24:22] <mato> and if you start getting bad figures back your application can take evasive action/start paging netops people/whatever...
| [Wednesday 31 March 2010] [05:26:10] <pquerna>  thanks for answering all my questions
| [Wednesday 31 March 2010] [05:26:21] <mato> also, flow control (high/low water mark) on sockets has been implemented in 0mq
| [Wednesday 31 March 2010] [05:26:37] <pquerna>  yes, thank goodness
| [Wednesday 31 March 2010] [05:26:59] <pquerna>  i actually want a mode where it throws away exploding queues, but meh
| [Wednesday 31 March 2010] [05:27:00] <mato> so that can also be used to good effect and may be enough for some applications
| [Wednesday 31 March 2010] [05:27:39] <mato> pquerna: you're welcome
| [Wednesday 31 March 2010] [05:27:53] <mato> pquerna: have fun, tell a friend, come back, contribute, sponsor, etc etc :-)
| [Wednesday 31 March 2010] [05:37:44] <sustrik>  mato: test env is running
| [Wednesday 31 March 2010] [05:37:48] <mato> sustrik: thanks
| [Wednesday 31 March 2010] [07:12:44] <mato> sustrik: ok, pgm on trunk has regressed. see my emails
| [Wednesday 31 March 2010] [07:12:54] <mato> sustrik: i don't think there's anything else i can do now
| [Wednesday 31 March 2010] [07:13:02] <sustrik>  mato: ok, seen that
| [Wednesday 31 March 2010] [07:13:05] <mato> sustrik: will have to wait for feedback from steven
| [Wednesday 31 March 2010] [07:13:17] <mato> sustrik: so i'll shut down the servers...
| [Wednesday 31 March 2010] [07:13:17] <sustrik>  can i switch the boxes off now?
| [Wednesday 31 March 2010] [07:13:22] <sustrik>  ok
| [Wednesday 31 March 2010] [07:14:24] <mato> you can unplug it once they all switch off
| [Wednesday 31 March 2010] [08:21:41] <sjampoo>  Hi, i do not completely understand zmq_init(appthreads, iothreads), are there any pointers with more information? What happens when i access a context with more threads then appthreads specified?  Do i need to worry about iothreads, are there any guidelines for its size? 
| [Wednesday 31 March 2010] [08:23:17] <sustrik>  sjampoo: if you've specified say 3 application threads
| [Wednesday 31 March 2010] [08:23:24] <sustrik>  and have sockets opened from 3 threads
| [Wednesday 31 March 2010] [08:23:33] <sustrik>  and try to open a socket from 4th thread
| [Wednesday 31 March 2010] [08:23:40] <sustrik>  you'll get EMTHREAD error
| [Wednesday 31 March 2010] [08:24:07] <sustrik>  as for I/O threads think of them as of CPU cores
| [Wednesday 31 March 2010] [08:24:14] <sustrik>  say you have 8-core box
| [Wednesday 31 March 2010] [08:24:33] <sustrik>  you want 2 cores to handle to background part of 0MQ work
| [Wednesday 31 March 2010] [08:24:50] <sustrik>  use 2 I/O threads then
| [Wednesday 31 March 2010] [08:25:05] <sjampoo>  Ok I understand IOThreads now, thanks.
| [Wednesday 31 March 2010] [08:25:23] <sjampoo>  Concerning appthreads, i am planning to use it in a singe event loop with multiple light weight threads.
| [Wednesday 31 March 2010] [08:25:53] <sustrik>  each thread will have a socket open, right?
| [Wednesday 31 March 2010] [08:25:56] <sjampoo>  So i will want to open multiple ZMQ sockets on a single context and use them non-blocking, should i increase the app threads number to the amount of sockets? 
| [Wednesday 31 March 2010] [08:26:23] <sustrik>  it's number of threads you'll be using 0MQ from
| [Wednesday 31 March 2010] [08:26:34] <sustrik>  so if you are using it from 1 thread, specify 1
| [Wednesday 31 March 2010] [08:26:51] <sustrik>  is you have your event loop thread + 5 worker threads, specify 6
| [Wednesday 31 March 2010] [08:27:03] <sjampoo>  aha
| [Wednesday 31 March 2010] [08:27:33] <sjampoo>  Would 10.000 be a weird big number? 
| [Wednesday 31 March 2010] [08:28:21] <sustrik>  whoa, what kind of application are you writing?
| [Wednesday 31 March 2010] [08:28:25] <sustrik>  HPC cluster?
| [Wednesday 31 March 2010] [08:28:35] <sjampoo>  I am planning to integrate it with websockets where each user would get its own ZMQ thread.
| [Wednesday 31 March 2010] [08:28:59] <sustrik>  you are planning for 10000 threads on a single box?
| [Wednesday 31 March 2010] [08:29:10] <sustrik>  how many CPU cores there are?
| [Wednesday 31 March 2010] [08:29:14] <sjampoo>  10000 lightweight threads
| [Wednesday 31 March 2010] [08:29:33] <sjampoo>  (with stackless Python)
| [Wednesday 31 March 2010] [08:29:49] <sustrik>  ah, you mean python pseudo-threads?
| [Wednesday 31 March 2010] [08:29:54] <sustrik>  or green threads
| [Wednesday 31 March 2010] [08:29:55] <sjampoo>  yes.
| [Wednesday 31 March 2010] [08:29:58] <sjampoo>  Green Threads
| [Wednesday 31 March 2010] [08:30:01] <sjampoo>  Tasklets really
| [Wednesday 31 March 2010] [08:30:27] <sustrik>  afaik all python green threads map to a single OS thread
| [Wednesday 31 March 2010] [08:30:38] <sustrik>  so specify 1
| [Wednesday 31 March 2010] [08:30:42] <sjampoo>  Ok.
| [Wednesday 31 March 2010] [08:31:09] <sjampoo>  So that appthread does in no way limit the amount of sockets i can open is my real question i think.
| [Wednesday 31 March 2010] [08:31:48] <sjampoo>  (I mean the appthread setting to zmq_init)
| [Wednesday 31 March 2010] [08:33:53] <sustrik>  no, it's just number of threads
| [Wednesday 31 March 2010] [08:33:59] <sustrik>  even if you have 1 thread
| [Wednesday 31 March 2010] [08:34:05] <sustrik>  you can open 1000 sockets
| [Wednesday 31 March 2010] [08:34:23] <sjampoo>  ok thanks for clearing that up for me
| [Wednesday 31 March 2010] [08:34:45] <sustrik>  np
| [Wednesday 31 March 2010] [08:34:45] <sjampoo>  ZMQ is really nice, did some benchmarks its really fast
| [Wednesday 31 March 2010] [08:34:52] <sustrik>  we've tried :)
| [Wednesday 31 March 2010] [08:41:49] <sjampoo>  I also love the design of the website and the documentation. But it took me some time to understand the level at which ZMQ operates, which is pretty low compared to other messaging systems. But, really like it for that. 
| [Wednesday 31 March 2010] [08:46:59] <sustrik>  sjampoo: if you have any suggestion how to organise the documentation better
| [Wednesday 31 March 2010] [08:47:12] <sustrik>  give us a hint
| [Wednesday 31 March 2010] [08:47:37] <sustrik>  what kind of info would you have preferred to see first?
| [Wednesday 31 March 2010] [08:47:39] <sustrik>  etc.
| [Wednesday 31 March 2010] [08:48:33] <sjampoo>  i'll give it some thought and might get back to it on the mailing list
| [Wednesday 31 March 2010] [08:49:03] <sustrik>  sjampoo: thanks
| [Wednesday 31 March 2010] [08:49:54] <sjampoo>  I think the main thing that i know understand is that ZMQ isn't really a messaging system but an awesome socket implementation on which you can build your own MS.
| [Wednesday 31 March 2010] [08:51:34] <sustrik>  it depends on the exact meaning of "messaging system"
| [Wednesday 31 March 2010] [08:51:46] <sustrik>  the problem is that the terminology is pretty vague
| [Wednesday 31 March 2010] [08:52:37] <sustrik>  so what we thought of was ditching all the "messaging middleware" terminology on the front page
| [Wednesday 31 March 2010] [08:52:52] <sustrik>  and instead presenting what you can do with the product
| [Wednesday 31 March 2010] [08:53:05] <sustrik>  something like:
| [Wednesday 31 March 2010] [08:53:15] <sustrik>  "write a server in 10 lines of code"
| [Wednesday 31 March 2010] [08:54:06] <sjampoo>  I completely agree with that.  The problem with my specific case is, that I started looking at ZMQ after i read about a comparison on the SecondLife wiki, it is different than RabbitMQ or ActiveMQ.
| [Wednesday 31 March 2010] [08:54:54] <sustrik>  yup, but the difference is hard to explain, we've been struggling with explaining it for years
| [Wednesday 31 March 2010] [08:55:06] <sustrik>  i mean, explaining it in 1-2 paragrahs on the frontpage
| [Wednesday 31 March 2010] [08:55:38] <sustrik>  so that all kinds of people that come to the website get at least a dim idea of what the hell is it about
| [Wednesday 31 March 2010] [09:16:53] <sjampoo>  I think a good analogy would be that where ActiveMQ/RabbitMQ gives you a post office, ZMQ gives you couriers. While being lightweight and fast you do need to take care of them yourself. 
| [Wednesday 31 March 2010] [09:21:35] <sustrik>  hm, makes sense
| [Wednesday 31 March 2010] [09:21:55] <sustrik>  what about "a new layer of Internet stack"
| [Wednesday 31 March 2010] [09:22:10] <sustrik>  + a picture showing Ethernet, IP, TCP, UDP and 0MQ on top of that?
| [Wednesday 31 March 2010] [09:24:56] <sjampoo>  yes that makes sense, i personally think of ZMQ as TCP/IP covered in sugar. All the flexibility without the headaches. 
| [Wednesday 31 March 2010] [09:25:52] <sjampoo>  I think it makes a perfect combination with high level languages such as Python.
| [Wednesday 31 March 2010] [09:36:42] <sjampoo>  I really think it is important to stress the level at which ZMQ operates. I remember that i read the article: 'broker vs brokerless' a while ago and after finishing it started looking for broker/directory service options. 
| [Wednesday 31 March 2010] [09:37:08] <sjampoo>  Now that i understand what ZMQ provides and doesn't provide it makes sense. 
| [Wednesday 31 March 2010] [09:50:10] <sustrik>  ok, i'll try to improve the frontpage...
| [Wednesday 31 March 2010] [10:10:47] Part   hurtonm has left this channel.
| [Wednesday 31 March 2010] [10:13:31] <mato> sustrik: i had an idea
| [Wednesday 31 March 2010] [10:13:37] <mato> sustrik: are you around?
| [Wednesday 31 March 2010] [10:37:12] <CIA-5>    zeromq2: 03Martin Hurton 07master * r37fd1a7 10/ src/rep.cpp : Handle full-pipe for REP sockets more gracefully - http://bit.ly/aAszD1
| [Wednesday 31 March 2010] [12:10:01] <sjampoo>  Hmm what is causing the huge interest spike in ZMQ at the moment? I see lots of people bookmarking it at delicious today and yesterday. 
| [Wednesday 31 March 2010] [12:14:09] <sjampoo>  ah, probably the 'AMQP fundamentally flawed' article by Hintjes (which hit Hacker News)
| [Wednesday 31 March 2010] [12:16:03] <squeeky>  few people tweeted about it.
| [Wednesday 31 March 2010] [12:16:13] <sjampoo>  yah saw that too
| [Wednesday 31 March 2010] [15:30:06] <mikko>    howdy
| [Wednesday 31 March 2010] [17:02:20]     * impl looks at mikko 
| [Wednesday 31 March 2010] [20:03:20] <wutang>   I am very familiar with 29west...are there any documents out there describing the differences in architecture and possible API differences between the two?
| [Wednesday 31 March 2010] [20:03:49] <wutang>   Also, I haven't found many examples beyond the most basic...are there any good repositories of examples or real applications that are open source?
| [Wednesday 31 March 2010] [21:34:26] Part   gz_ has left this channel ("Konversation terminated!").
| [Monday 29 March 2010] [18:37:34] Part  dh1r has left this channel.
| 
| *** Logfile started
| *** on Mon Mar 29 19:06:08 2010
| 
| [Monday 29 March 2010] [19:06:08] Topic The channel topic is "Welcome!".
| [Monday 29 March 2010] [19:06:08] Topic The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Monday 29 March 2010] [19:06:14] Mode  Channel modes: no messages from outside, topic protection
| [Monday 29 March 2010] [19:06:14] Created   This channel was created on 2010-02-05 10:44.
| 
| *** Logfile started
| *** on Mon Mar 29 20:26:50 2010
| 
| [Monday 29 March 2010] [20:26:50] Topic The channel topic is "Welcome!".
| [Monday 29 March 2010] [20:26:50] Topic The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Monday 29 March 2010] [20:26:56] Mode  Channel modes: no messages from outside, topic protection
| [Monday 29 March 2010] [20:26:56] Created   This channel was created on 2010-02-05 10:44.
| 
| *** Logfile started
| *** on Mon Mar 29 21:53:10 2010
| 
| [Monday 29 March 2010] [21:53:10] Topic The channel topic is "Welcome!".
| [Monday 29 March 2010] [21:53:10] Topic The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Monday 29 March 2010] [21:53:16] Mode  Channel modes: no messages from outside, topic protection
| [Monday 29 March 2010] [21:53:16] Created   This channel was created on 2010-02-05 10:44.
| 
| *** Logfile started
| *** on Tue Mar 30 00:16:23 2010
| 
| [Tuesday 30 March 2010] [00:16:23] Topic    The channel topic is "Welcome!".
| [Tuesday 30 March 2010] [00:16:23] Topic    The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Tuesday 30 March 2010] [00:16:29] Mode Channel modes: no messages from outside, topic protection
| [Tuesday 30 March 2010] [00:16:29] Created  This channel was created on 2010-02-05 10:44.
| [Tuesday 30 March 2010] [05:34:39] <vtl>    sustrik: hi! which error code non-blocking zmq_msg_recv() will return on m$ windows if there's no bytes to read?
| 
| *** Logfile started
| *** on Tue Mar 30 20:06:31 2010
| 
| [Tuesday 30 March 2010] [20:06:31] Topic    The channel topic is "Welcome!".
| [Tuesday 30 March 2010] [20:06:31] Topic    The topic was set by dermoth!~dermoth@205.151.111.9 on 2010-02-05 16:34.
| [Tuesday 30 March 2010] [20:06:37] Mode Channel modes: no messages from outside, topic protection
| [Tuesday 30 March 2010] [20:06:37] Created  This channel was created on 2010-02-05 10:44.
| [Tuesday 30 March 2010] [20:14:02] <davelee>    hi. So i've installed zeromq. There doesn't seem to be any docs about how to actually start the service ... ? 
| [Tuesday 30 March 2010] [20:14:41] <davelee>    (i'm on snow leopard FWIW)
| [Tuesday 30 March 2010] [20:15:05] <davelee>    there's a zmq_queue binary which wants a config file ..
| [Wednesday 31 March 2010] [01:45:29] <sustrik>  davelee: what are you trying to do?
| [Wednesday 31 March 2010] [02:44:46] <davelee>  sustrik: I was just trying to get "up and running"
| [Wednesday 31 March 2010] [02:45:10] <davelee>  to get the ruby gem demo / test running
| [Wednesday 31 March 2010] [02:45:21] <sustrik>  let me see...
| [Wednesday 31 March 2010] [02:45:38] <davelee>  i'm assuming that, like rabbitmq, there's a server you need to run  ... ? 
| [Wednesday 31 March 2010] [02:45:44] <davelee>  or is it just a p2p scenario
| [Wednesday 31 March 2010] [02:45:49] <sustrik>  both
| [Wednesday 31 March 2010] [02:45:55] <sustrik>  it depends on what you want to do
| [Wednesday 31 March 2010] [02:46:11] <sustrik>  if you just want to test it, run the perf tests
| [Wednesday 31 March 2010] [02:46:27] <sustrik>  rbzmq/perf
| [Wednesday 31 March 2010] [02:46:40] <sustrik>  someting like:
| [Wednesday 31 March 2010] [02:47:05] <sustrik>  ruby local_thr tcp://127.0.0.1:5555 1 10000
| [Wednesday 31 March 2010] [02:47:09] <sustrik>  then:
| [Wednesday 31 March 2010] [02:47:25] <sustrik>  ruby remote_thr.rb tcp://127.0.0.1:5555 1 10000
| [Wednesday 31 March 2010] [02:47:46] <davelee>  in different terminals (ie, are they communicating)? 
| [Wednesday 31 March 2010] [02:48:01] <sustrik>  yes, in different terminals
| [Wednesday 31 March 2010] [02:48:10] <sustrik>  or you can try it on two boxes
| [Wednesday 31 March 2010] [02:48:33] <sustrik>  you have to supply real IP addresses in the latter case of course
| [Wednesday 31 March 2010] [02:48:40] <sustrik>  (or names)
| [Wednesday 31 March 2010] [02:49:01] <davelee>  ok, that's the part which confused me. I ran ruby local_lat.rb tcp://127.0.0.1:5555 1 100
| [Wednesday 31 March 2010] [02:49:23] <sustrik>  yeah, you need the other endpoint
| [Wednesday 31 March 2010] [02:49:29] <davelee>  and it did nothing - i was expecting it'd want to connect to a broker / etc and complain, at which point I'd go start something
| [Wednesday 31 March 2010] [02:49:32] <davelee>  yep rgr
| [Wednesday 31 March 2010] [02:51:27] <davelee>  ok, that seemed to work; local_thr.rb closed with a message about throughput; remote_thr.rb remains running
| [Wednesday 31 March 2010] [02:51:45] <sustrik>  yup
| [Wednesday 31 March 2010] [02:53:09] <davelee>  so ... are there any other examples of how to actually use the ruby gem ?
| [Wednesday 31 March 2010] [02:53:34] <davelee>  the amqp gem is a bit arcane but reasonably easy to figure out by looking at the examples 
| [Wednesday 31 March 2010] [02:53:54] <davelee>  zmq gem has these perf scripts, and i've got a basic idea from looking at them 
| [Wednesday 31 March 2010] [02:54:48] <davelee>  oh right, time to look @ the C bindings ... 
| [Wednesday 31 March 2010] [02:55:56] <davelee>  in that case,  I'll assume there's not yet a higher-level ruby library - it's just a wrapper around the C libs? 
| [Wednesday 31 March 2010] [02:56:47] <davelee>  anyway, gotta go. thanks for the help 
| [Wednesday 31 March 2010] [02:57:01] Part   davelee has left this channel.
| [Wednesday 31 March 2010] [04:04:55] Nick   mato_ is now known as mato.
| [Wednesday 31 March 2010] [05:05:11] <mato> sustrik: take a look at my proposals regarding MSG_MORE when you get a moment
| [Wednesday 31 March 2010] [05:05:33] <mato> sustrik: i think they are nice and consistent
| [Wednesday 31 March 2010] [05:07:30] <pquerna>  hi, for $work we use lots of txAMQP and rabbitmq, but am unhappy with various parts.  I'm trying to gork zmq, but really it seems to just be a transport layer, abit a cool one that abstracts more than most tcp based transports.  
| [Wednesday 31 March 2010] [05:07:51] <pquerna>  It seems hinted at that you need to build your own mechnisims for configuration management and distribution of how to communicate between machines
| [Wednesday 31 March 2010] [05:08:28] <pquerna>  is this something zmq intends to do more of, I mean I look at for example http://api.zeromq.org/zmq_queue.html , and it makes me feel like those more higher level services just don't exist yet?
| [Wednesday 31 March 2010] [05:09:01] <mato> pquerna: the device implementations do exist, but they're still considered early days, so are not documented
| [Wednesday 31 March 2010] [05:09:41] <mato> pquerna: however, there are people using e.g. zmq_queue to successfully implement shared queues
| [Wednesday 31 March 2010] [05:10:23] <mato> and yes, zmq devices are something that we will be focusing on
| [Wednesday 31 March 2010] [05:12:20] <pquerna>  okay, and what about the brokerless design -- i read throguh http://www.zeromq.org/whitepapers:brokerless and yeha, I've done this before with my own wire format about 2 jobs back :) but doesn't seem like there are bits on the open source side of zmq that do it yet (?)
| [Wednesday 31 March 2010] [05:13:14] <pquerna>  or rather, its left as an exercise to the reader...
| [Wednesday 31 March 2010] [05:13:28] <mato> well, it depends on what you *need* from the broker
| [Wednesday 31 March 2010] [05:13:59] <mato> all the bits are in place, and if you look at recent discussion on the mailing list, you'll see that there is talk of embedding devices inside applications
| [Wednesday 31 March 2010] [05:14:25] <mato> so instead of zmq_queue being a binary, it's a call to e.g. zmq_queue_device(...) inside your app
| [Wednesday 31 March 2010] [05:14:39] <pquerna>  ah
| [Wednesday 31 March 2010] [05:14:49] <mato> which means that you decide where your "broker" bits go, if you need them
| [Wednesday 31 March 2010] [05:15:12] <pquerna>  ya, we have a mix of use cases, some of them definately could use somehting as simple as that.
| [Wednesday 31 March 2010] [05:15:35] <pquerna>  most of ours are either single writer, lots of readers, or single reader, lots of writers, both of which can fit that just fine.
| [Wednesday 31 March 2010] [05:16:30] <mato> yep, and you can probably do a lot of that without any devices at all
| [Wednesday 31 March 2010] [05:16:46] <mato> since 0mq sockets let you talk to multiple endpoints
| [Wednesday 31 March 2010] [05:17:05] <mato> take a look at the zmq_socket documentation, it describes the messaging patterns you can use
| [Wednesday 31 March 2010] [05:17:18] <mato> http://api.zeromq.org/zmq_socket.html
| [Wednesday 31 March 2010] [05:17:30] <mato> (yes, it's terse, but it's a reference so you should get the idea)
| [Wednesday 31 March 2010] [05:18:09] <mato> you might also want to skim the LWN article if you haven't read it already
| [Wednesday 31 March 2010] [05:18:14] <mato> http://lwn.net/Articles/370307/
| [Wednesday 31 March 2010] [05:19:08] <pquerna>  one thing I don't quite understand is error handling, say in the simplest case of a p2p tcp connection -- how much does zmq retry underneath, is there any way to hook in my own logging subsystem to say 'hey tcp ain't working to host xxx'
| [Wednesday 31 March 2010] [05:19:30] <mato> no there isn't, and that's kind of deliberate
| [Wednesday 31 March 2010] [05:19:55] <mato> since even with tcp you don't get a real/instant notification of e.g. "the other end went away"
| [Wednesday 31 March 2010] [05:19:59] <pquerna>  sure
| [Wednesday 31 March 2010] [05:20:06] <pquerna>  (unless you wait for a reply)
| [Wednesday 31 March 2010] [05:20:09] <mato> precisely
| [Wednesday 31 March 2010] [05:21:01] <mato> which you can also do with 0mq, but the point is that a 0mq socket lets you access an asynchronous queue
| [Wednesday 31 March 2010] [05:21:29] <pquerna>  right, we just do lots of... multi-data center stuff on cloud servers.
| [Wednesday 31 March 2010] [05:21:34] <pquerna>  the network can.. be... sucky.
| [Wednesday 31 March 2010] [05:21:55] <mato> so you want to detect and respond to that suckiness somehow?
| [Wednesday 31 March 2010] [05:21:57] <mato> right?
| [Wednesday 31 March 2010] [05:21:57] <pquerna>  also I guess no native encryption.. so vpn/ipsec everything?
| [Wednesday 31 March 2010] [05:22:14] <pquerna>  ya, at least log it a bit, ideally we switch whcih endpoint we are using
| [Wednesday 31 March 2010] [05:22:37] <mato> no encryption, so yes, vpn/ipsec... designing good encryption is hard and vpn/ipsec is proven and understood
| [Wednesday 31 March 2010] [05:22:43] <mato> we try not to reinvent the wheel
| [Wednesday 31 March 2010] [05:22:56] <pquerna>  :)
| [Wednesday 31 March 2010] [05:23:10] <mato> as for detecting the network...
| [Wednesday 31 March 2010] [05:23:28] <mato> what i would suggest is a side channel / monitoring messages using 0mq
| [Wednesday 31 March 2010] [05:23:41] <mato> so you periodically ping the other end and test latency
| [Wednesday 31 March 2010] [05:24:22] <mato> and if you start getting bad figures back your application can take evasive action/start paging netops people/whatever...
| [Wednesday 31 March 2010] [05:26:10] <pquerna>  thanks for answering all my questions
| [Wednesday 31 March 2010] [05:26:21] <mato> also, flow control (high/low water mark) on sockets has been implemented in 0mq
| [Wednesday 31 March 2010] [05:26:37] <pquerna>  yes, thank goodness
| [Wednesday 31 March 2010] [05:26:59] <pquerna>  i actually want a mode where it throws away exploding queues, but meh
| [Wednesday 31 March 2010] [05:27:00] <mato> so that can also be used to good effect and may be enough for some applications
| [Wednesday 31 March 2010] [05:27:39] <mato> pquerna: you're welcome
| [Wednesday 31 March 2010] [05:27:53] <mato> pquerna: have fun, tell a friend, come back, contribute, sponsor, etc etc :-)
| [Wednesday 31 March 2010] [05:37:44] <sustrik>  mato: test env is running
| [Wednesday 31 March 2010] [05:37:48] <mato> sustrik: thanks
| [Wednesday 31 March 2010] [07:12:44] <mato> sustrik: ok, pgm on trunk has regressed. see my emails
| [Wednesday 31 March 2010] [07:12:54] <mato> sustrik: i don't think there's anything else i can do now
| [Wednesday 31 March 2010] [07:13:02] <sustrik>  mato: ok, seen that
| [Wednesday 31 March 2010] [07:13:05] <mato> sustrik: will have to wait for feedback from steven
| [Wednesday 31 March 2010] [07:13:17] <mato> sustrik: so i'll shut down the servers...
| [Wednesday 31 March 2010] [07:13:17] <sustrik>  can i switch the boxes off now?
| [Wednesday 31 March 2010] [07:13:22] <sustrik>  ok
| [Wednesday 31 March 2010] [07:14:24] <mato> you can unplug it once they all switch off
| [Wednesday 31 March 2010] [08:21:41] <sjampoo>  Hi, i do not completely understand zmq_init(appthreads, iothreads), are there any pointers with more information? What happens when i access a context with more threads then appthreads specified?  Do i need to worry about iothreads, are there any guidelines for its size? 
| [Wednesday 31 March 2010] [08:23:17] <sustrik>  sjampoo: if you've specified say 3 application threads
| [Wednesday 31 March 2010] [08:23:24] <sustrik>  and have sockets opened from 3 threads
| [Wednesday 31 March 2010] [08:23:33] <sustrik>  and try to open a socket from 4th thread
| [Wednesday 31 March 2010] [08:23:40] <sustrik>  you'll get EMTHREAD error
| [Wednesday 31 March 2010] [08:24:07] <sustrik>  as for I/O threads think of them as of CPU cores
| [Wednesday 31 March 2010] [08:24:14] <sustrik>  say you have 8-core box
| [Wednesday 31 March 2010] [08:24:33] <sustrik>  you want 2 cores to handle to background part of 0MQ work
| [Wednesday 31 March 2010] [08:24:50] <sustrik>  use 2 I/O threads then
| [Wednesday 31 March 2010] [08:25:05] <sjampoo>  Ok I understand IOThreads now, thanks.
| [Wednesday 31 March 2010] [08:25:23] <sjampoo>  Concerning appthreads, i am planning to use it in a singe event loop with multiple light weight threads.
| [Wednesday 31 March 2010] [08:25:53] <sustrik>  each thread will have a socket open, right?
| [Wednesday 31 March 2010] [08:25:56] <sjampoo>  So i will want to open multiple ZMQ sockets on a single context and use them non-blocking, should i increase the app threads number to the amount of sockets? 
| [Wednesday 31 March 2010] [08:26:23] <sustrik>  it's number of threads you'll be using 0MQ from
| [Wednesday 31 March 2010] [08:26:34] <sustrik>  so if you are using it from 1 thread, specify 1
| [Wednesday 31 March 2010] [08:26:51] <sustrik>  is you have your event loop thread + 5 worker threads, specify 6
| [Wednesday 31 March 2010] [08:27:03] <sjampoo>  aha
| [Wednesday 31 March 2010] [08:27:33] <sjampoo>  Would 10.000 be a weird big number? 
| [Wednesday 31 March 2010] [08:28:21] <sustrik>  whoa, what kind of application are you writing?
| [Wednesday 31 March 2010] [08:28:25] <sustrik>  HPC cluster?
| [Wednesday 31 March 2010] [08:28:35] <sjampoo>  I am planning to integrate it with websockets where each user would get its own ZMQ thread.
| [Wednesday 31 March 2010] [08:28:59] <sustrik>  you are planning for 10000 threads on a single box?
| [Wednesday 31 March 2010] [08:29:10] <sustrik>  how many CPU cores there are?
| [Wednesday 31 March 2010] [08:29:14] <sjampoo>  10000 lightweight threads
| [Wednesday 31 March 2010] [08:29:33] <sjampoo>  (with stackless Python)
| [Wednesday 31 March 2010] [08:29:49] <sustrik>  ah, you mean python pseudo-threads?
| [Wednesday 31 March 2010] [08:29:54] <sustrik>  or green threads
| [Wednesday 31 March 2010] [08:29:55] <sjampoo>  yes.
| [Wednesday 31 March 2010] [08:29:58] <sjampoo>  Green Threads
| [Wednesday 31 March 2010] [08:30:01] <sjampoo>  Tasklets really
| [Wednesday 31 March 2010] [08:30:27] <sustrik>  afaik all python green threads map to a single OS thread
| [Wednesday 31 March 2010] [08:30:38] <sustrik>  so specify 1
| [Wednesday 31 March 2010] [08:30:42] <sjampoo>  Ok.
| [Wednesday 31 March 2010] [08:31:09] <sjampoo>  So that appthread does in no way limit the amount of sockets i can open is my real question i think.
| [Wednesday 31 March 2010] [08:31:48] <sjampoo>  (I mean the appthread setting to zmq_init)
| [Wednesday 31 March 2010] [08:33:53] <sustrik>  no, it's just number of threads
| [Wednesday 31 March 2010] [08:33:59] <sustrik>  even if you have 1 thread
| [Wednesday 31 March 2010] [08:34:05] <sustrik>  you can open 1000 sockets
| [Wednesday 31 March 2010] [08:34:23] <sjampoo>  ok thanks for clearing that up for me
| [Wednesday 31 March 2010] [08:34:45] <sustrik>  np
| [Wednesday 31 March 2010] [08:34:45] <sjampoo>  ZMQ is really nice, did some benchmarks its really fast
| [Wednesday 31 March 2010] [08:34:52] <sustrik>  we've tried :)
| [Wednesday 31 March 2010] [08:41:49] <sjampoo>  I also love the design of the website and the documentation. But it took me some time to understand the level at which ZMQ operates, which is pretty low compared to other messaging systems. But, really like it for that. 
| [Wednesday 31 March 2010] [08:46:59] <sustrik>  sjampoo: if you have any suggestion how to organise the documentation better
| [Wednesday 31 March 2010] [08:47:12] <sustrik>  give us a hint
| [Wednesday 31 March 2010] [08:47:37] <sustrik>  what kind of info would you have preferred to see first?
| [Wednesday 31 March 2010] [08:47:39] <sustrik>  etc.
| [Wednesday 31 March 2010] [08:48:33] <sjampoo>  i'll give it some thought and might get back to it on the mailing list
| [Wednesday 31 March 2010] [08:49:03] <sustrik>  sjampoo: thanks
| [Wednesday 31 March 2010] [08:49:54] <sjampoo>  I think the main thing that i know understand is that ZMQ isn't really a messaging system but an awesome socket implementation on which you can build your own MS.
| [Wednesday 31 March 2010] [08:51:34] <sustrik>  it depends on the exact meaning of "messaging system"
| [Wednesday 31 March 2010] [08:51:46] <sustrik>  the problem is that the terminology is pretty vague
| [Wednesday 31 March 2010] [08:52:37] <sustrik>  so what we thought of was ditching all the "messaging middleware" terminology on the front page
| [Wednesday 31 March 2010] [08:52:52] <sustrik>  and instead presenting what you can do with the product
| [Wednesday 31 March 2010] [08:53:05] <sustrik>  something like:
| [Wednesday 31 March 2010] [08:53:15] <sustrik>  "write a server in 10 lines of code"
| [Wednesday 31 March 2010] [08:54:06] <sjampoo>  I completely agree with that.  The problem with my specific case is, that I started looking at ZMQ after i read about a comparison on the SecondLife wiki, it is different than RabbitMQ or ActiveMQ.
| [Wednesday 31 March 2010] [08:54:54] <sustrik>  yup, but the difference is hard to explain, we've been struggling with explaining it for years
| [Wednesday 31 March 2010] [08:55:06] <sustrik>  i mean, explaining it in 1-2 paragrahs on the frontpage
| [Wednesday 31 March 2010] [08:55:38] <sustrik>  so that all kinds of people that come to the website get at least a dim idea of what the hell is it about
| [Wednesday 31 March 2010] [09:16:53] <sjampoo>  I think a good analogy would be that where ActiveMQ/RabbitMQ gives you a post office, ZMQ gives you couriers. While being lightweight and fast you do need to take care of them yourself. 
| [Wednesday 31 March 2010] [09:21:35] <sustrik>  hm, makes sense
| [Wednesday 31 March 2010] [09:21:55] <sustrik>  what about "a new layer of Internet stack"
| [Wednesday 31 March 2010] [09:22:10] <sustrik>  + a picture showing Ethernet, IP, TCP, UDP and 0MQ on top of that?
| [Wednesday 31 March 2010] [09:24:56] <sjampoo>  yes that makes sense, i personally think of ZMQ as TCP/IP covered in sugar. All the flexibility without the headaches. 
| [Wednesday 31 March 2010] [09:25:52] <sjampoo>  I think it makes a perfect combination with high level languages such as Python.
| [Wednesday 31 March 2010] [09:36:42] <sjampoo>  I really think it is important to stress the level at which ZMQ operates. I remember that i read the article: 'broker vs brokerless' a while ago and after finishing it started looking for broker/directory service options. 
| [Wednesday 31 March 2010] [09:37:08] <sjampoo>  Now that i understand what ZMQ provides and doesn't provide it makes sense. 
| [Wednesday 31 March 2010] [09:50:10] <sustrik>  ok, i'll try to improve the frontpage...
| [Wednesday 31 March 2010] [10:10:47] Part   hurtonm has left this channel.
| [Wednesday 31 March 2010] [10:13:31] <mato> sustrik: i had an idea
| [Wednesday 31 March 2010] [10:13:37] <mato> sustrik: are you around?
| [Wednesday 31 March 2010] [10:37:12] <CIA-5>    zeromq2: 03Martin Hurton 07master * r37fd1a7 10/ src/rep.cpp : Handle full-pipe for REP sockets more gracefully - http://bit.ly/aAszD1
| [Wednesday 31 March 2010] [12:10:01] <sjampoo>  Hmm what is causing the huge interest spike in ZMQ at the moment? I see lots of people bookmarking it at delicious today and yesterday. 
| [Wednesday 31 March 2010] [12:14:09] <sjampoo>  ah, probably the 'AMQP fundamentally flawed' article by Hintjes (which hit Hacker News)
| [Wednesday 31 March 2010] [12:16:03] <squeeky>  few people tweeted about it.
| [Wednesday 31 March 2010] [12:16:13] <sjampoo>  yah saw that too
| [Wednesday 31 March 2010] [15:30:06] <mikko>    howdy
| [Wednesday 31 March 2010] [17:02:20]     * impl looks at mikko 
| [Wednesday 31 March 2010] [20:03:20] <wutang>   I am very familiar with 29west...are there any documents out there describing the differences in architecture and possible API differences between the two?
| [Wednesday 31 March 2010] [20:03:49] <wutang>   Also, I haven't found many examples beyond the most basic...are there any good repositories of examples or real applications that are open source?
| [Wednesday 31 March 2010] [21:34:26] Part   gz_ has left this channel ("Konversation terminated!").
| 
| *** Logfile started
| *** on Mon Mar 29 19:06:08 2010
| 
| 
| *** Logfile started
| *** on Mon Mar 29 20:26:50 2010
| 
| 
| *** Logfile started
| *** on Mon Mar 29 21:53:10 2010
| 
| 
| *** Logfile started
| *** on Tue Mar 30 00:16:23 2010
| 
| [Tuesday 30 March 2010] [05:34:39] <vtl>    sustrik: hi! which error code non-blocking zmq_msg_recv() will return on m$ windows if there's no bytes to read?
| 
| *** Logfile started
| *** on Tue Mar 30 20:06:31 2010
| 
| [Tuesday 30 March 2010] [20:14:02] <davelee>    hi. So i've installed zeromq. There doesn't seem to be any docs about how to actually start the service ... ? 
| [Tuesday 30 March 2010] [20:14:41] <davelee>    (i'm on snow leopard FWIW)
| [Tuesday 30 March 2010] [20:15:05] <davelee>    there's a zmq_queue binary which wants a config file ..
| [Wednesday 31 March 2010] [01:45:29] <sustrik>  davelee: what are you trying to do?
| [Wednesday 31 March 2010] [02:44:46] <davelee>  sustrik: I was just trying to get "up and running"
| [Wednesday 31 March 2010] [02:45:10] <davelee>  to get the ruby gem demo / test running
| [Wednesday 31 March 2010] [02:45:21] <sustrik>  let me see...
| [Wednesday 31 March 2010] [02:45:38] <davelee>  i'm assuming that, like rabbitmq, there's a server you need to run  ... ? 
| [Wednesday 31 March 2010] [02:45:44] <davelee>  or is it just a p2p scenario
| [Wednesday 31 March 2010] [02:45:49] <sustrik>  both
| [Wednesday 31 March 2010] [02:45:55] <sustrik>  it depends on what you want to do
| [Wednesday 31 March 2010] [02:46:11] <sustrik>  if you just want to test it, run the perf tests
| [Wednesday 31 March 2010] [02:46:27] <sustrik>  rbzmq/perf
| [Wednesday 31 March 2010] [02:46:40] <sustrik>  someting like:
| [Wednesday 31 March 2010] [02:47:05] <sustrik>  ruby local_thr tcp://127.0.0.1:5555 1 10000
| [Wednesday 31 March 2010] [02:47:09] <sustrik>  then:
| [Wednesday 31 March 2010] [02:47:25] <sustrik>  ruby remote_thr.rb tcp://127.0.0.1:5555 1 10000
| [Wednesday 31 March 2010] [02:47:46] <davelee>  in different terminals (ie, are they communicating)? 
| [Wednesday 31 March 2010] [02:48:01] <sustrik>  yes, in different terminals
| [Wednesday 31 March 2010] [02:48:10] <sustrik>  or you can try it on two boxes
| [Wednesday 31 March 2010] [02:48:33] <sustrik>  you have to supply real IP addresses in the latter case of course
| [Wednesday 31 March 2010] [02:48:40] <sustrik>  (or names)
| [Wednesday 31 March 2010] [02:49:01] <davelee>  ok, that's the part which confused me. I ran ruby local_lat.rb tcp://127.0.0.1:5555 1 100
| [Wednesday 31 March 2010] [02:49:23] <sustrik>  yeah, you need the other endpoint
| [Wednesday 31 March 2010] [02:49:29] <davelee>  and it did nothing - i was expecting it'd want to connect to a broker / etc and complain, at which point I'd go start something
| [Wednesday 31 March 2010] [02:49:32] <davelee>  yep rgr
| [Wednesday 31 March 2010] [02:51:27] <davelee>  ok, that seemed to work; local_thr.rb closed with a message about throughput; remote_thr.rb remains running
| [Wednesday 31 March 2010] [02:51:45] <sustrik>  yup
| [Wednesday 31 March 2010] [02:53:09] <davelee>  so ... are there any other examples of how to actually use the ruby gem ?
| [Wednesday 31 March 2010] [02:53:34] <davelee>  the amqp gem is a bit arcane but reasonably easy to figure out by looking at the examples 
| [Wednesday 31 March 2010] [02:53:54] <davelee>  zmq gem has these perf scripts, and i've got a basic idea from looking at them 
| [Wednesday 31 March 2010] [02:54:48] <davelee>  oh right, time to look @ the C bindings ... 
| [Wednesday 31 March 2010] [02:55:56] <davelee>  in that case,  I'll assume there's not yet a higher-level ruby library - it's just a wrapper around the C libs? 
| [Wednesday 31 March 2010] [02:56:47] <davelee>  anyway, gotta go. thanks for the help 
| [Wednesday 31 March 2010] [05:05:11] <mato> sustrik: take a look at my proposals regarding MSG_MORE when you get a moment
| [Wednesday 31 March 2010] [05:05:33] <mato> sustrik: i think they are nice and consistent
| [Wednesday 31 March 2010] [05:07:30] <pquerna>  hi, for $work we use lots of txAMQP and rabbitmq, but am unhappy with various parts.  I'm trying to gork zmq, but really it seems to just be a transport layer, abit a cool one that abstracts more than most tcp based transports.  
| [Wednesday 31 March 2010] [05:07:51] <pquerna>  It seems hinted at that you need to build your own mechnisims for configuration management and distribution of how to communicate between machines
| [Wednesday 31 March 2010] [05:08:28] <pquerna>  is this something zmq intends to do more of, I mean I look at for example http://api.zeromq.org/zmq_queue.html , and it makes me feel like those more higher level services just don't exist yet?
| [Wednesday 31 March 2010] [05:09:01] <mato> pquerna: the device implementations do exist, but they're still considered early days, so are not documented
| [Wednesday 31 March 2010] [05:09:41] <mato> pquerna: however, there are people using e.g. zmq_queue to successfully implement shared queues
| [Wednesday 31 March 2010] [05:10:23] <mato> and yes, zmq devices are something that we will be focusing on
| [Wednesday 31 March 2010] [05:12:20] <pquerna>  okay, and what about the brokerless design -- i read throguh http://www.zeromq.org/whitepapers:brokerless and yeha, I've done this before with my own wire format about 2 jobs back :) but doesn't seem like there are bits on the open source side of zmq that do it yet (?)
| [Wednesday 31 March 2010] [05:13:14] <pquerna>  or rather, its left as an exercise to the reader...
| [Wednesday 31 March 2010] [05:13:28] <mato> well, it depends on what you *need* from the broker
| [Wednesday 31 March 2010] [05:13:59] <mato> all the bits are in place, and if you look at recent discussion on the mailing list, you'll see that there is talk of embedding devices inside applications
| [Wednesday 31 March 2010] [05:14:25] <mato> so instead of zmq_queue being a binary, it's a call to e.g. zmq_queue_device(...) inside your app
| [Wednesday 31 March 2010] [05:14:39] <pquerna>  ah
| [Wednesday 31 March 2010] [05:14:49] <mato> which means that you decide where your "broker" bits go, if you need them
| [Wednesday 31 March 2010] [05:15:12] <pquerna>  ya, we have a mix of use cases, some of them definately could use somehting as simple as that.
| [Wednesday 31 March 2010] [05:15:35] <pquerna>  most of ours are either single writer, lots of readers, or single reader, lots of writers, both of which can fit that just fine.
| [Wednesday 31 March 2010] [05:16:30] <mato> yep, and you can probably do a lot of that without any devices at all
| [Wednesday 31 March 2010] [05:16:46] <mato> since 0mq sockets let you talk to multiple endpoints
| [Wednesday 31 March 2010] [05:17:05] <mato> take a look at the zmq_socket documentation, it describes the messaging patterns you can use
| [Wednesday 31 March 2010] [05:17:18] <mato> http://api.zeromq.org/zmq_socket.html
| [Wednesday 31 March 2010] [05:17:30] <mato> (yes, it's terse, but it's a reference so you should get the idea)
| [Wednesday 31 March 2010] [05:18:09] <mato> you might also want to skim the LWN article if you haven't read it already
| [Wednesday 31 March 2010] [05:18:14] <mato> http://lwn.net/Articles/370307/
| [Wednesday 31 March 2010] [05:19:08] <pquerna>  one thing I don't quite understand is error handling, say in the simplest case of a p2p tcp connection -- how much does zmq retry underneath, is there any way to hook in my own logging subsystem to say 'hey tcp ain't working to host xxx'
| [Wednesday 31 March 2010] [05:19:30] <mato> no there isn't, and that's kind of deliberate
| [Wednesday 31 March 2010] [05:19:55] <mato> since even with tcp you don't get a real/instant notification of e.g. "the other end went away"
| [Wednesday 31 March 2010] [05:19:59] <pquerna>  sure
| [Wednesday 31 March 2010] [05:20:06] <pquerna>  (unless you wait for a reply)
| [Wednesday 31 March 2010] [05:20:09] <mato> precisely
| [Wednesday 31 March 2010] [05:21:01] <mato> which you can also do with 0mq, but the point is that a 0mq socket lets you access an asynchronous queue
| [Wednesday 31 March 2010] [05:21:29] <pquerna>  right, we just do lots of... multi-data center stuff on cloud servers.
| [Wednesday 31 March 2010] [05:21:34] <pquerna>  the network can.. be... sucky.
| [Wednesday 31 March 2010] [05:21:55] <mato> so you want to detect and respond to that suckiness somehow?
| [Wednesday 31 March 2010] [05:21:57] <mato> right?
| [Wednesday 31 March 2010] [05:21:57] <pquerna>  also I guess no native encryption.. so vpn/ipsec everything?
| [Wednesday 31 March 2010] [05:22:14] <pquerna>  ya, at least log it a bit, ideally we switch whcih endpoint we are using
| [Wednesday 31 March 2010] [05:22:37] <mato> no encryption, so yes, vpn/ipsec... designing good encryption is hard and vpn/ipsec is proven and understood
| [Wednesday 31 March 2010] [05:22:43] <mato> we try not to reinvent the wheel
| [Wednesday 31 March 2010] [05:22:56] <pquerna>  :)
| [Wednesday 31 March 2010] [05:23:10] <mato> as for detecting the network...
| [Wednesday 31 March 2010] [05:23:28] <mato> what i would suggest is a side channel / monitoring messages using 0mq
| [Wednesday 31 March 2010] [05:23:41] <mato> so you periodically ping the other end and test latency
| [Wednesday 31 March 2010] [05:24:22] <mato> and if you start getting bad figures back your application can take evasive action/start paging netops people/whatever...
| [Wednesday 31 March 2010] [05:26:10] <pquerna>  thanks for answering all my questions
| [Wednesday 31 March 2010] [05:26:21] <mato> also, flow control (high/low water mark) on sockets has been implemented in 0mq
| [Wednesday 31 March 2010] [05:26:37] <pquerna>  yes, thank goodness
| [Wednesday 31 March 2010] [05:26:59] <pquerna>  i actually want a mode where it throws away exploding queues, but meh
| [Wednesday 31 March 2010] [05:27:00] <mato> so that can also be used to good effect and may be enough for some applications
| [Wednesday 31 March 2010] [05:27:39] <mato> pquerna: you're welcome
| [Wednesday 31 March 2010] [05:27:53] <mato> pquerna: have fun, tell a friend, come back, contribute, sponsor, etc etc :-)
| [Wednesday 31 March 2010] [05:37:44] <sustrik>  mato: test env is running
| [Wednesday 31 March 2010] [05:37:48] <mato> sustrik: thanks
| [Wednesday 31 March 2010] [07:12:44] <mato> sustrik: ok, pgm on trunk has regressed. see my emails
| [Wednesday 31 March 2010] [07:12:54] <mato> sustrik: i don't think there's anything else i can do now
| [Wednesday 31 March 2010] [07:13:02] <sustrik>  mato: ok, seen that
| [Wednesday 31 March 2010] [07:13:05] <mato> sustrik: will have to wait for feedback from steven
| [Wednesday 31 March 2010] [07:13:17] <mato> sustrik: so i'll shut down the servers...
| [Wednesday 31 March 2010] [07:13:17] <sustrik>  can i switch the boxes off now?
| [Wednesday 31 March 2010] [07:13:22] <sustrik>  ok
| [Wednesday 31 March 2010] [07:14:24] <mato> you can unplug it once they all switch off
| [Wednesday 31 March 2010] [08:21:41] <sjampoo>  Hi, i do not completely understand zmq_init(appthreads, iothreads), are there any pointers with more information? What happens when i access a context with more threads then appthreads specified?  Do i need to worry about iothreads, are there any guidelines for its size? 
| [Wednesday 31 March 2010] [08:23:17] <sustrik>  sjampoo: if you've specified say 3 application threads
| [Wednesday 31 March 2010] [08:23:24] <sustrik>  and have sockets opened from 3 threads
| [Wednesday 31 March 2010] [08:23:33] <sustrik>  and try to open a socket from 4th thread
| [Wednesday 31 March 2010] [08:23:40] <sustrik>  you'll get EMTHREAD error
| [Wednesday 31 March 2010] [08:24:07] <sustrik>  as for I/O threads think of them as of CPU cores
| [Wednesday 31 March 2010] [08:24:14] <sustrik>  say you have 8-core box
| [Wednesday 31 March 2010] [08:24:33] <sustrik>  you want 2 cores to handle to background part of 0MQ work
| [Wednesday 31 March 2010] [08:24:50] <sustrik>  use 2 I/O threads then
| [Wednesday 31 March 2010] [08:25:05] <sjampoo>  Ok I understand IOThreads now, thanks.
| [Wednesday 31 March 2010] [08:25:23] <sjampoo>  Concerning appthreads, i am planning to use it in a singe event loop with multiple light weight threads.
| [Wednesday 31 March 2010] [08:25:53] <sustrik>  each thread will have a socket open, right?
| [Wednesday 31 March 2010] [08:25:56] <sjampoo>  So i will want to open multiple ZMQ sockets on a single context and use them non-blocking, should i increase the app threads number to the amount of sockets? 
| [Wednesday 31 March 2010] [08:26:23] <sustrik>  it's number of threads you'll be using 0MQ from
| [Wednesday 31 March 2010] [08:26:34] <sustrik>  so if you are using it from 1 thread, specify 1
| [Wednesday 31 March 2010] [08:26:51] <sustrik>  is you have your event loop thread + 5 worker threads, specify 6
| [Wednesday 31 March 2010] [08:27:03] <sjampoo>  aha
| [Wednesday 31 March 2010] [08:27:33] <sjampoo>  Would 10.000 be a weird big number? 
| [Wednesday 31 March 2010] [08:28:21] <sustrik>  whoa, what kind of application are you writing?
| [Wednesday 31 March 2010] [08:28:25] <sustrik>  HPC cluster?
| [Wednesday 31 March 2010] [08:28:35] <sjampoo>  I am planning to integrate it with websockets where each user would get its own ZMQ thread.
| [Wednesday 31 March 2010] [08:28:59] <sustrik>  you are planning for 10000 threads on a single box?
| [Wednesday 31 March 2010] [08:29:10] <sustrik>  how many CPU cores there are?
| [Wednesday 31 March 2010] [08:29:14] <sjampoo>  10000 lightweight threads
| [Wednesday 31 March 2010] [08:29:33] <sjampoo>  (with stackless Python)
| [Wednesday 31 March 2010] [08:29:49] <sustrik>  ah, you mean python pseudo-threads?
| [Wednesday 31 March 2010] [08:29:54] <sustrik>  or green threads
| [Wednesday 31 March 2010] [08:29:55] <sjampoo>  yes.
| [Wednesday 31 March 2010] [08:29:58] <sjampoo>  Green Threads
| [Wednesday 31 March 2010] [08:30:01] <sjampoo>  Tasklets really
| [Wednesday 31 March 2010] [08:30:27] <sustrik>  afaik all python green threads map to a single OS thread
| [Wednesday 31 March 2010] [08:30:38] <sustrik>  so specify 1
| [Wednesday 31 March 2010] [08:30:42] <sjampoo>  Ok.
| [Wednesday 31 March 2010] [08:31:09] <sjampoo>  So that appthread does in no way limit the amount of sockets i can open is my real question i think.
| [Wednesday 31 March 2010] [08:31:48] <sjampoo>  (I mean the appthread setting to zmq_init)
| [Wednesday 31 March 2010] [08:33:53] <sustrik>  no, it's just number of threads
| [Wednesday 31 March 2010] [08:33:59] <sustrik>  even if you have 1 thread
| [Wednesday 31 March 2010] [08:34:05] <sustrik>  you can open 1000 sockets
| [Wednesday 31 March 2010] [08:34:23] <sjampoo>  ok thanks for clearing that up for me
| [Wednesday 31 March 2010] [08:34:45] <sustrik>  np
| [Wednesday 31 March 2010] [08:34:45] <sjampoo>  ZMQ is really nice, did some benchmarks its really fast
| [Wednesday 31 March 2010] [08:34:52] <sustrik>  we've tried :)
| [Wednesday 31 March 2010] [08:41:49] <sjampoo>  I also love the design of the website and the documentation. But it took me some time to understand the level at which ZMQ operates, which is pretty low compared to other messaging systems. But, really like it for that. 
| [Wednesday 31 March 2010] [08:46:59] <sustrik>  sjampoo: if you have any suggestion how to organise the documentation better
| [Wednesday 31 March 2010] [08:47:12] <sustrik>  give us a hint
| [Wednesday 31 March 2010] [08:47:37] <sustrik>  what kind of info would you have preferred to see first?
| [Wednesday 31 March 2010] [08:47:39] <sustrik>  etc.
| [Wednesday 31 March 2010] [08:48:33] <sjampoo>  i'll give it some thought and might get back to it on the mailing list
| [Wednesday 31 March 2010] [08:49:03] <sustrik>  sjampoo: thanks
| [Wednesday 31 March 2010] [08:49:54] <sjampoo>  I think the main thing that i know understand is that ZMQ isn't really a messaging system but an awesome socket implementation on which you can build your own MS.
| [Wednesday 31 March 2010] [08:51:34] <sustrik>  it depends on the exact meaning of "messaging system"
| [Wednesday 31 March 2010] [08:51:46] <sustrik>  the problem is that the terminology is pretty vague
| [Wednesday 31 March 2010] [08:52:37] <sustrik>  so what we thought of was ditching all the "messaging middleware" terminology on the front page
| [Wednesday 31 March 2010] [08:52:52] <sustrik>  and instead presenting what you can do with the product
| [Wednesday 31 March 2010] [08:53:05] <sustrik>  something like:
| [Wednesday 31 March 2010] [08:53:15] <sustrik>  "write a server in 10 lines of code"
| [Wednesday 31 March 2010] [08:54:06] <sjampoo>  I completely agree with that.  The problem with my specific case is, that I started looking at ZMQ after i read about a comparison on the SecondLife wiki, it is different than RabbitMQ or ActiveMQ.
| [Wednesday 31 March 2010] [08:54:54] <sustrik>  yup, but the difference is hard to explain, we've been struggling with explaining it for years
| [Wednesday 31 March 2010] [08:55:06] <sustrik>  i mean, explaining it in 1-2 paragrahs on the frontpage
| [Wednesday 31 March 2010] [08:55:38] <sustrik>  so that all kinds of people that come to the website get at least a dim idea of what the hell is it about
| [Wednesday 31 March 2010] [09:16:53] <sjampoo>  I think a good analogy would be that where ActiveMQ/RabbitMQ gives you a post office, ZMQ gives you couriers. While being lightweight and fast you do need to take care of them yourself. 
| [Wednesday 31 March 2010] [09:21:35] <sustrik>  hm, makes sense
| [Wednesday 31 March 2010] [09:21:55] <sustrik>  what about "a new layer of Internet stack"
| [Wednesday 31 March 2010] [09:22:10] <sustrik>  + a picture showing Ethernet, IP, TCP, UDP and 0MQ on top of that?
| [Wednesday 31 March 2010] [09:24:56] <sjampoo>  yes that makes sense, i personally think of ZMQ as TCP/IP covered in sugar. All the flexibility without the headaches. 
| [Wednesday 31 March 2010] [09:25:52] <sjampoo>  I think it makes a perfect combination with high level languages such as Python.
| [Wednesday 31 March 2010] [09:36:42] <sjampoo>  I really think it is important to stress the level at which ZMQ operates. I remember that i read the article: 'broker vs brokerless' a while ago and after finishing it started looking for broker/directory service options. 
| [Wednesday 31 March 2010] [09:37:08] <sjampoo>  Now that i understand what ZMQ provides and doesn't provide it makes sense. 
| [Wednesday 31 March 2010] [09:50:10] <sustrik>  ok, i'll try to improve the frontpage...
| [Wednesday 31 March 2010] [10:13:31] <mato> sustrik: i had an idea
| [Wednesday 31 March 2010] [10:13:37] <mato> sustrik: are you around?
| [Wednesday 31 March 2010] [10:37:12] <CIA-5>    zeromq2: 03Martin Hurton 07master * r37fd1a7 10/ src/rep.cpp : Handle full-pipe for REP sockets more gracefully - http://bit.ly/aAszD1
| [Wednesday 31 March 2010] [12:10:01] <sjampoo>  Hmm what is causing the huge interest spike in ZMQ at the moment? I see lots of people bookmarking it at delicious today and yesterday. 
| [Wednesday 31 March 2010] [12:14:09] <sjampoo>  ah, probably the 'AMQP fundamentally flawed' article by Hintjes (which hit Hacker News)
| [Wednesday 31 March 2010] [12:16:03] <squeeky>  few people tweeted about it.
| [Wednesday 31 March 2010] [12:16:13] <sjampoo>  yah saw that too
| [Wednesday 31 March 2010] [15:30:06] <mikko>    howdy
| [Wednesday 31 March 2010] [17:02:20]     * impl looks at mikko 
| [Wednesday 31 March 2010] [20:03:20] <wutang>   I am very familiar with 29west...are there any documents out there describing the differences in architecture and possible API differences between the two?
| [Wednesday 31 March 2010] [20:03:49] <wutang>   Also, I haven't found many examples beyond the most basic...are there any good repositories of examples or real applications that are open source?