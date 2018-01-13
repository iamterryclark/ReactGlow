#Reference: http://docs.tweepy.org/en/v3.4.0/streaming_how_to.html
#Reference: For Filtering I took information from this code http://stackoverflow.com/questions/22889122/how-to-add-a-location-filter-to-tweepy-module
#https://github.com/tweepy/tweepy
from __future__ import absolute_import, print_function
#Tweepy Specific class handlers
from tweepy.streaming import StreamListener
from tweepy import OAuthHandler
from tweepy import Stream
from pythonosc import osc_message_builder
from pythonosc import udp_client
#Using json library to parse the information and collect only the text
import json
import argparse
import time
# Go to http://apps.twitter.com and create an app.
# The consumer key and secret will be generated for you after
consumer_key = "5UTusUZBbHivlFfroTpTyGehN"
consumer_secret = "bjfmyB37vj8hACTPy02f7a8s9gbFFk7tbpX6D63Qqvav1pv4DS"
# After the step above, you will be redirected to your app's page.
# Create an access token under the the "Your access token" section
access_token= "805905830054920192-6BtTL1l4n1UZRdqNuJRMGjyLSuAfkfU"
access_token_secret = "nk7PXcSquTOEmDKFscVQ2kIiQTPrIsGiEYnb6LpKEFxQw"
#Show in terminal all information regarding tweet
class StdOutListener(StreamListener):
    """ A listener handles tweets that are received from the stream.
    This is a basic listener that just prints received tweets to stdout.
    """
    def on_data(self, data):
        tweetJSON = json.loads(data) #Make sure the data recieved gets loading into JSON parse
        #Need to set a global variables attribute to make changes to the variables
        global tweetCol
        global tweetNum
        tweetCol = tweetJSON['text'].split(' ', 1)[0] #Collect first word only as this is the color
        tweetNum += 1 #Make a change to the varieble adding 1 everytime we recieve a tweet to count it
        print(tweetCol) #Check color is picked up properly
        print("Tweet Number " + str(tweetNum)) #Check count is working
        client.send_message("/tweetStreamCol", tweetCol)
        client.send_message("/tweetStreamNum", tweetNum)
        return True
    def on_error(self, status):
        print(status)
if __name__ == '__main__':
    tweetNum = 0 #define tweetNum here
    tweetCol = "nothing"
    #OSC parser (sends the number of tweets to openFrameworks realtime)
    #Reference: https://pypi.python.org/pypi/python-osc
    parser = argparse.ArgumentParser()
    parser.add_argument("--ip", default="localhost",
    help = "The ip of the OSC sercer")
    parser.add_argument("--port", type=int, default=12345,
    help = "The port the OSC server is listening on")
    args = parser.parse_args()
    client = udp_client.SimpleUDPClient(args.ip, args.port)
    l = StdOutListener()
    auth = OAuthHandler(consumer_key, consumer_secret)
    auth.set_access_token(access_token, access_token_secret)
    stream = Stream(auth, l)
    stream.filter(track=['yellow'], async=True)
