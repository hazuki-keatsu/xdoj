"""
任务排序模块 - 提供基于自定义公式的权重计算排序功能
"""

import math
import re

def create_weight_function(formula):
    """
    根据用户输入的公式创建权重计算函数
    
    Parameters:
    -----------
    formula : str
        用户输入的权重计算公式
        
    Returns:
    --------
    callable
        一个接受task_data字典作为输入的函数
    """
    # 安全检查
    if not isinstance(formula, str):
        raise ValueError("公式必须是字符串")
    
    
    
    # 使用更宽松的公式检查，允许更多数学表达式
    safe_pattern = r'^[a-zA-Z0-9_\s\+\-\*\/\(\)\^\.\,\[\]\'\"]+$'
    if not re.match(safe_pattern, formula):
        # 输出详细的错误信息，帮助诊断问题
        illegal_chars = re.findall(r'[^a-zA-Z0-9_\s\+\-\*\/\(\)\^\.\,\[\]\'\"]', formula)
        print(f"公式中包含不允许的字符: {set(illegal_chars)}")
        print(f"公式: {formula}")
        
        # 尝试修复公式中可能导致问题的特殊字符
        fixed_formula = formula
        # 替换常见的错误字符
        replacements = {
            '（': '(',
            '）': ')',
            '，': ',',
            '"': '"',
            '"': '"',
            ''': "'",
            ''': "'",
            '×': '*',
            '÷': '/',
            '**': '^',  # 修复可能的 ** 写法为 ^
            '：': ':',
            '；': ';'
        }
        
        for bad, good in replacements.items():
            if bad in fixed_formula:
                fixed_formula = fixed_formula.replace(bad, good)
                
        # 如果修复后的公式通过检查，使用修复后的公式
        if re.match(safe_pattern, fixed_formula):
            print(f"已自动修复公式为: {fixed_formula}")
            formula = fixed_formula
        else:
            raise ValueError("公式包含不允许的字符，无法自动修复")
    
    # 允许的数学函数
    allowed_funcs = {
        'sqrt': math.sqrt,
        'pow': pow,
        'abs': abs,
        'min': min,
        'max': max,
        'round': round,
        'sin': math.sin,
        'cos': math.cos,
        'log': math.log,
        'log10': math.log10,
        'exp': math.exp
    }
    
    # 创建权重计算函数
    def weight_function(task_data):
        # 创建局部变量环境
        local_vars = allowed_funcs.copy()
        
        # 添加所有权重项到局部变量
        for key, value in task_data.items():
            # 跳过任务名称等非数值字段
            if key == 'name' or key == 'priority_score':
                continue
                
            try:
                local_vars[key] = float(value)
            except (ValueError, TypeError):
                local_vars[key] = 0
        
        # 处理公式中带引号的列名
        processed_formula = formula
        column_pattern = r'[\'\"](.*?)[\'\"]'
        for column_match in re.finditer(column_pattern, formula):
            column_name = column_match.group(1)
            # 替换引号包围的列名为直接引用
            processed_formula = processed_formula.replace(f"'{column_name}'", column_name)
            processed_formula = processed_formula.replace(f'"{column_name}"', column_name)
            
        # 处理使用^代替**的情况
        processed_formula = processed_formula.replace('^', '**')
            
        try:
            # 执行公式计算
            return eval(processed_formula, {"__builtins__": {}}, local_vars)
        except Exception as e:
            print(f"公式计算错误: {e}")
            print(f"尝试计算公式: {processed_formula}")
            print(f"可用变量: {', '.join(local_vars.keys())}")
            return 0
    
    return weight_function
def calculate_priority_score(task_data, formula=None, weight_columns=None):
    """
    计算任务的优先级得分，基于自定义公式或默认线性加权
    
    Parameters:
    -----------
    task_data : dict
        包含任务信息的字典
    formula : str, optional
        优先级计算公式，例如"'权重1'*0.5 + '权重2'*0.2 + '权重3'*0.3"
    weight_columns : list, optional
        权重列名列表
        
    Returns:
    --------
    float
        计算后的优先级得分，得分越高优先级越高
    """
    # 默认使用线性加权公式
    if formula is None:
        # 使用指定的权重列或任务数据中的所有数值列
        if weight_columns is None:
            weight_keys = [key for key in task_data if key != 'name' and key != 'priority_score']
        else:
            weight_keys = weight_columns
        
        if not weight_keys:
            return 0
            
        # 默认每个权重平均分配
        weight_value = 1.0 / len(weight_keys)
        formula = " + ".join([f"'{key}' * {weight_value}" for key in weight_keys])
    
    try:
        # 创建并执行权重函数
        weight_function = create_weight_function(formula)
        return weight_function(task_data)
    except Exception as e:
        print(f"计算优先级时出错: {e}")
        return 0  # 出错时返回默认值0

def topological_sort_with_weights(graph, in_degree, tasks, formula=None, weight_columns=None):
    """
    执行基于自定义公式的拓扑排序
    
    Parameters:
    -----------
    graph : dict
        表示有向图的邻接表
    in_degree : dict
        存储每个节点入度的字典
    tasks : dict
        存储任务信息的字典
    formula : str, optional
        优先级计算公式
    weight_columns : list, optional
        权重列名列表
        
    Returns:
    --------
    list
        排序后的任务ID列表
    """
    
    # 检查是否有任何权重信息
    has_weights = formula is not None or any(
        any(key.startswith('C') and key != 'name' and key != 'priority_score' for key in task_info)
        for task_info in tasks.values()
    )
    
    # 为每个任务计算优先级得分（如果有权重）
    if has_weights:
        for task_id, task_info in tasks.items():
            # 计算加权分数
            task_info['priority_score'] = calculate_priority_score(task_info, formula, weight_columns)
    else:
        # 没有权重时，为所有任务赋予相同的优先级
        for task_id, task_info in tasks.items():
            task_info['priority_score'] = 0
    
    # 初始化队列，包含所有入度为0的节点
    queue = []
    for task_id, degree in in_degree.items():
        if degree == 0:
            queue.append(task_id)
    
    # 按优先级得分对相同入度的任务排序（得分高的先执行）
    if has_weights:
        queue.sort(key=lambda x: -tasks.get(x, {}).get('priority_score', 0))
    
    result = []
    in_degree_copy = in_degree.copy()  # 复制入度字典以避免修改原始数据
    
    # 进行拓扑排序
    while queue:
        curr_task = queue.pop(0)  # 取出队列中的第一个任务
        result.append(curr_task)
        
        # 更新相邻节点的入度
        next_level_tasks = []
        for next_task in graph.get(curr_task, []):
            in_degree_copy[next_task] -= 1
            if in_degree_copy[next_task] == 0:
                next_level_tasks.append(next_task)
        
        # 对下一级可执行的任务按优先级得分排序（如果有权重）
        if has_weights:
            next_level_tasks.sort(key=lambda x: -tasks.get(x, {}).get('priority_score', 0))
            
        queue.extend(next_level_tasks)
    
    return result

def detect_cycles(graph, tasks):
    """检测有向图中的循环，找出不能被拓扑排序的任务"""
    # 创建已访问节点集合
    visited = set()
    temp_visited = set()
    cycles = set()
    
    def dfs(node):
        if node in temp_visited:
            # 检测到循环
            cycles.add(node)
            return True
        
        if node in visited:
            return False
            
        temp_visited.add(node)
        
        # 访问所有邻居节点
        for neighbor in graph.get(node, []):
            if dfs(neighbor):
                cycles.add(neighbor)
                return True
                
        temp_visited.remove(node)
        visited.add(node)
        return False
    
    # 对每个未访问的节点执行DFS
    for node in tasks:
        if node not in visited:
            dfs(node)
    
    return cycles

def analyze_unprocessed_tasks(result, tasks, graph):
    """分析未被排序的任务，找出原因"""
    unprocessed = set(tasks.keys()) - set(result)
    
    # 检测循环
    cycles = detect_cycles(graph, tasks)
    
    # 找出没有入度但也不在排序结果中的孤立节点
    isolated = set()
    for task_id in unprocessed:
        if task_id not in cycles:
            is_isolated = True
            for source in graph:
                if task_id in graph[source]:
                    is_isolated = False
                    break
            if is_isolated and not graph.get(task_id):
                isolated.add(task_id)
    
    return {
        "unprocessed_count": len(unprocessed),
        "unprocessed_tasks": unprocessed,
        "cycles": cycles,
        "isolated": isolated
    }
    
if __name__ == "__main__":
    pass