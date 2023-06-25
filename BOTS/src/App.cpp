#include "botspch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Renderer2D.h"

int main(void)
{
	Log::Init();

	BOTS_LOG_INFO("Starting BOTS App.");

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "Hello World", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	uint32_t status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	float positions[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f,
	};

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0

	};

	Shared<VertexArray> va = VertexArray::Create();
	Shared<VertexBuffer> vb = VertexBuffer::Create(positions, 4 * 2 * sizeof(float));
	Shared<IndexBuffer> ib = IndexBuffer::Create(indices, 6);
	vb->SetLayout({
		{ BufferDataType::Float2, "a_Position" }
	});

	va->AddVertexBuffer(vb);
	va->SetIndexBuffer(ib);

	Shared<Shader> shader = Shader::Create("res/shaders/Basic.shader");

	vb->Bind();
	shader->Bind();

	va->Unbind();
	vb->Unbind();
	ib->Unbind();
	shader->Unbind();

	Shared<Renderer2D> renderer = Renderer2D::Create();

	float r = 0.0f;
	float increment = 0.05f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer->Clear();

		shader->Bind();
		shader->SetFloat4("u_Color", { r, 0.6f, 0.3f, 1.0f });

		renderer->Draw(va, ib, shader);

		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;

		r += increment;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	shader->Unbind();

	glfwTerminate();
	return 0;
}
