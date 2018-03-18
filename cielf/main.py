import web
urls=("/wx", "Handle",)

class Handle(object):
	def GET(self):
		return "Hello this is ci-elf."

if __name__ == '__main__':
	app = web.application(urls, globals())
	app.run()
