# C++ Concurrency in Action

The source code of the Book [C++ Concurrency in Action](http://www.manning.com/williams/)
by Anthony Williams imported from the [ZIP Archive](http://www.manning.com/williams/CCiA_SourceCode.zip).
笔记：

两种方式利用并发提高性能：
第一，将一个单个任务分成几部分，且各自并行运行，从而降
低总运行时间。这就是任务并行（task parallelism）。虽然这听起来很直观，但它是一个相当
复杂的过程，因为在各个部分之间可能存在着依赖。区别可能是在过程方面——一个线程执
行算法的一部分，而另一个线程执行算法的另一个部分——或是在数据方面——每个线程在
不同的数据部分上执行相同的操作（第二种方式）。后一种方法被称为数据并行（data
parallelism）。









