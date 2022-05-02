#Programa que implementa QLearning para o ambiente CartPole na OpenAI.
#O programa ira terminar depois de 200 movimentos
#O agente usa uma logica randomica para aprender os movimentos e decidir qual acao tomar
#O Programa usa o algoritmo Epsilon-Greedy

import gym
import numpy as np 
import matplotlib.pyplot as plt 

env = gym.make('CartPole-v0') #estanciando o ambiente

MAXSTATES = 10**4 #Iremos ter no maximo 10.000 estados
GAMMA = 0.9
ALPHA = 0.01

def max_dict(d):
	max_v = float('-inf')
	for key, val in d.items():
		if val > max_v:
			max_v = val
			max_key = key
	return max_key, max_v

def create_bins():
	# obs[0] -> cart position --- -4.8 - 4.8
	# obs[1] -> cart velocity --- -inf - inf
	# obs[2] -> pole angle    --- -41.8 - 41.8
	# obs[3] -> pole velocity --- -inf - inf
	
	bins = np.zeros((4,10)) #Array de 4x10
	bins[0] = np.linspace(-4.8, 4.8, 10)
	bins[1] = np.linspace(-5, 5, 10)
	bins[2] = np.linspace(-.418, .418, 10)
	bins[3] = np.linspace(-5, 5, 10)

	return bins

def assign_bins(observation, bins):
	state = np.zeros(4)
	for i in range(4):
		state[i] = np.digitize(observation[i], bins[i])# funcao DIGITIZE da numpy passa o numero para binario
	return state

def get_state_as_string(state):
	string_state = ''.join(str(int(e)) for e in state)
	return string_state

def get_all_states_as_string():
	states = []
	for i in range(MAXSTATES):
		states.append(str(i).zfill(4)) #funcao ZFILL -> Retorna uma cadeia de caracteres que especifica o comprimento da cadeia original justificado à direita, frente zeros à esquerda.
	return states

def initialize_Q(): #Inicializa o Q learning
	Q = {}

	all_states = get_all_states_as_string()
	for state in all_states:
		Q[state] = {}
		for action in range(env.action_space.n):
			Q[state][action] = 0 #estado do reward inicial e do que o programa espera é ZERO
	return Q

def play_one_game(bins, Q, eps=0.5):
	observation = env.reset()
	done = False
	cnt = 0 #numero de movimentos em um episodio
	state = get_state_as_string(assign_bins(observation, bins))
	total_reward = 0

	while not done:
		cnt += 1	
		
		if np.random.uniform() < eps:
			act = env.action_space.sample() # Algoritmo que usa a estrategia de Epsilon-Greedy || Essa logica usa um numero random da Numpy que é MENOR que o algoritmo Epsilon, a partir dai o Epsilon precisa fazer uma acao randomica, que busca o maior valor possivel do reward
		else:			
			act = max_dict(Q[state])[0]
		
		observation, reward, done, _ = env.step(act)

		total_reward += reward

		if done and cnt < 200: #Reward maximo
			reward = -300          ## -300 NEGATIVO PARA ELE REALMENTE PERDER MUITO REWARD AO FRACASSAR E SEMPRE BUSCAR O MAXIMO DE VALOR POSSIVEL

		state_new = get_state_as_string(assign_bins(observation, bins)) 

		a1, max_q_s1a1 = max_dict(Q[state_new])
		Q[state][act] += ALPHA*(reward + GAMMA*max_q_s1a1 - Q[state][act]) ## Atualizando meu array do Q Learning
		state, act = state_new, a1					

	return total_reward, cnt

def play_many_games(bins, N=10000): ##setar um numero alto de jogos para ele jogar
	Q = initialize_Q()

	length = []
	reward = []
	for n in range(N):
		#eps=0.5/(1+n*10e-3)
		eps = 1.0 / np.sqrt(n+1) #a funcao EPSILON IRA diminuir conforme a quantidade de jogos indo cada vez mais fundo no aprendizado, o numero randon de acoes ira se tornar cada vez menor, isso muda completamente o comportamento do agente e tambem agiliza o processo de aprendizado

		episode_reward, episode_length = play_one_game(bins, Q, eps)
		
		if n % 100 == 0:
			print(n, '%.4f' % eps, episode_reward)
		length.append(episode_length)
		reward.append(episode_reward)

	return length, reward

def plot_running_avg(totalrewards):
	N = len(totalrewards)
	running_avg = np.empty(N)
	for t in range(N):
		running_avg[t] = np.mean(totalrewards[max(0, t-100):(t+1)])
	plt.plot(running_avg)
	plt.title("Running Average")
	plt.show()

if __name__ == '__main__':
	bins = create_bins()
	episode_lengths, episode_rewards = play_many_games(bins)

	plot_running_avg(episode_rewards)