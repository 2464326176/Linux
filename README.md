# Linux

# 并发

## lock

1.unique_lock是可以取代lock_guard
		unique_lock是个类模板，工作中，一般lock_guard(推荐使用)；lock_guard取代了mutex的lock()和unlock();

​		unique_lock比lock_guard灵活很多，效率上差一点，内存占用多一点。

​		unique_lock的第二个参数 lock_guard可以带第二个参数：

```c++
std::lock_guard<std::mutex> sbguard1(my_mutex1, std::adopt_lock);  // std::adopt_lock标记作用；
```

1.1 std::adopt_lock
		表示这个互斥量已经被lock了（你必须要把互斥量提前lock了 ，否者会报异常）；

​		std::adopt_lock标记的效果就是假设调用一方已经拥有了互斥量的所有权（已经lock成功了）；通知lock_guard不需要再构造函数中lock这个互斥量了。

​		unique_lock也可以带std::adopt_lock标记，含义相同，就是不希望再unique_lock()的构造函数中lock这个mutex。

​		用std::adopt_lock的前提是，自己需要先把mutex lock上；用法与lock_guard相同。

1.2 std::try_to_lock
		我们会尝试用mutex的lock()去锁定这个mutex,但如果没有锁定成功，我也会立即返回，并不会阻塞在那里；

​		用这个try_to_lock的前提是你自己不能先lock。实例代码如下：

1.3 std::defer_lock

​		用std::defer_lock的前提是，你不能自己先lock,否则会报异常

​		std::defer_lock的意思就是并没有给mutex加锁：初始化了一个没有加锁的mutex。



```c++
#defer_lock、lock()与unlock() relese() try_lock 
for (int i = 0; i < 10000; i++)
{
	cout << "inMsgRecvQueue()执行，插入一个元素" << i << endl;
	std::unique_lock<std::mutex> sbguard(my_mutex, std::defer_lock);//没有加锁的my_mutex
	sbguard.lock();//咱们不用自己unlock
	//处理共享代码

	//因为有一些非共享代码要处理
	sbguard.unlock();
	//处理非共享代码要处理。。。
	
	sbguard.lock();
	//处理共享代码
	
	msgRecvQueue.push_back(i);
	//...
	//其他处理代码
	sbguard.unlock();//画蛇添足，但也可以

}

for (int i = 0; i < 10000; i++)
{
	std::unique_lock<std::mutex> sbguard(my_mutex, std::defer_lock);//没有加锁的my_mutex

if (sbguard.try_lock() == true)//返回true表示拿到锁了
{
	msgRecvQueue.push_back(i);
	//...
	//其他处理代码
} else {
	//没拿到锁
	cout << "inMsgRecvQueue()执行，但没拿到锁头，只能干点别的事" << i << endl;
}

for (int i = 0; i < 10000; i++)
{
	std::unique_lock<std::mutex> sbguard(my_mutex);
	std::mutex *ptx = sbguard.release(); //现在你有责任自己解锁了

	msgRecvQueue.push_back(i);
	
	ptx->unlock(); //自己负责mutex的unlock了

}
```

1.4 std::unique_lock<std::mutex> sbguard(my_mutex);//所有权概念

sbguard拥有my_mutex的所有权；sbguard可以把自己对mutex(my_mutex)的所有权转移给其他的unique_lock对象；

所以unique_lock对象这个mutex的所有权是可以转移，但是不能复制。

std::unique_lock<std::mutex> sbguard1(my_mutex);

std::unique_lock<std::mutex> sbguard2(sbguard1);//此句是非法的，复制所有权是非法的

std::unique_lock<std::mutex> sbguard2(std::move(sbguard));//移动语义，现在先当与sbguard2与my_mutex绑定到一起了

//现在sbguard1指向空，sbguard2指向了my_mutex
方法1 ：std::move()

方法2：return std:: unique_lock<std::mutex>  代码如下：

std::unique_lock<std::mutex> rtn_unique_lock()
	{
		std::unique_lock<std::mutex> tmpguard(my_mutex);
		return tmpguard;//从函数中返回一个局部的unique_lock对象是可以的。三章十四节讲解过移动构造函数。
		//返回这种举报对象tmpguard会导致系统生成临时unique_lock对象，并调用unique_lock的移动构造函数
	}

```c++
void inMsgRecvQueue()
{
	for (int i = 0; i < 10000; i++)
	{
		std::unique_lock<std::mutex> sbguard1 = rtn_unique_lock();
 
		msgRecvQueue.push_back(i);
	}
}
```



在很多情况下，主线程生成并起动了子线程，如果子线程里要进行大量的耗时的运算，主线程往往将于子线程之前结束，但是如果主线程处理完其他的事务后，需要用到子线程的处理结果，也就是主线程需要等待子线程执行完成之后再结束，这个时候就要用到pthread_join()方法了。
即pthread_join()的作用可以这样理解：主线程等待子线程的终止。也就是在子线程调用了pthread_join()方法后面的代码，只有等到子线程结束了才能执行。

当A线程调用线程B并 pthread_join() 时，A线程会处于阻塞状态，直到B线程结束后，A线程才会继续执行下去。当 pthread_join() 函数返回后，被调用线程才算真正意义上的结束，它的内存空间也会被释放（如果被调用线程是非分离的）。这里有三点需要注意：

被释放的内存空间仅仅是系统空间，你必须手动清除程序分配的空间，比如 malloc() 分配的空间。
2.一个线程只能被一个线程所连接。
3.被连接的线程必须是非分离的，否则连接会出错。
所以可以看出pthread_join()有两种作用：

用于等待其他线程结束：当调用 pthread_join() 时，当前线程会处于阻塞状态，直到被调用的线程结束后，当前线程才会重新开始执行。

对线程的资源进行回收：如果一个线程是非分离的（默认情况下创建的线程都是非分离）并且没有对该线程使用 pthread_join() 的话，该线程结束后并不会释放其内存空间，这会导致该线程变成了“僵尸线程”。

