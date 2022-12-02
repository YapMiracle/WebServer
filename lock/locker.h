/*
 * @Author: mirac
 * @Date: 2022-12-1 15.06
 * @LastEditTime: 2022-12-1
 * @LastEditors: mirac
 */

/**
 * what is pthread_cond_wait ...:
 * https://blog.csdn.net/zzran/article/details/8830213
 */
#ifndef WEBSERVER_LOCKER_H
#define WEBSERVER_LOCKER_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>
namespace webserver
{
class locker {
public:
    locker(){
        if(pthread_mutex_init(&m_mutex, nullptr)!=0){
            throw std::exception();
        }
    }
    ~locker(){
        pthread_mutex_destroy(&m_mutex);
    }
    inline bool lock(){
        return pthread_mutex_lock(&m_mutex);
    }
    inline bool unlock(){
        return pthread_mutex_unlock(&m_mutex);
    }
    pthread_mutex_t* get(){
        return &m_mutex;
    }
private:
    pthread_mutex_t m_mutex;
};

class sem {
public:
    sem(){
        if(sem_init(&m_sem, 0, 0)!=0){
            throw std::exception();
        }
    }
    sem(int num) {
        if(sem_init(&m_sem, 0, num)!=0){
            throw std::exception();
        }
    }
    ~sem(){
        sem_destroy(&m_sem);
    }

    inline bool wait(){
        return sem_wait(&m_sem);
    }

    inline bool post(){
        return sem_post(&m_sem) == 0;
    }
private:
    sem_t m_sem;
};

class cond {
public:
    cond(){
        if(pthread_cond_init(&m_cond, nullptr)!=0){
            throw std::exception();
        }
    }
    ~cond(){
        pthread_cond_destroy(&m_cond);
    }

    inline bool wait(pthread_mutex_t* mutex){
        int ret=0;
        ret = pthread_cond_wait(&m_cond, mutex);
        return ret==0;
    }
    inline bool timewait(pthread_mutex_t* mutex, struct timespec t){
        int ret=0;
        ret = pthread_cond_timedwait(&m_cond, mutex, &t);
        return ret==0;
    }
    inline bool signal(){
        return pthread_cond_signal(&m_cond) == 0;
    }
    inline bool broadcast(){
        return pthread_cond_broadcast(&m_cond) == 0;
    }
private:
    pthread_cond_t m_cond;
};
} // namespace webserver

#endif //WEBSERVER_LOCKER_H
