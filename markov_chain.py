from collections import defaultdict
import string
import random

class Markov:
	def __init__(self, source_file, length):
		self.source_file = source_file
		self.length = length
		self.input_data = []
		self.trigrams = []
		self.markov_data = defaultdict(list)
		self.chain = []
		
		with open(source_file, 'r') as fin:
			input_string = format(fin.read().lower())
		self.input_data = input_string.split()	

		self.gen_trigrams()
		self.populate_dictionary()

	def format(self, line):
		return ' '.join(filter(None, (word.strip(string.punctuation) for word in line.split())))

	def gen_trigrams(self):
		self.trigrams.append(zip(self.input_data, self.input_data[1:], self.input_data[2:]))

	def populate_dictionary(self):
		for trigram_set in self.trigrams:
			for single_trigram in trigram_set:
				self.markov_data[single_trigram[:2]].append(single_trigram[2])

	def generate_markov_chain(self):
		current = random.choice(self.markov_data.keys())
		self.chain.append(current[0])
		self.chain.append(current[1])
		while (len(self.chain) < self.length):
			next_word = random.choice(self.markov_data[current])
			next_pair = (current[1], next_word)
			current = next_pair
			self.chain.append(next_word)
		return self.chain

	def look_in_the_dictionary(self):
		for key in self.markov_data:
			print key, self.markov_data[key]

	def to_string(self):
		pass
