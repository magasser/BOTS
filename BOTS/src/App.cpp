#include "botspch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Core.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/Texture.h"

int main(void)
{
	Log::Init();

	BOTS_LOG_INFO("Starting BOTS App.");

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", nullptr, nullptr);
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
		100.0f, 100.0f, 0.0f, 0.0f,
		200.0f, 100.0f, 1.0f, 0.0f,
		200.0f, 200.0f, 1.0f, 1.0f,
		100.0f, 200.0f, 0.0f, 1.0f,
	};

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0

	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shared<VertexArray> va = VertexArray::Create();
	Shared<VertexBuffer> vb = VertexBuffer::Create(positions, 4 * 4 * sizeof(float));
	Shared<IndexBuffer> ib = IndexBuffer::Create(indices, 6);
	vb->SetLayout({
		{ BufferDataType::Float2, "a_Position" },
		{ BufferDataType::Float2, "u_Texture" },
	});

	va->AddVertexBuffer(vb);
	va->SetIndexBuffer(ib);

	glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(500.0f, 0.0f, 0.0f));

	Shared<Shader> shader = Shader::Create("res/shaders/Basic.shader");
	shader->Bind();

	Shared<Texture2D> texture = Texture2D::Create("res/textures/Beast.png");
	texture->Bind(0);
	shader->SetInt("u_Texture", 0);

	va->Unbind();
	vb->Unbind();
	ib->Unbind();
	shader->Unbind();

	Shared<Renderer2D> renderer = Renderer2D::Create();

	renderer->SetClearColor({ 0.2f, 0.8f, 0.4f, 1.0f });
	float r = 0.0f;
	float increment = 0.05f;

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		static glm::vec3 translation(0.0f);

		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* Render here */
		renderer->Clear();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mvp = projection * view * model;

		shader->Bind();
		shader->SetFloat4("u_Color", { r, 0.6f, 0.3f, 1.0f });
		shader->SetMat4("u_MVP", mvp);

		renderer->Draw(va, ib, shader);

		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;

		r += increment;


		ImGui::Begin("Hello, world!");

		ImGui::SliderFloat2("Translation", &translation.x, 0.0f, 1000.0f);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}

	shader->Unbind();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
