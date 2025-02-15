/*******************************************************************************
** @file:     %{Cpp:License:FileName}
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-8-13
** @version:
*******************************************************************************/

// 参考 https://www.cnblogs.com/swarmbees/p/5889297.html
#include <iostream>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <condition_variable>
#include <QString>

static const int kItemsToProduce = 100;    //计划生产的Item个数
static const int kItemRepositorySize = 5;  //缓存区存储的Item的个数
using namespace std;
std::mutex m_mutex;		//多线程标准输出同步锁

namespace SingleToSingle {
//单生产者--单消费者
    struct ItemRepository
    {
        int item_buffer[kItemRepositorySize]; // 产品缓冲区, 配合 read_position 和 write_position 模型环形队列.
        size_t read_position; // 消费者读取产品位置.
        size_t write_position; // 生产者写入产品位置.
        std::mutex mtx; // 互斥量,保护产品缓冲区
        std::condition_variable repo_not_full; // 条件变量, 指示产品缓冲区不为满.
        std::condition_variable repo_not_empty; // 条件变量, 指示产品缓冲区不为空.
    } gItemRepository; // 产品库全局变量, 生产者和消费者操作该变量.

    typedef struct ItemRepository ItemRepository;

    void ProduceItem(ItemRepository * ir, int item)
    {
        std::unique_lock<std::mutex> lock(ir->mtx);
        while (((ir->write_position + 1) % kItemRepositorySize)
               == ir->read_position)
        { // item buffer is full, just wait here.
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                //std::cout << "缓冲区满，等待缓冲区不满\n";
                std::cout << "Buffer full, wait for buffer not full.\n" << std::endl;
            }
            (ir->repo_not_full).wait(lock); // 生产者等待"产品库缓冲区不为满"这一条件发生.
        }

        (ir->item_buffer)[ir->write_position] = item; // 写入产品.
        (ir->write_position)++; // 写入位置后移.

        if (ir->write_position == kItemRepositorySize) // 写入位置若是在队列最后则重新设置为初始位置.
            ir->write_position = 0;

        (ir->repo_not_empty).notify_all(); // 通知消费者产品库不为空.
        lock.unlock(); // 解锁.
    }

    int ConsumeItem(ItemRepository *ir)
    {
        int data;
        std::unique_lock<std::mutex> lock(ir->mtx);
        // item buffer is empty, just wait here.
        while (ir->write_position == ir->read_position)
        {
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                //std::cout << "缓冲区空，等待生产者生成产品\n";
                std::cout << "The buffer is empty, waiting for the producer to produce the product.\n" << std::endl;
            }
            (ir->repo_not_empty).wait(lock); // 消费者等待"产品库缓冲区不为空"这一条件发生.
        }

        data = (ir->item_buffer)[ir->read_position]; // 读取某一产品
        (ir->read_position)++; // 读取位置后移

        if (ir->read_position >= kItemRepositorySize) // 读取位置若移到最后，则重新置位.
            ir->read_position = 0;

        (ir->repo_not_full).notify_all(); // 通知消费者产品库不为满.
        lock.unlock(); // 解锁.

        return data; // 返回产品.
    }


    void ProducerTask() // 生产者任务
    {
        for (int i = 1; i <= kItemsToProduce; ++i)
        {
            // sleep(1);
            ProduceItem(&gItemRepository, i); // 循环生产 kItemsToProduce 个产品.
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                std::cout << "Produce the product number : " << i << std::endl;
                //std::cout << QString::fromLocal8Bit("生产第 ").toStdString() << i << QString::fromLocal8Bit("个产品").toStdString() << std::endl;
            }
        }
    }

    void ConsumerTask() // 消费者任务
    {
        static int cnt = 0;
        while (1)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            int item = ConsumeItem(&gItemRepository); // 消费一个产品.
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                //std::cout << QString::fromLocal8Bit("消费第").toStdString() << item << QString::fromLocal8Bit("个产品").toStdString() << std::endl;
                std::cout << "Consume the product number : " << item << std::endl;
            }
            if (++cnt == kItemsToProduce) break; // 如果产品消费个数为 kItemsToProduce, 则退出.
        }
    }

    void InitItemRepository(ItemRepository *ir)
    {
        ir->write_position = 0; // 初始化产品写入位置.
        ir->read_position = 0; // 初始化产品读取位置.
    }

    void S2STest()
    {
        InitItemRepository(&gItemRepository);
        std::thread producer(ProducerTask); // 创建生产者线程.
        std::thread consumer(ConsumerTask); // 创建消费之线程.

        producer.join();
        consumer.join();
    }
}

namespace SingleToMulti
{
    struct ItemRepository
    {
        int item_buffer[kItemRepositorySize];
        size_t read_position;
        size_t write_position;
        size_t item_counter;
        std::mutex mtx;
        std::mutex item_counter_mtx;
        std::condition_variable repo_not_full;
        std::condition_variable repo_not_empty;
    } gItemRepository;

    typedef struct ItemRepository ItemRepository;

    void ProduceItem(ItemRepository *ir, int item)
    {
        std::unique_lock<std::mutex> lock(ir->mtx);
        while (((ir->write_position + 1) % kItemRepositorySize)
            == ir->read_position)
        {
            // item buffer is full, just wait here.
            {
                std::lock_guard<std::mutex> lock(mutex);
                //std::cout << "缓冲区满，等待缓冲区不满\n";
                std::cout << "Buffer full, wait for buffer not full.\n" << std::endl;
            }
            (ir->repo_not_full).wait(lock);
        }

        (ir->item_buffer)[ir->write_position] = item;
        (ir->write_position)++;

        if (ir->write_position == kItemRepositorySize)
            ir->write_position = 0;

        (ir->repo_not_empty).notify_all();
        lock.unlock();
    }

    int ConsumeItem(ItemRepository *ir)
    {
        int data;
        std::unique_lock<std::mutex> lock(ir->mtx);
        // item buffer is empty, just wait here.
        while (ir->write_position == ir->read_position)
        {
            {
                std::lock_guard<std::mutex> lock(mutex);
                //std::cout << "缓冲区空，等待生产者生产产品\n";
                std::cout << "The buffer is empty, waiting for the producer to produce the product.\n" << std::endl;
            }
            (ir->repo_not_empty).wait(lock);
        }

        data = (ir->item_buffer)[ir->read_position];
        (ir->read_position)++;

        if (ir->read_position >= kItemRepositorySize)
            ir->read_position = 0;

        (ir->repo_not_full).notify_all();
        lock.unlock();

        return data;
    }


    void ProducerTask()
    {
        for (int i = 1; i <= kItemsToProduce; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(6));
            ProduceItem(&gItemRepository, i);
            {
                std::lock_guard<std::mutex> lock(mutex);
//                std::cout << "生产线程" << std::this_thread::get_id()
//                    << "生产第" << i << "个产品" << std::endl;
                std::cout << "Produc thread : " << std::this_thread::get_id()
                          << " are produc the product number is : "
                          << i << std::endl;
            }
        }
        {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "Produc thread : " << std::this_thread::get_id()
                << " exit." << std::endl;
        }
    }

    void ConsumerTask()
    {
        bool ready_to_exit = false;
        while (1)
        {
        //	std::this_thread::sleep_for(std::chrono::milliseconds(6));
            std::unique_lock<std::mutex> lock(gItemRepository.item_counter_mtx);
            if (gItemRepository.item_counter < kItemsToProduce)
            {
                int item = ConsumeItem(&gItemRepository);
                ++(gItemRepository.item_counter);
                {
                    std::lock_guard<std::mutex> lock(mutex);
//                    std::cout << "消费线程" << std::this_thread::get_id()
//                        << "正在消费第" << item << "个产品" << std::endl;
                    std::cout << "Consum thread : " << std::this_thread::get_id()
                              << " are consuming the product number is : "
                              << item << std::endl;
                }
            }
            else
            {
                ready_to_exit = true;
            }
            lock.unlock();

            if (ready_to_exit == true)
            {
                break;
            }
        }
        {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "Comsum thread : " << std::this_thread::get_id()
                << " exit." << std::endl;
        }
    }

    void InitItemRepository(ItemRepository *ir)
    {
        ir->write_position = 0;
        ir->read_position = 0;
        ir->item_counter = 0;
    }

    void S2MTest()
    {
        InitItemRepository(&gItemRepository);
        std::thread producer(ProducerTask);
        std::thread consumer1(ConsumerTask);
        std::thread consumer2(ConsumerTask);
        std::thread consumer3(ConsumerTask);
        std::thread consumer4(ConsumerTask);

        producer.join();
        consumer1.join();
        consumer2.join();
        consumer3.join();
        consumer4.join();
    }
}

namespace MultiToSingle
{
    struct ItemRepository
    {
        int item_buffer[kItemRepositorySize];
        size_t read_position;
        size_t write_position;
        size_t item_counter;
        std::mutex mtx;
        std::mutex item_counter_mtx;
        std::condition_variable repo_not_full;
        std::condition_variable repo_not_empty;
    } gItemRepository;

    typedef struct ItemRepository ItemRepository;

    void ProduceItem(ItemRepository *ir, int item)
    {
        std::unique_lock<std::mutex> lock(ir->mtx);
        while (((ir->write_position + 1) % kItemRepositorySize)
            == ir->read_position)
        {
            {
                std::lock_guard<std::mutex> lock(mutex);
                //std::cout << "缓冲区满，等待缓冲区不满\n";
                std::cout << "Buffer full, wait for buffer not full.\n" << std::endl;
            }
            (ir->repo_not_full).wait(lock);
        }

        (ir->item_buffer)[ir->write_position] = item;
        (ir->write_position)++;

        if (ir->write_position == kItemRepositorySize)
            ir->write_position = 0;

        (ir->repo_not_empty).notify_all();
        lock.unlock();
    }

    int ConsumeItem(ItemRepository *ir)
    {
        int data;
        std::unique_lock<std::mutex> lock(ir->mtx);
        // item buffer is empty, just wait here.
        while (ir->write_position == ir->read_position)
        {
            {
                std::lock_guard<std::mutex> lock(mutex);
                //std::cout << "消费者等待产品中。。。\n";
                std::cout << "Consumers wait for products...\n" << std::endl;
            }
            (ir->repo_not_empty).wait(lock);
        }

        data = (ir->item_buffer)[ir->read_position];
        (ir->read_position)++;

        if (ir->read_position >= kItemRepositorySize)
            ir->read_position = 0;

        (ir->repo_not_full).notify_all();
        lock.unlock();

        return data;
    }

    void ProducerTask()
    {
        bool ready_to_exit = false;
        while (1)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::unique_lock<std::mutex> lock(gItemRepository.item_counter_mtx);
            if (gItemRepository.item_counter < kItemsToProduce)
            {
                ++(gItemRepository.item_counter);
                ProduceItem(&gItemRepository, gItemRepository.item_counter);
                {
                    std::lock_guard<std::mutex> lock(mutex);
//                    std::cout << "消费者" << std::this_thread::get_id()
//                        << "正在生产第" << gItemRepository.item_counter
//                        << "个产品" << std::endl;
                    std::cout << "Consumers : " << std::this_thread::get_id()
                              << " are produc the product number is : "
                              << gItemRepository.item_counter << std::endl;
                }
            }
            else
            {
                ready_to_exit = true;
            }
            lock.unlock();
            if (ready_to_exit == true) break;
        }
        {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "Consumer : " << std::this_thread::get_id()
                << " exit." << std::endl;
        }
    }

    void ConsumerTask()
    {
        static int item_consumed = 0;
        while (1)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            ++item_consumed;
            if (item_consumed <= kItemsToProduce)
            {
                int item = ConsumeItem(&gItemRepository);
                {
                    std::lock_guard<std::mutex> lock(mutex);
//                    std::cout << "消费者" << std::this_thread::get_id()
//                        << "正在消费第" << item << "个产品" << std::endl;
                    std::cout << "Consumers : " << std::this_thread::get_id()
                              << " are consuming the product number is : "
                              << item << std::endl;
                }
            }
            else break;
        }
        {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "Consumer : " << std::this_thread::get_id()
                << " exit." << std::endl;
        }
    }

    void InitItemRepository(ItemRepository *ir)
    {
        ir->write_position = 0;
        ir->read_position = 0;
        ir->item_counter = 0;
    }

    void M2STest()
    {
        InitItemRepository(&gItemRepository);
        std::thread producer1(ProducerTask);
        std::thread producer2(ProducerTask);
        std::thread producer3(ProducerTask);
        std::thread producer4(ProducerTask);
        std::thread consumer(ConsumerTask);

        producer1.join();
        producer2.join();
        producer3.join();
        producer4.join();
        consumer.join();
    }
}

namespace MultiToMulti
{
    struct ItemRepository
    {
        int item_buffer[kItemRepositorySize];
        size_t read_position;
        size_t write_position;
        size_t produced_item_counter;
        size_t consumed_item_counter;
        std::mutex mtx;
        std::mutex produced_item_counter_mtx;
        std::mutex consumed_item_counter_mtx;
        std::condition_variable repo_not_full;
        std::condition_variable repo_not_empty;
    } gItemRepository;

    typedef struct ItemRepository ItemRepository;

    void ProduceItem(ItemRepository *ir, int item)
    {
        std::unique_lock<std::mutex> lock(ir->mtx);
        while (((ir->write_position + 1) % kItemRepositorySize)
            == ir->read_position)
        {
            // item buffer is full, just wait here.
            {
                std::lock_guard<std::mutex> lock(mutex);
                //std::cout << "缓冲区满，生产者等待中\n";
                std::cout << "Buffer empty, producer waiting.\n" << std::endl;
            }
            (ir->repo_not_full).wait(lock);
        }

        (ir->item_buffer)[ir->write_position] = item;
        (ir->write_position)++;

        if (ir->write_position == kItemRepositorySize)
            ir->write_position = 0;

        (ir->repo_not_empty).notify_all();
        lock.unlock();
    }

    int ConsumeItem(ItemRepository *ir)
    {
        int data;
        std::unique_lock<std::mutex> lock(ir->mtx);
        // item buffer is empty, just wait here.
        while (ir->write_position == ir->read_position)
        {
            {
                std::lock_guard<std::mutex> lock(mutex);
                //std::cout << "缓冲区空，消费者等待中\n";
                std::cout << "Buffer empty, consumer waiting.\n" << std::endl;
            }
            (ir->repo_not_empty).wait(lock);
        }

        data = (ir->item_buffer)[ir->read_position];
        (ir->read_position)++;

        if (ir->read_position >= kItemRepositorySize)
            ir->read_position = 0;

        (ir->repo_not_full).notify_all();
        lock.unlock();

        return data;
    }

    void ProducerTask()
    {
        bool ready_to_exit = false;
        while (1)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::unique_lock<std::mutex> lock(gItemRepository.produced_item_counter_mtx);
            if (gItemRepository.produced_item_counter < kItemsToProduce)
            {
                ++(gItemRepository.produced_item_counter);
                ProduceItem(&gItemRepository, gItemRepository.produced_item_counter);
                {
                    std::lock_guard<std::mutex> lock(mutex);
//                    std::cout << "生产者" << std::this_thread::get_id()
//                        << "正在生产第" << gItemRepository.produced_item_counter
//                        << "个产品" << std::endl;

                    std::cout << "Producer : " << std::this_thread::get_id()
                              << " are produc the product number is : "
                              << gItemRepository.produced_item_counter << std::endl;
                }
            }
            else
            {
                ready_to_exit = true;
            }

            lock.unlock();
            if (ready_to_exit == true)
            {
                break;
            }
        }
        {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "Producer : " << std::this_thread::get_id()
                << " exit." << std::endl;
        }
    }

    void ConsumerTask()
    {
        bool ready_to_exit = false;
        while (1)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::unique_lock<std::mutex> lock(gItemRepository.consumed_item_counter_mtx);
            if (gItemRepository.consumed_item_counter < kItemsToProduce)
            {
                int item = ConsumeItem(&gItemRepository);
                ++(gItemRepository.consumed_item_counter);
                {
                    std::lock_guard<std::mutex> lock(mutex);
//                    std::cout << "Consumer" << std::this_thread::get_id()
//                        << "正在消费第" << item << "个产品" << std::endl;
                    std::cout << "Consumers : " << std::this_thread::get_id()
                              << " are consuming the product number is : "
                              << item << std::endl;
                }
            }
            else
            {
                ready_to_exit = true;
            }
            lock.unlock();
            if (ready_to_exit == true)
            {
                break;
            }
        }
        {
            std::lock_guard<std::mutex> lock(mutex);
            std::cout << "Consumer : " << std::this_thread::get_id()
                << " exit." << std::endl;
        }
    }

    void InitItemRepository(ItemRepository *ir)
    {
        ir->write_position = 0;
        ir->read_position = 0;
        ir->produced_item_counter = 0;
        ir->consumed_item_counter = 0;
    }

    void M2MTest()
    {
        InitItemRepository(&gItemRepository);
        std::thread producer1(ProducerTask);
        std::thread producer2(ProducerTask);
        std::thread producer3(ProducerTask);
        std::thread producer4(ProducerTask);

        std::thread consumer1(ConsumerTask);
        std::thread consumer2(ConsumerTask);
        std::thread consumer3(ConsumerTask);
        std::thread consumer4(ConsumerTask);

        producer1.join();
        producer2.join();
        producer3.join();
        producer4.join();

        consumer1.join();
        consumer2.join();
        consumer3.join();
        consumer4.join();
    }
}

int main()
{
    std::cout << "------SingleToSingle------start------\n" << std::endl;
    SingleToSingle::S2STest();
    std::cout << "------SingleToSingle------end------\n\n\n" << std::endl;


    std::cout << "------SingleToMulti------start------\n" << std::endl;
    SingleToMulti::S2MTest();
    std::cout << "------SingleToMulti------end------\n\n\n" << std::endl;


    std::cout << "------MultiToSingle------start------\n" << std::endl;
    MultiToSingle::M2STest();
    std::cout << "------MultiToSingle------end------\n\n\n" << std::endl;


    std::cout << "------MultiToMulti------start------\n" << std::endl;
    MultiToMulti::M2MTest();
    std::cout << "------MultiToMulti------end------\n\n\n" << std::endl;

    return 0;
}
