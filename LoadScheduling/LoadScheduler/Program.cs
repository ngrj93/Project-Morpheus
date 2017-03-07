using System;
using Eneter.Messaging.MessagingSystems.MessagingSystemBase;
using Eneter.Messaging.MessagingSystems.TcpMessagingSystem;
using Eneter.Messaging.Nodes.LoadBalancer;
using System.Diagnostics;

namespace LoadScheduler
{
    class Program
    {
        static void Main(string[] args)
        {
            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();

            // TCP messaging protocol for communication with the master node
            IMessagingSystemFactory aMessaging = new TcpMessagingSystemFactory();

            // Create load scheduler
            ILoadBalancerFactory aLoadBalancerFactory = new RoundRobinBalancerFactory(aMessaging);
            ILoadBalancer aLoadBalancer = aLoadBalancerFactory.CreateLoadBalancer();

            // Addresses of cluster compute nodes
            string[] anAvailableServices = {
                       "tcp://127.0.0.1:8071/", "tcp://127.0.0.1:8072/", "tcp://127.0.0.1:8073/","tcp://127.0.0.1:8074/" ,"tcp://127.0.0.1:8075/"};

            foreach (string anIpAddress in anAvailableServices)
            {
                aLoadBalancer.AddDuplexOutputChannel(anIpAddress);
            }

            // Create input channel listening to master node
            IDuplexInputChannel anInputChannel = aMessaging.CreateDuplexInputChannel("tcp://127.0.0.1:8060/");

            aLoadBalancer.AttachDuplexInputChannel(anInputChannel);
          

            stopWatch.Stop();
            long duration = stopWatch.ElapsedMilliseconds;
            Console.WriteLine("-------------------------------\n");
            Console.WriteLine("Ready Time : {0}ms", duration);
            Console.WriteLine("Load Scheduler is running.\r\nPress ENTER to stop.");
            stopWatch.Start();
            Console.ReadLine();
            stopWatch.Stop();
            duration = stopWatch.ElapsedMilliseconds;
            Console.WriteLine("Completion Time : {0}ms", duration);
            Console.ReadLine();
            aLoadBalancer.DetachDuplexInputChannel();
        }
    }
}
