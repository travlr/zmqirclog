===============
2011-March
===============

| [Friday 18 March 2011] [06:51:12] <sustrik>	oh well
| [Friday 18 March 2011] [06:51:41] <sustrik>	so it's up to the rest of erlzmq community to drive the project forward
| [Friday 18 March 2011] [06:51:51] <yrashk>	yup
| [Friday 18 March 2011] [06:52:01] <yrashk>	but again
| [Friday 18 March 2011] [06:52:10] <yrashk>	erlzmq and erlzq2 can't be merged by any means
| [Friday 18 March 2011] [06:52:15] <yrashk>	they are way too different
| [Friday 18 March 2011] [06:52:17] <sustrik>	yes, the codebase itself cannot be merged
| [Friday 18 March 2011] [06:52:25] <yrashk>	erlzmq2 won't work with older Erlang VMs
| [Friday 18 March 2011] [06:52:30] <yrashk>	as it uses a new binding technique
| [Friday 18 March 2011] [06:52:30] <sustrik>	what could be merged is functionality
| [Friday 18 March 2011] [06:52:39] <yrashk>	I thiknk they are very close functionally
| [Friday 18 March 2011] [06:53:00] <sustrik>	close = equivalent?
| [Friday 18 March 2011] [06:53:00] <yrashk>	we don't have an active mode (like saleyn had for the main erlzmq)
| [Friday 18 March 2011] [06:53:11] <yrashk>	APIs is not absolutely equivalent, no
| [Friday 18 March 2011] [06:53:22] <yrashk>	module names are different, app name is different
| [Friday 18 March 2011] [06:53:24] <sustrik>	the problem is that as long as there's functionality missing, those using one binding
| [Friday 18 March 2011] [06:53:28] <yrashk>	some calls might look a little bit different
| [Friday 18 March 2011] [06:53:29] <sustrik>	cannot switch to anotherone
| [Friday 18 March 2011] [06:53:39] <yrashk>	I don't think we have any functionality missing, really
| [Friday 18 March 2011] [06:53:52] <yrashk>	active mode was controversial anyway
| [Friday 18 March 2011] [06:54:01] <yrashk>	I think jugg opposed it a lot
| [Friday 18 March 2011] [06:54:14] <sustrik>	doesn't it have to do with pushback?
| [Friday 18 March 2011] [06:54:27] <sustrik>	won't passive mode just exhaust all the memory
| [Friday 18 March 2011] [06:54:34] <sustrik>	if sender is faster than receiver?
| [Friday 18 March 2011] [06:54:50] <yrashk>	well
| [Friday 18 March 2011] [06:55:00] <yrashk>	passive mode is pretty much reliant on the way 0mq works
| [Friday 18 March 2011] [06:55:34] <yrashk>	recv/poll
| [Friday 18 March 2011] [06:55:50] <yrashk>	there are certain issues why we haven't implemented active mode yet
| [Friday 18 March 2011] [06:56:07] <yrashk>	we could have done a workaround.. but still not sure if it is worth it
| [Friday 18 March 2011] [06:56:22] <yrashk>	it probably is worth a try
| [Friday 18 March 2011] [06:56:23] <sustrik>	is there any other way to implement pushback?
| [Friday 18 March 2011] [06:56:34] <yrashk>	what od you mean by a pushback?
| [Friday 18 March 2011] [06:56:59] <sustrik>	meaning that when the receiving end is not able to keep up with the sender
| [Friday 18 March 2011] [06:57:05] <sustrik>	the sender gets blocked
| [Friday 18 March 2011] [06:57:19] <sustrik>	until the receiver catches up
| [Friday 18 March 2011] [06:57:23] <yrashk>	not sure how to do anything about this
| [Friday 18 March 2011] [06:57:36] <sustrik>	i think that was what active mode was for
| [Friday 18 March 2011] [06:57:37] <yrashk>	basically what we do is we just pass messages back to erlang
| [Friday 18 March 2011] [06:57:42] <yrashk>	either directly or as actual essages
| [Friday 18 March 2011] [06:58:03] <yrashk>	active mode is just something that does recv for you, basically
| [Friday 18 March 2011] [06:58:25] <yrashk>	so I am not sure
| [Friday 18 March 2011] [06:58:45] <sustrik>	the problem is that erlang stores the messages in erlang mailbox
| [Friday 18 March 2011] [06:58:50] <yrashk>	yep
| [Friday 18 March 2011] [06:58:51] <sustrik>	which grows indefinitely
| [Friday 18 March 2011] [06:58:57] <yrashk>	but we don't send them unless you request
| [Friday 18 March 2011] [06:59:10] <yrashk>	active is what sends them regardless of whether you can keep up
| [Friday 18 March 2011] [06:59:16] <yrashk>	our recv() algo is simple
| [Friday 18 March 2011] [06:59:27] <yrashk>	1. recv noblock
| [Friday 18 March 2011] [06:59:31] <yrashk>	2. if there was something, return
| [Friday 18 March 2011] [06:59:40] <yrashk>	3. if not, let the reader thread poll it
| [Friday 18 March 2011] [06:59:51] <sustrik>	yes, that's ok
| [Friday 18 March 2011] [06:59:52] <yrashk>	4. when something appears there, send a message to the original requesting process
| [Friday 18 March 2011] [06:59:58] <sustrik>	what about the sender side?
| [Friday 18 March 2011] [07:00:16] <yrashk>	sender just does send() and that's it
| [Friday 18 March 2011] [07:00:27] <sustrik>	it blocks the thread?
| [Friday 18 March 2011] [07:00:38] <yrashk>	you mean the scheduler?
| [Friday 18 March 2011] [07:00:42] <sustrik>	then you can end up with deadlocked erlang VM
| [Friday 18 March 2011] [07:00:51] <sustrik>	i mean physicall thread
| [Friday 18 March 2011] [07:00:57] <sustrik>	from erlang's thread pool
| [Friday 18 March 2011] [07:01:02] <yrashk>	if you don't pass noblock, yes it will block the scheduler
| [Friday 18 March 2011] [07:01:08] <yrashk>	we don't use erlang's thead pool
| [Friday 18 March 2011] [07:01:20] <yrashk>	NIF calls block the scheduler
| [Friday 18 March 2011] [07:01:35] <sustrik>	i mean, erlang VM has to execute in an OS thread(s)
| [Friday 18 March 2011] [07:01:46] <yrashk>	so if zmq_send blocks, the VM is blocked (well, one cpu core is blocked, to be precise)
| [Friday 18 March 2011] [07:01:59] <sustrik>	exactly
| [Friday 18 March 2011] [07:02:00] <yrashk>	yes, erlang vm usually has # of schedulers equal to number of cores
| [Friday 18 March 2011] [07:02:08] <sustrik>	so, if there's 1 CPU
| [Friday 18 March 2011] [07:02:20] <yrashk>	and 1 core?
| [Friday 18 March 2011] [07:02:27] <sustrik>	and you call invoke 0mq in a blocking way
| [Friday 18 March 2011] [07:02:41] <sustrik>	the whole OS process gets bloecked
| [Friday 18 March 2011] [07:02:43] <yrashk>	it will fuck up, yes
| [Friday 18 March 2011] [07:02:52] <yrashk>	we were thinking about non-blocking send()
| [Friday 18 March 2011] [07:02:58] <yrashk>	just haven't done it yet
| [Friday 18 March 2011] [07:03:08] <yrashk>	there's nothing that prevents us from doing it
| [Friday 18 March 2011] [07:03:30] <sustrik>	that would mean busy-looping and 100% CPU usage, no?
| [Friday 18 March 2011] [07:03:54] <yrashk>	nah
| [Friday 18 March 2011] [07:04:02] <yrashk>	we poll on internal inproc sockets
| [Friday 18 March 2011] [07:04:06] <yrashk>	for commands
| [Friday 18 March 2011] [07:04:13] <yrashk>	in the receiver thread
| [Friday 18 March 2011] [07:04:17] <yrashk>	which does async recv
| [Friday 18 March 2011] [07:04:37] <yrashk>	so we can do the same thing for send, pretty much
| [Friday 18 March 2011] [07:04:41] <yrashk>	may be even in the same thread
| [Friday 18 March 2011] [07:04:43] <sustrik>	aha
| [Friday 18 March 2011] [07:04:55] <yrashk>	no biggie
| [Friday 18 March 2011] [07:05:00] <sustrik>	that way the polling doesn't block the erlang scheduler, right?
| [Friday 18 March 2011] [07:05:02] <yrashk>	will take probabyl an hour or two to implement
| [Friday 18 March 2011] [07:05:07] <yrashk>	it does not
| [Friday 18 March 2011] [07:05:10] <yrashk>	it never does
| [Friday 18 March 2011] [07:05:14] <sustrik>	nice
| [Friday 18 March 2011] [07:05:21] <yrashk>	it's always in that second thread
| [Friday 18 March 2011] [07:05:27] <yrashk>	we have one thread per context
| [Friday 18 March 2011] [07:05:38] <yrashk>	which I guess is good enough
| [Friday 18 March 2011] [07:05:43] <yrashk>	originally I had a thread per socket
| [Friday 18 March 2011] [07:05:47] <yrashk>	and that was a tad nasty
| [Friday 18 March 2011] [07:05:56] <yrashk>	but evax refactored this nicely
| [Friday 18 March 2011] [07:06:05] <sustrik>	so erlang allows you to say "please invoke this code when this file descriptor becomes active"?
| [Friday 18 March 2011] [07:06:23] <sustrik>	and erlang scheduler will do that for you
| [Friday 18 March 2011] [07:06:28] <yrashk>	no, it's all manual
| [Friday 18 March 2011] [07:06:41] <yrashk>	there's some FD stuff in there, but not for NIFs afaik
| [Friday 18 March 2011] [07:06:59] <yrashk>	basically, when we poll in that thread
| [Friday 18 March 2011] [07:07:01] <sustrik>	the question is whether waiting for FD blocks the OS thread or not
| [Friday 18 March 2011] [07:07:16] <yrashk>	you mean zmq_poll?
| [Friday 18 March 2011] [07:07:22] <sustrik>	are you using zmq_poll?
| [Friday 18 March 2011] [07:07:24] <yrashk>	yes
| [Friday 18 March 2011] [07:07:33] <sustrik>	zmq_poll is blocking
| [Friday 18 March 2011] [07:07:38] <yrashk>	yes, and that's fine
| [Friday 18 March 2011] [07:07:43] <yrashk>	because we're in a separate thread
| [Friday 18 March 2011] [07:07:54] <yrashk>	which erlang has no idea about
| [Friday 18 March 2011] [07:07:55] <sustrik>	outside of erlang VM?
| [Friday 18 March 2011] [07:07:59] <sustrik>	i see
| [Friday 18 March 2011] [07:08:01] <yrashk>	well, it's in the same process
| [Friday 18 March 2011] [07:08:11] <yrashk>	but it's separate from the scheduler
| [Friday 18 March 2011] [07:08:24] <yrashk>	so all NIF calls are generally very short
| [Friday 18 March 2011] [07:08:35] <sustrik>	yep, that could work
| [Friday 18 March 2011] [07:08:35] <yrashk>	except for send() which might theoretically block
| [Friday 18 March 2011] [07:08:43] <yrashk>	but that's something we can definitely fix
| [Friday 18 March 2011] [07:08:51] <yrashk>	I just never saw zmq_send() blocking
| [Friday 18 March 2011] [07:08:51] <sustrik>	but can be done in same way as recv()
| [Friday 18 March 2011] [07:08:54] <yrashk>	yes
| [Friday 18 March 2011] [07:08:55] <yrashk>	absolutely
| [Friday 18 March 2011] [07:09:01] <sustrik>	you get that for high loads
| [Friday 18 March 2011] [07:09:06] <yrashk>	like I said, it's an easy change
| [Friday 18 March 2011] [07:09:13] <yrashk>	since we have worked out the approach
| [Friday 18 March 2011] [07:09:20] <sustrik>	would be good to get that in
| [Friday 18 March 2011] [07:09:27] <sustrik>	it's essential for some applications
| [Friday 18 March 2011] [07:09:31] <yrashk>	I see
| [Friday 18 March 2011] [07:09:35] <sustrik>	such as rabbitmq/0mq bridge
| [Friday 18 March 2011] [07:09:37] <yrashk>	I am adding a github issue right now
| [Friday 18 March 2011] [07:10:17] <yrashk>	https://github.com/zeromq/erlzmq2/issues/1
| [Friday 18 March 2011] [07:10:21] <sustrik>	:)
| [Friday 18 March 2011] [07:10:41] <sustrik>	what about the third erlzmq binding?
| [Friday 18 March 2011] [07:10:48] <sustrik>	any additional functionality there?
| [Friday 18 March 2011] [07:11:16] <yrashk>	cstar/jugg's?
| [Friday 18 March 2011] [07:11:21] <sustrik>	i guess
| [Friday 18 March 2011] [07:11:30] <yrashk>	I don't remember any special functionality there
| [Friday 18 March 2011] [07:11:37] <yrashk>	it looked more polished than the official one
| [Friday 18 March 2011] [07:11:41] <yrashk>	to my eye
| [Friday 18 March 2011] [07:11:55] <yrashk>	so I guess it's good for older erlangs
| [Friday 18 March 2011] [07:12:11] <sustrik>	aha, that's the catch, right?
| [Friday 18 March 2011] [07:12:11] <yrashk>	or if you have any reasons to use port driver instead of NIF
| [Friday 18 March 2011] [07:12:16] <sustrik>	old arlangs don't have NIF
| [Friday 18 March 2011] [07:12:19] <yrashk>	yeah they don't
| [Friday 18 March 2011] [07:12:42] <sustrik>	well, if you believe there's all the functionality in erlzmq2
| [Friday 18 March 2011] [07:12:44] <yrashk>	and some of those have (like last R13Bs and early R14As) but the API was changing a lot
| [Friday 18 March 2011] [07:12:58] <yrashk>	so we're pretty much >=R14B01 or so
| [Friday 18 March 2011] [07:13:12] <sustrik>	let's discuss making it a primary erlang binding on the mailing list
| [Friday 18 March 2011] [07:13:22] <yrashk>	also, jugg was never able to clock performance comparable to erlzmq2
| [Friday 18 March 2011] [07:13:29] <sustrik>	yes, i recall that
| [Friday 18 March 2011] [07:13:30] <yrashk>	lets do that
| [Friday 18 March 2011] [07:13:37] <yrashk>	we have like 1.3mln/sec for 1bytes
| [Friday 18 March 2011] [07:13:41] <yrashk>	which is not bad
| [Friday 18 March 2011] [07:13:46] <yrashk>	not great, but decent
| [Friday 18 March 2011] [07:13:51] <sustrik>	it's very nice
| [Friday 18 March 2011] [07:13:55] <yrashk>	(on my mac pro)
| [Friday 18 March 2011] [07:13:58] <sustrik>	comparable to other non-C languages
| [Friday 18 March 2011] [07:14:02] <yrashk>	c-to-c on my mac pro is like twice as fast
| [Friday 18 March 2011] [07:14:23] <yrashk>	2.5+mln/sec
| [Friday 18 March 2011] [07:14:31] <yrashk>	but we weren't able to squeeze out more yet
| [Friday 18 March 2011] [07:14:36] <yrashk>	and I am not sure we can
| [Friday 18 March 2011] [07:14:56] <sustrik>	you have to keep in mind that erlang runtime does a lot of stuff
| [Friday 18 March 2011] [07:15:00] <sustrik>	scheduling etc.
| [Friday 18 March 2011] [07:15:08] <sustrik>	which takes some time itself
| [Friday 18 March 2011] [07:15:17] <yrashk>	of course
| [Friday 18 March 2011] [07:15:28] <yrashk>	I know erlang fairly well
| [Friday 18 March 2011] [07:15:31] <yrashk>	or so I think
| [Friday 18 March 2011] [07:15:37] <sustrik>	with throughput over 1M/sec
| [Friday 18 March 2011] [07:15:46] <sustrik>	you are getting to nanosecond ranges
| [Friday 18 March 2011] [07:15:53] <yrashk>	well that's for 1bytes
| [Friday 18 March 2011] [07:15:59] <yrashk>	1Kb is like 300K/sec
| [Friday 18 March 2011] [07:16:13] <yrashk>	which is still okay I guess
| [Friday 18 March 2011] [07:16:22] <sustrik>	100% bandwidth utilisation i would guess
| [Friday 18 March 2011] [07:16:28] <sustrik>	1GbE?
| [Friday 18 March 2011] [07:16:36] <yrashk>	it's all localhost tests :)
| [Friday 18 March 2011] [07:16:57] <yrashk>	both for c-to-c and erlang-to-erlang
| [Friday 18 March 2011] [07:17:04] <sustrik>	ack
| [Friday 18 March 2011] [07:17:07] <yrashk>	for comparison
| [Friday 18 March 2011] [07:17:11] <yrashk>	tcp transport
| [Friday 18 March 2011] [07:17:14] <sustrik>	the larger the message, the less the erlang overhead
| [Friday 18 March 2011] [07:17:16] <yrashk>	ipc was about the same
| [Friday 18 March 2011] [07:17:41] <sustrik>	anyway, 1.3M is great
| [Friday 18 March 2011] [07:18:30] 	 * yrashk performs a happy dance
| [Friday 18 March 2011] [07:19:11] <yrashk>	anyway
| [Friday 18 March 2011] [07:19:18] <yrashk>	lets discuss binding issue on the mailing list?
| [Friday 18 March 2011] [07:19:28] <yrashk>	I am subscribed (digest mode)
| [Friday 18 March 2011] [07:19:59] <yrashk>	will be back in about 30 mins
| [Friday 18 March 2011] [07:21:22] <sustrik>	yrashk: yes, send the proposal to the mailing listr
| [Friday 18 March 2011] [07:27:32] <Guthur>	talking of bindings, sustrik do you think it would be wise to discuss marking clrzmq as deprecated and that users should consider either the interop binding or clrzmq2
| [Friday 18 March 2011] [07:27:52] <Guthur>	the rational being that the original binding isn't really actively developed
| [Friday 18 March 2011] [07:28:10] <sustrik>	it's a community project, discuss it on the mailing list
| [Friday 18 March 2011] [07:28:14] <Guthur>	sure
| [Friday 18 March 2011] [07:28:19] <sustrik>	and if there's no opposition, let's do it
| [Friday 18 March 2011] [07:28:22] <Guthur>	just interested in what you think
| [Friday 18 March 2011] [07:28:45] <sustrik>	i would rather have actively maintained bindings as "official" :)
| [Friday 18 March 2011] [07:28:49] <Guthur>	ok, I'm raise it on the list later today
| [Friday 18 March 2011] [07:48:26] <pieterh_>	sustrik: ping
| [Friday 18 March 2011] [07:48:32] <sustrik>	pong
| [Friday 18 March 2011] [07:48:41] <pieterh_>	random question about pub/sub...
| [Friday 18 March 2011] [07:48:54] <pieterh_>	if I send a two-frame message, first key then value, I expect to receive two frames, right?
| [Friday 18 March 2011] [07:49:09] <sustrik>	yes
| [Friday 18 March 2011] [07:49:26] <pieterh_>	ok, I have a test case where it appears to sometimes fail at connection startup
| [Friday 18 March 2011] [07:49:39] <pieterh_>	loses first frame, sometimes
| [Friday 18 March 2011] [07:49:40] <pieterh_>	i
| [Friday 18 March 2011] [07:49:43] <sustrik>	ok
| [Friday 18 March 2011] [07:49:50] <pieterh_>	I'll post the server and client, hang on...
| [Friday 18 March 2011] [07:50:45] <Guthur>	pieterh_: with your lazy pirate patterns did you notice that reconnecting after CPU overload rarely happened?
| [Friday 18 March 2011] [07:51:20] <Guthur>	I've noticed this behaviour, even with the C examples
| [Friday 18 March 2011] [07:51:24] <pieterh_>	Guthur: what do you mean?
| [Friday 18 March 2011] [07:51:29] <pieterh_>	the client doesn't reconnect? 
| [Friday 18 March 2011] [07:51:46] <Guthur>	yeah, it tries and thinks the server is not there
| [Friday 18 March 2011] [07:51:50] <pieterh_>	normal, because its timeouts are quite aggressive, and simulation of CPU overload is quite a long pause afair
| [Friday 18 March 2011] [07:51:54] <Guthur>	if I remove the 1sec sleep it connects
| [Friday 18 March 2011] [07:52:05] <pieterh_>	try making the client more patient...
| [Friday 18 March 2011] [07:52:11] <Guthur>	1sec (heavy work)
| [Friday 18 March 2011] [07:52:15] <pieterh_>	i'll retest, hang on a sec...
| [Friday 18 March 2011] [07:53:10] <pieterh_>	sustrik: so, https://gist.github.com/875932
| [Friday 18 March 2011] [07:53:16] <pieterh_>	start the server, then the client
| [Friday 18 March 2011] [07:53:25] <sustrik>	ok, will give it a look
| [Friday 18 March 2011] [07:53:44] <pieterh_>	thanks, this is hitting one of my examples and I can't see my fault
| [Friday 18 March 2011] [07:53:53] <pieterh_>	so made a simplistic case, it still hits...
| [Friday 18 March 2011] [07:58:07] <pieterh_>	Guthur: it's just because the client is too impatient
| [Friday 18 March 2011] [07:59:03] <Guthur>	pieterh_: ok, cheers for testing
| [Friday 18 March 2011] [07:59:50] <pieterh_>	Guthur: I'll change the 'CPU overload' delay to 2 seconds instead of 5
| [Friday 18 March 2011] [07:59:57] <pieterh_>	this lets the client recover
| [Friday 18 March 2011] [08:00:09] <Guthur>	sounds good
| [Friday 18 March 2011] [08:01:02] <yrashk>	sustrik: what exactly should be in that proposal?
| [Friday 18 March 2011] [08:01:08] <Guthur>	it had me scratching my head for a while yesterday, for a moment I thought the Mono runtime was just insanely slow
| [Friday 18 March 2011] [08:01:18] <Guthur>	but then seen the same in C
| [Friday 18 March 2011] [08:02:18] <pieterh_>	yeah, it's good to be able to compare the different languages
| [Friday 18 March 2011] [08:02:19] <sustrik>	yrashk: "i propose making erlzmq2 an official erlang binding while keeping erlzmq as a binding for old versions of erlang"
| [Friday 18 March 2011] [08:02:25] <sustrik>	then list your arguments
| [Friday 18 March 2011] [08:02:28] <yrashk>	ok
| [Friday 18 March 2011] [08:02:29] <sustrik>	and ask people to comment
| [Friday 18 March 2011] [08:02:36] <pieterh_>	sustrik: I think that was already agreed...
| [Friday 18 March 2011] [08:02:46] <yrashk>	can I refer to you as it was your idea?
| [Friday 18 March 2011] [08:02:51] <pieterh_>	so erlzmq kind of became v1
| [Friday 18 March 2011] [08:03:01] <sustrik>	did it?
| [Friday 18 March 2011] [08:03:04] <yrashk>	wel
| [Friday 18 March 2011] [08:03:05] <yrashk>	well
| [Friday 18 March 2011] [08:03:05] <pieterh_>	yrashk: I missed something, why are you asking for people to comment on this?
| [Friday 18 March 2011] [08:03:09] <yrashk>	ont the wiki, eys
| [Friday 18 March 2011] [08:03:16] <yrashk>	pieterh_: I am not, sustrik does
| [Friday 18 March 2011] [08:03:41] <pieterh_>	sustrik: we already afaik got agreement from the erlzmq authors to make v2
| [Friday 18 March 2011] [08:03:52] <yrashk>	pieterh_: just one of them
| [Friday 18 March 2011] [08:04:01] <pieterh_>	yrashk: ah... did you ask the others?
| [Friday 18 March 2011] [08:04:03] <yrashk>	pieterh_: saleyn is unable to answer for some sad reasons
| [Friday 18 March 2011] [08:04:10] <pieterh_>	ok
| [Friday 18 March 2011] [08:04:26] <sustrik>	if it was discussed already, then there's no point in discussing it anew
| [Friday 18 March 2011] [08:04:31] <pieterh_>	indeed
| [Friday 18 March 2011] [08:04:34] <yrashk>	ok
| [Friday 18 March 2011] [08:04:35] <sustrik>	i just missed the original discussion
| [Friday 18 March 2011] [08:04:39] <yrashk>	ya it was discussed here 
| [Friday 18 March 2011] [08:04:51] <pieterh_>	it's already an official repository, and the name was made coherent, the wiki correct, etc.
| [Friday 18 March 2011] [08:05:08] <sustrik>	then there's no problem
| [Friday 18 March 2011] [08:05:14] <yrashk>	sweet
| [Friday 18 March 2011] [08:05:17] <yrashk>	less work for me then
| [Friday 18 March 2011] [08:05:23] <yrashk>	we'll then improve send() some time later
| [Friday 18 March 2011] [08:05:26] <pieterh_>	given that it's much faster and sticks to the same API, there was no real argument...
| [Friday 18 March 2011] [08:05:35] <sustrik>	i see
| [Friday 18 March 2011] [08:05:38] <yrashk>	to make it behave better on blocking sends
| [Friday 18 March 2011] [08:05:38] <evax>	yrashk, sustrik: doing it now
| [Friday 18 March 2011] [08:05:45] <yrashk>	evax: oh the issue #1?
| [Friday 18 March 2011] [08:05:50] <evax>	yes
| [Friday 18 March 2011] [08:06:01] <yrashk>	evax: I bet it should be easy to replicate the same method as we do with recv
| [Friday 18 March 2011] [08:06:05] <yrashk>	may be even the same thread
| [Friday 18 March 2011] [08:06:28] <evax>	same thread, yes
| [Friday 18 March 2011] [08:06:32] <yrashk>	sweet
| [Friday 18 March 2011] [08:06:47] <yrashk>	should be fairly trivial then
| [Friday 18 March 2011] [08:06:56] <yrashk>	just adding an enum flag to recv structure
| [Friday 18 March 2011] [08:07:07] <yrashk>	and renaming recv structure to something like command or someting
| [Friday 18 March 2011] [08:07:16] <yrashk>	also, evax
| [Friday 18 March 2011] [08:07:22] <evax>	yes, along those lines
| [Friday 18 March 2011] [08:07:24] <yrashk>	do you plan to do exactly the same scheme?
| [Friday 18 March 2011] [08:07:26] <yrashk>	i.e.
| [Friday 18 March 2011] [08:07:30] <yrashk>	recv noblock first
| [Friday 18 March 2011] [08:07:33] <evax>	sure
| [Friday 18 March 2011] [08:07:35] <yrashk>	err
| [Friday 18 March 2011] [08:07:37] <yrashk>	send*
| [Friday 18 March 2011] [08:07:41] <yrashk>	if it says EAGAIN
| [Friday 18 March 2011] [08:07:43] <yrashk>	then pool it
| [Friday 18 March 2011] [08:07:56] <evax>	shouldn't I ?
| [Friday 18 March 2011] [08:08:04] <yrashk>	so that we don't pool when it is unnecessary
| [Friday 18 March 2011] [08:08:10] <yrashk>	I think it's a good approach
| [Friday 18 March 2011] [08:08:22] <yrashk>	zmq_send(.., ZMQ_NOBLOCK) -> if EGAGAIN, pool
| [Friday 18 March 2011] [08:08:27] <yrashk>	otherwise, be done with it
| [Friday 18 March 2011] [08:08:30] <yrashk>	EAGAIN*
| [Friday 18 March 2011] [08:08:49] <yrashk>	that looks really very much the same way recv does
| [Friday 18 March 2011] [08:11:21] <evax>	except we have to store the msg somewhere
| [Friday 18 March 2011] [08:12:17] <yrashk>	in the same struct
| [Friday 18 March 2011] [08:12:25] <yrashk>	recv, but renamed
| [Friday 18 March 2011] [08:12:35] <yrashk>	and extended accordingly
| [Friday 18 March 2011] [08:12:57] <evax>	this goes over the ipc socket, so for big messages its ugly
| [Friday 18 March 2011] [08:13:01] <yrashk>	just copy the zms_msg
| [Friday 18 March 2011] [08:13:07] <yrashk>	it is
| [Friday 18 March 2011] [08:13:13] <yrashk>	but its not ipc
| [Friday 18 March 2011] [08:13:16] <yrashk>	inproc
| [Friday 18 March 2011] [08:13:21] <evax>	yeah
| [Friday 18 March 2011] [08:13:24] <yrashk>	we just pass a pointer
| [Friday 18 March 2011] [08:13:31] <yrashk>	how about that?
| [Friday 18 March 2011] [08:13:59] <yrashk>	and then zmq_msg_close it when done sending it in a loop
| [Friday 18 March 2011] [08:14:23] <yrashk>	theres more important problem
| [Friday 18 March 2011] [08:14:33] <yrashk>	in that thread we poll
| [Friday 18 March 2011] [08:14:47] <yrashk>	but if we do the blocking send there
| [Friday 18 March 2011] [08:15:09] <yrashk>	then receivers will get blocked untill the send is over
| [Friday 18 March 2011] [08:15:12] <yrashk>	mhm
| [Friday 18 March 2011] [08:15:18] <evax>	reading zmq.h shouldn't be a problem to pass the msg in, ideed
| [Friday 18 March 2011] [08:15:39] <yrashk>	yeah, so pointer in that struct for msg is cool
| [Friday 18 March 2011] [08:15:50] <yrashk>	but this problem above bothers me
| [Friday 18 March 2011] [08:15:53] <yrashk>	not nice
| [Friday 18 March 2011] [08:16:50] <yrashk>	also separate sending thread isnt solving this completely
| [Friday 18 March 2011] [08:17:02] <yrashk>	it will help us from blocking poller
| [Friday 18 March 2011] [08:17:23] <yrashk>	but it will not b able to send more than one thing at a time
| [Friday 18 March 2011] [08:17:33] <yrashk>	since sending is blocked
| [Friday 18 March 2011] [08:17:44] <yrashk>	if only we had a reverse poll
| [Friday 18 March 2011] [08:17:47] <yrashk>	wait
| [Friday 18 March 2011] [08:18:00] <yrashk>	dont we have that kind of event in poll?
| [Friday 18 March 2011] [08:18:08] <evax>	it has to be in the same thread
| [Friday 18 March 2011] [08:18:14] <yrashk>	not sure how it will help tho
| [Friday 18 March 2011] [08:18:43] <evax>	and I'm not sure sending and recving are allowed at the same time
| [Friday 18 March 2011] [08:19:05] <evax>	if one must not use a socket in multiple threads
| [Friday 18 March 2011] [08:19:37] <yrashk>	hey
| [Friday 18 March 2011] [08:19:52] <yrashk>	how about using zmq_pollout event?
| [Friday 18 March 2011] [08:20:03] <evax>	sure
| [Friday 18 March 2011] [08:20:09] <yrashk>	it guarantees you can send without blocking
| [Friday 18 March 2011] [08:20:27] <yrashk>	so we can embed this into our poller
| [Friday 18 March 2011] [08:21:03] <yrashk>	this way we wont be blocking the poller ever
| [Friday 18 March 2011] [08:21:11] <yrashk>	i think it is a sound idea
| [Friday 18 March 2011] [08:21:56] <yrashk>	sustrik, wdyt? will it work fine? any precautions?
| [Friday 18 March 2011] [08:23:28] <yrashk>	i really like it
| [Friday 18 March 2011] [08:42:40] <sustrik>	yes, that's what POLLOUT is for
| [Friday 18 March 2011] [08:43:08] <yrashk>	sweet
| [Friday 18 March 2011] [08:43:22] <yrashk>	so hopefully we'll have this non-blocking very soon then
| [Friday 18 March 2011] [08:43:32] <yrashk>	as it will not change our poller much
| [Friday 18 March 2011] [08:45:51] <Steve-o>	mikko: looks like all the platforms are good now
| [Friday 18 March 2011] [09:06:34] <pieterh_>	 sustrik: I think your email is inaccurate in some key ways
| [Friday 18 March 2011] [09:06:53] <pieterh_>	most critically, you are claiming a purpose for XREP that was never documented before
| [Friday 18 March 2011] [09:06:56] <sustrik>	feel free to discuss
| [Friday 18 March 2011] [09:07:09] <sustrik>	that's why i sent the email out
| [Friday 18 March 2011] [09:07:11] <pieterh_>	as a user, and the developer of many devices, the notion that you would break this, is... shocking
| [Friday 18 March 2011] [09:07:40] <sustrik>	that's why it has to be solved
| [Friday 18 March 2011] [09:07:41] <pieterh_>	it suggests (a) you don't know wtf you were doing, (b) you don't care about your users, (c) you don't understand what they are doing
| [Friday 18 March 2011] [09:07:48] <pieterh_>	none of this is true, but it's what your email suggests
| [Friday 18 March 2011] [09:07:50] <sustrik>	i would start with ZMQ)ROUTER socket type
| [Friday 18 March 2011] [09:08:19] <sustrik>	shrug, it has to be solved somehow
| [Friday 18 March 2011] [09:08:20] <pieterh_>	it's unavoidable that people use this as a ROUTER
| [Friday 18 March 2011] [09:08:27] <pieterh_>	so, embrace that and make it work nicely
| [Friday 18 March 2011] [09:08:28] <sustrik>	feel free to propose a solution
| [Friday 18 March 2011] [09:08:32] <pieterh_>	I've done that many times
| [Friday 18 March 2011] [09:08:39] <sustrik>	ZMQ_ROUTER, right?
| [Friday 18 March 2011] [09:08:40] <pieterh_>	call it by the right name, make it work a little better
| [Friday 18 March 2011] [09:08:42] <pieterh_>	yes
| [Friday 18 March 2011] [09:08:43] <pieterh_>	of course
| [Friday 18 March 2011] [09:08:49] <sustrik>	that's option 2 i think
| [Friday 18 March 2011] [09:08:51] <pieterh_>	you will see the overwhelming consensus on the list
| [Friday 18 March 2011] [09:09:02] <sustrik>	sure
| [Friday 18 March 2011] [09:09:03] <pieterh_>	you did read that thread, right?
| [Friday 18 March 2011] [09:09:04] <sustrik>	np
| [Friday 18 March 2011] [09:09:17] <sustrik>	yes
| [Friday 18 March 2011] [09:09:21] <pieterh_>	I like your solution of a verbose compile option
| [Friday 18 March 2011] [09:09:29] <sustrik>	i am just explaining the internals
| [Friday 18 March 2011] [09:09:40] <sustrik>	opt.2 is probably the best
| [Friday 18 March 2011] [09:09:53] <pieterh_>	well, you're saying you might make a different implementation of "return to sender" 
| [Friday 18 March 2011] [09:10:03] <sustrik>	definitely
| [Friday 18 March 2011] [09:10:10] <pieterh_>	which (and I give you the raw emotion) is ... shokcing
| [Friday 18 March 2011] [09:10:11] <pieterh_>	shocking
| [Friday 18 March 2011] [09:10:14] <sustrik>	that's the XREP should be separated from REOUTER
| [Friday 18 March 2011] [09:10:17] <sustrik>	ROUTER*
| [Friday 18 March 2011] [09:10:29] <sustrik>	they are two distinct things
| [Friday 18 March 2011] [09:10:32] <pieterh_>	you have a better idea for the REP-REQ chain?
| [Friday 18 March 2011] [09:10:40] <sustrik>	not at the moment
| [Friday 18 March 2011] [09:10:51] <sustrik>	but it's conceptually different from router
| [Friday 18 March 2011] [09:10:56] <pieterh_>	precisely, and afaics it's impossible without creating stateful fabric
| [Friday 18 March 2011] [09:11:02] <sustrik>	say the dropping of unroutable messages ->
| [Friday 18 March 2011] [09:11:03] <pieterh_>	conceptually it's the same
| [Friday 18 March 2011] [09:11:05] <pieterh_>	it's a use case
| [Friday 18 March 2011] [09:11:08] <sustrik>	ROUTER should not drop
| [Friday 18 March 2011] [09:11:10] <sustrik>	XREP should
| [Friday 18 March 2011] [09:11:14] <pieterh_>	yes it should
| [Friday 18 March 2011] [09:11:24] <pieterh_>	ROUTER should drop BUT it should be able to warn you
| [Friday 18 March 2011] [09:11:45] <pieterh_>	there is nothing useful you can do with an unroutable message but since it often suggests a programming error, you need visibility
| [Friday 18 March 2011] [09:11:47] <pieterh_>	that's all
| [Friday 18 March 2011] [09:11:52] <sustrik>	sure
| [Friday 18 March 2011] [09:12:08] <pieterh_>	I literally go into src/xrep.cpp and add a printf
| [Friday 18 March 2011] [09:12:15] <pieterh_>	so I can debug a complex router
| [Friday 18 March 2011] [09:12:41] <pieterh_>	doing a req-rep chain is just one use case for routing
| [Friday 18 March 2011] [09:12:44] <pieterh_>	it's not a core pattern
| [Friday 18 March 2011] [09:12:50] <sustrik>	it is
| [Friday 18 March 2011] [09:13:00] <pieterh_>	not a *separate* core pattern
| [Friday 18 March 2011] [09:13:02] <pieterh_>	afaics
| [Friday 18 March 2011] [09:14:18] <pieterh_>	tbh the envelope concept is ugly as heck but I can't see anything simpler or better
| [Friday 18 March 2011] [09:14:38] <sustrik>	the one described in the email is nice
| [Friday 18 March 2011] [09:14:46] <sustrik>	but works on only for req/rep
| [Friday 18 March 2011] [09:14:49] <sustrik>	not for router
| [Friday 18 March 2011] [09:15:02] <sustrik>	and it has some scaling issues
| [Friday 18 March 2011] [09:15:12] <sustrik>	so it's not a real alternative, i think
| [Friday 18 March 2011] [09:16:29] 	 * pieterh_ is re-reading the email
| [Friday 18 March 2011] [09:16:36] <pieterh_>	XPUB/XSUB are hop-by-hop?
| [Friday 18 March 2011] [09:16:53] <sustrik>	yes
| [Friday 18 March 2011] [09:16:59] <pieterh_>	the fact you implement PUB on XPUB, REQ on XREQ, is irrelevant to the user
| [Friday 18 March 2011] [09:17:04] <pieterh_>	it's vital to you, irrelevant to me
| [Friday 18 March 2011] [09:17:15] <pieterh_>	in fact, worse than irrelevant, it's negative data
| [Friday 18 March 2011] [09:17:53] <pieterh_>	you basically ask me as user to think about your implementation design, which breaks my brain
| [Friday 18 March 2011] [09:18:05] <pieterh_>	"The end-to-end type is always layered on top of the corresponding X socket"
| [Friday 18 March 2011] [09:18:06] <sustrik>	it works like IP and TCP
| [Friday 18 March 2011] [09:18:10] <pieterh_>	that's rubbish, sorry
| [Friday 18 March 2011] [09:18:14] <pieterh_>	I don't know IP
| [Friday 18 March 2011] [09:18:16] <sustrik>	a TCP user doesn't have to be aware of IP
| [Friday 18 March 2011] [09:18:19] <sustrik>	but it's there
| [Friday 18 March 2011] [09:18:32] <pieterh_>	sorry, it does not work for me, not at all
| [Friday 18 March 2011] [09:18:42] <pieterh_>	what I want are a set of socket types with clear names and clear semantics
| [Friday 18 March 2011] [09:18:50] <Steve-o>	+1
| [Friday 18 March 2011] [09:18:51] <pieterh_>	I don't want some layering and abstraction I need to learn first
| [Friday 18 March 2011] [09:18:52] <sustrik>	that's the option 2
| [Friday 18 March 2011] [09:18:59] <sustrik>	ZMQ_ROUTER
| [Friday 18 March 2011] [09:19:06] <pieterh_>	do not try to sell me your abstractions, it's what AMQP does and it's bogus
| [Friday 18 March 2011] [09:19:22] <sustrik>	what do you want exactly then?
| [Friday 18 March 2011] [09:19:25] <sustrik>	i am not following
| [Friday 18 March 2011] [09:19:28] <pieterh_>	I want clear socket names
| [Friday 18 March 2011] [09:19:33] <sustrik>	ZMQ_ROUTER
| [Friday 18 March 2011] [09:19:35] <pieterh_>	clear semantics that are documented up-front
| [Friday 18 March 2011] [09:19:36] <pieterh_>	yes
| [Friday 18 March 2011] [09:19:46] <pieterh_>	this is, sadly, reverse engineering
| [Friday 18 March 2011] [09:19:47] <sustrik>	what's the problem then?
| [Friday 18 March 2011] [09:19:55] <pieterh_>	it's me trying to make names that fit your semantics
| [Friday 18 March 2011] [09:20:12] <pieterh_>	there's no problem so long as you don't come back with abstractions that hurt my brain
| [Friday 18 March 2011] [09:20:13] <pieterh_>	:-)
| [Friday 18 March 2011] [09:20:23] <pieterh_>	it is already hard enough
| [Friday 18 March 2011] [09:20:35] <sustrik>	that's an abstraction on which 0mq is working from very beginning
| [Friday 18 March 2011] [09:20:38] <sustrik>	just ignore it
| [Friday 18 March 2011] [09:20:55] <sustrik>	as a user you don't have to care
| [Friday 18 March 2011] [09:20:58] <pieterh_>	do you understand that your semantics are counter-productive for mine?
| [Friday 18 March 2011] [09:21:08] <pieterh_>	we have a conflict, as user vs. designer?
| [Friday 18 March 2011] [09:21:27] <sustrik>	i don't think so
| [Friday 18 March 2011] [09:21:37] <pieterh_>	it's been that way so far
| [Friday 18 March 2011] [09:21:43] <pieterh_>	e.g. The end-to-end type is always layered on top of the corresponding X socket
| [Friday 18 March 2011] [09:21:49] <sustrik>	yes
| [Friday 18 March 2011] [09:22:03] <pieterh_>	that is toxic for me as user
| [Friday 18 March 2011] [09:22:12] <sustrik>	you don't have to care
| [Friday 18 March 2011] [09:22:20] <sustrik>	use just the non-X types
| [Friday 18 March 2011] [09:22:26] <sustrik>	that's what proposition 2 is about
| [Friday 18 March 2011] [09:22:34] <sustrik>	people want to use routing
| [Friday 18 March 2011] [09:22:43] <sustrik>	so let's make routing a first-class non-X socket
| [Friday 18 March 2011] [09:22:46] <sustrik>	ZMQ_ROUTER
| [Friday 18 March 2011] [09:22:53] <pieterh_>	well, you can make internal socket types that are undocumented
| [Friday 18 March 2011] [09:23:05] <pieterh_>	but ZMQ_ROUTER and ZMQ_DEALER cannot be internal and undocumented
| [Friday 18 March 2011] [09:23:15] <pieterh_>	since they cover 40%, as I said, of real application use cases
| [Friday 18 March 2011] [09:23:24] <sustrik>	X-sockets must be documented because they are used to make devices
| [Friday 18 March 2011] [09:23:32] <pieterh_>	devices are apps
| [Friday 18 March 2011] [09:23:43] <sustrik>	i.e. intermdiate nodes with no end-to-end functionalitty
| [Friday 18 March 2011] [09:23:46] <pieterh_>	X-sockets are your terminology
| [Friday 18 March 2011] [09:23:55] <pieterh_>	I'm against that terminology
| [Friday 18 March 2011] [09:24:02] <sustrik>	what would you want instead?
| [Friday 18 March 2011] [09:24:09] <pieterh_>	especially when you explain it
| [Friday 18 March 2011] [09:24:16] <sustrik>	i admitt the X- thing is stupid
| [Friday 18 March 2011] [09:24:18] <pieterh_>	just a clear set of sockets that are properly documented and match real requirements
| [Friday 18 March 2011] [09:24:23] <pieterh_>	it's not hard
| [Friday 18 March 2011] [09:24:24] <pieterh_>	design from the use case backwards
| [Friday 18 March 2011] [09:24:29] <sustrik>	haven't though of anything better though
| [Friday 18 March 2011] [09:24:30] <pieterh_>	not from the implementation forwards
| [Friday 18 March 2011] [09:24:36] <pieterh_>	I don't *care* how you implement stuff
| [Friday 18 March 2011] [09:24:58] <pieterh_>	what I do care about is the clarity of documentation as a contract
| [Friday 18 March 2011] [09:25:00] <pieterh_>	clear names
| [Friday 18 March 2011] [09:25:09] <sustrik>	the problem is that X- sockets have to be exposed because of device implementers
| [Friday 18 March 2011] [09:25:12] <pieterh_>	clear semantics that directly speak to user requirements
| [Friday 18 March 2011] [09:25:16] <pieterh_>	?
| [Friday 18 March 2011] [09:25:21] <sustrik>	so they can't be hidden
| [Friday 18 March 2011] [09:25:22] <pieterh_>	ZMQ_ROUTER is not a problem
| [Friday 18 March 2011] [09:25:28] <pieterh_>	sigh
| [Friday 18 March 2011] [09:25:32] <pieterh_>	devices are apps
| [Friday 18 March 2011] [09:25:34] <sustrik>	no, the problem is layering
| [Friday 18 March 2011] [09:25:40] <pieterh_>	that's your problem, not mine
| [Friday 18 March 2011] [09:25:55] <pieterh_>	that's an implementation detail
| [Friday 18 March 2011] [09:25:58] <pieterh_>	look... just make small steps here
| [Friday 18 March 2011] [09:26:06] <sustrik>	ok, so just ignore the X types
| [Friday 18 March 2011] [09:26:09] <pieterh_>	rename XREP and XREQ to ROUTER and DEALER
| [Friday 18 March 2011] [09:26:17] <pieterh_>	and stop using weird names that make no sense 
| [Friday 18 March 2011] [09:26:17] <sustrik>	it's mine problem, not yours
| [Friday 18 March 2011] [09:26:33] <pieterh_>	if you want to use undocumented internal socket types, fine
| [Friday 18 March 2011] [09:26:38] <pieterh_>	but they don't exist for me
| [Friday 18 March 2011] [09:26:45] <sustrik>	they must be documented because of devices
| [Friday 18 March 2011] [09:26:57] <sustrik>	there's no way to create a device with REQ/REP
| [Friday 18 March 2011] [09:27:01] <sustrik>	it would blockl
| [Friday 18 March 2011] [09:27:01] <pieterh_>	then they are not internal
| [Friday 18 March 2011] [09:27:07] <pieterh_>	well, I do know that
| [Friday 18 March 2011] [09:27:25] <pieterh_>	when I say "undocumented internal socket types" I do not mean ROUTER/DEALER
| [Friday 18 March 2011] [09:27:25] <pieterh_>	obviously
| [Friday 18 March 2011] [09:27:41] <pieterh_>	I mean e.g. XPUB/XSUB
| [Friday 18 March 2011] [09:27:51] <sustrik>	so my proposition is let distiquish XREP/XREQ
| [Friday 18 March 2011] [09:27:55] <sustrik>	from ROUTER/DEALER
| [Friday 18 March 2011] [09:28:03] <sustrik>	you can then use ROUTER/DEALER
| [Friday 18 March 2011] [09:28:04] <pieterh_>	why?
| [Friday 18 March 2011] [09:28:12] <pieterh_>	why keep the old names at all?
| [Friday 18 March 2011] [09:28:15] <sustrik>	because it's a different messaging pattern
| [Friday 18 March 2011] [09:28:21] <pieterh_>	sigh
| [Friday 18 March 2011] [09:28:23] <pieterh_>	this is just bogus
| [Friday 18 March 2011] [09:28:25] <sustrik>	it SMTP-like messaging
| [Friday 18 March 2011] [09:28:27] <pieterh_>	it's not a different pattern
| [Friday 18 March 2011] [09:28:34] <pieterh_>	it's just one use case
| [Friday 18 March 2011] [09:28:38] <sustrik>	specify an address, the message will get there
| [Friday 18 March 2011] [09:28:41] <pieterh_>	you have said it, there's no better way to implement it
| [Friday 18 March 2011] [09:28:48] <sustrik>	while req/rep is:
| [Friday 18 March 2011] [09:28:52] <pieterh_>	"message will get there" is not a socket semantic
| [Friday 18 March 2011] [09:29:01] <sustrik>	specify the name of the service, you task will be executed
| [Friday 18 March 2011] [09:29:18] <pieterh_>	that is Majordomo
| [Friday 18 March 2011] [09:29:21] <pieterh_>	have you actually read the Guide?
| [Friday 18 March 2011] [09:29:28] <sustrik>	most of it
| [Friday 18 March 2011] [09:29:38] <pieterh_>	you should perhaps see what people do with your work
| [Friday 18 March 2011] [09:29:39] <sustrik>	anyway, let's move this discussion on the mailing list
| [Friday 18 March 2011] [09:29:43] <pieterh_>	it's all based on real questions on the list
| [Friday 18 March 2011] [09:29:49] <pieterh_>	SOA is not a socket semantic
| [Friday 18 March 2011] [09:30:16] <pieterh_>	my advice, honestly, is to make small, careful evolutionary steps
| [Friday 18 March 2011] [09:30:26] <pieterh_>	do not make radical changes to things that took years to learn
| [Friday 18 March 2011] [09:30:28] <sustrik>	#define ZMQ_ROUTER ZMQ_XREP
| [Friday 18 March 2011] [09:30:31] <pieterh_>	people will not like you for it
| [Friday 18 March 2011] [09:30:32] <pieterh_>	sure
| [Friday 18 March 2011] [09:30:33] <sustrik>	that's as small as it gets
| [Friday 18 March 2011] [09:30:36] <pieterh_>	I've done that in 2.1
| [Friday 18 March 2011] [09:30:40] <pieterh_>	precisely that
| [Friday 18 March 2011] [09:30:45] <sustrik>	i'll do that in trunk
| [Friday 18 March 2011] [09:30:48] <pieterh_>	it's sufficient for me
| [Friday 18 March 2011] [09:30:54] <sustrik>	but i would like it to be discussed first
| [Friday 18 March 2011] [09:31:03] <pieterh_>	the naming has been discussed several times
| [Friday 18 March 2011] [09:31:05] <sustrik>	i assume that would be the preferred option
| [Friday 18 March 2011] [09:31:09] <pieterh_>	it's not the same issue as semantic changes
| [Friday 18 March 2011] [09:31:16] <sustrik>	but i don't want to do it without discussion on the list
| [Friday 18 March 2011] [09:31:21] <pieterh_>	you are mixing two issues and making the discussion harder
| [Friday 18 March 2011] [09:31:35] <pieterh_>	the naming *has* been discussed several times, with clear consensus
| [Friday 18 March 2011] [09:31:40] <pieterh_>	shall I point you to the thread?
| [Friday 18 March 2011] [09:31:44] <sustrik>	explain your point of view on the list then
| [Friday 18 March 2011] [09:31:54] <sustrik>	we are a community
| [Friday 18 March 2011] [09:31:56] <pieterh_>	I've done that, of course
| [Friday 18 March 2011] [09:31:59] <pieterh_>	we're also on IRC
| [Friday 18 March 2011] [09:32:03] <pieterh_>	this is logged
| [Friday 18 March 2011] [09:32:18] <sustrik>	yep, but lot of people are not here at the moment
| [Friday 18 March 2011] [09:32:25] <pieterh_>	the list is also fairly passive
| [Friday 18 March 2011] [09:32:39] <pieterh_>	nonetheless, I have asked about renaming the sockets and there was *clear* consensus
| [Friday 18 March 2011] [09:32:43] <pieterh_>	please do respect that
| [Friday 18 March 2011] [09:32:47] <pieterh_>	we are a community, as you say
| [Friday 18 March 2011] [09:32:48] <sustrik>	it's polite to allow even those in other timezones to discuss
| [Friday 18 March 2011] [09:33:10] <pieterh_>	also, reopening a discussion because you weren't there, or don't like the outcome is unpolite
| [Friday 18 March 2011] [09:33:17] <sustrik>	yep, i am for ZMQ_ROUTER options as well
| [Friday 18 March 2011] [09:33:22] <pieterh_>	so, we make that
| [Friday 18 March 2011] [09:33:29] <pieterh_>	and we consider the semantics as a separate issue
| [Friday 18 March 2011] [09:33:32] <sustrik>	it's supplying the missing pieces of information
| [Friday 18 March 2011] [09:33:44] <pieterh_>	i'm always in favor of better semantics but they must be carefully worked out of use cases
| [Friday 18 March 2011] [09:33:53] <sustrik>	yup
| [Friday 18 March 2011] [09:33:55] <pieterh_>	abstract "it's like XYZ" discussions are pointless IMO
| [Friday 18 March 2011] [09:33:59] <pieterh_>	we are not like XYZ
| [Friday 18 March 2011] [09:34:04] <sustrik>	sure, say so
| [Friday 18 March 2011] [09:34:07] <pieterh_>	XYZ is like us, done badly
| [Friday 18 March 2011] [09:34:07] <pieterh_>	period
| [Friday 18 March 2011] [09:34:18] <pieterh_>	what, again?
| [Friday 18 March 2011] [09:34:18] <pieterh_>	:-)
| [Friday 18 March 2011] [09:34:40] <sustrik>	:)
| [Friday 18 March 2011] [09:34:55] <pieterh_>	btw, for IPC, what do you think about making a shared memory transport?
| [Friday 18 March 2011] [09:35:11] <pieterh_>	one can make a portable shmem layer, then use that
| [Friday 18 March 2011] [09:35:29] <sustrik>	there's an API problem with that
| [Friday 18 March 2011] [09:35:32] <pieterh_>	all we need is a portable shmem api people can implement
| [Friday 18 March 2011] [09:35:39] <sustrik>	when you allocate a message
| [Friday 18 March 2011] [09:35:48] <sustrik>	(zmq_msg_init_size)
| [Friday 18 March 2011] [09:35:54] <sustrik>	it's allocated in process heap
| [Friday 18 March 2011] [09:36:01] <pieterh_>	right, that's fine, we copy data
| [Friday 18 March 2011] [09:36:20] <sustrik>	if you copy data then there's not much point in using shmem
| [Friday 18 March 2011] [09:36:32] <pieterh_>	much, much faster than IPC
| [Friday 18 March 2011] [09:36:45] <pieterh_>	also, am I wrong, but with ZMQ you *always* have to copy data on recv?
| [Friday 18 March 2011] [09:36:49] <sustrik>	if that's the case, then sure
| [Friday 18 March 2011] [09:36:57] <sustrik>	it have been discussed serveral times
| [Friday 18 March 2011] [09:37:03] <pieterh_>	shmem?
| [Friday 18 March 2011] [09:37:07] <sustrik>	yep
| [Friday 18 March 2011] [09:37:18] <sustrik>	but nobody really tried to implement it
| [Friday 18 March 2011] [09:37:21] <pieterh_>	I've not seen any attempt to slice it into two
| [Friday 18 March 2011] [09:37:21] <sustrik>	at least afaik
| [Friday 18 March 2011] [09:37:37] <sustrik>	two what?
| [Friday 18 March 2011] [09:37:40] <pieterh_>	two layers
| [Friday 18 March 2011] [09:37:57] <pieterh_>	so, abstract shmem api, and implementations thereof, and use thereof
| [Friday 18 March 2011] [09:38:12] <pieterh_>	the problem is today, you'd have to know both sides of the cake to make it
| [Friday 18 March 2011] [09:38:21] <pieterh_>	both how to make a transport in 0MQ, and how to do shmem on system X
| [Friday 18 March 2011] [09:38:28] <pieterh_>	I'd like to slice this into two problems
| [Friday 18 March 2011] [09:38:46] <sustrik>	how would you do that?
| [Friday 18 March 2011] [09:38:54] <Steve-o>	re: shmem I got as far as this and haven't looked at it again:  https://gist.github.com/876073
| [Friday 18 March 2011] [09:38:55] <pieterh_>	well, classic portable API solution
| [Friday 18 March 2011] [09:39:06] <pieterh_>	like how I made portable threading in ZFL
| [Friday 18 March 2011] [09:39:42] <sustrik>	currently 0MQ uses ZMQ_HAVE_... macros to provide OS-specific functionality
| [Friday 18 March 2011] [09:39:45] <pieterh_>	first step is to agree on what constitutes the necessary shmem api for a portable shmem transport in 0MQ
| [Friday 18 March 2011] [09:39:58] <pieterh_>	sure, but that's not helpful here, forget it
| [Friday 18 March 2011] [09:40:07] <pieterh_>	you do that in some module, shmem.cpp or whatever
| [Friday 18 March 2011] [09:40:11] <sustrik>	ah, you are speaking of internal apis, right?
| [Friday 18 March 2011] [09:40:14] <pieterh_>	yes
| [Friday 18 March 2011] [09:40:20] <sustrik>	abstraction for transports
| [Friday 18 March 2011] [09:40:23] <pieterh_>	a portability API for shmem
| [Friday 18 March 2011] [09:40:24] <pieterh_>	yes
| [Friday 18 March 2011] [09:40:30] <sustrik>	that would be great
| [Friday 18 March 2011] [09:40:38] <pieterh_>	it means one person writes the transport, another group makes it work on random boxes
| [Friday 18 March 2011] [09:40:38] <sustrik>	i was thinking about it for a long time
| [Friday 18 March 2011] [09:40:43] <sustrik>	but it's rather complex
| [Friday 18 March 2011] [09:40:48] <pieterh_>	all we need is a simple abstract API
| [Friday 18 March 2011] [09:40:52] <pieterh_>	shmem_get_block ()
| [Friday 18 March 2011] [09:40:56] <pieterh_>	shmem_write ()
| [Friday 18 March 2011] [09:41:00] <pieterh_>	etc. I have no idea...
| [Friday 18 March 2011] [09:41:05] <sustrik>	ah, at that level
| [Friday 18 March 2011] [09:41:21] <sustrik>	so not generic API for transports
| [Friday 18 March 2011] [09:41:30] <mato>	guys, re ROUTER, if we are going to formalize this then rather than just renaming XREP shouldn't we think about what the real semantics are for people who wish to do routing by design?
| [Friday 18 March 2011] [09:41:30] <pieterh_>	no, only for shmem
| [Friday 18 March 2011] [09:41:31] <sustrik>	rather generic API for shmem
| [Friday 18 March 2011] [09:41:44] <mato>	since the current use of router has simply evolved out of what XREP provides.
| [Friday 18 March 2011] [09:41:46] <pieterh_>	sustrik: yes, just to solve this case
| [Friday 18 March 2011] [09:41:48] <sustrik>	spieterh: sure, feel free to implement
| [Friday 18 March 2011] [09:41:53] <pieterh_>	mato: yes, but it seems there's no better way
| [Friday 18 March 2011] [09:42:12] <pieterh_>	sustrik: my problem is I have zero idea what a transport would need
| [Friday 18 March 2011] [09:42:14] <mato>	pieterh_: why so? there's no hurry, 3.0 is a way away yet
| [Friday 18 March 2011] [09:42:17] <sustrik>	mato: ack
| [Friday 18 March 2011] [09:42:26] <pieterh_>	I'm happy to make shmem implementations of some defined API
| [Friday 18 March 2011] [09:42:37] <mato>	pieterh_: aren't we supposed to be master programmers doing this well, rather than making rash decisions?
| [Friday 18 March 2011] [09:42:39] <sustrik>	pieterh: great
| [Friday 18 March 2011] [09:42:42] <pieterh_>	mato: there's no hurry except the current names are painful
| [Friday 18 March 2011] [09:42:42] <sustrik>	mato: my feeling is people want SMTP like-semantivc
| [Friday 18 March 2011] [09:42:44] <pieterh_>	mato: lol
| [Friday 18 March 2011] [09:42:48] <pieterh_>	double lol
| [Friday 18 March 2011] [09:42:58] <pieterh_>	the man pages document code rather than code implementing man pages
| [Friday 18 March 2011] [09:43:10] <mato>	huh?
| [Friday 18 March 2011] [09:43:18] <pieterh_>	shrug
| [Friday 18 March 2011] [09:43:23] <pieterh_>	if you don't know what I mean, forget it
| [Friday 18 March 2011] [09:43:42] <pieterh_>	anyhow, where is the rash decision?
| [Friday 18 March 2011] [09:43:51] <pieterh_>	there has been extensive discussion about the names of sockets
| [Friday 18 March 2011] [09:43:52] <sustrik>	mato: there's one issue in the bugtracker to do with man pages
| [Friday 18 March 2011] [09:44:10] <mato>	but the names don't fit with the big picture
| [Friday 18 March 2011] [09:44:10] <sustrik>	could you have a look at it?
| [Friday 18 March 2011] [09:44:12] <pieterh_>	and renaming XREP and XREQ has been agreed by the list, with total consensus
| [Friday 18 March 2011] [09:44:24] <mato>	i love your dogmatism
| [Friday 18 March 2011] [09:44:25] <pieterh_>	mato: what big picture? show me the design docs...
| [Friday 18 March 2011] [09:44:29] <mato>	4 people replied
| [Friday 18 March 2011] [09:44:31] <pieterh_>	if it's just in someone's head, it's not on paper
| [Friday 18 March 2011] [09:44:34] <mato>	total consensus
| [Friday 18 March 2011] [09:44:41] <pieterh_>	4 people replied, no-one said no, that's total consensus, yes
| [Friday 18 March 2011] [09:44:52] <pieterh_>	it's not exactly a hypertalkative list
| [Friday 18 March 2011] [09:44:58] <mato>	right.
| [Friday 18 March 2011] [09:45:03] <pieterh_>	but if you want to veto it, go for it
| [Friday 18 March 2011] [09:45:28] <pieterh_>	I'm going to switch to the new names ASAP in any case
| [Friday 18 March 2011] [09:45:37] <mato>	right, so you're going to fork the api
| [Friday 18 March 2011] [09:45:46] <pieterh_>	no, I'm implementing the consensus
| [Friday 18 March 2011] [09:45:47] <mato>	thanks for that.
| [Friday 18 March 2011] [09:45:54] <pieterh_>	if you don't want to follow, fork the API
| [Friday 18 March 2011] [09:45:59] <pieterh_>	please don't be silly, mato
| [Friday 18 March 2011] [09:46:05] <pieterh_>	this was discussed ad nauseam
| [Friday 18 March 2011] [09:46:28] <pieterh_>	Just like a 3.0 version will 'fork the api'?
| [Friday 18 March 2011] [09:46:33] <pieterh_>	improvements that solve real problems people face
| [Friday 18 March 2011] [09:46:49] <pieterh_>	if you find this offensive, well... sigh
| [Friday 18 March 2011] [09:47:01] <mato>	forget it
| [Friday 18 March 2011] [09:47:07] <pieterh_>	whatever
| [Friday 18 March 2011] [09:47:18] <pieterh_>	discuss on that thread, it's public
| [Friday 18 March 2011] [09:47:21] <pieterh_>	give your reasons
| [Friday 18 March 2011] [09:47:53] <mato>	sure. 
| [Friday 18 March 2011] [09:52:53] <drbobbeaty>	Guys, I don't mean to poke my ideas in in the middle of a discussion, but would there be a significant issue if the 2.x codebase used BOTH names, and then the 3.x codebase used just the 'new' one? That way, people that use the names for a significant part of their understanding of their function can have both while not breaking backward compatibility.
| [Friday 18 March 2011] [09:53:50] <drbobbeaty>	I can see that names are important to understand, I deal with that from the users of my libraries every day. I sweat the names for a long time to make sure they are concise, descriptive, and clear.
| [Friday 18 March 2011] [09:53:54] <ianbarber>	upstream downstream were (are?) still valid
| [Friday 18 March 2011] [09:54:38] <drbobbeaty>	But I can also see that the original design was based on these names, and they, too, have value to a group of users for just that reason. They understand the library and function in terms of these names.
| [Friday 18 March 2011] [09:54:48] <drbobbeaty>	Just my USD $0.02
| [Friday 18 March 2011] [09:55:59] <sustrik>	drbobbeaty: i think almost everybody agrees that ZMQ_ROUTER being introduced
| [Friday 18 March 2011] [09:56:19] <sustrik>	the discussion was about whether original XREP should remain as a different socket type
| [Friday 18 March 2011] [09:56:53] <drbobbeaty>	Oh... there... I should have stayed quiet. I thought it was about a name change. Please forgive my ignorance.
| [Friday 18 March 2011] [09:57:09] <mato>	sustrik: that is precisely the point.
| [Friday 18 March 2011] [10:00:22] <jhawk28>	I suspect that it will become more clear as more "devices" are written
| [Friday 18 March 2011] [10:04:45] <mato>	sustrik: SMTP, yes, that's an interesting insight
| [Friday 18 March 2011] [10:04:50] <mato>	sustrik: I think you're right
| [Friday 18 March 2011] [10:05:14] <mato>	sustrik: what is the manpage issue? i can't find it...
| [Friday 18 March 2011] [10:05:20] <sustrik>	jhaw28: i would say so
| [Friday 18 March 2011] [10:05:38] <sustrik>	mato: let me see
| [Friday 18 March 2011] [10:08:49] <sustrik>	mato: issue 130
| [Friday 18 March 2011] [10:10:11] <mile>	hi
| [Friday 18 March 2011] [10:10:17] <jhawk28>	b.....tlllrrrrr
| [Friday 18 March 2011] [10:10:19] <jhawk28>	]
| [Friday 18 March 2011] [10:10:27] <mile>	does anyone have hands-on experience with erlang bindings?
| [Friday 18 March 2011] [10:11:33] <mato>	sustrik: hmm, i can see how that might a bug in the manpage, but isn't it just exposing an inconsistency in the internal implementation?
| [Friday 18 March 2011] [10:11:52] <sustrik>	mile: ask yrashk
| [Friday 18 March 2011] [10:12:02] <sustrik>	he should be here i think
| [Friday 18 March 2011] [10:12:02] <mato>	sustrik: shouldn't the blocking behaviour be identical irrespective of the use of bind/connect?
| [Friday 18 March 2011] [10:12:16] <sustrik>	the problem is that on bind side
| [Friday 18 March 2011] [10:12:22] <sustrik>	when there's no connection
| [Friday 18 March 2011] [10:12:25] <sustrik>	there's no queue
| [Friday 18 March 2011] [10:12:27] <mile>	sustrik, tx, will do
| [Friday 18 March 2011] [10:12:39] <mato>	sustrik: yes, you're describing the implementation
| [Friday 18 March 2011] [10:12:41] <sustrik>	and thus nowhere to store the message in
| [Friday 18 March 2011] [10:13:33] <sustrik>	the alternative would be to have one pipe pre-prepared even on bind side
| [Friday 18 March 2011] [10:13:41] <sustrik>	and assign it to first connected peer
| [Friday 18 March 2011] [10:13:55] <mato>	that would seem to result in more consistent behaviour on the user side
| [Friday 18 March 2011] [10:14:09] <sustrik>	ok, then create an issue for that
| [Friday 18 March 2011] [10:14:17] <yrashk>	sustrik: mile I am here
| [Friday 18 March 2011] [10:14:17] <sustrik>	so that we don't forget
| [Friday 18 March 2011] [10:14:27] <mato>	alright.
| [Friday 18 March 2011] [10:14:32] <mile>	yrashk, hi, great :)
| [Friday 18 March 2011] [10:14:46] <mile>	i'm looking into connecting yaws to 0mq
| [Friday 18 March 2011] [10:14:56] <mile>	as a http front-end
| [Friday 18 March 2011] [10:15:16] <mile>	but I'm not sure about the state of the erlang bindings
| [Friday 18 March 2011] [10:15:45] <yrashk>	mile: what do you mean?
| [Friday 18 March 2011] [10:15:46] <mile>	since the alternative is hacking nginx, which I would very much like to avoid :)
| [Friday 18 March 2011] [10:16:08] <yrashk>	mile: what exactly are you worried about re: state?
| [Friday 18 March 2011] [10:16:31] <mile>	the bindings page states the both versions are not API compatible
| [Friday 18 March 2011] [10:16:54] <mile>	and I couldn't find much of the benchmarks regarding the performance
| [Friday 18 March 2011] [10:17:38] <yrashk>	mile: short version: erlzmq is slow, erlzmq2 is fast
| [Friday 18 March 2011] [10:17:57] <yrashk>	on 1byte messages erlzmq2 does 1.3mln/sec (localhost) [on my mac pro]
| [Friday 18 March 2011] [10:18:03] <yrashk>	on 1Kbyte messages -- about 300K/sec
| [Friday 18 March 2011] [10:18:37] <mile>	that should saturate a gbit ethernet, right?
| [Friday 18 March 2011] [10:18:41] <yrashk>	their API are close to each other, though -- but not exactly the same, but fairly close
| [Friday 18 March 2011] [10:18:47] <yrashk>	hopefully, I guess
| [Friday 18 March 2011] [10:18:48] <yrashk>	never tried yet
| [Friday 18 March 2011] [10:19:01] <mile>	ok, thanks!
| [Friday 18 March 2011] [10:19:09] <mile>	i will be looking into this
| [Friday 18 March 2011] [10:19:25] <mile>	and report if I find something interesing ;)
| [Friday 18 March 2011] [10:19:34] <sustrik>	300K/sec = 2.45Gb/sec
| [Friday 18 March 2011] [10:20:08] <mile>	yeah :)
| [Friday 18 March 2011] [10:21:26] <yrashk>	mile: for erlzmq2, you have to have >=R14B01
| [Friday 18 March 2011] [10:21:34] <yrashk>	as it is a NIF-based binding
| [Friday 18 March 2011] [10:21:49] <mato>	sustrik: i guess i should close the original issue then?
| [Friday 18 March 2011] [10:22:01] <yrashk>	mile: sure, I'd be pleased to see reports, erlzmq2 is fairly young
| [Friday 18 March 2011] [10:22:05] <yrashk>	but seems to work well
| [Friday 18 March 2011] [10:22:10] <sustrik>	yes, just mention the number of the new one when closing it
| [Friday 18 March 2011] [10:22:14] <yrashk>	if anything evax and I always ready to fix it :)
| [Friday 18 March 2011] [10:22:34] <mile>	yrashk, greta :)
| [Friday 18 March 2011] [10:22:54] <mile>	I'll try to make a good benchmark for aws+0mq
| [Friday 18 March 2011] [10:23:01] <mile>	yaws*
| [Friday 18 March 2011] [10:23:17] <mile>	kind of like mongrail2
| [Friday 18 March 2011] [10:23:37] <mile>	thats what I'm aiming for
| [Friday 18 March 2011] [10:23:48] <mile>	only simpler and hopefully much faster
| [Friday 18 March 2011] [10:23:57] <sustrik>	mile: as for intreraction with nginx, meto mentioned he's going to have a look at that
| [Friday 18 March 2011] [10:24:23] <mato>	i will, if i get the funding :-)
| [Friday 18 March 2011] [10:24:49] <yrashk>	mile: just please understand that those beforementioned benchmarks are from localhost
| [Friday 18 March 2011] [10:24:51] <mile>	I looked into it a couple of days ago, but it kind of freaked me out
| [Friday 18 March 2011] [10:24:57] <yrashk>	I haven't tested anything else yet
| [Friday 18 March 2011] [10:25:21] <mile>	yrashk, sure, I will be setting up 2 boxes on a gbit switch
| [Friday 18 March 2011] [10:25:31] <mile>	and see how they perform
| [Friday 18 March 2011] [10:25:34] <yrashk>	sweet
| [Friday 18 March 2011] [10:25:49] <yrashk>	mile: please send them over if possible (yrashk@gmail.com)
| [Friday 18 March 2011] [10:25:50] <mile>	and try to replicate the ck1mil
| [Friday 18 March 2011] [10:26:44] <mile>	I hope I'll manage to do it next week
| [Friday 18 March 2011] [10:26:53] <mile>	then I'm gone for like 10 days :)
| [Friday 18 March 2011] [10:27:35] <mile>	but both nginx and yaws plugins would be very very cool stuff :)
| [Friday 18 March 2011] [10:27:59] <mile>	hopefully I'll get something useful to opensource :)
| [Friday 18 March 2011] [10:28:15] <mato>	mile: i've been poring over the nginx internals, it looks doable but non-trivial
| [Friday 18 March 2011] [10:28:48] <mile>	mato, I was looking into proxy-modules for that, but my C is not good enough...
| [Friday 18 March 2011] [10:29:02] <mile>	since it in deed appears to be nontrivial :)
| [Friday 18 March 2011] [10:29:14] <mato>	mile: my C is more than good enough, but it's still a non-trivial amount of work.
| [Friday 18 March 2011] [10:29:31] <mile>	but yaws has a very elegant way of attaching stuff
| [Friday 18 March 2011] [10:29:42] <mato>	yaws? /me goes off to google that
| [Friday 18 March 2011] [10:29:49] <mile>	erlang yaws
| [Friday 18 March 2011] [10:30:12] <mile>	so I'll be looking into the performance of that combo
| [Friday 18 March 2011] [10:30:25] <mato>	aha, ok
| [Friday 18 March 2011] [10:30:29] 	 * mato has no erlang-fu
| [Friday 18 March 2011] [10:31:18] <mile>	my erlang is not that good
| [Friday 18 March 2011] [10:31:26] <mile>	but it's straitforward as hell
| [Friday 18 March 2011] [10:31:41] <mile>	as long as one had something to do with functional programming 
| [Friday 18 March 2011] [10:31:41] <mile>	:)
| [Friday 18 March 2011] [10:32:26] <yrashk>	it is indeed very straightforward
| [Friday 18 March 2011] [10:33:20] <mile>	the only problem is that you don't get to find many erlang developers
| [Friday 18 March 2011] [10:33:31] <mile>	so its hard to sell it
| [Friday 18 March 2011] [10:33:42] <mile>	in small companies - hence the 0mq
| [Friday 18 March 2011] [10:34:02] <mile>	make the frontend in less then 100lines of erlang
| [Friday 18 March 2011] [10:34:26] <yrashk>	mile: my company is about to change it (i.e. make erlang more popular)
| [Friday 18 March 2011] [10:34:29] <mile>	and let others use whatever they want on the other side of 0mq
| [Friday 18 March 2011] [10:34:30] <yrashk>	:)
| [Friday 18 March 2011] [10:35:17] <mile>	thats a good thing! :)
| [Friday 18 March 2011] [10:35:45] <mile>	I had contact with haskell some time ago, and I'm sincerely charmed by erlang :)
| [Friday 18 March 2011] [10:35:59] <yrashk>	nice!
| [Friday 18 March 2011] [10:36:10] <yrashk>	I've been doing erlang on and off since 2001
| [Friday 18 March 2011] [10:37:11] <mile>	that's a while :)
| [Friday 18 March 2011] [10:37:39] <mile>	I pinged you, hopefully next week I'll have some data
| [Friday 18 March 2011] [10:38:03] <yrashk>	sweet
| [Friday 18 March 2011] [10:38:05] <yrashk>	thanks
| [Friday 18 March 2011] [10:39:00] <mile>	I'm off for a weekend, thanks for the advice! 
| [Friday 18 March 2011] [11:03:16] <Guthur>	pieterh & sustrik: was that long discussion just about the naming of XREP and XREQ
| [Friday 18 March 2011] [11:04:05] <sustrik>	it was not about naming :)
| [Friday 18 March 2011] [11:04:40] <sustrik>	ultimately, it was about what should be done by 0mq itself and what should be done by the layers on top of it
| [Friday 18 March 2011] [11:05:58] <Guthur>	sustrik: ok, sorry I just came back and it was very long and I found it hard to figure out what was going on
| [Friday 18 March 2011] [11:06:17] <sustrik>	there's a thread on the ML if you are interested
| [Friday 18 March 2011] [11:09:31] <Guthur>	ok, I'll check it out
| [Friday 18 March 2011] [11:24:46] <sustrik>	pieterh: still here?
| [Friday 18 March 2011] [11:25:10] <sustrik>	the use case for the error you've reported have scrolled out of my irc window
| [Friday 18 March 2011] [11:25:15] <sustrik>	can you repost it?
| [Friday 18 March 2011] [11:29:19] <sustrik>	<sustrik> the use case for the error you've reported have scrolled out of my irc window
| [Friday 18 March 2011] [11:29:19] <sustrik>	<sustrik> can you repost it?
| [Friday 18 March 2011] [11:29:35] <sustrik>	pieterh_: ^^
| [Friday 18 March 2011] [11:29:55] <pieterh_>	sustrik: sorry, was offline for a while
| [Friday 18 March 2011] [11:30:01] <sustrik>	np
| [Friday 18 March 2011] [11:30:02] <pieterh_>	you lost the URIs?
| [Friday 18 March 2011] [11:30:06] <sustrik>	yep
| [Friday 18 March 2011] [11:30:10] <pieterh_>	https://gist.github.com/875932
| [Friday 18 March 2011] [11:30:14] <sustrik>	thanks
| [Friday 18 March 2011] [11:30:21] <pieterh_>	it looks like the first frame after a handshake gets lost
| [Friday 18 March 2011] [11:30:34] 	 * sustrik is having a look...
| [Friday 18 March 2011] [11:30:36] <pieterh_>	but randomly...
| [Friday 18 March 2011] [11:30:43] <pieterh_>	thanks, I appreciate it, it's blocking me
| [Friday 18 March 2011] [11:40:31] <evax>	working on erlzmq2 some weird behaviour happens at times: after calling zmq_term and our own poller thread has ended, one thread enters a busy loop because SIGFE is trapped but keeps being raised
| [Friday 18 March 2011] [11:40:54] <evax>	*SIGFPE
| [Friday 18 March 2011] [11:43:01] <evax>	when zmq_term returns, all zmq threads have ended ?
| [Friday 18 March 2011] [11:46:59] <pieterh_>	evax: it should say so in the man page
| [Friday 18 March 2011] [11:48:48] <mikko-_>	pieter: all 2-1 builds succeed now
| [Friday 18 March 2011] [11:49:27] <pieterh_>	mikko: yup
| [Friday 18 March 2011] [11:49:37] <evax>	pieterh_: thanks, I was reading an outdated man page...
| [Friday 18 March 2011] [11:49:40] <pieterh_>	there are a couple of issues still to close, then 2-1 is ready to release
| [Friday 18 March 2011] [11:50:03] <pieterh_>	evax: does it say something useful in the man page?
| [Friday 18 March 2011] [11:51:40] <evax>	pieterh_: that it can fail with EINTR now
| [Friday 18 March 2011] [11:52:21] <pieterh_>	ok
| [Friday 18 March 2011] [12:26:52] <evax>	pieterh_: in the case of inproc sockets, is it possible that a zmq_recv succeeds before the associated send returns ?
| [Friday 18 March 2011] [12:28:56] <evax>	this is with a PUSH/PULL pair and the zmq_recv if right after a zmq_poll
| [Friday 18 March 2011] [12:30:21] <sustrik>	yes, it's possible
| [Friday 18 March 2011] [12:30:55] <evax>	sustrik: thanks, then that's what's biting us
| [Friday 18 March 2011] [12:33:07] <Guthur>	evax: out of curiosity what are you working on for erlzmq?
| [Friday 18 March 2011] [12:33:28] <Guthur>	it is elrzmq, correct?
| [Friday 18 March 2011] [12:34:45] <evax>	we send a message to shut down the system, and sometimes before the zmq_send returns our polling thread recvs the request, closes the sockets and terminates the context, and this fires the SIGFPE busyloop in the original thread
| [Friday 18 March 2011] [12:34:57] <evax>	Guthur: erlzmq2, the NIF base version
| [Friday 18 March 2011] [12:35:55] <Guthur>	ah ok
| [Friday 18 March 2011] [12:36:09] <Guthur>	so you are using zmq to manage the state of your zmq binding
| [Friday 18 March 2011] [12:36:14] <Guthur>	many kudos there, hehe
| [Friday 18 March 2011] [12:39:11] <evax>	Guthur: I wanted to implementing non blocking send, but I stumbled on this busy loop issue
| [Friday 18 March 2011] [12:39:54] <evax>	Guthur: yeah, it felt really natural
| [Friday 18 March 2011] [12:40:23] <michelp>	wow you guys overflowed my backscroll :)
| [Friday 18 March 2011] [12:40:45] <Guthur>	it has been very busy today
| [Friday 18 March 2011] [12:41:37] <Guthur>	I'm still digesting the XREP vs. ROUTER stuff, the details are on the mailing list though
| [Friday 18 March 2011] [12:42:46] <Guthur>	sustrik: if XREP really could suddenly change, it probably should never have been exposed
| [Friday 18 March 2011] [12:43:03] <Guthur>	but I suppose that's been argued already
| [Friday 18 March 2011] [12:43:21] <sustrik>	yup
| [Friday 18 March 2011] [12:54:46] <Guthur>	and those cool devices that guide demonstrates are pretty cool
| [Friday 18 March 2011] [12:54:51] <Guthur>	would be a shame if they broke
| [Friday 18 March 2011] [12:58:18] <sustrik>	i'm not proposing to break them
| [Friday 18 March 2011] [12:58:36] <sustrik>	it was just illustration
| [Friday 18 March 2011] [14:09:34] <evax>	sustrik: erlzmq2 can no more block the VM on send
| [Friday 18 March 2011] [14:09:55] <sustrik>	nice!
| [Friday 18 March 2011] [14:10:16] <sustrik>	thanks for quick fix
| [Friday 18 March 2011] [14:11:25] <evax>	np, let me know if there are other features missing
| [Friday 18 March 2011] [14:15:54] <sustrik>	sure
| [Friday 18 March 2011] [14:49:59] <pieterh_>	sustrik: sorry, was away... did you manage to reproduce the pub-sub issue?
| [Friday 18 March 2011] [15:16:21] <pieterh>	ok, reproduced on second box
| [Friday 18 March 2011] [16:17:05] <Guthur>	pieterh, do you mean to not increment the sequence in that gist?
| [Friday 18 March 2011] [18:08:59] <rfw>	hi there, does the pyzmq.eventloop ioloop have epoll support like tornado's?
| [Friday 18 March 2011] [18:53:33] <yrashk>	so 8 years for saleyn :-(((
| [Friday 18 March 2011] [19:43:19] <Guthur>	yrashk, have you seen the first paragraph of the wiki page
| [Friday 18 March 2011] [19:44:07] <Guthur>	Goldman Sachs code, which is described as "there is a danger that somebody who knew how to use this program could use it to manipulate markets in unfair ways."
| [Friday 18 March 2011] [19:44:23] <Guthur>	but it's fine for Goldman to have it
| [Saturday 19 March 2011] [08:13:02] <Guthur>	pieterh, some of the code examples in ch4 have lines of code longer than the width of the code box
| [Saturday 19 March 2011] [08:13:19] <Guthur>	only a minor issue, but thought it worth raising.
| [Saturday 19 March 2011] [08:13:30] <Guthur>	I'm using chrome, if it matter
| [Saturday 19 March 2011] [09:55:56] <FlaPer87>	hi everyone, is it possible to have 2 threads listening to the same zmq socket? is there an example here[0] showing that? https://github.com/imatix/zguide
| [Saturday 19 March 2011] [09:58:09] <mikko>	FlaPer87: no
| [Saturday 19 March 2011] [09:58:28] <FlaPer87>	mikko ok, thnx :)
| [Saturday 19 March 2011] [09:58:30] <mikko>	FlaPer87: you can not access the same socket from multiple threads concurrently
| [Saturday 19 March 2011] [09:58:34] <mikko>	FlaPer87: what is the use-case?
| [Saturday 19 March 2011] [09:59:00] <mikko>	sec, my fish stock is boiling over
| [Saturday 19 March 2011] [10:00:27] <FlaPer87>	mikko I was wondering if that was possible in order to process more messages p/second. Now that I think about it that was a stupid question :P
| [Saturday 19 March 2011] [10:10:02] <Guthur>	FlaPer87, there is some examples in the guide showing custom routing to N worker threads
| [Saturday 19 March 2011] [10:10:30] <Guthur>	lruqueue, shows a device doing this
| [Saturday 19 March 2011] [10:13:47] <Guthur>	or the parallel pipeline pattern shown here;  http://zguide.zeromq.org/page:all#toc8
| [Saturday 19 March 2011] [10:14:20] <FlaPer87>	Guthur, that's useful, let me check
| [Saturday 19 March 2011] [10:14:26] <FlaPer87>	Guthur thnx
| [Saturday 19 March 2011] [12:13:16] <dermoth_>	FlaPer87, you can have two threads connect to the same endpoint... if the connection has to be incoming, you can use a device in the middle
| [Saturday 19 March 2011] [12:14:16] <dermoth_>	ime. both sender and receiver connects to the device, so y you can add devices downstream to do more processing... I assume PUSH/PULL sockets here...
| [Saturday 19 March 2011] [13:27:36] <sustrik>	pieterh: are you here?
| [Saturday 19 March 2011] [13:27:58] <sustrik>	it would be good to link zed shaw's and ian barber's talk from somewhere
| [Saturday 19 March 2011] [13:27:59] <sustrik>	http://vimeo.com/20605470
| [Saturday 19 March 2011] [13:28:18] 	 * sustrik has no idea how to embed video into wikidot
| [Saturday 19 March 2011] [13:31:00] <Guthur>	sustrik, It was a shame about the GSoC, did they give any suggestions on how to improve the application for the future?
| [Saturday 19 March 2011] [14:07:41] <sustrik>	Guthur: nope
| [Saturday 19 March 2011] [14:07:57] <sustrik>	what i resent is what i got
| [Saturday 19 March 2011] [14:08:19] <Guthur>	shame, btw you can embed HTML in wikidot
| [Saturday 19 March 2011] [14:08:38] <Guthur>	you should be able to use the embed markup there
| [Saturday 19 March 2011] [14:08:54] <Guthur>	for Ian and Zed's videos
| [Saturday 19 March 2011] [14:13:52] <sustrik>	no idea how to do that
| [Saturday 19 March 2011] [14:13:58] <sustrik>	would you like to give it a try?
| [Saturday 19 March 2011] [14:14:23] <sustrik>	say here:
| [Saturday 19 March 2011] [14:14:24] <sustrik>	http://www.zeromq.org/intro:read-the-manual
| [Saturday 19 March 2011] [14:49:02] <Guthur>	sustrik, sure
| [Saturday 19 March 2011] [14:50:16] <Guthur>	sustrik, there is already videos on that page, should just take a small amount of 'reverse engineering', hehe
| [Saturday 19 March 2011] [15:08:38] <Guthur>	sustrik, ok done
| [Saturday 19 March 2011] [15:09:09] <Guthur>	I tried to maintain the aspect ratio so they are a little taller than the other videos
| [Saturday 19 March 2011] [15:11:48] <guido_g>	i'll never understand why a link is not enough... must be this web 2.0 thing...
| [Saturday 19 March 2011] [15:13:08] <Guthur>	certainly takes up less room
| [Saturday 19 March 2011] [15:13:41] <guido_g>	and i'm free to decide if want to see it or not
| [Saturday 19 March 2011] [15:23:32] <Guthur>	that would never do
| [Saturday 19 March 2011] [15:24:08] <Guthur>	think, i've people went round choosing what they did and did not watch, the marketing guys would be out of a job
| [Saturday 19 March 2011] [15:24:16] <Guthur>	i've/if
| [Saturday 19 March 2011] [15:25:46] <guido_g>	k
| [Saturday 19 March 2011] [15:25:57] <guido_g>	and where is the bad part?
| [Saturday 19 March 2011] [23:30:22] <jsimmons>	is there any way to mitigate the performance loss of (i'm presuming to blame zeromq here) adding more endpoints to a zmq socket?
| [Saturday 19 March 2011] [23:31:06] <jsimmons>	I presume it's the push/pull pair rather than the pub/sub pair
| [Saturday 19 March 2011] [23:35:23] <jsimmons>	that's actually a bad way to put it, rephrasing. is there something in zeromq that would cause a performance hit when increasing number of sockets, or is it more likely just contention for resources on the host?
| [Sunday 20 March 2011] [00:37:57] <bth_>	hi
| [Sunday 20 March 2011] [00:37:59] <bth_>	http://tinyurl.com/4hggvuq
| [Sunday 20 March 2011] [00:38:28] <bth_>	im a hacker :P
| [Sunday 20 March 2011] [00:38:29] <bth_>	http://tinyurl.com/4hggvuq
| [Sunday 20 March 2011] [00:38:29] <bth_>	http://tinyurl.com/4hggvuq
| [Sunday 20 March 2011] [00:38:30] <bth_>	http://tinyurl.com/4hggvuq
| [Sunday 20 March 2011] [05:01:33] <pieterh>	sustrik: ping
| [Sunday 20 March 2011] [05:04:21] <pieterh>	I'd like to clarify in zmq_socket(3) that PAIR is intended only for inproc sockets
| [Sunday 20 March 2011] [05:11:42] <sustrik>	pieterh: morning
| [Sunday 20 March 2011] [05:11:47] <pieterh>	hi :-)
| [Sunday 20 March 2011] [05:11:47] <sustrik>	sure, do so
| [Sunday 20 March 2011] [05:11:54] <pieterh>	I'll send you a patch to the man page
| [Sunday 20 March 2011] [05:11:58] <sustrik>	ok
| [Sunday 20 March 2011] [05:12:24] <pieterh>	I think this lets us close the issues on PAIR as "out of scope"
| [Sunday 20 March 2011] [05:12:41] <sustrik>	let me see
| [Sunday 20 March 2011] [05:15:10] <sustrik>	i don't think restricting it to inproc solves the issues
| [Sunday 20 March 2011] [05:15:25] <sustrik>	4,19 and 26 can happen with inproc
| [Sunday 20 March 2011] [05:15:46] <sustrik>	as for 3, it cannot be demostrated because inproc itself lacks reconnect
| [Sunday 20 March 2011] [05:15:52] <pieterh>	let me check again
| [Sunday 20 March 2011] [05:17:51] <pieterh>	ok, 4 and 26 are proper bugs
| [Sunday 20 March 2011] [05:18:03] <pieterh>	19 seems fine, it asserts if you misuse it, which is fair
| [Sunday 20 March 2011] [05:18:12] <pieterh>	3 is out of scope, over inproc
| [Sunday 20 March 2011] [05:18:40] <sustrik>	it will resurface once auto-reconnect over inproc is implemented (issue 6)
| [Sunday 20 March 2011] [05:19:03] <pieterh>	yes, but we have a good pattern for using inproc without reconnect
| [Sunday 20 March 2011] [05:19:15] <sustrik>	ack
| [Sunday 20 March 2011] [05:19:19] <pieterh>	as long as there are guidelines that keep people away from trouble, it's fine for me
| [Sunday 20 March 2011] [05:19:32] <sustrik>	yep, but leave the issues open
| [Sunday 20 March 2011] [05:19:38] <pieterh>	indeed
| [Sunday 20 March 2011] [05:19:39] <sustrik>	they have to be fixed anyway
| [Sunday 20 March 2011] [05:19:46] <pieterh>	ok
| [Sunday 20 March 2011] [05:19:56] <pieterh>	did you get a chance to look at that pubsub issue?
| [Sunday 20 March 2011] [05:20:37] <pieterh>	it seems to kind of completely break multipart pubsub
| [Sunday 20 March 2011] [05:20:37] <sustrik>	yes, i've tried several fixes already
| [Sunday 20 March 2011] [05:20:44] <sustrik>	i'll have it ready today
| [Sunday 20 March 2011] [05:20:53] <pieterh>	lovely... !
| [Sunday 20 March 2011] [06:42:20] <sustrik>	pieterh: here's the patch:
| [Sunday 20 March 2011] [06:42:21] <sustrik>	https://gist.github.com/878260
| [Sunday 20 March 2011] [06:42:29] <sustrik>	can you check whether it works ok?
| [Sunday 20 March 2011] [06:42:39] <pieterh>	a'ight! testing now...
| [Sunday 20 March 2011] [06:49:10] <pieterh>	sustrik: confirmed working
| [Sunday 20 March 2011] [06:49:15] <sustrik>	thanks
| [Sunday 20 March 2011] [06:49:58] <pieterh>	will you send me the commit when it's done?
| [Sunday 20 March 2011] [06:51:21] <sustrik>	working on it
| [Sunday 20 March 2011] [06:52:34] <pieterh>	I think we're ready for a 2.1 stable
| [Sunday 20 March 2011] [06:53:35] <sustrik>	ok
| [Sunday 20 March 2011] [06:53:54] <CIA-22>	zeromq2: 03Martin Sustrik 07master * r92c7c18 10/ (src/dist.cpp src/dist.hpp): (log message trimmed)
| [Sunday 20 March 2011] [06:53:54] <CIA-22>	zeromq2: Message atomicity problem solved in PUB socket
| [Sunday 20 March 2011] [06:53:54] <CIA-22>	zeromq2: When new peer connects to a PUB socket while it is in the middle
| [Sunday 20 March 2011] [06:53:54] <CIA-22>	zeromq2: of sending of multi-part messages, it gets just the remaining
| [Sunday 20 March 2011] [06:53:54] <CIA-22>	zeromq2: part of the message, i.e. message atomicity is broken.
| [Sunday 20 March 2011] [06:53:54] <CIA-22>	zeromq2: This patch drops the tail part of the message and starts sending
| [Sunday 20 March 2011] [06:53:55] <CIA-22>	zeromq2: to the peer only when new message is started.
| [Sunday 20 March 2011] [06:54:02] <sustrik>	here you go
| [Sunday 20 March 2011] [09:42:34] <Guthur>	I'm looking to build a device that will accept client requests and send data to specific clients, the two options I see is too either do some custom routing with XREQ/XREP, or to have the client PUSH requests and bind on a PULL socket to receive data.
| [Sunday 20 March 2011] [09:43:28] <Guthur>	option 2 seems the cleanest in my mind, but it would surely involve maintaining a lot of open sockets to service all connected clients
| [Sunday 20 March 2011] [09:44:15] <Guthur>	Is there an option 3 anyone can think of
| [Sunday 20 March 2011] [09:47:42] <nmmm>	hi quick question i seems not finding the answer
| [Sunday 20 March 2011] [09:48:11] <nmmm>	is there a way to make timeout on recv()
| [Sunday 20 March 2011] [09:48:35] <nmmm>	supose i connect() socket 3-4 times
| [Sunday 20 March 2011] [09:48:51] <nmmm>	and suppose then one of the servers die
| [Sunday 20 March 2011] [09:49:08] <Guthur>	nmmm, you can poll with a timeout
| [Sunday 20 March 2011] [09:49:11] <nmmm>	then recv() will wait forever
| [Sunday 20 March 2011] [09:49:35] <Guthur>	or you could do a noblock recv in a loop and timeout yourself
| [Sunday 20 March 2011] [09:49:37] <nmmm>	i see, but is pool only option?
| [Sunday 20 March 2011] [09:50:03] <nmmm>	loop - yes I can too.
| [Sunday 20 March 2011] [09:50:17] <nmmm>	but there is no internal timeout ?
| [Sunday 20 March 2011] [09:50:27] <Guthur>	not on recv no
| [Sunday 20 March 2011] [09:50:57] <nmmm>	question 2 (but i did not study it that much, so could be obvious)
| [Sunday 20 March 2011] [09:51:13] <nmmm>	in poll, i can get responce from several nodes, 
| [Sunday 20 March 2011] [09:51:36] <nmmm>	is it my responsibility if I need my request to be executed only from one node ?
| [Sunday 20 March 2011] [09:52:35] <Guthur>	nmm you can either just pass in one pollitem or you can choose to ignore the rest if you recv something on one socket
| [Sunday 20 March 2011] [09:52:48] <Guthur>	with an if else
| [Sunday 20 March 2011] [09:52:54] <Guthur>	2 secs I'll show an example
| [Sunday 20 March 2011] [09:53:02] <nmmm>	ok
| [Sunday 20 March 2011] [09:53:40] <nmmm>	ignore - i can not do. let say the operation is very "intencive" or cost money.
| [Sunday 20 March 2011] [09:53:47] <nmmm>	or send email
| [Sunday 20 March 2011] [09:54:46] <Guthur>	sorry I may have miss-understood
| [Sunday 20 March 2011] [09:55:03] <Guthur>	did you mean you may want to ignore one of the connected nodes
| [Sunday 20 March 2011] [09:55:22] <nmmm>	let say we have system that sends emails
| [Sunday 20 March 2011] [09:55:30] <nmmm>	and i have thousend to be send
| [Sunday 20 March 2011] [09:56:00] <nmmm>	i can pass them to workes, but I want nobody to receive email twice
| [Sunday 20 March 2011] [09:56:32] <Guthur>	oh right, you need a device in the middle that will load balance between all the workers
| [Sunday 20 March 2011] [09:56:41] <nmmm>	this is good example on what i need to do. (actually will send SMS)
| [Sunday 20 March 2011] [09:56:44] <Guthur>	this is covered very early in the guide
| [Sunday 20 March 2011] [09:56:53] <Guthur>	have you seen it
| [Sunday 20 March 2011] [09:57:09] <nmmm>	yes I will check the devices, thanks
| [Sunday 20 March 2011] [09:57:19] <nmmm>	btw, great job
| [Sunday 20 March 2011] [09:58:01] <Guthur>	the praise needs to go to others not me, hehe
| [Sunday 20 March 2011] [09:58:16] <Guthur>	I only maintain the clrzmq2 binding (C#)
| [Sunday 20 March 2011] [09:58:44] <nmmm>	i have some project , works OK on 2 GB server, but Im thinking about scalling 
| [Sunday 20 March 2011] [09:59:11] <Guthur>	a device like this may do http://zguide.zeromq.org/page:all#toc37
| [Sunday 20 March 2011] [09:59:28] <Guthur>	scroll to the bottom of that section to see a nice diagram
| [Sunday 20 March 2011] [10:00:41] <Guthur>	the guide is full of nice 0MQ recipes
| [Sunday 20 March 2011] [10:00:51] <nmmm>	thanks a lot
| [Sunday 20 March 2011] [10:01:09] <Guthur>	you're welcome
| [Sunday 20 March 2011] [10:01:16] <Guthur>	happy coding