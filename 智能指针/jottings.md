>文件更新日志
>***-version:0.1***
>***-date:2024/04/24***

参考：
[https://blog.csdn.net/weixin_43908419/article/details/131060402](https://blog.csdn.net/weixin_43908419/article/details/131060402)
[https://blog.csdn.net/Albert_weiku/article/details/125715913](https://blog.csdn.net/Albert_weiku/article/details/125715913)
[https://blog.csdn.net/shaosunrise/article/details/85158249](https://blog.csdn.net/shaosunrise/article/details/85158249)

## 智能指针
智能指针RAII(Resource Acquisition Is Initialization)，是一种利用对象的生命周期来管理资源的技术。如果我们采用传统的new/delete来申请和释放资源，<font color='red'>如果忘记调用delete，或者在调用delete之前程序抛出异常，都会导致内存泄漏问题。</font>

智能指针是一个"类"，在对象构造时调用构造函数获取资源，在对象生命周期内，保证资源不被释放，在对象生命周期结束时，编译器自动调用析构函数来释放资源。这就相当于，将管理资源的责任移交给了对象，这样即使程序抛出异常也不存在内存泄漏，因为捕获异常往往跳出函数体，执行流会离开对象的作用域，对象生命周期结束，编译器自动调用析构函数释放了资源。

采用智能指针管理资源，有如下优点：
- 将资源管理的责任转移给智能指针对象，不用显示地释放资源，杜绝了异常安全问题。
- 保证对象管理的资源在其生命周期内有效。

## 智能指针的类型
C++11 提供了3种智能指针类型，它们分别由unique_ptr类（独占指针）、shared_ptr类(共享指针)和weak_ptr 类(弱指针)定义。
- 独占指针：unique_ptr是C++ 11 提供的用于防止内存泄漏的智能指针中的一种实现，独享被管理对象指针所有权的智能指针。unique_ptr对象包装一个原始指针，并负责其生命周期。当该对象被销毁时，会在其析构函数中删除关联的原始指针。unique_ptr具有->和*运算符重载符，因此它可以像普通指针一样使用。
    - ```unique_ptr<Task>``` 对象manPtr接受原始指针作为参数。现在当main函数退出时，该对象超出作用范围就会调用其析构函数，在unique_ptr对象manPtr的析构函数中，会删除关联的原始指针，这样就不用专门delete manPtr对象了。这样不管函数正常退出还是异常退出（由于某些异常），也会始终调用taskPtr的析构函数。因此，原始指针将始终被删除并防止内存泄漏。
        实例code：
        ```c++
        std::unique_ptr<Man> manPtr(new Man(25 ,"cjm"));//创建一个Man类的独占指针
        int cjmAge=manPtr->getAge(); //访问成员
        ```
    - <font color='red'>unique_ptr独享所有权:</font>unique_ptr对象始终是关联的原始指针的唯一所有者。我们无法复制unique_ptr对象，它只能移动。由于每个unique_ptr对象都是原始指针的唯一所有者，因此在其析构函数中它直接删除关联的指针，不需要任何参考计数。
        实例code：
        ```c++
        // std::unique_ptr<Man> manPtr1= manPtr;//不能直接复制 无法通过编译
        ```
    - 转移 unique_ptr 对象的所有权 我们无法复制 unique_ptr 对象，但我们可以转移它们。这意味着 unique_ptr 对象可以将关联的原始指针的所有权转移到另一个 unique_ptr 对象。
        实例code：
        ```c++
            std::unique_ptr<Man> manPtr(new Man(25 ,"cjm"));//创建一个Man类的独占指针
            int cjmAge=manPtr->getAge(); //访问成员
            // std::unique_ptr<Man> manPtr1= manPtr;//不能直接复制 无法通过编译

            std::unique_ptr<Man> manPtrMove =std::move(manPtr);
            if(manPtrMove!=nullptr){
                std::cout<<"manPtrMove not null and its name is "<<manPtrMove->name_.c_str()<<std::endl;
                // std::cout<<manPtrMove->getName()<<std::endl;
            }
            if(manPtr == nullptr){
                std::cout<<"manPtr is null now!"<<std::endl;
            }
        ```
- 共享指针：共享指针将记录有多少个指针共同享有某个对象的所有权。当有更多指针被设置为指向该对象时，引用计数随之增加；当指针和对象分离时，则引用计数也相应减少。当引用计数降低至0时，该对象被删除。
    - 每个shared_ptr对象在内部指向两个内存位置：
        1、指向对象的指针。
        2、用于控制引用计数数据的指针。
    - 共享所有权如何在参考计数的帮助下工作：
        1、当新的 shared_ptr 对象与指针关联时，则在其构造函数中，将与此指针关联的引用计数增加1。
        2、当任何 shared_ptr 对象超出作用域时，则在其析构函数中，它将关联指针的引用计数减1。如果引用计数变为0，则表示没有其他 shared_ptr 对象与此内存关联，在这种情况下，它使用delete函数删除该内存。
    - 创建shared指针
        实例code
        ```c++
        std::shared_ptr<Man> manPtr (new Man(25,"demo")); //创建一个共享指针
        std::cout<<manPtr.use_count()<<std::endl; //计数 1
        std::cout<<manPtr->getName().c_str()<<std::endl;

        std::shared_ptr<Man> manPtr1=manPtr; //直接复制
        std::cout<<manPtr1.use_count()<<std::endl; //计数 2

        manPtr->name_="ABC";
        std::cout<<manPtr1->getName().c_str()<<std::endl; // ABC

        //创建一个空的sharedpointer 
        std::shared_ptr<Man> manPtr2;
        manPtr2=manPtr1;
        std::cout<<manPtr1.use_count()<<std::endl; //计数 3
        ```






