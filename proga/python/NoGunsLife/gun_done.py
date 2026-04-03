import math
from random import randint as rnd
from random import choice
from random import choices

import pygame
import pygame.freetype
pygame.init()

FPS = 30

RED = 0xFF0000
BLUE = 0x0000FF
YELLOW = 0xFFC91F
GREEN = 0x00FF00
MAGENTA = 0xFF03B8
CYAN = 0x00FFCC
BLACK = (0, 0, 0)
WHITE = 0xFFFFFF
GREY = 0x7D7D7D
GAME_COLORS = [RED, BLUE, YELLOW, GREEN, MAGENTA, CYAN]

WIDTH = 800
HEIGHT = 600
GAME_FONT = pygame.freetype.SysFont('Comic Sans MS', 16)

TARGET_SPRITE = 'target.png'
BODY_SPRITE = 'body.png'
GUN_SPRITE = 'gun.png'
BULLET_SPRITE = 'shot.png'
EXPLOSIVE_SPRITE = 'explosive.png'

class Target(pygame.sprite.Sprite):
	
	def __init__(self):
		super().__init__()
		self.x = rnd(600, 708)
		self.y = rnd(300, 550)
		self.vx = rnd(1, 10)
		self.vy = rnd(1, 10)
		self.image = pygame.image.load(TARGET_SPRITE)
		self.size = self.image.get_size()
		self.image = pygame.transform.scale(self.image, (max(self.size[0]/2*(self.vx/10), 10), max(self.size[1]/2*(self.vx/10), 10)))
		self.rect = self.image.get_rect()
		self.rect.center = [self.x, self.y]
		self.score = 0
	
	def move(self):
		if self.x - self.rect.w/2 <= 0 or self.x + self.rect.w/2 >= WIDTH: self.vx *= -1
		if self.y - self.rect.h/2 <= 0 or self.y + self.rect.h/2 >= HEIGHT: self.vy *= -1
		self.x += self.vx
		self.y -= self.vy
		self.rect.center = [self.x, self.y]
	
	def hit(self):
		self.score += 1
	
	def update(self):
		self.move()

class Bullet(pygame.sprite.Sprite):

	def __init__(self, x, y, vx, vy, typ = 'rand'):
		super().__init__()
		self.x = x
		self.y = y
		self.vx = vx
		self.vy = vy
		
		if typ == 'rand':
			self.type = choices(['std', 'explosive'], weights = [80, 20], k=1)[0]
		else:
			self.type = typ
		
		if self.type == 'std':
			self.image = self.image = pygame.image.load(BULLET_SPRITE)
		elif self.type == 'explosive':
			self.image = pygame.image.load(EXPLOSIVE_SPRITE)
		
		#print(self.type) #DEBUG
		#self.image = pygame.image.load(BULLET_SPRITE) #DEPRICATED
		self.size = self.image.get_size()
		self.orig = pygame.transform.scale(self.image, (self.size[0]/1.5, self.size[1]/1.5))
		self.image = self.orig
		self.size = self.image.get_size()
		self.rect = self.image.get_rect()
		self.rect.center = [self.x, self.y]
		
		self.angle = math.atan2(self.vy, self.vx)
	
	def explode(self):
		#print('explosive!')
		bullets.remove(self)
		v = 0.7*(math.sqrt(self.vx**2 + self.vy**2))
		angle = -math.pi
		for i in range(8):
			angle += math.pi/8
			vx = v*math.cos(angle)
			vy = v*math.sin(angle)
			bullets.add(Bullet(self.x, self.y, vx, vy, typ = 'std'))
	
	def move(self):
		if self.type == 'std':
			if self.x + self.rect.w/2 >= WIDTH: self.vx *= -1
			if self.y - self.rect.h/2 <= 0: self.vy *= -1
		#print(str(rnd(1, 100)) + ' ' + str(len(pygame.sprite.spritecollide(self, targets, False))))
		if self.type == 'explosive' and (self.x + self.rect.w/2 >= WIDTH or self.x - self.rect.w/2 <= 0 or self.y - self.rect.h/2 <= 0 or self.y + self.rect.h >= HEIGHT):
			self.explode()
		self.x += self.vx
		self.vy -= 0.6
		self.y -= self.vy
		self.rect.center = [self.x, self.y]
	
	def align(self):
		self.angle = math.atan2(self.vy, self.vx)
		self.image = pygame.transform.rotozoom(self.orig, self.angle*180/math.pi, 1)
		self.rect = self.image.get_rect(center = self.rect.center)
	
	'''
	def hitcheck(self, sprite):
		col = pygame.sprite.collide_rect(self, sprite1)
		return 
	'''
	
	def update(self):
		self.move()
		self.align()

class Gun(pygame.sprite.Sprite):

	def __init__(self, x, y, base_power = 10):
		super().__init__()
		self.x = x
		self.y = y
		
		self.image = pygame.image.load(GUN_SPRITE)
		self.size = self.image.get_size()
		self.orig = pygame.transform.scale(self.image, (self.size[0]*4, self.size[1]*4))
		self.size = self.image.get_size()
		self.image = self.orig
		self.rect = self.image.get_rect()
		
		self.pivot = (self.x, self.y)
		self.rect.center = (self.x + self.rect.w/2, self.y + self.rect.h/2)
		self.angle = 0
		self.shooting = False
		self.power = base_power
	
	def rotate(self):
		#offset = pygame.math.Vector2(self.rect.w/2, self.rect.h/2).rotate(-1*self.angle) #depricated
		offset = (self.rect.w/2*math.cos(self.angle), self.rect.h/2*math.sin(self.angle))
		newCenterPos = (self.pivot[0] + offset[0], self.pivot[1] - offset[1])
		#print(self.pivot, offset, newCenterPos) #debug
		self.image = pygame.transform.rotozoom(self.orig, self.angle*180/math.pi, 1)
		self.rect = self.image.get_rect(center = newCenterPos)
		
	
	def targetting(self, event):
		try:
			self.angle = math.atan2(-event.pos[1]+self.y, event.pos[0]-self.x)
		except:
			pass
		self.rotate()
	
	def shoot(self):
		vx = self.power*math.cos(self.angle)
		vy = self.power*math.sin(self.angle)
		new_bullet = Bullet(self.rect.center[0] + self.rect.w*math.cos(self.angle), self.rect.center[1] - self.rect.h*math.sin(self.angle), vx, vy)
		self.shooting = False
		return new_bullet
	
	def charge(self):
		if self.shooting:
			if self.power <= 100:
				self.power += 1
			pygame.draw.polygon(screen, RED, [(self.x, self.y), (self.x + 5, self.y), (self.x, self.y + 5), (self.x + 5, self.y + 5)])
		else:
			self.power = 10

	
	def update(self): self.rotate()

class Tank(pygame.sprite.Sprite):

	def __init__(self, x, y):
		super().__init__()
		self.x = x
		self.y = y
		self.v = 0
		self.a = 0
		self.image = pygame.image.load(BODY_SPRITE)
		self.size = self.image.get_size()
		self.image = pygame.transform.scale(self.image, (self.size[0]*4, self.size[1]*4))
		self.size = self.image.get_size()
		self.rect = self.image.get_rect()
		self.rect.center = (x, y)
		self.gun = Gun(x, y - self.rect.h/2 + 2)
		
	def shoot(self): self.gun.shoot()
	
	def move(self):
		if self.x - self.rect.w/2 <= 0 or self.x + self.rect.w/2 >= WIDTH: self.v *= -1
		self.v += self.a
		self.x += self.v
		self.rect.center = (self.x, self.y)
		self.gun.pivot = (self.x, self.y - self.rect.h/2 + 2)
	
	def update(self):
		self.move()
		if abs(self.v) <= 0.05:
			self.a = 0
			self.v = 0

screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()

targets = pygame.sprite.Group()
for t in range(3):
	targets.add(Target())
	
guns = pygame.sprite.Group()
#gun1 = Gun(WIDTH/2, HEIGHT/2)
#guns.add(gun1)

tanks = pygame.sprite.Group()
tank1 = Tank(WIDTH/2, HEIGHT - 22)
gun1 = tank1.gun
tanks.add(tank1)
guns.add(gun1)

bullets = pygame.sprite.Group()
score = 0

running = True

while running:
	screen.fill(YELLOW)
	targets.draw(screen)
	tanks.draw(screen)
	guns.draw(screen)
	bullets.draw(screen)
	GAME_FONT.render_to(screen, (10, 10), str(score), (0, 0, 0))
	pygame.display.update()
	
	clock.tick(FPS)
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			running = False
		elif event.type == pygame.MOUSEBUTTONDOWN:
			gun1.shooting = True
		elif event.type == pygame.MOUSEBUTTONUP:
			bullets.add(gun1.shoot())
		elif event.type == pygame.MOUSEMOTION:
			gun1.targetting(event)
		elif event.type == pygame.KEYDOWN:
			if event.key == pygame.K_a:
				tank1.a = -0.2
			if event.key == pygame.K_d:
				tank1.a = 0.2
		elif event.type == pygame.KEYUP:
			tank1.a = -0.05*tank1.v
	
	targets.update()
	#print(bullets)
	tanks.update()
	guns.update()
	bullets.update()
	#guns.update()
	if pygame.sprite.groupcollide(targets, bullets, True, True):
		score += 1
		targets.add(Target())
	gun1.charge()
	
pygame.quit()
