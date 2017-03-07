using System;
using System.Collections.Generic;
using System.Net;
using System.Net.NetworkInformation;
using Eneter.Messaging.EndPoints.TypedMessages;
using Eneter.Messaging.MessagingSystems.MessagingSystemBase;
using Eneter.Messaging.MessagingSystems.TcpMessagingSystem;

namespace PiCalculator
{
    public class Range
    {
        public double From;
        public double To;
    }

    class Program
    {
        static void Main(string[] args)
        {
            string aServiceAddress = GetMyAddress();
            if (aServiceAddress == "")
            {
                Console.WriteLine("The service could not start because all possible ports are occupied");
                return;
            }

            // TCP message protocol for receiving requests
            IMessagingSystemFactory aMessaging = new TcpMessagingSystemFactory();
            IDuplexInputChannel anInputChannel = aMessaging.CreateDuplexInputChannel(aServiceAddress);

            IDuplexTypedMessagesFactory aReceiverFactory = new DuplexTypedMessagesFactory();
            IDuplexTypedMessageReceiver<double, Range> aReceiver
                = aReceiverFactory.CreateDuplexTypedMessageReceiver<double, Range>();

            aReceiver.MessageReceived += OnMessageReceived;

            aReceiver.AttachDuplexInputChannel(anInputChannel);

            Console.WriteLine("Root Square Calculator listening to " + aServiceAddress +
                " is running.\r\n Press ENTER to stop.");
            Console.ReadLine();

            aReceiver.DetachDuplexInputChannel();
        }

        private static void OnMessageReceived(object sender, TypedRequestReceivedEventArgs<Range> e)
        {
            Console.WriteLine("Calculate From: {0} To: {1}", e.RequestMessage.From, e.RequestMessage.To);

            // Calculate requested range.
            double aResult = 0.0;
            double aDx = 0.000000001;
            for (double x = e.RequestMessage.From; x < e.RequestMessage.To; x += aDx)
            {
                aResult += 2 * Math.Sqrt(1 - x * x) * aDx;
            }

            // Response back the result.
            IDuplexTypedMessageReceiver<double, Range> aReceiver
                = (IDuplexTypedMessageReceiver<double, Range>)sender;
            aReceiver.SendResponseMessage(e.ResponseReceiverId, aResult);
        }

        // Helper method to get the address
        private static string GetMyAddress()
        {
            List<int> aPossiblePorts = new List<int>(new int[]{ 8071, 8072, 8073, 8074, 8075});
            IPGlobalProperties anIpGlobalProperties = IPGlobalProperties.GetIPGlobalProperties();
            IPEndPoint[] aTcpListeners = anIpGlobalProperties.GetActiveTcpListeners();

            // Remove from the possible ports those which are used
            foreach (IPEndPoint aListener in aTcpListeners)
            {
                aPossiblePorts.Remove(aListener.Port);
            }

            // Get the first available port
            if (aPossiblePorts.Count > 0)
            {
                return "tcp://127.0.0.1:" + aPossiblePorts[0] + "/";
            }

            return "";
        }

    }
}
