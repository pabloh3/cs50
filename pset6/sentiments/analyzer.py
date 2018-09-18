import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        
        "open file"
        pos_file  = open(positives,"r") 
        neg_file  = open(negatives,"r") 
        
        pos=[]; neg=[]
        "read each line, if not comment save in array"
        
        for line in pos_file:
            s = pos_file.readlines(1)
            s1 = "".join(s)
            s2 = s1.strip()
            if not(s2.startswith(';')):
                pos.append(s2)
        
        for line in neg_file:
            t = neg_file.readlines(1)
            t1 = "".join(t)
            t2 = t1.strip()
            if not(t2.startswith(';')):
                neg.append(t2)
        
        self.positives = pos
        self.negatives = neg
        
        
        pos_file.close()
        neg_file.close()
        
        
    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)        
        
        f=[]
        for i in tokens:
            if i.lower() in self.positives:
                f.append(1)
            elif i.lower() in self.negatives:
                f.append(-1)
            else:
                f.append(0)
        
        f2 = sum(f) / float(len(f))
        if f2< -0.01:
            return -1
        elif f2 > 0.01:
            return 1
        else:
            return 0
