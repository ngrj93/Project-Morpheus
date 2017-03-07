using System;
using System.Windows.Forms;
using Eneter.Messaging.EndPoints.TypedMessages;
using Eneter.Messaging.MessagingSystems.MessagingSystemBase;
using Eneter.Messaging.MessagingSystems.TcpMessagingSystem;

namespace Client
{
    public partial class MasterNode : Form
    {
        public class Range
        {
            public double From;
            public double To;
        }

        public MasterNode()
        {
            InitializeComponent();
            OpenConnection();
        }

        public void OpenConnection()
        {
            // Establish connection with load scheduling module
            IMessagingSystemFactory myMessaging = new TcpMessagingSystemFactory();
            IDuplexOutputChannel anOutputChannel = myMessaging.CreateDuplexOutputChannel("tcp://127.0.0.1:8060/");
            IDuplexTypedMessagesFactory aSenderFactory = new DuplexTypedMessagesFactory();
            mySender = aSenderFactory.CreateDuplexTypedMessageSender<double, Range>();

            // Event handler on receipt of response
            mySender.ResponseReceived += OnResponseReceived;

            // Attach the output channel to send messages and receive responses
            mySender.AttachDuplexOutputChannel(anOutputChannel);
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            mySender.DetachDuplexOutputChannel();
        }

        private void CalculatePiBtn_Click(object sender, EventArgs e)
        {
            myCalculatedPi = 0.0;

            // Split calculation of PI to 400 ranges
            for (double i = -1.0; i <= 1.0; i += 0.005)
            {
                Range anInterval = new Range() { From = i, To = i + 0.005 };
                mySender.SendRequestMessage(anInterval);
            }
        }

        private void OnResponseReceived(object sender, TypedResponseReceivedEventArgs<double> e)
        {
            // Incremental calculation of PI
            myCalculatedPi += e.ResponseMessage;

            // UI control can be used only from the UI thread
            InvokeInUIThread(() => ResultTextBox.Text = myCalculatedPi.ToString());
        }

        private void InvokeInUIThread(Action uiMethod)
        {
            if (InvokeRequired)
            {
                Invoke(uiMethod);
            }
            else
            {
                uiMethod();
            }
        }

        private IDuplexTypedMessageSender<double, Range> mySender;
        private double myCalculatedPi;
    }
}
