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
| [Sunday 20 March 2011] [15:54:11] <CIA-22>	zeromq2: 03Martin Sustrik 07master * r1619b3d 10/ (src/lb.cpp src/lb.hpp): 
| [Sunday 20 March 2011] [15:54:11] <CIA-22>	zeromq2: Message atomicity bug in load-balancer fixed
| [Sunday 20 March 2011] [15:54:11] <CIA-22>	zeromq2: If the peer getting the message have disconnected in the middle
| [Sunday 20 March 2011] [15:54:11] <CIA-22>	zeromq2: of multiplart message, the remaining part of the message went
| [Sunday 20 March 2011] [15:54:11] <CIA-22>	zeromq2: to a different peer. This patch fixes the issue.
| [Sunday 20 March 2011] [15:54:11] <CIA-22>	zeromq2: Signed-off-by: Martin Sustrik <sustrik@250bpm.com> - http://bit.ly/eAhwVE
| [Monday 21 March 2011] [05:54:40] <pieterh>	sustrik: ping
| [Monday 21 March 2011] [06:01:31] <pieterh>	ok, new packages of 0MQ 2.0 and 2.1 are fresh and hot!
| [Monday 21 March 2011] [06:05:29] <Guthur>	pieterh: should all socket types be able to connect and bind in any order?
| [Monday 21 March 2011] [06:05:46] <pieterh>	Guthur: in an ideal world, yes, but there are gaps
| [Monday 21 March 2011] [06:05:52] <pieterh>	e.g. PAIR sockets can't
| [Monday 21 March 2011] [06:06:01] <Guthur>	what about PUSH/PULL
| [Monday 21 March 2011] [06:06:08] <pieterh>	anything over inproc can't either
| [Monday 21 March 2011] [06:06:14] <Guthur>	ah it was the inproc
| [Monday 21 March 2011] [06:06:19] <pieterh>	yep
| [Monday 21 March 2011] [06:06:35] <pieterh>	with inproc the pattern is 'bind, start child thread, which connects'
| [Monday 21 March 2011] [06:06:47] <Guthur>	I suppose inproc ain't so bad, relatively easy to control the order
| [Monday 21 March 2011] [06:07:03] <pieterh>	since it's structurally different from other transports, I use it only when I'm doing literal multithreading
| [Monday 21 March 2011] [06:07:17] <pieterh>	as compared to multitasking with threads... which I use tcp or ipc for
| [Monday 21 March 2011] [06:07:44] <pieterh>	btw I fixed the guide examples to fit 73 columns, thanks for that hint
| [Monday 21 March 2011] [06:07:58] <Guthur>	you're welcome
| [Monday 21 March 2011] [06:08:30] <Guthur>	it wasn't too bad, but you had set the bar high so these wee things are noticeable, hehe
| [Monday 21 March 2011] [06:09:22] <Guthur>	Ian Barber's PHP conf video is really good
| [Monday 21 March 2011] [06:10:02] <pieterh>	the bar is never too high :-)
| [Monday 21 March 2011] [06:10:23] <pieterh>	Ian Barber is a phenomenon, it was great to meet him in London last week
| [Monday 21 March 2011] [06:11:01] <pieterh>	but then, this community seems to attract bru
| [Monday 21 March 2011] [06:11:06] <pieterh>	*brilliant people
| [Monday 21 March 2011] [06:11:29] <Guthur>	The mention of stable/unstable components was very enlighting
| [Monday 21 March 2011] [06:11:54] <Guthur>	static/dynamic is the other way of describing it
| [Monday 21 March 2011] [06:13:19] <Guthur>	His highlevel description of a imaging process system was a inspirational as well, fanning out and in where appropriate
| [Monday 21 March 2011] [06:13:39] <Guthur>	I'm looking a similar architecture for a 0MQ FIX engine
| [Monday 21 March 2011] [06:13:42] <Guthur>	a/at
| [Monday 21 March 2011] [06:14:19] <pieterh>	yup, understanding the stable/unstable aspects of an architecture is key to making it right
| [Monday 21 March 2011] [06:21:56] <Guthur>	I find myself now looking at my arch and asking the question is this a stable/unstable component
| [Monday 21 March 2011] [06:59:44] <sustrik>	pieterh: pong
| [Monday 21 March 2011] [07:00:22] <pieterh>	sustrik: I was just wondering if it was OK to mention the plans for 3.0 to zeromq-dev
| [Monday 21 March 2011] [07:00:36] <sustrik>	yes
| [Monday 21 March 2011] [07:00:40] <sustrik>	i'm going to do that now
| [Monday 21 March 2011] [07:00:50] 	 * sustrik was waiting for stable 2
| [Monday 21 March 2011] [07:00:57] <pieterh>	goodo
| [Monday 21 March 2011] [07:01:19] <pieterh>	I think it's important to say that we will maintain 2.1 for a long time
| [Monday 21 March 2011] [07:01:44] <pieterh>	change is fun but also scary to anyone wanting to use 0MQ in production
| [Monday 21 March 2011] [07:02:02] <sustrik>	yep, several years presumably
| [Monday 21 March 2011] [07:02:17] <pieterh>	well, I was thinking of 6-12 months, more like :-)
| [Monday 21 March 2011] [07:02:34] <sustrik>	although the impact of new API won't be that bad as it will affect only C apps
| [Monday 21 March 2011] [07:02:39] <pieterh>	I assume we will have a 3.0 stable fairly rapidly
| [Monday 21 March 2011] [07:02:45] <pieterh>	indeed
| [Monday 21 March 2011] [07:03:09] <Guthur>	sustrik:why will the API change only effect C apps?
| [Monday 21 March 2011] [07:03:09] <pieterh>	if we do the API changes separately from semantic changes like xpub/xsub, it's less painful
| [Monday 21 March 2011] [07:03:20] <pieterh>	Guthur: also affect all bindings, of course
| [Monday 21 March 2011] [07:03:30] <sustrik>	Guthur: have a look at 3.0 roadmap
| [Monday 21 March 2011] [07:03:42] <sustrik>	you'll see that most changes don't affect the bindings API
| [Monday 21 March 2011] [07:03:56] <sustrik>	although it obviously affect binding implemetations
| [Monday 21 March 2011] [07:04:05] <Guthur>	oh the roadmap page has been updated
| [Monday 21 March 2011] [07:04:14] <Guthur>	I had not noticed that
| [Monday 21 March 2011] [07:04:25] <sustrik>	yes, i've listed all the backward imcompatible changes there
| [Monday 21 March 2011] [07:04:26] <pieterh>	sustrik: I'm going to already switch to the new ROUTER/DEALER terminology in the guide
| [Monday 21 March 2011] [07:04:28] <sustrik>	feel free to comment
| [Monday 21 March 2011] [07:04:37] <pieterh>	this pushes that change up
| [Monday 21 March 2011] [07:04:56] <sustrik>	ok
| [Monday 21 March 2011] [07:05:02] <sustrik>	pieterh: yes, 2 steps
| [Monday 21 March 2011] [07:05:20] <sustrik>	1, change the API --> do as quickly as possible
| [Monday 21 March 2011] [07:05:22] <pieterh>	sustrik: I'd like to get a stable 3.0 with new API and no real functionality changes, so we can kill 2.0
| [Monday 21 March 2011] [07:05:23] <pieterh>	yes
| [Monday 21 March 2011] [07:05:26] <sustrik>	2. add new functionality
| [Monday 21 March 2011] [07:05:33] <pieterh>	yes, +1
| [Monday 21 March 2011] [07:06:53] <pieterh>	I think the new release process is working nicely, it's certainly easy
| [Monday 21 March 2011] [07:07:30] <sustrik>	well, nobody have really tested the recent changes
| [Monday 21 March 2011] [07:07:38] <sustrik>	let's hope it works as expected
| [Monday 21 March 2011] [07:08:06] <Guthur>	what needs to be done to zmq_send/recv to make them coherent with POSIX?
| [Monday 21 March 2011] [07:08:25] <sustrik>	zmq_send (void *data, size_t size, int flags);
| [Monday 21 March 2011] [07:08:32] <sustrik>	same for zmq_recv
| [Monday 21 March 2011] [07:08:44] <sustrik>	no zmq_msg_t
| [Monday 21 March 2011] [07:08:46] <pieterh>	sustrik: I've been testing pretty heavily, via Guide examples
| [Monday 21 March 2011] [07:08:53] <sustrik>	ah, ok then
| [Monday 21 March 2011] [07:09:02] <Guthur>	and then they would wrap it as a zmq_msg internally?
| [Monday 21 March 2011] [07:09:07] <sustrik>	yes
| [Monday 21 March 2011] [07:09:22] <Guthur>	umm, that's pretty nice
| [Monday 21 March 2011] [07:09:24] <sustrik>	the original signature will still be available as zmq_sendmsg and zmq_recvmsg
| [Monday 21 March 2011] [07:09:24] <pieterh>	sustrik: one thing I noticed is missing is zero-copy on recv
| [Monday 21 March 2011] [07:09:34] <sustrik>	yes?
| [Monday 21 March 2011] [07:09:44] <Guthur>	that could actually simplify bindings
| [Monday 21 March 2011] [07:09:46] <pieterh>	I assume this is what we can do with 3.0
| [Monday 21 March 2011] [07:10:08] <pieterh>	size = zmq_recv (socket, void **data)
| [Monday 21 March 2011] [07:10:27] <Guthur>	*authoring bindings
| [Monday 21 March 2011] [07:10:27] <pieterh>	where I get a malloc'd blob I can then pass around
| [Monday 21 March 2011] [07:10:48] <sustrik>	can't be done
| [Monday 21 March 2011] [07:11:03] <sustrik>	because you don't know what allocation mechanism was used to allocate the buffer
| [Monday 21 March 2011] [07:11:14] <sustrik>	thus, you don't know whether to free it or what
| [Monday 21 March 2011] [07:11:21] <pieterh>	ah, I mean recv() would always allocate on the heap
| [Monday 21 March 2011] [07:11:31] <sustrik>	copying the data?
| [Monday 21 March 2011] [07:11:50] <pieterh>	no copying, allocate a block, read into that block, and provide the caller with the block address
| [Monday 21 March 2011] [07:11:58] <pieterh>	the caller then uses the block with no copying
| [Monday 21 March 2011] [07:12:05] <pieterh>	today, you have to always copy the data received
| [Monday 21 March 2011] [07:12:06] <sustrik>	the socket is not in control of the allocation process
| [Monday 21 March 2011] [07:12:18] <sustrik>	it can be say another socket allocating buffer
| [Monday 21 March 2011] [07:12:25] <sustrik>	and sending it via inproc
| [Monday 21 March 2011] [07:12:34] <pieterh>	inproc is special...
| [Monday 21 March 2011] [07:12:41] <sustrik>	it is
| [Monday 21 March 2011] [07:12:49] <pieterh>	forgetting inproc for a second...
| [Monday 21 March 2011] [07:13:07] <sustrik>	you still have the VSM problem
| [Monday 21 March 2011] [07:13:16] <sustrik>	very small messages are allocated on the stack
| [Monday 21 March 2011] [07:13:24] <sustrik>	to speed the processing
| [Monday 21 March 2011] [07:13:25] <pieterh>	in C?
| [Monday 21 March 2011] [07:13:32] <sustrik>	inside libzmq
| [Monday 21 March 2011] [07:13:42] <pieterh>	how do you return a zmq_msg_t referring to a VSM on the stack?
| [Monday 21 March 2011] [07:13:53] <sustrik>	it's embedded
| [Monday 21 March 2011] [07:14:04] <sustrik>	see the definition in zmq.h
| [Monday 21 March 2011] [07:14:28] <pieterh>	ok, sure
| [Monday 21 March 2011] [07:14:30] <sustrik>	in short, there are different alloc/dealloc mechanisms
| [Monday 21 March 2011] [07:14:43] <sustrik>	zmq_msg_t cleanly wraps the buffer and the deallocation function
| [Monday 21 March 2011] [07:14:44] <pieterh>	ok, at the risk of being glib, forget VSMs for a second too, they're special
| [Monday 21 March 2011] [07:14:51] <sustrik>	ok
| [Monday 21 March 2011] [07:15:00] <pieterh>	the bulk case is large messages, where copying is a cost
| [Monday 21 March 2011] [07:15:01] <Guthur>	so inproc is special and VSM is special
| [Monday 21 March 2011] [07:15:09] <pieterh>	yes, this is accurate, they're both optimizations
| [Monday 21 March 2011] [07:15:20] <pieterh>	which means they can depend on a more complex API, that's fine
| [Monday 21 March 2011] [07:16:16] <pieterh>	sustrik: the semantic which I used in the zmsg class, and which works really neatly
| [Monday 21 March 2011] [07:16:21] <sustrik>	if you don't care about allocation and copying cost in inproc and small message scenarios
| [Monday 21 March 2011] [07:16:24] <Guthur>	at the moment though this specialness is too apparent the user, the inproc issue earlier withstanding
| [Monday 21 March 2011] [07:16:33] <pieterh>	is that recv() returns a freshly allocated block, and send() always frees a block when it's done
| [Monday 21 March 2011] [07:16:38] <Guthur>	iis/isn't
| [Monday 21 March 2011] [07:16:55] <sustrik>	you can wrap zmq_sendmsg to do the transformation of zmq_msg_t into alloc'd buffer
| [Monday 21 March 2011] [07:17:36] <pieterh>	sustrik: I do care, but we can (will) make multiple levels of API
| [Monday 21 March 2011] [07:17:55] <sustrik>	and what's the point of the proposal?
| [Monday 21 March 2011] [07:18:00] 	 * sustrik doesn't get it
| [Monday 21 March 2011] [07:18:06] <pieterh>	hmm, well,.. :-)
| [Monday 21 March 2011] [07:18:12] <pieterh>	zero-copy on read
| [Monday 21 March 2011] [07:18:19] <pieterh>	in the simplest possible fashion
| [Monday 21 March 2011] [07:18:37] <pieterh>	ok, forget it, POSIX socket API doesn't offer this
| [Monday 21 March 2011] [07:18:43] <sustrik>	while at the same time sacrificing zero copy in some scenarios
| [Monday 21 March 2011] [07:18:50] <sustrik>	zero-copy is a beast
| [Monday 21 March 2011] [07:18:54] <pieterh>	as long as you can recv() directly into a user-allocated buffer, you get zero copy
| [Monday 21 March 2011] [07:18:55] <sustrik>	no support in POSIX
| [Monday 21 March 2011] [07:19:23] <pieterh>	I just want to be able to store message contents without copying them
| [Monday 21 March 2011] [07:19:28] <sustrik>	yes, but that makes the messaging lock-step
| [Monday 21 March 2011] [07:19:37] <pieterh>	indeed
| [Monday 21 March 2011] [07:19:44] <pieterh>	only the recv knows how much memory to allocate
| [Monday 21 March 2011] [07:19:54] <sustrik>	exactly
| [Monday 21 March 2011] [07:20:05] <sustrik>	so think of zmq_msg_t as a buffer
| [Monday 21 March 2011] [07:20:06] <pieterh>	or else, as has been discussed, a user-pluggable allocator
| [Monday 21 March 2011] [07:20:10] <pieterh>	which is horrid IMO
| [Monday 21 March 2011] [07:20:38] <sustrik>	yuck
| [Monday 21 March 2011] [07:20:53] <sustrik>	you can use tcmalloc and similar though
| [Monday 21 March 2011] [07:21:00] <sustrik>	as they expose alloc/free API
| [Monday 21 March 2011] [07:21:07] <pieterh>	they look like malloc/free
| [Monday 21 March 2011] [07:21:16] <sustrik>	you just link the library
| [Monday 21 March 2011] [07:21:19] <pieterh>	yup
| [Monday 21 March 2011] [07:21:22] <sustrik>	and all allocations are redirected
| [Monday 21 March 2011] [07:21:33] <pieterh>	anyhow, think about it, if there's a way to return a fresh buffer on recv
| [Monday 21 March 2011] [07:21:39] <pieterh>	it would be elegant IMO
| [Monday 21 March 2011] [07:21:45] <sustrik>	well, zmq_msg_t is a buffer
| [Monday 21 March 2011] [07:21:51] <sustrik>	it looks something like this:
| [Monday 21 March 2011] [07:21:52] <pieterh>	yeah, but it's not a buffer
| [Monday 21 March 2011] [07:22:00] <sustrik>	struct zmq_msg_t
| [Monday 21 March 2011] [07:22:01] <sustrik>	{
| [Monday 21 March 2011] [07:22:03] <sustrik>	   void *data
| [Monday 21 March 2011] [07:22:05] <pieterh>	it's a structure that contains a buffer
| [Monday 21 March 2011] [07:22:06] <sustrik>	   size_t size;
| [Monday 21 March 2011] [07:22:15] <sustrik>	   free_fn_t free_fn;
| [Monday 21 March 2011] [07:22:16] <sustrik>	}
| [Monday 21 March 2011] [07:22:16] <sustrik>	;
| [Monday 21 March 2011] [07:22:18] <pieterh>	well... 
| [Monday 21 March 2011] [07:22:24] <pieterh>	ok, point taken, it does work
| [Monday 21 March 2011] [07:22:28] <pieterh>	it's a blob descriptor
| [Monday 21 March 2011] [07:22:33] <sustrik>	yes
| [Monday 21 March 2011] [07:23:05] <pieterh>	(a) it should be called 'blob_t' and (b) recv() should return a freshly created blob
| [Monday 21 March 2011] [07:23:18] <pieterh>	blob_t *blob = zmq_recv (socket)
| [Monday 21 March 2011] [07:23:28] <sustrik>	recv has to return int
| [Monday 21 March 2011] [07:23:34] <sustrik>	to be POSIX compliant
| [Monday 21 March 2011] [07:23:40] <sustrik>	int + errno
| [Monday 21 March 2011] [07:23:45] <pieterh>	int rc = zmq_recv (socket, &blob)
| [Monday 21 March 2011] [07:23:49] <sustrik>	yes
| [Monday 21 March 2011] [07:23:59] <sustrik>	that's how it works now
| [Monday 21 March 2011] [07:23:59] <pieterh>	point being, recv creates the buffer
| [Monday 21 March 2011] [07:24:02] <sustrik>	except for the name
| [Monday 21 March 2011] [07:24:09] <pieterh>	no, now you need this extra init
| [Monday 21 March 2011] [07:24:17] <sustrik>	ah
| [Monday 21 March 2011] [07:24:17] <pieterh>	rather annoying
| [Monday 21 March 2011] [07:24:28] <sustrik>	that's to avoid additional malloc
| [Monday 21 March 2011] [07:24:38] <pieterh>	optimization
| [Monday 21 March 2011] [07:24:39] <sustrik>	so you create blob_t on the stack
| [Monday 21 March 2011] [07:24:51] <sustrik>	which is really fast
| [Monday 21 March 2011] [07:24:55] <pieterh>	I know you want that but it shouldn't be in the simple API
| [Monday 21 March 2011] [07:24:58] <sustrik>	instead of putting it on the heap
| [Monday 21 March 2011] [07:25:21] <pieterh>	simple API should be just fast enough, and as simple as it can be, and POSIX like
| [Monday 21 March 2011] [07:25:23] <pieterh>	IMO
| [Monday 21 March 2011] [07:25:24] <sustrik>	in 3.0 the simple API will be POSIX like
| [Monday 21 March 2011] [07:25:35] <sustrik>	zmq_send (void*, size_t)
| [Monday 21 March 2011] [07:25:45] <sustrik>	zero-copy is never neat
| [Monday 21 March 2011] [07:25:53] <sustrik>	it's optimisation in itself
| [Monday 21 March 2011] [07:26:00] <pieterh>	what's the zmq_recv syntax for 3.0...?
| [Monday 21 March 2011] [07:26:03] <sustrik>	and one that crosses all levels of stack
| [Monday 21 March 2011] [07:26:08] <sustrik>	and makes mess of layering
| [Monday 21 March 2011] [07:26:27] <pieterh>	int size = zmq_recv (socket, void *)...?
| [Monday 21 March 2011] [07:26:28] <sustrik>	zmq_recv (void *buf, size_t *size, int flags);
| [Monday 21 March 2011] [07:26:39] <sustrik>	forgor socket
| [Monday 21 March 2011] [07:26:41] <sustrik>	forgot
| [Monday 21 March 2011] [07:26:52] <sustrik>	same as POSIX recv()
| [Monday 21 March 2011] [07:27:32] <pieterh>	ok, should be 'ssize_t zmq_recv(void *socket, void *buf, size_t len, int flags);
| [Monday 21 March 2011] [07:27:41] <sustrik>	size_t *len
| [Monday 21 March 2011] [07:27:45] <pieterh>	nope
| [Monday 21 March 2011] [07:27:51] <pieterh>	size_t len, maximum size of buffer
| [Monday 21 March 2011] [07:27:58] <sustrik>	ah
| [Monday 21 March 2011] [07:27:59] <pieterh>	return code is actual size read
| [Monday 21 March 2011] [07:28:00] <sustrik>	you are right
| [Monday 21 March 2011] [07:28:11] <pieterh>	it's hugely annoying because you have to allocate randomly huge buffers
| [Monday 21 March 2011] [07:28:25] <pieterh>	and there's no way to recover if the buffer was too small
| [Monday 21 March 2011] [07:28:37] <pieterh>	conclusion: you *cannot* use the POSIX socket API 100% for recv
| [Monday 21 March 2011] [07:28:38] <sustrik>	EMSGSIZE
| [Monday 21 March 2011] [07:28:43] <pieterh>	no way to recover
| [Monday 21 March 2011] [07:28:48] <sustrik>	then you can increase the buffer
| [Monday 21 March 2011] [07:28:50] <sustrik>	and recv() anew
| [Monday 21 March 2011] [07:28:53] <pieterh>	'please go back and re-read'?
| [Monday 21 March 2011] [07:28:53] <sustrik>	however
| [Monday 21 March 2011] [07:28:57] <pieterh>	ugh
| [Monday 21 March 2011] [07:29:05] <pieterh>	ugh and ugh
| [Monday 21 March 2011] [07:29:15] <sustrik>	in most scenarios you want to put the limit on message size anyway
| [Monday 21 March 2011] [07:29:17] <pieterh>	it means putting message lengths into separate frames
| [Monday 21 March 2011] [07:29:27] <sustrik>	setsockopt (MAXMSGSIZE, 1000);
| [Monday 21 March 2011] [07:29:35] <pieterh>	that's orthogonal to this
| [Monday 21 March 2011] [07:29:39] <sustrik>	char buff [1000];
| [Monday 21 March 2011] [07:29:46] <sustrik>	zmq_recv (buff, 1000);
| [Monday 21 March 2011] [07:29:50] <pieterh>	ugh and ugh again
| [Monday 21 March 2011] [07:30:03] <pieterh>	I have frames of 8 bytes and frames of 2MB
| [Monday 21 March 2011] [07:30:42] <pieterh>	seriously unsatisfactory to not be able to properly allocate the right buffer size for each frame
| [Monday 21 March 2011] [07:30:50] <sustrik>	then you need to use more complex API
| [Monday 21 March 2011] [07:31:16] <pieterh>	this makes the simple API almost useless IMO
| [Monday 21 March 2011] [07:31:21] <pieterh>	nice for send, useless for recv
| [Monday 21 March 2011] [07:32:25] <sustrik>	what's the alternative then?
| [Monday 21 March 2011] [07:32:40] <sustrik>	tha'ts how UDP works, irrc
| [Monday 21 March 2011] [07:32:42] <pieterh>	I don't know, but reading into a pre-allocated buffer is inacceptable IMO
| [Monday 21 March 2011] [07:32:47] <pieterh>	UDP has maximum frame sizes
| [Monday 21 March 2011] [07:32:51] <pieterh>	TCP is a stream
| [Monday 21 March 2011] [07:32:54] <sustrik>	ZMQ_MAXMSGSIZE
| [Monday 21 March 2011] [07:33:04] <sustrik>	same as MTU
| [Monday 21 March 2011] [07:33:07] <pieterh>	0MQ is message-oriented, that means different read/write semantics
| [Monday 21 March 2011] [07:33:09] <sustrik>	but on messaging level
| [Monday 21 March 2011] [07:33:15] <pieterh>	it's not the same thing
| [Monday 21 March 2011] [07:33:24] <pieterh>	you have a 64-bit message size
| [Monday 21 March 2011] [07:33:48] <sustrik>	well, i think there are 2 distinct use cases here
| [Monday 21 March 2011] [07:33:54] <sustrik>	1. something like market data
| [Monday 21 March 2011] [07:34:02] <pieterh>	I think it's necessary to define semantics that fit messaging
| [Monday 21 March 2011] [07:34:03] <sustrik>	you want to limit max size of message
| [Monday 21 March 2011] [07:34:10] <pieterh>	not try to make 0MQ look like TCP, it's not
| [Monday 21 March 2011] [07:34:22] <sustrik>	to prevent someone killing the transmission by pushing 4GB blob
| [Monday 21 March 2011] [07:34:30] <pieterh>	this is orthogonal
| [Monday 21 March 2011] [07:34:33] <pieterh>	it's not the issue
| [Monday 21 March 2011] [07:34:37] <sustrik>	in such case zmq_recv() is sufficient
| [Monday 21 March 2011] [07:34:46] <pieterh>	I can't agree...
| [Monday 21 March 2011] [07:34:46] <sustrik>	2. something like FTP
| [Monday 21 March 2011] [07:34:52] <pieterh>	let's say I want to hold a queue of messages
| [Monday 21 March 2011] [07:34:59] <sustrik>	in that case you don't know the size in advance
| [Monday 21 March 2011] [07:35:00] <pieterh>	might be 1M messages, held for 1 second
| [Monday 21 March 2011] [07:35:09] <pieterh>	I have to allocate the maximum frame size for each one
| [Monday 21 March 2011] [07:35:15] <pieterh>	this is seriously problematic
| [Monday 21 March 2011] [07:35:33] <pieterh>	my alternative is to read everything into a frame buffer and memcpy
| [Monday 21 March 2011] [07:35:35] <pieterh>	that is seriously stupid
| [Monday 21 March 2011] [07:35:40] <pieterh>	what I want is a recv() that allocates and returns a block
| [Monday 21 March 2011] [07:35:43] <pieterh>	that is seriously simple
| [Monday 21 March 2011] [07:35:55] <sustrik>	that's zmq_recvmsg
| [Monday 21 March 2011] [07:36:02] <pieterh>	then I will never use recv() because it's *more* complex
| [Monday 21 March 2011] [07:36:05] <pieterh>	which is pointless
| [Monday 21 March 2011] [07:36:09] <sustrik>	ok
| [Monday 21 March 2011] [07:36:16] <pieterh>	trying to make 0MQ look like TCP is a big mistake IMO
| [Monday 21 March 2011] [07:36:20] <Guthur>	frankly from what I'm reading POSIX recv is just pants
| [Monday 21 March 2011] [07:36:31] <pieterh>	it is simply not a file-oriented metaphor, period
| [Monday 21 March 2011] [07:36:38] <Guthur>	and modelling it after that is the problem
| [Monday 21 March 2011] [07:36:40] <pieterh>	yes
| [Monday 21 March 2011] [07:36:52] <pieterh>	and it won't make 0MQ more compatible with the kernel
| [Monday 21 March 2011] [07:37:04] <sustrik>	so you want zmq_recvmsg and no zmq_recv, right?
| [Monday 21 March 2011] [07:37:07] <pieterh>	the way to get 0MQ into the kernel is to make it utterly compelling
| [Monday 21 March 2011] [07:37:12] <pieterh>	so every developer on the planet uses it
| [Monday 21 March 2011] [07:37:21] <pieterh>	and you get that by making it utterly simple for simple cases
| [Monday 21 March 2011] [07:37:56] <pieterh>	sustrik: what I want, speaking as a 0MQ user, is a recv method (any name) which returns a fresh buffer or blob structure
| [Monday 21 March 2011] [07:38:05] <sustrik>	zmq_recvmsg
| [Monday 21 March 2011] [07:38:07] <sustrik>	that's it
| [Monday 21 March 2011] [07:38:09] <pieterh>	and a send method that takes the same buffer or blob structure
| [Monday 21 March 2011] [07:38:18] <sustrik>	zmq_sendmsg
| [Monday 21 March 2011] [07:38:20] <pieterh>	sure
| [Monday 21 March 2011] [07:38:26] <pieterh>	then recv and send are useless
| [Monday 21 March 2011] [07:38:27] <sustrik>	it's going to be there
| [Monday 21 March 2011] [07:38:30] <pieterh>	and won't get showtime
| [Monday 21 March 2011] [07:38:43] <sustrik>	zmq_send (s, "ABC", 3);
| [Monday 21 March 2011] [07:38:48] <sustrik>	what's wrong about that?
| [Monday 21 March 2011] [07:38:55] <pieterh>	using one API metaphor for sending, another for receiving?
| [Monday 21 March 2011] [07:39:14] <sustrik>	char buff [3];
| [Monday 21 March 2011] [07:39:23] <sustrik>	zmq_recv (s, buf, 3)
| [Monday 21 March 2011] [07:39:35] <pieterh>	yes, and if the sender gives you 4 bytes, your socket is dead
| [Monday 21 March 2011] [07:39:38] <sustrik>	the sendmsg and recvmsg will be of course availabler
| [Monday 21 March 2011] [07:39:40] <pieterh>	it's not defensible
| [Monday 21 March 2011] [07:39:46] <sustrik>	it's not dead
| [Monday 21 March 2011] [07:39:49] <sustrik>	it reports error
| [Monday 21 March 2011] [07:39:54] <pieterh>	and the next read... 
| [Monday 21 March 2011] [07:39:58] <pieterh>	next frame or same frame?
| [Monday 21 March 2011] [07:40:07] <sustrik>	i would copy UDP semantics
| [Monday 21 March 2011] [07:40:12] <pieterh>	or a special flag to re-read the same frame?
| [Monday 21 March 2011] [07:40:13] <sustrik>	but it's open to discussion
| [Monday 21 March 2011] [07:40:19] <pieterh>	it gets horrid
| [Monday 21 March 2011] [07:40:25] <pieterh>	and it's not worth it just to get that simple send
| [Monday 21 March 2011] [07:40:39] <pieterh>	I can make a 'send string' method in 10 lines of C, and have done this
| [Monday 21 March 2011] [07:40:49] <pieterh>	it's not worth upgrading to 3.0 to save 10 lines of C
| [Monday 21 March 2011] [07:40:51] <sustrik>	so you want to keep the existing API right?
| [Monday 21 March 2011] [07:40:53] <pieterh>	send is really not the issue
| [Monday 21 March 2011] [07:41:05] <pieterh>	nope, the existing API is also too complex
| [Monday 21 March 2011] [07:41:08] <pieterh>	sorry :-)
| [Monday 21 March 2011] [07:41:25] <sustrik>	ok, send your proposal to the mailing list
| [Monday 21 March 2011] [07:41:33] <sustrik>	no point in discussing it here
| [Monday 21 March 2011] [07:41:36] <pieterh>	well, I have thousands of lines of sample code in the Guide
| [Monday 21 March 2011] [07:41:42] <pieterh>	that show what I like as APIs, in C
| [Monday 21 March 2011] [07:41:54] <pieterh>	string = s_recv (socket); free (string);
| [Monday 21 March 2011] [07:41:54] <sustrik>	using blobs, yes
| [Monday 21 March 2011] [07:42:00] <pieterh>	s_send (socket, "Hello");
| [Monday 21 March 2011] [07:42:08] <pieterh>	that's for strings, it's simple and clean
| [Monday 21 March 2011] [07:42:11] <sustrik>	that's a special case of current 0mq api
| [Monday 21 March 2011] [07:42:54] <sustrik>	you can propose changing zmq_msg_t into blob_t
| [Monday 21 March 2011] [07:42:54] <pieterh>	anyhow, my advice is to not try to imitate neither TCP nor UDP but develop clear and optimal 0MQ semantics in the API
| [Monday 21 March 2011] [07:43:03] <pieterh>	you will get more adoption of your API
| [Monday 21 March 2011] [07:43:10] <pieterh>	and that's the way to get 0MQ into the kernel
| [Monday 21 March 2011] [07:43:18] <sustrik>	sure, go on, propose an alternative
| [Monday 21 March 2011] [07:43:23] <pieterh>	slavish imitation of old, semi-accurate APIs won't work
| [Monday 21 March 2011] [07:43:28] <pieterh>	ok, I'll propose an alternative
| [Monday 21 March 2011] [07:43:33] <sustrik>	ok
| [Monday 21 March 2011] [07:44:04] <sustrik>	as for kernel it's a very different problem so let's forget about it atm
| [Monday 21 March 2011] [07:44:23] <pieterh>	well, I think the point is that simple / clean gets you market share
| [Monday 21 March 2011] [07:44:31] <sustrik>	sure
| [Monday 21 March 2011] [07:44:50] <sustrik>	kernel is different though -- if you propose change to ABI, you'll never get in
| [Monday 21 March 2011] [07:44:59] <pieterh>	the kernel is just peopl;e
| [Monday 21 March 2011] [07:45:02] <pieterh>	*people
| [Monday 21 March 2011] [07:45:22] <sustrik>	the problem with new ABIs is they have to be maintained indefinitely
| [Monday 21 March 2011] [07:45:24] <Guthur>	tis a shame C doesn't support method overloading
| [Monday 21 March 2011] [07:45:42] <Guthur>	method/function
| [Monday 21 March 2011] [07:45:54] <pieterh>	Guthur: well, it's nice that you know what a function is, forever
| [Monday 21 March 2011] [07:46:08] <pieterh>	sustrik: do you mind if I delete the irrelevant comments on the 3.0 page?
| [Monday 21 March 2011] [07:46:21] <sustrik>	which are those?
| [Monday 21 March 2011] [07:46:27] <pieterh>	all of them, I guess
| [Monday 21 March 2011] [07:46:27] <sustrik>	ah, the comments
| [Monday 21 March 2011] [07:46:30] <sustrik>	yes
| [Monday 21 March 2011] [07:46:31] <sustrik>	sure
| [Monday 21 March 2011] [07:46:39] <sustrik>	i haven't known it's even possible
| [Monday 21 March 2011] [07:46:40] <Guthur>	overloading doesn't remove that but you can have Send(blob*, size)  Send(zmq_msg) etc
| [Monday 21 March 2011] [07:47:11] <Guthur>	anyway not really benefiting the discussing
| [Monday 21 March 2011] [07:47:11] <sustrik>	Guthur: that helps with API, but doesn't help with ABI
| [Monday 21 March 2011] [07:47:27] <sustrik>	from ABI point of view it's still 2 functions
| [Monday 21 March 2011] [07:48:57] <Guthur>	but this was a discussion about API,
| [Monday 21 March 2011] [07:49:03] <Guthur>	i thought
| [Monday 21 March 2011] [07:49:23] <sustrik>	mostly, there are some ABI users though
| [Monday 21 March 2011] [07:49:29] <sustrik>	namely, clrzmq :)
| [Monday 21 March 2011] [07:49:34] <sustrik>	right?
| [Monday 21 March 2011] [07:49:58] <mile>	yrashk, 
| [Monday 21 March 2011] [07:50:07] <Guthur>	well... yeah 
| [Monday 21 March 2011] [07:57:51] <yrashk>	mile: ?
| [Monday 21 March 2011] [07:58:56] <mile>	yrashk, hi, I was just into connecting yaws to erlzmq2, and I'd need some advice
| [Monday 21 March 2011] [07:59:14] <yrashk>	mile: sure
| [Monday 21 March 2011] [07:59:44] <mile>	docs says it creates an OS thread per context
| [Monday 21 March 2011] [08:00:16] <yrashk>	that's right
| [Monday 21 March 2011] [08:00:21] <mile>	that means, if I want to serve a large number of connections (parallel), I should make some kind of a router talking to zmq
| [Monday 21 March 2011] [08:00:36] <mile>	which then talks to many erlang processes
| [Monday 21 March 2011] [08:00:59] <yrashk>	do you plan to open a large open of contexts?
| [Monday 21 March 2011] [08:01:16] <pieterh>	sustrik: ok, I've thrown together a very rough API proposal
| [Monday 21 March 2011] [08:01:17] <mile>	yes, a web server in the front
| [Monday 21 March 2011] [08:01:24] <sustrik>	ok
| [Monday 21 March 2011] [08:01:24] <mile>	so, the more, the better :)
| [Monday 21 March 2011] [08:01:44] <pieterh>	sustrik: mostly, there is a really nice class-oriented API style we've developed for ZFL
| [Monday 21 March 2011] [08:01:49] <Guthur>	pieterh: you sending to the mailing list, or is it on the wiki
| [Monday 21 March 2011] [08:01:55] <yrashk>	is there any good reason to open a large # of contexts?
| [Monday 21 March 2011] [08:02:02] <mile>	a good example is comet/ajax clients
| [Monday 21 March 2011] [08:02:04] <sustrik>	pieterh: can you send that to the ML
| [Monday 21 March 2011] [08:02:05] <pieterh>	Guthur: my pattern is to document on the wiki first, then tell the list or IRC about it
| [Monday 21 March 2011] [08:02:14] <pieterh>	sending specs / proposals to the ML is an anti-pattern
| [Monday 21 March 2011] [08:02:27] <Guthur>	no probs, just eager to have a look
| [Monday 21 March 2011] [08:02:33] <mile>	yrashk, no good reason, one would do good, it it takes care of multiplexing
| [Monday 21 March 2011] [08:02:36] <sustrik>	nobody is going to notice it
| [Monday 21 March 2011] [08:02:47] <yrashk>	mile: our recv does multiplex
| [Monday 21 March 2011] [08:03:31] <mile>	yrashk, so a single recv which then talks to a large number of erlang processes should work fine?
| [Monday 21 March 2011] [08:03:45] <pieterh>	sustrik: what are the actual goals with the 3.0 API?
| [Monday 21 March 2011] [08:04:12] <sustrik>	move towards POSIX
| [Monday 21 March 2011] [08:04:36] <pieterh>	simpler API?
| [Monday 21 March 2011] [08:04:41] <pieterh>	less lines of code in apps?
| [Monday 21 March 2011] [08:04:46] <sustrik>	nope, POSIX-like api
| [Monday 21 March 2011] [08:04:50] <pieterh>	that's all?
| [Monday 21 March 2011] [08:04:55] <sustrik>	for me, yes
| [Monday 21 March 2011] [08:04:56] <yrashk>	mile: well, you can spawn multiple recvs on the erlang side for different sockets (even in a single context, but you can do multiple contextrs too) and every context will multiplex (it uses zmq_poll)
| [Monday 21 March 2011] [08:05:10] <pieterh>	ok, I'll add my goals too, they're not in conflict afaics
| [Monday 21 March 2011] [08:05:16] <tjgillies>	anyone have a pub/sub example for node? i can't find one anywhere
| [Monday 21 March 2011] [08:05:18] <sustrik>	+ removing some obsolete stuff
| [Monday 21 March 2011] [08:05:30] <sustrik>	but please use mailing list
| [Monday 21 March 2011] [08:05:46] <sustrik>	nobody will see the discussion on the webpage
| [Monday 21 March 2011] [08:06:03] <pieterh>	sustrik: like I said, I document on the wiki first, *then* discuss on the list
| [Monday 21 March 2011] [08:06:03] <mile>	yrashk, thanks! :)   do you know of any code snippets around? 
| [Monday 21 March 2011] [08:06:13] <sustrik>	ok
| [Monday 21 March 2011] [08:06:16] <mile>	I couldn't find much on the webpage
| [Monday 21 March 2011] [08:06:25] <yrashk>	mile: perf/ and test/
| [Monday 21 March 2011] [08:06:30] <yrashk>	mile: in the repo
| [Monday 21 March 2011] [08:06:30] <sustrik>	but i makes unclear what's your proposal
| [Monday 21 March 2011] [08:06:31] <mile>	tx :)
| [Monday 21 March 2011] [08:06:37] <sustrik>	at least mark it as such
| [Monday 21 March 2011] [08:06:44] <pieterh>	sustrik: have you read the page?
| [Monday 21 March 2011] [08:06:56] <sustrik>	yep
| [Monday 21 March 2011] [08:07:10] <pieterh>	it's literally a brain dump, not organized yet
| [Monday 21 March 2011] [08:07:12] <yrashk>	mile: yw
| [Monday 21 March 2011] [08:07:22] <sustrik>	whatever
| [Monday 21 March 2011] [08:07:30] <sustrik>	just move the discussion the mailing list
| [Monday 21 March 2011] [08:07:50] <pieterh>	Yes, I'm in the process of doing that
| [Monday 21 March 2011] [08:07:55] <sustrik>	goodo
| [Monday 21 March 2011] [08:08:23] <pieterh>	you'd prefer that my proposal is marked "proposed by Pieter" or somesuch?
| [Monday 21 March 2011] [08:08:35] <pieterh>	we don't generally do this
| [Monday 21 March 2011] [08:08:49] <pieterh>	wiki pages = edit into shape and consensus
| [Monday 21 March 2011] [08:09:32] <sustrik>	doesn't really matter as long as it's discussed on the mailing list
| [Monday 21 March 2011] [08:09:40] <sustrik>	then it's clear who proposed what
| [Monday 21 March 2011] [08:13:12] <pieterh>	ok, done
| [Monday 21 March 2011] [08:13:19] <Guthur>	will pushing string handling down into 0MQ have any adverse effect on people sending binary blobs
| [Monday 21 March 2011] [08:13:29] <pieterh>	Guthur: it's two different use cases
| [Monday 21 March 2011] [08:13:38] <pieterh>	sending strings is one very common case
| [Monday 21 March 2011] [08:13:54] <Guthur>	sure, but binary serialization is quite popular these days
| [Monday 21 March 2011] [08:13:58] <pieterh>	it's only in C that a string and a blob are fundamentally different
| [Monday 21 March 2011] [08:14:03] <Guthur>	protobuffers etc
| [Monday 21 March 2011] [08:14:17] <pieterh>	yeah, but this is not stuff you want to learn as a beginner
| [Monday 21 March 2011] [08:15:13] <Guthur>	if you are a beginner you probably shouldn't be using C
| [Monday 21 March 2011] [08:15:21] <Guthur>	you're feet can only take so much
| [Monday 21 March 2011] [08:15:28] <pieterh>	perhaps it was an error to use C as the language for the Guide
| [Monday 21 March 2011] [08:16:32] <Guthur>	pieterh: you have done a good job there though
| [Monday 21 March 2011] [08:16:53] <pieterh>	with a lot of help from contributors...
| [Monday 21 March 2011] [08:16:59] <Guthur>	I suppose my comment was more programming general as opposed to 0MQ beginners
| [Monday 21 March 2011] [08:17:51] <Guthur>	I'd imagine most of the bindings provide string handling
| [Monday 21 March 2011] [08:18:02] <Guthur>	I know i did with clrzmq
| [Monday 21 March 2011] [08:18:04] <pieterh>	perhaps we should make a standard C binding... :-)
| [Monday 21 March 2011] [08:18:56] <Guthur>	well you did mention multiple levels of the API
| [Monday 21 March 2011] [08:20:01] <pieterh>	hmm
| [Monday 21 March 2011] [08:22:47] <pieterh>	sustrik: if we made a separate C binding, most of my concerns could be solved there
| [Monday 21 March 2011] [08:23:25] <sustrik>	you mean like C binding on top of POSIX api
| [Monday 21 March 2011] [08:23:28] <pieterh>	yes
| [Monday 21 March 2011] [08:23:34] <sustrik>	why not
| [Monday 21 March 2011] [08:23:37] <sustrik>	it's up to you
| [Monday 21 March 2011] [08:23:43] <pieterh>	I have a lovely class-oriented model in ZFL...
| [Monday 21 March 2011] [08:23:48] <sustrik>	ack
| [Monday 21 March 2011] [08:24:13] <pieterh>	this would remove the need for random ad-hoc layers like zmsg and s_recv/s_send
| [Monday 21 March 2011] [08:24:22] <pieterh>	ok, I'll think it through
| [Monday 21 March 2011] [08:24:25] <sustrik>	sure, go for it
| [Monday 21 March 2011] [08:24:41] <pieterh>	there's stuff like serialization that other bindings offer, right?
| [Monday 21 March 2011] [08:24:44] <pieterh>	json, etc.
| [Monday 21 March 2011] [08:24:53] <sustrik>	yes, different stuff
| [Monday 21 March 2011] [08:24:56] <pieterh>	hmm
| [Monday 21 March 2011] [08:25:08] <sustrik>	some bindings don't even follow the underlying APIs
| [Monday 21 March 2011] [08:25:18] <pieterh>	indeed
| [Monday 21 March 2011] [08:25:34] <sustrik>	and adhere more to paradigm of the language in question
| [Monday 21 March 2011] [08:25:39] <sustrik>	like C#
| [Monday 21 March 2011] [08:25:51] <sustrik>	Guthur may be more specific on that
| [Monday 21 March 2011] [08:26:21] <pieterh>	this means the real API can be as complex as you need to make it
| [Monday 21 March 2011] [08:26:40] <pieterh>	hmm, ok, this is a good plan
| [Monday 21 March 2011] [08:26:46] <sustrik>	nice
| [Monday 21 March 2011] [08:40:05] <Guthur>	yeah. I'm guilty of deviating somewhat from the underlying API 
| [Monday 21 March 2011] [08:41:01] <Guthur>	my rational is that to get accepted by a language community such as C# you need to provide adequate abstractions
| [Monday 21 March 2011] [08:41:33] <Guthur>	string handling being a prime example
| [Monday 21 March 2011] [08:42:09] <Guthur>	they get scared if they see too many byte arrays
| [Monday 21 March 2011] [08:43:03] <Guthur>	I'm not joking there either, when I demonstrated something to my boss that is exactly what he picked up on, he was like 'ugh byte arrays'
| [Monday 21 March 2011] [08:43:25] <Guthur>	I should have hid that better for my demo
| [Monday 21 March 2011] [08:45:49] <sustrik>	:)
| [Monday 21 March 2011] [09:15:12] <mile>	yrashk, got the forst results
| [Monday 21 March 2011] [09:15:22] <mile>	erlang talking to c++ 
| [Monday 21 March 2011] [09:15:41] <mile>	but not very impressive, I guess I have done something wrong
| [Monday 21 March 2011] [09:16:03] <mile>	got around 2600 msg/sec
| [Monday 21 March 2011] [09:16:28] <mile>	that is, the double of that
| [Monday 21 March 2011] [09:16:29] <pieterh>	mile: are you doing request-reply?
| [Monday 21 March 2011] [09:16:50] <mile>	yes
| [Monday 21 March 2011] [09:17:00] <pieterh>	that's pretty normal then
| [Monday 21 March 2011] [09:17:27] <pieterh>	round-tripping is slow
| [Monday 21 March 2011] [09:17:35] <mile>	ok, thats good in terms I didn't screw up :)
| [Monday 21 March 2011] [09:17:54] <pieterh>	ah, you may also have screwed up, that's not excluded :-)
| [Monday 21 March 2011] [09:18:07] <mile>	hehe
| [Monday 21 March 2011] [09:18:19] <pieterh>	if you want to measure throughput, try a push/pull or pub/sub test
| [Monday 21 March 2011] [09:18:30] <mile>	so, if I get it right, single request/reply are bounded by the roundtrip
| [Monday 21 March 2011] [09:18:35] <yrashk>	there are pub/sub perf tests in erlzmq2
| [Monday 21 March 2011] [09:18:38] <mile>	but if I had parallel clients
| [Monday 21 March 2011] [09:18:38] <pieterh>	yes
| [Monday 21 March 2011] [09:18:51] <mile>	that would scale 
| [Monday 21 March 2011] [09:19:00] <pieterh>	mile: how far in the Guide have you read?
| [Monday 21 March 2011] [09:19:28] <mile>	pieterh, good point, I started skipping at some point
| [Monday 21 March 2011] [09:19:29] <mile>	:)
| [Monday 21 March 2011] [09:19:45] <mile>	I'll get back to it
| [Monday 21 March 2011] [09:20:06] <pieterh>	it doesn't talk about round-tripping until chapter 4
| [Monday 21 March 2011] [09:20:21] <pieterh>	but at least you need to know how to scale up req/rep
| [Monday 21 March 2011] [09:20:35] <pieterh>	using devices, which we cover in ch2
| [Monday 21 March 2011] [09:21:04] <yrashk>	btw pieterh I am considering actually using 0mq for some notification bus here :) still not sure whether I can make this simple enough, though..
| [Monday 21 March 2011] [09:21:06] <mile>	that I have read, but I definitely need to read it again :)
| [Monday 21 March 2011] [09:21:41] <pieterh>	yrashk: well, let us know if you hit any blocks
| [Monday 21 March 2011] [09:21:55] <yrashk>	I already hit one, it looks too complicated for me :D
| [Monday 21 March 2011] [09:23:06] <pieterh>	you mean the use case?
| [Monday 21 March 2011] [09:23:13] <yrashk>	yeah
| [Monday 21 March 2011] [09:23:28] <yrashk>	I am still to come to any kind of real model yet
| [Monday 21 March 2011] [09:23:44] <pieterh>	it's a new system or you want to reimplement an existing one?
| [Monday 21 March 2011] [09:23:54] <yrashk>	but I need to build a cluster-wide notification system where everyone can push a mesasge to a "topic" and subscribe to any topic
| [Monday 21 March 2011] [09:24:14] <yrashk>	but it's multihost and host-failure tolerant.. (well, it should be)
| [Monday 21 March 2011] [09:24:18] <pieterh>	read the whaleshark whitepaper yet?
| [Monday 21 March 2011] [09:24:27] <yrashk>	briefly
| [Monday 21 March 2011] [09:24:28] <pieterh>	that's more or less the idea
| [Monday 21 March 2011] [09:24:52] <pieterh>	more or less, not exactly
| [Monday 21 March 2011] [09:24:59] <pieterh>	but there may be ideas there to help you
| [Monday 21 March 2011] [09:25:16] <yrashk>	good idea, thanks
| [Monday 21 March 2011] [09:25:32] <pieterh>	depending on the scale you can also make a brokered model
| [Monday 21 March 2011] [09:25:43] <pieterh>	e.g. something like AMQP's topic exchange
| [Monday 21 March 2011] [09:25:55] <yrashk>	I'd rather avoid amqp
| [Monday 21 March 2011] [09:26:04] <pieterh>	no, not AMQP, just some of the semantics
| [Monday 21 March 2011] [09:26:13] <yrashk>	I mean
| [Monday 21 March 2011] [09:26:16] <pieterh>	I can explain briefly if you like, it's very elegant
| [Monday 21 March 2011] [09:26:21] <yrashk>	I'd rather avoid single-broker thing
| [Monday 21 March 2011] [09:26:26] <pieterh>	ah, ok, why?
| [Monday 21 March 2011] [09:26:47] <pieterh>	'notification' doesn't immediately suggest high volumes
| [Monday 21 March 2011] [09:26:48] <yrashk>	I need to be very tolerant to host failures (any host can go down any time)
| [Monday 21 March 2011] [09:26:56] <pieterh>	bleh, this is trivial to address
| [Monday 21 March 2011] [09:27:07] <pieterh>	you make live-live redundancy, period
| [Monday 21 March 2011] [09:27:24] <pieterh>	especially simple for pubsub models
| [Monday 21 March 2011] [09:27:40] <pieterh>	so what's the volume?
| [Monday 21 March 2011] [09:28:12] <yrashk>	and yeah there no high volumes -- I just want this system to work through any # of hosts, don't fail when any host is down and make some messages durable
| [Monday 21 March 2011] [09:28:32] <yrashk>	a kind of intra-cluster signalling framework, so to say
| [Monday 21 March 2011] [09:28:38] <yrashk>	serverless one, if you wish
| [Monday 21 March 2011] [09:28:57] <yrashk>	i.e. each host is equal to any other host in the system
| [Monday 21 March 2011] [09:28:57] <pieterh>	... removing stable points from a network doesn't always make it simpler
| [Monday 21 March 2011] [09:29:03] <pieterh>	atomic multicast?
| [Monday 21 March 2011] [09:29:09] <pieterh>	paxos style?
| [Monday 21 March 2011] [09:29:27] <pieterh>	actually I have an Erlang implementation in my pocket somewhere
| [Monday 21 March 2011] [09:29:43] <pieterh>	but not using 0MQ
| [Monday 21 March 2011] [09:29:54] <yrashk>	I probably don't even care about atomicity. Just getting messages delivered to those who want to listen to them, if the host was down, deliver all durable messages there, too
| [Monday 21 March 2011] [09:30:41] <yrashk>	and yeah, dynamic node additions and removals, obviously
| [Monday 21 March 2011] [09:30:44] <pieterh>	well... IMO you're setting the bar too high 
| [Monday 21 March 2011] [09:30:47] <yrashk>	nothing fancy, in fact
| [Monday 21 March 2011] [09:30:55] <pieterh>	yet, too complex to implement... :-)
| [Monday 21 March 2011] [09:31:03] <pieterh>	make it simpler, implement that, then improve it
| [Monday 21 March 2011] [09:31:03] <yrashk>	yep
| [Monday 21 March 2011] [09:31:19] <pieterh>	my suggestion would be to use a broker, and if you need it, a broker pair
| [Monday 21 March 2011] [09:31:29] <pieterh>	use a simple topic routing engine, I can provide you a design if needed
| [Monday 21 March 2011] [09:31:54] <pieterh>	then, when you have that working, figure out what you really want to make
| [Monday 21 March 2011] [09:32:40] <yrashk>	I guess I also need to read about pgm
| [Monday 21 March 2011] [09:32:44] <pieterh>	you can relatively easily evolve from a broker-based architecture to a distributed one
| [Monday 21 March 2011] [09:32:55] <pieterh>	however, jumping straight to a distributed model is rather hard
| [Monday 21 March 2011] [09:33:01] <pieterh>	look at the RRR patterns in Ch4
| [Monday 21 March 2011] [09:33:01] <yrashk>	ikr :)
| [Monday 21 March 2011] [09:33:08] <pieterh>	the distributed pirate is the very last example
| [Monday 21 March 2011] [09:33:49] <pieterh>	pgm is a decent option here but will require network support
| [Monday 21 March 2011] [09:34:33] <pieterh>	you could even make this work with a forwarder device, in a very short time
| [Monday 21 March 2011] [09:34:36] <pieterh>	hah
| [Monday 21 March 2011] [09:34:45] <pieterh>	to cheat... 
| [Monday 21 March 2011] [09:34:59] <pieterh>	every node connects to the forwarder front-end, and to the forwarder back-end
| [Monday 21 March 2011] [09:35:09] <pieterh>	use SUB socket filtering
| [Monday 21 March 2011] [09:35:15] <pieterh>	problem solved
| [Monday 21 March 2011] [09:35:31] <yrashk>	so a single forwarded device, then?
| [Monday 21 March 2011] [09:35:35] <pieterh>	yeah
| [Monday 21 March 2011] [09:35:36] <yrashk>	for starters
| [Monday 21 March 2011] [09:35:46] <pieterh>	all it does is connect a SUB to a PUB socket
| [Monday 21 March 2011] [09:36:16] <pieterh>	it acts like a network-global multicast group
| [Monday 21 March 2011] [09:36:26] <yrashk>	yeah I get it
| [Monday 21 March 2011] [09:36:41] <pieterh>	it'll take you about 1 hour to make, maybe less
| [Monday 21 March 2011] [09:36:57] <yrashk>	I can already imagine this, I have some good visual thinking
| [Monday 21 March 2011] [09:37:08] <pieterh>	when it works, send $1.50 to my paypal account, thanks
| [Monday 21 March 2011] [09:37:16] <yrashk>	hahah
| [Monday 21 March 2011] [09:37:21] <pieterh>	:-) 
| [Monday 21 March 2011] [09:37:28] <yrashk>	what's the account address? ;))
| [Monday 21 March 2011] [09:38:16] <pieterh>	ah, I have it here somewhere...
| [Monday 21 March 2011] [09:38:35] <pieterh>	so the downside of this approach is that filtering is subscriber-side
| [Monday 21 March 2011] [09:39:04] <pieterh>	and you have a central point, which you can scale to N redundant live-live instances
| [Monday 21 March 2011] [09:39:29] <pieterh>	upside is every node except the forwarder is dynamic
| [Monday 21 March 2011] [09:40:45] <yrashk>	yeah forwarders are obviously the bottlenecks here
| [Monday 21 March 2011] [09:41:12] <pieterh>	it won't slow things down unless you're doing millions of msg/sec
| [Monday 21 March 2011] [09:41:23] <pieterh>	if you need more scale, you switch to a name service approach
| [Monday 21 March 2011] [09:41:38] <pieterh>	i.e. every publisher is also a forwarder
| [Monday 21 March 2011] [09:41:39] <yrashk>	no I am not expecting huge volumes
| [Monday 21 March 2011] [09:41:49] <pieterh>	so, no bottleneck issue
| [Monday 21 March 2011] [09:42:01] <pieterh>	simple code doesn't crash
| [Monday 21 March 2011] [09:42:31] <pieterh>	you probably need to set a HWM properly
| [Monday 21 March 2011] [09:43:07] <yrashk>	so what you're suggesting is having a forwarder on each and every node, right?
| [Monday 21 March 2011] [09:44:00] <pieterh>	no, that's only if you need a lot more scale
| [Monday 21 March 2011] [09:44:06] <pieterh>	forget that
| [Monday 21 March 2011] [09:44:11] <pieterh>	one forwarder in middle of network
| [Monday 21 March 2011] [09:44:20] <pieterh>	binds to a SUB frontend, binds to a PUB backend
| [Monday 21 March 2011] [09:44:45] <pieterh>	every node connects to those two sockets, one to publish, one to subscribe
| [Monday 21 March 2011] [09:44:54] <pieterh>	every node receives every message, and filters using SUB filtering
| [Monday 21 March 2011] [09:45:00] <yrashk>	right
| [Monday 21 March 2011] [09:45:13] <pieterh>	then, if you need it, you double the forwarders and make live/live redundancy
| [Monday 21 March 2011] [09:45:46] <yrashk>	this live-live redundancy, any suggestions on how you would typically do it?
| [Monday 21 March 2011] [09:46:00] <yrashk>	is it like doing the same operations on a # of forwarders?
| [Monday 21 March 2011] [09:46:05] <pieterh>	you run two forwarders, right?
| [Monday 21 March 2011] [09:46:23] <pieterh>	and every node connects its PUB socket to both forwarders, and its SUB socket to both forwarders
| [Monday 21 March 2011] [09:46:42] <pieterh>	then you have to identity each message uniquely (sequence number per publisher)
| [Monday 21 March 2011] [09:46:42] <yrashk>	yeah then I imagined it right
| [Monday 21 March 2011] [09:46:47] <pieterh>	and reject duplicates
| [Monday 21 March 2011] [09:46:55] <pieterh>	0MQ handles the fanout and fanin properly
| [Monday 21 March 2011] [10:50:45] <mikko-_>	hi
| [Monday 21 March 2011] [10:51:05] <mikko-_>	I am not quite clear who should prepare the upstream patch for openpgm changes
| [Monday 21 March 2011] [10:57:56] <sustrik>	mikko-_: neither am i
| [Monday 21 March 2011] [10:58:12] <sustrik>	presumably, it's better to patch the master and downstream it afterwards
| [Monday 21 March 2011] [11:12:32] <mikko-_>	yes
| [Monday 21 March 2011] [11:41:00] <pieterh>	hi mikko
| [Monday 21 March 2011] [11:41:26] <pieterh>	we can't do pull requests to multiple gits, which is annoying
| [Monday 21 March 2011] [11:42:04] <pieterh>	mikko-_: I'm happy to send a patch from 2.1 to master
| [Monday 21 March 2011] [11:45:13] <sustrik>	pieterh: if you do so, take care to separate the openpgm thing from other functionality
| [Monday 21 March 2011] [11:45:32] <pieterh>	sustrik: yes, it's a single commit, the only grey part is that I tend to update the NEWS at the same time
| [Monday 21 March 2011] [11:45:41] <pieterh>	I'm going to start doing that in a separate commit
| [Monday 21 March 2011] [11:45:46] <sustrik>	ack
| [Monday 21 March 2011] [11:46:24] <pieterh>	I'll send you the patch for OpenPGM then, offlist since it's rather huge
| [Monday 21 March 2011] [11:47:01] <sustrik>	ok, also don't forget to sign it off
| [Monday 21 March 2011] [11:47:07] <pieterh>	right
| [Monday 21 March 2011] [11:48:41] <pieterh>	OK, sent...
| [Monday 21 March 2011] [11:49:19] <pieterh>	there's a better way to do this kind of exchange
| [Monday 21 March 2011] [11:49:42] <pieterh>	but I keep forgetting the ins and outs of git... :-)
| [Monday 21 March 2011] [12:08:14] <pieterh>	sustrik: I'm not going to scream on the list, but I'm using PAIR quite systematically now
| [Monday 21 March 2011] [12:23:39] <pieterh>	ok, I screamt
| [Monday 21 March 2011] [12:52:02] <Aaron__>	So I'm trying to build zeromq and have it link against a static uuid library. I'm not very good with configure scripts, and I don't see a parameter to tell configure where the static library and headers are. Can anyone help?
| [Monday 21 March 2011] [12:53:53] <pieterh>	Aaron__: what OS are you on?
| [Monday 21 March 2011] [12:54:05] <pieterh>	and what language are you working in?
| [Monday 21 March 2011] [12:54:18] <Aaron__>	Just Ubuntu.
| [Monday 21 March 2011] [12:54:28] <Aaron__>	c++
| [Monday 21 March 2011] [12:55:03] <pieterh>	hang on, I'll get you the gcc syntax...
| [Monday 21 March 2011] [12:55:40] <Aaron__>	gcc? Don't I need to satisfy the configure check?
| [Monday 21 March 2011] [12:55:44] <Aaron__>	first
| [Monday 21 March 2011] [12:56:02] <pieterh>	you are building an application right?
| [Monday 21 March 2011] [12:56:09] <pieterh>	or building zmq?
| [Monday 21 March 2011] [12:56:26] <pieterh>	ah, it doesn't link against anything when you build it
| [Monday 21 March 2011] [12:56:31] <Aaron__>	Well, it's a little complicated, but right now I'm just trying to build zeromq.
| [Monday 21 March 2011] [12:56:41] <pieterh>	please use the 2.1 package released today
| [Monday 21 March 2011] [12:56:47] <Aaron__>	I am.
| [Monday 21 March 2011] [12:56:57] <pieterh>	ok, good
| [Monday 21 March 2011] [12:57:10] <Aaron__>	It builds fine if I use the uuid-dev package.
| [Monday 21 March 2011] [12:57:17] <pieterh>	right, which is what you want
| [Monday 21 March 2011] [12:57:35] <Aaron__>	But that creates a dependance on libuuid.so.
| [Monday 21 March 2011] [12:57:39] <Aaron__>	Which I don't want.
| [Monday 21 March 2011] [12:57:46] <Seta00>	Aaron__: should be something like --with-uuid=/path/to/your/custom/build
| [Monday 21 March 2011] [12:57:52] <Aaron__>	I have uuid built statically...
| [Monday 21 March 2011] [12:58:05] <Aaron__>	ah
| [Monday 21 March 2011] [12:58:28] <pieterh>	Aaron__: when you find out how to do this, add it to the tips page at http://zero.mq/tips
| [Monday 21 March 2011] [13:00:43] <Aaron__>	I tried --with-uuid=/path/to/uuid/install/folder but got nothing.
| [Monday 21 March 2011] [13:01:00] <Aaron__>	Just the same "configure: error: cannot link with -luuid, install uuid-dev."
| [Monday 21 March 2011] [13:02:12] <Aaron__>	I tried a few different directories, /path/to/uuid/install/folder, /path/to/uuid/install/folder/lib, /path/to/uuid/install/folder/include, /path/to/uuid/install/folder/bin, but nothing did anything different.
| [Monday 21 March 2011] [13:02:37] <Aaron__>	Does the configure script actually support that argument?
| [Monday 21 March 2011] [13:02:49] <pieterh>	Aaron__: from reading configure, it's looking for, and not finding 'uuid_generate' in -luuid
| [Monday 21 March 2011] [13:03:29] <Aaron__>	Hmm, I guess I could double check my uuid.
| [Monday 21 March 2011] [13:05:32] <pieterh>	The rule in configure.in is pretty clear:
| [Monday 21 March 2011] [13:05:33] <pieterh>	AC_CHECK_LIB(uuid, uuid_generate, ,
| [Monday 21 March 2011] [13:05:33] <pieterh>	            [AC_MSG_ERROR([cannot link with -luuid, install uuid-dev.])])
| [Monday 21 March 2011] [13:06:55] <Aaron__>	Yeah, my uuid library does have a uuid_generate,
| [Monday 21 March 2011] [13:07:00] <Aaron__>	Sorry about that.
| [Monday 21 March 2011] [13:07:07] <Aaron__>	Barking up the wrong tree.
| [Monday 21 March 2011] [13:07:40] <Aaron__>	Thanks for the --with-uuid argument though.
| [Monday 21 March 2011] [13:08:07] <Aaron__>	I meant "doesn't have uuid_generate"
| [Monday 21 March 2011] [13:10:50] <pieterh>	ok, problem solved...
| [Monday 21 March 2011] [13:14:58] <Seta00>	:)
| [Monday 21 March 2011] [13:16:28] <Aaron__>	Apparantly there is more than one uuid library out there, sigh.
| [Monday 21 March 2011] [13:17:09] <Aaron__>	I thought it was the same one Postgresql was using.
| [Monday 21 March 2011] [13:17:31] <mikko-_>	Aaron__: are you building zeromq shared or static?
| [Monday 21 March 2011] [13:17:45] <Aaron__>	I want zeromq to be static too.
| [Monday 21 March 2011] [13:17:59] <mikko-_>	./configure --disable-shared
| [Monday 21 March 2011] [13:18:17] <Aaron__>	Yeah, I'll pop that on too.
| [Monday 21 March 2011] [13:18:26] <mikko-_>	as far as i understand if zeromq is static then libuuid would be as well
| [Monday 21 March 2011] [13:18:32] <Aaron__>	Ah
| [Monday 21 March 2011] [13:18:42] <Aaron__>	Well, I need to get the right uuid as the first step.
| [Monday 21 March 2011] [13:18:58] <mikko-_>	you should be able to use one provided by your OS
| [Monday 21 March 2011] [13:19:02] <mikko-_>	usually they ship .a as well
| [Monday 21 March 2011] [13:19:32] <Aaron__>	Yeah, I'm working on it as we speak.
| [Monday 21 March 2011] [13:20:32] <mikko-_>	on rhel its usually efsprogs and on ubuntu/debian etc uuid-dev
| [Monday 21 March 2011] [13:20:41] <mikko-_>	not sure about others
| [Monday 21 March 2011] [13:21:07] <mikko-_>	uuid libs are confusing as there are multiple of them
| [Monday 21 March 2011] [13:21:10] <mikko-_>	and they are not compatible
| [Monday 21 March 2011] [13:24:22] <Aaron__>	Yeah, I was certainly confused.
| [Monday 21 March 2011] [13:37:44] <drbobbeaty>	Question about the 2.1.3 packaging... with the change from 2.1.2 to 2.1.3, I now see that I'm generating a libpgm.so - but I'm not seeing it as an 'ldd' dependency of libzmq.so - is this right?
| [Monday 21 March 2011] [13:38:23] <drbobbeaty>	I used '--with-pgm' in the build, and I see it unpacking the OpenPGM code, and the libpgm.so is generated, but I'm having trouble running my code that worked fine with 2.1.2.
| [Monday 21 March 2011] [13:38:32] <Aaron__>	Well, "nm --demangle" tells me I have uuid_generate (0000000000000ee0 T uuid_generate). I'm running configure like so, "../configure --with-pic --prefix=/root/zeromq_install/ --enable-static --disable-shared --without-documentation --with-uuid=/path/to/uuid/install/dir/ ". And I still get "configure: error: cannot link with -luuid, install uuid-dev."
| [Monday 21 March 2011] [13:39:21] <drbobbeaty>	I have tried linking with '-lzmq -lpgm' and still it's not even starting to execute - it's as if I'm missing a critical step.
| [Monday 21 March 2011] [13:39:26] <drbobbeaty>	Anyone run into this?
| [Monday 21 March 2011] [13:39:30] <drbobbeaty>	Pieter?
| [Monday 21 March 2011] [13:39:35] <pieterh>	drbobbeaty: this is indeed a new part of 2.1.3
| [Monday 21 March 2011] [13:40:38] <pieterh>	it's quite possible that the OpenPGM integration doesn't work properly yet :-/
| [Monday 21 March 2011] [13:40:43] <drbobbeaty>	I'm OK with it being new, but code that ran fine with 2.1.2 is core dumping on main() in 2.1.3 - like I'm missing a linking step or something. Is there something I'm missing OTHER than the inclusion of '-lpgm' in the linking step?
| [Monday 21 March 2011] [13:41:10] <pieterh>	drbobbeaty: mikko is the man to answer this
| [Monday 21 March 2011] [13:41:15] <drbobbeaty>	That would be sad for a 'stable' tag.
| [Monday 21 March 2011] [13:41:15] <pieterh>	summon mikko...
| [Monday 21 March 2011] [13:41:45] <pieterh>	drbobbeaty: a bit, yes, but if there's a problem we'll fix it immediately
| [Monday 21 March 2011] [13:42:28] <pieterh>	mikko: are you around?
| [Monday 21 March 2011] [13:43:21] <pieterh>	drbobbeaty: can you post a minimal test case that causes it to die? I'll reproduce it
| [Monday 21 March 2011] [13:43:41] <drbobbeaty>	peiterh: Sure, give me a sec.
| [Monday 21 March 2011] [13:43:45] <pieterh>	k
| [Monday 21 March 2011] [14:01:17] <drbobbeaty>	pieterh: is there a list of what's changed from 2.1.2 to 2.1.3 - I'm having a tough time makeing the "minimal test" as my simple tests are OK, but the biggies that fail are awfully complex. Too complex for a test case, really.
| [Monday 21 March 2011] [14:01:34] <drbobbeaty>	If I knew what changed, maybe it'd help me find the issue in my code.
| [Monday 21 March 2011] [14:15:17] <cremes>	i'm starting to see a new assertion that i haven't run into before
| [Monday 21 March 2011] [14:15:18] <cremes>	Assertion failed: sessions.empty () (socket_base.cpp:127)
| [Monday 21 March 2011] [14:15:35] <cremes>	my code hasn't changed but i did update to the latest master
| [Monday 21 March 2011] [14:15:54] <cremes>	has anyone else seen this?
| [Monday 21 March 2011] [14:21:11] <drbobbeaty>	cremes: not me, but I'm seeing other problems with 2.1.3 that I wasn't seeing in 2.1.2
| [Monday 21 March 2011] [14:21:27] <cremes>	drbobbeaty: what problems are you seeing?
| [Monday 21 March 2011] [14:23:24] <drbobbeaty>	cremes: I'm tracking down an immediate app core dump when using the new 2.1.3 - It's not easily reproducable in a small app, but it's 100% reproduceable in my larger app. I'm trying to trim it down to get a good test case, but it's proving to be hard based on the immediate nature of the core dump.
| [Monday 21 March 2011] [14:23:44] <drbobbeaty>	The small test case runs fine. But the bigger one is nasty.
| [Monday 21 March 2011] [14:24:41] <cremes>	drbobbeaty: if you catch the crash in gdb, where is it crashing inside 0mq?
| [Monday 21 March 2011] [14:25:37] <drbobbeaty>	Nope, it's crashing on main() - the very first executable line. But if I comment out the calls to 0MQ, it runs just fine. 
| [Monday 21 March 2011] [14:26:00] <drbobbeaty>	It's the invocation of the ZMQ calls in some way that's causing it to core dump - I just haven't figured out what.
| [Monday 21 March 2011] [14:26:19] <cremes>	that is quite... odd :)
| [Monday 21 March 2011] [14:26:20] <drbobbeaty>	If I had a nice stack trace, I'd be able to figure this out easily. But I don't.
| [Monday 21 March 2011] [14:26:49] <pieterh>	drbobbeaty: are you using pgm in all your cases?
| [Monday 21 March 2011] [14:28:08] <pieterh>	cremes: this is from the development master?
| [Monday 21 March 2011] [14:28:17] <cremes>	pieterh: correct
| [Monday 21 March 2011] [14:28:31] <pieterh>	can you try with the 2.1 release and see if you also get it?
| [Monday 21 March 2011] [14:28:32] <cremes>	i am trying to 'bisect' it now to see if i can narrow down the commit that broke it
| [Monday 21 March 2011] [14:28:41] <cremes>	sure, i can do that
| [Monday 21 March 2011] [14:29:30] <drbobbeaty>	pieterh: Yup, pgm is what I use - 100% of the time.
| [Monday 21 March 2011] [14:29:36] <drbobbeaty>	I'm getting closer... :)
| [Monday 21 March 2011] [14:29:49] <pieterh>	drbobbeaty: ok, so presumably there's a load library issue
| [Monday 21 March 2011] [14:30:02] <pieterh>	the other changes over 2.1.2 are all quite specific patches for core bugs
| [Monday 21 March 2011] [14:32:26] <drbobbeaty>	pieterh: I'm in the configuration code of my app - setting the ZMQ_ properties of the socket. It *appears* I'm getting close.
| [Monday 21 March 2011] [14:33:00] <pieterh>	drbobbeaty: presumably a load error on the openpgm library
| [Monday 21 March 2011] [14:33:59] <drbobbeaty>	In my simple test ( https://gist.github.com/635015 ) I'm now seeing the following error:
| [Monday 21 March 2011] [14:34:20] <drbobbeaty>	Assertion failed: rc == 0 (connect_session.cpp:84)
| [Monday 21 March 2011] [14:34:44] <drbobbeaty>	Double-checking to see if I messed up the test.
| [Monday 21 March 2011] [14:38:47] <drbobbeaty>	pieterh: triple-checked... if I compile this as 'g++ xmit.cpp -o xmit -lzmq' I get the error.
| [Monday 21 March 2011] [14:38:59] <drbobbeaty>	If I add in the '-lpgm' at the end I still get the error.
| [Monday 21 March 2011] [14:39:09] <pieterh>	ok, let me give it a shot
| [Monday 21 March 2011] [14:39:20] <drbobbeaty>	If I switch the order so it reads: '-lpgm -lzmq' I still get the error.
| [Monday 21 March 2011] [14:42:38] <pieterh>	drbobbeaty: I get a clean error message 'Protocol not supported' and then a core dump
| [Monday 21 March 2011] [14:42:49] <pieterh>	this is 0MQ 2.1.3 built without OpenPGM
| [Monday 21 March 2011] [14:43:50] <drbobbeaty>	pieterh: not surprising... I'm using OpenPGM in the example. You need to build it --with-pgm and then try it.
| [Monday 21 March 2011] [14:44:16] <drbobbeaty>	pieterh: I've tried two boxes - Ubuntu 10.04.1 and CentOS 5 and both have the same error when using 2.1.3 w/OpenPGM
| [Monday 21 March 2011] [14:44:31] <pieterh>	drbobbeaty: would you raise an issue at https://github.com/zeromq/zeromq2-1/issues and put a link to your example?
| [Monday 21 March 2011] [14:44:33] <drbobbeaty>	(same gist used on both machines)
| [Monday 21 March 2011] [14:45:01] <drbobbeaty>	I've never done that. I'll try. I'll be as complete as I can be.
| [Monday 21 March 2011] [14:45:26] <pieterh>	interesting... when I build 2.1.3 with pgm, the test program says 'sending...' in a loop
| [Monday 21 March 2011] [14:45:30] <pieterh>	it doesn't crash
| [Monday 21 March 2011] [14:45:45] <drbobbeaty>	Ha... I saw that once, but then when I tried it again, it failed.
| [Monday 21 March 2011] [14:45:59] <pieterh>	ok, will try a few times... this is Ubuntu 10.10 fwiw
| [Monday 21 March 2011] [14:46:04] <drbobbeaty>	The correct behavior is to see the "sending..." in a loop. (until a Ctrl-C)
| [Monday 21 March 2011] [14:46:20] <pieterh>	yes, that's what I get
| [Monday 21 March 2011] [14:46:25] <pieterh>	doing a naive build 
| [Monday 21 March 2011] [14:46:46] <pieterh>	so... I'm suspecting you have a conflict between versions of OpenPGM on your systems
| [Monday 21 March 2011] [14:47:10] <pieterh>	or some such mix caused by the upgrade of the OpenPGM version in this package
| [Monday 21 March 2011] [14:48:09] <pieterh>	drbobbeaty: have you enabled core dumps ('ulimit unlimited')?
| [Monday 21 March 2011] [14:48:09] <drbobbeaty>	Yeah, I'm going to check on that now. Thanks for showing that it might be me.
| [Monday 21 March 2011] [14:48:26] <pieterh>	when you get an assertion failure, you need to get the backtrace
| [Monday 21 March 2011] [14:52:19] <drbobbeaty>	pieterh: got the backtrace.
| [Monday 21 March 2011] [14:52:45] <drbobbeaty>	I'll include it if I can't clean up the problem with a drop and load of all the ZMQ libraries on the box.
| [Monday 21 March 2011] [14:52:49] <pieterh>	cool... actually, you can log the issue in the development git, https://github.com/zeromq/zeromq2, it'll be the same
| [Monday 21 March 2011] [14:53:04] <pieterh>	please, do log the assertion and backtrace, it may be useful info
| [Monday 21 March 2011] [14:56:51] <sustrik>	yuck, the change should have gone to master first
| [Monday 21 March 2011] [15:01:59] <pieterh>	sustrik: no-one would have tested it there, and it's not clear that it's caused by a code change
| [Monday 21 March 2011] [15:03:17] <pieterh>	I'd rather see valuable code delivered fast, and fixed fast, than held back...
| [Monday 21 March 2011] [15:04:52] <cremes>	after using git-bisect, it tells me that this is the first bad commit
| [Monday 21 March 2011] [15:04:53] <cremes>	32ded2b457b2102dba4c15e00363f031d212b1c4
| [Monday 21 March 2011] [15:05:01] <cremes>	Duplicate identities now checked with zmq_connect
| [Monday 21 March 2011] [15:05:19] <cremes>	this commit touched quite a bit of code too
| [Monday 21 March 2011] [15:05:42] <cremes>	pieterh: want me to open an issue against master?
| [Monday 21 March 2011] [15:05:47] <pieterh>	cremes: yes, please
| [Monday 21 March 2011] [15:05:49] <cremes>	i don't have a small repro
| [Monday 21 March 2011] [15:06:00] <pieterh>	it'll be the same issue in master and in 2.1.3
| [Monday 21 March 2011] [15:06:10] <sustrik>	how come it is in stable?
| [Monday 21 March 2011] [15:06:16] <sustrik>	it's an untested patch
| [Monday 21 March 2011] [15:06:23] <pieterh>	sustrik: because we apply all patches to stable automatically
| [Monday 21 March 2011] [15:06:31] <pieterh>	there is no other process for defining what's "tested"
| [Monday 21 March 2011] [15:06:47] <pieterh>	no other way except real use, since we lack comprehensive test coverage
| [Monday 21 March 2011] [15:07:18] <sustrik>	mail from March 16th: "This patch solves issue 176. However, it was not yet tested thoroughly so it should be applied to stable later on, when it's clear it doesn't introduce new bugs."
| [Monday 21 March 2011] [15:07:32] <pieterh>	ah, then that is not in stable
| [Monday 21 March 2011] [15:07:42] <pieterh>	cremes is testing against development master
| [Monday 21 March 2011] [15:07:59] <sustrik>	ok, good
| [Monday 21 March 2011] [15:08:00] <pieterh>	if you tell me to hold back a patch I do so, of course
| [Monday 21 March 2011] [15:08:13] <pieterh>	np
| [Monday 21 March 2011] [15:08:14] <cremes>	https://github.com/zeromq/zeromq2/issues/181
| [Monday 21 March 2011] [15:08:23] <sustrik>	cremes: thx
| [Monday 21 March 2011] [15:08:33] <pieterh>	cremes, just for sanity, can you confirm the problem does _not_ happen on 2.1.3?
| [Monday 21 March 2011] [15:08:47] <cremes>	sure; i will download it and confirm
| [Monday 21 March 2011] [15:08:50] <pieterh>	much appreciated
| [Monday 21 March 2011] [15:10:14] <FlaPer87>	In case anyone is interested and willing to contribute: https://github.com/FlaPer87/asterisk-zmq-manager
| [Monday 21 March 2011] [15:12:08] <mikko>	pieterh: am now
| [Monday 21 March 2011] [15:12:44] <pieterh>	mikko: possibly a false alarm, we found what might be a problem with OpenPGM in 2.1.3
| [Monday 21 March 2011] [15:13:09] <pieterh>	drbobbeaty is seeing if it's caused by library confusion on his systems
| [Monday 21 March 2011] [15:13:39] <pieterh>	anyhow, pgm example that worked with 2.1.2 fails with 2.1.3... on my system it works fine
| [Monday 21 March 2011] [15:14:39] <mikko>	zfl tests failed as well it seems
| [Monday 21 March 2011] [15:14:44] <pieterh>	FlaPer87: line 412 is lacking 'zmq_msg_close (&message);'
| [Monday 21 March 2011] [15:14:56] <mikko>	hmm, is there a way to test OpenPGM functionally easily?
| [Monday 21 March 2011] [15:15:10] <pieterh>	mikko: fixed that, was some old 2.0 code that magically continued to work on 2.1...
| [Monday 21 March 2011] [15:15:18] <mikko>	i kinda rely on Steven on that as I have no means on testing with any sort of wates
| [Monday 21 March 2011] [15:15:22] <pieterh>	yeah
| [Monday 21 March 2011] [15:15:28] <mikko>	rates*
| [Monday 21 March 2011] [15:15:51] <pieterh>	we have some pgm-capable material at iMatix in Slovakia but it's not configured any longer
| [Monday 21 March 2011] [15:16:28] <FlaPer87>	pieterh opps, thanks
| [Monday 21 March 2011] [15:16:45] <mikko>	so the openpgm is a false alarm?
| [Monday 21 March 2011] [15:16:53] <pieterh>	FlaPer87: try running under valgrind, you'll catch memory leaks like that
| [Monday 21 March 2011] [15:17:10] <pieterh>	mikko: don't know yet, could be a build issue we've not hit before
| [Monday 21 March 2011] [15:17:22] <mikko>	what OS is drbobbeaty running?
| [Monday 21 March 2011] [15:17:26] <FlaPer87>	pieterh indeed, I will
| [Monday 21 March 2011] [15:17:29] <FlaPer87>	thanks :)
| [Monday 21 March 2011] [15:17:37] <pieterh>	Ubuntu and CentOS
| [Monday 21 March 2011] [15:17:42] <drbobbeaty>	mikko: Ubuntu 10.04.1 and CentOS 5
| [Monday 21 March 2011] [15:17:50] <mikko>	drbobbeaty: both fail?
| [Monday 21 March 2011] [15:18:00] <drbobbeaty>	Yup
| [Monday 21 March 2011] [15:19:22] <mikko>	drbobbeaty: it's supposed to link against libtool convenience archive
| [Monday 21 March 2011] [15:19:30] <mikko>	libpgm_noinst.la
| [Monday 21 March 2011] [15:19:40] <mikko>	which just contains a set of object files
| [Monday 21 March 2011] [15:20:12] <mikko>	libpgm.so should not be used when building with zeromq
| [Monday 21 March 2011] [15:20:57] <drbobbeaty>	OK, that's news. In the past (2.1.2), I used the '-lzmq' and it worked just fine with the ZMQ shared lib. Is this not supported in 2.1.3?
| [Monday 21 March 2011] [15:21:21] <mikko>	that should work fine
| [Monday 21 March 2011] [15:22:07] <pieterh>	fwiw I've done 'g++ xmit.cpp -o xmit -lzmq' and the test case runs fine on my Ubuntu box
| [Monday 21 March 2011] [15:22:58] <mikko>	the convenience libtool archive is just a bunch of object files
| [Monday 21 March 2011] [15:23:08] <mikko>	and zeromq uses that rather than the .c files directly
| [Monday 21 March 2011] [15:23:43] <mikko>	in theory (unless there is some libtool weirdness going on) there should be no change how things work
| [Monday 21 March 2011] [15:23:56] <Guest31294>	in theory, everything always works.
| [Monday 21 March 2011] [15:24:40] <cremes>	pieterh: no assertion when using the 2.1.3 release, so that's a good sign
| [Monday 21 March 2011] [15:25:02] <pieterh>	cremes: thanks for testing that, it means our ad-hoc change flow process is working ... :-)
| [Monday 21 March 2011] [15:25:02] <drbobbeaty>	mikko: I certainly hope that's the case, but up to know I've had a ton of counter-examples staring me in the face. I'll try to clean up things here and see if I can get it back to what works.
| [Monday 21 March 2011] [15:25:49] <mikko>	is there a test code i can run for this openpgm thing?
| [Monday 21 March 2011] [15:26:15] <pieterh>	mikko: https://gist.github.com/635015
| [Monday 21 March 2011] [15:28:21] <mikko>	Initialization complete.
| [Monday 21 March 2011] [15:28:21] <mikko>	sending...
| [Monday 21 March 2011] [15:28:21] <mikko>	sending...
| [Monday 21 March 2011] [15:28:21] <mikko>	sending...
| [Monday 21 March 2011] [15:28:25] <mikko>	and so o n
| [Monday 21 March 2011] [15:28:32] <mikko>	is that the expected result?
| [Monday 21 March 2011] [15:29:42] <drbobbeaty>	mikko: yes.
| [Monday 21 March 2011] [15:30:09] <drbobbeaty>	What I'm getting is the "Assertion failed: rc == 0 (connect_session.cpp:84)"
| [Monday 21 March 2011] [15:30:38] <mikko>	just in case i did rm /path/to/lib/libpgm*
| [Monday 21 March 2011] [15:30:43] <mikko>	and the example still runs
| [Monday 21 March 2011] [15:30:58] <mikko>	can you put nm /path/to/libzmq.so to gist.github.com?
| [Monday 21 March 2011] [15:31:03] <mikko>	and ldd /path/to/libzmq.so
| [Monday 21 March 2011] [15:32:26] <pieterh>	mikko: my guess is that drbobbeaty's two systems have old versions of OpenPGM which is causing a problem
| [Monday 21 March 2011] [15:33:33] <pieterh>	drbobbeaty: any chance you can test on a virgin box? at least one you didn't build on before?
| [Monday 21 March 2011] [15:33:39] <drbobbeaty>	pieterh: I didn't have any old version of OpenPGM as I never had it until ZMQ. In 2.1.2 it was contained within the libzmq.so - with 2.1.3, it appeared that it was external. Now I see it wasn't external at all, just optionally external.
| [Monday 21 March 2011] [15:34:04] <pieterh>	hmm... indeed
| [Monday 21 March 2011] [15:34:13] <drbobbeaty>	pieterh: I'm certainly working on all these ideas. As fast as I can.
| [Monday 21 March 2011] [15:34:25] <drbobbeaty>	I would like to believe it's as simple as a bad version.
| [Monday 21 March 2011] [15:34:59] <mikko>	i would be keen on getting openpgm into daily builds somehow
| [Monday 21 March 2011] [15:35:10] <mikko>	that way we can see if the actual functionality ever breaks
| [Monday 21 March 2011] [15:35:58] <pieterh>	hmm, that would be very nice
| [Monday 21 March 2011] [15:37:16] <mikko>	drbobbeaty: can you paste nm output of libzmq.so ?
| [Monday 21 March 2011] [15:42:47] <drbobbeaty>	Yes, just need a bit. I'm trying to change the RPM packaging to remove the OpenPGM libraries and headers to make it cleaner as to what's really being installed.
| [Monday 21 March 2011] [15:46:13] <drbobbeaty>	mikko: when I run: 'nm /usr/lib64/libzmq.so.1' I get:
| [Monday 21 March 2011] [15:46:24] <drbobbeaty>	nm: /usr/lib64/libzmq.so.1: no symbols
| [Monday 21 March 2011] [15:47:01] <drbobbeaty>	I have cleaned up my RPMs and they are now built as zeromq, zeromq-devel and zeromq-pgm - where the latter has just the OpenPGM libs and headers.
| [Monday 21 March 2011] [15:47:24] <drbobbeaty>	Even after removing everything on my box related to ZMQ, and putting these new RPMs on, I get the assertion.
| [Monday 21 March 2011] [15:47:47] <mikko>	let me install a clean ubuntu VM
| [Monday 21 March 2011] [15:47:49] <mikko>	sec
| [Monday 21 March 2011] [15:55:24] <mikko>	drbobbeaty: i removed my installation of libzmq completely, rebuilt
| [Monday 21 March 2011] [15:55:40] <mikko>	rebuilt the xmit.cpp and ran with LD_LIBRARY_PATH
| [Monday 21 March 2011] [15:55:45] <mikko>	it seems to work ok
| [Monday 21 March 2011] [15:56:12] <mikko>	i'll make an install-exec-hook patch later so that people dont get confused with libpgm.so
| [Monday 21 March 2011] [15:56:28] <mikko>	i dont think there is a way to force autotools not to install it
| [Monday 21 March 2011] [15:56:33] <mikko>	brb
| [Monday 21 March 2011] [15:56:37] <drbobbeaty>	mikko: Thanks for the checking... I'm getting convinced it's now I have it built, but it's not at all clear why the way I build it from 2.1.2 to 2.1.3 causes these issues. I've had many upgrades in this process.
| [Monday 21 March 2011] [15:58:05] <mikko>	drbobbeaty: i will install clean ubuntu vm later and test
| [Monday 21 March 2011] [15:58:14] <mikko>	it's worrying if this actually fails for anyone
| [Monday 21 March 2011] [15:59:16] <pieterh>	drbobbeaty: can you post an issue with the assert and backtrace?
| [Monday 21 March 2011] [15:59:30] <drbobbeaty>	mikko: I'm troubled by what I'm seeing, and I fear it's in the building. I'm going to see if I can build it without the RPM structure if it works. I'm guessing that's how you guys are all doing it. Just 'configure --with-pgm' - right?
| [Monday 21 March 2011] [15:59:39] <pieterh>	it may be possible to figure out what's happening from that
| [Monday 21 March 2011] [15:59:45] <pieterh>	drbobbeaty: yes
| [Monday 21 March 2011] [16:00:02] <drbobbeaty>	pieterh: OK, trying that now
| [Monday 21 March 2011] [16:00:16] <pieterh>	just as explained in the docs; configure; make; sudo make install; sudo ldconfig
| [Monday 21 March 2011] [16:00:24] <pieterh>	--with-pgm, then
| [Monday 21 March 2011] [16:00:38] <mikko>	drbobbeaty: yes
| [Monday 21 March 2011] [16:01:24] <mikko>	drbobbeaty: it's possible that the build breaks if for example RPM does something very weird
| [Monday 21 March 2011] [16:01:41] <mikko>	i think install-exec-hook should allow cleaning the libpgm stuff
| [Monday 21 March 2011] [16:01:46] <drbobbeaty>	mikko: it's the same spec file that ships with the package.
| [Monday 21 March 2011] [16:02:02] <mikko>	drbobbeaty: i know, i don't think it's very actively checked (it seems)
| [Monday 21 March 2011] [16:02:29] <mikko>	i had RPM builds running earlier but it was in a chroot which was really slow
| [Monday 21 March 2011] [16:02:43] <mikko>	if there are actually RPM users i could install centos VM for rpm packaging
| [Monday 21 March 2011] [16:02:48] <pieterh>	drbobbeaty: I see at least one problem with the spec file in 2.1.3
| [Monday 21 March 2011] [16:02:59] <mikko>	so that the packaging gets tested regurly as well
| [Monday 21 March 2011] [16:03:10] <pieterh>	it *might* be causing corrupted RPMs...
| [Monday 21 March 2011] [16:03:13] <mikko>	now i need to run for a min ->
| [Monday 21 March 2011] [16:03:50] 	 * pieterh hates hand-generated build files...
| [Monday 21 March 2011] [16:06:09] <pieterh>	drbobbeaty: if you want a fixed spec file, https://gist.github.com/880103 should be better
| [Monday 21 March 2011] [16:06:23] <pieterh>	I doubt this could cause the test program to crash but you never know
| [Monday 21 March 2011] [16:06:37] <flexo_>	hey. as i didnt find an answer to my question in either the guide, reference or faq (well, actually the lack of an answer might be an answer...) here it goes: does zmq support unreliable transport? (pure udp unicast/multicast)
| [Monday 21 March 2011] [16:06:46] <pieterh>	flexo_: nope
| [Monday 21 March 2011] [16:07:07] <flexo_>	any plans to add support for it?
| [Monday 21 March 2011] [16:07:15] <pieterh>	flexo_: feel free to send us a patch... 
| [Monday 21 March 2011] [16:07:24] <flexo_>	:)
| [Monday 21 March 2011] [16:07:37] <pieterh>	:-)
| [Monday 21 March 2011] [16:08:04] <drbobbeaty>	pieterh: what changed? Something small, or a lot of things?
| [Monday 21 March 2011] [16:08:17] <pieterh>	drbobbeaty: in the spec file, removal of the stand-alone device programs
| [Monday 21 March 2011] [16:08:28] <pieterh>	in the core library, OpenPGM integration and a lot of small patches
| [Monday 21 March 2011] [16:08:37] <pieterh>	it's in the NEWS and ChangeLog
| [Monday 21 March 2011] [16:08:48] <pieterh>	except the spec file, which I forgot to fix until just now
| [Monday 21 March 2011] [16:09:22] <flexo_>	seriously, would it fit into zmq's design.. purpose.. whatever? (looks to me like quite some work was done to _guarantee_ that the messages arrive...)
| [Monday 21 March 2011] [16:09:41] <pieterh>	flexo_: it could be useful for certain apps, yes
| [Monday 21 March 2011] [16:09:59] <flexo_>	for example in the app i have in mind :)
| [Monday 21 March 2011] [16:10:15] <pieterh>	yeah, when real time performance is more important than reliability
| [Monday 21 March 2011] [16:10:21] <flexo_>	yep
| [Monday 21 March 2011] [16:10:42] <pieterh>	seriously, if you need it, and if you can write C++, it should be doable
| [Monday 21 March 2011] [16:10:49] <flexo_>	but there are also certain kinds of messages which must arrive intact, hence having something like zmq for that kind of stuff would be nice
| [Monday 21 March 2011] [16:10:49] <pieterh>	transports are pluggable in 0MQ
| [Monday 21 March 2011] [16:11:02] <pieterh>	you can use different sockets for different QoS
| [Monday 21 March 2011] [16:11:22] <flexo_>	pieterh: assuming that i am a c++ wizard, how long would think it would take me to do it?
| [Monday 21 March 2011] [16:11:39] <flexo_>	(i know zmq for 10 minutes :)
| [Monday 21 March 2011] [16:11:40] <pieterh>	if you also know UDP, 1 day to get it working, 2-3 more days to get it working real nice
| [Monday 21 March 2011] [16:12:02] <flexo_>	alright
| [Monday 21 March 2011] [16:12:33] <pieterh>	you start by asking the question on the list, "I intend to add UDP support, please tell me what files to create / modify"
| [Monday 21 March 2011] [16:12:59] <flexo_>	im pretty confident i can figure it out by myself...
| [Monday 21 March 2011] [16:13:03] <pieterh>	we'll help package it all (docs, etc.) afterwards
| [Monday 21 March 2011] [16:13:14] <pieterh>	well, take a look at pgm integration as an example
| [Monday 21 March 2011] [16:13:20] 	 * flexo_ nods
| [Monday 21 March 2011] [16:13:37] <pieterh>	actually I should point out that it's technically impossible
| [Monday 21 March 2011] [16:13:46] <flexo_>	uhm?
| [Monday 21 March 2011] [16:13:49] <pieterh>	no-one has ever done this before, make 0MQ work with UDP
| [Monday 21 March 2011] [16:13:55] <pieterh>	therefore it's impossible
| [Monday 21 March 2011] [16:13:59] <pieterh>	and perhaps even illegal
| [Monday 21 March 2011] [16:14:01] <flexo_>	i see :(
| [Monday 21 March 2011] [16:14:01] <pieterh>	:-)
| [Monday 21 March 2011] [16:14:12] <flexo_>	just fyi: the app i have in mind would be a flight simulation visual
| [Monday 21 March 2011] [16:14:37] <pieterh>	flexo_: I'm kidding, you'd be the first person to try it
| [Monday 21 March 2011] [16:14:58] <flexo_>	i.e. several render boxes which receive telemetry via multicast
| [Monday 21 March 2011] [16:15:04] <pieterh>	yes, excellent use case
| [Monday 21 March 2011] [16:15:09] <flexo_>	(which must get the data really fast. ;)
| [Monday 21 March 2011] [16:15:18] <pieterh>	but doesn't mind if there's some breakage
| [Monday 21 March 2011] [16:15:45] <drbobbeaty>	mikko: why are you passing in '--prefix=/usr/local' to the OpenPGM configure script within the main configure script? Isn't that assuming that I'm putting it there? I'm not.
| [Monday 21 March 2011] [16:15:48] <flexo_>	(and otoh there is some stuff which must arrive, although it doesnt matter if the latency is somewhat higher, i.e. you change the scenario, daytime, etc.)
| [Monday 21 March 2011] [16:16:08] <flexo_>	add a new entity into the simulation, that kind of stuff
| [Monday 21 March 2011] [16:16:16] <pieterh>	yeah, it's like VoIP
| [Monday 21 March 2011] [16:16:23] <pieterh>	mix of reliable and unreliable patterns
| [Monday 21 March 2011] [16:16:42] <pieterh>	UDP would make a great addition
| [Monday 21 March 2011] [16:17:04] <pieterh>	but impossible and perhaps even illegal, so don't tell anyone...
| [Monday 21 March 2011] [16:17:04] <flexo_>	i was about to make up some protocol using a mix of tcp and multicast udp myself.. but i suppose it might be less work to just add unreliable transport support to zmq
| [Monday 21 March 2011] [16:17:09] <flexo_>	sure
| [Monday 21 March 2011] [16:17:39] <pieterh>	well, advantage of layering it under zmq is you get access to nice semantics on top
| [Monday 21 March 2011] [16:17:44] <flexo_>	its even intended for military usage so its morally nasty too
| [Monday 21 March 2011] [16:17:45] <pieterh>	plus APIs in lots of languages
| [Monday 21 March 2011] [16:17:51] <pieterh>	morally nasty, I love it
| [Monday 21 March 2011] [16:18:03] <pieterh>	I mean, terrible, terrible stuff...
| [Monday 21 March 2011] [16:18:16] <flexo_>	yes, and the zmq API looks really nice
| [Monday 21 March 2011] [16:18:25] <flexo_>	and well-looking APIs are rare :)
| [Monday 21 March 2011] [16:18:45] <pieterh>	it's going to get polished some more for v3.0
| [Monday 21 March 2011] [16:19:44] <flexo_>	a far-fetching thought here... is there some project providing some highlevel RPC mechanisms on-top of zmq? (think CORBA)
| [Monday 21 March 2011] [16:21:45] <pieterh>	flexo_: see the Guide, Chapter 4
| [Monday 21 March 2011] [16:21:57] <pieterh>	there are a whole set of RPC-like patterns built on top of 0MQ
| [Monday 21 March 2011] [16:22:11] <pieterh>	plus sample code and protocol specs
| [Monday 21 March 2011] [16:22:21] <pieterh>	not CORBA, though
| [Monday 21 March 2011] [16:22:24] <pieterh>	rather more 2011
| [Monday 21 March 2011] [16:23:07] <flexo_>	chapter 4? reliable request-reply?
| [Monday 21 March 2011] [16:23:15] <pieterh>	yes
| [Monday 21 March 2011] [16:23:25] <flexo_>	i realize that you can do all that stuff on-top of zmq
| [Monday 21 March 2011] [16:23:38] <flexo_>	but an ORB actually _does_ provide some pretty nice stuff
| [Monday 21 March 2011] [16:24:34] <pieterh>	specifically...?
| [Monday 21 March 2011] [16:24:50] <pieterh>	not that I'm disagreeing, just curious to what you mean
| [Monday 21 March 2011] [16:25:42] <flexo_>	well, the basic thing would be the IDL compiler - more advanced stuff would be object keys, activation / incarnation, etc.
| [Monday 21 March 2011] [16:26:03] <flexo_>	its pretty easy to do distributed garbage collected servants
| [Monday 21 March 2011] [16:26:41] <pieterh>	i prefer garbage collecting servants
| [Monday 21 March 2011] [16:26:49] <pieterh>	actually have no idea what those terms mean
| [Monday 21 March 2011] [16:26:53] <flexo_>	well
| [Monday 21 March 2011] [16:27:01] <flexo_>	take a virtual filesystem for example
| [Monday 21 March 2011] [16:27:16] <pieterh>	ok
| [Monday 21 March 2011] [16:27:17] <flexo_>	built using interfaces like IStream, IFile, etc.
| [Monday 21 March 2011] [16:27:25] <pieterh>	sure
| [Monday 21 March 2011] [16:27:38] <flexo_>	you can connect to any component in our application, no matter where it runs and ask it to open a file for you
| [Monday 21 March 2011] [16:27:49] <pieterh>	sure
| [Monday 21 March 2011] [16:28:04] <flexo_>	it provides transparent encryption / decryption, there is a key ring manager which asks the user for passwords, etc.
| [Monday 21 March 2011] [16:28:36] <pieterh>	this can all be layered on top of 0MQ
| [Monday 21 March 2011] [16:28:54] <flexo_>	the ORB provides me with the means to implement something like this in a nice object-oriented manner without writing lots of the low-level management code
| [Monday 21 March 2011] [16:29:38] <flexo_>	so i just say "give me a POA with this policy", i put the filename into the object key, my servant manager gets invoked when someone wants to invoke a ::read() on the the stream
| [Monday 21 March 2011] [16:29:40] <mikko>	drbobbeaty: autotools probably pass down prefix automatically
| [Monday 21 March 2011] [16:30:05] <pieterh>	POA = piece of action? sorry, the jargon is not familiar to me
| [Monday 21 March 2011] [16:30:50] <pieterh>	so why are no companies making money from ORBs any more?
| [Monday 21 March 2011] [16:31:06] <flexo_>	portable object adapter.. an internal CORBA component which. hm..  is responsible for servants. it knows their servant manager and how to invoke methods on these servants
| [Monday 21 March 2011] [16:31:10] <flexo_>	heh
| [Monday 21 March 2011] [16:31:15] <flexo_>	pieterh: dont get me wrong here
| [Monday 21 March 2011] [16:31:26] <flexo_>	CORBA heavily sucks in a lot of areas
| [Monday 21 March 2011] [16:31:36] <pieterh>	nah, I'm just curious, CORBA has always appeared to me as massively complex
| [Monday 21 March 2011] [16:31:48] <pieterh>	complex concepts, complex APIs, complex tools
| [Monday 21 March 2011] [16:31:52] <flexo_>	but most of its "complex" design actually makes sense
| [Monday 21 March 2011] [16:32:01] <pieterh>	sure, but that doesn't mean much in the end
| [Monday 21 March 2011] [16:32:22] <flexo_>	actually
| [Monday 21 March 2011] [16:32:30] <pieterh>	sadly, a 100% complete solution that is 100x more complex than an 80% complete solution will not win
| [Monday 21 March 2011] [16:32:40] <flexo_>	well
| [Monday 21 March 2011] [16:32:44] <flexo_>	you definitly have a point there
| [Monday 21 March 2011] [16:32:50] <pieterh>	this is what I mean by 2011
| [Monday 21 March 2011] [16:32:53] <flexo_>	my company made money with an ORB i wrote couple of months ago
| [Monday 21 March 2011] [16:33:09] <flexo_>	but this ORB only implemented the features needed, so maybe it was like 70% conformant :)
| [Monday 21 March 2011] [16:33:17] <pieterh>	if you have customers for ORBs, you may enjoy using 0MQ as the transport
| [Monday 21 March 2011] [16:33:18] <flexo_>	(targeting embedded hardware)
| [Monday 21 March 2011] [16:33:41] <flexo_>	yea, im thinking about that
| [Monday 21 March 2011] [16:33:53] <flexo_>	im also thinking about replacing CORBA because it annoys me heavily...
| [Monday 21 March 2011] [16:33:57] <pieterh>	that's how we see 0MQ, as a smart transport layer
| [Monday 21 March 2011] [16:34:10] <flexo_>	its very cumbersome to use, especially with the c++ mapping
| [Monday 21 March 2011] [16:34:11] <pieterh>	it's never going to include IDLs and key managers
| [Monday 21 March 2011] [16:34:55] <flexo_>	do you think IDL compilers are bad in principle?
| [Monday 21 March 2011] [16:35:12] <pieterh>	no, just that data representation isn't the job of the messaging fabric
| [Monday 21 March 2011] [16:35:19] <flexo_>	(i.e. the whole RPC idea which makes it look like a function/method call)
| [Monday 21 March 2011] [16:35:25] <pieterh>	for most purposes, JSON is fine
| [Monday 21 March 2011] [16:35:29] <flexo_>	i completely agree
| [Monday 21 March 2011] [16:35:34] <pieterh>	JSON is very 2011
| [Monday 21 March 2011] [16:35:40] <flexo_>	heh
| [Monday 21 March 2011] [16:35:46] <pieterh>	totally cheap and nasty serialization that works for 80% of developers
| [Monday 21 March 2011] [16:35:54] <flexo_>	too nasty for my purposes
| [Monday 21 March 2011] [16:36:08] <flexo_>	the parsing overhead just...
| [Monday 21 March 2011] [16:36:09] <flexo_>	no
| [Monday 21 March 2011] [16:36:13] <flexo_>	it feels wrong.
| [Monday 21 March 2011] [16:36:22] <pieterh>	so you ideally want a JSON approach for low-volume cases, and smart binary framing for high-volume cases
| [Monday 21 March 2011] [16:36:44] <pieterh>	I'm also a fan of divide and conquer
| [Monday 21 March 2011] [16:36:45] <flexo_>	i dont really see the advantage of JSON over CDR
| [Monday 21 March 2011] [16:36:50] <flexo_>	CDR is very nice IMHO
| [Monday 21 March 2011] [16:36:56] <pieterh>	JSON requires no upfront thinking
| [Monday 21 March 2011] [16:37:13] <flexo_>	neighter does CDR if you are used to think of a struct like a damn struct in memory :)
| [Monday 21 March 2011] [16:37:25] <pieterh>	so why is no-one using CDR?
| [Monday 21 March 2011] [16:37:29] <pieterh>	I mean, the market decides
| [Monday 21 March 2011] [16:37:41] <flexo_>	pieterh: because CDR is deep within CORBA
| [Monday 21 March 2011] [16:37:44] <flexo_>	and CORBA scares people
| [Monday 21 March 2011] [16:37:48] <pieterh>	nah, because it's a complex toolchain
| [Monday 21 March 2011] [16:37:59] <flexo_>	no, CDR is complety separete of everything
| [Monday 21 March 2011] [16:38:12] <flexo_>	its simply a binary data representation
| [Monday 21 March 2011] [16:38:28] <flexo_>	containing some stupid padding.. but thats far less worse than JSON
| [Monday 21 March 2011] [16:38:46] <pieterh>	I can't even find a web page describing CDR
| [Monday 21 March 2011] [16:38:52] <flexo_>	as i said
| [Monday 21 March 2011] [16:38:53] <pieterh>	it's embedded in some PDF somewhere
| [Monday 21 March 2011] [16:38:55] <pieterh>	fail
| [Monday 21 March 2011] [16:39:01] <flexo_>	thats the point.. its embedded deep inside the CORBA specs
| [Monday 21 March 2011] [16:39:06] <flexo_>	and thats the reason no-one uses it
| [Monday 21 March 2011] [16:39:09] <flexo_>	not because its bad
| [Monday 21 March 2011] [16:39:11] <pieterh>	yeah, but that's not "very nice"
| [Monday 21 March 2011] [16:39:17] <flexo_>	agreed
| [Monday 21 March 2011] [16:39:24] <bpl29>	Hello hello.  I am trying to link the zmq library to my project, but think I have built an 1386 library instead of x86_64.
| [Monday 21 March 2011] [16:39:34] <flexo_>	but "everyone uses it" doesnt make it a nice format.. take bittorrent for example
| [Monday 21 March 2011] [16:39:52] <bpl29>	*i386
| [Monday 21 March 2011] [16:39:56] <flexo_>	everyone uses bittorrent and bittorrent uses a highly stupid serialization format
| [Monday 21 March 2011] [16:40:17] <pieterh>	flexo_: well, I've made dozens, hundreds of technically brilliant tools over the years
| [Monday 21 March 2011] [16:40:18] <pieterh>	all '
| [Monday 21 March 2011] [16:40:21] <pieterh>	'perfect'
| [Monday 21 March 2011] [16:40:30] <pieterh>	all dead, because they were inaccessible
| [Monday 21 March 2011] [16:40:39] <flexo_>	its nice to parse with some regular expressions, but if you try to make a very-high throughput implementation you turn crazy because of that "human readable" ascii mess
| [Monday 21 March 2011] [16:40:59] <pieterh>	bpl29: have you copied the library from one box to another?
| [Monday 21 March 2011] [16:41:24] <flexo_>	pieterh: well. i dont disagree with you on any particular point...
| [Monday 21 March 2011] [16:41:41] <pieterh>	anyhow, wrt ORB capabilities over 0MQ, go for it, I'd say
| [Monday 21 March 2011] [16:41:54] <bpl29>	pieterh: No.  As well, I just rebuilt from source.  I am linking with -L/usr/local/lib -lzmq
| [Monday 21 March 2011] [16:42:02] <flexo_>	i just refuse to acknowledge that i spend so much time working with crap
| [Monday 21 March 2011] [16:42:14] <pieterh>	flexo_: Sturgeon's Law
| [Monday 21 March 2011] [16:42:34] <flexo_>	yea :)
| [Monday 21 March 2011] [16:42:39] <bpl29>	pieterh: The error simply states "warning: in /usr/local/lib/libzmq.dylib, file was built for unsupported file format which is not the architecture being linked (i386)"
| [Monday 21 March 2011] [16:42:40] <pieterh>	bpl29: so why do you think you built it wrong? it should work automatically, your compiler knows it's on a 64-bit box
| [Monday 21 March 2011] [16:42:44] <pieterh>	hmm
| [Monday 21 March 2011] [16:42:55] <pieterh>	what OS are you on?
| [Monday 21 March 2011] [16:43:02] <bpl29>	pieterh: OS X
| [Monday 21 March 2011] [16:43:28] <pieterh>	bpl29: sorry, I'm not expert in OS X builds, but maybe someone else here can help.. cremes?
| [Monday 21 March 2011] [16:43:45] <cremes>	pieterh: what's up?
| [Monday 21 March 2011] [16:44:06] <pieterh>	any idea why a build on OS X would say "file was built for unsupported file format which is not the architecture being linked (i386)"
| [Monday 21 March 2011] [16:45:14] <cremes>	yes...
| [Monday 21 March 2011] [16:45:42] <cremes>	the library is being built i386 but it's linking against a (probably) x86_64 binary
| [Monday 21 March 2011] [16:46:00] <cremes>	bpl29: run "file <name>" against the library and tell us the output
| [Monday 21 March 2011] [16:46:11] <bpl29>	okay one moment
| [Monday 21 March 2011] [16:46:19] <pieterh>	"If you're using Xcode, then by default Debug mode only builds your platforms native arch. So on a new mac, this would be an x86_64 binary."
| [Monday 21 March 2011] [16:46:19] <yrashk>	it looks like I've got a case of send() lockup with ZMQ_NOBLOCK :-\
| [Monday 21 March 2011] [16:46:22] <pieterh>	http://www.qtcentre.org/threads/30670-On-Mac-quot-...file-was-built-for-unsupported-file-format..-quot-SOLVED
| [Monday 21 March 2011] [16:46:33] <pieterh>	yrashk: cool!
| [Monday 21 March 2011] [16:46:41] <flexo_>	pieterh: anyway, just wanted to clarify that it seems to me that you are one of the more.. much more.. competent people i have met. although i disagree with your JSON notion. :)
| [Monday 21 March 2011] [16:47:00] <bpl29>	creme: /usr/local/lib/libzmq.dylib: Mach-O 64-bit dynamically linked shared library x86_64
| [Monday 21 March 2011] [16:47:05] <pieterh>	flexo_: I'm just old and cynical, not particularly competent, but the compliment feels nice, thanks
| [Monday 21 March 2011] [16:47:24] <cremes>	bpl29: and what program is trying to load that library? run "file" against it too
| [Monday 21 March 2011] [16:47:31] <yrashk>	pieterh: indeed :) 
| [Monday 21 March 2011] [16:47:39] <flexo_>	pieterh: well, i am highly cynical aswell.. maybe thats the reason for the sympathy :)
| [Monday 21 March 2011] [16:47:59] <flexo_>	(not old though. :D)
| [Monday 21 March 2011] [16:48:00] <yrashk>	I think I know why it happens
| [Monday 21 March 2011] [16:48:06] <pieterh>	flexo_: one thing I've learned is that intelligence is a product of many minds, not a few experts
| [Monday 21 March 2011] [16:48:19] <pieterh>	yrashk: 2.1.3 or development master?
| [Monday 21 March 2011] [16:48:22] <yrashk>	but no idea how to fix it
| [Monday 21 March 2011] [16:48:33] <pieterh>	what do you think happens?
| [Monday 21 March 2011] [16:48:37] <yrashk>	184bdb8e2bb6fe252af1bf4dd16d1c9ed8892f7a
| [Monday 21 March 2011] [16:49:04] <yrashk>	with this specific command that I am sending to another thread, that thread closes the socket that its being sent through
| [Monday 21 March 2011] [16:49:13] <bpl29>	creme: I am using ocamlmklib.
| [Monday 21 March 2011] [16:49:21] <yrashk>	so sometimes it gets through fine (it closes the socket *after* send() is over)
| [Monday 21 March 2011] [16:49:25] <bpl29>	owait, sry, misinterpreted
| [Monday 21 March 2011] [16:49:35] <jond>	flexo_ CDR is an ok encoding, though the character set stuff is dreadful. havent used corba for years though
| [Monday 21 March 2011] [16:49:37] <yrashk>	but sometimes it closes it while send() is still working
| [Monday 21 March 2011] [16:49:41] <yrashk>	and send() locks
| [Monday 21 March 2011] [16:49:48] <yrashk>	even though it's in NOBLOCK
| [Monday 21 March 2011] [16:49:58] <yrashk>	or should I just upgrade to dev master?
| [Monday 21 March 2011] [16:50:06] <flexo_>	jond: i agree that it could be improved in some areas... i am just saying i prefer it over json :)
| [Monday 21 March 2011] [16:50:27] <jond>	flexo have you seen BSON?
| [Monday 21 March 2011] [16:50:27] <pieterh>	yrashk: that commit is in development master
| [Monday 21 March 2011] [16:50:49] <yrashk>	but are you aware of this issue I described? or whether it is an issue at all?
| [Monday 21 March 2011] [16:51:06] <pieterh>	not aware of the issue
| [Monday 21 March 2011] [16:51:22] <pieterh>	you distracted me by posting a long UUID
| [Monday 21 March 2011] [16:52:04] <pieterh>	yrashk: if you can log an issue, that'd be good, it sounds like an edge case
| [Monday 21 March 2011] [16:52:08] <flexo_>	jond: looking at it right now... what immediatly caught my attention... no unsigned integers?
| [Monday 21 March 2011] [16:52:22] <yrashk>	I am still experimenting
| [Monday 21 March 2011] [16:52:24] <bpl29>	creme: I'm not quite sure where that binary is.  Do you think it could be i386?  I can search more.
| [Monday 21 March 2011] [16:52:32] <jond>	flexo: always thought it would be nice to rip the structs / types part of idl out to use as message format generator, leaving all the interface stuff behind, idl looks so much better than an xml or some schema
| [Monday 21 March 2011] [16:52:40] <bpl29>	creme: ocamlmklib, that is
| [Monday 21 March 2011] [16:52:55] <flexo_>	jond: oh yea.
| [Monday 21 March 2011] [16:53:16] <flexo_>	especially if the IDL happens to look almost exactly the same in the language you are developing in... :)
| [Monday 21 March 2011] [16:54:01] <flexo_>	(but even if it doesnt fit... i like our python testcases, using omniorbpy)
| [Monday 21 March 2011] [16:54:48] <flexo_>	there are some nice really nice things about CORBA, the mean problem is that its one huge "solution", not a set of solutions layered on-top of each other
| [Monday 21 March 2011] [16:54:52] <cremes>	bpl29: i'm not really sure what you are doing
| [Monday 21 March 2011] [16:54:53] <jond>	flexo : yep, but remember that python corba binding in omniorb almost makes corba bearable, so much easier than the c++
| [Monday 21 March 2011] [16:54:54] <flexo_>	*main
| [Monday 21 March 2011] [16:55:03] <flexo_>	jond: true...
| [Monday 21 March 2011] [16:55:09] <cremes>	bpl29: are you running the examples using the ocaml bindings?
| [Monday 21 March 2011] [16:55:20] <flexo_>	(the ICE mappings look like nice by the way)
| [Monday 21 March 2011] [16:55:44] <bpl29>	cremes: I am writing new OCaml bindings.
| [Monday 21 March 2011] [16:56:12] <cremes>	bpl29: ok; how do you execute your ocaml runtime?
| [Monday 21 March 2011] [16:56:36] <flexo_>	sigh. but project management will never let me deviate from the "industry standard" CORBA.... :)
| [Monday 21 March 2011] [16:57:16] <jond>	flexo: well henning was pretty damning in the end and thought he could better, even thought CDR was no better than XDR and the Zero Ice would be the way to go. Last time I looked Vinoski had discovered erlang
| [Monday 21 March 2011] [16:57:36] <bpl29>	cremes: the command in question is "ocamlmklib -o _wrapper_stubs wrapper.o -L/usr/local/lib -lzmq"
| [Monday 21 March 2011] [16:57:47] <flexo_>	hehe
| [Monday 21 March 2011] [16:58:04] <cremes>	bpl29: ok; type "which ocamlmklib" and it will tell you where that program is in your PATH
| [Monday 21 March 2011] [16:58:08] <cremes>	then run "file" on it
| [Monday 21 March 2011] [16:58:25] <bpl29>	cremes: thanks.  I knew it was something so simple.
| [Monday 21 March 2011] [16:58:59] <jond>	flexo: where I am we use XDR and our own message defn language generating all the marshall/unmarshall classes. No corba
| [Monday 21 March 2011] [16:59:45] <flexo_>	jond: yea.. could have been done for our project too... but as i said.. "industry standard" :)
| [Monday 21 March 2011] [17:00:02] <flexo_>	(the department i am working for still has some 200mhz SGI boxes where they actually develop for)
| [Monday 21 March 2011] [17:00:16] <bpl29>	cremes: "/usr/local/bin/ocamlmktop: POSIX shell script text executable"
| [Monday 21 March 2011] [17:00:29] <bpl29>	cremes: I think that's not what I'm looking for
| [Monday 21 March 2011] [17:00:33] <cremes>	bpl29: umm... you are going to have to do some digging
| [Monday 21 March 2011] [17:00:44] <bpl29>	cremes: the bash script just calls ocamlc, so I'll go file that
| [Monday 21 March 2011] [17:00:54] <cremes>	that script must be calling some binary that is trying to link a 32-bit binary against the 64-bit 0mq lib
| [Monday 21 March 2011] [17:01:17] <jond>	flexo: that's corporate life....
| [Monday 21 March 2011] [17:01:21] <flexo_>	yep
| [Monday 21 March 2011] [17:01:28] <flexo_>	OTOH this is the reason i know some MIPS assembly :)
| [Monday 21 March 2011] [17:01:36] <cremes>	bpl29: you might need to pass some flags when linking your ocaml code so that it makes everything 64-bit
| [Monday 21 March 2011] [17:01:41] <bpl29>	cremes:  Okay, thanks Cremes.  I think I can do something with that.  You've been a big help to me, and you also helped me yesterday, so thank you very much.
| [Monday 21 March 2011] [17:01:52] <yrashk>	still can reproduce on master
| [Monday 21 March 2011] [17:01:54] <flexo_>	(i maintain a very small library which runs on said boxes... had to debug it there once :)
| [Monday 21 March 2011] [17:01:55] <yrashk>	hmmm
| [Monday 21 March 2011] [17:02:03] <cremes>	bpl29: ok; at this point, you'll need to jump into the ocaml channel and ask them for some help :)
| [Monday 21 March 2011] [17:02:12] <yrashk>	but only on my slower laptop, not mac pro
| [Monday 21 March 2011] [17:02:13] <yrashk>	heh
| [Monday 21 March 2011] [17:02:21] <bpl29>	cremes: That's a good idea.  I'll do that then.  Thanks again.
| [Monday 21 March 2011] [17:02:30] <flexo_>	the dept. is getting into trouble because its getting harder and harder to get replacement parts for these boxes :)
| [Monday 21 March 2011] [17:02:57] <flexo_>	the funny thing about the harddisks is that if the power goes out and they cool down about 1/3 of them dies
| [Monday 21 March 2011] [17:03:05] <flexo_>	so the boxes must be online all the time
| [Monday 21 March 2011] [17:03:48] <flexo_>	and i really enjoy taking interns into that room
| [Monday 21 March 2011] [17:05:23] <flexo_>	they dont quite believe it otherwise :)
| [Monday 21 March 2011] [17:06:04] <flexo_>	the number of people who know how to administer them grows shorter every year too
| [Monday 21 March 2011] [17:06:06] <cremes>	i just added one of my wish-list items to the 0mq 3.0 roadmap wiki page
| [Monday 21 March 2011] [17:06:15] <flexo_>	sheesh. where am i working :)
| [Monday 21 March 2011] [17:07:52] <pieterh>	cremes: a page is like... 60 lines of 80 chars?
| [Monday 21 March 2011] [17:08:21] <cremes>	pieterh: a page is usually some multiple of 512 bytes, like 4k on linux
| [Monday 21 March 2011] [17:09:06] <pieterh>	so, almost 60 x 80 like I thought :-)
| [Monday 21 March 2011] [17:09:21] <cremes>	almost
| [Monday 21 March 2011] [17:09:23] <cremes>	heh
| [Monday 21 March 2011] [17:10:03] <pieterh>	nice change request, but you may have to submit the patch yourself
| [Monday 21 March 2011] [17:10:13] <cremes>	pieterh: understood
| [Monday 21 March 2011] [17:31:49] <Guthur>	hehe, I love how CORBA was defined by OMG
| [Monday 21 March 2011] [17:32:06] <Guthur>	I have this strange feeling it is very fitting]
| [Monday 21 March 2011] [17:50:57] <mikko>	drbobbeaty: i got a patch that disables shared library building on openpgm side
| [Monday 21 March 2011] [17:51:05] <mikko>	i will chat with steven about it and see what he things
| [Monday 21 March 2011] [17:51:08] <mikko>	thinks*
| [Monday 21 March 2011] [17:52:42] <drbobbeaty>	mikko: thanks, but I found the problem. You didn't see it because etho0 is OK for you, but on my Ubuntu box, they bonded the NICs so I could use eth0, I had to use bond0.
| [Monday 21 March 2011] [17:52:53] <drbobbeaty>	tricky admins.
| [Monday 21 March 2011] [17:53:00] <pieterh>	drbobbeaty: heh, and this worked with 2.1.2?
| [Monday 21 March 2011] [17:53:17] <drbobbeaty>	It worked when I HAD 2.1.2 - they did it in the last week.
| [Monday 21 March 2011] [17:54:18] <pieterh>	drbobbeaty, ah, just retesting 2.1.2 would have saved us all some time
| [Monday 21 March 2011] [17:55:40] <drbobbeaty>	Yeah, that was my fault, and I'm really sorry about that. It just didn't cross my mind because it was working.
| [Monday 21 March 2011] [17:56:25] <pieterh>	glad pgm is working, anyhow
| [Monday 21 March 2011] [18:00:54] <mikko>	drbobbeaty, pieterh good!
| [Monday 21 March 2011] [18:01:12] <mikko>	in any case i worked up solutions on zeromq and libpgm side to prevent the confusing libpgm.so install
| [Monday 21 March 2011] [18:01:18] <mikko>	pieterh: you are CCd on mail to steven
| [Monday 21 March 2011] [18:01:26] <mikko>	let's see what he thinks
| [Monday 21 March 2011] [18:01:31] <pieterh>	mikko: reading it now...
| [Monday 21 March 2011] [18:01:32] <drbobbeaty>	Thanks, mikko... I think it'll be a very good thing to have.
| [Monday 21 March 2011] [18:02:37] <pieterh>	mikko: I'd guess not installing the libpgm.so is best
| [Monday 21 March 2011] [18:04:08] <mikko>	yeah
| [Monday 21 March 2011] [18:04:16] <mikko>	would be the best if steven agrees with the patch
| [Monday 21 March 2011] [18:06:46] <mikko>	productive day
| [Monday 21 March 2011] [18:07:05] <pieterh>	yeah, I've almost finished the clone pattern
| [Monday 21 March 2011] [18:07:26] <pieterh>	*and* I took the kids to the park
| [Monday 21 March 2011] [18:07:28] <pieterh>	great day
| [Monday 21 March 2011] [18:11:10] <Guthur>	would exposing the connected IPs to a 0MQ be possible
| [Monday 21 March 2011] [18:11:20] <pieterh>	Guthur: doubt it
| [Monday 21 March 2011] [18:13:03] <Guthur>	shame, I was just thinking in terms of a FIX engine, one of the recommend authentication procedures was to match IPs to companies
| [Monday 21 March 2011] [18:13:28] <Guthur>	obviously spoofing is possible, which the whitepaper also mentions
| [Monday 21 March 2011] [18:13:29] <pieterh>	it's been discussed before
| [Monday 21 March 2011] [18:13:36] <Guthur>	oh
| [Monday 21 March 2011] [18:14:00] <pieterh>	one might have a pluggable authentication layer that sits above the transport
| [Monday 21 March 2011] [18:14:24] <pieterh>	this would be necessary for any public-facing 0MQ server IMO
| [Monday 21 March 2011] [18:14:47] <pieterh>	though people have argued stuff like banning bogus clients is a firewall issue
| [Monday 21 March 2011] [18:15:39] <Guthur>	security is always should a head pickle
| [Monday 21 March 2011] [18:16:06] <pieterh>	indeed... :-)
| [Monday 21 March 2011] [18:16:57] <Guthur>	Better I at least making a passing effort to understand the options now though
| [Monday 21 March 2011] [18:17:21] <pieterh>	if you take 0MQ today, rather than some possible future version
| [Monday 21 March 2011] [18:17:35] <pieterh>	then validation must be done explicitly using authentication
| [Monday 21 March 2011] [18:18:10] <pieterh>	alternatively you can make a TCP front-end that speaks FIX to the world, and 0MQ to the internal network
| [Monday 21 March 2011] [18:18:28] <Guthur>	that was a feature I would like
| [Monday 21 March 2011] [18:18:40] <Guthur>	I was going to build the 0MQ version first though
| [Monday 21 March 2011] [18:18:40] <pieterh>	it's a fairly simple app, if you have FIX libraries
| [Monday 21 March 2011] [18:18:55] <Guthur>	then add the bridge to TCP later
| [Monday 21 March 2011] [18:19:15] <Guthur>	I was going to take QuickFIXs message parsing for now
| [Monday 21 March 2011] [18:19:38] <Guthur>	and replace the engine with 0MQ
| [Monday 21 March 2011] [18:19:42] <pieterh>	if you asked me, I'd make the bridge first
| [Monday 21 March 2011] [18:20:03] <pieterh>	use QuickFIX parsing over TCP at one side, 0MQ at the other side
| [Monday 21 March 2011] [18:23:10] <Guthur>	probably the more sensible approach
| [Monday 21 March 2011] [18:23:45] <Guthur>	I was just really eager to build a big 0MQ system, hehe
| [Monday 21 March 2011] [18:28:14] <pieterh>	btw, an open source FIX-to-0MQ bridge would be very useful for Whaleshark
| [Monday 21 March 2011] [18:32:59] <Guthur>	the question in my mind is how much functionality to put in the bridge
| [Monday 21 March 2011] [18:33:27] <pieterh>	filtering and extraction
| [Monday 21 March 2011] [18:33:45] <pieterh>	so that you chop the message flow down as far as possible
| [Monday 21 March 2011] [18:33:49] <pieterh>	without doing too much CPU intensive work
| [Monday 21 March 2011] [18:34:01] <pieterh>	IMHO
| [Monday 21 March 2011] [18:34:29] <Guthur>	well the easy one is splitting the admin and app message
| [Monday 21 March 2011] [18:34:37] <Guthur>	messages*#
| [Monday 21 March 2011] [18:35:39] <Guthur>	would a bridge offer a place to add encryption/decryption
| [Monday 21 March 2011] [18:36:04] <pieterh>	probably not, unless you can offload that work
| [Monday 21 March 2011] [18:37:11] <Guthur>	so add the basic level possibly filter admin/app messages, and verify checksums
| [Monday 21 March 2011] [18:37:16] <Guthur>	add/at
| [Monday 21 March 2011] [18:37:37] <pieterh>	it depends really on the volumes you're dealing with and your hardware
| [Monday 21 March 2011] [18:37:50] <pieterh>	you want to get the machines working hard enough but not stressed
| [Monday 21 March 2011] [18:38:12] <pieterh>	otherwise you're going to get latency spikes when there's a lot of data
| [Monday 21 March 2011] [18:38:26] <Guthur>	FIX engines can be running on some pretty hefty hardware
| [Monday 21 March 2011] [18:38:54] <Guthur>	the bank I work for is now serving up all their FX pricing on a FIX engine
| [Monday 21 March 2011] [18:39:06] <pieterh>	you work for a bank...
| [Monday 21 March 2011] [18:39:13] <Guthur>	and now even clients are asking for it to be exposed them
| [Monday 21 March 2011] [18:39:16] <Guthur>	pieterh, yep
| [Monday 21 March 2011] [18:39:16] 	 * pieterh ends the free consulting
| [Monday 21 March 2011] [18:39:21] <Guthur>	lol
| [Monday 21 March 2011] [18:39:28] 	 * pieterh doubles his rates
| [Monday 21 March 2011] [18:39:47] <Guthur>	if only I was writing the cheques
| [Monday 21 March 2011] [18:40:15] <Guthur>	in truth though this is a personal project
| [Monday 21 March 2011] [18:40:37] <pieterh>	an open source FIX-to-0MQ bridge would be neat
| [Monday 21 March 2011] [18:41:25] <Guthur>	yep, it's my goal to have this stuff open source
| [Monday 21 March 2011] [18:41:38] <Guthur>	if I can build it properly
| [Monday 21 March 2011] [18:41:55] <mikko>	pieterh: sent you some stuff again
| [Monday 21 March 2011] [18:41:56] <pieterh>	make it open source first, then you'll be sure to build it properly
| [Monday 21 March 2011] [18:42:09] <mikko>	don't read it before morning, it's work related
| [Monday 21 March 2011] [18:42:23] <mikko>	build the community first, good products will follow
| [Monday 21 March 2011] [18:42:37] <mikko>	said some mozilla guy
| [Monday 21 March 2011] [18:42:41] <pieterh>	mikko: I'm supposed to *sleep* knowing there's an unread mail from you?
| [Monday 21 March 2011] [18:42:44] <pieterh>	unpossible
| [Monday 21 March 2011] [18:43:17] <mikko>	heh, im gonna sleep now. another long day ahead
| [Monday 21 March 2011] [18:43:18] <mikko>	night
| [Monday 21 March 2011] [19:00:36] <pieterh>	anyone here using 0MQ from C?
| [Monday 21 March 2011] [19:07:13] <Guthur>	when something does not work I now use it for a sanity check
| [Monday 21 March 2011] [19:07:19] <Guthur>	but i don't think that really counts
| [Monday 21 March 2011] [19:18:44] <pieterh>	I've sketched out a proposal for a high-level C binding
| [Monday 21 March 2011] [19:18:53] <pieterh>	http://www.zeromq.org/bindings:c
| [Monday 21 March 2011] [19:21:35] <pieterh>	well, g'nite everyone...
| [Monday 21 March 2011] [19:32:45] <Guthur>	g'night pieterh 
| [Monday 21 March 2011] [21:02:11] <reiddraper>	I'm seeing ~4K requests/second for a REQ-REP socket with two python processes. The are sending "hello". Is this performance expected?
| [Monday 21 March 2011] [21:04:28] <jhawk28>	not sure about python, but it usually depends
| [Monday 21 March 2011] [21:04:50] <jhawk28>	on the network, the computing platform, and the language bindings
| [Monday 21 March 2011] [21:05:22] <reiddraper>	jhawk28: localhost, ubuntu
| [Monday 21 March 2011] [21:06:01] <reiddraper>	jhawk28: suppose I was expecting it to be an order of magnitude faster
| [Monday 21 March 2011] [21:06:27] <jhawk28>	are you just req: Hello and Rep: hello?
| [Monday 21 March 2011] [21:06:40] <reiddraper>	yes
| [Monday 21 March 2011] [21:07:25] <reiddraper>	zeromq 2.1.3
| [Monday 21 March 2011] [21:07:41] <jhawk28>	let me do a quick one in Java
| [Monday 21 March 2011] [21:07:52] <reiddraper>	same performance with ipc and tcp
| [Monday 21 March 2011] [21:08:13] <reiddraper>	jhawk28: thanks
| [Monday 21 March 2011] [21:21:17] <andrewvc>	cremes: around?
| [Monday 21 March 2011] [21:21:29] <andrewvc>	cremes: Wondering if you'd mind me releasing 0.7.3 w/ zdevice support
| [Monday 21 March 2011] [21:23:52] <jhawk28>	reiddraper: I'm getting about 10k/s
| [Monday 21 March 2011] [21:25:30] <reiddraper>	jhawk28: ok, seems reasonable that python would be 4K then
| [Monday 21 March 2011] [21:26:51] <jhawk28>	thats Java with 2.1.3 on a 2.4 Core i5 (OSX)
| [Monday 21 March 2011] [21:30:01] <jhawk28>	reiddraper: push/pull gets 2mil/s
| [Monday 21 March 2011] [21:30:37] <reiddraper>	jhawk28: pretty big difference
| [Monday 21 March 2011] [21:31:40] <reiddraper>	only really surprised because I've seen http servers do more req/s than what I'm seeing
| [Monday 21 March 2011] [21:33:10] <jhawk28>	req/rep is synchronous
| [Monday 21 March 2011] [21:33:20] <jhawk28>	single threaded both sides
| [Monday 21 March 2011] [21:34:44] <reiddraper>	yeah, figured it would have to be, that being said, so is something like Redis, which gets 10's of thousands of operations / second, over tcp
| [Monday 21 March 2011] [21:34:53] <reiddraper>	req-rep
| [Monday 21 March 2011] [21:47:17] <jhawk28>	reiddraper: increase the number of clients
| [Monday 21 March 2011] [21:48:30] <jhawk28>	when I bump up the number of clients, I am getting 25k/sec
| [Monday 21 March 2011] [21:49:56] <reiddraper>	jhawk28: Cool, and to be honest, for what I have in mind, 4k/sec is plenty fast
| [Monday 21 March 2011] [21:51:15] <jhawk28>	I could probably scale it more if I used XREP
| [Monday 21 March 2011] [21:52:16] <jhawk28>	and actually split it between machines
| [Monday 21 March 2011] [21:55:20] <reiddraper>	jhawk28: can you explain the difference betwen xreq/rep and req/rep?
| [Monday 21 March 2011] [21:56:02] <jhawk28>	req/rep is syncronous, xreq/xrep uses identities
| [Monday 21 March 2011] [21:56:48] <reiddraper>	ah, OK
| [Monday 21 March 2011] [21:56:56] <jhawk28>	the identities are then used by zmq to route the response back to the correct socket
| [Monday 21 March 2011] [21:58:07] <jhawk28>	thats as much as I know
| [Monday 21 March 2011] [21:58:16] <jhawk28>	I haven't used them much
| [Monday 21 March 2011] [21:58:27] <jhawk28>	its on my todo list...
| [Monday 21 March 2011] [22:00:08] <reiddraper>	jhawk28: ok, so you don't get slowed down by slowest client that is load-balanced
| [Monday 21 March 2011] [22:01:15] <jhawk28>	or worker
| [Monday 21 March 2011] [22:01:40] <jhawk28>	thats what xreq is for (for dealing out work)
| [Monday 21 March 2011] [22:04:14] <reiddraper>	ok, so for a queue broker, the clients sending xreq (give me a task), and the broker sending xrep (do this) makes sense?
| [Monday 21 March 2011] [22:07:41] <jhawk28>	Chapter 3 does a good job explaining it: http://zguide.zeromq.org/page:all#toc45
| [Monday 21 March 2011] [22:08:15] <reiddraper>	jhawk28: awesome. thanks
| [Monday 21 March 2011] [22:16:11] <believa>	newb question - are the following statements true? You cannot "bind" multiple sockets to the same endpoint. You "can" connect multiple sockets to the same endpoint. A socket can "bind" and/or "connect" to multiple endpoints.
| [Monday 21 March 2011] [22:18:58] <jhawk28>	Yes, yes
| [Monday 21 March 2011] [22:19:16] <jhawk28>	yes
| [Monday 21 March 2011] [22:19:21] <believa>	jhawk28: thanks for the confirmation
| [Monday 21 March 2011] [22:20:46] <neopallium>	believa: you can bind one socket to multiple different endpoints, but you can't bind multiple sockets to the same endpoint.
| [Monday 21 March 2011] [22:21:13] <believa>	neopallium: gotcha
| [Monday 21 March 2011] [22:21:15] <neopallium>	just like you can't bind multiple tcp sockets to the same port on the same computer.
| [Monday 21 March 2011] [22:22:29] <believa>	neopallium: that should result in EADDRINUSE right?
| [Monday 21 March 2011] [22:30:20] <neopallium>	believa: yes
| [Monday 21 March 2011] [22:30:35] <believa>	neopallium: thanks
| [Tuesday 22 March 2011] [03:47:12] <sustrik>	reiddrapper: req/rep is lock-step; the performance is determined by the latency of your network
| [Tuesday 22 March 2011] [03:47:32] <sustrik>	the actual messaging fabric is almost irrelevant
| [Tuesday 22 March 2011] [04:09:14] <pieterh>	good morning
| [Tuesday 22 March 2011] [04:10:23] <pieterh>	sustrik: we had this question twice in a day, perhaps worth some explanation in the guide
| [Tuesday 22 March 2011] [04:12:06] <sustrik>	yes, that would be good
| [Tuesday 22 March 2011] [04:12:11] <sustrik>	alternatively
| [Tuesday 22 March 2011] [04:12:17] <sustrik>	there's a page about rinning perf tests
| [Tuesday 22 March 2011] [04:12:21] <sustrik>	let me see
| [Tuesday 22 March 2011] [04:12:40] <pieterh>	perhaps an explicit page we can refer to upfront, yes
| [Tuesday 22 March 2011] [04:12:54] <pieterh>	e.g. expected throughput and latency of each pattern
| [Tuesday 22 March 2011] [04:13:05] <pieterh>	very rough, but to set expectations properly
| [Tuesday 22 March 2011] [04:14:23] <sustrik>	http://www.zeromq.org/results:perf-howto
| [Tuesday 22 March 2011] [04:20:18] <pieterh>	sustrik: it's not very useful to beginners IMO
| [Tuesday 22 March 2011] [04:21:25] <pieterh>	I'll think about how to explain this, it's got to be in terms of limits, capacity, speed of different patterns & transports
| [Tuesday 22 March 2011] [04:21:35] <pieterh>	like a spec sheet
| [Tuesday 22 March 2011] [04:21:40] <sustrik>	let me send you a diagram
| [Tuesday 22 March 2011] [04:22:17] <pieterh>	sure
| [Tuesday 22 March 2011] [04:39:19] <pieterh>	sustrik: random idea for cleaner semantics on multipart messages
| [Tuesday 22 March 2011] [04:39:36] <pieterh>	make the MORE bit a property of a frame (zmq_msg_t) rather than a socket
| [Tuesday 22 March 2011] [04:40:03] <sustrik>	that's how it works on wire level
| [Tuesday 22 March 2011] [04:40:11] <pieterh>	it would also make more sense at the API level IMO
| [Tuesday 22 March 2011] [04:40:12] <sustrik>	with API it's a pain to use
| [Tuesday 22 March 2011] [04:40:26] <sustrik>	i though of combining the two approaches
| [Tuesday 22 March 2011] [04:40:30] <pieterh>	it means I can prepare a frame and write it with a generic method
| [Tuesday 22 March 2011] [04:40:41] <sustrik>	yes
| [Tuesday 22 March 2011] [04:40:58] <pieterh>	if you consider zmq_msg_t as a 'smart blob' (and I like this), then it should have a more property
| [Tuesday 22 March 2011] [04:41:10] <sustrik>	the problem is this:
| [Tuesday 22 March 2011] [04:41:27] <sustrik>	zmq_send (msg, MSG_SNDMORE);
| [Tuesday 22 March 2011] [04:41:27] <sustrik>	vs.
| [Tuesday 22 March 2011] [04:41:47] <sustrik>	zmq_msg_setflag (msg, ZMQ_MORE, 1);
| [Tuesday 22 March 2011] [04:41:51] <pieterh>	you can always do both
| [Tuesday 22 March 2011] [04:41:53] <sustrik>	zmq_send (msg, 0);
| [Tuesday 22 March 2011] [04:41:58] <sustrik>	yes
| [Tuesday 22 March 2011] [04:42:19] <pieterh>	I see the zmq_send (..., MSG_SENDMORE) as either an optimization or an override
| [Tuesday 22 March 2011] [04:42:26] <sustrik>	yes
| [Tuesday 22 March 2011] [04:42:32] <sustrik>	convenience feature
| [Tuesday 22 March 2011] [04:42:45] <pieterh>	e.g. if I have an identity frame, and want to send it, it's always going to be MORE
| [Tuesday 22 March 2011] [04:43:04] <pieterh>	read / write then become symmetric
| [Tuesday 22 March 2011] [04:43:04] <sustrik>	yes, it would simplify devices
| [Tuesday 22 March 2011] [04:43:07] <pieterh>	yes
| [Tuesday 22 March 2011] [04:43:20] <pieterh>	indeed, any generic handling of multipart messages becomes cleaner
| [Tuesday 22 March 2011] [04:43:30] <sustrik>	ack
| [Tuesday 22 March 2011] [04:43:38] <pieterh>	another question, is it necessary to destroy a message after sending it?
| [Tuesday 22 March 2011] [04:43:50] <pieterh>	sending the same frame N times is rather clumsy today
| [Tuesday 22 March 2011] [04:43:53] <sustrik>	it you don't nothing happens
| [Tuesday 22 March 2011] [04:44:13] <sustrik>	but it's safer to do so for forward compatibility
| [Tuesday 22 March 2011] [04:44:23] <pieterh>	ah, you mean _close is optional
| [Tuesday 22 March 2011] [04:44:29] <sustrik>	nope
| [Tuesday 22 March 2011] [04:44:46] <sustrik>	technically, closing empty message translates to noop
| [Tuesday 22 March 2011] [04:45:03] <sustrik>	however, that is not guaranteed to hold in future versions of 0mq
| [Tuesday 22 March 2011] [04:45:31] <sustrik>	so, preferable, close the messages so that 0mq can hook into message destruction process
| [Tuesday 22 March 2011] [04:45:41] <sustrik>	preferably*
| [Tuesday 22 March 2011] [04:46:01] <pieterh>	To send a message twice I need to:
| [Tuesday 22 March 2011] [04:46:02] <pieterh>	zmq_msg_t copy;
| [Tuesday 22 March 2011] [04:46:03] <pieterh>	zmq_msg_init (&copy);
| [Tuesday 22 March 2011] [04:46:03] <pieterh>	zmq_msg_copy (&copy, &original);
| [Tuesday 22 March 2011] [04:46:03] <pieterh>	zmq_send (socket, &copy, 0);
| [Tuesday 22 March 2011] [04:46:03] <pieterh>	zmq_msg_close (&copy);
| [Tuesday 22 March 2011] [04:46:13] <sustrik>	yes
| [Tuesday 22 March 2011] [04:46:39] <sustrik>	well, you should close the original as well
| [Tuesday 22 March 2011] [04:46:39] <pieterh>	so my question is whether it's necessary for 0MQ to destroy the message after sending
| [Tuesday 22 March 2011] [04:46:43] <sustrik>	unless you are going to use it
| [Tuesday 22 March 2011] [04:46:49] <sustrik>	not now
| [Tuesday 22 March 2011] [04:46:55] <sustrik>	may be necessary in future
| [Tuesday 22 March 2011] [04:47:04] <pieterh>	could I have a flag saying, "don't nullify after sending"?
| [Tuesday 22 March 2011] [04:47:13] <pieterh>	MSG_REUSE
| [Tuesday 22 March 2011] [04:47:29] <sustrik>	ah, a convenience feature
| [Tuesday 22 March 2011] [04:47:41] <sustrik>	you can have that, but you should be aware it's slow
| [Tuesday 22 March 2011] [04:47:53] <pieterh>	slower than creating copies each time?
| [Tuesday 22 March 2011] [04:47:54] <pieterh>	how so?
| [Tuesday 22 March 2011] [04:47:59] <sustrik>	there's refernce counting going on there
| [Tuesday 22 March 2011] [04:48:05] <sustrik>	which is implemented using atomic ops
| [Tuesday 22 March 2011] [04:48:19] <sustrik>	which in turn means the memory bus is locked each time you do so
| [Tuesday 22 March 2011] [04:48:37] <pieterh>	yes, but I'm copying the message each time now
| [Tuesday 22 March 2011] [04:48:43] <pieterh>	that also locks the memory bus each time
| [Tuesday 22 March 2011] [04:48:48] <sustrik>	yes, we can add the convenience flag
| [Tuesday 22 March 2011] [04:49:07] <sustrik>	nope, copying doesn't lock the bus
| [Tuesday 22 March 2011] [04:49:24] <sustrik>	well, unless there's contention between CPU cores on that particular cacheline
| [Tuesday 22 March 2011] [04:49:33] <pieterh>	well, copying also uses atomic ops for reference counting
| [Tuesday 22 March 2011] [04:49:51] <sustrik>	ah, you mean zmq_msg_copy
| [Tuesday 22 March 2011] [04:49:53] <sustrik>	yes
| [Tuesday 22 March 2011] [04:49:59] <sustrik>	so yes, we can add the flag
| [Tuesday 22 March 2011] [04:50:07] <pieterh>	yes, there's no other way to send the same frame twice
| [Tuesday 22 March 2011] [04:50:17] <sustrik>	what i'm saying is that it should not be the default
| [Tuesday 22 March 2011] [04:50:17] <pieterh>	aight...
| [Tuesday 22 March 2011] [04:50:22] <pieterh>	ah, certainly
| [Tuesday 22 March 2011] [04:51:00] 	 * pieterh peeks at the code...
| [Tuesday 22 March 2011] [04:52:18] <pieterh>	well, I'll add this to the 3.0 page but I have no idea how to make it :-)
| [Tuesday 22 March 2011] [04:52:25] <pieterh>	it would be useful, though IMO
| [Tuesday 22 March 2011] [04:53:54] <sustrik>	it's backward compatible, so no need to solve it immediately
| [Tuesday 22 March 2011] [04:54:12] <sustrik>	the backward incompatible changes are what's in focus now
| [Tuesday 22 March 2011] [04:54:28] <sustrik>	they have to be done in a single go, if possible
| [Tuesday 22 March 2011] [04:54:33] <sustrik>	to minimise the pain
| [Tuesday 22 March 2011] [04:54:53] <sustrik>	the remaining functionality can be added gradually afterwards
| [Tuesday 22 March 2011] [04:58:29] <pieterh>	I'm not sure the changes will be as painful as you imagine
| [Tuesday 22 March 2011] [04:58:55] <sustrik>	dunno, but minimising the pain is a good thing in itself
| [Tuesday 22 March 2011] [04:59:10] <pieterh>	yes, at least doing it all in one go
| [Tuesday 22 March 2011] [06:59:40] <pieterh>	sustrik: I've built the basic API for the high-level C binding, at https://github.com/zeromq/zapi
| [Tuesday 22 March 2011] [06:59:51] <pieterh>	will fill in the pieces over the next few days
| [Tuesday 22 March 2011] [07:01:10] <drbobbeaty>	pieterh: if the C level binding is separate in 3.x, is the C++ binding as well? Are they different bindings? What comes "standard" with the ZMQ libraries? Any 'default' API?
| [Tuesday 22 March 2011] [07:01:25] <pieterh>	drbobbeaty: yes, we plan to split off the C++ binding as well
| [Tuesday 22 March 2011] [07:01:33] <pieterh>	the default API is the Core C API
| [Tuesday 22 March 2011] [07:02:09] <pieterh>	the new C binding will work over 2.x as well as 3.x
| [Tuesday 22 March 2011] [07:02:42] <drbobbeaty>	Ah! I see the advantage to having the separate binding now - bridge the versions. Nice plan.
| [Tuesday 22 March 2011] [07:03:03] <pieterh>	also it makes it much easier to add useful functionality without breaking other language bindings
| [Tuesday 22 March 2011] [07:03:18] <pieterh>	so we can e.g. write a C reactor without affecting the core
| [Tuesday 22 March 2011] [07:18:47] <Guthur>	pieterh: I think I'll draw some inspiration from the new C binding
| [Tuesday 22 March 2011] [07:19:09] <pieterh>	Guthur: could be fun, I've tried to use a class-oriented approach for most of it
| [Tuesday 22 March 2011] [07:20:26] <pieterh>	I'll be converting the Guide examples to zapi when it's ready
| [Tuesday 22 March 2011] [07:20:40] <pieterh>	so if the C++ binding is anything like that, it'll be a lot easier for those examples too
| [Tuesday 22 March 2011] [07:21:14] <pieterh>	Guthur: when you need a repository created in the zeromq organization, give me a shout
| [Tuesday 22 March 2011] [07:21:16] <Guthur>	C# you mean, hehe
| [Tuesday 22 March 2011] [07:21:21] <pieterh>	oh, sorry
| [Tuesday 22 March 2011] [07:21:23] <pieterh>	C#
| [Tuesday 22 March 2011] [07:21:29] 	 * pieterh was getting all confused
| [Tuesday 22 March 2011] [07:21:48] 	 * pieterh searches for the 'edit' button... 
| [Tuesday 22 March 2011] [07:24:16] <Guthur>	When 0MQ 3.0 API is finalized I'm going to develop a new branch for clrzmq2
| [Tuesday 22 March 2011] [07:24:46] <Guthur>	I have a far better idea now what works and what doesn't
| [Tuesday 22 March 2011] [07:25:02] <pieterh>	please don't call it clrzmq3 :-)
| [Tuesday 22 March 2011] [07:25:23] <Guthur>	yeah I'll resist that temptation
| [Tuesday 22 March 2011] [07:25:47] <Guthur>	It will just be a branch of clrzmq2
| [Tuesday 22 March 2011] [07:26:00] <pieterh>	though ... embracing the chaos... it could be useful
| [Tuesday 22 March 2011] [07:26:07] <pieterh>	if binding versions track the development version
| [Tuesday 22 March 2011] [07:26:19] <pieterh>	so people know that clrzmq3 supports 3.x and 2.x
| [Tuesday 22 March 2011] [07:26:26] <Guthur>	the assembly will be version 3.x
| [Tuesday 22 March 2011] [07:26:49] <Guthur>	the assembly is currently 2.1.x
| [Tuesday 22 March 2011] [07:26:58] <pieterh>	problem is that the version number is in the github repo name
| [Tuesday 22 March 2011] [07:27:05] <Guthur>	true
| [Tuesday 22 March 2011] [07:27:11] <pieterh>	we have the same problem with zeromq2
| [Tuesday 22 March 2011] [07:28:00] <Guthur>	not an easy decision to be honest
| [Tuesday 22 March 2011] [07:28:15] <Guthur>	I really don't want to confuse potential/current users
| [Tuesday 22 March 2011] [07:30:50] <Guthur>	pieterh: can you briefly explain you reactor pattern thing in the C binding
| [Tuesday 22 March 2011] [07:31:16] <pieterh>	Guthur: to be honest I've never used a reactor pattern so this is kind of a guess
| [Tuesday 22 March 2011] [07:31:25] <pieterh>	the idea is to register the events you want to handle
| [Tuesday 22 March 2011] [07:31:34] <pieterh>	and then a tickless poll loop can handle it
| [Tuesday 22 March 2011] [07:31:38] <mikko>	howdy boys
| [Tuesday 22 March 2011] [07:31:39] <mikko>	and girls
| [Tuesday 22 March 2011] [07:31:42] <pieterh>	hey mikko!
| [Tuesday 22 March 2011] [07:31:47] <Guthur>	hi mikko 
| [Tuesday 22 March 2011] [07:31:55] <Guthur>	pieterh: what is the alarm part
| [Tuesday 22 March 2011] [07:32:17] <Guthur>	and clock
| [Tuesday 22 March 2011] [07:32:21] <pieterh>	Guthur: if you look at a realistic app like the Majordomo broker
| [Tuesday 22 March 2011] [07:32:27] <pieterh>	then it mixes socket events with timer events
| [Tuesday 22 March 2011] [07:32:36] <pieterh>	e.g. "send heartbeats every 3 seconds"
| [Tuesday 22 March 2011] [07:32:46] <pieterh>	"kill server if no response in 2500 msecs"
| [Tuesday 22 March 2011] [07:33:12] <pieterh>	I made a proper tickless poll loop in the flcliapi (freelance client)
| [Tuesday 22 March 2011] [07:33:21] <pieterh>	it calculates the next timer event and polls that long
| [Tuesday 22 March 2011] [07:33:23] <Guthur>	ok so that would be too all registered sockets
| [Tuesday 22 March 2011] [07:33:28] <pieterh>	rather than polling every second or whatever
| [Tuesday 22 March 2011] [07:33:47] <Guthur>	I haven't got as far as freelance yet
| [Tuesday 22 March 2011] [07:34:17] <pieterh>	take a brief look at the flcliapi poll loop, if you want to understand zloop
| [Tuesday 22 March 2011] [07:34:19] <Guthur>	I've just got to majordomo
| [Tuesday 22 March 2011] [07:34:22] <pieterh>	:-)
| [Tuesday 22 March 2011] [07:35:18] <pieterh>	the reactor won't work for all cases, sometimes we poll selectively
| [Tuesday 22 March 2011] [07:35:27] <pieterh>	but it should help the more complex designs
| [Tuesday 22 March 2011] [07:40:40] <Guthur>	I think I've sort of included a limited reactor pattern in clrzmq2
| [Tuesday 22 March 2011] [07:42:19] <Guthur>	but unfortunately the incremental nature of the development of the polling mechanism has left the API in a state that is less clear that I would like
| [Tuesday 22 March 2011] [07:42:42] <Guthur>	it's one of the main area's I would like to refactor
| [Tuesday 22 March 2011] [07:44:10] <Guthur>	I'd also like to simplify the send/recv
| [Tuesday 22 March 2011] [07:45:29] <pieterh>	in C# strings are just blobs, right?
| [Tuesday 22 March 2011] [07:45:55] <Guthur>	they are objects
| [Tuesday 22 March 2011] [07:46:36] <pieterh>	right
| [Tuesday 22 March 2011] [07:47:35] <Guthur>	i'd rather deal with them in an msg object as oppose to at the socket level send/recv
| [Tuesday 22 March 2011] [07:48:00] <pieterh>	the breakdown I'm using in zapi is frame vs. msg
| [Tuesday 22 March 2011] [07:48:08] <pieterh>	where frame is one part, msg is a multipart object
| [Tuesday 22 March 2011] [07:48:23] <Guthur>	I meant to ask about the framw
| [Tuesday 22 March 2011] [07:48:26] <Guthur>	frame*
| [Tuesday 22 March 2011] [07:48:44] <pieterh>	0MQ uses 'msg' to mean 'part', which is confusing
| [Tuesday 22 March 2011] [07:49:11] <Guthur>	yeah, was taking more about the multipart you describe
| [Tuesday 22 March 2011] [07:49:21] <pieterh>	perhaps I should use 'part' instead of 'frame'... anyhow
| [Tuesday 22 March 2011] [07:49:39] <pieterh>	the frame class lets you do things like 'receive the identity' and 'send the identity' with ROUTER sockets
| [Tuesday 22 March 2011] [07:50:14] <pieterh>	whereas the msg class is more like 'recv a list of frames' and 'send a list of frames'
| [Tuesday 22 March 2011] [07:51:46] <Guthur>	I was also then going to take a lazy marshalling approach, only marshalling the zeromq msg (part) to a c# data type when required, should improved performance in situations where you don't need to know about the whole message 
| [Tuesday 22 March 2011] [07:52:24] <pieterh>	that makes sense, it's what I'm doing in other places
| [Tuesday 22 March 2011] [07:52:28] <Guthur>	it's sort of all in my head at the moment though, I really should try to define the API like you have done
| [Tuesday 22 March 2011] [07:52:40] <pieterh>	yeah, start with the API, it makes everything clearer
| [Tuesday 22 March 2011] [09:03:12] <drbobbeaty>	I have a core dump with ZeroMQ 2.1.3 this morning... I have detailed it in this gist: https://gist.github.com/881176 . It includes the stack trace and the code from OpenPGM that's the last step in the trace.
| [Tuesday 22 March 2011] [09:03:49] <drbobbeaty>	It seems impossible to be true -- if the assert is causing the exception, then the value of minor_bucket has to be NULL... but it's not, as shown in the stack trace.
| [Tuesday 22 March 2011] [09:03:58] <drbobbeaty>	Is this a problem for Steve?
| [Tuesday 22 March 2011] [09:04:34] <drbobbeaty>	(I've received this on two different boxes on four separate occasions this morning)
| [Tuesday 22 March 2011] [09:06:38] <drbobbeaty>	HA! I think it's the data_size being 0!
| [Tuesday 22 March 2011] [09:06:47] <drbobbeaty>	Any ideas as to why that would be?
| [Tuesday 22 March 2011] [09:07:03] <sustrik>	drbobbeaty: you have to discuss that with steve-o
| [Tuesday 22 March 2011] [09:07:14] <sustrik>	seem to be a problem with new version of opnepgm
| [Tuesday 22 March 2011] [09:09:58] <drbobbeaty>	Steve-o: can you have a look at https://gist.github.com/881176 and give me an idea of why data_size == 0 on the call? I'm hitting the assertion and have no idea why.
| [Tuesday 22 March 2011] [09:10:20] <drbobbeaty>	pieterh: should I just hit the mailing list for steve-o?
| [Tuesday 22 March 2011] [09:10:58] <pieterh>	drbobbeaty: I'd do that, he's in Asia and probably out of the office by now
| [Tuesday 22 March 2011] [09:11:21] <pieterh>	the good news is you can get a new OpenPGM and use that with 2.1.3 without further changes
| [Tuesday 22 March 2011] [09:16:16] <Guthur>	sustrik: I see in the IPC discussion no one is actually talking about using IOCP and named pipes. I've been meaning to ask you about whether you think an abstraction layer over either Sockets & Named Pipes or IOCP itself could feasibly provide the necessary functionality to mimic what is required from poll, select etc in 0MQ
| [Tuesday 22 March 2011] [09:16:50] <Guthur>	this would all be window centric changes of course
| [Tuesday 22 March 2011] [09:22:50] <drbobbeaty>	Steve-o: if you get this, please check the mailing list... I'm getting more than two core dumps an hour with 2.1.3 due to this data_size == 0 issue. Yikes!
| [Tuesday 22 March 2011] [09:23:56] <pieterh>	drbobbeaty: sorry about this, we don't have the facilities to properly test OpenPGM yet
| [Tuesday 22 March 2011] [09:24:29] <pieterh>	I'd advise you to rollback to 2.1.2 until we get a fix to it
| [Tuesday 22 March 2011] [09:24:42] <drbobbeaty>	I understand... If I had to guess it's an edge condition where data_size == 0, and I'm just hitting it more with all the exchange feeds I'm dealing with.
| [Tuesday 22 March 2011] [09:24:51] <sustrik>	Guthur: what's being discussed is a workaround
| [Tuesday 22 March 2011] [09:25:00] <drbobbeaty>	pieterh: that's a good plan.
| [Tuesday 22 March 2011] [09:25:06] <sustrik>	something that would look like IPC but would actually be TCP
| [Tuesday 22 March 2011] [09:25:17] <pieterh>	drbobbeaty: I expect tomorrow morning Steve will have an updated OpenPGM package
| [Tuesday 22 March 2011] [09:25:17] <sustrik>	real solution is IPC & NamedPipes
| [Tuesday 22 March 2011] [09:25:46] <pieterh>	you can install it and rebuild 2.1.3, --with-openpgm=<version> or somesuch, I'm not 100% sure on that syntax
| [Tuesday 22 March 2011] [09:28:10] <Guthur>	sustrik: does the abstraction sound like a feasible objective?
| [Tuesday 22 March 2011] [09:29:52] <sustrik>	Guthur: the abstraction exists already
| [Tuesday 22 March 2011] [09:30:12] <sustrik>	check how poll_t, select_t, epoll_t etc. interface with the rest of the system
| [Tuesday 22 March 2011] [09:30:27] <sustrik>	check whether IOCP can use the same interface
| [Tuesday 22 March 2011] [09:30:35] <sustrik>	if not, propose changes
| [Tuesday 22 March 2011] [09:31:06] <Guthur>	I thought the problem was that underneath those abstractions they use functionality that IOCP does not provide
| [Tuesday 22 March 2011] [09:31:22] <Guthur>	IOCP only providing notification of completion
| [Tuesday 22 March 2011] [09:32:10] <sustrik>	right, IOCP has an additional buffer between the user and the network
| [Tuesday 22 March 2011] [09:32:14] <sustrik>	something like AIO
| [Tuesday 22 March 2011] [09:32:24] <sustrik>	is there a way to limit the size of the buffer?
| [Tuesday 22 March 2011] [09:32:40] <Guthur>	I can check that out
| [Tuesday 22 March 2011] [09:33:00] <sustrik>	yes, please
| [Tuesday 22 March 2011] [09:33:08] <sustrik>	if there's no limit to the buffer
| [Tuesday 22 March 2011] [09:33:17] <sustrik>	it could easily exhaust all the memory
| [Tuesday 22 March 2011] [09:33:47] <sustrik>	in such case the code using IOCP would have to keep track of amount of memory in use
| [Tuesday 22 March 2011] [09:35:12] <Guthur>	oh, that does not sound ideal
| [Tuesday 22 March 2011] [09:45:48] <sustrik>	cremes: hi
| [Tuesday 22 March 2011] [09:46:01] <cremes>	sustrik: good morning
| [Tuesday 22 March 2011] [09:46:09] <sustrik>	morning
| [Tuesday 22 March 2011] [09:46:23] <sustrik>	as for the assertion, any chance of getting backtrace?
| [Tuesday 22 March 2011] [09:47:01] <cremes>	sustrik: i can try to capture it in gdb; give me a few minutes and i'll see what i can do
| [Tuesday 22 March 2011] [09:47:07] <sustrik>	ok
| [Tuesday 22 March 2011] [09:47:28] <sustrik>	another thing: the allocation mechanism you proposed
| [Tuesday 22 March 2011] [09:47:44] <sustrik>	have you found out where the memory disappers?
| [Tuesday 22 March 2011] [09:48:18] <sustrik>	(issue 174)
| [Tuesday 22 March 2011] [09:48:31] <cremes>	sustrik: i need to run your code with the patch you supplied on my linux box
| [Tuesday 22 March 2011] [09:48:45] <cremes>	i ran it on my osx box and it was disappearing in the same place as before
| [Tuesday 22 March 2011] [09:48:59] <cremes>	(the backtrace in issue 174)
| [Tuesday 22 March 2011] [09:52:32] <sustrik>	i though the proposal you made is related to 174
| [Tuesday 22 March 2011] [09:54:33] <cremes>	sustrik: it was; based on your feedback i was assuming the memory growth was due to page fragmentation caused
| [Tuesday 22 March 2011] [09:54:37] <cremes>	by small memory allocations
| [Tuesday 22 March 2011] [09:55:33] <sustrik>	afaik most allocators have per-size caches
| [Tuesday 22 March 2011] [09:55:49] <sustrik>	so you have special cache for 16 byte blocks
| [Tuesday 22 March 2011] [09:56:04] <sustrik>	another one for 32 byte blocks etc.
| [Tuesday 22 March 2011] [09:56:06] <Guthur>	sustrik: you can indeed specify a buffer size
| [Tuesday 22 March 2011] [09:56:25] <sustrik>	that in turn leads to optimal heap utilisation
| [Tuesday 22 March 2011] [09:56:48] <Guthur>	I need to check some of my resources at home though to remind myself of details of IOCP
| [Tuesday 22 March 2011] [09:56:49] <cremes>	sustrik: okay, then i don't understand why in the ticket you wrote that it's due to a known problem with malloc
| [Tuesday 22 March 2011] [09:56:55] <sustrik>	Guthur: how do you do that?
| [Tuesday 22 March 2011] [09:57:12] <Guthur>	sustrik: during the read call
| [Tuesday 22 March 2011] [09:57:31] <Guthur>	you specify a buffer and bytestoread
| [Tuesday 22 March 2011] [09:58:15] <sustrik>	Guthur: i meant limiting the send buffer
| [Tuesday 22 March 2011] [09:58:33] <sustrik>	say, totoal amount that can be used is 64kB
| [Tuesday 22 March 2011] [09:58:55] <sustrik>	attempt to exceed the buffer would mean the send call would fail
| [Tuesday 22 March 2011] [09:59:07] <sustrik>	is there anything like that in IOCP?
| [Tuesday 22 March 2011] [09:59:33] <sustrik>	cremes: the problem i referred to is that processes don't return allocated memory to the OS
| [Tuesday 22 March 2011] [10:00:13] <sustrik>	thus, it's not used, but cannot be reused by a different process
| [Tuesday 22 March 2011] [10:00:54] <cremes>	sustrik: sure, and from my research that is due to page fragmentation caused by malloc/free called on lots of small blocks (smaller than a page)
| [Tuesday 22 March 2011] [10:01:19] <sustrik>	does it return allocated memory at all?
| [Tuesday 22 March 2011] [10:01:33] <cremes>	yes, if an entire page can be freed
| [Tuesday 22 March 2011] [10:01:42] <sustrik>	that's linux?
| [Tuesday 22 March 2011] [10:01:45] <cremes>	yes
| [Tuesday 22 March 2011] [10:01:54] <sustrik>	nice
| [Tuesday 22 March 2011] [10:02:03] <cremes>	i got this from a few different write-ups that i read on stackoverflow and one other site
| [Tuesday 22 March 2011] [10:02:03] <sustrik>	iirc it wasn't the case in the past
| [Tuesday 22 March 2011] [10:02:11] <cremes>	i'll try to find them again
| [Tuesday 22 March 2011] [10:02:17] <Guthur>	sustrik: do you mean more than http://msdn.microsoft.com/en-us/library/aa365748(v=VS.85).aspx
| [Tuesday 22 March 2011] [10:02:30] <cremes>	yes, it appears that was an issue with kernel 2.4 and earlier
| [Tuesday 22 March 2011] [10:02:39] <cremes>	apparently 2.6 resolves that issue
| [Tuesday 22 March 2011] [10:05:19] <Guthur>	you could presumably build some chunking mechanism on top of that with IOCP
| [Tuesday 22 March 2011] [10:05:48] <Guthur>	send chunk 1 with Completed send chunk 2....
| [Tuesday 22 March 2011] [10:05:53] <Guthur>	with/when
| [Tuesday 22 March 2011] [10:09:16] <sustrik>	Guthur: yes, something like that
| [Tuesday 22 March 2011] [10:09:41] <sustrik>	cremes: nice
| [Tuesday 22 March 2011] [10:10:09] <sustrik>	now, the problem occurs because of 2 specific allocations
| [Tuesday 22 March 2011] [10:10:17] <sustrik>	according to the OSX tool
| [Tuesday 22 March 2011] [10:10:33] <sustrik>	1. allocating the chunk in yqueue_t
| [Tuesday 22 March 2011] [10:10:55] <sustrik>	2. allocating the encoder/decoder buffers in engine
| [Tuesday 22 March 2011] [10:11:34] <sustrik>	so, afaiu, if the size of those allocations is a muliply of page size, the problem should go away, right?
| [Tuesday 22 March 2011] [10:11:54] <sustrik>	as for 2 the size of those buffers is 8kB
| [Tuesday 22 March 2011] [10:12:07] <sustrik>	so there's no fragmentation issue
| [Tuesday 22 March 2011] [10:12:30] <sustrik>	hm, for 1. the size is 12kB
| [Tuesday 22 March 2011] [10:12:45] <sustrik>	so the fragmentation should not happen
| [Tuesday 22 March 2011] [10:13:08] <sustrik>	but given that the test is run on OSX, the allocation mechanism may be different
| [Tuesday 22 March 2011] [10:13:57] <cremes>	sustrik: true, but the memory growth is also reproducible on linux
| [Tuesday 22 March 2011] [10:14:04] <cremes>	i just don't have a tool there to show where it's happening
| [Tuesday 22 March 2011] [10:14:12] <sustrik>	:(
| [Tuesday 22 March 2011] [10:14:18] <cremes>	i am *assuming* it occurs in the same place on both OSes
| [Tuesday 22 March 2011] [10:14:36] <sustrik>	you'll have to run the test with my patch
| [Tuesday 22 March 2011] [10:14:38] <cremes>	sustrik: just to confirm, you were able to reproduce this on your linux system with that example code, right?
| [Tuesday 22 March 2011] [10:14:47] <sustrik>	that'll at least show whether it's the yqueue issue
| [Tuesday 22 March 2011] [10:15:15] <sustrik>	yes, i think so
| [Tuesday 22 March 2011] [10:15:38] <sustrik>	i assumed it was process not returning memory to the OS
| [Tuesday 22 March 2011] [10:15:53] <sustrik>	but given the issue was solved in linux/2.6
| [Tuesday 22 March 2011] [10:15:59] <sustrik>	it has to be something different
| [Tuesday 22 March 2011] [10:16:43] <cremes>	sustrik: after i try to get this backtrace for the other issue (181) i'll apply your patch on linux and run it
| [Tuesday 22 March 2011] [10:16:51] <sustrik>	thanks
| [Tuesday 22 March 2011] [10:20:46] <Guthur>	pieterh: with MDP do you see anything inherently wrong with having workers being other brokers 
| [Tuesday 22 March 2011] [10:29:00] <Guthur>	maybe even have service requests routed via a URI
| [Tuesday 22 March 2011] [10:52:13] <pieterh>	Guthur: workers can certainly be brokers as well
| [Tuesday 22 March 2011] [10:54:25] <cremes>	sustrik: got a core; do you want the output from 'bt' or from 'thread apply all bt'?
| [Tuesday 22 March 2011] [10:54:53] <sustrik>	presumably the latter
| [Tuesday 22 March 2011] [10:55:12] <cremes>	sustrik: ok... i'll give you both :)
| [Tuesday 22 March 2011] [10:55:27] <sustrik>	thx
| [Tuesday 22 March 2011] [10:55:51] <cremes>	sustrik: https://gist.github.com/881336
| [Tuesday 22 March 2011] [10:56:51] <cremes>	btw, this is off of commit 1619b3d84a04fe1886347fd83280a607
| [Tuesday 22 March 2011] [10:59:51] <sustrik>	cremes: the assertion happens in mutex destructor
| [Tuesday 22 March 2011] [10:59:57] <sustrik>	interesting
| [Tuesday 22 March 2011] [11:00:04] <sustrik>	do you console output?
| [Tuesday 22 March 2011] [11:00:23] <sustrik>	it should print out the actual error code
| [Tuesday 22 March 2011] [11:00:28] <cremes>	i don't understand the question; i have a core file... is there something else you want me to look at?
| [Tuesday 22 March 2011] [11:00:33] <sustrik>	errno
| [Tuesday 22 March 2011] [11:00:42] <cremes>	p errno?
| [Tuesday 22 March 2011] [11:00:44] <sustrik>	yes
| [Tuesday 22 March 2011] [11:00:49] <sustrik>	in the asserted thread
| [Tuesday 22 March 2011] [11:01:12] <sustrik>	thread 1
| [Tuesday 22 March 2011] [11:01:14] <sustrik>	p errno
| [Tuesday 22 March 2011] [11:01:47] <cremes>	Cannot find thread-local variables on this target
| [Tuesday 22 March 2011] [11:01:56] <sustrik>	:|
| [Tuesday 22 March 2011] [11:02:19] <sustrik>	does the program show the console output
| [Tuesday 22 March 2011] [11:02:20] <sustrik>	?
| [Tuesday 22 March 2011] [11:02:23] <sustrik>	stderr
| [Tuesday 22 March 2011] [11:02:25] <sustrik>	?
| [Tuesday 22 March 2011] [11:02:59] <sustrik>	if so, the error should be visible there
| [Tuesday 22 March 2011] [11:03:30] <cremes>	looking...
| [Tuesday 22 March 2011] [11:03:55] <sustrik>	you should see the assert there
| [Tuesday 22 March 2011] [11:04:06] <sustrik>	the line above it should be the error
| [Tuesday 22 March 2011] [11:04:59] <cremes>	all it printed was the assert from socket_base.cpp
| [Tuesday 22 March 2011] [11:05:32] <sustrik>	the stack trace shows a different assert
| [Tuesday 22 March 2011] [11:05:42] <sustrik>	is that the same run?
| [Tuesday 22 March 2011] [11:05:45] <cremes>	let me run it again and put everything to the console instead of to files (i usually redirect the output)
| [Tuesday 22 March 2011] [11:05:54] <cremes>	same run
| [Tuesday 22 March 2011] [11:05:58] <sustrik>	strange
| [Tuesday 22 March 2011] [11:06:52] <cremes>	running again...
| [Tuesday 22 March 2011] [11:12:47] <cremes>	sustrik: all it prints is:
| [Tuesday 22 March 2011] [11:12:48] <cremes>	Assertion failed: sessions.empty () (socket_base.cpp:127)
| [Tuesday 22 March 2011] [11:12:56] <cremes>	Aborted (core dumped)
| [Tuesday 22 March 2011] [11:14:00] <cremes>	the thread backtraces are the same for this core
| [Tuesday 22 March 2011] [11:15:43] <sustrik>	that's really strange
| [Tuesday 22 March 2011] [11:15:56] <sustrik>	thread 1 reports the assertion happened in mutex.hpp
| [Tuesday 22 March 2011] [11:16:06] <sustrik>	rather than in socket_base.cpp
| [Tuesday 22 March 2011] [11:16:21] <sustrik>	maybe it's optimiser's fault
| [Tuesday 22 March 2011] [11:16:23] <cremes>	i don't have an explanation :(
| [Tuesday 22 March 2011] [11:16:35] <pieterh>	cremes: are you building a debug version?
| [Tuesday 22 March 2011] [11:16:36] <sustrik>	any chance of building 0mq with optimisations disabled?
| [Tuesday 22 March 2011] [11:16:45] <cremes>	pieterh: yes, ./configure --enable-debug
| [Tuesday 22 March 2011] [11:16:53] <cremes>	sustrik: yes
| [Tuesday 22 March 2011] [11:17:11] <sustrik>	--enable-debug should turn optimisations off
| [Tuesday 22 March 2011] [11:17:16] <sustrik>	(-O0)
| [Tuesday 22 March 2011] [11:17:42] <cremes>	let me rebuild
| [Tuesday 22 March 2011] [11:17:48] <cremes>	i'll make clean first...
| [Tuesday 22 March 2011] [11:18:03] <sustrik>	cremes: wait a sec
| [Tuesday 22 March 2011] [11:18:16] <sustrik>	maybe it makes more sense to try to figure out what's failing
| [Tuesday 22 March 2011] [11:18:22] <sustrik>	are you using identities?
| [Tuesday 22 March 2011] [11:18:53] <cremes>	oops, too late
| [Tuesday 22 March 2011] [11:18:58] <cremes>	yes, i am using identities
| [Tuesday 22 March 2011] [11:19:40] <sustrik>	the failing socket seems to be xreq, right?
| [Tuesday 22 March 2011] [11:19:54] <cremes>	yes
| [Tuesday 22 March 2011] [11:20:19] <sustrik>	any chance it gets connected to two peers that happen to have the same identity
| [Tuesday 22 March 2011] [11:20:27] <sustrik>	one of them via connect, other one via bind?
| [Tuesday 22 March 2011] [11:20:42] <cremes>	let me take a quick look at the code; i want to say "no" but let me verify
| [Tuesday 22 March 2011] [11:21:02] <sustrik>	simpler question: do you bind or connect the xreq socket; or both?
| [Tuesday 22 March 2011] [11:22:33] <cremes>	hard to say
| [Tuesday 22 March 2011] [11:22:41] <cremes>	if the xreq is part of a QUEUE device, then it's binding
| [Tuesday 22 March 2011] [11:22:46] <cremes>	otherwise all other sockets connect
| [Tuesday 22 March 2011] [11:23:02] <sustrik>	never both on the same socket, right?
| [Tuesday 22 March 2011] [11:23:08] <cremes>	correct
| [Tuesday 22 March 2011] [11:24:49] <sustrik>	hm, maybe the socket_base_t happens to get destructed twice
| [Tuesday 22 March 2011] [11:24:59] <sustrik>	is it possible to add printf's to your program?
| [Tuesday 22 March 2011] [11:25:10] <cremes>	sustrik: yes
| [Tuesday 22 March 2011] [11:25:30] <cremes>	you want them added to calls to zmq_close() ?
| [Tuesday 22 March 2011] [11:25:34] <sustrik>	something like this:
| [Tuesday 22 March 2011] [11:25:55] <sustrik>	printf ("alloc %p\n", (void*) this);
| [Tuesday 22 March 2011] [11:26:07] <sustrik>	in socket_base_t constructor
| [Tuesday 22 March 2011] [11:26:09] <sustrik>	and
| [Tuesday 22 March 2011] [11:26:17] <sustrik>	printf ("dealloc %p\n", (void*) this);
| [Tuesday 22 March 2011] [11:26:21] <sustrik>	in the destructor
| [Tuesday 22 March 2011] [11:26:41] <sustrik>	that should show us whether the destructor is called twice for the same object
| [Tuesday 22 March 2011] [11:27:17] <cremes>	in the destructor, do you want this printf called first or last?
| [Tuesday 22 March 2011] [11:27:25] <cremes>	presumably first
| [Tuesday 22 March 2011] [11:27:43] <sustrik>	first
| [Tuesday 22 March 2011] [11:28:40] <cremes>	running...
| [Tuesday 22 March 2011] [11:28:55] <cremes>	hmmm, i should have separated that stuff out to stderr
| [Tuesday 22 March 2011] [11:31:59] <cremes>	how do i redirect stdout and stderr to separate files in bash?
| [Tuesday 22 March 2011] [11:33:26] <cremes>	figured it out
| [Tuesday 22 March 2011] [11:33:27] <pieterh>	cremes: someproc 2> stderr.log
| [Tuesday 22 March 2011] [11:33:30] <cremes>	running...
| [Tuesday 22 March 2011] [11:38:31] <mikko>	pieterh: did you merge the pull req?
| [Tuesday 22 March 2011] [11:38:36] <mikko>	there is prolly more coming soon
| [Tuesday 22 March 2011] [11:38:43] <mikko>	([zeromq-dev] ZMQ 2.1.3 w/OpenPGM Assertion on pgm_rate_check2())
| [Tuesday 22 March 2011] [11:38:51] <pieterh>	mikko: you mean the autoconf fix for OpenPGM in 2.1?
| [Tuesday 22 March 2011] [11:38:58] <mikko>	y
| [Tuesday 22 March 2011] [11:39:09] <mikko>	im thinking this atm
| [Tuesday 22 March 2011] [11:39:10] <pieterh>	hmm, did you see my email about sending patches instead?
| [Tuesday 22 March 2011] [11:39:14] <pieterh>	I think it's going to be simpler
| [Tuesday 22 March 2011] [11:39:37] <pieterh>	pubsub instead of reqrep
| [Tuesday 22 March 2011] [11:39:50] <mikko>	"There is a smarter way to do this, and I think it is:"
| [Tuesday 22 March 2011] [11:39:53] <pieterh>	two subscribers (martin, myself), one publisher (you)
| [Tuesday 22 March 2011] [11:40:25] <mikko>	i will update a patch and send to ML
| [Tuesday 22 March 2011] [11:40:31] <pieterh>	that's best IMO
| [Tuesday 22 March 2011] [11:41:11] <pieterh>	somewhere there's a magic git incantation to pull a commit from a random git, but I don't know it
| [Tuesday 22 March 2011] [11:41:34] <mikko>	what do you mean?
| [Tuesday 22 March 2011] [11:41:41] <mikko>	git is built on that sort of thing
| [Tuesday 22 March 2011] [11:41:49] <sustrik>	cherry-pick?
| [Tuesday 22 March 2011] [11:41:52] <mikko>	you could even pull changes from my personal repo
| [Tuesday 22 March 2011] [11:42:04] <mikko>	and if i was privileged to i could push to your home machine
| [Tuesday 22 March 2011] [11:42:38] <cremes>	sustrik: with a confirmed debug build, the backtraces are different now
| [Tuesday 22 March 2011] [11:42:41] <cremes>	sustrik: https://gist.github.com/881439
| [Tuesday 22 March 2011] [11:42:46] <cremes>	thread 1 and thread 19 look relevant
| [Tuesday 22 March 2011] [11:42:54] <cremes>	i still can't print errno
| [Tuesday 22 March 2011] [11:44:09] <sustrik>	never mind, this is the assert (empty) thing
| [Tuesday 22 March 2011] [11:44:17] <sustrik>	what about the output?
| [Tuesday 22 March 2011] [11:44:22] <pieterh>	mikko, ok, so how do we do this without using github's pull request?
| [Tuesday 22 March 2011] [11:44:27] <cremes>	lots of alloc/dealloc messages
| [Tuesday 22 March 2011] [11:44:41] <pieterh>	e.g. create an issue pointing to a remote git/commit 
| [Tuesday 22 March 2011] [11:45:02] <mikko>	pieterh: or mailing list?
| [Tuesday 22 March 2011] [11:45:11] <pieterh>	let's work it out here...
| [Tuesday 22 March 2011] [11:45:19] <sustrik>	cremes: check for 0x7f1a582a4ea0
| [Tuesday 22 March 2011] [11:45:24] <pieterh>	what git commands do I need to use to pull one commit from your git
| [Tuesday 22 March 2011] [11:45:47] <cremes>	sustrik: 1 alloc, 1 dealloc
| [Tuesday 22 March 2011] [11:46:05] <cremes>	sustrik: however, that is the *last* dealloc printed
| [Tuesday 22 March 2011] [11:46:06] <mikko>	git remote add mikko <url to my repo>
| [Tuesday 22 March 2011] [11:46:15] <pieterh>	ok
| [Tuesday 22 March 2011] [11:46:16] <sustrik>	and the printf is at the beginning of the destructor, right?
| [Tuesday 22 March 2011] [11:46:17] <mikko>	git fetch mikko
| [Tuesday 22 March 2011] [11:46:22] <mikko>	then check the hash of the commit 
| [Tuesday 22 March 2011] [11:46:23] <cremes>	correct
| [Tuesday 22 March 2011] [11:46:24] <pieterh>	git fetch --no-tags, at least
| [Tuesday 22 March 2011] [11:46:28] <mikko>	and cherry-pick it
| [Tuesday 22 March 2011] [11:46:37] <mikko>	i think that should do it
| [Tuesday 22 March 2011] [11:46:50] <sustrik>	then it's some other problem...
| [Tuesday 22 March 2011] [11:46:50] <cremes>	sustrik: line 792 is the first line of the destructor
| [Tuesday 22 March 2011] [11:47:12] <pieterh>	git fetch won't make a mess of your target git?
| [Tuesday 22 March 2011] [11:47:13] <cremes>	sustrik: i grep'ed all of the dealloc lines to their own file 'z2'
| [Tuesday 22 March 2011] [11:47:23] <sustrik>	792?
| [Tuesday 22 March 2011] [11:47:27] <sustrik>	what file?
| [Tuesday 22 March 2011] [11:47:30] <cremes>	sustrik: then ran:  wc -l z2; sort -u z2 | wc -l
| [Tuesday 22 March 2011] [11:47:35] <sustrik>	socket_base_t?
| [Tuesday 22 March 2011] [11:47:36] <cremes>	socket_base.cpp
| [Tuesday 22 March 2011] [11:47:48] <mikko>	pieterh: git-fetch - Download objects and refs from another repository
| [Tuesday 22 March 2011] [11:47:54] <mikko>	pieterh: nope
| [Tuesday 22 March 2011] [11:47:56] <sustrik>	cremes: what version?
| [Tuesday 22 March 2011] [11:48:02] <sustrik>	my socket_base.cpp ends at 790
| [Tuesday 22 March 2011] [11:48:22] <pieterh>	mikko: ok, I like cherry-pick, it's how I pull patches from sustrik
| [Tuesday 22 March 2011] [11:48:33] <cremes>	sustrik: oops, sorry, misread the vi output; line 124 of 792 (i added two printfs)
| [Tuesday 22 March 2011] [11:48:40] <pieterh>	but you have to do 'git fetch --no-tags whatever' to avoid polluting your home git
| [Tuesday 22 March 2011] [11:48:56] <sustrik>	cremes: ok
| [Tuesday 22 March 2011] [11:48:58] <pieterh>	sustrik: do you want to try cherry-pick from mikko's git?
| [Tuesday 22 March 2011] [11:49:19] <sustrik>	i want a patch on the ML
| [Tuesday 22 March 2011] [11:49:23] <sustrik>	that's the process
| [Tuesday 22 March 2011] [11:49:35] <cremes>	sustrik: anyway, by removing duplicate dealloc prints using 'sort -u' it looks like 180 sockets are dealloc'ed twice
| [Tuesday 22 March 2011] [11:49:36] <pieterh>	sustrik: you don't send me patches via the ML
| [Tuesday 22 March 2011] [11:49:43] <sustrik>	i should
| [Tuesday 22 March 2011] [11:49:43] <pieterh>	so the process isn't symmetric now
| [Tuesday 22 March 2011] [11:49:51] <pieterh>	perhaps
| [Tuesday 22 March 2011] [11:50:04] <pieterh>	sending me a commit tag is much less work for you
| [Tuesday 22 March 2011] [11:50:08] <pieterh>	and also easier for me
| [Tuesday 22 March 2011] [11:50:31] <pieterh>	if you send the URI to the commit, it's as good as a patch
| [Tuesday 22 March 2011] [11:50:36] <sustrik>	that's good for backporting
| [Tuesday 22 March 2011] [11:50:36] <pieterh>	everyone who cares can review it
| [Tuesday 22 March 2011] [11:50:47] <pieterh>	here we're porting in all directions, no back or fwd
| [Tuesday 22 March 2011] [11:50:49] <sustrik>	it's only a reference to what has to be backported
| [Tuesday 22 March 2011] [11:50:57] <pieterh>	nope, no special cases please
| [Tuesday 22 March 2011] [11:50:59] <sustrik>	with new functionality you want a full patch
| [Tuesday 22 March 2011] [11:51:26] <pieterh>	it should be a single process between any two gits
| [Tuesday 22 March 2011] [11:51:53] <pieterh>	github pull requests are eliminated because they only work between forks
| [Tuesday 22 March 2011] [11:52:03] <sustrik>	there has to be an entry point
| [Tuesday 22 March 2011] [11:52:08] <pieterh>	entry point?
| [Tuesday 22 March 2011] [11:52:18] <sustrik>	the place where patch enters the ecosystem
| [Tuesday 22 March 2011] [11:52:23] <pieterh>	one always addresses a patch/commit to the author of the target git
| [Tuesday 22 March 2011] [11:52:33] <pieterh>	entry point can be ML, that's excellent
| [Tuesday 22 March 2011] [11:52:38] <pieterh>	it's ideal for this
| [Tuesday 22 March 2011] [11:52:41] <sustrik>	yup
| [Tuesday 22 March 2011] [11:52:46] <pieterh>	but signed patches are extra effort
| [Tuesday 22 March 2011] [11:52:59] <pieterh>	and we can do it better
| [Tuesday 22 March 2011] [11:53:19] <pieterh>	i think, anyhow, and I'm sure it should be orthogonal for any two gits
| [Tuesday 22 March 2011] [11:53:35] <pieterh>	i.e. if you want to send a patch to mikko, same process
| [Tuesday 22 March 2011] [11:53:53] <sustrik>	mikko doesn't care about sign-offs
| [Tuesday 22 March 2011] [11:53:59] <sustrik>	as it's his private git
| [Tuesday 22 March 2011] [11:54:06] <pieterh>	that's a separate issue
| [Tuesday 22 March 2011] [11:54:14] <pieterh>	signed off or not, that's QC on the patch or commit
| [Tuesday 22 March 2011] [11:54:52] <pieterh>	I'd like a single process for all of us, no special cases
| [Tuesday 22 March 2011] [11:54:53] <mikko>	what about CLA?
| [Tuesday 22 March 2011] [11:54:56] <mikko>	too complicated?
| [Tuesday 22 March 2011] [11:54:58] <pieterh>	CLA?
| [Tuesday 22 March 2011] [11:55:02] <pieterh>	way too complex
| [Tuesday 22 March 2011] [11:55:04] <pieterh>	by 100x
| [Tuesday 22 March 2011] [11:55:11] <mikko>	contributor license agreement
| [Tuesday 22 March 2011] [11:55:13] <mikko>	like apache etc do
| [Tuesday 22 March 2011] [11:55:22] <pieterh>	no way, dead body over, etc.
| [Tuesday 22 March 2011] [11:55:27] <sustrik>	sign-off is simpler imo
| [Tuesday 22 March 2011] [11:55:39] <pieterh>	it creates *huge* management issues and individual developers hate it to the point of not contributing
| [Tuesday 22 March 2011] [11:56:05] <pieterh>	we switched to co-owned code and signoff last year, it's superior in every sense
| [Tuesday 22 March 2011] [11:56:21] <pieterh>	this is not relevant to the thread however
| [Tuesday 22 March 2011] [11:56:33] <pieterh>	cherry-picking is very simple for both parties
| [Tuesday 22 March 2011] [11:56:47] <mikko>	pieterh: we were a bit too drunk to discuss this properly last weds
| [Tuesday 22 March 2011] [11:56:59] <pieterh>	mikko: drunk? I'm Scottish, we don't get drunk
| [Tuesday 22 March 2011] [11:57:09] <pieterh>	oh, hang on, yes we do... but it was English beer, doesn't count
| [Tuesday 22 March 2011] [11:57:41] <pieterh>	sustrik: I'm not sure cherry-picking conforms to signing off, that's all
| [Tuesday 22 March 2011] [11:58:06] <pieterh>	but it has to, of course
| [Tuesday 22 March 2011] [11:58:19] <mikko>	can you not sign a commit?
| [Tuesday 22 March 2011] [11:58:19] <pieterh>	pulling code from a public git means it's by definition signed off
| [Tuesday 22 March 2011] [11:58:23] <pieterh>	you don't need to
| [Tuesday 22 March 2011] [11:58:38] <pieterh>	once you commit & push to a git, you license the code under whatever, LGPL etc.
| [Tuesday 22 March 2011] [11:59:08] <pieterh>	this is why pull requests work
| [Tuesday 22 March 2011] [11:59:24] <pieterh>	but they are crippled for general use
| [Tuesday 22 March 2011] [11:59:55] <pieterh>	sustrik: allow me to make a short proposal on the list, OK?
| [Tuesday 22 March 2011] [12:00:01] <sustrik>	sure
| [Tuesday 22 March 2011] [12:00:07] <pieterh>	thanks
| [Tuesday 22 March 2011] [12:00:15] <pieterh>	BTW the new C API is almost working
| [Tuesday 22 March 2011] [12:00:35] <pieterh>	it does everything I was asking for, e.g. automatic close of sockets, message reuse, etc.
| [Tuesday 22 March 2011] [12:00:51] <pieterh>	nicely emulates 2.0 semantics on termination :-)
| [Tuesday 22 March 2011] [12:01:23] <sustrik>	goodo
| [Tuesday 22 March 2011] [12:01:33] <cremes>	sustrik: i applied your patch for issue 174 and ran your minimal test case (also in that issue)
| [Tuesday 22 March 2011] [12:01:41] <cremes>	sustrik: shall i email you the output?
| [Tuesday 22 March 2011] [12:01:46] <cremes>	it's too big to pastie
| [Tuesday 22 March 2011] [12:04:04] <Guthur>	pieterh: you're scottish?
| [Tuesday 22 March 2011] [12:04:15] <pieterh>	Guthur: half Scottish, half Belgian...
| [Tuesday 22 March 2011] [12:04:24] <pieterh>	born somewhere in the middle of the North Sea
| [Tuesday 22 March 2011] [12:06:22] <Guthur>	one of those water births then
| [Tuesday 22 March 2011] [12:07:23] <pieterh>	lol
| [Tuesday 22 March 2011] [12:08:53] <Guthur>	belgians aren't renown for their seafaring as well
| [Tuesday 22 March 2011] [12:09:01] <Guthur>	I hear they don't have much of a navy
| [Tuesday 22 March 2011] [12:10:45] <pieterh>	my great-great grandfather was hung for being a pirate
| [Tuesday 22 March 2011] [12:11:28] <sustrik>	cremes: did it drop to 0?
| [Tuesday 22 March 2011] [12:11:55] <cremes>	sustrik: no, it didn't; i just sent you the output in an email with attachment
| [Tuesday 22 March 2011] [12:12:03] <sustrik>	ok
| [Tuesday 22 March 2011] [12:13:17] <sustrik>	cremes: it's looks like it's dropping
| [Tuesday 22 March 2011] [12:13:24] <sustrik>	see the end of the file
| [Tuesday 22 March 2011] [12:13:58] <sustrik>	if you let it run a bit longet it would probably get to 0
| [Tuesday 22 March 2011] [12:14:13] <sustrik>	longer*
| [Tuesday 22 March 2011] [12:14:57] <cremes>	sustrik: i let it run for 5 minutes... it didn't appear to be dropping anymore
| [Tuesday 22 March 2011] [12:15:06] <cremes>	sustrik: i'll let it go for 20m and see what happens
| [Tuesday 22 March 2011] [12:15:30] <sustrik>	it seems like it was terminated in the middle of the process of dropping
| [Tuesday 22 March 2011] [12:15:34] <sustrik>	see the last line
| [Tuesday 22 March 2011] [12:15:44] <sustrik>	it's cut in the middle of output
| [Tuesday 22 March 2011] [12:16:04] <sustrik>	356 355 354 35
| [Tuesday 22 March 2011] [12:16:06] <cremes>	sustrik: i think that's from buffered output
| [Tuesday 22 March 2011] [12:16:17] <cremes>	i was tailing the log file and it stopped there
| [Tuesday 22 March 2011] [12:16:20] <sustrik>	ah
| [Tuesday 22 March 2011] [12:16:28] <sustrik>	anyway, it dropped almost to zero
| [Tuesday 22 March 2011] [12:16:39] <sustrik>	up to 30,000
| [Tuesday 22 March 2011] [12:16:51] <sustrik>	then back to 353
| [Tuesday 22 March 2011] [12:17:18] <sustrik>	the leak is either elsewhere
| [Tuesday 22 March 2011] [12:17:28] <sustrik>	or it's process not returning memory to the OS
| [Tuesday 22 March 2011] [12:18:19] <cremes>	sustrik: i'll let it sit for a while... i just saw it go from 1 to 3200 and now it's down to 310
| [Tuesday 22 March 2011] [12:18:26] <cremes>	but it's not printing anything anymore
| [Tuesday 22 March 2011] [12:18:40] <sustrik>	hm
| [Tuesday 22 March 2011] [12:18:44] <cremes>	if it's 'cut off' due to stdout buffering, hitting ctrl-c ought to flush that buffer
| [Tuesday 22 March 2011] [12:19:02] <sustrik>	maybe a problem with the buffering itself?
| [Tuesday 22 March 2011] [12:19:27] <sustrik>	anyway, i've used simple non-buffered console
| [Tuesday 22 March 2011] [12:19:39] <sustrik>	and i saw the number of chunks dropping to 0
| [Tuesday 22 March 2011] [12:19:56] <cremes>	i don't know how to get an unbuffered xterm going
| [Tuesday 22 March 2011] [12:20:12] <sustrik>	cremes: i don't think it matters
| [Tuesday 22 March 2011] [12:20:18] <cremes>	i should probably add an explicit flush
| [Tuesday 22 March 2011] [12:20:28] <sustrik>	350 chunks won't account for all the allocated memory you see
| [Tuesday 22 March 2011] [12:20:30] <sustrik>	right?
| [Tuesday 22 March 2011] [12:20:34] <sustrik>	1 chunk = 12kb
| [Tuesday 22 March 2011] [12:20:34] <mikko>	fflush (stdout);
| [Tuesday 22 March 2011] [12:20:48] <sustrik>	x350 = 4.2MB
| [Tuesday 22 March 2011] [12:20:58] <cremes>	sustrik: do those chunks contain message data?
| [Tuesday 22 March 2011] [12:21:16] <sustrik>	how large is your message?
| [Tuesday 22 March 2011] [12:21:19] <sustrik>	8 bytes?
| [Tuesday 22 March 2011] [12:21:30] <cremes>	your test case was using a 20byte message
| [Tuesday 22 March 2011] [12:21:36] <sustrik>	ok
| [Tuesday 22 March 2011] [12:21:43] <sustrik>	then the chunks contain message data
| [Tuesday 22 March 2011] [12:23:28] <cremes>	i added fflush() and am rerunning; we'll see if that makes a difference
| [Tuesday 22 March 2011] [12:23:35] <cremes>	it did; count went to 0
| [Tuesday 22 March 2011] [12:23:50] <cremes>	resident memory is still inflated though
| [Tuesday 22 March 2011] [12:24:14] <sustrik>	the next step would be to replace all the mallocs and frees and news and deletes
| [Tuesday 22 March 2011] [12:24:28] <sustrik>	by something that would track amount of memory allocated
| [Tuesday 22 March 2011] [12:24:46] <cremes>	sustrik: i think it's easier for me to just restart my applications every 48 hours 
| [Tuesday 22 March 2011] [12:24:49] <cremes>	to free up swap
| [Tuesday 22 March 2011] [12:25:02] <sustrik>	hm
| [Tuesday 22 March 2011] [12:25:31] <sustrik>	let's keep the issue open then
| [Tuesday 22 March 2011] [12:25:37] <sustrik>	when i get some time
| [Tuesday 22 March 2011] [12:25:42] <cremes>	ok
| [Tuesday 22 March 2011] [12:25:50] <cremes>	i'll add an update with my findings
| [Tuesday 22 March 2011] [12:25:55] <spht>	Does zmq not exit in its SIGINT handler? Can't SIGINT to kill my script using the python binding..
| [Tuesday 22 March 2011] [12:26:05] <sustrik>	i'll try to check whether the memory is held by 0mq or glibc
| [Tuesday 22 March 2011] [12:27:19] <sustrik>	spht: what version of 0mq are you using?
| [Tuesday 22 March 2011] [12:27:54] <spht>	sustrik:  Python module version is 2.0.10
| [Tuesday 22 March 2011] [12:28:43] <sustrik>	there used to be a problem with SIGINT in old versions, let me check...
| [Tuesday 22 March 2011] [12:29:22] <cremes>	spht: this was fixed in the 2.1 branches
| [Tuesday 22 March 2011] [12:29:41] <cremes>	spht: time to upgrade
| [Tuesday 22 March 2011] [12:29:44] <spht>	cremes: sustrik: Ahht thanks! I'll go upgrade ASAP :)
| [Tuesday 22 March 2011] [12:29:48] <ianbarber>	mikko: about?
| [Tuesday 22 March 2011] [12:29:51] <mikko>	ianbarber: yes
| [Tuesday 22 March 2011] [12:29:55] <mikko>	bam!
| [Tuesday 22 March 2011] [12:31:02] <ianbarber>	bam!
| [Tuesday 22 March 2011] [12:31:10] <ianbarber>	so, I was translating a pieterh example
| [Tuesday 22 March 2011] [12:31:16] <ianbarber>	which measures round trip speed
| [Tuesday 22 March 2011] [12:31:48] <ianbarber>	it starts a client, worker and broker, and tries doing send() recv() 10000 time and then send() 10000 and recv() 10000
| [Tuesday 22 March 2011] [12:32:01] <ianbarber>	to compare the speed of waiting for a response versus async
| [Tuesday 22 March 2011] [12:32:24] <ianbarber>	in the c version I get ~6k/s for the first, around 50k/s for the second
| [Tuesday 22 March 2011] [12:32:32] <ianbarber>	in the PHP i get ~6k/s for both
| [Tuesday 22 March 2011] [12:33:37] <mikko>	that's interesting
| [Tuesday 22 March 2011] [12:33:40] <ianbarber>	i thought it might be because PHP was doing a msg destroy after each one, but taking that out of the c version didn't affect it
| [Tuesday 22 March 2011] [12:34:03] <mikko>	probably need to run with a profiler to see
| [Tuesday 22 March 2011] [12:35:16] <ianbarber>	yeah, i guess
| [Tuesday 22 March 2011] [13:01:46] <pieterh>	ianbarber: destroying messages, allocs, etc. don't make that much impact