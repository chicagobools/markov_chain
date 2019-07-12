from markov_chain import Markov
import sys

obj = Markov(sys.argv[1], int(sys.argv[2]))
print ' '.join(obj.generate_markov_chain())