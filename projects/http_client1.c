103 // 几种应用场景：

104 //    1. GET请求，异步处理数据

105 void get_data_from_server(const char *url)

106 {

107     http_client_t client;

108

109     http_client_init(&client);

110     http_client_set_url(&client, url);

111

112     if (http_client_connect(&client, NULL) != 0)

113     {

114         //分析错误原因

115     }

116

117     int total_length = 0;

118     while (1)

119     {

120         char buffer[512];

121         int bytes = http_client_get_body(&client, buffer, sizeof(buffer));

122         if (bytes < 0)

123         {

124             //分析错误原因

125         }

126         else if (bytes == 0)

127         {

128             //读取结束

129             break;

130         }

131

132         //处理数据

133

134         total_length += bytes;

135     }

136

137 //    http_client_disconnect(&client);

138     http_client_free(&client);

139 }

140

141 //      2. POST请求，发送文件到服务器

142 void post_file_to_server(const char *url, const char *file)

143 {

144     http_client_t client;

145

146     http_client_init(&client);

147     http_client_set_url(&client, url);

148     http_client_set_method(&client, HTTP_METHOD_POST);

149     http_client_set_body_file(&client, file);

150

151     if (http_client_connect(&client, &config) != 0)

152     {

153         //分析错误原因

154     }

155

156 //    http_client_disconnect(&client);

157     http_client_free(&client);

158 }

159

160 //      3.  GET请求。同步获取到文件。

161 void get_file_from_server(const char *url, const char *file)

162 {

163     http_client_t client;

164     http_config_t config;

165

166     http_client_init(&client);

167     http_config_init(&config);

168     http_client_set_url(&client, url);

169     http_config_sync(&config);

170     http_config_save_file(&config, file);

171

172     if (http_client_connect(&client, &config) != 0)

173     {

174         //分析错误原因

175     }

176

177 //    http_client_disconnect(&client);

178     http_config_free(&config);

179     http_client_free(&client);

180 }